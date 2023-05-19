//
// Created by alpat on 16.04.2023.
//

#include "CObject2.h"

CObject2::CObject2(CBase* pParent, const std::string& sName) : CBase(pParent, sName)
{

}

int CObject2::GetObjectID() const
{
	return 2;
}

void CObject2::Signal(std::string& sText)
{
	sText += " (class: 2)";
	printf("Signal from %s\n", GetAbsolutePath().c_str());

}

void CObject2::Handle(const std::string& text)
{
	printf("Signal to %s Text: %s\n", GetAbsolutePath().c_str(), text.c_str());
}
