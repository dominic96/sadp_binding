// DlgRestoreInactive.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgRestoreInactive.h"
#include "afxdialogex.h"


// CDlgRestoreInactive �Ի���

IMPLEMENT_DYNAMIC(CDlgRestoreInactive, CDialogEx)

CDlgRestoreInactive::CDlgRestoreInactive(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRestoreInactive::IDD, pParent)
{

}

CDlgRestoreInactive::~CDlgRestoreInactive()
{
}

BOOL CDlgRestoreInactive::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_DevSerialNO.SetWindowText(devSerialNO);
	return TRUE;
}

void CDlgRestoreInactive::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DEV_SERIAL_NO, m_DevSerialNO);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_password);
}


BEGIN_MESSAGE_MAP(CDlgRestoreInactive, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgRestoreInactive::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgRestoreInactive::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgRestoreInactive ��Ϣ�������


void CDlgRestoreInactive::OnBnClickedButtonSave()
{
	UpdateData(TRUE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SADP_INACTIVE_INFO struInactiveInfo = { 0 };
	SADP_DEV_LOCK_INFO strDevLockInfo = { 0 };
	//�������
	CString password;
	m_password.GetWindowText(password);
	memcpy(struInactiveInfo.szPassword, password.GetBuffer(0), password.GetLength());
	int iFlag = SADP_SetDeviceConfig(devSerialNO.GetBuffer(0), SADP_RESTORE_INACTIVE, &struInactiveInfo, sizeof(struInactiveInfo), &strDevLockInfo, sizeof(strDevLockInfo));
	if (iFlag == 1)
	{
		AfxMessageBox("RestoreInactive success");
	}
	else if (iFlag == 0)
	{
		DWORD dwError = SADP_GetLastError();
		char szTemp[128] = { 0 };

		if (dwError == SADP_TIMEOUT)
		{
			AfxMessageBox("Set RestoreInactive: Time out!");
		}
		else if (dwError == SADP_DEVICE_DENY)
		{
			AfxMessageBox("Set Ehome enable failed!");
		}
		else if (dwError == SADP_LOCKED)
		{
			sprintf(szTemp, "Device Lock��Lock %d minute.", strDevLockInfo.bySurplusLockTime);
			AfxMessageBox(szTemp);
		}
		else if (dwError == SADP_PASSWORD_ERROR)
		{
			sprintf(szTemp, "Password error��%d tiem you can try.", strDevLockInfo.byRetryTime);
			AfxMessageBox(szTemp);
		}
		else if (dwError == SADP_NOT_ACTIVATED)
		{
			AfxMessageBox("dev has not Activate");
		}
		else if (dwError == SADP_RISK_PASSWORD)
		{
			AfxMessageBox("Risk password!");
		}
		else
		{
			sprintf(szTemp, "Set Ehome enable failed!,Error Number%d", dwError);
			AfxMessageBox(szTemp);
		}
	}

	//�رմ���
	CDialog::OnCancel();
}


void CDlgRestoreInactive::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
