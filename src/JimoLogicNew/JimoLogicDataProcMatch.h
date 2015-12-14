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
// 2015/07/23 Created by Bryant Zhou 
////////////////////////////////////////////////////////////////////////////
#ifndef AOS_JimoLogicNew_JimoLogicDataProcMatch_h
#define AOS_JimoLogicNew_JimoLogicDataProcMatch_h

#include "JimoLogicNew/JimoLogicDataProc.h"
#include "JimoParser/JimoParser.h"

#include "Util/Ptrs.h"
#include "XmlUtil/Ptrs.h"


#include <vector>

class AosJimoLogicDataProcMatch : public AosJimoLogicDataProc
{
	OmnDefineRCObject;

private:
	OmnString		    		mType;
    OmnString           		mDataProcName;
    vector<OmnString> 			mInputs;               
	OmnString					mOutput;
	
	OmnString  					mDataprocMatchName;
	vector<OmnString>			mInputNames;
	OmnString					mOutputName;
	vector<OmnString> 			mLeftMatchKeys;
	vector<OmnString> 			mRightMatchKeys;
    int                 		mSplit;
	vector<AosExprObjPtr> 		mNameValueList;
	OmnString					mCache;
	OmnString 					mErrmsg;

public:
	AosJimoLogicDataProcMatch(const int version);
	~AosJimoLogicDataProcMatch();

	// Jimo Interface
	virtual AosJimoPtr cloneJimo() const;

	// AosGenericObj interface
	virtual bool parseJQL(
					AosRundata *rdata, 
					AosJimoParserObj *jimo_parser, 
					AosJimoProgObj *prog,
					bool &parsed, 
					bool dft = false);

	// AosJimoLogicObjNew interface
	virtual bool compileJQL(                       
			        AosRundata *rdata,
					AosJimoProgObj *prog);

	bool getOutputName(AosRundata *rdata, AosJimoProgObj *prog, OmnString &name);

	virtual bool run(
					AosRundata *rdata, 
					AosJimoProgObj *job,
					OmnString &statements_str,
					bool isparse);
	//arvin 2015.09.23
	//JIMODB-872
	virtual bool getInputV(vector<OmnString> &inputs);
private:
	bool createMatchDataproc(AosRundata *rdata, AosJimoProgObj *jimo_prog, OmnString &);
	bool parseRun(AosRundata* rdata, OmnString &stmt, AosJimoProgObj *jimo_prog);
	bool addMatchTask(AosRundata *rdata, AosJimoProgObj *jimo_prog);
	bool processInput(
					AosRundata *rdata,
					AosJimoProgObj *prog,
					OmnString &statements_str);

};
#endif
