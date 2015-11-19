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
 * This source file is part of the ace-radius-linux library.  This code was
 * written by Alex Agranov in 2004-2009, and is covered by the BSD open source
 * license. Refer to the accompanying documentation for details on usage and
 * license.
 */

#ifndef _RADIUS_H__
#define _RADIUS_H__

#include <stdlib.h>
#ifdef _MSC_VER
    #ifndef _MSC_INTTYPES_H_
    #define _MSC_INTTYPES_H_
		// Visual Studio 6 and Embedded Visual C++ 4 doesn't
		// realize that, e.g. char has the same size as __int8
		// so we give up on __intX for them.
        typedef unsigned short    uint16_t;
        typedef unsigned int      uint32_t;
        typedef unsigned short    in_port_t;
        typedef unsigned long     in_addr_t;
    #endif // _MSC_INTTYPES_H_
#else
    #include <inttypes.h>
#endif

// return codes
#define RC_SUCCESS 0
#define RC_FAIL   -1

// standard ports
#define D_RADIUS_AUTHENTICATION_PORT  1812
#define D_RADIUS_ACCOUNTING_PORT      1813

#endif // _RADIUS_H__

