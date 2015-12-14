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
// 07/28/2012 Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_TaskUtil_Ptrs_h
#define Aos_TaskUtil_Ptrs_h

#include "Util/SPtr.h"


OmnPtrDecl(AosDataColCtlr,		AosDataColCtlrPtr)
OmnPtrDecl(AosTaskToken,		AosTaskTokenPtr)
OmnPtrDecl(AosTaskInfo,			AosTaskInfoPtr)
OmnPtrDecl(AosTaskRunnerInfo,	AosTaskRunnerInfoPtr)
OmnPtrDecl(AosTaskDriver,		AosTaskDriverPtr)
OmnPtrDecl(AosTaskDriverRequest,AosTaskDriverRequestPtr)


#endif