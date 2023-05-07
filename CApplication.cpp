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


CApplication::CApplication() : CBase(nullptr, "RootObject")
{

}

void CApplication::BuildTree()
{
    std::cin >> m_sName;


    while (true)
    {
		std::string sPathToHeadObject;
		std::string sNewObjectName;
		int         iClassType;

		std::cin >> sPathToHeadObject;

		if (sPathToHeadObject == "endtree")
			break;

		auto pHeadObject = GetObjectByPath(sPathToHeadObject);

		if (!pHeadObject)
			continue;

		std::cin >> sNewObjectName >> iClassType;

		if (pHeadObject->HasChild(sNewObjectName))
			continue;

		CreateObjectByNumber(iClassType, pHeadObject, sNewObjectName);

    }
}

int CApplication::ExecApp()
{
	printf("Object tree\n");
	PrintMultyLine();
	printf("\n");

	CBase* pCurrentObject = this;
	while (true)
	{
		std::string sCommandName;
		std::cin >>sCommandName;

		if (sCommandName == "END")
			break;

		if (sCommandName == "FIND")
		{
			std::string sPath;
			std::cin >> sPath;

			FindObjectByPath(pCurrentObject,sPath);

		}
		else if (sCommandName == "MOVE")
		{
			std::string sPath;
			std::cin >> sPath;

			MoveObject(pCurrentObject,sPath);
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
	}
	printf("Current object hierarchy tree\n");
	PrintMultyLine();
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
		printf("The object was not found at the specified coordinate: %s\n", sPathToObject.c_str());
	else
		printf("Object is set: %s\n", pFoundObject->GetName().c_str());

	pObject = pFoundObject;
}

