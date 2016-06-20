// IvsGlobalPreview.cpp : implementation file
//

#include "stdafx.h"

#include <math.h>

#include "demoIVSPC.h"
#include "IvsGlobalPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvsGlobalPreview

CIvsGlobalPreview::CIvsGlobalPreview()
		: m_iPtCnt(0)
		, m_pPolygonCfg(NULL)
		, m_bCloseRegion(FALSE)
		, m_bLButtonDown(false)
		, m_bDrawLine(false)
		, m_pGlobalInfo(NULL)
{
}

CIvsGlobalPreview::~CIvsGlobalPreview()
{
}


BEGIN_MESSAGE_MAP(CIvsGlobalPreview, CWnd)
	//{{AFX_MSG_MAP(CIvsGlobalPreview)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIvsGlobalPreview message handlers



//设置绘图区域
void CIvsGlobalPreview::setGlobalInfo(CFG_ANALYSEGLOBAL_INFO* pGlobalInfo, BOOL bClear)
{
	CGuard guard(&m_cs);
	m_pGlobalInfo = pGlobalInfo;
}

CFG_ANALYSEGLOBAL_INFO* CIvsGlobalPreview::getGlobalInfo()
{
	return m_pGlobalInfo;
}

void DrawArrow(HDC *pdc,POINT m_One, POINT m_Two)
{
	double slopy , cosy , siny;
	double Par = 10.0;//length of Arrow (>)
	slopy = atan2( ( m_One.y - m_Two.y )*1.0,
		( m_One.x - m_Two.x ) );
	cosy = cos( slopy );
	siny = sin( slopy );

	MoveToEx(*pdc,  m_Two.x, m_Two.y, NULL );
	LineTo(*pdc,  m_Two.x + int( Par * cosy - ( Par / 2.0 * siny ) ),
		m_Two.y + int( Par * siny + ( Par / 2.0 * cosy ) ) );
	MoveToEx(*pdc,  m_Two.x, m_Two.y, NULL );
	LineTo(*pdc,  m_Two.x + int( Par * cosy + Par / 2.0 * siny ),
		m_Two.y - int( Par / 2.0 * cosy - Par * siny ) );
	
}

void CIvsGlobalPreview::DrawIvsGlobalCfgProc(long nPort, HDC hDc, LONG dwUser)
{
	CIvsGlobalPreview* pDlg = (CIvsGlobalPreview*)dwUser;
	if (!pDlg || !IsWindow(pDlg->GetSafeHwnd()))
	{
		return;
	}
	
	CGuard guard(&pDlg->m_cs);

	CFG_ANALYSEGLOBAL_INFO* pGlobalInfo = pDlg->getGlobalInfo();
	if (!pGlobalInfo)
	{
		return;
	}

	CRect rt;
	pDlg->GetClientRect(&rt);
	float fX = float(rt.Width() / 8192.0);
	float fY = float(rt.Height() / 8192.0);

	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDc, hPen);


	POINT pointStart;
	pointStart.x = LONG(pGlobalInfo->stuLandLineStart.nX * fX);
	pointStart.y = LONG(pGlobalInfo->stuLandLineStart.nY * fY);


	POINT pointEnd;
	pointEnd.x = LONG(pGlobalInfo->stuLandLineEnd.nX * fX);
	pointEnd.y = LONG(pGlobalInfo->stuLandLineEnd.nY * fY);

	MoveToEx(hDc, pointStart.x, pointStart.y, NULL);
	LineTo(hDc, pointEnd.x, pointEnd.y);

	// 画箭头
	DrawArrow(&hDc, pointStart, pointEnd);

	SelectObject(hDc, hOldPen);
	DeleteObject(hPen);
}

int CIvsGlobalPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	/*m_pPolygonCfg = new CFG_POLYGON[MAX_POLYGON_NUM];
	if (!m_pPolygonCfg)
	{
		return -1;
	}

	for (int i = 0; i < MAX_POLYGON_NUM; i++)
	{
		m_pPolygonCfg[i].nX = 0;
		m_pPolygonCfg[i].nY = 0;
	}*/

	InitializeCriticalSection(&m_cs);

	return 0;
}

void CIvsGlobalPreview::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rt;
	GetClientRect(&rt);
	dc.FillSolidRect(&rt, RGB(100, 100, 100));
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CIvsGlobalPreview::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here

	DeleteCriticalSection(&m_cs);
}

void CIvsGlobalPreview::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	CGuard guard(&m_cs);
	if (!m_bDrawLine)
	{
		return;
	}
	
	m_bLButtonDown = true;

	CFG_ANALYSEGLOBAL_INFO* pGlobalInfo = getGlobalInfo();
	if (!pGlobalInfo)
	{
		return;
	}

	CRect rt;
	GetClientRect(&rt);
	float fX = float(rt.Width() / 8192.0);
	float fY = float(rt.Height() / 8192.0);

	pGlobalInfo->stuLandLineStart.nX = int(point.x / fX);
	pGlobalInfo->stuLandLineStart.nY = int(point.y / fY);

	pGlobalInfo->stuLandLineEnd.nX = int(point.x / fX);
	pGlobalInfo->stuLandLineEnd.nY = int(point.y / fY);


// 	CWnd::OnLButtonDown(nFlags, point);
}

void CIvsGlobalPreview::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);
	if (!m_bLButtonDown)
	{
		return;
	}
	
	CFG_ANALYSEGLOBAL_INFO* pGlobalInfo = getGlobalInfo();
	if (!pGlobalInfo)
	{
		return;
	}

	CRect rt;
	GetClientRect(&rt);
	float fX = float(rt.Width() / 8192.0);
	float fY = float(rt.Height() / 8192.0);

	pGlobalInfo->stuLandLineEnd.nX = int(point.x / fX);
	pGlobalInfo->stuLandLineEnd.nY = int(point.y / fY);

// 	CWnd::OnMouseMove(nFlags, point);
}


void CIvsGlobalPreview::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
}

void CIvsGlobalPreview::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	ReleaseCapture();
	//CGuard guard(&m_cs);
	m_bLButtonDown = false;
	m_bDrawLine = false;

	//CWnd::OnLButtonUp(nFlags, point);
}
