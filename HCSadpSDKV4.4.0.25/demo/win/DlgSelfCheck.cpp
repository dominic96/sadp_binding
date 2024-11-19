// DlgSelfCheck.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgSelfCheck.h"
#include "afxdialogex.h"
#include "DlgHikSadp.h"


// CDlgSelfCheck 对话框

IMPLEMENT_DYNAMIC(CDlgSelfCheck, CDialog)

CDlgSelfCheck::CDlgSelfCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelfCheck::IDD, pParent)
{
    m_strDevID = "";
    m_strDevMAC = "";
    m_iTotalDisk = -1;
    m_iGoodDisk = -1;
    m_csCPU = _T("");
    m_csMemory = _T("");
    m_iProgress = 0;
    m_iTotalNetworkPort = -1;
    m_iConnectNetworkPort = -1;
}

BOOL CDlgSelfCheck::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbTemperatureState.SetCurSel(0);
    m_cmbFanState.SetCurSel(0);
    m_cmbPowerState.SetCurSel(0);
    m_cmbSASConnectState.SetCurSel(0);

    return TRUE;
}

CDlgSelfCheck::~CDlgSelfCheck()
{
}

void CDlgSelfCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_TOTAL_DISK, m_iTotalDisk);
    DDX_Text(pDX, IDC_EDIT_GOOD_DISK, m_iGoodDisk);
    DDX_Text(pDX, IDC_EDIT_CPU, m_csCPU);
    DDX_Text(pDX, IDC_EDIT_MEMORY, m_csMemory);
    DDX_Text(pDX, IDC_EDIT_PROGRESS, m_iProgress);
    DDX_Control(pDX, IDC_COM_TEMPERATURE_STATE, m_cmbTemperatureState);
    DDX_Control(pDX, IDC_COM_FAN_STATE, m_cmbFanState);
    DDX_Control(pDX, IDC_COM_POWER_STATE, m_cmbPowerState);
    DDX_Control(pDX, IDC_COM_SAS_CONNECT_STATE, m_cmbSASConnectState);
    DDX_Text(pDX, IDC_EDIT_TOTAL_NETWORK_PORT, m_iTotalNetworkPort);
    DDX_Text(pDX, IDC_EDIT_CONNECT_NETWORK_PORT, m_iConnectNetworkPort);
}


BEGIN_MESSAGE_MAP(CDlgSelfCheck, CDialog)
    ON_BN_CLICKED(IDC_BTN_CHECK, &CDlgSelfCheck::OnBnClickedBtnCheck)
    ON_BN_CLICKED(IDC_BTN_CHECK_BY_MAC, &CDlgSelfCheck::OnBnClickedBtnCheckByMac)
END_MESSAGE_MAP()


// CDlgSelfCheck 消息处理程序


void CDlgSelfCheck::OnBnClickedBtnCheck()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    SADP_SELF_CHECK_STATE struSelfCheckState = { 0 };
    struSelfCheckState.dwSize = sizeof(struSelfCheckState);
    if (!SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_SELF_CHECK, NULL, 0, &struSelfCheckState, sizeof(struSelfCheckState)))
    {
        int iError = SADP_GetLastError();
        char szTemp[128] = { 0 };
        sprintf(szTemp, "SADP_GET_SELF_CHECK fail err %d!", iError);
        AfxMessageBox(szTemp);
    }
    else
    {
        m_iTotalDisk = struSelfCheckState.dwTotalDisk;
        m_iGoodDisk = struSelfCheckState.dwGoodDisk;
        m_csCPU = struSelfCheckState.szCPU;
        m_csMemory = struSelfCheckState.szMemory;
        m_iProgress = struSelfCheckState.byProgress;
        m_cmbTemperatureState.SetCurSel(struSelfCheckState.byTemperatureState);
        m_cmbFanState.SetCurSel(struSelfCheckState.byFanState);
        m_cmbPowerState.SetCurSel(struSelfCheckState.byPowerState);
        m_cmbSASConnectState.SetCurSel(struSelfCheckState.bySASConnectState);
        m_iTotalNetworkPort = struSelfCheckState.byTotalNetworkPort;
        m_iConnectNetworkPort = struSelfCheckState.byConnectNetworkPort;
        AfxMessageBox("SADP_GET_SELF_CHECK Success!");
    }

    UpdateData(FALSE);
}


void CDlgSelfCheck::OnBnClickedBtnCheckByMac()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    SADP_SELF_CHECK_STATE struSelfCheckState = { 0 };
    struSelfCheckState.dwSize = sizeof(struSelfCheckState);
    if (!SADP_GetDeviceConfigByMAC(m_strDevMAC.GetBuffer(0), SADP_GET_SELF_CHECK, NULL, 0, &struSelfCheckState, sizeof(struSelfCheckState)))
    {
        int iError = SADP_GetLastError();
        char szTemp[128] = { 0 };
        sprintf(szTemp, "SADP_GET_SELF_CHECK fail err %d!", iError);
        AfxMessageBox(szTemp);
    }
    else
    {
        m_iTotalDisk = struSelfCheckState.dwTotalDisk;
        m_iGoodDisk = struSelfCheckState.dwGoodDisk;
        m_csCPU = struSelfCheckState.szCPU;
        m_csMemory = struSelfCheckState.szMemory;
        m_iProgress = struSelfCheckState.byProgress;
        m_cmbTemperatureState.SetCurSel(struSelfCheckState.byTemperatureState);
        m_cmbFanState.SetCurSel(struSelfCheckState.byFanState);
        m_cmbPowerState.SetCurSel(struSelfCheckState.byPowerState);
        m_cmbSASConnectState.SetCurSel(struSelfCheckState.bySASConnectState);
        m_iTotalNetworkPort = struSelfCheckState.byTotalNetworkPort;
        m_iConnectNetworkPort = struSelfCheckState.byConnectNetworkPort;
        AfxMessageBox("SADP_GET_SELF_CHECK Success!");
    }

    UpdateData(FALSE);
}
