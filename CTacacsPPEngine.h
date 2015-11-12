/*
 * CTacacsPPEngine.h
 *
 *  Created on: 19-Oct-2015
 *      Author: kspviswa
 */

#ifndef CTACACSPPENGINE_H_
#define CTACACSPPENGINE_H_

#include "IProtocolData.h"
#include "IProtocolRequest.h"
#include "IProtocolResponse.h"
#include "CTacplusTypes.h"

namespace aaa {

class CTacacsPPEngine: public IProtocolData,
		public IProtocolRequest,
		public IProtocolResponse {
public:
	CTacacsPPEngine();
	virtual ~CTacacsPPEngine();
	virtual unsigned long initRequest(CProperties iConn);
	virtual bool isValid();
	virtual unsigned long prepareRequest(IProtocolData *pData);
	virtual unsigned long fireRequest();
	virtual IProtocolData* parseResponse();
	virtual long getResult();

private:
	CTacPlusProperties m_Conn;
	bool m_bValid;
	struct tac_attrib *attr; // linked list of AVPs.
	struct areply arep; // Response attributes

};

} /* namespace aaa */

#endif /* CTACACSPPENGINE_H_ */
