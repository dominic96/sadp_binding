#ifndef _SADP_H_
#define _SADP_H_


#if defined _WIN32 || defined _WIN64
#define CSADP_API  extern "C" __declspec(dllimport)
#elif defined __linux__ || defined __APPLE__
#define CSADP_API  extern "C"
#endif

#if defined _WIN32 || defined _WIN64
#define CALLBACK __stdcall
#elif defined __linux__ || defined __APPLE__
#define CALLBACK  
#endif

#define BOOL int

//Type of message operation
#define SADP_ADD		  1			//Add Device
#define SADP_UPDATE		  2			//Update Device
#define SADP_DEC		  3			//Device Offline
#define SADP_RESTART	  4			//Device Restart
#define SADP_UPDATEFAIL	  5			//Update Device fail


#define SADP_GET_DEVICE_CODE   1
#define SADP_GET_ENCRYPT_STRING   2				
#define SADP_GET_DEVICE_TYPE_UNLOCK_CODE    3   
#define SADP_SET_DEVICE_CUSTOM_TYPE         4   
#define SADP_GET_GUID                       5   
#define SADP_GET_SECURITY_QUESTION          6  
#define SADP_SET_SECURITY_QUESTION          7  
#define SADP_SET_HCPLATFORM_STATUS          8   //set HCPLATFORM status
#define SADP_SET_VERIFICATION_CODE          9   //SET verification code
#define SADP_GET_BIND_LIST          12   
#define SADP_SET_BIND_LIST          13   
#define SADP_RESTORE_INACTIVE          14   
#define SADP_SET_WIFI_REGION          15   
#define SADP_SET_CHANNEL_DEFAULT_PASSWORD          16
#define SADP_GET_SELF_CHECK    17
#define SADP_DISK_LOCATE       18
#define SADP_EHOME_ENABLE       19
#define SADP_SET_USER_MAILBOX   20
#define SADP_GET_QR_CODES       21
#define SADP_GET_PASSWORD_RESET_TYPE   27
#define SADP_SET_EZVIZ_USER_TOKEN      28
#define SADP_GET_PHONE_QR_CODES        29
#define SADP_GET_DEVICE_CODE_V31       30
#define SADP_GET_ENCRYPT_STRING_V31    31
#define SADP_GET_GUID_V31              32
#define SADP_GET_QR_CODES_V31          33


#define MAX_DEVICE_CODE     128  
#define MAX_DEVICE_CODE_V31 512  
#define MAX_EXCHANGE_CODE   256  
#define MAX_PASS_LEN           16  
#define MAX_PASS_LEN_V31       128
#define MAX_FILE_PATH_LEN      260 
#define MAX_ENCRYPT_CODE       256 
#define MAX_ENCRYPT_CODE_V31   1024 
#define MAX_MAILBOX_LEN        128
#define MAX_UNLOCK_CODE_RANDOM_LEN  256   // Unlock code random string 
#define MAX_UNLOCK_CODE_KEY         256   // Unlock code key
#define MAX_QR_CODES           256
#define MAX_QR_CODES_V31       1024
#define MAX_GUID_LEN           128 //GUID LEN
#define MAX_GUID_LEN_V31       512 //v3.1 GUID LEN
#define MAX_QUESTION_LIST_LEN  32  
#define MAX_ANSWER_LEN         256 
#define SADP_MAX_VERIFICATION_CODE_LEN         12 //Max VERIFICATION CODE LEN
#define SADP_MAX_SERIALNO_LEN         64
#define SADP_MAX_BIND_NUM         32
#define MAX_CPU_LEN         32
#define MAX_MEMORY_LEN      32
#define MAX_USERNAME_LEN    32
#define MAX_TOKEN_LEN       16


// Error code
#define SADP_ERROR_BASE					2000
#define SADP_NOERROR 					0					  
#define SADP_ALLOC_RESOURCE_ERROR		(SADP_ERROR_BASE+1)   
#define SADP_NOT_START_ERROR			(SADP_ERROR_BASE+2)   
#define SADP_NO_ADAPTER_ERROR			(SADP_ERROR_BASE+3)   
#define SADP_GET_ADAPTER_FAIL_ERROR		(SADP_ERROR_BASE+4)   
#define SADP_PARAMETER_ERROR			(SADP_ERROR_BASE+5)   
#define SADP_OPEN_ADAPTER_FAIL_ERROR	(SADP_ERROR_BASE+6)   
#define SADP_SEND_PACKET_FAIL_ERROR		(SADP_ERROR_BASE+7)   
#define SADP_SYSTEM_CALL_ERROR			(SADP_ERROR_BASE+8)   
#define SADP_DEVICE_DENY		        (SADP_ERROR_BASE+9)   
#define SADP_NPF_INSTALL_ERROR			(SADP_ERROR_BASE+10)  
#define SADP_TIMEOUT					(SADP_ERROR_BASE+11)  
#define SADP_CREATE_SOCKET_ERROR		(SADP_ERROR_BASE+12)  
#define SADP_BIND_SOCKET_ERROR			(SADP_ERROR_BASE+13)  
#define SADP_JOIN_MULTI_CAST_ERROR		(SADP_ERROR_BASE+14)  
#define SADP_NETWORK_SEND_ERROR			(SADP_ERROR_BASE+15)  
#define SADP_NETWORK_RECV_ERROR			(SADP_ERROR_BASE+16)  
#define SADP_XML_PARSE_ERROR			(SADP_ERROR_BASE+17)  
#define SADP_LOCKED						(SADP_ERROR_BASE+18)  
#define SADP_NOT_ACTIVATED              (SADP_ERROR_BASE+19)  
#define SADP_RISK_PASSWORD              (SADP_ERROR_BASE+20)  
#define SADP_HAS_ACTIVATED              (SADP_ERROR_BASE+21)  
#define SADP_EMPTY_ENCRYPT_STRING       (SADP_ERROR_BASE+22)  
#define SADP_EXPORT_FILE_OVERDUE        (SADP_ERROR_BASE+23)  
#define SADP_PASSWORD_ERROR             (SADP_ERROR_BASE+24)  
#define SADP_LONG_SECURITY_ANSWER       (SADP_ERROR_BASE+25)  
#define SADP_INVALID_GUID               (SADP_ERROR_BASE+26)  
#define SADP_ANSWER_ERROR               (SADP_ERROR_BASE+27) 
#define SADP_QUESTION_NUM_ERR           (SADP_ERROR_BASE+28)  
#define SADP_LOAD_WPCAP_FAIL            (SADP_ERROR_BASE+30) 
#define SADP_ILLEGAL_VERIFICATION_CODE  (SADP_ERROR_BASE+33)  
#define SADP_BIND_ERROR_DEV             (SADP_ERROR_BASE+34)  
#define SADP_EXTED_MAX_BIND_NUM         (SADP_ERROR_BASE+35) 
#define SADP_MAILBOX_NOT_EXIST          (SADP_ERROR_BASE+36)
#define SADP_MAILBOX_NOT_SET            (SADP_ERROR_BASE+38)
#define SADP_INVALID_RESET_CODE         (SADP_ERROR_BASE+39)
#define SADP_NO_PERMISSION              (SADP_ERROR_BASE+40)
#define SADP_GET_EXCHANGE_CODE_ERROR    (SADP_ERROR_BASE+41)
#define SADP_CREATE_RSA_KEY_ERROR       (SADP_ERROR_BASE+42)
#define SADP_BASE64_ENCODE_ERROR        (SADP_ERROR_BASE+43)
#define SADP_BASE64_DECODE_ERROR        (SADP_ERROR_BASE+44)
#define SADP_AES_ENCRYPT_ERROR          (SADP_ERROR_BASE+45)
#define SADP_PHONE_NOT_SET              (SADP_ERROR_BASE+46)
#define SADP_NOENOUGH_BUF               (SADP_ERROR_BASE+47)
#define SADP_INVALID_SUBNET_IP          (SADP_ERROR_BASE+48)


//SADP Device Filter rule type
#define SADP_DISPLAY_ALL           0            
#define SADP_FILTER_EZVIZ          0x01         
#define SADP_FILTER_OEM            0x02         
#define SADP_FILTER_EZVIZ_OEM      0x03         
#define SADP_ONLY_DISPLAY_OEM      0xfffffffd   
#define SADP_ONLY_DISPLAY_EZVIZ    0xfffffffe   


typedef struct tagSADP_DEVICE_INFO
{
	char			szSeries[12];
	char			szSerialNO[48];
	char			szMAC[20];
	char			szIPv4Address[16];
	char			szIPv4SubnetMask[16];
	unsigned int	dwDeviceType;
	unsigned int	dwPort;
	unsigned int	dwNumberOfEncoders; 
	unsigned int	dwNumberOfHardDisk;
	char			szDeviceSoftwareVersion[48];
	char			szDSPVersion[48]; 
	char			szBootTime[48];
	int				iResult;
	char			szDevDesc[24];       
	char			szOEMinfo[24];       
	char			szIPv4Gateway[16];   
	char			szIPv6Address[46];	 
	char			szIPv6Gateway[46];   
	unsigned char   byIPv6MaskLen;       
    unsigned char   bySupport;           //According to the position, the corresponding value is 1 to support:,0x01:support Ipv6,0x02:support modificatate Ipv6,0x04:support Dhcp	0x08: support udp  multicase,0x10:encrypt node,0x20:support restore default password,0x40:support reset password			 
	unsigned char   byDhcpEnabled;       //Dhcp, 0 :not enable, 1:enable
    unsigned char   byDeviceAbility;	//0：device not support “‘Device type description’ 'OEM' 'IPv4 Gateway' ‘IPv6’ 'IPv6 Gateway' ‘IPv6 Mask len’‘DHCP’”  1：support above functions
	unsigned short	wHttpPort;			// Http port
	unsigned short	wDigitalChannelNum;
	char			szCmsIPv4[16];
	unsigned short	wCmsPort;
	unsigned char	byOEMCode;  //0-base device 1-OEM device
    unsigned char   byActivated; //Device activation state,0-Activated，1-Not activated
	char			szBaseDesc[24];	
    unsigned char   bySupport1; //According to the position, the corresponding value is 1 to support:
                               //0x01:support ResetMode2  
								// 0x02: support Lock
	                         //0x04:support GUID
                          //0x08: Qustion 
	unsigned char   byHCPlatform; //support HCPlatform 0-res， 1-support， 2-not support   
	unsigned char   byEnableHCPlatform; //Enable  HCPlatform 0 -res 1- support， 2- not support 
    unsigned char   byEZVIZCode;        //0-base device 1- EZVIZ
    unsigned int    dwDetailOEMCode;
	unsigned char   byModifyVerificationCode; //0-res, 1- modify ，2- not modify
    unsigned char    byMaxBindNum;
    unsigned short	 wOEMCommandPort;
    unsigned char    bySupportWifiRegion;// Support Wifi Region，the corresponding value is 1 to support
                                        //0x01:support default
                                        //0x02:support china
                                        //0x04:support nothAmerica
                                        //0x08: support japan
                                        //0x10: support europe
                                        //0x20:support world
    unsigned char    byEnableWifiEnhancement;//Enable Wifi Enhancement,0-not enable，1-enable
    unsigned char    byWifiRegion;//current wifi region，0-default，1-china，2-nothAmerica，3-japan，4-europe,5-world
    unsigned char   bySupport2; //According to the position, the corresponding value is 1 to support:
                      //0x01:support chanael default password 
                      //0x02:support MAILBOX reset password
                      //0x04:support set SSID and password
}SADP_DEVICE_INFO, *LPSADP_DEVICE_INFO;

typedef struct tagSADP_DEVICE_INFO_V40
{
    SADP_DEVICE_INFO struSadpDeviceInfo;
    unsigned char   byLicensed;
    unsigned char   bySystemMode;
    unsigned char   byControllerType;
    char			szEhmoeVersion[16];
    unsigned char   bySpecificDeviceType;
    unsigned int	dwSDKOverTLSPort;
    unsigned char   bySecurityMode;
    unsigned char   bySDKServerStatus;
    unsigned char   bySDKOverTLSServerStatus;
    char            szUserName[MAX_USERNAME_LEN + 1];
    char            szWifiMAC[20];
    unsigned char   byDataFromMulticast;
    unsigned char   bySupportEzvizUnbind;
    unsigned char   bySupportCodeEncrypt;
    unsigned char   bySupportPasswordResetType;
    unsigned char   byEZVIZBindStatus;
    char            szPhysicalAccessVerification[16];
    unsigned short  wHttpsPort;
    unsigned char   bySupportEzvizUserToken;
    char            szDevDescEx[64];
    char            szSerialNOEx[128];
    char            szManufacturer[32];
    unsigned char   bySupportResetPwByPhoneNo;
    unsigned char   byRes[183];
}SADP_DEVICE_INFO_V40, *LPSADP_DEVICE_INFO_V40;


typedef struct tagSADP_DEV_NET_PARAM
{
	char			szIPv4Address[16];		
	char			szIPv4SubNetMask[16];	
	char			szIPv4Gateway[16];		
	char			szIPv6Address[128];		
	char			szIPv6Gateway[128];		
	unsigned short	wPort;					
	unsigned char	byIPv6MaskLen;			
	unsigned char	byDhcpEnable;			
	unsigned short	wHttpPort;
    unsigned int	dwSDKOverTLSPort;
	unsigned char	byRes[122];
}SADP_DEV_NET_PARAM, *LPSADP_DEV_NET_PARAM;


typedef struct tagSADP_DEV_RET_NET_PARAM
{
    unsigned char   byRetryModifyTime;  
    unsigned char   bySurplusLockTime;  
    unsigned char	byRes[126];
}SADP_DEV_RET_NET_PARAM, *LPSADP_DEV_RET_NET_PARAM;


typedef struct tagSADP_SAFE_CODE
{
	unsigned int    dwCodeSize;
	char            szDeviceCode[MAX_DEVICE_CODE];
    unsigned char   byRes[128];
}SADP_SAFE_CODE, *LPSADP_SAFE_CODE;

typedef struct tagSADP_SAFE_CODE_V31
{
    unsigned int    dwCodeSize;
    char            szDeviceCode[MAX_DEVICE_CODE_V31];
    unsigned char   byRes[512];
}SADP_SAFE_CODE_V31, *LPSADP_SAFE_CODE_V31;

typedef struct tagSADP_QR_CODES
{
    unsigned int    dwCodeSize;
    unsigned int    dwMailBoxSize;
    unsigned int    dwServiceMailBoxSize;
    char            szQrCodes[MAX_QR_CODES];
    char            szMailBoxAddr[MAX_MAILBOX_LEN];
    char            szServiceMailBoxAddr[MAX_MAILBOX_LEN];
    unsigned char   byRes[128];
}SADP_QR_CODES, *LPSADP_QR_CODES;

typedef struct tagSADP_QR_CODES_V31
{
    unsigned int    dwCodeSize;
    unsigned int    dwMailBoxSize;
    unsigned int    dwServiceMailBoxSize;
    char            szQrCodes[MAX_QR_CODES_V31];
    char            szMailBoxAddr[MAX_MAILBOX_LEN];
    char            szServiceMailBoxAddr[MAX_MAILBOX_LEN];
    unsigned char   byRes[256];
}SADP_QR_CODES_V31, *LPSADP_QR_CODES_V31;

typedef struct tagSADP_ENCRYPT_STRING
{
    unsigned int    dwEncryptStringSize;
    char            szEncryptString[MAX_ENCRYPT_CODE];
    unsigned char   byRes[128];
}SADP_ENCRYPT_STRING, *LPSADP_ENCRYPT_STRING;

typedef struct tagSADP_ENCRYPT_STRING_V31
{
    unsigned int    dwEncryptStringSize;
    char            szEncryptString[MAX_ENCRYPT_CODE_V31];
    unsigned char   byRes[512];
}SADP_ENCRYPT_STRING_V31, *LPSADP_ENCRYPT_STRING_V31;

typedef struct tagSADP_RESET_PARAM
{
    char            szCode[MAX_ENCRYPT_CODE]; 
    char            szAuthFile[MAX_FILE_PATH_LEN];             
    char            szPassword[MAX_PASS_LEN];  
    unsigned char   byEnableSyncIPCPW;      
    unsigned char   byRes[511];
}SADP_RESET_PARAM, *LSADP_RESET_PARAM;


typedef struct tagSADP_DISPLAY_OEM_CFG
{
    unsigned int    dwDisplayOEM;      	
    unsigned char   byRes[32];  //RES
}SADP_DISPLAY_OEM_CFG, *LPSADP_DISPLAY_OEM_CFG;

typedef struct tagSADP_TYPE_UNLOCK_CODE
{
    unsigned int dwCodeSize;
    char       szDeviceTypeUnlockCode[MAX_UNLOCK_CODE_RANDOM_LEN/*256*/];//Unlock code random string 
    unsigned char  byRes[128];
}SADP_TYPE_UNLOCK_CODE, *LPSADP_TYPE_UNLOCK_CODE;

typedef struct tagSADP_CUSTOM_DEVICE_TYPE
{
    unsigned int dwCodeSize;
    char       szDeviceTypeSecretKey[MAX_UNLOCK_CODE_KEY/*256*/];//Unlock code key
    unsigned char  byRes[128];
}SADP_CUSTOM_DEVICE_TYPE, *LPSADP_CUSTOM_DEVICE_TYPE;

typedef struct tagSADP_GUID_FILE_COND
{
    char           szPassword[MAX_PASS_LEN];  //user password
    unsigned char  byRes[128];
}SADP_GUID_FILE_COND, *LPSADP_GUID_FILE_COND;

typedef struct tagSADP_GUID_FILE
{
    unsigned int    dwGUIDSize;
    char            szGUID[MAX_GUID_LEN];
    unsigned char   byRetryGUIDTime;    //retry GUID times
    unsigned char   bySurplusLockTime;  //surplus lock times (unit:minutes)
    unsigned char   byRes[254];
}SADP_GUID_FILE, *LPSADP_GUID_FILE;

typedef struct tagSADP_SINGLE_SECURITY_QUESTION_CFG
{
    unsigned int     dwSize;
    unsigned int     dwId;
    char             szAnswer[MAX_ANSWER_LEN/*256*/]; //answer (get param invalid)
    unsigned char    byMark; //mark
    unsigned char    byRes[127];
}SADP_SINGLE_SECURITY_QUESTION_CFG, *LPSADP_SINGLE_SECURITY_QUESTION_CFG;

typedef struct tagSADP_SECURITY_QUESTION_CFG
{
    unsigned int   dwSize;
    SADP_SINGLE_SECURITY_QUESTION_CFG  struSecurityQuestion[MAX_QUESTION_LIST_LEN/*32*/];//security question list
    char           szPassword[MAX_PASS_LEN];  //user password
    unsigned char  byRes[512];
}SADP_SECURITY_QUESTION_CFG, *LPSADP_SECURITY_QUESTION_CFG;

typedef struct tagSADP_SECURITY_QUESTION
{
    unsigned char   byRetryAnswerTime;  //retry ansewr times
    unsigned char   bySurplusLockTime;  //surplus lock time  (unit:minutes)
    unsigned char   byRes[254];
}SADP_SECURITY_QUESTION, *LPSADP_SECURITY_QUESTION;

typedef struct tagSADP_RESET_PARAM_V40
{
    unsigned int    dwSize;
    unsigned char   byResetType;
    unsigned char   byEnableSyncIPCPW;
    unsigned char   byRes2[2];
    char            szPassword[MAX_PASS_LEN];
    char            szCode[MAX_ENCRYPT_CODE];
    char            szAuthFile[MAX_FILE_PATH_LEN];
    char            szGUID[MAX_GUID_LEN];
    SADP_SECURITY_QUESTION_CFG struSecurityQuestionCfg;
    unsigned char   byRes[512];
}SADP_RESET_PARAM_V40, *LPSADP_RESET_PARAM_V40;

typedef struct tagSADP_RESET_PARAM_V50
{
    unsigned int    dwSize;
    char            szPassword[MAX_PASS_LEN_V31];
    char            szCode[MAX_ENCRYPT_CODE_V31];
    char            szAuthFile[MAX_FILE_PATH_LEN];
    char            szGUID[MAX_GUID_LEN_V31];
    SADP_SECURITY_QUESTION_CFG struSecurityQuestionCfg;
    unsigned char   byResetType;
    unsigned char   byEnableSyncIPCPW;
    unsigned char   byRes[510];
}SADP_RESET_PARAM_V50, *LPSADP_RESET_PARAM_V50;

typedef struct tagSADP_RET_RESET_PARAM_V40
{
    unsigned char   byRetryGUIDTime;  //retry GUID times
    unsigned char   bySurplusLockTime;  //surplus lock times (unit:minutes)
    unsigned char   bRetryTimeValid;
    unsigned char   bLockTimeValid;
    unsigned char   byRes[252];
}SADP_RET_RESET_PARAM_V40, *LPSADP_RET_RESET_PARAM_V40;

//HCPlatform status
typedef struct tagSADP_HCPLATFORM_STATUS_INFO
{
	unsigned int    dwSize;
	unsigned char   byEnableHCPlatform;        //Enable  HCPlatform 0 -res 1- support， 2- not support
	unsigned char   byRes[3];             //res
	char            szPassword[MAX_PASS_LEN];  //psssword
	unsigned char	byRes2[128];
}SADP_HCPLATFORM_STATUS_INFO, *LPSADP_HCPLATFORM_STATUS_INFO;

typedef struct tagSADP_USER_MAILBOX
{
    unsigned int    dwSize;
    char             szPassword[MAX_PASS_LEN];
    char             szMailBoxAddr[MAX_MAILBOX_LEN];
    unsigned char    byRes[128];
}SADP_USER_MAILBOX, *LPSADP_USER_MAILBOX;

//VERIFICATION CODE
typedef struct tagSADP_VERIFICATION_CODE_INFO
{
	unsigned int    dwSize;
	char            szVerificationCode[SADP_MAX_VERIFICATION_CODE_LEN];  
	char            szPassword[MAX_PASS_LEN];  
	unsigned char	byRes[128];
}SADP_VERIFICATION_CODE_INFO, *LPSADP_VERIFICATION_CODE_INFO;

//Dev Lock info
typedef struct tagSADP_DEV_LOCK_INFO
{
    unsigned char   byRetryTime;
    unsigned char   bySurplusLockTime;
    unsigned char	byRes[126];
}SADP_DEV_LOCK_INFO, *LPSADP_DEV_LOCK_INFO;

typedef struct tagSADP_BIND_INFO
{
    char            szSerialNO[SADP_MAX_SERIALNO_LEN];
    unsigned char   byiBind;
    unsigned char    byRes[127];
}SADP_BIND_INFO, *LPSADP_BIND_INFO;

typedef struct tagSADP_BIND_LIST
{
    SADP_BIND_INFO   struBindInfo[SADP_MAX_BIND_NUM];
    char             szPassword[MAX_PASS_LEN];
    unsigned char    byUnbindAll;
    unsigned char    byRes[127];
}SADP_BIND_LIST, *LPSADP_BIND_LIST;

typedef struct tagSADP_INACTIVE_INFO
{
    char             szPassword[MAX_PASS_LEN];
    unsigned char    byRes[128];
}SADP_INACTIVE_INFO, *LPSADP_INACTIVE_INFO;

//wifi Region
typedef struct tagSADP_WIFI_REGION_INFO
{
    unsigned char   byMode;//mode，1-wifi  region mode，2-wifiEnhancement mode
    unsigned char   byWifiRegion;        //wifi  region，0 -default， 1- china, 2-nothAmerica,3-japan,4-europe, 5-world
    unsigned char   byWifiEnhancementEnabled;        //wifi Enhancement  0 -not enable， 1- enablde
    unsigned char   byRes;
    char            szPassword[MAX_PASS_LEN];  //password
    unsigned char	byRes2[128];
}SADP_WIFI_REGION_INFO, *LPSADP_WIFI_REGION_INFO;

typedef struct tagSADP_CHANNEL_DEFAULT_PASSWORD
{
    char             szPassword[MAX_PASS_LEN];  //
    char             szChannelDefaultPassword[MAX_PASS_LEN];  
    unsigned char    byRes[128];
}SADP_CHANNEL_DEFAULT_PASSWORD, *LPSADP_CHANNEL_DEFAULT_PASSWORD;

typedef struct tagSADP_SELF_CHECK_STATE
{
    unsigned int    dwSize;
    int    dwTotalDisk;
    int    dwGoodDisk;
    char            szCPU[MAX_CPU_LEN];
    char            szMemory[MAX_MEMORY_LEN];
    unsigned char   byProgress;
    unsigned char   byTemperatureState;
    unsigned char   byFanState;
    unsigned char   byPowerState;
    unsigned char   bySASConnectState;
    char   byTotalNetworkPort;
    char   byConnectNetworkPort;
    unsigned char   byRes[129];
}SADP_SELF_CHECK_STATE, *LPSADP_SELF_CHECK_STATE;

//EHome使能参数
typedef struct tagSADP_EHOME_ENABLE_PARAM
{
    unsigned int    dwSize;
    char            szDevID[MAX_PASS_LEN];    //ID
    char            szEhomeKey[MAX_PASS_LEN];  //Ehome Key
    char            szPassword[MAX_PASS_LEN];
    unsigned char   byRes[64];
}SADP_EHOME_ENABLE_PARAM, *LPSADP_EHOME_ENABLE_PARAM;

//WIFI config
typedef struct tagSADP_WIFI_CONFIG_PARAM
{
    unsigned int    dwSize;
    char            szSSID[SADP_MAX_SERIALNO_LEN];      //SSID
    char            szPassword[SADP_MAX_SERIALNO_LEN];  //password
    unsigned char   byWifiMode;  //wifi mode ，0-default，1-Station， 2-AP
    unsigned char   byRes[64];
}SADP_WIFI_CONFIG_PARAM, *LPSADP_WIFI_CONFIG_PARAM;

//Password Reset Type
typedef struct tagSADP_PASSWORD_RESET_TYPE_PARAM
{
    unsigned int    dwSize;
    unsigned char   byEnable;
    unsigned char   byGuidEnabled;
    unsigned char   bySecurityQuestionEnabled;
    unsigned char   bySecurityMailBoxEnabled;
    unsigned char   byHikConnectEnabled;
    unsigned char   byRes1[3];
    unsigned char   byRes[64];
}SADP_PASSWORD_RESET_TYPE_PARAM, *LPSADP_PASSWORD_RESET_TYPE_PARAM;

typedef struct tagSADP_EZVIZ_USER_TOKEN_PARAM
{
    unsigned int    dwSize;
    char            szToken[MAX_TOKEN_LEN]; //token
    char            szPassword[MAX_PASS_LEN]; //password，8-16字节
    unsigned char   byRes[256];
}SADP_EZVIZ_USER_TOKEN_PARAM, *LPSADP_EZVIZ_USER_TOKEN_PARAM;

typedef struct tagSADP_PHONE_QR_CODES
{
    unsigned int    dwSize;
    char            szDomainName[MAX_QR_CODES];
    char            szDevModel[32];
    char            szQrCodes[MAX_QR_CODES_V31];
    unsigned char   byRes[128];
}SADP_PHONE_QR_CODES, *LPSADP_PHONE_QR_CODES;

typedef struct tagSADP_GUID_FILE_V31
{
    unsigned int    dwGUIDSize;
    char            szGUID[MAX_GUID_LEN_V31];
    SADP_DEV_LOCK_INFO struDevLockInfo;
    unsigned char   byRes[256];
}SADP_GUID_FILE_V31, *LPSADP_GUID_FILE_V31;

typedef struct tagSADP_SUBNET_INFO
{
    unsigned int    dwSize;
    unsigned char   byIPType;
    unsigned char   byRes1[3];
    char            szStartSubnetIP[48];
    char            szStopSubnetIP[48];
    unsigned char   byRes[128];
}SADP_SUBNET_INFO, *LPSADP_SUBNET_INFO;

typedef struct tagSADP_SUBNET_DEVICE_INFO
{
    unsigned int    dwDeviceType;
    char            szDevDesc[64];
    char            szSerialNO[128];
    char            szIPv4Address[16];
    char            szIPv4SubnetMask[16];
    char            szIPv4Gateway[16];
    char            szIPv6Address[46];
    char            szIPv6Gateway[46];
    unsigned char   byIPv6MaskLen;
    unsigned char   bySupportIPv6;
    unsigned char   bySupportModifyIPv6;
    unsigned char   bySupportDhcp;
    unsigned char   byDhcpEnabled;
    unsigned char   byRes1[3];
    unsigned char   byRes[1024];
}SADP_SUBNET_DEVICE_INFO, *LPSADP_SUBNET_DEVICE_INFO;




// Interface
typedef void (CALLBACK *PDEVICE_FIND_CALLBACK)(const SADP_DEVICE_INFO *lpDeviceInfo, void *pUserData);
CSADP_API BOOL CALLBACK SADP_Start_V30(PDEVICE_FIND_CALLBACK pDeviceFindCallBack, int bInstallNPF = 0, void* pUserData = NULL);
typedef void (CALLBACK *PDEVICE_FIND_CALLBACK_V40)(const SADP_DEVICE_INFO_V40 *lpDeviceInfo, void *pUserData);
CSADP_API BOOL CALLBACK SADP_Start_V40(PDEVICE_FIND_CALLBACK_V40 pDeviceFindCallBack, int bInstallNPF = 0, void* pUserData = NULL);
typedef void (CALLBACK *PSUBNET_DEVICE_FIND_CALLBACK)(const SADP_SUBNET_DEVICE_INFO *lpDeviceInfo, void *pUserData);

typedef struct tagSADP_START_PARAM
{
    PDEVICE_FIND_CALLBACK_V40 fnDevCB;
    PSUBNET_DEVICE_FIND_CALLBACK fnSubnetDevCB;
    void* pUserData;
    unsigned char   byRes[1024];
}SADP_START_PARAM, *LPSADP_START_PARAM;

CSADP_API BOOL CALLBACK SADP_Start_V50(LPSADP_START_PARAM pStartParam);
CSADP_API BOOL  CALLBACK SADP_SendInquiry(void);
CSADP_API BOOL CALLBACK SADP_InquirySpecificSubnet(const SADP_SUBNET_INFO *pSubnetInfo);
CSADP_API BOOL  CALLBACK SADP_Stop(void);
CSADP_API BOOL CALLBACK SADP_ModifyDeviceNetParam(const char* sMAC, const char* sPassword, const SADP_DEV_NET_PARAM *lpNetParam);
CSADP_API unsigned int CALLBACK SADP_GetSadpVersion(void);
CSADP_API BOOL CALLBACK SADP_SetLogToFile(int nLogLevel=0, char const *strLogDir = NULL, int bAutoDel = 1);		
CSADP_API unsigned int CALLBACK SADP_GetLastError(void);
CSADP_API BOOL CALLBACK SADP_ResetDefaultPasswd(const char* sDevSerialNO, const char* sCommand);
CSADP_API BOOL CALLBACK SADP_Clearup(void);
CSADP_API void CALLBACK SADP_SetAutoRequestInterval(unsigned int dwInterval);

CSADP_API BOOL CALLBACK SADP_GetDeviceConfig(const char* sDevSerialNO, unsigned int dwCommand,void* lpInBuffer, unsigned int  dwinBuffSize, void *lpOutBuffer, unsigned int  dwOutBuffSize);
CSADP_API BOOL CALLBACK SADP_SetDeviceConfig(const char* sDevSerialNO, unsigned int dwCommand, void* lpInBuffer, unsigned int  dwInBuffSize, void* lpOutBuffer, unsigned int  dwOutBuffSize);
CSADP_API BOOL CALLBACK SADP_GetDeviceConfigByMAC(const char* sDevMAC, unsigned int dwCommand, void* lpInBuffer, unsigned int  dwinBuffSize, void *lpOutBuffer, unsigned int  dwOutBuffSize);

CSADP_API BOOL CALLBACK SADP_ActivateDevice(const char* sDevSerialNO, const char* sCommand);


CSADP_API BOOL CALLBACK SADP_ResetPasswd(const char* sDevSerialNO, const SADP_RESET_PARAM *pResetParam);
CSADP_API BOOL CALLBACK SADP_ResetPasswd_V40(const char* sDevSerialNO, const SADP_RESET_PARAM_V40 *pResetParam, SADP_RET_RESET_PARAM_V40 *pRetResetParam);
CSADP_API BOOL CALLBACK SADP_ResetPasswd_V50(const char* sDevSerialNO, const SADP_RESET_PARAM_V50 *pResetParam, SADP_DEV_LOCK_INFO *pLockInfo);

//Set Device Filter Rule
//dwFilterRule,if the result of bit is 1, it means filter:0: not filter;0x01:filter EZVIZ;0x02:filter OEM;0x03:filter EZVIZ and OEM;0xfffffffe:only display EZVIZ;0xfffffffd:only display OEM
CSADP_API BOOL CALLBACK SADP_SetDeviceFilterRule( unsigned int dwFilterRule, const void *lpInBuff, unsigned int dwInBuffLen);
//Modify the network parameters V40
CSADP_API BOOL CALLBACK SADP_ModifyDeviceNetParam_V40(const char* sMAC, const char* sPassword, const SADP_DEV_NET_PARAM *lpNetParam, SADP_DEV_RET_NET_PARAM *lpRetNetParam, unsigned int  dwOutBuffSize);

#endif




