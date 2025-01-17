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
// 05/06/2007 Created by Chen Ding
//
//////////////////////////////////////////////////////////////////////////
#include "RandomValueGen/Tester/Util.h"

#include "Alarm/Alarm.h"
#include "alarm/Alarm.h"
#include "RandomValueGen/RVG.h"
#include "Util/GenTable.h"
#include "Util/GenRecord.h"
#include "Util/String.h"


bool
AosCliTorturerUtil_addToTable(
				const AosGenTablePtr &table, 
				const OmnString &value, 
				const AosRVGPtr &parm)
{
	if (table->isFull()) return true;
	AosGenRecordPtr record = table->createRecord();
	aos_assert_r(record, false);
	record->resetMarks();

	if (!parm->newRecordAdded(record))
	{
		OmnAlarm << "Failed to process the event: newRecordAdded" << enderr;
		return false;
	}
	record->removeMarks();

	table->appendRecord(record);
	return true;
}

