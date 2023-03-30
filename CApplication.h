//
// Created by alpat on 30.03.2023.
//

#ifndef OOP_COURSEWORK_CAPPLICATION_H
#define OOP_COURSEWORK_CAPPLICATION_H
#include "CBase.h"

class CApplication final : public CBase
{
public:
    CApplication(CBase* pHead);
    void BuildTree();
    int ExecApp();
};


#endif //OOP_COURSEWORK_CAPPLICATION_H
