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
};


#endif //OOP_COURSEWORK_CAPPLICATION_H
