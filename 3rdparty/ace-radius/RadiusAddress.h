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
 * This source file is part of the ace-radius library.  This code was
 * written by Alex Agranov in 2004-2009, and is covered by the BSD open source
 * license. Refer to the accompanying documentation for details on usage and
 * license.
 */

#ifndef _RADIUSADDRESS_H__
#define _RADIUSADDRESS_H__

#ifdef _MSC_VER
    #include "Radius.h"
#else
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif

/**
 * @class RadiusAddress
 *
 * @brief Address of RADIUS server/client (IP address + port)
 */
class RadiusAddress
{
public:
    /// Constructor
    RadiusAddress();

    /// Constructor
    /**
     * @param[in] p_hostname - IP address or hostname
     * @param[in] p_port - IP port
     */
    RadiusAddress(const char *p_hostname, uint16_t p_port);

    /// Get IP port
    in_port_t getPort() const;
    /// Get IP address
    in_addr_t getIP() const;

    /// Update IP address & port
    void set(in_addr_t p_hostname, uint16_t p_port);
    /// Update IP address & port
    void set(const char *p_hostname, uint16_t p_port);

    /// Dump RadiusAddress in readable text format to STDOUT
    void dump();

private:
    in_addr_t  m_IP;    
    in_port_t  m_port;
};

#endif // _RADIUSADDRESS_H__

