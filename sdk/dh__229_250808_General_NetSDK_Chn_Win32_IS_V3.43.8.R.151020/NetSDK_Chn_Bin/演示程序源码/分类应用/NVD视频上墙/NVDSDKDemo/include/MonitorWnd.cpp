// MonitorWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MonitorWnd.h"
#include "WndContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GET_PARENT_CONTAINER			((CWndContainer *)(this->GetParent()))

/////////////////////////////////////////////////////////////////////////////
// CMonitorWnd

CMonitorWnd::CMonitorWnd()
{
	m_nMonitorID = 0;

	m_pActivePage = NULL;
	m_bDrawActive = TRUE;
	m_clrTopLeft = RGB(255, 0, 0);
	m_clrBottomRight = RGB(255, 0, 0);

	m_bMultiScreen = TRUE;
	m_bAutoAdjustPos = FALSE;
	m_nShowPortion = 100;
}

CMonitorWnd::~CMonitorWnd()
{
	while(!m_PageList.IsEmpty())
	{
		m_PageList.RemoveHead();
	}
}


BEGIN_MESSAGE_MAP(CMonitorWnd, CWnd)
	//{{AFX_MSG_MAP(CMonitorWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMonitorWnd message handlers

BOOL CMonitorWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	dwStyle|=WS_EX_TOOLWINDOW;
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CMonitorWnd::SetShowPlayWindow(int nWindowNum, int nBeginNum)
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
	
	for(int i = nBeginNum; i < (nBeginNum+nWindowNum); i++)
	{
		AddPage(&m_WndVideo[i], TRUE);
	}

//	SetActivePage(&m_WndVideo[nBeginNum], TRUE);

	return m_PageList.GetCount();
}

BOOL CMonitorWnd::AddPage(CWnd *pWnd, BOOL bRepaint)
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

CWnd* CMonitorWnd::DelPage(CWnd *pWnd)
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

CWnd* CMonitorWnd::DelPage()
{
	return DelPage(m_pActivePage);
}

CWnd* CMonitorWnd::GetPage(int nIndex)
{
	POSITION pos = m_PageList.FindIndex(nIndex);
	if(pos == NULL)
	{
		return NULL;
	}

	return m_PageList.GetAt(pos);
}

void CMonitorWnd::SetActivePage(CWnd *pWnd, BOOL bRepaint)
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

	m_bDrawActive = TRUE;
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

CWnd* CMonitorWnd::GetActivePage()
{
	return m_pActivePage;
}

void CMonitorWnd::CleanActivePage()
{
	DrawActivePage(FALSE);
	m_bDrawActive = FALSE;
}

void CMonitorWnd::SetDrawActivePage(BOOL bFlag, COLORREF clrTopLeft, COLORREF clrBottomRight)
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

BOOL CMonitorWnd::GetDrawActivePage()
{
	return m_bDrawActive;
}

void CMonitorWnd::SetShowPortion(int nPortion)
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

int CMonitorWnd::GetShowPortion()
{
	return m_nShowPortion;
}

CWnd* CMonitorWnd::GetNextPage(CWnd *pWnd)
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

CWnd* CMonitorWnd::GetPrevPage(CWnd *pWnd)
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

int CMonitorWnd::GetCount() const
{
	return m_PageList.GetCount();
}

int CMonitorWnd::GetCurCount()
{
	int nNum = 1;
	if (m_bMultiScreen)
	{
		nNum = m_PageList.GetCount();
	}

	return nNum;
}

CWnd* CMonitorWnd::GetTailPage()
{
	return m_PageList.GetTail();
}

BOOL CMonitorWnd::GetFullScreen()
{
	return GET_PARENT_CONTAINER->GetFullScreen();
}

void CMonitorWnd::SetFullScreen(BOOL bFlag)
{
	GET_PARENT_CONTAINER->SetFullScreen(bFlag);
}

void CMonitorWnd::SetMultiScreen(BOOL bFlag)
{
	if(m_bMultiScreen == bFlag)
	{
		return;
	}

	m_bMultiScreen = bFlag;
	Invalidate();
}

BOOL CMonitorWnd::GetMultiScreen()
{
	return m_bMultiScreen;
}

void CMonitorWnd::SetAutoAdjustPos(BOOL bFlag)
{
	if(m_bAutoAdjustPos == bFlag)
	{
		return;
	}

	m_bAutoAdjustPos = bFlag;
	Invalidate();
}

BOOL CMonitorWnd::GetAutoAdjustPos()
{
	return m_bAutoAdjustPos;
}

int CMonitorWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	for(int i = 0; i < MAX_CHANNELNUM; i++)
	{
		m_WndVideo[i].Create(
			NULL, 
			NULL, 
			WS_VISIBLE | WS_CHILD,
			CRect(0, 0, 0, 0),
			this,
			1979,
			NULL);

		m_WndVideo[i].SetWndID(i);
		m_WndVideo[i].SetTimer(1, 1000, NULL);
		
		AddPage(&m_WndVideo[i]);
	}

//	SetActivePage(&m_WndVideo[0], TRUE);
//	SetDrawActivePage(TRUE, RGB(248,5,182), RGB(248,5,182));
	
	return 0;
}

BOOL CMonitorWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(MONITOR_BACK_COLOR);
	pDC->FillRect(&rect, &brush);

	return TRUE;
}

void CMonitorWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	UpdateWnd();
	// Do not call CWnd::OnPaint() for painting messages
}

void CMonitorWnd::UpdateWnd()
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
			rect.DeflateRect(WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE); // 窗口之间的间隔
			pWnd->MoveWindow(&rect);
			pWnd->ShowWindow(SW_SHOW);
		}
	}
	else
	{
		for(POSITION pos = m_PageList.GetHeadPosition(); pos!=NULL;)
		{
			CWnd *pWnd = m_PageList.GetNext(pos);
			if(pWnd == m_pActivePage)
			{
				CRect rect = rectContainer;
				rect.DeflateRect(WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE);
				pWnd->MoveWindow(&rect);
				pWnd->ShowWindow(SW_SHOW);
			}
			else 
			{
				pWnd->MoveWindow(rectContainer.right+1, rectContainer.bottom+1, 1, 1);
//				pWnd->ShowWindow(SW_HIDE);
			}
		}
	}

	if(m_bDrawActive && m_PageList.GetCount() > 1)
	{
		DrawActivePage(TRUE);
	}
}

void CMonitorWnd::OnVideoLButtonDown(int nWndID, WPARAM wParam, LPARAM lParam)
{
	GET_PARENT_CONTAINER->SetActivePage(m_nMonitorID, FALSE);
	GET_PARENT_CONTAINER->OnVideoLButtonDown(m_nMonitorID, nWndID, wParam, lParam);
}

void CMonitorWnd::OnVideoLButtonUp(int nWndID, WPARAM wParam, LPARAM lParam)
{
	GET_PARENT_CONTAINER->OnVideoLButtonUp(m_nMonitorID, nWndID, wParam, lParam);
}

void CMonitorWnd::OnVideoLButtonDblClk(int nWndID, WPARAM wParam, LPARAM lParam)
{
	GET_PARENT_CONTAINER->OnVideoLButtonDblClk(m_nMonitorID, nWndID, wParam, lParam);
}

void CMonitorWnd::onVideoRButtonDown(int nWndID, WPARAM wParam, LPARAM lParam)
{
	GET_PARENT_CONTAINER->onVideoRButtonDown(m_nMonitorID, nWndID, wParam, lParam);
}

void CMonitorWnd::onVideoRButtonUp(int nWndID, WPARAM wParam, LPARAM lParam)
{
	GET_PARENT_CONTAINER->onVideoRButtonUp(m_nMonitorID, nWndID, wParam, lParam);
}

void CMonitorWnd::onVideoMove(int nWndID, WPARAM wParam, LPARAM lParam)
{
	GET_PARENT_CONTAINER->onVideoMove(m_nMonitorID, nWndID, wParam, lParam);
}

void CMonitorWnd::onVideoMoving(int nWndID, WPARAM wParam, LPARAM lParam)
{
	GET_PARENT_CONTAINER->onVideoMoving(m_nMonitorID, nWndID, wParam, lParam);
}

void CMonitorWnd::GetShowRect(LPRECT lpRect)
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

void CMonitorWnd::AdjustRect(LPRECT lpRect)
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

void CMonitorWnd::CalcPageRect(LPRECT lpRect, int nIndex, int nPageCount)
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

void CMonitorWnd::DrawActivePage(BOOL bFlag)
{
	if(!m_pActivePage || m_PageList.GetCount() < 2)
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

		pDC->Draw3dRect(&rect,m_clrTopLeft, m_clrBottomRight);	

		ReleaseDC(pDC);
	}
	else
	{
		CDC *pDC = GetDC();
		if(pDC == NULL)
		{
			return;
		}

		pDC->Draw3dRect(&rect, MONITOR_BACK_COLOR, MONITOR_BACK_COLOR);	

		ReleaseDC(pDC);
	}
}