// PlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PlayWnd.h"
#include "MonitorWnd.h"
#include "../NVDSDKDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GET_PARENT_MONITOR			((CMonitorWnd *)(this->GetParent()))

/////////////////////////////////////////////////////////////////////////////
// CPlayWnd

CPlayWnd::CPlayWnd()
{
	m_nWndID = 0;
	m_bDoing = FALSE;
	m_nNum = 0;
}

CPlayWnd::~CPlayWnd()
{
}


BEGIN_MESSAGE_MAP(CPlayWnd, CWnd)
	//{{AFX_MSG_MAP(CPlayWnd)
	ON_WM_CONTEXTMENU()
	ON_WM_ERASEBKGND()
	ON_COMMAND_RANGE(VIDEO_MENU_BASE, VIDEO_MENU_END, OnVideoMenu)
	ON_MESSAGE(VIDEO_REPAINT, OnRepaintWnd)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPlayWnd message handlers

LRESULT CPlayWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			GET_PARENT_MONITOR->SetActivePage(this, FALSE);
			GET_PARENT_MONITOR->OnVideoLButtonDown(m_nWndID, wParam, lParam);
		}
		break;
	case WM_LBUTTONUP:
		{
			GET_PARENT_MONITOR->OnVideoLButtonUp(m_nWndID, wParam, lParam);
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
//			GET_PARENT_MONITOR->SetMultiScreen(!GET_PARENT_MONITOR->GetMultiScreen());
			GET_PARENT_MONITOR->OnVideoLButtonDblClk(m_nWndID, wParam, lParam);
		}
		break;
	case WM_RBUTTONDOWN:
		{
			GET_PARENT_MONITOR->onVideoRButtonDown(m_nWndID, wParam, lParam);
		}
		break;
	case WM_RBUTTONUP:
		{
			GET_PARENT_MONITOR->onVideoRButtonUp(m_nWndID, wParam, lParam);
		}
		break;
	case WM_MOVE:
		{
			GET_PARENT_MONITOR->onVideoMove(m_nWndID, wParam, lParam);
		}
		break;
	case WM_MOVING:
		{
			GET_PARENT_MONITOR->onVideoMoving(m_nWndID, wParam, lParam);
		}
		break;
	default:
		break;
	}
	
	return CWnd::DefWindowProc(message, wParam, lParam);
}

BOOL CPlayWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(VIDEO_BACK_COLOR);
	pDC->FillRect(&rect, &brush);
	return TRUE;
}

void CPlayWnd::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING | GET_PARENT_MONITOR->GetFullScreen() ? MF_CHECKED : MF_UNCHECKED, VIDEO_MENU_FULLSCREEN, ConvertString(NAME_MENU_FULLSCREEN));
	menu.AppendMenu(MF_STRING | GET_PARENT_MONITOR->GetMultiScreen() ? MF_CHECKED : MF_UNCHECKED, VIDEO_MENU_MULTISCREEN, ConvertString(NAME_MENU_MULTISCREEN));
	menu.AppendMenu(MF_STRING | GET_PARENT_MONITOR->GetAutoAdjustPos() ? MF_CHECKED : MF_UNCHECKED, VIDEO_MENU_AUTOADJUST, ConvertString(NAME_MENU_AUTOADJUST));

	TrackPopupMenu( 
		menu.m_hMenu, 
		TPM_LEFTALIGN, 
		point.x, 
		point.y,
		0,
		m_hWnd,
		NULL);
}

void CPlayWnd::OnVideoMenu(UINT nID)
{
	switch(nID)
	{
	case VIDEO_MENU_FULLSCREEN:
		GET_PARENT_MONITOR->SetFullScreen(!GET_PARENT_MONITOR->GetFullScreen());
		break;
	case VIDEO_MENU_MULTISCREEN:
//		GET_PARENT_MONITOR->SetMultiScreen(!GET_PARENT_MONITOR->GetMultiScreen());
		GET_PARENT_MONITOR->OnVideoLButtonDblClk(m_nWndID, 0, 0);
		break;
	case VIDEO_MENU_AUTOADJUST:
		GET_PARENT_MONITOR->SetAutoAdjustPos(!GET_PARENT_MONITOR->GetAutoAdjustPos());
		break;
	default:
		break;
	}
}

LRESULT CPlayWnd::OnRepaintWnd(WPARAM wParam, LPARAM lParam)
{
	Invalidate();
	
	return 0;
}

void CPlayWnd::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rectText;
	CRect rect;
	
	if (m_bDoing)
	{
		CString str = "";
		
		if (++m_nNum > 6)
		{
			m_nNum = 0;
			str = ".     ";
		}
		else
		{
			for (int i = 0; i < m_nNum; i++)
			{
				str += ".";
			}
			
			for (int j = m_nNum; j < 6; j++)
			{
				str += " ";
			}
		}
		
		GetClientRect(&rect);
		rectText.left = rect.Width()/2 - 100;
		rectText.right = rect.Width()/2 + 100;
		rectText.top = rect.Height()/2 - 8;
		rectText.bottom = rect.Height()/2 + 8;
		ShowCaptureText(str, &rectText);
	}

	CWnd::OnTimer(nIDEvent);
}

BOOL CPlayWnd::ShowCaptureText(CString strText, LPRECT lpRect)
{
	if (strText.IsEmpty())
	{  
		return FALSE;
	}
	
	CDC *pDC = GetDC();
	if(pDC == NULL)
	{
		return FALSE;
	}

	pDC->SetTextColor(RGB(232,226,63));
	pDC->SetBkColor(VIDEO_BACK_COLOR); 
	pDC->DrawText(strText, lpRect, DT_CENTER | ETO_OPAQUE | ETO_CLIPPED);

	ReleaseDC(pDC);
	return TRUE;
}

void CPlayWnd::SetFlash(BOOL bFlag)
{
	m_bDoing = bFlag;
}

