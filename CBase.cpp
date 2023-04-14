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

	if (m_pParent and m_pParent->GetChildByName(sName))
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

CBase* CBase::BrowseTree(const std::string &sName)
{
    if (sName ==m_sName)
        return this;

    for (auto pChild : m_vecChildren)
    {
        auto res = pChild->BrowseTree(sName);
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

void CBase::PrintInLine() const
{
	if (IsRoot())
		printf("%s", m_sName.c_str());

    if (m_vecChildren.empty())
        return;


    printf("\n%s", m_sName.c_str());
	for (const auto pHeir : m_vecChildren)
		printf("  %s", pHeir->m_sName.c_str());

    for (const auto pHeir : m_vecChildren)
        pHeir->PrintInLine();
}

bool CBase::IsRoot() const
{
    return !m_pParent;
}

void CBase::PrintMultyLine(size_t depth) const
{
    std::string space(depth*4, ' ');
    printf("%s%s\n", space.c_str(), m_sName.c_str());
    for (auto child : m_vecChildren)
        child->PrintMultyLine(depth+1);
}

void CBase::PrintMultyLine() const
{

}
