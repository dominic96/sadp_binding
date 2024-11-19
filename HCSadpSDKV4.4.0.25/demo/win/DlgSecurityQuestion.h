#pragma once
#include "Sadp.h"

// CDlgSecurityQuestion �Ի���
#define MAX_QUESTION_NUM 18 //���豸���15�����⣬ ���豸��2�������� + 3�������õ����� + 13�������⣬���������18����

class CDlgSecurityQuestion : public CDialog
{
	DECLARE_DYNAMIC(CDlgSecurityQuestion)

public:
	CDlgSecurityQuestion(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSecurityQuestion();

// �Ի�������
	enum { IDD = IDD_DLG_SECURITY_QUESTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
