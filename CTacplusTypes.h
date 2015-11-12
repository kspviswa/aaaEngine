/*
 * CTacplusTypes.h
 *
 *  Created on: 12 Nov 2015
 *      Author: osboxes
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
