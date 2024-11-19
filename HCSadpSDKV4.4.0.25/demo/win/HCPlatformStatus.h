#pragma once

#include "Sadp.h"
// HCPlatformStatus 对话框

class HCPlatformStatus : public CDialog
{
	DECLARE_DYNAMIC(HCPlatformStatus)

public:
	HCPlatformStatus(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HCPlatformStatus();

// 对话框数据
	enum { IDD = IDD_HCPLATFORMSTATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bHCPlatforStatus;
	CString m_strVerificationCode;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_strDevID;//设备序列号
	CString m_strPassword;
	afx_msg void OnBnClickedButton1();
};
