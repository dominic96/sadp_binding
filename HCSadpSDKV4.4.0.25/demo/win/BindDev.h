#pragma once
#include "Sadp.h"

// CBindDev 对话框

class CBindDev : public CDialog
{
	DECLARE_DYNAMIC(CBindDev)

public:
	CBindDev(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBindDev();

// 对话框数据
	enum { IDD = IDD_DLG_BIND_DEV_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGetBindList();
    afx_msg void OnBnClickedBtnSetBindList();
    CString m_strDevID;
    BOOL m_bUnBindAll;
    BOOL m_bSupportBind;
    CString m_strSerial[15];
    BOOL m_bBind[15];
    CString m_csPassword;
    afx_msg void OnBnClickedBtnCancle();
};
