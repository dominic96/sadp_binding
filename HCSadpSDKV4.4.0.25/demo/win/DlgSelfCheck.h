#pragma once


// CDlgSelfCheck 对话框

class CDlgSelfCheck : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelfCheck)

public:
	CDlgSelfCheck(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSelfCheck();
    BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_SELF_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnCheck();
    CString m_strDevID;
    CString m_strDevMAC;
    int m_iTotalDisk;
    int m_iGoodDisk;
    CString m_csCPU;
    CString m_csMemory;
    int m_iProgress;
    CComboBox m_cmbTemperatureState;
    CComboBox m_cmbFanState;
    CComboBox m_cmbPowerState;
    CComboBox m_cmbSASConnectState;
    int m_iTotalNetworkPort;
    int m_iConnectNetworkPort;
    afx_msg void OnBnClickedBtnCheckByMac();
};
