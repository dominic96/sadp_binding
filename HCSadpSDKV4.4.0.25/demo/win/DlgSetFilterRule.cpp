// DlgSetFilterRule.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgSetFilterRule.h"
#include "afxdialogex.h"


// CDlgSetFilterRule 对话框

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


// CDlgSetFilterRule 消息处理程序


void CDlgSetFilterRule::OnBnClickedBtnWifiParamCheck()
{
	// TODO:  在此添加控件通知处理程序代码
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
	case 1: //过滤萤石 
		iRet = SADP_SetDeviceFilterRule(SADP_FILTER_EZVIZ, NULL, 0);
		break;
	case 2: //过滤OEM
		iRet = SADP_SetDeviceFilterRule(SADP_FILTER_OEM, NULL, 0);
		break;
	case 3: //过滤萤石和OEM
		iRet = SADP_SetDeviceFilterRule(SADP_FILTER_EZVIZ_OEM, NULL, 0);
		break;
	case 4: //仅显示OEM
		iRet = SADP_SetDeviceFilterRule(SADP_ONLY_DISPLAY_EZVIZ, NULL, 0);
		break;
	case 5: //仅显示萤石
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
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
