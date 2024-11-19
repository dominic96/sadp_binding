#pragma once
#include "Sadp.h"

// CDlgSecurityQuestion 对话框
#define MAX_QUESTION_NUM 18 //老设备最大15个问题， 新设备：2个老问题 + 3个已设置的问题 + 13个新问题，理论上最多18个问

class CDlgSecurityQuestion : public CDialog
{
	DECLARE_DYNAMIC(CDlgSecurityQuestion)

public:
	CDlgSecurityQuestion(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSecurityQuestion();

// 对话框数据
	enum { IDD = IDD_DLG_SECURITY_QUESTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGetQuestion();
    afx_msg void OnBnClickedBtnSetQuestion();
    afx_msg void OnBnClickedAnswerResetPassword();
    CString m_strDevID;
    BOOL m_bSupportSecurityQuestion;
    DWORD m_dwID[MAX_QUESTION_NUM];
    CComboBox m_cmbMark[MAX_QUESTION_NUM];
    CString m_csAnswer[MAX_QUESTION_NUM];
    CString m_csPassword;
    afx_msg void OnBnClickedSyncIpcPw();
    BYTE m_bSyncIPCPW;
    BOOL m_bSupportSycnIPCPW;
};
