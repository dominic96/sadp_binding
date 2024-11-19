#pragma once
#include "afxcmn.h"
#include "Sadp.h"


// DlgInquiry 对话框

class DlgInquiry : public CDialog
{
	DECLARE_DYNAMIC(DlgInquiry)

public:
	DlgInquiry(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgInquiry();

// 对话框数据
	enum { IDD = IDD_DIG_INQUIRY_SUBNET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnSearch();
    CIPAddressCtrl m_StartIP;
    CIPAddressCtrl m_StopIP;
};
