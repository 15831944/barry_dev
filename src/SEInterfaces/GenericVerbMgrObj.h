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
// 2014/10/26 Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_SEInterfaces_GenericVerbMgrObj_h
#define Aos_SEInterfaces_GenericVerbMgrObj_h

#include "Jimo/Jimo.h"
//#include "JQLStatement/Ptrs.h"
#include "SEInterfaces/Ptrs.h"
#include "Rundata/Ptrs.h"
#include "Util/Ptrs.h"
#include "XmlUtil/XmlTag.h"


class AosGenericVerbMgrObj : public AosJimo
{
	static  AosGenericVerbMgrObjPtr smGenericVerbMgrObj;

public:
	AosGenericVerbMgrObj(const int version);

	static AosGenericVerbMgrObjPtr getSelf(AosRundata *rdata);

	virtual bool addGenericVerb(AosRundata *rdata, const AosGenericVerbObjPtr &verb) = 0;
	virtual bool proc( AosRundata *rdata, 
						const OmnString &verb,
						const OmnString &obj_type,
						const OmnString &obj_name, 
						const OmnString &json) = 0;
};
#endif
