#pragma once
#include "afxwin.h"
#include "Sadp.h"


// CDlgRestoreInactive 对话框

class CDlgRestoreInactive : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRestoreInactive)

public:
	CDlgRestoreInactive(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRestoreInactive();

// 对话框数据
	enum { IDD = IDD_DLG_RESTORE_INACTIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 设备序列号
	CEdit m_DevSerialNO;
	// 设备密码
	CEdit m_password;
	// 设备序列号
	CString devSerialNO;
	afx_msg void OnBnClickedButtonSave();
	//初始化信息
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
};
