#pragma once
#include "afxwin.h"
#include "Sadp.h"


// CDlgRestoreInactive �Ի���

class CDlgRestoreInactive : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRestoreInactive)

public:
	CDlgRestoreInactive(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRestoreInactive();

// �Ի�������
	enum { IDD = IDD_DLG_RESTORE_INACTIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �豸���к�
	CEdit m_DevSerialNO;
	// �豸����
	CEdit m_password;
	// �豸���к�
	CString devSerialNO;
	afx_msg void OnBnClickedButtonSave();
	//��ʼ����Ϣ
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
};
