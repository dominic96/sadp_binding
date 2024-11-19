#pragma once
#include "afxwin.h"
#include "Sadp.h"


// CDlgActivateDevice 对话框

class CDlgActivateDevice : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgActivateDevice)

public:
	CDlgActivateDevice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgActivateDevice();

// 对话框数据
	enum { IDD = IDD_DLG_ACTIVATE_DEVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString deviceNo;
	// 设备序列号
	CEdit m_DevSerialNO;
	// 密码
	CString m_password;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	virtual BOOL OnInitDialog();
};
