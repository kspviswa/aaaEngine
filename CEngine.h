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
#include <map>
using namespace std;

namespace aaa {

typedef map<string, string> mAVP;

class CEngine {

public:
	CEngine();
	virtual ~CEngine();
	void setProtocolType(int nType);
	unsigned long initRequest(CProperties iConn);
	void setData(string sAttribute, string sValue);
	unsigned long prepareAndFireRequest();
	mAVP handleResponse();

private:
	EProtocols eType;
	mAVP m_AVP;
};


#define PROT_SUCCESS 0
#define PROT_FAILURE 1

} /* namespace aaa */

#endif /* CENGINE_H_ */
