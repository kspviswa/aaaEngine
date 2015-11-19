/*******************************************************************************
*  The MIT License (MIT)
*  
*  Copyright (c) 2015 kspviswa
*  
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*  
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*  
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*******************************************************************************/
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
