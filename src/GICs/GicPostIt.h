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
// 08/07/2010: Created by felicia
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_GICs_GicPostIt_h
#define Aos_GICs_GicPostIt_h

#include "GICs/GIC.h"
#include "SEUtil/Ptrs.h"
#include "Util/RCObject.h"
#include "Util/RCObjImp.h"
#include "Util/String.h"



class AosGicPostIt : public AosGic
{

public:
	AosGicPostIt(const bool flag);
	~AosGicPostIt();

	virtual bool	
	generateCode(
		const AosHtmlReqProcPtr &htmlPtr,
		AosXmlTagPtr &vpd,
		const AosXmlTagPtr &obj,
	    const OmnString &parentid,
		AosHtmlCode &code);

private:
	bool
		convertToJson(
			   const AosXmlTagPtr &vpd,
			   const AosXmlTagPtr &obj,
			   const OmnString &paneid,
			   const OmnString &panelid,

			   OmnString &jsonStr);
};

#endif
