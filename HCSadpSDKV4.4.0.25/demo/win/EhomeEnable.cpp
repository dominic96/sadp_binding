// EhomeEnable.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "EhomeEnable.h"
#include "afxdialogex.h"
#include "DlgHikSadp.h"


// CEhomeEnable 对话框

IMPLEMENT_DYNAMIC(CEhomeEnable, CDialog)

CEhomeEnable::CEhomeEnable(CWnd* pParent /*=NULL*/)
	: CDialog(CEhomeEnable::IDD, pParent)
    , m_strDevID(_T(""))
    , m_strEhomeKey(_T(""))
    , m_strPassword(_T(""))
{

}

CEhomeEnable::~CEhomeEnable()
{
}

void CEhomeEnable::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_DEV_ID, m_strDevID);
    DDX_Text(pDX, IDC_EDIT_EHOME_KEY, m_strEhomeKey);
    DDX_Text(pDX, IDC_EDIT_EHOME_ENABLE_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CEhomeEnable, CDialog)
    ON_BN_CLICKED(IDC_BTN_ENABLE, &CEhomeEnable::OnBnClickedBtnEnable)
END_MESSAGE_MAP()


// CEhomeEnable 消息处理程序


void CEhomeEnable::OnBnClickedBtnEnable()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    SADP_DEV_LOCK_INFO struDevLockInfo = { 0 };
    SADP_EHOME_ENABLE_PARAM struEhomeEnableParam = { 0 };
    struEhomeEnableParam.dwSize = sizeof(struEhomeEnableParam);
    memcpy(struEhomeEnableParam.szDevID, m_strDevID.GetBuffer(0), m_strDevID.GetLength());
    memcpy(struEhomeEnableParam.szEhomeKey, m_strEhomeKey.GetBuffer(0), m_strEhomeKey.GetLength());
    memcpy(struEhomeEnableParam.szPassword, m_strPassword.GetBuffer(0), m_strPassword.GetLength());

    if (SADP_SetDeviceConfig(m_strDevSerialNo.GetBuffer(0), SADP_EHOME_ENABLE,
        &struEhomeEnableParam, sizeof(struEhomeEnableParam), &struDevLockInfo, sizeof(struDevLockInfo)))
    {
        AfxMessageBox("SADP_EHOME_ENABLE success");
    }
    else
    {
        DWORD dwError = SADP_GetLastError();
        char szTemp[128] = { 0 };

        if (dwError == SADP_TIMEOUT)
        {
            AfxMessageBox("Set Ehome enable failed: Time out!");
        }
        else if (dwError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Set Ehome enable  failed!");
        }
        else if (dwError == SADP_LOCKED)
        {
            sprintf(szTemp, "Device Lock，Lock %d minute.", struDevLockInfo.bySurplusLockTime);
            AfxMessageBox(szTemp);
        }
        else if (dwError == SADP_PASSWORD_ERROR)
        {
            sprintf(szTemp, "Password error，%d tiem you can try.", struDevLockInfo.byRetryTime);
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
}
