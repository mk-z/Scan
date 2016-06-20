// WndContainer.cpp : implementation file
//

#include "stdafx.h"
#include "WndContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndContainer

CWndContainer::CWndContainer()
{
	m_pActivePage = NULL;
	m_bDrawActive = FALSE;
	m_clrTopLeft = RGB(255, 0, 0);
	m_clrBottomRight = RGB(255, 0, 0);
	
	m_bFullScreen = FALSE;
	m_bMultiScreen = TRUE;
	m_bAutoAdjustPos = FALSE;
	m_nShowPortion = 100;
}

CWndContainer::~CWndContainer()
{
	while(!m_PageList.IsEmpty())
	{
		m_PageList.RemoveHead();
	}
}


BEGIN_MESSAGE_MAP(CWndContainer, CWnd)
	//{{AFX_MSG_MAP(CWndContainer)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndContainer message handlers

BOOL CWndContainer::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	dwStyle|=WS_EX_TOOLWINDOW;
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CWndContainer::SetShowPlayWindow(int nMonitorNum, int nPageNum)
{
	m_bMultiScreen = TRUE;
	POSITION pos = m_PageList.GetHeadPosition();
	while(pos != NULL)
	{
		CWnd* pWnd = m_PageList.GetNext(pos);
		if (pWnd != NULL)
		{
			pWnd->ShowWindow(SW_HIDE);
		}
	}

	m_PageList.RemoveAll();
	
	for(int i = 0; i < nMonitorNum; i++)
	{
		m_WndMonitor[i].SetShowPlayWindow(nPageNum);
		AddPage(&m_WndMonitor[i], TRUE);
	}

	m_WndMonitor[0].SetActivePage(m_WndMonitor[0].GetPage(0), FALSE);
	m_pActivePage = &m_WndMonitor[0];

	return m_PageList.GetCount();
}

BOOL CWndContainer::AddPage(CWnd *pWnd, BOOL bRepaint)
{
	if(pWnd == NULL || !IsWindow(pWnd->m_hWnd))
	{
		return FALSE;
	}

	POSITION pos = m_PageList.Find(pWnd);
	if(pos != NULL) 
	{
		return TRUE;
	}

	m_PageList.AddTail(pWnd);

	if(m_bDrawActive)
	{
		DrawActivePage(FALSE);
	}

//	SetActivePage(pWnd, bRepaint);

	return TRUE;
}

CWnd* CWndContainer::DelPage(CWnd *pWnd)
{
	POSITION pos = m_PageList.Find(pWnd);
	if(pos == NULL)
	{
		TRACE("This Window is not a member of container, the operation will terminate.\n");
		return NULL;
	}

	if(pWnd == m_pActivePage)
	{
		if(m_pActivePage == GetPrevPage(pWnd))
		{
			m_pActivePage = NULL;
		}
		else
		{
			m_pActivePage = GetPrevPage(pWnd);
		}
	}
	
	m_PageList.RemoveAt(pos);

	if (pWnd)
	{
		pWnd->ShowWindow(SW_HIDE);
	}

	return pWnd;
}

CWnd* CWndContainer::DelPage()
{
	return DelPage(m_pActivePage);
}

CWnd* CWndContainer::GetPage(int nIndex)
{
	POSITION pos = m_PageList.FindIndex(nIndex);
	if(pos == NULL)
	{
		return NULL;
	}

	return m_PageList.GetAt(pos);
}

void CWndContainer::SetActivePage(CWnd *pWnd, BOOL bRepaint)
{
	if(pWnd == NULL || !IsWindow(pWnd->m_hWnd))
	{
		return;
	}

	POSITION pos = m_PageList.Find(pWnd);
	if(pos == NULL)
	{
		TRACE("__This Window is not a member of container, the operation will terminate.\n");
		return;
	}

	if(m_bDrawActive)
	{
		DrawActivePage(FALSE);
	}

	m_pActivePage = pWnd;

	if(bRepaint)
	{
		UpdateWnd();
	}

	if(m_bDrawActive)
	{
		DrawActivePage(TRUE);
	}
}

void CWndContainer::SetActivePage(int nMonitorID, BOOL bRepaint)
{
	for(POSITION pos = m_PageList.GetHeadPosition(); pos != NULL;)
	{
		CMonitorWnd *pWnd = (CMonitorWnd *)m_PageList.GetNext(pos);
		if (pWnd->GetMonitorID() == nMonitorID)
		{
//			SetActivePage(pWnd, bRepaint);
		}
		else
		{
			pWnd->CleanActivePage();
		}
	}
}

CWnd* CWndContainer::GetActivePage()
{
	return m_pActivePage;
}

void CWndContainer::SetDrawActivePage(BOOL bFlag, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	if(m_bDrawActive == bFlag)
	{
		return;
	}

	if(bFlag)
	{
		m_clrTopLeft = clrTopLeft;
		m_clrBottomRight = clrBottomRight;
	}

	m_bDrawActive = bFlag;
}

BOOL CWndContainer::GetDrawActivePage()
{
	return m_bDrawActive;
}

void CWndContainer::SetShowPortion(int nPortion)
{
	if(m_nShowPortion == nPortion)
	{
		return;
	}
	
	if(m_nShowPortion < 40)
	{
		m_nShowPortion = 40;
	}

	if(m_nShowPortion > 100)
	{
		m_nShowPortion = 100;
	}

	m_nShowPortion = nPortion;
	Invalidate();
}

int CWndContainer::GetShowPortion()
{
	return m_nShowPortion;
}

CWnd* CWndContainer::GetNextPage(CWnd *pWnd)
{
	if(pWnd == NULL || !IsWindow(pWnd->m_hWnd))
	{
		return NULL;
	}

	POSITION pos = m_PageList.Find(pWnd);
	if(pos == NULL)
	{
		TRACE("This Window is not a member of container, the operation will terminate.\n");
		return NULL;
	}
	
	m_PageList.GetNext(pos);
	if(pos == NULL)
	{
		return m_PageList.GetHead();
	}
	else
	{
		return m_PageList.GetNext(pos);
	}

	return NULL;
}

CWnd* CWndContainer::GetPrevPage(CWnd *pWnd)
{
	if(pWnd == NULL || !IsWindow(pWnd->m_hWnd))
	{
		return NULL;
	}

	POSITION pos = m_PageList.Find(pWnd);
	if(pos == NULL)
	{
		TRACE("This Window is not a member of container, the operation will terminate.\n");
		return NULL;
	}
	
	m_PageList.GetPrev(pos);
	if(pos == NULL)
	{
		return m_PageList.GetTail();
	}
	else
	{
		return m_PageList.GetPrev(pos);
	}

	return NULL;
}

int CWndContainer::GetCount() const
{
	return m_PageList.GetCount();
}

CWnd* CWndContainer::GetTailPage()
{
	return m_PageList.GetTail();
}

void CWndContainer::SetFullScreen(BOOL bFlag)
{
	if(bFlag == m_bFullScreen)
	{
		return;
	}

	if(bFlag)
	{
		int cx = GetSystemMetrics(SM_CXSCREEN);
		int cy = GetSystemMetrics(SM_CYSCREEN);

		GetWindowPlacement(&m_windowPlace);

		ModifyStyle(WS_CHILD, WS_POPUP);
	
		m_wndParent = SetParent(NULL);
		m_wndParent->ShowWindow(SW_HIDE);

		MoveWindow(0, 0, cx, cy);
	}
	else
	{
		m_wndParent->ShowWindow(SW_SHOW);
		SetParent(m_wndParent);

		ModifyStyle(WS_POPUP, WS_CHILD);

		SetWindowPlacement(&m_windowPlace);
	}

	m_bFullScreen = bFlag;
	Invalidate();
}

BOOL CWndContainer::GetFullScreen()
{
	return m_bFullScreen;
}

void CWndContainer::SetMultiScreen(BOOL bFlag)
{
	if(m_bMultiScreen == bFlag)
	{
		return;
	}

	m_bMultiScreen = bFlag;
	Invalidate();
}

BOOL CWndContainer::GetMultiScreen()
{
	return m_bMultiScreen;
}

void CWndContainer::SetAutoAdjustPos(BOOL bFlag)
{
	if(m_bAutoAdjustPos == bFlag)
	{
		return;
	}

	m_bAutoAdjustPos = bFlag;
	Invalidate();
}

BOOL CWndContainer::GetAutoAdjustPos()
{
	return m_bAutoAdjustPos;
}

int CWndContainer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	for(int i = 0; i < MAX_CHANNELNUM; i++)
	{
		m_WndMonitor[i].Create(
			NULL, 
			NULL, 
			WS_VISIBLE | WS_CHILD,
			CRect(0, 0, 0, 0),
			this,
			1979,
			NULL);

		m_WndMonitor[i].SetMonitorID(i);
		
		AddPage(&m_WndMonitor[i]);
	}

//	SetActivePage(&m_WndMonitor[0], TRUE);
//	SetDrawActivePage(TRUE, RGB(248,5,182), RGB(248,5,182));
	
	return 0;
}

BOOL CWndContainer::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(CONTAINER_BACK_COLOR);
	pDC->FillRect(&rect, &brush);

	return TRUE;
}

void CWndContainer::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	UpdateWnd();
	// Do not call CWnd::OnPaint() for painting messages
}

void CWndContainer::UpdateWnd()
{
	if(!IsWindowVisible() || IsIconic())
	{
		return;
	}

	CRect rectContainer;
	GetClientRect(&rectContainer);
	GetShowRect(&rectContainer);
//	rectContainer.DeflateRect(1,1);

	if(m_bAutoAdjustPos)
	{
		AdjustRect(&rectContainer);
	}

	if(m_bMultiScreen)
	{
		CRect rect;
		int nCount = m_PageList.GetCount();
		int i = 0;
		for(POSITION pos = m_PageList.GetHeadPosition(); pos != NULL; i++)
		{
			CWnd *pWnd = m_PageList.GetNext(pos);

			rect = rectContainer;
			CalcPageRect(&rect, i, nCount);
			rect.DeflateRect(WINDOW_MONITOR_SPACE, WINDOW_MONITOR_SPACE, WINDOW_MONITOR_SPACE, WINDOW_MONITOR_SPACE); // 窗口之间的间隔
			pWnd->MoveWindow(&rect);
			pWnd->ShowWindow(SW_SHOW);
		}

		if(m_bDrawActive && m_PageList.GetCount() > 1)
		{
			DrawActivePage(TRUE);
		}
	}
	else
	{
		for(POSITION pos = m_PageList.GetHeadPosition(); pos!=NULL;)
		{
			CWnd *pWnd = m_PageList.GetNext(pos);
			if(pWnd == m_pActivePage)
			{
				pWnd->MoveWindow(&rectContainer);
			}
			else 
			{
				if(m_bFullScreen)
					pWnd->MoveWindow(0,0,1,1);
				else
					pWnd->MoveWindow(rectContainer.right+1, rectContainer.bottom+1, 1, 1);
			}
		}
	}
}

void CWndContainer::OnVideoLButtonDown(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{
	
}

void CWndContainer::OnVideoLButtonUp(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CWndContainer::OnVideoLButtonDblClk(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CWndContainer::onVideoRButtonDown(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CWndContainer::onVideoRButtonUp(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CWndContainer::onVideoMove(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CWndContainer::onVideoMoving(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam)
{

}

void CWndContainer::GetShowRect(LPRECT lpRect)
{
	if(m_nShowPortion < 40) m_nShowPortion = 40;
	if(m_nShowPortion > 100) m_nShowPortion = 100;

	int nWidth = lpRect->right - lpRect->left;
	int nHeight	= lpRect->bottom - lpRect->top;

	int nNewWidth = (int)(nWidth*m_nShowPortion/100);
	int nNewHeight = (int)(nHeight*m_nShowPortion/100);

	int ndx	= (nWidth-nNewWidth)/2;
	int ndy = (nHeight-nNewHeight)/2;

	lpRect->left = lpRect->left	+ ndx;
	lpRect->top = lpRect->top + ndy;
	lpRect->right = lpRect->left + nNewWidth;
	lpRect->bottom = lpRect->top + nNewHeight;
}

void CWndContainer::AdjustRect(LPRECT lpRect)
{
	int nWidth = lpRect->right - lpRect->left;
	int nHeight = lpRect->bottom - lpRect->top;
	CPoint point((lpRect->left + lpRect->right)/2, (lpRect->top + lpRect->bottom)/2);

	int nTemp = nWidth*8/11;
	if(nTemp > nHeight)
	{
		nWidth = nHeight*11/8;
	}
	else if(nTemp < nHeight)
	{
		nHeight = nTemp;
	}

	lpRect->left = point.x - nWidth/2;
	lpRect->right = point.x + nWidth/2;
	lpRect->top = point.y - nHeight/2;
	lpRect->bottom = point.y + nHeight/2;
}

void CWndContainer::CalcPageRect(LPRECT lpRect, int nIndex, int nPageCount)
{
	if(nPageCount <= 0 || nIndex >= nPageCount)
	{
		lpRect->left = lpRect->right = lpRect->top = lpRect->bottom = 0;
		return;
	}

	//get row count
	int nRow=0;
	while((nRow)*(nRow) < nPageCount) nRow++;

	//get singledlg width and height
	int nWidth = (lpRect->right - lpRect->left)/nRow;
	int nHeight = (lpRect->bottom - lpRect->top)/nRow;

	//get top-left point
	CPoint point;
	point.x = lpRect->left + nWidth*(nIndex%nRow);
	point.y = lpRect->top + nHeight*(nIndex/nRow);

	//set rect return back
	lpRect->left = point.x;
	lpRect->top = point.y;
	lpRect->right = lpRect->left + nWidth;
	lpRect->bottom = lpRect->top + nHeight;
}

void CWndContainer::DrawActivePage(BOOL bFlag)
{
	if(!m_bMultiScreen || !m_pActivePage || m_PageList.GetCount() < 2)
	{
		return;
	}

	CRect rect;
	m_pActivePage->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.InflateRect(1,1);

	if(bFlag)
	{
		CDC *pDC = GetDC();
		if(pDC == NULL)
		{
			return;
		}

		pDC->Draw3dRect(&rect, m_clrTopLeft, m_clrBottomRight);	

		ReleaseDC(pDC);
	}
	else
	{
		CDC *pDC = GetDC();
		if(pDC == NULL)
		{
			return;
		}

		pDC->Draw3dRect(&rect, CONTAINER_BACK_COLOR, CONTAINER_BACK_COLOR);	

		ReleaseDC(pDC);
	}
}