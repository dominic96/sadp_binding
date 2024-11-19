// BindDev.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "BindDev.h"
#include "afxdialogex.h"


// CBindDev 对话框

IMPLEMENT_DYNAMIC(CBindDev, CDialog)

CBindDev::CBindDev(CWnd* pParent /*=NULL*/)
	: CDialog(CBindDev::IDD, pParent)
    , m_bUnBindAll(FALSE)
    , m_csPassword(_T(""))
{
    m_strDevID = _T("");
    m_bUnBindAll = FALSE;
    m_bSupportBind = FALSE;
    for (int i = 0; i < 15; ++i)
    {
        m_strSerial[i] = _T("");
    }
    memset(&m_bBind, 0, 15);
}

CBindDev::~CBindDev()
{
}

void CBindDev::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_UNBIND_ALL, m_bUnBindAll);
    DDX_Text(pDX, IDC_EDIT_SERIAL_1, m_strSerial[0]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_2, m_strSerial[1]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_3, m_strSerial[2]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_4, m_strSerial[3]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_5, m_strSerial[4]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_6, m_strSerial[5]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_7, m_strSerial[6]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_8, m_strSerial[7]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_9, m_strSerial[8]); 
    DDX_Text(pDX, IDC_EDIT_SERIAL_10, m_strSerial[9]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_11, m_strSerial[10]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_12, m_strSerial[11]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_13, m_strSerial[12]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_14, m_strSerial[13]);
    DDX_Text(pDX, IDC_EDIT_SERIAL_15, m_strSerial[14]);
    DDX_Check(pDX, IDC_SERIAL_1, m_bBind[0]);
    DDX_Check(pDX, IDC_SERIAL_2, m_bBind[1]);
    DDX_Check(pDX, IDC_SERIAL_3, m_bBind[2]);
    DDX_Check(pDX, IDC_SERIAL_4, m_bBind[3]);
    DDX_Check(pDX, IDC_SERIAL_5, m_bBind[4]);
    DDX_Check(pDX, IDC_SERIAL_6, m_bBind[5]);
    DDX_Check(pDX, IDC_SERIAL_7, m_bBind[6]);
    DDX_Check(pDX, IDC_SERIAL_8, m_bBind[7]);
    DDX_Check(pDX, IDC_SERIAL_9, m_bBind[8]);
    DDX_Check(pDX, IDC_SERIAL_10, m_bBind[9]);
    DDX_Check(pDX, IDC_SERIAL_11, m_bBind[10]);
    DDX_Check(pDX, IDC_SERIAL_12, m_bBind[11]);
    DDX_Check(pDX, IDC_SERIAL_13, m_bBind[12]);
    DDX_Check(pDX, IDC_SERIAL_14, m_bBind[13]);
    DDX_Check(pDX, IDC_SERIAL_15, m_bBind[14]);

    DDX_Text(pDX, IDC_EDIT_INPUT_PASSWORD2, m_csPassword);
}


BEGIN_MESSAGE_MAP(CBindDev, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_BIND_LIST, &CBindDev::OnBnClickedBtnGetBindList)
    ON_BN_CLICKED(IDC_BTN_SET_BIND_LIST, &CBindDev::OnBnClickedBtnSetBindList)
    ON_BN_CLICKED(IDC_BTN_CANCLE, &CBindDev::OnBnClickedBtnCancle)
END_MESSAGE_MAP()


// CBindDev 消息处理程序


/** @fn void CBindDev::OnBnClickedBtnGetBindList()
 *  @brief 获取列表
 *  @return void
 */
void CBindDev::OnBnClickedBtnGetBindList()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    /* if (FALSE == m_bSupportBind)
     {
     AfxMessageBox("设备不支持设备绑定!");
     return;
     }*/
    SADP_BIND_LIST struBindCfg = { 0 };
 
    int iRet = SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_BIND_LIST, NULL, 0, &struBindCfg, sizeof(struBindCfg));
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        if (iError == SADP_TIMEOUT)
        {
            AfxMessageBox("Get Bind List failed, timeout!");
        }
        else if (iError == SADP_NOT_ACTIVATED)
        {
            AfxMessageBox("Get Bind List failed, device not activate!");
        }
        else
        {
            sprintf(szTemp, "Get Bind List failed, Error code%d", iError);
            AfxMessageBox(szTemp);
        }
        return;
    }

    for (int i = 0; i < 15; i++)
    {
       if (struBindCfg.struBindInfo[i].byiBind)
       {

          m_strSerial[i] = struBindCfg.struBindInfo[i].szSerialNO;
          m_bBind[i] = TRUE;
       }
    }
    AfxMessageBox("Get security question successfully!");
    UpdateData(FALSE);
   
}


/** @fn void CBindDev::OnBnClickedBtnSetBindList()
 *  @brief 配置绑定列表
 *  @return void
 */
void CBindDev::OnBnClickedBtnSetBindList()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
   /* if (FALSE == m_bSupportBind)
    {
        AfxMessageBox("设备不支持设备绑定!");
        return;
    }*/
    if (m_csPassword == "")
    {
        AfxMessageBox("请先输入密码!");
        return;
    }
    if (m_csPassword.GetLength() > 16)
    {
        AfxMessageBox("密码长度超出范围!");
        return;
    }
    SADP_BIND_LIST struBindListCfg = { 0 };

    memcpy(struBindListCfg.szPassword, m_csPassword.GetBuffer(0), m_csPassword.GetLength());
    if (m_bUnBindAll)
    {
        struBindListCfg.byUnbindAll = TRUE;
    }
    else
    {
        for (int i = 0; i < 15; i++)
        {
            struBindListCfg.struBindInfo[i].byiBind = m_bBind[i];
            memcpy(struBindListCfg.struBindInfo[i].szSerialNO, m_strSerial[i].GetBuffer(0), SADP_MAX_SERIALNO_LEN);
        }
    }
    
    SADP_DEV_LOCK_INFO struLockInfo = { 0 };
    int iRet = SADP_SetDeviceConfig(m_strDevID.GetBuffer(0), SADP_SET_BIND_LIST, &struBindListCfg, sizeof(struBindListCfg), &struLockInfo, sizeof(struLockInfo));
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        if (iError == SADP_TIMEOUT)
        {
            AfxMessageBox("Set Bind List failed, timeout!");
        }
        else if (iError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Set Bind List failed, device deny!");
        }
        else if (iError == SADP_PASSWORD_ERROR)
        {
            sprintf(szTemp, "Set Bind List failed, password error, retry times:[%d]!", struLockInfo.byRetryTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_LOCKED)
        {
            sprintf(szTemp, "Set Bind List failed, device locked，lock time:[%d]!", struLockInfo.bySurplusLockTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_BIND_ERROR_DEV)
        {
            sprintf(szTemp, "Set Bind List failed, Bind Error Dev!");
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_EXTED_MAX_BIND_NUM)
        {
            sprintf(szTemp, "Set Bind List failed, Exted max bind num");
            AfxMessageBox(szTemp);
        }
        else
        {
            sprintf(szTemp, "Set Bind List failed, Error code%d", iError);
            AfxMessageBox(szTemp);
        }
        return;
    }

    UpdateData(FALSE);
    AfxMessageBox("Set Bind List successfully!");
}


void CBindDev::OnBnClickedBtnCancle()
{
    // TODO:  在此添加控件通知处理程序代码
    OnCancel();
}
