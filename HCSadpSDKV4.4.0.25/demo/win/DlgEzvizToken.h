#pragma once
#include "afxwin.h"


// CDlgEzvizToken �Ի���

class CDlgEzvizToken : public CDialog
{
	DECLARE_DYNAMIC(CDlgEzvizToken)

public:
	CDlgEzvizToken(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgEzvizToken();

// �Ի�������
	enum { IDD = IDD_DLG_EZVIZ_TOKEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CString m_strDevID;//�豸���к�
    CEdit m_editToken;
    CButton m_btnSet;
    CEdit m_editPassword;
    afx_msg void OnBnClickedBtnEzvizToken();
    CString m_strToken;
    CString m_strPassword;
};
