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
 * CTacplusTypes.h
 *
 *  Created on: 12 Nov 2015
 *      Author: kspviswa
 */

#ifndef CTACPLUSTYPES_H_
#define CTACPLUSTYPES_H_

#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include <vector>
#include <map>
#include "3rdparty/tac_plus/libtac.h"
#include <sstream>

using namespace std;

typedef map<string,string> tacAVP;

class CTacPlusProperties{
public:
	string m_sTarget;
	string m_sSharedSecret;
	unsigned long m_nPort;
	struct sockaddr_in sa;
	struct addrinfo server, src;
	int tac_fd;

/* Unlike RADIUS, here the AVPs are not enumerated */
	string m_sDevice;
	string m_sUser;
	string m_sPass;
};

#define TAC_SUCCESS 0
#define TAC_FAILURE 1


#endif /* CTACPLUSTYPES_H_ */
