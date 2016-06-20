// ConfigFTP.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigFTP.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigFTP dialog


CConfigFTP::CConfigFTP(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigFTP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigFTP)
	m_bFriAlarm = FALSE;
	m_bFriMd = FALSE;
	m_bFriTimer = FALSE;
	m_bFTP = FALSE;
	m_bMonAlarm = FALSE;
	m_bMonMd = FALSE;
	m_bMonTimer = FALSE;
	m_bSatAlarm = FALSE;
	m_bSatMd = FALSE;
	m_bSatTimer = FALSE;
	m_bSunAlarm = FALSE;
	m_bSunMd = FALSE;
	m_bSunTimer = FALSE;
	m_bThursAlarm = FALSE;
	m_bThursMd = FALSE;
	m_bThursTimer = FALSE;
	m_bTuesAlarm = FALSE;
	m_bTuesMd = FALSE;
	m_bTuesTimer = FALSE;
	m_bWenAlarm = FALSE;
	m_bWenMd = FALSE;
	m_bWenTimer = FALSE;
	
	m_nFileLenth = 0;
	m_nFri_E1_Hour = 0;
	m_nFri_E1_Minute = 0;
	m_nFri_E1_Sec = 0;
	m_nFri_S1_Hour = 0;
	m_nFri_S1_Minute = 0;
	m_nFri_S1_Sec = 0;
	
	m_nMon_E1_Hour = 0;
	m_nMon_E1_Minute = 0;
	m_nMon_E1_Sec = 0;
	m_nMon_S1_Hour = 0;
	m_nMon_S1_Minute = 0;
	m_nMon_S1_Sec = 0;

	m_nSat_E1_Hour = 0;
	m_nSat_E1_Minute = 0;
	m_nSat_E1_Sec = 0;
	m_nSat_S1_Hour = 0;
	m_nSat_S1_Minute = 0;
	m_nSat_S1_Sec = 0;

	m_nSun_E1_Hour = 0;
	m_nSun_E1_Minute = 0;
	m_nSun_E1_Sec = 0;
	m_nSun_S1_Hour = 0;
	m_nSun_S1_Minute = 0;
	m_nSun_S1_Sec = 0;
	m_nThurs_E1_Hour = 0;
	m_nThurs_E1_Minute = 0;
	m_nThurs_E1_Sec = 0;
	m_nThurs_S1_Hour = 0;
	m_nThurs_S1_Minute = 0;
    m_nThurs_S1_Sec = 0;

	m_nTues_E1_Hour = 0;
	m_nTues_E1_Minute = 0;
	m_nTues_E1_Sec = 0;
	m_nTues_S1_Hour = 0;
	m_nTues_S1_Minute = 0;
	m_nTues_S1_Sec = 0;
	m_strName = _T("");
	m_nWen_E1_Hour = 0;
	m_nWen_E1_Minute = 0;
	m_nWen_E1_Sec = 0;
	m_nWen_S1_Hour = 0;
	m_nWen_S1_Minute = 0;
	m_nWen_S1_Sec = 0;
	m_nInernalTime = 0;
	//}}AFX_DATA_INIT
	//memset(&m_stuFtpInfo, 0, sizeof(FTP_PROTO_CFG_EX));
//	memset(&m_stuNasInfoEx, 0, sizeof(CFG_NAS_INFO_EX));
	m_nChannelNum = 0;
	m_nStorageNum = 0;
	m_nCurrentStorageNum = -1;
	m_nCurrentChannel = -1;
	m_nCurrentTimePeriod = -1;
	memset(&m_stuRemoteStorage, 0, sizeof(CFG_REMOTE_STORAGELIMIT_GROUP));
}


void CConfigFTP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigFTP)
	DDX_Control(pDX, IDC_COMBO_TIMEPERIOD, m_cbTimePeriod);
	DDX_Control(pDX, IDC_COMBO_CHANNElNUM, m_cbChannelNum);
	DDX_Control(pDX, IDC_COMBO_STORAGENUM, m_cbStorageNum);
	DDX_Check(pDX, IDC_CHECK_FRI_ALARM, m_bFriAlarm);
	DDX_Check(pDX, IDC_CHECK_FRI_MD, m_bFriMd);
	DDX_Check(pDX, IDC_CHECK_FRI_TIMER, m_bFriTimer);
	//DDX_Check(pDX, IDC_CHECK_FTP, m_bFTP);
	DDX_Check(pDX, IDC_CHECK_MON_ALARM, m_bMonAlarm);
	DDX_Check(pDX, IDC_CHECK_MON_MD, m_bMonMd);
	DDX_Check(pDX, IDC_CHECK_MON_TIMER, m_bMonTimer);
	DDX_Check(pDX, IDC_CHECK_SAT_ALARM, m_bSatAlarm);
	DDX_Check(pDX, IDC_CHECK_SAT_MD, m_bSatMd);
	DDX_Check(pDX, IDC_CHECK_SAT_TIMER, m_bSatTimer);
	DDX_Check(pDX, IDC_CHECK_SUN_ALARM, m_bSunAlarm);
	DDX_Check(pDX, IDC_CHECK_SUN_MD, m_bSunMd);
	DDX_Check(pDX, IDC_CHECK_SUN_TIMER, m_bSunTimer);
	DDX_Check(pDX, IDC_CHECK_THURS_ALARM, m_bThursAlarm);
	DDX_Check(pDX, IDC_CHECK_THURS_MD, m_bThursMd);
	DDX_Check(pDX, IDC_CHECK_THURS_TIMER, m_bThursTimer);
	DDX_Check(pDX, IDC_CHECK_TUES_ALARM, m_bTuesAlarm);
	DDX_Check(pDX, IDC_CHECK_TUES_MD, m_bTuesMd);
	DDX_Check(pDX, IDC_CHECK_TUES_TIMER, m_bTuesTimer);
	DDX_Check(pDX, IDC_CHECK_WEN_ALARM, m_bWenAlarm);
	DDX_Check(pDX, IDC_CHECK_WEN_MD, m_bWenMd);
	DDX_Check(pDX, IDC_CHECK_WEN_TIMER, m_bWenTimer);
	DDX_Text(pDX, IDC_EDIT_FILELENTH, m_nFileLenth);
	DDX_Text(pDX, IDC_EDIT_FRI_E1_HOUR, m_nFri_E1_Hour);
	DDV_MinMaxInt(pDX, m_nFri_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_FRI_E1_MINUTE, m_nFri_E1_Minute);
	DDV_MinMaxInt(pDX, m_nFri_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_FRI_E1_SEC, m_nFri_E1_Sec);
	DDV_MinMaxInt(pDX, m_nFri_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_FRI_S1_HOUR, m_nFri_S1_Hour);
	DDV_MinMaxInt(pDX, m_nFri_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_FRI_S1_MINUTE, m_nFri_S1_Minute);
	DDV_MinMaxInt(pDX, m_nFri_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_FRI_S1_SEC, m_nFri_S1_Sec);
	DDV_MinMaxInt(pDX, m_nFri_S1_Sec, 0, 60);
	
	DDX_Text(pDX, IDC_EDIT_MON_E1_HOUR, m_nMon_E1_Hour);
	DDV_MinMaxInt(pDX, m_nMon_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_MON_E1_MINUTE, m_nMon_E1_Minute);
	DDV_MinMaxInt(pDX, m_nMon_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_MON_E1_SEC, m_nMon_E1_Sec);
	DDV_MinMaxInt(pDX, m_nMon_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_MON_S1_HOUR, m_nMon_S1_Hour);
	DDV_MinMaxInt(pDX, m_nMon_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_MON_S1_MINUTE, m_nMon_S1_Minute);
	DDV_MinMaxInt(pDX, m_nMon_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_MON_S1_SEC, m_nMon_S1_Sec);
	DDV_MinMaxInt(pDX, m_nMon_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SAT_E1_HOUR, m_nSat_E1_Hour);
	DDV_MinMaxInt(pDX, m_nSat_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_SAT_E1_MINUTE, m_nSat_E1_Minute);
	DDV_MinMaxInt(pDX, m_nSat_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SAT_E1_SEC, m_nSat_E1_Sec);
	DDV_MinMaxInt(pDX, m_nSat_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SAT_S1_HOUR2, m_nSat_S1_Hour);
	DDV_MinMaxInt(pDX, m_nSat_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_SAT_S1_MINUTE2, m_nSat_S1_Minute);
	DDV_MinMaxInt(pDX, m_nSat_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SAT_S1_SEC2, m_nSat_S1_Sec);
	DDV_MinMaxInt(pDX, m_nSat_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SUN_E1_HOUR, m_nSun_E1_Hour);
	DDV_MinMaxInt(pDX, m_nSun_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_SUN_E1_MINUTE, m_nSun_E1_Minute);
	DDV_MinMaxInt(pDX, m_nSun_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SUN_E1_SEC, m_nSun_E1_Sec);
	DDV_MinMaxInt(pDX, m_nSun_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SUN_S1_HOUR, m_nSun_S1_Hour);
	DDV_MinMaxInt(pDX, m_nSun_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_SUN_S1_MINUTE, m_nSun_S1_Minute);
	DDV_MinMaxInt(pDX, m_nSun_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SUN_S1_SEC, m_nSun_S1_Sec);
	DDV_MinMaxInt(pDX, m_nSun_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_THURS_E1_HOUR, m_nThurs_E1_Hour);
	DDV_MinMaxInt(pDX, m_nThurs_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_THURS_E1_MINUTE, m_nThurs_E1_Minute);
	DDV_MinMaxInt(pDX, m_nThurs_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_THURS_E1_SEC, m_nThurs_E1_Sec);
	DDV_MinMaxInt(pDX, m_nThurs_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_THURS_S1_HOUR, m_nThurs_S1_Hour);
	DDV_MinMaxInt(pDX, m_nThurs_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_THURS_S1_MINUTE2, m_nThurs_S1_Minute);
	DDV_MinMaxInt(pDX, m_nThurs_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_THURS_S1_SEC2, m_nThurs_S1_Sec);
	DDV_MinMaxInt(pDX, m_nThurs_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_TUES_E1_HOUR, m_nTues_E1_Hour);
	DDV_MinMaxInt(pDX, m_nTues_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_TUES_E1_MINUTE, m_nTues_E1_Minute);
	DDV_MinMaxInt(pDX, m_nTues_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_TUES_E1_SEC, m_nTues_E1_Sec);
	DDX_Text(pDX, IDC_EDIT_TUES_S1_HOUR, m_nTues_S1_Hour);
	DDV_MinMaxInt(pDX, m_nTues_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_TUES_S1_MINUTE, m_nTues_S1_Minute);
	DDV_MinMaxInt(pDX, m_nTues_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_TUES_S1_SEC, m_nTues_S1_Sec);
	DDV_MinMaxInt(pDX, m_nTues_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 128);
	DDX_Text(pDX, IDC_EDIT_WEN_E1_HOUR, m_nWen_E1_Hour);
	DDV_MinMaxInt(pDX, m_nWen_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_WEN_E1_MINUTE, m_nWen_E1_Minute);
	DDV_MinMaxInt(pDX, m_nWen_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_WEN_E1_SEC, m_nWen_E1_Sec);
	DDV_MinMaxInt(pDX, m_nWen_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_WEN_S1_HOUR, m_nWen_S1_Hour);
	DDV_MinMaxInt(pDX, m_nWen_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_WEN_S1_MINUTE, m_nWen_S1_Minute);
	DDV_MinMaxInt(pDX, m_nWen_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_WEN_S1_SEC, m_nWen_S1_Sec);
	DDV_MinMaxInt(pDX, m_nWen_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_INTERNALTIME, m_nInernalTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigFTP, CDialog)
	//{{AFX_MSG_MAP(CConfigFTP)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FTP, OnButtonSaveFtp)
	ON_BN_CLICKED(IDC_BUTTON_READ_FTP, OnButtonReadFtp)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNElNUM, OnSelchangeCOMBOCHANNElNUM)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMEPERIOD, OnSelchangeComboTimeperiod)
	ON_CBN_SELCHANGE(IDC_COMBO_STORAGENUM, OnSelchangeComboStoragenum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigFTP message handlers
BOOL CConfigFTP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	return TRUE;
}

void CConfigFTP::InitFtpInfo()
{
	int i = 0;
	for (i=0; i<MAX_NAS_LIMIT; i++)
	{
        if (NULL != m_stuRemoteStorage.stuRemoteStorageLimit[i].pstuChnTime)
		{
			delete[] m_stuRemoteStorage.stuRemoteStorageLimit[i].pstuChnTime;
		}
	}
    memset(&m_stuRemoteStorage, 0, sizeof(CFG_REMOTE_STORAGELIMIT_GROUP));
	for (i=0; i<MAX_NAS_LIMIT; i++)
	{
        m_stuRemoteStorage.stuRemoteStorageLimit[i].pstuChnTime = new CFG_CHANNEL_TIME_SECTION[CHANNEL_NUM_LIMIT];
		memset(m_stuRemoteStorage.stuRemoteStorageLimit[i].pstuChnTime, 0, CHANNEL_NUM_LIMIT * sizeof(CFG_CHANNEL_TIME_SECTION));
        m_stuRemoteStorage.stuRemoteStorageLimit[i].nMaxChnCount = CHANNEL_NUM_LIMIT;
	}
	int nIndex = 0;
	char szBuf[20] = {0};
	CString strTimePeriod = "TimePeriod";

	m_cbTimePeriod.ResetContent();
	for(i = 0; i < DH_TIME_SECTION; i++)
	{
		nIndex = m_cbTimePeriod.AddString(ConvertString(strTimePeriod) + itoa(i+1, szBuf, 10));
		m_cbTimePeriod.SetItemData(nIndex, i);
	}
	m_cbTimePeriod.SetCurSel(0);
	m_nCurrentTimePeriod = 0;
	OnButtonReadFtp();

}

bool CConfigFTP::IsWeekDataValid()
{
	UpdateData(TRUE);
	
	ValidWeekData2(Mon);
	ValidWeekData2(Tues);
	ValidWeekData2(Thurs);
	ValidWeekData2(Wen);
	ValidWeekData2(Fri);
	ValidWeekData2(Sat);
	ValidWeekData2(Sun);
	
	return true;
}

// set configuration information
void CConfigFTP::OnButtonSaveFtp() 
{
	bool bRet = IsWeekDataValid();
	if (!bRet)
	{
		MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
		return;
	}

	// get ftp configuration information current info from the dialog
	SaveConfigInfo();
	
	// set ftp configuration information to device
	((CClientDemo5Dlg*)AfxGetMainWnd())->SetRemoteStorageLimit(&m_stuRemoteStorage);
}

// get configuration information
void CConfigFTP::OnButtonReadFtp() 
{
	// clean the exit info in the dialog 
	CleanAll();	
	int i;
	for (i=0; i<MAX_NAS_LIMIT; i++)
	{
        m_stuRemoteStorage.stuRemoteStorageLimit[i].pstuChnTime = new CFG_CHANNEL_TIME_SECTION[CHANNEL_NUM_LIMIT];
		memset(m_stuRemoteStorage.stuRemoteStorageLimit[i].pstuChnTime, 0, CHANNEL_NUM_LIMIT * sizeof(CFG_CHANNEL_TIME_SECTION));
        m_stuRemoteStorage.stuRemoteStorageLimit[i].nMaxChnCount = CHANNEL_NUM_LIMIT;
	}
	// get ftp configuration information from device
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetRemoteStorageLimit(&m_stuRemoteStorage,0);

	// 实际通道数填充m_cbChannelNum
	int nIndex = 0;
	char szBuf[20] = {0};
	CString strChannel = "channel";
	m_nChannelNum = __min(m_stuRemoteStorage.stuRemoteStorageLimit[0].nRetChnCount, CHANNEL_NUM_LIMIT);
	m_cbChannelNum.ResetContent();
	for(i= 0; i < m_nChannelNum; i++)
	{
		nIndex = m_cbChannelNum.AddString(ConvertString(strChannel) + itoa(i+1, szBuf, 10));
		m_cbChannelNum.SetItemData(nIndex, i);
	}
	m_cbChannelNum.SetCurSel(0);
	m_nCurrentChannel = 0;

	// 根据实际服务器数填充m_cbStorageNum
	memset(szBuf,0,20);
	CString strServer = "Server";
	m_cbStorageNum.ResetContent();
    m_nStorageNum = __min(m_stuRemoteStorage.nLimitCount, MAX_NAS_NUM);
	for(i = 0; i < m_nStorageNum; i++)
	{
		nIndex = m_cbStorageNum.AddString(ConvertString(strServer) + itoa(i+1, szBuf, 10));
		m_cbStorageNum.SetItemData(nIndex, i);
	}
	m_cbStorageNum.SetCurSel(0);
	m_nCurrentStorageNum = 0;

	ShowConfigInfo();
}

// clean the exit info in the dialog 
void CConfigFTP::CleanAll(void)
{
	m_bFriAlarm = FALSE;
	m_bFriMd = FALSE;
	m_bFriTimer = FALSE;
	m_bFTP = FALSE;
	m_bMonAlarm = FALSE;
	m_bMonMd = FALSE;
	m_bMonTimer = FALSE;
	m_bSatAlarm = FALSE;
	m_bSatMd = FALSE;
	m_bSatTimer = FALSE;
	m_bSunAlarm = FALSE;
	m_bSunMd = FALSE;
	m_bSunTimer = FALSE;
	m_bThursAlarm = FALSE;
	m_bThursMd = FALSE;
	m_bThursTimer = FALSE;
	m_bTuesAlarm = FALSE;
	m_bTuesMd = FALSE;
	m_bTuesTimer = FALSE;
	m_bWenAlarm = FALSE;
	m_bWenMd = FALSE;
	m_bWenTimer = FALSE;

	UpdateData(FALSE);

	//SetDlgItemText(IDC_EDIT_DIRNAME, "");
	SetDlgItemText(IDC_EDIT_FILELENTH, "");
	SetDlgItemText(IDC_EDIT_FRI_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_FRI_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_FRI_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_FRI_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_FRI_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_FRI_S1_SEC, "");
	//SetDlgItemText(IDC_EDIT_MAXPICNUM, "");
	SetDlgItemText(IDC_EDIT_MON_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_MON_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_MON_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_MON_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_MON_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_MON_S1_SEC, "");
	//SetDlgItemText(IDC_EDIT_PASSWORD, "");
	//SetDlgItemText(IDC_EDIT_PICNAMERULE, "");
	//SetDlgItemText(IDC_EDIT_PORT, "");
	SetDlgItemText(IDC_EDIT_SAT_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_SAT_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_SAT_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_SAT_S1_HOUR2, "");
	SetDlgItemText(IDC_EDIT_SAT_S1_MINUTE2, "");
	SetDlgItemText(IDC_EDIT_SAT_S1_SEC2, "");
	//SetDlgItemText(IDC_EDIT_SERVERIP, "");
	//SetDlgItemText(IDC_EDIT_SUBDIRNAME, "");
	SetDlgItemText(IDC_EDIT_SUN_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_SUN_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_SUN_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_SUN_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_SUN_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_SUN_S1_SEC, "");
	SetDlgItemText(IDC_EDIT_THURS_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_THURS_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_THURS_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_THURS_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_THURS_S1_MINUTE2, "");
	SetDlgItemText(IDC_EDIT_THURS_S1_SEC2, "");
	SetDlgItemText(IDC_EDIT_TUES_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_TUES_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_TUES_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_TUES_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_TUES_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_TUES_S1_SEC, "");
	SetDlgItemText(IDC_EDIT_NAME, "");
	SetDlgItemText(IDC_EDIT_WEN_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_WEN_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_WEN_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_WEN_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_WEN_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_WEN_S1_SEC, "");

	for (int i=0; i<MAX_NAS_LIMIT; i++)
	{
        if (NULL != m_stuRemoteStorage.stuRemoteStorageLimit[i].pstuChnTime)
		{
			delete[] m_stuRemoteStorage.stuRemoteStorageLimit[i].pstuChnTime;
		}
	}
    memset(&m_stuRemoteStorage, 0, sizeof(CFG_REMOTE_STORAGELIMIT_GROUP));
}

void CConfigFTP::ShowConfigInfo(void)
{
    if (0 > m_nCurrentStorageNum || m_nStorageNum <= m_nCurrentStorageNum
		|| 0 > m_nCurrentChannel || m_nChannelNum <= m_nCurrentChannel
		|| 0 > m_nCurrentTimePeriod || DH_TIME_SECTION <= m_nCurrentTimePeriod)
    {
		return;
    }
    CFG_REMOTE_STORAGE_LIMIT& stEachStorage = m_stuRemoteStorage.stuRemoteStorageLimit[m_nCurrentStorageNum];
    m_nFileLenth = stEachStorage.nFileLen;
	m_nInernalTime = stEachStorage.nInterval;
	
	char szBuf[MAX_NAME_LEN + 1] = {0};
	memcpy(szBuf, stEachStorage.szName, MAX_NAME_LEN);
	m_strName = szBuf;
	if (NULL == stEachStorage.pstuChnTime)
	{
		return;
	}
    CFG_TIME_SECTION& stSunSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[0][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stMonSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[1][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stTuesSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[2][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stWenSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[3][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stThursSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[4][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stFriSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[5][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stSatSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[6][m_nCurrentTimePeriod];

	m_bSunAlarm = (stSunSection.dwRecordMask & 0x02) ? TRUE : FALSE;
	m_bSunMd = (stSunSection.dwRecordMask & 0x01) ? TRUE : FALSE;
	m_bSunTimer = (stSunSection.dwRecordMask & 0x04) ? TRUE : FALSE;
	m_nSun_S1_Hour = stSunSection.nBeginHour;
	m_nSun_S1_Minute = stSunSection.nBeginMin;
	m_nSun_S1_Sec = stSunSection.nBeginSec;
	m_nSun_E1_Hour = stSunSection.nEndHour;
	m_nSun_E1_Minute = stSunSection.nEndMin;
	m_nSun_E1_Sec = stSunSection.nEndSec;

	m_bMonAlarm = (stMonSection.dwRecordMask & 0x02) ? TRUE : FALSE;
	m_bMonMd = (stMonSection.dwRecordMask & 0x01) ? TRUE : FALSE;
	m_bMonTimer = (stMonSection.dwRecordMask & 0x04) ? TRUE : FALSE;
	m_nMon_S1_Hour = stMonSection.nBeginHour;
	m_nMon_S1_Minute = stMonSection.nBeginMin;
	m_nMon_S1_Sec = stMonSection.nBeginSec;
	m_nMon_E1_Hour = stMonSection.nEndHour;
	m_nMon_E1_Minute = stMonSection.nEndMin;
	m_nMon_E1_Sec = stMonSection.nEndSec;
	
	m_bTuesAlarm = (stTuesSection.dwRecordMask & 0x02) ? TRUE : FALSE;
	m_bTuesMd = (stTuesSection.dwRecordMask & 0x01) ? TRUE : FALSE;
	m_bTuesTimer = (stTuesSection.dwRecordMask & 0x04) ? TRUE : FALSE;
	m_nTues_S1_Hour = stTuesSection.nBeginHour;
	m_nTues_S1_Minute = stTuesSection.nBeginMin;
	m_nTues_S1_Sec = stTuesSection.nBeginSec;
	m_nTues_E1_Hour = stTuesSection.nEndHour;
	m_nTues_E1_Minute = stTuesSection.nEndMin;
	m_nTues_E1_Sec = stTuesSection.nEndSec;
	
	m_bWenAlarm = (stWenSection.dwRecordMask & 0x02) ? TRUE : FALSE;
	m_bWenMd = (stWenSection.dwRecordMask & 0x01) ? TRUE : FALSE;
	m_bWenTimer = (stWenSection.dwRecordMask & 0x04) ? TRUE : FALSE;
	m_nWen_S1_Hour = stWenSection.nBeginHour;
	m_nWen_S1_Minute = stWenSection.nBeginMin;
	m_nWen_S1_Sec = stWenSection.nBeginSec;
	m_nWen_E1_Hour = stWenSection.nEndHour;
	m_nWen_E1_Minute = stWenSection.nEndMin;
	m_nWen_E1_Sec = stWenSection.nEndSec;
	
	m_bThursAlarm = (stThursSection.dwRecordMask & 0x02) ? TRUE : FALSE;
	m_bThursMd	= (stThursSection.dwRecordMask & 0x01) ? TRUE : FALSE;
	m_bThursTimer = (stThursSection.dwRecordMask & 0x04) ? TRUE : FALSE;
	m_nThurs_S1_Hour = stThursSection.nBeginHour;
	m_nThurs_S1_Minute = stThursSection.nBeginMin;
	m_nThurs_S1_Sec = stThursSection.nBeginSec;
	m_nThurs_E1_Hour = stThursSection.nEndHour;
	m_nThurs_E1_Minute = stThursSection.nEndMin;
	m_nThurs_E1_Sec = stThursSection.nEndSec;
	
	m_bFriAlarm = (stFriSection.dwRecordMask & 0x02) ? TRUE : FALSE;
	m_bFriMd = (stFriSection.dwRecordMask & 0x01) ? TRUE : FALSE;
	m_bFriTimer = (stFriSection.dwRecordMask & 0x04) ? TRUE : FALSE;
	m_nFri_S1_Hour = stFriSection.nBeginHour;
	m_nFri_S1_Minute = stFriSection.nBeginMin;
	m_nFri_S1_Sec = stFriSection.nBeginSec;
	m_nFri_E1_Hour = stFriSection.nEndHour;
	m_nFri_E1_Minute = stFriSection.nEndMin;
	m_nFri_E1_Sec = stFriSection.nEndSec;
	
	m_bSatAlarm = (stSatSection.dwRecordMask & 0x02) ? TRUE : FALSE;
	m_bSatMd = (stSatSection.dwRecordMask & 0x01) ? TRUE : FALSE;
	m_bSatTimer = (stSatSection.dwRecordMask & 0x04) ? TRUE : FALSE;
	m_nSat_S1_Hour = stSatSection.nBeginHour;
	m_nSat_S1_Minute = stSatSection.nBeginMin;
	m_nSat_S1_Sec = stSatSection.nBeginSec;
	m_nSat_E1_Hour = stSatSection.nEndHour;
	m_nSat_E1_Minute = stSatSection.nEndMin;
	m_nSat_E1_Sec = stSatSection.nEndSec;
	
	UpdateData(FALSE);
}

void CConfigFTP::SaveConfigInfo(void)
{
    if (0 > m_nCurrentStorageNum || m_nStorageNum <= m_nCurrentStorageNum
		|| 0 > m_nCurrentChannel || m_nChannelNum <= m_nCurrentChannel
		|| 0 > m_nCurrentTimePeriod || DH_TIME_SECTION <= m_nCurrentTimePeriod)
    {
		return;
    }
	UpdateData(TRUE);

    CFG_REMOTE_STORAGE_LIMIT& stEachStorage = m_stuRemoteStorage.stuRemoteStorageLimit[m_nCurrentStorageNum];
    stEachStorage.nFileLen = m_nFileLenth;
	stEachStorage.nInterval = m_nInernalTime;
	memset(stEachStorage.szName, 0, MAX_NAME_LEN);
	memcpy(stEachStorage.szName, m_strName, m_strName.GetLength());
	if (NULL == stEachStorage.pstuChnTime)
	{
		return;
	}
    CFG_TIME_SECTION& stSunSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[0][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stMonSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[1][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stTuesSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[2][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stWenSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[3][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stThursSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[4][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stFriSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[5][m_nCurrentTimePeriod];
    CFG_TIME_SECTION& stSatSection = stEachStorage.pstuChnTime[m_nCurrentChannel].stuTimeSection[6][m_nCurrentTimePeriod];

	stSunSection.dwRecordMask = (m_bSunTimer << 2)| (m_bSunAlarm << 1) | m_bSunMd;
	stSunSection.nBeginHour = m_nSun_S1_Hour;
	stSunSection.nBeginMin = m_nSun_S1_Minute;
	stSunSection.nBeginSec = m_nSun_S1_Sec;
	stSunSection.nEndHour = m_nSun_E1_Hour;
	stSunSection.nEndMin = m_nSun_E1_Minute;
	stSunSection.nEndSec = m_nSun_E1_Sec;
	
	stMonSection.dwRecordMask = (m_bMonTimer << 2)| (m_bMonAlarm << 1) | m_bMonMd;
	stMonSection.nBeginHour = m_nMon_S1_Hour;
	stMonSection.nBeginMin = m_nMon_S1_Minute;
	stMonSection.nBeginSec = m_nMon_S1_Sec;
	stMonSection.nEndHour = m_nMon_E1_Hour;
	stMonSection.nEndMin = m_nMon_E1_Minute;
	stMonSection.nEndSec = m_nMon_E1_Sec;

	stTuesSection.dwRecordMask = (m_bTuesTimer << 2)| (m_bTuesAlarm << 1) | m_bTuesMd;
	stTuesSection.nBeginHour = m_nTues_S1_Hour;
	stTuesSection.nBeginMin = m_nTues_S1_Minute;
	stTuesSection.nBeginSec = m_nTues_S1_Sec;
	stTuesSection.nEndHour = m_nTues_E1_Hour;
	stTuesSection.nEndMin = m_nTues_E1_Minute;
	stTuesSection.nEndSec = m_nTues_E1_Sec;
	
	stWenSection.dwRecordMask = (m_bWenTimer << 2)| (m_bWenAlarm << 1) | m_bWenMd;
	stWenSection.nBeginHour = m_nWen_S1_Hour;
	stWenSection.nBeginMin = m_nWen_S1_Minute;
	stWenSection.nBeginSec = m_nWen_S1_Sec;
	stWenSection.nEndHour = m_nWen_E1_Hour;
	stWenSection.nEndMin = m_nWen_E1_Minute;
	stWenSection.nEndSec = m_nWen_E1_Sec;
	
	stThursSection.dwRecordMask = (m_bThursTimer << 2)| (m_bThursAlarm << 1) | m_bThursMd;
	stThursSection.nBeginHour = m_nThurs_S1_Hour;
	stThursSection.nBeginMin = m_nThurs_S1_Minute;
	stThursSection.nBeginSec = m_nThurs_S1_Sec;
	stThursSection.nEndHour = m_nThurs_E1_Hour;
	stThursSection.nEndMin = m_nThurs_E1_Minute;
	stThursSection.nEndSec = m_nThurs_E1_Sec;

	stFriSection.dwRecordMask = (m_bFriTimer << 2)| (m_bFriAlarm << 1) | m_bFriMd;
	stFriSection.nBeginHour = m_nFri_S1_Hour;
	stFriSection.nBeginMin = m_nFri_S1_Minute;
	stFriSection.nBeginSec = m_nFri_S1_Sec;
	stFriSection.nEndHour = m_nFri_E1_Hour;
	stFriSection.nEndMin = m_nFri_E1_Minute;
	stFriSection.nEndSec = m_nFri_E1_Sec;

	stSatSection.dwRecordMask = (m_bSatTimer << 2)| (m_bSatAlarm << 1) | m_bSatMd;
	stSatSection.nBeginHour = m_nSat_S1_Hour;
	stSatSection.nBeginMin = m_nSat_S1_Minute;
	stSatSection.nBeginSec = m_nSat_S1_Sec;
	stSatSection.nEndHour = m_nSat_E1_Hour;
	stSatSection.nEndMin = m_nSat_E1_Minute;
	stSatSection.nEndSec = m_nSat_E1_Sec;

}

void CConfigFTP::OnSelchangeCOMBOCHANNElNUM() 
{
	int nIndex = m_cbChannelNum.GetCurSel();
	if (CB_ERR == nIndex)
	{
		return;
	}
	int nChannel = m_cbChannelNum.GetItemData(nIndex);
	if (0 > nChannel || nChannel >= m_nChannelNum)
	{
		return;
	}
	//save pre info	
	SaveConfigInfo();
	m_nCurrentChannel = nChannel;
    ShowConfigInfo();
	UpdateData(FALSE);
}

void CConfigFTP::OnSelchangeComboTimeperiod() 
{
	int nIndex = m_cbTimePeriod.GetCurSel();
	if (CB_ERR == nIndex)
	{
		return;
	}
	int nTimePeriod = m_cbTimePeriod.GetItemData(nIndex);
	if (0 > nTimePeriod || nTimePeriod >= DH_TIME_SECTION)
	{
		return;
	}
	// save preinfo
    SaveConfigInfo();
    m_nCurrentTimePeriod = nTimePeriod;
	ShowConfigInfo();
	UpdateData(FALSE);
}

void CConfigFTP::OnSelchangeComboStoragenum() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_cbStorageNum.GetCurSel();
	if (CB_ERR == nIndex)
	{
		return;
	}
	int nStorageNum = m_cbStorageNum.GetItemData(nIndex);
	if (0 > nStorageNum || nStorageNum >= m_nStorageNum)
	{
		return;
	}
	// 未切换服务器，直接返回
    if (m_nCurrentStorageNum == nStorageNum)
    {
		return;
    }
	// 根据实际通道数填充m_cbChannelNum
	char szBuf[20] = {0};
	CString strChannel = "channel";
	m_nChannelNum = __min(m_stuRemoteStorage.stuRemoteStorageLimit[nStorageNum].nRetChnCount, CHANNEL_NUM_LIMIT);
	m_cbChannelNum.ResetContent();
	for(int i= 0; i < m_nChannelNum; i++)
	{
		nIndex = m_cbChannelNum.AddString(ConvertString(strChannel) + itoa(i+1, szBuf, 10));
		m_cbChannelNum.SetItemData(nIndex, i);
	}
	m_cbChannelNum.SetCurSel(0);
	m_nCurrentChannel = 0;

    SaveConfigInfo();
    m_nStorageNum = nStorageNum;
	ShowConfigInfo();
	UpdateData(FALSE);
}
