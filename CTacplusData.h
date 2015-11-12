/*
 * CTacplusData.h
 *
 *  Created on: 12 Nov 2015
 *      Author: osboxes
 */

#ifndef CTACPLUSDATA_H_
#define CTACPLUSDATA_H_

#include "IProtocolData.h"
#include "IProtocolRequest.h"
#include "IProtocolResponse.h"
#include "CTacplusTypes.h"

namespace aaa {

class CTacplusData: public IProtocolData{

public:
	CTacplusData();
	virtual ~CTacplusData();
	virtual unsigned long setDataEx(EProtocolDataType eType, string attr, string value);
	virtual unsigned long setData(EProtocolDataType eType, unsigned long nID, string rawData);
	virtual void* getDataDump();

private:
	tacAVP m_avp;
};

} /* namespace aaa */

#endif /* CTACPLUSDATA_H_ */
