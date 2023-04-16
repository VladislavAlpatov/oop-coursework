//
// Created by alpat on 30.03.2023.
//

#include "CApplication.h"
#include <iostream>
#include "CBase2.h"


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
			pLastAddedObject = new CBase2(pLastAddedObject, sNewObjectName);
			continue;
		}

		if (pLastAddedObject->IsRoot())
			continue;

		auto pParentOfLastObject = pLastAddedObject->GetParent();

		if (pParentOfLastObject->GetName() == sHeadObjectName and !pParentOfLastObject->HasChild(sNewObjectName))
			pLastAddedObject = new CBase2(pParentOfLastObject, sNewObjectName);
    }
}

int CApplication::ExecApp()
{
    PrintInLine();
    return 0;
}
