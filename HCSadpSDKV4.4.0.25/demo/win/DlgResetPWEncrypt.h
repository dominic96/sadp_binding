#pragma once
#include "Sadp.h"
#include "afxwin.h"


// CDlgResetPWEncrypt 对话框

class CDlgResetPWEncrypt : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgResetPWEncrypt)

public:
	CDlgResetPWEncrypt(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgResetPWEncrypt();

// 对话框数据
	enum { IDD = IDD_DLG_REST_PW_ENCRYPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bResetPWModeSecond;
	SADP_ENCRYPT_STRING_V31 m_struEncryptString;
	afx_msg void OnBnClickedButtonExport();
	void GetPath();
	CString m_strdir;
	CString m_strDevID;//设备序列号
	FILE *m_pFile;
	afx_msg void OnBnClickedButtonImport();
	CString m_strEncryptFile;
	afx_msg void OnBnClickedButtonReset2();
	CString m_password;
	CString m_Edit_Input_Str;
	BOOL m_sync;
};
