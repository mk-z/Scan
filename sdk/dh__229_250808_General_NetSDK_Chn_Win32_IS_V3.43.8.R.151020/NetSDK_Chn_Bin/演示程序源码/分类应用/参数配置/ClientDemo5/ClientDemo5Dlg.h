// ClientDemo5Dlg.h : header file
//

#if !defined(AFX_CLIENTDEMO5DLG_H__71084F64_0DFF_43C2_8AD9_6F5AE7FE9253__INCLUDED_)
#define AFX_CLIENTDEMO5DLG_H__71084F64_0DFF_43C2_8AD9_6F5AE7FE9253__INCLUDED_

#include "dhnetsdk.h"
#include "dhconfigsdk.h"
#include "ConfigServer.h"	// Added by ClassView
#include "ConfigComm.h"	    // Added by ClassView
#include "ConfigChannel.h"	// Added by ClassView
#include "ConfigAlarm.h"	// Added by ClassView
#include "ConfigRecord.h"	// Added by ClassView
#include "ConfigNetwork.h"	// Added by ClassView
#include "ConfigCover.h"	// Added by ClassView
#include "ConfigStrategy.h"
#include "Configfile.h"
#include "DlgIPC.h"
#include "ConfigFTP.h"
#include "ConfigVideoIn.h"
#include "ConfigFTPEx.h"
#include "ConfigFTPMain.h"
#include "ConfigChannelEx.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5Dlg dialog

class CClientDemo5Dlg : public CDialog
{
// Construction
public:
	void GetCoverConfigInfo();
    BOOL SetAlarmName(const DHDEV_ALARM_SCHEDULE_EX* pAlarmInfo);
	void SetAlarmConfigInfo(DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo);	
	//Get alarm property configuration information(ALL)
	void GetAlarmConfigInfo();
	//Save network configuration information
	void SetNetWorkConfigInfo(DHDEV_NET_CFG_EX *pNetIOInfo, CFG_EMAIL_INFO& stuMailInfo, CFG_MULTICASTS_INFO_IN* pMulticastIn);
	//Get network configuration information
	void GetNetWorkConfigInfo();
	//Set video configuration information
	void SetRecordConfigInfo(DHDEV_RECORD_CFG *pRecordInfo,BYTE nLength);
	//Get video configuration information
	void GetRecordConfigInfo();
	//Save COM information
	void SetCommConfigInfo(DEV_COMM_CFG_EX *pCommInfo, int nCurChannel = 0);
	//Get COM information
	void GetCommConfigInfo();
	//Save video channel property configuration information
	//void SetChannelConfigInfo(DHDEV_CHANNEL_CFG *pChannelInfo, int nLength);
	//Get video channel property
	void GetChannelConfigInfo();
	//Get videoInoption property
	void GetVideoInputOption();
	//Get FtpEx property();
	void GetFtpExInfo();
    //Get EncodeEx property
    void GetChannelConfigInfoEx();

	// more than 32 channels configuration
	void SetOneCoverConfigInfo(DHDEV_VIDEOCOVER_CFG *pInfo, int nCurChannel = 0);
	void GetOneCoverConfigInfo(DHDEV_VIDEOCOVER_CFG *pInfo, int nCurChannel = 0);
	void SetAlarmInConfigInfo(CFG_ALARMIN_INFO *pAlarmIn, int nCurChannel = 0);
	void SetMotionAlarmConfigInfo(int nCurChannel = 0, CFG_MOTION_INFO* pMotionInfo = NULL);
	void SetBlindAlarmConfigInfo(CFG_SHELTER_INFO *pShelterInfo, int nCurChannel = 0);
	void SetLossAlarmConfigInfo(CFG_VIDEOLOST_INFO *pVideoLostInf, int nCurChannel = 0);
	void GetAlarmInConfigInfo(CFG_ALARMIN_INFO *pAlarmIn,int nCurChannel = 0);
	void GetMotionAlarmConfigInfo(CFG_MOTION_INFO *pMotionInfo,int nCurChannel = 0);
	void GetBlindAlarmConfigInfo(CFG_SHELTER_INFO *pShelterInfo, int nCurChannel = 0);
	void GetLossAlarmConfigInfo(CFG_VIDEOLOST_INFO *pVideoLostInf, int nCurChannel = 0);
	void SetOneRecordConfigInfo(DHDEV_RECORD_CFG *pInfo, int nCurChannel = 0);
	void GetOneRecordConfigInfo(DHDEV_RECORD_CFG *pInfo, int nCurChannel = 0);

	//P3
	void SetOneChannelConfigInfo(CFG_ENCODE_INFO *pstEncodeInfo,int nCurChannel = 0);
	void GetOneChannelConfigInfo(CFG_ENCODE_INFO *pstEncodeInfo,int nCurChannel = 0);
	
	void SetFTPEXConfigInfo(CFG_NAS_INFO_EX *pstNasInfoEx,int nCurChannel = 0);
	void GetFTPEXConfigInfo(CFG_NAS_INFO_EX *pstNasInfoEx,int nCurChannel = 0);
	
    void GetRemoteStorageLimit(CFG_REMOTE_STORAGELIMIT_GROUP *pstRemoteStorage, int nCurChannel = 0);
    void SetRemoteStorageLimit(CFG_REMOTE_STORAGELIMIT_GROUP *pstRemoteStorage, int nCurChannel = 0);

	//Set device property configuration information
	void SetDeviceConfigInfo(LPDHDEV_SYSTEM_ATTR_CFG sysConfigInfo);
	//Get device property configuration information
	void GetDeviceConfigInfo();

	void SetStrategyConfigInfo(CFG_DVRIP_INFO* pDVRIPInfo,DHDEV_DOWNLOAD_STRATEGY_CFG* pDownloadInfo);
	void GetStrategyConfigInfo();

	//Configuration file
	LONG ImportConfigFile(char* szPathName, fDownLoadPosCallBack cbUploadPos, DWORD dwUser);
	LONG ExportConfigFile(char* szFileName, DH_CONFIG_FILE_TYPE emConfigFileType, fDownLoadPosCallBack cbUploadPos, DWORD dwUser);

	//Interface for callback
	void DeviceDisConnect(LLONG lLoginID, char *sDVRIP,LONG nDVRPort);
	//Callback function when device disconnected
	friend void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
	
	CClientDemo5Dlg(CWnd* pParent = NULL);	// standard constructor
	~CClientDemo5Dlg();

	void ResolutionSizetoInt(int nResolution, int *nWidth, int *nHeight);
	int ResolutionInttoSize(int nWidth, int nHeight);
	void ParseEventHandle(CFG_ALARM_MSG_HANDLE& stuHandlle, DH_MSG_HANDLE_EX *pstruHandle);
	void BuildEventHandle(DH_MSG_HANDLE_EX stuHandlle, CFG_ALARM_MSG_HANDLE *pstruHandle);
	void Change_Assic_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen);
	void Change_Utf8_Assic(unsigned char * pUTF8, char *destbuf);
	void GetOneChannelDspConfigF6(int nCurChannel, CFG_ENCODE_INFO& encInfo, NET_OUT_ENCODE_CFG_CAPS& stEncodeCfgCaps, BOOL& bShowPix);

    void GetOneChannelDspConfig(int nCurChannel, DHDEV_DSP_ENCODECAP &stDspInfo, CFG_DSPENCODECAP_INFO &stDspEncodeCapInfo, NET_OUT_ENCODE_CFG_CAPS& stEncodeCfgCaps, BOOL& bShowPix);
	
	void GetOneChannelOsdInfo(AV_CFG_VideoWidget *pstVideoWidget, int nCurChannel = 0);
	void SetOneChannelOsdInfo(AV_CFG_VideoWidget *pstVideoWidget, int nCurChannel = 0);
	void InitAVCFGVIdeoWidget(AV_CFG_VideoWidget *pstVideoWidget);

	void GetOneChannelVideoColor(AV_CFG_ChannelVideoColor *pstChannelVideoColor, int nCurChannel = 0);
	void SetOneChannelVideoColor(AV_CFG_ChannelVideoColor *pstChannelVideoColor, int nCurChannel = 0);
	void InitAVCFGVideoColor(AV_CFG_ChannelVideoColor *pstChannelVideoColor);
	
	void GetOneChannelName(AV_CFG_ChannelName *pstChannelName, int nCurChannel = 0);
	void SetOneChannelName(AV_CFG_ChannelName *pstChannelName, int nCurChannel = 0);
	void InitAVCFGChannelName(AV_CFG_ChannelName *pstChannelName);

	void GetOneVideoInOption(CFG_VIDEO_IN_OPTIONS * pstVideoInOption, int nCurChannel = 0);
	void SetOneVideoInOption(CFG_VIDEO_IN_OPTIONS * pstVideoInOption, int nCurChannel = 0); 
	

	void GetOneVideoCapVieoInfo(CFG_CAP_VIDEOINPUT_INFO *pstCapVieoInput, int nCurChannel = 0);

    BOOL GetMailConfig(CFG_EMAIL_INFO& stuMailInfo);
    BOOL SetMailConfig(CFG_EMAIL_INFO& stuMailInfo);

    BOOL GetDVRIPConfig(CFG_DVRIP_INFO& stuDVRIPInfo, int nWaitTime = SDK_DEMO_WAITTIME);
    BOOL SetDVRIPConfig(CFG_DVRIP_INFO& stuDVRIPInfo, int nWaitTime = SDK_DEMO_WAITTIME);

	BOOL IsWholeDay(AV_CFG_ChannelVideoColor *pstChannelVideoColor);

    BOOL GetVideoDetectCaps(NET_IN_VIDEO_DETECT_CAPS& stuInParam , NET_OUT_VIDEO_DETECT_CAPS& stuOutParam);

// Dialog Data
	//{{AFX_DATA(CClientDemo5Dlg)
	enum { IDD = IDD_CLIENTDEMO5_DIALOG };
	CComboBox	m_ctlRevertType;
	CTabCtrl	m_ctlMainTab;
	CString	m_strDvrIP;
	UINT	m_nPort;
	CString	m_strUserName;
	CString	m_strPwd;
	BOOL m_b3ProDev;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo5Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
public:
	//add by yu_peng
	//因为一次只能登陆一个设备，所以最多多一个页面
	BOOL AddPage(CString strTitle, CDialog* dlgPage, UINT uID);
	BOOL DeletePage();

	enum PAGETYPE{NONE, IPC, DVR};
	PAGETYPE FromDeviceType(NET_DEVICE_TYPE eDeviceType);
	//end add
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDemo5Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLogout();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonRevert();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nDevProtoVer;
	CConfigCover m_coverDlg;
	void InitCombo();
	void SetDlgState(CWnd *pWnd, BOOL bShow);
	void DoTab(int nTab);
	CConfigNetwork m_networkDlg;
	CConfigRecord m_recordDlg;
	CConfigAlarm m_alarmDlg;
	CConfigChannel m_channelDlg;
	CConfigComm m_commDlg;
	CConfigServer m_serverDlg;
	CConfigStrategy m_StrategyDlg;
	CConfigFile		m_configFile;
	//CConfigFTP      m_configFTP;
	CConfigVideoIn  m_VideoInDlg;
	//CConfigFTPEx    m_configFTPEX;
	CConfigFTPMain  m_configFTPMain;
	//CDlgIPC			m_configIPC;
	CDialog*	m_dlgDeviceType;
    CConfigChannelEx m_channelDlgEx;

	void InitTabControl();
	void ShowLoginErrorReason(int nError);
	//CString GetDvrIP();
	LLONG m_LoginID;
	int m_nChannel;
	void InitNetSDK();
	int m_nVideoStandard;
	BOOL InitAlarmName(DHDEV_ALARM_SCHEDULE_EX* pAlarmInfo);
	//16路以上设备的配置
	CFG_ENCODE_INFO m_stuEncodeInfo;
	CFG_PTZ_INFO m_PTZInfo;
	CFG_RECORD_INFO m_RecordInfo;
	CFG_ALARMIN_INFO *m_AlarmInfo;
	CFG_MOTION_INFO *m_MotionInfo;
	CFG_SHELTER_INFO *m_BlindInfo;
	CFG_VIDEOLOST_INFO *m_VideoLostInfo;	
	CFG_VIDEO_COVER m_VideoCoveInfo;
	CFG_COMMGROUP_INFO m_CommGroupInfo;
//	CFG_PTZ_INFO m_PTZInfo2[32];
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO5DLG_H__71084F64_0DFF_43C2_8AD9_6F5AE7FE9253__INCLUDED_)
