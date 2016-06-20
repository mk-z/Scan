// Preview.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSPC.h"
#include "Preview.h"
#include "DemoIVSPCDlg.h"
#include "Config.h"
#include <TCHAR.H>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPreview::CPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CPreview::IDD, pParent)//, m_nDrawPortNum(300)
{
}


void CPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreview)
	DDX_Control(pDX, IDC_PREVIEW_CMB_CHANNEL, m_cmbChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreview, CDialog)
	//{{AFX_MSG_MAP(CPreview)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_PREVIEW_CMB_CHANNEL, OnSelchangePreviewCmbChannel)
	ON_NOTIFY(NM_RCLICK, IDC_PREVIEW_LIST_ALARM, OnRclickPreviewListAlarm)
	ON_COMMAND(WM_CLOSEPREVIEW, OnClosePreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CPreview::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	DRAW_Open(g_nPreviewDrawPort);

	DRAW_SetLifeCount(g_nPreviewDrawPort, DRAW_ALARM, 30);
	DRAW_SetPen(g_nPreviewDrawPort, DRAW_ALARM, DRAW_PEN_DEFAULT, 1, RGB(255, 0, 0));
	DRAW_SetPen(g_nPreviewDrawPort, DRAW_TRACK, DRAW_PEN_DEFAULT, 1, RGB(255, 255, 0));

	return TRUE;
}

void CPreview::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	DRAW_Close(g_nPreviewDrawPort);

	UninitPreviewDlg();
}

void CPreview::OnSelchangePreviewCmbChannel() 
{
	// TODO: Add your control notification handler code here
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)GetParent();
	if (!pMainDlg)
	{
		return;
	}	

	if (pMainDlg->GetRealPlayHandle())
	{
		::CLIENT_StopRealPlay(pMainDlg->GetRealPlayHandle());

		g_PlayAPI.PLAY_Stop(g_nPlayPort);
		g_PlayAPI.PLAY_CloseStream(g_nPlayPort);

		pMainDlg->SetRealPlayHandel(0);
		pMainDlg->SetCurrentChannel(-1);
		pMainDlg->m_pdlgConfig->UninitConfigDlg();
	}

	LLONG m_lPlayID = 0;
	HWND hWnd = GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->GetSafeHwnd();
	NET_DEVICEINFO* pDevInfo = pMainDlg->GetDevInfo();
	int nChnCount = 0;
	if (pDevInfo)
	{
		nChnCount = pDevInfo->byChanNum;
	}


	//Enable stream
	BOOL bOpenRet = g_PlayAPI.PLAY_OpenStream(g_nPlayPort, 0, 0, 1024 * 900);
	if(bOpenRet)
	{
		BOOL bRet = g_PlayAPI.PLAY_SetIVSCallBack(g_nPlayPort, GetIvsInfoProc, (DWORD)this);
		if (!bRet)
		{
			MessageBox(ConvertString(_T("Fail to Set IVS Callback!")), ConvertString("Prompt"));
		}
		
		CFG_ANALYSERULES_INFO* pRule 
			= (CFG_ANALYSERULES_INFO*)pMainDlg->GetAnalyseRulesInfo(m_cmbChannel.GetCurSel());
		if (pRule)
		{
			DRAW_Reset(g_nPreviewDrawPort, DRAW_RULE);
			int iErr = DRAW_InputRuleData(g_nPreviewDrawPort, 0, (unsigned char*)pRule, 0);
			if (iErr < 0)
			{
				MessageBox(ConvertString(_T("Fail to Input RuleData!")), ConvertString("Prompt"));
			}
		}
		
		DRAW_SetPen(g_nPreviewDrawPort, DRAW_RULE, DRAW_PEN_SOLID, 1, RGB(0, 255, 0));
		bRet = g_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, DrawIvsInfoPreviewProc, (DWORD)this);
		if (!bRet)
		{
			MessageBox(ConvertString(_T("Fail to RigisterDrawFun!")), ConvertString("Prompt"));
		}
		//Begin play 
		BOOL bPlayRet = g_PlayAPI.PLAY_Play(g_nPlayPort, hWnd);
		if(bPlayRet)
		{
			//Real-time play 
			m_lPlayID = CLIENT_RealPlay(pMainDlg->GetLoginHandle(), m_cmbChannel.GetCurSel(), 0);
			if(0 != m_lPlayID)
			{
				CLIENT_SetRealDataCallBackEx(m_lPlayID, RealDataCallBackEx, (LDWORD)this, 0x1f);
			}
			else
			{
				g_PlayAPI.PLAY_Stop(g_nPlayPort);
				g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				int x = ::CLIENT_GetLastError();
				MessageBox(ConvertString(_T("Fail to realplay!")), ConvertString("Prompt"));
			}
		}
		else
		{
			g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			MessageBox(ConvertString(_T("Fail to play!")), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString(_T("Fail to OpenStream!")), ConvertString("Prompt"));
	}
	//////////////////////////////////////////////////////////////////////////
	//切换预览视频图像

 	pMainDlg->SetRealPlayHandel(m_lPlayID);
	pMainDlg->SetCurrentChannel(m_cmbChannel.GetCurSel());
	pMainDlg->EnableLoginWindow(LoginOpenView);
	pMainDlg->m_pdlgConfig->InitConfigDlg(m_cmbChannel.GetCurSel());
	Invalidate(FALSE);

}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：Get device info, initialize gui info
//参数：nChnCount，Device's Totle Channe Count；
//返回：无
//////////////////////////////////////////////////////////////////////////
void CPreview::InitPreviewDlg(int nChnCount)
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
		_sntprintf(szItem, _countof(szItem) * sizeof(TCHAR), _T("%s%02d"), ConvertString(_T("Channel")), i + 1);
		m_cmbChannel.InsertString(i, szItem);
		ZeroMemory(szItem, _countof(szItem));
	}

	m_cmbChannel.SetCurSel(-1);


}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：close preview, clear gui info
//参数：
//返回：
//////////////////////////////////////////////////////////////////////////
void CPreview::UninitPreviewDlg()
{
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)GetParent();
	if (pMainDlg)
	{
		if (pMainDlg->GetRealPlayHandle())
		{
			::CLIENT_StopRealPlay(pMainDlg->GetRealPlayHandle());
			
			//////////////////////////////////////////////////////////////////////////
			//
			g_PlayAPI.PLAY_Stop(g_nPlayPort);
			g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			
			//////////////////////////////////////////////////////////////////////////
			GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->SetRealPlayHandel(0);
		}

		if (pMainDlg->GetLoginHandle())
		{
			::CLIENT_Logout(pMainDlg->GetLoginHandle());
			pMainDlg->SetLoginHandel(0);
		}
	}
	//清空组合框
	m_cmbChannel.ResetContent();

}
//////////////////////////////////////////////////////////////////////////
//函数：
//描述：show preview
//参数：
//返回：
//////////////////////////////////////////////////////////////////////////
void CPreview::ShowPreview(LONG lLoginHanlde, int nChannel)
{
	if (!lLoginHanlde || nChannel < 0)
	{
		return;
	}

	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)GetParent();
	if (pMainDlg)
	{
		if (pMainDlg->GetLoginHandle())
		{
			if (pMainDlg->GetRealPlayHandle())
			{
				::CLIENT_StopRealPlay(pMainDlg->GetRealPlayHandle());
				pMainDlg->SetRealPlayHandel(0);
				
				g_PlayAPI.PLAY_Stop(g_nPlayPort);
				g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			}
			
			LLONG m_lPlayID = 0;
			HWND hWnd = GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->GetSafeHwnd();
			NET_DEVICEINFO* pDevInfo = pMainDlg->GetDevInfo();
			int nChnCount = 0;
			if (pDevInfo)
			{
				nChnCount = pDevInfo->byChanNum;
			}
			
			CFG_ANALYSERULES_INFO* pRule
				= (CFG_ANALYSERULES_INFO*)pMainDlg->GetAnalyseRulesInfo(m_cmbChannel.GetCurSel());
			if (!pRule)
			{
				return;
			}

			//Enable stream
			BOOL bOpenRet = g_PlayAPI.PLAY_OpenStream(g_nPlayPort, 0, 0, 1024 * 900);
			if(bOpenRet)
			{
				BOOL bRet = g_PlayAPI.PLAY_SetIVSCallBack(g_nPlayPort, GetIvsInfoProc, (DWORD)this);
				
				DRAW_Reset(g_nPreviewDrawPort, DRAW_RULE);
				DRAW_InputRuleData(g_nPreviewDrawPort, 0, (unsigned char*)pRule, 0);
				DRAW_SetPen(g_nPreviewDrawPort, DRAW_RULE, DRAW_PEN_SOLID, 1, RGB(0, 255, 0));

				bRet = g_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, DrawIvsInfoPreviewProc, (DWORD)this);
				if (!bRet)
				{
					MessageBox(ConvertString("PLAY_RigisterDrawFun failed!"), ConvertString("Prompt"));
				}
				//Begin play 
				BOOL bPlayRet = g_PlayAPI.PLAY_Play(g_nPlayPort, hWnd);
				if(bPlayRet)
				{
					//Real-time play 
					m_lPlayID = CLIENT_RealPlay(pMainDlg->GetLoginHandle(), nChannel, 0);
					if(m_lPlayID)
					{
						pMainDlg->SetRealPlayHandel(m_lPlayID);
						CLIENT_SetRealDataCallBackEx(m_lPlayID, RealDataCallBackEx, (LDWORD)this, 0x1f);
					}
					else
					{
						g_PlayAPI.PLAY_Stop(g_nPlayPort);
						g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
						int x = ::CLIENT_GetLastError();
						MessageBox(ConvertString("Fail to play!"), ConvertString("Prompt"));
					}
				}
				else
				{
					g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
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
void CPreview::ClosePreview(LONG lRealPlayHandle)
{
	if (!lRealPlayHandle)
	{
		return;
	}
	
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)GetParent();
	if (pMainDlg)
	{
		if (pMainDlg->GetRealPlayHandle())
		{
			::CLIENT_StopRealPlay(pMainDlg->GetRealPlayHandle());
			
			g_PlayAPI.PLAY_Stop(g_nPlayPort);
			g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->SetRealPlayHandel(0);
		}
	}
}

void CPreview::DrawIvsInfoPreviewProc(long nPort,HDC hdc,LONG nUser)
{
	CPreview* pDlg = (CPreview*)nUser;
	if (!pDlg || !IsWindow(pDlg->GetSafeHwnd()))
	{
		return;
	}

	HWND hWnd = pDlg->GetDlgItem(IDC_PREVIEW_STATIC_PREVIEW)->GetSafeHwnd();

#define PLAY_CMD_GetRenderNum 4 
	int nFrameNumber = 0;
	int nret = 0;
	BOOL bRet = g_PlayAPI.PLAY_QueryInfo(nPort, 
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

void CPreview::GetIvsInfoProc(char* buf, long type, long len, long reallen, long reserved, long nUser)
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
	popupMenu.TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
}

void CPreview::OnClosePreview()
{
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)GetParent();
	if (!pMainDlg)
	{
		return;
	}

	ClosePreview(pMainDlg->GetRealPlayHandle());
	
	pMainDlg->SetCurrentChannel(-1);
	pMainDlg->m_pdlgConfig->UninitConfigDlg();

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
