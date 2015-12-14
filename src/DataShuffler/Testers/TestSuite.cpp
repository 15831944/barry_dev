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
// 05/14/2011	Created by Chen Ding 
////////////////////////////////////////////////////////////////////////////
#include "DataShuffler/Testers/TestSuite.h"

#include "Tester/TestSuite.h"
#include "Tester/TestMgr.h"
#include "Util/OmnNew.h"
#include "Util/File.h"
#include "Util/Ptrs.h"
#include "Util/BuffArray.h"
#include "DataShuffler/Testers/DocidShufflerTester.h"
#include "DataShuffler/Testers/DistMapShufflerTester.h"


OmnTestSuitePtr		
AosDataShufflerTestSuite::getSuite(const AosXmlTagPtr &testers)
{
	OmnTestSuitePtr suite = OmnNew OmnTestSuite("DataShuffler", "Test Suite");

	if (!testers)
	{
		// Get all the testers
		suite->addTestPkg(OmnNew AosDocidShufflerTester());
		return suite;
	}

	AosXmlTagPtr tester = testers->getFirstChild();
	while (tester)
	{
		OmnString name = tester->getNodeText();
		cout<< "my start-------------" << name.data() <<endl;
		if (name == "docid_tester")
		{
			suite->addTestPkg(OmnNew AosDocidShufflerTester());
		}
		else if (name == "dist_tester")
		{
			suite->addTestPkg(OmnNew AosDistMapShufflerTester());
		}
		else
		{
			OmnAlarm << "Unrecognized tester: " << name << enderr;
		}
		tester = testers->getNextChild();
	}

	return suite;
}