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
	sText += " (class: 5)";
	printf("\nSignal from %s", GetAbsolutePath().c_str());

}

void CObject5::Handle(const std::string& text)
{
	printf("\nSignal to %s Text: %s", GetAbsolutePath().c_str(), text.c_str());
}
