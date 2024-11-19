#pragma once
#include "afxwin.h"


// CDlgEzvizToken 对话框

class CDlgEzvizToken : public CDialog
{
	DECLARE_DYNAMIC(CDlgEzvizToken)

public:
	CDlgEzvizToken(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgEzvizToken();

// 对话框数据
	enum { IDD = IDD_DLG_EZVIZ_TOKEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CString m_strDevID;//设备序列号
    CEdit m_editToken;
    CButton m_btnSet;
    CEdit m_editPassword;
    afx_msg void OnBnClickedBtnEzvizToken();
    CString m_strToken;
    CString m_strPassword;
};
