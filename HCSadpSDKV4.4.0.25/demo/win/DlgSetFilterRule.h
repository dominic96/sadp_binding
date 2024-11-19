#pragma once
#include "afxwin.h"
#include "Sadp.h"


// CDlgSetFilterRule 对话框

class CDlgSetFilterRule : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetFilterRule)

public:
	CDlgSetFilterRule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSetFilterRule();

// 对话框数据
	enum { IDD = IDD_DLG_SET_FILTER_RULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnWifiParamCheck();
	// 设置过滤规则  
	CComboBox m_FilterRule;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
};
