/* An implementation of the nsd interface for plain tcp sockets.
 *
 * Copyright 2007, 2008 Rainer Gerhards and Adiscon GmbH.
 *
 * This file is part of the rsyslog runtime library.
 *
 * The rsyslog runtime library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The rsyslog runtime library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the rsyslog runtime library.  If not, see <http://www.gnu.org/licenses/>.
 *
 * A copy of the GPL can be found in the file "COPYING" in this distribution.
 * A copy of the LGPL can be found in the file "COPYING.LESSER" in this distribution.
 */

#ifndef INCLUDED_NSD_PTCP_H
#define INCLUDED_NSD_PTCP_H

#include "nsd.h"
typedef nsd_if_t nsd_ptcp_if_t; /* we just *implement* this interface */

/* the nsd_ptcp object */
struct nsd_ptcp_s {
	BEGINobjInstance; /* Data to implement generic object - MUST be the first data element! */
	uchar *pRemHostIP; /**< IP address of remote peer (currently used in server mode, only) */
	uchar *pRemHostName; /**< host name of remote peer (currently used in server mode, only) */
	int sock;	/**< the socket we use for regular, single-socket, operations */
	int *socks;	/**< the socket(s) we use for listeners, element 0 has nbr of socks */
	int iSessMax;	/**< maximum number of sessions permitted */
};

/* interface is defined in nsd.h, we just implement it! */
#define nsd_ptcpCURR_IF_VERSION nsdCURR_IF_VERSION

/* prototypes */
PROTOTYPEObj(nsd_ptcp);

/* the name of our library binary */
#define LM_NSD_PTCP_FILENAME "lmnsd_ptcp"

#endif /* #ifndef INCLUDED_NSD_PTCP_H */
