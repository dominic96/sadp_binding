#pragma once
#include "Sadp.h"

// CDlgResetPWPhone 对话框

class CDlgResetPWPhone : public CDialog
{
	DECLARE_DYNAMIC(CDlgResetPWPhone)

public:
	CDlgResetPWPhone(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgResetPWPhone();

// 对话框数据
	enum { IDD = IDD_DLG_RESET_PHONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
    void GetPath();
    CString m_strDevID;//设备序列号
    CString m_strdir;
    FILE *m_pFile;
    afx_msg void OnBnClickedButtonExport();
    afx_msg void OnBnClickedButtonReset2();
    CString m_szCode;
    CString m_szPassword;
};
