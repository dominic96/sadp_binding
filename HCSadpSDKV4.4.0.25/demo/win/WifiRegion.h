#pragma once
#include "Sadp.h"
#include "afxwin.h"

// CWifiRegion �Ի���

class CWifiRegion : public CDialog
{
	DECLARE_DYNAMIC(CWifiRegion)

public:
	CWifiRegion(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWifiRegion();

// �Ի�������
	enum { IDD = IDD_WIFI_GEGION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CComboBox m_cbRegion;
    BOOL m_bsupportEnhancement;
    BOOL m_bEnhancement;
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    CString m_strDevID;//�豸���к�
    CString m_strPassword;
    BYTE    m_bySupportRegion;
    BYTE   m_byCurrentRegion;
    virtual BOOL OnInitDialog();
    CString m_szPassword;
};
