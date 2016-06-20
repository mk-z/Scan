// PlayBackProcess.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "PlayBackProcess.h"
#include "NVDSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayBackProcess dialog


CPlayBackProcess::CPlayBackProcess(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayBackProcess::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayBackProcess)
	//}}AFX_DATA_INIT
	m_nTimer = 0;
}


void CPlayBackProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayBackProcess)
	DDX_Control(pDX, IDC_SLIDER_PROCESS, m_ctlProcess);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayBackProcess, CDialog)
	//{{AFX_MSG_MAP(CPlayBackProcess)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_PROCESS, OnReleasedcaptureSliderProcess)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PLAY, OnBtnPlay)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayBackProcess message handlers

BOOL CPlayBackProcess::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	CRect rectContainer;
	GetClientRect(&rectContainer);

	MoveWindow(0, 0, rectContainer.Width(), rectContainer.Height());
	CenterWindow();

	m_ctlProcess.SetRange(0, 100);
	m_ctlProcess.SetPos(0);
	m_ctlProcess.SetSelection(0, 0);

	m_nTimer = SetTimer(1, 500, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPlayBackProcess::OnBtnClose() 
{
	// TODO: Add your control notification handler code here
	this->ShowWindow(SW_HIDE);
}


void CPlayBackProcess::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ClientToScreen(&point);                             
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CPlayBackProcess::OnReleasedcaptureSliderProcess(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(0 != m_nTimer)
	{
		KillTimer(m_nTimer);
		m_nTimer = 0;
	}
	
	int nOffsetPos = m_ctlProcess.GetPos();
	
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	if (pParentDlg == NULL)
	{
		return;
	}
	LONG lLoinHandle = pParentDlg->m_stuShowWindow[pParentDlg->m_screenPannel.m_nCurMonitorID][pParentDlg->m_screenPannel.m_nCurWndID].lDecLoginID;
	int nEncoderNum = pParentDlg->m_stuShowWindow[pParentDlg->m_screenPannel.m_nCurMonitorID][pParentDlg->m_screenPannel.m_nCurWndID].nEncoderNum;
	CReadWriteMutexLock lock(pParentDlg->m_csDecoder);
	
	list<DECODER_INFO*>::iterator it = pParentDlg->m_lstDecoders.begin();
	while (it != pParentDlg->m_lstDecoders.end())
	{
		DECODER_INFO *pDecoderInfo = (DECODER_INFO *)(*it);
		if (pDecoderInfo != NULL)
		{
			if (pDecoderInfo->lLoginID == lLoinHandle)
			{
				if (nEncoderNum < NVD_ENCODER_MAX)
				{
					pDecoderInfo->dwCurSize[nEncoderNum] = nOffsetPos * pDecoderInfo->dwTotalSize[nEncoderNum]/100;
				}
				break;
			}
		}
		
		++it;
	}
	lock.Unlock();

	if (pParentDlg != NULL)
	{
		pParentDlg->PlaybackSeek(nOffsetPos);
	}

	if(0 == m_nTimer)
	{
		m_nTimer = SetTimer(1, 500, NULL);
	}

	*pResult = 0;
}

void CPlayBackProcess::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	if(nIDEvent == m_nTimer && pParentDlg != NULL)
	{
		int nOffsetPos = pParentDlg->GetCurWndPlaybackPos();

		m_ctlProcess.SetPos(nOffsetPos);
		m_ctlProcess.SetSelection(0, nOffsetPos);
		m_ctlProcess.Invalidate();
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CPlayBackProcess::ExSliderButtonDown()
{
	if(0 != m_nTimer)
	{
		KillTimer(m_nTimer);
		m_nTimer = 0;
	}
}

void CPlayBackProcess::ExSliderButtonUp()
{
	if(0 == m_nTimer)
	{
		m_nTimer = SetTimer(1, 500, NULL);
	}
}

void CPlayBackProcess::OnBtnPlay() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	LLONG lLoinHandle = pParentDlg->m_stuShowWindow[pParentDlg->m_screenPannel.m_nCurMonitorID][pParentDlg->m_screenPannel.m_nCurWndID].lDecLoginID;
	int nEncoderNum = pParentDlg->m_stuShowWindow[pParentDlg->m_screenPannel.m_nCurMonitorID][pParentDlg->m_screenPannel.m_nCurWndID].nEncoderNum;
	int nPlayType = pParentDlg->m_stuShowWindow[pParentDlg->m_screenPannel.m_nCurMonitorID][pParentDlg->m_screenPannel.m_nCurWndID].nPlayType;
	if (lLoinHandle != 0 && nPlayType != 0)
	{
		CString strText;
		GetDlgItemText(IDC_BTN_PLAY,strText);
		if(strText ==  ConvertString("PLAY"))
		{
			//BOOL bSuccess = CLIENT_CtrlDecPlayback(lLoinHandle, nEncoderNum, Dec_Playback_Pause, 0, 1000);
			BOOL bSuccess = CLIENT_CtrlDecPlayback(lLoinHandle, nEncoderNum, Dec_Playback_Play, 0, 1000);
			if (bSuccess)
			{
				SetDlgItemText(IDC_BTN_PLAY, ConvertString("PAUSE"));
			}
		}
		else
		{
			//BOOL bSuccess = CLIENT_CtrlDecPlayback(lLoinHandle, nEncoderNum, Dec_Playback_Play, 0, 1000);
			BOOL bSuccess = CLIENT_CtrlDecPlayback(lLoinHandle, nEncoderNum, Dec_Playback_Pause, 0, 1000);
			if (bSuccess)
			{
				SetDlgItemText(IDC_BTN_PLAY, ConvertString("PLAY"));
			}
		}
	}
}

void CPlayBackProcess::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	LLONG lLoinHandle = pParentDlg->m_stuShowWindow[pParentDlg->m_screenPannel.m_nCurMonitorID][pParentDlg->m_screenPannel.m_nCurWndID].lDecLoginID;
	int nEncoderNum = pParentDlg->m_stuShowWindow[pParentDlg->m_screenPannel.m_nCurMonitorID][pParentDlg->m_screenPannel.m_nCurWndID].nEncoderNum;
	int nPlayType = pParentDlg->m_stuShowWindow[pParentDlg->m_screenPannel.m_nCurMonitorID][pParentDlg->m_screenPannel.m_nCurWndID].nPlayType;
	if (lLoinHandle != 0 && nPlayType != 0)
	{
		BOOL bSuccess = CLIENT_CtrlDecPlayback(lLoinHandle, nEncoderNum, Dec_Playback_Stop, 0, 2000);
		if (bSuccess)
		{
			SetDlgItemText(IDC_BTN_PLAY, ConvertString("PLAY"));
		}
	}
}
