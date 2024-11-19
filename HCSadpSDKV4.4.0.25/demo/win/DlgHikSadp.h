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

#define MSG_FIND_DEVICE  WM_USER +1    // 发现设备消息
#define MSG_FIND_SUBNET_DEVICE  WM_USER +2    // 发现跨网段设备消息

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
	char			szDevDesc[24];       //设备类型描述
	char			szOEMinfo[24];       //OEM产商信息
	char			szBaseDesc[24];       //OEM产商信息
	char			szIPv4Gateway[16];   //IPv4网关
	char			szIPv6Address[46];	 //IPv6地址
	char			szIPv6Gateway[46];   //IPv6网关
	unsigned char   byIPv6MaskLen;       //IPv6子网前缀长度
	unsigned char   bySupport;           //按位表示,对应为为1表示支持,0x01:是否支持Ipv6,0x02:是否支持修改Ipv6参数,0x04:是否支持Dhcp				 
	unsigned char   byDhcpEnabled;       //Dhcp状态, 0 不启用 1 启用
	unsigned char	byOEMCode;			//0-基线设备 1-OEM设备
	unsigned short	wHttpPort;			// Http 端口
	unsigned short	wDigitalChannelNum;
	char			szCmsIPv4[16];
	unsigned short	wCmsPort;
	int				result;
	unsigned char   byActivated;       //设备激活状态, 0 :激活 1：未激活
    unsigned char   bySupport1; //按位表示,  1表示支持，0表示不支持
                                //0x01:是否支持重置密码方式2 
                                //0x04:是否支持导入GUID重置密码
                                //0x08:是否支持安全问题重置密码
                                //0x10: 是否支持OEM更换Logo
                                //0x20: 是否支持绑定操作
                                //0x40: 是否支持恢复未激活
	unsigned char   byHCPlatform; //是否支持HCPlatform 0-保留， 1-支持， 2-不支持   
	unsigned char   byEnableHCPlatform; //是否启用HCPlatform  0 -保留 1- 启用， 2- 不启用
	unsigned char   byEZVIZCode;    //0- 基线设备 1- 萤石设备
	unsigned int    dwDetailOEMCode;    //详细OEMCode信息:oemcode由客户序号（可变位,从1开始，1~429496)+菜单风格（2位）+区域号（2位）三部分构成。	
	//规则说明：oemcode最大值为4294967295，最多是十位数。
	unsigned char   byModifyVerificationCode; //是否修改验证码 0-保留， 1-修改验证码， 2- 不修改验证码
    unsigned char    byMaxBindNum;//支持绑定的最大个数（目前只有NVR支持该字段）
    unsigned short	 wOEMCommandPort;     // OEM命令 端口
    unsigned char    bySupportWifiRegion;//设备支持的wifi区域列表，按位表示，1表示支持，0表示不支持
    //0x01:是否支持default（默认功率和北美一致）
    //0x02:是否支持china
    //0x04:是否支持nothAmerica
    //0x08: 是否支持japan
    //0x10: 是否支持europe
    //0x20:是否支持world
    unsigned char    bySupport2;
    //0x01:是否通道默认密码配置 
    //0x02:是否支持邮箱重置密码
    //0x04:是否支持未激活配置SSID和Password
    unsigned char    byEnableWifiEnhancement;//是否启用wifi增强模式,0-不启用，1-启用
    unsigned char    byWifiRegion;//设备当前区域，0-default，1-china，2-nothAmerica，3-japan，4-europe,5-world
    unsigned char    byLicensed; //设备是否授权：0-保留,1-设备未授权，2-设备已授权
    unsigned char    bySystemMode;      //系统模式 0-保留,1-单控，2-双控，3-单机集群，4-双控集群
    unsigned char    byControllerType;  //控制器类型 0-保留，1-A控，2-B控
    char			 szEhmoeVersion[16]; //Ehmoe版本号
    unsigned char    bySpecificDeviceType;//设备类型 1-中性设备 2-海康设备
    unsigned int	 dwSDKOverTLSPort;	//私有协议中 SDK Over TLS 命令端口
    unsigned char    bySecurityMode;    //设备安全模式：0-standard,1-high-A,2-high-B,3-custom
    unsigned char    bySDKServerStatus; //设备SDK服务状态, 0-未知，1-开启，2-关闭
    unsigned char    bySDKOverTLSServerStatus; //设备SDKOverTLS服务状态, 0-未知，1-开启，2-关闭
    char             szUserName[MAX_USERNAME_LEN + 1]; //管理员用户的用户名
    char             szWifiMAC[20]; //设备所连wifi的Mac地址
    unsigned char    byDataFromMulticast; //0-链路 1-多播
    unsigned char    bySupportEzvizUnbind; //是否支持萤石解绑 0-不支持 1-支持
    unsigned char    bySupportCodeEncrypt; //是否支持重置口令AES128_ECB解密 0-不支持 1-支持
    unsigned char    bySupportPasswordResetType; //是否支持获取密码重置方式参数 0-不支持 1-支持
    unsigned char   byEZVIZBindStatus; //设备萤石云绑定状态,0-未知,1-已绑定,2-未绑定
    char            szPhysicalAccessVerification[16]; //设备支持的物理接触式添加方式,1#AP配网传递,2#用户令牌（用户token）绑定,3#物理按键接触,4#扫码绑定（设备token）
    unsigned short  wHttpsPort; // Https 端口
    unsigned char   bySupportEzvizUserToken; //是否支持萤石用户token配置  0-不支持 1-支持
    char            szDevDescEx[64];         //是对szDevDesc字段扩展
    char            szSerialNOEx[128];        //是对szSerialNO字段扩展
    char            szManufacturer[32];       //设备厂商信息
    unsigned char   bySupportResetPwByPhoneNo; //是否支持手机扫码重置设备管理员密码  0-不支持 1-支持
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


	CList<SSADPDEV,SSADPDEV&>	m_devlist;//已存在设备列表

	BOOL		m_brun;
	BOOL		m_bedit;
    BOOL        m_bSyncIPCPW;  //同步IPC密码
    BOOL        m_bResetPWModeSecond;
    BOOL        m_bResetPW; //重置密码
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
