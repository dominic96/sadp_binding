// DlgHikSadp.cpp : implementation file
//

#include "stdafx.h"
#include "DlgHikSadp.h"
#include "ResetPassword.h"
#include "DlgCustom.h"
#include "HCPlatformStatus.h"
#include "BindDev.h"
#include "WifiRegion.h"
#include "Config.h"
#include "DlgSelfCheck.h"
#include "EhomeEnable.h"
#include "EzvizUnbind.h"
#include "EzvizUnbindDelUser.h"
#include "DlgAutoRequestInterval.h"
#include "DlgSetFilterRule.h"
#include "DlgActivateDevice.h"
#include "DlgSecurityQuestion.h"
#include "MailBoxResetPW.h"
#include "DlgRestoreInactive.h"
#include "DlgResetPWGUID.h"
#include "DlgResetPWEncrypt.h"
#include "DlgRestPWDeviceCode.h"
#include "DlgEzvizToken.h"
#include "DlgResetPWPhone.h"
#include "DlgInquiry.h"

#define MAX_LEN 128

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define Single 1

CString g_csPort;
CString g_csSDKOverTLSPort;
CString g_csMask;
CString g_csIP;
////////////////////////////////////////////
//Multi language support

typedef struct TXT_SRC
{
    int		index;
    char	*text;
}TXT_SRC_S;

TXT_SRC_S TEXT_chinese[]=
{
	{0,		"   在线设备侦测...."},
	{1,		"设备编号"},
	{2,		"软件版本"},
	{3,		"子网掩码"},
	{4,		"IP地址"},
	{5,		"设备PORT"},
	{6,		"设备MAC"},
	{7,		"---- 请输入管理员口令 ----"},
	{8,		"修改"},
	{9,		"取消"},
	{10,	"保存"},
	{11,	"Start"},
	{12,	"返回"},
	{13,	"请输入PORT号!"},
	{14,	"请输入管理员口令!"},
	{15,	"请选择一台设备!"},
	{16,	"确定添加设备(%s)吗?"},
	{17,    "确定"},
	{18,	"错误:参数不是有效值!"},
	{19,	"启动sadp失败!\n"},
	{20,	"保存失败!"},
	{21,	"保存成功!"},
	{22,	"请选择要修改的设备!"},
	{23,	"请输入要修改的子网掩码!"},
	{24,	"请输入要修改的IP!"},
	{25,	"请输入验证码!"},
	{26,	"更新设备，修改成功!"},
	{27,	"修改失败!"},
	{28,	" ----恢复设备缺省密码----"},
	{29,	"PORT号必须在65535以内"},
	{30,	"恢复成功!"},
	{31,	"恢复失败"},
	{32,	"设备类型"},
	{33,	"IP地址"},
	{34,	"端口号"},
	{35,	"设备序列号"},
	{36,	"子网掩码"},
	{37,	"物理地址"},
	{38,	"模拟通道数"},
	{39,	"软件版本"},
	{40,	"DSP版本"},
	{41,	"启动时间"},
	{42,    "设备类型描述"},
	{43,    "OEM厂商信息"},
	{44,    "IPv4网关"},
	{45,    "IPv6地址"},
	{46,    "IPv6网关"},
	{47,    "IPv6子网前缀长度"},
	{48,    "是否支持IPv6"},
	{49,    "IPv4 DHCP状态"},
	{50,    "是否支持修改IPv6"},
	{51,    "是否支持DHCP"},
	{52,    "CMS IPv4地址"},
	{53,    "CMS 端口"},
	{54,    "数字通道数"},
	{55,    "Http 端口"},
	{56,	"OEM 标识"},
	{57,    "OEM 信息"},
	{58,	"版本信息"},
    {59,	"序号"	},
    {60,	"基线短型号"},
    {61,	"该设备已锁定"},
    {62,	"该设备未激活"},
    {63,	"支持密码恢复"	},
    {64,	"设备激活状态"},
    {65,	"支持密码重置"},
	{66, "支持HCPlatform" },
	{67, "开启HCPlatform" },
	{68, "需要修改验证码" },
    {69, "支持绑定" },
    {70, "最大绑定个数" },
    {71, "恢复未激活" },
    {72, "支持wifi增强" },
    { 73, "开启wifi增强" },
    { 74, "支持wifi区域" },
    { 75, "当前wifi区域" },
    { 76, "支持通道默认密码" }

};

TXT_SRC_S TEXT_english[]=
{
	{0,		"   SADP"},
	{1,		"Device Serial Number"},
	{2,		"Soft Version"},
	{3,		"Subnet Mask"},
	{4,		"IP Address"},
	{5,		"Device Port"},
	{6,		"MAC Address"},
	{7,		"---please input password---"},
	{8,		"modify"},
	{9,		"cancel"},
	{10,	"save"},
	{11,	"start"},
	{12,	"Exit"},
	{13,	"please input device port!"},
	{14,	"please input password!"},
	{15,	"please select a device!"},
	{16,	"are you sure to insert device(%s)?"},
	{17,    "OK"},
	{18,	"err: params invalid!"},
	{19,	"start sadp fail!\n"},
	{20,	"save failed!"},
	{21,	"save successfully!"},
	{22,	"select a device to modify,please!"},
	{23,	"input the subnet,please!"},
	{24,	"input the device IP,please!"},
	{25,	"input the confirm-word!"},
	{26,	"update device,modify device successfully!"},
	{27,	"modify failed!"},
	{28,	"-Restore default password-"},
	{29,	"The port number must small than 65535"},
	{30,	"success for Restore default password"},
	{31,	"failed to Restore default password"},
	{32,	"Device Type"},
	{33,	"IP Address"},
	{34,	"Port Number"},
	{35,	"Device Serial No."},
	{36,	"Mask"},
	{37,	"Mac"},
	{38,	"Analog Channels"},
	{39,	"Soft Version"},
	{40,	"DSP Version"},
	{41,	"Start Time"},
	{42,    "Device Type Description"},
	{43,    "OEM Info"},
	{44,    "IPv4 Gateway"},
	{45,    "IPv6 Address"},
	{46,    "IPv6 Gateway"},
	{47,    "IPv6 Subnetmask Len"},
	{48,    "IPv6 support or not"},
	{49,    "IPv4 DHCP state"},
	{50,    "IPv6 modify or not"},
	{51,    "DHCP support or not"},
	{52,    "CMS IPv4"},
	{53,    "CMS Port"},
	{54,    "Digital Channels"},
	{55,    "Http Port"},
	{56,    "OEM Code"},
	{57,    "OEM Info"},
	{58,	"Version Info"},
	{59,	"No."	},
	{60,	"Base Desc"	},
	{61,	"The device is locked"},
	{62,	"The device is not activated"},
    {63,	"Password Restore"},
    {64,	"Activate State"},
    {65,	"Password Reset"},
	{ 66, "Support HCPlatform" },
	{ 67, "Enable HCPlatform" },
	{ 68, "Modify VerificationCode" },
    {69, "Support Bind" },
    {70, "Max Bind Num" },
    {71, "Restore Inactive" },
    { 72, "Support wifi Enhancement" },
    { 73, "Enable wifi Enhancement" },
    { 74, "Support wifi Region" },
    { 75, "Current wifi Region" },
    { 76, "Support Channel Default PW" }
	
};

TXT_SRC_S TEXT_chineseT[]=
{
	{0,		"   絬砞称盎代...."},
	{1,		"砞称絪腹"},
	{2,		"硁ンセ"},
	{3,		"呼被絏"},
	{4,		"IP"},
	{5,		"砞称PORT"},
	{6,		"砞称MAC"},
	{7,		"----叫块恨瞶----"},
	{8,		"э"},
	{9,		""},
	{10,	"玂"},
	{11,	"匡拒砞称"},
	{12,	""},
	{13,	"叫块PORT腹"},
	{14,	"叫块恨瞶"},
	{15,	"叫匡拒籓砞称"},
	{16,	"絋﹚睰砞称(%s)盾"},
	{17,    "絋﹚"},
	{18,	"岿粇把计ぃ琌Τ"},
	{19,	"币笆sadpア毖\n"},
	{20,	"玂ア毖"},
	{21,	"玂Θ"},
	{22,	"叫匡拒璶э砞称"},
	{23,	"叫块璶э呼被絏"},
	{24,	"叫块璶эIP"},
	{25,	"叫块喷靡絏"},
	{26,	"穝砞称эΘ"},
	{27,	"эア毖"},
	{28,	" ----確砞称盞絏----"},
	{29,	"PORT腹ゲ斗2000-65535ぇ丁"},
	{30,	"確Θ"},
	{31,	"確ア毖"},
	{32,	"砞称摸"},
	{33,	"IP"},
	{34,	"狠腹"},
	{35,	"砞称腹"},
	{36,	"呼被絏"},
	{37,	"瞶"},
	{38,	"硄笵腹"},
	{39,	"硁ンセ"},
	{40,	"DSPセ"},
	{41,	"币笆丁"}
};

TXT_SRC_S *TEXT_index[]=
{
	TEXT_chinese,		//0
	TEXT_english,		//1
	TEXT_chineseT		//2
};

char * CDlgHikSadp::GetText(int id)
{
	TXT_SRC_S * TEXT_tmp;

	TEXT_tmp = TEXT_index[m_ilanguage];

	return TEXT_tmp[id].text;
}

//
////////////////////////////////////////////


HWND gHwndSADP;

BOOL strlenchk(char *sstr)
{
	if(sstr==NULL)
		return TRUE;

	if(strlen(sstr)>=64)
	{
		return FALSE;
	}else
	{
		return TRUE;
	}
}

SADP_SUBNET_DEVICE_INFO g_struSubnetDevInfoList[4096] = { 0 };

void __stdcall SadpSubnetDataCallBack(const SADP_SUBNET_DEVICE_INFO *_pSubnetDevInfo, void* _pUserData)
{
    SADP_SUBNET_DEVICE_INFO * pinfo;
    pinfo = (SADP_SUBNET_DEVICE_INFO*)malloc(sizeof(SADP_SUBNET_DEVICE_INFO));
    memset(pinfo, 0, sizeof(SADP_SUBNET_DEVICE_INFO));

    memcpy(pinfo, _pSubnetDevInfo, sizeof(SADP_SUBNET_DEVICE_INFO));

    //查询是否已经显示过
    for (int i = 0; i < 4096; i++)
    {
        if (0 == strlen(g_struSubnetDevInfoList[i].szSerialNO))
        {
            break;
        }
        if (0 == strcmp(g_struSubnetDevInfoList[i].szSerialNO, _pSubnetDevInfo->szSerialNO))
        {
            return;
        }
    }

    for (int i = 0; i < 4096; i++)
    {
        if (0 == strlen(g_struSubnetDevInfoList[i].szSerialNO))
        {
            memcpy(&g_struSubnetDevInfoList[i], _pSubnetDevInfo, sizeof(SADP_SUBNET_DEVICE_INFO));
            break;
        }
    }

    if (gHwndSADP)   //gHwndSADP
    {
        ::PostMessage(gHwndSADP, MSG_FIND_SUBNET_DEVICE, (int)pinfo, 0);
    }
    //free(pinfo);
    return;
}

void __stdcall SadpDataCallBack_V40(const SADP_DEVICE_INFO_V40 *_pDevInfo_V40, void* _pUserData)
{
    //check!!
    // 	if((strlenchk(_pDevInfo->szSeries) ||
    // 		strlenchk(_pDevInfo->szSerialNO) || 
    // 		strlenchk(_pDevInfo->szMAC) ||
    // 		strlenchk(_pDevInfo->szIPv4Address) ||
    // 		strlenchk(_pDevInfo->szIPv4SubnetMask) ||
    // 		strlenchk(_pDevInfo->szDeviceSoftwareVersion) || 
    // 		strlenchk(_pDevInfo->szDSPVersion) ||
    // 		strlenchk(_pDevInfo->szBootTime)) == FALSE)
    // 	{
    // 		AfxMessageBox("err : params invalid!");
    // 		return;
    // 	}

    // 	TRACE("  %d  > series=%s,deviceid=%s,hwaddr=%s,praddr=%s,subnetmask=%s,result=%d,sfwversion=%s,dspversion=%s,starttime=%s\n",
    // 		result,series,deviceid,hwaddr,praddr,subnetmask,result,sfwversion,dspversion,starttime);

    SSADPINFO * pinfo;

    pinfo = (SSADPINFO*)malloc(sizeof(SSADPINFO));

    memset(pinfo, 0, sizeof(SSADPINFO));


    strncpy(pinfo->sseries, _pDevInfo_V40->struSadpDeviceInfo.szSeries, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szSeries));
    strncpy(pinfo->szSerialNO, _pDevInfo_V40->struSadpDeviceInfo.szSerialNO, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szSerialNO));
    strncpy(pinfo->szMac, _pDevInfo_V40->struSadpDeviceInfo.szMAC, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szMAC));
    strncpy(pinfo->szIPv4, _pDevInfo_V40->struSadpDeviceInfo.szIPv4Address, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szIPv4Address));
    strncpy(pinfo->szSubnetMask, _pDevInfo_V40->struSadpDeviceInfo.szIPv4SubnetMask, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szIPv4SubnetMask));
    strncpy(pinfo->szSoftVersion, _pDevInfo_V40->struSadpDeviceInfo.szDeviceSoftwareVersion, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szDeviceSoftwareVersion));
    strncpy(pinfo->szDSPVersion, _pDevInfo_V40->struSadpDeviceInfo.szDSPVersion, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szDSPVersion));
    strncpy(pinfo->szBootTime, _pDevInfo_V40->struSadpDeviceInfo.szBootTime, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szBootTime));

    strncpy(pinfo->szDevDesc, _pDevInfo_V40->struSadpDeviceInfo.szDevDesc, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szDevDesc));
    strncpy(pinfo->szOEMinfo, _pDevInfo_V40->struSadpDeviceInfo.szOEMinfo, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szOEMinfo));
    strncpy(pinfo->szIPv4Gateway, _pDevInfo_V40->struSadpDeviceInfo.szIPv4Gateway, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szIPv4Gateway));
    strncpy(pinfo->szIPv6Address, _pDevInfo_V40->struSadpDeviceInfo.szIPv6Address, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szIPv6Address));
    strncpy(pinfo->szIPv6Gateway, _pDevInfo_V40->struSadpDeviceInfo.szIPv6Gateway, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szIPv6Gateway));
    strncpy(pinfo->szBaseDesc, _pDevInfo_V40->struSadpDeviceInfo.szBaseDesc, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szBaseDesc));
    pinfo->result = _pDevInfo_V40->struSadpDeviceInfo.iResult;
    pinfo->iDevType = _pDevInfo_V40->struSadpDeviceInfo.dwDeviceType;
    pinfo->wPort = _pDevInfo_V40->struSadpDeviceInfo.dwPort;
    pinfo->dwNumOfEncoder = _pDevInfo_V40->struSadpDeviceInfo.dwNumberOfEncoders;
    pinfo->dwNumOfHardDisk = _pDevInfo_V40->struSadpDeviceInfo.dwNumberOfHardDisk;

    pinfo->byIPv6MaskLen = _pDevInfo_V40->struSadpDeviceInfo.byIPv6MaskLen;
    pinfo->bySupport = _pDevInfo_V40->struSadpDeviceInfo.bySupport;
    pinfo->byDhcpEnabled = _pDevInfo_V40->struSadpDeviceInfo.byDhcpEnabled;
    strncpy(pinfo->szCmsIPv4, _pDevInfo_V40->struSadpDeviceInfo.szCmsIPv4, sizeof(_pDevInfo_V40->struSadpDeviceInfo.szCmsIPv4));
    pinfo->wCmsPort = _pDevInfo_V40->struSadpDeviceInfo.wCmsPort;
    pinfo->wHttpPort = _pDevInfo_V40->struSadpDeviceInfo.wHttpPort;
    pinfo->wDigitalChannelNum = _pDevInfo_V40->struSadpDeviceInfo.wDigitalChannelNum;
    pinfo->byOEMCode = _pDevInfo_V40->struSadpDeviceInfo.byOEMCode;
    pinfo->byActivated = _pDevInfo_V40->struSadpDeviceInfo.byActivated;
    pinfo->bySupport1 = _pDevInfo_V40->struSadpDeviceInfo.bySupport1;
    pinfo->byHCPlatform = _pDevInfo_V40->struSadpDeviceInfo.byHCPlatform;
    pinfo->byEnableHCPlatform = _pDevInfo_V40->struSadpDeviceInfo.byEnableHCPlatform;
    pinfo->byModifyVerificationCode = _pDevInfo_V40->struSadpDeviceInfo.byModifyVerificationCode;
    pinfo->byMaxBindNum = _pDevInfo_V40->struSadpDeviceInfo.byMaxBindNum;
    pinfo->byEnableWifiEnhancement = _pDevInfo_V40->struSadpDeviceInfo.byEnableWifiEnhancement;
    pinfo->bySupportWifiRegion = _pDevInfo_V40->struSadpDeviceInfo.bySupportWifiRegion;
    pinfo->byWifiRegion = _pDevInfo_V40->struSadpDeviceInfo.byWifiRegion;

    pinfo->bySupport2 = _pDevInfo_V40->struSadpDeviceInfo.bySupport2;
    /*********************分界  上面老结构体  下面V40扩展*******************/
    pinfo->byLicensed = _pDevInfo_V40->byLicensed;
    pinfo->bySystemMode = _pDevInfo_V40->bySystemMode;
    pinfo->byControllerType = _pDevInfo_V40->byControllerType;
    strncpy(pinfo->szEhmoeVersion, _pDevInfo_V40->szEhmoeVersion, sizeof(_pDevInfo_V40->szEhmoeVersion));
    pinfo->bySpecificDeviceType = _pDevInfo_V40->bySpecificDeviceType;
    pinfo->dwSDKOverTLSPort = _pDevInfo_V40->dwSDKOverTLSPort;
    pinfo->bySecurityMode = _pDevInfo_V40->bySecurityMode;
    pinfo->bySDKServerStatus = _pDevInfo_V40->bySDKServerStatus;
    pinfo->bySDKOverTLSServerStatus = _pDevInfo_V40->bySDKOverTLSServerStatus;
    strncpy(pinfo->szUserName, _pDevInfo_V40->szUserName, MAX_USERNAME_LEN);
    strncpy(pinfo->szWifiMAC, _pDevInfo_V40->szWifiMAC, 20);\
    pinfo->byDataFromMulticast = _pDevInfo_V40->byDataFromMulticast;
    pinfo->bySupportEzvizUnbind = _pDevInfo_V40->bySupportEzvizUnbind;
    pinfo->bySupportCodeEncrypt = _pDevInfo_V40->bySupportCodeEncrypt;
    pinfo->bySupportPasswordResetType = _pDevInfo_V40->bySupportPasswordResetType;
    pinfo->byEZVIZBindStatus = _pDevInfo_V40->byEZVIZBindStatus;
    strncpy(pinfo->szPhysicalAccessVerification, _pDevInfo_V40->szPhysicalAccessVerification, 16);
    pinfo->wHttpsPort = _pDevInfo_V40->wHttpsPort;
    pinfo->bySupportEzvizUserToken = _pDevInfo_V40->bySupportEzvizUserToken;
    strncpy(pinfo->szDevDescEx, _pDevInfo_V40->szDevDescEx, sizeof(_pDevInfo_V40->szDevDescEx));
    strncpy(pinfo->szSerialNOEx, _pDevInfo_V40->szSerialNOEx, sizeof(_pDevInfo_V40->szSerialNOEx));
    strncpy(pinfo->szManufacturer, _pDevInfo_V40->szManufacturer, 32);
    pinfo->bySupportResetPwByPhoneNo = _pDevInfo_V40->bySupportResetPwByPhoneNo;

    if (gHwndSADP)   //gHwndSADP
    {
        ::PostMessage(gHwndSADP, MSG_FIND_DEVICE, (int)pinfo, 0);
    }

    //free(pinfo);

    return;
}

void __stdcall SadpDataCallBack(const SADP_DEVICE_INFO *_pDevInfo, void* _pUserData)
{
	//check!!
// 	if((strlenchk(_pDevInfo->szSeries) ||
// 		strlenchk(_pDevInfo->szSerialNO) || 
// 		strlenchk(_pDevInfo->szMAC) ||
// 		strlenchk(_pDevInfo->szIPv4Address) ||
// 		strlenchk(_pDevInfo->szIPv4SubnetMask) ||
// 		strlenchk(_pDevInfo->szDeviceSoftwareVersion) || 
// 		strlenchk(_pDevInfo->szDSPVersion) ||
// 		strlenchk(_pDevInfo->szBootTime)) == FALSE)
// 	{
// 		AfxMessageBox("err : params invalid!");
// 		return;
// 	}

// 	TRACE("  %d  > series=%s,deviceid=%s,hwaddr=%s,praddr=%s,subnetmask=%s,result=%d,sfwversion=%s,dspversion=%s,starttime=%s\n",
// 		result,series,deviceid,hwaddr,praddr,subnetmask,result,sfwversion,dspversion,starttime);

	SSADPINFO * pinfo;

	pinfo = (SSADPINFO*)malloc(sizeof(SSADPINFO));

	memset(pinfo, 0, sizeof(SSADPINFO));


    strncpy(pinfo->sseries, _pDevInfo->szSeries, sizeof(_pDevInfo->szSeries));
    strncpy(pinfo->szSerialNO, _pDevInfo->szSerialNO, sizeof(_pDevInfo->szSerialNO));
    strncpy(pinfo->szSerialNOEx, _pDevInfo->szSerialNO, sizeof(_pDevInfo->szSerialNO));
    strncpy(pinfo->szMac, _pDevInfo->szMAC, sizeof(_pDevInfo->szMAC));
    strncpy(pinfo->szIPv4, _pDevInfo->szIPv4Address, sizeof(_pDevInfo->szIPv4Address));
    strncpy(pinfo->szSubnetMask, _pDevInfo->szIPv4SubnetMask, sizeof(_pDevInfo->szIPv4SubnetMask));
    strncpy(pinfo->szSoftVersion, _pDevInfo->szDeviceSoftwareVersion, sizeof(_pDevInfo->szDeviceSoftwareVersion));
    strncpy(pinfo->szDSPVersion, _pDevInfo->szDSPVersion, sizeof(_pDevInfo->szDSPVersion));
    strncpy(pinfo->szBootTime, _pDevInfo->szBootTime, sizeof(_pDevInfo->szBootTime));

    strncpy(pinfo->szDevDesc, _pDevInfo->szDevDesc, sizeof(_pDevInfo->szDevDesc));
    strncpy(pinfo->szDevDescEx, _pDevInfo->szDevDesc, sizeof(_pDevInfo->szDevDesc));
    strncpy(pinfo->szOEMinfo, _pDevInfo->szOEMinfo, sizeof(_pDevInfo->szOEMinfo));
    strncpy(pinfo->szIPv4Gateway, _pDevInfo->szIPv4Gateway, sizeof(_pDevInfo->szIPv4Gateway));
    strncpy(pinfo->szIPv6Address, _pDevInfo->szIPv6Address, sizeof(_pDevInfo->szIPv6Address));
    strncpy(pinfo->szIPv6Gateway, _pDevInfo->szIPv6Gateway, sizeof(_pDevInfo->szIPv6Gateway));
    strncpy(pinfo->szBaseDesc, _pDevInfo->szBaseDesc, sizeof(_pDevInfo->szBaseDesc));
	pinfo->result	=	_pDevInfo->iResult;
	pinfo->iDevType	=	_pDevInfo->dwDeviceType;
	pinfo->wPort		=	_pDevInfo->dwPort;
	pinfo->dwNumOfEncoder	=	_pDevInfo->dwNumberOfEncoders; 
	pinfo->dwNumOfHardDisk	=	_pDevInfo->dwNumberOfHardDisk;

	pinfo->byIPv6MaskLen  =	_pDevInfo->byIPv6MaskLen;
	pinfo->bySupport	  =	_pDevInfo->bySupport; 
	pinfo->byDhcpEnabled  =	_pDevInfo->byDhcpEnabled;
    strncpy(pinfo->szCmsIPv4, _pDevInfo->szCmsIPv4, sizeof(_pDevInfo->szCmsIPv4));
	pinfo->wCmsPort = _pDevInfo->wCmsPort;
	pinfo->wHttpPort = _pDevInfo->wHttpPort;
	pinfo->wDigitalChannelNum = _pDevInfo->wDigitalChannelNum;
	pinfo->byOEMCode = _pDevInfo->byOEMCode;
	pinfo->byActivated = _pDevInfo->byActivated;
    pinfo->bySupport1 = _pDevInfo->bySupport1;
	pinfo->byHCPlatform = _pDevInfo->byHCPlatform;
	pinfo->byEnableHCPlatform = _pDevInfo->byEnableHCPlatform;
	pinfo->byModifyVerificationCode = _pDevInfo->byModifyVerificationCode;
    pinfo->byMaxBindNum = _pDevInfo->byMaxBindNum;
    pinfo->byEnableWifiEnhancement = _pDevInfo->byEnableWifiEnhancement;
    pinfo->bySupportWifiRegion = _pDevInfo->bySupportWifiRegion;
    pinfo->byWifiRegion = _pDevInfo->byWifiRegion;
    pinfo->bySupport2 = _pDevInfo->bySupport2;
	if(gHwndSADP)   //gHwndSADP
	{
		::PostMessage(gHwndSADP, MSG_FIND_DEVICE, (int)pinfo, 0);
	}
	
	//free(pinfo);

	return;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgHikSadp dialog


CDlgHikSadp::CDlgHikSadp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHikSadp::IDD, pParent)
	, m_origipasswd(_T(""))
{
	//{{AFX_DATA_INIT(CDlgHikSadp)
	m_sdevid = _T("");
	m_sversion = _T("");
	m_uport = 0;
    m_uSDKOverTLSPort = 0;
	m_smac = _T("");
	m_spsw = _T("");
	m_strSoftVersion = _T("");
	m_strPUID = _T("");
	m_strCmsPasswd = _T("");
	m_strCmsIPv6 = _T("");
	m_wCmsPort = 0;
	m_wHttpPort = 0;
    m_strWifiPassword = _T("");
    m_strWifiSSID = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_retbuf = NULL;
    m_bSyncIPCPW = FALSE;
    m_bResetPW = FALSE;
    m_bResetPWModeSecond = FALSE;
    m_bSupportGUID = FALSE;
    m_bSupportSecurityQuestion = FALSE;
    m_bSupportBind = FALSE;
    m_bEnableEnhancement = FALSE;
    m_bySupportWifiRegion = FALSE;
    m_bSupportEnhancement = FALSE;
    m_byCurrentWiriRegion = FALSE;
    m_bySupportChannelDefaultPW = FALSE;
    m_bMailBoxResetPW = FALSE;
    m_bSupportSSIDAndPasswordCfg = FALSE;
    m_bSupportEzvizUserToken = FALSE;
}


void CDlgHikSadp::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgHikSadp)
    DDX_Control(pDX, IDC_COM_DISPLAYRULE, m_CtrDisplayRule);
    DDX_Control(pDX, IDC_COM_WIFIMODE, m_CtrWifiMode);
    DDX_Control(pDX, IDC_COM_LAMP_ACTION, m_CtrLampAction);
    DDX_Control(pDX, IDC_IPADDRESS_CMS, m_addrCmsIPv4);
    DDX_Control(pDX, IDC_IPADDRESS_ADDR, m_sip);
    DDX_Control(pDX, IDC_IPADDRESS_MASK, m_smask);
    DDX_Control(pDX, IDC_IPADDRESS_GATEWAY, m_addrIPv4Gateway);
    DDX_Control(pDX, IDC_LIST_DEV_INFO, m_slist);
    DDX_Control(pDX, IDC_LIST_SUBNET_DEV_INFO, m_slistSubnet);
    DDX_Text(pDX, IDC_EDIT_DEV_SN, m_sdevid);
    DDX_Text(pDX, IDC_EDIT_IPv6_ADDRESS, m_strIPv6Adress);
    DDX_Text(pDX, IDC_EDIT_IPv6_GATEWAY, m_strIPv6Gateway);
    DDX_Text(pDX, IDC_EDIT_MASK_LEN, m_strIPv6MaskLen);
    DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_strDevDescription);
    DDX_Text(pDX, IDC_EDIT_DEV_TYPE, m_strDevType);
    DDX_Text(pDX, IDC_EDIT_PORT, m_uport);
    DDX_Text(pDX, IDC_EDIT_TLS_PORT, m_uSDKOverTLSPort);
    DDX_Text(pDX, IDC_EDIT_MAC, m_smac);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_spsw);
    DDX_Text(pDX, IDC_EDIT_SOFT_VERSION, m_strSoftVersion);
    DDX_Text(pDX, IDC_EDIT_PUID, m_strPUID);
    DDX_Text(pDX, IDC_EDIT_PW, m_strCmsPasswd);
    DDX_Text(pDX, IDC_EDIT_IPv6, m_strCmsIPv6);
    DDX_Text(pDX, IDC_EDIT_CMS_PORT, m_wCmsPort);
    DDX_Text(pDX, IDC_EDIT_DEFAULT_PW, m_origipasswd);
    DDX_Text(pDX, IDC_EDIT_HTTP_PORT, m_wHttpPort);
    DDX_Text(pDX, IDC_EDIT_WIFI_PASSWORD, m_strWifiPassword);
    DDX_Text(pDX, IDC_EDIT_WIFI_SSID, m_strWifiSSID);
    //}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgHikSadp, CDialog)
	ON_MESSAGE(MSG_FIND_DEVICE, OnTabDraw)
    ON_MESSAGE(MSG_FIND_SUBNET_DEVICE, OnTabDrawSubnet)
	//{{AFX_MSG_MAP(CDlgHikSadp)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButBack)
	ON_NOTIFY(HDN_ITEMCHANGED, IDC_LIST_DEV_INFO, OnItemchangedList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DEV_INFO, OnClickList)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_CANSEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAFE, OnButtonSafe)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_DEV, OnButtonSelectDev)
	ON_BN_CLICKED(IDC_BUTTON_CMS_SET, OnButtonCmsSet)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT_PW, OnBnClickedButtonDefaultPW)
	ON_BN_CLICKED(IDC_CHECK_DHCP, OnCheckDhcp)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_ACTIVATE_DEVICE, OnBtnActivateDevice)
	ON_BN_CLICKED(IDC_BTN_RESET_PW, OnBtnResetPw)
	ON_BN_CLICKED(IDC_BTN_SET_DISPLAY_RULE, OnBtnSetDisplayRule)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_DEV_INFO, OnCustomDrawList)
    //ON_STN_CLICKED(IDC_STATIC_PSWINPUT, OnStnClickedStaticPswinput)
    ON_BN_CLICKED(IDC_CUSTOM_FUNC, &CDlgHikSadp::OnBnClickedCustomFunc)
    ON_BN_CLICKED(IDC_BTN_HCPLATFORM, &CDlgHikSadp::OnBnClickedBtnHcplatform)
    ON_BN_CLICKED(IDC_BTN_BIND, &CDlgHikSadp::OnBnClickedBtnBind)
    ON_BN_CLICKED(IDC_BTN_WIFI_REGION, &CDlgHikSadp::OnBnClickedBtnWifiRegion)
    ON_BN_CLICKED(IDC_BTN_SEND_LAMP, &CDlgHikSadp::OnBnClickedBtnSendLamp)
    ON_BN_CLICKED(IDC_BTN_DISK_LOCATE, &CDlgHikSadp::OnBnClickedBtnDiskLocate)
    ON_BN_CLICKED(IDC_BTN_SELF_CHECK, &CDlgHikSadp::OnBnClickedBtnSelfCheck)
    ON_BN_CLICKED(IDC_BTN_SEND_LAMP, &CDlgHikSadp::OnBnClickedBtnSendLamp)
    ON_BN_CLICKED(IDC_BTN_CONFIG, &CDlgHikSadp::OnBnClickedBtnConfig)
    ON_BN_CLICKED(IDC_BTN_WIFI_PARAM_CFG, &CDlgHikSadp::OnBnClickedBtnWifiParamCfg)
    ON_BN_CLICKED(IDC_BTN_WIFI_PARAM_CHECK, &CDlgHikSadp::OnBnClickedBtnWifiParamCheck)
    ON_BN_CLICKED(IDC_BTN_EHOME_ENABLE, &CDlgHikSadp::OnBnClickedBtnEhomeEnable)
    ON_BN_CLICKED(IDC_BTN_UNBIND, &CDlgHikSadp::OnBnClickedBtnUnbind)
    ON_BN_CLICKED(IDC_BTN_UNBIND_DEL_USER, &CDlgHikSadp::OnBnClickedBtnUnbindDelUser)
	ON_BN_CLICKED(IDC_BUTTON_STARTV30, &CDlgHikSadp::OnBnClickedButtonStartv30)
	ON_BN_CLICKED(IDC_BUTTON_STARTV40, &CDlgHikSadp::OnBnClickedButtonStartv40)
	ON_BN_CLICKED(IDC_BUTTON_SET_REQINTERVAL, &CDlgHikSadp::OnBnClickedButtonSetReqinterval)
	ON_BN_CLICKED(IDC_BUTTON_SEC_QUE, &CDlgHikSadp::OnBnClickedButtonSecQue)
	ON_BN_CLICKED(IDC_BUTTON_MAIL_RESET, &CDlgHikSadp::OnBnClickedButtonMailReset)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE_INACTIVE, &CDlgHikSadp::OnBnClickedButtonRestoreInactive)
	ON_BN_CLICKED(IDC_BUTTON9, &CDlgHikSadp::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BTN_RESET_PW4, &CDlgHikSadp::OnBnClickedBtnResetPw4)
	ON_BN_CLICKED(IDC_BTN_RESET_PW2, &CDlgHikSadp::OnBnClickedBtnResetPw2)
	ON_BN_CLICKED(IDC_BTN_RESET_PW3, &CDlgHikSadp::OnBnClickedBtnResetPw3)
	ON_BN_CLICKED(IDC_BUTTON11, &CDlgHikSadp::OnBnClickedButton11)
    ON_BN_CLICKED(IDC_BTN_SET_TOKEN, &CDlgHikSadp::OnBnClickedBtnSetToken)
    ON_BN_CLICKED(IDC_BUTTON_PHONE_RESET, &CDlgHikSadp::OnBnClickedButtonPhoneReset)
    ON_NOTIFY(NM_RCLICK, IDC_LIST_DEV_INFO, &CDlgHikSadp::OnNMRClickListDevInfo)
    ON_BN_CLICKED(IDC_BUTTON_STARTV50, &CDlgHikSadp::OnBnClickedButtonStartv50)
    ON_BN_CLICKED(IDC_BUTTON_SUBNET_INQUERY, &CDlgHikSadp::OnBnClickedButtonSubnetInquery)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHikSadp message handlers

void CDlgHikSadp::OnCustomDrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	
    // Take the default processing unless we set this to something else below.
    *pResult = 0;
	
    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.
    if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
        *pResult = CDRF_NOTIFYITEMDRAW;
	}
    else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
        // This is the prepaint stage for an item. Here's where we set the
        // item's text color. Our return value will tell Windows to draw the
        // item itself, but it will use the new color we set here.
        // We'll cycle the colors through red, green, and light blue.	
        int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);

		int nold = 0;

		nold = m_slist.GetItemData(nItem);

		switch(nold) 
		{
		case 1:
			pLVCD->clrTextBk = RGB(255, 192, 203);//
			break;
		case 0:
			pLVCD->clrTextBk = RGB(255, 192, 203);//
			//pLVCD->clrTextBk = RGB(191, 191, 242);//
			break;
		default:
			pLVCD->clrTextBk = RGB(255, 192, 203);//
			//pLVCD->clrTextBk = RGB(255, 255, 255);
			break;
		}
        // Store the color back in the NMLVCUSTOMDRAW struct.
			
        // Tell Windows to paint the control itself.
        *pResult = CDRF_DODEFAULT;
	}
}

BOOL CDlgHikSadp::OnInitDialog() 
{
	CDialog::OnInitDialog();

	DWORD dwSadpVersion = SADP_GetSadpVersion();

	CString csTemp = _T("");
	csTemp.Format("V%d.%d.%d.%d", (0xff000000 & dwSadpVersion)>>24, (0x00ff0000 & dwSadpVersion)>>16,\
		(0x0000ff00 & dwSadpVersion)>>8, (0x000000ff & dwSadpVersion));

	GetDlgItem(IDC_STATIC_SADP_VERSION)->SetWindowText(csTemp);
	GetDlgItem(IDC_BUTTON_SELECT_DEV)->SetWindowText("Start") ;


	// TODO: Add extra initialization here
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	
#ifdef Single
	GetDlgItem(IDC_BUTTON_SELECT_DEV)->ShowWindow(SW_HIDE);
#else
	GetDlgItem(IDC_BUTTON_SELECT_DEV)->ShowWindow(SW_SHOW);
#endif

	m_brun	 = FALSE;
	m_bedit	 = FALSE;
	m_icount = 1;
    m_icountSubnet = 1;
    m_bSyncIPCPW = FALSE;
    m_bSupportBind = FALSE;
    m_bEnableEnhancement = FALSE;
    m_bySupportWifiRegion = FALSE;
    m_byCurrentWiriRegion = FALSE;
    m_bSupportEnhancement = FALSE;
    m_bySupportChannelDefaultPW = FALSE;
	m_sip.SetAddress(0,0,0,0);
	m_smask.SetAddress(0,0,0,0);
	m_dwsip = 0;
	m_dwsmask = 0;

	// Judge the default lanuage ID of Windows System
//     WORD wLangID=PRIMARYLANGID(::GetSystemDefaultLangID());
// 
//     switch(wLangID)
//     {
// 		case LANG_CHINESE:
// 			m_ilanguage = 0;
// 			break;
//         case LANG_ENGLISH:
// 		default:
// 			m_ilanguage = 1;
// 			break;
// 	}
    //
    m_ilanguage = 1;
	//set text!
//	m_ilanguage = g_nLanguageType;
	
	gHwndSADP = this->GetSafeHwnd();
	GetDlgItem(IDC_IPADDRESS_MASK)->EnableWindow(FALSE);
	GetDlgItem(IDC_IPADDRESS_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_IPADDRESS_GATEWAY)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_IPv6_ADDRESS)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_IPv6_GATEWAY)->EnableWindow(TRUE);

	
	m_btnDhcp = (CButton*)GetDlgItem(IDC_CHECK_DHCP);
	m_btnDhcp->SetCheck(FALSE);
	m_btnDhcp->EnableWindow(FALSE);

	((CEdit *)GetDlgItem(IDC_EDIT_PORT))->SetLimitText(5);
	((CEdit *)GetDlgItem(IDC_EDIT_PASSWORD))->SetLimitText(32);
	((CEdit *)GetDlgItem(IDC_EDIT_DEFAULT_PW))->SetLimitText(32);

	CString strTemp = _T("");

    //-------------------------跨网段搜索-----------------------------------
    strTemp.Format("%s", GetText(59));
    m_slistSubnet.InsertColumn(0, GetText(59), LVCFMT_CENTER, 30);

    strTemp.Format("%s", GetText(42));//设备类型描述
    m_slistSubnet.InsertColumn(1, strTemp, LVCFMT_LEFT, 100);

    strTemp.Format("%s", GetText(33));//设备IPv4地址
    m_slistSubnet.InsertColumn(2, strTemp, LVCFMT_LEFT, 100);

    strTemp.Format("%s", GetText(35));//设备序列号
    m_slistSubnet.InsertColumn(3, strTemp, LVCFMT_LEFT, 240);

    strTemp.Format("%s", GetText(36));//设备IPv4子网掩码
    m_slistSubnet.InsertColumn(4, strTemp, LVCFMT_LEFT, 100);

    strTemp.Format("%s", GetText(44));//IPv4网关
    m_slistSubnet.InsertColumn(5, strTemp, LVCFMT_LEFT, 140);

    strTemp.Format("%s", GetText(45));//IPv6地址
    m_slistSubnet.InsertColumn(6, strTemp, LVCFMT_LEFT, 140);

    strTemp.Format("%s", GetText(46));//IPv6网关
    m_slistSubnet.InsertColumn(7, strTemp, LVCFMT_LEFT, 140);

    strTemp.Format("%s", GetText(47));//IPv6子网前缀长度
    m_slistSubnet.InsertColumn(8, strTemp, LVCFMT_LEFT, 140);

    strTemp.Format("%s", GetText(48));//是否支持IPv6
    m_slistSubnet.InsertColumn(9, strTemp, LVCFMT_LEFT, 140);

    strTemp.Format("%s", GetText(50));//是否支持修改IPv6
    m_slistSubnet.InsertColumn(10, strTemp, LVCFMT_LEFT, 140);

    strTemp.Format("%s", GetText(51));//是否支持Dhcp
    m_slistSubnet.InsertColumn(11, strTemp, LVCFMT_LEFT, 140);

    strTemp.Format("%s", GetText(49));//Dhcp状态
    m_slistSubnet.InsertColumn(12, strTemp, LVCFMT_LEFT, 140);
    //-------------------------跨网段搜索-----------------------------------
	strTemp.Format("%s",GetText(59));
	m_slist.InsertColumn(0, GetText(59), LVCFMT_CENTER, 30);
	strTemp.Format("%s",GetText(42));
	m_slist.InsertColumn(1, strTemp, LVCFMT_LEFT, 100);
	strTemp.Format("%s",GetText(33));
	m_slist.InsertColumn(2, strTemp, LVCFMT_LEFT, 100);
	strTemp.Format("%s",GetText(34));
	m_slist.InsertColumn(3, strTemp, LVCFMT_LEFT, 80);
	strTemp.Format("%s",GetText(35));
	m_slist.InsertColumn(4, strTemp, LVCFMT_LEFT, 240);
	strTemp.Format("%s",GetText(36));
	m_slist.InsertColumn(5, strTemp, LVCFMT_LEFT, 100);
	strTemp.Format("%s",GetText(37));
	m_slist.InsertColumn(6, strTemp, LVCFMT_LEFT, 140);
	strTemp.Format("%s",GetText(38));
	m_slist.InsertColumn(7, strTemp, LVCFMT_LEFT, 100);
	strTemp.Format("%s",GetText(39));
	m_slist.InsertColumn(8, strTemp, LVCFMT_LEFT, 140);
	strTemp.Format("%s",GetText(40));
	m_slist.InsertColumn(9, strTemp,LVCFMT_LEFT,140);
	strTemp.Format("%s",GetText(41));
	m_slist.InsertColumn(10,strTemp,LVCFMT_LEFT,140);
	strTemp.Format("%s",GetText(44));
	m_slist.InsertColumn(11,strTemp,LVCFMT_LEFT,140);
	strTemp.Format("%s",GetText(45));
	m_slist.InsertColumn(12,strTemp,LVCFMT_LEFT,140);
	strTemp.Format("%s",GetText(46));
	m_slist.InsertColumn(13,strTemp,LVCFMT_LEFT,140);
	strTemp.Format("%s",GetText(47));
	m_slist.InsertColumn(14,strTemp,LVCFMT_LEFT,140);
	strTemp.Format("%s",GetText(48));
	m_slist.InsertColumn(15,strTemp,LVCFMT_LEFT,140);
	strTemp.Format("%s",GetText(49));
	m_slist.InsertColumn(16,strTemp,LVCFMT_LEFT,140);
	strTemp.Format("%s",GetText(50));
	m_slist.InsertColumn(17,strTemp,LVCFMT_LEFT,140);
	strTemp.Format("%s",GetText(51));
	m_slist.InsertColumn(18,strTemp,LVCFMT_LEFT,140);

	//CMS IPv4
	strTemp.Format("%s",GetText(52));
	m_slist.InsertColumn(19,strTemp,LVCFMT_LEFT,140);

	//CMS Port
	strTemp.Format("%s",GetText(53));
	m_slist.InsertColumn(20,strTemp,LVCFMT_LEFT,140);

	//Digital Channel Number
	strTemp.Format("%s",GetText(54));
	m_slist.InsertColumn(21,strTemp,LVCFMT_LEFT,140);
	
	//Http port
	strTemp.Format("%s",GetText(55));
	m_slist.InsertColumn(22,strTemp,LVCFMT_LEFT,100);

	//OEM Code
	strTemp.Format("%s",GetText(56));
	m_slist.InsertColumn(23,strTemp,LVCFMT_LEFT,100);

	//OEM info
	strTemp.Format("%s",GetText(57));
	m_slist.InsertColumn(24,strTemp,LVCFMT_LEFT,100);


	strTemp.Format("%s",GetText(60));
	m_slist.InsertColumn(25,strTemp,LVCFMT_LEFT,100);

	//Password Restore
	strTemp.Format("%s", GetText(63));
	m_slist.InsertColumn(26, strTemp, LVCFMT_LEFT, 100);
	//Activate state
	strTemp.Format("%s", GetText(64));
	m_slist.InsertColumn(27, strTemp, LVCFMT_LEFT, 100);
	//Password Reset
	strTemp.Format("%s", GetText(65));
	m_slist.InsertColumn(28, strTemp, LVCFMT_LEFT, 100);
    //是否同步密码到IPC 
    strTemp.Format("%s", "支持同步IPC密码");
	m_slist.InsertColumn(29, strTemp, LVCFMT_LEFT, 120);


    //是否重置密码方式2 
    strTemp.Format("%s", "支持重置密码方式2");
	m_slist.InsertColumn(30, strTemp, LVCFMT_LEFT, 120);

    //是否支持导入GUID重置密码 
    strTemp.Format("%s", "支持导入GUID");
    m_slist.InsertColumn(31, strTemp, LVCFMT_LEFT, 120);

    //是否支持安全问题重置密码 
    strTemp.Format("%s", "支持安全问题");
    m_slist.InsertColumn(32, strTemp, LVCFMT_LEFT, 120);


	//HCPlatform
	strTemp.Format("%s", GetText(66));
	m_slist.InsertColumn(33, strTemp, LVCFMT_LEFT, 120);
	//HCPlatform Status
	strTemp.Format("%s", GetText(67));
	m_slist.InsertColumn(34, strTemp, LVCFMT_LEFT, 120);
	//Verification Code
	strTemp.Format("%s", GetText(68));
	m_slist.InsertColumn(35, strTemp, LVCFMT_LEFT, 120);

    //Bind
    strTemp.Format("%s", GetText(69));
    m_slist.InsertColumn(36, strTemp, LVCFMT_LEFT, 120);
    //Max Bind Num
    strTemp.Format("%s", GetText(70));
    m_slist.InsertColumn(37, strTemp, LVCFMT_LEFT, 120);
    //Restore Inactive
    strTemp.Format("%s", GetText(71));
    m_slist.InsertColumn(38, strTemp, LVCFMT_LEFT, 120);

    //support wifi Enhancement
    strTemp.Format("%s", GetText(72));
    m_slist.InsertColumn(39, strTemp, LVCFMT_LEFT, 120);
    //Enable wifi Enhancement
    strTemp.Format("%s", GetText(73));
    m_slist.InsertColumn(40, strTemp, LVCFMT_LEFT, 120);
    //support wifi Region
    strTemp.Format("%s", GetText(74));
    m_slist.InsertColumn(41, strTemp, LVCFMT_LEFT, 80);
    //current wifi Region
    strTemp.Format("%s", GetText(75));
    m_slist.InsertColumn(42, strTemp, LVCFMT_LEFT, 120);

    //设备是否授权
    strTemp.Format("%s", "设备是否授权");
    m_slist.InsertColumn(43, strTemp, LVCFMT_LEFT, 120);
    //系统模式
    strTemp.Format("%s", "系统模式");
    m_slist.InsertColumn(44, strTemp, LVCFMT_LEFT, 80);
    //控制器类型
    strTemp.Format("%s", "控制器类型");
    m_slist.InsertColumn(45, strTemp, LVCFMT_LEFT, 80);
    //support channel default PW
    strTemp.Format("%s", GetText(76));
    m_slist.InsertColumn(46, strTemp, LVCFMT_LEFT, 120);
    //EHome版本
    strTemp.Format("%s", "EHome版本号");
    m_slist.InsertColumn(47, strTemp, LVCFMT_LEFT, 80);

    //SupportMailBoxResetPassword
    strTemp.Format("%s", "SupportMailBoxResetPW");
    m_slist.InsertColumn(48, strTemp, LVCFMT_LEFT, 120);

    //是否支持未激活配置SSID和Password
    strTemp.Format("%s", "是否支持未激活配置SSID和Password");
    m_slist.InsertColumn(49, strTemp, LVCFMT_LEFT, 220);

    //设备类型
    strTemp.Format("%s", "设备类型(中性/海康)");
    m_slist.InsertColumn(50, strTemp, LVCFMT_LEFT, 130);

    //tls端口
    strTemp.Format("%s", "TLS端口");
    m_slist.InsertColumn(51, strTemp, LVCFMT_LEFT, 100);

    //设备安全模式：0-standard,1-high-A,2-high-B,3-custom
    strTemp.Format("%s", "设备安全模式");
    m_slist.InsertColumn(52, strTemp, LVCFMT_LEFT, 100);

    //设备SDK服务状态, 0-开启，1-关闭
    strTemp.Format("%s", "SDK服务状态");
    m_slist.InsertColumn(53, strTemp, LVCFMT_LEFT, 100);

    //设备SDKOverTLS服务状态, 0-关闭，1-开启
    strTemp.Format("%s", "SDKOverTLS服务状态");
    m_slist.InsertColumn(54, strTemp, LVCFMT_LEFT, 150);

    //管理员用户用户名
    strTemp.Format("%s", "管理员用户用户名");
    m_slist.InsertColumn(55, strTemp, LVCFMT_LEFT, 150);

    //协议类型
    strTemp.Format("%s", "协议类型");
    m_slist.InsertColumn(56, strTemp, LVCFMT_LEFT, 50);

    //设备所连wifi的Mac地址
    strTemp.Format("%s", "Wifi的Mac地址");
    m_slist.InsertColumn(57, strTemp, LVCFMT_LEFT, 120);

    //是否支持萤石解绑
    strTemp.Format("%s", "是否支持萤石解绑");
    m_slist.InsertColumn(58, strTemp, LVCFMT_LEFT, 120);

    //是否支持重置口令AES128_ECB解密
    strTemp.Format("%s", "是否支持重置口令AES128_ECB解密");
    m_slist.InsertColumn(59, strTemp, LVCFMT_LEFT, 200);

    //是否支持获取密码重置方式参数
    strTemp.Format("%s", "是否支持获取密码重置方式参数");
    m_slist.InsertColumn(60, strTemp, LVCFMT_LEFT, 200);

    //设备萤石云绑定状态
    strTemp.Format("%s", "设备萤石云绑定状态");
    m_slist.InsertColumn(61, strTemp, LVCFMT_LEFT, 200);

    //设备支持的物理接触式添加方式
    strTemp.Format("%s", "设备支持的物理接触式添加方式");
    m_slist.InsertColumn(62, strTemp, LVCFMT_LEFT, 200);

    //Https端口
    strTemp.Format("%s", "Https Port");
    m_slist.InsertColumn(63, strTemp, LVCFMT_LEFT, 200);

    //设备接入萤石云版本
    strTemp.Format("%s", "是否支持萤石用户token配置");
    m_slist.InsertColumn(64, strTemp, LVCFMT_LEFT, 200);

    //设备厂商信息
    strTemp.Format("%s", "设备厂商");
    m_slist.InsertColumn(65, strTemp, LVCFMT_LEFT, 200);

    //手机扫码重置密码
    strTemp.Format("%s", "手机扫码重置密码");
    m_slist.InsertColumn(66, strTemp, LVCFMT_LEFT, 200);

    //设备类型
    strTemp.Format("%s", "设备类型");
    m_slist.InsertColumn(67, strTemp, LVCFMT_LEFT, 120);

	((CEdit *)GetDlgItem(IDC_EDIT_PASSWORD))->SetLimitText(32);

	m_slist.SetExtendedStyle(m_slist.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_slistSubnet.SetExtendedStyle(m_slist.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_CtrDisplayRule.SetCurSel(0);
    m_CtrWifiMode.SetCurSel(0);
    m_CtrLampAction.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHikSadp::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_brun)
	{
		TRACE("STOP");
		SADP_Stop();
	}

	gHwndSADP = NULL;
	m_devlist.RemoveAll();
}

void CDlgHikSadp::fInsDevice(char *dvrip)
{
	SSADPDEV sdev;

	if(strlen(dvrip)<20)
	{
		strcpy(sdev.cdev, dvrip);
		m_devlist.AddTail(sdev);
	}

	return;
}

void CDlgHikSadp::fSetRetBuf(SSADPRET * pbuf)
{

	m_retbuf = pbuf;

	return;
}

BOOL CDlgHikSadp::fIfInUsed(char * sip)
{
	BOOL bret=FALSE;
	SSADPDEV stmp1,stmp2;
	
	memset(&stmp1, 0, sizeof(SSADPDEV));
	strcpy(stmp1.cdev, sip);

	POSITION pos = m_devlist.GetHeadPosition();
	for (int i=0;i < m_devlist.GetCount();i++)
	{
	   stmp2 = m_devlist.GetNext(pos);

	   if(0==strcmp(stmp2.cdev, stmp1.cdev))
	   {
			bret=TRUE;
		   break;
	   }
	}


	return bret;
}

LRESULT CDlgHikSadp::OnTabDrawSubnet(WPARAM wParam, LPARAM lParam)
{
    SADP_SUBNET_DEVICE_INFO * pinfo;
    pinfo = (SADP_SUBNET_DEVICE_INFO*)wParam;
    fSubnetDevOnLine(pinfo);
    free(pinfo);
    return 0;
}

LRESULT CDlgHikSadp::OnTabDraw(WPARAM wParam, LPARAM lParam)
{
    SSADPINFO * pinfo;
    CString str = _T("");

    pinfo = (SSADPINFO*)wParam;

    switch (pinfo->result)
    {
    case SADP_RESTART:
    case SADP_ADD:
        fDevOnLine(pinfo);
        break;
    case SADP_DEC:
        fDevOffLine(pinfo);
        break;
    case SADP_UPDATE:
        fDevRefresh(pinfo);
        str.Format(GetText(26));
        GetDlgItem(IDC_STA_STATE)->SetWindowText(str);
        break;
    case SADP_UPDATEFAIL:
        str.Format(GetText(27));
        GetDlgItem(IDC_STA_STATE)->SetWindowText(str);
        m_uport = atoi(g_csPort);
        m_uSDKOverTLSPort = atoi(g_csSDKOverTLSPort);
        GetDlgItem(IDC_IPADDRESS_MASK)->SetWindowText(g_csMask);
        GetDlgItem(IDC_IPADDRESS_ADDR)->SetWindowText(g_csIP);
        UpdateData(FALSE);
        break;
    default:
        OutputDebugString("unknow result!\n");
        break;
    }

    free(pinfo);
    return 0;
}

void CDlgHikSadp::fDevOnLine(SSADPINFO *pinfo)
{
    //To determine whether the device has been added
	BOOL bused;

	bused = fIfInUsed(pinfo->szMac);

    //Check whether repeat the insert
	CString strListMAC, strAddMAC;
	BOOL bbingo = FALSE;
	
	strAddMAC = pinfo->szMac;


	for(int i=0;i<m_slist.GetItemCount();i++)
	{
		strListMAC = m_slist.GetItemText(i, 6);
		
		if(strListMAC == strAddMAC) 
		{
			bbingo = TRUE;
			break;
		}
	}

	if(bbingo) 
	{
        OutputDebugString("wrong 003(Repeat insert!!!)\n");
		return ;
	}

	//Insert List
	int item;
	char tbuf[32];
//	char tbuf1[32];

	sprintf(tbuf,"%03d",m_icount);
	
 	item=m_slist.InsertItem(50000, tbuf);

// 	CString strDevType = _T("");
// 	strDevType = F_GetDeviceTypeName(pinfo->dev_type);
// 	sprintf(tbuf1,"%s",strDevType);
// 	m_slist.SetItemText(item,1,tbuf1);

	m_slist.SetItemText(item,1,(const char*)pinfo->szDevDescEx);
	m_slist.SetItemText(item,2,pinfo->szIPv4);
	sprintf(tbuf,"%ld",pinfo->wPort);
	m_slist.SetItemText(item,3,tbuf);
	m_slist.SetItemText(item,4,pinfo->szSerialNOEx);
	m_slist.SetItemText(item,5,pinfo->szSubnetMask);
	m_slist.SetItemText(item,6,pinfo->szMac);
	m_slist.SetItemText(item,8,pinfo->szSoftVersion);

	sprintf(tbuf,"%d",pinfo->dwNumOfEncoder);
	m_slist.SetItemText(item,7,tbuf);
	m_slist.SetItemText(item,9,pinfo->szDSPVersion);
	m_slist.SetItemText(item,10,pinfo->szBootTime);


	m_slist.SetItemText(item,11,(const char*)pinfo->szIPv4Gateway);
	m_slist.SetItemText(item,12,(const char*)pinfo->szIPv6Address);
	m_slist.SetItemText(item,13,(const char*)pinfo->szIPv6Gateway);

	sprintf(tbuf,"%d",pinfo->byIPv6MaskLen);
	m_slist.SetItemText(item,14,tbuf);
	sprintf(tbuf,"%d",pinfo->bySupport);
	m_slist.SetItemText(item,15,tbuf);
	
	if (1 == pinfo->byDhcpEnabled)
	{
		m_slist.SetItemText(item,16,"ON");
	}
	else 
	{
		m_slist.SetItemText(item,16,"OFF");
	}

	//support IPv6
	if (pinfo->bySupport & 0x1)
	{
		m_slist.SetItemText(item, 15, "support");
	}
	else
	{
		m_slist.SetItemText(item, 15, "not support");	
	}
	
	//support  modify IPv6
	if (pinfo->bySupport & 0x2)
	{
		m_slist.SetItemText(item, 17, "support");
	}
	else
	{
		m_slist.SetItemText(item, 17, "not support");	
	}
	
	
	//support DHCP
	if (pinfo->bySupport & 0x4)
	{
		m_slist.SetItemText(item, 18, "support");
	}
	else
	{
		m_slist.SetItemText(item, 18, "not support");	
	}


	sprintf(tbuf,"%s",pinfo->szCmsIPv4);
	m_slist.SetItemText(item,19,tbuf);

	sprintf(tbuf,"%d",pinfo->wCmsPort);
	m_slist.SetItemText(item,20,tbuf);

	sprintf(tbuf,"%d",pinfo->wDigitalChannelNum);
	m_slist.SetItemText(item,21,tbuf);

	sprintf(tbuf,"%d",pinfo->wHttpPort);
	m_slist.SetItemText(item,22,tbuf);

	sprintf(tbuf,"%d",pinfo->byOEMCode);
	m_slist.SetItemText(item,23,tbuf);

	m_slist.SetItemText(item,24,(const char*)pinfo->szOEMinfo);

	m_slist.SetItemText(item,25,(const char*)pinfo->szBaseDesc);
	
	//support Restore Password
	if (pinfo->bySupport & 0x20)
	{
		m_slist.SetItemText(item, 26, "support");
	}
	else
	{
		m_slist.SetItemText(item, 26, "not support");	
	}
	//Activate state
	if (pinfo->byActivated == 0)
	{
        m_slist.SetItemText(item, 27, "Activated");
	}
	else if (pinfo->byActivated == 1)
	{
        m_slist.SetItemText(item, 27, "Not Activated");
	}
	
	//support password reset
	if (pinfo->bySupport & 0x40)
	{
		m_slist.SetItemText(item, 28, "support");
	}
	else
	{
		m_slist.SetItemText(item, 28, "not support");	
	}
    //是否支持同步密码到IPC
    if (pinfo->bySupport & 0x80)
    {
        m_slist.SetItemText(item, 29, "support");
    }
    else
    {
        m_slist.SetItemText(item, 29, "not support");	
	}

    //是否支持重置密码方式2
    if ((pinfo->bySupport1 & 0x01))
    {
        m_slist.SetItemText(item, 30, "support");
    }
    else
    {
        m_slist.SetItemText(item, 30, "not support");	
	}

    //是否支持导入GUID重置密码
    if ((pinfo->bySupport1 & 0x04))
    {
        m_slist.SetItemText(item, 31, "support");
    }
    else
    {
        m_slist.SetItemText(item, 31, "not support");
    }

    //是否支持安全问题重置密码
    if ((pinfo->bySupport1 & 0x08))
    {
        m_slist.SetItemText(item, 32, "support");
    }
    else
    {
        m_slist.SetItemText(item, 32, "not support");
    }
	//HCPlatform
	if (1 == pinfo->byHCPlatform)
	{
		m_slist.SetItemText(item, 33, "support");
	}
	else if (2 == pinfo->byHCPlatform)
	{
		m_slist.SetItemText(item, 33, "not support");
	}
	else
	{
		m_slist.SetItemText(item, 33, "NA");
	}
	//EnableHCPlatform
	if (1 == pinfo->byEnableHCPlatform)
	{
		m_slist.SetItemText(item, 34, "support");
	}
	else if (2 == pinfo->byEnableHCPlatform)
	{
		m_slist.SetItemText(item, 34, "not support");
	}
	else
	{
		m_slist.SetItemText(item, 34, "NA");
	}
	//ModifyVerificationCode
	if (1 == pinfo->byModifyVerificationCode)
	{
		m_slist.SetItemText(item, 35, "modify");
	}
	else if (2 == pinfo->byModifyVerificationCode)
	{
		m_slist.SetItemText(item, 35, "not modify");
	}
	else
	{
		m_slist.SetItemText(item, 35, "NA");
	}

    //是否支持绑定设备
    if ((pinfo->bySupport1 & 0x20))
    {
        m_slist.SetItemText(item, 36, "support");
    }
    else
    {
        m_slist.SetItemText(item, 36, "not support");
    }
    //最大绑定个数
    sprintf(tbuf, "%ld", pinfo->byMaxBindNum);
    m_slist.SetItemText(item, 37, tbuf);
    //是否支持恢复未激活
    if ((pinfo->bySupport1 & 0x40))
    {
        m_slist.SetItemText(item, 38, "support");
    }
    else
    {
        m_slist.SetItemText(item, 38, "not support");
    }

    //support wifi Enhancement
    if ((pinfo->bySupport1 & 0x80))
    {
        m_slist.SetItemText(item, 39, "support");
    }
    else
    {
        m_slist.SetItemText(item, 39, "not support");
    }
  
    //Enable wifi Enhancement
    if (1 == pinfo->byEnableWifiEnhancement)
    {
        m_slist.SetItemText(item, 40, "True");
    }
    else 
    {
        m_slist.SetItemText(item, 40, "False");
    }
    //support wifi Region

    sprintf(tbuf, "0x%x", pinfo->bySupportWifiRegion);
    m_slist.SetItemText(item, 41, tbuf);
    //current wifi Region
    //0 - default，1 - china，2 - nothAmerica，3 - japan，4 - europe, 5 - world
    if (0 == pinfo->byWifiRegion)
    {
        m_slist.SetItemText(item, 42, "default");
    }
    else if (1 == pinfo->byWifiRegion)
    {
        m_slist.SetItemText(item, 42, "china");
    }
    else if (2 == pinfo->byWifiRegion)
    {
        m_slist.SetItemText(item, 42, "nothAmerica");
    }
    else if (3 == pinfo->byWifiRegion)
    {
        m_slist.SetItemText(item, 42, "japan");
    }
    else if (4 == pinfo->byWifiRegion)
    {
        m_slist.SetItemText(item, 42, "europe");
    }
    else if (5 == pinfo->byWifiRegion)
    {
        m_slist.SetItemText(item, 42, "world");
    }

    //设备是否授权
    if ((pinfo->byLicensed == 2))
    {
        m_slist.SetItemText(item, 43, "authorized");
    }
    else if((pinfo->byLicensed == 1))
    {
        m_slist.SetItemText(item, 43, "unauthorized");
    }
    else
    {
        m_slist.SetItemText(item, 43, "default");
    }

    //系统模式
    if ((pinfo->bySystemMode == 1))
    {
        m_slist.SetItemText(item, 44, "single");
    }
    else if ((pinfo->bySystemMode == 2))
    {
        m_slist.SetItemText(item, 44, "double");
    }
    else if ((pinfo->bySystemMode == 3))
    {
        m_slist.SetItemText(item, 44, "singleCluster");
    }
    else if ((pinfo->bySystemMode == 4))
    {
        m_slist.SetItemText(item, 44, "doubleCluster");
    }
    else
    {
        m_slist.SetItemText(item, 44, "default");
    }

    //控制器类型
    if ((pinfo->byControllerType == 1))
    {
        m_slist.SetItemText(item, 45, "A");
    }
    else if ((pinfo->byControllerType == 2))
    {
        m_slist.SetItemText(item, 45, "B");
    }
    else
    {
        m_slist.SetItemText(item, 45, "default");
    }

    //support channel default pw
    if ((pinfo->bySupport2 & 0x1))
    {
        m_slist.SetItemText(item, 46, "support");
    }
    else
    {
        m_slist.SetItemText(item, 46, "not support");
    }

    //EHome版本号
    m_slist.SetItemText(item, 47, pinfo->szEhmoeVersion);

    //Support MailBox Reset Password
    if ((pinfo->bySupport2 & 0x2))
    {
        m_slist.SetItemText(item, 48, "support");
    }
    else
    {
        m_slist.SetItemText(item, 48, "not support");
    }

    //是否支持未激活配置SSID和Password
    if ((pinfo->bySupport2 & 0x4))
    {
        m_slist.SetItemText(item, 49, "support");
    }
    else
    {
        m_slist.SetItemText(item, 49, "not support");
    }

    if (pinfo->bySpecificDeviceType == 1)
    {
        sprintf(tbuf, "%s", "中性");
        m_slist.SetItemText(item, 50, tbuf);
    }
    else if (pinfo->bySpecificDeviceType == 2)
    {
        sprintf(tbuf, "%s", "海康");
        m_slist.SetItemText(item, 50, tbuf);
    }
    else
    {
        sprintf(tbuf, "%s", "未识别");
        m_slist.SetItemText(item, 50, tbuf);
    }

    sprintf(tbuf, "%ld", pinfo->dwSDKOverTLSPort);
    m_slist.SetItemText(item, 51, tbuf); 

    if (pinfo->bySecurityMode == 0)
    {
        sprintf(tbuf, "%s", "standard");
        m_slist.SetItemText(item, 52, tbuf);
    }
    else if (pinfo->bySecurityMode == 1)
    {
        sprintf(tbuf, "%s", "high-A");
        m_slist.SetItemText(item, 52, tbuf);
    }
    else if (pinfo->bySecurityMode == 2)
    {
        sprintf(tbuf, "%s", "high-B");
        m_slist.SetItemText(item, 52, tbuf);
    }
    else if (pinfo->bySecurityMode == 3)
    {
        sprintf(tbuf, "%s", "custom");
        m_slist.SetItemText(item, 52, tbuf);
    }
    else
    {
        sprintf(tbuf, "%s", "未识别");
        m_slist.SetItemText(item, 52, tbuf);
    }


    if (pinfo->bySDKServerStatus == 0)
    {
        sprintf(tbuf, "%s", "开启");
        m_slist.SetItemText(item, 53, tbuf);
    }
    else if (pinfo->bySDKServerStatus == 1)
    {
        sprintf(tbuf, "%s", "关闭");
        m_slist.SetItemText(item, 53, tbuf);
    }

    if (pinfo->bySDKOverTLSServerStatus == 0)
    {
        sprintf(tbuf, "%s", "关闭");
        m_slist.SetItemText(item, 54, tbuf);
    }
    else if (pinfo->bySDKOverTLSServerStatus == 1)
    {
        sprintf(tbuf, "%s", "开启");
        m_slist.SetItemText(item, 54, tbuf);
    }

    //管理员用户用户名
    sprintf(tbuf, "%s", pinfo->szUserName);
    m_slist.SetItemText(item, 55, tbuf);

    //协议类型
    sprintf(tbuf, "%d", pinfo->byDataFromMulticast);
    m_slist.SetItemText(item, 56, tbuf);

    //设备所连wifi的Mac地址
    m_slist.SetItemText(item, 57, pinfo->szWifiMAC);

    //是否支持萤石账号解绑
    sprintf(tbuf, "%d", pinfo->bySupportEzvizUnbind);
    m_slist.SetItemText(item, 58, tbuf);

    //是否支持重置口令AES128_ECB解密
    sprintf(tbuf, "%d", pinfo->bySupportCodeEncrypt);
    m_slist.SetItemText(item, 59, tbuf);

    //是否支持获取密码重置方式参数
    sprintf(tbuf, "%d", pinfo->bySupportPasswordResetType);
    m_slist.SetItemText(item, 60, tbuf);

    //萤石云绑定状态
    sprintf(tbuf, "%d", pinfo->byEZVIZBindStatus);
    m_slist.SetItemText(item, 61, tbuf);

    //萤石云物理接触式添加方式
    sprintf(tbuf, "%s", pinfo->szPhysicalAccessVerification);
    m_slist.SetItemText(item, 62, tbuf);

    //Https 端口
    sprintf(tbuf, "%d", pinfo->wHttpsPort);
    m_slist.SetItemText(item, 63, tbuf);

    //萤石用户token配置
    sprintf(tbuf, "%d", pinfo->bySupportEzvizUserToken);
    m_slist.SetItemText(item, 64, tbuf);

    //设备厂商信息
    sprintf(tbuf, "%s", pinfo->szManufacturer);
    m_slist.SetItemText(item, 65, tbuf);

    //手机扫码重置密码
    sprintf(tbuf, "%d", pinfo->bySupportResetPwByPhoneNo);
    m_slist.SetItemText(item, 66, tbuf);

    //设备类型
    sprintf(tbuf, "%d", pinfo->iDevType);
    m_slist.SetItemText(item, 67, tbuf);

	m_slist.SetItemData(item,bused?0:1);

	m_icount++;
}

void CDlgHikSadp::fDevOffLine(SSADPINFO *pinfo)
{
	//Delete list

	CString strDelMAC, strListMAC;
	BOOL bbingo = FALSE;

	strDelMAC = pinfo->szMac;


	for(int i=0; i<m_slist.GetItemCount(); i++)
	{
		strListMAC = m_slist.GetItemText(i, 6);

        if(strDelMAC == strListMAC) 
		{
			m_slist.DeleteItem(i);
			bbingo = TRUE;
			break;
		}
	}

	if(!bbingo) 
	{
		OutputDebugString("Delete item failed\n");
	}
    m_icount--;
}

void CDlgHikSadp::fDevReboot(SSADPINFO *pinfo)
{
	return;
}

void CDlgHikSadp::fDevRefresh(SSADPINFO *pinfo)
{
	//Modify list

	CString  strUpdateMAC, strListMAC;
	BOOL bbingo=FALSE;

    strUpdateMAC = pinfo->szMac;

	for(int i=0;i<m_slist.GetItemCount();i++)
	{

		strListMAC = m_slist.GetItemText(i, 6);

		if((strUpdateMAC == strListMAC)) 
		{
			char tbuf[32];
			m_slist.SetItemText(i,1,(const char*)pinfo->szDevDescEx);
			m_slist.SetItemText(i,2,pinfo->szIPv4);
			sprintf(tbuf,"%ld",pinfo->wPort);
			m_slist.SetItemText(i,3,tbuf);
			m_slist.SetItemText(i,4,pinfo->szSerialNOEx);
			m_slist.SetItemText(i,5,pinfo->szSubnetMask);
			m_slist.SetItemText(i,6,pinfo->szMac);
			sprintf(tbuf,"%d",pinfo->dwNumOfEncoder);
			m_slist.SetItemText(i,7,tbuf);
			m_slist.SetItemText(i,8,pinfo->szSoftVersion);
			m_slist.SetItemText(i,9,pinfo->szDSPVersion);
			m_slist.SetItemText(i,10,pinfo->szBootTime);

			m_slist.SetItemText(i,11,(const char*)pinfo->szIPv4Gateway);
			m_slist.SetItemText(i,12,(const char*)pinfo->szIPv6Address);
			m_slist.SetItemText(i,13,(const char*)pinfo->szIPv6Gateway);
			
			sprintf(tbuf,"%d",pinfo->byIPv6MaskLen);
			m_slist.SetItemText(i,14,tbuf);

			
			if (1 == pinfo->byDhcpEnabled)
			{
				m_slist.SetItemText(i,16,"ON");
			}
			else 
			{
				m_slist.SetItemText(i,16,"OFF");
			}

			//support IPv6
			if (pinfo->bySupport & 0x1)
			{
				m_slist.SetItemText(i, 15, "support");
			}
			else
			{
				m_slist.SetItemText(i, 15, "not support");	
			}
			
			//support Modify IPv6
			if (pinfo->bySupport & 0x2)
			{
				m_slist.SetItemText(i, 17, "support");
			}
			else
			{
				m_slist.SetItemText(i, 17, "not support");	
			}
			
			
			//support DHCP
			if (pinfo->bySupport & 0x4)
			{
				m_slist.SetItemText(i, 18, "support");
			}
			else
			{
				m_slist.SetItemText(i, 18, "not support");	
			}

			sprintf(tbuf,"%s",pinfo->szCmsIPv4);
			m_slist.SetItemText(i,19,tbuf);
			
			sprintf(tbuf,"%d",pinfo->wCmsPort);
			m_slist.SetItemText(i,20,tbuf);
			
			sprintf(tbuf,"%d",pinfo->wDigitalChannelNum);
			m_slist.SetItemText(i,21,tbuf);
			
			sprintf(tbuf,"%d",pinfo->wHttpPort);
			m_slist.SetItemText(i,22,tbuf);

			sprintf(tbuf,"%d",pinfo->byOEMCode);
			m_slist.SetItemText(i,23,tbuf);

			m_slist.SetItemText(i,24,(const char*)pinfo->szOEMinfo);
			
			m_slist.SetItemText(i,25,(const char*)pinfo->szBaseDesc);
			//support Password Restore
			if (pinfo->bySupport & 0x20)
			{
				m_slist.SetItemText(i, 26, "support");
			}
			else
			{
				m_slist.SetItemText(i, 26, "not support");	
			}
			//Activate State
			if (pinfo->byActivated == 0)
			{
				m_slist.SetItemText(i, 27, "Activated");
			}
			else if (pinfo->byActivated == 1)
			{
				m_slist.SetItemText(i, 27, "Not Activated");
			}
			
			//support Password Reset
			if (pinfo->bySupport & 0x40)
			{
				m_slist.SetItemText(i, 28, "support");
			}
			else
			{
				m_slist.SetItemText(i, 28, "not support");	
			}


            if (pinfo->bySupport & 0x80)
            {
                m_slist.SetItemText(i, 29, "support");
            }
            else
            {
                m_slist.SetItemText(i, 29, "not support");	
			}

            if (pinfo->bySupport1 & 0x01)
            {
                m_slist.SetItemText(i, 30, "support");
            }
            else
            {
                m_slist.SetItemText(i, 30, "not support");	
	        }
            if (pinfo->bySupport1 & 0x04)
            {
                m_slist.SetItemText(i, 31, "support");
            }
            else
            {
                m_slist.SetItemText(i, 31, "not support");
            }
            if (pinfo->bySupport1 & 0x08)
            {
                m_slist.SetItemText(i, 32, "support");
            }
            else
            {
                m_slist.SetItemText(i, 32, "not support");
            }

			//HCPlatform
			if (1 == pinfo->byHCPlatform)
			{
				m_slist.SetItemText(i, 33, "support");
			}
			else if (2 == pinfo->byHCPlatform)
			{
				m_slist.SetItemText(i, 33, "not support");
			}
			else
			{
				m_slist.SetItemText(i, 33, "NA");
			}
			//EnableHCPlatform
			if (1 == pinfo->byEnableHCPlatform)
			{
				m_slist.SetItemText(i, 34, "support");
			}
			else if (2 == pinfo->byEnableHCPlatform)
			{
				m_slist.SetItemText(i, 34, "not support");
			}
			else
			{
				m_slist.SetItemText(i, 34, "NA");
			}
			//ModifyVerificationCode
			if (1 == pinfo->byModifyVerificationCode)
			{
				m_slist.SetItemText(i, 35, "modify");
			}
			else if (2 == pinfo->byModifyVerificationCode)
			{
				m_slist.SetItemText(i, 35, "not modify");
			}
			else
			{
				m_slist.SetItemText(i, 35, "NA");
			}
            //Bind
            if (pinfo->bySupport1 & 0x20)
            {
                m_slist.SetItemText(i, 36, "support");
            }
            else
            {
                m_slist.SetItemText(i, 36, "not support");
            }
            //Max Bind Num
            sprintf(tbuf, "%d", pinfo->byMaxBindNum);
            m_slist.SetItemText(i, 37, tbuf);
            //Restore Inactive
            if (pinfo->bySupport1 & 0x40)
            {
                m_slist.SetItemText(i, 38, "support");
            }
            else
            {
                m_slist.SetItemText(i, 38, "not support");
            }
            //support wifi Enhancement
            if ((pinfo->bySupport1 & 0x80))
            {
                m_slist.SetItemText(i, 39, "support");
            }
            else
            {
                m_slist.SetItemText(i, 39, "not support");
            }

            //Enable wifi Enhancement
            if (1 == pinfo->byEnableWifiEnhancement)
            {
                m_slist.SetItemText(i, 40, "True");
            }
            else
            {
                m_slist.SetItemText(i, 40, "False");
            }
            //support wifi Region

            sprintf(tbuf, "0x%x", pinfo->bySupportWifiRegion);
            m_slist.SetItemText(i, 41, tbuf);
            //current wifi Region
            //0 - default，1 - china，2 - nothAmerica，3 - japan，4 - europe, 5 - world
            if (0 == pinfo->byWifiRegion)
            {
                m_slist.SetItemText(i, 42, "default");
            }
            else if (1 == pinfo->byWifiRegion)
            {
                m_slist.SetItemText(i, 42, "china");
            }
            else if (2 == pinfo->byWifiRegion)
            {
                m_slist.SetItemText(i, 42, "nothAmerica");
            }
            else if (3 == pinfo->byWifiRegion)
            {
                m_slist.SetItemText(i, 42, "japan");
            }
            else if (4 == pinfo->byWifiRegion)
            {
                m_slist.SetItemText(i, 42, "europe");
            }
            else if (5 == pinfo->byWifiRegion)
            {
                m_slist.SetItemText(i, 42, "world");
            }

            if ((pinfo->byLicensed == 1))
            {
                m_slist.SetItemText(i, 43, "authorized");
            }
            else
            {
                m_slist.SetItemText(i, 43, "unauthorized");
            }

            //设备是否授权
            if ((pinfo->byLicensed == 2))
            {
                m_slist.SetItemText(i, 43, "authorized");
            }
            else if ((pinfo->byLicensed == 1))
            {
                m_slist.SetItemText(i, 43, "unauthorized");
            }
            else
            {
                m_slist.SetItemText(i, 43, "default");
            }

            //系统模式
            if ((pinfo->bySystemMode == 1))
            {
                m_slist.SetItemText(i, 44, "single");
            }
            else if ((pinfo->bySystemMode == 2))
            {
                m_slist.SetItemText(i, 44, "double");
            }
            else if ((pinfo->bySystemMode == 3))
            {
                m_slist.SetItemText(i, 44, "singleCluster");
            }
            else if ((pinfo->bySystemMode == 4))
            {
                m_slist.SetItemText(i, 44, "doubleCluster");
            }
            else
            {
                m_slist.SetItemText(i, 44, "default");
            }

            //控制器类型
            if ((pinfo->byControllerType == 1))
            {
                m_slist.SetItemText(i, 45, "A");
            }
            else if ((pinfo->byControllerType == 2))
            {
                m_slist.SetItemText(i, 45, "B");
            }
            else
            {
                m_slist.SetItemText(i, 45, "default");
            }

            //support channel default pw
            if (pinfo->bySupport2 & 0x1)
            {
                m_slist.SetItemText(i, 46, "support");
            }
            else
            {
                m_slist.SetItemText(i, 46, "not support");
            }

            //EHome版本号
            m_slist.SetItemText(i, 47, pinfo->szEhmoeVersion);

            //Support MailBox Reset Password
            if ((pinfo->bySupport2 & 0x2))
            {
                m_slist.SetItemText(i, 48, "support");
            }
            else
            {
                m_slist.SetItemText(i, 48, "not support");
            }

            //是否支持未激活配置SSID和Password
            if ((pinfo->bySupport2 & 0x4))
            {
                m_slist.SetItemText(i, 49, "support");
            }
            else
            {
                m_slist.SetItemText(i, 49, "not support");
            }

            if (pinfo->bySpecificDeviceType == 1)
            {
                sprintf(tbuf, "%s", "中性");
                m_slist.SetItemText(i, 50, tbuf);
            }
            else if (pinfo->bySpecificDeviceType == 2)
            {
                sprintf(tbuf, "%s", "海康");
                m_slist.SetItemText(i, 50, tbuf);
            }
            else
            {
                sprintf(tbuf, "%s", "未识别");
                m_slist.SetItemText(i, 50, tbuf);
            }

            sprintf(tbuf, "%ld", pinfo->dwSDKOverTLSPort);
            m_slist.SetItemText(i, 51, tbuf);

            if (pinfo->bySecurityMode == 0)
            {
                sprintf(tbuf, "%s", "standard");
                m_slist.SetItemText(i, 52, tbuf);
            }
            else if (pinfo->bySecurityMode == 1)
            {
                sprintf(tbuf, "%s", "high-A");
                m_slist.SetItemText(i, 52, tbuf);
            }
            else if (pinfo->bySecurityMode == 2)
            {
                sprintf(tbuf, "%s", "high-B");
                m_slist.SetItemText(i, 52, tbuf);
            }
            else if (pinfo->bySecurityMode == 3)
            {
                sprintf(tbuf, "%s", "custom");
                m_slist.SetItemText(i, 52, tbuf);
            }
            else
            {
                sprintf(tbuf, "%s", "未识别");
                m_slist.SetItemText(i, 52, tbuf);
            }

            if (pinfo->bySDKServerStatus == 0)
            {
                sprintf(tbuf, "%s", "开启");
                m_slist.SetItemText(i, 53, tbuf);
            }
            else if (pinfo->bySDKServerStatus == 1)
            {
                sprintf(tbuf, "%s", "关闭");
                m_slist.SetItemText(i, 53, tbuf);
            }

            if (pinfo->bySDKOverTLSServerStatus == 0)
            {
                sprintf(tbuf, "%s", "关闭");
                m_slist.SetItemText(i, 54, tbuf);
            }
            else if (pinfo->bySDKOverTLSServerStatus == 1)
            {
                sprintf(tbuf, "%s", "开启");
                m_slist.SetItemText(i, 54, tbuf);
            }

            //管理员用户用户名
            sprintf(tbuf, "%s", pinfo->szUserName);
            m_slist.SetItemText(i, 55, tbuf);

            //协议类型
            sprintf(tbuf, "%d", pinfo->byDataFromMulticast);
            m_slist.SetItemText(i, 56, tbuf);

            //设备所连wifi的Mac地址
            m_slist.SetItemText(i, 57, pinfo->szWifiMAC);

            //是否支持萤石账号解绑
            sprintf(tbuf, "%d", pinfo->bySupportEzvizUnbind);
            m_slist.SetItemText(i, 58, tbuf);

            //是否支持重置口令AES128_ECB解密
            sprintf(tbuf, "%d", pinfo->bySupportCodeEncrypt);
            m_slist.SetItemText(i, 59, tbuf);

            //是否支持获取密码重置方式参数
            sprintf(tbuf, "%d", pinfo->bySupportPasswordResetType);
            m_slist.SetItemText(i, 60, tbuf);

            //萤石云绑定状态
            sprintf(tbuf, "%d", pinfo->byEZVIZBindStatus);
            m_slist.SetItemText(i, 61, tbuf);

            //萤石云物理接触式添加方式
            sprintf(tbuf, "%s", pinfo->szPhysicalAccessVerification);
            m_slist.SetItemText(i, 62, tbuf);

            //Https 端口
            sprintf(tbuf, "%d", pinfo->wHttpsPort);
            m_slist.SetItemText(i, 63, tbuf);

            //萤石用户token配置
            sprintf(tbuf, "%d", pinfo->bySupportEzvizUserToken);
            m_slist.SetItemText(i, 64, tbuf);

            //设备厂商信息
            sprintf(tbuf, "%s", pinfo->szManufacturer);
            m_slist.SetItemText(i, 65, tbuf);

            //手机扫码重置密码
            sprintf(tbuf, "%d", pinfo->bySupportResetPwByPhoneNo);
            m_slist.SetItemText(i, 66, tbuf);

            //设备类型
            sprintf(tbuf, "%d", pinfo->iDevType);
            m_slist.SetItemText(i, 67, tbuf);

			bbingo = TRUE;
			break;
		}
	}

	if(!bbingo) 
    {
        OutputDebugString("wrong 002\n");
    }

}

void CDlgHikSadp::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here

// 	BOOL bret = SADP_InstallNPF();
// 	if (!bret)
// 	{
// 		AfxMessageBox("Install NPF failed, Please reboot and try again");
// 		return;
// 	}
	int iRet = SADP_SetDeviceFilterRule(SADP_DISPLAY_ALL, NULL, 0);
	if (iRet == 1)
	{
		//AfxMessageBox("SADP_SetDeviceDisplayRule Success!");
	}
	else
	{
		int iError = SADP_GetLastError();
		char szTemp[128] = { 0 };
		sprintf(szTemp, "SADP_SetDeviceDisplayRule fail err %d!", iError);
		AfxMessageBox(szTemp);
	}

    SADP_SetLogToFile(3, "C:\\SadpLog\\", TRUE);

    SADP_START_PARAM struStartParam = { 0 };
    struStartParam.fnDevCB = SadpDataCallBack_V40;
    struStartParam.fnSubnetDevCB = SadpSubnetDataCallBack;
    BOOL bret = SADP_Start_V50(&struStartParam);
	//BOOL bret = SADP_Start_V40(SadpDataCallBack_V40);
   /// BOOL bret = SADP_Start_V30(SadpDataCallBack);
	//SADP_Stop();

//	DWORD dwErr = SADP_GetLastError();

    SADP_SetAutoRequestInterval(0);

	
	if(bret)
	{
		m_brun = TRUE;
	}else
	{
        DWORD dwErr = SADP_GetLastError();
        if (dwErr == SADP_LOAD_WPCAP_FAIL)
        {
            char szTemp[128] = { 0 };
            sprintf_s(szTemp, "Load Wpcap.dll fail!");
            AfxMessageBox(szTemp);
        }
        else
        {
            AfxMessageBox(GetText(19));
        }
		
	}

	GetDlgItem(IDC_IPADDRESS_MASK)->EnableWindow(FALSE);
	GetDlgItem(IDC_IPADDRESS_ADDR)->EnableWindow(FALSE);

	SetWindowText(GetText(0));
	GetDlgItem(IDC_STATIC_ID)->SetWindowText(GetText(1));
	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(GetText(2));
	GetDlgItem(IDC_STATIC_MASK)->SetWindowText(GetText(3));
	GetDlgItem(IDC_STATIC_IP)->SetWindowText(GetText(4));
	GetDlgItem(IDC_STATIC_PORT)->SetWindowText(GetText(5));
	GetDlgItem(IDC_STATIC_MAC)->SetWindowText(GetText(6));
	GetDlgItem(IDC_STATIC_PSWINPUT)->SetWindowText(GetText(7));
	GetDlgItem(IDC_BUTTON_MODIFY)->SetWindowText(GetText(8));
	GetDlgItem(IDC_BUTTON_CANSEL)->SetWindowText(GetText(9));
	GetDlgItem(IDC_BUTTON_SAFE)->SetWindowText(GetText(10));
	//GetDlgItem(IDC_BUTTON1)->SetWindowText(GetText(11));
	GetDlgItem(IDC_BUTTON_BACK)->SetWindowText(GetText(12));
	GetDlgItem(IDC_STATIC_MODIFYPSWD)->SetWindowText(GetText(28));
	GetDlgItem(IDC_BUTTON_DEFAULT_PW)->SetWindowText(GetText(17));
	GetDlgItem(IDC_STATIC_DEVICE_DESC)->SetWindowText(GetText(42));
	GetDlgItem(IDC_STATIC_VERSION_INFO)->SetWindowText(GetText(58));
}

void CDlgHikSadp::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CDlgHikSadp::OnCancel() 
{
	// TODO: Add extra cleanup here
//	return;
	CDialog::OnCancel();
}

void CDlgHikSadp::OnOK() 
{
	// TODO: Add extra validation here
	return;
	CDialog::OnOK();
}

void CDlgHikSadp::OnButBack() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgHikSadp::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CDlgHikSadp::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	int nItem;

	POSITION pos = m_slist.GetFirstSelectedItemPosition();
	if (pos == NULL)
	   TRACE0("No items were selected!\n");
	else
	{
	  nItem = m_slist.GetNextSelectedItem(pos);

	  GetDlgItem(IDC_BUTTON_MODIFY)->EnableWindow(TRUE);
	  GetDlgItem(IDC_BUTTON_CANSEL)->EnableWindow(FALSE);
	  GetDlgItem(IDC_BUTTON_SAFE)->EnableWindow(FALSE);

	  //Display Info
	  m_strDevDescription = m_slist.GetItemText(nItem, 1);
      m_strDevType = m_slist.GetItemText(nItem, 67);
	  GetDlgItem(IDC_IPADDRESS_ADDR)->SetWindowText(m_slist.GetItemText(nItem, 2).GetBuffer(0));
	  m_uport	=	atoi(m_slist.GetItemText(nItem, 3).GetBuffer(0));
      m_uSDKOverTLSPort = atoi(m_slist.GetItemText(nItem, 51).GetBuffer(0));
	  m_sdevid	=	m_slist.GetItemText(nItem, 4);
	  GetDlgItem(IDC_IPADDRESS_MASK)->SetWindowText(m_slist.GetItemText(nItem, 5).GetBuffer(0));
	  m_smac	=	m_slist.GetItemText(nItem, 6);
	  m_strSoftVersion = m_slist.GetItemText(nItem, 8);//20080403
	  GetDlgItem(IDC_IPADDRESS_GATEWAY)->SetWindowText(m_slist.GetItemText(nItem, 11).GetBuffer(0));
	  m_strIPv6Adress = m_slist.GetItemText(nItem, 12);
	  m_strIPv6Gateway = m_slist.GetItemText(nItem, 13);
	  m_strIPv6MaskLen = m_slist.GetItemText(nItem, 14);

	  GetDlgItem(IDC_IPADDRESS_CMS)->SetWindowText(m_slist.GetItemText(nItem, 19).GetBuffer(0));
	  m_wCmsPort	=	atoi(m_slist.GetItemText(nItem, 20).GetBuffer(0));
	  m_wHttpPort	=	atoi(m_slist.GetItemText(nItem, 22).GetBuffer(0));


	  int iDhcp = 0;
	  CString strDhcp = m_slist.GetItemText(nItem, 16);
	  if (0 == strDhcp.Compare("ON"))
	  {
		  iDhcp = 1;
	  }
	  else if (0 == strDhcp.Compare("OFF"))
	  {
		   iDhcp = 0;
	  }
	  else
	  {
		  iDhcp = 0;
	  }


	  m_btnDhcp->SetCheck(iDhcp);
	//重置密码
      CString strResetPassword = m_slist.GetItemText(nItem, 28);
      if (0 == strResetPassword.Compare("support"))
      {
          m_bResetPW = TRUE;
      }
      else
      {
          m_bResetPW = FALSE;
      }
	  
      //同步IPC密码
      CString strSyncIPCPW = m_slist.GetItemText(nItem, 29);
      if (0 == strSyncIPCPW.Compare("support"))
      {
          m_bSyncIPCPW = TRUE;
      }
      else
      {
          m_bSyncIPCPW = FALSE;
	  } 
      //重置密码方式2
      CString strResetPasswordModeSecond = m_slist.GetItemText(nItem, 30);
      if (0 == strResetPasswordModeSecond.Compare("support"))
      {
          m_bResetPWModeSecond = TRUE;
      }
      else
      {
          m_bResetPWModeSecond = FALSE;
	     } 

      //邮箱重置密码
      CString strMailBoxResetPW = m_slist.GetItemText(nItem, 48);
      if (0 == strMailBoxResetPW.Compare("support"))
      {
          m_bMailBoxResetPW = TRUE;
      }
      else
      {
          m_bMailBoxResetPW = FALSE;
      }

      //邮箱重置密码
      CString strSSIDAndPasswordCfg = m_slist.GetItemText(nItem, 49);
      if (0 == strSSIDAndPasswordCfg.Compare("support"))
      {
          m_bSupportSSIDAndPasswordCfg = TRUE;
      }
      else
      {
          m_bSupportSSIDAndPasswordCfg = FALSE;
      }

      //GUID重置密码方式
      CString strGUIDResetPassword = m_slist.GetItemText(nItem, 31);
      if (0 == strGUIDResetPassword.Compare("support"))
      {
          m_bSupportGUID = TRUE;
      }
      else
      {
          m_bSupportGUID = FALSE;
      }
      //安全问题重置密码方式
      CString strSecurityQuestionResetPassword = m_slist.GetItemText(nItem, 32);
      if (0 == strSecurityQuestionResetPassword.Compare("support"))
      {
          m_bSupportSecurityQuestion = TRUE;
      }
      else
      {
          m_bSupportSecurityQuestion = FALSE;
      }
	  
      //根据激活状态，显示对应按钮内容
      CString strRestoreInactive = m_slist.GetItemText(nItem, 38);
      CString strActivateStatus = m_slist.GetItemText(nItem, 27);
      if (0 == strRestoreInactive.Compare("support") && 0 == strActivateStatus.Compare("Activated"))
      {
          GetDlgItem(IDC_BTN_ACTIVATE_DEVICE)->SetWindowText("Inactive");
      }
      else
      {
          GetDlgItem(IDC_BTN_ACTIVATE_DEVICE)->SetWindowText("Activate Dev");
      }

      //支持绑定
      CString strBind = m_slist.GetItemText(nItem, 36);
      if (0 == strBind.Compare("support"))
      {
          m_bSupportBind = TRUE;
      }
      else
      {
          m_bSupportBind = FALSE;
      }

      //是否启用wifi增强
      CString strSupportEnhance = m_slist.GetItemText(nItem, 39);
      if (0 == strSupportEnhance.Compare("support"))
      {
          m_bSupportEnhancement = TRUE;
      }
      else
      {
          m_bSupportEnhancement = FALSE;
      }
      CString strEnableEnhance = m_slist.GetItemText(nItem, 40);
      if (0 == strEnableEnhance.Compare("support"))
      {
          m_bEnableEnhancement = TRUE;
      }
      else
      {
          m_bEnableEnhancement = FALSE;
      }
      
      CString strChannelDefaultPW = m_slist.GetItemText(nItem, 46);
      if (0 == strChannelDefaultPW.Compare("support"))
      {
          m_bySupportChannelDefaultPW = TRUE;
      }
      else
      {
          m_bySupportChannelDefaultPW = FALSE;
      }

      CString strSupportEzvizUserToken = m_slist.GetItemText(nItem, 64);
      if (0 == strSupportEzvizUserToken.Compare("1"))
      {
          m_bSupportEzvizUserToken = TRUE;
      }
      else
      {
          m_bSupportEzvizUserToken = FALSE;
      }

      CString strSupportPhoneReset = m_slist.GetItemText(nItem, 66);
      if (0 == strSupportPhoneReset.Compare("1"))
      {
          m_bSupportPhoneReset = TRUE;
      }
      else
      {
          m_bSupportPhoneReset = FALSE;
      }

	  CString str = _T("");
	  GetDlgItem(IDC_STA_STATE)->SetWindowText(str);

	  UpdateData(FALSE);
	}
	
	*pResult = 0;
}

void CDlgHikSadp::fEnableButton(BOOL bedit)
{
	GetDlgItem(IDC_BUTTON_MODIFY)->EnableWindow(!bedit);
	GetDlgItem(IDC_LIST_DEV_INFO)->EnableWindow(!bedit);
	GetDlgItem(IDC_BUTTON_SELECT_DEV)->EnableWindow(!bedit);
	GetDlgItem(IDC_BUTTON_BACK)->EnableWindow(!bedit);

	GetDlgItem(IDC_BUTTON_CANSEL)->EnableWindow(bedit);
	GetDlgItem(IDC_BUTTON_SAFE)->EnableWindow(bedit);

	GetDlgItem(IDC_IPADDRESS_MASK)->EnableWindow(bedit);
	GetDlgItem(IDC_IPADDRESS_ADDR)->EnableWindow(bedit);
	GetDlgItem(IDC_IPADDRESS_GATEWAY)->EnableWindow(bedit);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(bedit);
    GetDlgItem(IDC_EDIT_TLS_PORT)->EnableWindow(bedit);
	GetDlgItem(IDC_EDIT_HTTP_PORT)->EnableWindow(bedit);
	GetDlgItem(IDC_EDIT_IPv6_ADDRESS)->EnableWindow(bedit);
	GetDlgItem(IDC_EDIT_IPv6_GATEWAY)->EnableWindow(bedit);
	GetDlgItem(IDC_EDIT_MASK_LEN)->EnableWindow(bedit);

	GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(bedit);
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText("");
	GetDlgItem(IDC_STATIC_PSWINPUT)->ShowWindow(bedit);

	GetDlgItem(IDC_CHECK_DHCP)->EnableWindow(bedit);

}

void CDlgHikSadp::OnButtonModify() 
{
	//modify
	UpdateData();
    CString sip, smask, sport, sSDKOverTLSPort;
	BYTE nfield0,nfield1,nfield2,nfield3;

	m_sip.GetAddress(nfield0,nfield1,nfield2,nfield3);
	m_sip.GetAddress(m_dwsip);
	sip.Format("%d.%d.%d.%d",nfield0,nfield1,nfield2,nfield3);

	m_smask.GetAddress(nfield0,nfield1,nfield2,nfield3);
	m_smask.GetAddress(m_dwsmask);
	smask.Format("%d.%d.%d.%d",nfield0,nfield1,nfield2,nfield3);


	sport.Format("%ld",m_uport);
    sSDKOverTLSPort.Format("%ld", m_uSDKOverTLSPort);

	CString str = _T("");
	GetDlgItem(IDC_STA_STATE)->SetWindowText(str);

	m_bedit = TRUE;
	g_csPort = sport;
    g_csSDKOverTLSPort = sSDKOverTLSPort;
	g_csMask = smask;
	g_csIP   = sip;

	fEnableButton(m_bedit);

    //To determine the state of the DHCP
	if (BST_CHECKED == m_btnDhcp->GetCheck())
	{
		GetDlgItem(IDC_IPADDRESS_MASK)->EnableWindow(FALSE);
		GetDlgItem(IDC_IPADDRESS_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_IPADDRESS_GATEWAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPv6_ADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPv6_GATEWAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MASK_LEN)->EnableWindow(FALSE);
	}
	else if (BST_UNCHECKED == m_btnDhcp->GetCheck())
	{
		GetDlgItem(IDC_IPADDRESS_MASK)->EnableWindow(TRUE);
		GetDlgItem(IDC_IPADDRESS_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_IPADDRESS_GATEWAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IPv6_ADDRESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IPv6_GATEWAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MASK_LEN)->EnableWindow(TRUE);
	}
}

void CDlgHikSadp::OnButtonCancel() 
{
	//cancel
	m_sip.SetAddress(m_dwsip);
	m_smask.SetAddress(m_dwsmask);
	POSITION pos = m_slist.GetFirstSelectedItemPosition();
	int nItem = m_slist.GetNextSelectedItem(pos);
	m_uport	=	atoi(m_slist.GetItemText(nItem, 3).GetBuffer(0));
    m_uSDKOverTLSPort = atoi(m_slist.GetItemText(nItem, 51).GetBuffer(0));
	UpdateData(FALSE);

	m_bedit = FALSE;

	fEnableButton(m_bedit);
}

void CDlgHikSadp::OnButtonSafe() 
{

	//check
	char tbuf[64];
	memset(tbuf, 0, 64);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(tbuf, 64);
	if(strlen(tbuf)<=0)
	{
		AfxMessageBox(GetText(13));
		return;
	}	
	int iport = atoi(tbuf);
	memset(tbuf, 0, 64);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(tbuf, 64);
	if(strlen(tbuf)<0)
	{
		AfxMessageBox(GetText(14));
		return;
	}
    UpdateData(TRUE);//20080403

	//save 不对端口号进行2000以内的限制
    if (iport>65535)
    {
        AfxMessageBox(GetText(29));
        return;
    }

	//do it
    CString sip, smask, sport, strHttpPort,sSDKOverTLSPort;
	BYTE nfield0,nfield1,nfield2,nfield3;

	m_sip.GetAddress(nfield0,nfield1,nfield2,nfield3);
	sip.Format("%d.%d.%d.%d",nfield0,nfield1,nfield2,nfield3);

	m_smask.GetAddress(nfield0,nfield1,nfield2,nfield3);
	smask.Format("%d.%d.%d.%d",nfield0,nfield1,nfield2,nfield3);


	CString strIPv4Gateway;
	m_addrIPv4Gateway.GetAddress(nfield0,nfield1,nfield2,nfield3);
	strIPv4Gateway.Format("%d.%d.%d.%d",nfield0,nfield1,nfield2,nfield3);

// 	unsigned char szMaskLen[16] = {0};
// 	memset(szMaskLen, 0, 16);
// 	GetDlgItem(IDC_EDIT_MASK_LEN)->GetWindowText(szMaskLen, 16);
	unsigned char byMaskLen = atoi(m_strIPv6MaskLen);

	int iDhcpCheck = m_btnDhcp->GetCheck();





	sport.Format("%ld",m_uport);
    sSDKOverTLSPort.Format("%ld", m_uSDKOverTLSPort);

	SADP_DEV_NET_PARAM struNetParam;
	memset(&struNetParam, 0, sizeof(SADP_DEV_NET_PARAM));
	strcpy(struNetParam.szIPv4Address, sip);
	strcpy(struNetParam.szIPv4SubNetMask, smask);
	strcpy(struNetParam.szIPv4Gateway, strIPv4Gateway);
	strcpy(struNetParam.szIPv6Address, m_strIPv6Adress);
	strcpy(struNetParam.szIPv6Gateway, m_strIPv6Gateway);
	struNetParam.wPort = atoi(sport);
    struNetParam.dwSDKOverTLSPort = atoi(sSDKOverTLSPort);
	struNetParam.byDhcpEnable = iDhcpCheck;
	if ((byMaskLen >= 3 && byMaskLen <= 127) || (byMaskLen == 0 && strlen(m_strIPv6Adress.GetBuffer(0)) < 3) )
	{
		struNetParam.byIPv6MaskLen = byMaskLen;
	}
	else
	{
        AfxMessageBox("Please enter the IPv6 mask length between 3-127!");
		return;
	}
	
	if (m_wHttpPort < 1 || m_wHttpPort > 65535)
	{
        AfxMessageBox("Please enter the Http port number between 1-65535");
		return;
	}

	struNetParam.wHttpPort = m_wHttpPort;
    SADP_DEV_RET_NET_PARAM struDevRetNetParam = { 0 };


	//int bret = SADP_ModifyDeviceNetParam(m_smac, m_spsw, &struNetParam);
    int bret = SADP_ModifyDeviceNetParam_V40(m_smac, m_spsw, &struNetParam, &struDevRetNetParam, sizeof(struDevRetNetParam));

	TRACE("desDLC=%s,desIP=%s,subnetmask=%s,passwd=%s,port=%s",
		m_smac,sip,smask,m_spsw,sport);
    char strTemp[100];
    memset(strTemp, 0, 100);
	if (bret == 0)
	{
		GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText("");
		DWORD dwError = SADP_GetLastError();
		if (dwError == SADP_LOCKED)
		{
            sprintf(strTemp, "设备已锁定，锁定时间:%d 分钟.", struDevRetNetParam.bySurplusLockTime);
            AfxMessageBox(strTemp);
		}
		else if (dwError == SADP_NOT_ACTIVATED)
		{
			AfxMessageBox(GetText(62));
		}
        else if (dwError == SADP_PASSWORD_ERROR)
        {
            sprintf(strTemp, "密码错误，剩余尝试修改次数:%d 次.", struDevRetNetParam.byRetryModifyTime);
            AfxMessageBox(strTemp);
        }
		else
		{
			//AfxMessageBox(GetText(20));
			
			sprintf(strTemp, "Safe failed ,Error Number:%d", dwError);
			AfxMessageBox(strTemp);
		}

		return;			//20080325 yujl
	}
	else if (bret == 1)
	{
		AfxMessageBox(GetText(21));
		POSITION pos = m_slist.GetFirstSelectedItemPosition();
		int nItem = m_slist.GetNextSelectedItem(pos);
//		m_uport	=	atoi(m_slist.GetItemText(nItem, 3).GetBuffer(0));
		m_slist.SetItemText(nItem,3,sport);
		
        if (BST_UNCHECKED == m_btnDhcp->GetCheck())
        {
            m_slist.SetItemText(nItem,2,sip);
            m_slist.SetItemText(nItem,5,smask);
        }
		
		strHttpPort.Format("%d", m_wHttpPort);
		m_slist.SetItemText(nItem,22,strHttpPort);
	}
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText("");
	m_bedit = FALSE;

	fEnableButton(m_bedit);
}

void CDlgHikSadp::OnButtonCmsSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strIPv4;
	BYTE nfield0,nfield1,nfield2,nfield3;
	m_addrCmsIPv4.GetAddress(nfield0,nfield1,nfield2,nfield3);
	strIPv4.Format("%d.%d.%d.%d",nfield0,nfield1,nfield2,nfield3);

	//SADP_CMS_PARAM struCmsParam;
	//memset(&struCmsParam, 0, sizeof(SADP_CMS_PARAM));
	//strcpy(struCmsParam.szCmsIPv4, strIPv4);
	//strcpy(struCmsParam.szCmsIPv6, m_strCmsIPv6);
	//strcpy(struCmsParam.szPUID, m_strPUID);
	//strcpy(struCmsParam.szPassword, m_strCmsPasswd);
	//struCmsParam.wCmsPort = m_wCmsPort;
	//int iRet = SADP_SetCMSInfo(m_smac, &struCmsParam);
	//if (1 == iRet)
	//{
	//	AfxMessageBox("Set successful!");
	//}
	//else if(0 == iRet)
	//{
	//	AfxMessageBox("Fail to set!");
	//}
	//else
	//{
	//	AfxMessageBox("unvalid return value!");
	//}
}

void CDlgHikSadp::OnButtonSelectDev() 
{
	BOOL bRet = FALSE;
	CString strCaption;
	GetDlgItem(IDC_BUTTON_SELECT_DEV)->GetWindowText(strCaption);
	if (0 == strCaption.CompareNoCase("Stop"))
	{
		bRet = SADP_Stop();
		if (bRet)
		{
			GetDlgItem(IDC_BUTTON_SELECT_DEV)->SetWindowText("Start");
		}
		else
		{
			AfxMessageBox("Stop failed");
		}
		
	}
	else
	{
		bRet = SADP_Start_V40(SadpDataCallBack_V40);
		if (bRet)
		{
			GetDlgItem(IDC_BUTTON_SELECT_DEV)->SetWindowText("Stop");
		}
		else
		{
			AfxMessageBox("Start failed");
		}
	}


}

void CDlgHikSadp::OnBnClickedButtonDefaultPW()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char TempPasswd[MAX_LEN]={0};      
	GetDlgItemText(IDC_EDIT_DEFAULT_PW,TempPasswd,MAX_LEN);


	if(strcmp(TempPasswd,"")==0 )
	{
		AfxMessageBox(GetText(25));
		return;
	}
    //Call the new interface
	SADP_RESET_PARAM struResetParam = {0};
	memcpy(struResetParam.szCode, TempPasswd, strlen(TempPasswd));
	int iFlag = SADP_ResetPasswd(m_sdevid.GetBuffer(0), &struResetParam);
	//int iFlag = SADP_ResetDefaultPasswd(m_sdevid.GetBuffer(0), TempPasswd);

	SetDlgItemText(IDC_EDIT_DEFAULT_PW,"");
	if(iFlag == 1)
	{
		AfxMessageBox(GetText(30));
	}
	else if(iFlag == 0)
	{
		AfxMessageBox(GetText(31));
		return;			//20080325 yujl
	}
	GetDlgItem(IDC_EDIT_DEFAULT_PW)->SetWindowText("");
}



void CDlgHikSadp::OnCheckDhcp() 
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_btnDhcp->GetCheck())
	{
		GetDlgItem(IDC_IPADDRESS_MASK)->EnableWindow(FALSE);
		GetDlgItem(IDC_IPADDRESS_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_IPADDRESS_GATEWAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPv6_ADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPv6_GATEWAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MASK_LEN)->EnableWindow(FALSE);
	}
	else if (BST_UNCHECKED == m_btnDhcp->GetCheck())
	{
		GetDlgItem(IDC_IPADDRESS_MASK)->EnableWindow(TRUE);
		GetDlgItem(IDC_IPADDRESS_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_IPADDRESS_GATEWAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IPv6_ADDRESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IPv6_GATEWAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MASK_LEN)->EnableWindow(TRUE);
	}
}

void CDlgHikSadp::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
    SADP_Clearup();
    m_slist.DeleteAllItems();
    m_icount = 1;
    SADP_SendInquiry();
    UpdateData(FALSE);
}

void CDlgHikSadp::OnBtnActivateDevice() 
{
	// TODO: Add your control notification handler code here
	CString m_dev = m_sdevid.GetBuffer(0);
	if (m_dev.IsEmpty()){
		AfxMessageBox("Please choose device");
		return;
	}

	CDlgActivateDevice dlg;
	dlg.deviceNo = m_sdevid;
	dlg.DoModal();
}

void CDlgHikSadp::OnBtnResetPw() 
{
	// TODO: Add your control notification handler code here
	CResetPassword dlg;
	dlg.m_strDevID = m_sdevid;
    dlg.m_bSycnIPCPW = m_bSyncIPCPW;
    dlg.m_bResetPWModeSecond = m_bResetPWModeSecond;
    dlg.m_bResetPW = dlg.m_bResetPW;
    dlg.m_bSupportGUID = m_bSupportGUID;
    dlg.m_bSupportSecurityQuestion = m_bSupportSecurityQuestion;
	dlg.m_bMailBoxResetPW = m_bMailBoxResetPW;
	dlg.DoModal();
}

void CDlgHikSadp::OnBtnSetDisplayRule() 
{
	CDlgSetFilterRule dlg;
	dlg.DoModal();
    OnBtnRefresh();
}

void CDlgHikSadp::OnBnClickedCustomFunc()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgCustom dlg;
    dlg.m_strDevID = m_sdevid;
    dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedBtnHcplatform()
{
	// TODO:  在此添加控件通知处理程序代码
	HCPlatformStatus dlg;
	dlg.m_strDevID = m_sdevid;
	dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedBtnBind()
{
    // TODO:  在此添加控件通知处理程序代码
    CBindDev dlg;
    dlg.m_strDevID = m_sdevid;
    dlg.m_bSupportBind = m_bSupportBind;
    dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedBtnWifiRegion()
{
    // TODO:  在此添加控件通知处理程序代码
    CWifiRegion dlg;
    dlg.m_strDevID = m_sdevid;
    dlg.m_bsupportEnhancement = m_bSupportEnhancement;
    dlg.m_bEnhancement = m_bEnableEnhancement;
    dlg.DoModal();
    
}


void CDlgHikSadp::OnBnClickedBtnSendLamp()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    //if (!SADP_SendLamp(m_smac, m_CtrLampAction.GetCurSel()))
    //{
    //    int iError = SADP_GetLastError();
    //    char szTemp[128] = { 0 };
    //    sprintf(szTemp, "SADP_SendLamp fail err %d!", iError);
    //    AfxMessageBox(szTemp);
    //}
    //else
    //{
    //    AfxMessageBox("SADP_SendLamp Success!");
    //}
}


void CDlgHikSadp::OnBnClickedBtnDiskLocate()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (!SADP_GetDeviceConfig(m_sdevid.GetBuffer(0), SADP_DISK_LOCATE, NULL, 0, NULL, 0))
    {
        int iError = SADP_GetLastError();
        char szTemp[128] = { 0 };
        sprintf(szTemp, "SADP_DISK_LOCATE fail err %d!", iError);
        AfxMessageBox(szTemp);
    }
    else
    {
        AfxMessageBox("SADP_DISK_LOCATE Success!");
    }
}


void CDlgHikSadp::OnBnClickedBtnSelfCheck()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgSelfCheck dlg;
    dlg.m_strDevID = m_sdevid;
    dlg.m_strDevMAC = m_smac;
    dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedBtnConfig()
{
    // TODO:  在此添加控件通知处理程序代码
    CConfig dlg;
    dlg.m_strDevID = m_sdevid;
    dlg.m_bySupportChannelDefaultPW = m_bySupportChannelDefaultPW;
    dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedBtnWifiParamCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    //if (FALSE == m_bSupportSSIDAndPasswordCfg)
    //{
    //    AfxMessageBox("Device not support!");
    //}

    //if (!SADP_WifiParamCfg(m_smac, m_strWifiSSID.GetBuffer(0), m_strWifiPassword.GetBuffer(0)))
    //{
    //    int iError = SADP_GetLastError();
    //    char szTemp[128] = { 0 };
    //    sprintf(szTemp, "Wifi Param Config fail err %d!", iError);
    //    AfxMessageBox(szTemp);
    //}
    //else
    //{
    //    AfxMessageBox("Wifi Param Config Success!");
    //}

    //SADP_WIFI_CONFIG_PARAM struSadpWifiConfigParam = { 0 };
    //struSadpWifiConfigParam.dwSize = sizeof(SADP_WIFI_CONFIG_PARAM);
    //memcpy(struSadpWifiConfigParam.szSSID, m_strWifiSSID.GetBuffer(0), SADP_MAX_SERIALNO_LEN);
    //memcpy(struSadpWifiConfigParam.szPassword, m_strWifiPassword.GetBuffer(0), SADP_MAX_SERIALNO_LEN);
    //struSadpWifiConfigParam.byWifiMode = m_CtrWifiMode.GetCurSel();


    //if (!SADP_SetDeviceConfig(m_sdevid.GetBuffer(), SADP_SET_WIFI_SSID_PASSWORD, &struSadpWifiConfigParam, sizeof(struSadpWifiConfigParam), NULL, NULL))
    //{
    //    int iError = SADP_GetLastError();
    //    char szTemp[128] = { 0 };
    //    sprintf(szTemp, "Wifi Param Config fail err %d!", iError);
    //    AfxMessageBox(szTemp);
    //}
    //else
    //{
    //    AfxMessageBox("Wifi Param Config Success!");
    //}
}


void CDlgHikSadp::OnBnClickedBtnWifiParamCheck()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    //if (FALSE == m_bSupportSSIDAndPasswordCfg)
    //{
    //    AfxMessageBox("Device not support!");
    //}


    //if (!SADP_WifiParamCheck(m_smac, m_strWifiSSID.GetBuffer(0), m_strWifiPassword.GetBuffer(0)))
    //{
    //    int iError = SADP_GetLastError();
    //    char szTemp[128] = { 0 };
    //    sprintf(szTemp, "Wifi Param Check fail err %d!", iError);
    //    AfxMessageBox(szTemp);
    //}
    //else
    //{
    //    AfxMessageBox("Wifi Param Check Success!");
    //}


    //SADP_WIFI_CONFIG_PARAM struSadpWifiConfigParam = { 0 };
    //struSadpWifiConfigParam.dwSize = sizeof(SADP_WIFI_CONFIG_PARAM);
    //memcpy(struSadpWifiConfigParam.szSSID, m_strWifiSSID.GetBuffer(0), SADP_MAX_SERIALNO_LEN);
    //memcpy(struSadpWifiConfigParam.szPassword, m_strWifiPassword.GetBuffer(0), SADP_MAX_SERIALNO_LEN);
    //struSadpWifiConfigParam.byWifiMode = m_CtrWifiMode.GetCurSel();

    //if (!SADP_SetDeviceConfig(m_sdevid.GetBuffer(), SADP_CHECK_WIFI_SSID_PASSWORD, &struSadpWifiConfigParam, sizeof(struSadpWifiConfigParam), NULL, NULL))
    //{
    //    int iError = SADP_GetLastError();
    //    char szTemp[128] = { 0 };
    //    sprintf(szTemp, "Wifi Param Check fail err %d!", iError);
    //    AfxMessageBox(szTemp);
    //}
    //else
    //{
    //    AfxMessageBox("Wifi Param Check Success!");
    //}
}


void CDlgHikSadp::OnBnClickedBtnEhomeEnable()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_sdevid == "")
    {
        AfxMessageBox("no select device!");
        return;
    }
    CEhomeEnable dlg;
    dlg.m_strDevSerialNo = m_sdevid;
    dlg.m_strDevMAC = m_smac;
    dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedBtnUnbind()
{
    // TODO:  在此添加控件通知处理程序代码
    //if (m_sdevid == "")
    //{
    //    AfxMessageBox("no select device!");
    //    return;
    //}
    //CEzvizUnbind dlg;
    //dlg.m_strDevSerialNo = m_sdevid;
    //dlg.m_strDevMAC = m_smac;
    //dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedBtnUnbindDelUser()
{
    // TODO:  在此添加控件通知处理程序代码
    //if (m_sdevid == "")
    //{
    //    AfxMessageBox("no select device!");
    //    return;
    //}
    //CEzvizUnbindDelUser dlg;
    //dlg.m_strDevSerialNo = m_sdevid;
    //dlg.m_strDevMAC = m_smac;
    //dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedButtonStartv30()
{
    // TODO:  在此添加控件通知处理程序代
    SADP_SetLogToFile(3, "C:\\SadpLog\\", TRUE);
    BOOL bret = SADP_Start_V30(SadpDataCallBack);
    if (bret)
    {
        m_brun = TRUE;
    }
    else
    {
        DWORD dwErr = SADP_GetLastError();
        if (dwErr == SADP_LOAD_WPCAP_FAIL)
        {
            char szTemp[128] = { 0 };
            sprintf_s(szTemp, "Load Wpcap.dll fail!");
            AfxMessageBox(szTemp);
        }
        else
        {
            AfxMessageBox(GetText(19));
        }

    }
}


void CDlgHikSadp::OnBnClickedButtonStartv40()
{
    // TODO:  在此添加控件通知处理程序代码
    SADP_SetLogToFile(3, "C:\\SadpLog\\", TRUE);
    BOOL bret = SADP_Start_V40(SadpDataCallBack_V40);
    if (bret)
    {
        m_brun = TRUE;
    }
    else
    {
        DWORD dwErr = SADP_GetLastError();
        if (dwErr == SADP_LOAD_WPCAP_FAIL)
        {
            char szTemp[128] = { 0 };
            sprintf_s(szTemp, "Load Wpcap.dll fail!");
            AfxMessageBox(szTemp);
        }
        else
        {
            AfxMessageBox(GetText(19));
        }
    }
}

void CDlgHikSadp::OnBnClickedButtonStartv50()
{
    // TODO:  在此添加控件通知处理程序代码
    SADP_SetLogToFile(3, "C:\\SadpLog\\", TRUE);
    SADP_START_PARAM struStartParam = { 0 };
    struStartParam.fnDevCB = SadpDataCallBack_V40;
    struStartParam.fnSubnetDevCB = SadpSubnetDataCallBack;
    BOOL bret = SADP_Start_V50(&struStartParam);
    if (bret)
    {
        m_brun = TRUE;
    }
    else
    {
        DWORD dwErr = SADP_GetLastError();
        if (dwErr == SADP_LOAD_WPCAP_FAIL)
        {
            char szTemp[128] = { 0 };
            sprintf_s(szTemp, "Load Wpcap.dll fail!");
            AfxMessageBox(szTemp);
        }
        else
        {
            AfxMessageBox(GetText(19));
        }

    }
}


void CDlgHikSadp::OnBnClickedButtonSetReqinterval()
{
	// TODO:  在此添加控件通知处理程序代码
	// SADP_SetAutoRequestInterval
	CDlgAutoRequestInterval dlg;

	dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedButtonSecQue()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgSecurityQuestion dlg;
	dlg.m_strDevID = m_sdevid;
	dlg.m_bSupportSecurityQuestion = m_bSupportSecurityQuestion;
	dlg.m_bSupportSycnIPCPW = m_bSyncIPCPW;
	dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedButtonMailReset()
{
	// TODO:  在此添加控件通知处理程序代码
	CMailBoxResetPW dlg;
	dlg.m_strDevID = m_sdevid;
	dlg.m_bMailBoxResetPW = m_bMailBoxResetPW;
	dlg.m_bSycnIPCPW = m_bSyncIPCPW;

	dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedButtonRestoreInactive()
{
	// TODO:  在此添加控件通知处理程序代码
	// 弹出是否恢复激活对话框
	CDlgRestoreInactive dlg;
	dlg.devSerialNO = m_sdevid;
	dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedButton9()
{
	// TODO:  在此添加控件通知处理程序代码
	SADP_Stop();
	MessageBox("Stop SADP Success!");
}


void CDlgHikSadp::OnBnClickedBtnResetPw4()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgResetPWGUID dlg;
	dlg.m_strDevID = m_sdevid;
	dlg.m_bSupportGUID = m_bSupportGUID;
	dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedBtnResetPw2()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgResetPWEncrypt dlg;
	dlg.m_strDevID = m_sdevid;
	dlg.m_bResetPWModeSecond = m_bResetPWModeSecond;
	dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedBtnResetPw3()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgRestPWDeviceCode dlg;
	dlg.m_strDevID = m_sdevid;
	dlg.m_bResetPWModeSecond = m_bResetPWModeSecond;
	dlg.m_bResetPW = m_bResetPW;
	dlg.DoModal();
}

HANDLE hThread;
bool startTest = false;

//稳定性测试用例
DWORD WINAPI StableTest1(LPVOID pParam)
{
    int iRet = 0;
    bool right = true;
    while (startTest)
    {
        iRet = SADP_Start_V40(SadpDataCallBack_V40);
        if (iRet == 0)
        {
            right = false;
            break;
        }

        iRet = SADP_SendInquiry();
        if (iRet == 0)
        {
            right = false;
            break;
        }
        Sleep(3000);
        iRet = SADP_Clearup();
        if (iRet == 0)
        {
            right = false;
            break;
        }

        iRet = SADP_Stop();
        if (iRet == 0)
        {
            right = false;
            break;
        }
        if (!right)
        {
            break;
        }
    }
    if (right)
    {
        MessageBox(NULL, "稳定性测试成功", "提示", MB_OK);
    }
    else
    {
        MessageBox(NULL, "稳定性测试失败", "提示", MB_OK);
    }

    return 0;
}

DWORD WINAPI StableTest2(LPVOID pParam)
{
    int iRet = 0;
    bool right = true;
    SADP_START_PARAM struStartParam = { 0 };
    struStartParam.fnDevCB = SadpDataCallBack_V40;
    struStartParam.fnSubnetDevCB = SadpSubnetDataCallBack;
    while (startTest)
    {
        iRet = SADP_Start_V50(&struStartParam);
        if (iRet == 0)
        {
            right = false;
            break;
        }

        iRet = SADP_SendInquiry();
        if (iRet == 0)
        {
            right = false;
            break;
        }
        Sleep(3000);
        iRet = SADP_Clearup();
        if (iRet == 0)
        {
            right = false;
            break;
        }

        iRet = SADP_Stop();
        if (iRet == 0)
        {
            right = false;
            break;
        }
        if (!right)
        {
            break;
        }
    }
    if (right)
    {
        MessageBox(NULL, "稳定性测试成功", "提示", MB_OK);
    }
    else
    {
        MessageBox(NULL, "稳定性测试失败", "提示", MB_OK);
    }

    return 0;
}

DWORD WINAPI StableTest3(LPVOID pParam)
{
    int iRet = 0;
    bool right = true;

    iRet = SADP_Start_V40(SadpDataCallBack_V40);
    if (iRet == 0)
    {
        right = false;
    }
    while (right)
    {
        if (startTest)
        {
            Sleep(3000);
            continue;
        }

        iRet = SADP_Clearup();
        if (iRet == 0)
        {
            right = false;
        }

        iRet = SADP_Stop();
        if (iRet == 0)
        {
            right = false;
        }
        break;
    }
    if (right)
    {
        MessageBox(NULL, "稳定性测试成功", "提示", MB_OK);
    }
    else
    {
        MessageBox(NULL, "稳定性测试失败", "提示", MB_OK);
    }

    return 0;
}

DWORD WINAPI StableTest4(LPVOID pParam)
{
    int iRet = 0;
    bool right = true;
    SADP_START_PARAM struStartParam = { 0 };
    struStartParam.fnDevCB = SadpDataCallBack_V40;
    struStartParam.fnSubnetDevCB = SadpSubnetDataCallBack;

    iRet = SADP_Start_V50(&struStartParam);
    if (iRet == 0)
    {
        right = false;
    }
    while (right)
    {
        if (startTest)
        {
            Sleep(3000);
            continue;
        }

        iRet = SADP_Clearup();
        if (iRet == 0)
        {
            right = false;
        }

        iRet = SADP_Stop();
        if (iRet == 0)
        {
            right = false;
        }
        break;
    }
    if (right)
    {
        MessageBox(NULL, "稳定性测试成功", "提示", MB_OK);
    }
    else
    {
        MessageBox(NULL, "稳定性测试失败", "提示", MB_OK);
    }

    return 0;
}

void CDlgHikSadp::OnBnClickedButton11()
{
    // TODO:  在此添加控件通知处理程序代码
    //稳定性测试
    if (!startTest)
    {
        hThread = CreateThread(NULL, 0, StableTest1, 0, 0, 0);  //可替换为StableTest2、StableTest3、StableTest4
        startTest = true;
        GetDlgItem(IDC_BUTTON11)->SetWindowText("Stop StabilityTest");
        MessageBox("开始测试");
    }
    else
    {
        CloseHandle(hThread);
        startTest = false;
        GetDlgItem(IDC_BUTTON11)->SetWindowText("Start StabilityTest");
        MessageBox("关闭测试");
    }
}


void CDlgHikSadp::OnBnClickedBtnSetToken()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_bSupportEzvizUserToken == FALSE)
    {
        AfxMessageBox("No support!");
        return;
    }
    CDlgEzvizToken dlg;
    dlg.m_strDevID = m_sdevid;
    dlg.DoModal();
}


void CDlgHikSadp::OnBnClickedButtonPhoneReset()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_bSupportPhoneReset == FALSE)
    {
        AfxMessageBox("No support!");
        return;
    }
    CDlgResetPWPhone dlg;
    dlg.m_strDevID = m_sdevid;
    dlg.DoModal();
}


void CDlgHikSadp::OnNMRClickListDevInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码
    *pResult = 0;
}

void CDlgHikSadp::fSubnetDevOnLine(SADP_SUBNET_DEVICE_INFO *pinfo)
{
    //Insert List
    int item;
    char tbuf[32];

    sprintf(tbuf, "%03d", m_icountSubnet);
    item = m_slistSubnet.InsertItem(50000, tbuf);

    m_slistSubnet.SetItemText(item, 1, (const char*)pinfo->szDevDesc);
    m_slistSubnet.SetItemText(item, 2, pinfo->szIPv4Address);
    m_slistSubnet.SetItemText(item, 3, pinfo->szSerialNO);
    m_slistSubnet.SetItemText(item, 4, pinfo->szIPv4SubnetMask);
    m_slistSubnet.SetItemText(item, 5, pinfo->szIPv4Gateway);
    m_slistSubnet.SetItemText(item, 6, pinfo->szIPv6Address);
    m_slistSubnet.SetItemText(item, 7, pinfo->szIPv6Gateway);

    sprintf(tbuf, "%d", pinfo->byIPv6MaskLen);
    m_slistSubnet.SetItemText(item, 8, tbuf);
    sprintf(tbuf, "%d", pinfo->bySupportIPv6);
    m_slistSubnet.SetItemText(item, 9, tbuf);
    sprintf(tbuf, "%d", pinfo->bySupportModifyIPv6);
    m_slistSubnet.SetItemText(item, 10, tbuf);
    sprintf(tbuf, "%d", pinfo->bySupportDhcp);
    m_slistSubnet.SetItemText(item, 11, tbuf);
    sprintf(tbuf, "%d", pinfo->byDhcpEnabled);
    m_slistSubnet.SetItemText(item, 12, tbuf);

    m_slistSubnet.SetItemData(item, 0);
    m_icountSubnet++;
}

void CDlgHikSadp::OnBnClickedButtonSubnetInquery()
{
    // TODO:  在此添加控件通知处理程序代码
    DlgInquiry dlg;
    dlg.DoModal();
}
