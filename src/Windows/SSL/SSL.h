////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// File Name: SSL.h
// Description:
//   
//
// Modification History:
// 
////////////////////////////////////////////////////////////////////////////
// SSL.h : SSL DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CSSLApp
// �йش���ʵ�ֵ���Ϣ������� SSL.cpp
//

class CSSLApp : public CWinApp
{
public:
	CSSLApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
