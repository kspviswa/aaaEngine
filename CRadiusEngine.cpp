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

virtual unsigned long CRadiusEngine::initRequest() {

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

virtual bool CRadiusEngine::isValid()
{
	return this->m_stack.isValid();
}

virtual unsigned long CRadiusEngine::prepareRequest(IProtocolData *pData)
{
	unsigned long nRet = RAD_FAILURE;
	if(pData)
	{
		CRadiusData *p_req = pData;
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

virtual unsigned long CRadiusEngine::fireRequest()
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
		return ;

	case D_ATTR_CHAP_PASSWORD:
		return E_ATTR_FORMAT_CHAP_PASSWORD;

	case D_ATTR_VENDOR_SPECIFIC:
		return E_ATTR_FORMAT_VENDOR_SPECIFIC;

	default:
		return E_ATTR_FORMAT_STRING;
	}

}

virtual IProtocolData* CRadiusEngine::parseResponse()
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
				p_Res->setData(l_attr.getType(), l_attr.get)
				this->m_pPacketResponse->getFirstAttribute(l_attr);
			}
		}
	}

}

virtual unsigned long CRadiusEngine::getRadiusResult()
{
	RadiusResultType nRet = TYPE_NO_TRANSACTION;
	if(this->m_pPacketResponse)
	{
		string sResult = this->m_pPacketResponse->getCodeDescription();
		switch(sResult)
		{
		case "Access-Accept":
			nRet = TYPE_ACCEPT;
			break;
		case "Access-Reject":
			nRet = TYPE_REJECT;
			break;
		case "Access-Challenge":
			nRet = TYPE_CHALLENGE;
			break;
		default:
		}
	}

}

} /* namespace aaa */
