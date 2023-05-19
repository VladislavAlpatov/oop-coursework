#include "CBase.h"
#include "../utils/utils.h"
#include <algorithm>


std::string CBase::GetName() const
{
	return m_sName;
}

bool CBase::SetName(const std::string& sName)
{

	if (m_pParent && m_pParent->HasChild(sName)) // проверка еслть ли объект м таким имеменем
		return false;

	if (sName.find("/") != std::string::npos)
		return false;

	m_sName = sName;
	return true;
}

CBase* CBase::GetParent() const
{
	return m_pParent;
}
bool CBase::IsReady() const
{
	return m_iReadiness;
}
CBase* CBase::GetChildByName(const std::string& sChildName) const // получение объекта по имени
{
	for (const auto pChild : m_vecChildren)
		if (pChild->m_sName == sChildName)
			return pChild;
	return nullptr;
}
CBase::CBase(CBase* pParent,const std::string& sName)
{
	m_pParent = pParent;
	m_sName = sName;
	m_iReadiness = 0; // объекты не готовы поумолчанию

	if (!IsRoot()) // если объект будет иметь подчинителя
		m_pParent->m_vecChildren.push_back(this);
}
CBase::~CBase()
{
	for (auto pChild : m_vecChildren)
		delete pChild;
}
bool CBase::IsRoot() const
{
	return !m_pParent;
}
void CBase::PrintInLine() const
{
	if (IsRoot())
		printf("%s", m_sName.c_str()); // вывод имени только корневого объекта

	if (m_vecChildren.empty()) // у объекта нет подчинённых
		return;

	printf("\n%s", m_sName.c_str());

	for (const auto pChild : m_vecChildren)
		printf("  %s", pChild->m_sName.c_str()); // вывод имени подчинённых

	for (const auto pChild : m_vecChildren)
		pChild->PrintInLine();
}

bool CBase::HasChild(const std::string& sChildName) const
{
	return GetChildByName(sChildName); // поиск объекта по имени
}

CBase* CBase::GetRootObject()
{
	return (IsRoot()) ? this : GetParent()->GetRootObject(); // проверка если текущий объект корень
}

int CBase::CountObjectsByName(const std::string& sName) const
{
	int iCount = 0; // колличество найденных объектов

	if (m_sName == sName)
		iCount++;

	for (const auto pObj : m_vecChildren)
		iCount += pObj->CountObjectsByName(sName);

	return iCount;
}

void CBase::SetReadiness(int iReadyStatus)
{
	// избегаем ситуации когда объект готов
	// а вышестоящие объекты не готовы
	if (iReadyStatus && !ChainOfSubordinatesIsReady())
		return;

	m_iReadiness = iReadyStatus;

	// если объект не готов то и нижестоящии объекты тоже должны потерять готовность
	if (!IsReady())
		for (auto pObject : m_vecChildren)
			pObject->SetReadiness(iReadyStatus);

}
CBase* CBase::FindObjectByName(const std::string& sName) // рекурсивный поиск
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
	return (CountObjectsByName(sName) > 1) ? nullptr : FindObjectByName(sName); // поиск объекта локально
}

CBase* CBase::FindObjectFromRoot(const std::string& sName)
{
	return GetRootObject()->FindObjectFromCurrentObject(sName); // запуск поиска от корня
}
bool CBase::ChainOfSubordinatesIsReady() const
{
	// проверяем каждый вышестоящий объект на готовность
	for (auto pObj = GetParent(); pObj; pObj = pObj->GetParent())
		if (!pObj->IsReady())
			return false;
	return true;
}
void CBase::PrintMultyLineWithReadiness(size_t depth) const
{
	std::string space(depth*4, ' '); // отступ
	printf((IsRoot()) ? "%s%s %s" : "\n%s%s %s", space.c_str(), m_sName.c_str(), (IsReady()) ? "is ready" : "is not ready"); // индикатор готовности

	for (const auto pChild : m_vecChildren)
		pChild->PrintMultyLineWithReadiness(depth+1);
}
void CBase::PrintMultyLine(size_t depth) const
{
	std::string space(depth*4, ' '); // отступ
	printf((IsRoot()) ? "%s%s" : "\n%s%s", space.c_str(), m_sName.c_str()); // вывод имени объекта

	for (const auto pChild : m_vecChildren)
		pChild->PrintMultyLine(depth+1);
}
CBase* CBase::GetObjectByPath(const std::string& sPath) // получить объект по пути
{
	if (sPath.empty()) // пусть пустой
		return nullptr;

	if (sPath == ".") // . - вернуть текущий
		return this;

	if (sPath.front() == '.') // поиск от текущего
		return FindObjectFromCurrentObject({sPath.begin()+1, sPath.end()});

	if (sPath.find("//") == 0) // поиск от корня
		return FindObjectFromRoot({sPath.begin()+2, sPath.end()});

	auto pCurrentObject = (sPath.front() == '/') ? GetRootObject() : this;

	for (const auto& sNameOfNextObject : utils::SplitString(sPath, "/"))
	{
		if (sNameOfNextObject.empty())
			continue;

		pCurrentObject = pCurrentObject->GetChildByName(sNameOfNextObject); // получение следующего объекта по имени в пути

		if (!pCurrentObject) return nullptr;
	}

	return pCurrentObject; // вернуть конечный объект
}

bool CBase::TransferOwnershipTo(CBase* pNewOwner) // переопределить головоной объект
{
	// объект не корень и путь до нового
	// головного объекта не содержит текущий
	if (IsRoot() || pNewOwner->HasChild(m_sName) || pNewOwner->PathContainsObject(this))
		return false;

	GetParent()->RemoveChildByName(m_sName);

	pNewOwner->m_vecChildren.push_back(this);
	return true;
}

void CBase::RemoveChildByName(const std::string& sName)
{
	m_vecChildren.erase(std::remove(m_vecChildren.begin(), m_vecChildren.end(), GetChildByName(sName)), m_vecChildren.end());

}
bool CBase::PathContainsObject(CBase* pObject) const // проверка есть ли объект в пути до текущего
{

	for (auto pCurrent = this; !pCurrent->IsRoot(); pCurrent = pCurrent->GetParent())
		if (pCurrent == pObject)
			return true;
	return false;

}
std::string CBase::GetAbsolutePath() const // получение абсолютного пути
{
	if (IsRoot()) return "/"; // если корень то путь "/"

	std::string path;

	for (auto pCurrent = this; !pCurrent->IsRoot(); pCurrent = pCurrent->GetParent())
		path = "/" + pCurrent->m_sName + path; // добавление части к пути

	return path;
}
void CBase::DeleteChildByName(const std::string& sChildName)
{
	auto tmp = GetChildByName(sChildName); // сохраняем объект на удаление
	RemoveChildByName(sChildName); // отвязываем объект

	delete tmp; // освобождение памяти
}

bool CBase::IsNameIsNotCausePathConflict(const std::string& sName)
{
	return sName.find('/') == std::string::npos;
}

void CBase::EmitSignal(TYPE_SIGNAL pSignal, std::string& sCommand)
{
	if (!IsReady())
		return;

	(this->*pSignal)(sCommand);

	for (const auto& connection : m_vecConnections)
	{
		if (connection.m_pSignal != pSignal)
			continue;

		auto pHandle = connection.m_pTypeHandler;

		if (connection.m_pTargetObject->IsReady())
			(connection.m_pTargetObject->*pHandle) (sCommand);
	}
}

void CBase::SetConnection(TYPE_SIGNAL pSignal, CBase* pObject, TYPE_HANDLER pHandle)
{
	if (std::find(m_vecConnections.begin(), m_vecConnections.end(),  connection_t(pSignal, pObject, pHandle)) == m_vecConnections.end())
		m_vecConnections.emplace_back(pSignal, pObject, pHandle);
}

void CBase::TerminateConnection(TYPE_SIGNAL pSignal, CBase* pObject, TYPE_HANDLER pHandle)
{
	m_vecConnections.erase(std::remove(m_vecConnections.begin(), m_vecConnections.end(), connection_t(pSignal, pObject, pHandle)), m_vecConnections.end());
}