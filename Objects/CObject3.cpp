//
// Created by alpat on 25.04.2023.
//

#include "CObject3.h"

CObject3::CObject3(CBase* pParent, const std::string& sName) : CBase(pParent, sName)
{
	
}

int CObject3::GetObjectID() const
{
	return 3;
}

void CObject3::Signal(std::string& sText)
{

}

void CObject3::Handle(const std::string& text)
{

}
