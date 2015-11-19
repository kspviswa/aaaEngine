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

#ifndef _RADIUSCLIENTCONNECTION_H__
#define _RADIUSCLIENTCONNECTION_H__

#include "Radius.h"
#include "RadiusAddress.h"
#include "RadiusPacket.h"
#include "RadiusSecret.h"


class RadiusClientStack;

/**
 * @class RadiusClientConnection
 *
 * @brief Connection between client RADIUS stack and single RADIUS server
 *
 * Each connection has it's own secret key and retransmission 
 * settings. Multiple connections can be used within the same 
 * RadiusClientStack for high-availability purposes (see 
 * documentation in RadiusClientStack class for details). 
 */
class RadiusClientConnection
{
public:
    /// Constructor
    /**
     * @param[in] p_stack     - RADIUS client stack that this connection belongs to
     * @param[in] p_secret    - secret key
     * @param[in] p_hostname  - RADIUS server hostname
     * @param[in] p_port      - RADIUS server port
     * @param[in] p_responseTimeout - RADIUS server response timeout (in sec)
     * @param[in] p_retransmitCount - max number of packet retransmits
     */
    RadiusClientConnection(RadiusClientStack * p_stack,
                           const RadiusSecret & p_secret,
                           const char * p_hostname, 
                           uint16_t p_port = D_RADIUS_AUTHENTICATION_PORT,
                           int p_responseTimeout = 5, 
                           int p_retransmitCount = 4);

    ~RadiusClientConnection();
    
    /// Send RADIUS packet
    /** 
     * Send packet to RADIUS server and wait for response. 
     * Retransmit packet as needed, if no response is received. 
     * Note that this method is blocking - i.e. all (re)transmission
     * is performed on the context of the calling thread.
     *  
     * @param[in] p_data - RADIUS packet to be sent 
     * @return response packet (if packet was successfully 
     *         transmitted and response was received); NULL
     *         otherwise
     */
    RadiusPacket * sendPacket(RadiusPacket & p_packet);

private:

    /// RADIUS stack that this connection belongs to
    RadiusClientStack * m_stack;

    /// RADIUS secret key
    RadiusSecret m_secret;

    /// RADIUS packet that is being currently received
    RadiusPacket m_packet;

    /// Server address
    RadiusAddress   m_serverAddress;
    
    /// RADIUS server response timeout (in seconds)
    int m_responseTimeout;
    
    /// Max number of packet retransmits towards specific connection
    int m_retransmitCount;
};

#endif // _RADIUSCLIENTCONNECTION_H__

