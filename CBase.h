//
// Created by alpat on 30.03.2023.
//

#ifndef OOP_COURSEWORK_CBASE_H
#define OOP_COURSEWORK_CBASE_H
#include <string>
#include <vector>


class CBase
{
protected:
    std::string         m_sName;
    CBase*              m_pParent;
    std::vector<CBase*> m_vecChildren;
public:
    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] bool SetName(const std::string& sName);
};


#endif //OOP_COURSEWORK_CBASE_H
