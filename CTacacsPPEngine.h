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

namespace aaa {

class CTacacsPPEngine: public IProtocolData,
		public IProtocolRequest,
		public IProtocolResponse {
public:
	CTacacsPPEngine();
	virtual ~CTacacsPPEngine();
};

} /* namespace aaa */

#endif /* CTACACSPPENGINE_H_ */
