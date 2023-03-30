//
// Created by alpat on 30.03.2023.
//

#include "CBase.h"

std::string CBase::GetName() const
{
    return m_sName;
}

bool CBase::SetName(const std::string &sName)
{
    if (sName.empty())
        return false;

    m_sName = sName;
    return true;
}

CBase* CBase::GetParent() const
{
    return m_pParent;
}

CBase* CBase::GetChildByName(const std::string &sChildName) const
{
    for (const auto pChild : m_vecChildren)
        if (pChild->m_sName == sChildName)
            return pChild;
    return nullptr;
}

CBase* CBase::BrowseTree(const std::string &sName, CBase *pObj) const
{
    if (sName == pObj->m_sName)
        return pObj;

    for (auto pChild : pObj->m_vecChildren)
    {
        auto res = BrowseTree(sName, pChild);
        if (res) return res;
    }

    return nullptr;
}

CBase::CBase(CBase *pParent, const std::string &sName)
{
    m_pParent = pParent;
    m_sName   = sName;

    if (pParent)
        m_pParent->m_vecChildren.push_back(this);
}

CBase::~CBase()
{
    for (auto pChild : m_vecChildren)
        delete pChild;
}

void CBase::PrintInLine(const CBase *pObj) const
{

    if (pObj->m_vecChildren.empty())
        return;
    if (pObj->IsRoot())
        printf("%s\n", pObj->m_sName.c_str());

    printf("%s ", pObj->m_sName.c_str());

    for (const auto pHeir : pObj->m_vecChildren)
        printf((pHeir != pObj->m_vecChildren.back()) ? "%s " : "%s\n", pHeir->m_sName.c_str());

    for (const auto pHeir : pObj->m_vecChildren)
        PrintInLine(pHeir);
}

void CBase::PrintInLine() const
{
    PrintInLine(this);
}

bool CBase::IsRoot() const
{
    return !m_pParent;
}
