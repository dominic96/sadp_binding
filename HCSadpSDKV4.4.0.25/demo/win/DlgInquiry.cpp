// DlgInquiry.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgInquiry.h"
#include "afxdialogex.h"


// DlgInquiry 对话框

IMPLEMENT_DYNAMIC(DlgInquiry, CDialog)

DlgInquiry::DlgInquiry(CWnd* pParent /*=NULL*/)
	: CDialog(DlgInquiry::IDD, pParent)
{

}

DlgInquiry::~DlgInquiry()
{
}

void DlgInquiry::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_IPADDRESS_START_IP, m_StartIP);
    DDX_Control(pDX, IDC_IPADDRESS_STOP_IP, m_StopIP);
}


BEGIN_MESSAGE_MAP(DlgInquiry, CDialog)
    ON_BN_CLICKED(IDC_BTN_SEARCH, &DlgInquiry::OnBnClickedBtnSearch)
END_MESSAGE_MAP()


// DlgInquiry 消息处理程序


void DlgInquiry::OnBnClickedBtnSearch()
{
    // TODO:  在此添加控件通知处理程序代码
    CString startIP, stopIP;
    BYTE nfield0, nfield1, nfield2, nfield3;

    m_StartIP.GetAddress(nfield0, nfield1, nfield2, nfield3);
    //nfield0 = 10;
    //nfield1 = 8;
    //nfield2 = 99;
    //nfield3 = 1;
    startIP.Format("%d.%d.%d.%d", nfield0, nfield1, nfield2, nfield3);

    m_StopIP.GetAddress(nfield0, nfield1, nfield2, nfield3);
    //nfield0 = 10;
    //nfield1 = 8;
    //nfield2 = 99;
    //nfield3 = 253;
    stopIP.Format("%d.%d.%d.%d", nfield0, nfield1, nfield2, nfield3);

    SADP_SUBNET_INFO struSubnet = { 0 };
    struSubnet.dwSize = sizeof(SADP_SUBNET_INFO);
    struSubnet.byIPType = 0;
    strcpy(struSubnet.szStartSubnetIP, startIP);
    strcpy(struSubnet.szStopSubnetIP, stopIP);
    
    int ret = SADP_InquirySpecificSubnet(&struSubnet);
    if (ret == 0)
    {
        DWORD dwError = SADP_GetLastError();
        char strTemp[100];
        sprintf(strTemp, "SADP_InquirySpecificSubnet failed ,Error Number:%d", dwError);
        AfxMessageBox(strTemp);
    } 
    else
    {
    }
}
