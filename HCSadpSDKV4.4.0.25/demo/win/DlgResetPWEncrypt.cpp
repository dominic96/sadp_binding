// DlgResetPWEncrypt.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgResetPWEncrypt.h"
#include "afxdialogex.h"


// CDlgResetPWEncrypt 对话框

IMPLEMENT_DYNAMIC(CDlgResetPWEncrypt, CDialogEx)

CDlgResetPWEncrypt::CDlgResetPWEncrypt(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgResetPWEncrypt::IDD, pParent)
	, m_password(_T(""))
	, m_Edit_Input_Str(_T(""))
	, m_sync(FALSE)
{

}

CDlgResetPWEncrypt::~CDlgResetPWEncrypt()
{
}

void CDlgResetPWEncrypt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Text(pDX, IDC_EDIT_INPUT_STRING, m_Edit_Input_Str);
	DDX_Check(pDX, IDC_CHECK_SYNC, m_sync);
}

void CDlgResetPWEncrypt::GetPath()
{
	char  exepath[MAX_PATH];
	CString tmpdir;
	memset(exepath, 0, MAX_PATH);
	GetModuleFileName(NULL, exepath, MAX_PATH);
	tmpdir = exepath;
	m_strdir = tmpdir.Left(tmpdir.ReverseFind('\\'));
}

BEGIN_MESSAGE_MAP(CDlgResetPWEncrypt, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgResetPWEncrypt::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CDlgResetPWEncrypt::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_RESET2, &CDlgResetPWEncrypt::OnBnClickedButtonReset2)
END_MESSAGE_MAP()


// CDlgResetPWEncrypt 消息处理程序


void CDlgResetPWEncrypt::OnBnClickedButtonExport()
{
	// TODO:  在此添加控件通知处理程序代码
	int  iRet = 0;
	memset(&m_struEncryptString, 0, sizeof(m_struEncryptString));
	if (m_bResetPWModeSecond)
	{
		iRet = SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_ENCRYPT_STRING_V31, NULL, 0, &m_struEncryptString, sizeof(m_struEncryptString));
	}
	else
	{
		AfxMessageBox("不支持获得加密串重置密码功能");
		return;
	}
	if (iRet == 0)
	{
		int iError = SADP_GetLastError();
		char szTemp[100] = { 0 };
		if (iError == SADP_NOT_ACTIVATED)
		{
			AfxMessageBox("Get device code failed, device was not activated!");
		}
		else if (iError == SADP_TIMEOUT)
		{
			AfxMessageBox("Get device code failed, timeout!");
		}
		else if (iError == SADP_DEVICE_DENY)
		{
			AfxMessageBox("Get device code failed!");
		}
		else
		{
			sprintf(szTemp, "Get device code failed, Error code%d", iError);
			AfxMessageBox(szTemp);
		}
		return;
	}
	//Open file,read infomation
	char szDeviceCode[256] = { 0 };
	GetPath();
	sprintf((char*)szDeviceCode, "%s%s", m_strdir, "\\DeviceKey.xml");
	m_pFile = fopen(szDeviceCode, "wb");
	if (NULL == m_pFile)
	{
		AfxMessageBox("Open File failed");
		return;
	}
	int iWriteData = 0;
    if (m_bResetPWModeSecond)
    {
        iWriteData = fwrite(m_struEncryptString.szEncryptString, sizeof(BYTE), strlen(m_struEncryptString.szEncryptString), m_pFile);
    }
	else
	{
		//iWriteData = fwrite(m_struSafeCode.szDeviceCode, sizeof(BYTE), strlen(m_struSafeCode.szDeviceCode), m_pFile);
	}

	if (0 == iWriteData)
	{
		AfxMessageBox("Write 0 Byte Data");
		return;
	}
	if (NULL != m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
	AfxMessageBox("Export file successfully!");
}


void CDlgResetPWEncrypt::OnBnClickedButtonImport()
{
	// TODO:  在此添加控件通知处理程序代码
	GetPath();
	CString strDirectoryName = m_strdir;
	CString strTempFile = m_strdir + "\\Encrypt.xml";
	CFileDialog openFileDlg(TRUE, strDirectoryName, strTempFile, OFN_HIDEREADONLY | OFN_READONLY, "", NULL);
	int  iOpenResult = openFileDlg.DoModal();

	if (IDOK == iOpenResult)
	{
		m_strEncryptFile = openFileDlg.GetPathName();
	}
}


void CDlgResetPWEncrypt::OnBnClickedButtonReset2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char *TempPasswd = { 0 };
	TempPasswd = m_password.GetBuffer(0);
	if (m_bResetPWModeSecond)
	{
		if (0 == strcmp(m_strEncryptFile, "") && 0 == strcmp(m_Edit_Input_Str, ""))
		{
			AfxMessageBox("请输入字符或导入文件!");
			return;
		}
	}
	else
	{
		AfxMessageBox("不支持获得加密串重置密码功能");
		return;
	}
	if (strcmp(TempPasswd, "") == 0)
	{
		AfxMessageBox("Please enter password!");
		return;
	}
	int iPassWordLength = strlen(TempPasswd);
	if (iPassWordLength > 16)
	{
		AfxMessageBox("Please enter a password less than 16 bit.");
		return;
	}

    SADP_RESET_PARAM_V50 struResetParamV50 = { 0 };
    struResetParamV50.dwSize = sizeof(struResetParamV50);
    struResetParamV50.byResetType = 2;
    struResetParamV50.byEnableSyncIPCPW = m_sync;
    memcpy(struResetParamV50.szPassword, TempPasswd, iPassWordLength);
    memcpy(struResetParamV50.szAuthFile, m_strEncryptFile.GetBuffer(0), strlen(m_strEncryptFile));
    memcpy(struResetParamV50.szCode, m_Edit_Input_Str.GetBuffer(0), strlen(m_Edit_Input_Str));


    SADP_DEV_LOCK_INFO struDevLockInfo = { 0 };

    int iRet = SADP_ResetPasswd_V50(m_strDevID.GetBuffer(0), &struResetParamV50, &struDevLockInfo);
	//清空数据
	m_strEncryptFile = "";
	if (iRet == 0)
	{

		int iError = SADP_GetLastError();
		char szTemp[100] = { 0 };
		if (iError == SADP_NOT_ACTIVATED)
		{
			AfxMessageBox("Password reset failed, the device was not activated!");
		}
		else if (iError == SADP_RISK_PASSWORD)
		{
			AfxMessageBox("Password reset failed, high risk password!");
		}
		else if (iError == SADP_TIMEOUT)
		{
			AfxMessageBox("Password reset failed, timeout!");
		}
		else if (iError == SADP_DEVICE_DENY)
		{
			AfxMessageBox("Password reset failed!");
		}
		else if (iError == SADP_EMPTY_ENCRYPT_STRING)
		{
            sprintf(szTemp, "加密串为空，请重新获取加密串! 剩余可尝试次数:[%d]", struDevLockInfo.byRetryTime);
			AfxMessageBox(szTemp);
		}
		else if (iError == SADP_INVALID_RESET_CODE)
		{
            sprintf(szTemp, "重置密码 重置口令错误! 剩余可尝试次数:[%d]", struDevLockInfo.byRetryTime);
			AfxMessageBox(szTemp);
		}
		else if (iError == SADP_LOCKED)
		{
            sprintf(szTemp, "reset password failed, device locked, lock time:[%d]!", struDevLockInfo.bySurplusLockTime);
			AfxMessageBox(szTemp);
		}
		else
		{
			sprintf(szTemp, "Password reset failed,Error code%d", iError);
			AfxMessageBox(szTemp);
		}
        GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText("");
		return;
	}
	else
	{
		char szTemp[100] = { 0 };
		sprintf(szTemp, "Password reset successfully!");
		AfxMessageBox(szTemp);
	}
}
