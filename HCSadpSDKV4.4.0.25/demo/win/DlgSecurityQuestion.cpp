// DlgSecurityQuestion.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgSecurityQuestion.h"
#include "afxdialogex.h"


// CDlgSecurityQuestion 对话框

IMPLEMENT_DYNAMIC(CDlgSecurityQuestion, CDialog)

CDlgSecurityQuestion::CDlgSecurityQuestion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSecurityQuestion::IDD, pParent)
{
    m_strDevID = _T("");
    memset(m_dwID, 0, sizeof(m_dwID));
    for (int i = 0; i < MAX_QUESTION_NUM; i++)
    {
        m_csAnswer[i] = _T("");
    }
    m_bSupportSecurityQuestion = FALSE;
    m_csPassword = _T("");
    m_bSyncIPCPW = 0;
    m_bSupportSycnIPCPW = FALSE;
}

BOOL CDlgSecurityQuestion::OnInitDialog()
{
    CDialog::OnInitDialog();

    for (int i = 0; i < MAX_QUESTION_NUM; i++)
    {
        m_cmbMark[i].SetCurSel(0);
    }

    GetDlgItem(IDC_SYNC_IPC_PW)->ShowWindow(SW_HIDE);
    if (m_bSupportSycnIPCPW)
    {
        GetDlgItem(IDC_SYNC_IPC_PW)->ShowWindow(SW_NORMAL);
    }
    
    return TRUE;
}

CDlgSecurityQuestion::~CDlgSecurityQuestion()
{
}

void CDlgSecurityQuestion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_ID1, m_dwID[0]);
    DDX_Text(pDX, IDC_EDIT_ID2, m_dwID[1]);
    DDX_Text(pDX, IDC_EDIT_ID3, m_dwID[2]);
    DDX_Text(pDX, IDC_EDIT_ID4, m_dwID[3]);
    DDX_Text(pDX, IDC_EDIT_ID5, m_dwID[4]);
    DDX_Text(pDX, IDC_EDIT_ID6, m_dwID[5]);
    DDX_Text(pDX, IDC_EDIT_ID7, m_dwID[6]);
    DDX_Text(pDX, IDC_EDIT_ID8, m_dwID[7]);
    DDX_Text(pDX, IDC_EDIT_ID9, m_dwID[8]);
    DDX_Text(pDX, IDC_EDIT_ID10, m_dwID[9]);
    DDX_Text(pDX, IDC_EDIT_ID11, m_dwID[10]);
    DDX_Text(pDX, IDC_EDIT_ID12, m_dwID[11]);
    DDX_Text(pDX, IDC_EDIT_ID13, m_dwID[12]);
    DDX_Text(pDX, IDC_EDIT_ID14, m_dwID[13]);
    DDX_Text(pDX, IDC_EDIT_ID15, m_dwID[14]);
    DDX_Text(pDX, IDC_EDIT_ID16, m_dwID[15]);
    DDX_Text(pDX, IDC_EDIT_ID17, m_dwID[16]);
    DDX_Text(pDX, IDC_EDIT_ID18, m_dwID[17]);
    DDX_Text(pDX, IDC_EDIT_ANSWER1, m_csAnswer[0]);
    DDX_Text(pDX, IDC_EDIT_ANSWER2, m_csAnswer[1]);
    DDX_Text(pDX, IDC_EDIT_ANSWER3, m_csAnswer[2]);
    DDX_Text(pDX, IDC_EDIT_ANSWER4, m_csAnswer[3]);
    DDX_Text(pDX, IDC_EDIT_ANSWER5, m_csAnswer[4]);
    DDX_Text(pDX, IDC_EDIT_ANSWER6, m_csAnswer[5]);
    DDX_Text(pDX, IDC_EDIT_ANSWER7, m_csAnswer[6]);
    DDX_Text(pDX, IDC_EDIT_ANSWER8, m_csAnswer[7]);
    DDX_Text(pDX, IDC_EDIT_ANSWER9, m_csAnswer[8]);
    DDX_Text(pDX, IDC_EDIT_ANSWER10, m_csAnswer[9]);
    DDX_Text(pDX, IDC_EDIT_ANSWER11, m_csAnswer[10]);
    DDX_Text(pDX, IDC_EDIT_ANSWER12, m_csAnswer[11]);
    DDX_Text(pDX, IDC_EDIT_ANSWER13, m_csAnswer[12]);
    DDX_Text(pDX, IDC_EDIT_ANSWER14, m_csAnswer[13]);
    DDX_Text(pDX, IDC_EDIT_ANSWER15, m_csAnswer[14]);
    DDX_Text(pDX, IDC_EDIT_ANSWER16, m_csAnswer[15]);
    DDX_Text(pDX, IDC_EDIT_ANSWER17, m_csAnswer[16]);
    DDX_Text(pDX, IDC_EDIT_ANSWER18, m_csAnswer[17]);
    DDX_Text(pDX, IDC_EDIT_INPUT_PASSWORD2, m_csPassword);
    DDX_Control(pDX, IDC_CMB_MARK1, m_cmbMark[0]);
    DDX_Control(pDX, IDC_CMB_MARK2, m_cmbMark[1]);
    DDX_Control(pDX, IDC_CMB_MARK3, m_cmbMark[2]);
    DDX_Control(pDX, IDC_CMB_MARK4, m_cmbMark[3]);
    DDX_Control(pDX, IDC_CMB_MARK5, m_cmbMark[4]);
    DDX_Control(pDX, IDC_CMB_MARK6, m_cmbMark[5]);
    DDX_Control(pDX, IDC_CMB_MARK7, m_cmbMark[6]);
    DDX_Control(pDX, IDC_CMB_MARK8, m_cmbMark[7]);
    DDX_Control(pDX, IDC_CMB_MARK9, m_cmbMark[8]);
    DDX_Control(pDX, IDC_CMB_MARK10, m_cmbMark[9]);
    DDX_Control(pDX, IDC_CMB_MARK11, m_cmbMark[10]);
    DDX_Control(pDX, IDC_CMB_MARK12, m_cmbMark[11]);
    DDX_Control(pDX, IDC_CMB_MARK13, m_cmbMark[12]);
    DDX_Control(pDX, IDC_CMB_MARK14, m_cmbMark[13]);
    DDX_Control(pDX, IDC_CMB_MARK15, m_cmbMark[14]);
    DDX_Control(pDX, IDC_CMB_MARK16, m_cmbMark[15]);
    DDX_Control(pDX, IDC_CMB_MARK17, m_cmbMark[16]);
    DDX_Control(pDX, IDC_CMB_MARK18, m_cmbMark[17]);
}


BEGIN_MESSAGE_MAP(CDlgSecurityQuestion, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_QUESTION, &CDlgSecurityQuestion::OnBnClickedBtnGetQuestion)
    ON_BN_CLICKED(IDC_BTN_SET_QUESTION, &CDlgSecurityQuestion::OnBnClickedBtnSetQuestion)
    ON_BN_CLICKED(IDC_ANSWER_RESET_PASSWORD, &CDlgSecurityQuestion::OnBnClickedAnswerResetPassword)
    ON_BN_CLICKED(IDC_SYNC_IPC_PW, &CDlgSecurityQuestion::OnBnClickedSyncIpcPw)
END_MESSAGE_MAP()


// CDlgSecurityQuestion 消息处理程序


void CDlgSecurityQuestion::OnBnClickedBtnGetQuestion()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (FALSE == m_bSupportSecurityQuestion)
    {
        AfxMessageBox("设备不支持安全问题获取!");
        return;
    }
    SADP_SECURITY_QUESTION_CFG struSecurityQuestionCfg = { 0 };
    struSecurityQuestionCfg.dwSize = sizeof(struSecurityQuestionCfg);
    int iRet = SADP_GetDeviceConfig(m_strDevID.GetBuffer(0), SADP_GET_SECURITY_QUESTION, NULL, 0, &struSecurityQuestionCfg, sizeof(struSecurityQuestionCfg));
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        if (iError == SADP_TIMEOUT)
        {
            AfxMessageBox("Get question failed, timeout!");
        }
        else if (iError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Get question failed, device deny!");
        }
        else
        {
            sprintf(szTemp, "Get question failed, Error code%d", iError);
            AfxMessageBox(szTemp);
        }
        return;
    }

    for (int i = 0; i < MAX_QUESTION_NUM; i++)
    {
        m_dwID[i] = struSecurityQuestionCfg.struSecurityQuestion[i].dwId;
        m_cmbMark[i].SetCurSel(struSecurityQuestionCfg.struSecurityQuestion[i].byMark);
    }
    
    UpdateData(FALSE);
    AfxMessageBox("Get security question successfully!");
}


void CDlgSecurityQuestion::OnBnClickedBtnSetQuestion()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (FALSE == m_bSupportSecurityQuestion)
    {
        AfxMessageBox("设备不支持安全问题设置!");
        return;
    }
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
    SADP_SECURITY_QUESTION_CFG struSecurityQuestionCfg = { 0 };
    struSecurityQuestionCfg.dwSize = sizeof(struSecurityQuestionCfg);
    memcpy(struSecurityQuestionCfg.szPassword, m_csPassword.GetBuffer(0), m_csPassword.GetLength());
    for (int i = 0; i < MAX_QUESTION_NUM/*设备目前支持的最大问题数*/; i++)
    {
        struSecurityQuestionCfg.struSecurityQuestion[i].dwSize = sizeof(struSecurityQuestionCfg.struSecurityQuestion[i]);
        struSecurityQuestionCfg.struSecurityQuestion[i].dwId = m_dwID[i];
        struSecurityQuestionCfg.struSecurityQuestion[i].byMark = m_cmbMark[i].GetCurSel();
        memcpy(struSecurityQuestionCfg.struSecurityQuestion[i].szAnswer, m_csAnswer[i].GetBuffer(0), m_csAnswer[i].GetLength());   
    }
    SADP_SECURITY_QUESTION struSecurityQuestion = { 0 };
    int iRet = SADP_SetDeviceConfig(m_strDevID.GetBuffer(0), SADP_SET_SECURITY_QUESTION, &struSecurityQuestionCfg, sizeof(struSecurityQuestionCfg), &struSecurityQuestion, sizeof(struSecurityQuestion));
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        if (iError == SADP_TIMEOUT)
        {
            AfxMessageBox("Set question failed, timeout!");
        }
        else if (iError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Set question failed, device deny!");
        }
        else if (iError == SADP_PASSWORD_ERROR)
        {
            sprintf(szTemp, "Set question failed, password error, retry times:[%d]!", struSecurityQuestion.byRetryAnswerTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_LOCKED)
        {
            sprintf(szTemp, "Set question failed, device locked，lock time:[%d]!", struSecurityQuestion.bySurplusLockTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_LONG_SECURITY_ANSWER)
        {
            AfxMessageBox("Set question failed, long security answer!");
        }
        else if (iError == SADP_QUESTION_NUM_ERR)
        {
            AfxMessageBox("Set question failed, question number error!");
        }
        else
        {
            sprintf(szTemp, "Set question failed, Error code%d", iError);
            AfxMessageBox(szTemp);
        }
        return;
    }

    UpdateData(FALSE);
    AfxMessageBox("Set security question successfully!");
}


void CDlgSecurityQuestion::OnBnClickedAnswerResetPassword()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (FALSE == m_bSupportSecurityQuestion)
    {
        AfxMessageBox("设备不支持安全问题重置密码!");
        return;
    }
    if (m_csPassword == "")
    {
        AfxMessageBox("请先输入密码!");
        return;
    }
    if (m_csPassword.GetLength() > 15)
    {
        AfxMessageBox("密码长度超出范围!");
        return;
    }

    SADP_RESET_PARAM_V50 struResetParamV50 = { 0 };
    struResetParamV50.dwSize = sizeof(struResetParamV50);
    struResetParamV50.byResetType = 5;
    struResetParamV50.byEnableSyncIPCPW = m_bSyncIPCPW;
    memcpy(struResetParamV50.szPassword, m_csPassword.GetBuffer(0), m_csPassword.GetLength());
    struResetParamV50.struSecurityQuestionCfg.dwSize = sizeof(struResetParamV50.struSecurityQuestionCfg);
    for (int i = 0; i < 15; i++)
    {
        struResetParamV50.struSecurityQuestionCfg.struSecurityQuestion[i].dwSize = sizeof(struResetParamV50.struSecurityQuestionCfg.struSecurityQuestion[i]);
        struResetParamV50.struSecurityQuestionCfg.struSecurityQuestion[i].dwId = m_dwID[i];
        struResetParamV50.struSecurityQuestionCfg.struSecurityQuestion[i].byMark = m_cmbMark[i].GetCurSel();
        memcpy(struResetParamV50.struSecurityQuestionCfg.struSecurityQuestion[i].szAnswer, m_csAnswer[i].GetBuffer(0), m_csAnswer[i].GetLength());
    }
    SADP_DEV_LOCK_INFO struDevLockInfo = { 0 };

    int iRet = SADP_ResetPasswd_V50(m_strDevID.GetBuffer(0), &struResetParamV50, &struDevLockInfo);
    if (iRet == 0)
    {
        int iError = SADP_GetLastError();
        char szTemp[100] = { 0 };
        if (iError == SADP_TIMEOUT)
        {
            AfxMessageBox("Question reset password failed, timeout!");
        }
        else if (iError == SADP_DEVICE_DENY)
        {
            AfxMessageBox("Question reset password failed, device deny!");
        }
        else if (iError == SADP_LOCKED)
        {
            sprintf(szTemp, "Question reset password failed, device locked，lock time:[%d]!", struDevLockInfo.bySurplusLockTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_RISK_PASSWORD)
        {
            AfxMessageBox("Question reset password failed, risk password!");
        }
        else if (iError == SADP_NOT_ACTIVATED)
        {
            AfxMessageBox("Question reset password failed, device not activated!");
        }
        else if (iError == SADP_EMPTY_ENCRYPT_STRING)
        {
            AfxMessageBox("Question reset password failed, empty encrypt string!");
        }
        else if (iError == SADP_EXPORT_FILE_OVERDUE)
        {
            AfxMessageBox("Question reset password failed, export file overdue!");
        }
        else if (iError == SADP_INVALID_GUID)
        {
            AfxMessageBox("Question reset password failed, invalid guid!");
        }
        else if (iError == SADP_ANSWER_ERROR)
        {
            sprintf(szTemp, "Question reset password failed, answer error, retry times:[%d]!", struDevLockInfo.byRetryTime);
            AfxMessageBox(szTemp);
        }
        else if (iError == SADP_QUESTION_NUM_ERR)
        {
            AfxMessageBox("Question reset password failed, question number error!");
        }
        else
        {
            sprintf(szTemp, "Question reset password failed, Error code%d", iError);
            AfxMessageBox(szTemp);
        }
        return;
    }

    UpdateData(FALSE);
    AfxMessageBox("Security question reset password successfully!");
}


void CDlgSecurityQuestion::OnBnClickedSyncIpcPw()
{
    // TODO:  在此添加控件通知处理程序代码
    if (IsDlgButtonChecked(IDC_SYNC_IPC_PW))
    {
        m_bSyncIPCPW = 1;
    }
    else
    {
        m_bSyncIPCPW = 0;
    }
}
