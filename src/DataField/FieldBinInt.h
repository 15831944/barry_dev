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
// 01/16/2014	Created by Young
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_DataField_FieldBinInt_h
#define Aos_DataField_FieldBinInt_h

#include "DataField/DataField.h"


class AosFieldBinInt : virtual public AosDataField
{
	OmnDefineRCObject;

public:
	AosFieldBinInt(const bool reg);
	AosFieldBinInt(const AosFieldBinInt &rhs);
	~AosFieldBinInt();

	virtual AosDataType::E getDataType(
						AosRundata *rdata, 
						AosDataRecordObj *record) const
	{	
		return AosDataType::eInt32;
	}
	virtual bool	getDefaultIgnoreSerialize() {return false;}
	virtual bool	needValueFromField() {return false;}
	
	virtual AosDataFieldObjPtr clone(AosRundata *rdata) const;

	virtual bool	setValueToRecord(
						char * const data,
						const int data_len,
						const AosValueRslt &value, 
						bool &outofmem,
						AosRundata* rdata);

	virtual bool	getValueFromRecord(
						AosDataRecordObj* record,
						const char * data,
						const int len,
						int &idx,
						AosValueRslt &value, 
						const bool copy_flag,
						AosRundata* rdata);

	virtual AosDataFieldObjPtr create(
						const AosXmlTagPtr &def,
						AosDataRecordObj *record,
						AosRundata *rdata) const;

private:
	bool			config(
						const AosXmlTagPtr &def,
						AosDataRecordObj *record,
						AosRundata *rdata);

};

#endif
