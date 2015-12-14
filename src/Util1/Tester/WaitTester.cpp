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
// 5/27/2007 Created by TorturerGen Facility
//////////////////////////////////////////////////////////////////////////
#include "Util1/Tester/WaitTester.h"

#include "Debug/Debug.h"
#include "Random/RandomUtil.h"
#include "Tester/Test.h"
#include "Tester/TestMgr.h"
#include "Util/GenTable.h"
#include "Util1/Wait.h"
#include "Util1/Time.h"


AosWaitTester::AosWaitTester()
{
    mBasicTestRepeat = 10000;
}


AosWaitTester::~AosWaitTester()
{
}


bool
AosWaitTester::start()
{
	u32 tries = 1000;
    basicTest(tries, mTable);
    return true;
}


bool
AosWaitTester::basicTest(const u32 tries, const AosGenTablePtr &table)
{
	for (u32 i=0; i<tries; i++)
	{
		int sec = aos_next_int(1, 20);
		cout << "To wait: " << sec << endl;
		uint crtsec, crtusec;
		OmnTime::getRealtime(crtsec, crtusec);
		OmnWait::getSelf()->wait(sec, 0);
		uint crtsec1, crtusec1;
		OmnTime::getRealtime(crtsec1, crtusec1);
		int actual = (crtsec1 - crtsec) * 1000000 + crtusec1 - crtusec;
		actual = actual/1000;
		OmnTCTrue(actual >= sec * 1000 - 30 && actual <= sec * 1000 + 30) 
			<< actual << endtc;
		cout << "Actual: " << actual << ". Delta: " 
			<< sec * 1000 - actual << endl;
	}

    return true;
}

