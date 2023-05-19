//
// Created by alpat on 25.04.2023.
//

#include "CObject5.h"

CObject5::CObject5(CBase* pParent, const std::string& sName) : CBase(pParent, sName)
{
}

int CObject5::GetObjectID() const
{
	return 5;
}

void CObject5::Signal(std::string& sText)
{

}

void CObject5::Handle(const std::string& text)
{

}
