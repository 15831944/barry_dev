//////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// Description:
// This file is automatically generated by the TorturerGen facility. 
//
// Modification History:
// 05/06/2007 Created by TorturerGen Facility
//////////////////////////////////////////////////////////////////////////
#ifndef Aos_RandomValueGen_Tester_AosStrRVGTester_h
#define Aos_RandomValueGen_Tester_AosStrRVGTester_h

#include "RandomValueGen/Tester/RVGTester.h"



class AosStrRVGTester : public AosRVGTester
{
private:

public:
    AosStrRVGTester();
    ~AosStrRVGTester();

    virtual bool     start();


private:
	bool	createData();
	bool 	testTimeStr(u32 tries);
	bool 	runParm(const OmnString &parmDef, 
						  const OmnString &dbDef, 
						  const u32 tries);
	bool 	check(const OmnString &file, 
						const int line, 
						const bool flag,
						const OmnString &value, 
						const OmnString &errmsg);
};
#endif

