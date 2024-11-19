// DlgResetPWPhone.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgResetPWPhone.h"
#include "afxdialogex.h"
#include "QrCodes.h"

// CDlgResetPWPhone 对话框

IMPLEMENT_DYNAMIC(CDlgResetPWPhone, CDialog)

CDlgResetPWPhone::CDlgResetPWPhone(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgResetPWPhone::IDD, pParent)
    , m_szCode(_T(""))
    , m_szPassword(_T(""))
{

}

CDlgResetPWPhone::~CDlgResetPWPhone()
{
}

void CDlgResetPWPhone::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_INPUT_STRING, m_szCode);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_szPassword);
}


BEGIN_MESSAGE_MAP(CDlgResetPWPhone, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgResetPWPhone::OnBnClickedButtonExport)
    ON_BN_CLICKED(IDC_BUTTON_RESET2, &CDlgResetPWPhone::OnBnClickedButtonReset2)
END_MESSAGE_MAP()


void CDlgResetPWPhone::GetPath()
{
    char  exepath[MAX_PATH];
    CString tmpdir;
    memset(exepath, 0, MAX_PATH);
    GetModuleFileName(NULL, exepath, MAX_PATH);
    tmpdir = exepath;
    m_strdir = tmpdir.Left(tmpdir.ReverseFind('\\'));
}

// CDlgResetPWPhone 消息处理程序


void CDlgResetPWPhone::OnBnClickedButtonExport()
{
    UpdateData(TRUE);
    CString csFileName = "";
    CString csFileNameXml = "";
    CString csFileDirectory = "";
    CString csTmp = "";
    CString csTmpQrCodes = "";
    CString csTmpDevModel = "";
    CString csTmpDomainName = "";

    csFileDirectory = "c:\\QrCodes";
    if (!CreateDirectory(csFileDirectory, NULL))
    {
        TRACE("CreateDirectory Fail");
    }
    SYSTEMTIME t;
    GetLocalTime(&t);
    csTmp.Format("%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    csFileName = csFileDirectory + "\\" + "PhoneQrCodes" + csTmp + ".bmp";
    csFileNameXml = csFileDirectory + "\\" + "PhoneQrCodes" + csTmp + ".xml";

    DWORD dwRetLen = 0;
    SADP_PHONE_QR_CODES struPhoneQrCode = { 0 };
    //memcpy(struPhoneQrCode.szQrCodes, "//8AADxjb2RlPg0KPGNtZD5QaG9uZU5vUmVzZXRfdjMxPC9jbWQ+DQo8UlNBVmVyc2lvbj4xMzwvUlNBVmVyc2lvbj4NCjxlbmNyeXB0ZWRTdHJpbmc+WS9Kc3FTbTZuMDZ6ZUltOERHRC9DU0ptcUpqSGFqRTU4WTZ1Wi9KSjdKOVhaM1NSMVVyYU8vbkQ0OUVES1FvMXRNWkNpcE9tMDFjblFSOGVRb0tlZ2VYUjhpb21ESTVzbTdRcVBZeTNWNURyRWZuSlNaN3lSQWZ4dytadUVrWnVjak04VkJ0a1FMbTBjS2ZKMktPMmI4VHdiRkVCMGcxTmdOWm01QmFHZjRYWHBrc1NmaFNaRWs1aEczYi93bGN5M1QzUGJHRVFjR2pmWk5qUjYybTZHeGZCekx5c1h6QVNPUmdzRVBRMHJFcFM2VHF1T0JYSmtSTHpQcm0rYi9qYUhLV0RNYmFSQXJvWHE3alFyeDBvWG13UWpPZjJTaWFKaUVLcDl5Wk9UZkVYRGlFN3VEYWo0b1BKR0lKNUdVbG5tckcrREQrRVJoUDluc2tURUp5UmJBPT08L2VuY3J5cHRlZFN0cmluZz4NCjwvY29kZT4NCg==", 1023);
    int iRet = SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_PHONE_QR_CODES, NULL, 0, &struPhoneQrCode, sizeof(SADP_PHONE_QR_CODES));
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

    FILE *m_pFile = fopen(csFileNameXml, "wb");
    if (NULL == m_pFile)
    {
        AfxMessageBox("Open File failed");
        return;
    }
    int iWriteData = fwrite(struPhoneQrCode.szQrCodes, sizeof(BYTE), strlen(struPhoneQrCode.szQrCodes), m_pFile);
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

    //上层应用拿到 域名，设备类型，二维码字符串，生成二维码
    csTmpQrCodes.Format("%s", struPhoneQrCode.szQrCodes);
    CQrcode *qrcode = CQrcode::getMinimumQRCode(csTmpQrCodes, ErrorCorrectLevel_L);
    qrcode->SaveToBmp(csFileName, 4, 4);
    delete qrcode;

    char szTemp[512] = { 0 };
    csTmpDevModel.Format("%s", struPhoneQrCode.szDevModel);
    csTmpDomainName.Format("%s", struPhoneQrCode.szDomainName);
    sprintf(szTemp, "SUCCESS; DevModel[%s], DomainName[%s], QrCode path[%s]", csTmpDevModel, csTmpDomainName, csFileName);
    AfxMessageBox(szTemp);
}


void CDlgResetPWPhone::OnBnClickedButtonReset2()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char *TempPasswd = { 0 };
    TempPasswd = m_szPassword.GetBuffer(0);
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
    struResetParamV50.byResetType = 7;
    memcpy(struResetParamV50.szPassword, TempPasswd, iPassWordLength);
    memcpy(struResetParamV50.szCode, m_szCode.GetBuffer(0), strlen(m_szCode));

    SADP_DEV_LOCK_INFO struDevLockInfo = { 0 };

    int iRet = SADP_ResetPasswd_V50(m_strDevID.GetBuffer(0), &struResetParamV50, &struDevLockInfo);
    //清空数据
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
