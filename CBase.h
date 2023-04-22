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
	int					m_iReadiness;
public:
    CBase(CBase* pParent,const std::string& sName);


    [[nodiscard]] std::string GetName()                                              const;
    [[nodiscard]] CBase*      GetParent()                                            const;
    [[nodiscard]] CBase*      GetChildByName(const std::string& sChildName)          const;


    [[nodiscard]] bool        SetName(const std::string& sName);
    [[nodiscard]] bool        IsRoot()                                const;
	[[nodiscard]] bool 		  IsReady()                               const;

	[[nodiscard]] bool        HasChild(const std::string& sChildName) const;
	              void        PrintInLine()                           const;
				  void        PrintMultyLine(size_t depth = 0) const;
				  void PrintMultyLineWithReadiness(size_t depth = 0) const;
    ~CBase();

};
#endif //OOP_COURSEWORK_CBASE_H
