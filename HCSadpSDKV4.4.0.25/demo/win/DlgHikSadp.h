#if !defined(AFX_DLGHIKSADP_H__2A85A69B_6821_4174_BF8E_EA2F34ECC57E__INCLUDED_)
#define AFX_DLGHIKSADP_H__2A85A69B_6821_4174_BF8E_EA2F34ECC57E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHikSadp.h : header file
//


#include "Sadp.h"
//#include "InsideSadp.h"
#include "sadpdlg.h"
#include <afxmt.h>
#include <afxtempl.h>

#define MSG_FIND_DEVICE  WM_USER +1    // �����豸��Ϣ
#define MSG_FIND_SUBNET_DEVICE  WM_USER +2    // ���ֿ������豸��Ϣ

typedef struct tagSADPRet
{
	BOOL	bselect;
	char	sversion[64];
	char	sseries[64];
	char	szSerialNO[64];
	char	shwaddr[64];
	char	spraddr[64];
	char	ssubnetmask[64];
	int		dev_type;
	unsigned int	port;
	unsigned int	enccnt; 
}SSADPRET,*PSSADPRET;

typedef struct tagSADPDev
{
	char	cdev[20];
}SSADPDEV,*PSSADPDEV;

typedef struct tagSADPInfo
{
	char			sseries[64];
	char			szSerialNO[64];
	char			szMac[64];
	char			szIPv4[64];
	char			szSubnetMask[64];
	char			szSoftVersion[64];
	char			szDSPVersion[64];
	char			szBootTime[64];
	int				iDevType;
	unsigned int	wPort;
	unsigned int	dwNumOfEncoder; 
	unsigned int	dwNumOfHardDisk;
	char			szDevDesc[24];       //�豸��������
	char			szOEMinfo[24];       //OEM������Ϣ
	char			szBaseDesc[24];       //OEM������Ϣ
	char			szIPv4Gateway[16];   //IPv4����
	char			szIPv6Address[46];	 //IPv6��ַ
	char			szIPv6Gateway[46];   //IPv6����
	unsigned char   byIPv6MaskLen;       //IPv6����ǰ׺����
	unsigned char   bySupport;           //��λ��ʾ,��ӦΪΪ1��ʾ֧��,0x01:�Ƿ�֧��Ipv6,0x02:�Ƿ�֧���޸�Ipv6����,0x04:�Ƿ�֧��Dhcp				 
	unsigned char   byDhcpEnabled;       //Dhcp״̬, 0 ������ 1 ����
	unsigned char	byOEMCode;			//0-�����豸 1-OEM�豸
	unsigned short	wHttpPort;			// Http �˿�
	unsigned short	wDigitalChannelNum;
	char			szCmsIPv4[16];
	unsigned short	wCmsPort;
	int				result;
	unsigned char   byActivated;       //�豸����״̬, 0 :���� 1��δ����
    unsigned char   bySupport1; //��λ��ʾ,  1��ʾ֧�֣�0��ʾ��֧��
                                //0x01:�Ƿ�֧���������뷽ʽ2 
                                //0x04:�Ƿ�֧�ֵ���GUID��������
                                //0x08:�Ƿ�֧�ְ�ȫ������������
                                //0x10: �Ƿ�֧��OEM����Logo
                                //0x20: �Ƿ�֧�ְ󶨲���
                                //0x40: �Ƿ�֧�ָֻ�δ����
	unsigned char   byHCPlatform; //�Ƿ�֧��HCPlatform 0-������ 1-֧�֣� 2-��֧��   
	unsigned char   byEnableHCPlatform; //�Ƿ�����HCPlatform  0 -���� 1- ���ã� 2- ������
	unsigned char   byEZVIZCode;    //0- �����豸 1- өʯ�豸
	unsigned int    dwDetailOEMCode;    //��ϸOEMCode��Ϣ:oemcode�ɿͻ���ţ��ɱ�λ,��1��ʼ��1~429496)+�˵����2λ��+����ţ�2λ�������ֹ��ɡ�	
	//����˵����oemcode���ֵΪ4294967295�������ʮλ����
	unsigned char   byModifyVerificationCode; //�Ƿ��޸���֤�� 0-������ 1-�޸���֤�룬 2- ���޸���֤��
    unsigned char    byMaxBindNum;//֧�ְ󶨵���������Ŀǰֻ��NVR֧�ָ��ֶΣ�
    unsigned short	 wOEMCommandPort;     // OEM���� �˿�
    unsigned char    bySupportWifiRegion;//�豸֧�ֵ�wifi�����б���λ��ʾ��1��ʾ֧�֣�0��ʾ��֧��
    //0x01:�Ƿ�֧��default��Ĭ�Ϲ��ʺͱ���һ�£�
    //0x02:�Ƿ�֧��china
    //0x04:�Ƿ�֧��nothAmerica
    //0x08: �Ƿ�֧��japan
    //0x10: �Ƿ�֧��europe
    //0x20:�Ƿ�֧��world
    unsigned char    bySupport2;
    //0x01:�Ƿ�ͨ��Ĭ���������� 
    //0x02:�Ƿ�֧��������������
    //0x04:�Ƿ�֧��δ��������SSID��Password
    unsigned char    byEnableWifiEnhancement;//�Ƿ�����wifi��ǿģʽ,0-�����ã�1-����
    unsigned char    byWifiRegion;//�豸��ǰ����0-default��1-china��2-nothAmerica��3-japan��4-europe,5-world
    unsigned char    byLicensed; //�豸�Ƿ���Ȩ��0-����,1-�豸δ��Ȩ��2-�豸����Ȩ
    unsigned char    bySystemMode;      //ϵͳģʽ 0-����,1-���أ�2-˫�أ�3-������Ⱥ��4-˫�ؼ�Ⱥ
    unsigned char    byControllerType;  //���������� 0-������1-A�أ�2-B��
    char			 szEhmoeVersion[16]; //Ehmoe�汾��
    unsigned char    bySpecificDeviceType;//�豸���� 1-�����豸 2-�����豸
    unsigned int	 dwSDKOverTLSPort;	//˽��Э���� SDK Over TLS ����˿�
    unsigned char    bySecurityMode;    //�豸��ȫģʽ��0-standard,1-high-A,2-high-B,3-custom
    unsigned char    bySDKServerStatus; //�豸SDK����״̬, 0-δ֪��1-������2-�ر�
    unsigned char    bySDKOverTLSServerStatus; //�豸SDKOverTLS����״̬, 0-δ֪��1-������2-�ر�
    char             szUserName[MAX_USERNAME_LEN + 1]; //����Ա�û����û���
    char             szWifiMAC[20]; //�豸����wifi��Mac��ַ
    unsigned char    byDataFromMulticast; //0-��· 1-�ಥ
    unsigned char    bySupportEzvizUnbind; //�Ƿ�֧��өʯ��� 0-��֧�� 1-֧��
    unsigned char    bySupportCodeEncrypt; //�Ƿ�֧�����ÿ���AES128_ECB���� 0-��֧�� 1-֧��
    unsigned char    bySupportPasswordResetType; //�Ƿ�֧�ֻ�ȡ�������÷�ʽ���� 0-��֧�� 1-֧��
    unsigned char   byEZVIZBindStatus; //�豸өʯ�ư�״̬,0-δ֪,1-�Ѱ�,2-δ��
    char            szPhysicalAccessVerification[16]; //�豸֧�ֵ�����Ӵ�ʽ��ӷ�ʽ,1#AP��������,2#�û����ƣ��û�token����,3#�������Ӵ�,4#ɨ��󶨣��豸token��
    unsigned short  wHttpsPort; // Https �˿�
    unsigned char   bySupportEzvizUserToken; //�Ƿ�֧��өʯ�û�token����  0-��֧�� 1-֧��
    char            szDevDescEx[64];         //�Ƕ�szDevDesc�ֶ���չ
    char            szSerialNOEx[128];        //�Ƕ�szSerialNO�ֶ���չ
    char            szManufacturer[32];       //�豸������Ϣ
    unsigned char   bySupportResetPwByPhoneNo; //�Ƿ�֧���ֻ�ɨ�������豸����Ա����  0-��֧�� 1-֧��
}SSADPINFO,*PSSADPINFO;

/*int dev_type,unsigned int port,\
										unsigned int enccnt, unsigned int hdiskcnt*/
/////////////////////////////////////////////////////////////////////////////
// CDlgHikSadp dialog

class CDlgHikSadp : public CDialog
{
// Construction
public:
	CDlgHikSadp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHikSadp)
	enum { IDD = IDD_DLG_HIKSADP };
	CComboBox	m_CtrDisplayRule;
    CComboBox	m_CtrWifiMode;
    CComboBox   m_CtrLampAction;
	CIPAddressCtrl	m_addrCmsIPv4;
	CIPAddressCtrl	m_sip;
	CIPAddressCtrl	m_smask;
	CIPAddressCtrl  m_addrIPv4Gateway;
	CListCtrl	m_slist;
    CListCtrl	m_slistSubnet;
	CString	m_sdevid;
	CString	m_sversion;
	CString m_strIPv6Adress;
	CString m_strIPv6Gateway;
	CString m_strIPv6MaskLen;
	CString m_strDevDescription;
    CString m_strDevType;
	UINT	m_uport;
    UINT	m_uSDKOverTLSPort;
	CString	m_smac;
	CString	m_spsw;
	CString m_strSoftVersion;
	CString	m_strPUID;
	CString	m_strCmsPasswd;
	CString	m_strCmsIPv6;
	UINT	m_wCmsPort;
	CString m_origipasswd;
	UINT	m_wHttpPort;
    CString	m_strWifiSSID;
    CString	m_strWifiPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHikSadp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	afx_msg void OnCustomDrawList(NMHDR *pNMHDR, LRESULT *pResult);

	// Generated message map functions
	//{{AFX_MSG(CDlgHikSadp)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButBack();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonModify();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtonSafe();
	afx_msg void OnButtonSelectDev();
	afx_msg void OnButtonCmsSet();
	afx_msg void OnBnClickedButtonDefaultPW();
	afx_msg void OnCheckDhcp();
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnActivateDevice();
	afx_msg void OnBtnResetPw();
	afx_msg void OnBtnSetDisplayRule();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int			m_ilanguage;

	char *		GetText(int id);

	int			m_icount;
    int			m_icountSubnet;
	HICON		m_hIcon;
	SSADPRET *	m_retbuf;

	CButton *m_btnDhcp;


	CList<SSADPDEV,SSADPDEV&>	m_devlist;//�Ѵ����豸�б�

	BOOL		m_brun;
	BOOL		m_bedit;
    BOOL        m_bSyncIPCPW;  //ͬ��IPC����
    BOOL        m_bResetPWModeSecond;
    BOOL        m_bResetPW; //��������
    BOOL        m_bSupportGUID;
    BOOL        m_bSupportSecurityQuestion;
    BOOL        m_bSupportBind;
    BOOL        m_bSupportEnhancement;
    BOOL        m_bEnableEnhancement;
    BYTE        m_bySupportWifiRegion;
    BYTE        m_byCurrentWiriRegion;
    BYTE        m_bySupportChannelDefaultPW;
    BOOL        m_bMailBoxResetPW;
    BOOL        m_bSupportSSIDAndPasswordCfg;
    BOOL        m_bSupportEzvizUserToken;
    BOOL        m_bSupportPhoneReset;

	LRESULT		OnTabDraw(WPARAM wParam, LPARAM lParam);
    LRESULT		OnTabDrawSubnet(WPARAM wParam, LPARAM lParam);

	
	void	fDevOnLine(SSADPINFO *pinfo);
	void	fDevOffLine(SSADPINFO *pinfo);
	void	fDevReboot(SSADPINFO *pinfo);
	void	fDevRefresh(SSADPINFO *pinfo);

    void	fSubnetDevOnLine(SADP_SUBNET_DEVICE_INFO *pinfo);

	void	fEnableButton(BOOL bedit);

	BOOL	fIfInUsed(char * sip);
public:
	DWORD m_dwsmask;
	DWORD m_dwsip;

	void	fInsDevice(char *dvrip);
	void	fSetRetBuf(SSADPRET * pbuf);
	//afx_msg void OnStnClickedStaticPswinput();
	
	
    afx_msg void OnBnClickedCustomFunc();
	afx_msg void OnBnClickedBtnHcplatform();
    afx_msg void OnBnClickedBtnBind();
    afx_msg void OnBnClickedBtnWifiRegion();
    afx_msg void OnBnClickedBtnSendLamp();
    afx_msg void OnBnClickedBtnDiskLocate();
    afx_msg void OnBnClickedBtnSelfCheck();
    afx_msg void OnBnClickedBtnConfig();
    afx_msg void OnBnClickedBtnWifiParamCfg();
    afx_msg void OnBnClickedBtnWifiParamCheck();
    afx_msg void OnBnClickedBtnEhomeEnable();
    afx_msg void OnBnClickedBtnUnbind();
    afx_msg void OnBnClickedBtnUnbindDelUser();
	afx_msg void OnBnClickedButtonStartv30();
	afx_msg void OnBnClickedButtonStartv40();
	afx_msg void OnBnClickedButtonSetReqinterval();
	afx_msg void OnBnClickedButtonSecQue();
	afx_msg void OnBnClickedButtonMailReset();
	afx_msg void OnBnClickedButtonRestoreInactive();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedBtnResetPw4();
	afx_msg void OnBnClickedBtnResetPw2();
	afx_msg void OnBnClickedBtnResetPw3();
	afx_msg void OnBnClickedButton11();
    afx_msg void OnBnClickedBtnSetToken();
    afx_msg void OnBnClickedButtonMailReset2();
    afx_msg void OnBnClickedButtonPhoneReset();
    afx_msg void OnNMRClickListDevInfo(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedButtonStartv50();
    afx_msg void OnBnClickedButtonSubnetInquery();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHIKSADP_H__2A85A69B_6821_4174_BF8E_EA2F34ECC57E__INCLUDED_)
