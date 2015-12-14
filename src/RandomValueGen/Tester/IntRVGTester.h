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
// 05/06/2007 Created by TorturerGen Facility
//////////////////////////////////////////////////////////////////////////
#ifndef Aos_RandomValueGen_Tester_AosIntRVGTester_h
#define Aos_RandomValueGen_Tester_AosIntRVGTester_h

#include "RandomValueGen/Tester/RVGTester.h"



class AosIntRVGTester : public AosRVGTester
{
private:

public:
    AosIntRVGTester();
    ~AosIntRVGTester();

    virtual bool     start();


private:
	bool	createData();
};
#endif
