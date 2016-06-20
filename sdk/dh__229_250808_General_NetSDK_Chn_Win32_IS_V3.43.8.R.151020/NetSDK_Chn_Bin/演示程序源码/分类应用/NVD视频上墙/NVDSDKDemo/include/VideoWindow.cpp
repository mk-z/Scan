// VideoWindow.cpp: implementation of the CVideoWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VideoWindow.h"
#include "../NVDSDKDemo.h"
#include "../NVDSDKDemoDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define GET_PARENT_DIALOG			((CNVDSDKDemoDlg *)(this->GetParent()))

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVideoWindow::CVideoWindow()
{
	m_nCurMonitorID = 0;
	m_nCurWndID = 0;
}

CVideoWindow::~CVideoWindow()
{

}

int CVideoWindow::SetShowWindow(SPLIT_TYPE nMain, SPLIT_TYPE nSub)
{
	return SetShowPlayWindow(nMain, nSub);
}

CWnd* CVideoWindow::GetShowWindow(int nMain, int nSub)
{
	CMonitorWnd *pWndMonitor = (CMonitorWnd *)GetPage(nMain);
	if (pWndMonitor != NULL)
	{
		return pWndMonitor->GetPage(nSub);
	}

	return NULL;
}

CWnd* CVideoWindow::GetActiveWindow()
{
	if (m_nCurMonitorID == -1 || m_nCurWndID == -1)
	{
		return NULL;
	}

	return GetShowWindow(m_nCurMonitorID, m_nCurWndID);
}

void CVideoWindow::SetActiveWindow(int nMain, int nSub)
{
	CMonitorWnd *pWndMonitor = (CMonitorWnd *)GetPage(nMain);
	if (pWndMonitor != NULL)
	{
		pWndMonitor->SetActivePage(pWndMonitor->GetPage(nSub), FALSE);
	}
	SetActivePage(nMain, FALSE);
}

int CVideoWindow::GetMonitorCurWndNum(int nMain)
{
	CMonitorWnd *pWndMonitor = (CMonitorWnd *)GetPage(nMain);
	if (pWndMonitor != NULL)
	{
		return pWndMonitor->GetCurCount();
	}

	return 0;
}

int CVideoWindow::GetMonitorWndNum(int nMain)
{
	CMonitorWnd *pWndMonitor = (CMonitorWnd *)GetPage(nMain);
	if (pWndMonitor != NULL)
	{
		return pWndMonitor->GetCount();
	}

	return 0;
}

void CVideoWindow::SetMonitorMultiScreen(int nMain, BOOL bFlag)
{
	CMonitorWnd *pWndMonitor = (CMonitorWnd *)GetPage(nMain);
	if (pWndMonitor != NULL)
	{
		pWndMonitor->SetMultiScreen(bFlag);
	}
}

void CVideoWindow::SetWndFlash(int nMain, int nSub, BOOL bFlag)
{
	CMonitorWnd *pWndMonitor = (CMonitorWnd *)GetPage(nMain);
	if (pWndMonitor != NULL)
	{
		CPlayWnd *pSubWnd = (CPlayWnd *)pWndMonitor->GetPage(nSub);
		if (pSubWnd != NULL)
		{
			pSubWnd->SetFlash(bFlag);
			pSubWnd->Invalidate(TRUE);
		}
	}
}

void CVideoWindow::OnVideoLButtonDown(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{
	m_nCurMonitorID = nMonitorID;
	m_nCurWndID = nWndID;
}

void CVideoWindow::OnVideoLButtonUp(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CVideoWindow::OnVideoLButtonDblClk(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{
	int nCurWndNum = GetMonitorCurWndNum(nMonitorID);

	int nWndNum = GetMonitorWndNum(nMonitorID);

	if (GET_PARENT_DIALOG)
	{
		GET_PARENT_DIALOG->OnVideoLButtonDblClk(nMonitorID, nWndID, nCurWndNum==1?FALSE:TRUE, nWndNum);
	}
}

void CVideoWindow::onVideoRButtonDown(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CVideoWindow::onVideoRButtonUp(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CVideoWindow::onVideoMove(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CVideoWindow::onVideoMoving(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{
	
}