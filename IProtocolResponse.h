/*
 * IProtocolResponse.h
 *
 *  Created on: 18-Oct-2015
 *      Author: kspviswa
 */

#ifndef IPROTOCOLRESPONSE_H_
#define IPROTOCOLRESPONSE_H_

#include "IProtocolData.h"

namespace aaa {

class IProtocolResponse {
public:
	IProtocolResponse();
	virtual ~IProtocolResponse();
	virtual IProtocolData* parseResponse() =0;
	virtual unsigned long getRadiusResult() =0;
};

} /* namespace aaa */

#endif /* IPROTOCOLRESPONSE_H_ */
