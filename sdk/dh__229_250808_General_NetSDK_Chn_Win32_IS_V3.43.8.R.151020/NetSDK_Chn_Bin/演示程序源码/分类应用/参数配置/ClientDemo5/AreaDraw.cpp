// AreaDraw.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "AreaDraw.h"
#include "ConfigAlarmMotionArea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaDraw dialog


CAreaDraw::CAreaDraw(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaDraw::IDD, pParent),
	m_pMotionInfo(NULL),
	m_bAdd(FALSE),
	m_bDraging(FALSE),
	m_dwHalfLen(50),
	m_nAreaThreshold(0),
	m_nSensitivity(0),
	m_pCurrentRect(NULL)
{
	//{{AFX_DATA_INIT(CAreaDraw)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_rtWnd, 0, sizeof(m_rtWnd));
	memset(&m_ptStartPt, 0, sizeof(m_ptStartPt));
}


void CAreaDraw::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaDraw)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAreaDraw, CDialog)
	//{{AFX_MSG_MAP(CAreaDraw)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaDraw message handlers

void CAreaDraw::InitDlg(CFG_MOTION_INFO* pMotionInfo)
{
	m_pMotionInfo = new CFG_MOTION_INFO;
	if (m_pMotionInfo)
	{
		memcpy(m_pMotionInfo, pMotionInfo, sizeof(*m_pMotionInfo));
	}
}

void CAreaDraw::AddWnd(const CFG_MOTION_WINDOW& stuMotionWnd)
{
	if (m_bAdd)
	{
		return;
	}

	if (m_lsMotionWnd.size() > MAX_MOTION_WINDOW)
	{
		return;
	}

	if (stuMotionWnd.nThreshold >= 0
		&& stuMotionWnd.nThreshold <= 100
		&& stuMotionWnd.nSensitive >= 0
		&& stuMotionWnd.nSensitive <= 100)
	{
		m_nAreaThreshold = stuMotionWnd.nThreshold;
		m_nSensitivity = stuMotionWnd.nSensitive;
		
		m_bAdd = TRUE;
	}
}

void CAreaDraw::DeleteWnd()
{
	if (!m_pCurrentRect)
	{
		return;
	}
	
	if (m_bAdd)
	{
		AfxMessageBox(_T("Add a Rect First!"));
		return;
	}

	std::list<CFG_MOTION_WINDOW*>::iterator it = m_lsMotionWnd.begin();
	while(it != m_lsMotionWnd.end())
	{
		if (m_pCurrentRect == *it)
		{
			m_lsMotionWnd.remove(*it);
			break;
		}
		it++;
	}
}

void CAreaDraw::SetAreathreshold(int nParam)
{
	if (m_pCurrentRect)
	{
		m_pCurrentRect->nThreshold = nParam;
	}
}

void CAreaDraw::SetSensitivity(int nParam)
{
	if (m_pCurrentRect)
	{
		m_pCurrentRect->nSensitive = nParam;
	}
}

void CAreaDraw::DrawRect(HDC hDc, CFG_RECT& rt)
{
	MoveToEx(hDc, rt.nLeft / 8192. * m_rtWnd.Width(), rt.nTop / 8192. * m_rtWnd.Height(), NULL);
	LineTo(hDc, rt.nLeft / 8192. * m_rtWnd.Width(), rt.nBottom / 8192. * m_rtWnd.Height());

	MoveToEx(hDc, rt.nLeft / 8192. * m_rtWnd.Width(), rt.nBottom / 8192. * m_rtWnd.Height(), NULL);
	LineTo(hDc, rt.nRight / 8192. * m_rtWnd.Width(), rt.nBottom / 8192. * m_rtWnd.Height());

	LineTo(hDc, rt.nRight / 8192. * m_rtWnd.Width(), rt.nTop / 8192. * m_rtWnd.Height());
	LineTo(hDc, rt.nLeft / 8192. * m_rtWnd.Width(), rt.nTop / 8192. * m_rtWnd.Height());
}

CFG_MOTION_WINDOW* CAreaDraw::IsOnRect(CPoint& pt)
{
	CPoint ptTmp;
	ptTmp.x = pt.x * 8192. / m_rtWnd.Width();
	ptTmp.y = pt.y * 8192. / m_rtWnd.Height();

	std::list<CFG_MOTION_WINDOW*>::iterator it = m_lsMotionWnd.begin();
	while (it != m_lsMotionWnd.end())
	{
		CFG_MOTION_WINDOW* p = *it;

		// left 
		if (ptTmp.x >= p->stuWindow.nLeft - m_dwHalfLen && ptTmp.x <= p->stuWindow.nLeft + m_dwHalfLen)
		{
			if (ptTmp.y >= p->stuWindow.nTop - m_dwHalfLen && ptTmp.y <= p->stuWindow.nBottom + m_dwHalfLen)
			{
				return p;
			}
		}

		// top 
		if (ptTmp.x >= p->stuWindow.nLeft - m_dwHalfLen && ptTmp.x <= p->stuWindow.nRight + m_dwHalfLen)
		{
			if (ptTmp.y >= p->stuWindow.nTop - m_dwHalfLen && ptTmp.y <= p->stuWindow.nTop + m_dwHalfLen)
			{
				return p;
			}
		}

		// right 
		if (ptTmp.x >= p->stuWindow.nRight - m_dwHalfLen && ptTmp.x <= p->stuWindow.nRight + m_dwHalfLen)
		{
			if (ptTmp.y >= p->stuWindow.nTop - m_dwHalfLen && ptTmp.y <= p->stuWindow.nBottom + m_dwHalfLen)
			{
				return p;
			}
		}

		// bottom 
		if (ptTmp.x >= p->stuWindow.nLeft - m_dwHalfLen && ptTmp.x <= p->stuWindow.nRight + m_dwHalfLen)
		{
			if (ptTmp.y >= p->stuWindow.nBottom - m_dwHalfLen && ptTmp.y <= p->stuWindow.nBottom + m_dwHalfLen)
			{
				return p;
			}
		}

		it++;
	}

	return NULL;
}

BOOL CAreaDraw::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_pMotionInfo)
	{
		for (int i = 0; i < m_pMotionInfo->nWindowCount; i++)
		{
			m_lsMotionWnd.push_back(&m_pMotionInfo->stuWindows[i]);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAreaDraw::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.FillSolidRect(&m_rtWnd, RGB(200, 200, 255));

	std::list<CFG_MOTION_WINDOW*>::iterator it = m_lsMotionWnd.begin();
	while(it != m_lsMotionWnd.end())
	{
		CFG_MOTION_WINDOW* pRectInfo = *it;
		DrawRect(dc.GetSafeHdc(), pRectInfo->stuWindow);
		it++;
	}

	// Do not call CDialog::OnPaint() for painting messages
}

void CAreaDraw::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bAdd)
	{
		m_ptStartPt = point;
		m_bDraging = TRUE;
	} 
	else
	{
		m_pCurrentRect = IsOnRect(point);
		if (m_pCurrentRect)
		{
			((CConfigAlarmMotionArea*)GetParent())->ShowParam(*m_pCurrentRect);
		}
		else
		{
			CFG_MOTION_WINDOW stu = {0};
			stu.nThreshold = -1;
			stu.nSensitive = -1;
			((CConfigAlarmMotionArea*)GetParent())->ShowParam(stu);
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CAreaDraw::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDraging)
	{
		CClientDC dc(this);

		CFG_RECT rt;
		rt.nLeft = m_ptStartPt.x * 8192. / m_rtWnd.Width();
		rt.nTop = m_ptStartPt.y * 8192. / m_rtWnd.Height();
		rt.nRight = point.x * 8192. / m_rtWnd.Width();
		rt.nBottom = point.y * 8192. / m_rtWnd.Height();

		DrawRect(dc.GetSafeHdc(), rt);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CAreaDraw::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDraging)
	{
		m_bDraging = FALSE;
		m_bAdd = FALSE;

		CFG_MOTION_WINDOW* p = new CFG_MOTION_WINDOW;
		if (p)
		{
			memset(p, 0, sizeof(*p));
			p->stuWindow.nLeft = _MIN(m_ptStartPt.x * 8192. / m_rtWnd.Width(),point.x * 8192. / m_rtWnd.Width());
			p->stuWindow.nTop = _MIN(m_ptStartPt.y * 8192. / m_rtWnd.Height(),point.y * 8192. / m_rtWnd.Height());
			p->stuWindow.nRight = _MAX(m_ptStartPt.x * 8192. / m_rtWnd.Width(),point.x * 8192. / m_rtWnd.Width());
			p->stuWindow.nBottom = _MAX(m_ptStartPt.y * 8192. / m_rtWnd.Height(),point.y * 8192. / m_rtWnd.Height());
			p->nThreshold = m_nAreaThreshold;
			p->nSensitive = m_nSensitivity;
			m_lsMotionWnd.push_back(p);
			
			Invalidate(TRUE);
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CAreaDraw::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (GetSafeHwnd())
	{
		GetClientRect(&m_rtWnd);
	}
}

void CAreaDraw::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pMotionInfo)
	{
		delete m_pMotionInfo;
		m_pMotionInfo = NULL;
	}
}
