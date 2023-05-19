//
// Created by alpat on 25.04.2023.
//

#ifndef OOP_COURSEWORK_COBJECT6_H
#define OOP_COURSEWORK_COBJECT6_H
#include "CBase.h"

class CObject6 : public CBase
{
public:
	CObject6(CBase* pParent, const std::string& sName);

	int GetObjectID() const override;
	void Signal(std::string& sText);
	void Handle(const std::string& text);
};


#endif //OOP_COURSEWORK_COBJECT6_H
