#pragma once
#include "Sadp.h"
#include "afxwin.h"

// CDlgAutoRequestInterval �Ի���

class CDlgAutoRequestInterval : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAutoRequestInterval)

public:
	CDlgAutoRequestInterval(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAutoRequestInterval();

// �Ի�������
	enum { IDD = IDD_DLG_SET_AUTOREQ_INTERVAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	// �����Զ�ˢ������ʱ����
	int m_interval;
	afx_msg void OnBnClickedButtonCancel();
};
