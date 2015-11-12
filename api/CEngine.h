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

class CEngine : public IProtocolRequest, IProtocolResponse {

public:
	CEngine();
	virtual ~CEngine();
	virtual unsigned long initRequest(CProperties iConn);
	virtual bool isValid();
	virtual unsigned long prepareRequest(IProtocolData *pData);
	virtual unsigned long fireRequest();
	virtual IProtocolData* parseResponse();
	virtual long getResult();
	void setProtocolType(int nType);

private:
	EProtocols eType;
};

} /* namespace aaa */

#endif /* CENGINE_H_ */
