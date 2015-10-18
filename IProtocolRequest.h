/*
 * IProtocolRequest.h
 *
 *  Created on: 18-Oct-2015
 *      Author: kspviswa
 */

#ifndef IPROTOCOLREQUEST_H_
#define IPROTOCOLREQUEST_H_

namespace aaa {

class IProtocolRequest {
public:
	IProtocolRequest();
	virtual ~IProtocolRequest();
	unsigned long initRequest();
	bool isValid();
	unsigned long addTarget(IProtocolData *pData);
	IProtocolResponse* fireRequest();
};

} /* namespace aaa */

#endif /* IPROTOCOLREQUEST_H_ */
