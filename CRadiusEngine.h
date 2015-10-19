/*
 * CRadiusEngine.h
 *
 *  Created on: 19-Oct-2015
 *      Author: kspviswa
 */

#ifndef CRADIUSENGINE_H_
#define CRADIUSENGINE_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "IProtocolData.h"
#include "IProtocolRequest.h"
#include "IProtocolResponse.h"
#include "CRadTypes.h"

using namespace std;

namespace aaa {

class CRadiusEngine {
public:
	CRadiusEngine(string strHost, string strSSecret, unsigned long nPort);
	virtual ~CRadiusEngine();
	unsigned long initRequest();
	bool isValid();
	unsigned long prepareRequest(IProtocolData *pData);
	IProtocolResponse* fireRequest();

private:
	void clearAVP();

private:
	RadiusClientStack m_stack;
	RadiusPacket* m_pPacket;
	CRadProperties m_Conn;
};

} /* namespace aaa */

#endif /* CRADIUSENGINE_H_ */
