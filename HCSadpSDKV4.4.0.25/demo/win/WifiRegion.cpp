// WifiRegion.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "WifiRegion.h"
#include "afxdialogex.h"


// CWifiRegion �Ի���

IMPLEMENT_DYNAMIC(CWifiRegion, CDialog)

CWifiRegion::CWifiRegion(CWnd* pParent /*=NULL*/)
	: CDialog(CWifiRegion::IDD, pParent)
    , m_bEnhancement(FALSE)
    , m_bsupportEnhancement(FALSE)
    , m_szPassword(_T(""))
{

}

CWifiRegion::~CWifiRegion()
{
}

void CWifiRegion::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_REGION, m_cbRegion);
    DDX_Check(pDX, IDC_CHECK_WIFI_ENHANCEMENT, m_bEnhancement);
    DDX_Text(pDX, IDC_EDIT_PASS_WORD, m_szPassword);
}


BEGIN_MESSAGE_MAP(CWifiRegion, CDialog)
    ON_BN_CLICKED(IDOK, &CWifiRegion::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CWifiRegion::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWifiRegion ��Ϣ�������


void CWifiRegion::OnBnClickedOk()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CDialog::OnOK();
    UpdateData(TRUE);
    //
    SADP_WIFI_REGION_INFO struWifiRegion = { 0 };
    //���ؽṹ��
    SADP_DEV_LOCK_INFO struLockInfo = { 0 };
    if (m_szPassword == "")
    {
        AfxMessageBox("������������!");
        return;
    }
    if (m_bsupportEnhancement)
    {
        struWifiRegion.byMode = 2;
        struWifiRegion.byWifiEnhancementEnabled = m_bEnhancement;
    }
    else 
    {
        struWifiRegion.byMode = 1;
        struWifiRegion.byWifiRegion = m_cbRegion.GetCurSel();
    }
    memcpy(struWifiRegion.szPassword, m_szPassword.GetBuffer(), 16);
    //memcpy(struVerificationCode.szVerificationCode, m_strVerificationCode.GetBuffer(), SADP_MAX_VERIFICATION_CODE_LEN);

    int iRet = 0;

    iRet = SADP_SetDeviceConfig(m_strDevID.GetBuffer(), SADP_SET_WIFI_REGION, &struWifiRegion, sizeof(struWifiRegion),
        &struLockInfo, sizeof(struLockInfo));

    if (iRet == TRUE)
    {
        AfxMessageBox("SADP_SET_WIFI_REGION success");
    }
    else
    {
        DWORD dwError = SADP_GetLastError();
        char szTemp[128] = { 0 };

        if (dwError == SADP_TIMEOUT)
        {
            AfxMessageBox("Set wifi region failed: Time out!");
        }
        else if (dwError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Set wifi region  failed!");
        }
        else if (dwError == SADP_ILLEGAL_VERIFICATION_CODE)
        {
            AfxMessageBox("Set wifi region  failed: Illegal Verification Code!");
        }
        else if (dwError == SADP_LOCKED)
        {
            sprintf(szTemp, "Device Lock��Lock %d minute.", struLockInfo.bySurplusLockTime);
            AfxMessageBox(szTemp);
        }
        else if (dwError == SADP_PASSWORD_ERROR)
        {
            sprintf(szTemp, "Password error��%d tiem you can try.", struLockInfo.byRetryTime);
            AfxMessageBox(szTemp);
        }
        else if (dwError == SADP_NOT_ACTIVATED)
        {
            AfxMessageBox("dev has not Activate");
        }
        else
        {
            sprintf(szTemp, "Set wifi region  failed!,Error Number%d", dwError);
            AfxMessageBox(szTemp);
        }
    }
}


void CWifiRegion::OnBnClickedCancel()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CDialog::OnCancel();
}


BOOL CWifiRegion::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}
