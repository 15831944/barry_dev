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
// 2010/10/23	Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_SearchEngine_TesterNew_IILCompStrTester_h
#define Aos_SearchEngine_TesterNew_IILCompStrTester_h

#include "Rundata/Ptrs.h"
#include "SearchEngine/Ptrs.h"
#include "IILMgr/Ptrs.h"
#include "Tester/TestPkg.h"
#include "Util/Opr.h"


class AosIILCompStrTester : public OmnTestPkg
{
public:
	enum 
	{
		eMaxCheckedIILs = 1000,
		eMaxIILLen = 5000
	};
//eMaxCheckedIILs = 10000
//eMaxIILs = 70000,
	enum Operation
	{
		eVerifyGetObjid, 
		eAddEntry,
		eDeleteEntry,
		eModifyEntry,

		eOperationMax
	};

private:
	int				mNumDocs;
	int				mVerifyGetObjidWeight;
	AosIILCompStrPtr	mStriil;
	OmnString		mIILName;
	int				mTotal;
	int				mAddOpr;
	int				mDelOpr;
	int				mModOpr;
	int				mVerifyOpr;
	AosRundataPtr	mRunData;

public:
	AosIILCompStrTester();
	~AosIILCompStrTester();

	virtual bool		start();

private:
	void	toString();
	bool	basicTest();
	bool	torture();
	bool 	verifyObjidIIL();
	bool 	verifyObjidDuplicated();
	bool 	verifyObjidDuplicatedEntries();
	bool 	verifyGetObjid();
	bool 	retrieveAllObjids();
//	bool 	copyData1(const OmnString &iilname);
	bool 	verifyNextDocidSafe(
				const bool reverse, 
				const bool value_unique); 
	bool 	verifyValues(
				const OmnString &iilname, 
				const bool value_unique,
				const bool docid_unique);
	AosOpr pickOperator();

	bool 	tortureCheckDocSafe(
				const int tries,
				const bool value_unique, 
				const bool docid_unique, 
				char **values, 
				const u64 *docids, 
				const int num_docs);
	bool 	tortureNextDocidSafe(
				const int tries,
				const bool value_unique, 
				const bool docid_unique, 
				char **values, 
				const u64 *docids, 
				const int num_docs);
	bool	searchNormal(
				const OmnString &value, 
				const bool reverse,
				const bool value_unique, 
				const bool docid_unique,
				const u64 &docid, 
				const AosOpr opr,
				const bool value_valid);
	bool 	searchGE(
				const OmnString &value, 
				const bool reverse,
				const bool value_unique, 
				const bool docid_unique,
				const u64 &expected_docid, 
				const AosOpr opr,
				const bool value_valid);
	bool 	searchEQ(
				const OmnString &value, 
				const bool reverse,
				const bool value_unique, 
				const bool docid_unique,
				const u64 &expected_docid);
	bool 	searchLT(
				const OmnString &value, 
				const bool reverse,
				const bool value_unique, 
				const bool docid_unique,
				const u64 &expected_docid);
	bool	searchLE(
				const OmnString &value, 
				const bool reverse,
				const bool value_unique, 
				const bool docid_unique,
				const u64 &expected_docid, 
				const AosOpr opr,
				const bool value_valid);
	bool	searchNormalLE(
				const OmnString &value, 
				const bool value_unique,
				const bool docid_unique,
				const u64 &expected_docid, 
				const AosOpr opr,
				const bool value_valid);
	bool	searchReverseLE(
				const OmnString &value, 
				const bool value_unique,
				const bool docid_unique,
				const u64 &expected_docid, 
				const AosOpr opr,
				const bool value_valid);
	bool 	searchNE(
				const OmnString &value, 
				const bool reverse,
				const bool value_unique, 
				const bool docid_unique,
				const u64 &expected_docid);
	bool 	searchReverseGE(
				const OmnString &value, 
				const bool value_unique,
				const bool docid_unique,
				const u64 &expected_docid, 
				const AosOpr opr,
				const bool value_valid);
	bool 	searchNormalGE(
				const OmnString &value, 
				const bool value_unique,
				const bool docid_unique,
				const u64 &expected_docid, 
				const AosOpr opr,
				const bool value_valid);
	bool 	searchNormalGT(
				const OmnString &value, 
				const bool value_unique,
				const bool docid_unique,
				const u64 &expected_docid);
	bool 	verifyStrIIL(const AosIILCompStrPtr &iil);
	bool 	verifyAllIILS(const u64 &start_iilidx, const u64 &end_iilidx);
	bool 	loadStrIIL(const OmnString &iilname);

	//tank
	bool	addEntry();
	bool 	deleteEntry();
	bool	modifyEntry();
private:
	AosIILCompStrPtr pickIIL(int &idx,const bool create_new);
	bool
	removeEntry(
		char **values,
		u64 *docids,
		const int idx,
		const int num_docs,
		const u64 &iilid);

public:
	bool	doesDocidExist(
				const AosIILCompStrPtr &iil,
				const OmnString &value,
				const u64 &docid);
	bool	getUnique(
			u64 iilid, 
			bool &value_unique, 
			bool &docid_unique);

	int	findValueDocid(
			const OmnString &value,
			const u64 &docid, 
			char **values, 
			const u64 *docids,
			const int num_values, 
			bool &found);

	int findValue(
				const OmnString &value, 
				char **values, 
//				const u64 *docids,
				const int num_values, 
				bool &found);

	bool addValueToArray(
		const OmnString &value, 
		const u64 &docid,
		char**	values,
		u64* docids,
		const int num_docs);

	bool removeValueFromArray(
		const OmnString &value, 
		const u64 &docid,
		char**	values,
		u64* docids,
		const int num_docs);

	bool modifyValueFromArray(
		const OmnString &oldvalue, 
		const u64 &olddocid,
		const OmnString &newvalue, 
		const u64 &newdocid,
		char**	values,
		u64* docids,
		const int num_docs);
	bool compareValueDocid2(const int num_docs, const int iilpos);

//	bool addValueToArray(
//				const OmnString &value, 
//				const u64 &docid,
//				const u64 &iilid,
//				const bool value_unique, 
//				const bool docid_unique);
private:
	bool
	insertDoc(
			const u64 &iilid, 
			const OmnString &value, 
			const u64 &docid, 
			const u32 idx);

	bool
	verifyIIL(const AosIILCompStrPtr &iil, const int iilpos);

	bool 
	verifyIIL(
		const u32 num_docs,
		const AosIILCompStrPtr &iil, 
		char **values, 
		const u64 *docids);
	bool 
	verifyEntries(
		const u32 num_docs,
		const AosIILCompStrPtr &iil, 
		char **values, 
		const u64 *docids);
	bool	compareValueDocid(const int num_docs, const int iilpos);
	int 
	compareValueDocid(
			const char* str1,
			const u64 docid1,
			const char* str2,
			const u64 docid2);
	void	Clean();
	
	inline bool 
	valueMatch(
		const char *v1, 
		const AosOpr opr, 
		const OmnString &value)
	{
		int rslt = strcmp(v1, value.data());

		switch (opr)
		{
			case eAosOpr_le: return rslt <= 0;
			case eAosOpr_lt: return rslt < 0;
			case eAosOpr_eq: return rslt == 0;
			case eAosOpr_gt: return rslt > 0;
			case eAosOpr_ge: return rslt >= 0;
			case eAosOpr_ne: return rslt != 0;
			default: return false;
		}
		return false;
	}

};


#endif
