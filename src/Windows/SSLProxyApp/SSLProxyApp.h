////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// File Name: SSLProxyApp.h
// Description:
//   
//
// Modification History:
// 
////////////////////////////////////////////////////////////////////////////
// SSLProxyApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CSSLProxyAppApp:
// �йش����ʵ�֣������ SSLProxyApp.cpp
//

class CSSLProxyAppApp : public CWinApp
{
public:
	CSSLProxyAppApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSSLProxyAppApp theApp;
