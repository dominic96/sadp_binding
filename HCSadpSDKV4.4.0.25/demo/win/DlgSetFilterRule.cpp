// DlgSetFilterRule.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgSetFilterRule.h"
#include "afxdialogex.h"


// CDlgSetFilterRule �Ի���

IMPLEMENT_DYNAMIC(CDlgSetFilterRule, CDialogEx)

CDlgSetFilterRule::CDlgSetFilterRule(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetFilterRule::IDD, pParent)
{
	
}

CDlgSetFilterRule::~CDlgSetFilterRule()
{
}

BOOL CDlgSetFilterRule::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_FilterRule.SetCurSel(0);
	return true;
}



void CDlgSetFilterRule::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX); 
	DDX_Control(pDX, IDC_COM_SET_FILTER_RULE, m_FilterRule);
}


BEGIN_MESSAGE_MAP(CDlgSetFilterRule, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_WIFI_PARAM_CHECK, &CDlgSetFilterRule::OnBnClickedBtnWifiParamCheck)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgSetFilterRule::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgSetFilterRule ��Ϣ�������


void CDlgSetFilterRule::OnBnClickedBtnWifiParamCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	int iRule = m_FilterRule.GetCurSel();
	int iRet = 0;
	SADP_DISPLAY_OEM_CFG struOEMCfg = { 0 };
	switch (iRule)
	{
	case 0:
		iRet = SADP_SetDeviceFilterRule(SADP_DISPLAY_ALL, NULL, 0);
		break;
	case 1: //����өʯ 
		iRet = SADP_SetDeviceFilterRule(SADP_FILTER_EZVIZ, NULL, 0);
		break;
	case 2: //����OEM
		iRet = SADP_SetDeviceFilterRule(SADP_FILTER_OEM, NULL, 0);
		break;
	case 3: //����өʯ��OEM
		iRet = SADP_SetDeviceFilterRule(SADP_FILTER_EZVIZ_OEM, NULL, 0);
		break;
	case 4: //����ʾOEM
		iRet = SADP_SetDeviceFilterRule(SADP_ONLY_DISPLAY_EZVIZ, NULL, 0);
		break;
	case 5: //����ʾөʯ
		iRet = SADP_SetDeviceFilterRule(SADP_ONLY_DISPLAY_OEM, &struOEMCfg, sizeof(struOEMCfg));
		break;
	default:
		break;
	}
	if (iRet == 1)
	{
		AfxMessageBox("SADP_SetDeviceDisplayRule Success!");
	}
	else
	{
		int iError = SADP_GetLastError();
		char szTemp[128] = { 0 };
		sprintf(szTemp, "SADP_SetDeviceDisplayRule fail err %d!", iError);
		AfxMessageBox(szTemp);
	}
	CDialog::OnCancel();
}


void CDlgSetFilterRule::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
