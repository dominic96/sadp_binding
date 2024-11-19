#if !defined(AFX_RESETPASSWORD_H__14F1EC3F_5AD5_460D_A8BC_E1CA677EDDDE__INCLUDED_)
#define AFX_RESETPASSWORD_H__14F1EC3F_5AD5_460D_A8BC_E1CA677EDDDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResetPassword.h : header file
//
#include "Sadp.h"
/////////////////////////////////////////////////////////////////////////////
// CResetPassword dialog

class CResetPassword : public CDialog
{
// Construction
public:
	CResetPassword(CWnd* pParent = NULL);   // standard constructor
	CString m_strDevID;
	void GetPath() ;
    CString m_strdir;
	CString m_strEncryptFile;
    CString m_strGUIDFile;
	char m_szEncrytCode[256];
    BOOL m_bSycnIPCPW;
    SADP_RESET_PARAM m_struResetParam;
    BOOL m_bResetPWModeSecond;
    SADP_SAFE_CODE_V31 m_struSafeCode;
    SADP_ENCRYPT_STRING_V31 m_struEncryptString;
    BOOL m_bResetPW;
    CString m_csInputPassword;
    BOOL m_bSupportGUID;
    BOOL m_bSupportSecurityQuestion;
    CComboBox m_cmbResetPasswordType;
    BOOL m_bSycnIPCPW2;
    BOOL m_bMailBoxResetPW;

    
// Dialog Data
	//{{AFX_DATA(CResetPassword)
	enum { IDD = IDD_RESET_PASSWORD };
	CString	m_Edit_Input_Str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResetPassword)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResetPassword)
	afx_msg void OnBtnResetPassword();
	afx_msg void OnBtnRestorePassword();
	afx_msg void OnBtnExportFile();
	afx_msg void OnBtnImportFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnSyncIpcPw();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	FILE *m_pFile;
public:
    afx_msg void OnBnClickedBtnExportGuid();
    afx_msg void OnBnClickedBtnSecurityQuestion();
    afx_msg void OnBnClickedBtnImportGuid();
    afx_msg void OnBnClickedBtnGuidResetPassword();
    afx_msg void OnBnClickedBtnMailBoxResetPw();
    afx_msg void OnBnClickedBtnResetPassword2();
    afx_msg void OnBnClickedBtnGetResetType();
    BOOL m_cbGUID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESETPASSWORD_H__14F1EC3F_5AD5_460D_A8BC_E1CA677EDDDE__INCLUDED_)
