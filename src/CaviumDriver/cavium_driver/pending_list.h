////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// File Name: pending_list.h
// Description:
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, 
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, 
//    this list of conditions and the following disclaimer in the documentation 
//    and/or other materials provided with the distribution.
// 
// 3. All manuals,brochures,user guides mentioning features or use of this software 
//    must display the following acknowledgement:
// 
//   This product includes software developed by Cavium Networks
// 
// 4. Cavium Networks' name may not be used to endorse or promote products 
//    derived from this software without specific prior written permission.
// 
// 5. User agrees to enable and utilize only the features and performance 
//    purchased on the target hardware.
// 
// This Software,including technical data,may be subject to U.S. export control 
// laws, including the U.S. Export Administration Act and its associated 
// regulations, and may be subject to export or import regulations in other 
// countries.You warrant that You will comply strictly in all respects with all 
// such regulations and acknowledge that you have the responsibility to obtain 
// licenses to export, re-export or import the Software.
// TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS" AND 
// WITH ALL FAULTS AND CAVIUM MAKES NO PROMISES, REPRESENTATIONS OR WARRANTIES, 
// EITHER EXPRESS,IMPLIED,STATUTORY, OR OTHERWISE, WITH RESPECT TO THE SOFTWARE,
// INCLUDING ITS CONDITION,ITS CONFORMITY TO ANY REPRESENTATION OR DESCRIPTION, 
// OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM SPECIFICALLY 
// DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE, MERCHANTABILITY, 
// NONINFRINGEMENT,FITNESS FOR A PARTICULAR PURPOSE,LACK OF VIRUSES, ACCURACY OR
// COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO 
// DESCRIPTION. THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE 
// SOFTWARE LIES WITH YOU.    
//
// Modification History:
// 
////////////////////////////////////////////////////////////////////////////

#ifndef PENDING_LIST_H
#define PENDING_LIST_H

void push_pending(struct PENDING_ENTRY *, Csp1ResponseOrder );
__inline void push_pending_ordered(struct PENDING_ENTRY *entry);
__inline void push_pending_unordered(struct PENDING_ENTRY *entry);
void poll_pending_ordered(cavium_device *);
void poll_pending_unordered(cavium_device *);
void finalize_request(cavium_device *pdev,
		struct PENDING_ENTRY *entry, 
		Csp1ResponseOrder response_order);

__inline struct PENDING_ENTRY *get_queue_head_ordered(void);
__inline struct PENDING_ENTRY *get_queue_head_unordered(void);
void check_for_completion_callback(void *);
void init_pending_lists(void);
void cleanup_pending_lists(void);
#endif


/*
 * $Id: pending_list.h,v 1.4 2015/01/06 08:57:48 andy Exp $
 * $Log: pending_list.h,v $
 * Revision 1.4  2015/01/06 08:57:48  andy
 * *** empty log message ***
 *
 * Revision 1.3  2009-03-23 03:06:37  cding
 * *** empty log message ***
 *
 * Revision 1.1.1.1  2008-09-22 05:49:30  cding
 * init
 *
 * Revision 1.1.1.1  2008-04-26 01:41:36  chen
 * AOS
 *
 * Revision 1.1.1.1  2007/09/27 06:28:06  jeff
 * Rebuild AOS trunk
 *
 * Revision 1.3  2006/06/23 09:57:51  lixiaox
 * mod by lxx.Change the comment.
 *
 * Revision 1.2  2006/04/06 02:25:00  lijing
 * add cavium_driver support by lijing
 *
 * Revision 1.1.2.1  2006/04/04 17:53:41  lijing
 * no message
 *
 * Revision 1.9  2005/09/21 06:54:49  lpathy
 * Merging windows server 2003 release with CVS head
 *
 * Revision 1.8  2005/09/06 14:38:57  ksadasivuni
 * - Some cleanup error fixing and spin_lock_destroy functionality added to osi.
 *   spin_lock_destroy was necessary because of FreeBSD 6.0.
 *
 * Revision 1.7  2005/09/06 07:08:22  ksadasivuni
 * - Merging FreeBSD 4.11 Release with CVS Head
 *
 * Revision 1.6  2005/08/31 18:10:30  bimran
 * Fixed several warnings.
 * Fixed the corerct use of ALIGNMENT and related macros.
 *
 * Revision 1.5  2005/06/13 06:35:42  rkumar
 * Changed copyright
 *
 * Revision 1.4  2005/02/01 04:11:07  bimran
 * copyright fix
 *
 * Revision 1.3  2004/05/02 19:45:31  bimran
 * Added Copyright notice.
 *
 * Revision 1.2  2004/04/30 01:39:12  tsingh
 * changed some functions to inline.(bimran)
 *
 * Revision 1.1  2004/04/15 22:40:49  bimran
 * Checkin of the code from India with some cleanups.
 *
 */
