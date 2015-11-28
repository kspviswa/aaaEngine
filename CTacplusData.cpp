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
 * CTacplusData.cpp
 *
 *  Created on: 12 Nov 2015
 *      Author: kspviswa
 */

#include "CTacplusData.h"

namespace aaa {

CTacplusData::CTacplusData() {
	// TODO Auto-generated constructor stub
	this->m_avp.clear();
}

CTacplusData::~CTacplusData() {
	// TODO Auto-generated destructor stub
	this->m_avp.clear();
}

unsigned long CTacplusData::setDataEx(EProtocolDataType eType, string attr, string value)
{
	this->m_avp.insert(make_pair(attr, value));
	return TAC_SUCCESS;
}

unsigned long CTacplusData::setData(EProtocolDataType eType, unsigned long nID, string rawData)
{
	// Dummy function - just to satisfy the virtual constraint.
	return TAC_SUCCESS;
}

void* CTacplusData::getDataDump()
{
	return (void *)&this->m_avp;
}

} /* namespace aaa */