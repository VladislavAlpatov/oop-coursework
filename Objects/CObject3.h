//
// Created by alpat on 25.04.2023.
//

#ifndef OOP_COURSEWORK_COBJECT3_H
#define OOP_COURSEWORK_COBJECT3_H
#include "CBase.h"

class CObject3 : public  CBase
{
public:
	CObject3(CBase* pParent, const std::string& sName);

	int GetObjectID() const override;
	void Signal(std::string& sText);
	void Handle(const std::string& text);
};


#endif //OOP_COURSEWORK_COBJECT3_H
