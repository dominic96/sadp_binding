#pragma once


// CEhomeEnable �Ի���

class CEhomeEnable : public CDialog
{
	DECLARE_DYNAMIC(CEhomeEnable)

public:
	CEhomeEnable(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEhomeEnable();

// �Ի�������
	enum { IDD = IDD_DLG_EHOME_ENABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnEnable();

public:
    CString m_strDevSerialNo;
    CString m_strDevMAC;
    CString m_strDevID;
    CString m_strEhomeKey;
    CString m_strPassword;
};
