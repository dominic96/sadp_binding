#pragma once
#include "afxcmn.h"
#include "Sadp.h"


// DlgInquiry �Ի���

class DlgInquiry : public CDialog
{
	DECLARE_DYNAMIC(DlgInquiry)

public:
	DlgInquiry(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgInquiry();

// �Ի�������
	enum { IDD = IDD_DIG_INQUIRY_SUBNET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnSearch();
    CIPAddressCtrl m_StartIP;
    CIPAddressCtrl m_StopIP;
};
