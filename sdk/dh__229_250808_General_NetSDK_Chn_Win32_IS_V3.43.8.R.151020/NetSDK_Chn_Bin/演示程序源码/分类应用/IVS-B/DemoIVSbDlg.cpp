// DemoIVSbDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSb.h"
#include "DemoIVSbDlg.h"

#include "Login.h"
#include "Logo.h"
#include "Switch.h"
#include "Preview.h"
#include "Config.h"
#include "Alarm.h"

#include "IvsGlobalPreview.h"
#include "IvsModulePreview.h"
#include "IvsRulePreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//Forbid opening two programs at the same time 
#pragma data_seg("sharesec")
__declspec (allocate("sharesec")) HWND g_share_hWnd = NULL;
#pragma comment(linker,"/SECTION:sharesec,RWS")

/*
 *	
 */
int  CDemoIVSbDlg::RealLoadPicCallback (LLONG lAnalyzerHandle,	//CLIENT_RealLoadPicEx的返回值
									    DWORD dwAlarmType,		//报警的事件类型
										void* pAlarmInfo,		//根据dwAlarmType不同填充不同结构体信息
										BYTE *pBuffer,			//图片信息
										DWORD dwBufSize,		//图片大小
										LDWORD dwUser,			//
										int nSequence,			//
										void *userdata)			//
{
	int nLen = g_getStructInfo(dwAlarmType);
	if (!nLen)
	{
		return -1;
	}

	//如果在回调线程中处理UI上的元素，会导致UI中消息的产生，
	//这个时候如果去操作UI,去调用Client_stop等，可能会导致死锁
	EventPara* eventData = new EventPara;
	if (!eventData)
	{
		return -1;
	}

	eventData->lAnalyzerHandle = lAnalyzerHandle;
	eventData->dwAlarmType = dwAlarmType;
	eventData->dwBufSize = dwBufSize;
	eventData->nSequence = nSequence;
	
	eventData->pBuffer = new BYTE[dwBufSize];
	if (eventData->pBuffer)
	{
		memcpy(eventData->pBuffer, pBuffer, dwBufSize);
	}
	
	eventData->pAlarmInfo = new char[nLen];
	if (eventData->pAlarmInfo)
	{
		memcpy(eventData->pAlarmInfo, pAlarmInfo, nLen);
	}
	
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)dwUser;//AfxGetMainWnd();
	::PostMessage(pMainDlg->m_pdlgAlarm->GetSafeHwnd(), WM_USER_ALAMR_COME, (DWORD)(eventData), 0);

	//////////////////////////////////////////////////////////////////////////
	//
	IVS_CFG_ANALYSEVENTS_INFOEX ivsInfoEx = {0};
	ivsInfoEx.nEventsNum = 1;

	DEV_EVENT_CROSSFENCEDETECTION_INFO* pCrossFence = NULL;
	DEV_EVENT_CROSSLINE_INFO* pCrossLine = NULL;
	DEV_EVENT_CROSSREGION_INFO* pCrossRegion = NULL;
	DEV_EVENT_MOVE_INFO* pMove = NULL;
	DEV_EVENT_LEFT_INFO* pLeft = NULL;
	DEV_EVENT_PARKINGDETECTION_INFO* pParking = NULL;
	DEV_EVENT_PRESERVATION_INFO* pPreservation = NULL;
	DEV_EVENT_RETROGRADEDETECTION_INFO* pRetro = NULL;
	DEV_EVENT_STAY_INFO* pStay = NULL;
	DEV_EVENT_TAKENAWAYDETECTION_INFO* pTakenAway = NULL;
	DEV_EVENT_VIDEOABNORMALDETECTION_INFO* pVideoAbnormal = NULL;
	DEV_EVENT_WANDER_INFO* pWander = NULL;

	switch (dwAlarmType)
	{
		//1CrossFence
	case EVENT_IVS_CROSSFENCEDETECTION:
		pCrossFence = (DEV_EVENT_CROSSFENCEDETECTION_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pCrossFence->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName, 
				pCrossFence->szName,
				(sizeof(pCrossFence->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
					? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pCrossFence->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = 1;
		memcpy(&ivsInfoEx.stuEventInfo[0].stuObject[0],
			   &pCrossFence->stuObject,
			   sizeof(pCrossFence->stuObject));
		break;
		//2CrossLine
	case EVENT_IVS_CROSSLINEDETECTION:
		pCrossLine = (DEV_EVENT_CROSSLINE_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pCrossLine->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pCrossLine->szName,
				(sizeof(pCrossLine->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
					? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pCrossLine->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = 1;
		memcpy(&ivsInfoEx.stuEventInfo[0].stuObject[0],
			   &pCrossLine->stuObject,
			   sizeof(pCrossLine->stuObject));
		break;
		//3CrossRegion
	case EVENT_IVS_CROSSREGIONDETECTION:
		pCrossRegion = (DEV_EVENT_CROSSREGION_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pCrossRegion->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pCrossRegion->szName,
				(sizeof(pCrossRegion->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
					? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pCrossRegion->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = pCrossRegion->nObjectNum;
		memcpy(ivsInfoEx.stuEventInfo[0].stuObject,
			   pCrossRegion->stuObjectIDs,
			   16 * sizeof(DH_MSG_OBJECT));
		break;
		//4Move
	case EVENT_IVS_MOVEDETECTION:
		pMove = (DEV_EVENT_MOVE_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pMove->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pMove->szName,
				(sizeof(pMove->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
					? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pMove->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = 1;
		memcpy(ivsInfoEx.stuEventInfo[0].stuObject,
			   &pMove->stuObject,
			   sizeof(pMove->stuObject));
		break;
		//5Left
	case EVENT_IVS_LEFTDETECTION:
		pLeft = (DEV_EVENT_LEFT_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pLeft->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pLeft->szName,
				(sizeof(pLeft->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
				? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pLeft->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = 1;
		memcpy(ivsInfoEx.stuEventInfo[0].stuObject,
			   &pLeft->stuObject,
			   sizeof(pLeft->stuObject));
		break;
		//6Parking
	case EVENT_IVS_PARKINGDETECTION:
		pParking = (DEV_EVENT_PARKINGDETECTION_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pParking->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pParking->szName,
				(sizeof(pParking->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
				? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pParking->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = 1;
		memcpy(ivsInfoEx.stuEventInfo[0].stuObject,
			   &pParking->stuObject,
			   sizeof(pParking->stuObject));
		break;
		//7Preservation
	case EVENT_IVS_PRESERVATION:
		pPreservation = (DEV_EVENT_PRESERVATION_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pPreservation->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pPreservation->szName,
				(sizeof(pPreservation->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
				? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pPreservation->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = 1;
		memcpy(ivsInfoEx.stuEventInfo[0].stuObject,
			   &pPreservation->stuObject,
			   sizeof(pPreservation->stuObject));
		break;
		//8Retro
	case EVENT_IVS_RETROGRADEDETECTION:
		pRetro = (DEV_EVENT_RETROGRADEDETECTION_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pRetro->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pRetro->szName,
				(sizeof(pRetro->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
				? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pRetro->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = 1;
		memcpy(ivsInfoEx.stuEventInfo[0].stuObject,
			   &pRetro->stuObject,
			   sizeof(pRetro->stuObject));
		break;
		//9Stay
	case EVENT_IVS_STAYDETECTION:
		pStay = (DEV_EVENT_STAY_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pStay->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pStay->szName,
				(sizeof(pStay->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
				? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pStay->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = 1;
		memcpy(ivsInfoEx.stuEventInfo[0].stuObject,
			   &pStay->stuObject,
			   sizeof(pStay->stuObject));
		break;
		//10TakenAway
	case EVENT_IVS_TAKENAWAYDETECTION:
		pTakenAway = (DEV_EVENT_TAKENAWAYDETECTION_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pTakenAway->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pTakenAway->szName,
				(sizeof(pTakenAway->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
				? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pTakenAway->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = 1;
		memcpy(ivsInfoEx.stuEventInfo[0].stuObject,
			   &pTakenAway->stuObject,
			   sizeof(pTakenAway->stuObject));
		break;
		//11VideoAbnormal
	case EVENT_IVS_VIDEOABNORMALDETECTION:
		pVideoAbnormal = (DEV_EVENT_VIDEOABNORMALDETECTION_INFO*)pAlarmInfo;
		break;
		//12Wander
	case EVENT_IVS_WANDERDETECTION:
		pWander = (DEV_EVENT_WANDER_INFO*)pAlarmInfo;
		ivsInfoEx.stuEventInfo[0].alarmAction = pWander->bEventAction;
		ivsInfoEx.stuEventInfo[0].alarmType = dwAlarmType;
		strncpy(ivsInfoEx.stuEventInfo[0].szRuleName,
				pWander->szName,
				(sizeof(pWander->szName) >= sizeof(ivsInfoEx.stuEventInfo[0].szRuleName)
				? sizeof(ivsInfoEx.stuEventInfo[0].szRuleName) : sizeof(pWander->szName)));
		ivsInfoEx.stuEventInfo[0].nObjectNum = pWander->nObjectNum;
		memcpy(ivsInfoEx.stuEventInfo[0].stuObject,
			   pWander->stuObjectIDs,
			   16 * sizeof(DH_MSG_OBJECT));

		break;
	default:
		return 0;
		break;
	}

	int iErr = DRAW_InputAlarmDataEx(g_nPreviewDrawPort, 0, (unsigned char*)&ivsInfoEx, sizeof(ivsInfoEx));

	return 0;
}
//////////////////////////////////////////////////////////////////////////
//function:
//describ: Get device info, initialize gui info
//param: nChnCount，Device's Totle Channe Count；
//return: 
//////////////////////////////////////////////////////////////////////////
LRESULT CDemoIVSbDlg::OnClearAlarmInfo(WPARAM wParam, LPARAM lParam)
{
	while (m_lstAlarmInfo.size())
	{
		AlarmInfoNode* pNode = m_lstAlarmInfo.front();
		if (pNode)
		{
			delete pNode;
			pNode = NULL;
		}
		m_lstAlarmInfo.pop_front();
	}

	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoIVSbDlg dialog

CDemoIVSbDlg::CDemoIVSbDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoIVSbDlg::IDD, pParent),
	m_currentDlg(dlgNone),
	m_nCurrentChn(-1),
	m_bIsSwitchOn(FALSE),
	m_pdlgPreview(NULL),
	m_pdlgConfig(NULL),
	m_pdlgAlarm(NULL),
	m_pdlgLogo(NULL),
	m_lLoginHandle(0),
	m_lRealPlayHandle(0),
	m_lAnalyzerHandle(0),
	m_nChnCount(0),
	m_pStuCfgCapAnalyseInfo(NULL),
	m_pStuCfgAnalyseGlobalInfo(NULL),
	m_pStuCfgAnalyseModuleInfo(NULL),
	m_pStuCfgAnalyseRuleInfo(NULL)
{
	//{{AFX_DATA_INIT(CDemoIVSbDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ZeroMemory(&m_stuDeviceInfo, sizeof(m_stuDeviceInfo));
}

void CDemoIVSbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoIVSbDlg)
	DDX_Control(pDX, IDC_MAIN_CHK_SWITCH, m_chkSwitch);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoIVSbDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoIVSbDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MAIN_BTN_PREVIEW, OnBtnPreview)
	ON_BN_CLICKED(IDC_MAIN_BTN_CONFIG, OnBtnConfig)
	ON_BN_CLICKED(IDC_MAIN_BTN_ALARM, OnBtnAlarm)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MAIN_CHK_SWITCH, OnMainChkSwitch)
	ON_BN_CLICKED(IDC_MAIN_BTN_LOGOUT, OnMainBtnLogout)
	ON_MESSAGE(WM_CLEARINFO, OnClearAlarmInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
//

/*
 *	获取能力分析集
 */
BOOL CDemoIVSbDlg::getCap(int nChannel, CFG_CAP_ANALYSE_INFO* pCfgCapAnalyseInfo)
{
	if (nChannel < 0 || !pCfgCapAnalyseInfo)
	{
		return FALSE;
	}

	char szOutBuffer[32 * 1024] = {0};
	int nErr = 0;
	
	BOOL bSuccess 
		= CLIENT_QueryNewSystemInfo(getLoginHandle(), 
									CFG_CAP_CMD_VIDEOANALYSE, 
									nChannel, 
									szOutBuffer, 
									32 * 1024, 
									&nErr);
	if (bSuccess)
	{
		int nSize = sizeof(CFG_CAP_ANALYSE_INFO);
		int nRetLen = 0;
		BOOL bRet = 
			CLIENT_ParseData(CFG_CAP_CMD_VIDEOANALYSE, 
							szOutBuffer, 
							(char*)pCfgCapAnalyseInfo, 
							sizeof(CFG_CAP_ANALYSE_INFO), 
							&nRetLen);
		if (bRet == FALSE)
		{
			int x = ::CLIENT_GetLastError();
			AfxMessageBox(ConvertString(_T("Parser cap data error")));
			return FALSE;
		}
	}
	else
	{
		int x = ::CLIENT_GetLastError();
		AfxMessageBox(ConvertString(_T("Get device cap failed")));
		return FALSE;
	}
	return TRUE;
}
/*
 *	获取全局配置
 */
BOOL CDemoIVSbDlg::getGlobal(int nChannel, CFG_ANALYSEGLOBAL_INFO* pCfgAnalyseGlobalInfo)
{
	if (nChannel < 0 || !pCfgAnalyseGlobalInfo)
	{
		return FALSE;
	}
	
	int nErr = 0;
	char szOutBuffer[32 * 1024] = {0};
	
	// get global info
	BOOL bSuccess
		= CLIENT_GetNewDevConfig(getLoginHandle(), 
								CFG_CMD_ANALYSEGLOBAL, 
								nChannel,
								szOutBuffer, 
								32 * 1024, 
								&nErr);
	if (bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet
			= CLIENT_ParseData(CFG_CMD_ANALYSEGLOBAL, 
								szOutBuffer, 
								(char*)pCfgAnalyseGlobalInfo, 
								sizeof(CFG_ANALYSEGLOBAL_INFO),
								&nRetLen);
		if (bRet == FALSE)
		{
			int x = ::CLIENT_GetLastError();
			AfxMessageBox(ConvertString(_T("Parser Global data error")));
			return FALSE;
		}
	}//if(bSuccess)
	else
	{
		int x = ::CLIENT_GetLastError();
		AfxMessageBox(ConvertString(_T("Get device GlobalInfo failed")));
		return FALSE;
	}

	return TRUE;
}
/*
 *	获取模块配置
 */
BOOL CDemoIVSbDlg::getModule(int nChannel, CFG_ANALYSEMODULES_INFO* pCfgAnalyseModulesInfo)
{
	if (nChannel < 0 || !pCfgAnalyseModulesInfo)
	{
		return FALSE;
	}
	
	int nErr = 0;
	char szOutBuffer[32 * 1024] = {0};
	
	// get module info
	BOOL bSuccess 
		= CLIENT_GetNewDevConfig(getLoginHandle(), 
								CFG_CMD_ANALYSEMODULE, 
								nChannel,
								szOutBuffer, 
								32 * 1024, 
								&nErr);
	if (bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet 
			= CLIENT_ParseData(CFG_CMD_ANALYSEMODULE, 
								szOutBuffer, 
								(char*)pCfgAnalyseModulesInfo, 
								sizeof(CFG_ANALYSEMODULES_INFO), 
								&nRetLen);
		if (bRet == FALSE)
		{
			AfxMessageBox(ConvertString(_T("Parser Module data error")));
			return FALSE;
		}
	}//if(bSuccess)
	else
	{
		AfxMessageBox(ConvertString(_T("Get device ModuleInfo failed")));
		return FALSE;
	}

	return TRUE;
}
/*
 *	获取规则配置
 */
BOOL CDemoIVSbDlg::getRule(int nChannel, CFG_ANALYSERULES_INFO* pCfgAnalyseRulesInfo)
{
	if (nChannel < 0 || !pCfgAnalyseRulesInfo)
	{
		return FALSE;
	}

	int nErr = 0;
	char szOutBuffer[32*1024] = {0};
	
	// get module info
	BOOL bSuccess 
		= CLIENT_GetNewDevConfig(m_lLoginHandle, 
								CFG_CMD_ANALYSERULE, 
								nChannel,
								szOutBuffer, 
								32 * 1024, 
								&nErr, 
								2000);
	if (bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet
			= CLIENT_ParseData(CFG_CMD_ANALYSERULE, 
								szOutBuffer, 
								(char*)pCfgAnalyseRulesInfo, 
								sizeof(CFG_ANALYSERULES_INFO), 
								&nRetLen);
		if (bRet == FALSE)
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, 
					   _countof(szErr), 
					   _T("CLIENT_GetNewDevConfig() getChannel[%d] RuleInfo Error:%08x\n"), 
					   nChannel, 
					   ::CLIENT_GetLastError());
			::OutputDebugString(szErr);
			AfxMessageBox(ConvertString(_T("Parser Rule data error")));
			return FALSE;
		}
	}//if(bSuccess)
	else
	{
		TCHAR szErr[128] = {0};
		_sntprintf(szErr, 
				   _countof(szErr), 
				   _T("CLIENT_GetNewDevConfig() getChannel[%d] RuleInfo Error:%08x\n"), 
				   nChannel, 
				   ::CLIENT_GetLastError());
		::OutputDebugString(szErr);
		AfxMessageBox(ConvertString(_T("Get Rule info error")));
		return FALSE;
	}

	return TRUE;
}
/*
 *	因为具体的规则信息结构体大小不定，需要边获取配置信息得到需要的内存大小，边分配内存
 */
BOOL CDemoIVSbDlg::newConfigInfo(int nChnCount)
{
	if (nChnCount < 0 || nChnCount > g_MaxChannelCount)
	{
		return FALSE;
	}
	
	int i = 0;
	int nMaxStuSize = 0;
	int nSupportedRulesNum = 0;
	int nBufLen = 0;

	//获取每个通道的能力分析集
	m_pStuCfgCapAnalyseInfo  = new CFG_CAP_ANALYSE_INFO[nChnCount];
	if (!m_pStuCfgCapAnalyseInfo)
	{
		goto ErrorHandle;
	}
	ZeroMemory(m_pStuCfgCapAnalyseInfo, 
				sizeof(m_pStuCfgCapAnalyseInfo[0]) * nChnCount);
	
	for (i = 0; i < nChnCount; i++)
	{
		if (!getCap(i, &m_pStuCfgCapAnalyseInfo[i]))
		{
			::OutputDebugString(_T("getCap[] failed, goto ErrorHandle.\n"));
			goto ErrorHandle;
		}
	}

	if (m_pdlgLogo && m_pdlgLogo->GetSafeHwnd())
	{
		m_pdlgLogo->stepIt();
	}


	//获取每个通道的全局配置
	m_pStuCfgAnalyseGlobalInfo = new CFG_ANALYSEGLOBAL_INFO[nChnCount];
	if (!m_pStuCfgAnalyseGlobalInfo)
	{
		goto ErrorHandle;
	}
	ZeroMemory(m_pStuCfgAnalyseGlobalInfo, 
				sizeof(m_pStuCfgAnalyseGlobalInfo[0]) * nChnCount);

	for (i = 0; i < nChnCount; i++)
	{
		if (!getGlobal(i, &m_pStuCfgAnalyseGlobalInfo[i]))
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, 
					   _countof(szErr), 
					   _T("getChannel[%d] GlobalInfo Error:%08x\n"),
					   i, 
					   ::CLIENT_GetLastError());
			::OutputDebugString(szErr);
		}
	}
	
	if (m_pdlgLogo && m_pdlgLogo->GetSafeHwnd())
	{
		m_pdlgLogo->stepIt();
	}

	//获取每个通道的模块配置
	m_pStuCfgAnalyseModuleInfo = new CFG_ANALYSEMODULES_INFO[nChnCount];
	if (!m_pStuCfgAnalyseModuleInfo)
	{
		goto ErrorHandle;
	}
	ZeroMemory(m_pStuCfgAnalyseModuleInfo,
				sizeof(m_pStuCfgAnalyseModuleInfo[0]) * nChnCount);

	for (i = 0; i < nChnCount; i++)
	{
		if (!getModule(i, &m_pStuCfgAnalyseModuleInfo[i]))
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, 
					   _countof(szErr), 
					   _T("getChannel[%d] ModuleInfo Error:%08x\n"),
					   i, 
					   ::CLIENT_GetLastError());
			::OutputDebugString(szErr);
		}
	}
	
	if (m_pdlgLogo && m_pdlgLogo->GetSafeHwnd())
	{
		m_pdlgLogo->stepIt();
	}

	//////////////////////////////////////////////////////////////////////////

	//获取每个通道的规则配置，需要粗略的估计并分配内存给规则信息
	m_pStuCfgAnalyseRuleInfo = new CFG_ANALYSERULES_INFO[nChnCount];
	if (!m_pStuCfgAnalyseRuleInfo)
	{
		goto ErrorHandle;
	}
	ZeroMemory(m_pStuCfgAnalyseRuleInfo,
				sizeof(m_pStuCfgAnalyseRuleInfo[0]) * nChnCount);
	
	for (i = 0; i < nChnCount; i++)
	{
		nSupportedRulesNum = m_pStuCfgCapAnalyseInfo[i].nSupportedRulesNum;
		int j = 0;
		if (!nSupportedRulesNum)
		{
			//////////////////////////////////////////////////////////////////////////
			//2012-06-06 根据变化的能力分析集对应修改如下
			for (j = 0; j < m_pStuCfgCapAnalyseInfo[i].stSupportScenes.nScenes; j++)
			{
				if (strcmp(m_pStuCfgAnalyseGlobalInfo[i].szSceneType, 
						   m_pStuCfgCapAnalyseInfo[i].stSupportScenes.stScenes[j].szSceneName) == 0)
				{
					nSupportedRulesNum = m_pStuCfgCapAnalyseInfo[i].stSupportScenes.stScenes[j].nSupportRules;
					break;
				}
			}

			if (!nSupportedRulesNum)
			{
				continue;
			}
			//////////////////////////////////////////////////////////////////////////
		}

		nMaxStuSize 
			= getMaxStuSize(m_pStuCfgCapAnalyseInfo[i].stSupportScenes.stScenes[j].stSpportRules, 
							nSupportedRulesNum);
		if (!nMaxStuSize)
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, _countof(szErr), _T("getChannel[%d] MaxStuSize Error.\n"), i);
			::OutputDebugString(szErr);
			continue;
		}

		nBufLen = (nMaxStuSize + sizeof(CFG_RULE_INFO)) * m_pStuCfgCapAnalyseInfo[i].stSupportScenes.stScenes[j].nSupportRules;

		m_pStuCfgAnalyseRuleInfo[i].pRuleBuf = new char[nBufLen];
		if (!m_pStuCfgAnalyseRuleInfo[i].pRuleBuf)
		{
			goto ErrorHandle;
		}
		m_pStuCfgAnalyseRuleInfo[i].nRuleLen = nBufLen;
		ZeroMemory(m_pStuCfgAnalyseRuleInfo[i].pRuleBuf, nBufLen);
	}	
	
	if (m_pdlgLogo)
	{
		if (m_pdlgLogo->GetSafeHwnd())
		{
			m_pdlgLogo->stepIt();
		}
	}

	for (i = 0; i < nChnCount; i++)
	{
		if (!m_pStuCfgAnalyseRuleInfo[i].pRuleBuf)
		{
			continue;
		}

		if (!getRule(i, &m_pStuCfgAnalyseRuleInfo[i]))
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, _countof(szErr), _T("getChannel[%d] RuleInfo Error:%08x\n"), i, ::CLIENT_GetLastError());
			::OutputDebugString(szErr);
		}
	}
	
	if (m_pdlgLogo && m_pdlgLogo->GetSafeHwnd())
	{
		m_pdlgLogo->stepIt();
	}

	if (m_pdlgLogo && m_pdlgLogo->GetSafeHwnd())
	{
		m_pdlgLogo->stepIt();
	}

	//////////////////////////////////////////////////////////////////////////

	::OutputDebugString(_T("newConfigInfo success.\n"));

	return TRUE;

ErrorHandle:
	deleteConfigInfo();
	return FALSE;
}
/*
 *	
 */
void CDemoIVSbDlg::deleteConfigInfo()
{

	if (m_pStuCfgAnalyseRuleInfo)
	{
		for (int i = 0; i < m_nChnCount; i++)
		{
			if (m_pStuCfgAnalyseRuleInfo[i].pRuleBuf)
			{
				delete []m_pStuCfgAnalyseRuleInfo[i].pRuleBuf;
				m_pStuCfgAnalyseRuleInfo[i].pRuleBuf = NULL;
			}
		}

		delete []m_pStuCfgAnalyseRuleInfo;
		m_pStuCfgAnalyseRuleInfo = NULL;
	}
	
	if (m_pStuCfgAnalyseModuleInfo)
	{
		delete []m_pStuCfgAnalyseModuleInfo;
		m_pStuCfgAnalyseModuleInfo = NULL;
	}
	
	if (m_pStuCfgAnalyseGlobalInfo)
	{
		delete []m_pStuCfgAnalyseGlobalInfo;
		m_pStuCfgAnalyseGlobalInfo = NULL;
	}
	
	if (m_pStuCfgCapAnalyseInfo)
	{
		delete []m_pStuCfgCapAnalyseInfo;
		m_pStuCfgCapAnalyseInfo = NULL;
	}

	::OutputDebugString(_T("ReleaseConfigInfo success.\n"));
}

/*
 *	获取设备某通道的能力分析集
 */
CFG_CAP_ANALYSE_INFO* CDemoIVSbDlg::getCapAnalyseInfo(int nChannel)
{
	if (!m_pStuCfgCapAnalyseInfo || nChannel < 0 || nChannel >= g_MaxChannelCount)
	{
		return NULL;
	}

	return &(m_pStuCfgCapAnalyseInfo[nChannel]);
}
/*
 *	获取某通道的全局配置信息
 */
CFG_ANALYSEGLOBAL_INFO* CDemoIVSbDlg::getAnalyseGlobalInfo(int nChannel)
{
	if (!m_pStuCfgAnalyseGlobalInfo || nChannel < 0 || nChannel >= g_MaxChannelCount)
	{
		return NULL;
	}

	return (m_pStuCfgAnalyseGlobalInfo[nChannel].szSceneType ? &m_pStuCfgAnalyseGlobalInfo[nChannel] : NULL);
}
/*
 *	获取某通道的模块信息，具体的模块信息绑定在树控件节点上
 */
CFG_ANALYSEMODULES_INFO* CDemoIVSbDlg::getAnalyseModuleInfo(int nChannel)
{
	if (!m_pStuCfgAnalyseModuleInfo || nChannel < 0 || nChannel >= g_MaxChannelCount)
	{
		return NULL;
	}

	return (m_pStuCfgAnalyseModuleInfo[nChannel].nMoudlesNum ? &m_pStuCfgAnalyseModuleInfo[nChannel] : NULL);
}
/*
 *	获取某通道的规则信息，具体的规则信息绑定在树控件节点上
 */
CFG_ANALYSERULES_INFO* CDemoIVSbDlg::getAnalyseRulesInfo(int nChannel)
{
	if (!m_pStuCfgAnalyseRuleInfo || nChannel < 0 || nChannel >= g_MaxChannelCount)
	{
		return NULL;
	}

	return &m_pStuCfgAnalyseRuleInfo[nChannel];
}

int CDemoIVSbDlg::getScenceSeqOfCurChn(CFG_CAP_ANALYSE_INFO* pCapAnalyseInfo, CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobalInfo)
{
	if (!pCapAnalyseInfo || !pAnalyseGlobalInfo)
	{
		return -1;
	}

	int nScence = pCapAnalyseInfo->stSupportScenes.nScenes;
	if (!nScence)
	{
		return -1;
	}

	for (int i = 0; i < nScence; i++)
	{
		if (strcmp(pCapAnalyseInfo->stSupportScenes.stScenes[i].szSceneName,
				   pAnalyseGlobalInfo->szSceneType) == 0)
		{
			return i;
		}
	}

	return -1;
}

typedef struct tagMy_ThreadParam
{
	std::list<DWORD>* plsPtr;
	CDemoIVSbDlg* pMainDlg;

	tagMy_ThreadParam()
	{
		plsPtr = NULL;
		pMainDlg = NULL;
	}
}MY_THREADPARAM;
/*
 *	
 */
DWORD CDemoIVSbDlg::ThreadStartAlarm(void* pParam)
{
	MY_THREADPARAM* p = (MY_THREADPARAM*)pParam;
	if (!p->plsPtr || !p->pMainDlg)
	{
		return -1;
	}

	std::list<DWORD>* plsChannel = p->plsPtr;
	CDemoIVSbDlg* pMainDlg = p->pMainDlg;

	pMainDlg->stopAlarmCallBack();
	
	while(plsChannel->size())
	{
		DWORD dwChannel = plsChannel->front();
		
		LLONG lAlarmHandle = ::CLIENT_RealLoadPictureEx(pMainDlg->getLoginHandle(),
														dwChannel,	//ChannelNum,
														0,			//not support
														FALSE,		//not support
														CDemoIVSbDlg::RealLoadPicCallback,
														(LDWORD)pMainDlg,
														NULL);
		if (!lAlarmHandle)
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, 
						_countof(szErr), 
						_T("%s%02d %s 0x%08x\n"),
						ConvertString("Channel"),
						dwChannel + 1,
						ConvertString("can't start alarm detection with error:"),
						CLIENT_GetLastError());
			AfxMessageBox(szErr);
			plsChannel->pop_front();
			continue;
		}
		else
		{
			TCHAR szInfo[128] = {0};
			_sntprintf(szInfo,
					   _countof(szInfo),
					   _T("Start channel%02d alarm detection successfully with handle %08x.\n"),
					   dwChannel + 1,
					   lAlarmHandle);
			::OutputDebugString(szInfo);
		}
		
		pMainDlg->m_lsAlarmHandle.push_back(lAlarmHandle);

		plsChannel->pop_front();
	}

	if (plsChannel)
	{
		delete plsChannel;
		plsChannel = NULL;
	}

	if (p)
	{
		delete p;
		p = NULL;
	}

	
	if (pMainDlg->m_currentDlg != CDemoIVSbDlg::dlgAlarm)
	{
		pMainDlg->m_chkSwitch.EnableWindow(TRUE);
	}

	return 0;
}
/*
 *	
 */
void CDemoIVSbDlg::startAlarmCallBack(std::list<DWORD>* plsdwChannel)
{
	if (!plsdwChannel)
	{
		return;
	}

	if (!plsdwChannel->size())
	{
		return;
	}

	MY_THREADPARAM* pParam = new MY_THREADPARAM;
	if (!pParam)
	{
		return;
	}

	pParam->plsPtr = plsdwChannel;
	pParam->pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();

	HANDLE hThreadStartAlarm = ::CreateThread(NULL, 
											  0, 
											  (LPTHREAD_START_ROUTINE)ThreadStartAlarm,
											  (void*)pParam,
											  0, 
											  NULL);
	
	m_chkSwitch.EnableWindow(FALSE);

	if (hThreadStartAlarm == INVALID_HANDLE_VALUE)
	{
		m_chkSwitch.EnableWindow(TRUE);
		return;
	}
	
	::CloseHandle(hThreadStartAlarm);
}
/*
 *	
 */
BOOL CDemoIVSbDlg::stopAlarmCallBack()
{
	//TODO
	while(m_lsAlarmHandle.size())
	{
		LLONG llAlarmHandle = m_lsAlarmHandle.front();
		if (llAlarmHandle)
		{
			if (!::CLIENT_StopLoadPic(llAlarmHandle))
			{
				TCHAR szErr[64] = {0};
				_sntprintf(szErr, 
						   _countof(szErr), 
						   _T("Can't stop alarm, restart the demo and try.\n"));
				OutputDebugString(szErr);
				return FALSE;
			}
			else
			{
				TCHAR szInfo[32] = {0};
				_sntprintf(szInfo,
						   _countof(szInfo),
						   _T("Alarm Handle %08x stopped\n"),
						   llAlarmHandle);
				OutputDebugString(szInfo);
			}
		}

		m_lsAlarmHandle.pop_front();
	}

	return TRUE;
}
/*
 *	
 */
int CDemoIVSbDlg::getMaxStuSize(SCENE_SUPPORT_RULE* pRuleType, int nRuleNum)
{
	if (!pRuleType || nRuleNum <= 0)
	{
		return 0;
	}

	int nMaxSize = 0;

	for (int i = 0; i < nRuleNum; i++)
	{
		switch(pRuleType[i].dwSupportedRule)
		{
		case EVENT_IVS_CROSSFENCEDETECTION:
			nMaxSize = max(sizeof(CFG_CROSSFENCEDETECTION_INFO), nMaxSize);
			break;
		case EVENT_IVS_CROSSLINEDETECTION:
			nMaxSize = max(sizeof(CFG_CROSSLINE_INFO), nMaxSize);
			break;
		case EVENT_IVS_CROSSREGIONDETECTION:
			nMaxSize = max(sizeof(CFG_CROSSREGION_INFO), nMaxSize);
			break;
		case EVENT_IVS_MOVEDETECTION:
			nMaxSize = max(sizeof(CFG_MOVE_INFO), nMaxSize);
			break;
		case EVENT_IVS_LEFTDETECTION:
			nMaxSize = max(sizeof(CFG_LEFT_INFO), nMaxSize);
			break;
		case EVENT_IVS_PARKINGDETECTION:
			nMaxSize = max(sizeof(CFG_PARKINGDETECTION_INFO), nMaxSize);
			break;
		case EVENT_IVS_PRESERVATION:
			nMaxSize = max(sizeof(CFG_PRESERVATION_INFO), nMaxSize);
			break;
		case EVENT_IVS_RETROGRADEDETECTION:
			nMaxSize = max(sizeof(CFG_RETROGRADEDETECTION_INFO), nMaxSize);
			break;
		case EVENT_IVS_STAYDETECTION:
			nMaxSize = max(sizeof(CFG_STAY_INFO), nMaxSize);
			break;
		case EVENT_IVS_TAKENAWAYDETECTION:
			nMaxSize = max(sizeof(CFG_TAKENAWAYDETECTION_INFO), nMaxSize);
			break;
		case EVENT_IVS_VIDEOABNORMALDETECTION:
			nMaxSize = max(sizeof(CFG_VIDEOABNORMALDETECTION_INFO), nMaxSize);
			break;
		case EVENT_IVS_WANDERDETECTION:
			nMaxSize = max(sizeof(CFG_WANDER_INFO), nMaxSize);
			break;
		default:
			break;
		}
	}

	return nMaxSize;
}

/////////////////////////////////////////////////////////////////////////////
// CDemoIVSbDlg message handlers

BOOL CDemoIVSbDlg::OnInitDialog()
{
	//Forbid opening two programs at the same time
	if(g_share_hWnd)
	{
		AfxMessageBox(ConvertString(_T("Only one program will be allowed to open!")));
		CWnd* pWnd = CWnd::FromHandle(g_share_hWnd);
		if(pWnd)
		{
			if (pWnd->IsIconic())
			{
				pWnd->ShowWindow(SW_RESTORE);
			}
			pWnd->SetForegroundWindow(); 
		}
		EndDialog(FALSE);
		return TRUE;
	}
	else
	{
		g_share_hWnd = m_hWnd;
	}

	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//////////////////////////////////////////////////////////////////////////
	//初始化主窗口
	g_SetWndStaticText(this);

	CRect rt;
	GetClientRect(&rt);
	rt.top += 26;

	m_pdlgPreview = new CPreview;
	if (m_pdlgPreview)
	{
		m_pdlgPreview->Create(CPreview::IDD, this);
		m_pdlgPreview->MoveWindow(&rt, TRUE);
		m_pdlgPreview->ShowWindow(SW_SHOW);
	}

	m_pdlgConfig = new CConfig;
	if (m_pdlgConfig)
	{
		m_pdlgConfig->Create(CConfig::IDD, this);
		m_pdlgConfig->MoveWindow(&rt, TRUE);
		m_pdlgConfig->ShowWindow(SW_HIDE);
	}

	m_pdlgAlarm = new CAlarm;
	if (m_pdlgAlarm)
	{
		m_pdlgAlarm->Create(CAlarm::IDD, this);
		m_pdlgAlarm->MoveWindow(&rt, TRUE);
		m_pdlgAlarm->ShowWindow(SW_HIDE);
	}

	//////////////////////////////////////////////////////////////////////////
	//主窗口初始化成功后，尝试登录设备
	CLogin dlgLogin;
	if (dlgLogin.DoModal() == IDOK)
	{
		if (m_pdlgLogo)
		{
			if (m_pdlgLogo->GetSafeHwnd())
			{
				m_pdlgLogo->DestroyWindow();
			}
			delete m_pdlgLogo;
			m_pdlgLogo = NULL;
		}
		//
		m_pdlgLogo = new CLogo;
		if (m_pdlgLogo)
		{
			m_pdlgLogo->Create(CLogo::IDD, this);
			m_pdlgLogo->CenterWindow();
			m_pdlgLogo->ShowWindow(SW_SHOW);
		}

		//将登陆成功的设备的地址、端口、句柄传递给主窗口
		LLONG lLoginHandle = dlgLogin.getLoginHandle();
		if (lLoginHandle)
		{
			setLoginHandel(lLoginHandle);
		}

		if (m_pdlgLogo)
		{
			if (m_pdlgLogo->GetSafeHwnd())
			{
				m_pdlgLogo->stepIt();
			}
		}

		NET_DEVICEINFO* pNetDevInfo = dlgLogin.getNetDeviceInfo();
		if (pNetDevInfo)
		{
			memcpy(&m_stuDeviceInfo, pNetDevInfo, sizeof(*pNetDevInfo));
		}

		if (m_pdlgLogo)
		{
			if (m_pdlgLogo->GetSafeHwnd())
			{
				m_pdlgLogo->stepIt();
			}
		}
		m_pdlgPreview->initPreviewDlg(m_stuDeviceInfo.byChanNum);
		if (m_pdlgLogo)
		{
			if (m_pdlgLogo->GetSafeHwnd())
			{
				m_pdlgLogo->stepIt();
			}
		}

		m_pdlgAlarm->initAlarmDlg(m_stuDeviceInfo.byChanNum);
		if (m_pdlgLogo)
		{
			if (m_pdlgLogo->GetSafeHwnd())
			{
				m_pdlgLogo->stepIt();
			}
		}
	}
	else
	{
		m_chkSwitch.EnableWindow(FALSE);
		SetDlgItemText(IDC_MAIN_BTN_LOGOUT, ConvertString(_T("Login")));
		m_pdlgPreview->EnableWindow(FALSE);
		m_pdlgConfig->EnableWindow(FALSE);
		m_pdlgAlarm->EnableWindow(FALSE);

		GetDlgItem(IDC_MAIN_BTN_PREVIEW)->EnableWindow(FALSE);
		GetDlgItem(IDC_MAIN_BTN_CONFIG)->EnableWindow(FALSE);
		GetDlgItem(IDC_MAIN_BTN_ALARM)->EnableWindow(FALSE);
	}
	
	//////////////////////////////////////////////////////////////////////////
	//初始化配置信息结构体
	if (m_lLoginHandle)
	{
		m_nChnCount 
			= (g_MaxChannelCount >= m_stuDeviceInfo.byChanNum 
			   ? m_stuDeviceInfo.byChanNum : g_MaxChannelCount);

		//要先获得能力集，再给配置信息结构体们分配内存
		newConfigInfo(m_nChnCount);

		m_pdlgLogo->stepIt();
	}

	if (m_pdlgLogo)
	{
		if (m_pdlgLogo->GetSafeHwnd())
		{
			m_pdlgLogo->DestroyWindow();
		}
		delete m_pdlgLogo;
		m_pdlgLogo = NULL;
	}

	ShowWindow(SW_MINIMIZE);
	ShowWindow(SW_RESTORE);
	SetForegroundWindow();
	CenterWindow();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoIVSbDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoIVSbDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoIVSbDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoIVSbDlg::ShowDlg(enum DlgType dlgTYPE)
{
	if (dlgTYPE == m_currentDlg)
	{
		return;
	}

	if (m_pdlgConfig->m_dlgConfigGlobal.m_pIvsGlobalPreview->isDrawing()
		|| m_pdlgConfig->m_dlgConfigModule.m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	BOOL bAddRegion = m_pdlgConfig->m_dlgConfigRules.m_pIvsRulePreview->m_bAddRegion;

	if (bAddRegion || m_pdlgConfig->m_dlgConfigRules.m_bAddRule)
	{
		if (m_pdlgConfig->m_dlgConfigRules.m_cmbRuleType.GetCurSel() == -1)
		{
			AfxMessageBox(ConvertString(_T("Please select the rule type first")));
		} 
		else
		{
			AfxMessageBox(ConvertString(_T("Please draw the line of rule first or click right button to stop drawing")));
		}

		return;
	}

	if (m_currentDlg == dlgPreview)
	{
		m_pdlgPreview->closePreview(m_lRealPlayHandle);
	}

	switch(dlgTYPE)
	{
	case dlgPreview:
		m_pdlgPreview->ShowWindow(SW_SHOW);
		m_pdlgConfig->ShowWindow(SW_HIDE);
		m_pdlgAlarm->ShowWindow(SW_HIDE);
		m_currentDlg = dlgPreview;
		m_chkSwitch.EnableWindow(TRUE);
		if (m_lLoginHandle)
		{
			m_pdlgPreview->showPreview(m_lLoginHandle, m_nCurrentChn);
		}
		break;
	case dlgConfig:
		m_pdlgPreview->ShowWindow(SW_HIDE);
		m_pdlgConfig->ShowWindow(SW_SHOW);
		m_pdlgAlarm->ShowWindow(SW_HIDE);
		m_currentDlg = dlgConfig;
		m_chkSwitch.EnableWindow(TRUE);
		if (m_lLoginHandle)
		{
			m_pdlgConfig->showPreview();
		}
		break;
	case dlgAlarm:
		m_pdlgPreview->ShowWindow(SW_HIDE);
		m_pdlgConfig->ShowWindow(SW_HIDE);
		m_pdlgAlarm->ShowWindow(SW_SHOW);
		m_currentDlg = dlgAlarm;
		if (m_lLoginHandle)
		{
			m_pdlgPreview->closePreview(m_lRealPlayHandle);
		}
		m_pdlgAlarm->showAlarmInfo();
		m_chkSwitch.EnableWindow(FALSE);
		break;
	default:
		break;
	}
}

void CDemoIVSbDlg::OnBtnPreview() 
{
	// TODO: Add your control notification handler code here
	ShowDlg(dlgPreview);
}

void CDemoIVSbDlg::OnBtnConfig() 
{
	// TODO: Add your control notification handler code here
	ShowDlg(dlgConfig);
}

void CDemoIVSbDlg::OnBtnAlarm() 
{
	// TODO: Add your control notification handler code here
	ShowDlg(dlgAlarm);
}

void CDemoIVSbDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	stopAlarmCallBack();

	while(m_lstAlarmInfo.size())
	{
		AlarmInfoNode* pNode = m_lstAlarmInfo.front();
		if (pNode)
		{
			delete pNode;
			pNode = NULL;
		}
		m_lstAlarmInfo.pop_front();
	}

	//先关闭画面
	if (m_lRealPlayHandle)
	{
		::CLIENT_StopRealPlay(m_lRealPlayHandle);
		m_lRealPlayHandle = 0;

		
		s_PlayAPI.PLAY_Stop(g_nPlayPort);
		s_PlayAPI.PLAY_CloseStream(g_nPlayPort);

		OutputDebugString(_T("Stop RealPlay...\n"));
	}

	if (m_lLoginHandle)
	{
		::CLIENT_Logout(m_lLoginHandle);
		m_lLoginHandle = 0;
		OutputDebugString(_T("Logout...\n"));
	}

	//然后关闭、释放子窗口
	if (m_pdlgPreview)
	{
		if (m_pdlgPreview->GetSafeHwnd())
		{
			m_pdlgPreview->DestroyWindow();
		}
		delete m_pdlgPreview;
		m_pdlgPreview = NULL;
	}

	if (m_pdlgConfig)
	{
		if (m_pdlgConfig->GetSafeHwnd())
		{
			m_pdlgConfig->DestroyWindow();
		}
		delete m_pdlgConfig;
		m_pdlgConfig = NULL;
	}

	if (m_pdlgAlarm)
	{
		if (m_pdlgAlarm->GetSafeHwnd())
		{
			m_pdlgAlarm->DestroyWindow();
		}
		delete m_pdlgAlarm;
		m_pdlgAlarm = NULL;
	}
	
	//最后清空配置信息
	deleteConfigInfo();

	//////////////////////////////////////////////////////////////////////////
}
/*
 *	选择通道和订阅事件，启动/关闭设备检测
 */
void CDemoIVSbDlg::OnMainChkSwitch() 
{
	// TODO: Add your control notification handler code here
	BOOL bAddRegion = m_pdlgConfig->m_dlgConfigRules.m_pIvsRulePreview->m_bAddRegion;
	
	if (bAddRegion || m_pdlgConfig->m_dlgConfigRules.m_bAddRule)
	{
		if (m_pdlgConfig->m_dlgConfigRules.m_cmbRuleType.GetCurSel() == -1)
		{
			AfxMessageBox(ConvertString(_T("Please select the rule type first")));
		} 
		else
		{
			AfxMessageBox(ConvertString(_T("Please draw the line of rule first or click right button to stop drawing")));
		}

		if (m_chkSwitch.GetCheck())
		{
			m_chkSwitch.SetCheck(BST_UNCHECKED);
			m_chkSwitch.SetWindowText(ConvertString(_T("AlarmOn")));
		} 
		else
		{
			m_chkSwitch.SetCheck(BST_CHECKED);
			m_chkSwitch.SetWindowText(ConvertString(_T("AlarmOff")));
		}
		
		return;
	}

	if (!m_lLoginHandle)
	{
		AfxMessageBox(ConvertString(_T("Login first")));
		m_chkSwitch.SetCheck(BST_UNCHECKED);
		m_chkSwitch.SetWindowText(ConvertString(_T("AlarmOn")));
		return;
	}

// 	if (!m_lRealPlayHandle)
// 	{
// 		AfxMessageBox(ConvertString(_T("Choose a channel to play first")));
//		m_chkSwitch.SetCheck(BST_UNCHECKED);
// 		return;
// 	}

	if (!m_chkSwitch.GetCheck())
	{
		//关闭设备检测
		m_chkSwitch.SetCheck(BST_UNCHECKED);
		m_chkSwitch.SetWindowText(ConvertString(_T("AlarmOn")));

		stopAlarmCallBack();
	}
	else
	{
		CSwitch dlgSwitch;
		if (dlgSwitch.DoModal() == IDOK)
		{
			//启动设备检测

			m_chkSwitch.SetCheck(BST_CHECKED);
			m_chkSwitch.SetWindowText(ConvertString(_T("AlarmOff")));
		}
		else
		{
			m_chkSwitch.SetCheck(BST_UNCHECKED);
			m_chkSwitch.SetWindowText(ConvertString(_T("AlarmOn")));
		}
	}
}
/*
 *	登出设备按钮
 */
void CDemoIVSbDlg::OnMainBtnLogout() 
{
	// TODO: Add your control notification handler code here
	if (m_lLoginHandle)
	{
		//登出设备，
		//关闭主窗口视频画面、报警信息，清理主窗口信息；
		if (m_lRealPlayHandle)
		{
			stopAlarmCallBack();
			while(m_lstAlarmInfo.size())
			{
				AlarmInfoNode* pNode = m_lstAlarmInfo.front();
				if (pNode)
				{
					delete pNode;
					pNode = NULL;
				}
				m_lstAlarmInfo.pop_front();
			}

			::CLIENT_StopRealPlay(m_lRealPlayHandle);
			m_lRealPlayHandle = 0;
			//////////////////////////////////////////////////////////////////////////
			//
			s_PlayAPI.PLAY_Stop(g_nPlayPort);
			s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			
			//////////////////////////////////////////////////////////////////////////
			Invalidate(FALSE);
		}

		if (m_lLoginHandle)
		{
			::CLIENT_Logout(m_lLoginHandle);
			m_lLoginHandle = 0;
		}

		m_nCurrentChn = -1;

		m_pdlgAlarm->uninitAlarmDlg();
		m_pdlgConfig->uninitConfigDlg();
		m_pdlgPreview->uninitPreviewDlg();

		//清理配置窗口信息；
		deleteConfigInfo();

		//清理报警查看窗口信息；
		
		m_chkSwitch.SetCheck(BST_UNCHECKED);
		m_chkSwitch.SetWindowText(ConvertString(_T("AlarmOn")));
		m_chkSwitch.EnableWindow(FALSE);
		SetDlgItemText(IDC_MAIN_BTN_LOGOUT, ConvertString(_T("Login")));
		m_pdlgPreview->EnableWindow(FALSE);
		m_pdlgConfig->EnableWindow(FALSE);
		m_pdlgAlarm->EnableWindow(FALSE);

		GetDlgItem(IDC_MAIN_BTN_PREVIEW)->EnableWindow(FALSE);
		GetDlgItem(IDC_MAIN_BTN_CONFIG)->EnableWindow(FALSE);
		GetDlgItem(IDC_MAIN_BTN_ALARM)->EnableWindow(FALSE);

//		ShowDlg(dlgPreview);
		m_pdlgPreview->ShowWindow(SW_SHOW);
		m_pdlgConfig->ShowWindow(SW_HIDE);
		m_pdlgAlarm->ShowWindow(SW_HIDE);
		m_currentDlg = dlgPreview;
	}
	else
	{
		//登录设备
		CLogin dlgLogin;
		if (dlgLogin.DoModal() == IDOK)
		{
			if (m_pdlgLogo)
			{
				if (m_pdlgLogo->GetSafeHwnd())
				{
					m_pdlgLogo->DestroyWindow();
				}
				delete m_pdlgLogo;
				m_pdlgLogo = NULL;
			}

			m_pdlgLogo = new CLogo;
			if (m_pdlgLogo)
			{
				m_pdlgLogo->Create(CLogo::IDD, this);
				m_pdlgLogo->CenterWindow(NULL);
				m_pdlgLogo->ShowWindow(SW_SHOW);
				m_pdlgLogo->stepIt();
			}

			LLONG lLoginHandle = dlgLogin.getLoginHandle();
			if (lLoginHandle)
			{
				m_lLoginHandle = lLoginHandle;
			}

			if (m_pdlgLogo)
			{
				if (m_pdlgLogo->GetSafeHwnd())
				{
					m_pdlgLogo->stepIt();
				}
			}

			NET_DEVICEINFO* pNetDevInfo = dlgLogin.getNetDeviceInfo();
			if (pNetDevInfo)
			{
				ZeroMemory(&m_stuDeviceInfo, sizeof(m_stuDeviceInfo));
				memcpy(&m_stuDeviceInfo, pNetDevInfo, sizeof(*pNetDevInfo));
			}
			
			if (m_pdlgLogo)
			{
				if (m_pdlgLogo->GetSafeHwnd())
				{
					m_pdlgLogo->stepIt();
				}
			
			}
			//分配空间，获取设备配置信息
			m_nChnCount 
				= (g_MaxChannelCount >= m_stuDeviceInfo.byChanNum ? m_stuDeviceInfo.byChanNum : g_MaxChannelCount);
			newConfigInfo(m_nChnCount);

			//初始化子窗口
			m_pdlgPreview->initPreviewDlg(m_stuDeviceInfo.byChanNum);
			if (m_pdlgLogo)
			{
				if (m_pdlgLogo->GetSafeHwnd())
				{
					m_pdlgLogo->stepIt();
				}
			}

			m_pdlgAlarm->initAlarmDlg(m_stuDeviceInfo.byChanNum);
			if (m_pdlgLogo)
			{
				if (m_pdlgLogo->GetSafeHwnd())
				{
					m_pdlgLogo->stepIt();
				}
			}

			m_chkSwitch.EnableWindow(TRUE);
			SetDlgItemText(IDC_MAIN_BTN_LOGOUT, ConvertString(_T("Logout")));
			m_pdlgPreview->EnableWindow(TRUE);
			m_pdlgConfig->EnableWindow(TRUE);
			m_pdlgAlarm->EnableWindow(TRUE);
			
			GetDlgItem(IDC_MAIN_BTN_PREVIEW)->EnableWindow(TRUE);
			GetDlgItem(IDC_MAIN_BTN_CONFIG)->EnableWindow(TRUE);
			GetDlgItem(IDC_MAIN_BTN_ALARM)->EnableWindow(TRUE);
			
			if (m_pdlgLogo)
			{
				if (m_pdlgLogo->GetSafeHwnd())
				{
					m_pdlgLogo->stepIt();
				}
			}

			if (m_pdlgLogo)
			{
				if (m_pdlgLogo->GetSafeHwnd())
				{
					m_pdlgLogo->DestroyWindow();
				}
				delete m_pdlgLogo;
				m_pdlgLogo = NULL;
			}
		}
		else
		{
			m_chkSwitch.SetCheck(BST_UNCHECKED);
		}
	}
}

