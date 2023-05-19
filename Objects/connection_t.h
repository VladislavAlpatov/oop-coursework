//
// Created by alpat on 20.05.2023.
//

#ifndef OOP_COURSEWORK_CONNECTION_T_H
#define OOP_COURSEWORK_CONNECTION_T_H
#include <string>

class CBase;

typedef void (CBase::*TYPE_SIGNAL) ( std::string& );
typedef void (CBase::*TYPE_HANDLER) (const std::string& );

class connection_t
{
public:
	connection_t(TYPE_SIGNAL pSignal, CBase* pBase, TYPE_HANDLER pTypeHandler);
	TYPE_SIGNAL  m_pSignal;
	CBase*		 m_pTargetObject;
	TYPE_HANDLER m_pTypeHandler;
	bool operator==(const connection_t& other) const;
	bool operator!=(const connection_t& other) const;
};


#endif //OOP_COURSEWORK_CONNECTION_T_H
