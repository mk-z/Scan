// PlayCtrlPannel.cpp : implementation file
//

#include "StdAfx.h"
#include "netsdkdemo.h"
#include "PlayCtrlPannel.h"
#include "NetSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayCtrlPannel dialog


CPlayCtrlPannel::CPlayCtrlPannel(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayCtrlPannel::IDD, pParent)
{
	m_myBrush.CreateSolidBrush(RGB(170,170,170));
	//{{AFX_DATA_INIT(CPlayCtrlPannel)
	m_play_frame = 0;
	//}}AFX_DATA_INIT
}


void CPlayCtrlPannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayCtrlPannel)
	DDX_Control(pDX, IDC_PLAY_POSITION, m_play_position);
	DDX_Text(pDX, IDC_PLAY_FRAME, m_play_frame);
	DDV_MinMaxUInt(pDX, m_play_frame, 0, 120);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayCtrlPannel, CDialog)
	//{{AFX_MSG_MAP(CPlayCtrlPannel)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PLAY_POSITION, OnReleasedcapturePlayPosition)
	ON_BN_CLICKED(IDC_CTRL_PLAY, OnCtrlPlay)
	ON_BN_CLICKED(IDC_CTRL_PLAYSTOP, OnCtrlPlaystop)
	ON_BN_CLICKED(IDC_CTRL_STEPPLAY, OnCtrlStepplay)
	ON_BN_CLICKED(IDC_CTRL_PLAYFAST, OnCtrlPlayfast)
	ON_BN_CLICKED(IDC_CTRL_PLAYSLOW, OnCtrlPlayslow)
	ON_BN_CLICKED(IDC_CTRL_FRAMECONTROL, OnCtrlFramecontrol)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayCtrlPannel message handlers

BOOL CPlayCtrlPannel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	g_SetWndStaticText(this);

	m_bPlaying = FALSE;
	lPlayCount = 0;
	m_play_position.SetRange(0, 100);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayCtrlPannel::OnReleasedcapturePlayPosition(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nPos = m_play_position.GetPos();

	BOOL bRet = ((CNetSDKDemoDlg *)GetParent())->SeekPlayPositon(nPos);
	if (bRet)
	{
		CString str;
		str.Format("[%d%%]",nPos);
		GetDlgItem(IDC_INT_PLAYPOS)->SetWindowText(str);
	}
}


void CPlayCtrlPannel::OnCtrlPlay() 
{
	BOOL bRet =	((CNetSDKDemoDlg *)GetParent())->PlayCtrl_Play();
	if (bRet)
	{
		if(!m_bPlaying)
		{
			m_bPlaying = TRUE;
			GetDlgItem(IDC_CTRL_PLAY)->SetWindowText(ConvertString(MSG_DEMODLG_PAUSE));
		}
		else
		{
			m_bPlaying = FALSE;
			GetDlgItem(IDC_CTRL_PLAY)->SetWindowText(ConvertString(MSG_DEMODLG_PLAY));
		}
	}
}

void CPlayCtrlPannel::OnCtrlPlaystop() 
{
	BOOL bRet =	((CNetSDKDemoDlg *)GetParent())->PlayCtrl_Stop();
	if (bRet)
	{
		StopPlay();
	}
	else
	{
		//主窗口已有提示，这里暂时不需要处理。
	}
}

void CPlayCtrlPannel::OnCtrlStepplay() 
{
	BOOL bRet =	((CNetSDKDemoDlg *)GetParent())->PlayCtrl_Step();
	if (!bRet)
	{
		//主窗口已有提示，这里暂时不需要处理。
	}
}

void CPlayCtrlPannel::OnCtrlPlayfast() 
{
	BOOL bRet =	((CNetSDKDemoDlg *)GetParent())->PlayCtrl_Fast();
	if (!bRet)
	{
		//主窗口已有提示，这里暂时不需要处理。
	}
}

void CPlayCtrlPannel::OnCtrlPlayslow() 
{
	BOOL bRet =	((CNetSDKDemoDlg *)GetParent())->PlayCtrl_Slow();
	if (!bRet)
	{
		//主窗口已有提示，这里暂时不需要处理。
	}
}

void CPlayCtrlPannel::OnCtrlFramecontrol() 
{
	if (!UpdateData(true))
	{
		return;
	}
	BOOL bRet =	((CNetSDKDemoDlg *)GetParent())->PlayCtrl_Frame(m_play_frame);
	if (!bRet)
	{
		//主窗口已有提示，这里暂时不需要处理。
	}
}

void CPlayCtrlPannel::StartPlay()
{
	m_bPlaying = TRUE;
	lPlayCount++;

	GetDlgItem(IDC_CTRL_PLAY)->SetWindowText(ConvertString(MSG_DEMODLG_PAUSE));
	SetTimer((UINT)this,1000,0);
}

void CPlayCtrlPannel::StopPlay()
{
	m_bPlaying = FALSE;
	lPlayCount--;
	if (0 == lPlayCount) 
	{	
		GetDlgItem(IDC_CTRL_PLAY)->SetWindowText(ConvertString(MSG_DEMODLG_PLAY));
		m_play_position.SetPos(0);
		GetDlgItem(IDC_INT_PLAYPOS)->SetWindowText("[ 0 %]");
		m_play_frame = 0;
		GetDlgItem(IDC_PLAY_FRAME)->SetWindowText("0");
		KillTimer((UINT)this);
	}

}

HBRUSH CPlayCtrlPannel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (pWnd->GetDlgCtrlID() != IDC_PLAY_FRAME)
	{	
		pDC->SetBkMode(TRANSPARENT);
		return m_myBrush;
	}

	return hbr;
}


void CPlayCtrlPannel::OnTimer(UINT_PTR nIDEvent) 
{
	int fileframe = 0;
	int playframe = 0;
	int pos = 0;

	CNetSDKDemoDlg *pMain = (CNetSDKDemoDlg *)AfxGetMainWnd();

	int curScreen = pMain->GetCurScreen();

	SplitInfoNode siNode;
	memset(&siNode, 0, sizeof(siNode));
	BOOL ret = pMain->GetSplitInfo_Main(curScreen, &siNode);
	if (!ret)
	{
		MessageBox(ConvertString("error while getting split info"));
	}

//	EnterCriticalSection(&g_csPlayPos);

	//验证播放id与当前画面记录的信息是否一致
	if(siNode.Type == SPLIT_TYPE_NETPLAY)
	{
		SplitNetPlayParam *nParam = (SplitNetPlayParam *)siNode.Param;
		pos = nParam->iPlayPos;
		BOOL nRet = CLIENT_GetFramePlayBack(siNode.iHandle, &fileframe, &playframe);
		if(!nRet)
		{
			return;
		//	pMain->LastError();
		}
	}
	else if (siNode.Type == SPLIT_TYPE_PBBYTIME)
	{
		SplitPBByTimeParam *pbParam = (SplitPBByTimeParam *)siNode.Param;
		pos = pbParam->npos;
		BOOL nRet = CLIENT_GetFramePlayBack(siNode.iHandle, &fileframe, &playframe);
		if(!nRet)
		{
			return;
		//	pMain->LastError();		
		}
	}

//	LeaveCriticalSection(&g_csPlayPos);
	if (!m_play_position.m_bLButtonDown)
	{
		m_play_position.SetPos(pos);
	}

	CString str;
	str.Format("[%d%%]", pos);
	GetDlgItem(IDC_INT_PLAYPOS)->SetWindowText(str);
	
	if(GetDlgItem(IDC_PLAY_FRAME) != GetFocus())
	{
		str.Format("%d", playframe);
		GetDlgItem(IDC_PLAY_FRAME)->SetWindowText(str);
	}
	
}

BOOL CPlayCtrlPannel::PreTranslateMessage(MSG* pMsg) 
{
	if (WM_KEYDOWN == pMsg->message && 
		(VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
