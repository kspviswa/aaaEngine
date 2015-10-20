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
	virtual unsigned long initRequest() =0;
	virtual bool isValid() =0;
	virtual unsigned long addTarget(IProtocolData *pData) =0;
	virtual unsigned long fireRequest() =0;
};

} /* namespace aaa */

#endif /* IPROTOCOLREQUEST_H_ */
