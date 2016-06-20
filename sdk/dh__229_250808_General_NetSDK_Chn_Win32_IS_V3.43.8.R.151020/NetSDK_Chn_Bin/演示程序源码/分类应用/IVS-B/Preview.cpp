// Preview.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSb.h"
#include "Preview.h"
#include "DemoIVSbDlg.h"
#include "Config.h"
#include "Alarm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreview dialog


CPreview::CPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CPreview::IDD, pParent)//, m_nDrawPortNum(300)
{
	//{{AFX_DATA_INIT(CPreview)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreview)
	DDX_Control(pDX, IDC_PREVIEW_LIST_ALARM, m_lsAlarm);
	DDX_Control(pDX, IDC_PREVIEW_CMB_CHANNEL, m_cmbChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreview, CDialog)
	//{{AFX_MSG_MAP(CPreview)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_PREVIEW_CMB_CHANNEL, OnSelchangePreviewCmbChannel)
	ON_NOTIFY(NM_RCLICK, IDC_PREVIEW_LIST_ALARM, OnRclickPreviewListAlarm)
	ON_COMMAND(WM_CLEARINFO, OnClearInfo)
	ON_COMMAND(WM_CLOSEPREVIEW, OnClosePreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreview message handlers

BOOL CPreview::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	m_lsAlarm.SetExtendedStyle(m_lsAlarm.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_lsAlarm.InsertColumn(0, ConvertString(_T("ChannelID")), LVCFMT_LEFT, 60, -1);
	m_lsAlarm.InsertColumn(1, ConvertString(_T("EventType")), LVCFMT_LEFT, 100, -1);
	m_lsAlarm.InsertColumn(2, ConvertString(_T("TriggerTime")), LVCFMT_LEFT, 130, -1);
	m_lsAlarm.InsertColumn(3, ConvertString(_T("RuleName")), LVCFMT_LEFT, 80, -1);

	DRAW_Open(g_nPreviewDrawPort);

	DRAW_SetLifeCount(g_nPreviewDrawPort, DRAW_ALARM, 30);
	DRAW_SetPen(g_nPreviewDrawPort, DRAW_ALARM, DRAW_PEN_DEFAULT, 1, RGB(255, 0, 0));
	DRAW_SetPen(g_nPreviewDrawPort, DRAW_TRACK, DRAW_PEN_DEFAULT, 1, RGB(255, 255, 0));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreview::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	DRAW_Close(g_nPreviewDrawPort);

	uninitPreviewDlg();
}

void CPreview::OnSelchangePreviewCmbChannel() 
{
	// TODO: Add your control notification handler code here
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)GetParent();
	if (!pMainDlg)
	{
		return;
	}	

	if (pMainDlg->getRealPlayHandle())
	{
		::CLIENT_StopRealPlay(pMainDlg->getRealPlayHandle());

		//////////////////////////////////////////////////////////////////////////
		//
		s_PlayAPI.PLAY_Stop(g_nPlayPort);
		s_PlayAPI.PLAY_CloseStream(g_nPlayPort);

		//////////////////////////////////////////////////////////////////////////

		pMainDlg->setRealPlayHandel(0);
		pMainDlg->setCurrentChannel(-1);
		pMainDlg->m_pdlgConfig->uninitConfigDlg();
	}

	//////////////////////////////////////////////////////////////////////////
	int nPort = 450;
	LLONG m_lPlayID = 0;
	HWND hWnd = GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->GetSafeHwnd();
	NET_DEVICEINFO* pDevInfo = pMainDlg->getDevInfo();
	int nChnCount = 0;
	if (pDevInfo)
	{
		nChnCount = pDevInfo->byChanNum;
	}


	//Enable stream
	BOOL bOpenRet = s_PlayAPI.PLAY_OpenStream(g_nPlayPort, 0, 0, 1024 * 900);
	if(bOpenRet)
	{
		BOOL bRet = s_PlayAPI.PLAY_SetIVSCallBack(g_nPlayPort, getIvsInfoProc, (DWORD)this);
		if (!bRet)
		{
			::OutputDebugString(_T("PLAY_SetIVSCallBack failed!\n"));
		}
		
		CFG_ANALYSERULES_INFO* pRule 
			= (CFG_ANALYSERULES_INFO*)pMainDlg->getAnalyseRulesInfo(m_cmbChannel.GetCurSel());
		if (pRule)
		{
			DRAW_Reset(g_nPreviewDrawPort, DRAW_RULE);
			DRAW_Reset(g_nPreviewDrawPort, DRAW_ALARM);
			DRAW_Reset(g_nPreviewDrawPort, DRAW_TRACK);
			int iErr = DRAW_InputRuleData(g_nPreviewDrawPort, 0, (unsigned char*)pRule, 0);
		}
		
		DRAW_SetPen(g_nPreviewDrawPort, DRAW_RULE, DRAW_PEN_SOLID, 1, RGB(0, 255, 0));
		bRet = s_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, drawIvsInfoPreviewProc, (DWORD)this);
		if (!bRet)
		{
			::OutputDebugString(_T("PLAY_RigisterDrawFun failed!\n"));
		}
		//Begin play 
		BOOL bPlayRet = s_PlayAPI.PLAY_Play(g_nPlayPort, hWnd);
		if(bPlayRet)
		{
			//Real-time play 
			m_lPlayID = CLIENT_RealPlay(pMainDlg->getLoginHandle(), m_cmbChannel.GetCurSel(), 0);
			if(0 != m_lPlayID)
			{
				CLIENT_SetRealDataCallBackEx(m_lPlayID, RealDataCallBackEx, (DWORD)this, 0x1f);
			}
			else
			{
				s_PlayAPI.PLAY_Stop(g_nPlayPort);
				s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				int x = ::CLIENT_GetLastError();
				AfxMessageBox(ConvertString(_T("Fail to play")));
			}
		}
		else
		{
			s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//切换预览视频图像

 	pMainDlg->setRealPlayHandel(m_lPlayID);
	pMainDlg->setCurrentChannel(m_cmbChannel.GetCurSel());
	pMainDlg->m_pdlgConfig->initConfigDlg(m_cmbChannel.GetCurSel());
	pMainDlg->m_pdlgAlarm->initAlarmDlg(nChnCount);
	Invalidate(FALSE);

	//////////////////////////////////////////////////////////////////////////
	//TODO按照通道筛选，切换报警信息显示
	clearAllAlarmInfo();
	showAlarmInfo(m_cmbChannel.GetCurSel());
}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：Get device info, initialize gui info
//参数：nChnCount，Device's Totle Channe Count；
//返回：无
//////////////////////////////////////////////////////////////////////////
void CPreview::initPreviewDlg(int nChnCount)
{
	if (!nChnCount)
	{
		return;
	}

	//清空组合框
	m_cmbChannel.ResetContent();

	TCHAR szItem[16] = {0};
	for (int i = 0; i < nChnCount; i++)
	{
		_sntprintf(szItem, _countof(szItem), _T("%s%02d"), ConvertString(_T("Channel")), i + 1);
		m_cmbChannel.InsertString(i, szItem);
		ZeroMemory(szItem, sizeof(szItem));
	}

	m_cmbChannel.SetCurSel(-1);

	//清空报警信息表格
	m_lsAlarm.DeleteAllItems();

}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：close preview, clear gui info
//参数：
//返回：
//////////////////////////////////////////////////////////////////////////
void CPreview::uninitPreviewDlg()
{
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)GetParent();
	if (pMainDlg)
	{
		if (pMainDlg->getRealPlayHandle())
		{
			::CLIENT_StopRealPlay(pMainDlg->getRealPlayHandle());
			
			//////////////////////////////////////////////////////////////////////////
			//
			s_PlayAPI.PLAY_Stop(g_nPlayPort);
			s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			
			//////////////////////////////////////////////////////////////////////////
			GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->setRealPlayHandel(0);
		}

		if (pMainDlg->getLoginHandle())
		{
			::CLIENT_Logout(pMainDlg->getLoginHandle());
			pMainDlg->setLoginHandel(0);
		}
	}
	//清空组合框
	m_cmbChannel.ResetContent();

	//清空报警信息表格
	m_lsAlarm.DeleteAllItems();
}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：show preview
//参数：
//返回：
//////////////////////////////////////////////////////////////////////////
void CPreview::showPreview(LONG lLoginHanlde, int nChannel)
{
	if (!lLoginHanlde || nChannel < 0)
	{
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)GetParent();
	if (pMainDlg)
	{
		if (pMainDlg->getLoginHandle())
		{
			if (pMainDlg->getRealPlayHandle())
			{
				::CLIENT_StopRealPlay(pMainDlg->getRealPlayHandle());
				pMainDlg->setRealPlayHandel(0);
				
				//////////////////////////////////////////////////////////////////////////
				//
				s_PlayAPI.PLAY_Stop(g_nPlayPort);
				s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				
				//////////////////////////////////////////////////////////////////////////
			}
			
			//////////////////////////////////////////////////////////////////////////
			
			int nPort = 450;
			LLONG m_lPlayID = 0;
			HWND hWnd = GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->GetSafeHwnd();
			NET_DEVICEINFO* pDevInfo = pMainDlg->getDevInfo();
			int nChnCount = 0;
			if (pDevInfo)
			{
				nChnCount = pDevInfo->byChanNum;
			}
			
			CFG_ANALYSERULES_INFO* pRule
				= (CFG_ANALYSERULES_INFO*)pMainDlg->getAnalyseRulesInfo(m_cmbChannel.GetCurSel());
			if (!pRule)
			{
				return;
			}

			//Enable stream
			BOOL bOpenRet = s_PlayAPI.PLAY_OpenStream(g_nPlayPort, 0, 0, 1024 * 900);
			if(bOpenRet)
			{
				BOOL bRet = s_PlayAPI.PLAY_SetIVSCallBack(g_nPlayPort, getIvsInfoProc, (DWORD)this);
				
				DRAW_InputRuleData(g_nPreviewDrawPort, 0, (unsigned char*)pRule, 0);
				DRAW_SetPen(g_nPreviewDrawPort, DRAW_RULE, DRAW_PEN_SOLID, 1, RGB(0, 255, 0));

				bRet = s_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, drawIvsInfoPreviewProc, (DWORD)this);
				if (!bRet)
				{
					MessageBox(ConvertString("PLAY_RigisterDrawFun failed!"), ConvertString("Prompt"));
				}
				//Begin play 
				BOOL bPlayRet = s_PlayAPI.PLAY_Play(g_nPlayPort, hWnd);
				if(bPlayRet)
				{
					//Real-time play 
					m_lPlayID = CLIENT_RealPlay(pMainDlg->getLoginHandle(), nChannel, 0);
					if(m_lPlayID)
					{
						pMainDlg->setRealPlayHandel(m_lPlayID);
						CLIENT_SetRealDataCallBackEx(m_lPlayID, RealDataCallBackEx, (DWORD)this, 0x1f);
					}
					else
					{
						s_PlayAPI.PLAY_Stop(g_nPlayPort);
						s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
						MessageBox(ConvertString("Fail to play!"), ConvertString("Prompt"));
					}
				}
				else
				{
					s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：close preview
//参数：lRealPlayHandle，playhandle
//返回：
//////////////////////////////////////////////////////////////////////////
void CPreview::closePreview(LONG lRealPlayHandle)
{
	if (!lRealPlayHandle)
	{
		return;
	}
	
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)GetParent();
	if (pMainDlg)
	{
		if (pMainDlg->getRealPlayHandle())
		{
			::CLIENT_StopRealPlay(pMainDlg->getRealPlayHandle());
			
			//////////////////////////////////////////////////////////////////////////
			//
			s_PlayAPI.PLAY_Stop(g_nPlayPort);
			s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			
			//////////////////////////////////////////////////////////////////////////
			GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->setRealPlayHandel(0);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：Chose to show the selected channel's Alarminfo
//参数：nChnCount，ChannelNum；
//返回：
//////////////////////////////////////////////////////////////////////////
void CPreview::showAlarmInfo(int nChannel)
{
	if (nChannel < 0)
	{
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	lsAlarmInfo* plsAlarmInfo = pMainDlg->getAlarmInfoList();
	if (!plsAlarmInfo)
	{
		return;
	}

	lsAlarmInfo::iterator it = plsAlarmInfo->begin();
	for(; it != plsAlarmInfo->end(); ++it)
	{
		AlarmInfoNode* pAlarmInfo = (AlarmInfoNode*)*it;
		if (pAlarmInfo && pAlarmInfo->nChnNum == m_cmbChannel.GetCurSel())
		{
			insertAlarmInfo(pAlarmInfo);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：insert a AlarmInfo into ListCtrl
//参数：pAlarmInfoNode，AlarmInfo struct ptr
//返回：
//////////////////////////////////////////////////////////////////////////
void CPreview::insertAlarmInfo(AlarmInfoNode* pAlarmInfoNode)
{
	if (!pAlarmInfoNode)// || pAlarmInfoNode->nChnNum != m_cmbChannel.GetCurSel())
	{
		return;
	}

	if (m_cmbChannel.GetCurSel() == -1
		|| pAlarmInfoNode->nChnNum == m_cmbChannel.GetCurSel())
	{
		int nCount = m_lsAlarm.GetItemCount();
		m_lsAlarm.InsertItem(nCount, _T(""));
		
		CString strTmp;
		strTmp.Format(_T("%s%02d"), ConvertString(_T("Channel")), pAlarmInfoNode->nChnNum + 1);
		m_lsAlarm.SetItemText(nCount, 0, strTmp);
		strTmp.Empty();
		
		strTmp = g_convertRuleTypeToString(pAlarmInfoNode->dwRuleType);
		m_lsAlarm.SetItemText(nCount, 1, strTmp);
		strTmp.Empty();
		
		strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), 
			pAlarmInfoNode->Time.dwYear,
			pAlarmInfoNode->Time.dwMonth,
			pAlarmInfoNode->Time.dwDay,
			pAlarmInfoNode->Time.dwHour,
			pAlarmInfoNode->Time.dwMinute,
			pAlarmInfoNode->Time.dwSecond);
		m_lsAlarm.SetItemText(nCount, 2, strTmp);
		strTmp.Empty();

		m_lsAlarm.SetItemText(nCount, 3, pAlarmInfoNode->szAlarmName);
		
//		m_lsAlarm.SetItemData(nCount, (DWORD)pAlarmInfoNode);
	}
}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：Clear All AlarmInfo in the ListCtrl
//参数：
//返回：
//////////////////////////////////////////////////////////////////////////
void CPreview::clearAllAlarmInfo()
{
	m_lsAlarm.DeleteAllItems();
}

void CPreview::drawIvsInfoPreviewProc(long nPort,HDC hdc,LONG nUser)
{
	CPreview* pDlg = (CPreview*)nUser;
	if (!pDlg)
	{
		return;
	}

	HWND hWnd = pDlg->GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->GetSafeHwnd();

#define PLAY_CMD_GetRenderNum 4 
	int nFrameNumber = 0;
	int nret = 0;
	BOOL bRet = s_PlayAPI.PLAY_QueryInfo(nPort, 
							   PLAY_CMD_GetRenderNum,
							   (char*)&nFrameNumber, 
							   sizeof(nFrameNumber),
							   &nret);
	if (!bRet)
	{
		return;
	}

	int iErr = DRAW_Draw(g_nPreviewDrawPort, hdc, hWnd, nFrameNumber);
	if (iErr < 0)
	{
		return;
	}
}

void CPreview::getIvsInfoProc(char* buf, long type, long len, long reallen, long reserved, long nUser)
{	
	DRAW_SetLifeCount(g_nPreviewDrawPort, DRAW_TRACK, 30);
	DRAW_SetLifeCount(g_nPreviewDrawPort, DRAW_ALARM, 30);

	int nErr = -1;

	switch (reserved)
	{
	case 6:
		nErr = DRAW_InputTrackData(g_nPreviewDrawPort, 0, (unsigned char*)buf, len, reallen);
		break;
	}
}

void CPreview::OnRclickPreviewListAlarm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	CMenu popupMenu;
	popupMenu.CreatePopupMenu();

	CPoint pt;
	GetCursorPos(&pt);

	popupMenu.AppendMenu(MF_STRING, WM_CLEARINFO, ConvertString(_T("Clear all info")));
	popupMenu.TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
}

void CPreview::OnClearInfo()
{
	clearAllAlarmInfo();
	::SendMessage(GetParent()->GetSafeHwnd(), WM_CLEARINFO, (WPARAM)0, (LPARAM)0);
}

void CPreview::OnClosePreview()
{
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)GetParent();
	if (!pMainDlg)
	{
		return;
	}

	closePreview(pMainDlg->getRealPlayHandle());
	
	pMainDlg->setCurrentChannel(-1);
	pMainDlg->m_pdlgConfig->uninitConfigDlg();

	m_cmbChannel.SetCurSel(-1);
}

BOOL CPreview::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)
	{
	case WM_RBUTTONUP:
		if (pMsg->hwnd == GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->GetSafeHwnd())
		{
			CMenu menu;
			menu.CreatePopupMenu();
						
			menu.AppendMenu(MF_STRING, WM_CLOSEPREVIEW, ConvertString(_T("Close preview")));
			menu.TrackPopupMenu(TPM_LEFTALIGN, pMsg->pt.x, pMsg->pt.y, this);
		}
		break;
	default:
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
