/*
 * IProtocolData.h
 *
 *  Created on: 18-Oct-2015
 *      Author: kspviswa
 */

#ifndef IPROTOCOLDATA_H_
#define IPROTOCOLDATA_H_

#include <iostream>
using namespace std;

namespace aaa {

enum EProtocolDataType {
	TYPE_INT,
	TYPE_STRING,
	TYPE_PASSWORD,
	TYPE_ADDRESS,
	TYPE_HEX,
	TYPE_OTHER
};

class IProtocolData {
public:
	IProtocolData();
	virtual ~IProtocolData();
	virtual unsigned long setData(EProtocolDataType eType, unsigned long nID, string rawData) =0;
	virtual void* getDataDump() =0;
};

} /* namespace aaa */

#endif /* IPROTOCOLDATA_H_ */
