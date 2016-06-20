#if !defined(AFX_CONFIGFTP_H__2125E842_D8EE_4499_8210_06B356FB65EC__INCLUDED_)
#define AFX_CONFIGFTP_H__2125E842_D8EE_4499_8210_06B356FB65EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigFTP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigFTP dialog

typedef struct
{
	DWORD				dwSize;
	BOOL				bEnable;							// 是否启用
	char				szHostIp[DH_MAX_IPADDR_LEN];		// 主机IP
	WORD				wHostPort;							// 主机端口
	char				szDirName[DH_FTP_MAX_PATH];			// FTP目录路径
	char				szUserName[DH_FTP_USERNAME_LEN];	// 用户名
	char				szPassword[DH_FTP_PASSWORD_LEN];	// 密码
	int					iFileLen;							// 文件长度
	int					iInterval;							// 相邻文件时间间隔(1~600),单位秒 
	DH_FTP_UPLOAD_CFG	struUploadCfg[32][DH_N_WEEKS];
	char 				protocol;							// 0-FTP 1-SMB 2-NFS，3-ISCSI
	char				NASVer;								// 网络存储服务器版本0=老的FTP(界面上显示时间段)，1=NAS存储(界面上屏蔽时间段)
	DWORD				dwFunctionMask;						// 功能能力掩码，按位表示，低16位(网络存储)依次表示FTP，SMB，NFS，ISCSI, 高16位(本地存储)依次为DISK，U
	BYTE 				reserved[124];
} FTP_PROTO_CFG;

// FTP上传扩展配置(支持通道独立设置FTP存储路径，最大存储图片数等)
typedef struct 
{
    int            nMaxPictures;                             // 总存储张数，每一个通道文件夹中的图片数量可以限制，
	// 超过限制就覆盖老的文件,0:表示不限制，写满为止
    char           szPreChannelName[DH_FTP_MAX_SUB_PATH];    // 图片文件名
    char           szFTPChannelPath[DH_FTP_MAX_SUB_PATH];    // ftp存储路径(存储子目录)
    char           szRev[128];                               // 保留字段
}FTP_CHANNEL_CFG; 


typedef struct 
{ 
	FTP_PROTO_CFG       stuFtpNormalSet;                             // FTP原有功能，扩展通道数
	FTP_CHANNEL_CFG     stuFtpChannelSet[32];           // FTP扩展功能
	char                szRev[128];                                 // 保留字段
}FTP_PROTO_CFG_EX;


class CConfigFTP : public CDialog
{
// Construction
public:
	CConfigFTP(CWnd* pParent = NULL);   // standard constructor
	void InitFtpInfo();
	void CleanAll(void);

// Dialog Data
	//{{AFX_DATA(CConfigFTP)
	enum { IDD = IDD_CONFIG_FTP };
	CComboBox	m_cbTimePeriod;
	CComboBox	m_cbChannelNum;
	CComboBox   m_cbStorageNum;
	BOOL	m_bFriAlarm;
	BOOL	m_bFriMd;
	BOOL	m_bFriTimer;
	BOOL	m_bFTP;
	BOOL	m_bMonAlarm;
	BOOL	m_bMonMd;
	BOOL	m_bMonTimer;
	BOOL	m_bSatAlarm;
	BOOL	m_bSatMd;
	BOOL	m_bSatTimer;
	BOOL	m_bSunAlarm;
	BOOL	m_bSunMd;
	BOOL	m_bSunTimer;
	BOOL	m_bThursAlarm;
	BOOL	m_bThursMd;
	BOOL	m_bThursTimer;
	BOOL	m_bTuesAlarm;
	BOOL	m_bTuesMd;
	BOOL	m_bTuesTimer;
	BOOL	m_bWenAlarm;
	BOOL	m_bWenMd;
	BOOL	m_bWenTimer;
	
	int		m_nFileLenth;
	int		m_nFri_E1_Hour;
	int		m_nFri_E1_Minute;
	int		m_nFri_E1_Sec;
	int		m_nFri_S1_Hour;
	int		m_nFri_S1_Minute;
	int		m_nFri_S1_Sec;
	//int		m_nMaxPicNum;
	int		m_nMon_E1_Hour;
	int		m_nMon_E1_Minute;
	int		m_nMon_E1_Sec;
	int		m_nMon_S1_Hour;
	int		m_nMon_S1_Minute;
	int		m_nMon_S1_Sec;
	
	int		m_nSat_E1_Hour;
	int		m_nSat_E1_Minute;
	int		m_nSat_E1_Sec;
	int		m_nSat_S1_Hour;
	int		m_nSat_S1_Minute;
	int		m_nSat_S1_Sec;
	int		m_nSun_E1_Hour;
	int		m_nSun_E1_Minute;
	int		m_nSun_E1_Sec;
	int		m_nSun_S1_Hour;
	int		m_nSun_S1_Minute;
	int		m_nSun_S1_Sec;
	int		m_nThurs_E1_Hour;
	int		m_nThurs_E1_Minute;
	int		m_nThurs_E1_Sec;
	int		m_nThurs_S1_Hour;
	int		m_nThurs_S1_Minute;
	int		m_nThurs_S1_Sec;
	int		m_nTues_E1_Hour;
	int		m_nTues_E1_Minute;
	int		m_nTues_E1_Sec;
	int		m_nTues_S1_Hour;
	int		m_nTues_S1_Minute;
	int		m_nTues_S1_Sec;
	CString	m_strName;
	int		m_nWen_E1_Hour;
	int		m_nWen_E1_Minute;
	int		m_nWen_E1_Sec;
	int		m_nWen_S1_Hour;
	int		m_nWen_S1_Minute;
	int		m_nWen_S1_Sec;
	int     m_nInernalTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigFTP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigFTP)
	afx_msg void OnButtonSaveFtp();
	afx_msg void OnButtonReadFtp();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOCHANNElNUM();
	afx_msg void OnSelchangeComboTimeperiod();
	afx_msg void OnSelchangeComboStoragenum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	//FTP_PROTO_CFG_EX m_stuFtpInfo; 

	CFG_REMOTE_STORAGELIMIT_GROUP m_stuRemoteStorage;  // 网络存储服务器限制配置
	int m_nChannelNum;           // 视频通道数
	int m_nStorageNum;           // 网络存储服务器数量
	int m_nCurrentStorageNum;    // 当前选中服务器号
	int m_nCurrentChannel;       // 当前选中通道号
	int m_nCurrentTimePeriod;    // 当期选中时间段
	
//	CFG_NAS_INFO_EX m_stuNasInfoEx;

	void ShowConfigInfo(void);
	void SaveConfigInfo(void);

	bool IsWeekDataValid();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGFTP_H__2125E842_D8EE_4499_8210_06B356FB65EC__INCLUDED_)
