#pragma once
#include "Sadp.h"

// CDlgResetPWPhone �Ի���

class CDlgResetPWPhone : public CDialog
{
	DECLARE_DYNAMIC(CDlgResetPWPhone)

public:
	CDlgResetPWPhone(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgResetPWPhone();

// �Ի�������
	enum { IDD = IDD_DLG_RESET_PHONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
    void GetPath();
    CString m_strDevID;//�豸���к�
    CString m_strdir;
    FILE *m_pFile;
    afx_msg void OnBnClickedButtonExport();
    afx_msg void OnBnClickedButtonReset2();
    CString m_szCode;
    CString m_szPassword;
};
