// Config.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "Config.h"
#include "afxdialogex.h"


// CConfig 对话框

IMPLEMENT_DYNAMIC(CConfig, CDialog)

CConfig::CConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CConfig::IDD, pParent)
    , m_szPassWord(_T(""))
    , m_szChannelDefaultPW(_T(""))
{

}

CConfig::~CConfig()
{
}

void CConfig::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PASS_WORD, m_szPassWord);
    DDV_MaxChars(pDX, m_szPassWord, 16);
    DDX_Text(pDX, IDC_EDIT_CHANNEL_DEFAULT_PW, m_szChannelDefaultPW);
	DDV_MaxChars(pDX, m_szChannelDefaultPW, 16);
}


BEGIN_MESSAGE_MAP(CConfig, CDialog)
    ON_BN_CLICKED(IDOK2, &CConfig::OnBnClickedOk2)
    ON_BN_CLICKED(IDCANCEL2, &CConfig::OnBnClickedCancel2)
END_MESSAGE_MAP()


// CConfig 消息处理程序


void CConfig::OnBnClickedOk2()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialog::OnOK();
    UpdateData(TRUE);
    if (!m_bySupportChannelDefaultPW)
    {
        AfxMessageBox("Device not support channel default Password!");
        return;
    }
    //
    SADP_CHANNEL_DEFAULT_PASSWORD struChannelDefaultPW = { 0 };
    //返回结构体
    SADP_DEV_LOCK_INFO struLockInfo = { 0 };
    if (m_szPassWord == "" || m_szChannelDefaultPW == "")
    {
        AfxMessageBox("Please input password first!");
        return;
    }

    memcpy(struChannelDefaultPW.szPassword, m_szPassWord.GetBuffer(), 16);
    memcpy(struChannelDefaultPW.szChannelDefaultPassword, m_szChannelDefaultPW.GetBuffer(), 16);
    //memcpy(struVerificationCode.szVerificationCode, m_strVerificationCode.GetBuffer(), SADP_MAX_VERIFICATION_CODE_LEN);

    int iRet = 0;

    iRet = SADP_SetDeviceConfig(m_strDevID.GetBuffer(), SADP_SET_CHANNEL_DEFAULT_PASSWORD, &struChannelDefaultPW, sizeof(struChannelDefaultPW),
        &struLockInfo, sizeof(struLockInfo));

    if (iRet == TRUE)
    {
        AfxMessageBox("SADP_SET_CHANNEL_DEFAULT_PASSWORD success");
    }
    else
    {
        DWORD dwError = SADP_GetLastError();
        char szTemp[128] = { 0 };

        if (dwError == SADP_TIMEOUT)
        {
            AfxMessageBox("SADP_SET_CHANNEL_DEFAULT_PASSWORD failed: Time out!");
        }
        else if (dwError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("SADP_SET_CHANNEL_DEFAULT_PASSWORD  failed!");
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
        else if (dwError == SADP_RISK_PASSWORD)
        {
            AfxMessageBox("risk Password");
        }
        else
        {
            sprintf(szTemp, "SADP_SET_CHANNEL_DEFAULT_PASSWORD  failed!,Error Number%d", dwError);
            AfxMessageBox(szTemp);
        }
    }
	UpdateData(FALSE);
}


void CConfig::OnBnClickedCancel2()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialog::OnCancel();
}
