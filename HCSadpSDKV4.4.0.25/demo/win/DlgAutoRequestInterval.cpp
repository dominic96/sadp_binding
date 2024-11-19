// DlgAutoRequestInterval.cpp : 实现文件
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgAutoRequestInterval.h"
#include "afxdialogex.h"


// CDlgAutoRequestInterval 对话框

IMPLEMENT_DYNAMIC(CDlgAutoRequestInterval, CDialogEx)

CDlgAutoRequestInterval::CDlgAutoRequestInterval(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAutoRequestInterval::IDD, pParent)
	, m_interval(0)
{

}

CDlgAutoRequestInterval::~CDlgAutoRequestInterval()
{
}

void CDlgAutoRequestInterval::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_interval);
}


BEGIN_MESSAGE_MAP(CDlgAutoRequestInterval, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgAutoRequestInterval::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgAutoRequestInterval::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CDlgAutoRequestInterval 消息处理程序


void CDlgAutoRequestInterval::OnBnClickedButtonOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
	UpdateData(TRUE);
	SADP_SetAutoRequestInterval(m_interval);
	AfxMessageBox("SADP_SET_AUTO_REQUEST_INTERVAL success");
}


void CDlgAutoRequestInterval::OnBnClickedButtonCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
