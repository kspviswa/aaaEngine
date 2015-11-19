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
 * CTacplusData.h
 *
 *  Created on: 12 Nov 2015
 *      Author: kspviswa
 */

#ifndef CTACPLUSDATA_H_
#define CTACPLUSDATA_H_

#include "IProtocolData.h"
#include "IProtocolRequest.h"
#include "IProtocolResponse.h"
#include "CTacplusTypes.h"

namespace aaa {

class CTacplusData: public IProtocolData{

public:
	CTacplusData();
	virtual ~CTacplusData();
	virtual unsigned long setDataEx(EProtocolDataType eType, string attr, string value);
	virtual unsigned long setData(EProtocolDataType eType, unsigned long nID, string rawData);
	virtual void* getDataDump();

private:
	tacAVP m_avp;
};

} /* namespace aaa */

#endif /* CTACPLUSDATA_H_ */
