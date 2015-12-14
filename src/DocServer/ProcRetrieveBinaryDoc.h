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
// 07/06/2012	Created by Linda
////////////////////////////////////////////////////////////////////////////
#if 0
#ifndef Aos_DocServer_ProcRetrieveBinaryDoc_h
#define Aos_DocServer_ProcRetrieveBinaryDoc_h

#include "DocServer/DocSvrProc.h"
#include "DocServer/Ptrs.h"


class AosProcRetrieveBinaryDoc : virtual public AosDocSvrProc
{
private:

public:
	AosProcRetrieveBinaryDoc(const bool regflag);
	~AosProcRetrieveBinaryDoc();

	virtual AosDocSvrProcPtr clone();
	virtual bool proc(const AosRundataPtr &rdata, const AosXmlTagPtr &request, const AosXmlTransPtr &trans);
};
#endif
#endif