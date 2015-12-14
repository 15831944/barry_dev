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
// This file is automatically generated by the TorturerGen facility.  
//
// Modification History:
// 3/4/2007: Created by TorturerGen facility
////////////////////////////////////////////////////////////////////////////

#include "Tester/TestMgr.h"
          
#include "AppMgr/App.h"
#include "Debug/Debug.h" 
#include "Porting/GetTime.h"
#include "SingletonClass/SingletonMgr.h"    
#include "Tester/TestSuite.h"
#include "Tester/TestPkg.h"
#include "CliTorturer/Tester/TestSuite.h"
#include "Util/OmnNew.h"
  
 

int 
main(int argc, char **argv)
{
	OmnApp theApp(argc, argv);
	try
	{
		// theApp.startSingleton(OmnNew OmnStoreMgrSingleton());
	}

	catch (const OmnExcept &e)
	{
		OmnAlarm << "Failed to start the application: " << e.toString() << enderr;
		theApp.exitApp();
		return 0;
	}

	int idx = 0;
	OmnString logFilename;
    while (idx < argc)
	{
	    if (strcmp(argv[idx], "-l") == 0)
		{
			logFilename = argv[idx+1];
			idx += 2;
			continue;
		}
		else
		{
			idx++;
		}
	}

		       
	// 
	// This is the application part
	//
	OmnTestMgrPtr testMgr = OmnNew OmnTestMgr("Util/Tester", "Try", "Chen Ding");
	testMgr->addSuite(AosCliTorturerTestSuite::getSuite());
	if (logFilename != "")
	{
		if (!AosCliTorturerTestSuite::openLogfile(logFilename))
		{
			OmnAlarm << "Failed to open the log file: " << logFilename << enderr;
			theApp.exitApp();
			return 0;
		}
	}

	cout << "Start Testing ..." << endl;
 
	testMgr->start();

	cout << "\nFinished. " << testMgr->getStat() << endl;

	testMgr = 0;
 
	// theApp.appLoop();
	theApp.exitApp();
	return 0;
} 

 