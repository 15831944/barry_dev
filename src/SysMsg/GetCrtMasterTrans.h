////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
//
// Modification History:
// Created: 04/26/2013 by Ketty 
////////////////////////////////////////////////////////////////////////////
#ifndef AOS_SysMsg_GetCrtMasterTrans_h
#define AOS_SysMsg_GetCrtMasterTrans_h

#include "TransUtil/TaskTrans.h"
#include "Util/Buff.h"

class AosGetCrtMasterTrans: public AosTaskTrans
{

private:
	u32		mCubeGrpId;

public:
	AosGetCrtMasterTrans(const bool reg_flag);
	AosGetCrtMasterTrans(
		const int to_svrid,
		const u32 to_proc_id,
		const u32 cube_grp_id);
	~AosGetCrtMasterTrans();
	
	virtual bool 	serializeTo(const AosBuffPtr &buff);
	virtual bool 	serializeFrom(const AosBuffPtr &buff);
	virtual OmnString getStrType(){ return "eGetCrtMaster"; };
	//virtual AosConnMsgPtr clone();
	virtual AosTransPtr clone();
	virtual bool	proc();
	
};

#endif