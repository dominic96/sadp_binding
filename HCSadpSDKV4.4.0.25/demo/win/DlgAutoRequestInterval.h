#pragma once
#include "Sadp.h"
#include "afxwin.h"

// CDlgAutoRequestInterval 对话框

class CDlgAutoRequestInterval : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAutoRequestInterval)

public:
	CDlgAutoRequestInterval(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAutoRequestInterval();

// 对话框数据
	enum { IDD = IDD_DLG_SET_AUTOREQ_INTERVAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	// 设置自动刷新搜索时间间隔
	int m_interval;
	afx_msg void OnBnClickedButtonCancel();
};
