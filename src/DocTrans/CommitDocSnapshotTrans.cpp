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
// 07/28/2011	Created by Linda 
////////////////////////////////////////////////////////////////////////////
#include "DocTrans/CommitDocSnapshotTrans.h"

#include "API/AosApi.h"
#include "SEInterfaces/DocSvrObj.h"
#include "TransUtil/TaskTransChecker.h"
#include "XmlUtil/XmlTag.h"

AosCommitDocSnapshotTrans::AosCommitDocSnapshotTrans(const bool regflag)
:
AosDocTrans(AosTransType::eCommitDocSnapshot, regflag)
{
}


AosCommitDocSnapshotTrans::AosCommitDocSnapshotTrans(
		const int virtual_id,
		const AosDocType::E doc_type,
		const u64 &snap_id,
		const u64 &task_docid,
		const bool need_save)
:
AosDocTrans(AosTransType::eCommitDocSnapshot, virtual_id, true, need_save, false, snap_id),
mVirtualId(virtual_id),
mDocType(doc_type),
mTaskDocid(task_docid)
{
}


AosCommitDocSnapshotTrans::~AosCommitDocSnapshotTrans()
{
}


bool
AosCommitDocSnapshotTrans::serializeFrom(const AosBuffPtr &buff)
{
	bool rslt = AosDocTrans::serializeFrom(buff);
	aos_assert_r(rslt, false);
	
	mVirtualId = buff->getInt(-1);
	aos_assert_r(mVirtualId >=0, false);
	mDocType = (AosDocType::E)buff->getU32(0);

	mTaskDocid = buff->getU64(0);
	aos_assert_r(mTaskDocid, false);
	setDistId(mVirtualId);
	return true;
}


bool
AosCommitDocSnapshotTrans::serializeTo(const AosBuffPtr &buff)
{
	bool rslt = AosDocTrans::serializeTo(buff);
	aos_assert_r(rslt, false);
	
	buff->setInt(mVirtualId);
	buff->setU32(mDocType);
	aos_assert_r(mTaskDocid, false);
	buff->setU64(mTaskDocid);
	return true;
}


AosTransPtr
AosCommitDocSnapshotTrans::clone()
{
	return OmnNew AosCommitDocSnapshotTrans(false);
}


bool
AosCommitDocSnapshotTrans::proc()
{
	bool rslt = AosDocSvrObj::getDocSvr()->commitSnapshot(
			mVirtualId, mDocType, mSnapshotId, getTransId(), mRdata);	

	AosTaskTransChecker::getSelf()->removeEntry(mTaskDocid, mVirtualId, mSnapshotId); 
	return rslt;
}

