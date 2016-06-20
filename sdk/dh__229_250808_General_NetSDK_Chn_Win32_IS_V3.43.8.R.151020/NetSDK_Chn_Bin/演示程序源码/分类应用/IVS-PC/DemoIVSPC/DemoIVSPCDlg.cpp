// DemoIVSPCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSPC.h"
#include "DemoIVSPCDlg.h"

#include "Login.h"
#include "Logo.h"
#include "Preview.h"
#include "Config.h"
#include "DlgQuery.h"


#define WM_DISCONNECT	WM_USER + 100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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
// CDemoIVSPCDlg dialog

CDemoIVSPCDlg::CDemoIVSPCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoIVSPCDlg::IDD, pParent),
	m_pdlgLogo(NULL),
	m_currentDlg(dlgNone),
	m_nCurrentChn(-1),
	m_bIsSwitchOn(FALSE),
	m_pdlgPreview(NULL),
	m_pdlgConfig(NULL),
	m_pdlgQuery(NULL),
	m_lLoginHandle(0),
	m_lRealPlayHandle(0),
	m_lAnalyzerHandle(0),
	m_nChnCount(0),
	m_pStuCfgCapAnalyseInfo(NULL),
	m_pStuCfgAnalyseGlobalInfo(NULL),
	m_pStuCfgAnalyseModuleInfo(NULL),
	m_pStuCfgAnalyseRuleInfo(NULL),
	m_pRuleList(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ZeroMemory(&m_stuDeviceInfo, sizeof(m_stuDeviceInfo));
}

CDemoIVSPCDlg::~CDemoIVSPCDlg()
{
};

void CDemoIVSPCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoIVSPCDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoIVSPCDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoIVSPCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MAIN_BTN_PREVIEW, OnBtnPreview)
	ON_BN_CLICKED(IDC_MAIN_BTN_CONFIG, OnBtnConfig)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MAIN_BTN_LOGOUT, OnMainBtnLogout)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MAIN_BTN_QUERY, CDemoIVSPCDlg::OnBnClickedMainBtnQuery)
	ON_MESSAGE(WM_DISCONNECT, CDemoIVSPCDlg::DeviceDisConnect)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
//

/*
 *	获取能力分析集
 */
BOOL CDemoIVSPCDlg::GetCap(int nChannel, CFG_CAP_ANALYSE_INFO* pCfgCapAnalyseInfo)
{
	if (nChannel < 0 || !pCfgCapAnalyseInfo)
	{
		return FALSE;
	}

	char szOutBuffer[32 * 1024] = {0};
	int nErr = 0;
	
	BOOL bSuccess 
		= CLIENT_QueryNewSystemInfo(GetLoginHandle(), 
									CFG_CAP_CMD_VIDEOANALYSE, 
									nChannel, 
									szOutBuffer, 
									_countof(szOutBuffer), 
									&nErr);
// 	if (nChannel == 1)
// 	{
// 		FILE* fp = fopen("szOutBuffer.txt", "wb");
// 		if (fp == NULL)
// 		{
// 			MessageBox(ConvertString("Save picture failed!"), ConvertString("Prompt"));
// 		}
// 		fwrite(szOutBuffer, strlen(szOutBuffer), 1, fp);
// 		fclose(fp);
// 	}
	if (bSuccess)
	{
// 		if (0 == nChannel)
// 		{
// 			CFile file;
// 			file.Open("10.36.45.124_0.txt", CFile::modeCreate | CFile::modeWrite);
// 			file.WriteHuge(szOutBuffer, strlen(szOutBuffer));
// 			file.Close();
// 		}

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
			MessageBox(ConvertString("Parser data error!"), ConvertString("Prompt"));
			return FALSE;
		}
	}
	else
	{
		int x = ::CLIENT_GetLastError();
		MessageBox(ConvertString("Get device cap failed!"), ConvertString("Prompt"));
		return FALSE;
	}
	return TRUE;
}
/*
 *	获取全局配置
 */
BOOL CDemoIVSPCDlg::GetGlobal(int nChannel, CFG_ANALYSEGLOBAL_INFO* pCfgAnalyseGlobalInfo)
{
	if (nChannel < 0 || !pCfgAnalyseGlobalInfo)
	{
		return FALSE;
	}
	
	int nErr = 0;
	char szOutBuffer[32 * 1024] = {0};
	
	// get global info
	BOOL bSuccess
		= CLIENT_GetNewDevConfig(GetLoginHandle(), 
								CFG_CMD_ANALYSEGLOBAL, 
								nChannel,
								szOutBuffer, 
								_countof(szOutBuffer), 
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
			MessageBox(ConvertString("Parser data error!"), ConvertString("Prompt"));
			return FALSE;
		}
	}//if(bSuccess)
	else
	{
		int x = ::CLIENT_GetLastError();
		MessageBox(ConvertString("Get TrafficScene failed!"), ConvertString("Prompt"));
		return FALSE;
	}

	return TRUE;
}
/*
 *	获取模块配置
 */
BOOL CDemoIVSPCDlg::GetModule(int nChannel, CFG_ANALYSEMODULES_INFO* pCfgAnalyseModulesInfo)
{
	if (nChannel < 0 || !pCfgAnalyseModulesInfo)
	{
		return FALSE;
	}
	
	int nErr = 0;
	char szOutBuffer[32 * 1024] = {0};
	
	// get module info
	BOOL bSuccess 
		= CLIENT_GetNewDevConfig(GetLoginHandle(), 
								CFG_CMD_ANALYSEMODULE, 
								nChannel,
								szOutBuffer, 
								_countof(szOutBuffer), 
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
			MessageBox(ConvertString("Parser data error!"), ConvertString("Prompt"));
			return FALSE;
		}
	}//if(bSuccess)
	else
	{
		MessageBox(ConvertString("Get Module info failed!"), ConvertString("Prompt"));
		return FALSE;
	}

	return TRUE;
}
/*
 *	获取规则配置
 */
BOOL CDemoIVSPCDlg::GetRule(int nChannel, CFG_ANALYSERULES_INFO* pCfgAnalyseRulesInfo)
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
								_countof(szOutBuffer), 
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
			_sntprintf(szErr, _countof(szErr) * sizeof(TCHAR), _T("CLIENT_GetNewDevConfig() getChannel[%d] RuleInfo Error:%08x"), 
					   nChannel, ::CLIENT_GetLastError());
			::OutputDebugString(szErr);
			return FALSE;
		}
	}//if(bSuccess)
	else
	{
		TCHAR szErr[128] = {0};
		_sntprintf(szErr, _countof(szErr) * sizeof(TCHAR), _T("CLIENT_GetNewDevConfig() getChannel[%d] RuleInfo Error:%08x"), 
				   nChannel, ::CLIENT_GetLastError());
		::OutputDebugString(szErr);
		return FALSE;
	}

	return TRUE;
}
/*
 *	因为具体的规则信息结构体大小不定，需要边获取配置信息得到需要的内存大小，边分配内存
 */
BOOL CDemoIVSPCDlg::NewConfigInfo(int nChnCount)
{
	if (nChnCount < 0 || nChnCount > g_MaxChannelCount)
	{
		return FALSE;
	}
	
	int i = 0;
	int nMaxStuSize = 0;
	int nSupportedRulesNum = 0;
	int nBufLen = 0;
	DeleteConfigInfo();
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
		if (!GetCap(i, &m_pStuCfgCapAnalyseInfo[i]))
		{
			::OutputDebugString(_T("getCap[] failed, goto ErrorHandle."));
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
		if (!GetGlobal(i, &m_pStuCfgAnalyseGlobalInfo[i]))
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, _countof(szErr) * sizeof(TCHAR), _T("getChannel[%d] GlobalInfo Error:%08x"),
					   i, ::CLIENT_GetLastError());
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
		if (!GetModule(i, &m_pStuCfgAnalyseModuleInfo[i]))
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, _countof(szErr) * sizeof(TCHAR), _T("getChannel[%d] ModuleInfo Error:%08x"),
					   i, ::CLIENT_GetLastError());
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

		nMaxStuSize = GetMaxStuSize(m_pStuCfgCapAnalyseInfo[i].stSupportScenes.stScenes[j].stSpportRules, 
							nSupportedRulesNum);
		if (!nMaxStuSize)
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, _countof(szErr) * sizeof(TCHAR), _T("getChannel[%d] MaxStuSize Error."), i);
			::OutputDebugString(szErr);
			continue;

		}

		nBufLen = (nMaxStuSize + sizeof(CFG_RULE_INFO)) * m_pStuCfgCapAnalyseInfo[i].nMaxRules;
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

		if (!GetRule(i, &m_pStuCfgAnalyseRuleInfo[i]))
		{
			TCHAR szErr[128] = {0};
			_sntprintf(szErr, _countof(szErr) * sizeof(TCHAR), _T("getChannel[%d] RuleInfo Error:%08x"), i, ::CLIENT_GetLastError());
			::OutputDebugString(szErr);
		}
	}
	
	if (m_pdlgLogo && m_pdlgLogo->GetSafeHwnd())
	{
		m_pdlgLogo->stepIt();
	}

	//将规则按照通道号罗列成链表
	PutRuleInfoIntoList(nChnCount);

	if (m_pdlgLogo && m_pdlgLogo->GetSafeHwnd())
	{
		m_pdlgLogo->stepIt();
	}

	//////////////////////////////////////////////////////////////////////////

	::OutputDebugString(_T("newConfigInfo success."));

	return TRUE;

ErrorHandle:
	DeleteConfigInfo();
	return FALSE;
}
/*
 *	
 */
void CDemoIVSPCDlg::DeleteConfigInfo()
{
	if (m_pRuleList)
	{
		RuleStruct* pRuleStruct = NULL;

		for (int i = 0; i < m_nChnCount; i++)
		{
			while (m_pRuleList[i].size())
			{
				pRuleStruct = (RuleStruct*)m_pRuleList[i].front();
				if (pRuleStruct)
				{
					if (pRuleStruct->pRuleBuf)
					{
						delete []pRuleStruct->pRuleBuf;
						pRuleStruct->pRuleBuf = NULL;
					}

					delete pRuleStruct;
					pRuleStruct = NULL;
				}

				m_pRuleList[i].pop_front();
			}

			m_pRuleList[i].clear();
		}

		delete []m_pRuleList;
		m_pRuleList = NULL;
	}

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

	::OutputDebugString(_T("ReleaseConfigInfo success."));
}

/*
 *	获取设备某通道的能力分析集
 */
CFG_CAP_ANALYSE_INFO* CDemoIVSPCDlg::GetCapAnalyseInfo(int nChannel)
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
CFG_ANALYSEGLOBAL_INFO* CDemoIVSPCDlg::GetAnalyseGlobalInfo(int nChannel)
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
CFG_ANALYSEMODULES_INFO* CDemoIVSPCDlg::GetAnalyseModuleInfo(int nChannel)
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
CFG_ANALYSERULES_INFO* CDemoIVSPCDlg::GetAnalyseRulesInfo(int nChannel)
{
	if (!m_pStuCfgAnalyseRuleInfo || nChannel < 0 || nChannel >= g_MaxChannelCount)
	{
		return NULL;
	}

	return (m_pStuCfgAnalyseRuleInfo[nChannel].nRuleCount ? &m_pStuCfgAnalyseRuleInfo[nChannel] : NULL);
}

int CDemoIVSPCDlg::GetScenceSeqOfCurChn(CFG_CAP_ANALYSE_INFO* pCapAnalyseInfo, CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobalInfo)
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
/*
 *	获取某通道的具体规则链表的头指针
 */
lsRuleList* CDemoIVSPCDlg::GetRuleList(int nChannel)
{
	if (!m_pRuleList || nChannel < 0 || nChannel >= g_MaxChannelCount)
	{
		return NULL;
	}

	return (m_pRuleList[nChannel].size() ? &m_pRuleList[nChannel] : NULL);
}


void CDemoIVSPCDlg::EnableLoginWindow(LoginState emState)
{
	switch(emState)
	{
	case LoginSucc:
		{
			GetDlgItem(IDC_MAIN_BTN_PREVIEW)->EnableWindow(TRUE);
			GetDlgItem(IDC_MAIN_BTN_CONFIG)->EnableWindow(FALSE);
			GetDlgItem(IDC_MAIN_BTN_QUERY)->EnableWindow(TRUE);
		}
		break;
	case LogOut:
	case LoginFailed:
		{
			GetDlgItem(IDC_MAIN_BTN_PREVIEW)->EnableWindow(FALSE);
			GetDlgItem(IDC_MAIN_BTN_CONFIG)->EnableWindow(FALSE);
			GetDlgItem(IDC_MAIN_BTN_QUERY)->EnableWindow(FALSE);
		}
		break;
	case LoginOpenView:
		{
			GetDlgItem(IDC_MAIN_BTN_PREVIEW)->EnableWindow(TRUE);
			GetDlgItem(IDC_MAIN_BTN_CONFIG)->EnableWindow(TRUE);
			GetDlgItem(IDC_MAIN_BTN_QUERY)->EnableWindow(TRUE);
		}
		break;
	default:
		{
			GetDlgItem(IDC_MAIN_BTN_PREVIEW)->EnableWindow(FALSE);
			GetDlgItem(IDC_MAIN_BTN_CONFIG)->EnableWindow(FALSE);
			GetDlgItem(IDC_MAIN_BTN_QUERY)->EnableWindow(FALSE);
		}
		break;
	}
		
};

void CDemoIVSPCDlg::RefreshModuleInfo()
{
	if (m_pStuCfgAnalyseModuleInfo == NULL)
	{
		return;
	}

	for (int i = 0; i < m_nChnCount; ++i)
	{
		GetModule(i, &m_pStuCfgAnalyseModuleInfo[i]);
	}
};

void CDemoIVSPCDlg::RefreshGlobalInfo()
{
	if (m_pStuCfgAnalyseGlobalInfo == NULL)
	{
		return;
	}

	for (int i = 0; i < m_nChnCount; ++i)
	{
		GetGlobal(i, &m_pStuCfgAnalyseGlobalInfo[i]);
	}

};

void CDemoIVSPCDlg::RefreshRuleInfo()
{
	if (m_pStuCfgAnalyseRuleInfo == NULL)
	{
		return;
	}
	
	for (int i = 0; i < m_nChnCount; ++i)
	{
		GetRule(i, &m_pStuCfgAnalyseRuleInfo[i]);
	}
	
};


/*
 *	
 */
int CDemoIVSPCDlg::GetMaxStuSize(SCENE_SUPPORT_RULE* pRuleType, int nRuleNum)
{
	if (!pRuleType || nRuleNum <= 0)
// 	if (!pRuleType || nRuleNum < 0)
	{
		return 0;
	}

	int nMaxSize = 0;

	for (int i = 0; i < nRuleNum; i++)
	{
		switch(pRuleType[i].dwSupportedRule)
		{
		case EVENT_IVS_TRAFFICGATE:
			nMaxSize = max(sizeof(CFG_TRAFFICGATE_INFO), nMaxSize);
			break;
			//
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
		case EVENT_IVS_NUMBERSTAT:
			nMaxSize = max(sizeof(CFG_NUMBERSTAT_INFO), nMaxSize);
			break;
		default:
			break;
		}
	}

	return nMaxSize;
}

void CDemoIVSPCDlg::PutRuleInfoIntoList(int nChnCount)
{
	if (!nChnCount)
	{
		return;
	}

	m_pRuleList = new lsRuleList[nChnCount];
	if (!m_pRuleList)
	{
		return;
	}
//	ZeroMemory(m_pRuleList, sizeof(lsRuleList) * nChnCount);
	
	CFG_ANALYSERULES_INFO* pAnaRuleInfo = NULL;
	CFG_RULE_INFO* pRule = NULL;
	RuleStruct* pRuleStruct = NULL;

	for(int i = 0; i < nChnCount; i++)
	{
		pAnaRuleInfo = GetAnalyseRulesInfo(i);
		if (!pAnaRuleInfo)
		{
			continue;
		}

		
		int nReadLen = 0;
		for(int j = 0; j < pAnaRuleInfo->nRuleCount; j++)
		{
			pRule = (CFG_RULE_INFO*)(pAnaRuleInfo->pRuleBuf + nReadLen);

			pRuleStruct = new RuleStruct;
			if (!pRuleStruct)
			{
				goto ErrorHandleDispatch;
			}

			int x = sizeof(CFG_PASTE_INFO);

			//读取每个规则，指针存到链表
			switch(pRule->dwRuleType)
			{
				//0Paste
			case EVENT_IVS_PASTEDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_PASTE_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_PASTE_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_PASTE_INFO);
				break;
				//1CrossFence
			case EVENT_IVS_CROSSFENCEDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_CROSSFENCEDETECTION_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}

				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					   pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					   sizeof(CFG_CROSSFENCEDETECTION_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_CROSSFENCEDETECTION_INFO);
				break;
				//2CrossLine
			case EVENT_IVS_CROSSLINEDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_CROSSLINE_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					   pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					   sizeof(CFG_CROSSLINE_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_CROSSLINE_INFO);
				break;
				//3CrossRegion
			case EVENT_IVS_CROSSREGIONDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_CROSSREGION_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_CROSSREGION_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_CROSSREGION_INFO);
				break;
				//4Move
			case EVENT_IVS_MOVEDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_MOVE_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_MOVE_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_MOVE_INFO);
				break;
				//5Left
			case EVENT_IVS_LEFTDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_LEFT_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_LEFT_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_LEFT_INFO);
				break;
				//6Parking
			case EVENT_IVS_PARKINGDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_PARKINGDETECTION_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_PARKINGDETECTION_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_PARKINGDETECTION_INFO);
				break;
				//7Preservation
			case EVENT_IVS_PRESERVATION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_PRESERVATION_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_PRESERVATION_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_PRESERVATION_INFO);
				break;
				//8Retro
			case EVENT_IVS_RETROGRADEDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_RETROGRADEDETECTION_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_RETROGRADEDETECTION_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_RETROGRADEDETECTION_INFO);
				break;
				//9Stay
			case EVENT_IVS_STAYDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_STAY_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_STAY_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_STAY_INFO);
				break;
				//10TakenAway
			case EVENT_IVS_TAKENAWAYDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_TAKENAWAYDETECTION_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_TAKENAWAYDETECTION_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_TAKENAWAYDETECTION_INFO);
				break;
				//11VideoAbnormal
			case EVENT_IVS_VIDEOABNORMALDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_VIDEOABNORMALDETECTION_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_VIDEOABNORMALDETECTION_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_VIDEOABNORMALDETECTION_INFO);
				break;
				//12Wander
			case EVENT_IVS_WANDERDETECTION:
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_WANDER_INFO)];
				if (!pRuleStruct->pRuleBuf)
				{
					goto ErrorHandleDispatch;
				}
				
				memcpy(&pRuleStruct->RuleInfo, pAnaRuleInfo->pRuleBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, 
					pAnaRuleInfo->pRuleBuf + nReadLen + sizeof(CFG_RULE_INFO), 
					sizeof(CFG_WANDER_INFO));
				nReadLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_WANDER_INFO);
				break;
			default:
				if (pRuleStruct)
				{
					delete pRuleStruct;
					pRuleStruct = NULL;
				}
				break;
			}

			if (pRuleStruct)
			{
				m_pRuleList[i].push_back(pRuleStruct);
			}
		}//for rule j
	}//for channel i

	return;

ErrorHandleDispatch:
	if (pRuleStruct)
	{
		if (pRuleStruct->pRuleBuf)
		{
			delete []pRuleStruct->pRuleBuf;
			pRuleStruct->pRuleBuf = NULL;
		}

		delete pRuleStruct;
		pRuleStruct = NULL;
	}

	if (pRule)
	{
		delete pRule;
		pRule = NULL;
	}

	if (m_pRuleList)
	{
		for (int i = 0; i < nChnCount; i++)
		{
			while(m_pRuleList[i].size())
			{
				RuleStruct* pRuleStr = (RuleStruct*)m_pRuleList[i].front();
				if (pRuleStr)
				{
					if (pRuleStr->pRuleBuf)
					{
						delete []pRuleStr->pRuleBuf;
						pRuleStr->pRuleBuf = NULL;
					}
				}
				m_pRuleList[i].pop_front();
			}
		}

		delete []m_pRuleList;
		m_pRuleList = NULL;
	}
}

//Callback function when device disconnected
void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser)
{
	if(0 != dwUser)
	{
		CDemoIVSPCDlg *dlg = (CDemoIVSPCDlg *)dwUser;
		if (dlg)
		{
			//dlg->DeviceDisConnect(lLoginID, pchDVRIP,nDVRPort);
			DeviceDisConnectData * pData = new DeviceDisConnectData;
			if (pData == NULL)
			{
				return;
			}
			pData->lLoginID = lLoginID;
			if (pchDVRIP != NULL)
			{
				memcpy(pData->pchDVRIP, pchDVRIP, strlen(pchDVRIP));
			}
			pData->nDVRPort = nDVRPort;
			dlg->PostMessage(WM_DISCONNECT, (WPARAM)pData, 0);
		}
		
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDemoIVSPCDlg message handlers

BOOL CDemoIVSPCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (!::CLIENT_Init(DisConnectFunc, (LDWORD)this))
	{
		::MessageBox(NULL, _T("Initialization of SDK Error!"), _T("Error"), MB_OK);
	}

	g_SetWndStaticText(this);
	
	int nSize = sizeof(CFG_CAP_ANALYSE_INFO);
	nSize = sizeof(CFG_ANALYSEGLOBAL_INFO);
	nSize = sizeof(CFG_ANALYSEMODULES_INFO);
	nSize = sizeof(CFG_ANALYSERULES_INFO);

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
	CRect rt;
	GetClientRect(&rt);
	rt.top += 26;

	m_pdlgPreview = new CPreview;
	m_pdlgPreview->Create(CPreview::IDD, this);
	m_pdlgPreview->MoveWindow(&rt, TRUE);
	m_pdlgPreview->ShowWindow(SW_SHOW);

	m_pdlgConfig = new CConfig;
	m_pdlgConfig->Create(CConfig::IDD, this);
	m_pdlgConfig->MoveWindow(&rt, TRUE);
	m_pdlgConfig->ShowWindow(SW_HIDE);

	m_pdlgQuery = new CDlgQuery;
	m_pdlgQuery->Create(CDlgQuery::IDD, this);
	m_pdlgQuery->MoveWindow(&rt, TRUE);
	m_pdlgQuery->ResizeWnd();
	m_pdlgQuery->ShowWindow(SW_HIDE);

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
		m_pdlgLogo->Create(CLogo::IDD, this);
		m_pdlgLogo->CenterWindow();
		m_pdlgLogo->ShowWindow(SW_SHOW);

		//将登陆成功的设备的地址、端口、句柄传递给主窗口
		LONG lLoginHandle = dlgLogin.GetLoginHandle();
		if (lLoginHandle)
		{
			SetLoginHandel(lLoginHandle);
		}

		m_pdlgLogo->stepIt();

		NET_DEVICEINFO* pNetDevInfo = dlgLogin.GetNetDeviceInfo();
		if (pNetDevInfo)
		{
			memcpy(&m_stuDeviceInfo, pNetDevInfo, sizeof(*pNetDevInfo));
		}

		m_pdlgLogo->stepIt();

		m_pdlgPreview->InitPreviewDlg(m_stuDeviceInfo.byChanNum);
		m_pdlgLogo->stepIt();

		m_pdlgQuery->InitQueryDlg(m_stuDeviceInfo.byChanNum);
		m_pdlgLogo->stepIt();
		EnableLoginWindow(LoginSucc);
	}
	else
	{
		SetDlgItemText(IDC_MAIN_BTN_LOGOUT, ConvertString("Login"));
		m_pdlgPreview->EnableWindow(FALSE);
		m_pdlgConfig->EnableWindow(FALSE);
		m_pdlgQuery->EnableWindow(FALSE);
		EnableLoginWindow(LoginFailed);
	}
	
	

	//////////////////////////////////////////////////////////////////////////
	//初始化配置信息结构体
	if (m_lLoginHandle)
	{
		m_nChnCount 
			= (g_MaxChannelCount >= m_stuDeviceInfo.byChanNum ? m_stuDeviceInfo.byChanNum : g_MaxChannelCount);

		//要先获得能力集，再给配置信息结构体们分配内存
		NewConfigInfo(m_nChnCount);

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

	return TRUE;  // return TRUE  unless you set the focus to a control
}




//Process when device disconnected 
LRESULT CDemoIVSPCDlg::DeviceDisConnect(WPARAM wpara, LPARAM lpara)
{
	//The codes need to be processed when device disconnected
	DeviceDisConnectData * pData = (DeviceDisConnectData*)wpara;
	if (pData)
	{
		OnMainBtnLogout();
		delete pData;
	}
	MessageBox(ConvertString("Network disconnected!"), ConvertString("Prompt"));

	return S_OK;
}



void CDemoIVSPCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoIVSPCDlg::OnPaint() 
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
HCURSOR CDemoIVSPCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoIVSPCDlg::ShowDlg(enum DlgType dlgTYPE)
{
	if (dlgTYPE == m_currentDlg)
	{
		return;
	}

	switch(dlgTYPE)
	{
	case dlgPreview:
		m_pdlgPreview->ShowWindow(SW_SHOW);
		m_pdlgConfig->ShowWindow(SW_HIDE);
		m_pdlgQuery->ShowWindow(SW_HIDE);
		m_currentDlg = dlgPreview;
		if (m_lLoginHandle)
		{
			m_pdlgPreview->ShowPreview(m_lLoginHandle, m_nCurrentChn);
		}
		break;
	case dlgConfig:
		m_pdlgPreview->ShowWindow(SW_HIDE);
		m_pdlgConfig->ShowWindow(SW_SHOW);
		m_pdlgQuery->ShowWindow(SW_HIDE);
		m_currentDlg = dlgConfig;
		if (m_lLoginHandle)
		{
			m_pdlgConfig->ShowPreview();
		}
		break;
	case dlgQuery:
		m_pdlgPreview->ShowWindow(SW_HIDE);
		m_pdlgConfig->ShowWindow(SW_HIDE);
		m_pdlgQuery->ShowWindow(SW_SHOW);
		m_currentDlg = dlgQuery;
		if (m_lLoginHandle)
		{
			m_pdlgPreview->ClosePreview(m_lRealPlayHandle);
		}
		break;
	default:
		break;
	}
}

void CDemoIVSPCDlg::OnBtnPreview() 
{
	// TODO: Add your control notification handler code here
	ShowDlg(dlgPreview);
}

void CDemoIVSPCDlg::OnBtnConfig() 
{
	// TODO: Add your control notification handler code here
	ShowDlg(dlgConfig);
}

void CDemoIVSPCDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	//先关闭画面
	if (m_lRealPlayHandle)
	{
		::CLIENT_StopRealPlay(m_lRealPlayHandle);
		m_lRealPlayHandle = 0;
		g_PlayAPI.PLAY_Stop(g_nPlayPort);
		g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
		OutputDebugString(_T("Stop RealPlay..."));
	}
	
	if (m_lLoginHandle)
	{
		::CLIENT_Logout(m_lLoginHandle);
		m_lLoginHandle = 0;
		OutputDebugString(_T("Logout..."));
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

	if (m_pdlgQuery)
	{
		if (m_pdlgQuery->GetSafeHwnd())
		{
			m_pdlgQuery->DestroyWindow();
		}
		delete m_pdlgQuery;
		m_pdlgQuery = NULL;
	}

	//最后清空配置信息
	DeleteConfigInfo();
	
}
/*
 *	登出设备按钮
 */
void CDemoIVSPCDlg::OnMainBtnLogout() 
{
	// TODO: Add your control notification handler code here
	if (m_lLoginHandle)
	{
		//登出设备，
		//关闭主窗口视频画面、报警信息，清理主窗口信息；
		if (m_lRealPlayHandle)
		{

			::CLIENT_StopRealPlay(m_lRealPlayHandle);
			m_lRealPlayHandle = 0;
			//////////////////////////////////////////////////////////////////////////
			//
			g_PlayAPI.PLAY_Stop(g_nPlayPort);
			g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			
			//////////////////////////////////////////////////////////////////////////
			Invalidate(FALSE);
		}

		if (m_lLoginHandle)
		{
			::CLIENT_Logout(m_lLoginHandle);
			m_lLoginHandle = 0;
		}

		m_nCurrentChn = -1;

		m_pdlgQuery->UninitQueryDlg();
		m_pdlgConfig->UninitConfigDlg();
		m_pdlgPreview->UninitPreviewDlg();

		//清理配置窗口信息；
		DeleteConfigInfo();    
		SetDlgItemText(IDC_MAIN_BTN_LOGOUT, ConvertString("Login"));
		m_pdlgPreview->EnableWindow(FALSE);
		m_pdlgConfig->EnableWindow(FALSE);
		m_pdlgQuery->EnableWindow(FALSE);

		EnableLoginWindow(LogOut);
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
			m_pdlgLogo->Create(CLogo::IDD, this);
			m_pdlgLogo->CenterWindow(NULL);
			m_pdlgLogo->ShowWindow(SW_SHOW);
			m_pdlgLogo->stepIt();

			LONG lLoginHandle = dlgLogin.GetLoginHandle();
			if (lLoginHandle)
			{
				m_lLoginHandle = lLoginHandle;
			}

			m_pdlgLogo->stepIt();

			NET_DEVICEINFO* pNetDevInfo = dlgLogin.GetNetDeviceInfo();
			if (pNetDevInfo)
			{
				ZeroMemory(&m_stuDeviceInfo, sizeof(m_stuDeviceInfo));
				memcpy(&m_stuDeviceInfo, pNetDevInfo, sizeof(*pNetDevInfo));
			}
			
			m_pdlgLogo->stepIt();

			//分配空间，获取设备配置信息
			m_nChnCount = (g_MaxChannelCount >= m_stuDeviceInfo.byChanNum 
									? m_stuDeviceInfo.byChanNum : g_MaxChannelCount);
			NewConfigInfo(m_nChnCount);

			//初始化子窗口
			m_pdlgPreview->InitPreviewDlg(m_stuDeviceInfo.byChanNum);
			m_pdlgLogo->stepIt();

			m_pdlgQuery->InitQueryDlg(m_stuDeviceInfo.byChanNum);
			m_pdlgLogo->stepIt();
			SetDlgItemText(IDC_MAIN_BTN_LOGOUT, ConvertString("Logout"));
			m_pdlgPreview->EnableWindow(TRUE);
			m_pdlgConfig->EnableWindow(TRUE);
			m_pdlgQuery->EnableWindow(TRUE);

			m_pdlgLogo->stepIt();

			if (m_pdlgLogo)
			{
				if (m_pdlgLogo->GetSafeHwnd())
				{
					m_pdlgLogo->DestroyWindow();
				}
				delete m_pdlgLogo;
				m_pdlgLogo = NULL;
			}
			EnableLoginWindow(LoginSucc);
		}
	}
	OnBtnPreview();
}


void CDemoIVSPCDlg::OnBnClickedMainBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowDlg(dlgQuery);
}
