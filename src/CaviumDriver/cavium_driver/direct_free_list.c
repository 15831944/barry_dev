////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// File Name: direct_free_list.c
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

#include "cavium_sysdep.h"
#include "cavium_common.h"
#include "cavium_list.h"
#include "cavium.h"
#include "direct_free_list.h"

volatile static Uint32 direct_free_max=0;
volatile static Uint32 direct_free_index=0;
static ptrlong *direct_free_list=NULL;
static struct PKP_DIRECT_OPERATION_STRUCT  *direct_entry_array=NULL;

static cavium_spinlock_t   direct_free_lock;

Uint32 get_direct_free_index(void);

int 
init_direct_free_list(Uint32 max)
{
  Uint32 i;

  cavium_spin_lock_init(&direct_free_lock); 
  if(direct_free_list)
  {
     cavium_print(("DIRECT free list already exists\n"));
     return 1;
  }
  
  direct_free_max = max;
  direct_free_list = (ptrlong *)cavium_malloc_virt(direct_free_max*sizeof(ptrlong));
  
  if(direct_free_list == NULL)
     {
       cavium_print(("Not enough memory in allocating direct_free_list\n"));
       return 1;
     }

  direct_entry_array = (struct PKP_DIRECT_OPERATION_STRUCT *)
      cavium_malloc_virt(direct_free_max*sizeof(struct PKP_DIRECT_OPERATION_STRUCT));

  if(direct_entry_array == NULL)
     {
       cavium_print(("Not enough memory in allocating direct_entry_array.\n"));
     cavium_free_virt(direct_free_list);
     direct_free_list = NULL;
       return 1;
     }

  for(i=0; i<direct_free_max; i++)
      {
        direct_free_list[i] = (ptrlong)&direct_entry_array[i];
      }    
      
 /* cavium_spin_lock_init(&direct_free_lock); */
 direct_free_index=0;
 return 0;
}


struct PKP_DIRECT_OPERATION_STRUCT * 
get_direct_entry(cavium_device *n1_dev)
{
   struct PKP_DIRECT_OPERATION_STRUCT *p = NULL;

   /* acquire lock */
  cavium_spin_lock_softirqsave(&direct_free_lock);

  if(direct_free_index >= direct_free_max)
   {
        p = NULL;
        goto cleanup;
   }
   

  p = (struct PKP_DIRECT_OPERATION_STRUCT *)direct_free_list[direct_free_index];
  direct_free_index++;

cleanup: 
  /* release lock*/
  cavium_spin_unlock_softirqrestore(&direct_free_lock);
  return p;
}


int
put_direct_entry(struct PKP_DIRECT_OPERATION_STRUCT *p)
{
   
   int ret=0;
 
   cavium_spin_lock_softirqsave(&direct_free_lock);

   direct_free_index--;
   direct_free_list[direct_free_index] = (ptrlong)p;
   ret=0;
   
   /* release lock*/
   cavium_spin_unlock_softirqrestore(&direct_free_lock);   
   return ret;

}


int 
cleanup_direct_free_list(void)
{
   cavium_spin_lock_destroy(&direct_free_lock);
   if(direct_free_list)
      cavium_free_virt(direct_free_list);

   if(direct_entry_array)
      cavium_free_virt(direct_entry_array);
   return 0;
}

Uint32 get_direct_free_index(void)
{
   return direct_free_index;
}




/*
 * $Id: direct_free_list.c,v 1.4 2015/01/06 08:57:46 andy Exp $
 * $Log: direct_free_list.c,v $
 * Revision 1.4  2015/01/06 08:57:46  andy
 * *** empty log message ***
 *
 * Revision 1.3  2009-03-23 03:06:53  cding
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
 * Revision 1.4  2006/06/23 09:57:51  lixiaox
 * mod by lxx.Change the comment.
 *
 * Revision 1.3  2006/04/07 00:24:14  lijing
 * *** empty log message ***
 *
 * Revision 1.2  2006/04/06 02:24:59  lijing
 * add cavium_driver support by lijing
 *
 * Revision 1.1.2.1  2006/04/04 17:53:41  lijing
 * no message
 *
 * Revision 1.11  2005/10/13 09:22:31  ksnaren
 * changed cavium_malloc_dma to cavium_malloc_virt for the control structs
 *
 * Revision 1.10  2005/09/28 15:50:26  ksadasivuni
 * - Merging FreeBSD 6.0 AMD64 Release with CVS Head
 * - Now context pointer given to user space applications is physical pointer.
 *   So there is no need to do cavium_vtophys() of context pointer.
 *
 * Revision 1.9  2005/09/06 14:38:57  ksadasivuni
 * - Some cleanup error fixing and spin_lock_destroy functionality added to osi.
 *   spin_lock_destroy was necessary because of FreeBSD 6.0.
 *
 * Revision 1.8  2005/09/06 07:11:23  ksadasivuni
 * - Merging FreeBSD 4.11 release with CVS Head
 *
 * Revision 1.7  2005/06/13 06:35:42  rkumar
 * Changed copyright
 *
 * Revision 1.6  2005/02/01 04:11:07  bimran
 * copyright fix
 *
 * Revision 1.5  2004/06/23 19:58:24  bimran
 * compiler warnings on NetBSD.
 *
 * Revision 1.4  2004/06/03 21:22:56  bimran
 * included cavium_list.h
 * fixed list* calls to use cavium_list
 *
 * Revision 1.3  2004/05/02 19:44:29  bimran
 * Added Copyright notice.
 *
 * Revision 1.2  2004/04/30 00:00:34  bimran
 * Removed semaphoers from context memory in favour of just counts and a lock.
 *
 * Revision 1.1  2004/04/15 22:40:49  bimran
 * Checkin of the code from India with some cleanups.
 *
 */
