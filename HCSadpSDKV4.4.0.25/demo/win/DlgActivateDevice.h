#pragma once
#include "afxwin.h"
#include "Sadp.h"


// CDlgActivateDevice �Ի���

class CDlgActivateDevice : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgActivateDevice)

public:
	CDlgActivateDevice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgActivateDevice();

// �Ի�������
	enum { IDD = IDD_DLG_ACTIVATE_DEVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString deviceNo;
	// �豸���к�
	CEdit m_DevSerialNO;
	// ����
	CString m_password;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	virtual BOOL OnInitDialog();
};
