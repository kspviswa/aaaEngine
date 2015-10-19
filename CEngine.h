/*
 * CEngine.h
 *
 *  Created on: 18-Oct-2015
 *      Author: kspviswa
 */

#ifndef CENGINE_H_
#define CENGINE_H_

#include "IProtocolData.h"
#include "IProtocolRequest.h"
#include "IProtocolResponse.h"

#include <iostream>
using namespace std;

namespace aaa {

enum EProtocols {
	RADIUS_STACK,
	TACACS_STACK,
	TACACS_PLUS_STACK
};

class IProtocolHandler;
class IProtocolData;
class IProtocolRequest;
class IProtocolResponse;

class CEngine {
public:
	CEngine();
	virtual ~CEngine();
	unsigned long addProtocolStack(EProtocols eType);
	IProtocolRequest* prepareDataAndReturnRequest(IProtocolData *pData, EProtocols eType);
	IProtocolResponse* fireRequestAndHandleResponse(IProtocolRequest *pRequest);
};

} /* namespace aaa */

#endif /* CENGINE_H_ */
