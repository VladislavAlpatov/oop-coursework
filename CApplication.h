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
private:
	CBase* CreateObjectByNumber(int iNumber, CBase* pHead, const std::string& sName) const;
	void FindObjectByPath(CBase* pObject, const std::string& sPathToObject);
	void MoveObject(CBase* pObject, const std::string& sPathTo);
	void DeleteChildByName(CBase* pObject, const std::string& sChildName);
	void SetCurrentObject(CBase*& pObject,const std::string& sPathToObject);
};


#endif //OOP_COURSEWORK_CAPPLICATION_H
