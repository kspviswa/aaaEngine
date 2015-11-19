/*
 * CRadiusData.cpp
 *
 *  Created on: 19 Oct 2015
 *      Author: osboxes
 */

#include "CRadiusData.h"

namespace aaa {

CRadiusData::CRadiusData() {
	// TODO Auto-generated constructor stub
	this->m_AVP.clear();
}

CRadiusData::~CRadiusData() {
	// TODO Auto-generated destructor stub
	this->m_AVP.clear();
}

unsigned long CRadiusData::setData(aaa::EProtocolDataType eType, unsigned long nID, string rawData) {

	CRadAVP l_avp;
	l_avp.m_data = rawData;
	l_avp.m_eType = static_cast<RadDataType>(eType);
	l_avp.m_nOrdinal = nID;

	this->m_AVP.push_back(l_avp);
	return RAD_SUCCESS;
}
unsigned long CRadiusData::setDataEx(EProtocolDataType eType, string attr, string value)
{
	// Dummy function - just to satisfy the virtual constraint.
	return RAD_SUCCESS;
}

void* CRadiusData:: getDataDump() {
	return (void*)&this->m_AVP;
}

} /* namespace aaa */
