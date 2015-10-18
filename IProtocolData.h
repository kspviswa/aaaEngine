/*
 * IProtocolData.h
 *
 *  Created on: 18-Oct-2015
 *      Author: kspviswa
 */

#ifndef IPROTOCOLDATA_H_
#define IPROTOCOLDATA_H_

namespace aaa {

class IProtocolData {
public:
	IProtocolData();
	virtual ~IProtocolData();
	unsigned long setData(void *pData);
	void* getData();
};

} /* namespace aaa */

#endif /* IPROTOCOLDATA_H_ */
