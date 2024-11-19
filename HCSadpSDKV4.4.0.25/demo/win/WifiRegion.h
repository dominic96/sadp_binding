#pragma once
#include "Sadp.h"
#include "afxwin.h"

// CWifiRegion 对话框

class CWifiRegion : public CDialog
{
	DECLARE_DYNAMIC(CWifiRegion)

public:
	CWifiRegion(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWifiRegion();

// 对话框数据
	enum { IDD = IDD_WIFI_GEGION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CComboBox m_cbRegion;
    BOOL m_bsupportEnhancement;
    BOOL m_bEnhancement;
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    CString m_strDevID;//设备序列号
    CString m_strPassword;
    BYTE    m_bySupportRegion;
    BYTE   m_byCurrentRegion;
    virtual BOOL OnInitDialog();
    CString m_szPassword;
};
