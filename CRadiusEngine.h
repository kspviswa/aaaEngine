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

class CRadiusEngine : public IProtocolRequest, IProtocolResponse{
public:
	CRadiusEngine(string strHost, string strSSecret, unsigned long nPort);
	virtual ~CRadiusEngine();
	virtual unsigned long initRequest();
	virtual bool isValid();
	virtual unsigned long prepareRequest(IProtocolData *pData);
	virtual unsigned long fireRequest();
	virtual IProtocolData* parseResponse();
	virtual unsigned long getRadiusResult();

private:
	void clearAVP();

private:
	RadiusClientStack m_stack;
	RadiusPacket* m_pPacket;
	RadiusPacket* m_pPacketResponse;

	CRadProperties m_Conn;
};

} /* namespace aaa */

#endif /* CRADIUSENGINE_H_ */
