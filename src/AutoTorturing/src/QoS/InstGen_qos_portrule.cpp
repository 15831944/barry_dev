////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// Description:
// This file is automatically generated by the TorturerGen facility.
//
// Modification History:
// 7/18/2007 : Created by TorturerGen Facility
//////////////////////////////////////////////////////////////////////////
#include "AutoTorturing/src/QoS/InstGen_qos_portrule.h"

#include "CliTorturer/CliTorturer.h"
#include "Tester/TestMgr.h"
#include "Torturer/Parm.h"
#include "Torturer/ParmIncls.h"
#include "Torturer/ParmInstGen.h"
#include "Torturer/ParmInt.h"
#include "Torturer/ParmStr.h"
#include "Util/DynArray.h"
#include "Util/String.h"
#include "Util/RCObject.h"
#include "Util/RCObjImp.h"
#include "XmlParser/XmlItem.h"



qos_portrule_InstGen::qos_portrule_InstGen(const OmnString &name)
:
AosParmInstGen(name)
{
}

qos_portrule_InstGen::~qos_portrule_InstGen()
{
}


bool
qos_portrule_InstGen::nextStr(OmnString &value,
                 		const AosGenTablePtr &data,
				        const AosGenRecordPtr &record,
						bool &isCorrect,
						const bool correctOnly,
						const bool selectFromRecord,
						AosParmReturnCode &rcode,
						OmnString &errmsg)
{
	if (!mInstGen)
	{
		OmnAlarm << "mInstGen is null" << enderr;
		return false;
	}

     qos_portrule* inst = OmnNew qos_portrule;
    if (mInstance) OmnDelete mInstance; 
    mInstance = inst;
    qos_portrule_InstGenPtr ptr = (qos_portrule_InstGen *) mInstGen.getPtr();

	return ptr->nextPtr(inst, data, record, isCorrect, correctOnly, 
			selectFromRecord, rcode, errmsg);
}


bool
qos_portrule_InstGen::nextPtr(
				  qos_portrule* inst,
				 const AosGenTablePtr &data,
				 const AosGenRecordPtr &record,
				 bool &isCorrect,
				 const bool correctOnly,
				 const bool selectFromRecord,
				 AosParmReturnCode &rcode,
				 OmnString &errmsg)
{
	    bool __correct;
	isCorrect = true;

	
    int mMember0;
    if (!mParmGens[0]->nextInt(mMember0, data, record, __correct, correctOnly, selectFromRecord, rcode, errmsg))
    {
        OmnAlarm << "Failed to generate member: "
            << mParmGens[0]->getName() << enderr;
        isCorrect = false;
        return 0;
    }
    isCorrect = isCorrect && __correct;

    OmnString mMember1;
    if (!mParmGens[1]->nextStr(mMember1, data, record, __correct, correctOnly, selectFromRecord, rcode, errmsg))
    {
        OmnAlarm << "Failed to generate member: "
            << mParmGens[1]->getName() << enderr;
        isCorrect = false;
        return 0;
    }
    isCorrect = isCorrect && __correct;

    int mMember2;
    if (!mParmGens[2]->nextInt(mMember2, data, record, __correct, correctOnly, selectFromRecord, rcode, errmsg))
    {
        OmnAlarm << "Failed to generate member: "
            << mParmGens[2]->getName() << enderr;
        isCorrect = false;
        return 0;
    }
    isCorrect = isCorrect && __correct;

    OmnString mMember3;
    if (!mParmGens[3]->nextStr(mMember3, data, record, __correct, correctOnly, selectFromRecord, rcode, errmsg))
    {
        OmnAlarm << "Failed to generate member: "
            << mParmGens[3]->getName() << enderr;
        isCorrect = false;
        return 0;
    }
    isCorrect = isCorrect && __correct;


	inst->port = mMember0;
		strncpy(inst->app, mMember1.data(), 12);
		inst->priority = mMember2;
		strncpy(inst->dev_name, mMember3.data(), 31);
	return true;
}


bool
qos_portrule_InstGen::nextInst(qos_portrule_InstGen &inst,
				  const AosGenTablePtr &data,
				 const AosGenRecordPtr &record,
				 bool &isCorrect,
				 const bool correctOnly,
				 const bool selectFromRecord,
				 AosParmReturnCode &rcode,
				 OmnString &errmsg)
{
	    if (!mParmGens[0]->nextInt(mMember0, data, record, isCorrect, correctOnly, selectFromRecord, 
            rcode, errmsg)) 
    {
        OmnAlarm << "Failed to generate member: "
            << mParmGens[0]->getName() << enderr;
        return 0;
    }
    if (!mParmGens[1]->nextStr(mMember1, data, record, isCorrect, correctOnly, selectFromRecord, 
            rcode, errmsg)) 
    {
        OmnAlarm << "Failed to generate member: "
            << mParmGens[1]->getName() << enderr;
        return 0;
    }
    if (!mParmGens[2]->nextInt(mMember2, data, record, isCorrect, correctOnly, selectFromRecord, 
            rcode, errmsg)) 
    {
        OmnAlarm << "Failed to generate member: "
            << mParmGens[2]->getName() << enderr;
        return 0;
    }
    if (!mParmGens[3]->nextStr(mMember3, data, record, isCorrect, correctOnly, selectFromRecord, 
            rcode, errmsg)) 
    {
        OmnAlarm << "Failed to generate member: "
            << mParmGens[3]->getName() << enderr;
        return 0;
    }


	return true;
}


AosParmPtr
qos_portrule_InstGen::createInstance(const OmnXmlItemPtr &def, OmnVList<AosGenTablePtr> &tables)
{
    qos_portrule_InstGenPtr inst = OmnNew qos_portrule_InstGen(getName());
	if (!inst->config(def, "", tables, false))
	{
		OmnAlarm << "Failed to config the object" << enderr;
		return 0;
	}
	
	return inst;         
}


bool
qos_portrule_InstGen::registerInstanceGen(const OmnString &name)
{
	qos_portrule_InstGenPtr inst = OmnNew qos_portrule_InstGen(name);
	if (!AosParmInstGen::registerInstanceGen(inst))
	{
		OmnAlarm << "Failed to register Instance Generator: " 
			<< "qos_portrule_InstGen" << enderr;
		return false;
	}

	return true;
}


bool
qos_portrule_InstGen::getCrtValue(AosParmInstGenPtr &value) const
{
	value = mLastInstGen;
	return true;
}


bool 	
qos_portrule_InstGen::getCrtValueAsArg(OmnString &value) const
{
	value = "inst";
	return true;
}


AosParmInstGenPtr 
qos_portrule_InstGen::clone() const
{
	qos_portrule_InstGenPtr ptr = OmnNew qos_portrule_InstGen;	
	copyData(ptr.getPtr());
	return ptr.getPtr();
}

