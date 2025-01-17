////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// This type of IIL maintains a list of (string, docid) and is sorted
// based on the string value. It has a companion IIL that keeps the
// same set of Docids but sorted based on docids. 
//
// Modification History:
// 	Created: 2013/03/14 by Ken Lee
////////////////////////////////////////////////////////////////////////////
#include "IILMgr/IILBigD64.h"

#include "IILUtil/IILSave.h"

void
AosIILBigD64::setSnapShotId(const u64 &snap_id)
{
	AOSLOCK(mLock);
	setSnapShotIdPriv(snap_id);
	AOSUNLOCK(mLock);
}


void
AosIILBigD64::setSnapShotIdPriv(const u64 &snap_id)
{
	aos_assert(mSnapShotId == 0 || snap_id == mSnapShotId);
	mSnapShotId = snap_id;

	if (isParentIIL())
	{
		AosIILBigD64Ptr subiil;
		for (i64 i=1; i<mNumSubiils; i++)
		{
			subiil = mSubiils[i];
			if (!subiil) continue;
			subiil->setSnapShotIdPriv(snap_id);
		}
	}
}


void
AosIILBigD64::resetSnapShotId()
{
	AOSLOCK(mLock);
	resetSnapShotIdPriv();
	AOSUNLOCK(mLock);
}


void
AosIILBigD64::resetSnapShotIdPriv()
{
	mSnapShotId = 0;	
	if (isParentIIL())
	{
		AosIILBigD64Ptr subiil;
		for (i64 i=1; i<mNumSubiils; i++)
		{
			subiil = mSubiils[i];
			if (!subiil) continue;
			subiil->resetSnapShotIdPriv();
		}
	}
}


bool
AosIILBigD64::resetIIL(const AosRundataPtr &rdata)
{
	OmnNotImplementedYet;
	return true;
}
