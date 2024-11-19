// DlgAutoRequestInterval.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sadpdlg.h"
#include "DlgAutoRequestInterval.h"
#include "afxdialogex.h"


// CDlgAutoRequestInterval �Ի���

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


// CDlgAutoRequestInterval ��Ϣ�������


void CDlgAutoRequestInterval::OnBnClickedButtonOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
	UpdateData(TRUE);
	SADP_SetAutoRequestInterval(m_interval);
	AfxMessageBox("SADP_SET_AUTO_REQUEST_INTERVAL success");
}


void CDlgAutoRequestInterval::OnBnClickedButtonCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
