/*
 * CRadTypes.h
 *
 *  Created on: 19 Oct 2015
 *      Author: osboxes
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
