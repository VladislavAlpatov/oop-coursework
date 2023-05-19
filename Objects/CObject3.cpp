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
	sText += " (class: 3)";
	printf("\nSignal from %s", GetAbsolutePath().c_str());

}

void CObject3::Handle(const std::string& text)
{
	printf("\nSignal to %s Text: %s", GetAbsolutePath().c_str(), text.c_str());
}
