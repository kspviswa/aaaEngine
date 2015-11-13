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
	TYPE_CHAP_PASSWORD,
	TYPE_VENDOR_SPECIFIC,
	TYPE_ADDRESS,
	TYPE_HEX,
	TYPE_OTHER
};

enum EProtocols {
	RADIUS_STACK,
	TACACS_STACK,
	TACACS_PLUS_STACK,
	UNKNOWN_STACK
};

class CProperties
{
public:
	string sHost;
	string sKey;
	string sUser;
	string sPass;
	string sDevice;
	unsigned long nPort;
};


class IProtocolData {
public:
	IProtocolData();
	virtual ~IProtocolData();
	// ToDo : To club both versions of setData in generic format.
	/* Primarily used for RADIUS */
	virtual unsigned long setData(EProtocolDataType eType, unsigned long nID, string rawData) =0;
	/* Primarily used for TACACS+ */
	virtual unsigned long setDataEx(EProtocolDataType eType, string attr, string value) =0;

	virtual void* getDataDump() =0;
};

} /* namespace aaa */

#endif /* IPROTOCOLDATA_H_ */
