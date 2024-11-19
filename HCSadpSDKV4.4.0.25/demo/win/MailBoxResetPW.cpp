// MailBoxResetPW.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "MailBoxResetPW.h"
#include "afxdialogex.h"
#include "DlgHikSadp.h"
#include "QrCodes.h"

// CMailBoxResetPW 对话框

IMPLEMENT_DYNAMIC(CMailBoxResetPW, CDialog)

CMailBoxResetPW::CMailBoxResetPW(CWnd* pParent /*=NULL*/)
	: CDialog(CMailBoxResetPW::IDD, pParent)
 , m_strMailBox(_T("XXX@hikvision.com"))
 , m_strPassword(_T(""))
 , m_strQrCodes(_T(""))
 , m_strResetPassWord(_T(""))
 , m_strSafeCode(_T(""))
{
    m_strDevID = "";
    m_bSycnIPCPW = FALSE;
    m_bMailBoxResetPW = FALSE;
}

CMailBoxResetPW::~CMailBoxResetPW()
{
}

void CMailBoxResetPW::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_MAIL_BOX_ADDR, m_strMailBox);
    DDV_MaxChars(pDX, m_strMailBox, 128);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
    DDX_Text(pDX, IDC_EDIT_QR_CODES, m_strQrCodes);
    DDV_MaxChars(pDX, m_strQrCodes, 128);
    DDX_Text(pDX, IDC_EDIT_MAIL_BOX_ADDR, m_strMailBox);
    DDX_Text(pDX, IDC_EDIT_RESET_PASSWORD, m_strResetPassWord);
    DDV_MaxChars(pDX, m_strResetPassWord, 16);
    DDX_Text(pDX, IDC_EDIT_SAFE_CODE, m_strSafeCode);
	DDV_MaxChars(pDX, m_strSafeCode, 256);
}


BEGIN_MESSAGE_MAP(CMailBoxResetPW, CDialog)
    ON_BN_CLICKED(ID_SET_MAIL_BOX, &CMailBoxResetPW::OnBnClickedSetMailBox)
    ON_BN_CLICKED(IDC_EXPORT_QR_CODES, &CMailBoxResetPW::OnBnClickedExportQrCodes)
    ON_BN_CLICKED(IDC_RESET_PASSWORD, &CMailBoxResetPW::OnBnClickedResetPassword)
END_MESSAGE_MAP()


// CMailBoxResetPW 消息处理程序


void CMailBoxResetPW::OnBnClickedSetMailBox()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);   
    if (!m_bMailBoxResetPW)
    {
        AfxMessageBox("SADP_SET_USER_MAILBOX  does not support");
        return;
    }
    SADP_DEV_LOCK_INFO struDevLockInfo = { 0 };
    SADP_USER_MAILBOX struMailBoxParam = { 0 };
    struMailBoxParam.dwSize = sizeof(struMailBoxParam);
    memcpy(struMailBoxParam.szMailBoxAddr, m_strMailBox.GetBuffer(0), m_strMailBox.GetLength());
    memcpy(struMailBoxParam.szPassword, m_strPassword.GetBuffer(0), m_strPassword.GetLength());

    if (SADP_SetDeviceConfig(m_strDevID.GetBuffer(0), SADP_SET_USER_MAILBOX,
        &struMailBoxParam, sizeof(struMailBoxParam), &struDevLockInfo, sizeof(struDevLockInfo)))
    {
        AfxMessageBox("SADP_SET_USER_MAILBOX success");
    }
    else
    {
        DWORD dwError = SADP_GetLastError();
        char szTemp[128] = { 0 };

        if (dwError == SADP_TIMEOUT)
        {
            AfxMessageBox("Set MailBox failed: Time out!");
        }
        else if (dwError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Set MailBox  failed!");
        }
        else if (dwError == SADP_LOCKED)
        {
            sprintf(szTemp, "Device Lock，Lock %d minute.", struDevLockInfo.bySurplusLockTime);
            AfxMessageBox(szTemp);
        }
        else if (dwError == SADP_PASSWORD_ERROR)
        {
            sprintf(szTemp, "Password error，%d time you can try.", struDevLockInfo.byRetryTime);
            AfxMessageBox(szTemp);
        }
        else if (dwError == SADP_NOT_ACTIVATED)
        {
            AfxMessageBox("dev has not Activate");
        }
        else
        {
            sprintf(szTemp, "SetMailBox failed!,Error Number%d", dwError);
            AfxMessageBox(szTemp);
        }
    }
}


void CMailBoxResetPW::OnBnClickedExportQrCodes()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (FALSE == m_bMailBoxResetPW)
    {
        AfxMessageBox("device does not support mailbox reset password!");
        //return;
    }
    CString csFileName = "";
    CString csFileNameXml = "";
    CString csFileDirectory = "";
    CString csTmp = "";
    CString csTmpQrCodes = "";
    CString csTmpMailBox = "";
    CString csTmpServiceMailBox = "";

    csFileDirectory = "c:\\QrCodes";
    if (!CreateDirectory(csFileDirectory, NULL))
    {
        TRACE("CreateDirectory Fail");
    }
    SYSTEMTIME t;
    GetLocalTime(&t);
    csTmp.Format("%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    csFileName = csFileDirectory + "\\" + "MailQrCodes"+ csTmp  + ".bmp";
    csFileNameXml = csFileDirectory + "\\" + "MailQrCodes" + csTmp + ".xml";

    SADP_QR_CODES_V31 struQrCodes = { 0 };
    if (SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_QR_CODES_V31, NULL, 0, &struQrCodes, sizeof(struQrCodes)))
    {
        FILE *m_pFile = fopen(csFileNameXml, "wb");
        if (NULL == m_pFile)
        {
            AfxMessageBox("Open File failed");
            return;
        }
        int iWriteData = fwrite(struQrCodes.szQrCodes, sizeof(BYTE), strlen(struQrCodes.szQrCodes), m_pFile);
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

        csTmpQrCodes.Format("%s", struQrCodes.szQrCodes);
        CQrcode *qrcode = CQrcode::getMinimumQRCode(csTmpQrCodes, ErrorCorrectLevel_L);
        qrcode->SaveToBmp(csFileName, 4, 4);
        delete qrcode;

        m_strQrCodes = csFileName;

        char szTemp[512] = { 0 };
        csTmpMailBox.Format("%s", struQrCodes.szMailBoxAddr);
        csTmpServiceMailBox.Format("%s", struQrCodes.szServiceMailBoxAddr);
        sprintf(szTemp, "SUCCESS;MailBox[%s],MailServiceBox[%s]", csTmpMailBox, csTmpServiceMailBox);       
        UpdateData(FALSE);
        AfxMessageBox(szTemp);
    }
    else
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        sprintf(szTemp, "Get Qr Code failed, Error code%d", iError);
        AfxMessageBox(szTemp);
        return;
    }
}


void CMailBoxResetPW::OnBnClickedResetPassword()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (FALSE == m_bMailBoxResetPW)
    {
        AfxMessageBox("device does not support mailbox reset password!");
        //return;
    }
    if (m_strResetPassWord == "")
    {
        AfxMessageBox("input reset password!");
        return;
    }
    if (m_strResetPassWord.GetLength() > 16)
    {
        AfxMessageBox("password is too long!");
        return;
    }

    SADP_RESET_PARAM_V50 struResetParamV50 = { 0 };
    struResetParamV50.dwSize = sizeof(struResetParamV50);
    struResetParamV50.byResetType = 6;
    memcpy(struResetParamV50.szPassword, m_strResetPassWord.GetBuffer(0), m_strResetPassWord.GetLength());
    memcpy(struResetParamV50.szCode, m_strSafeCode.GetBuffer(0), m_strSafeCode.GetLength());

    SADP_DEV_LOCK_INFO struDevLockInfo = { 0 };

    int iRet = SADP_ResetPasswd_V50(m_strDevID.GetBuffer(0), &struResetParamV50, &struDevLockInfo);
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        if (iError == SADP_TIMEOUT)
        {
            AfxMessageBox("MailBox reset password failed, timeout!");
        }
        else if (iError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("MailBox reset password failed, device deny!");
        }
        else if (iError == SADP_LOCKED)
        {
            sprintf(szTemp, "MailBox reset password failed, device locked，lock time:[%d]!", struDevLockInfo.bySurplusLockTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_RISK_PASSWORD)
        {
            AfxMessageBox("MailBox reset password failed, risk password!");
        }
        else if (iError == SADP_NOT_ACTIVATED)
        {
            AfxMessageBox("MailBox reset password failed, device not activated!");
        }
		//[add] <2019/01/11> by yangzhengh 
		else if (iError == SADP_MAILBOX_NOT_SET)
		{
			AfxMessageBox("MailBox reset password failed, mailbox is null!");
		}
        else
        {
            sprintf(szTemp, "MailBox reset password failed, Error code%d", iError);
            AfxMessageBox(szTemp);
        }
        return;
    }

    UpdateData(FALSE);
    AfxMessageBox("MailBox question reset password successfully!");
}
