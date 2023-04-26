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
    std::string sHeadObjectName;
    std::string sNewObjectName;

    std::cin >> sHeadObjectName;

    m_sName = sHeadObjectName;

	CBase* pLastAddedObject = this;

    while (true)
    {
        std::cin >> sHeadObjectName >> sNewObjectName;

        if (sHeadObjectName == sNewObjectName)
            return;

		if (pLastAddedObject->GetName() == sHeadObjectName)
		{
			pLastAddedObject = new CObject2(pLastAddedObject, sNewObjectName);
			continue;
		}

		if (pLastAddedObject->IsRoot())
			continue;

		auto pParentOfLastObject = pLastAddedObject->GetParent();

		if (pParentOfLastObject->GetName() == sHeadObjectName and !pParentOfLastObject->HasChild(sNewObjectName))
			pLastAddedObject = new CObject2(pParentOfLastObject, sNewObjectName);
    }
}

int CApplication::ExecApp()
{
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
