#pragma once
#include "Sadp.h"
#include "afxwin.h"


// CDlgResetPWGUID 对话框

class CDlgResetPWGUID : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgResetPWGUID)

public:
	CDlgResetPWGUID(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgResetPWGUID();

// 对话框数据
	enum { IDD = IDD_DLG_RESET_GUID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExport();
	// 密码
	CString m_csInputPassword;
	int m_bSupportGUID;
	CString m_strDevID;
	void GetPath();
	CString m_strdir;
	FILE *m_pFile;
	CString m_strGUIDFile;
	afx_msg void OnBnClickedButtonImport();
	afx_msg void OnBnClickedButtonReset2();
	BOOL m_bSycnIPCPW2;
};
