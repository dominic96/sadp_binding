#pragma once

#include "Sadp.h"
// HCPlatformStatus �Ի���

class HCPlatformStatus : public CDialog
{
	DECLARE_DYNAMIC(HCPlatformStatus)

public:
	HCPlatformStatus(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HCPlatformStatus();

// �Ի�������
	enum { IDD = IDD_HCPLATFORMSTATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bHCPlatforStatus;
	CString m_strVerificationCode;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_strDevID;//�豸���к�
	CString m_strPassword;
	afx_msg void OnBnClickedButton1();
};
