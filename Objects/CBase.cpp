//
// Created by alpat on 30.03.2023.
//

#include "CBase.h"
#include "../utils/utils.h"


std::string CBase::GetName() const
{
    return m_sName;
}

bool CBase::SetName(const std::string &sName)
{
	if (m_pParent and m_pParent->HasChild(sName))
		return false;

	if (!IsNameIsNotCausePathConflict(sName))
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

CBase::CBase(CBase *pParent, const std::string &sName)
{
    m_pParent = pParent;
    m_sName   = sName;
	m_iReadiness = 0;
    if (!IsRoot())
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
void CBase::PrintMultyLineWithReadiness(size_t depth) const
{
	std::string space(depth*4, ' ');
	printf((IsRoot()) ? "%s%s %s" : "\n%s%s %s", space.c_str(), m_sName.c_str(), (IsReady()) ? "is ready" : "is not ready");
	for (auto child : m_vecChildren)
		child->PrintMultyLineWithReadiness(depth+1);
}

void CBase::PrintMultyLine(size_t depth) const
{
	std::string space(depth*4, ' ');
	printf((IsRoot()) ? "%s%s" : "\n%s%s", space.c_str(), m_sName.c_str());
	for (auto child : m_vecChildren)
		child->PrintMultyLine(depth+1);
}
bool CBase::IsRoot() const
{
    return !m_pParent;
}

bool CBase::HasChild(const std::string& sChildName) const
{
	return GetChildByName(sChildName);
}

bool CBase::IsReady() const
{
	return m_iReadiness != 0;
}

CBase* CBase::GetRootObject()
{
	if (IsRoot())
		return this;
	return GetParent()->GetRootObject();
 }

int CBase::CountObjectsByName(const std::string& sName) const
{
	int count = 0;

	if (m_sName == sName)
		count++;

	for (const auto pObj : m_vecChildren)
		count += pObj->CountObjectsByName(sName);

	return count;
}

void CBase::SetReadiness(int iReadyStatus)
{
	if (iReadyStatus and !ChainOfSubordinatesIsReady())
		return;

	m_iReadiness = iReadyStatus;

	if (!iReadyStatus)
		for (auto pObject : m_vecChildren)
			pObject->SetReadiness(iReadyStatus);

}

CBase* CBase::FindObjectByName(const std::string& sName)
{
	if (m_sName == sName)
		return this;

	for (const auto pObject : m_vecChildren)
	{
		auto res = pObject->FindObjectByName(sName);

		if (res)
			return res;
	}
	return nullptr;
}

CBase* CBase::FindObjectFromCurrentObject(const std::string& sName)
{
	return (CountObjectsByName(sName) > 1) ? nullptr : FindObjectByName(sName);
}

CBase* CBase::FindObjectFromRoot(const std::string& sName)
{
	return GetRootObject()->FindObjectFromCurrentObject(sName);
}

bool CBase::ChainOfSubordinatesIsReady() const
{
	for (auto pObj = GetParent(); pObj; pObj = pObj->GetParent())
		if (!pObj->IsReady())
			return false;
	return true;
}

CBase* CBase::GetObjectByPath(const std::string& sPath)
{
	if (sPath.empty())
		return nullptr;

	if (sPath.front() == '.' and sPath.length() == 1)
		return this;

	if (sPath.front() == '.')
		return FindObjectFromCurrentObject({ sPath.begin() + 1, sPath.end()});

	if (sPath.rfind("//") == 0)
		return FindObjectFromRoot({ sPath.begin() + 2, sPath.end()});


	auto pCurrentObject = (sPath.front() == '/') ? GetRootObject() : this;

	for (const  auto& sNameOfNextObject : utils::SplitString(sPath, "/"))
	{
		if (sNameOfNextObject.empty())
			continue;

		pCurrentObject = pCurrentObject->GetChildByName(sNameOfNextObject);

		if (!pCurrentObject) return nullptr;
	}
	return pCurrentObject;
}

void CBase::RemoveChildByName(const std::string& sName)
{
	if (!HasChild(sName))
		return;

	auto pChild = GetChildByName(sName);

	m_vecChildren.erase(std::remove(m_vecChildren.begin(), m_vecChildren.end(), pChild), m_vecChildren.end());
}

bool CBase::TransferOwnershipTo(CBase* pNewOwner)
{
	if (IsRoot() or pNewOwner->HasChild(m_sName) or pNewOwner->PathContainsObject(this))
		return false;

	GetParent()->RemoveChildByName(m_sName);

	pNewOwner->m_vecChildren.push_back(this);
	return true;
}

std::string CBase::GetAbsolutePath() const
{
	if (IsRoot()) return "/";
	std::string path;


	for (auto pCurrent = this; !pCurrent->IsRoot(); pCurrent = pCurrent->GetParent())
		path = "/" + pCurrent->m_sName + path;

	return path;
}

void CBase::DeleteChildByName(const std::string& sName)
{
	auto tmp = GetChildByName(sName);
	RemoveChildByName(sName);

	delete tmp;
}

bool CBase::PathContainsObject(CBase* pObject) const
{
	for (auto pCurrent = this; pCurrent->IsRoot(); pCurrent = pCurrent->GetParent())
		if (pCurrent == pObject)
			return true;
	return false;
}

bool CBase::IsNameIsNotCausePathConflict(const std::string& sName)
{
	return sName.find('/') == std::string::npos;
}
