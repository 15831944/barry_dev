////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// Modification History:
// 	Created: 2012/04/16 by Ken Lee
////////////////////////////////////////////////////////////////////////////
#include "IILMgr/IILBigHit.h"
#include "BitmapMgr/Bitmap.h"
#include "IILMgr/IILMgr.h"


bool
AosIILBigHit::clearIILPriv(const AosRundataPtr &rdata)
{
	bool rslt = resetSubIILInfo(rdata);
	aos_assert_r(rslt, false);

	mNumDocs = 0;
	mFlag = AOS_ACTIVE_FLAG;
	mHitcount = 0;
	mRootIIL = 0;
	mLevel = 0;

	mMemCap = 0;
	if (mDocBitmap)
	{
		mDocBitmap->clean();
		mDocBitmap = 0;
	}
	
	if (mNumEntries)
	{
		OmnDelete [] mNumEntries;
		mNumEntries = 0;
	}

	if (mIILIds)
	{
		OmnDelete [] mIILIds;
		mIILIds = 0;
	}

	return true;
}


bool
AosIILBigHit::deleteIILPriv(
		const bool true_delete,
		const AosRundataPtr &rdata)
{
	bool rslt = true;
	if (!isSingleIIL())
	{
		vector<u64> iilids;
		AosIILObjPtr iil;
		AosIILType iiltype;
		AosIILBigHitPtr subiil;
		for (i64 i = 0; i < mNumSubiils; i++)
		{
			subiil = mSubiils[i];
			if (true_delete)
			{
				iilids.push_back(mIILIds[i]);

				if (!subiil && mLevel >= 2)
				{
					subiil = getSubiilByIndexPriv(i, rdata);
					aos_assert_r(subiil, false);
				}

				if (!subiil)
				{
					iil = AosIILMgr::getSelf()->getIILFromHashPublic(
						mIILIds[i], mSiteid, iiltype, rdata);
					if (iil) subiil = (AosIILBigHit *)(iil.getPtr());
				}

				if (subiil)
				{
					rslt = subiil->deleteIILRecSafe(iilids, rdata);
					aos_assert_r(rslt, false);
				}
			}

			if (!subiil) continue;
			subiil->setDirty(false);
			rslt = AosIILMgr::getSelf()->returnIILPublic(subiil, rdata);
			aos_assert_r(rslt, false);
			
			mSubiils[i] = 0;
		}

		if (true_delete)
		{
			for (u32 i=0; i<iilids.size(); i++)
			{
				rslt = deleteFromLocalFileByID(iilids[i], mSnapShotId, rdata);
				aos_assert_r(rslt, false);
			}
		}
	}


	rslt = clearIILPriv(rdata);
	aos_assert_r(rslt, false);
	
	mIsDirty = true;
	rslt = saveToFilePriv(rdata);
	aos_assert_r(rslt, false);

	return true;
}


bool
AosIILBigHit::deleteIILRecPriv(
		vector<u64> &iilids,
		const AosRundataPtr &rdata)
{
	if (isSingleIIL()) return true;

	bool rslt = true;
	AosIILObjPtr iil;
	AosIILType iiltype;
	AosIILBigHitPtr subiil;
	for (i64 i=0; i<mNumSubiils; i++)
	{
		iilids.push_back(mIILIds[i]);

		subiil = mSubiils[i];
		if (!subiil && mLevel >= 2)
		{
			subiil = getSubiilByIndexPriv(i, rdata);
			aos_assert_r(subiil, false);
		}
				
		if (!subiil)
		{
			iil = AosIILMgr::getSelf()->getIILFromHashPublic(
				mIILIds[i], mSiteid, iiltype, rdata);
			if (iil) subiil = (AosIILBigHit *)(iil.getPtr());
		}

		if (!subiil) continue;
			
		rslt = subiil->deleteIILRecSafe(iilids, rdata);
		aos_assert_r(rslt, false);
			
		subiil->setDirty(false);
		rslt = AosIILMgr::getSelf()->returnIILPublic(subiil, rdata);
		aos_assert_r(rslt, false);
			
		mSubiils[i] = 0;
	}

	return true;
}


bool
AosIILBigHit::splitListPriv(
		const AosIILExecutorObjPtr &executor,
		const AosRundataPtr &rdata)
{
	//case 1: level 0 add doc over 5000, split
	//case 2: level 1 has multi level 0, level 0 over 5000
	//case 3: level 1 has 5000 level 0, level 0 over 5000
	//case 4: level 2 has multi level 1, level 1 has multi level 0, level 0 needs split
	//case 5: level 2 has multi level 1, level 1 has 5000 level 0, level 0 needs split
	
	// level 0:
	// 		no parent:
	//				1. create 2 new iils with iilids
	//				2. split conents to 2 new iils,
	//				3. change self to level 1, 
	//				4. index subiil info.
	// 		has parent:step 
	//				1: split 
	//				2: call parent function to notify parent.
	// level 1-n(notified by level 0):
	// 1. add sub, update sub info.
	// 2. if, too many subs:
	//    2.1 no parent:
	//			create 2 new iils in same level with iilids
	//			split content(subiil info) to 2 new iils(update all subiils' root)
	//			change self to level++
	//			index 2 new iils as its subs.
	//	  2.2 has parent:
	//			split
	//			update subiils to know new root
	//			notify parent

	aos_assert_r(splitCheck(), false);
	aos_assert_r(isLeafIIL(), false);

	AosIILBigHitPtr subiil = splitLeafContent(rdata);
	aos_assert_r(subiil, false);

	vector<AosIILBigHitPtr> subiil_list;
	subiil_list.push_back(subiil);
	if (isSingleIIL())
	{
		return splitListSinglePriv(subiil_list, rdata);
	}
	
	aos_assert_r(mParentIIL, false);
	return mParentIIL->subiilSplited(mIILIdx, subiil_list, executor, rdata);
}


bool 
AosIILBigHit::splitCheck()
{
	if (mNumSubiils <= mMaxSubIILs)
	{
		return true;
	}
	if (mParentIIL)
	{
		return mParentIIL->splitCheck();
	}
	if (mLevel == AosIILIdx::eMaxLevelIndex)
	{
		return false;
	}
	return true;
}


AosIILBigHitPtr
AosIILBigHit::splitLeafContent(const AosRundataPtr &rdata)
{
	AosIILBigHitPtr subiil = splitContentUtil(rdata);
	aos_assert_r(subiil, 0);

	// Initialize the new subiil
	i64 startidx = mNumDocs / 2;
	const i64 len = mNumDocs - startidx;
	//bool rslt = subiil->initSubiilLeaf(&mDocids[startidx], &mValues[startidx], len);
	AosBitmapObjPtr tmp_bitmap = AosGetBitmap();
	bool rslt = false;
/*
	rslt = mDocBitmap->copyDocids(startidx, len, tmp_bitmap, false);
	aos_assert_r(rslt, 0);
*/
//////////////////////////
u64 tmp_docid;
mDocBitmap->reset();

for(int i=0; i<startidx; i++)
{
	mDocBitmap->nextDocid(tmp_docid);
}

for(int i=0; i<len; i++)
{
	rslt = mDocBitmap->nextDocid(tmp_docid);
	aos_assert_r(rslt, false);
	tmp_bitmap->appendDocid(tmp_docid);
}
//////////////////////////

	rslt = subiil->initSubiilLeaf(tmp_bitmap);
	aos_assert_r(rslt, 0);

	// 5. Shrink this IIL

	mDocBitmap = AosBitmap::countAndAnotB(mDocBitmap, tmp_bitmap);

	// ModifyNumDocs
	mNumDocs = startidx;
	aos_assert_r(mNumDocs < mMaxBigIILSize, 0);
	
	return subiil;	
}


bool 
AosIILBigHit::initSubiilLeaf(AosBitmapObjPtr bitmap) 
{
	aos_assert_r(mIILType == eAosIILType_BigHit, false);

    mWordId = AOS_INVWID;
	// ModifyNumDocs
	aos_assert_r(mNumDocs < mMaxBigIILSize, false);


	if (mMinDocids)
	{
		OmnDelete [] mMinDocids;
		mMinDocids = 0;
	}

	if (mMaxDocids)
	{
		OmnDelete [] mMaxDocids;
		mMaxDocids = 0;
	}

	if (mIILIds)
	{
		OmnDelete [] mIILIds;
		mIILIds = 0;
	}
	if (mSubiils)
	{
		OmnDelete [] mSubiils;
		mSubiils = 0;
	}
	if (mNumEntries)
	{
		OmnDelete [] mNumEntries;
		mNumEntries = 0;
	}

    mFlag = 0;
    mHitcount = 0;
	//mTotalDocs = 0;
    //mIILDiskSize = 0;
    //mOffset = 0;
    //mSeqno = 0;
	mCompressedSize = 0;

    mNumSubiils = 0;
    mIILIdx = 0;

	bool rslt = prepareMemoryForReloading();
	aos_assert_r(rslt, false);

	mDocBitmap = bitmap->clone(0);
    mNumDocs = mDocBitmap->getNumBits(); 
	mIsDirty = true;
	return true;
}


bool 
AosIILBigHit::initSubiilParent(
		u64 *minDocids,
		u64 *maxDocids,
		u64 *iilids,
		i64 *numEntries,
		AosIILBigHitPtr *subiils,
		const i64 &numSubiils)
{
    mWordId = AOS_INVWID;
    mNumSubiils = numSubiils; 

	// set mMinDocids
	if (!mMinDocids)
	{
		mMinDocids = OmnNew u64[mMaxSubIILs + eExtraSubIILsSpace];
	}
	// set mMaxDocids
	if (!mMaxDocids)
	{
		mMaxDocids = OmnNew u64[mMaxSubIILs + eExtraSubIILsSpace];
	}

	aos_assert_r(mMinDocids, false);
	aos_assert_r(mMaxDocids, false);
	memset(mMinDocids, 0, sizeof(u64) * (mMaxSubIILs + eExtraSubIILsSpace));
	memcpy(mMinDocids, minDocids, sizeof(u64) * mNumSubiils);
	memset(mMaxDocids, 0, sizeof(u64) * (mMaxSubIILs + eExtraSubIILsSpace));
	memcpy(mMaxDocids, maxDocids, sizeof(u64) * mNumSubiils);

	// set mIILIds
	if (!mIILIds)
	{
		mIILIds = OmnNew u64[mMaxSubIILs + eExtraSubIILsSpace];
	}
	aos_assert_r(mIILIds, false);
	memset(mIILIds, 0, sizeof(u64) * (mMaxSubIILs + eExtraSubIILsSpace));
	memcpy(mIILIds, iilids, sizeof(u64) * mNumSubiils);

	// set mNumEntries
	if (!mNumEntries)
	{
		mNumEntries = OmnNew i64[mMaxSubIILs + eExtraSubIILsSpace];
	}
	aos_assert_r(mNumEntries, false);
	memset(mNumEntries, 0, sizeof(i64) * (mMaxSubIILs + eExtraSubIILsSpace));
	memcpy(mNumEntries, numEntries, sizeof(i64) * mNumSubiils);
	
	mNumDocs = 0;
	for(i64 i=0; i<mNumSubiils; i++)
	{
		mNumDocs += mNumEntries[i];
	}
	
	// set mSubiils
	if (!mSubiils)
	{
		bool rslt = createSubiilIndex();
		aos_assert_r(rslt, false);
		//mSubiils = OmnNew AosIILBigHitPtr[mMaxSubIILs + eExtraSubIILsSpace];
	}
	aos_assert_r(mSubiils, false);

	//ken 2012/11/12
	// this place must use for loop
	//memset(mSubiils, 0, sizeof(AosIILBigHitPtr) * (mMaxSubIILs + eExtraSubIILsSpace));
	//memcpy(mSubiils, subiils, sizeof(AosIILBigHitPtr) * mNumSubiils);
	for(i64 i=0; i<mMaxSubIILs + (i64)eExtraSubIILsSpace; i++)
	{
		mSubiils[i] = 0;
	}
	for(i64 i=0; i<mNumSubiils; i++)
	{
		mSubiils[i] = subiils[i];
	}
	
	// update info in subiils
	AosIILBigHitPtr thisPtr(this, false);
	for(i64 i=0; i<mNumSubiils; i++)
	{
		if (mSubiils[i])
		{
			mSubiils[i]->setIILIdx(i);
			mSubiils[i]->setParentIIL(thisPtr);
		}
	}

    mFlag = 0;
    mHitcount = 0;
    //mIILDiskSize = 0;
    //mOffset = 0;
    //mSeqno = 0;
	mCompressedSize = 0;

    mIILIdx = 0;
	mIsDirty = true;
	return true;
}


bool
AosIILBigHit::splitListSinglePriv(
		const vector<AosIILBigHitPtr> &subiil_list,
		const AosRundataPtr &rdata)
{
	// the 2nd subiil is created, now we need to :
	// 1. create a new subiil
	// 2. move content to new subiil
	// 3. make itself a root iil
	// 4. index 2 subiils
	
	// 1. create a new subiil
	//aos_assert_r(mNumDocs > 0, false);

	AosIILBigHitPtr subiil = splitContentUtil(rdata);
	aos_assert_r(subiil, false);

	// 2. move content to new subiil
	// Initialize the new subiil
	bool rslt = subiil->initSubiilLeaf(mDocBitmap);
	aos_assert_r(rslt, false);

	// 3. make itself a root iil

	mDocBitmap->clean();
	mLevel = 1;
	
	AosIILBigHitPtr thisPtr(this, false);
	subiil->setParentIIL(thisPtr);	
	subiil->setIILIdx(0);

	// 4. index 2 subiils
	rslt = createSubiilIndex();
	aos_assert_r(rslt, false);

	mSubiils[0] = subiil;
	mMinDocids[0] = subiil->getMinDocid();
	mMaxDocids[0] = subiil->getMaxDocid();
	mIILIds[0] = subiil->getIILID();
	mNumEntries[0] = subiil->getNumDocs();
	mNumDocs = subiil->getNumDocs();
	mNumSubiils = subiil_list.size() + 1;
	
	for(u32 i=0; i<subiil_list.size(); i++)
	{
		aos_assert_r(subiil_list[i], false);

		mSubiils[i+1] = subiil_list[i];
		mSubiils[i+1]->setParentIIL(thisPtr);
		mSubiils[i+1]->setIILIdx(i+1);
		
		mMinDocids[i+1] = mSubiils[i+1]->getMinDocid();
		mMaxDocids[i+1] = mSubiils[i+1]->getMaxDocid();
		mIILIds[i+1] = mSubiils[i+1]->getIILID();
		mNumEntries[i+1] = mSubiils[i+1]->getNumDocs();
		mNumDocs += mSubiils[i+1]->getNumDocs();

	}

	return true;	
}


bool
AosIILBigHit::subiilSplited(
		const i64 &iilIdx,
		const vector<AosIILBigHitPtr> &subiil_list,
		const AosIILExecutorObjPtr &executor,
		const AosRundataPtr &rdata)
{
	//1. update subiil info
	bool rslt = updateIndexData(iilIdx, true, true, rdata);
	aos_assert_r(rslt, false);

	rslt = addSubiils(iilIdx + 1, subiil_list, rdata);
	aos_assert_r(rslt, false);

	return subiilSplited(executor, rdata);
}				  


bool
AosIILBigHit::subiilSplited(
		const AosIILExecutorObjPtr &executor,
		const AosRundataPtr &rdata)
{
	//1. check whether it need to split
	//2. split the content
	//3. (need split) check whether it is root

	//1. check whether it need to split
	if (mNumSubiils <= mMaxSubIILs)
	{
		// do not need to split
		return true;
	}
	
	//2. split the content
	AosIILBigHitPtr newsubiil = splitParentContent(rdata);
	aos_assert_r(newsubiil, false);

	vector<AosIILBigHitPtr> new_subiil_list;
	new_subiil_list.push_back(newsubiil);

	//3. (need split) check whether it is root
	if (mParentIIL)
	{
		return mParentIIL->subiilSplited(mIILIdx, new_subiil_list, executor, rdata);
	}
	
	// it is root iil, and it need to split
	return splitListRootPriv(new_subiil_list, executor, rdata);
}				  


AosIILBigHitPtr
AosIILBigHit::splitContentUtil(const AosRundataPtr &rdata)
{
	// 1. Create the subiil
	AosIILObjPtr subiil = AosIILMgrSelf->createSubIILSafe(
		mIILID, mSiteid, mSnapShotId, eAosIILType_BigHit, mIsPersis, rdata);
	aos_assert_r(subiil, 0);
	aos_assert_r(subiil->getIILType() == eAosIILType_BigHit, 0);
	AosIILBigHitPtr newsubiil = (AosIILBigHit*)subiil.getPtr();
	
	newsubiil->setSnapShotId(mSnapShotId);

	// 2. Set subiil attributes
//	subiil->setRootIIL(mRootIIL);
//	newsubiil->setParentIIL(mParentIIL);
//	if (mIILIdx < 0) mIILIdx = 0;
//	newsubiil->setIILIdx(mIILIdx+1);
	newsubiil->setIILLevel(mLevel);
	newsubiil->setSiteid(mSiteid);
	
	mIsDirty = true;
	newsubiil->setDirty(true);
	return newsubiil;
}


AosIILBigHitPtr
AosIILBigHit::splitParentContent(const AosRundataPtr &rdata)
{
	AosIILBigHitPtr subiil = splitContentUtil(rdata);
	aos_assert_r(subiil, 0);

	// 4. Initialize the new subiil
	i64 startidx = mNumSubiils / 2;
	const i64 len = mNumSubiils - startidx;
	
	bool rslt = subiil->initSubiilParent(
		&mMinDocids[startidx], &mMaxDocids[startidx], &mIILIds[startidx], &mNumEntries[startidx], &mSubiils[startidx], len);
	aos_assert_r(rslt, 0);

	// 5. Shrink this IIL
	memset(&mMinDocids[startidx], 0, sizeof(u64) * len);
	memset(&mMaxDocids[startidx], 0, sizeof(u64) * len);
	memset(&mIILIds[startidx], 0, sizeof(u64) * len);
	memset(&mNumEntries[startidx], 0, sizeof(i64) * len);

	//ken 2012/11/12
	// this place must use for loop
	//memset(&mSubiils[startidx], 0, sizeof(AosIILBigHitPtr) * len);
	for(i64 i=0; i<len; i++)
	{
		mSubiils[startidx + i] = 0;
	}

	// ModifyNumDocs
	mNumSubiils = startidx;
	mNumDocs = 0;
	for(i64 i=0; i<mNumSubiils; i++)
	{
		mNumDocs += mNumEntries[i];
	}
	return subiil;	
}


bool
AosIILBigHit::splitListRootPriv(
		const vector<AosIILBigHitPtr> &subiil_list,
		const AosIILExecutorObjPtr &executor,
		const AosRundataPtr &rdata)
{
	// the 2nd subiil is created, now we need to :
	// 1. create a new subiil
	// 2. move content to new subiil
	// 3. make itself a root iil
	// 4. index 2 subiils
	
	// 1. create a new subiil
	AosIILBigHitPtr subiil = splitContentUtil(rdata);
	aos_assert_r(subiil, false);

	// 2. move content to new subiil
	// Initialize the new subiil
	bool rslt = subiil->initSubiilParent(mMinDocids, mMaxDocids, mIILIds, mNumEntries, mSubiils, mNumSubiils);
	aos_assert_r(rslt, false);

	memset(mMinDocids, 0, sizeof(u64) * mNumSubiils);
	memset(mMaxDocids, 0, sizeof(u64) * mNumSubiils);
	memset(mIILIds, 0, sizeof(u64) * mNumSubiils);
	memset(mNumEntries, 0, sizeof(i64) * mNumSubiils);

	//ken 2012/11/12
	// this place must use for loop
	//memset(mSubiils, 0, sizeof(AosIILBigHitPtr) * mNumSubiils);
	for(int i=0; i<mNumSubiils; i++)
	{
		mSubiils[i] = 0;
	}
	
	mLevel++;
	
	AosIILBigHitPtr thisPtr(this, false);
	subiil->setParentIIL(thisPtr);	
	subiil->setIILIdx(0);

	// 4. index 2 subiils
	//ken 2012/04/25
	//rslt = createSubiilIndex();
	//aos_assert_r(rslt, false);

	mSubiils[0] = subiil;
	mMinDocids[0] = subiil->getMinDocid();
	mMaxDocids[0] = subiil->getMaxDocid();
	mIILIds[0] = subiil->getIILID();
	mNumEntries[0] = subiil->getNumDocs();
	mNumDocs = subiil->getNumDocs();
	mNumSubiils = subiil_list.size() + 1;

	for(u32 i=0; i<subiil_list.size(); i++)
	{
		aos_assert_r(subiil_list[i], false);
		
		mSubiils[i+1] = subiil_list[i];
		mSubiils[i+1]->setParentIIL(thisPtr);
		mSubiils[i+1]->setIILIdx(i+1);
	
		mMinDocids[i+1] = mSubiils[i+1]->getMinDocid();
		mMaxDocids[i+1] = mSubiils[i+1]->getMaxDocid();
		mIILIds[i+1] = mSubiils[i+1]->getIILID();
		mNumEntries[i+1] = mSubiils[i+1]->getNumDocs();
		mNumDocs += mSubiils[i+1]->getNumDocs();
	}

	return true;	
}


bool
AosIILBigHit::addSubiils(
		const i64 &iilidx,
		const vector<AosIILBigHitPtr> &subiil_list,
		const AosRundataPtr &rdata)
{
	aos_assert_r(sanityCheckPriv(rdata), false);
	aos_assert_r(isParentIIL(),false);
	// It inserts the new subiil 'newsubiil' after 'crtsubiil'. This function
	// must be called by the root IIL.
	if (!mSubiils)
	{
		bool rslt = createSubiilIndex();
		aos_assert_r(rslt, false);
	}

	i64 num = subiil_list.size();
	if (num <= 0) 
	{
		return true;
	}

	aos_assert_r(mNumSubiils + num < mMaxSubIILs + (i64)eExtraSubIILsSpace, false);
	aos_assert_r(iilidx >= 0, false);

	// 1. Insert the new subiil in mSubiils[]
	for(i64 i=0; i<num; i++)
	{
		aos_assert_r(!mSubiils[mNumSubiils+i], false);
	}

	i64 num_to_move = mNumSubiils - iilidx;
	if (iilidx <= mNumSubiils-1)
	{
		//ken 2012/11/12
		// this place must use for loop
		//memmove(&mSubiils[iilidx+num], &mSubiils[iilidx], sizeof(AosIILBigHitPtr) * num_to_move);
		//memset(&mSubiils[iilidx], 0, sizeof(AosIILBigHitPtr) * num);
		for(int i=num_to_move; i>=0; i--)
		{
			mSubiils[iilidx+num+i] = mSubiils[iilidx+i];
		}
		for(int i=0; i<num; i++)
		{
			mSubiils[iilidx+i] = 0;
		}

        memmove(&mMinDocids[iilidx+num], &mMinDocids[iilidx], sizeof(u64) * num_to_move);
        memset(&mMinDocids[iilidx], 0, sizeof(u64) * num);

        memmove(&mMaxDocids[iilidx+num], &mMaxDocids[iilidx], sizeof(u64) * num_to_move);
        memset(&mMaxDocids[iilidx], 0, sizeof(u64) * num);

        memmove(&mIILIds[iilidx+num], &mIILIds[iilidx], sizeof(u64) * num_to_move);
		memset(&mIILIds[iilidx], 0, sizeof(u64) * num);

        memmove(&mNumEntries[iilidx+num], &mNumEntries[iilidx], sizeof(i64) * num_to_move);
		memset(&mNumEntries[iilidx], 0, sizeof(i64) * num);

		for (i64 i=iilidx+num; i<mNumSubiils+num; i++)
		{
			if (mSubiils[i].notNull())
			{
				mSubiils[i]->setIILIdx(i);
			}
		}
	}	

	AosIILBigHitPtr thisPtr(this, false);
	for(i64 i=0; i<num; i++)
	{
		aos_assert_r(subiil_list[i], false);

		mSubiils[iilidx+i] = subiil_list[i];
		mSubiils[iilidx+i]->setIILIdx(iilidx+i);
		mSubiils[iilidx+i]->setParentIIL(thisPtr);
		
		mIILIds[iilidx+i] = mSubiils[iilidx+i]->getIILID();
		mMinDocids[iilidx+i] = mSubiils[iilidx+i]->getMinDocid();
		mMaxDocids[iilidx+i] = mSubiils[iilidx+i]->getMaxDocid();
		mNumEntries[iilidx+i] = mSubiils[iilidx+i]->getNumDocs();
		mNumDocs += mSubiils[iilidx+i]->getNumDocs();

	}
	mNumSubiils += num;

	aos_assert_r(sanityCheckPriv(rdata), false);
	if (mParentIIL)
	{
		bool rslt = mParentIIL->updateIndexData(mIILIdx, true, true, rdata);
		aos_assert_r(rslt, false);
	}

	mIsDirty = true;
	aos_assert_r(sanityCheckPriv(rdata), false);
	return true;
}


bool	
AosIILBigHit::mergeSubiilPriv(
		const i64 &iilidx,
		const AosRundataPtr &rdata)
{
	return true;
}


bool
AosIILBigHit::createSubiilIndex()
{
//shawn when we create a branch node,call this function
	aos_assert_r(!mSubiils, false);

	if (!mSubiils)
	{
		mSubiils = OmnNew AosIILBigHitPtr[mMaxSubIILs + eExtraSubIILsSpace];
		aos_assert_r(mSubiils, false);
	}
/*
	if (!mMinVals)
	{
		mMinVals = OmnNew u64[mMaxSubIILs + eExtraSubIILsSpace];
		aos_assert_r(mMinVals, false);
		memset(mMinVals, 0, sizeof(u64) * (mMaxSubIILs + eExtraSubIILsSpace));
	}
	
	if (!mMaxVals)
	{
		mMaxVals = OmnNew u64[mMaxSubIILs + eExtraSubIILsSpace];
		aos_assert_r(mMaxVals, false);
		memset(mMaxVals, 0, sizeof(u64) * (mMaxSubIILs + eExtraSubIILsSpace));
	}
*/		
	if (!mMinDocids)
	{
		mMinDocids = OmnNew u64[mMaxSubIILs + eExtraSubIILsSpace];
		aos_assert_r(mMinDocids, false);
		memset(mMinDocids, 0, sizeof(u64) * (mMaxSubIILs + eExtraSubIILsSpace));
	}

	if (!mMaxDocids)
	{
		mMaxDocids = OmnNew u64[mMaxSubIILs + eExtraSubIILsSpace];
		aos_assert_r(mMaxDocids, false);
		memset(mMaxDocids, 0, sizeof(u64) * (mMaxSubIILs + eExtraSubIILsSpace));
	}
	
	if (!mIILIds)
	{
		mIILIds = OmnNew u64[mMaxSubIILs + eExtraSubIILsSpace];
		aos_assert_r(mIILIds, false);
		memset(mIILIds, 0, sizeof(u64) * (mMaxSubIILs + eExtraSubIILsSpace));
	}
	
	if (!mNumEntries)
	{
		mNumEntries = OmnNew i64[mMaxSubIILs + eExtraSubIILsSpace];
		aos_assert_r(mNumEntries, false);
		memset(mNumEntries, 0, sizeof(i64) * (mMaxSubIILs + eExtraSubIILsSpace));
	}
	
	return true;
}
