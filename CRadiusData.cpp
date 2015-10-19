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

unsigned long CRadiusData::setData(EProtocolDataType eType, unsigned long nID, string rawData) {

	CRadAVP l_avp;
	l_avp.m_data = rawData;
	l_avp.m_eType = eType;
	l_avp.m_nOrdinal = nID;

	this->m_AVP.push_back(l_avp);
}

void* CRadiusData:: getDataDump() {
	return (void*)this->m_AVP.data();
}

} /* namespace aaa */
