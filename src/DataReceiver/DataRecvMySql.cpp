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
// 2013/08/28 Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#if 0
#include "DataReceiver/DataRecvMySql.h"

#include "Rundata/Rundata.h"
#include "Thread/Mutex.h"
#include "Util/Buff.h"


extern "C"
{
AosJimoPtr AosCreateJimoFunc_AosDataRecvMySql_ver_0(
		const AosRundataPtr &rdata, 
		const u32 version) 
{
	try
	{
		OmnScreen << "To create Jimo: " << endl;
		return OmnNew AosDataRecvMySql(version);
	}

	catch (...)
	{
		AosSetErrorU(rdata, "Failed creating jimo") << enderr;
		return 0;
	}

	OmnShouldNeverComeHere;
	return 0;
}
}



AosDataRecvMySql::AosDataRecvMySql()
:
AosDataReceiverObj()
{
}


AosDataRecvMySql::AosDataRecvMySql(const u32 version)
:
AosDataReceiverObj(version)
{
}


AosDataRecvMySql::~AosDataRecvMySql()
{
}


bool 
AosDataRecvMySql::run(const AosRundataPtr &rdata)
{
	OmnNotImplementedYet;
	return false;
}


AosJimoPtr 
AosDataRecvMySql::cloneJimo()  const
{
	try
	{
		return OmnNew AosDataRecvMySql(*this);
	}

	catch (...)
	{
		OmnAlarm << "Failed creating jimo" << enderr;
	}
	return 0;
}


bool 
AosDataRecvMySql::config(
		const AosRundataPtr &rdata,
		const AosXmlTagPtr &worker_doc,
		const AosXmlTagPtr &jimo_doc)
{
	OmnNotImplementedYet;
	return false;
}


void * 
AosDataRecvMySql::getMethod(
		const AosRundataPtr &rdata, 
		const OmnString &name, 
		AosMethodId::E &method_id)
{
	OmnNotImplementedYet;
	return false;
}

#endif