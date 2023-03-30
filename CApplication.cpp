//
// Created by alpat on 30.03.2023.
//

#include "CApplication.h"
#include <iostream>


CApplication::CApplication(CBase *pHead) : CBase(pHead)
{

}

void CApplication::BuildTree()
{
    std::string sHeadObjectName;
    std::string sNewObjectName;

    std::cin >> sHeadObjectName;

    m_sName = sHeadObjectName;

    while (true)
    {
        std::cin >> sHeadObjectName >> sNewObjectName;
        if (sHeadObjectName == sNewObjectName)
            return;


        auto pTarget = BrowseTree(sHeadObjectName, this);
        new CBase(pTarget, sNewObjectName);
    }
}

int CApplication::ExecApp()
{
    PrintMultyLine();
    return 0;
}
