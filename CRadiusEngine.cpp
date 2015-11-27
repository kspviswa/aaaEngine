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
 * CRadiusEngine.cpp
 *
 *  Created on: 19-Oct-2015
 *      Author: kspviswa
 */

#include <iostream>
#include "CRadiusEngine.h"
#include "CRadiusData.h"
#include <string.h>

namespace aaa {

CRadiusEngine::CRadiusEngine() {
	// TODO Auto-generated constructor stub

}

CRadiusEngine::~CRadiusEngine() {
	// TODO Auto-generated destructor stub
}

unsigned long  CRadiusEngine::initRequest(CProperties iConn) {

	unsigned long nRet = RAD_SUCCESS;

	this->m_Conn.m_nPort = iConn.nPort;
	this->m_Conn.m_sSharedSecret = iConn.sKey;
	this->m_Conn.m_sTarget = iConn.sHost;

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

bool CRadiusEngine::isValid()
{
	return this->m_stack.isValid();
}

unsigned long CRadiusEngine::prepareRequest(IProtocolData *pData)
{
	unsigned long nRet = RAD_FAILURE;
	if(pData)
	{
		CRadiusData *p_req = dynamic_cast<CRadiusData*>(pData);
		vectAVP *pAVP = static_cast<vectAVP*>(p_req->getDataDump());
		if(pAVP)
		{
			// add some attributes to the packet
			RadiusAttribute l_attr;
			vectAVP::iterator itVectAVP;
			nRet = RAD_SUCCESS;
			for(itVectAVP = pAVP->begin(); itVectAVP != pAVP->end(); ++itVectAVP)
			{
				switch(itVectAVP->m_nOrdinal)
				{
				case D_ATTR_USER_NAME:
					this->m_pPacket->addAttribute(D_ATTR_USER_NAME, l_attr);
					l_attr.setString(itVectAVP->m_data.c_str());
					break;
				case D_ATTR_USER_PASSWORD:
					this->m_pPacket->addAttribute(D_ATTR_USER_PASSWORD, l_attr);
					l_attr.setUserPassword(itVectAVP->m_data.c_str());
					break;
				default:
					cout << "Not Implemented" << endl;

				}
			}

		}
	}

	return nRet;
}

unsigned long CRadiusEngine::fireRequest()
{
	m_pPacketResponse = this->m_stack.sendPacket(*(this->m_pPacket));

#ifdef VERBOSE
	// print response if it was received
	if (m_pPacketResponse)
	{
		printf("---\nPacket was successfully transmitted\n---\n");
		printf("\nResponse packet:\n");
		l_response->dump();

	}
	else
	{
		printf("---\nPacket transmit failure\n---\n");
	}
#endif

	if(m_pPacketResponse)
	{
		return RAD_SUCCESS;
	}
	else
	{
		return RAD_FAILURE;
	}
}

unsigned long formatHelper(unsigned long nAttrID)
{

	switch (nAttrID)
	{
	case D_ATTR_NAS_PORT:
	case D_ATTR_SERVICE_TYPE:
	case D_ATTR_FRAMED_PROTOCOL:
	case D_ATTR_FRAMED_ROUTING:
	case D_ATTR_FRAMED_MTU:
	case D_ATTR_FRAMED_COMPRESSION:
	case D_ATTR_LOGIN_SERVICE:
	case D_ATTR_LOGIN_TCP_PORT:
	case D_ATTR_FRAMED_IPX_NETWORK:
	case D_ATTR_SESSION_TIMEOUT:
	case D_ATTR_IDLE_TIMEOUT:
	case D_ATTR_TERMINATION_ACTION:
	case D_ATTR_FRAMED_APPLETALK_LINK:
	case D_ATTR_FRAMED_APPLETALK_NETWORK:
	case D_ATTR_NAS_PORT_TYPE:
	case D_ATTR_PORT_LIMIT:
	case D_ATTR_ACCT_STATUS_TYPE:
	case D_ATTR_ACCT_DELAY_TIME:
	case D_ATTR_ACCT_INPUT_OCTETS:
	case D_ATTR_ACCT_OUTPUT_OCTETS:
	case D_ATTR_ACCT_AUTHENTIC:
	case D_ATTR_ACCT_SESSION_TIME:
	case D_ATTR_ACCT_INPUT_PACKETS:
	case D_ATTR_ACCT_OUTPUT_PACKETS:
	case D_ATTR_ACCT_TERMINATE_CAUSE:
	case D_ATTR_ACCT_LINK_COUNT:

		return TYPE_INT;
		break;

	case D_ATTR_NAS_IP_ADDRESS:
	case D_ATTR_FRAMED_IP_ADDRESS:
	case D_ATTR_FRAMED_IP_NETMASK:
	case D_ATTR_LOGIN_IP_HOST:
		return TYPE_ADDRESS;

	case D_ATTR_USER_PASSWORD:
		return TYPE_PASSWORD;

	case D_ATTR_CHAP_PASSWORD:
		return TYPE_CHAP_PASSWORD;

	case D_ATTR_VENDOR_SPECIFIC:
		return TYPE_VENDOR_SPECIFIC;

	case D_ATTR_REPLY_MESSAGE:
	default:
		return TYPE_STRING;
	}

}

string to_String(unsigned long nVal)
{
	stringstream ss;
	ss << nVal;
	return ss.str();
}

IProtocolData* CRadiusEngine::parseResponse()
{
	if(this->m_pPacketResponse)
	{
		CRadiusData *p_Res = new CRadiusData();
		if(p_Res)
		{
			RadiusAttribute l_attr;
			this->m_pPacketResponse->getFirstAttribute(l_attr);

			while(l_attr.isValid())
			{
				switch(formatHelper(l_attr.getType()))
				{
				case TYPE_INT:
					p_Res->setData(TYPE_INT, (unsigned long)l_attr.getType(),
							to_String(l_attr.getNumber()));
					break;
				case TYPE_ADDRESS:
					char szIP[50];
					struct in_addr addr;
					addr = l_attr.getIPAddress();
					inet_aton(szIP, &addr);
					p_Res->setData(TYPE_ADDRESS, (unsigned long)l_attr.getType(),
							string(szIP, strlen(szIP)));
					break;
				case TYPE_STRING:
					const char *pszStr;
					//string str = "";
					unsigned short int nLen;
					l_attr.getString(pszStr, nLen);
					string str(pszStr, nLen);

					p_Res->setData(TYPE_STRING, (unsigned long)l_attr.getType(),str);
					break;
				}
				this->m_pPacketResponse->getNextAttribute(l_attr);
			}

			return dynamic_cast<IProtocolData*>(p_Res);
		}
	}

	return NULL;

}

long CRadiusEngine::getResult()
{
	RadiusResultType nRet = TYPE_NO_TRANSACTION;
	if(this->m_pPacketResponse)
	{
		string sResult = this->m_pPacketResponse->getCodeDescription();

		if(sResult == "Access-Accept")
		{
			nRet = TYPE_ACCEPT;
		}
		else if(sResult == "Access-Reject")
		{
			nRet = TYPE_REJECT;
		}
		else if(sResult == "Access-Challenge")
		{
			nRet = TYPE_CHALLENGE;
		}
		else
		{
			nRet = TYPE_NO_TRANSACTION;
		}

	}

	return (long)nRet;

}

} /* namespace aaa */
