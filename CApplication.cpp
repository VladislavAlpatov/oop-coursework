//
// Created by alpat on 30.03.2023.
//

#include "CApplication.h"
#include <iostream>

#include "Objects/CObject2.h"
#include "Objects/CObject3.h"
#include "Objects/CObject4.h"
#include "Objects/CObject5.h"
#include "Objects/CObject6.h"

#define MAKE_SIGNAL( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define MAKE_HANDLER( handler_f ) ( TYPE_HANDLER ) ( & handler_f )

CApplication::CApplication() : CBase(nullptr, "RootObject")
{

}

void CApplication::BuildTree()
{
    std::cin >> m_sName;
	m_iReadiness = 1;

    while (true)
    {
		std::string sPathToHeadObject;
		std::string sNewObjectName;
		int         iClassType;

		std::cin >> sPathToHeadObject;

		if (sPathToHeadObject == "endtree")
			break;

		std::cin >> sNewObjectName >> iClassType;

		auto pHeadObject = GetObjectByPath(sPathToHeadObject);

		if (!pHeadObject)
		{
			printf("Object tree\n");
			PrintMultyLine();
			printf("\nThe head object %s is not found\n", sPathToHeadObject.c_str());
			exit(1);
		}

		if (pHeadObject->HasChild(sNewObjectName) || !IsNameIsNotCausePathConflict(sNewObjectName))
		{
			printf("%s    Dubbing the names of subordinate objects\n", sPathToHeadObject.c_str());
			continue;
		}

		CreateObjectByNumber(iClassType, pHeadObject, sNewObjectName)->SetReadiness(1);

	}
	while (true)
	{
		std::string sPathToSignalSenderObject;
		std::string sPathTargetObject;

		std::cin >> sPathToSignalSenderObject;
		if (sPathToSignalSenderObject == "end_of_connections")
			break;

		std::cin >> sPathTargetObject;

		const auto pSignalStartObject   = GetObjectByPath(sPathToSignalSenderObject);
		const auto pHandleTargetObject  = GetObjectByPath(sPathTargetObject);

		if (!pSignalStartObject)
		{
			printf("Object %s not found\n", sPathToSignalSenderObject.c_str());
			return;
		}
		if (!pHandleTargetObject)
		{
			printf("Handler object %s not found\n", sPathTargetObject.c_str());
			return;
		}

		pSignalStartObject->SetConnection(GetObjectSignal(pSignalStartObject),pHandleTargetObject, GetObjectHandle(pHandleTargetObject));

	}
}

int CApplication::ExecApp()
{
	printf("Object tree\n");
	PrintMultyLine();
	CBase* pCurrentObject = this;
	while (true)
	{
		std::string sCommandName;
		std::cin >> sCommandName;

		if (sCommandName == "END")
			break;

		if (sCommandName == "FIND")
		{
			std::string sPath;
			std::cin >> sPath;

			FindObjectByPath(pCurrentObject, sPath);

		}
		else if (sCommandName == "MOVE")
		{
			std::string sPath;
			std::cin >> sPath;

			MoveObject(pCurrentObject, sPath);
		}
		else if (sCommandName == "DELETE")
		{
			std::string sChildName;
			std::cin >> sChildName;

			DeleteChildByName(pCurrentObject, sChildName);
		}
		else if (sCommandName == "SET")
		{
			std::string sChildName;
			std::cin >> sChildName;

			SetCurrentObject(pCurrentObject, sChildName);
		}
		else if (sCommandName == "EMIT")
		{
			std::string sPathToObject;
			std::string sText;
			std::cin >> sPathToObject;
			std::getline(std::cin, sText);

			EmitSignalForObject(sPathToObject, sText);
		}
		else if (sCommandName == "SET_CONDITION")
		{
			std::string sPathToObject;
			int iStateValue;
			std::cin >> sPathToObject >> iStateValue;

			SetCondition(sPathToObject, iStateValue);
		}
		else if (sCommandName == "SET_CONNECT")
		{
			std::string sPathToSignalObject;
			std::string sPathToHandlerObject;

			std::cin >> sPathToSignalObject >> sPathToHandlerObject;
			SetConnect(sPathToSignalObject, sPathToHandlerObject);
		}
		else if (sCommandName == "DELETE_CONNECT")
		{
			std::string sPathToSignalObject;
			std::string sPathToHandlerObject;

			std::cin >> sPathToSignalObject >> sPathToHandlerObject;
			DeleteConnect(sPathToSignalObject, sPathToHandlerObject);
		}
	}
    return 0;
}

CBase* CApplication::CreateObjectByNumber(const int iNumber, CBase* pHead, const std::string& sName) const
{
	switch (iNumber)
	{
	case 2: return new CObject2(pHead, sName);
	case 3: return new CObject3(pHead, sName);
	case 4: return new CObject4(pHead, sName);
	case 5: return new CObject5(pHead, sName);
	case 6: return new CObject6(pHead, sName);
	}
	return nullptr;
}


void CApplication::FindObjectByPath(CBase* pObject, const std::string& sPathToObject)
{
	const auto pFoundObject = pObject->GetObjectByPath(sPathToObject);

	if (pFoundObject)
		printf("%s     Object name: %s\n", sPathToObject.c_str(), pFoundObject->GetName().c_str());

	else
		printf("%s     Object is not found\n", sPathToObject.c_str());
}

void CApplication::MoveObject(CBase* pObject, const std::string& sPathTo)
{
	auto pNewHeadObject = pObject->GetObjectByPath(sPathTo);

	if (!pNewHeadObject)
	{
		printf("%s     Head object is not found\n", sPathTo.c_str());
		return;
	}
	if (pNewHeadObject->HasChild(pObject->GetName()))
	{
		printf("%s     Dubbing the names of subordinate objects\n", sPathTo.c_str());
		return;
	}

	if (!pObject->TransferOwnershipTo(pNewHeadObject))
		printf("%s     Redefining the head object failed\n", sPathTo.c_str());
	else
		printf("New head object: %s\n",pNewHeadObject->GetName().c_str());
}

void CApplication::DeleteChildByName(CBase* pObject, const std::string& sChildName)
{
	if (!pObject->HasChild(sChildName))
		return;

	auto sAbsPathToDeletedObject = pObject->GetChildByName(sChildName)->GetAbsolutePath();

	pObject->DeleteChildByName(sChildName);

	printf("The object %s has been deleted\n", sAbsPathToDeletedObject.c_str());
}

void CApplication::SetCurrentObject(CBase*& pObject, const std::string& sPathToObject)
{
	const auto pFoundObject = pObject->GetObjectByPath(sPathToObject);

	if (!pFoundObject)
	{
		printf("The object was not found at the specified coordinate: %s\n",sPathToObject.c_str());
		return;
	}
	printf("Object is set: %s\n", pFoundObject->GetName().c_str());

	pObject = pFoundObject;
}

int CApplication::GetObjectID() const
{
	return 1;
}

TYPE_SIGNAL CApplication::GetObjectSignal(const CBase* pObject) const
{
	switch (pObject->GetObjectID())
	{
		case 1: return MAKE_SIGNAL(CApplication::Signal);
		case 2: return MAKE_SIGNAL(CObject2::Signal);
		case 3: return MAKE_SIGNAL(CObject3::Signal);
		case 4: return MAKE_SIGNAL(CObject4::Signal);
		case 5: return MAKE_SIGNAL(CObject5::Signal);
		case 6: return MAKE_SIGNAL(CObject6::Signal);
	}
	return nullptr;
}

TYPE_HANDLER CApplication::GetObjectHandle(const CBase* pObject) const
{
	switch (pObject->GetObjectID())
	{
	case 1: return MAKE_HANDLER(CApplication::Handle);
	case 2: return MAKE_HANDLER(CObject2::Handle);
	case 3: return MAKE_HANDLER(CObject3::Handle);
	case 4: return MAKE_HANDLER(CObject4::Handle);
	case 5: return MAKE_HANDLER(CObject5::Handle);
	case 6: return MAKE_HANDLER(CObject6::Handle);
	}
	return nullptr;
}

void CApplication::EmitSignalForObject(const std::string& sPathToTargetObject, std::string sText)
{
	auto pObject = GetObjectByPath(sPathToTargetObject);

	if (!pObject)
	{
		printf("Object %s not found\n", sPathToTargetObject.c_str());
		return;
	}
	pObject->EmitSignal(GetObjectSignal(pObject), sText);
}

void CApplication::SetCondition(const std::string& sPathToTargetObject, int iCondition)
{
	auto pObject = GetObjectByPath(sPathToTargetObject);

	if (!pObject)
	{
		printf("Object %s not found\n", sPathToTargetObject.c_str());
		return;
	}

	pObject->SetReadiness(iCondition);
}

void CApplication::Signal(std::string& sText)
{
	sText += " (class: 1)";
	printf("\nSignal from %s", GetAbsolutePath().c_str());
}

void CApplication::Handle(const std::string& text)
{
	printf("\nSignal to %s Text: %s", GetAbsolutePath().c_str(), text.c_str());
}

void CApplication::SetConnect(const std::string& sPathToSignal, const std::string& sPathToHandler)
{
	const auto pObject        = GetObjectByPath(sPathToSignal);
	const auto pHandlerObject = GetObjectByPath(sPathToHandler);

	if (!pObject)
	{
		printf("Object %s not found\n", sPathToSignal.c_str());
		return;
	}
	if (!pHandlerObject)
	{
		printf("Handler object %s not found\n", sPathToHandler.c_str());
		return;
	}
	pObject->SetConnection(GetObjectSignal(pObject), pHandlerObject, GetObjectHandle(pHandlerObject));
}

void CApplication::DeleteConnect(const std::string& sPathToSignal, const std::string& sPathToHandler)
{
	const auto pObject        = GetObjectByPath(sPathToSignal);
	const auto pHandlerObject = GetObjectByPath(sPathToHandler);

	if (!pObject)
	{
		printf("Object %s not found\n", sPathToSignal.c_str());
		return;
	}
	if (!pHandlerObject)
	{
		printf("Handler object %s not found\n", sPathToHandler.c_str());
		return;
	}
	pObject->TerminateConnection(GetObjectSignal(pObject), pHandlerObject, GetObjectHandle(pHandlerObject));
}

