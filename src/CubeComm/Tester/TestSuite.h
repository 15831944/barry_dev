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
//
// Modification History:
// 2014/11/25 Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_CubeCome_Tester_TestSuite_h
#define Aos_CubeCome_Tester_TestSuite_h

#include "Tester/Ptrs.h"
#include "Util/String.h"
#include "Tester/TestPkg.h"
#include "CubeComm/CubeComm.h"
class AosCubeCommTestSuite:public OmnTestPkg
{
private:
	OmnTestSuitePtr		mSuite;

public:
	AosCubeCommTestSuite() {}
	~AosCubeCommTestSuite() {}

	static OmnTestSuitePtr		getSuite();
};
#endif
