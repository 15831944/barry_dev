////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// File Name: CliCommTestSuite.cpp
// Description:
//   
//
// Modification History:
// 
////////////////////////////////////////////////////////////////////////////

#include "CliComm/Tester/CliCommTestSuite.h"

#include "Tester/TestSuite.h"
#include "Tester/TestMgr.h"
#include "Tester/TestPkg.h"
#include "Util/OmnNew.h"

#include "CliComm/Tester/CliCommTester.h"


OmnTestSuitePtr	
AosCliCommTestSuite::getSuite()
{
	OmnTestSuitePtr suite = OmnNew 
		OmnTestSuite("CliCommTestSuite", "CliComm Test Suite");

	// 
	// Now add all the testers
	//
	suite->addTestPkg(OmnNew AosCliCommTester());

	return suite;
}
