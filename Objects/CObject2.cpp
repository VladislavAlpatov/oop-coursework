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
	printf("\nSignal from %s", GetAbsolutePath().c_str());

}

void CObject2::Handle(const std::string& text)
{
	printf("\nSignal to %s Text: %s", GetAbsolutePath().c_str(), text.c_str());
}
