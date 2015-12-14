////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
//
// Modification History:
// 06/16/2015 Created by YanYan 
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_JimoDataProc_DataProcDistinct_h
#define Aos_JimoDataProc_DataProcDistinct_h

#include "JimoDataProc/JimoDataProc.h"

#include "SEInterfaces/RecordsetObj.h"

#include "AosConf/DataRecordFixbin.h"
#include "AosConf/DataRecordCtnr.h"
#include "AosConf/DataAssembler.h"
#include "JSON/JSON.h"
#include "Util/StrSplit.h"

#include <map>
#include <vector>
#include <boost/make_shared.hpp>   
using namespace std;

class AosDataProcDistinct : public	AosJimoDataProc
{
private:
	vector<AosDataRecordObjPtr>			mInputRecords;
	AosDataRecordObjPtr 				mOutputRecord;
	vector<AosExprObjPtr>				mLeftFieldExprs;
	vector<AosExprObjPtr>				mRightFieldExprs;
	OmnString							mOutCurrKey;
	bool								mLeftAdd;
	bool								mRightAdd;

public:
	AosDataProcDistinct(const int ver);
	AosDataProcDistinct(const AosDataProcDistinct &proc);
	~AosDataProcDistinct();

	virtual AosJimoPtr cloneJimo() const;  
	virtual AosDataProcObjPtr cloneProc();

	virtual AosDataProcStatus::E procData(
						AosRundata *rdata,
						AosDataRecordObj **input_records,
						AosDataRecordObj **output_records);

	virtual AosDataProcStatus::E procData(
						AosRundata *rdata,
						const AosRecordsetObjPtr &lhs_recordset,
						const AosRecordsetObjPtr &rhs_recordset,
						AosDataRecordObj **output_records);
	bool createByJql(
						AosRundata *rdata,
						const OmnString &dpname,
						const OmnString &jsonstr, 
						const AosJimoProgObjPtr &prog);

private:
	bool			config(
						const AosXmlTagPtr &def,
						const AosRundataPtr &rdata);

	bool 			createOutput(
						const AosRundataPtr &rdata,
						const OmnString &dpname,
						const AosDataRecordType::E type);

	virtual void setInputDataRecords(vector<AosDataRecordObjPtr> &records);
	bool 			appendRecord(
						AosDataRecordObj **input_records,
						AosDataRecordObj *record,
						const OmnString &key,
						AosRundata *rdata);
	int compare(const OmnString &left, const OmnString &right);
};

#endif
