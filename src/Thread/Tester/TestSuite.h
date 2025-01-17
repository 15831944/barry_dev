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
// 4/16/2007 Created by TorturerGen Facility
//////////////////////////////////////////////////////////////////////////
// 4/16/2007 Created by TorturerGen Facility
//////////////////////////////////////////////////////////////////////////
#ifndef Aos_Thread_Tester_TestSuite_h
#define Aos_Thread_Tester_TestSuite_h

#include "Tester/Ptrs.h"
#include "Tester/TestPkg.h"
#include "Util/String.h"


class AosThreadTestSuite
{
private:
    OmnTestSuitePtr     mSuite;

public:
    AosThreadTestSuite();
    ~AosThreadTestSuite();

    static OmnTestSuitePtr      getSuite();
};
#endif
