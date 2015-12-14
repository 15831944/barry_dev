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
// 05/24/2011	Created by Ketty 
////////////////////////////////////////////////////////////////////////////
#ifndef Omn_ReqProc_ShmConfirm_h
#define Omn_ReqProc_ShmConfirm_h	

#include "ReqProc/ReqProc.h"
#include "Util/String.h"
#include "alarm_c/alarm.h"
#include "Alarm/Alarm.h"
#include "Debug/Debug.h"
#include "Rundata/Rundata.h"
#include "SeReqProc/SeRequestProc.h"

class AosShmConfirm: public AosSeRequestProc
{
public:
	AosShmConfirm(const bool);
	~AosShmConfirm() {}
	
	virtual bool proc(const AosRundataPtr &rdata);
	
private:
	bool sendShortMsgResp(
					const AosXmlTagPtr &doc, 
					const AosRundataPtr &rdata);

	bool sendShortMsgNoResp(
					const AosXmlTagPtr &doc, 
					const AosRundataPtr &rdata);
};
#endif
