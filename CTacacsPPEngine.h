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
 * CTacacsPPEngine.h
 *
 *  Created on: 19-Oct-2015
 *      Author: kspviswa
 */

#ifndef CTACACSPPENGINE_H_
#define CTACACSPPENGINE_H_

#include "IProtocolData.h"
#include "IProtocolRequest.h"
#include "IProtocolResponse.h"
#include "CTacplusTypes.h"

namespace aaa {

class CTacacsPPEngine:
		public IProtocolRequest,
		public IProtocolResponse {
public:
	CTacacsPPEngine();
	virtual ~CTacacsPPEngine();
	virtual unsigned long initRequest(CProperties iConn);
	virtual bool isValid();
	virtual unsigned long prepareRequest(IProtocolData *pData);
	virtual unsigned long fireRequest();
	virtual IProtocolData* parseResponse();
	virtual long getResult();

private:
	CTacPlusProperties m_Conn;
	bool m_bValid;
	struct tac_attrib *attr; // linked list of AVPs.
	struct areply arep; // Response attributes

};

} /* namespace aaa */

#endif /* CTACACSPPENGINE_H_ */
