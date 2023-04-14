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
    CBase(CBase* pParent,const std::string& sName = "BaseObject");


    [[nodiscard]] std::string GetName()                                              const;
    [[nodiscard]] CBase*      GetParent()                                            const;
    [[nodiscard]] CBase*      GetChildByName(const std::string& sChildName)          const;
    [[nodiscard]] CBase*      BrowseTree(const std::string& sName);


    [[nodiscard]] bool        SetName(const std::string& sName);
    [[nodiscard]] bool        IsRoot() const;
	void PrintInLine()           const;
    void PrintMultyLine()               const;
    ~CBase();
private:
    void PrintMultyLine(size_t depth)   const;
};

class CBase2 : public CBase
{
public:
	CBase2(CBase* pParent,const std::string& sName) : CBase(pParent, sName)
	{

	}
};

#endif //OOP_COURSEWORK_CBASE_H
