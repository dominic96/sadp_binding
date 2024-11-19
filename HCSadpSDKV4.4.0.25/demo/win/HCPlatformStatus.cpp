// HCPlatformStatus.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "HCPlatformStatus.h"
#include "afxdialogex.h"


// HCPlatformStatus 对话框

IMPLEMENT_DYNAMIC(HCPlatformStatus, CDialog)

HCPlatformStatus::HCPlatformStatus(CWnd* pParent /*=NULL*/)
	: CDialog(HCPlatformStatus::IDD, pParent)
	, m_bHCPlatforStatus(FALSE)
	, m_strVerificationCode(_T(""))
	, m_strPassword(_T(""))
{

}

HCPlatformStatus::~HCPlatformStatus()
{
}

void HCPlatformStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_HCPLATFORM_STATUS, m_bHCPlatforStatus);
	DDX_Text(pDX, IDC_EDIT_VERIFICATION_CODE, m_strVerificationCode);
	DDX_Text(pDX, IDC_EDIT_PASS_WORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(HCPlatformStatus, CDialog)
	ON_BN_CLICKED(IDOK, &HCPlatformStatus::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &HCPlatformStatus::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &HCPlatformStatus::OnBnClickedButton1)
END_MESSAGE_MAP()


// HCPlatformStatus 消息处理程序


void HCPlatformStatus::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//先修改验证码
	SADP_VERIFICATION_CODE_INFO struVerificationCode = { 0 };
	//返回结构体
	SADP_DEV_LOCK_INFO struLockInfo = { 0 };
	struVerificationCode.dwSize = sizeof(struVerificationCode);
	//memcpy(struVerificationCode.szVerificationCode, m_strVerificationCode.GetBuffer(), SADP_MAX_VERIFICATION_CODE_LEN);
	strncpy((char*)struVerificationCode.szVerificationCode, (LPCTSTR)m_strVerificationCode, SADP_MAX_VERIFICATION_CODE_LEN);
	memcpy(struVerificationCode.szPassword, m_strPassword.GetBuffer(), 16);
	int iRet = 0;

	iRet = SADP_SetDeviceConfig(m_strDevID.GetBuffer(), SADP_SET_VERIFICATION_CODE, &struVerificationCode, sizeof(struVerificationCode),
			&struLockInfo, sizeof(struLockInfo));

	if (iRet == TRUE)
	{
		AfxMessageBox("SADP_SET_VERIFICATION_CODE success");
	}
	else
	{
		DWORD dwError = SADP_GetLastError();
		char szTemp[128] = { 0 };
		
	 if (dwError == SADP_TIMEOUT)
		{
			AfxMessageBox("Set Verification Code failed: Time out!");
		}
		else if (dwError == SADP_DEVICE_DENY)
		{
			AfxMessageBox("Set Verification Code failed!");
		}
		else if (dwError == SADP_ILLEGAL_VERIFICATION_CODE)
		{
			AfxMessageBox("Set Verification Code failed: Illegal Verification Code!");
		}
		else if (dwError == SADP_LOCKED)
		{
			sprintf(szTemp, "Device Lock，Lock %d minute.", struLockInfo.bySurplusLockTime);
			AfxMessageBox(szTemp);
		}
		else if (dwError == SADP_PASSWORD_ERROR)
		{
			sprintf(szTemp, "Password error，%d tiem you can try.", struLockInfo.byRetryTime);
			AfxMessageBox(szTemp);
		}
		else if (dwError == SADP_NOT_ACTIVATED)
		{
			AfxMessageBox("dev has not Activate");
		}
		else
		{
			sprintf(szTemp, "Set Verification Code failed!,Error Number%d", dwError);
			AfxMessageBox(szTemp);
		}
	}
	//CDialog::OnOK();
}


void HCPlatformStatus::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

//修改HCPlatForm状态
void HCPlatformStatus::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SADP_HCPLATFORM_STATUS_INFO struStatus = { 0 };
	struStatus.dwSize = sizeof(SADP_HCPLATFORM_STATUS_INFO);
	struStatus.byEnableHCPlatform = m_bHCPlatforStatus;
	//
	memcpy(struStatus.szPassword, m_strPassword.GetBuffer(), 16);

	//返回结构体
	SADP_DEV_LOCK_INFO struLockInfo = { 0 };

	int iRet = SADP_SetDeviceConfig(m_strDevID.GetBuffer(), SADP_SET_HCPLATFORM_STATUS, &struStatus, sizeof(struStatus),
		&struLockInfo, sizeof(struLockInfo));
	if (iRet == TRUE)
	{
		AfxMessageBox("SADP_SET_HCPLATFORM_STATUS success");
	}
	else
	{
		DWORD dwError = SADP_GetLastError();
		char szTemp[128] = { 0 };
	
		if (dwError == SADP_TIMEOUT)
		{
			AfxMessageBox("Set HCPlatform status failed: Time out!");
		}
		else if (dwError == SADP_DEVICE_DENY)
		{
			AfxMessageBox("Set HCPlatform status failed!");
		}
		else if (dwError == SADP_ILLEGAL_VERIFICATION_CODE)
		{
			AfxMessageBox("Set HCPlatform status failed: Illegal Verification Code!");
		}
		if (dwError == SADP_LOCKED)
		{
			sprintf(szTemp, "Device Lock，Lock %d minute.", struLockInfo.bySurplusLockTime);
			AfxMessageBox(szTemp);
		}
		else if (dwError == SADP_NOT_ACTIVATED)
		{
			AfxMessageBox("dev has not Activate");
		}
		else if (dwError == SADP_PASSWORD_ERROR)
		{
			sprintf(szTemp, "Password error，%d tiem you can try.", struLockInfo.byRetryTime);
			AfxMessageBox(szTemp);
		}

		else
		{
			sprintf(szTemp, "Set HCPlatform status failed!,Error Number%d", dwError);
			AfxMessageBox(szTemp);
		}
	}
}
