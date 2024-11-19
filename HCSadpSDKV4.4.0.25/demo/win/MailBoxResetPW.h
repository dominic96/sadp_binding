#pragma once


// CMailBoxResetPW �Ի���

class CMailBoxResetPW : public CDialog
{
	DECLARE_DYNAMIC(CMailBoxResetPW)

public:
	CMailBoxResetPW(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMailBoxResetPW();
 CString m_strDevID;
 BOOL m_bMailBoxResetPW;
 BOOL m_bSycnIPCPW;

// �Ի�������
	enum { IDD = IDD_DLG_MAIL_BOX_RESET_PW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CString m_strMailBox;
    CString m_strPassword;
    CString m_strQrCodes;

    afx_msg void OnBnClickedSetMailBox();
    afx_msg void OnBnClickedExportQrCodes();

    CString m_strResetPassWord;
    CString m_strSafeCode;
    afx_msg void OnBnClickedResetPassword();
};
