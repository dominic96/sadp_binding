#pragma once
#include "Sadp.h"
#include "afxwin.h"
// CConfig 对话框

class CConfig : public CDialog
{
	DECLARE_DYNAMIC(CConfig)

public:
	CConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfig();

// 对话框数据
	enum { IDD = IDD_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CString m_strDevID;//设备序列号
    CString m_szPassWord;
    CString m_szChannelDefaultPW;
    BYTE   m_bySupportChannelDefaultPW;
    afx_msg void OnBnClickedOk2();
    afx_msg void OnBnClickedCancel2();
};
