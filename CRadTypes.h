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
 * CRadTypes.h
 *
 *  Created on: 19 Oct 2015
 *      Author: kspviswa
 */

#ifndef CRADTYPES_H_
#define CRADTYPES_H_

#include <iostream>
#include <vector>
#include <map>
#include "3rdparty/ace-radius/RadiusClientStack.h"
#include <sstream>

using namespace std;

enum RadiusPassType {
	TYPE_PAP,
	TYPE_MSCHAP,
	TYPE_TLS,
	TYPE_TTLS
};

enum RadDataType {
	RAD_TYPE_INT,
	RAD_TYPE_STRING,
	RAD_TYPE_PASSWORD,
	RAD_TYPE_CHAP_PASSWORD,
	RAD_TYPE_VENDOR_SPECIFIC,
	RAD_TYPE_ADDRESS,
	RAD_TYPE_HEX,
	RAD_TYPE_OTHER
};

enum RadiusResultType {
	TYPE_ACCEPT,
	TYPE_CHALLENGE,
	TYPE_REJECT,
	TYPE_OK,
	TYPE_NOK,
	TYPE_NO_TRANSACTION
};

class CRadAVP{
public:
	RadDataType m_eType;
	unsigned long m_nOrdinal;
	string m_data;
};

class CRadProperties{
public:
	string m_sTarget;
	string m_sSharedSecret;
	unsigned long m_nPort;
};

typedef vector<CRadAVP> vectAVP;

#define RAD_SUCCESS 0
#define RAD_FAILURE 1


#endif /* CRADTYPES_H_ */
