//
// Created by alpat on 30.03.2023.
//

#include "CApplication.h"
#include <iostream>


CApplication::CApplication() : CBase(nullptr)
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

		if (pLastAddedObject->GetParent()->GetName() == sHeadObjectName and !pLastAddedObject->GetParent()->GetChildByName(sNewObjectName))
			pLastAddedObject = new CBase2(pLastAddedObject->GetParent(), sNewObjectName);
    }
}

int CApplication::ExecApp()
{
    PrintInLine();
    return 0;
}
