/*
 * CRadiusEngine.cpp
 *
 *  Created on: 19-Oct-2015
 *      Author: kspviswa
 */

#include "CRadiusEngine.h"

namespace aaa {

CRadiusEngine::CRadiusEngine(string strHost, string strSSecret, unsigned long nPort) {
	// TODO Auto-generated constructor stub
	this->m_Conn.m_nPort = nPort;
	this->m_Conn.m_sSharedSecret = strSSecret;
	this->m_Conn.m_sTarget = strHost;
}

CRadiusEngine::~CRadiusEngine() {
	// TODO Auto-generated destructor stub
}

unsigned long CRadiusEngine::initRequest() {

	unsigned long nRet = RAD_SUCCESS;

	if (!this->m_stack.isValid())
	{
		cout << "Error during RADIUS stack init. Aborting!!" << endl;
		return RAD_FAILURE;
	}

	nRet = this->m_stack.addServer(this->m_Conn.m_sTarget.c_str(),
							this->m_Conn.m_nPort,
							RadiusSecret(this->m_Conn.m_sSharedSecret.c_str()));
	if(nRet != RC_SUCCESS)
	{
		return RAD_FAILURE;
	}

	this->m_pPacket = new RadiusPacket(D_PACKET_ACCESS_REQUEST, this->m_stack);

	if(!this->m_pPacket)
	{
		cout << "Memory allocation failure. Unable to construct packet" << endl;
		return RAD_FAILURE;
	}

	return nRet;
}

} /* namespace aaa */
