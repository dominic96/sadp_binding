// DlgResetPWGUID.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgResetPWGUID.h"
#include "afxdialogex.h"


// CDlgResetPWGUID 对话框

IMPLEMENT_DYNAMIC(CDlgResetPWGUID, CDialogEx)

CDlgResetPWGUID::CDlgResetPWGUID(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgResetPWGUID::IDD, pParent)
	, m_csInputPassword(_T(""))
	, m_bSycnIPCPW2(FALSE)
{

}

CDlgResetPWGUID::~CDlgResetPWGUID()
{
}

void CDlgResetPWGUID::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_csInputPassword);
	DDX_Check(pDX, IDC_CHECK_SYNC, m_bSycnIPCPW2);
}


BEGIN_MESSAGE_MAP(CDlgResetPWGUID, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgResetPWGUID::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CDlgResetPWGUID::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_RESET2, &CDlgResetPWGUID::OnBnClickedButtonReset2)
END_MESSAGE_MAP()


// CDlgResetPWGUID 消息处理程序


void CDlgResetPWGUID::OnBnClickedButtonExport()
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


void CDlgResetPWGUID::GetPath()
{
	char  exepath[MAX_PATH];
	CString tmpdir;
	memset(exepath, 0, MAX_PATH);
	GetModuleFileName(NULL, exepath, MAX_PATH);
	tmpdir = exepath;
	m_strdir = tmpdir.Left(tmpdir.ReverseFind('\\'));
}

void CDlgResetPWGUID::OnBnClickedButtonImport()
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


void CDlgResetPWGUID::OnBnClickedButtonReset2()
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
