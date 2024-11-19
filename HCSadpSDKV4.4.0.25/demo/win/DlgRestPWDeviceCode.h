#pragma once
#include "Sadp.h"
#include "afxwin.h"

// CDlgRestPWDeviceCode �Ի���

class CDlgRestPWDeviceCode : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRestPWDeviceCode)

public:
	CDlgRestPWDeviceCode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRestPWDeviceCode();

// �Ի�������
	enum { IDD = IDD_DLG_REST_PW_DEVICE_CODE };
public:
	BOOL m_bResetPWModeSecond;
	SADP_SAFE_CODE_V31 m_struSafeCode;
	void GetPath();
	CString m_strdir;
	CString m_strDevID;//�豸���к�
	CString m_strEncryptFile;
	BOOL m_bResetPW;
	FILE *m_pFile;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnBnClickedButtonImport();
	afx_msg void OnBnClickedButtonReset2();
	BOOL m_sync;
	CString m_password;
};
