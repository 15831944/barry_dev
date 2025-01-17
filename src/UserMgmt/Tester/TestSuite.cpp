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
// 3/19/2007 Created by TorturerGen Facility
//////////////////////////////////////////////////////////////////////////
// 3/19/2007 Created by TorturerGen Facility
//////////////////////////////////////////////////////////////////////////
#include "UserMgmt/Tester/TestSuite.h"

#include "Tester/TestSuite.h"
#include "Tester/TestMgr.h"
#include "Util/OmnNew.h"
#include "UserMgmt/Tester/UserTester.h"

//
// Default constructor.
// Code automatically generated by TorturerGen
//
AosUserMgmtTorturerTestSuite::AosUserMgmtTorturerTestSuite()
{
}


//
// Destructor.
// Code automatically generated by TorturerGen
//
AosUserMgmtTorturerTestSuite::~AosUserMgmtTorturerTestSuite()
{
}


//
// Code automatically generated by TorturerGen
//
OmnTestSuitePtr
AosUserMgmtTorturerTestSuite::getSuite()
{
    OmnTestSuitePtr suite = OmnNew OmnTestSuite("UserMgmtTorturerTestSuite", "");
    // 
    // Add all the testers
    // 
    suite->addTestPkg(OmnNew AosUserTesterTester());

    return suite;
}

