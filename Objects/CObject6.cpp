//
// Created by alpat on 25.04.2023.
//

#include "CObject6.h"

CObject6::CObject6(CBase* pParent, const std::string& sName) : CBase(pParent, sName)
{
}

int CObject6::GetObjectID() const
{
	return 6;
}

void CObject6::Signal(std::string& sText)
{

}

void CObject6::Handle(const std::string& text)
{

}
