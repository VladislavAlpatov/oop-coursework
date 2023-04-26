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
		std::string sNameOfObjectAddTo;
		std::string sNewObjectName;
		int         iClassType;

		std::cin >> sNameOfObjectAddTo;

		if (sNameOfObjectAddTo == "endtree")
			return;

		CBase*  pHeadObject = FindObjectFromRoot(sNameOfObjectAddTo);

		if (!pHeadObject)
			continue;

		std::cin >> sNewObjectName >> iClassType;

		if (pHeadObject->FindObjectFromRoot(sNewObjectName))
			continue;

		CreateObjectByNumber(iClassType, pHeadObject, sNewObjectName);

    }
}

int CApplication::ExecApp()
{
	printf("Object tree\n");
	PrintMultyLine();
	std::string sNameOfObjectForReadinessChange;

	while (std::cin >> sNameOfObjectForReadinessChange)
	{
		int iReadinessStatus;
		std::cin >> iReadinessStatus;

		auto pTargetObject = FindObjectFromRoot(sNameOfObjectForReadinessChange);

		if (pTargetObject)
			pTargetObject->SetReadiness(iReadinessStatus);

	}
	printf("The tree of objects and their readiness\n");

    PrintMultyLineWithReadiness();

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