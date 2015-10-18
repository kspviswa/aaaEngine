/*
 * IProtocolResponse.h
 *
 *  Created on: 18-Oct-2015
 *      Author: kspviswa
 */

#ifndef IPROTOCOLRESPONSE_H_
#define IPROTOCOLRESPONSE_H_

namespace aaa {

class IProtocolResponse {
public:
	IProtocolResponse();
	virtual ~IProtocolResponse();
	IProtocolData* parseResponse();
};

} /* namespace aaa */

#endif /* IPROTOCOLRESPONSE_H_ */
