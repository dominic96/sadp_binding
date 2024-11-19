#pragma once

#include "Sadp.h"

// CDlgCustom �Ի���

class CDlgCustom : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCustom)

public:
	CDlgCustom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCustom();

// �Ի�������
	enum { IDD = IDD_DIALOG_CUSTOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CString m_sDeviceTypeUnlockCode;
    afx_msg void OnBnClickedBtnGet();

    SADP_TYPE_UNLOCK_CODE m_strTypeUnLockCode;
    SADP_CUSTOM_DEVICE_TYPE m_strCustomDeviceType;
    CString m_strDevID;

    CString m_csDeviceTypeSecretKey;
    afx_msg void OnBnClickedOk();

};
