// ResetPassword.cpp : implementation file
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "ResetPassword.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResetPassword dialog


CResetPassword::CResetPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CResetPassword::IDD, pParent)
    , m_cbGUID(FALSE)
{
	//{{AFX_DATA_INIT(CResetPassword)
	m_Edit_Input_Str = _T("");
	//}}AFX_DATA_INIT
	m_strDevID = "";
	m_strEncryptFile= "";
    m_strGUIDFile = "";
	m_pFile = NULL;
    m_bSycnIPCPW = FALSE;
    memset(&m_struResetParam, 0, sizeof(m_struResetParam));
    memset(&m_struSafeCode, 0, sizeof(m_struSafeCode));
    memset(&m_struEncryptString, 0, sizeof(m_struEncryptString));
    m_bResetPWModeSecond = FALSE;
    m_bResetPW = FALSE;
    m_bSupportGUID = FALSE;
    m_bSupportSecurityQuestion = FALSE;
    m_csInputPassword = _T("");
    m_bSycnIPCPW2 = FALSE;
}


void CResetPassword::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CResetPassword)
    DDX_Text(pDX, IDC_EDIT_INPUT_STRING, m_Edit_Input_Str);
    DDX_Text(pDX, IDC_EDIT_INPUT_PASSWORD, m_csInputPassword);
    DDX_Control(pDX, IDC_CMB_RESET_PASSWORD_TYPE, m_cmbResetPasswordType);
    DDX_Check(pDX, IDC_SYNC_IPC_PW2, m_bSycnIPCPW2);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CB_GUID, m_cbGUID);
}


BEGIN_MESSAGE_MAP(CResetPassword, CDialog)
	//{{AFX_MSG_MAP(CResetPassword)
	ON_BN_CLICKED(IDC_BTN_RESET_PASSWORD, OnBtnResetPassword)
	ON_BN_CLICKED(IDC_BTN_RESTORE_PASSWORD, OnBtnRestorePassword)
	ON_BN_CLICKED(IDC_BTN_EXPORT_FILE, OnBtnExportFile)
	ON_BN_CLICKED(IDC_BTN_IMPORT_FILE, OnBtnImportFile)
	ON_BN_CLICKED(IDC_SYNC_IPC_PW, OnSyncIpcPw)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_EXPORT_GUID, &CResetPassword::OnBnClickedBtnExportGuid)
    ON_BN_CLICKED(IDC_BTN_SECURITY_QUESTION, &CResetPassword::OnBnClickedBtnSecurityQuestion)
    ON_BN_CLICKED(IDC_BTN_IMPORT_GUID, &CResetPassword::OnBnClickedBtnImportGuid)
    ON_BN_CLICKED(IDC_BTN_GUID_RESET_PASSWORD, &CResetPassword::OnBnClickedBtnGuidResetPassword)
    ON_BN_CLICKED(IDC_BTN_MAIL_BOX_RESET_PW, &CResetPassword::OnBnClickedBtnMailBoxResetPw)
    ON_BN_CLICKED(IDC_BTN_RESET_PASSWORD2, &CResetPassword::OnBnClickedBtnResetPassword2)
    ON_BN_CLICKED(IDC_BTN_GET_RESET_TYPE, &CResetPassword::OnBnClickedBtnGetResetType)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResetPassword message handlers

//Reset Password
void CResetPassword::OnBtnResetPassword() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char TempPasswd[32] = {0};      
	GetDlgItemText(IDC_EDIT_ACTIVATE_PASSWORD,TempPasswd,32);
	
    
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
        //支持密码重置需要导入文件
        if (m_bResetPW)
        {
            if (0 == strcmp(m_strEncryptFile, ""))
            {
                AfxMessageBox("请先导入文件!");
                return;
            }
        }

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

    //先清空结构体
    memset(&m_struResetParam, 0, sizeof(m_struResetParam));
    //为结构体赋值
	memcpy(m_struResetParam.szPassword, TempPasswd, strlen(TempPasswd));
	memcpy(m_struResetParam.szAuthFile, m_strEncryptFile.GetBuffer(0), strlen(m_strEncryptFile));
    //只支持密码恢复
    if (!(m_bResetPW || m_bResetPWModeSecond))
    {
        memcpy(m_struResetParam.szCode, TempPasswd, strlen(TempPasswd));
    }
    else
    {
        memcpy(m_struResetParam.szCode, m_Edit_Input_Str.GetBuffer(0), strlen(m_Edit_Input_Str));
    }
        
    OnSyncIpcPw();
	int iRet = SADP_ResetPasswd(m_strDevID.GetBuffer(0), &m_struResetParam);
    //清空数据
    m_strEncryptFile = "";
	if (iRet == 0 )
	{
	
		int iError = SADP_GetLastError();
		char szTemp[100] = {0};
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
            AfxMessageBox("加密串为空，请重新获取加密串!");
        }
        else if (iError == SADP_INVALID_RESET_CODE)
        {
            AfxMessageBox("重置密码 重置口令错误!");
        }
		else
		{
			sprintf(szTemp, "Password reset failed,Error code%d", iError);
			AfxMessageBox(szTemp);
		}
		GetDlgItem(IDC_EDIT_ACTIVATE_PASSWORD)->SetWindowText("");
		return;
	}
	else
	{
		char szTemp[100] = {0};
        sprintf(szTemp, "Password reset successfully!");
		AfxMessageBox(szTemp);
	}
}

//Restore Password
void CResetPassword::OnBtnRestorePassword() 
{
	// TODO: Add your control notification handler code here
	if (0 == strcmp(m_strEncryptFile, ""))
	{
		AfxMessageBox("Please Import File first!");
		return;
	}
	SADP_RESET_PARAM struResetParam = {0};

	//Open file, read infomation
	m_pFile = fopen(m_strEncryptFile, "rb");
	if (NULL == m_pFile)
	{
		AfxMessageBox("Open File failed");  
		return;
	}
	int iReadData = fread(struResetParam.szCode, sizeof(BYTE), MAX_ENCRYPT_CODE, m_pFile);
	if (NULL != m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
	if (0 == iReadData)
	{
		AfxMessageBox("Read 0 Byte Data");  
		return;
	}
	int iRet = SADP_ResetPasswd(m_strDevID.GetBuffer(0), &struResetParam);
	if (iRet == 0 )
	{
		
		int iError = SADP_GetLastError();
		char szTemp[100] = {0};
		if (iError == SADP_TIMEOUT)
		{
			AfxMessageBox("Password restore failed, timeout!");
		}
		else if (iError == SADP_DEVICE_DENY)
		{
			AfxMessageBox("Password restore failed!");
		}
		else
		{
			sprintf(szTemp, "Password restore failed!,Error code%d", iError);
			AfxMessageBox(szTemp);
		}
		return;
	}
	else
	{
		char szTemp[100] = {0};
		sprintf(szTemp, "Password restore successfully!");
		AfxMessageBox(szTemp);
	}
	
}

void CResetPassword::GetPath()
{
	char  exepath[MAX_PATH];
    CString tmpdir; 
    memset(exepath,0,MAX_PATH); 
    GetModuleFileName(NULL,exepath,MAX_PATH); 
    tmpdir=exepath; 
    m_strdir=tmpdir.Left(tmpdir.ReverseFind('\\'));
}

void CResetPassword::OnBtnExportFile() 
{
	// TODO: Add your control notification handler code here

	//1. get device code
    DWORD dwRetLen = 0;
    int  iRet = 0;
    memset(&m_struSafeCode, 0, sizeof(m_struSafeCode));
    memset(&m_struEncryptString, 0, sizeof(m_struEncryptString));
    if (m_bResetPWModeSecond)
    {
	    iRet = SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_ENCRYPT_STRING_V31, NULL, 0, &m_struEncryptString, sizeof(m_struEncryptString));
    }
    else
    {
	    iRet = SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_DEVICE_CODE_V31, NULL, 0, &m_struSafeCode, sizeof(m_struSafeCode));
    }
	
	if (iRet == 0)
	{
		int iError = SADP_GetLastError();
		char szTemp[100] = {0};
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
	char szDeviceCode[256] = {0};
	char szTempComtent[512] = {0};
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
        iWriteData = fwrite(m_struEncryptString.szEncryptString, sizeof(BYTE), strlen(m_struEncryptString.szEncryptString), m_pFile);;
    }
    else
    {
        iWriteData = fwrite(m_struSafeCode.szDeviceCode, sizeof(BYTE), strlen(m_struSafeCode.szDeviceCode), m_pFile);
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

void CResetPassword::OnBtnImportFile() 
{
	// TODO: Add your control notification handler code here
	GetPath();
	CString strDirectoryName = m_strdir;
	CString strTempFile = m_strdir + "\\Encrypt.xml";
	CFileDialog openFileDlg(TRUE, strDirectoryName, strTempFile, OFN_HIDEREADONLY|OFN_READONLY, "", NULL);
	int  iOpenResult = openFileDlg.DoModal();

	if (IDOK == iOpenResult)
	{
		m_strEncryptFile = openFileDlg.GetPathName();
	}
}

BOOL CResetPassword::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_SYNC_IPC_PW)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_INPUT_STRING)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_INPUT_STRING)->ShowWindow(SW_HIDE);
    if (m_bSycnIPCPW)
    {
        GetDlgItem(IDC_SYNC_IPC_PW)->ShowWindow(SW_NORMAL);
    }
    if (m_bResetPWModeSecond)
    {
        GetDlgItem(IDC_STATIC_INPUT_STRING)->ShowWindow(SW_NORMAL);
        GetDlgItem(IDC_EDIT_INPUT_STRING)->ShowWindow(SW_NORMAL);
    }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResetPassword::OnSyncIpcPw() 
{
	// TODO: Add your control notification handler code here
    if (IsDlgButtonChecked(IDC_SYNC_IPC_PW))
    {
        m_struResetParam.byEnableSyncIPCPW = 1;
    }
    else
    {
        m_struResetParam.byEnableSyncIPCPW = 0;
    }
	
}

void CResetPassword::OnBnClickedBtnExportGuid()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (FALSE == m_bSupportGUID)
    {
        AfxMessageBox("设备不支持GUID导出!");
        return;
    }
    if (m_csInputPassword == "")
    {
        AfxMessageBox("请先输入密码!");
        return;
    }
    if (m_csInputPassword.GetLength() > 16)
    {
        AfxMessageBox("密码长度超出范围!");
        return;
    }
    SADP_GUID_FILE_COND struGuidFileCond = { 0 };
    memcpy(struGuidFileCond.szPassword, m_csInputPassword.GetBuffer(0), m_csInputPassword.GetLength());
    SADP_GUID_FILE_V31 struGuidFile = { 0 };
    struGuidFile.dwGUIDSize = sizeof(struGuidFile);
    int iRet = SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_GUID_V31, &struGuidFileCond, sizeof(struGuidFileCond), &struGuidFile, sizeof(struGuidFile));
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        if (iError == SADP_NOT_ACTIVATED)
        {
            AfxMessageBox("Export guid failed, device was not activated!");
        }
        else if (iError == SADP_TIMEOUT)
        {
            AfxMessageBox("Export guid failed, timeout!");
        }
        else if (iError == SADP_PASSWORD_ERROR)
        {
            sprintf(szTemp, "Export guid failed, password error, retry guid times:[%d]!", struGuidFile.struDevLockInfo.byRetryTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Export guid failed, device deny!");
        }
        else if (iError == SADP_LOCKED)
        {
            sprintf(szTemp, "Export guid failed, device locked，lock time:[%d]!", struGuidFile.struDevLockInfo.bySurplusLockTime);
            AfxMessageBox(szTemp);
        }
        else
        {
            sprintf(szTemp, "Export guid failed, Error code%d", iError);
            AfxMessageBox(szTemp);
        }
        return;
    }

    //Open file,read infomation
    char szGUIDInfo[256] = { 0 };
    GetPath();
    sprintf((char*)szGUIDInfo, "%s%s", m_strdir, "\\DeviceGUID.xml");
    m_pFile = fopen(szGUIDInfo, "wb");
    if (NULL == m_pFile)
    {
        AfxMessageBox("Open File failed");
        return;
    }
    int iWriteData = fwrite(struGuidFile.szGUID, sizeof(BYTE), MAX_GUID_LEN, m_pFile);

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
    AfxMessageBox("Export GUID successfully!");
}

#include "DlgSecurityQuestion.h"
void CResetPassword::OnBnClickedBtnSecurityQuestion()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgSecurityQuestion dlg;
    dlg.m_strDevID = m_strDevID;
    dlg.m_bSupportSecurityQuestion = m_bSupportSecurityQuestion;
    dlg.m_bSupportSycnIPCPW = m_bSycnIPCPW;
    dlg.DoModal();
}


void CResetPassword::OnBnClickedBtnImportGuid()
{
    // TODO:  在此添加控件通知处理程序代码
    GetPath();
    CString strDirectoryName = m_strdir;
    CString strTempFile = m_strdir + "\\DeviceGUID.xml";
    CFileDialog openFileDlg(TRUE, strDirectoryName, strTempFile, OFN_HIDEREADONLY | OFN_READONLY, "", NULL);
    int  iOpenResult = openFileDlg.DoModal();

    if (IDOK == iOpenResult)
    {
        m_strGUIDFile = openFileDlg.GetPathName();
    }
}


void CResetPassword::OnBnClickedBtnGuidResetPassword()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (FALSE == m_bSupportGUID)
    {
        AfxMessageBox("设备不支持GUID重置密码!");
        return;
    }
    if (m_csInputPassword == "")
    {
        AfxMessageBox("请先输入密码!");
        return;
    }
    if (m_csInputPassword.GetLength() > 15)
    {
        AfxMessageBox("密码长度超出范围!");
        return;
    }
    if (0 == strcmp(m_strGUIDFile, ""))
    {
        AfxMessageBox("请先导入GUID文件!");
        return;
    }

    SADP_RESET_PARAM_V50 struResetParamV50 = { 0 };
    struResetParamV50.dwSize = sizeof(struResetParamV50);
    struResetParamV50.byResetType = 4;
    struResetParamV50.byEnableSyncIPCPW = m_bSycnIPCPW2;
    memcpy(struResetParamV50.szPassword, m_csInputPassword.GetBuffer(0), m_csInputPassword.GetLength());

    FILE* fp = NULL;
    fp = fopen((const char *)m_strGUIDFile.GetBuffer(0), "rb"); //只供读取
    if (fp == NULL)
    {
        AfxMessageBox("读取导入GUID文件失败!");
        return;
    }
    fseek(fp, 0L, SEEK_END);
    int len = ftell(fp);
    rewind(fp);
    fread(struResetParamV50.szGUID, 1, len, fp);
    fclose(fp);
    SADP_DEV_LOCK_INFO struDevLockInfo = { 0 };
    m_strGUIDFile = "";

    int iRet = SADP_ResetPasswd_V50(m_strDevID.GetBuffer(0), &struResetParamV50, &struDevLockInfo);
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        if (iError == SADP_TIMEOUT)
        {
            AfxMessageBox("Guid reset password failed, timeout!");
        }
        else if (iError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Guid reset password failed, device deny!");
        }
        else if (iError == SADP_LOCKED)
        {
            sprintf(szTemp, "Guid reset password failed, device locked, lock time:[%d]!", struDevLockInfo.bySurplusLockTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_RISK_PASSWORD)
        {
            AfxMessageBox("Guid reset password failed, risk password!");
        }
        else if (iError == SADP_NOT_ACTIVATED)
        {
            AfxMessageBox("Guid reset password failed, device not activated!");
        }
        else if (iError == SADP_EMPTY_ENCRYPT_STRING)
        {
            AfxMessageBox("Guid reset password failed, empty encrypt string!");
        }
        else if (iError == SADP_EXPORT_FILE_OVERDUE)
        {
            AfxMessageBox("Guid reset password failed, export file overdue!");
        }
        else if (iError == SADP_INVALID_GUID)
        {
            sprintf(szTemp, "Guid reset password failed, invalid guid, retry guid times:[%d]!", struDevLockInfo.byRetryTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_ANSWER_ERROR)
        {
            AfxMessageBox("Guid reset password failed, answer error!");
        }
        else
        {
            sprintf(szTemp, "Guid reset password failed, Error code%d", iError);
            AfxMessageBox(szTemp);
        }
        return;
    }

    UpdateData(FALSE);
    AfxMessageBox("GUID reset password successfully!");
}

#include "MailBoxResetPW.h"
void CResetPassword::OnBnClickedBtnMailBoxResetPw()
{
    // TODO:  在此添加控件通知处理程序代码
    CMailBoxResetPW dlg;
    dlg.m_strDevID = m_strDevID;
    dlg.m_bMailBoxResetPW = m_bMailBoxResetPW;
    dlg.m_bSycnIPCPW = m_bSycnIPCPW;

    dlg.DoModal();
}


void CResetPassword::OnBnClickedBtnResetPassword2()
{
    // TODO:  在此添加控件通知处理程序代码
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char TempPasswd[32] = { 0 };
    GetDlgItemText(IDC_EDIT_ACTIVATE_PASSWORD, TempPasswd, 32);


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
        //支持密码重置需要导入文件
        if (m_bResetPW)
        {
            if (0 == strcmp(m_strEncryptFile, ""))
            {
                AfxMessageBox("请先导入文件!");
                return;
            }
        }
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

    OnSyncIpcPw();

    SADP_RESET_PARAM_V50 struResetParamV50 = { 0 };
    struResetParamV50.dwSize = sizeof(struResetParamV50);
    struResetParamV50.byResetType = 2;
    struResetParamV50.byEnableSyncIPCPW = m_bSycnIPCPW;
    memcpy(struResetParamV50.szPassword, TempPasswd, iPassWordLength);
    memcpy(struResetParamV50.szAuthFile, m_strEncryptFile.GetBuffer(0), strlen(m_strEncryptFile));

    //memcpy(m_struResetParam.szCode, m_Edit_Input_Str.GetBuffer(0), strlen(m_Edit_Input_Str));

    SADP_DEV_LOCK_INFO struDevLockInfo = { 0 };

    int iRet = SADP_ResetPasswd_V50(m_strDevID.GetBuffer(0), &struResetParamV50, &struDevLockInfo);
    //清空数据
    m_strEncryptFile = "";
    if (iRet == FALSE)
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
        GetDlgItem(IDC_EDIT_ACTIVATE_PASSWORD)->SetWindowText("");
        return;
    }
    else
    {
        char szTemp[100] = { 0 };
        sprintf(szTemp, "Password reset successfully!");
        AfxMessageBox(szTemp);
    }
}


void CResetPassword::OnBnClickedBtnGetResetType()
{
    // TODO:  在此添加控件通知处理程序代码

    //第一步CheckBox清空
    ((CButton*)GetDlgItem(IDC_CB_GUID))->SetCheck(FALSE);
    ((CButton*)GetDlgItem(IDC_CB_SECURITY_QUESTION))->SetCheck(FALSE);
    ((CButton*)GetDlgItem(IDC_CB_SECURITY_MAILBOX))->SetCheck(FALSE);
    ((CButton*)GetDlgItem(IDC_CB_HC))->SetCheck(FALSE);

    //第二步从设备获取配置
    SADP_PASSWORD_RESET_TYPE_PARAM struResetType = { 0 };

    if (SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_PASSWORD_RESET_TYPE, NULL, 0, &struResetType, sizeof(SADP_PASSWORD_RESET_TYPE_PARAM)))
    {
        if (struResetType.byEnable)
        {
            if (struResetType.byGuidEnabled)
            {
                ((CButton*)GetDlgItem(IDC_CB_GUID))->SetCheck(TRUE);
            }
            if (struResetType.bySecurityQuestionEnabled)
            {
                ((CButton*)GetDlgItem(IDC_CB_SECURITY_QUESTION))->SetCheck(TRUE);
            }
            if (struResetType.bySecurityMailBoxEnabled)
            {
                ((CButton*)GetDlgItem(IDC_CB_SECURITY_MAILBOX))->SetCheck(TRUE);
            }
            if (struResetType.byHikConnectEnabled)
            {
                ((CButton*)GetDlgItem(IDC_CB_HC))->SetCheck(TRUE);
            }
        }
    }
    else
    {
        int dwErr = SADP_GetLastError();
        char szTemp[100] = { 0 };
        sprintf(szTemp, "SADP_GET_PASSWORD_RESET_TYPE failed! error:%d", dwErr);
        AfxMessageBox(szTemp);
    }
}
