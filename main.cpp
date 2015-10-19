/*
 * main.cpp
 *
 *  Created on: 19 Oct 2015
 *      Author: osboxes
 */

#include <iostream>
#include "CEngine.h"
#include "CRadiusData.h"

using namespace std;
using namespace aaa;

void main()
{
	CEngine l_Engine;
	CRadiusData l_radData;

	l_radData.m_eType = TYPE_PAP;
	l_radData.m_nPort = 1812;
	l_radData.m_sSharedSecret = "1234";
	l_radData.m_sTarget = "127.0.0.1";

	l_radData.setData(TYPE_STRING, D_ATTR_USER_NAME, "root");

}



