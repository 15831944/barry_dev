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
// Modification History:
// 08/09/2013 	Created by Young pan 
////////////////////////////////////////////////////////////////////////////
#include "Snapshot/TestersClt/TestSuite.h"

#include "Snapshot/TestersClt/SnapShotTester.h"
#include "Tester/TestSuite.h"
#include "Tester/TestMgr.h"
#include "Thread/Mutex.h"
#include "Util/OmnNew.h"
#include "Util/File.h"


OmnTestSuitePtr		
AosSnapShotTestSuite::getSuite()
{
	OmnTestSuitePtr suite = OmnNew OmnTestSuite("SnapShotTester", "");

	//AosTcpServerTester* t = OmnNew AosTcpServerTester();
	// suite->addTestPkg(OmnNew AosTcpServerTester());
	//suite->addTestPkg(OmnNew AosKeyValuePairTester());
	
	suite->addTestPkg(OmnNew AosSnapShotTester());
	return suite;
}