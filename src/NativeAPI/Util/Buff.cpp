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
#include "Util/Buff.h"

#include "alarm_c/alarm.h"
#include "Alarm/Alarm.h"
#include "Debug/Debug.h"
#include "Thread/Mutex.h"
#include "Util/OmnNew.h"
#include "Util/Ptrs.h"
#include "UtilComm/ConnBuff.h"

i64 AosBuff::smMaxBuffLen = AosBuff::eDftMaxBuffLen;
static volatile i64 sgAosCountObjInstCount = 0; 
static volatile i64 sgAosCountObjTotalCount = 0;


AosBuff::AosBuff(
		char *buff, 
		const i64 &bufflen,
		const i64 &datalen)
:
mCB(0),
mBuff(buff),
mBuffLen(bufflen),
mCrtIdx(0),
mDataLen(datalen),
mDeleteFlag(false),
mMemoryUsed(0)
{
	if(!mBuffLen)mBuffLen = eDftBuffLen;
	sgAosCountObjInstCount++;
	sgAosCountObjTotalCount++;
	AosMemoryCheckerObjCreated(AosClassName::eAosBuff);
}


AosBuff::AosBuff(const OmnConnBuffPtr &connbuff)
:
mCB(0),
mCrtIdx(0),
mDeleteFlag(false),
mMemoryUsed(0)
{
	sgAosCountObjInstCount++;
	sgAosCountObjTotalCount++;
	AosMemoryCheckerObjCreated(AosClassName::eAosBuff);

	aos_assert(connbuff);
	mBuff = connbuff->getData();
	mBuffLen = connbuff->getDataLength();
	if(!mBuffLen)mBuffLen = eDftBuffLen;
	mDataLen = connbuff->getDataLength();
	mConnBuff = connbuff;
}


AosBuff::AosBuff()
:
mCB(0),
mBuffLen(eDftBuffLen),
mCrtIdx(0),
mDataLen(0),
mDeleteFlag(true),
mMemoryUsed(0)
{
	sgAosCountObjInstCount++;
	sgAosCountObjTotalCount++;
	AosMemoryCheckerObjCreated(AosClassName::eAosBuff);

	mBuff = OmnNew char[mBuffLen+10];
	mMemoryUsed = mBuffLen;
}


AosBuff::AosBuff(const i64 &bufflen)
:
mCB(0),
mBuffLen(bufflen),
mCrtIdx(0),
mDataLen(0),
mDeleteFlag(true),
mMemoryUsed(0)
{
	if(!mBuffLen)mBuffLen = eDftBuffLen;
	sgAosCountObjInstCount++;
	sgAosCountObjTotalCount++;
	AosMemoryCheckerObjCreated(AosClassName::eAosBuff);

	mBuff = OmnNew char[bufflen+10];
	mMemoryUsed = mBuffLen;
}


AosBuff::AosBuff(const i64 &bufflen, void (*cb)(i64, i64))
:
mCB(cb),
mBuffLen(bufflen),
mCrtIdx(0),
mDataLen(0),
mDeleteFlag(true),
mMemoryUsed(0)
{
	if(!mBuffLen)mBuffLen = eDftBuffLen;
	sgAosCountObjInstCount++;
	sgAosCountObjTotalCount++;
	AosMemoryCheckerObjCreated(AosClassName::eAosBuff);

	//	OmnScreen << "Buff : " << this << "  created: " << bufflen << endl;
	if (mCB) mCB(0, bufflen);
	mBuff = OmnNew char[bufflen+10];
	mMemoryUsed = mBuffLen;
}


AosBuff::~AosBuff()
{
	sgAosCountObjInstCount--;
	AosMemoryCheckerObjDeleted(AosClassName::eAosBuff);

	if (mDeleteFlag)
	{
		OmnDelete [] mBuff;
		mBuff = 0;
		if (mCB) mCB(1, mBuffLen);
	}
}


bool
AosBuff::setU8(const u8 value)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen >= 0, false);
	i64 newsize = mCrtIdx + 1;
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	mBuff[mCrtIdx++] = value;
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setChar(const char value)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + 1;
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	mBuff[mCrtIdx++] = value;
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setInt(const int value)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + sizeof(int);
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	*(int*)&mBuff[mCrtIdx] = value;
	mCrtIdx += sizeof(int);
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setI16(const i16 value)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + sizeof(i16);
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	*(i16*)&mBuff[mCrtIdx] = value;
	mCrtIdx += sizeof(i16);
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setU32(const u32 value)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + sizeof(u32);
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	*(u32*)&mBuff[mCrtIdx] = value;
	mCrtIdx += sizeof(u32);
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}

bool
AosBuff::setU16(const u16 value)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + sizeof(u16);
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	*(u16*)&mBuff[mCrtIdx] = value;
	mCrtIdx += sizeof(u16);
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setU64(const u64 &value)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + sizeof(u64);
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	*(u64*)&mBuff[mCrtIdx] = value;
	mCrtIdx += sizeof(u64);
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


// Ken Lee, 2013/04/18
bool
AosBuff::setU64s(const u64 * values, const i64 &size)
{
	if (size <= 0) return true;
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + size * sizeof(u64);
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	memcpy(&mBuff[mCrtIdx], values, sizeof(u64) * size);
	mCrtIdx += size * sizeof(u64);
	mDataLen = mCrtIdx > mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setFloat(const float &value)                             
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + sizeof(float);
	if (newsize > mBuffLen)
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	*(float*)&mBuff[mCrtIdx] = value;
	mCrtIdx += sizeof(float);
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setDouble(const double &value)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + sizeof(double);
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	*(double*)&mBuff[mCrtIdx] = value;
	mCrtIdx += sizeof(double);
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setI64(const i64 &value)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + sizeof(i64);
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	*(i64*)&mBuff[mCrtIdx] = value;
	mCrtIdx += sizeof(i64);
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


// Ken Lee, 2013/04/18
bool
AosBuff::setI64s(const i64 * values, const i64 &size)
{
	if (size <= 0) return true;
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + size * sizeof(i64);
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	memcpy(&mBuff[mCrtIdx], values, sizeof(i64) * size);
	mCrtIdx += size * sizeof(i64);
	mDataLen = mCrtIdx > mDataLen ? mCrtIdx : mDataLen;
	return true;
}


// Chen Ding, 05/13/2012
// When setting char string, it needs to add one more byte for the 
// null character. 
bool
AosBuff::setCharStr(const char *value, const int len, const bool add_null)
{
	aos_assert_r(value, false);
	// Chen Ding, 12/13/2012
	// int len = strlen(value);
	aos_assert_r(len >= 0, false);
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);

	// Chen Ding, 05/13/2012
	// i64 newsize = mCrtIdx + sizeof(int) + len;
	i64 newsize = mCrtIdx + sizeof(int) + len + 1;
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}

	// Chen Ding, 05/13/2012
	if (add_null)
	{
		setInt(len+1);
	}
	else
	{
		setInt(len);
	}

	if (len > 0) 
	{
		memcpy(&mBuff[mCrtIdx], value, len);
		mCrtIdx += len;
	}

	if (add_null) mBuff[mCrtIdx++] = 0;
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setOmnStr(const OmnString &value)
{
	int len = value.length();
	aos_assert_r(len >= 0, false);
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);

	i64 newsize = mCrtIdx + sizeof(int) + len;
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	setInt(len);
	if (len == 0) return true;

	memcpy(&mBuff[mCrtIdx], value.data(), len);
	mCrtIdx += len;
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::setCrtIdx(const i64 &idx)
{
	aos_assert_r(idx <= mBuffLen, false);
	mCrtIdx = idx;
	return true;
}


char
AosBuff::getChar(const char dft)
{
	if (mCrtIdx + 1 > mDataLen) return dft;
	char value = mBuff[mCrtIdx++];
	return value;
}


int
AosBuff::getInt(const int dft)
{
	if (mCrtIdx + (i64)sizeof(int) > mDataLen) return dft;
	int value = *(int *)&mBuff[mCrtIdx];
	mCrtIdx += sizeof(int);
	return value;
}


int
AosBuff::getInt(const i64 &offset, const int dft) const
{
	if (offset + (i64)sizeof(int) > mDataLen) return dft;
	int value = *(int *)&mBuff[offset];
    return value;
}


i16
AosBuff::getI16(const i16 dft)
{
	aos_assert_r(mCrtIdx >= 0 && mDataLen >= 0, false);
	if (mCrtIdx + (i64)sizeof(i16) > mDataLen) return dft;
	i16 value = *(i16 *)&mBuff[mCrtIdx];
	mCrtIdx += sizeof(i16);
	return value;
}


u8
AosBuff::getU8(const u8 dft)
{
	if (mCrtIdx + (i64)sizeof(u8) > mDataLen) return dft;
	u8 value = *(u8 *)&mBuff[mCrtIdx];
	mCrtIdx += sizeof(u8);
	return value;
}

u16
AosBuff::getU16(const u16 dft)
{
	if (mCrtIdx + (i64)sizeof(u16) > mDataLen) return dft;
	u16 value = *(u16 *)&mBuff[mCrtIdx];
	mCrtIdx += sizeof(u16);
	return value;
}

u32
AosBuff::getU32(const u32 dft)
{
	if (mCrtIdx + (i64)sizeof(u32) > mDataLen) return dft;
	u32 value = *(u32 *)&mBuff[mCrtIdx];
	mCrtIdx += sizeof(u32);
	return value;
}


u64
AosBuff::getU64(const i64 &offset, const u64 &dft) const
{
    if (offset + (i64)sizeof(u64) > mDataLen) return dft;
    u64 value = *(u64 *)&mBuff[offset];
    return value;
}


u32
AosBuff::getU32(const i64 &offset, const u32 dft) const
{
    if (offset + (i64)sizeof(u32) > mDataLen) return dft;
    u32 value = *(u32 *)&mBuff[offset];
    return value;
}


char *
AosBuff::getCharStr(int &len)
{
	len = -1;
	if (mCrtIdx + (i64)sizeof(u32) > mDataLen) 
	{
		OmnAlarm << "Error: " << mCrtIdx << ":" << mDataLen << enderr;
		len = -2;
		return 0;
	}
	len = getInt(-1);
	aos_assert_r(len >= 0, 0);
	if (len == 0) 
	{
		// OmnAlarm << "len = 0" << mCrtIdx << ":" << mDataLen << enderr;
		return 0;
	}
	aos_assert_r(mCrtIdx + len <= mDataLen, 0);
	int idx = mCrtIdx;
	mCrtIdx += len;
	return &mBuff[idx];
}


char *
AosBuff::getCharStr(const i64 &offset, int &len)
{
	len = -1;
	if (offset + (i64)sizeof(int) > mDataLen) 
	{
		OmnAlarm << "Error: " << offset << ":" << mDataLen << enderr;
		return 0;
	}

	len = *(int *)&mBuff[offset];
	aos_assert_r(len >= 0, 0);

	int idx = offset + (i64)sizeof(int);
	aos_assert_r(idx + len <= mDataLen, 0);

	return &mBuff[idx];
}


u64
AosBuff::getU64(const u64 &dft)
{
	if (mCrtIdx + (i64)sizeof(u64) > mDataLen) return dft;
	u64 value = *(u64 *)&mBuff[mCrtIdx];
	mCrtIdx += sizeof(u64);
	return value;
}


// Ken Lee, 2013/04/18
bool
AosBuff::getU64s(u64 * values, const i64 &size)
{
	if (size <= 0) return true;
	aos_assert_r(mCrtIdx + size * (i64)sizeof(u64) <= mDataLen, false);
	memcpy(values, &mBuff[mCrtIdx], sizeof(u64) * size);
	mCrtIdx += size * sizeof(u64);
	return true;
}


double
AosBuff::getDouble(const double &dft)
{
	if (mCrtIdx + (i64)sizeof(double) > mDataLen) return dft;
	double value = *(double *)&mBuff[mCrtIdx];
	mCrtIdx += sizeof(double);
	return value;
}


i64
AosBuff::getI64(const i64 &dft)
{
	if (mCrtIdx + (i64)sizeof(i64) > mDataLen) return dft;
	i64 value = *(i64 *)&mBuff[mCrtIdx];
	mCrtIdx += sizeof(i64);
	return value;
}


// Ken Lee, 2013/04/18
bool
AosBuff::getI64s(i64 * values, const i64 &size)
{
	if (size <= 0) return true;
	aos_assert_r(mCrtIdx + size * (i64)sizeof(i64) <= mDataLen, false);
	memcpy(values, &mBuff[mCrtIdx], sizeof(i64) * size);
	mCrtIdx += size * sizeof(i64);
	return true;
}


// Chen Ding, 05/13/2012
// The char string has a null character. 
char *
AosBuff::getCharStr()
{
	int len = -1;
	if (mCrtIdx + (i64)sizeof(u32) > mDataLen) 
	{
		OmnAlarm << "Error: " << mCrtIdx << ":" << mDataLen << enderr;
		len = -2;
		return 0;
	}
	len = getInt(-1);
	aos_assert_r(len >= 0, 0);
	int idx = mCrtIdx;
	aos_assert_r(mCrtIdx + len + 1 <= mDataLen, 0);
	mCrtIdx += len+1;
	return &mBuff[idx];
}


OmnString
AosBuff::getOmnStr(const OmnString &dft)
{
	aos_assert_r(mCrtIdx + (i64)sizeof(u32) <= mDataLen, dft);
	int len = getInt(-1);
	aos_assert_r(len >= 0, dft);
	if (len == 0) return "";
	aos_assert_r(mCrtIdx + len <= mDataLen, dft);
	OmnString str(&mBuff[mCrtIdx], len);
	mCrtIdx += len;
	return str;
}


bool
AosBuff::getOmnStr(OmnString &value)
{
	aos_assert_r(mCrtIdx + (i64)sizeof(u32) <= mDataLen, false);
	int len = getInt(-1);
	aos_assert_r(len >= 0, false);
	if (len == 0) 
	{
		value = "";
		return true;
	}
	aos_assert_r(mCrtIdx + len <= mDataLen, false);
	value.assign(&mBuff[mCrtIdx], len);
	mCrtIdx += len;
	return true;
}


bool
AosBuff::expandMemory1(const i64 &newsize)
{
	aos_assert_r(newsize > 0, false);
	char *mem = OmnNew char[newsize + 10];
	aos_assert_r(mem, false);
	mem[newsize] = 0;

	if (mBuff) 
	{
		// Ice Yu, 2012/6/19
		//memcpy(mem, mBuff, mCrtIdx);
		memcpy(mem, mBuff, mDataLen);
		
		// Chen Ding, 01/02/2012
		if (mDeleteFlag) 
		{
			OmnDelete [] mBuff;
			aos_assert_r(mMemoryUsed >= mBuffLen, false);
			mMemoryUsed -= mBuffLen;
		}
		mDeleteFlag = true;
	}
	mBuff = mem;
	mBuffLen = newsize;
	mMemoryUsed += mBuffLen;
	return true;
}


bool
AosBuff::addBuff(const char* content, const i64 &len)
{
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mDataLen + (u32)len;
	if (newsize > mBuffLen) 	
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	memcpy(&mBuff[mDataLen],content,len);
	mDataLen += len;	
	return true;
}


bool
AosBuff::setBuff(const char* content, const i64 &len)
{
	// Chen Ding, 2013/05/26
	// If 'len' is 0, it does nothing.
	aos_assert_r(len >= 0, false);
	if (len == 0)
	{
		// It is allowed to have a buff of length 0. Do nothing.
		return true;
	}

	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + len;
	aos_assert_r(newsize > 0, false);
	if (newsize > mBuffLen) 	
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	memcpy(&mBuff[mCrtIdx],content,len);
	mCrtIdx += len;	
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::appendBuff(const AosBuffPtr &buff)
{
	// This function appends 'buff' as binary data to the buff. 
	// Note that it does not store the buff length.
	aos_assert_r(buff, false);
	aos_assert_r(mCrtIdx >= 0, false);
	i64 len = buff->dataLen();
	aos_assert_r(len >= 0, false);
	if (len == 0) return true;

	i64 newsize = mCrtIdx + len;
	aos_assert_r(newsize > 0, false);
	if (newsize > mBuffLen)
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	memcpy(&mBuff[mCrtIdx], buff->mBuff, len);
	mCrtIdx += len;
	mDataLen = mCrtIdx;
	return true;
}


bool
AosBuff::getBuff(char* content, const i64 &len)
{	
 	if (mCrtIdx + len > mDataLen) return false;	
 	memcpy(content,&mBuff[mCrtIdx],len);
 	mCrtIdx += len;
 	return true;
}


bool
AosBuff::addBuff(const AosBuffPtr &buff)
{
 	aos_assert_r(mDataLen >= 0 && mBuffLen > 0, false);
 	aos_assert_r(buff,false);
 				
 	return addBuff(buff->data(),buff->dataLen());
}


bool
AosBuff::setBuff(const AosBuffPtr &buff)
{
 	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
 	aos_assert_r(buff,false);
 				
 	return setBuff(buff->data(),buff->dataLen());
}


// Chen Ding, 03/18/2012
bool		
AosBuff::resetMemory(const i64 &len)
{
	// It releases the current memory and allocate a new memory.
	if (mDeleteFlag)
	{
		OmnDelete [] mBuff;
		aos_assert_r(mMemoryUsed >= mBuffLen, false);
		mMemoryUsed -= mBuffLen;
		mBuff = 0;
	}

	mBuff = OmnNew char[len];
	mBuffLen = len;
	mCrtIdx = 0;
	mDataLen = 0;
	mDeleteFlag = true;
	mMemoryUsed += mBuffLen;
	return true;
}


bool
AosBuff::addVarStr(const OmnString &value)
{
	// This is new format. Its length is variable unsigned int: 
	int len = value.length();
	aos_assert_r(len >= 0, false);
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);

	i64 newsize = mCrtIdx + 4 + len;
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}
	addVarUint((u64)len);
	if (len == 0) return true;

	memcpy(&mBuff[mCrtIdx], value.data(), len);
	mCrtIdx += len;
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::addVarUint(const u64 &value)
{
	// It is saved in big endian or the network order.
	aos_assert_r(mCrtIdx >= 0 && mBuffLen > 0, false);
	i64 newsize = mCrtIdx + 10;
	if (newsize > mBuffLen) 
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}

	int len = -1;
	if (value <= 127)
	{
		// 0xxxxxxx (7 bits)
		mBuff[mCrtIdx++] = value;
		len = 1;
	}
	else if (value <= 0x3fff)
	{
		// 10xxxxxx xxxxxxxx (14 bits)
		mBuff[mCrtIdx++] = (u8)(value >> 8) + 0x80;
		mBuff[mCrtIdx++] = (u8)value;
		len = 2;
	}
	else if (value < 0x1fffff)
	{
		// 110xxxxx xxxxxxxx xxxxxxxx (21 bits)
		mBuff[mCrtIdx++] = (u8)(value >> 16) + 0xc0;
		mBuff[mCrtIdx++] = (u8)(value >> 8);
		mBuff[mCrtIdx++] = (u8)value;
		len = 3;
	}
	else if (value < 0xfffffff)
	{
		// 1110xxxx xxxxxxxx xxxxxxxx xxxxxxxx (28 bits)
		mBuff[mCrtIdx++] = (u8)(value >> 24) + 0xe0;
		mBuff[mCrtIdx++] = (u8)(value >> 16);
		mBuff[mCrtIdx++] = (u8)(value >> 8);
		mBuff[mCrtIdx++] = (u8)value;
		len = 4;
	}
	else if (value < 0x7ffffffffULL)
	{
		// 11110xxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx (35 bits)
		mBuff[mCrtIdx++] = (u8)(value >> 32) + 0xf0;
		mBuff[mCrtIdx++] = (u8)(value >> 24);
		mBuff[mCrtIdx++] = (u8)(value >> 16);
		mBuff[mCrtIdx++] = (u8)(value >> 8);
		mBuff[mCrtIdx++] = (u8)value;
		len = 5;
	}
	else if (value < 0x3ffffffffffULL)
	{
		// 111110xx xxxxxxxx xxxxxxxx xxxxxxxx ... (42 bits)
		mBuff[mCrtIdx++] = (u8)(value >> 40) + 0xf8;
		mBuff[mCrtIdx++] = (u8)(value >> 32);
		mBuff[mCrtIdx++] = (u8)(value >> 24);
		mBuff[mCrtIdx++] = (u8)(value >> 16);
		mBuff[mCrtIdx++] = (u8)(value >> 8);
		mBuff[mCrtIdx++] = (u8)value;
		len = 6;
	}
	else if (value < 0x1ffffffffffffULL)
	{
		// 1111110x xxxxxxxx xxxxxxxx xxxxxxxx ... (49 bits)
		mBuff[mCrtIdx++] = (u8)(value >> 48) + 0xfc;
		mBuff[mCrtIdx++] = (u8)(value >> 40);
		mBuff[mCrtIdx++] = (u8)(value >> 32);
		mBuff[mCrtIdx++] = (u8)(value >> 24);
		mBuff[mCrtIdx++] = (u8)(value >> 16);
		mBuff[mCrtIdx++] = (u8)(value >> 8);
		mBuff[mCrtIdx++] = (u8)value;
		len = 7;
	}
	else if (value < 0xffffffffffffffULL)
	{
		// 11111110 xxxxxxxx xxxxxxxx xxxxxxxx ... (56 bits)
		mBuff[mCrtIdx++] = (u8)0xfe;
		mBuff[mCrtIdx++] = (u8)(value >> 48);
		mBuff[mCrtIdx++] = (u8)(value >> 40);
		mBuff[mCrtIdx++] = (u8)(value >> 32);
		mBuff[mCrtIdx++] = (u8)(value >> 24);
		mBuff[mCrtIdx++] = (u8)(value >> 16);
		mBuff[mCrtIdx++] = (u8)(value >> 8);
		mBuff[mCrtIdx++] = (u8)value;
		len = 8;
	}
	else if (value < 0x7fffffffffffffffULL)
	{
		// 11111111 0xxxxxxx xxxxxxxx xxxxxxxx ... (63 bits)
		mBuff[mCrtIdx++] = (u8)0xff;
		mBuff[mCrtIdx++] = (u8)(value >> 56);
		mBuff[mCrtIdx++] = (u8)(value >> 48);
		mBuff[mCrtIdx++] = (u8)(value >> 40);
		mBuff[mCrtIdx++] = (u8)(value >> 32);
		mBuff[mCrtIdx++] = (u8)(value >> 24);
		mBuff[mCrtIdx++] = (u8)(value >> 16);
		mBuff[mCrtIdx++] = (u8)(value >> 8);
		mBuff[mCrtIdx++] = (u8)value;
		len = 9;
	}
	else
	{
		// xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx 
		// 11111111 10xxxxxx xxxxxxxx xxxxxxxx ... (70 bits)
		mBuff[mCrtIdx++] = (u8)0xff;
		mBuff[mCrtIdx++] = (u8)(value >> 63) + 0x80;
		mBuff[mCrtIdx++] = (u8)(value >> 56);
		mBuff[mCrtIdx++] = (u8)(value >> 48);
		mBuff[mCrtIdx++] = (u8)(value >> 40);
		mBuff[mCrtIdx++] = (u8)(value >> 32);
		mBuff[mCrtIdx++] = (u8)(value >> 24);
		mBuff[mCrtIdx++] = (u8)(value >> 16);
		mBuff[mCrtIdx++] = (u8)(value >> 8);
		mBuff[mCrtIdx++] = (u8)value;
		len = 10;
	}

	mCrtIdx += len;
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


u64
AosBuff::getVarUint(const u64 &dft)
{
	if ((mBuff[mCrtIdx] & 0x80) == 0x00)
	{
		// 0xxxxxxx (7 bits)
		if (mCrtIdx + 1 > mDataLen) return dft;
		u64 value = (u64)mBuff[mCrtIdx];
		mCrtIdx++;
		return value;
	}

	if ((mBuff[mCrtIdx] & 0xc0) == 0x80)
	{
		// 10xxxxxx xxxxxxxx (14 bits)
		if (mCrtIdx + 2 > mDataLen) return dft;
		u64 value = (((u64)mBuff[mCrtIdx+0]) << 8) + 
					  (u64)mBuff[mCrtIdx+1];
		mCrtIdx += 2;
		return value;
	}

	if ((mBuff[mCrtIdx] & 0xe0) == 0xc0)
	{
		// 110xxxxx xxxxxxxx xxxxxxxx (21 bits)
		if (mCrtIdx + 3 > mDataLen) return dft;
		u64 value = (((u64)mBuff[mCrtIdx+0]) << 16) + 
					(((u64)mBuff[mCrtIdx+1]) << 8) + 
					  (u64)mBuff[mCrtIdx+2];
		mCrtIdx += 3;
		return value;
	}

	if ((mBuff[mCrtIdx] & 0xf0) == 0xe0)
	{
		// 1110xxxx xxxxxxxx xxxxxxxx xxxxxxxx (28 bits)
		if (mCrtIdx + 4 > mDataLen) return dft;
		u64 value = (((u64)mBuff[mCrtIdx+0]) << 24) + 
					(((u64)mBuff[mCrtIdx+1]) << 16) + 
					(((u64)mBuff[mCrtIdx+2]) << 8) + 
					  (u64)mBuff[mCrtIdx+3];
		mCrtIdx += 4;
		return value;
	}

	if ((mBuff[mCrtIdx] & 0xf8) == 0xf0)
	{
		// 11110xxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx (35 bits)
		if (mCrtIdx + 5 > mDataLen) return dft;
		u64 value = (((u64)mBuff[mCrtIdx+0]) << 32) + 
					(((u64)mBuff[mCrtIdx+1]) << 24) + 
					(((u64)mBuff[mCrtIdx+2]) << 16) + 
					(((u64)mBuff[mCrtIdx+3]) << 8) + 
					  (u64)mBuff[mCrtIdx+4];
		mCrtIdx += 5;
		return value;
	}
	
	if ((mBuff[mCrtIdx] & 0xfc) == 0xf8)
	{
		// 111110xx xxxxxxxx xxxxxxxx xxxxxxxx ... (42 bits)
		if (mCrtIdx + 6 > mDataLen) return dft;
		u64 value = (((u64)mBuff[mCrtIdx+0]) << 40) + 
					(((u64)mBuff[mCrtIdx+1]) << 32) + 
					(((u64)mBuff[mCrtIdx+2]) << 24) + 
					(((u64)mBuff[mCrtIdx+3]) << 16) + 
					(((u64)mBuff[mCrtIdx+4]) << 8) + 
					  (u64)mBuff[mCrtIdx+5];
		mCrtIdx += 6;
		return value;
	}

	if ((mBuff[mCrtIdx] & 0xfe) == 0xfc)
	{
		// 1111110x xxxxxxxx xxxxxxxx xxxxxxxx ... (49 bits)
		if (mCrtIdx + 7 > mDataLen) return dft;
		u64 value = (((u64)mBuff[mCrtIdx+0]) << 48) + 
					(((u64)mBuff[mCrtIdx+1]) << 40) + 
					(((u64)mBuff[mCrtIdx+2]) << 32) + 
					(((u64)mBuff[mCrtIdx+3]) << 24) + 
					(((u64)mBuff[mCrtIdx+4]) << 16) + 
					(((u64)mBuff[mCrtIdx+5]) << 8) + 
					  (u64)mBuff[mCrtIdx+6];
		mCrtIdx += 7;
		return value;
	}

	if ((mBuff[mCrtIdx] & 0xff) == 0xfe)
	{
		// 11111110 xxxxxxxx xxxxxxxx xxxxxxxx ... (56 bits)
		if (mCrtIdx + 8 > mDataLen) return dft;
		u64 value = (((u64)mBuff[mCrtIdx+0]) << 56) + 
					(((u64)mBuff[mCrtIdx+1]) << 48) + 
					(((u64)mBuff[mCrtIdx+2]) << 40) + 
					(((u64)mBuff[mCrtIdx+3]) << 32) + 
					(((u64)mBuff[mCrtIdx+4]) << 24) + 
					(((u64)mBuff[mCrtIdx+5]) << 16) + 
					(((u64)mBuff[mCrtIdx+6]) << 8) + 
					  (u64)mBuff[mCrtIdx+7];
		mCrtIdx += 8;
		return value;
	}

	if (mBuff[mCrtIdx] != 0xff) return dft;
	mCrtIdx++;

	if ((mBuff[mCrtIdx] & 0x80) == 0)
	{
		// 11111111 0xxxxxxx xxxxxxxx xxxxxxxx ... (63 bits)
		if (mCrtIdx + 8 > mDataLen) return dft;
		u64 value = (((u64)mBuff[mCrtIdx+0]) << 56) + 
					(((u64)mBuff[mCrtIdx+1]) << 48) + 
					(((u64)mBuff[mCrtIdx+2]) << 40) + 
					(((u64)mBuff[mCrtIdx+3]) << 32) + 
					(((u64)mBuff[mCrtIdx+4]) << 24) + 
					(((u64)mBuff[mCrtIdx+5]) << 16) + 
					(((u64)mBuff[mCrtIdx+6]) << 8) + 
					  (u64)mBuff[mCrtIdx+7];
		mCrtIdx += 8;
		return value;
	}

	if ((mBuff[mCrtIdx] & 0xc0) == 0x80)
	{
		// 11111111 10xxxxxxx xxxxxxxx xxxxxxxx ... (70 bits)
		if (mCrtIdx + 9 > mDataLen) return dft;
		u64 value = (((u64)(((u8)mBuff[mCrtIdx+0] << 7) + (u8)mBuff[mCrtIdx+1])) << 56) + 
					(((u64)mBuff[mCrtIdx+2]) << 48) + 
					(((u64)mBuff[mCrtIdx+3]) << 40) + 
					(((u64)mBuff[mCrtIdx+4]) << 32) + 
					(((u64)mBuff[mCrtIdx+5]) << 24) + 
					(((u64)mBuff[mCrtIdx+6]) << 16) + 
					(((u64)mBuff[mCrtIdx+7]) << 8) + 
					  (u64)mBuff[mCrtIdx+8];
		mCrtIdx += 9;
		return value;
	}

	return dft;
}


bool
AosBuff::addNameValuePair(
		const OmnString &name, 
		const OmnString &value, 
		const char field_sep,
		const char attr_sep)
{
	// This function appends the following:
	// 	<name-as-string> + attr_sep + <type> + 
	// 		value-as-string> + field_sep
	int len = name.length() + 25 + value.length();
	i64 newsize = mCrtIdx + len;
	if (newsize > mBuffLen)
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}

	// Add 'name'
	bool rslt = addVarStr(name);
	aos_assert_r(rslt, false);

	// Add 'attr_sep'
	mBuff[mCrtIdx++] = attr_sep;

	// Add 'type'
	mBuff[mCrtIdx++] = eFieldTypeStr;

	// Add 'value'
	rslt = addVarStr(value);
	aos_assert_r(rslt, false);

	// Add 'field_sep'
	mBuff[mCrtIdx++] = field_sep;
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


bool
AosBuff::addNameValuePair(
		const OmnString &name, 
		const u64 &value, 
		const char field_sep,
		const char attr_sep)
{
	// This function appends the following:
	// 	<name-as-string> + attr_sep + <type> + 
	// 		value-as-string> + field_sep
	int len = name.length() + 25;
	i64 newsize = mCrtIdx + len;
	if (newsize > mBuffLen)
	{
		bool rslt = expandMemory1(getNewSize(newsize));
		aos_assert_r(rslt, false);
	}

	// Add 'name'
	bool rslt = addVarStr(name);
	aos_assert_r(rslt, false);

	// Add 'attr_sep'
	mBuff[mCrtIdx++] = attr_sep;

	// Add 'type'
	mBuff[mCrtIdx++] = eFieldTypeVarUint;

	// Add 'value'
	rslt = addVarUint(value);
	aos_assert_r(rslt, false);

	// Add 'field_sep'
	mBuff[mCrtIdx++] = field_sep;
	mDataLen = mCrtIdx>mDataLen ? mCrtIdx : mDataLen;
	return true;
}


// Chen Ding, 2013/02/08
AosBuffPtr 
AosBuff::getBuff(const i64 &len, const bool copy AosMemoryCheckDecl)
{
	// This function converts the memory [mCrtIdx, mCrtIdx+len] into 
	// a new AosBuff. If 'copy' is true, it will copy the memory. 
	// Otherwise, it uses the memory.
	// Chen Ding, 2013/05/26
	// If 'len' is 0, it means there are no contents for the buff. 
	// When this happens, we still need to return a buff.
	aos_assert_r(len >= 0, 0);
	if (len == 0)
	{
		AosBuffPtr buff = OmnNew AosBuff(0 AosMemoryCheckerFileLine);
		buff->setDataLen(0);
		return buff;
	}

	// Ketty 2013/03/25
	//aos_assert_r(mCrtIdx + len < mDataLen, 0);
	aos_assert_r(mCrtIdx + len <= mDataLen, 0);

	AosBuffPtr buff;
	if (copy)
	{
		buff = OmnNew AosBuff(len AosMemoryCheckerFileLine);
		char *data = buff->data();
		memcpy(data, &mBuff[mCrtIdx], len);
		buff->setDataLen(len);
	}
	else
	{
		buff = OmnNew AosBuff(&mBuff[mCrtIdx], len, len AosMemoryCheckerFileLine);
	}
	mCrtIdx += len;
	return buff;
}


// Chen Ding, 2013/02/08
bool
AosBuff::setAosBuff(const AosBuffPtr &buff)
{
	// This function adds the following:
	// 		length		int
	// 		buff		binary
	setI64(buff->dataLen());
	if(!buff->dataLen())
	{
		return true;
	}
	appendBuff(buff);
	return true;
}

// Chen Ding, 2013/02/21
AosBuffPtr
AosBuff::getAosBuff(const bool copy AosMemoryCheckDecl)
{
	// This function assumes:
	// 		length		int	
	// 		buff		binary
	if (mCrtIdx + (i64)sizeof(i64) > mDataLen) return 0;
	i64 len = getI64(-1);
	aos_assert_r(len >= 0, 0);

	if (len == 0) return 0;
	return getBuff(len, copy AosMemoryCheckerFileLine);
}


bool
AosBuff::skipBuff(
		i64 &position, 
		i64 &len)
{
	position = -1;
	len = getI64(-1);
	aos_assert_r(len >= 0, false);
	if (len == 0) return true;
	position = mCrtIdx;
	mCrtIdx += len;
	return true;
}

bool 
AosBuff::removeBuff()
{
	OmnNotImplementedYet;
	return false;
}


i64
AosBuff::getNumInstances()
{
	return sgAosCountObjInstCount;
}


i64
AosBuff::getTotalInstances()
{
	return sgAosCountObjTotalCount;
}


i64
AosBuff::resize(const i64 &new_size)
{
	aos_assert_r(new_size > 0, -1);
	if (new_size <= mBuffLen) return mBuffLen;
	bool rslt = expandMemory1(getNewSize(new_size));
	aos_assert_r(rslt, mBuffLen);
	return mBuffLen;
}


bool
AosBuff::replaceMemory(
		const char *data, 
		const i64 &len)
{
	// This function releases the current memory as needed
	// and replaces the current memory with 'data'.
	if (mDeleteFlag)
	{
		OmnDelete [] mBuff;
	}
	mDeleteFlag = false;
	mBuff = (char *)data;
	mBuffLen = len;
	mDataLen = len;
	return true;
}


bool		
AosBuff::appendInt(const int &v)
{
	mCrtIdx = mDataLen;
	return setInt(v);
}


int			
AosBuff::removeInt()
{
	aos_assert_r(mDataLen >= (int)sizeof(int), 0);
	mCrtIdx = mDataLen - sizeof(int);
	int rt = getInt(0);
	mDataLen -= sizeof(int);
	mCrtIdx = 0;
	return rt;
}


bool		
AosBuff::appendU64(const u64 &v)
{
	mCrtIdx = mDataLen;
	return setU64(v);
}


u64			
AosBuff::removeU64()
{
	aos_assert_r(mDataLen >= (int)sizeof(u64), 0);
	mCrtIdx = mDataLen - sizeof(u64);
	u64 rt = getU64(0);
	mDataLen -= sizeof(u64);
	mCrtIdx = 0;
	return rt;
}


void		
AosBuff::setDataLen(const i64 len) 
{
	aos_assert(mDataLen <= mBuffLen);
	mDataLen = len; 
	if (mDataLen < mBuffLen)
	{
		mBuff[mDataLen] = 0;
	}
}


bool
AosBuff::removeData(const i64 &len)
{
	aos_assert_r(mDataLen >= len, false);
	mDataLen -= len;
	if (mCrtIdx > mDataLen) mCrtIdx = mDataLen;
	return true;
}

