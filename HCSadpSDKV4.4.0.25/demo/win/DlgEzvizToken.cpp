// DlgEzvizToken.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgEzvizToken.h"
#include "afxdialogex.h"
#include "DlgHikSadp.h"


// CDlgEzvizToken 对话框

IMPLEMENT_DYNAMIC(CDlgEzvizToken, CDialog)

CDlgEzvizToken::CDlgEzvizToken(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEzvizToken::IDD, pParent)
    , m_strToken(_T(""))
    , m_strPassword(_T(""))
{

}

CDlgEzvizToken::~CDlgEzvizToken()
{
}

void CDlgEzvizToken::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_EZVIZ_TOKEN, m_editToken);
    DDX_Control(pDX, IDC_BTN_EZVIZ_TOKEN, m_btnSet);
    DDX_Control(pDX, IDC_EDIT_EZVIZ_TOKEN_PASSWORD, m_editPassword);
    DDX_Text(pDX, IDC_EDIT_EZVIZ_TOKEN, m_strToken);
    DDX_Text(pDX, IDC_EDIT_EZVIZ_TOKEN_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CDlgEzvizToken, CDialog)
    ON_BN_CLICKED(IDC_BTN_EZVIZ_TOKEN, &CDlgEzvizToken::OnBnClickedBtnEzvizToken)
END_MESSAGE_MAP()


// CDlgEzvizToken 消息处理程序


void CDlgEzvizToken::OnBnClickedBtnEzvizToken()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    SADP_DEV_LOCK_INFO struDevLockInfo = { 0 };
    SADP_EZVIZ_USER_TOKEN_PARAM struEzvizUserTokenParam = { 0 };
    struEzvizUserTokenParam.dwSize = sizeof(struEzvizUserTokenParam);
    memcpy(struEzvizUserTokenParam.szToken, m_strToken.GetBuffer(0), m_strToken.GetLength());
    memcpy(struEzvizUserTokenParam.szPassword, m_strPassword.GetBuffer(0), m_strPassword.GetLength());

    if (SADP_SetDeviceConfig(m_strDevID.GetBuffer(0), SADP_SET_EZVIZ_USER_TOKEN,
        &struEzvizUserTokenParam, sizeof(struEzvizUserTokenParam), &struDevLockInfo, sizeof(struDevLockInfo)))
    {
        AfxMessageBox("SADP_SET_EZVIZ_USER_TOKEN success");
    }
    else
    {
        DWORD dwError = SADP_GetLastError();
        char szTemp[128] = { 0 };

        if (dwError == SADP_TIMEOUT)
        {
            AfxMessageBox("Set token failed: Time out!");
        }
        else if (dwError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Set token failed!");
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
            sprintf(szTemp, "Set token failed!,Error Number%d", dwError);
            AfxMessageBox(szTemp);
        }
    }
}
