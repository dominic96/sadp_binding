// EzvizUnbind.cpp : 实现文件
//

#include "stdafx.h"
//#include "sadpdlg.h"
//#include "EzvizUnbind.h"
//#include "afxdialogex.h"
//
//
//// CEzvizUnbind 对话框
//
//IMPLEMENT_DYNAMIC(CEzvizUnbind, CDialogEx)
//
//CEzvizUnbind::CEzvizUnbind(CWnd* pParent /*=NULL*/)
//	: CDialogEx(CEzvizUnbind::IDD, pParent)
//{
//
//}
//
//CEzvizUnbind::~CEzvizUnbind()
//{
//}
//
//void CEzvizUnbind::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//}
//
//
//BEGIN_MESSAGE_MAP(CEzvizUnbind, CDialogEx)
//    ON_BN_CLICKED(IDC_BTN_GETSTATUS, &CEzvizUnbind::OnBnClickedBtnGetstatus)
//    ON_BN_CLICKED(IDC_BUTTON_UNBIND, &CEzvizUnbind::OnBnClickedButtonUnbind)
//END_MESSAGE_MAP()
//
//
//// CEzvizUnbind 消息处理程序
//
//
//void CEzvizUnbind::OnBnClickedBtnGetstatus()
//{
//    // TODO:  在此添加控件通知处理程序代码
//
//    SADP_EZVIZ_UNBIND_STATUS struEzvizUnbindStatus = { 0 };
//
//
//    int iRet = SADP_GetDeviceConfig(m_strDevSerialNo, SADP_GET_EZVIZ_UNBIND_STATUS, NULL, 0, &struEzvizUnbindStatus, sizeof(struEzvizUnbindStatus));
//    if (iRet == 0)
//    {
//        int iError = SADP_GetLastError();
//        char szTemp[100] = { 0 };
//        if (iError == SADP_NOT_ACTIVATED)
//        {
//            AfxMessageBox("GET_EZVIZ_UNBIND_STATUS failed, device was not activated!");
//        }
//        else if (iError == SADP_TIMEOUT)
//        {
//            AfxMessageBox("GET_EZVIZ_UNBIND_STATUS failed, timeout!");
//        }
//        else if (iError == SADP_DEVICE_DENY)
//        {
//            AfxMessageBox("GET_EZVIZ_UNBIND_STATUS failed, device deny!");
//        }
//        else
//        {
//            sprintf(szTemp, "GET_EZVIZ_UNBIND_STATUS failed, Error code%d", iError);
//            AfxMessageBox(szTemp);
//        }
//        return;
//    }
//
//    switch (struEzvizUnbindStatus.byResult)
//    {
//    case 1:
//        AfxMessageBox("设备当前可以解绑");
//        break;
//    case 2:
//        AfxMessageBox("没有绑定萤石账号");
//        break;
//    case 3:
//        AfxMessageBox("没有开启萤石云功能");
//        break;
//    case 4:
//        AfxMessageBox("萤石云状态为离线");
//        break;
//    default:
//        break;
//    }
//}
//
//
//void CEzvizUnbind::OnBnClickedButtonUnbind()
//{
//    // TODO:  在此添加控件通知处理程序代码
//    UpdateData(TRUE);
//    char TempPasswd[32] = { 0 };
//    GetDlgItemText(IDC_EDIT_PASSWORD, TempPasswd, 32);
//
//    if (strcmp(TempPasswd, "") == 0)
//    {
//        AfxMessageBox("Please enter password!");
//        return;
//    }
//
//    int iPassWordLength = strlen(TempPasswd);
//    if (iPassWordLength > 16)
//    {
//        AfxMessageBox("Please enter a password less than 16 bit.");
//        return;
//    }
//
//    SADP_EZVIZ_UNBIND_PARAM struEzvizUnbindParam = { 0 };
//    memcpy(struEzvizUnbindParam.szPassword, TempPasswd, 16);
//
//    SADP_DEV_LOCK_INFO struLockInfo = { 0 };
//
//    int iRet = SADP_SetDeviceConfig(m_strDevSerialNo, SADP_EZVIZ_UNBIND, &struEzvizUnbindParam, sizeof(struEzvizUnbindParam), &struLockInfo, sizeof(struLockInfo));
//    if (iRet == 0)
//    {
//        int iError = SADP_GetLastError();
//        char szTemp[100] = { 0 };
//        if (iError == SADP_PASSWORD_ERROR)
//        {
//            sprintf(szTemp, "SADP_EZVIZ_UNBIND failed, password error   RetryTime:%d", struLockInfo.byRetryTime);
//            AfxMessageBox(szTemp);
//        }
//        if (iError == SADP_LOCKED)
//        {
//            sprintf(szTemp, "SADP_EZVIZ_UNBIND failed, Locked   LockTime:%d", struLockInfo.bySurplusLockTime);
//            AfxMessageBox(szTemp);
//        }
//        else if (iError == SADP_TIMEOUT)
//        {
//            AfxMessageBox("SADP_EZVIZ_UNBIND failed, timeout!");
//        }
//        else if (iError == SADP_DEVICE_DENY)
//        {
//            AfxMessageBox("SADP_EZVIZ_UNBIND failed, device deny!");
//        }
//        else
//        {
//            sprintf(szTemp, "SADP_EZVIZ_UNBIND failed, Error code%d", iError);
//            AfxMessageBox(szTemp);
//        }
//        return;
//    }
//
//    AfxMessageBox("SADP_EZVIZ_UNBIND success");
//
//}
