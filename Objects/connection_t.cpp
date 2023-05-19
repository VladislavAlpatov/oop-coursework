//
// Created by alpat on 20.05.2023.
//

#include "connection_t.h"

connection_t::connection_t(TYPE_SIGNAL pSignal, CBase* pBase, TYPE_HANDLER pTypeHandler)
{
	m_pSignal       = pSignal;
	m_pTargetObject = pBase;
	m_pTypeHandler  = pTypeHandler;
}
bool connection_t::operator==(const connection_t& other) const
{
	return m_pTargetObject == other.m_pTargetObject and m_pSignal == other.m_pSignal and m_pTypeHandler == other.m_pTypeHandler;
}


bool connection_t::operator!=(const connection_t& other) const
{
	return !(*this == other);
}
