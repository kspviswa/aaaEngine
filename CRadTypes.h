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

using namespace std;

enum RadiusPassType {
	TYPE_PAP,
	TYPE_MSCHAP,
	TYPE_TLS,
	TYPE_TTLS
};

class CRadAVP{
public:
	RadiusPassType m_eType;
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
