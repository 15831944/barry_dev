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
// Modification History:
// 09/02/2013 Created by Linda 
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_Snapshot_Testers_DfmTester_h
#define Aos_Snapshot_Testers_DfmTester_h

#include "DocFileMgr/Ptrs.h"
#include "Rundata/Ptrs.h"
#include "SEInterfaces/Ptrs.h"
#include "Snapshot/Testers/Ptrs.h"
#include "Util/TransId.h"
#include "Util/RCObject.h"
#include "Util/RCObjImp.h"
#include "Util/File.h"
#include "Util/Ptrs.h"

class AosDfmTester : virtual public OmnRCObject 
{
	OmnDefineRCObject;

private:
	OmnString		mType;

public:
	AosDfmTester();
	AosDfmTester(const OmnString &tt);
	~AosDfmTester();

	OmnString getType() {return mType;}
	virtual bool basicTest() = 0;

	virtual bool serializeFrom(const AosBuffPtr &buff){return false;};
	virtual bool serializeTo(const AosBuffPtr &buff){return false;};
};
#endif
