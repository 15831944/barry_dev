////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// File Name: flow.h
// Description:
//   
//
// Modification History:
// 
////////////////////////////////////////////////////////////////////////////

#ifndef Omn_aos_KernelSimu_flow_h
#define Omn_aos_KernelSimu_flow_h

#ifdef AOS_KERNEL_SIMULATE

#include "KernelSimu/types.h"
#include "KernelSimu/compiler.h"

struct flowi {
	int	oif;
	int	iif;

	union {
		struct {
			__u32			daddr;
			__u32			saddr;
			__u32			fwmark;
			__u8			tos;
			__u8			scope;
		} ip4_u;
		
		// struct {
		// 	struct in6_addr		daddr;
		// 	struct in6_addr		saddr;
		// 	__u32			flowlabel;
		// } ip6_u;

		struct {
			__u16			daddr;
			__u16			saddr;
			__u32			fwmark;
			__u8			scope;
		} dn_u;
	} nl_u;
#define fld_dst		nl_u.dn_u.daddr
#define fld_src		nl_u.dn_u.saddr
#define fld_fwmark	nl_u.dn_u.fwmark
#define fld_scope	nl_u.dn_u.scope
#define fl6_dst		nl_u.ip6_u.daddr
#define fl6_src		nl_u.ip6_u.saddr
#define fl6_flowlabel	nl_u.ip6_u.flowlabel
#define fl4_dst		nl_u.ip4_u.daddr
#define fl4_src		nl_u.ip4_u.saddr
#define fl4_fwmark	nl_u.ip4_u.fwmark
#define fl4_tos		nl_u.ip4_u.tos
#define fl4_scope	nl_u.ip4_u.scope

	__u8	proto;
	__u8	flags;
	union {
		struct {
			__u16	sport;
			__u16	dport;
		} ports;

		struct {
			__u8	type;
			__u8	code;
		} icmpt;

		struct {
			__u16	sport;
			__u16	dport;
			__u8	objnum;
			__u8	objnamel; /* Not 16 bits since max val is 16 */
			__u8	objname[16]; /* Not zero terminated */
		} dnports;

		__u32		spi;
	} uli_u;
#define fl_ip_sport	uli_u.ports.sport
#define fl_ip_dport	uli_u.ports.dport
#define fl_icmp_type	uli_u.icmpt.type
#define fl_icmp_code	uli_u.icmpt.code
#define fl_ipsec_spi	uli_u.spi
};

#define FLOW_DIR_IN	0
#define FLOW_DIR_OUT	1
#define FLOW_DIR_FWD	2

typedef void (*flow_resolve_t)(struct flowi *key, 
								u16 family, 
								u8 dir,
			       				void **objp, 
								atomic_t **obj_refp);

#else
#include <net/flow.h>
#endif

#endif

