////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// Description:
//   
//
// Modification History:
// 08/13/2011	Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#if 0
#include "EventMgr/EventBitmap.h"

u64 AosEventBitmap::smBitmap[] =
{
	0x01,		// 00000001
	0x02,		// 00000010
	0x04,		// 00000100
	0x08,		// 00001000
	0x10,		// 00010000
	0x20,		// 00100000
	0x40,		// 01000000
	0x80,		// 10000000

	0x0100,
	0x0200,
	0x0400,
	0x0800,
	0x1000,
	0x2000,
	0x4000,
	0x8000,

	0x010000,
	0x020000,
	0x040000,
	0x080000,
	0x100000,
	0x200000,
	0x400000,
	0x800000,

	0x01000000,
	0x02000000,
	0x04000000,
	0x08000000,
	0x10000000,
	0x20000000,
	0x40000000,
	0x80000000,

	((u64)0x01 << 32),		
	((u64)0x02 << 32),	
	((u64)0x04 << 32),
	((u64)0x08 << 32),
	((u64)0x10 << 32),
	((u64)0x20 << 32),
	((u64)0x40 << 32),
	((u64)0x80 << 32),

	((u64)0x0100 << 32),
	((u64)0x0200 << 32),
	((u64)0x0400 << 32),
	((u64)0x0800 << 32),
	((u64)0x1000 << 32),
	((u64)0x2000 << 32),
	((u64)0x4000 << 32),
	((u64)0x8000 << 32),

	((u64)0x010000 << 32),
	((u64)0x020000 << 32),
	((u64)0x040000 << 32),
	((u64)0x080000 << 32),
	((u64)0x100000 << 32),
	((u64)0x200000 << 32),
	((u64)0x400000 << 32),
	((u64)0x800000 << 32),

	((u64)0x01000000 << 32),
	((u64)0x02000000 << 32),
	((u64)0x04000000 << 32),
	((u64)0x08000000 << 32),
	((u64)0x10000000 << 32),
	((u64)0x20000000 << 32),
	((u64)0x40000000 << 32),
	((u64)0x80000000 << 32)

};
#endif
