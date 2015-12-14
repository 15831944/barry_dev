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
// 10/06/2011	Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#ifndef AOS_IILTrans_GetDocid_h
#define AOS_IILTrans_GetDocid_h

#include "TransUtil/IILTrans.h"
#include "IILTrans/IILTransInclude.h"
#include "TransUtil/Ptrs.h"
#include "Util/Opr.h"


class AosIILTransGetDocid : public AosIILTrans
{
	OmnString	mKey;
	AosOpr		mOpr;
	bool		mReverse;
	AosIILType	mIILType;
public:
	AosIILTransGetDocid(const bool regflag);
	AosIILTransGetDocid(
		const OmnString &iilname,
		const AosIILType &iiltype,
		const OmnString &key,
		const AosOpr opr,
		const bool reverse,
		const bool need_save,
		const bool need_resp,
		const u64 snap_id);
	AosIILTransGetDocid(
		const u64 &iilid,
		const AosIILType &iiltype,
		const OmnString &key,
		const AosOpr opr,
		const bool reverse,
		const bool need_save,
		const bool need_resp,
		const u64 snap_id);
	~AosIILTransGetDocid(){}

	// Trans Interface
	virtual bool serializeTo(const AosBuffPtr &buff);
	virtual bool serializeFrom(const AosBuffPtr &buff);
	virtual AosTransPtr clone();
	virtual bool procGetResp();

	// IILTrans Interface
	virtual bool proc(const AosIILObjPtr &iilobj,
			AosBuffPtr &resp_buff,
			const AosRundataPtr &rdata);
	virtual AosIILType getIILType() const;
	virtual int getSerializeSize() const;

	OmnString getKey() const {return mKey;}
	AosOpr getOpr() const {return mOpr;}
	bool getReverse() const {return mReverse;}
	virtual bool needCreateIIL() const {return false;}
};

#endif