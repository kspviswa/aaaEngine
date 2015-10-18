/*
 * CRadiusEngine.h
 *
 *  Created on: 19-Oct-2015
 *      Author: kspviswa
 */

#ifndef CRADIUSENGINE_H_
#define CRADIUSENGINE_H_

#include "IProtocolData.h"
#include "IProtocolRequest.h"
#include "IProtocolResponse.h"

namespace aaa {

class CRadiusEngine: public IProtocolData,
		public IProtocolRequest,
		public IProtocolResponse {
public:
	CRadiusEngine();
	virtual ~CRadiusEngine();
};

} /* namespace aaa */

#endif /* CRADIUSENGINE_H_ */
