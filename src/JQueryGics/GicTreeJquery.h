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
// 07/04/2012 Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_GICs_GicTreeJquery_h
#define Aos_GICs_GicTreeJquery_h

#include "GICs/GIC.h"
#include "SEUtil/Ptrs.h"
#include "Util/RCObject.h"
#include "Util/RCObjImp.h"
#include "Util/String.h"



class AosGicTreeJquery : public AosGic
{

public:
	AosGicTreeJquery(const bool flag);
	~AosGicTreeJquery();

	virtual bool generateCode(
		const AosHtmlReqProcPtr &htmlPtr,
		AosXmlTagPtr &vpd, 
		const AosXmlTagPtr &obj,
		const OmnString &parentId,
		AosHtmlCode &code);
};


#endif
