/*
 * CTacplusData.cpp
 *
 *  Created on: 12 Nov 2015
 *      Author: osboxes
 */

#include "CTacplusData.h"

namespace aaa {

CTacplusData::CTacplusData() {
	// TODO Auto-generated constructor stub
	this->m_avp.clear();
}

CTacplusData::~CTacplusData() {
	// TODO Auto-generated destructor stub
	this->m_avp.clear();
}

unsigned long CTacplusData::setDataEx(EProtocolDataType eType, string attr, string value)
{
	this->m_avp.insert(make_pair(attr, value));
}

void* CTacplusData::getDataDump()
{
	return (void *)&this->m_avp;
}

} /* namespace aaa */
