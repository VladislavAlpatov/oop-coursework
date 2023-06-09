//
// Created by alpat on 25.04.2023.
//

#include "CObject4.h"

CObject4::CObject4(CBase* pParent, const std::string& sName) : CBase(pParent, sName)
{
}

int CObject4::GetObjectID() const
{
	return 4;
}

void CObject4::Signal(std::string& sText)
{
	sText += " (class: 4)";
	printf("\nSignal from %s", GetAbsolutePath().c_str());

}

void CObject4::Handle(const std::string& text)
{
	printf("\nSignal to %s Text: %s", GetAbsolutePath().c_str(), text.c_str());
}
