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
// 05/26/2012 Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_SdocAction_ActDeleteIILEntry_h
#define Aos_SdocAction_ActDeleteIILEntry_h

#include "Actions/SdocAction.h"


class AosActDeleteIILEntry : virtual public AosSdocAction
{

public:
	AosActDeleteIILEntry(const bool flag);
	~AosActDeleteIILEntry();

	virtual bool run(const AosXmlTagPtr &def, const AosRundataPtr &rdata);
	virtual AosActionObjPtr clone( const AosXmlTagPtr &def, const AosRundataPtr &rdata) const;
};
#endif
