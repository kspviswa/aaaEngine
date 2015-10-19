/*
 * CRadiusData.h
 *
 *  Created on: 19 Oct 2015
 *      Author: osboxes
 */

#ifndef CRADIUSDATA_H_
#define CRADIUSDATA_H_

#include <iostream>
#include <vector>
#include <algorithm>

#include "IProtocolData.h"
#include "IProtocolRequest.h"
#include "IProtocolResponse.h"
#include "CRadTypes.h"

using namespace std;



namespace aaa {

class CRadiusData: public IProtocolData {

public:
	CRadiusData();
	virtual ~CRadiusData();
	unsigned long setData(EProtocolDataType eType, unsigned long nID, string rawData);
	void* getDataDump();

private:
	vectAVP m_AVP;
};

} /* namespace aaa */

#endif /* CRADIUSDATA_H_ */
