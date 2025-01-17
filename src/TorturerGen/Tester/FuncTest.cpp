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
// 5/18/2007 Created by TorturerGen Facility
//////////////////////////////////////////////////////////////////////////
#include "TorturerGen/Tester/FuncTest.h"

#include "Debug/Debug.h"
#include "Tester/Test.h"
#include "Tester/TestMgr.h"
#include "Util/GenTable.h"


AosFuncTest::AosFuncTest()
{
    mBasicTestRepeat = 10000;
}


AosFuncTest::~AosFuncTest()
{
}


bool
AosFuncTest::start()
{
    basicTest(mBasicTestRepeat, mTable);
    return true;
}


bool
AosFuncTest::basicTest(const u32 repeat, const AosGenTablePtr &table)
{
    return true;
}


