#pragma once
#include "afxwin.h"
#include "Sadp.h"


// CDlgSetFilterRule �Ի���

class CDlgSetFilterRule : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetFilterRule)

public:
	CDlgSetFilterRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetFilterRule();

// �Ի�������
	enum { IDD = IDD_DLG_SET_FILTER_RULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnWifiParamCheck();
	// ���ù��˹���  
	CComboBox m_FilterRule;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
};
