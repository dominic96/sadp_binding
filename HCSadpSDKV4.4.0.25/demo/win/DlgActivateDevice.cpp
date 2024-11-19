// DlgActivateDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgActivateDevice.h"
#include "afxdialogex.h"


// CDlgActivateDevice 对话框

IMPLEMENT_DYNAMIC(CDlgActivateDevice, CDialogEx)

CDlgActivateDevice::CDlgActivateDevice(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgActivateDevice::IDD, pParent)
	, m_password(_T(""))
{

}

BOOL CDlgActivateDevice::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_DevSerialNO.SetWindowText(deviceNo);
	return TRUE;
}

CDlgActivateDevice::~CDlgActivateDevice()
{
}

void CDlgActivateDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DEVICE_SERIVAL_NO, m_DevSerialNO);
	DDX_Text(pDX, IDC_EDIT_COMMAND, m_password);
}


BEGIN_MESSAGE_MAP(CDlgActivateDevice, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgActivateDevice::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgActivateDevice::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CDlgActivateDevice 消息处理程序


void CDlgActivateDevice::OnBnClickedButtonOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char *TempPasswd;
	TempPasswd = m_password.GetBuffer(0);
	if (strcmp(TempPasswd, "") == 0)
	{
		AfxMessageBox("Please enter password");
		return;
	}
	int iFlag = SADP_ActivateDevice(deviceNo.GetBuffer(0), TempPasswd);
	SetDlgItemText(IDC_EDIT_ACTIVATE_PASSWORD, "");
	if (iFlag == 1)
	{
		AfxMessageBox("Activate success");
	}
	else if (iFlag == 0)
	{
		DWORD dwError = SADP_GetLastError();
		char szTemp[128] = { 0 };
		if (dwError == SADP_HAS_ACTIVATED)
		{
			AfxMessageBox("Activate failed:device has activated!");
		}
		else if (dwError == SADP_RISK_PASSWORD)
		{
			AfxMessageBox("Activate failed:High risk password!");
		}
		else if (dwError == SADP_TIMEOUT)
		{
			AfxMessageBox("Activate failed: Time out!");
		}
		else if (dwError == SADP_DEVICE_DENY)
		{
			AfxMessageBox("Activate failed!");
		}
		else
		{
			sprintf(szTemp, "Activate failed!,Error Number%d", dwError);
			AfxMessageBox(szTemp);
		}
	}
	CDialog::OnCancel();
}


void CDlgActivateDevice::OnBnClickedButtonCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
