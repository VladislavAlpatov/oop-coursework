//
// Created by alpat on 30.03.2023.
//

#ifndef OOP_COURSEWORK_CAPPLICATION_H
#define OOP_COURSEWORK_CAPPLICATION_H
#include "Objects/CBase.h"

class CApplication final : public CBase
{
public:
    CApplication();
    void BuildTree();
    int ExecApp();
	void Signal(std::string& sText);
	void Handle(const std::string& text);
	[[nodiscard]] int GetObjectID() const override;
private:
	CBase* CreateObjectByNumber(int iNumber, CBase* pHead, const std::string& sName) const;
	void FindObjectByPath(CBase* pObject, const std::string& sPathToObject);
	void MoveObject(CBase* pObject, const std::string& sPathTo);
	void DeleteChildByName(CBase* pObject, const std::string& sChildName);
	void SetCurrentObject(CBase*& pObject,const std::string& sPathToObject);
	void EmitSignalForObject(const std::string& sPathToTargetObject, std::string sText);
	void SetCondition(const std::string& sPathToTargetObject, int iCondition);
	void SetConnect(const std::string& sPathToSignal, const std::string& sPathToHandler);
	void DeleteConnect(const std::string& sPathToSignal, const std::string& sPathToHandler);
	TYPE_SIGNAL  GetObjectSignal(const CBase* pObject) const;
	TYPE_HANDLER GetObjectHandle(const CBase* pObject) const;

};


#endif //OOP_COURSEWORK_CAPPLICATION_H
