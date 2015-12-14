////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// File Name: ServiceControl.h
// Description:
//   
//
// Modification History:
// 
////////////////////////////////////////////////////////////////////////////
#pragma once


// CServiceControl �Ի���

class CServiceControl : public CDialog
{
	DECLARE_DYNAMIC(CServiceControl)

public:
	CServiceControl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServiceControl();

// �Ի�������
	enum { IDD = IDD_DIALOG_SERVICE_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strServiceName;
	BOOL m_bStart;
};
