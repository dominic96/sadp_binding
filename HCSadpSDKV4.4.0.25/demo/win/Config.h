#pragma once
#include "Sadp.h"
#include "afxwin.h"
// CConfig �Ի���

class CConfig : public CDialog
{
	DECLARE_DYNAMIC(CConfig)

public:
	CConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfig();

// �Ի�������
	enum { IDD = IDD_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CString m_strDevID;//�豸���к�
    CString m_szPassWord;
    CString m_szChannelDefaultPW;
    BYTE   m_bySupportChannelDefaultPW;
    afx_msg void OnBnClickedOk2();
    afx_msg void OnBnClickedCancel2();
};
