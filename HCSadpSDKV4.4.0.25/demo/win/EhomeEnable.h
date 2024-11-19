#pragma once


// CEhomeEnable 对话框

class CEhomeEnable : public CDialog
{
	DECLARE_DYNAMIC(CEhomeEnable)

public:
	CEhomeEnable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEhomeEnable();

// 对话框数据
	enum { IDD = IDD_DLG_EHOME_ENABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
