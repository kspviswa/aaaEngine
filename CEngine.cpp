/*
 * CEngine.cpp
 *
 *  Created on: 18-Oct-2015
 *      Author: kspviswa
 */

#include "CEngine.h"

#include "CRadiusEngine.h"
#include "CTacacsPPEngine.h"
#include "CRadiusData.h"
#include "CTacplusData.h"

using namespace std;
using namespace aaa;

// Globals
CRadiusEngine *pRadEngine = NULL;
CTacacsPPEngine *pTacEngine = NULL;


namespace aaa {

CEngine::CEngine() {
this->eType = UNKNOWN_STACK;
}

CEngine::~CEngine() {
	// TODO Auto-generated destructor stub
	if(pRadEngine)
	{
		free(pRadEngine);
	}

	if(pTacEngine)
	{
		free(pTacEngine);
	}
}

unsigned long CEngine::initRequest(CProperties iConn)
{
	unsigned long nResult = PROT_FAILURE;
	switch (this->eType)
	{
	case RADIUS_STACK:
		pRadEngine = new CRadiusEngine();
		nResult = pRadEngine->initRequest(iConn);
		break;
	case TACACS_PLUS_STACK:
		pTacEngine = new CTacacsPPEngine();
		nResult = pTacEngine->initRequest(iConn);
		break;
	default:
		break;
	}

	return nResult;
}

void CEngine::setProtocolType(int nType)
{
	this->eType = (EProtocols) nType;
}

void CEngine::setData(string sAttribute, string sValue)
{
	this->m_AVP.insert(make_pair(sAttribute, sValue));
}

unsigned long CEngine::prepareAndFireRequest()
{
	unsigned long nResult = PROT_FAILURE;
	switch(this->eType)
	{
	case RADIUS_STACK:
	{
		// Step 1 -> Set Data
		CRadiusData newData;
		map<string, string>::iterator iter;
		for(iter = this->m_AVP.begin(); iter != this->m_AVP.end(); ++iter)
		{
			int nOrdinal = D_ATTR_MAX_KNOWN_TYPE;
			int nFormat = TYPE_OTHER;
			if(iter->first == "User-Name")
			{
				nOrdinal = D_ATTR_USER_NAME;
				nFormat = TYPE_STRING;
			}
			else if(iter->first == "User-Password")
			{
				nOrdinal = D_ATTR_USER_PASSWORD;
				nFormat = TYPE_STRING;
			}
			else
			{
				//ToDo Other Rad types and Vendor Specific type support should go here.
			}
			newData.setData((EProtocolDataType)nFormat, nOrdinal, iter->second);
		}

		// Step 2 -> Fire Request
		if(pRadEngine)
		{
			nResult = pRadEngine->prepareRequest(&newData);
			if(nResult == PROT_SUCCESS)
			{
				return (pRadEngine->fireRequest());
			}
			else
			{
				return nResult;
			}
		}
	}
	break;
	case TACACS_PLUS_STACK:
	{
		// Step 1 -> Set Data
		CTacplusData newData;
		map<string, string>::iterator iter;
		for(iter = this->m_AVP.begin(); iter != this->m_AVP.end(); ++iter)
		{
			newData.setDataEx(TYPE_STRING, iter->first, iter->second);
		}

		// Step 2 -> Fire Request
		if(pTacEngine)
		{
			nResult = pTacEngine->prepareRequest(&newData);
			if(nResult == PROT_SUCCESS)
			{
				return (pTacEngine->fireRequest());
			}
			else
			{
				return nResult;
			}
		}
	}
	break;
	default :
		nResult = PROT_FAILURE;
		break;
	}

	return nResult;
}

mAVP CEngine::handleResponse()
{
	mAVP oAVP;

	switch(this->eType)
	{
	case TACACS_PLUS_STACK:
	{
		if(pTacEngine->getResult() == TAC_SUCCESS)
		{
			IProtocolData *pData = pTacEngine->parseResponse();
			while(pData)
			{
				tacAVP *pAVP = static_cast<tacAVP*>(pData->getDataDump());
				tacAVP::iterator iter;
				for(iter = pAVP->begin(); iter != pAVP->end(); iter++)
				{
					oAVP.insert(make_pair(iter->first, iter->second));
				}

				free(pData);
			}
		}
	}
	break;
	case RADIUS_STACK:
	{
		if(pRadEngine->getResult() == TYPE_ACCEPT)
		{
			IProtocolData *pData = pRadEngine->parseResponse();
			while(pData)
			{
				vectAVP *pAVP = static_cast<vectAVP*>(pData->getDataDump());
				vectAVP::iterator iter;
				for(iter = pAVP->begin(); iter != pAVP->end(); iter++)
				{
					oAVP.insert(make_pair("",iter->m_data));
				}

				free(pData);
			}
		}
	}
	break;
	default:
		break;
	}
	return oAVP;
}

unsigned long CEngine::getResult()
{
	switch(this->eType)
	{
	case TACACS_PLUS_STACK:
	{
		if(pTacEngine && pTacEngine->getResult() == TAC_SUCCESS)
		{
			return PROT_SUCCESS;
		}
	}
	break;
	case RADIUS_STACK:
	{
		if(pRadEngine && pRadEngine->getResult() == TYPE_ACCEPT)
		{
			return PROT_SUCCESS;
		}
	}
	break;
	default:
		break;
	}

	return PROT_FAILURE;
}

} /* namespace aaa */
