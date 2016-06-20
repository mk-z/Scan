   // NetSDKDemoDlg.cpp : implementation file

#include "StdAfx.h"
#include "NetSDKDemo.h"
#include "NetSDKDemoDlg.h"
#include "splitinfodlg.h"
#include "adddevicedlg.h"
#include "searchrecord.h"
#include "systemconfig.h"
#include "extptzctrl.h"
#include "ptzmenu.h"
#include "transcom.h"
#include "recordctrldlg.h"
#include "deviceworkstate.h"
#include "alarmctrldlg.h"
#include "cyclemonitor.h"
//#include "systemcfg.h"
#include "direct.h"
#include "playbackbytime.h"
#include "downloadbytime.h"
#include "NetUpgrade.h"
#include "DDNS_QueryIP.h"
#include "DiskControl.h"
#include "usermanage.h"
#include "configmaindlg.h"
#include "PreviewParmsDlg.h"
#include "automaintenance.h"

/*
/////////////////////////////////////////
//console
////////////////////////////////////////
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
*/


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// #pragma data_seg("sharesec")
// __declspec (allocate("sharesec")) HWND g_share_hWnd = NULL;
// #pragma comment(linker,"/SECTION:sharesec,RWS")

#define ALARMLOG	0x1099
#define UPDATATREE	0x2000

BOOL	g_bUpdataTree = FALSE;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

/*

using namespace std;

static const WORD MAX_CONSOLE_LINES = 500;

void RedirectIOToConsole()
{
	int hConHandle;
	long lStdHandle;
	
	CONSOLE_SCREEN_BUFFER_INFO coninfo; // 控制台信息
	FILE *fp;
	
	// allocate a console for this app
	AllocConsole();  // 打开一个控制台
	
	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	
	// 设置控制台参数
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(
		GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
	
	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE); 
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT); 
	
	fp = _fdopen(hConHandle, "w" );
	*stdout = *fp; // 为全局c变量stdout赋值，使用自己打开的控制台.
	setvbuf(stdout, NULL, _IONBF, 0);
	
	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);
	
	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);
	
	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
	// point to console as well
	ios::sync_with_stdio();
}
*/

inline void dbg_print_ex(int level, const char *msg, ...)
{
	char buf[256];
	
	va_list ap;
	va_start(ap, msg); // use variable arg list
	vsprintf(buf, msg, ap);
	va_end( ap );
}

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
	virtual BOOL OnInitDialog();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetSDKDemoDlg dialog

CNetSDKDemoDlg::CNetSDKDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetSDKDemoDlg::IDD, pParent)
{
	m_connectwaittime = 3000;
	m_myBrush.CreateSolidBrush(RGB(255,255,255));
	//{{AFX_DATA_INIT(CNetSDKDemoDlg)
	m_play_frame = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = 0;//AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetSDKDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetSDKDemoDlg)
	DDX_Control(pDX, IDC_TREE_DEVICELIST, m_devicelist);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNetSDKDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CNetSDKDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_DEVICELIST, OnDblclkTreeDevicelist)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////初始化回调相关的函数////////////////////////////////////////////////
//设备断开时回调函数，可以用来处理断开后设备列表的更新及设备的删除操作
void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CNetSDKDemoDlg *dlg = (CNetSDKDemoDlg *)dwUser;
	dlg->DeviceDisConnect(lLoginID, pchDVRIP,nDVRPort);
}

//设备断开处理
void CNetSDKDemoDlg::DeviceDisConnect(LONG lLoginID, char *sDVRIP,LONG nDVRPort)
{
	CDevMgr::GetDevMgr().ModifyNode(lLoginID, FALSE);

	g_bUpdataTree = TRUE;

	return;




	DeviceNode node;
	int r = CDevMgr::GetDevMgr().GetDev(lLoginID, node);
	if (r < 0)
	{
		return ;
	}

	/*
	DeviceNode *nDev=(DeviceNode *)FindDeviceInfo(lLoginID, sDVRIP,nDVRPort);
	if(nDev == NULL)
	{
		return;
	}
	*/
	CString nStr;
	nStr.Format("%s ",node.IP);
	nStr = nStr + ConvertString(MSG_DEVICE_DISCONNECT);

	ProcessDeleteDevice(&node, true, true);
	UpdateDeviceList();
	UpdateCurScreenInfo();
	
	MessageBox(nStr);
	UpdateScreen(m_normalBtnPannel.GetSplit());
//	Invalidate(true);
}

void CALLBACK HaveReconnFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CNetSDKDemoDlg *dlg = (CNetSDKDemoDlg *)dwUser;
	dlg->DeviceReConnect(lLoginID, pchDVRIP,nDVRPort);
}

void CNetSDKDemoDlg::DeviceReConnect(LONG lLoginID, char *sDVRIP,LONG nDVRPort)
{
	CDevMgr::GetDevMgr().ModifyNode(lLoginID, TRUE);

	UpdateDeviceList();

	return;
}

//消息回调处理函数,是对整个sdk应用的回调
BOOL CALLBACK MessCallBack(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, 
						   char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(!dwUser) return FALSE;

	CNetSDKDemoDlg *dlg = (CNetSDKDemoDlg *)dwUser;
	return dlg ->ReceiveMessage(lLoginID, lCommand, pchDVRIP, nDVRPort,pBuf, dwBufLen);
}

//接收到设备消息的处理,目前只定义了报警消息回调
BOOL CNetSDKDemoDlg::ReceiveMessage(LONG lLoginID, LLONG lCommand, char *pchDVRIP, LONG nDVRPort, 
		char *pBuf, LDWORD dwBufLen)
{
//	EnterCriticalSection(&g_csAlarm);
//	CCSLock lk(g_cs);
/*
		if (!m_bShowStatus) 
		{
			return false;
		}*/
	int nRet = CDevMgr::GetDevMgr().SetAlarmInfo(lLoginID, lCommand, pchDVRIP, nDVRPort, 
		pBuf, dwBufLen);
	return nRet<0?FALSE:TRUE;
/*
	DeviceNode node;
	int r = CDevMgr::GetDevMgr().GetDev(lLoginID, node);
	if (r < 0)
	{
		LeaveCriticalSection(&g_csAlarm);
		return false;
	}

	DeviceNode *nDev = &node;

	DeviceNode *nDev = (DeviceNode *)FindDeviceInfo(lLoginID, pchDVRIP,nDVRPort );
	
	if(nDev == NULL)
	{
		goto e_exit;
	}
	

	switch(lCommand) {
	case COMM_ALARM:
	{
	 
					NET_CLIENT_STATE *ClientState = (NET_CLIENT_STATE *)pBuf;
					
					if(ClientState == NULL)
					{
						return FALSE;
					}
					
					printf("alarm infomation:\n");
					
					CString str;
					
					for(int i=0; i<ClientState->channelcount; i++)
					{
						CString strTemp;
						strTemp.Format("%d ", ClientState->record[i]);
						str += strTemp;
					}
					
					printf("alarm: Recording Status-- %s\n", str.GetBuffer(0));
					
					for(i=0; i<ClientState->alarminputcount; i++)
					{
						CString strTemp;
						strTemp.Format("%d ", ClientState->alarm[i]);
						str += strTemp;
					}
					
					printf("alarm: Extern Alarm-- %s\n", str.GetBuffer(0));
					
					
					for(i=0; i<ClientState->channelcount; i++)
					{
						CString strTemp;
						strTemp.Format("%d ", ClientState->motiondection[i]);
						str += strTemp;
					}
					
					printf("alarm: Motion Detect-- %s\n", str.GetBuffer(0));
					
					for(i=0; i<ClientState->channelcount; i++)
					{
						CString strTemp;
						strTemp.Format("%d ", ClientState->videolost[i]);
						str += strTemp;
					}
					
					printf("alarm: Video Lost-- %s\n", str.GetBuffer(0));
		
		}
		UpdateDeviceState(nDev, pBuf, dwBufLen);
		//m_ClientStateDlg.UpdateState(nDev,pBuf, dwBufLen);
		if(!m_ClientStateDlg.m_isNoMoreShow)
		{
			m_ClientStateDlg.ShowWindow(SW_SHOW);
		}
		break;
	default : 
		goto e_exit;
	}

//	LeaveCriticalSection(&g_csAlarm);
	return true;
e_exit:
//	LeaveCriticalSection(&g_csAlarm);
	return false;
	*/
/*

	DeviceNode *nDev = (DeviceNode *)FindDeviceInfo(lLoginID, pchDVRIP,nDVRPort );

	if(nDev == NULL)
	{
		m_bShowStatus = FALSE;
		return false;
	}
	switch(lCommand) {
	case COMM_ALARM:
		UpdateDeviceState(nDev, pBuf, dwBufLen);
		m_ClientStateDlg.UpdateState(nDev,pBuf, dwBufLen);
		if(!m_ClientStateDlg.m_isNoMoreShow)
		{
			m_ClientStateDlg.ShowWindow(SW_SHOW);
		}
		break;
	default : 
		m_bShowStatus = FALSE;
		return false;
	}
	m_bShowStatus = FALSE;
	return true;*/

}

//自定义画板回调,可以用来显示通道信息
void CALLBACK ChannelAutoDraw(LLONG lLoginID, LLONG lPlayHandle, HDC hDC, LDWORD dwUser)
{
	if(!dwUser) return;

	CNetSDKDemoDlg *dlg = (CNetSDKDemoDlg *)dwUser;
	dlg->AddDisplayInfo(lLoginID, lPlayHandle, hDC);
}

//叠加字符或图片
void CNetSDKDemoDlg::AddDisplayInfo(LONG lLoginID, LONG lPlayHandle, HDC hDC)
{
	DeviceNode *pDev;
	CString str;

	//取得窗口号
	int i = GetHandleSplit(lPlayHandle);
	if(i < 0)
	{
		return;
	}

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(i, &siNode);
	if (!ret)
	{
		return;
	}

	switch(siNode.Type) 
	{
	case SPLIT_TYPE_MONITOR:
		{
			SplitMonitorParam *mParam = (SplitMonitorParam *)siNode.Param;
			if (mParam)
			{
				pDev = mParam->pDevice;
				str.Format(" %s[%s] %02d", pDev->Name,pDev->IP, mParam->iChannel + 1);
				str = ConvertString(MSG_DEMODLG_MONITOR) + str;
			//	for(int j = 0; j < pDev->State.channelcount; j++)
			//	{
				//	if(pDev->State.motion[mParam->iChannel])
					if(pDev->State.cState.motiondection[mParam->iChannel])
					{
						CString almstr;
						almstr.Format(ConvertString("! ALARM !"));
						SetTextColor(hDC, RGB(255,0,0));
						CRect rect;
						//m_playWnd[i].GetClientRect(&rect);
						CWnd* pWnd = m_screenPannel.GetPage(i);
						if (!pWnd)
						{
							MessageBox(ConvertString("unexpected error!!"));
						}
						pWnd->GetClientRect(&rect);
						if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
						{
							TextOut(hDC, rect.right / 3, rect.bottom / 2, almstr.GetBuffer(0), almstr.GetLength());
						}
					//	break;
					}
			//	}
			}
		}
		break;
	case SPLIT_TYPE_MULTIPLAY:
		pDev = (DeviceNode *)siNode.Param;
		str.Format(" %s[%s]", pDev->Name,  pDev->IP);
		str = ConvertString(MSG_DEMODLG_PREVIEW) + str;
		break;

	case SPLIT_TYPE_NETPLAY:
		{
			SplitNetPlayParam *nParam = (SplitNetPlayParam *)siNode.Param; 
			pDev = nParam->pFileInfo->pDevice;
			str.Format(" %s[%s]%02d", pDev->Name, pDev->IP, 
				nParam->pFileInfo->fileinfo.ch + 1);
			str = ConvertString(MSG_DEMODLG_PLAYBACKCHL) + str;
		}
		break;
	case SPLIT_TYPE_PBBYTIME:
		{
			break;
		}
	case SPLIT_TYPE_CYCLEMONITOR:
		{
			SplitCycleParam *cParam = (SplitCycleParam *)siNode.Param;
			CycleChannelInfo *cci = 0;
			POSITION pos = cParam->pChannelList->GetHeadPosition();
			for (int counter = 0; counter <= cParam->iCurPosition; counter++)
			{
				cci = (CycleChannelInfo *)cParam->pChannelList->GetNext(pos);
			}
			pDev = (DeviceNode *)cci->dwDeviceID;
			str.Format(" %s[%s](%02d)", pDev->Name, pDev->IP, cci->iChannel + 1);
			str = ConvertString(MSG_DEMODLG_CYCLEMONITOR) + str;
			break;
		}
	default :
		return;
	}

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255,255,0));
	TextOut(hDC, 0, 0, str.GetBuffer(0), str.GetLength());
	
}
// CNetSDKDemoDlg message handlers
BOOL CNetSDKDemoDlg::OnInitDialog()
{
//	RedirectIOToConsole();
// 	if(g_share_hWnd)
// 	{
// 		AfxMessageBox(_T("Only one process allowed"));
// 		CWnd* pWnd = CWnd::FromHandle(g_share_hWnd);
// 		if(pWnd)
// 		{
// 			if (pWnd->IsIconic())
// 			{
// 				pWnd->ShowWindow(SW_RESTORE);
// 			}
// 			pWnd->SetForegroundWindow(); 
// 		}
// 		exit(0);
// 	}
// 	else
// 	{
// 		g_share_hWnd = m_hWnd;
// 	}

	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	Getversion();
	char tmpDir[1000];
	_getcwd(tmpDir, 1000);
	g_strWorkDir.Format("%s", tmpDir);

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
	
	//初始化网络sdk,所有调用的开始
	BOOL ret = CLIENT_Init(DisConnectFunc, (DWORD)this);
	if (!ret)
	{
		LastError();
	}

	//设置断线重连
	CLIENT_SetAutoReconnect(HaveReconnFunc, (DWORD)this);

	//设置信息回调函数,默认接收所有设备信息
	CLIENT_SetDVRMessCallBack(MessCallBack, (DWORD)this);

	//初始化各子窗口

	m_selectPannel.Create(IDD_PANNEL_SELECT, this);
	//m_screenPannel.Create(IDD_PANNEL_SCREEN, this);
	m_screenPannel.Create(
		NULL,
		NULL,
		WS_CHILD|WS_VISIBLE, 
		CRect(0,0,0,0), 
		this, 
		1981);
	m_saveDataPannel.Create(IDD_PANNEL_SAVEDATA, this);
	m_colorPannel.Create(IDD_PANNEL_COLOR, this);
	m_playctrlPannel.Create(IDD_PANNEL_PLAYCTRL, this);
	m_normalBtnPannel.Create(IDD_PANNEL_NORMAL_BTN, this);
	m_advanceBtnPannel.Create(IDD_PANNEL_ADVANCE_BTN, this);
	m_ptzPannel.Create(IDD_PANNEL_PTZ, this);
	m_runtimeMsgPannel.Create(IDD_PANNEL_RUNTIME_MSG, this);

	UpdatePannelPosition();

	m_selectPannel.ShowWindow(SW_SHOW);
	m_screenPannel.ShowWindow(SW_SHOW);
	m_saveDataPannel.ShowWindow(SW_HIDE);
	m_colorPannel.ShowWindow(SW_HIDE);
	m_playctrlPannel.ShowWindow(SW_HIDE);
	m_devicelist.ShowWindow(SW_SHOW);
	m_advanceBtnPannel.ShowWindow(SW_HIDE);
	m_ptzPannel.ShowWindow(SW_HIDE);
	m_runtimeMsgPannel.ShowWindow(SW_SHOW);
	
	//初始化画面分割模式选择项
	m_normalBtnPannel.InitSplit(CUR_SPLIT);	
	m_normalBtnPannel.ShowWindow(SW_SHOW);

	m_curScreen = 0;
	m_screenPannel.SetShowPlayWin(CUR_SPLIT, m_curScreen);

	//设置连接等待时间
	CLIENT_SetConnectTime(m_connectwaittime, 3);
	LastError();  
	
	CLIENT_RigisterDrawFun(ChannelAutoDraw, (DWORD)this);
	LastError();  

//	for (int j = 0; j < CUR_MAXCHAN; j++)
//	{
//		m_playWnd[j].Create(IDD_CHILD_PLAYWND, &m_screenPannel);//can't input this point,may be input 
//		m_playWnd[j].SetWinID(j);
//	}

//	m_originParent = 0;
//	m_bFullSCRN = FALSE;
	

	//初始化关闭声音
	m_curSoundSplit = -1;
	
	//创建状态页面和系统配置页面
	m_ClientStateDlg.Create(IDD_CLIENT_STATE);
	m_ClientStateDlg.CenterWindow();
	m_ClientStateDlg.m_isNoMoreShow = TRUE;
	m_ClientStateDlg.UpdateData(false);

	//初始化云台控制状态
	m_bPTZCtrl = FALSE;

	//刷新界面信息
	UpdateScreen(CUR_SPLIT+1);
	UpdateCurScreenInfo();

	/*Begin: Add by yehao(10857) For Task.NO.11071 2006-12-23*/
	m_broadcastDevList.clear();
	m_bRecord = FALSE;
	memset((void *)&m_talkhandle, 0, sizeof(TalkHandleInfo));
	m_uRecordCount = 0;
	/*End: yehao(10857) Task.NO.11071 */
	//目前还没实现的功能
//	GetDlgItem(IDC_UPDATECPROCESS)->EnableWindow(false);
//	GetDlgItem(IDC_SETIFRAME)->EnableWindow(false);
//	GetDlgItem(IDC_DEVICE_WORKSTATE)->EnableWindow(false);
	//设置系统秒定时器,用于刷新码流统计和进度条并更新客户端信息
//	m_bShowStatus = FALSE;
//	SetTimer(TIMER_KBPS, 1111,NULL);
	
#ifdef DH_STREAMPARSER
	m_hSp = DHSP_Init(0 , 0, 1);
	m_spFile = 0;
	m_bGetIFrame = FALSE;
	m_framecount = 0;
#endif

	//download test
	m_dbByTime.Create(IDD_DOWNLOADBYTIME, this);

	//specified alarm test
	ZeroMemory(&m_lastAlarm, sizeof(DEV_STATE));
	CString strAlmLogPath = g_strWorkDir + "\\AlarmLog_comm.txt";
	m_almLogFile_Comm = fopen(strAlmLogPath, "w+");
	strAlmLogPath = g_strWorkDir + "\\AlarmLog_shelter.txt";
	m_almLogFile_Shelter = fopen(strAlmLogPath, "w+");
	strAlmLogPath = g_strWorkDir + "\\AlarmLog_diskFull.txt";
	m_almLogFile_dFull = fopen(strAlmLogPath, "w+");
	strAlmLogPath = g_strWorkDir + "\\AlarmLog_diskError.txt";
	m_almLogFile_dError = fopen(strAlmLogPath, "w+");
	strAlmLogPath = g_strWorkDir + "\\AlarmLog_soundAlarm.txt";
	m_almLogFile_SoundDec = fopen(strAlmLogPath, "w+");
	if (m_almLogFile_Comm && m_almLogFile_Shelter && m_almLogFile_dFull
		&& m_almLogFile_dError && m_almLogFile_SoundDec)
	{
		SetTimer(ALARMLOG, 1000, NULL);
	}

	SetTimer(UPDATATREE, 1000, NULL);

	//listen device test
	m_lListenDevice = 0;
	m_lListenChannel = 0;
	memset(&m_mylsdata, 0 , sizeof(m_mylsdata));

	return TRUE;
}

void CNetSDKDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNetSDKDemoDlg::OnPaint() 
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
HCURSOR CNetSDKDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

////////////////////////////////内部使用小接口函数///////////////////////////////////////////////////
//根据登录ID获取设备信息指针
void *CNetSDKDemoDlg::FindDeviceInfo(LONG lLoginID, char *sDVRIP,LONG nDVRPort)
{
	/*
	POSITION nPos;
	DeviceNode *pInfo;

	nPos = g_ptrdevicelist->GetHeadPosition();
	for(int i = 0; i < g_ptrdevicelist->GetCount(); i ++ )
	{
		pInfo = (DeviceNode *)g_ptrdevicelist->GetNext(nPos);
		if(pInfo->LoginID == lLoginID)
		{
			return pInfo;
		}
	}
	*/
	return NULL;	
}

//获取当前设备列表中选择的设备信息指针
void *CNetSDKDemoDlg::GetCurDeviceInfo()
{
	HTREEITEM node;
	DWORD nData;

	node = m_devicelist.GetSelectedItem();

	if(!node)
	{
		MessageBox(ConvertString(MSG_DEMODLG_CHECKSEL));
		return NULL;
	}
	
	nData = m_devicelist.GetItemData(node);
	if(nData < 2048/*256*/)    //通道选项，取得父项
	{
		node = m_devicelist.GetParentItem(node);
	}

	return (void *)m_devicelist.GetItemData(node);  //父项记录的数据为设备的信息指针值
}

//根据句柄获取播放窗口序号,其中句柄可以是监视通道Id,播放Id,预览id等
int CNetSDKDemoDlg::GetHandleSplit(LONG lPlayHandle)
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	for(int i = 0; i < DH_MAX_CHANNUM; i++)
	{
		if (!GetSplitInfo_Main(i, &siNode))
		{
			return -1;
		}

		if(siNode.Type != SPLIT_TYPE_NULL)
		{
			if(siNode.iHandle == (DWORD)lPlayHandle)
			{
				return i;
			}
		}
	}
	return -1;
} 

//获取当前画面分割模式的指定画面的起始画面序号
int  CNetSDKDemoDlg::GetCurSplitStart(int nScreen, int nSplit)
{
	return -1;
	/*
	//设置到对应画面的单画面
	int nScreenStart = 0;

	if(nScreen >= nSplit * nSplit)  
	{
		nScreenStart = m_curScreen/(nSplit * nSplit)*(nSplit * nSplit);
	}
	//当当前画面选择通道序号大于16时更改选择通道
	//例如当前画面序号时10时,显示9画面,则显示7~16通道;
	if((nScreenStart + nSplit * nSplit) >= CUR_MAXCHAN)
	{
		nScreenStart = CUR_MAXCHAN - nSplit * nSplit;
	} 
	return nScreenStart;
	*/

}

//检测当前画面状态并关闭当前状态
BOOL CNetSDKDemoDlg::CheckCurSplitAndClose()
{	
	ProcessCloseScreen(m_curScreen);
	UpdateCurScreenInfo();
	return TRUE;
}

//检测当前选择通道是否在某个轮循列表中
BOOL CNetSDKDemoDlg::IsCycling(DWORD deviceID, int channelNo)
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));

	for (int i = 0; i < DH_MAX_CHANNUM; i++)
	{
		BOOL ret = GetSplitInfo_Main(i, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while getting split information"));
			return TRUE;
		}
		
		if (siNode.Type == SPLIT_TYPE_CYCLEMONITOR) 
		{
			POSITION pos = ((SplitCycleParam *)siNode.Param)->pChannelList->GetHeadPosition();
			for (int j = 0; j < ((SplitCycleParam *)siNode.Param)->pChannelList->GetCount(); j++)
			{
				CycleChannelInfo *tempnode;
				tempnode = (CycleChannelInfo *)((SplitCycleParam *)siNode.Param)->pChannelList->GetNext(pos);
				if ((tempnode->dwDeviceID == deviceID) && (tempnode->iChannel == channelNo)) 
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void CNetSDKDemoDlg::DeleteCycleParam(int nScreen)
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(nScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	int count;
	count = ((SplitCycleParam *)siNode.Param)->pChannelList->GetCount();
	for (int i = 0; i < count; i++)
	{
		delete (CycleChannelInfo *)((SplitCycleParam *)siNode.Param)->pChannelList->GetTail();
		((SplitCycleParam *)siNode.Param)->pChannelList->RemoveTail();
	}
	delete ((SplitCycleParam *)siNode.Param)->pChannelList;
	delete (SplitCycleParam *)siNode.Param;
	siNode.Type = SPLIT_TYPE_NULL;
	siNode.Param = NULL;
	ret = SetSplitInfo_Main(nScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while setting split info"));
	}
	
	CPlayWnd *plWnd = (CPlayWnd *)m_screenPannel.GetPage(nScreen);
	if (plWnd)
	{
		plWnd->PostMessage(VIDEO_REPAINT);
	}
}

//关闭画面的显示状态
BOOL CNetSDKDemoDlg::ProcessCloseScreen(int scrNo, BOOL bDis) 
{
	BOOL ret = TRUE;

//	EnterCriticalSection(&g_cs);
//	CCSLock lck(g_cs);

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	ret = GetSplitInfo_Main(scrNo, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return FALSE;
	}

	switch(siNode.Type) 
	{
	case SPLIT_TYPE_MONITOR:
		{
	//	ret = CLIENT_StopRealPlay(siNode.iHandle);
		ret = CLIENT_StopRealPlayEx(siNode.iHandle);
		if (!ret) 
		{
			LastError();
			if (!bDis) 
			{
				MessageBox(ConvertString(MSG_CYCLE_STOPMONITORERROR));
			}
		}
		delete (SplitMonitorParam *)siNode.Param;
		siNode.Param = NULL;
		siNode.Type = SPLIT_TYPE_NULL;
		ret = SetSplitInfo_Main(scrNo, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while getting split info"));
		}
		CPlayWnd *plWnd = (CPlayWnd *)m_screenPannel.GetPage(scrNo);
		if (plWnd)
		{
			plWnd->PostMessage(VIDEO_REPAINT);
		}
		break;
		}
		
	case SPLIT_TYPE_MULTIPLAY:
		{
	//	ret = CLIENT_StopMultiPlay(siNode.iHandle);
		ret = CLIENT_StopRealPlayEx(siNode.iHandle);
		if (!ret)
		{
			LastError();
			if (!bDis) 
			{
				MessageBox(ConvertString(MSG_CYCLE_STOPMULTIPLAYERROR));
			}
		}
		siNode.Param = NULL;
		siNode.Type = SPLIT_TYPE_NULL;
		ret = SetSplitInfo_Main(scrNo, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while getting split info"));
		}
		m_advanceBtnPannel.EnableTalk(TRUE);
		CPlayWnd *plWnd = (CPlayWnd *)m_screenPannel.GetPage(scrNo);
		if (plWnd)
		{
			plWnd->PostMessage(VIDEO_REPAINT);
		}
		break;
		}
		
	case SPLIT_TYPE_NETPLAY:		
	case SPLIT_TYPE_PBBYTIME:
		{
			int nRet = PlayStop(scrNo, bDis);
			if (nRet < 0)
			{
				ret = FALSE;
			}
			else
			{
				ret = TRUE;
			}
			break;
		}
		
	case SPLIT_TYPE_CYCLEMONITOR:
		{
		//仅用于“关闭”指令，删除与断开设备有另外的代码。
		KillTimer(scrNo);
//		EnterCriticalSection(&g_csCycle);
		ret = CLIENT_StopRealPlay(siNode.iHandle);
		if (!ret) 
		{
			LastError();
			MessageBox(ConvertString(MSG_CYCLE_STOPCYCLEERROR));
		}
		if (siNode.Param) 
		{
			DeleteCycleParam(scrNo);
		}
//		LeaveCriticalSection(&g_csCycle);
		break;
		}
	default:
		break;
	}

//	LeaveCriticalSection(&g_cs);
	return ret;
}


int UpdateDeviceListCallback(const DeviceNode& node, DWORD dwUser)
{
	CNetSDKDemoDlg* pThis = (CNetSDKDemoDlg*)dwUser;
	if (!pThis)
	{
		return 1;
	}

	return pThis->UpdateDeviceListCallback_Imp(node);
}

int CNetSDKDemoDlg::UpdateDeviceListCallback_Imp(const DeviceNode& node)
{
	CString strDev, strCh;	
	HTREEITEM hnode, hnode1;
	CString strDevType;
	switch(node.Info.byDVRType)
	{
	case NET_DVR_MPEG4_SX2:
		strDevType.Format("LB");
		break;
	case NET_DVR_MEPG4_ST2:
		strDevType.Format("GB");
		break;
	case NET_DVR_MEPG4_SH2:
		strDevType.Format("HB");
		break;
	case NET_DVR_ATM:
		strDevType.Format("ATM");
		break;
	case NET_DVR_NONREALTIME:
		strDevType.Format("NRT");
		break;
	case NET_DVR_MPEG4_NVSII:
		strDevType.Format("NVS");
		break;
	case NET_NB_SERIAL:
		strDevType.Format("NB");
		break;
	case NET_LN_SERIAL:
		strDevType.Format("LN");
		break;
	case NET_BAV_SERIAL:
		strDevType.Format("BAV");
		break;
	case NET_SDIP_SERIAL:
		strDevType.Format("EIVS");
		break;
	case NET_IPC_SERIAL:
		strDevType.Format("IPC");
		break;
	case NET_NVS_B:
		strDevType.Format("NVS B");
		break;
	case NET_NVS_C:
		strDevType.Format("NVS H");
		break;
	case NET_NVS_S:
		strDevType.Format("NVS S");
		break;
	case NET_NVS_E:
		strDevType.Format("NVS E");
		break;
	case NET_DVR_NEW_PROTOCOL:
		strDevType.Format("DVR");
		break;
	case NET_NVD_SERIAL:
		strDevType.Format("NVD");
		break;
	case NET_DVR_N5:
		strDevType.Format("N5");
		break;
	case NET_DVR_MIX_DVR:
		strDevType.Format("HDVR");
		break;
	case NET_SVR_SERIAL:
		strDevType.Format("SVR");
		break;
	case NET_SVR_BS:
		strDevType.Format("SVR-BS");
		break;
	case NET_NVR_SERIAL:
		strDevType.Format("NVR");
		break;
	case NET_DVR_N51:
		strDevType.Format("N51");
		break;
	case NET_DVR_N52:
		strDevType.Format("N52");
		break;
	case NET_ESS_SERIAL:
		strDevType.Format("ESS");
		break;
	case NET_IVS_PC:
		strDevType.Format("IVS-PC");
		break;
	case NET_PC_NVR:
		strDevType.Format("PC_NVR");
		break;
	case NET_DSCON:
		strDevType.Format("DSCON");
		break;
	case NET_EVS:
		strDevType.Format("EVS");
		break;
	case NET_EIVS:
		strDevType.Format("EIVS");
		break;
    case NET_MATRIX_SERIAL:
        strDevType.Format("MATRIX");
        break;
	case NET_ITC_SERIAL:
		strDevType.Format("ITC");
		break;
	default:
		strDevType.Format("??");
	}
	strDev.Format(" %s (%s)<%s>",node.Name, node.IP, strDevType.GetBuffer(0));
	if (node.bIsOnline)
	{
		strDev = strDev + ConvertString("(on-line)");
	}
	else
	{
		strDev = strDev +ConvertString("(off-line)");
	}
	hnode = m_devicelist.InsertItem(strDev,0,0,TVI_ROOT);
	//设备项直接将设备信息指针作为列表Id
	m_devicelist.SetItemData(hnode,(DWORD)&node);		
    int nTotalChnNum = __max(node.nChnNum, node.Info.byChanNum);
	for(int j = 0; j < nTotalChnNum; j++)
	{
		strCh.Format(ConvertString("channel %02d"),j+1);

		hnode1 = m_devicelist.InsertItem(strCh,0,0,hnode);
		//通道项将通道序号作为列表ID
		m_devicelist.SetItemData(hnode1,j);
	}	

	return 0;
}


////////////////////////////////刷新显示相关的接口函数//////////////////////////////////////////
//刷新设备列表显示，直接根据g_ptrdevicelist重新刷新显示
void CNetSDKDemoDlg::UpdateDeviceList()
{
	/*
	DeviceNode *nDev;
	HTREEITEM node, node1;
	CString strDev, strCh;	
	POSITION nPos;
	*/

	m_devicelist.DeleteAllItems(); 

	CDevMgr::GetDevMgr().For_EachDev(UpdateDeviceListCallback, (DWORD)this);

	if (m_devicelist.GetCount() > 0)
	{
		m_devicelist.SetFocus();
	}
	/*
	nPos = g_ptrdevicelist->GetHeadPosition();
	for(int i = 0; i < g_ptrdevicelist->GetCount(); i ++ )
	{
		nDev = (DeviceNode *)g_ptrdevicelist->GetNext(nPos);

		strDev.Format(" %s (%s)<%s>",nDev->Name, nDev->IP, nDev->UserNanme);
		node = m_devicelist.InsertItem(strDev,0,0,TVI_ROOT);
		//设备项直接将设备信息指针作为列表Id
		m_devicelist.SetItemData(node,(DWORD)nDev);		

		for(int j = 0; j < nDev->Info.byChanNum; j++)
		{
			strCh.Format("channel %02d",j+1);

			node1 = m_devicelist.InsertItem(strCh,0,0,node);
			//通道项将通道序号作为列表ID
			m_devicelist.SetItemData(node1,j);
		}		
	}
	*/

}

//画面分割刷新显示
void CNetSDKDemoDlg::UpdateScreen(int nSplit)
{
	//m_screenPannel.SetShowPlayWin(nSplit, 0);
	/*
	int k;
	int spWide, spHight;    //分割大小

	CRect nRect;
	CRect subRect;

//	Invalidate();

	
	m_screenPannel.GetClientRect(&nRect);
	if (!m_bFullSCRN)
	{	
		m_screenPannel.ClientToScreen(&nRect);
		ScreenToClient(&nRect);
	}
	

	
	//处理为可以对任何画面显示在各种画面
	int nScreenStart = GetCurSplitStart(m_curScreen,nSplit);
	
	//隐藏所有画面
	for(k = 0 ; k < CUR_MAXCHAN; k++)
	{
		m_playWnd[k].ShowWindow(SW_HIDE);
	}

	//确定每个分割项大小
	spWide = nRect.Width()/nSplit;
	spHight = nRect.Height()/nSplit;

	//确定各分割项位置，并显示//CListBox
	int offsplit;
	for(int i = 0; i < nSplit; i++)
	{
		for(int j = 0; j < nSplit; j ++)
		{
			subRect.left = nRect.left + j * spWide+1;
			subRect.top = nRect.top + i * spHight+1;
			
			subRect.right = subRect.left + spWide - 1;
			subRect.bottom = subRect.top + spHight - 1;
			offsplit = nScreenStart + i * nSplit + j;

		//	m_playWnd[offsplit].ShowWindow(SW_HIDE);
			m_playWnd[offsplit].MoveWindow(&subRect,false);
		//	m_playWnd[offsplit].ShowWindow(SW_NORMAL);

			//当是当前选择分割项时，叠加显示外框
			if(offsplit == m_curScreen)
			{
				CRect rect;

				rect.left = subRect.left + 1;
				rect.top = subRect.top + 1;
				rect.right = subRect.right + 1;
				rect.bottom = subRect.bottom + 1;
				
				GetDlgItem(IDC_CURWIN)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CURWIN)->MoveWindow(&rect,false);
				GetDlgItem(IDC_CURWIN)->ShowWindow(SW_NORMAL);
			}
		}
	}

	//显示有效的分割画面
	for(k = nScreenStart ; k < nScreenStart + nSplit * nSplit ; k++)
	{
		m_playWnd[k].ShowWindow(SW_SHOW);
	}
	*/
}

//刷新当前显示画面的相关信息
void CNetSDKDemoDlg::UpdateCurScreenInfo()
{
	//判断是否打开了语音对讲
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));

/*	BOOL bTalkOpen = FALSE;
	for (int i  = 0; i < MAX_CHANNUM; i++)
	{
		BOOL ret = GetSplitInfo_Main(i, &siNode);
		if (!ret)
		{
			MessageBox("error while getting split info");
			return;
		}
		
		if (siNode.Type == SPLIT_TYPE_MONITOR)
		{
			if (((SplitMonitorParam *)(siNode.Param))->isTalkOpen) 
			{
				bTalkOpen = TRUE;
				break;
			}
		}
	}

	m_normalBtnPannel.EnableMultiplay(!bTalkOpen);
	*/

	//更新保存数据项和音频项
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	m_saveDataPannel.SetCheckReal(siNode.isSaveData);
	m_saveDataPannel.SetCheckRaw(siNode.SavecbFileRaw ? 1 : 0);
	m_saveDataPannel.SetCheckStd(siNode.SavecbFileStd ? 1 : 0);
	m_saveDataPannel.SetCheckYuv(siNode.SavecbFileYUV ? 1 : 0);
	m_saveDataPannel.SetCheckPcm(siNode.SavecbFilePcm ? 1 : 0);

	m_advanceBtnPannel.SetCheckSound(m_curSoundSplit == m_curScreen ? 1 : 0);

	//更新视频参数项
	UpdateVideoCtrl(VIDEO_TOTAL);
	
	/*
	if (siNode.Type == SPLIT_TYPE_MONITOR &&
		((SplitMonitorParam *)siNode.Param)->isTalkOpen)
	{
		m_advanceBtnPannel.SetCheckTalk(1);
	}
	else
	{
		m_advanceBtnPannel.SetCheckTalk(0);
	}
	*/
}

//刷新视频参数控制区,nMode 0~3对应单项刷新
void CNetSDKDemoDlg::UpdateVideoCtrl(int nMode)
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	BYTE bVideo[4];
	memset(bVideo,0, 4);
	if(siNode.Type == SPLIT_TYPE_MONITOR)
	{
		memcpy(bVideo, siNode.nVideoParam.bParam, 4);
		BOOL nRet = CLIENT_ClientSetVideoEffect(siNode.iHandle, 
									bVideo[0], bVideo[1], bVideo[2], bVideo[3]);
		if (!nRet)
		{
			LastError();
		}
	}

	if (nMode == VIDEO_TOTAL) 
	{
		for (int i = 0; i < VIDEO_TOTAL; i++)
		{
			m_colorPannel.UpdateVideoDisplay(i, bVideo[i]);
		}
	}
	else
	{
		m_colorPannel.UpdateVideoDisplay(nMode, bVideo[nMode]);
	}
}  
    
/////////////for one////////////////
DWORD GetMonthDays(const DWORD& dwYear, const DWORD& dwMonth)
{
	DWORD dwMDays = 0;
	switch(dwMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		dwMDays = 31;
	break;
	case 2:
	{
		if (((dwYear%4==0)&& dwYear%100) || (dwYear%400==0))
		{
			dwMDays = 29; 
		}
		else
		{
			dwMDays = 28;
		}
	}
	break;
	case 4:
	case 6:
	case 9:
	case 11:
	dwMDays = 30;
	break;
	default:
	break;
	} 

	return dwMDays;
}
 
/*
 * can't surpport year offset time
 */
NET_TIME GetSeekTimeByOffsetTime(const NET_TIME& bgtime, unsigned int offsettime)
{
	NET_TIME tmseek;
	memset(&tmseek, 0x00, sizeof(NET_TIME));
 
	DWORD dwNext = 0;
	//second
	tmseek.dwSecond = (bgtime.dwSecond+offsettime)%60;
	dwNext = (bgtime.dwSecond+offsettime)/60;
	//minute
	tmseek.dwMinute = (dwNext+bgtime.dwMinute)%60;
	dwNext = (dwNext+bgtime.dwMinute)/60;
	//hour
	tmseek.dwHour = (dwNext+bgtime.dwHour)%24;
	dwNext = (dwNext+bgtime.dwHour)/24;
 
	DWORD dwMDays = GetMonthDays(bgtime.dwYear, bgtime.dwMonth);
 
	//day
	tmseek.dwDay = (dwNext+bgtime.dwDay)%dwMDays;
	dwNext = (dwNext+bgtime.dwDay)/dwMDays;
	//month
	tmseek.dwMonth  = (dwNext+bgtime.dwMonth)%12;
	dwNext = (dwNext+bgtime.dwMonth)/12;
 
	tmseek.dwYear = dwNext+bgtime.dwYear;
 
	return tmseek;
}
 
/*
 * can't surpport year offset time
 */
DWORD GetOffsetTime(const NET_TIME& st, const NET_TIME& et)
{
	DWORD dwRet = -1; 
	if (et.dwYear != st.dwYear)
	{
		return dwRet;
	}

	DWORD dwDays = 0;

	for(int i=st.dwMonth+1; i < et.dwMonth; ++i)
	{
		dwDays += GetMonthDays(st.dwYear, i);
	}

	if (et.dwMonth == st.dwMonth)
	{
		dwDays +=et.dwDay - st.dwDay;
	}
	else
	{
		dwDays += et.dwDay;
		dwDays += GetMonthDays(st.dwYear, st.dwMonth) - st.dwDay;
	}

	dwRet = dwDays*24*60*60 + ((int)et.dwHour - (int)st.dwHour)*60*60 + 
		((int)et.dwMinute - (int)st.dwMinute)*60 + (int)et.dwSecond - (int)st.dwSecond;

	return dwRet;
}
/////////////for one////////////////
//播放进度条拖动的处理
BOOL CNetSDKDemoDlg::SeekPlayPositon(int nPos)
//void CNetSDKDemoDlg::OnReleasedcapturePlayPosition(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return FALSE;
	}

	ret = FALSE;
	if(siNode.Type == SPLIT_TYPE_NETPLAY)
	{
		SplitNetPlayParam * pbParam = (SplitNetPlayParam *)siNode.Param;
		if (pbParam->iStatus == STATUS_PAUSE) 
		{
			return FALSE;
		}

		pbParam->iPlayPos = nPos;
		DWORD total = pbParam->pFileInfo->fileinfo.size;
		ret = CLIENT_SeekPlayBack(siNode.iHandle, 0xFFFFFFFF, nPos * total /100);
		if (!ret)
		{
			LastError();
		}
	}
	else if (siNode.Type == SPLIT_TYPE_PBBYTIME) 
	{
		SplitPBByTimeParam * pbParam = (SplitPBByTimeParam *)siNode.Param;
		if (pbParam->iStatus == STATUS_PAUSE) 
		{
			return FALSE;
		}
		
		pbParam->npos = nPos;
		//DWORD time = g_IntervalTime(&pbParam->starttime, &pbParam->endtime);
		DWORD time = GetOffsetTime(pbParam->starttime, pbParam->endtime);
		
		BOOL ret = CLIENT_SeekPlayBack(siNode.iHandle, nPos * time /100, 0xFFFFFFFF);
		if (!ret)
		{
			LastError();
		}
	}

	return ret;
//	*pResult = 0;
}

////////////////////////////////////////////功能操作//////////////////////////////////////////////
//增加设备连接项
void CNetSDKDemoDlg::AddDevice() 
{
	AddDeviceDlg dlg;
		
	if(dlg.DoModal() == IDOK)
	{
		UpdateDeviceList();	   //刷新设备列表显示	
	}	
	// TODO: Add your control notification handler code here
	
}

//实时数据回调,用于计算码流统计和保存数据
void CALLBACK RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CNetSDKDemoDlg *dlg = (CNetSDKDemoDlg *)dwUser;
	dlg ->ReceiveRealData(lRealHandle,dwDataType, pBuffer, dwBufSize);
}

//回放数据回调函数，demo里将数据保存成文件
int CALLBACK PBDataCallBack(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return -1;
	}
	CNetSDKDemoDlg *dlg = (CNetSDKDemoDlg *)dwUser;
	dlg ->ReceiveRealData(lRealHandle,dwDataType, pBuffer, dwBufSize);
	return 1;
}

void CALLBACK RealDataCallBackEx(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize, LONG lParam, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}

	CNetSDKDemoDlg *dlg = (CNetSDKDemoDlg *)dwUser;
	dlg->ReceiveRealData(lRealHandle,dwDataType, pBuffer, dwBufSize);
}

//根据设备列表取得设备Id，根据通道选择通道号
void CNetSDKDemoDlg::OpenChannel() 
{
	HTREEITEM node_dev, tmpnode;
	DWORD nItem;
	CString strCh;
	DeviceNode *pInfo;
	
	tmpnode = m_devicelist.GetSelectedItem();
	if(!tmpnode)
	{
		MessageBox(ConvertString(MSG_DEMODLG_CHECKSEL));
		return;
	}
	
	DH_RealPlayType subtype;
	int subidx = m_normalBtnPannel.GetSubType();
	switch(subidx)
	{
	case 0:
		subtype = DH_RType_Realplay_0;
		break;
	case 1:
		subtype = DH_RType_Realplay_1;
		break;
	case 2:
		subtype = DH_RType_Realplay_2;
		break;
	case 3:
		subtype = DH_RType_Realplay_3;
		break;
	default:
		subtype = DH_RType_Realplay_0;
	}

	nItem = m_devicelist.GetItemData(tmpnode);
	if(!m_devicelist.GetChildItem(tmpnode))     //是通道项
	{
		node_dev = m_devicelist.GetParentItem(tmpnode);
		pInfo = (DeviceNode *)m_devicelist.GetItemData(node_dev);

		OpenSingleChannel(pInfo, nItem, m_curScreen, subtype);
	}
	else              //设备项
	{
		OpenAllChannel((DeviceNode *)nItem, subtype);
	}
}

void CNetSDKDemoDlg::OpenSingleChannel(DeviceNode *pInfo, int nCh, int screenNo, DH_RealPlayType subtype)
{
	//查询是否被列入轮循列表
	if (IsCycling((DWORD)pInfo, nCh))
	{
		MessageBox(ConvertString(MSG_DEMODLG_ERROR_CYCLING));
		return;
	}
	
	//关闭当前窗口的播放
	ProcessCloseScreen(screenNo);

	CWnd* pWnd = m_screenPannel.GetPage(screenNo);
	if (!pWnd)
	{
		return ;
	}

	LONG nID = pInfo->LoginID;

	LONG nChannelID;

// 	nChannelID = CLIENT_RealPlay(nID, nCh, GetDlgItem(IDC_SCREEN1 + m_curScreen )->m_hWnd);
// 	nChannelID = CLIENT_RealPlay(nID, nCh, NULL);	
	nChannelID = CLIENT_RealPlayEx(nID, nCh, pWnd->m_hWnd/*m_playWnd[screenNo].m_hWnd*/, subtype);
	
	int nStreamType = subtype;
    if (nStreamType >= DH_RType_Realplay_0 && nStreamType <= DH_RType_Realplay_3)
    {
        nStreamType -= (int)DH_RType_Realplay_0;
    }
    else 
    {
        nStreamType = 0;
    }

	CLIENT_MakeKeyFrame(nID, nCh, nStreamType);
	if(!nChannelID)
	{
		LastError();
		MessageBox(ConvertString(MSG_DEMODLG_OPENCHLFAILED));
		return;
	}
//	CLIENT_AdjustFluency(nChannelID, 7);
	//获取视频参数
	BYTE bVideo[4];
	BOOL nRet = CLIENT_ClientGetVideoEffect(nChannelID, &bVideo[0],&bVideo[1],&bVideo[2],&bVideo[3]);
	if (!nRet)
	{
		LastError();
	}

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(screenNo, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
	}
	siNode.Type = SPLIT_TYPE_MONITOR;
	siNode.nVideoParam.dwParam = *(DWORD *)bVideo;
	siNode.iHandle = nChannelID;

	SplitMonitorParam *mparam	= new SplitMonitorParam;
	mparam->pDevice  = pInfo;
	mparam->iChannel  = nCh;
	
	siNode.Param  = mparam;

	ret = SetSplitInfo_Main(screenNo, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while setting split info"));	
	}

	//更新保存数据状态
	if(siNode.isSaveData)
	{
		CString strName ;
		strName.Format("savech%d.dav", nCh);
		BOOL ret = CLIENT_SaveRealData(nChannelID, strName.GetBuffer(0));
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_SAVEDATAFAILED));
		}
	}

	UpdateCurScreenInfo();

	//更新音频
	if(m_curSoundSplit == screenNo)
	{
		BOOL nRet = CLIENT_OpenSound(nChannelID);
		if (!nRet)
		{
			LastError();
		}
	}
	//设置数据回调
//	BOOL cbRec = CLIENT_SetRealDataCallBack(nChannelID, RealDataCallBack, (DWORD)this);
	BOOL cbRec = CLIENT_SetRealDataCallBackEx(nChannelID, RealDataCallBackEx, (DWORD)this, 0x0000000f);
	if (!cbRec)
	{
		LastError();	
	}
//	BOOL bRet = CLIENT_DHPTZControl(nID,0, PTZ_UP_CONTROL, 2, 2,0, false);
//	int iii = 0;
}

//接收播放进度状态处理
void CNetSDKDemoDlg::ReceivePlayPos(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize)
{
	//取得窗口号
	int nScreen = GetHandleSplit(lPlayHandle);
	if(nScreen < 0)
	{
		return;
	}
	
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(nScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
	}
	
	//更新播放进度值
	if (siNode.Type == SPLIT_TYPE_NETPLAY)
	{
		SplitNetPlayParam *nParam = (SplitNetPlayParam *)siNode.Param;
		if (nParam && dwTotalSize > 0)
		{
			nParam->iPlayPos = dwDownLoadSize * 100 / dwTotalSize;
			if (nParam->iPlayPos > 100)
			{
					int xyz = 0;
			}
			if(((int)dwDownLoadSize == -1))
			{
				PlayStop(nScreen);
				//m_playWnd[nScreen].ShowWindow(SW_HIDE);
				//m_playWnd[nScreen].ShowWindow(SW_SHOW);
			}
		}
	}
	else if (siNode.Type == SPLIT_TYPE_PBBYTIME)
	{
		SplitPBByTimeParam *pbParam = (SplitPBByTimeParam *)siNode.Param;
		if (pbParam && dwTotalSize > 0)
		{
			pbParam->npos = dwDownLoadSize * 100 / dwTotalSize;
			if(((int)dwDownLoadSize == -1) || (pbParam->npos >= 100))
			{
				PlayStop(nScreen);
			}
		}
	}
}

//播放进度状态回调
void CALLBACK PlayCallBack(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CNetSDKDemoDlg *dlg = (CNetSDKDemoDlg *)dwUser;
	dlg->ReceivePlayPos(lPlayHandle, dwTotalSize, dwDownLoadSize);
}

//录像查询
void CNetSDKDemoDlg::SearchRecord() 
{
	CSearchRecord dlg;
	if(dlg.DoModal() == IDOK)   //打开回放时
	{	
		if (!dlg.m_playfile) 
		{
			return;
		}
		if(!CheckCurSplitAndClose())
		{
			return;
		}
		PlayRecordFile(dlg.m_playfile, m_curScreen);
		/*	
		if (!dlg.m_playList)
		{
			return;
		}
		else
		{
			for (int i = 0; i < dlg.m_playCount; i++)
			{
				PlayRecordFile(&dlg.m_playList[i], i);
			}
		}
	*/
	}
}

void CNetSDKDemoDlg::PlayRecordFile(FileInfoNode* playfile, int scrNo)
{
	CWnd *plWnd = m_screenPannel.GetPage(scrNo);
	if (!plWnd)
	{
		MessageBox(ConvertString("unexpected error!!!!"));
		return;
	}
//	playfile->fileinfo.ch = 0;
//	memset(&playfile->fileinfo.endtime, 0, sizeof(NET_TIME));
//	memset(&playfile->fileinfo.starttime, 0, sizeof(NET_TIME));
//	memset(playfile->fileinfo.filename, 0, 128);
//	playfile->fileinfo.size = 0;
	LONG lPlayHandle = CLIENT_PlayBackByRecordFile/*Ex*/(playfile->pDevice->LoginID, &playfile->fileinfo, 
		plWnd->m_hWnd/*m_playWnd[m_curScreen].m_hWnd*/, PlayCallBack, (DWORD)this/*, PBDataCallBack, (DWORD)this*/);
//	LONG lPlayHandle = CLIENT_PlayBackByRecordFile/*Ex*/(playfile->pDevice->LoginID, &playfile->fileinfo, 
//		plWnd->m_hWnd/*m_playWnd[m_curScreen].m_hWnd*/, PlayCallBack, (DWORD)this/*, PBDataCallBack, (DWORD)this*/);

	if(!lPlayHandle)
	{
		LastError();
		MessageBox(ConvertString(MSG_DEMODLG_PLAYFAILED));
		return;
	}
	else
	{  //如果其它通道没有打开音频，则打开音频
		if (m_curSoundSplit < 0)
		{
			if (FALSE == CLIENT_OpenSound(lPlayHandle)) 
			{
				LastError();
				MessageBox(ConvertString(MSG_OPENSOUNDFAILED));
				m_advanceBtnPannel.SetCheckSound(0);
			}
			else
			{
				m_advanceBtnPannel.SetCheckSound(1);
				m_curSoundSplit = scrNo;
			}
		}
	}
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(scrNo, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
	}
	
	siNode.Type = SPLIT_TYPE_NETPLAY;
	siNode.iHandle = lPlayHandle;
	
	SplitNetPlayParam *nParam	= new SplitNetPlayParam;
	nParam->pFileInfo = new FileInfoNode;
	memcpy(nParam->pFileInfo, playfile, sizeof(FileInfoNode));
	nParam->iPlayPos = 0;
	nParam->iStatus = STATUS_PLAY;
	
	siNode.Param = nParam;
	ret = SetSplitInfo_Main(scrNo, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
	}
	
	m_playctrlPannel.StartPlay();
	UpdateCurScreenInfo();
}

//停止播放当前播放画面
BOOL CNetSDKDemoDlg::PlayCtrl_Stop()
{
	int nRet = PlayStop(m_curScreen);
	if (nRet < 0)
	{
		return FALSE;
	}
	else
	{
	//	m_playWnd[curScreen].ShowWindow(SW_HIDE);
	//	m_playWnd[curScreen].ShowWindow(SW_NORMAL);
	}
	return TRUE;
}

//快放
BOOL CNetSDKDemoDlg::PlayCtrl_Fast()
{/*
	for (int i = 0; i<16; i++)
	{
		SplitInfoNode siNode;
		memset(&siNode, 0, sizeof(siNode));
		BOOL ret = GetSplitInfo_Main(i, &siNode);
		if (!ret)
		{
			MessageBox("error while getting split info");
			return FALSE;
		}
		
		if(siNode.Type == SPLIT_TYPE_NETPLAY)
		{
			SplitNetPlayParam *pParam = (SplitNetPlayParam *)siNode.Param;
			if(pParam->iStatus == STATUS_PAUSE)
			{
				goto e_exit;
			}
			if(pParam->iStatus == STATUS_STEP)
			{
				ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
				if (!ret)
				{
					LastError();
					goto e_exit;
				}
				pParam->iStatus = STATUS_STOP;
			}
			if (m_curSoundSplit == i)
			{
				if (FALSE == CLIENT_CloseSound())
				{
					LastError();
					MessageBox(MSG_CLOSESOUNDFAILED);
					goto e_exit;
				}
				m_advanceBtnPannel.SetCheckSound(0);
				m_curSoundSplit = -1;
			}
			
			ret = CLIENT_FastPlayBack(siNode.iHandle);
			if(!ret)
			{
				LastError();
				MessageBox(MSG_DEMODLG_PLAYCTRLFAILED);
			}
			pParam->iStatus = STATUS_PLAY;
		}
		else if (siNode.Type == SPLIT_TYPE_PBBYTIME)
		{
			SplitPBByTimeParam *pbParam = (SplitPBByTimeParam *)siNode.Param;
			if(pbParam->iStatus == STATUS_PAUSE)
			{
				goto e_exit;
			}
			if(pbParam->iStatus == STATUS_STEP)
			{
				ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
				if (!ret)
				{
					LastError();
				}
				else
				{
					pbParam->iStatus = STATUS_STOP;
				}
			}
			if (m_curSoundSplit == i)
			{
				if (FALSE == CLIENT_CloseSound())
				{
					LastError();
					MessageBox(MSG_CLOSESOUNDFAILED);
					goto e_exit;
				}
				m_advanceBtnPannel.SetCheckSound(0);
				m_curSoundSplit = -1;
			}
			ret = CLIENT_FastPlayBack(siNode.iHandle);
			if(!ret)
			{
				LastError();
				MessageBox(MSG_DEMODLG_PLAYCTRLFAILED);
				goto e_exit;
			}
			pbParam->iStatus = STATUS_PLAY;
		}
		else
		{
		//	MessageBox(MSG_DEMODLG_NOTPLAYING);
		//	goto e_exit;
		}
	}
		*/
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return FALSE;
	}

	if(siNode.Type == SPLIT_TYPE_NETPLAY)
	{
		SplitNetPlayParam *pParam = (SplitNetPlayParam *)siNode.Param;
		if(pParam->iStatus == STATUS_PAUSE)
		{
			goto e_exit;
		}
		if(pParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
				goto e_exit;
			}
			pParam->iStatus = STATUS_STOP;
		}
		if (m_curSoundSplit == m_curScreen)
		{
			if (FALSE == CLIENT_CloseSound())
			{
				LastError();
				MessageBox(ConvertString(MSG_CLOSESOUNDFAILED));
				goto e_exit;
			}
			m_advanceBtnPannel.SetCheckSound(0);
			m_curSoundSplit = -1;
		}
		
		ret = CLIENT_FastPlayBack(siNode.iHandle);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
		}
		pParam->iStatus = STATUS_PLAY;
	}
	else if (siNode.Type == SPLIT_TYPE_PBBYTIME)
	{
		SplitPBByTimeParam *pbParam = (SplitPBByTimeParam *)siNode.Param;
		if(pbParam->iStatus == STATUS_PAUSE)
		{
			goto e_exit;
		}
		if(pbParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
			}
			else
			{
				pbParam->iStatus = STATUS_STOP;
			}
		}
		if (m_curSoundSplit == m_curScreen)
		{
			if (FALSE == CLIENT_CloseSound())
			{
				LastError();
				MessageBox(ConvertString(MSG_CLOSESOUNDFAILED));
				goto e_exit;
			}
			m_advanceBtnPannel.SetCheckSound(0);
			m_curSoundSplit = -1;
		}
		ret = CLIENT_FastPlayBack(siNode.iHandle);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
			goto e_exit;
		}
		pbParam->iStatus = STATUS_PLAY;
	}
	else
	{
		MessageBox(ConvertString(MSG_DEMODLG_NOTPLAYING));
		goto e_exit;
	}

	return TRUE;
e_exit:
	return FALSE;

}

//慢放
BOOL CNetSDKDemoDlg::PlayCtrl_Slow() 
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return FALSE;
	}

	if(siNode.Type == SPLIT_TYPE_NETPLAY)
	{
		SplitNetPlayParam *pParam = (SplitNetPlayParam *)siNode.Param;
		if(pParam->iStatus == STATUS_PAUSE)
		{
			goto e_exit;
		}
		
		if(pParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
				goto e_exit;
			}
			pParam->iStatus = STATUS_STOP;
		}

		ret = CLIENT_SlowPlayBack(siNode.iHandle);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
			goto e_exit;
		}
		pParam->iStatus = STATUS_PLAY;	
	}
	else if (siNode.Type == SPLIT_TYPE_PBBYTIME)
	{
		SplitPBByTimeParam *pbParam = (SplitPBByTimeParam *)siNode.Param;
		if(pbParam->iStatus == STATUS_PAUSE)
		{
			goto e_exit;
		}
		
		if(pbParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
				goto e_exit;
			}
			pbParam->iStatus = STATUS_STOP;
		}

		ret = CLIENT_SlowPlayBack(siNode.iHandle);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
			goto e_exit;
		}
		pbParam->iStatus = STATUS_PLAY;	
	}
	else
	{
		MessageBox(ConvertString(MSG_DEMODLG_NOTPLAYING));
		goto e_exit;
	}

	return TRUE;
e_exit:
	return FALSE;
}

//单帧播放
BOOL CNetSDKDemoDlg::PlayCtrl_Step() 
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return FALSE;
	}

	if(siNode.Type == SPLIT_TYPE_NETPLAY)
	{
		SplitNetPlayParam *pParam = (SplitNetPlayParam *)siNode.Param;
		if(pParam->iStatus == STATUS_PAUSE)
		{
			goto e_exit;
		}
		ret = CLIENT_StepPlayBack(siNode.iHandle, FALSE);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
			goto e_exit;
		}
		pParam->iStatus = STATUS_STEP;
	}
	else if (siNode.Type == SPLIT_TYPE_PBBYTIME) 
	{
		SplitPBByTimeParam *pbParam = (SplitPBByTimeParam *)siNode.Param;
		if(pbParam->iStatus == STATUS_PAUSE)
		{
			MessageBox(ConvertString("paused"));
			goto e_exit;
		}
		ret = CLIENT_StepPlayBack(siNode.iHandle, FALSE);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
			goto e_exit;
		}
		pbParam->iStatus = STATUS_STEP;
	}
	else
	{
		MessageBox(ConvertString(MSG_DEMODLG_NOTPLAYING));
		goto e_exit;
	}

	return TRUE;
e_exit:
	return FALSE;
}

BOOL CNetSDKDemoDlg::PlayCtrl_Frame(int frame)
{
//	KillTimer(TIMER_KBPS);
	if(!UpdateData(true))
	{
		return FALSE;
	}

	if ((frame < 0) || (frame > 120))
	{
		MessageBox(ConvertString(MSG_SCHRECORD_ILLEGALFRAME));
		return FALSE;
	}

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return FALSE;
	}
	
	ret = FALSE;
	if(siNode.Type == SPLIT_TYPE_NETPLAY)
	{
		SplitNetPlayParam *pParam = (SplitNetPlayParam *)siNode.Param;
		if(pParam->iStatus == STATUS_PAUSE)
		{
			goto out;
		}
		if(pParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
				goto out;
			}
			pParam->iStatus = STATUS_STOP;
		}
		if (m_curSoundSplit == m_curScreen)
		{
			if (FALSE == CLIENT_CloseSound())
			{
				LastError();
				MessageBox(ConvertString(MSG_CLOSESOUNDFAILED));
				goto out;
			}
			m_advanceBtnPannel.SetCheckSound(0);
			m_curSoundSplit = -1;
		}
		ret = CLIENT_SetFramePlayBack(siNode.iHandle, frame);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
			goto out;
		}
	}
	else if(siNode.Type == SPLIT_TYPE_PBBYTIME)
	{
		SplitPBByTimeParam *pbParam = (SplitPBByTimeParam *)siNode.Param;
		if(pbParam->iStatus == STATUS_PAUSE)
		{
			goto out;
		}
		if(pbParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
				goto out;
			}
			pbParam->iStatus = STATUS_STOP;
		}
		if (m_curSoundSplit == m_curScreen)
		{
			if (FALSE == CLIENT_CloseSound())
			{
				LastError();
				MessageBox(ConvertString(MSG_CLOSESOUNDFAILED));
				goto out;
			}
			m_advanceBtnPannel.SetCheckSound(0);
			m_curSoundSplit = -1;
		}
		ret = CLIENT_SetFramePlayBack(siNode.iHandle, frame);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
			goto out;
		}
	}
	else
	{	
		MessageBox(ConvertString(MSG_DEMODLG_NOTPLAYING));
		goto out;
	}
out:
//	SetTimer(TIMER_KBPS, 1111,NULL);
	return ret;
}


//播放/暂停切换
BOOL CNetSDKDemoDlg::PlayCtrl_Play()
{
	BOOL isPause = false;

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return FALSE;
	}

	ret = FALSE; 
	if(siNode.Type == SPLIT_TYPE_NETPLAY)
	{
		SplitNetPlayParam *pParam = (SplitNetPlayParam *)siNode.Param;
		if(pParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
				goto out;
			}
			pParam->iStatus = STATUS_STOP;
		}

		if(pParam->iStatus != STATUS_PAUSE)
		{
			isPause = true;	
		}

		ret = CLIENT_PausePlayBack(siNode.iHandle, isPause);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
		}
		else
		{
			if(pParam->iStatus == STATUS_PAUSE)
			{
				pParam->iStatus = STATUS_PLAY;
			}
			else
			{
				pParam->iStatus = STATUS_PAUSE;
			}
		}
	}
	else if(siNode.Type == SPLIT_TYPE_PBBYTIME)
	{
		SplitPBByTimeParam *pbParam = (SplitPBByTimeParam *)siNode.Param;
		if(pbParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
				goto out;
			}
			pbParam->iStatus = STATUS_STOP;
		}

		if(pbParam->iStatus != STATUS_PAUSE)
		{
			isPause = true;	
		}
		
		ret = CLIENT_PausePlayBack(siNode.iHandle, isPause);
		if(!ret)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYCTRLFAILED));
		}	
		else
		{
			if(pbParam->iStatus == STATUS_PAUSE)
			{
				pbParam->iStatus = STATUS_PLAY;
			}
			else
			{
				pbParam->iStatus = STATUS_PAUSE;
			}
		}
	}
	else
	{
		MessageBox(ConvertString(MSG_DEMODLG_NOTPLAYING));
	}

out:
	return ret;
}

int CNetSDKDemoDlg::PlayStop(int iScreen, BOOL bDis)
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(iScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		goto e_clear;
	}

	CPlayWnd *plWnd;
	if(siNode.Type == SPLIT_TYPE_NETPLAY)
	{
		SplitNetPlayParam *pParam = (SplitNetPlayParam *)siNode.Param;
		//如果处于单帧播放状态，需先恢复
		if(pParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
				goto e_clear;
			}
		}
		m_playctrlPannel.StopPlay();
		ret = CLIENT_StopPlayBack(siNode.iHandle);
		if (!ret)
		{
			LastError();
			if (!bDis)
			{
				MessageBox(ConvertString(MSG_DEMODLG_STOPPLAYFAILED));
				goto e_clear;
			}
		}
		FileInfoNode *pFile = ((SplitNetPlayParam *)siNode.Param)->pFileInfo;
		delete pFile;
		delete (SplitNetPlayParam *)siNode.Param;
		siNode.Param = NULL;
		siNode.Type = SPLIT_TYPE_NULL;
		ret = SetSplitInfo_Main(iScreen, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while setting split info"));
		}

		if (m_curSoundSplit == iScreen)
		{
			//m_advanceBtnPannel.SetCheckSound(0);
			m_curSoundSplit = -1;
		}
	}
	else if (siNode.Type == SPLIT_TYPE_PBBYTIME)
	{
		SplitPBByTimeParam *pbParam = (SplitPBByTimeParam *)siNode.Param;
		//如果处于单帧播放状态，需先恢复
		if(pbParam->iStatus == STATUS_STEP)
		{
			ret = CLIENT_StepPlayBack(siNode.iHandle, TRUE);
			if (!ret)
			{
				LastError();
				goto e_clear;
			}
		}
		m_playctrlPannel.StopPlay();
		ret = CLIENT_StopPlayBack(siNode.iHandle);
		if (!ret)
		{
			LastError();
			if (!bDis)
			{
				MessageBox(ConvertString(MSG_DEMODLG_STOPPLAYFAILED));
				goto e_clear;
			}
		}
		delete (SplitPBByTimeParam *)siNode.Param;
		//add by zhaojs 2006-12-06
		siNode.Param = NULL;
		siNode.Type = SPLIT_TYPE_NULL;
		ret = SetSplitInfo_Main(iScreen, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while setting split info"));
		}

		if (m_curSoundSplit == iScreen)
		{
			//m_advanceBtnPannel.SetCheckSound(0);
			m_curSoundSplit = -1;
		}
	}
	else
	{
		MessageBox(ConvertString(MSG_DEMODLG_NOTPLAYING));
		goto e_clear;
	}

	// repaint the play window
	plWnd = (CPlayWnd *)m_screenPannel.GetPage(iScreen);
	if (plWnd)
	{
		plWnd->PostMessage(VIDEO_REPAINT);
	}

	return 0;
e_clear:
	return -1;
}

//对当前监视通道进行抓图,对播放通道是否能抓图有待验证
void CNetSDKDemoDlg::CaptureScreen() 
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	CString strName = "pct.bmp";
	
	//支持多种图像的抓图
	if(siNode.Type == SPLIT_TYPE_NULL)
	{
		MessageBox(ConvertString(MSG_DEMODLG_CANTCAPTURE));
		return;
	}

	//抓图保存文件名的输入
	CFileDialog dlg(FALSE,"*.bmp","pct.bmp",OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		"All File(*.bmp)|*.*||",this);

	if(dlg.DoModal() == IDOK)
	{
		strName = dlg.GetPathName();		
	}

	ret = CLIENT_CapturePicture(siNode.iHandle, strName.GetBuffer(0));
	if(!ret)
	{
		LastError();
		MessageBox(ConvertString(MSG_DEMODLG_CAPTUREFAILED));
	}
}

//强制I帧
void CNetSDKDemoDlg::SetIframe() 
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	if(siNode.Type != SPLIT_TYPE_MONITOR)
	{
		MessageBox(ConvertString(MSG_DEMODLG_CANTFORCE_I));
		return;
	}
	
	SplitMonitorParam *mParam = (SplitMonitorParam *)siNode.Param;

	ret = CLIENT_MakeKeyFrame(mParam->pDevice->LoginID, mParam->iChannel);
	if(!ret)
	{
		LastError();
		MessageBox(ConvertString(MSG_DEMODLG_FAILEDFORCE_I));
	}
}

//是否打开声音
BOOL CNetSDKDemoDlg::OpenSound(BOOL bOpen) 
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return FALSE;
	}

	if(bOpen)
	{
		if (m_curSoundSplit >= 0 && 
			(siNode.Type == SPLIT_TYPE_MONITOR || 
			siNode.Type == SPLIT_TYPE_NETPLAY || 
			siNode.Type == SPLIT_TYPE_PBBYTIME))
		{
			if (FALSE == CLIENT_CloseSound())
			{
				LastError();
				MessageBox(ConvertString(MSG_CLOSESOUNDFAILED));
				return FALSE;
			}
		}
		m_curSoundSplit = m_curScreen;
		if (siNode.Type == SPLIT_TYPE_MONITOR || 
			siNode.Type == SPLIT_TYPE_NETPLAY ||
			siNode.Type == SPLIT_TYPE_PBBYTIME)
		{
			if (FALSE == CLIENT_OpenSound(siNode.iHandle))
			{
				LastError();
				MessageBox(ConvertString(MSG_OPENSOUNDFAILED));
				return FALSE;
			}
		}
	}
	else
	{
		if (siNode.Type == SPLIT_TYPE_MONITOR || 
			siNode.Type == SPLIT_TYPE_NETPLAY ||
			siNode.Type == SPLIT_TYPE_PBBYTIME)
		{
			if (FALSE == CLIENT_CloseSound())
			{
				LastError();
				MessageBox(ConvertString(MSG_CLOSESOUNDFAILED));
				return FALSE;
			}
		}
		m_curSoundSplit = -1;
	}
	
	return TRUE;
}

//是否保存实时数据数据
void CNetSDKDemoDlg::SaveRealdata(int nCheck) 
{
	CPlayWnd *plWnd = (CPlayWnd *)m_screenPannel.GetPage(m_curScreen);
	if (!plWnd)
	{
		MessageBox(ConvertString("we have a big error here!"));
		return;
	}
	
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	CString strName = "save.dav";
	if(nCheck > 0)
	{
		siNode.isSaveData = 1;
		if (siNode.Type == SPLIT_TYPE_MONITOR || siNode.Type == SPLIT_TYPE_MULTIPLAY)
		{
			//文件名的输入
			CFileDialog dlg(FALSE,"*.dav","save.dav",OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
			"All File(*.dav)|*.*||",this);
			if(dlg.DoModal() == IDOK)
			{
				strName = dlg.GetPathName();		
			}
			else
			{
				return;
			}
			BOOL ret = CLIENT_SaveRealData(siNode.iHandle, strName.GetBuffer(0));
			if(!ret)
			{
				LastError();
				MessageBox (ConvertString(MSG_DEMODLG_SAVEDATAFAILED));
			}
			else
			{
				plWnd->SetSplitCBFlag_Real(1);
			}
		}
	}
	else
	{
		siNode.isSaveData = 0;
		if(siNode.Type == SPLIT_TYPE_MONITOR || siNode.Type == SPLIT_TYPE_MULTIPLAY)
		{
			BOOL stop = CLIENT_StopSaveRealData(siNode.iHandle);
			if (stop)
			{
				plWnd->SetSplitCBFlag_Real(0);
				MessageBox(ConvertString(MSG_DEMODLG_REALSAVE_STOPPED));
			}
			else
			{
				LastError();
				MessageBox(ConvertString("stop save file failed"));
			}
		}
	}
}

//用来打开显示画面分割各显示区域的信息
void CNetSDKDemoDlg::ShowFluxInfo() 
{
	
	CSplitInfoDlg dlg;
	m_runtimeMsgPannel.EnableShowFlux(FALSE);
	dlg.DoModal();
	m_runtimeMsgPannel.EnableShowFlux(TRUE);
}

/*
//刷新画面分割模式
void CNetSDKDemoDlg::OnSelchangeSplittesel() 
{
	UpdateScreen();
}
*/

//关闭监视图像
void CNetSDKDemoDlg::CloseScreen() 
{
	BOOL ret = ProcessCloseScreen(m_curScreen);

	//m_playWnd[m_curScreen].ShowWindow(SW_HIDE);
	//m_playWnd[m_curScreen].ShowWindow(SW_NORMAL);
	UpdateCurScreenInfo();
}


void CNetSDKDemoDlg::PtzControl(int type, BOOL stop, int param)
{
	BOOL ret;
	SplitMonitorParam *nParam ;
	BOOL upRet;
	
	LONG lHandle;
	int iChannel;

	if (stop) 
	{
		if (!m_bPTZCtrl)
		{
			goto exitPTZCtrl;
		}
	}

	switch(type) {
	//在主页面的控制
	case DH_PTZ_UP_CONTROL  :    //上           
	case DH_PTZ_DOWN_CONTROL:		//下
	case DH_PTZ_LEFT_CONTROL:	//左
	case DH_PTZ_RIGHT_CONTROL:		//右
	case DH_PTZ_ZOOM_ADD_CONTROL:		//变倍
	case DH_PTZ_ZOOM_DEC_CONTROL:		
	case DH_PTZ_FOCUS_ADD_CONTROL:	//调焦
	case DH_PTZ_FOCUS_DEC_CONTROL:	
	case DH_PTZ_APERTURE_ADD_CONTROL:	//光圈
	case DH_PTZ_APERTURE_DEC_CONTROL:
	case DH_EXTPTZ_LEFTTOP :
	case DH_EXTPTZ_RIGHTTOP :
	case DH_EXTPTZ_LEFTDOWN :
	case DH_EXTPTZ_RIGHTDOWN:
		upRet = UpdateData(true);
		if (!upRet) 
		{
			goto exitPTZCtrl;
		}
		break;
	case DH_PTZ_POINT_MOVE_CONTROL  :   //转至
	case DH_PTZ_POINT_SET_CONTROL   :   //设置
	case DH_PTZ_POINT_DEL_CONTROL   :   //删除
	case DH_PTZ_POINT_LOOP_CONTROL :   //点间轮循
	case DH_PTZ_LAMP_CONTROL:            //灯
	default:
		MessageBox(ConvertString(MSG_DEMODLG_PTZCMDFAILED));
		goto exitPTZCtrl;
	}

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));

	ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	if(siNode.Type != SPLIT_TYPE_MONITOR)
	{
		goto exitPTZCtrl;
	}
	nParam = (SplitMonitorParam *)siNode.Param;
	lHandle = nParam->pDevice->LoginID;
	iChannel = nParam->iChannel;
	if(type >= DH_EXTPTZ_LEFTTOP)
	{
		ret = CLIENT_DHPTZControl(lHandle,iChannel, type, (BYTE)param, (BYTE)param,0, stop);
		if (!ret)
		{
			LastError();
		}
		m_bPTZCtrl = !stop;
	}
	else
	{
		ret = CLIENT_DHPTZControl(lHandle,iChannel, type, 0, (BYTE)param,0, stop);
//		ret = CLIENT_PTZControl(lHandle,iChannel, type, param, stop);(因为此接口不发送停止命令给设备，因此还是使用CLIENT_DHPTZControl)
		if (!ret)
		{
			LastError();
		}
		m_bPTZCtrl = !stop;
	}
	if(!ret)
	{
		MessageBox(ConvertString(MSG_DEMODLG_PTZCTRLFAILED));
		goto exitPTZCtrl;
	}

	return;

exitPTZCtrl:
	m_bPTZCtrl = FALSE;
	return;
}

/*
//处理点击到当前分割区域时的显示，并确定刷新当前显示画面
void CNetSDKDemoDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect nRect, subRect;
	int nSplit, spWide, spHight, i, j;

	//m_mywindows 的客户区域位置
	GetDlgItem(IDC_MYWINDOW)->GetClientRect(&nRect);
	GetDlgItem(IDC_MYWINDOW)->ClientToScreen(&nRect);
	ScreenToClient(&nRect);

	//当不在显示的区域时直接返回
	if(point.x < nRect.left || point.x > nRect.right)
	{
		return;		
	}
	if(point.y < nRect.top || point.y > nRect.bottom)
	{
		return;
	}

	nSplit = m_splittesel.GetCurSel() + 1;     //分割画面类型确定分割行列数
	
	spWide = nRect.Width()/nSplit;
	spHight = nRect.Height()/nSplit;

	//确定当前画面序号和当前区域
	j = (point.x - nRect.left)/spWide;
	i = (point.y - nRect.top)/spHight;

	m_curScreen = i * nSplit + j + GetCurSplitStart(m_curScreen, nSplit);   

	subRect.left = nRect.left + j * spWide;
	subRect.top = nRect.top + i * spHight;
	
	subRect.right = subRect.left + spWide;
	subRect.bottom = subRect.top + spHight;

	//当前画面更新显示
//	GetDlgItem(IDC_CURWIN)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_CURWIN)->MoveWindow(&subRect,false);
//	GetDlgItem(IDC_CURWIN)->ShowWindow(SW_NORMAL);

	UpdateCurScreenInfo();
}
*/

/*
//双击切换到单画面
void CNetSDKDemoDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRect nRect, subRect;
	int nSplit, spWide, spHight, i, j;
	
	if(m_splittesel.GetCurSel() == SPLIT1)
	{
		m_splittesel.SetCurSel(m_previousSplit);
		UpdataScreen();
		return;
	}
	//m_mywindows 的客户区域位置
	GetDlgItem(IDC_MYWINDOW)->GetClientRect(&nRect);
	GetDlgItem(IDC_MYWINDOW)->ClientToScreen(&nRect);
	ScreenToClient(&nRect);

	//当不在显示的区域时直接返回
	if(point.x < nRect.left || point.x > nRect.right)
	{
		return;
	}
	if(point.y < nRect.top || point.y > nRect.bottom)
	{
		return;
	}

	nSplit = m_splittesel.GetCurSel() + 1;     //
	
	spWide = nRect.Width()/nSplit;
	spHight = nRect.Height()/nSplit;

	j = (point.x - nRect.left)/spWide;
	i = (point.y - nRect.top)/spHight;

	//设置到对应画面的单画面
	m_curScreen = i * nSplit + j + GetCurSplitStart(m_curScreen, nSplit);
	m_previousSplit = m_splittesel.GetCurSel();
	m_splittesel.SetCurSel(SPLIT1);


	//刷新显示
	UpdataScreen();
	UpdateCurScreenInfo();
	CDialog::OnLButtonDblClk(nFlags, point);
}
*/

int CloseAllDevCallback(const DeviceNode& node, DWORD dwUser)
{
	CNetSDKDemoDlg* pThis = (CNetSDKDemoDlg*)dwUser;
	if (!pThis)
	{
		return 1;
	}

	pThis->ProcessDeleteDevice(const_cast<DeviceNode*>(&node), false, true);

	return 0;
}

//窗口关闭时的处理，主要是需要释放动态内存
void CNetSDKDemoDlg::OnClose() 
{	
#ifdef DH_STREAMPARSER
	int spret = DHSP_Free(m_hSp);
#endif

	int i;

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));

	//关闭打开的回调数据保存文件
	for(i = 0; i < 16 ; i++)
	{
		BOOL ret = GetSplitInfo_Main(i, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while getting split info"));
		}
		if(siNode.SavecbFileRaw)
		{
			fclose(siNode.SavecbFileRaw);
		}
		if(siNode.SavecbFileStd)
		{
			fclose(siNode.SavecbFileStd);
		}
		if(siNode.SavecbFilePcm)
		{
			fclose(siNode.SavecbFilePcm);
		}
		if(siNode.SavecbFileYUV)
		{
			fclose(siNode.SavecbFileYUV);
		}
		ProcessCloseScreen(i);
	}
	
	//删除设备列表
	
	CDevMgr::GetDevMgr().For_EachDev(CloseAllDevCallback, (DWORD)this);
	
	//listen device test
	if (m_lListenChannel)
	{
		BOOL b = CLIENT_StopRealPlayEx(m_lListenChannel);
	}
	if (m_lListenDevice) 
	{
		BOOL b = CLIENT_Logout(m_lListenDevice);
	}

	CLIENT_Cleanup();    //关闭网络sdk
    LastError();
	//关闭网络sdk
	
	TCHAR* pPath = g_GetIniPath();
	if(NULL != pPath)
	{
		delete []pPath;
	}

	CDialog::OnClose();
}

void CNetSDKDemoDlg::ProcessDeleteDevice(DeviceNode *pDevice, BOOL bDelList, BOOL bDis)
{
	int i;
	FileInfoNode *pInfo;
	if(!pDevice)
	{
		return;
	}

	/*Begin: Add by yehao(10857) For Task.NO.11071 2006-12-26*/
	{
		list<DeviceNode *>::iterator it = m_broadcastDevList.begin();
		for (; it != m_broadcastDevList.end(); it++)
		{
			if (LONG(pDevice) == LONG(*it))
			{
				CLIENT_AudioBroadcastDelDev(pDevice->LoginID);
				m_broadcastDevList.erase(it);
				break;
			}
		}
	}
	if (m_talkhandle.pDevice && pDevice->LoginID == m_talkhandle.pDevice->LoginID)
	{
		this->OpenTalk(FALSE);
	}
	/*End: yehao(10857) Task.NO.11071 */

	//检查是否正在刷新该设备的报警信息
	DeviceNode *alarmDev = m_ClientStateDlg.GetDevice();
	if (alarmDev && alarmDev->LoginID == pDevice->LoginID)
	{
		m_ClientStateDlg.StopRefresh();
		m_ClientStateDlg.SetDevice(0);
	}

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));

	DeviceNode *pDev = pDevice;
	//关闭该设备的监视通道和播放通道
	for(i = 0; i < 16; i++)
	{
		BOOL ret = GetSplitInfo_Main(i, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while getting split info"));
		}
		
		switch(siNode.Type)
		{
		case SPLIT_TYPE_MONITOR:
			if (pDev->LoginID == ((SplitMonitorParam *)siNode.Param)->pDevice->LoginID) 
			{
				ProcessCloseScreen(i, bDis);
			}
			break;	
			
		case SPLIT_TYPE_MULTIPLAY:
			if (pDev->LoginID == ((DeviceNode *)siNode.Param)->LoginID) 
			{
				ProcessCloseScreen(i, bDis);
			}
			break;
			
		case SPLIT_TYPE_NETPLAY:
			if (pDev->LoginID == ((SplitNetPlayParam *)siNode.Param)->pFileInfo->pDevice->LoginID) 
			{
				ProcessCloseScreen(i, bDis);
			}
			break;
		case SPLIT_TYPE_PBBYTIME:
			if (pDev->LoginID == ((SplitPBByTimeParam *)siNode.Param)->pDevice->LoginID) 
			{
				ProcessCloseScreen(i, bDis);
			}
			break;
			
		case SPLIT_TYPE_CYCLEMONITOR:
			{
	//			EnterCriticalSection(&g_csCycle);
	//			CCSLock lck(g_cs);
				KillTimer(i);
				if (!siNode.Param) 
				{
					break;
				}
				POSITION pos1, pos2;
				pos1 = ((SplitCycleParam *)siNode.Param)->pChannelList->GetHeadPosition();
				int count = ((SplitCycleParam *)siNode.Param)->pChannelList->GetCount();
				for (int j = 0; j < count; j++)
				{
					pos2 = pos1;
					void *temp = ((SplitCycleParam *)siNode.Param)->pChannelList->GetNext(pos1);
					//比较轮循列表中节点的设备名
					if ((DWORD)pDev == ((CycleChannelInfo *)temp)->dwDeviceID) 
					{	
						//是否刚好是正在播放的节点
						if (j == ((SplitCycleParam *)siNode.Param)->iCurPosition)
						{
							BOOL ret = TRUE;
							if (0 != siNode.iHandle) 
							{
								ret = CLIENT_StopRealPlay(siNode.iHandle);
							}
							if(ret)
							{
								delete (CycleChannelInfo *)((SplitCycleParam *)siNode.Param)->pChannelList->GetAt(pos2);
								((SplitCycleParam *)siNode.Param)->pChannelList->RemoveAt(pos2);
								((SplitCycleParam *)siNode.Param)->iChannelCount--;
								siNode.iHandle = 0;
								ret = SetSplitInfo_Main(i, &siNode);
								if (!ret)
								{
									MessageBox(ConvertString("error while setting split info"));
								}
								//如果列表已空，则结束轮循
								if (((SplitCycleParam *)siNode.Param)->iChannelCount <= 0) 
								{
									DeleteCycleParam(i);
									siNode.Param = NULL;
									break;
								}
							}
							else
							{
								if (siNode.Param) 
								{
									if (!bDis) 
									{
										MessageBox(ConvertString(MSG_CYCLE_CLOSECHANNELFAILED));
									}
									DeleteCycleParam(i);
									siNode.Param = NULL;
								}
								break;
							}
						}
						//不是当前播放节点，直接删除
						else
						{
							delete (CycleChannelInfo *)((SplitCycleParam *)siNode.Param)->pChannelList->GetAt(pos2);
							((SplitCycleParam *)siNode.Param)->pChannelList->RemoveAt(pos2);
							((SplitCycleParam *)siNode.Param)->iChannelCount--;
							if (((SplitCycleParam *)siNode.Param)->iChannelCount <= 0) 
							{
								DeleteCycleParam(i);
								siNode.Param = NULL;
								break;
							}
						}
						//当前位置放回前一个，以便timer计时到了播放正确的下一个
						if (((SplitCycleParam *)siNode.Param)->iCurPosition != 0) 
						{
							((SplitCycleParam *)siNode.Param)->iCurPosition--;
						}
						else
						{
							((SplitCycleParam *)siNode.Param)->iCurPosition = ((SplitCycleParam *)siNode.Param)->iChannelCount - 1;
						}
					}
				}
				//如果列表中还有其它设备的通道，半秒后执行切换
				if (siNode.Param) 
				{
					SetTimer(i, 500, NULL);
				}
		//		LeaveCriticalSection(&g_csCycle);
			}
			
			break;
		default:
			break;
		}
	}

	//删除查询文件列表中该设备的文件项
	POSITION nPos1 = g_ptrfilelist->GetHeadPosition();
	POSITION nPos2;
	int filecount = g_ptrfilelist->GetCount();
	for(i = 0; i < filecount; i++)
	{
		nPos2 = nPos1;
		pInfo = (FileInfoNode *)g_ptrfilelist->GetNext(nPos1);
		if(pInfo && pInfo->pDevice == pDev)
		{
			g_ptrfilelist->RemoveAt(nPos2);
			delete pInfo;
		}
	}
	CLIENT_Logout(pDev->LoginID);
//	LastError();
	
	if(bDelList)
	{
		/*
		POSITION nPos = g_ptrdevicelist->Find(nDev);
		g_ptrdevicelist->RemoveAt(nPos);
		delete nDev;
		*/

		CDevMgr::GetDevMgr().DelNode(pDev->LoginID);
	}
}

//断开当前选择的设备
void CNetSDKDemoDlg::DeleteDevice() 
{
	DeviceNode *nDev=(DeviceNode *)GetCurDeviceInfo();
	if(nDev == NULL)
	{
		return;
	}
	ProcessDeleteDevice(nDev, TRUE);
	UpdateDeviceList();
	UpdateCurScreenInfo();
	UpdateScreen(m_normalBtnPannel.GetSplit());
//	Invalidate(true);
}

//拖动亮度控制条
void CNetSDKDemoDlg::CtrlColor_Bright(int pos)
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	if(siNode.Type == SPLIT_TYPE_MONITOR)
	{	
		siNode.nVideoParam.bParam[0] = pos;
		ret = SetSplitInfo_Main(m_curScreen, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while setting split info"));
			return;
		}
	}
	UpdateVideoCtrl(VIDEO_BRIGHT);
}

//拖动对比度控制条
void CNetSDKDemoDlg::CtrlColor_Contrast(int pos)

{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}
	
	if(siNode.Type == SPLIT_TYPE_MONITOR)
	{
		siNode.nVideoParam.bParam[1] = pos;
		ret = SetSplitInfo_Main(m_curScreen, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while setting split info"));
			return;
		}
	}
	UpdateVideoCtrl(VIDEO_CONTRAST);
}

//拖动色度控制条
void CNetSDKDemoDlg::CtrlColor_Hue(int pos)
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	if(siNode.Type == SPLIT_TYPE_MONITOR)
	{
		siNode.nVideoParam.bParam[2] = pos;
		ret = SetSplitInfo_Main(m_curScreen, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while setting split info"));
			return;
		}
	}
	UpdateVideoCtrl(VIDEO_HUE);	
}

//拖动饱和度控制条
void CNetSDKDemoDlg::CtrlColor_Saturation(int pos)
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}
	
	if(siNode.Type == SPLIT_TYPE_MONITOR)
	{
		siNode.nVideoParam.bParam[3] = pos;
		ret = SetSplitInfo_Main(m_curScreen, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while setting split info"));
			return;
		}
	}
	UpdateVideoCtrl(VIDEO_SATURATION);	
}

//更新设备状态
void CNetSDKDemoDlg::UpdateDeviceState(void *pDevice,  char *pBuf, DWORD dwBufLen)
{/*
	DeviceNode *pDev = (DeviceNode *)pDevice;
	NET_CLIENT_STATE *ClientState = (NET_CLIENT_STATE *)pBuf;

	if(ClientState == NULL)
	{
		return;
	}

	//设备列表中信息刷新
	pDev->State.channelcount = ClientState->channelcount;
	pDev->State.alarminputcount = ClientState->alarminputcount;
	memcpy(pDev->State.diskerror, ClientState->diskerror, 32);

	//录像状态
	if(pDev->State.record == NULL)
	{
		pDev->State.record = new BYTE[pDev->State.channelcount];
	}
	memcpy(pDev->State.record,ClientState->record,pDev->State.channelcount );

	//报警状态
	if(pDev->State.alarm == NULL)
	{
		pDev->State.alarm = new BYTE[pDev->State.alarminputcount];
	}
	memcpy(pDev->State.alarm,ClientState->alarm,pDev->State.alarminputcount );

	//动态检测报警
	if(pDev->State.motiondection == NULL)
	{
		pDev->State.motiondection = new BYTE[pDev->State.channelcount];
	}
	memcpy(pDev->State.motiondection,ClientState->motiondection,pDev->State.channelcount );
	
	//视频丢失报警
	if(pDev->State.videolost == NULL)
	{
		pDev->State.videolost = new BYTE[pDev->State.channelcount];
	}
	memcpy(pDev->State.videolost,ClientState->videolost,pDev->State.channelcount );
*/
}

//接收到实时数后需要做的处理
void CNetSDKDemoDlg::ReceiveRealData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize)
{
//	char ougmsg[100];
//	sprintf(ougmsg, "Receive real data--type:%d, length:%d\n", dwDataType, dwBufSize);
//	OutputDebugString(ougmsg);
	//取得窗口号
	int nScreen = GetHandleSplit(lRealHandle);
	if(nScreen < 0)
	{
		return;
	}
	
	//码流统计
//	g_splitinfo[nScreen].nKBPS +=  dwBufSize;

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(nScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}
	
	//保存实时数据
	switch(dwDataType) {
	case 0:
		if(siNode.SavecbFileRaw)
		{
#ifdef DH_STREAMPARSER
			//for stream parser
			if (m_spFile)
			{
				int spret = DHSP_InputData(m_hSp, pBuffer, dwBufSize);
				if (spret != 0)
				{
					int iiii = 0;//error，这种情况现在不会出现
				}
				else
				{
					//这里应当维护一个变量标志当前是否已顺利获得I帧
					DH_FRAME_INFO *frame = 0;
					while ((frame = DHSP_GetNextFrame(m_hSp)) != NULL)
					{
						//这里只提取视频帧
						if (frame->nType != DH_FRAME_TYPE_VIDEO)
						{
							continue;
						}
						//0 == frame->nLength表示无效帧
						if (0 == frame->nLength) 
						{
							continue;
						}
						//0 == frame->nFrameLength数据丢失了，后面的p帧应该丢掉，不然会有马赛克
						else if (0 == frame->nFrameLength) 
						{
							m_bGetIFrame = FALSE;
							continue;
						}
						if (frame->nType == DH_FRAME_TYPE_VIDEO &&
							 frame->nSubType == DH_FRAME_TYPE_VIDEO_I_FRAME) 
						{
							m_bGetIFrame = TRUE;
						}

						//可以取视频数据了
						if (m_bGetIFrame)
						{
							fwrite(frame->pData, 1, frame->nDataLength, m_spFile);
							m_framecount++;
							CString str;
							str.Format(ConvertString("++++++++write count : %d\n"), m_framecount);
						}

					}
				}
			}
#else
			fwrite(pBuffer, 1, dwBufSize, siNode.SavecbFileRaw);
#endif
		}
		break;
	case 1:
		if(siNode.SavecbFileStd)
		{
			fwrite(pBuffer, 1, dwBufSize, siNode.SavecbFileStd);
		}
		break;
	case 2:
		if(siNode.SavecbFileYUV)
		{
			fwrite(pBuffer, 1, dwBufSize, siNode.SavecbFileYUV);
		}
		break;
	case 3:   //音频
		if(siNode.SavecbFilePcm)
		{
			fwrite(pBuffer, 1, dwBufSize, siNode.SavecbFilePcm);
		}
		break;
	default: break;
	}
}

//显示设备列表中当前选项的详细信息
void CNetSDKDemoDlg::DeviceState() 
{
	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
	if (pDev)
	{
		m_ClientStateDlg.SetDevice(pDev);
		m_ClientStateDlg.StartRefresh();
		m_ClientStateDlg.ShowWindow(SW_SHOW);	
	}
}

//打开网络预览
void CNetSDKDemoDlg::OpenMultiplay() 
{
	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
	if(pDev == NULL)
	{
		return;
	}
	
	CPreviewParmsDlg dlg(this, pDev);
	int iRet = dlg.DoModal();
	int channelid = 0;
	DH_RealPlayType rType;
	if (IDOK == iRet)
	{
		channelid = dlg.GetStartChannel();
		rType = dlg.GetRealPlayType();
	}
	else
	{
		return;
	}

	if(/*m_advanceBtnPannel.IsTalkOpen() ||*/ !CheckCurSplitAndClose())
	{
		return;
	}
	
	CWnd *plWnd = m_screenPannel.GetPage(m_curScreen);
	if (!plWnd)
	{
		MessageBox(ConvertString("!error!"));
	}

//	LONG nPlayID = CLIENT_MultiPlay(pDev->LoginID, plWnd->m_hWnd);

	//LONG nPlayID = CLIENT_RealPlayEx(pDev->LoginID, -1, plWnd->m_hWnd/*m_playWnd[m_curScreen].m_hWnd*/, DH_RType_Multiplay);
	LONG nPlayID = CLIENT_RealPlayEx(pDev->LoginID, channelid, plWnd->m_hWnd, rType);
	
	if(!nPlayID)
	{
		LastError();
		AfxMessageBox(ConvertString(MSG_DEMODLG_NOPREVIEW));
		return;
	}
	else
	{
		//禁止语音对讲
		m_advanceBtnPannel.EnableTalk(FALSE);
	}

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
	}

	siNode.Type = SPLIT_TYPE_MULTIPLAY;
	siNode.iHandle = nPlayID;
	siNode.Param  = pDev;

	ret = SetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
	}

	UpdateCurScreenInfo();
	BOOL cbRec = CLIENT_SetRealDataCallBackEx(nPlayID, RealDataCallBackEx, (DWORD)this, 0x0000000F);
	if (!cbRec)
	{
		LastError();
	}
}

void CNetSDKDemoDlg::Sysconfig() 
{
	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
	if(pDev == NULL)
	{
		return;
	}

	MessageBox(ConvertString("Please use the Parameter Config Demo in Sort Application folder , this part of code is stopped maintenance"), ConvertString("prompt"));
	return;

	CConfigMainDlg dlg;
	dlg.SetDevice(pDev);
	dlg.DoModal();
/*
	DeviceNode *nDev;
	In_DeviceInfo m_di;
	CSystemConfig nSyscfgdlg;

	nDev = (DeviceNode *)GetCurDeviceInfo();
	if(nDev == NULL)
	{
		return;
	}
	
	memset(m_di.cDeviceIP ,0, 15);
	*(LONG *)m_di.cDeviceIP = nDev->LoginID;
	memcpy(m_di.cDeviceName , nDev->Name, 20);
	m_di.unAlarmInNum = nDev->Info.byAlarmInPortNum;
	m_di.unAlarmOutNum = nDev->Info.byAlarmOutPortNum;
	m_di.unChannelNum = nDev->Info.byChanNum;
	m_di.unTypeIndex = 1;
	m_di.unVideoCodeType = 8;
	m_di.unNetType = 1;

	nSyscfgdlg.setDeviceId(nDev->LoginID);
	nSyscfgdlg.ShowDefModal(m_di);
*/
}

void CNetSDKDemoDlg::ptzctrl() 
{
	CPtzMenu dlg;

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}
	
	if(siNode.Type != SPLIT_TYPE_MONITOR)
	{
		MessageBox(ConvertString(MSG_DEMODLG_NOTOPENNED));
		return;
	}
	SplitMonitorParam *nParam = (SplitMonitorParam *)siNode.Param;
	LONG iHandle = nParam->pDevice->LoginID;
	int iChannel = nParam->iChannel;

	dlg.SetPtzParam(iHandle, iChannel);
	dlg.DoModal();
}

void CNetSDKDemoDlg::Extptzctrl() 
{
	CExtPtzCtrl dlg;

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	if(siNode.Type != SPLIT_TYPE_MONITOR)
	{
		MessageBox(ConvertString(MSG_DEMODLG_NOTOPENNED));
		return;
	}
	SplitMonitorParam *nParam = (SplitMonitorParam *)siNode.Param;
	LONG iHandle = nParam->pDevice->LoginID;
	int iChannel = nParam->iChannel;

	dlg.SetExtPtzParam(iHandle, iChannel);
	dlg.DoModal();
	
}

//打开透明串口页面
void CNetSDKDemoDlg::Transcom() 
{
	CTransCom dlg;

	DeviceNode *nDev = (DeviceNode *)GetCurDeviceInfo();
	if(nDev == NULL)
	{
		return;
	}
	dlg.SetDeviceId(nDev->LoginID);
	dlg.DoModal();
}


void CNetSDKDemoDlg::UpdateDevice() 
{
	DeviceNode *nDev = (DeviceNode *)GetCurDeviceInfo();
	if(nDev == NULL)
	{
		return;
	}
	CNetUpgrade dlg;
	dlg.SetDevice(nDev);
	dlg.DoModal();
}

//录像控制
void CNetSDKDemoDlg::Recordstate() 
{
	DeviceNode *nDev = (DeviceNode *)GetCurDeviceInfo();
	if(nDev == NULL)
	{
		return;
	}

	CRecordCtrlDlg dlg;
	dlg.SetDeviceId(nDev->LoginID);
	dlg.DoModal();
}

//Io控制
void CNetSDKDemoDlg::AlarmIOctrl() 
{
	DeviceNode *nDev = (DeviceNode *)GetCurDeviceInfo();
	if(nDev == NULL)
	{
		return;
	}
	CAlarmCtrlDlg dlg;

	dlg.SetDeviceId(nDev->LoginID);

	dlg.DoModal();
}


//设备状态
/*
void CNetSDKDemoDlg::OnDeviceWorkstate() 
{
	DeviceNode *nDev = (DeviceNode *)GetCurDeviceInfo();
	if(nDev == NULL)
	{
		return;
	}

	CDeviceWorkState dlg;

	dlg.SetDeviceId(nDev->LoginID);

	dlg.DoModal();
	*/
//	CLIENT_StopUpgrade(0);
/*

	BOOL nRet = CLIENT_SetVolume(g_splitinfo[0].iHandle, 50);
	if(!nRet)
	{
		LastError();
	}	
}
*/

//语音对讲功能
/* Modified by yehao(10857) 2006-12-20*/
BOOL CNetSDKDemoDlg::OpenTalk(BOOL bOpen)
{
	/*Begin: yehao(10857) 2006-12-20*/
	HTREEITEM node_dev, tmpnode;
	DWORD nItem;
	DeviceNode *pInfo = NULL;

	MessageBox(ConvertString("Please use the Talk Demo in Sort Application folder , this part of code is stopped maintenance"), ConvertString("prompt"));
	return FALSE;

	tmpnode = m_devicelist.GetSelectedItem();
	if(!tmpnode)
	{
		MessageBox(ConvertString(MSG_DEMODLG_CHECKSEL));
		return FALSE;
	}
	
	nItem = m_devicelist.GetItemData(tmpnode);
	if(nItem < 16)     //是通道项
	{
		node_dev = m_devicelist.GetParentItem(tmpnode);
		pInfo = (DeviceNode *)m_devicelist.GetItemData(node_dev);
	}
	else              //设备项
	{
		pInfo = (DeviceNode *)nItem;
	}
	
	if (bOpen)
	{
		m_talkhandle.pDevice = pInfo;
		m_talkhandle.lHandle = CLIENT_StartTalkEx(pInfo->LoginID, CNetSDKDemoDlg::AudioDataCallBack, (DWORD)this);
		if (NULL == m_talkhandle.lHandle)
		{
			m_advanceBtnPannel.SetCheckTalk(0);
			m_talkhandle.pDevice = NULL;
			return FALSE;
		}
		/*
		int aaa = 0;
		int bbb = 0;
		BOOL b = CLIENT_QueryDevState(pInfo->LoginID, DH_DEVSTATE_TALK_ECTYPE, (char*)&aaa, sizeof(int), &bbb);
		if (!b)
		{
			bbb = 4;
		}
		*/
		m_normalBtnPannel.EnableMultiplay(FALSE);
		RecordStart();
	}
	else
	{
		RecordStop();
		BOOL bRet = CLIENT_StopTalkEx(m_talkhandle.lHandle);
		if (!bRet)
		{
			MessageBox(ConvertString("Stop talk error"));
		}
		m_advanceBtnPannel.SetCheckTalk(0);
		m_talkhandle.pDevice = NULL;
		m_normalBtnPannel.EnableMultiplay(TRUE);
	}
	/*End: yehao(10857) */
	/*
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox("error while getting split info");
		return FALSE;
	}
	
	if(siNode.Type != SPLIT_TYPE_MONITOR)
	{
		m_advanceBtnPannel.SetCheckTalk(0);
		MessageBox(MSG_DEMODLG_NOTMONITOR);
		return FALSE;
	}

	ret = FALSE;
	if(bOpen)
	{
		ret = CLIENT_StartTalk(siNode.iHandle);
		if(!ret)
		{
			LastError();
			m_advanceBtnPannel.SetCheckTalk(0);
			MessageBox(MSG_DEMODLG_OPENTALKFAILED);
			return FALSE;
		}
		else
		{
			((SplitMonitorParam *)siNode.Param)->isTalkOpen = TRUE;
			m_normalBtnPannel.EnableMultiplay(FALSE);
		}
	}
	else
	{
		ret = CLIENT_StopTalk(siNode.iHandle);
		if(!ret)
		{
			LastError();
			m_advanceBtnPannel.SetCheckTalk(1);
			MessageBox(MSG_DEMODLG_CLOSETALKFAILED);
			return FALSE;
		}
		else
		{
			((SplitMonitorParam *)siNode.Param)->isTalkOpen = FALSE;
			m_normalBtnPannel.EnableMultiplay(TRUE);
		}
	}	
	*/
	return TRUE;
}

/*Begin: Add by yehao(10857) 2006-12-20*/
LONG CNetSDKDemoDlg::GetTalkHandle()
{
	return m_talkhandle.lHandle;
}

BOOL CNetSDKDemoDlg::RecordStart()
{
	BOOL bRet = FALSE;

	if (0 == m_uRecordCount)
	{
		bRet = CLIENT_RecordStart();
	}
	else
	{
		bRet = TRUE;
	}
	if (TRUE == bRet)
	{
		m_uRecordCount++;
	}
//	char buf[100] = {0};
//	sprintf(buf, "record start num is %d \n", m_uRecordCount);
//	OutputDebugString(buf);

	return bRet;
}

BOOL CNetSDKDemoDlg::RecordStop()
{
	BOOL bRet = FALSE;

	if (m_uRecordCount > 0)
	{
		bRet = TRUE;
		m_uRecordCount--;
	}
	if (0 == m_uRecordCount)
	{
		bRet = CLIENT_RecordStop();
		if (FALSE == bRet)
		{
			m_uRecordCount++;
		}
	}
//	char buf[100] = {0};
//	sprintf(buf, "record stop num is %d \n", m_uRecordCount);
//	OutputDebugString(buf);

	return bRet;
}

void CNetSDKDemoDlg::AudioDataCallBack(LLONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, LDWORD dwUser)
{
	CNetSDKDemoDlg *pdlg = (CNetSDKDemoDlg *)dwUser;
	if (lTalkHandle != pdlg->GetTalkHandle())
	{
		return;
	}
	static int num = 0;
	char buf[100] = {0};
	LONG lRet = -1;
	switch (byAudioFlag)
	{
	case 0:
		lRet = CLIENT_TalkSendData(lTalkHandle, pDataBuf, dwBufSize);
		sprintf(buf, ConvertString("current num is %d \n"), num);
		num++;
//		OutputDebugString(buf);
		if (lRet != dwBufSize)
		{
		}
		break;
	case 1:
		CLIENT_AudioDec(pDataBuf, dwBufSize);
		break;
	default:
		break;
	}
}
/*End: yehao(10857) */
//是否保存回调原始数据
void CNetSDKDemoDlg::SavecbdataRaw(int nCheck) 
{
	CPlayWnd *plWnd = (CPlayWnd *)m_screenPannel.GetPage(m_curScreen);
	if (!plWnd)
	{
		MessageBox(ConvertString("we have a big error here!"));
		return;
	}
	
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	CString strName ;
	if(nCheck > 0)
	{
		strName.Format("cbdata %d.bin",m_curScreen);
		CFileDialog dlg(FALSE,"*.bin",strName.GetBuffer(0),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		"All File(*.bin)|*.*||",this);
		if(dlg.DoModal() == IDOK)
		{
			strName = dlg.GetPathName();
			FILE *file = fopen(strName.GetBuffer(0),"wb");
			if(!file)
			{
				MessageBox(ConvertString(MSG_DEMODLG_OPENFILEFAILED));
				m_saveDataPannel.SetCheckRaw(0);
			}
			plWnd->SetSplitCBFile_Raw(file);
			
#ifdef DH_STREAMPARSER
			m_spFile = file;
#endif
		}
		else
		{
			return;
		}
	}
	else
	{
		if(siNode.SavecbFileRaw)
		{
			fclose(siNode.SavecbFileRaw);
			plWnd->SetSplitCBFile_Raw(NULL);
		}
	}
}

void CNetSDKDemoDlg::SavecbdataStd(int nCheck) 
{
	CPlayWnd *plWnd = (CPlayWnd *)m_screenPannel.GetPage(m_curScreen);
	if (!plWnd)
	{
		MessageBox(ConvertString("we have a big error here!"));
		return;
	}
	
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	CString strName ;
	if(nCheck > 0)
	{
		strName.Format("cbdata %d.dav",m_curScreen);
		CFileDialog dlg(FALSE,"*.dav",strName.GetBuffer(0),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		"All File(*.dav)|*.*||",this);
		if(dlg.DoModal() == IDOK)
		{
			strName = dlg.GetPathName();
			FILE *file = fopen(strName.GetBuffer(0),"wb");
			if(!file)
			{
				MessageBox(ConvertString(MSG_DEMODLG_OPENFILEFAILED));
				m_saveDataPannel.SetCheckStd(0);
			}
			plWnd->SetSplitCBFile_Std(file);
		}
		else
		{
			return;
		}
	}
	else
	{
		if(siNode.SavecbFileStd)
		{
			fclose(siNode.SavecbFileStd);
			plWnd->SetSplitCBFile_Std(NULL);
		}
	}
}

void CNetSDKDemoDlg::Savecbdatapcm(int nCheck) 
{
	CPlayWnd *plWnd = (CPlayWnd *)m_screenPannel.GetPage(m_curScreen);
	if (!plWnd)
	{
		MessageBox(ConvertString("we have a big error here!"));
		return;
	}
	
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}

	CString strName ;
	if(nCheck > 0)
	{
		strName.Format("cbdata %d.pcm",m_curScreen);
		CFileDialog dlg(FALSE,"*.pcm",strName.GetBuffer(0),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		"All File(*.pcm)|*.*||",this);
		if(dlg.DoModal() == IDOK)
		{
			strName = dlg.GetPathName();
			FILE *file = fopen(strName.GetBuffer(0),"wb");
			if(!file)
			{
				MessageBox(ConvertString(MSG_DEMODLG_OPENFILEFAILED));
				m_saveDataPannel.SetCheckPcm(0);
			}
			plWnd->SetSplitCBFile_Pcm(file);
		}
		else
		{
			return;
		}
	}
	else
	{
		if(siNode.SavecbFilePcm)
		{
			fclose(siNode.SavecbFilePcm);
			plWnd->SetSplitCBFile_Pcm(NULL);
		}
	}
}

void CNetSDKDemoDlg::Savecbdatayuv(int nCheck) 
{
	CPlayWnd *plWnd = (CPlayWnd *)m_screenPannel.GetPage(m_curScreen);
	if (!plWnd)
	{
		MessageBox(ConvertString("we have a big error here!"));
		return;
	}
	
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}
	
	CString strName ;
	if(nCheck > 0)
	{
		strName.Format("cbdata %d.yuv",m_curScreen);
		CFileDialog dlg(FALSE,"*.yuv",strName.GetBuffer(0),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		"All File(*.yuv)|*.*||",this);
		if(dlg.DoModal() == IDOK)
		{
			strName = dlg.GetPathName();
			FILE *file = fopen(strName.GetBuffer(0),"wb");
			if(!file)
			{
				MessageBox(ConvertString(MSG_DEMODLG_OPENFILEFAILED));
				m_saveDataPannel.SetCheckYuv(0);
			}
			plWnd->SetSplitCBFile_Yuv(file);
		}
		else
		{
			return;
		}
	}
	else
	{
		if(siNode.SavecbFileYUV)
		{
			fclose(siNode.SavecbFileYUV);
			plWnd->SetSplitCBFile_Yuv(NULL);
		}
	}
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	return TRUE; 
}

void CNetSDKDemoDlg::CycleMonitor()
{
	CCycleMonitor dlg;

	if (dlg.DoModal() == IDOK) 
	{
		SplitInfoNode siNode;
		memset(&siNode, 0, sizeof(siNode));

//		EnterCriticalSection(&g_csCycle);
		//刷新画面，如果有画面被关闭了可以正常显示
		CPlayWnd *plWnd;
		for (int curWin = 0; curWin < DH_MAX_CHANNUM; curWin++)
		{
			plWnd = (CPlayWnd *)m_screenPannel.GetPage(curWin);
			if (plWnd)
			{
				plWnd->PostMessage(VIDEO_REPAINT);
			}
			plWnd->PostMessage(VIDEO_REPAINT);
		}

		for (int screenNo = 0; screenNo < DH_MAX_CHANNUM; screenNo++)
		{
			KillTimer(screenNo);
			
			BOOL ret = GetSplitInfo_Main(screenNo, &siNode);
			if (!ret)
			{
				MessageBox(ConvertString("error while getting split info"));
				return;
			}
			//判断是否轮循类型
			if (siNode.Type == SPLIT_TYPE_CYCLEMONITOR)
			{
				POSITION pos = ((SplitCycleParam *)siNode.Param)->pChannelList->GetHeadPosition();
				CycleChannelInfo *tempnode = (CycleChannelInfo *)((SplitCycleParam *)siNode.Param)->pChannelList->GetNext(pos);
				
				DeviceNode *pDev = (DeviceNode *)tempnode->dwDeviceID;
				((SplitCycleParam *)siNode.Param)->pDevice = pDev;
				LONG nID = pDev->LoginID;
				int nCh = tempnode->iChannel;
				
				CWnd *plWnd = m_screenPannel.GetPage(screenNo);
				if (!plWnd)
				{
					MessageBox(ConvertString("!!error!!"));
					return;
				}
				
				//用户选择1个通道，相当于打开1个监视通道
				//test，无论通道多少，一视同仁
				if (FALSE/*((SplitCycleParam *)siNode.Param)->iChannelCount == 1*/)
				{	
					LONG nChannelID = CLIENT_RealPlay(nID, nCh, plWnd->m_hWnd/*m_playWnd[screenNo].m_hWnd*/);
					if(!nChannelID)
					{
						LastError();
						KillTimer(screenNo);
						MessageBox(ConvertString(MSG_CYCLE_OPENCHANNELFAILED));
						if (siNode.Param) 
						{
							DeleteCycleParam(screenNo);
						}
						continue;
					}
					//设置轮循位置为第一个
					((SplitCycleParam *)siNode.Param)->iCurPosition = 0;
					//获取视频参数
					byte bVideo[4];
					BOOL nRet = CLIENT_ClientGetVideoEffect(nChannelID, &bVideo[0],&bVideo[1],&bVideo[2],&bVideo[3]);
					if (!nRet)
					{
						LastError();
					}
					siNode.nVideoParam.dwParam = *(DWORD *)bVideo;
					((CPlayWnd *)plWnd)->SetSplitHandle(nChannelID);
					continue;
				}
				//用户选择了2个或2个以上通道，开始轮循
				else
				{
// 					if(siNode.iHandle != 0)
// 					{
// 						//设置轮循计时器，将秒转换为毫秒
// 						UINT interval = ((SplitCycleParam *)siNode.Param)->iInterval;
// 						SetTimer((UINT)screenNo, interval * 1000, NULL);
// 						UpdateCurScreenInfo();
// 						return;
// 					}

					LONG nChannelID = CLIENT_RealPlay(nID, nCh, plWnd->m_hWnd/*m_playWnd[screenNo].m_hWnd*/);
					if(!nChannelID)
					{
						LastError();
						KillTimer(screenNo);
						MessageBox(ConvertString(MSG_CYCLE_OPENCHANNELFAILED));
						if (siNode.Param) 
						{
							DeleteCycleParam(screenNo);
						}
						continue;
					}
					
					//设置轮循位置为第一个
					((SplitCycleParam *)siNode.Param)->iCurPosition = 0;

					//获取视频参数
					byte bVideo[4];
					BOOL nRet = CLIENT_ClientGetVideoEffect(nChannelID, &bVideo[0],&bVideo[1],&bVideo[2],&bVideo[3]);
					if (!nRet)
					{
						LastError();
					}
					siNode.nVideoParam.dwParam = *(DWORD *)bVideo;
					((CPlayWnd *)plWnd)->SetSplitHandle(nChannelID);
					
					//设置轮循计时器，将秒转换为毫秒
					UINT interval = ((SplitCycleParam *)siNode.Param)->iInterval;
					SetTimer((UINT)screenNo, interval * 1000, NULL);
					UpdateCurScreenInfo();
				}
			}
		}//end of for (int screenNo = 0; screenNo < DH_MAX_CHANNUM; screenNo++)
	//LeaveCriticalSection(&g_csCycle);
	}
}

int WriteAlarmLogFunc(const AlarmNode& node, DWORD dwUser)
{
	CNetSDKDemoDlg* pThis = (CNetSDKDemoDlg*)dwUser;
	if (!pThis)
	{
		return 1;
	}
	
	return pThis->WriteAlarmLogFunc_Imp(node);
}

int CNetSDKDemoDlg::WriteAlarmLogFunc_Imp(const AlarmNode& node)
{
	if (!m_almLogFile_Comm || !m_almLogFile_Shelter || !m_almLogFile_dFull
		|| !m_almLogFile_dError || !m_almLogFile_SoundDec) 
	{
		return 1;
	}

	CString strNewLog = "";
	CString strAlmTime;
	strAlmTime.Format(ConvertString("upgrade time:%d-%d-%d,%d:%d:%d\n"),
		node.timeStamp.GetYear(), node.timeStamp.GetMonth(), node.timeStamp.GetDay(),
		node.timeStamp.GetHour(), node.timeStamp.GetMinute(), node.timeStamp.GetSecond());
	strNewLog += strAlmTime;
//	CString strAlmType;
	CString strAlmContent = (ConvertString("information:\n"));
	CString strTemp;
	BOOL isAlarm = FALSE; //确定是否有新的报警
	switch(node.alarmType)
	{
	case DH_COMM_ALARM:
//	case DH_ALARM_ALARM_EX:
//	case DH_MOTION_ALARM_EX:
//	case DH_VIDEOLOST_ALARM_EX:
		{
			//strAlmType.Format("报警类型：常规\n");
			//alarm input
			int i = 0;
			for(i = 0; i < 16; i++)
			{
			//	if (node.state.alarmout[i] != m_lastAlarm.alarmout[i])
				if (node.state.cState.alarm[i] != m_lastAlarm.cState.alarm[i])
				{
				//	if (m_lastAlarm.alarmout[i]) //alarm i is gone
					if (m_lastAlarm.cState.alarm[i]) //alarm i is gone
					{
						strTemp.Format(ConvertString("Alarm end, alarm:  channel No.:%d\n"), i+1);
					}
					else //new alarm 
					{
						strTemp.Format(ConvertString("Alarm start, alram: channel No.:%d\n"), i+1);
					}
					isAlarm = TRUE;
					strAlmContent += strTemp;
				}
			}
			if (m_almLogFile_Comm && isAlarm)
			{
				strNewLog += strAlmContent + "\n";
				fwrite(strNewLog.GetBuffer(0), strNewLog.GetLength(), 1, m_almLogFile_Comm);
				fflush(m_almLogFile_Comm);
			}

			//motion detect
			if (isAlarm)
			{
				strNewLog = "";
			}
			CString strAlmContent = "";
			isAlarm = FALSE;
			for (i = 0; i < 16; i++)
			{
			//	if (node.state.motion[i] != m_lastAlarm.motion[i])
				if (node.state.cState.motiondection[i] != m_lastAlarm.cState.motiondection[i])
				{
				//	if (m_lastAlarm.motion[i]) //alarm i is gone
					if (m_lastAlarm.cState.motiondection[i]) //alarm i is gone
					{
						strTemp.Format(ConvertString("Alarm end, motion alarm: channel No.:%d\n"), i+1);
					}
					else //new alarm 
					{
						strTemp.Format(ConvertString("Alarm start, motion alarm: channel No.:%d\n"), i+1);
					}
					isAlarm = TRUE;
					strAlmContent += strTemp;
				}
			}
			if (m_almLogFile_Comm && isAlarm)
			{
				strNewLog += strAlmContent + "\n";
				fwrite(strNewLog.GetBuffer(0), strNewLog.GetLength(), 1, m_almLogFile_Comm);
				fflush(m_almLogFile_Comm);
			}

			//video lost
			if (isAlarm)
			{
				strNewLog = "";
			}
			strAlmContent = "";
			isAlarm = FALSE;
			for (i = 0; i < 16; i++)
			{
			//	if (node.state.videolost[i] != m_lastAlarm.videolost[i])
				if (node.state.cState.videolost[i] != m_lastAlarm.cState.videolost[i])
				{
				//	if (m_lastAlarm.videolost[i]) //alarm i is gone
					if (m_lastAlarm.cState.videolost[i]) //alarm i is gone
					{
						strTemp.Format(ConvertString("Alarm end, video lost alarm: channel No.:%d\n"), i+1);
					}
					else //new alarm 
					{
						strTemp.Format(ConvertString("Alarm start, video lost alarm: channel No.:%d\n"), i+1);
					}
					isAlarm = TRUE;
					strAlmContent += strTemp;
				}
			}
			if (m_almLogFile_Comm && isAlarm)
			{
				strNewLog += strAlmContent + "\n";
				fwrite(strNewLog.GetBuffer(0), strNewLog.GetLength(), 1, m_almLogFile_Comm);
				fflush(m_almLogFile_Comm);
			}
		}
		break;
	case DH_SHELTER_ALARM:
//	case DH_SHELTER_ALARM_EX:
		{
		//	strAlmType.Format("报警类型：遮挡\n");
			for (int i = 0; i < 16; i++)
			{
				if (node.state.shelter[i] != m_lastAlarm.shelter[i])
				{
					if (m_lastAlarm.shelter[i]) //alarm i is gone
					{
						strTemp.Format(ConvertString("Alarm end, shelter alarm: channel No.:%d\n"), i+1);
					}
					else //new alarm 
					{
						strTemp.Format(ConvertString("Alarm start, shelter alarm: channel No.:%d\n"), i+1);
					}
					isAlarm = TRUE;
					strAlmContent += strTemp;
				}
			}
			if (m_almLogFile_Shelter && isAlarm)
			{
				strNewLog += strAlmContent + "\n";
				fwrite(strNewLog.GetBuffer(0), strNewLog.GetLength(), 1, m_almLogFile_Shelter);
				fflush(m_almLogFile_Shelter);
			}
		}
		break;
	case DH_DISK_FULL_ALARM:
//	case DH_DISKFULL_ALARM_EX:
		{
		//	strAlmType.Format("报警类型：硬盘满\n");
		//	if (node.state.dFull != m_lastAlarm.dFull)
			{
			//	if (node.state.diskfull) //disk full
				if (node.state.dFull) //disk full
				{
					strTemp.Format(ConvertString("Alarm, Disk full\n"));
					isAlarm = TRUE;
					strAlmContent += strTemp;
				}
				else //disk full alarm is gone
				{
				//	strTemp.Format("报警消失！硬盘满\n");
				}
			}
			if (m_almLogFile_dFull && isAlarm)
			{
				strNewLog += strAlmContent + "\n";
				fwrite(strNewLog.GetBuffer(0), strNewLog.GetLength(), 1, m_almLogFile_dFull);
				fflush(m_almLogFile_dFull);
			}
		}
		break;
	case DH_DISK_ERROR_ALARM:
//	case DH_DISKERROR_ALARM_EX:
		{
		//	strAlmType.Format("报警类型：坏硬盘\n");
			for (int i = 0; i < 32; i++)
			{
				DWORD dwDE = node.state.dError ^ m_lastAlarm.dError;
			//	if (node.state.diskerror[i] != m_lastAlarm.diskerror[i])
				if (dwDE & (0x01<<i))
				{
					if (m_lastAlarm.dError & (0x01<<i)) //disk error alarm is gone
					{
						strTemp.Format(ConvertString("Alarm end, Disk error alarm %d\n"), i+1);
					}
					else
					{
						strTemp.Format(ConvertString("Alarm start, Disk error alarm %d\n"), i+1);
					}
					isAlarm = TRUE;
					strAlmContent += strTemp;
				}
			}
			if (m_almLogFile_dError && isAlarm)
			{
				strNewLog += strAlmContent + "\n";
				fwrite(strNewLog.GetBuffer(0), strNewLog.GetLength(), 1, m_almLogFile_dError);
				fflush(m_almLogFile_dError);
			}
		}
		break;
	case DH_SOUND_DETECT_ALARM:
//	case DH_SOUND_DETECT_ALARM_EX:
		{
		//	strAlmType.Format("报警类型：音频检测\n");
			for (int i = 0; i < 16; i++)
			{
				if (node.state.soundalarm[i] != m_lastAlarm.soundalarm[i])
				{
					if (m_lastAlarm.soundalarm[i]) //alarm i is gone
					{
						strTemp.Format(ConvertString("Alarm end, sound detect alarm: channel No.:%d\n"), i+1);
					}
					else //new alarm 
					{
						strTemp.Format(ConvertString("Alarm start, sound detect alarm:channel No.:%d\n"), i+1);
					}
					isAlarm = TRUE;
					strAlmContent += strTemp;
				}
			}
			if (m_almLogFile_SoundDec && isAlarm)
			{
				strNewLog += strAlmContent + "\n";
				fwrite(strNewLog.GetBuffer(0), strNewLog.GetLength(), 1, m_almLogFile_SoundDec);
				fflush(m_almLogFile_SoundDec);
			}
		}
		break;
	default:
		return 1;
	}
	
	memcpy(&m_lastAlarm, &node.state, sizeof(DEV_STATE));
	return 0;
}

void CNetSDKDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	//刷新播放放进度条
	CDialog::OnTimer(nIDEvent);
	
	if (nIDEvent >= 0 && nIDEvent <= CUR_MAXCHAN)
	{
		NextCycleMonitor(nIDEvent);
	}
	else if (nIDEvent == ALARMLOG) 
	{
		CDevMgr::GetDevMgr().For_EachAlmNode(WriteAlarmLogFunc, (DWORD)this);		
	/*	//listen devide test
		if (m_mylsdata.state == 1)
		{
			NET_DEVICEINFO info = {0};
		//	int error;
			BOOL b = CLIENT_ResponseDevReg(m_mylsdata.serial, m_mylsdata.ip, m_mylsdata.port, true);
			if (b) 
			{
			//	m_lListenDevice = CLIENT_LoginEx(m_mylsdata.ip, m_mylsdata.port, "admin", "admin", 2, m_mylsdata.serial, &info, &error);
			//	if (!m_lListenDevice)
			//	{
			//		MessageBox("login failed!");
			//	}
			}
			if (m_lListenDevice)
			{//test disconnect
				//	MessageBox("1!");
			//	m_lListenChannel = CLIENT_RealPlayEx(m_lListenDevice, 0, m_screenPannel.GetPage(0)->m_hWnd);
			//	if (!m_lListenDevice)
			//	{
			//		MessageBox("open channel failed!");
			//	}
			//	MessageBox("1");
			}
		}
		*/
	}
	else if (nIDEvent == UPDATATREE)
	{
		if (g_bUpdataTree)
		{
			g_bUpdataTree = FALSE;

			UpdateDeviceList();
		}
	}
}


void CNetSDKDemoDlg::Getversion() 
{
	CString strCptn;
	GetWindowText(strCptn);

	LONG lVer = CLIENT_GetSDKVersion();

// 	int bVer[4] = {0};
// //	bVer[0] = (byte)lVer;
// 	bVer[1] = (int)((lVer)&0xFFFF);
// 	bVer[2] = (int)((lVer>>16)&0xFF);
// 	bVer[3] = (int)((lVer>>24)&0xFF);
	CString strVerTmp, strVer;
	strVerTmp.Format("%ld", lVer);
	strVer = strVerTmp.Left(1) + "." + strVerTmp.Right(strVerTmp.GetLength()-1).Left(2)+"."+strVerTmp.Right(strVerTmp.GetLength()-3);
	strVer = ConvertString(MSG_VERSION) + strVer;
	strCptn += strVer;
	
	SetWindowText(strCptn);
	/*
	MessageBox(strVer);
	*/
}

/*Begin: Add by yehao(10857) For Task.NO.11071 2006-12-23*/
void CNetSDKDemoDlg::OpenAudioBroadcastDlg()
{
	DeviceNode *ptmpDevNode = NULL;
	HTREEITEM tmphandle = m_devicelist.GetRootItem();
	int num = 0;
	m_audioBroadcastDlg.m_AllDevList.clear();
	m_audioBroadcastDlg.m_BroadcastDevList.clear();
	while (tmphandle)
	{
		ptmpDevNode = (DeviceNode *)m_devicelist.GetItemData(tmphandle);
		m_audioBroadcastDlg.m_AllDevList.push_back(ptmpDevNode);
		tmphandle = m_devicelist.GetNextItem(tmphandle, TVGN_NEXT);
	}
	
	list<DeviceNode *>::iterator it = m_broadcastDevList.begin();
	for (; it != m_broadcastDevList.end(); it++)
	{
		list<DeviceNode *>::iterator itt = m_audioBroadcastDlg.m_AllDevList.begin();
		for (; itt != m_audioBroadcastDlg.m_AllDevList.end(); itt++)
		{
			if (LONG(*it) == LONG(*itt))
			{
				m_audioBroadcastDlg.m_BroadcastDevList.push_back((*it));
				m_audioBroadcastDlg.m_AllDevList.erase(itt);
				break;
			}
		}
	}
	m_audioBroadcastDlg.m_bRecord = m_bRecord;
	int iRet = m_audioBroadcastDlg.DoModal();

	if (IDOK == iRet)
	{
		if (m_bRecord != m_audioBroadcastDlg.m_bRecord)
		{
			m_bRecord = m_audioBroadcastDlg.m_bRecord;
			if (m_bRecord)
			{
				RecordStart();
			}
			else
			{
				RecordStop();
			}
		}
		BOOL find = FALSE;
		{
			list<DeviceNode *>::iterator it = m_broadcastDevList.begin();
			for (; it != m_broadcastDevList.end(); it++)
			{
				find = FALSE;
				list<DeviceNode *>::iterator itt = m_audioBroadcastDlg.m_BroadcastDevList.begin();
				for (; itt != m_audioBroadcastDlg.m_BroadcastDevList.end(); itt++)
				{
					if (LONG(*it) == LONG(*itt))
					{
						find = TRUE;
						break;
					}
				}
				if (FALSE == find)
				{
					CLIENT_AudioBroadcastDelDev((*it)->LoginID);
				}
			}
		}

		{
			list<DeviceNode *>::iterator it = m_audioBroadcastDlg.m_BroadcastDevList.begin();
			for (; it != m_audioBroadcastDlg.m_BroadcastDevList.end(); it++)
			{
				find = FALSE;
				list<DeviceNode *>::iterator itt = m_broadcastDevList.begin();
				for (; itt != m_broadcastDevList.end(); itt++)
				{
					if (LONG(*it) == LONG(*itt))
					{
						find = TRUE;
						break;
					}
				}
				if (FALSE == find)
				{
					CLIENT_AudioBroadcastAddDev((*it)->LoginID);
				}
			}
		}

		{
			m_broadcastDevList.clear();
			list<DeviceNode *>::iterator it = m_audioBroadcastDlg.m_BroadcastDevList.begin();
			for (; it != m_audioBroadcastDlg.m_BroadcastDevList.end(); it++)
			{
				m_broadcastDevList.push_back(*it);
			}
		}
	}
	else
	{
	}

	return;
}
/*End: yehao(10857) Task.NO.11071 */
HBRUSH CNetSDKDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_TREE_DEVICELIST)
	{
		return m_myBrush;
	}
	return hbr;
}

void CNetSDKDemoDlg::Sysconfig2() 
{
	DeviceNode *pDev;
	In_DeviceInfo m_di;
	CSystemConfig nSyscfgdlg;
	
	pDev = (DeviceNode *)GetCurDeviceInfo();
	if(pDev == NULL)
	{
		return;
	}

//	memset(m_di.cDeviceIP ,0, 15);
	m_di.lDeviceID = pDev->LoginID;
	memcpy(m_di.cDeviceName , pDev->Name, 20);
	m_di.unAlarmInNum = pDev->Info.byAlarmInPortNum;
	m_di.unAlarmOutNum = pDev->Info.byAlarmOutPortNum;
	m_di.unChannelNum = pDev->Info.byChanNum;
	m_di.unTypeIndex = (pDev->Info.byDVRType == NET_DVR_MPEG4_NVSII) ? 2 : 1;
	m_di.unVideoCodeType = 8;
	m_di.unNetType = 1;
	
	nSyscfgdlg.setDeviceId(pDev->LoginID);
	nSyscfgdlg.ShowDefModal(m_di);
}

void CNetSDKDemoDlg::Playbackbytime() 
{
	CPlayBackByTime dlg;
showBTwindow:
	if (dlg.DoModal() == IDOK) 
	{
		if(!CheckCurSplitAndClose())
		{
			MessageBox(ConvertString("Error: Cannot close current screen!"));
			return;
		}		
		PlayBackByTimeInfo *tmpinfo = dlg.GetPlayBackInfo();
		
		NET_RECORDFILE_INFO ri;
		ZeroMemory(&ri, sizeof(ri));
		ri.starttime = tmpinfo->starttime;
		ri.endtime   = tmpinfo->endtime;
	
	/*	LONG lPlayID = CLIENT_PlayBackByRecordFile(tmpinfo->pDevice->LoginID, &ri, 
			GetDlgItem(IDC_SCREEN1 + m_curScreen )->m_hWnd, 0,0);
	*/

	//	LONG lPlayID = CLIENT_PlayBackByTime(tmpinfo->pDevice->LoginID, tmpinfo->nChannel, 
	//		&tmpinfo->starttime, &tmpinfo->endtime, GetDlgItem(IDC_SCREEN1 + m_curScreen )->m_hWnd, PlayCallBack, (DWORD)this);
		
		CWnd *plWnd = m_screenPannel.GetPage(m_curScreen);
		if (!plWnd)
		{
			MessageBox(ConvertString("!!error!!"));
			return;
		}

		LONG lPlayID = CLIENT_PlayBackByTimeEx(tmpinfo->pDevice->LoginID, tmpinfo->nChannel, 
			&tmpinfo->starttime, &tmpinfo->endtime, plWnd->m_hWnd/*m_playWnd[m_curScreen].m_hWnd*/, 
			PlayCallBack, (DWORD)this,PBDataCallBack, (DWORD)this);
		
		if(!lPlayID)
		{
			LastError();
			MessageBox(ConvertString(MSG_DEMODLG_PLAYFAILED));
			goto showBTwindow;
		}
		else
		{  //如果其它通道没有打开音频，则打开音频
			if (m_curSoundSplit < 0)
			{
				if (FALSE == CLIENT_OpenSound(lPlayID)) 
				{
					LastError();
					MessageBox(ConvertString(MSG_OPENSOUNDFAILED));
					m_advanceBtnPannel.SetCheckSound(0);
				}
				else
				{
					m_advanceBtnPannel.SetCheckSound(1);
					m_curSoundSplit = m_curScreen;
				}
			}
		}

		SplitInfoNode siNode;
		memset(&siNode, 0, sizeof(siNode));
		BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while getting split info"));
		}

		siNode.Type = SPLIT_TYPE_PBBYTIME;
		siNode.iHandle = lPlayID;

		SplitPBByTimeParam *nparam	= new SplitPBByTimeParam;
		nparam->pDevice = tmpinfo->pDevice;
		nparam->nChannel = tmpinfo->nChannel;
		nparam->starttime = tmpinfo->starttime;
		nparam->endtime = tmpinfo->endtime;

		siNode.Param  = nparam;

		ret = SetSplitInfo_Main(m_curScreen, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while setting split info"));
		}
		//时间播放的进度条目前不做
//		m_play_position.EnableWindow(FALSE);

		m_playctrlPannel.StartPlay();
		UpdateCurScreenInfo();
	}
}

void CNetSDKDemoDlg::Downloadbytime() 
{
	m_dbByTime.CenterWindow();
	m_dbByTime.ShowWindow(SW_SHOW);
}

void CNetSDKDemoDlg::RebootDevice() 
{
	DeviceNode *nDev = (DeviceNode *)GetCurDeviceInfo();
	if (NULL == nDev)
	{
		return;
	}
	BOOL bRet = CLIENT_RebootDev(nDev->LoginID);
	if (!bRet)
	{
		LastError();
		MessageBox(ConvertString(MSG_DEMODLG_REBOOTFAILED));
	}
	else
	{
		MessageBox(ConvertString(MSG_DEMODLG_REBOOTDONE));
	}
}

void CNetSDKDemoDlg::ShutdownDevice() 
{
	DeviceNode *nDev = (DeviceNode *)GetCurDeviceInfo();
	if (NULL == nDev)
	{
		return;
	}
	BOOL bRet = CLIENT_ShutDownDev(nDev->LoginID);
	if (!bRet)
	{
		LastError();
		MessageBox(ConvertString(MSG_DEMODLG_SHUTDOWNFAILED));
	}
	else
	{
		MessageBox(ConvertString(MSG_DEMODLG_SHUTDOWNDONE));
	}
}


void CNetSDKDemoDlg::DDNS_QueryIP() 
{
	CDDNS_QueryIP dlg;
	dlg.DoModal();
}

void CNetSDKDemoDlg::OnDblclkTreeDevicelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OpenChannel();
	*pResult = 0;
}

void CNetSDKDemoDlg::OpenAllChannel(DeviceNode *pInfo, DH_RealPlayType subtype) 
{
	LONG nChannelID = 0;

	ProcessCloseAllChannel(pInfo);
	
	LONG nID = pInfo->LoginID;
	int chNum = pInfo->Info.byChanNum;
	
	int ScreenNum = CUR_MAXCHAN;//本SDK现在所能显示的最大画面数
	int FreeScreen = 0;
	DWORD freeFlag = 0;

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));

	if(chNum > CUR_MAXCHAN)//设备返回通道数>SDK显示通道数
	{
		for(int ii = 0 ; ii < CUR_MAXCHAN ; ii++)
    	{
			if (ProcessCloseScreen(ii)) 
			{
				freeFlag |= (0x00000001 << ii);
			}
		}
		FreeScreen = CUR_MAXCHAN;
		UpdateCurScreenInfo();
	}
	else 
	{
		for(int ii = 0 ; ii< CUR_MAXCHAN; ii++)
		{
			BOOL ret = GetSplitInfo_Main(ii, &siNode);
			if (!ret)
			{
				MessageBox(ConvertString("error while getting split info"));
			}
			if(SPLIT_TYPE_NULL == siNode.Type)
			{
				freeFlag |= (0x00000001 << ii);
				FreeScreen ++;
			}
		}
		if((chNum > FreeScreen))//空余画面数<设备返回通道数
		{
			int killNum = chNum - FreeScreen;
			for (int ii = 0 ; ii < CUR_MAXCHAN; ii ++)
			{		
				if(killNum && !(freeFlag & (0x00000001 << ii)))
				{
					if (ProcessCloseScreen(ii))
					{
						freeFlag |= (0x00000001 << ii);
						FreeScreen ++;
					}
					killNum --;
				}
			}
			UpdateCurScreenInfo();
		}
	}

	int nCh = 0;
	for (int nScrn = 0; nScrn < CUR_MAXCHAN; nScrn++)
	{
		if (((freeFlag >> nScrn)& 0x00000001) && (nCh < FreeScreen) && (nCh < chNum))
		{
			OpenSingleChannel(pInfo, nCh, nScrn, subtype);
			nCh++;
		}
	}
//	m_normalBtnPannel.SetSplit(CUR_SPLIT);
	//	m_curScreen = 0;
//	m_screenPannel.SetShowPlayWin(CUR_SPLIT, 0);
	//	UpdateScreen(CUR_SPLIT + 1);
}

BOOL CNetSDKDemoDlg::ProcessCloseAllChannel(DeviceNode *pInfo) 
{
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));

	LONG nID = pInfo->LoginID;
	LONG curID = 0;
	BOOL ret = TRUE;
	for(int i = 0 ; i < CUR_MAXCHAN; i++)
    {
		BOOL ret = GetSplitInfo_Main(i, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while getting split info"));
			return FALSE;
		}

		if(SPLIT_TYPE_NULL == siNode.Type)
		{
			continue;
		}
		else if(SPLIT_TYPE_MONITOR == siNode.Type)
		{
			SplitMonitorParam *mParam = (SplitMonitorParam *)siNode.Param;
			curID = mParam->pDevice->LoginID;
		}
		else if (SPLIT_TYPE_NETPLAY == siNode.Type)
		{
			SplitNetPlayParam *nParam = (SplitNetPlayParam *)siNode.Param; 
			curID = nParam->pFileInfo->pDevice->LoginID;
		}
		else if (SPLIT_TYPE_MULTIPLAY == siNode.Type)
		{
			curID = ((DeviceNode *)siNode.Param)->LoginID;
		}
		else if (SPLIT_TYPE_CYCLEMONITOR == siNode.Type)
		{
			SplitCycleParam *mParam = (SplitCycleParam *)siNode.Param;
			curID = mParam->pDevice->LoginID;
		}
		else if (SPLIT_TYPE_PBBYTIME == siNode.Type)
		{
			SplitPBByTimeParam *mParam = (SplitPBByTimeParam *)siNode.Param;
			curID = mParam->pDevice->LoginID;
		}
		
		if (nID == curID)
		{
			if (!ProcessCloseScreen(i))
			{
				ret = FALSE;
			}
			else
			{
				CPlayWnd *plWnd = (CPlayWnd *)m_screenPannel.GetPage(i);
				if (!plWnd)
				{
					MessageBox(ConvertString("!!big error!!"));
					return FALSE;
				}
				plWnd->PostMessage(VIDEO_REPAINT);
			}
		}
		curID = 0;
	}
	UpdateCurScreenInfo();
	
	return ret;
}

void CNetSDKDemoDlg::SwitchFullScreen() 
{
	m_screenPannel.SetFullScreen(!m_screenPannel.GetFullScreen());
}

//void CNetSDKDemoDlg::ReturnOrignalSplit()
//{
//	if (m_bFullSCRN) 
//	{
//		SwitchFullScreen();
//	}
//}

//打开轮循列表中下一个通道
void CNetSDKDemoDlg::NextCycleMonitor(UINT nID)	
{
//	EnterCriticalSection(&g_csCycle);

	UINT nScreen = nID;
	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = GetSplitInfo_Main(nScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
		return;
	}
	if (siNode.Type != SPLIT_TYPE_CYCLEMONITOR || NULL == siNode.Param)
	{
		return;
	}
	//取轮循列表的下一个通道值
	CycleChannelInfo *tempnode;
	POSITION nPos = ((SplitCycleParam *)siNode.Param)->pChannelList->GetHeadPosition();
	tempnode = (CycleChannelInfo *)((SplitCycleParam *)siNode.Param)->pChannelList->GetNext(nPos);
	int nextPosition = ((SplitCycleParam *)siNode.Param)->iCurPosition + 1;
	//如果已经到了列表末尾，则返回列表头
	if (nextPosition >= ((SplitCycleParam *)siNode.Param)->iChannelCount)
	{
		nextPosition = 0;
	}
	else	
	{
		//否则取下一个
		for (int x = 0; x < nextPosition; x++)
		{
			tempnode = (CycleChannelInfo *)((SplitCycleParam *)siNode.Param)->pChannelList->GetNext(nPos);
		}
	}
	
	ret = TRUE;
	if (siNode.iHandle != 0) 
	{
		CLIENT_StopRealPlay(siNode.iHandle);
//		OutputDebugString("stop pre realpaly!\n");
	}
	if(ret)
	{
		DeviceNode *pDev = (DeviceNode *)(tempnode->dwDeviceID);
		((SplitCycleParam *)siNode.Param)->pDevice = pDev;
		LONG nID = pDev->LoginID;
		int nCh = tempnode->iChannel;

		CWnd *plWnd = m_screenPannel.GetPage(nScreen);
		if (!plWnd)
		{
			MessageBox(ConvertString("fatal error!"));
		}

		LONG nChannelID = CLIENT_RealPlay(nID, nCh, plWnd->m_hWnd/*m_playWnd[nScreen].m_hWnd*/);
//		OutputDebugString("start new realpaly!\n");
// 		if(!nChannelID)
// 		{
// 			LastError();
// 			KillTimer(nScreen);
// 			MessageBox(ConvertString(MSG_CYCLE_OPENCHANNELFAILED));
// 			if (siNode.Param) 
// 			{
// 				DeleteCycleParam(nScreen);
// 			}
// 
// 			//刷新该窗口显示
// 			//m_playWnd[nScreen].ShowWindow(SW_HIDE);
// 			//m_playWnd[nScreen].ShowWindow(SW_NORMAL);
// 			goto exit;
// 		}
		//设置当前轮循位置
		((SplitCycleParam *)siNode.Param)->iCurPosition = nextPosition;
		
		//获取视频参数
		byte bVideo[4];
		BOOL nRet = CLIENT_ClientGetVideoEffect(nChannelID, &bVideo[0],&bVideo[1],&bVideo[2],&bVideo[3]);
		if (!nRet)
		{
			LastError();
		}
		siNode.nVideoParam.dwParam = *(DWORD *)bVideo;
		siNode.iHandle = nChannelID;
		
		ret = SetSplitInfo_Main(nScreen, &siNode);
		if (!ret)
		{
			MessageBox(ConvertString("error while setting split info"));
		}
		
		//设置轮循计时器
		UINT interval = ((SplitCycleParam *)siNode.Param)->iInterval;
		SetTimer((UINT)nScreen, interval * 1000, NULL);
// 		char cBuf[32] = {0};
// 		sprintf(cBuf, "the inteval is %d \n", interval);
// 		OutputDebugString(cBuf);
		goto exit;
		
	}
	else
	{
		//通道关闭失败
		KillTimer(nScreen);
		if (siNode.Param) 
		{
			MessageBox(ConvertString(MSG_CYCLE_CLOSECHANNELFAILED));
			DeleteCycleParam(nScreen);
		}
		goto exit;
	}
	
exit:
//	LeaveCriticalSection(&g_csCycle);
	return;
}

void CNetSDKDemoDlg::CloseAllChannel() 
{
	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
	if (NULL == pDev)
	{
		return;
	}
	ProcessCloseAllChannel(pDev);
}

void CNetSDKDemoDlg::SeleteNormalPannel()			//显示“常规功能”页面
{
	m_normalBtnPannel.ShowWindow(SW_SHOW);
	m_advanceBtnPannel.ShowWindow(SW_HIDE);
	m_saveDataPannel.ShowWindow(SW_HIDE);
	m_ptzPannel.ShowWindow(SW_HIDE);
}

void CNetSDKDemoDlg::SeleteAdvancePannel()			//显示“高级”功能页面
{
	m_advanceBtnPannel.ShowWindow(SW_SHOW);
	m_normalBtnPannel.ShowWindow(SW_HIDE);
	m_saveDataPannel.ShowWindow(SW_HIDE);
	m_ptzPannel.ShowWindow(SW_HIDE);
}

void CNetSDKDemoDlg::SeletePTZPannel()				//显示“云台控制”功能页面
{
	m_ptzPannel.ShowWindow(SW_SHOW);
	m_advanceBtnPannel.ShowWindow(SW_HIDE);
	m_normalBtnPannel.ShowWindow(SW_HIDE);
	m_saveDataPannel.ShowWindow(SW_HIDE);
}

void CNetSDKDemoDlg::SeleteSaveDataPannel()		//显示“数据保存”功能页面
{
	m_saveDataPannel.ShowWindow(SW_SHOW);
	m_colorPannel.ShowWindow(SW_HIDE);
	m_devicelist.ShowWindow(SW_HIDE);
	m_playctrlPannel.ShowWindow(SW_HIDE);
}

void CNetSDKDemoDlg::SeleteColorPannel()			//显示“颜色调整”功能页面
{
	m_colorPannel.ShowWindow(SW_SHOW);
	m_devicelist.ShowWindow(SW_HIDE);
	m_playctrlPannel.ShowWindow(SW_HIDE);
	m_saveDataPannel.ShowWindow(SW_HIDE);
}

void CNetSDKDemoDlg::SeletePlayCtrlPannel()		//显示“播放控制”功能页面
{
	m_playctrlPannel.ShowWindow(SW_SHOW);
	m_devicelist.ShowWindow(SW_HIDE);
	m_colorPannel.ShowWindow(SW_HIDE);
	m_saveDataPannel.ShowWindow(SW_HIDE);
}

void CNetSDKDemoDlg::SeleteDevListPannel()			//显示“设备列表”功能页面
{
	m_devicelist.ShowWindow(SW_SHOW);
	m_colorPannel.ShowWindow(SW_HIDE);
	m_playctrlPannel.ShowWindow(SW_HIDE);
	m_saveDataPannel.ShowWindow(SW_HIDE);
}

//窗口改变时的处理
void CNetSDKDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	//窗口最小化与窗口大小无变化不处理
	if ((cx ==0 && cy == 0) || 
		(cx == m_clientRect.Width() && cy == m_clientRect.Height())) 
	{
		return;
	}
	else
	{
		UpdatePannelPosition();
		UpdateScreen(m_normalBtnPannel.GetSplit());
		Invalidate();
	}
}

void CNetSDKDemoDlg::UpdatePannelPosition()
{
	GetClientRect(&m_clientRect);

	m_screenRect.top = m_clientRect.top/* + 5*/;
	m_screenRect.bottom = m_clientRect.bottom/* - 20*/;
	m_screenRect.left = m_clientRect.left/* + 10*/;
	m_screenRect.right = m_clientRect.right - 210;
	GetDlgItem(IDC_SCREEN_WINDOW)->MoveWindow(m_screenRect);
	
	m_pannelRect.top = m_clientRect.top + 100;
	m_pannelRect.bottom = m_clientRect.bottom - 263;
	m_pannelRect.right = m_clientRect.right - 2;
	m_pannelRect.left = m_pannelRect.right - 197;
	GetDlgItem(IDC_FRAME_PANNEL)->MoveWindow(m_pannelRect);	
	
	m_selectRect.left = m_pannelRect.left;
	m_selectRect.right = m_pannelRect.right;
	m_selectRect.top = m_pannelRect.bottom;
	m_selectRect.bottom = m_selectRect.top + 50;
	
	m_btnAreaRect.left = m_selectRect.left;
	m_btnAreaRect.right = m_selectRect.right;
	m_btnAreaRect.top = m_selectRect.bottom;
	m_btnAreaRect.bottom = m_btnAreaRect.top + 203;
	GetDlgItem(IDC_FRAME_BTN_AREA)->MoveWindow(m_btnAreaRect);	
	
	m_runtimeMsgRect.left = m_pannelRect.left;
	m_runtimeMsgRect.right = m_pannelRect.right;
	m_runtimeMsgRect.top = m_pannelRect.top - 95;
	m_runtimeMsgRect.bottom = m_runtimeMsgRect.top + 90;
	
	m_selectPannel.MoveWindow(m_selectRect);	
	m_saveDataPannel.MoveWindow(m_pannelRect);
	m_colorPannel.MoveWindow(m_pannelRect);
	m_playctrlPannel.MoveWindow(m_pannelRect);
	m_devicelist.MoveWindow(m_pannelRect); //设备列表，非子窗口
	m_normalBtnPannel.MoveWindow(m_btnAreaRect);
	m_advanceBtnPannel.MoveWindow(m_btnAreaRect);
	m_ptzPannel.MoveWindow(m_btnAreaRect);
	m_runtimeMsgPannel.MoveWindow(m_runtimeMsgRect);
	m_screenPannel.MoveWindow(m_screenRect);
}

void CNetSDKDemoDlg::LastError()
{
	m_runtimeMsgPannel.ShowLastError();
}

BOOL CNetSDKDemoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYDOWN == pMsg->message && 
		(VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		if (VK_ESCAPE == pMsg->wParam && m_screenPannel.GetFullScreen())
		{
			m_screenPannel.SetFullScreen(FALSE);
		}
		return TRUE;
	}

	if (WM_SIZING == pMsg->message)
	{
		RECT* rc = (RECT*)(pMsg->lParam);
		if (rc)
		{		
			CRect rect(rc);

			//if (rect. || cy < 584)
			//{
			//	return TRUE;
			//}
		}

	}



	return CDialog::PreTranslateMessage(pMsg);
}

void CNetSDKDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_selectPannel.DestroyWindow();
	m_screenPannel.DestroyWindow();
	m_saveDataPannel.DestroyWindow();
	m_colorPannel.DestroyWindow();
	m_playctrlPannel.DestroyWindow();
	m_devicelist.DestroyWindow();
	m_advanceBtnPannel.DestroyWindow();
	m_ptzPannel.DestroyWindow();
	m_runtimeMsgPannel.DestroyWindow();
}

void CNetSDKDemoDlg::SwitchMultiWnd(int nSplit)
{
	if (SPLIT1 == nSplit)
	{
		m_screenPannel.SetMultiScreen(FALSE);
		return ;
	}
	else
	{
		m_screenPannel.SetMultiScreen(TRUE);
		m_screenPannel.SetShowPlayWin(nSplit, m_curScreen);
	}	
}


int	 CNetSDKDemoDlg::GetCurWinID(void)
{
	CPlayWnd* pWnd = (CPlayWnd*)m_screenPannel.GetActivePage();
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		return pWnd->GetWinID();
	}
	
	return -1;
}

LRESULT CNetSDKDemoDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
//	if (WM_SIZING == message)
//	{
//		RECT* rc = (RECT*)(lParam);
//		if (rc)
//		{		
//			CRect rect(rc);
//
//			if (rect.Width() < 800 || rect.Height() < 584)
//			{
//				return 0;
//			}
//		}
//
//	}
//
	return CDialog::DefWindowProc(message, wParam, lParam);
}

BOOL CNetSDKDemoDlg::GetSplitInfo_Main(int nIndex, SplitInfoNode* info)
{
	if (nIndex < 0 || nIndex > DH_MAX_CHANNUM)
	{
		return FALSE;
	}
	CPlayWnd *plWnd = (CPlayWnd*)m_screenPannel.GetPage(nIndex);
	if (!plWnd)
	{
		MessageBox(ConvertString("oops!"));
		return FALSE;
	}

	return plWnd->GetSplitInfo(info);
}

BOOL CNetSDKDemoDlg::SetSplitInfo_Main(int nIndex, SplitInfoNode* info)
{
	if (nIndex < 0 || nIndex > DH_MAX_CHANNUM)
	{
		return FALSE;
	}
	
	CPlayWnd *plWnd = (CPlayWnd*)m_screenPannel.GetPage(nIndex);
	if (!plWnd)
	{
		MessageBox(ConvertString("oops!"));
		return FALSE;
	}
	
	return plWnd->SetSplitInfo(info);
}

void CNetSDKDemoDlg::SetSplit(int split)
{
	m_normalBtnPannel.SetSplit(split);
}

int CNetSDKDemoDlg::GetSplit()
{
	return m_normalBtnPannel.GetSplit();
}

void CNetSDKDemoDlg::GetDeviceWorkstate()			//"设备工作状态"按键响应函数
{
	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
	if(pDev == NULL)
	{
		return;
	}

	CDeviceWorkState dlg;
	
	dlg.SetDevice(pDev);
	
	dlg.DoModal();

}

void CNetSDKDemoDlg::DeviceControldisk()			//"硬盘控制"按键响应函数
{
	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
	if(pDev == NULL)
	{
		return;
	}
	
	CDiskControl dlg;
	dlg.SetDeviceId(pDev);
	dlg.DoModal();
	/*
	DISKCTRL_PARAM diskParam;
	diskParam.dwSize = sizeof(DISKCTRL_PARAM);
	diskParam.nIndex = 0;		//硬盘号
	diskParam.ctrlType = 0;		// 0 - clear data, 1 - set as read-write, 2 - set as read-only
								//3 - set as redundant,  4 - error recovery
	CLIENT_ControlDevice(pDev->LoginID, CTRL_DISK, &diskParam);
	*/
}

void CNetSDKDemoDlg::DeviceUserinfo()				//"用户信息"按键响应函数
{
	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
	if(pDev == NULL)
	{
		return;
	}

	CUserManage dlg;
	dlg.SetDeviceId(pDev);
	dlg.DoModal();
}

int CALLBACK ListenCallBack(LONG lServerHandle, char* ip, WORD port, int nCmd, void* pParam, DWORD dwUserData)
{
	CNetSDKDemoDlg* pThis = (CNetSDKDemoDlg*)dwUserData;
	return pThis->ListenCallBack_Imp(lServerHandle, ip, port, nCmd, pParam);
}

int CNetSDKDemoDlg::ListenCallBack_Imp(LONG lServerHandle, char* ip, WORD port, int nCmd, void* pParam)
{
	switch(nCmd)
	{
	case DH_DVR_SERIAL_RETURN:
		{
			m_mylsdata.state = 1; //ready
			strcpy(m_mylsdata.ip, ip);
			strcpy(m_mylsdata.serial, (const char*)pParam);
			m_mylsdata.port = port;
		}
	break;
	case DH_DVR_DISCONNECT:
		{
			int jjjj = 0;
		}
		break;
	default:
		break;
	}
	return 0;
}

void CNetSDKDemoDlg::TestProc()
{
	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
	if(pDev == NULL)
	{
		return;
	}

//	DH_DEV_ENCODER_CFG
	DHDEV_CHANNEL_CFG stuInfo = {0};
	DWORD nRetLen = 0;
	BOOL bret = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_CHANNELCFG, -1, &stuInfo, sizeof(DHDEV_CHANNEL_CFG), &nRetLen);
	if (bret)
	{
		stuInfo.stMainVideoEncOpt->byEncodeMode = 7;
		stuInfo.stMainVideoEncOpt->bH264ProfileRank = 2;
		bret = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_CHANNELCFG, 0, &stuInfo, sizeof(DHDEV_CHANNEL_CFG));
		if (bret)
		{
			int i =0;
		}
	}

// 	DHDEV_SYSTEM_ATTR_CFG stuSystemInfo = {0};
// 	unsigned long lRet = 0;
// 	
// 	BOOL bRet = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_DEVICECFG, 0, &stuSystemInfo, 
// 		sizeof(DHDEV_SYSTEM_ATTR_CFG), &lRet);
// 	if (bRet)
// 	{
// 		MessageBox("ok");
// 	}
// 
// 	DH_SNAP_ATTR_EN stuSnapInfo = {0};
// 	int nRet = 0;
// 	bRet = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_SNAP, (char*)&stuSnapInfo, sizeof(DH_SNAP_ATTR_EN), &nRet);
// 	
// 	if (bRet)
// 	{
// 		int i = 0;
// 	}
// 	char szOutBuffer[32*1024] = {0};
// 	int nErr = 0;
// 	
// 	long handle = CLIENT_RealLoadPicture(pDev->LoginID, 0, EVENT_IVS_ALL, NULL, NULL);
// 	Sleep(10000);
// 	BOOL bSuccess = CLIENT_QueryNewSystemInfo(pDev->LoginID, "devVideoAnalyse.getCaps", 0, szOutBuffer, 32*1024, &nErr, 3000);
// 	DHDEV_CDMAGPRS_CFG cfgBuf = {0};
// 	CLIENT_StopLoadPic(handle);
// 	DWORD outSize = 0;
// 	BOOL bSuccess = CLIENT_GetDevConfig(pDev->LoginID,DH_DEV_CDMAGPRS_CFG,1,
// 		&cfgBuf,sizeof(cfgBuf), &outSize);

// 	char pFileName[] = "C:\\Documents and Settings\\Administrator\\桌面\\Config.cfg";
// 	BOOL bSuccess = CLIENT_ImportConfigFile(pDev->LoginID, pFileName, NULL, (DWORD)this);
// 	if (bSuccess)
// 	{
// 		MessageBox("success!");
// 	}

// 	int retlen = 0;
// 	DEV_DISK_RECORD_INFO stuDiskRecordInfo = {0};
// 	BOOL bSuccess = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_RECORD_TIME, (char*)&stuDiskRecordInfo, sizeof(DEV_DISK_RECORD_INFO), &retlen, 3000);
// 	if (bSuccess && retlen == sizeof(DEV_DISK_RECORD_INFO))
// 	{
// 		int a = 0;
// 	}
//	int jjjjj = -2147483644;
//	jjjjj &= 0xFF;
//	int iii = sizeof(USER_MANAGE_INFO);
//	int jjj = 16*sizeof(DHDEV_CHANNEL_CFG);
//	int kkk = sizeof(DHDEV_ALARM_SCHEDULE);
//	
//	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
//	if(pDev == NULL)
//	{
//		return;
//	}
//
//	DWORD dwret;
//
//	DH_DVR_VIDEOOSD_CFG st = {0};
//	
//	BOOL bSuccess = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_VIDEO_OSD_CFG, 1,
//		&st, sizeof(DH_DVR_VIDEOOSD_CFG), &dwret);
//
//	if (!bSuccess)
//	{
//		return;
//	}
//	
//
//	int num = st.nOSDChannelNum;
//
//	st.StTitleOSD[0].StOSDTitleOpt[0].StOSD_POS.bEncodeBlend = 1;
//	st.StTitleOSD[0].StOSDTitleOpt[0].StOSD_POS.bPreviewBlend = 1;
//	st.StTitleOSD[0].StOSDTitleOpt[0].StOSD_POS.rgbaBackground = 0xff;
//	st.StTitleOSD[0].StOSDTitleOpt[0].StOSD_POS.rcRelativePos.bottom = 0;
//	st.StTitleOSD[0].StOSDTitleOpt[0].StOSD_POS.rcRelativePos.left = 112;
//	st.StTitleOSD[0].StOSDTitleOpt[0].StOSD_POS.rcRelativePos.right = 0;
//	st.StTitleOSD[0].StOSDTitleOpt[0].StOSD_POS.rcRelativePos.top = 234;
//
//	strcpy(st.StTitleOSD[0].StOSDTitleOpt[0].SzOSD_Name, "你好中国");
//
//	BOOL b = CLIENT_SetDevConfig(pDev->LoginID,  DH_DEV_VIDEO_OSD_CFG, 1,
//		&st, sizeof(DH_DVR_VIDEOOSD_CFG));
//
//	if (!b)
//	{
//		return;
//	}






	/*
	DHDEV_DST_CFG pstDSTInfo = {0};

	BOOL bSuccess = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_DST_CFG, 1,
		&st, sizeof(DHDEV_DST_CFG), &dwret);

	if (!bSuccess)
	{
		return;
	}
	
	pstDSTInfo.stDSTStart.nYear = 2006;
	pstDSTInfo.stDSTStart.nMonth = 12;
	pstDSTInfo.stDSTStart.nWeekOrDay = 1;
	pstDSTInfo.stDSTStart.iWeekDay = 3;
	pstDSTInfo.stDSTStart.nHour = 12;
	pstDSTInfo.stDSTStart.nMinute = 30; 
	pstDSTInfo.stDSTEnd.nYear = 2008;
	pstDSTInfo.stDSTEnd.nMonth = 1;
	pstDSTInfo.stDSTEnd.nWeekOrDay = 1;
	pstDSTInfo.stDSTEnd.iWeekDay = 2;
	pstDSTInfo.stDSTEnd.nHour = 4 ;
	pstDSTInfo.stDSTEnd.nMinute = 20;
	
	BOOL b = CLIENT_SetDevConfig(pDev->LoginID,  DH_DEV_DST_CFG, 1,
		&st, sizeof(DHDEV_DST_CFG));

	if (!b)
	{
		return;
	}*/
	
// 	DHDEV_SMB_PROTO_CFG st = {0};
// 	BOOL bSuccess = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_SMB_PROTO_CFG, 0,
// 		&st, sizeof(DHDEV_SMB_PROTO_CFG), &dwret);
// 
// 	if (!bSuccess)
// 	{
// 		return;
// 	}
// 
// 	int t = st.bEnable;
// 	strcpy(st.szHostIp,"10.7.4.14");
// 	st.wHostPort = 37777;
// 	
// 	BOOL b = CLIENT_SetDevConfig(pDev->LoginID,  DH_DEV_SMB_PROTO_CFG, -1,
// 		&st, sizeof(DHDEV_SMB_PROTO_CFG));
// 
// 	if (!b)
// 	{
// 		return;
// 	}

// 
// 	int nretlen = 0;
// 	DH_DEV_LANGUAGE_INFO stuLan = {0};
// 	BOOL bbbbbb = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_LANGUAGE, (char*)&stuLan, sizeof(DH_DEV_LANGUAGE_INFO), &nretlen, 3000);
// 	if (bbbbbb && nretlen == sizeof(DH_DEV_LANGUAGE_INFO))
// 	{
// 		int  nnn = 0;
// 	}
// 
// 	int len = 0;
// 	DH_MULTIPLAY_EN stuMultiPlay = {0};
// 	BOOL bbb = CLIENT_QuerySystemInfo(pDev->LoginID, ABILITY_MULTIPLAY, (char*)&stuMultiPlay, sizeof(DH_MULTIPLAY_EN), &len);
// 	if (bbb && len == sizeof(DH_MULTIPLAY_EN))
// 	{
// 		int i =0;
// 	}
// 
// 	DH_INFRARED_CFG stuInfrared = {0};
// 	DWORD retlen = 0;
// 	BOOL bb = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_INFRARED_CFG, 0, &stuInfrared, sizeof(DH_INFRARED_CFG), &retlen, 2000);
// 	if (bb && retlen == sizeof(DH_INFRARED_CFG))
// 	{
// 		stuInfrared.InfraredAlarm[0].struHandle.byRelAlarmOut[0] = 0;
// 		bb = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_INFRARED_CFG, 0, &stuInfrared, sizeof(DH_INFRARED_CFG), 2000);
// 		int i =0;
// 	}
// /*
// 
// 		DH_DEV_LANGUAGE_INFO ss; 
// 		int result;
// 		BOOL brr = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_LANGUAGE, (char*)&ss, sizeof(ss), &result);
// 		if (!brr)
// 		{
// 			int lajdkfj = 0;
// 		}
// 	
// 		int i = ss.dwLanguageNum;
// 	*/
// 
// 
// 	DWORD dwret;
// 
// 	DH_AUDIO_DETECT_CFG st = {0};
// 	BOOL bSuccess = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_AUDIO_DETECT_CFG, 0,
// 		&st, sizeof(DH_AUDIO_DETECT_CFG), &dwret);
// 
// 	if (!bSuccess)
// 	{
// 		return;
// 	}
// 
// 	int t = st.AlarmNum;
// 	
// 	for (int i = 0; i<t; i++)
// 	{
// 		for (int j=0; j<DH_N_WEEKS; j++)
// 		{
// 			int iii = st.AudioDetectAlarm[i].Volume_max;
// 			int jjj = st.AudioDetectAlarm[i].Volume_min;
// 			unsigned long tt = st.AudioDetectAlarm[i].struHandle.dwActionMask;
// 			
// 			st.AudioDetectAlarm[i].Volume_max = 60 +i;
// 			
// 			
// 			st.AudioDetectAlarm[i].stSect[j][5].iBeginHour = 11;
// 			st.AudioDetectAlarm[i].stSect[j][5].iBeginMin = 21;
// 			st.AudioDetectAlarm[i].stSect[j][5].iBeginSec = 12;
// 			st.AudioDetectAlarm[i].stSect[j][5].iEndHour = 22;
// 			st.AudioDetectAlarm[i].stSect[j][5].iEndMin = 33;
// 			st.AudioDetectAlarm[i].stSect[j][5].iEndSec = 44;
// 			
// 			st.AudioDetectAlarm[i].stSect[j][4].iBeginHour = 1;
// 			st.AudioDetectAlarm[i].stSect[j][4].iBeginMin = 2;
// 			st.AudioDetectAlarm[i].stSect[j][4].iBeginSec = 3;
// 			st.AudioDetectAlarm[i].stSect[j][4].iEndHour = 4;
// 			st.AudioDetectAlarm[i].stSect[j][4].iEndMin = 5;
// 			st.AudioDetectAlarm[i].stSect[j][4].iEndSec = 6;
// 			
// 			st.AudioDetectAlarm[i].stSect[j][5].bEnable |= 0xFFFF0001;
// 			st.AudioDetectAlarm[i].stSect[j][4].bEnable |= 0xFFFF0001;
// 		}
// 
// 		int index = 16;
// 		for (j = 0; j < index; j++)
// 		{
// 			st.AudioDetectAlarm[i].struHandle.byRecordChannel[j] = 1;
// 			st.AudioDetectAlarm[i].struHandle.byTour[j]=1;
// 			st.AudioDetectAlarm[i].struHandle.byRecordChannel[j]=1;
// 			st.AudioDetectAlarm[i].struHandle.struPtzLink[j].iValue = 1;
// 			st.AudioDetectAlarm[i].struHandle.struPtzLink[j].iType = 1;
// 			st.AudioDetectAlarm[i].struHandle.byRelAlarmOut[j] = 1;
// 		}
// 		st.AudioDetectAlarm[i].struHandle.dwActionFlag = 2047;
// 		st.AudioDetectAlarm[i].struHandle.dwDuration = 0;
// 		st.AudioDetectAlarm[i].struHandle.dwRecLatch = 0;//把预录时间取消用来表示录像延时，变量名待改
// 		st.AudioDetectAlarm[i].struHandle.dwEventLatch = 0;
// 	}
// 
// 	BOOL b = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_AUDIO_DETECT_CFG, -1,
// 		&st, sizeof(DH_AUDIO_DETECT_CFG));
// 
// 	if (!b)
// 	{
// 		return;
// 	}
// /*
// 	DH_WIRELESS_EN st;
// 	int dwret;
// 	
// 	BOOL b = CLIENT_QuerySystemInfo(pDev->LoginID, 18, 
// 		(char*)&st, sizeof(st),  &dwret, 1000);
// 	
// 	if (!b)
// 	{
// 		return;
// 	}
// 	else
// 	{
// 		int i = st.IsWirelessEnable;
// 		
// 	}
// */
// 
// 	/*
// 
// 	
// 	DHDEV_TRANSFER_STRATEGY_CFG st;
// 	DWORD dwret = 0;
// 
// 
// 	BOOL b = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_TRANS_STRATEGY, -1, &st, sizeof(st), &dwret);
// 	if (!b || dwret < sizeof(DHDEV_TRANSFER_STRATEGY_CFG))
// 	{
// 		return;
// 	}
// 
// 	st.bEnable = 1;
// 	st.iStrategy = 1;
// 	b = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_TRANS_STRATEGY, -1, &st, sizeof(st));
// 	if (!b)
// 	{
// 		return;
// 	}
// 	
// 
// 	///download strategy
// 	DHDEV_DOWNLOAD_STRATEGY_CFG dst;
// 	dwret = 0;
// 	
// 	b = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_DOWNLOAD_STRATEGY, -1, &dst, sizeof(dst), &dwret);
// 	if (!b || dwret < sizeof(DHDEV_DOWNLOAD_STRATEGY_CFG))
// 	{
// 		return;
// 	}
// 	
// 	dst.bEnable = !dst.bEnable;
// 
// 	b = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_DOWNLOAD_STRATEGY, -1, &dst, sizeof(dst));
// 	if (!b)
// 	{
// 		return;
// 	}
// 
// /*	
// 	DHDEV_AUTOMT_CFG st;
// 	DWORD dwret = 0;
// 	
// 	BOOL b = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_AUTOMTCFG, -1, &st, sizeof(st), &dwret);
// 	if (!b || dwret < sizeof(DHDEV_INTERVIDEO_UCOM_CFG))
// 	{
// 		return;
// 	}
// 
// 	/*
// 	/*
// 	DHDEV_FTP_PROTO_CFG st;
// 	DWORD dwret = 0;
// 	
// 	BOOL b = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_FTP_PROTO_CFG, 0, &st, sizeof(st), &dwret);
// 	if (!b || dwret < sizeof(DHDEV_FTP_PROTO_CFG))
// 	{
// 		return;
// 	}
// 
// 	st.bEnable = 0;
// 	st.iFileLen = 1234;
// 	st.iInterval = 100;
// 	strcpy(st.szDirName, "hereisdirect");
// 	strcpy(st.szHostIp, "10.12.2.47");
// 	strcpy(st.szPassword, "damnshitpsw");
// 	strcpy(st.szUserName, "hereisusername");
// 	st.wHostPort = 12321;
// 	for (int i=0; i<DH_MAX_CHANNUM; i++)
// 	{
// 		for (int j=0; j<DH_N_WEEKS; j++)
// 		{
// 			for (int k=0; k<DH_TIME_SECTION; k++)
// 			{
// 				st.struUploadCfg[i][j].struPeriod[k].struSect.iBeginHour = k+1;
// 				st.struUploadCfg[i][j].struPeriod[k].struSect.iEndHour = k+2;
// 				st.struUploadCfg[i][j].struPeriod[k].struSect.iBeginMin = 10;
// 				st.struUploadCfg[i][j].struPeriod[k].struSect.iEndMin = 20;
// 				st.struUploadCfg[i][j].struPeriod[k].struSect.iBeginSec = 30;
// 				st.struUploadCfg[i][j].struPeriod[k].struSect.iEndSec = 40;
// 				
// 				st.struUploadCfg[i][j].struPeriod[k].bAlarmEn = 1;
// 				st.struUploadCfg[i][j].struPeriod[k].bMdEn = 1;
// 				st.struUploadCfg[i][j].struPeriod[k].bTimerEn = 1;
// 			}
// 		}
// 	}
// 
// 	b = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_FTP_PROTO_CFG, 0, &st, sizeof(st));
// 	if (!b)
// 	{
// 		return;
// 	}
// 	/*
// 
// 	int afs;
// 	int result;
// 	BOOL brr = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_PROTOCAL_VER, (char*)&afs, sizeof(int), &result);
// 	if (!brr)
// 	{
// 		int lajdkfj = 0;
// 	}
// *//*
// 	DHDEV_SNAP_CFG st[16];
// 	DWORD dwret = 0;
// 	BOOL b = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_SNAP_CFG, 0, st, sizeof(st), &dwret);
// 	if (!b || dwret < sizeof(DHDEV_SNAP_CFG)*pDev->Info.byChanNum)
// 	{
// 		return;
// 	}
// 
// 	st[0].bTimingEnable = 1;
// 	st[0].struSnapEnc[0].byImageSize = 3; //cif
// 	st[0].struSnapEnc[0].byImageQlty = 6;
// 	st[0].struSnapEnc[0].byFramesPerSec = 1;
// 	
// 	st[1].bTimingEnable = 1;
// 	st[0].struSnapEnc[1].byImageSize = 1; //HD1
// 	st[0].struSnapEnc[1].byImageQlty = 5;
// 	st[0].struSnapEnc[1].byFramesPerSec = 2;
// 	
// 	st[2].bTimingEnable = 1;
// 	st[1].struSnapEnc[0].byImageSize = 3; //cif
// 	st[1].struSnapEnc[0].byImageQlty = 6;
// 	st[1].struSnapEnc[0].byFramesPerSec = 1;
// 
// 	b = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_SNAP_CFG, 0, st, sizeof(st));
// 	if (!b)
// 	{
// 		return;
// 	}
// 
// //////////////////////////////////////////////////////////////////////////
// 
// 
// 	DHDEV_URL_CFG stt;
// 	
// 	b = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_WEB_URL_CFG, 0, &stt, sizeof(stt), &dwret);
// 	if (!b || dwret != sizeof(stt))
// 	{
// 		return;
// 	}
// 
// 	stt.bSnapEnable = TRUE;
// 	stt.iMsgInterval = 25;
// 	stt.iSnapInterval = 30;
// 	strcpy(stt.szDevId, "happy sun day bird");
// 	strcpy(stt.szHostIp, "123.123.232.123");
// 	strcpy(stt.szUrlImage, "http://acbdefg.php");
// 	strcpy(stt.szUrlState, "http://hijklmn.php");
// 	stt.wHostPort = 1234;
// 	
// 	b = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_WEB_URL_CFG, 0, &stt, sizeof(stt));
// 	if (!b)
// 	{
// 		return;
// 	}
// 
// 	/*
// 	DHDEV_MULTI_DDNS_CFG st = {0};
// 	DWORD dwret;
// 	BOOL b = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_MULTI_DDNS, 0, &st, sizeof(DHDEV_MULTI_DDNS_CFG), &dwret, CONFIG_WAITTIME);
// 	if (!b || dwret != sizeof(DHDEV_MULTI_DDNS_CFG))
// 	{
// 		return;
// 	}
// 
// 	Sleep(1000);
// 
// 	st.struDdnsServer[0].bEnable = 1;
// 	st.struDdnsServer[0].dwServerPort = 7000;
// 	char* ip = "100.100.100.100";
// 	strcpy(st.struDdnsServer[0].szServerIp, ip);
// 	char* domain = "testchange.3322.org";
// 	strcpy(st.struDdnsServer[0].szDomainName, domain);
// 	char* username = "testchange_username";
// 	strcpy(st.struDdnsServer[0].szUserName, username);
// 	char* userpsw = "testchange_psw";
// 	strcpy(st.struDdnsServer[0].szUserPsw, userpsw);
// 	char* alias = "testchange_alias";
// 	strcpy(st.struDdnsServer[0].szAlias, alias);
// 
// 	
// 	
// 	b = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_MULTI_DDNS, 0, &st, sizeof(DHDEV_MULTI_DDNS_CFG));
// 	if (!b)
// 	{
// 		return;
// 	}
// 
// 	/*
// 	DH_BURNING_DEVINFO stBD = {0};
// 	int retlen = 0;
// 	BOOL b = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_BURNING_DEV, (char*)&stBD, sizeof(stBD), &retlen, 5000);
// 	if (!b || stBD.dwDevNum <= 0)
// 	{
// 		//	return;
// 	}
// 	
// 	BURNNG_PARM stBP = {0};
// 	stBP.channelMask = 0x01; //1通道
// 	stBP.devMask = 0x03;	//1、2号设备
// 							
// 	
// 	DH_BURNING_PROGRESS stBnPrg = {0};
// 	int retlen = 0;
// 	BOOL b = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_BURNING_PROGRESS, (char*)&stBnPrg, sizeof(stBnPrg), &retlen);
// 	if (!b || retlen != sizeof(DH_BURNING_PROGRESS))
// 	{
// 		int jjjjj =0 ;
// 		//	return;
// 	}
// 	char temp[100] = {0};
// 	sprintf(temp, "burning = %d, starttime=%d-%d-%d %d:%d:%d, elapsed:%d, total:%d KB, remain: %d KB, burned:%d KB, status:%d\n",
// 		stBnPrg.bBurning, stBnPrg.stTimeStart.dwYear, stBnPrg.stTimeStart.dwMonth, stBnPrg.stTimeStart.dwDay, stBnPrg.stTimeStart.dwHour,
// 		stBnPrg.stTimeStart.dwMinute, stBnPrg.stTimeStart.dwSecond, stBnPrg.dwTimeElapse, stBnPrg.dwTotalSpace,
// 		stBnPrg.dwRemainSpace, stBnPrg.dwBurned, stBnPrg.dwStatus);
// 	OutputDebugString(temp);
// 
// 	b = CLIENT_ControlDevice(pDev->LoginID, DH_BURNING_START, &stBP);
// 	if (!b)
// 	{
// 		return;
// 	}
// 	
// 	for (int i = 0; i < 240; i++)
// 	{
// 		
// 		DH_BURNING_PROGRESS stBnPrg = {0};
// 		int retlen = 0;
// 		BOOL b = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_BURNING_PROGRESS, (char*)&stBnPrg, sizeof(stBnPrg), &retlen);
// 		if (!b || retlen != sizeof(DH_BURNING_PROGRESS))
// 		{
// 			int jjjjj =0 ;
// 			//	return;
// 		}
// 		char temp[100] = {0};
// 		sprintf(temp, "burning = %d, starttime=%d-%d-%d %d:%d:%d, elapsed:%d, total:%d KB, remain: %d KB, burned:%d KB, status:%d\n",
// 			stBnPrg.bBurning, stBnPrg.stTimeStart.dwYear, stBnPrg.stTimeStart.dwMonth, stBnPrg.stTimeStart.dwDay, stBnPrg.stTimeStart.dwHour,
// 			stBnPrg.stTimeStart.dwMinute, stBnPrg.stTimeStart.dwSecond, stBnPrg.dwTimeElapse, stBnPrg.dwTotalSpace,
// 			stBnPrg.dwRemainSpace, stBnPrg.dwBurned, stBnPrg.dwStatus);
// 		OutputDebugString(temp);
// 		
// 		Sleep(500);
// 	}
// 	
// 	b = CLIENT_ControlDevice(pDev->LoginID, DH_BURNING_STOP, &stBP);
// 	if (!b)
// 	{
// 		return;
// 	}*/
// 	/*
// 	DH_SDCARD_STATE stSd = {0};
// 	int retlen = 0;
// 	bool b = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_SD_CARD, (char*)&stSd, sizeof(stSd), &retlen, 1000);
// 	if (!b)
// 	{
// 		MessageBox("dame");
// 		return ;
// 	}
// 
// 	
// 	Sleep(1000);
// 
// 	DISKCTRL_PARAM stC = {0};
// 	stC.dwSize = sizeof(stC);
// 	stC.ctrlType = 0;
// 	stC.nIndex = 0;
// 
// 	b = CLIENT_ControlDevice(pDev->LoginID, DH_CTRL_SDCARD, &stC, 100000);
// 	if (!b)
// 	{
// 		DWORD dw = CLIENT_GetLastError();
// 		MessageBox("dame2!");
// 		return;
// 	}
// 	*/
// 
// 	/*
// 	ALARMCTRL_PARAM test;
// 	test.dwSize = sizeof(test);
// 	test.nAlarmNo = 0;
// 	test.nAction = 1;
// 	
// 	BOOL b = CLIENT_ControlDevice(pDev->LoginID, DH_CTRL_DISK, &test, 1000);
// 	if (!b)
// 	{
// 		DWORD dw = CLIENT_GetLastError();
// 		dw &= 0xFFFF;
// 	}
// */
// 
// 	/*
// 	DHDEV_ALARM_SCHEDULE st = {0};
// 	DWORD dwret;
// 	BOOL b = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_ALARMCFG, 0, &st, sizeof(DHDEV_ALARM_SCHEDULE), &dwret);
// 	if (!b)
// 	{
// 		return;
// 	}
// 
// 	for (int i = 0; i<DH_MAX_ALARM_IN_NUM; i++)
// 	{
// 		for (int j=0; j<DH_N_WEEKS; j++)
// 		{
// 			int iii = st.struLocalAlmIn[i].stSect[j][5].bEnable;
// 			int jjj = st.struLocalAlmIn[i].stSect[j][4].bEnable;
// 			
// 
// 			st.struLocalAlmIn[i].stSect[j][5].iBeginHour = 11;
// 			st.struLocalAlmIn[i].stSect[j][5].iBeginMin = 21;
// 			st.struLocalAlmIn[i].stSect[j][5].iBeginSec = 12;
// 			st.struLocalAlmIn[i].stSect[j][5].iEndHour = 22;
// 			st.struLocalAlmIn[i].stSect[j][5].iEndMin = 33;
// 			st.struLocalAlmIn[i].stSect[j][5].iEndSec = 44;
// 
// 			st.struLocalAlmIn[i].stSect[j][4].iBeginHour = 1;
// 			st.struLocalAlmIn[i].stSect[j][4].iBeginMin = 2;
// 			st.struLocalAlmIn[i].stSect[j][4].iBeginSec = 3;
// 			st.struLocalAlmIn[i].stSect[j][4].iEndHour = 4;
// 			st.struLocalAlmIn[i].stSect[j][4].iEndMin = 5;
// 			st.struLocalAlmIn[i].stSect[j][4].iEndSec = 6;
// 
// 			st.struLocalAlmIn[i].stSect[j][5].bEnable |= 0xFFFF0001;
// 			st.struLocalAlmIn[i].stSect[j][4].bEnable |= 0xFFFF0001;
// 		}
// 	}
// 	
// 	
// 	b = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_ALARMCFG, 0, &st, sizeof(DHDEV_ALARM_SCHEDULE));
// 	if (!b)
// 	{
// 		return;
// 	}
// 	
// 	  */
// 	/*
// 	///test alarm
// 	DHDEV_NET_CFG st = {0};
// 	DWORD dwret;
// 	BOOL b = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_NETCFG, 0, &st, sizeof(DHDEV_NET_CFG), &dwret);
// 	if (!b)
// 	{
// 		return;
// 	}
// 	
// 	memcpy(st.struFtpServer.sHostIPAddr, "10.12.2.47", strlen("10.12.2.47"));
// 	st.struFtpServer.wHostPort = 1122;
// 	memcpy(st.struFtpServer.sHostUser, "linjianyan", strlen("linjianyan"));
// 	memcpy(st.struFtpServer.sHostIPAddr, "password", strlen("password"));
// 	
// 	st.struFtpParam.dwFileLen = 1000;
// 	st.struFtpParam.dwIterval = 1000;
// 	memcpy(st.struFtpParam.sFtpDir, "d:\\test", strlen("d:\\test"));
// 	
// 	
// 	b = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_NETCFG, 0, &st, sizeof(DHDEV_NET_CFG));
// 	if (!b)
// 	{
// 		return;
// 	}
// 	*/
// /*
// 	DH_SDCARD_STATE sdCard = {0};
// 	int retlen = 0;
// 
// 	BOOL b = CLIENT_QueryDevState(pDev->LoginID, DH_DEVSTATE_SD_CARD, (char*)&sdCard, sizeof(DH_SDCARD_STATE),
// 				&retlen, 1000);
// 	if (!b)
// 	{
// 		MessageBox("query sd card info failed!");
// 	}
// */
// 	/*
// 	SplitInfoNode siNode;
// 	memset(&siNode, 0, sizeof(siNode));
// 	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
// 	if (!ret)
// 	{
// 		MessageBox("error while getting split info");
// 	}
// 
// 	BOOL b = CLIENT_SetVolume(siNode.iHandle, 100);
// 	if (!b)
// 	{
// 		MessageBox("damn set volume failed!");
// 	}
// 
// 	
// 	
// 	DHDEV_VIDEO_MATRIX_CFG test;
// 	DWORD retlen = 0;
// 	BOOL bg = CLIENT_GetDevConfig(pDev->LoginID, DH_DEV_VEDIO_MARTIX, -1, &test, sizeof(DHDEV_VIDEO_MATRIX_CFG), &retlen);
// 	if (!bg || retlen != sizeof(DHDEV_VIDEO_MATRIX_CFG))
// 	{
// 		OutputDebugString("test failed while get!\n");
// 		return;
// 	}
// 
// 	for (int i=0; i<DH_MATRIX_MAXOUT; i++)
// 	{
// 		test.struVideoGroup[i].byAlarmChannel = pDev->Info.byAlarmInPortNum+1+4;
// 		test.struVideoGroup[i].byEnableTour = 1;
// 		for (int j=0; j<DH_TOUR_GROUP_NUM; j++)
// 		{
// 			test.struVideoGroup[i].byVideoOut[j] = 1+j;
// 		}
// 		test.struVideoGroup[i].iInterval = 10;
// 	}
// 
// 	
// 	BOOL bs = CLIENT_SetDevConfig(pDev->LoginID, DH_DEV_VEDIO_MARTIX, 0, &test, sizeof(DHDEV_VIDEO_MATRIX_CFG));
// 	if (!bs)
// 	{
// 		OutputDebugString("test failed while set!\n");
// 		return;
// 	}
// 
// 	//test control
// 	Sleep(5000);
// 	MATRIXCTRL_PARAM test2 = {0};
// 	test2.dwSize = sizeof(MATRIXCTRL_PARAM);
// 	test2.nChannelNo = 2;
// 	test2.nMatrixNo = 1;
// 	BOOL bc = CLIENT_ControlDevice(pDev->LoginID, DH_CTRL_MATRIX, &test2);
// 
// 	
// 	char recbuf[1024*sizeof(DH_LOG_ITEM)]; //设备最多存储1024条日志记录
// 	memset(recbuf, 0, 1024*sizeof(DH_LOG_ITEM));
// /*
// 	int retlen = 0;
// 	BOOL bRet = CLIENT_QueryLogEx(pDev->LoginID, DHLOG_SYSTEM, (char*)recbuf, 1024*sizeof(DH_LOG_ITEM), &retlen, NULL, 30000);
// 	if (!bRet)
// 	{
// 		DWORD dwErr = CLIENT_GetLastError();
// 		CString strErr;
// 		strErr.Format("获取日志失败，错误号：_EC(%d)", dwErr & 0x7FFFFFFF);
// 		MessageBox(strErr);
// 		return;
// 	}
// 
// 	/*
// 	DH_CHANNEL_OSDSTRING test = {0};
// 	sprintf(test.szStrings[0], "acbdadf");
// 	sprintf(test.szStrings[1], "5484542321321");
// 	sprintf(test.szStrings[2], "");
// 	sprintf(test.szStrings[3], "");
// 	sprintf(test.szStrings[4], "金木水火士");
// 	sprintf(test.szStrings[5], "123adf45ddd");
// 	
// 	test.bEnable = TRUE;
// 	int pos = 2;
// 	test.dwPosition[0] = pos;
// 	test.dwPosition[1] = pos;
// 	test.dwPosition[2] = pos;
// 	test.dwPosition[3] = pos;
// 	test.dwPosition[4] = pos;
// 	test.dwPosition[5] = pos;
// 	
// 	BOOL b = CLIENT_SetupChannelOsdString(pDev->LoginID, 0, &test, sizeof(DH_CHANNEL_OSDSTRING));
// 	if (!b)
// 	{
// 		MessageBox("seg osd string failed!");
// 	}
// 	/*
// 	SplitInfoNode siNode;
// 	memset(&siNode, 0, sizeof(siNode));
// 	BOOL ret = GetSplitInfo_Main(m_curScreen, &siNode);
// 	if (!ret)
// 	{
// 	MessageBox("error while getting split info");
// 	return;
// 	}
// 	NET_TIME t1;
// 	NET_TIME t2;
// 	NET_TIME t3;
// 	BOOL bb = CLIENT_GetPlayBackOsdTime(siNode.iHandle, &t1, &t2, &t3);
// 	if (!bb)
// 	{
// 	}
// */
// 	/*
// 	DeviceNode *pDev = (DeviceNode *)GetCurDeviceInfo();
// 	if(pDev == NULL)
// 	{
// 	return;
// 	}
// 	CAutoMaintenance dlg;
// 	dlg.SetDeviceNode(pDev);
// 	dlg.DoModal();
// 	*/
// }
// /*
// unsigned long __stdcall SpCallBack(PARSERHANDLE hHandle, PARSERMSG msg, 
// 							unsigned long dwParam1, unsigned long dwParam2,
// 							unsigned long dwUserData)
// {
// 	CNetSDKDemoDlg *pThis = (CNetSDKDemoDlg *)dwUserData;
// 	if (!pThis)
// 	{
// 		return -1;
// 	}
// 	pThis->HandleParserMsg(hHandle, msg, dwParam1, dwParam2);
// 
// 	return 0;
// }
// 
// void CNetSDKDemoDlg::HandleParserMsg(PARSERHANDLE hHandle, PARSERMSG msg, 
// 				 unsigned long dwParam1, unsigned long dwParam2)
// {
// 	switch(msg)
// 	{
// 	case STREAM_MSG_GET_ONE_FRAME:
// 		break;
// 	case STREAM_MSG_ERROR:
// 	//	DHSP_Reset(m_hSp, 0);
// 		MessageBox("error in stream parser, call police!");
// 		break;
// 	default:
// 		return;
// 	}
//}
}
