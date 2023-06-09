//
// Created by alpat on 16.04.2023.
//

#ifndef OOP_COURSEWORK_COBJECT2_H
#define OOP_COURSEWORK_COBJECT2_H
#include "CBase.h"

class CObject2 : public CBase
{
public:
	CObject2(CBase* pParent, const std::string& sName);

	int GetObjectID() const override;
	void Signal(std::string& sText);
	void Handle(const std::string& text);
};

#endif //OOP_COURSEWORK_COBJECT2_H
