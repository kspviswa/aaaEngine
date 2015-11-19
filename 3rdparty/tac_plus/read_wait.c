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
/* read_wait.c - Wait for data to read on a fd.
 * 
 * Copyright (C) 2011, Darren Besler (dbesler@beehive.mb.ca)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program - see the file COPYING.
 *
 * See `CHANGES' file for revision history.
 */

#include <sys/time.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "libtac.h"

/* FIONREAD support for sun */
#ifdef sun
#include <sys/filio.h>
#endif

static int delta_msecs(struct timeval *newer, struct timeval *older) {
    long deltasecs, deltausecs;
    struct timeval now;

    if (newer == NULL) {
        gettimeofday(&now, NULL);
        newer = &now;
    }

    deltasecs = newer->tv_sec - older->tv_sec;
    deltausecs = newer->tv_usec - older->tv_usec;
    if ( newer->tv_usec < older->tv_usec ) {
        deltasecs--;
        deltausecs = (1000000+newer->tv_usec) - older->tv_usec;
    } else {
        deltausecs = newer->tv_usec - older->tv_usec;
    }
    return (deltasecs*1000)+(deltausecs/1000);
}


/*
 * tac_read_wait
 *
 * Parms:
 *   fd       - open fd to wait on till data avail, or timeout
 *   timeout  - maximum time to wait in milliseconds
 *   size     - amount of data to wait for
 *           0 : any amount of data
 *          >0 : amount of data to wait for
 *   timeleft - return of time left from timeout
 *
 * Returns:
 *    0 - data avail, no timeout
 *   -1 - timeout
 *    n - errno
 */

int tac_read_wait(int fd, int timeout, int size, int *time_left) {
    int retval = 0;
    int remaining;
    struct pollfd fds[1];

    struct timeval start;

    gettimeofday(&start, NULL);

    /* setup for read timeout. 
    *   will use poll() as it provides greatest compatibility
    *   vs setsockopt(SO_RCVTIMEO) which isn't supported on Solaris
    */

    remaining = timeout;  /* in msecs */

    fds[0].fd = fd;
    fds[0].events = POLLIN;

    while (remaining > 0) {
        int rc;
        int avail = 0;
        rc = poll(fds, 1, remaining);
        remaining -= delta_msecs(NULL, &start);
        if ( time_left != NULL ) {
            *time_left = remaining > 0 ? remaining : 0;
        }

        /* why did poll return */
        if (rc == 0) {    /* Receive timeout */
            retval = -1;
            break;
        }

        if (rc > 0) {     /* there is data available */
            if (size > 0 &&    /* check for enuf available? */
                ioctl(fd,FIONREAD,(char*)&avail) == 0 && avail < size) {
                continue;   /* not enuf yet, wait for more */
            } else {
                break;
            }
        }

        if (rc < 0 && errno == EINTR) {   /* interrupt */
            continue;
        }

        /* all other conditions is an error */
        retval = errno;
        break;
    }
    return retval;
}    /* read_wait */
