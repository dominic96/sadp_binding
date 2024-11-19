// DlgCustom.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgCustom.h"
#include "afxdialogex.h"

// CDlgCustom 对话框

IMPLEMENT_DYNAMIC(CDlgCustom, CDialogEx)

CDlgCustom::CDlgCustom(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCustom::IDD, pParent)
    , m_sDeviceTypeUnlockCode(_T(""))
    , m_csDeviceTypeSecretKey(_T(""))
{

}

CDlgCustom::~CDlgCustom()
{
}

void CDlgCustom::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_DEV_UNLOCK_CODE, m_sDeviceTypeUnlockCode);
    DDX_Text(pDX, IDC_EDIT_SECRET_KEY, m_csDeviceTypeSecretKey);
}


BEGIN_MESSAGE_MAP(CDlgCustom, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgCustom::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDOK, &CDlgCustom::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCustom 消息处理程序


void CDlgCustom::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwRetLen = 0;
    int  iRet = 0;
    memset(&m_strTypeUnLockCode, 0, sizeof(m_strTypeUnLockCode));

    iRet = SADP_GetDeviceConfig(m_strDevID, SADP_GET_DEVICE_TYPE_UNLOCK_CODE, NULL, \
        0, &m_strTypeUnLockCode, sizeof(m_strTypeUnLockCode));
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        sprintf(szTemp, "Get device code failed, Error code%d", iError);
        AfxMessageBox(szTemp);
        return;
    }
    else
    {
        m_sDeviceTypeUnlockCode.Format("%s", m_strTypeUnLockCode.szDeviceTypeUnlockCode);
    }
    UpdateData(FALSE);
}

void CDlgCustom::OnBnClickedOk()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int  iRet = 0;
    char szTemp[100] = { 0 };
    memset(&m_strCustomDeviceType, 0, sizeof(m_strCustomDeviceType));

    m_strCustomDeviceType.dwCodeSize = sizeof(m_strCustomDeviceType);
    memcpy(m_strCustomDeviceType.szDeviceTypeSecretKey, m_csDeviceTypeSecretKey.GetBuffer(0), strlen(m_csDeviceTypeSecretKey));

    iRet = SADP_SetDeviceConfig(m_strDevID, SADP_SET_DEVICE_CUSTOM_TYPE, &m_strCustomDeviceType, sizeof(m_strCustomDeviceType), NULL, 0);
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        sprintf(szTemp, "Set device custom type failed, Error code%d", iError);
        AfxMessageBox(szTemp);
        return;
    }
    else
    {
        sprintf(szTemp, "Set device custom type Succ!");
        AfxMessageBox(szTemp);
        return;
    }
    UpdateData(FALSE);
}

