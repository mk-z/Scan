// IvsGlobalPreview.cpp : implementation file
//

#include "stdafx.h"
#include "IvsSceneDraw.h"
#include "Utility.h"
#include <MATH.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvsGlobalPreview

CIvsSceneDraw::CIvsSceneDraw()
{
	m_bStartDraw = false;
	m_bShow = false;
	m_fX = 0;
	m_fY = 0;
	memset(m_szMainDirection, 0, sizeof(m_szMainDirection));
}

CIvsSceneDraw::~CIvsSceneDraw()
{
}


BEGIN_MESSAGE_MAP(CIvsSceneDraw, CWnd)
	//{{AFX_MSG_MAP(CIvsGlobalPreview)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIvsGlobalPreview message handlers


//清除已有的区域
void CIvsSceneDraw::clearRegion()
{
	for (int i = 0; i < 2; i++)
	{
		m_szMainDirection[i].nX = -1;
		m_szMainDirection[i].nY = -1;
	}
}

//设置绘图区域
void CIvsSceneDraw::setMainDirection(CFG_POLYGON* pMainDirectioInfo, BOOL bClear)
{
	CGuard guard(&m_cs);
	
	if (bClear)
	{
		m_bShow = false;
		ZeroMemory(m_szMainDirection, sizeof(m_szMainDirection));
	}
	else
	{
		if (pMainDirectioInfo)
		{
			memcpy(m_szMainDirection, pMainDirectioInfo, sizeof(m_szMainDirection));
			m_bShow = true;
		}
	}
}


void CIvsSceneDraw::beginDraw(bool bStart)
{
	m_bStartDraw = true;
}

void CIvsSceneDraw::drawIvsSceneCfgProc(long nPort, HDC hDc, LONG dwUser)
{
	CIvsSceneDraw* pDlg = (CIvsSceneDraw*)dwUser;
	if (!pDlg)
	{
		return;
	}
	
	CGuard guard(&pDlg->m_cs);
	
	CRect rt;
	pDlg->GetClientRect(&rt);
	float fX = rt.Width() / 8192.;
	float fY = rt.Height() / 8192.;

	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDc, hPen);

	CFG_POLYGON* pMainDirection = pDlg->GetMainDirectionInfo();
	bool bShow = pDlg->IsShow();
	
	if (pMainDirection!=NULL && bShow)
	{
 		MoveToEx(hDc, pMainDirection[0].nX * fX, pMainDirection[0].nY *fY, NULL);
 		LineTo(hDc, pMainDirection[1].nX * fX, pMainDirection[1].nY *fY);

		POINT startPoint;
		startPoint.x = pMainDirection[0].nX * fX;
		startPoint.y = pMainDirection[0].nY *fY;
		POINT endPoint;
		endPoint.x = pMainDirection[1].nX * fX;
		endPoint.y = pMainDirection[1].nY *fY;
		Paint_Arrow(startPoint, endPoint, hDc);
	}

	SelectObject(hDc, hOldPen);
	DeleteObject(hPen);
}

void CIvsSceneDraw::Paint_Arrow(POINT startPoint,POINT endPoint,HDC hDc_Paint_Arrow)
{
	double dThetaArrow;
	double dOffsetX1;
	double dOffsetY1;
	BYTE ArrowLength=10;
	if ( endPoint.x<startPoint.x )
	{
		dThetaArrow=atan((double) (startPoint.y-endPoint.y)/(startPoint.x-endPoint.x));
		
		dOffsetX1=ArrowLength*cos(dThetaArrow-3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow-3.14159/6);
		
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y,NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x+dOffsetX1),(int)(endPoint.y+dOffsetY1));
		
		dOffsetX1=ArrowLength*cos(dThetaArrow+3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow+3.14159/6);
		
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x+dOffsetX1),(int)(endPoint.y+dOffsetY1));
	}
	else if ( endPoint.x>startPoint.x )
	{
		dThetaArrow=atan((double) (startPoint.y-endPoint.y)/(startPoint.x-endPoint.x));
		
		dOffsetX1=ArrowLength*cos(dThetaArrow-3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow-3.14159/6);
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x-dOffsetX1),(int)(endPoint.y-dOffsetY1));
		dOffsetX1=ArrowLength*cos(dThetaArrow+3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow+3.14159/6);
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x-dOffsetX1),(int)(endPoint.y-dOffsetY1));
	}
	else
	{
		startPoint.x++;
		dThetaArrow=atan((double) (startPoint.y-endPoint.y)/(startPoint.x-endPoint.x));
		
		dOffsetX1=ArrowLength*cos(dThetaArrow-3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow-3.14159/6);
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x+dOffsetX1),(int)(endPoint.y+dOffsetY1));
		dOffsetX1=ArrowLength*cos(dThetaArrow+3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow+3.14159/6);
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x+dOffsetX1),(int)(endPoint.y+dOffsetY1));
	}
}

int CIvsSceneDraw::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitializeCriticalSection(&m_cs);

	return 0;
}

void CIvsSceneDraw::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rt;
	GetClientRect(&rt);
	dc.FillSolidRect(&rt, RGB(100, 100, 100));
}

void CIvsSceneDraw::OnDestroy() 
{
	CWnd::OnDestroy();
	
	DeleteCriticalSection(&m_cs);
}

void CIvsSceneDraw::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);

	if (m_bStartDraw)
	{
		m_bShow = true;
		m_szMainDirection[0].nX = point.x / m_fX;
		m_szMainDirection[0].nY = point.y / m_fY;
	}
}

void CIvsSceneDraw::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);

	if (m_bStartDraw)
	{
		m_szMainDirection[1].nX = point.x / m_fX;
		m_szMainDirection[1].nY = point.y / m_fY;
	}

}

void CIvsSceneDraw::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);
	
	if (m_bStartDraw)
	{	
		m_szMainDirection[1].nX = point.x / m_fX;
		m_szMainDirection[1].nY = point.y / m_fY;
		::SendMessage(GetParent()->GetSafeHwnd(), WM_ZONEDONE, (WPARAM)m_szMainDirection, (LPARAM)2);
		m_bStartDraw = false;
	}

}

void CIvsSceneDraw::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (GetSafeHwnd())
	{
		CRect rt;
		GetClientRect(&rt);

		m_fX = rt.Width() / 8192.;
		m_fY = rt.Height() / 8192.;
	}
}
