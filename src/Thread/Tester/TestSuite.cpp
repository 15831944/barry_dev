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
#include "Thread/Tester/TestSuite.h"

#include "Tester/TestSuite.h"
#include "Tester/TestMgr.h"
#include "Util/OmnNew.h"
#include "Thread/Tester/ThrdShellProcTester.h"
#include "Thread/Tester/ThreadRunnerTester.h"

//
// Default constructor.
// Code automatically generated by TorturerGen
//
AosThreadTestSuite::AosThreadTestSuite()
{
}


//
// Destructor.
// Code automatically generated by TorturerGen
//
AosThreadTestSuite::~AosThreadTestSuite()
{
}


//
// Code automatically generated by TorturerGen
//
OmnTestSuitePtr
AosThreadTestSuite::getSuite()
{
    OmnTestSuitePtr suite = OmnNew OmnTestSuite("ThreadTestSuite", "");
    // 
    // Add all the testers
    // 
    // suite->addTestPkg(OmnNew AosThrdShellProcTester());
    suite->addTestPkg(OmnNew AosThreadRunnerTester());

    return suite;
}

