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
//	12/07/2009	Created by Chen Ding 
////////////////////////////////////////////////////////////////////////////
#ifndef Omn_Util_Buff_h
#define Omn_Util_Buff_h

#include "alarm_c/alarm.h"
#include "Alarm/Alarm.h"
#include "aosUtil/Types.h"
#include "Debug/Debug.h"
#include "Util/DataTypes.h"
#include "Util/String.h"
#include "Util/MemoryChecker.h"
#include "Util/MemoryCheckerObj.h"
#include "Util/Ptrs.h"
#include "Util/OmnNew.h"
#include "UtilComm/Ptrs.h"

class AosBuff : virtual public OmnRCObject, public AosMemoryCheckerObj
{
	OmnDefineRCObject;

	enum
	{
		eDftMaxBuffLen = 2000000000,		// 2G
		eDftIncSize = 100000000,			// 100M
		eDftBuffLen = 1000
	};

	enum
	{
		eFieldTypeInvalid, 

		eFieldTypeU8, 
		eFieldTypeU16, 
		eFieldTypeU24, 
		eFieldTypeU32, 
		eFieldTypeU40, 
		eFieldTypeU48, 
		eFieldTypeU56, 
		eFieldTypeU64, 

		eFieldTypeInt8, 
		eFieldTypeInt16, 
		eFieldTypeInt24, 
		eFieldTypeInt32, 
		eFieldTypeInt40, 
		eFieldTypeInt48, 
		eFieldTypeInt56, 
		eFieldTypeInt64, 

		eFieldTypeVarUint, 

		eFieldTypeStr, 
		eFieldTypeBool, 
	};


private:
	void (*mCB)(i64, i64);
	char *			mBuff;
	i64				mBuffLen;
	i64				mCrtIdx;
	i64				mDataLen;
	bool			mDeleteFlag;
	OmnConnBuffPtr	mConnBuff;
	i64				mMemoryUsed;		// Chen Ding, 2013/05/13

	static i64  	smMaxBuffLen;
	static i64 		smTotalBuffsCreated;

public:
	AosBuff();
	AosBuff(char *buff, 
			const i64 &bufflen, 						// Chen Ding, 2013/03/02
			const i64 &datalen);
	AosBuff(const i64 &bufflen);	// Chen Ding, 2013/03/02
	AosBuff(const OmnConnBuffPtr &connbuff);

	AosBuff(const i64 &bufflen, void (*cb)(i64, i64) AosMemoryCheckDecl);
	~AosBuff();

	AosBuffPtr	copyContents(
			const i64 &idx,
			const i64 &len) const
	{
		aos_assert_r(mBuff, 0);
		aos_assert_r(len > 0, 0);
		aos_assert_r(idx >= 0, 0);
		aos_assert_r(idx + len < mDataLen, 0);
		
		try
		{
			AosBuffPtr buff = OmnNew AosBuff(len AosMemoryCheckerArgs);
			memcpy(buff->mBuff, &mBuff[idx], len);
			buff->setDataLen(len);
			return buff;
		}

		catch (...)
		{
			OmnAlarm << "Failed craeting obj!" << enderr;
			return 0;
		}
	}

	AosBuffPtr	clone(AosMemoryCheckDeclBegin) const
	{
		try
		{
			AosBuffPtr buff = OmnNew AosBuff(mBuffLen AosMemoryCheckerFileLine);
			buff->mDataLen = mDataLen;
			memcpy(buff->mBuff, mBuff, mDataLen);
			buff->mCrtIdx = 0;
			buff->mDeleteFlag = true;
			return buff;
		}

		catch (...)
		{
			OmnAlarm << "Failed cloning buff: " << mBuffLen << enderr;
			return 0;
		}
	}

	bool clone(AosBuff &buff AosMemoryCheckDecl)
	{
		if (buff.mBuffLen < mDataLen)
		{
			bool rslt = buff.expandMemory1(getNewSize(mDataLen));
			aos_assert_r(rslt, false);
		}
		buff.mDataLen = mDataLen;
		memcpy(buff.mBuff, mBuff, mDataLen);
		buff.mCrtIdx = 0;
		return true;
	}

	bool		reset() {mCrtIdx = 0; return true;}
	i64			dataLen() const {return mDataLen;}
	i64			buffLen() const {return mBuffLen;}
	// ice, 2014/06/24
	//void		setDataLen(const i64 len) {mDataLen = len;}
	// void		setDataLen(const i64 len) {mDataLen = len; if(mDataLen < mBuffLen){mBuff[mDataLen] = 0;}}
	void		setDataLen(const i64 len);
	char *		data() {return mBuff;}
	i64			getCrtIdx() const {return mCrtIdx;}
	char *		getCrtPos() const {return &mBuff[mCrtIdx];}
	void		gotoEnd() {mCrtIdx = mDataLen;}		// Chen Ding, 2014/08/10
	bool 		setCrtIdx(const i64 &value);  //Linda
	bool		resetMemory(const i64 &len);

	bool		setChar(const char c);
	bool		setBool(const bool c){return setChar(c);}
	bool		setI16(const i16);
	bool		setInt(const int);
	bool		setI64(const i64 &i);
	bool		setI64s(const i64 * values, const i64 &size);	// Ken Lee, 2013/04/18
	bool 		setU8(const u8);
	bool		setU16(const u16);
	bool		setU32(const u32);
	bool		setU64(const u64 &);
	bool		setU64s(const u64 * values, const i64 &size);	// Ken Lee, 2013/04/18
	bool		setFloat(const float&);
	bool		setDouble(const double &);
	bool		setCharStr(const char *, const int len, const bool add_null = false);
	bool		setOmnStr(const OmnString &);
	bool		setBuff(const char* content, const i64 &len);
	bool		setBuff(const AosBuffPtr &buff);
	bool		addBuff(const char* content, const i64 &len);
	bool		addBuff(const AosBuffPtr &buff);

	// Chen Ding, 01/01/2013
	bool 		addVarStr(const OmnString &value);
	bool 		addVarUint(const u64 &value);
	bool 		addNameValuePair(
					const OmnString &name, 
					const OmnString &value, 
					const char field_sep,
					const char attr_sep);
	bool 		addNameValuePair(
					const OmnString &name, 
					const u64 &value, 
					const char field_sep,
					const char attr_sep);

	char 		getChar(const char dft);
	bool		getBool(const bool dft){return (bool)getChar(dft);}
	i16			getI16(const i16 dft);
	int 		getInt(const int dft);
	int 		getInt(const i64 &offset, const int dft) const;
	i64 		getI64(const i64 &dft);   
	bool		getI64s(i64 * values, const i64 &size);		// Ken Lee, 2013/04/18
	u8 			getU8(const u8 dft);
	u16 		getU16(const u16 dft);
	u32 		getU32(const u32 dft);
	u32 		getU32(const i64 &offset, const u32 dft) const;
	u64 		getU64(const u64 &dft);
	u64 		getU64(const i64 &offset, const u64 &dft) const;
	bool		getU64s(u64 * values, const i64 &size);		// Ken Lee, 2013/04/18
	float		getFloat(const float &dft);
	double		getDouble(const double &dft);
	char *		getCharStr();
	char *		getCharStr(int &len);
	char *		getCharStr(const i64 &offset, int &len);
	bool 		getOmnStr(OmnString &value);
	OmnString	getOmnStr(const OmnString &dft);
	bool		getBuff(char* content, const i64 &len);   
	AosBuffPtr	getBuff(const i64 &len, const bool copy AosMemoryCheckDecl);	// Chen Ding, 2013/02/08

	void		incIndex(const u64 &i) {mCrtIdx += i;}

	u64 		getVarUint(const u64 &dft);

	inline i64	remainingMemSize() {return mBuffLen - mDataLen;}
	inline i64	remainingReadSize() {return mDataLen - mCrtIdx;}

	void		backInt() {mCrtIdx -= sizeof(int);}
	void		backI64() {mCrtIdx -= sizeof(i64);}
	void		backU32() {mCrtIdx -= sizeof(u32);}
	void		backU64() {mCrtIdx -= sizeof(u64);}

	static inline int getDataSize(const AosDataType::E type)
	{
		switch (type)
		{
		case AosDataType::eU64: 	return getU64Size();
		case AosDataType::eU32: 	return getU32Size();
		case AosDataType::eU16: 	return getU16Size();
		case AosDataType::eU8:		return getU8Size();
		case AosDataType::eChar:	return getCharSize();
		case AosDataType::eInt64:	return getInt64Size();
		case AosDataType::eInt32:	return getInt32Size();
		case AosDataType::eInt16:	return getInt16Size();
		case AosDataType::eBool:	return getCharSize();
		case AosDataType::eFloat:	return getFloatSize();
		case AosDataType::eDouble:	return getDoubleSize();
		default: 		break;
		}
		return -1;
	}

	static inline int getU64Size() {return sizeof(u64);}
	static inline int getU32Size() {return sizeof(u32);}
	static inline int getU16Size() {return sizeof(u16);}
	static inline int getU8Size() {return sizeof(u8);}
	static inline int getInt64Size() {return sizeof(i64);}
	static inline int getInt32Size() {return sizeof(int);}
	static inline int getIntSize() {return sizeof(int);}
	static inline int getInt16Size() {return sizeof(i16);}
	static inline int getStrSize(const int length) {return sizeof(int) + length;}
	static inline int getCharSize() {return 1;}
	static inline int getFloatSize() {return sizeof(float);}
	static inline int getDoubleSize() {return sizeof(double);}
	
	bool		appendBuff(const AosBuffPtr &buff);
	bool		appendU64(const u64 &);
	u64			removeU64();
	bool		appendInt(const int &);
	int			removeInt();
	bool		removeData(const i64 &len);

public:
	bool	expandMemory1(const i64 &nsize);
	inline i64 getNewSize(const i64 &desired_size)
	{
		aos_assert_r(desired_size > 0, 0);
		aos_assert_r(mBuffLen > 0, 0);
		i64 new_size = mBuffLen;
		while (new_size < desired_size && new_size < smMaxBuffLen)
		{
			if (new_size >= eDftIncSize) 
			{
				new_size += eDftIncSize;
			}
			else
			{
				new_size *= 2;
			}
		}
		aos_assert_r(new_size < smMaxBuffLen, 0);
		return new_size;
	}

	// Chen Ding, 2013/02/08
	bool		appendBuffAsBinary(const AosBuffPtr &buff){return setAosBuff(buff);}
	AosBuffPtr	getBuffAsBinary(const bool copy AosMemoryCheckDecl){return getAosBuff(copy AosMemoryCheckerArgs);}
	bool		setAosBuff(const AosBuffPtr &buff);
	AosBuffPtr	getAosBuff(const bool copy AosMemoryCheckDecl);

	// Chen Ding, 2013/04/01
	bool skipBuff(i64 &position, i64 &len);

	// Chen Ding, 2013/04/04
	bool removeBuff();

	// Chen Ding, 2013/05/13
	virtual i64 getMemorySize() const {return mMemoryUsed;}
	static i64 getNumInstances();
	static i64 getTotalInstances();

	// Chen Ding, 2013/06/11
	i64 resize(const i64 &new_size);
	bool hasMore() const {return mCrtIdx < mDataLen;}

	// Chen Ding, 2014/08/21
	inline bool ensureSpace(const int len) 
	{
		if (mDataLen + len < mBuffLen) return true;
		return expandMemory1(mDataLen + mDataLen);
	}

	// Chen Ding, 2013/12/13
	bool replaceMemory(const char *data, const i64 &len);

	// Chen Ding, 2014/01/01
	void setData(const char *data, const i64 &len, const bool delete_flag)
	{
		if (mDeleteFlag)
		{
			OmnDelete [] mBuff;
			mBuff = 0;
			if (mCB) mCB(1, mBuffLen);
		}
		mBuff = (char *)data;
		mBuffLen = len;
		mDataLen = len;
		mDeleteFlag = delete_flag;
	}

	inline void append(const char c)
	{
		if (mDataLen + 1 >= mBuffLen) 
		{
			expandMemory1(mDataLen + mDataLen);
		}
		mBuff[mDataLen++] = c;
	}

	inline void append(const char c1, const char c2)
	{
		if (mDataLen + 2 >= mBuffLen) 
		{
			expandMemory1(mDataLen + mDataLen);
		}
		mBuff[mDataLen++] = c1;
		mBuff[mDataLen++] = c2;
	}

	inline void append(const char c1, const char c2, const char c3, const char c4)
	{
		if (mDataLen + 4 >= mBuffLen) 
		{
			expandMemory1(mDataLen + mDataLen);
		}
		mBuff[mDataLen++] = c1;
		mBuff[mDataLen++] = c2;
		mBuff[mDataLen++] = c3;
		mBuff[mDataLen++] = c4;
	}

};
#endif




