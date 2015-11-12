/*
 * CTacacsPPEngine.cpp
 *
 *  Created on: 19-Oct-2015
 *      Author: kspviswa
 */

#include "CTacacsPPEngine.h"
#include "CTacplusData.h"

namespace aaa {

CTacacsPPEngine::CTacacsPPEngine() {
	// TODO Auto-generated constructor stub

}

CTacacsPPEngine::~CTacacsPPEngine() {
	// TODO Auto-generated destructor stub
}

unsigned long CTacacsPPEngine::initRequest(CProperties iConn)
{
	unsigned long nResult = TAC_SUCCESS;


	this->m_Conn.m_nPort = iConn.nPort;
	this->m_Conn.m_sSharedSecret = iConn.sKey;
	this->m_Conn.m_sTarget = iConn.sHost;
	this->m_Conn.m_sDevice = iConn.sDevice;
	this->m_Conn.m_sPass = iConn.sPass;
	this->m_Conn.m_sUser = iConn.sUser;
	this->m_bValid = false;

	this->m_Conn.sa.sin_family = AF_INET;
	this->m_Conn.sa.sin_port = htons(this->m_Conn.m_nPort);
	inet_pton(AF_INET, this->m_Conn.m_sTarget.c_str(), &(this->m_Conn.sa.sin_addr));


	this->m_Conn.server.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
	this->m_Conn.server.ai_socktype = SOCK_STREAM; /* Datagram socket */
	this->m_Conn.server.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	this->m_Conn.server.ai_protocol = 0;          /* Any protocol */
	this->m_Conn.server.ai_canonname = NULL;
	this->m_Conn.server.ai_addr = (sockaddr*)&this->m_Conn.sa;
	this->m_Conn.server.ai_addrlen = sizeof(this->m_Conn.sa);


	this->m_Conn.server.ai_next = NULL;


	this->m_Conn.tac_fd = tac_connect_single(&this->m_Conn.server,
			this->m_Conn.m_sSharedSecret.c_str(), NULL, 15000);

	if (this->m_Conn.tac_fd < 0)
	{
		nResult = TAC_FAILURE;
	}
	this->m_bValid = true;
	return nResult;
}

bool CTacacsPPEngine::isValid()
{
	return this->m_bValid;
}

unsigned long CTacacsPPEngine::prepareRequest(IProtocolData *pData)
{
	unsigned long nResult = TAC_FAILURE;

	if(!this->m_bValid)
	{
		return nResult;
	}

	CTacplusData *pnewData = static_cast<CTacplusData*> (pData);
	const tacAVP *pAvp = static_cast<tacAVP*>(pnewData->getDataDump());
	map<string, string>::const_iterator iter;

	for(iter = pAvp->begin(); iter != pAvp->end(); ++iter)
	{
		// Remember -> Attribute will be name=
		tac_add_attrib(&this->attr, const_cast<char*>(iter->first.c_str()),
				const_cast<char*>(iter->second.c_str()));
	}

	nResult = TAC_SUCCESS;

	return nResult;
}

unsigned long CTacacsPPEngine::fireRequest()
{
	unsigned long nResult = TAC_FAILURE;
	int tac_reply;

	if(!this->m_bValid)
	{
		return nResult;
	}

	tac_reply = tac_authen_send(this->m_Conn.tac_fd, this->m_Conn.m_sUser.c_str(),
			const_cast<char*>(this->m_Conn.m_sPass.c_str()), const_cast<char*>(this->m_Conn.m_sDevice.c_str()),
			"Unknown");

	if(tac_reply < 0)
	{
		return nResult;
	}

	nResult = tac_authen_read(this->m_Conn.tac_fd);

	 if( nResult == TAC_PLUS_AUTHEN_STATUS_PASS)
	 {
		 nResult = TAC_SUCCESS;

		 // Proceed with autorization

		 tac_reply = tac_author_send(this->m_Conn.tac_fd, this->m_Conn.m_sUser.c_str(),
				 const_cast<char*>(this->m_Conn.m_sDevice.c_str()),
				 "Unknown", this->attr);

		 tac_free_attrib(&this->attr);

		 if(tac_reply < 0 )
		 {
			 nResult = TAC_FAILURE;
			 return nResult;
		 }

		 tac_reply =  tac_author_read(this->m_Conn.tac_fd, &this->arep);

		 if(tac_reply < 0 )
		 {
			 nResult = TAC_FAILURE;
			 if(this->arep.msg != NULL)
				 free (this->arep.msg);

			 return nResult;
		 }

		 if(this->arep.status != AUTHOR_STATUS_PASS_ADD &&
				 this->arep.status != AUTHOR_STATUS_PASS_REPL)
		 {
			 nResult = TAC_FAILURE;
			 if(this->arep.msg != NULL)
				 free (this->arep.msg);

			 return nResult;
		 }

		 return TAC_SUCCESS;
	 }
	 else
	 {
		 return TAC_FAILURE;
	 }
}

IProtocolData* CTacacsPPEngine::parseResponse()
{
	struct tac_attrib *theattr;
	theattr = arep.attr;
	CTacplusData *pRes = new CTacplusData();

	while (theattr != NULL)  {
		char attribute[theattr->attr_len];
		char value[theattr->attr_len];
		char *sep;

		sep = index(theattr->attr, '=');
		if(sep == NULL)
			sep = index(theattr->attr, '*');
		if(sep != NULL) {
			bcopy(theattr->attr, attribute, theattr->attr_len-strlen(sep));
			attribute[theattr->attr_len-strlen(sep)] = '\0';
			bcopy(sep, value, strlen(sep));
			value[strlen(sep)] = '\0';

			size_t i;
			for (i = 0; attribute[i] != '\0'; i++) {
				attribute[i] = toupper(attribute[i]);
				if (attribute[i] == '-')
					attribute[i] = '_';
			}

			pRes->setDataEx(TYPE_STRING, string(attribute), string(value));

		}
		theattr = theattr->next;
	}

	return dynamic_cast<IProtocolData*>(pRes);
}

long CTacacsPPEngine::getResult()
{
	return this->arep.status;
}

} /* namespace aaa */
