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
// 10/21/2011	Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_IILTransMap_Testers_IILMergerTester_h
#define Aos_IILTransMap_Testers_IILMergerTester_h

#include "Util/Opr.h"
#include "Util/Buff.h"
#include "Rundata/Ptrs.h"
#include "Rundata/Rundata.h"
#include "SearchEngine/Ptrs.h"
#include "Tester/TestPkg.h"
#include "Thread/ThrdShellProc.h"
#include "Thread/Ptrs.h"
#include <set>
#include <stdlib.h>

using namespace std;
class AosIILMergerTester : public OmnTestPkg, virtual public OmnThreadedObj
{
private:
	enum
	{
		mNumThreads = 2
	};

public:
	AosIILMergerTester();
	~AosIILMergerTester();

	virtual bool    threadFunc(OmnThrdStatus::E &state, const OmnThreadPtr &thread);
	virtual bool    signal(const int threadLogicId){return true;}
	virtual bool    checkThread(OmnString &err, const int thrdLogicId) const{return false;}

	static vector<OmnThreadPtr> mThreads;
	static multiset<string> smCheck000;
	static OmnMutexPtr sgLock;
	virtual bool		start();
private:
	bool basicTest();
	void randString(char* buff, int i, int style);
	void getEntryConf(int &bktnum, u32 &mementries, u32 &maxentries);
};


#endif
