//// EzvizUnbindDelUser.cpp : 实现文件
////
//
#include "stdafx.h"
//#include "sadpdlg.h"
//#include "EzvizUnbindDelUser.h"
//#include "afxdialogex.h"
//
//
//// CEzvizUnbindDelUser 对话框
//
//IMPLEMENT_DYNAMIC(CEzvizUnbindDelUser, CDialogEx)
//
//CEzvizUnbindDelUser::CEzvizUnbindDelUser(CWnd* pParent /*=NULL*/)
//	: CDialogEx(CEzvizUnbindDelUser::IDD, pParent)
//{
//    m_Edit_Input_Str = _T("");
//}
//
//CEzvizUnbindDelUser::~CEzvizUnbindDelUser()
//{
//}
//
//void CEzvizUnbindDelUser::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//    DDX_Text(pDX, IDC_EDIT_INPUT_STRING2, m_Edit_Input_Str);
//}
//
//
//BEGIN_MESSAGE_MAP(CEzvizUnbindDelUser, CDialogEx)
//    ON_BN_CLICKED(IDC_BTN_EXPORT_FILE2, &CEzvizUnbindDelUser::OnBnClickedBtnExportFile2)
//    ON_BN_CLICKED(IDC_BTN_UNBIND_DEL_USER, &CEzvizUnbindDelUser::OnBnClickedBtnUnbindDelUser)
//END_MESSAGE_MAP()
//
//
//// CEzvizUnbindDelUser 消息处理程序
//
//void CEzvizUnbindDelUser::OnBnClickedBtnExportFile2()
//{
//    // TODO:  在此添加控件通知处理程序代码
//    // TODO: Add your control notification handler code here
//
//    //1. get device code
//    DWORD dwRetLen = 0;
//    int  iRet = 0;
//    SADP_ENCRYPT_STRING struEncryptString = { 0 };
//
//    iRet = SADP_GetDeviceConfig(m_strDevSerialNo.GetBuffer(0), SADP_GET_ENCRYPT_STRING, NULL, 0, &struEncryptString, sizeof(struEncryptString));
//    if (iRet == 0)
//    {
//        int iError = SADP_GetLastError();
//        char szTemp[100] = { 0 };
//        if (iError == SADP_NOT_ACTIVATED)
//        {
//            AfxMessageBox("Get device code failed, device was not activated!");
//        }
//        else if (iError == SADP_TIMEOUT)
//        {
//            AfxMessageBox("Get device code failed, timeout!");
//        }
//        else if (iError == SADP_DEVICE_DENY)
//        {
//            AfxMessageBox("Get device code failed!");
//        }
//        else
//        {
//            sprintf(szTemp, "Get device code failed, Error code%d", iError);
//            AfxMessageBox(szTemp);
//        }
//        return;
//    }
//
//    //Open file,read infomation
//    char szDeviceCode[256] = { 0 };
//    char szTempComtent[512] = { 0 };
//    char  exepath[MAX_PATH];
//    CString tmpdir;
//    memset(exepath, 0, MAX_PATH);
//    GetModuleFileName(NULL, exepath, MAX_PATH);
//    tmpdir = exepath;
//    CString strdir = tmpdir.Left(tmpdir.ReverseFind('\\'));
//
//    sprintf((char*)szDeviceCode, "%s%s", strdir, "\\DeviceKey.xml");
//    FILE *pFile = fopen(szDeviceCode, "wb");
//    if (NULL == pFile)
//    {
//        AfxMessageBox("Open File failed");
//        return;
//    }
//
//    int iWriteData = 0;
//    iWriteData = fwrite(struEncryptString.szEncryptString, sizeof(BYTE), strlen(struEncryptString.szEncryptString), pFile);
//    if (0 == iWriteData)
//    {
//        AfxMessageBox("Write 0 Byte Data");
//        return;
//    }
//    if (NULL != pFile)
//    {
//        fclose(pFile);
//        pFile = NULL;
//    }
//    AfxMessageBox("Export file successfully!");
//}
//
//
//void CEzvizUnbindDelUser::OnBnClickedBtnUnbindDelUser()
//{
//    // TODO:  在此添加控件通知处理程序代码
//    UpdateData(TRUE);
//
//    SADP_EZVIZ_UNBIND_DEL_USER_PARAM struEzvizUnbindDelUserParam = { 0 };
//    SADP_DEV_LOCK_INFO struLockInfo = { 0 };
//
//    if (0 == strcmp(m_Edit_Input_Str, ""))
//    {
//        AfxMessageBox("请输入字符!");
//        return;
//    }
//    memcpy(struEzvizUnbindDelUserParam.szCode, m_Edit_Input_Str.GetBuffer(0), strlen(m_Edit_Input_Str));
//    struEzvizUnbindDelUserParam.dwSize = sizeof(struEzvizUnbindDelUserParam);
//
//    int iRet = SADP_SetDeviceConfig(m_strDevSerialNo, SADP_EZVIZ_UNBIND_DEL_USER, &struEzvizUnbindDelUserParam, sizeof(struEzvizUnbindDelUserParam), &struLockInfo, sizeof(struLockInfo));
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
//}
