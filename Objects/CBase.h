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
	int					m_iReadiness;
	std::vector<CBase*> m_vecChildren;
public:
    CBase(CBase* pParent,const std::string& sName);


    [[nodiscard]] std::string GetName()                                              const;
    [[nodiscard]] CBase*      GetParent()                                            const;
    [[nodiscard]] CBase*      GetChildByName(const std::string& sChildName)          const;


    [[nodiscard]] bool        SetName(const std::string& sName);
	[[nodiscard]] CBase*	  FindObjectFromCurrentObject(const std::string& sName);
	[[nodiscard]] CBase*	  FindObjectFromRoot(const std::string& sName);
	[[nodiscard]] CBase*      GetObjectByPath(const std::string& str);
	[[nodiscard]] bool 		  TransferOwnershipTo(CBase* pNewOwner);
    [[nodiscard]] bool        IsRoot()                                      const;
	[[nodiscard]] bool 		  IsReady()                                     const;
	[[nodiscard]] bool        HasChild(const std::string& sChildName)       const;
	[[nodiscard]] bool 		  AbsolutePathToThisObjectContainsAnotherObject(CBase* pObject) const;
	[[nodiscard]] std::string GetAbsolutePath()								const;
	              void        PrintInLine()                                 const;
				  void        PrintMultyLine(size_t depth = 0)              const;
				  void        PrintMultyLineWithReadiness(size_t depth = 0) const;
				  void 		  DeleteChildByName(const std::string& sName);
	              void        SetReadiness(int iReadyStatus);
    ~CBase();
private:
	void 		  RemoveChildByName(const std::string& sName);
	[[nodiscard]] CBase*	  GetRootObject();
	[[nodiscard]] int		  CountObjectsByName(const std::string& sName) const;
	[[nodiscard]] CBase*	  FindObjectByName(const std::string& sName);
	[[nodiscard]] bool 		  ChainOfSubordinatesIsReady() const;
};
#endif //OOP_COURSEWORK_CBASE_H
