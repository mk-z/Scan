// IvsModulePreview.cpp : implementation file
//

#include "stdafx.h"
#include "demoIVSPC.h"
#include "IvsModulePreview.h"
#include "ConfigModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvsModulePreview

CIvsModulePreview::CIvsModulePreview()
	: m_pPolygonCfg(NULL)
	, m_iPtCnt(0)
	, m_fX(0.0)
	, m_fY(0.0)
	, m_bAddDetecRegion(FALSE)
{
	ZeroMemory(&m_cfgModuleInfo, sizeof(CFG_MODULE_INFO));
}

CIvsModulePreview::~CIvsModulePreview()
{
	if(m_pPolygonCfg)
	{
		delete m_pPolygonCfg;
		m_pPolygonCfg = NULL;
	}
}


BEGIN_MESSAGE_MAP(CIvsModulePreview, CWnd)
	//{{AFX_MSG_MAP(CIvsModulePreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//获取已经有的模块信息
CFG_MODULE_INFO* CIvsModulePreview::GetModuleInfo()
{
	return &m_cfgModuleInfo;
}

//设置/清空模块信息
void CIvsModulePreview::SetModuleInfo(CFG_MODULE_INFO* pModuleInfo, BOOL bClear)
{
	CGuard guard(&m_cs);
	
	if (bClear)
	{
		ZeroMemory(&m_cfgModuleInfo, sizeof(CFG_MODULE_INFO));
		return;
	}
	else
	{
		if (m_pModuleState)
		{
			memcpy(&m_cfgModuleInfo, pModuleInfo, sizeof(m_cfgModuleInfo));
		}
	}
}

//获取正在添加/已经添加完的区域
CFG_POLYGON* CIvsModulePreview::GetPolygonCfg(int& nCnt)
{
	if (!m_pPolygonCfg)
	{
		return NULL;
	}
	
	nCnt = m_iPtCnt;
	return m_pPolygonCfg;
}

//设置添加的区域
void CIvsModulePreview::SetPolygonCfg(CFG_POLYGON* pPolygonCfg, int nCnt)
{
	if (!pPolygonCfg || !nCnt)
	{
		return;
	}
	
	memcpy(m_pPolygonCfg, pPolygonCfg, sizeof(CFG_POLYGON) * nCnt);
}

void CIvsModulePreview::BeginDraw(HTREEITEM hItem, BOOL bAddDectectZone)
{
	if (!hItem)
	{
		return;
	}

	CGuard guard(&m_cs);

	m_hItemToBeDraw = hItem;

	//绘制检测区域
	m_bAddDetecRegion = bAddDectectZone;

		
}

BOOL CIvsModulePreview::IsDrawing()
{
	CGuard guard(&m_cs);
	
	if (m_bAddDetecRegion)
	{
		return TRUE;
	}

	return FALSE;
}

void CIvsModulePreview::DrawIvsModuleCfgProc(long nPort, HDC hDc, LONG dwUser)
{

	//绘制正在增加的模块区域/检测区域和绘制已经拥有的区域
	CIvsModulePreview* pDlg = (CIvsModulePreview*)dwUser;
	if (!pDlg || !IsWindow(pDlg->GetSafeHwnd()))
	{
		return;
	}
	
	CGuard guard(&pDlg->m_cs);

	CFG_MODULE_INFO* pModuleInfo = pDlg->GetModuleInfo();
	if (!pModuleInfo)
	{
		return;
	}
	
	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDc, hPen);
	
	CRect rt;
	pDlg->GetClientRect(&rt);
	
	float fFactorX = float(rt.Width() / 8192.0);
	float fFactorY = float(rt.Height() / 8192.0);
	
	//绘制检测区域
	int nPtCount = pModuleInfo->nDetectRegionPoint;
	CFG_POLYGON* pCfgPolygon = pModuleInfo->stuDetectRegion;
	
	MoveToEx(hDc, int(pCfgPolygon[0].nX * fFactorX), int(pCfgPolygon[0].nY * fFactorY), NULL);
	for (int i = 0; i < nPtCount; i++)
	{
		LineTo(hDc, int(pCfgPolygon[i].nX * fFactorX), int(pCfgPolygon[i].nY * fFactorY));
	}
	LineTo(hDc, int(pCfgPolygon[0].nX * fFactorX), int(pCfgPolygon[0].nY * fFactorY));
	

	//绘制正在添加的区域
	if (pDlg->IsDrawing())
//	if (pDlg->m_bAddDetecRegion || pDlg->m_bAddExcluRegion)
	{
		pCfgPolygon = pDlg->GetPolygonCfg(nPtCount);
		if (!pCfgPolygon || !nPtCount)
		{
			////SelectObject(hDc, hOldPen);
			//DeleteObject(hPen);
			//return;
		}

		MoveToEx(hDc, int(pCfgPolygon[0].nX * fFactorX), int(pCfgPolygon[0].nY * fFactorY), NULL);
		for (int j = 0; j <= nPtCount; j++)
		{
			LineTo(hDc, int(pCfgPolygon[j].nX * fFactorX), int(pCfgPolygon[j].nY * fFactorY));
		}
//		LineTo(hDc, pCfgPolygon[0].nX * fFactorX, pCfgPolygon[0].nY * fFactorY);
	}
	
	SelectObject(hDc, hOldPen);
	DeleteObject(hPen);
}


void CIvsModulePreview::Redraw(HTREEITEM hItem, BOOL bAddDectectZone)
{
	if (!hItem)
	{
		return;
	}
	CGuard guard(&m_cs);

	m_cfgModuleInfo.nDetectRegionPoint = 0;
	memset(m_cfgModuleInfo.stuDetectRegion, 0, sizeof(m_cfgModuleInfo.stuDetectRegion));

	SetModuleInfo(&m_cfgModuleInfo, TRUE);

	

	m_hItemToBeDraw = hItem;

	//绘制检测区域
	m_bAddDetecRegion = bAddDectectZone;
};

void CIvsModulePreview::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);

	if (m_bAddDetecRegion )
	{
		if(m_iPtCnt < MAX_POLYGON_NUM)
		{	
			m_pPolygonCfg[m_iPtCnt].nX = int(point.x / m_fX);
			m_pPolygonCfg[m_iPtCnt].nY = int(point.y / m_fY);
			m_iPtCnt++;
		}
		else
		{
			MessageBox(ConvertString(_T("The Number of the Points has been the maximum 20!Click the right mouse button to end painting")));
		}
	}

//	CWnd::OnLButtonDown(nFlags, point);
}

void CIvsModulePreview::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);

	if (m_bAddDetecRegion )
	{
		if(m_iPtCnt < MAX_POLYGON_NUM)
		{
			m_pPolygonCfg[m_iPtCnt].nX = int(point.x / m_fX);
			m_pPolygonCfg[m_iPtCnt].nY = int(point.y / m_fY);
		}
	}

//	CWnd::OnMouseMove(nFlags, point);
}

void CIvsModulePreview::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);

	MTNODE* pNode = new MTNODE;
	if (!pNode)
	{
		return;
	}

	if (m_bAddDetecRegion)
	{
		memcpy(pNode->CfgPolygon, m_pPolygonCfg, sizeof(CFG_POLYGON) * m_iPtCnt);
		pNode->nNodeType = DetectZone;

		m_bAddDetecRegion = FALSE;

		pNode->nPointCount = m_iPtCnt;
		m_iPtCnt = 0;
		ZeroMemory(m_pPolygonCfg, sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
		::SendMessage(GetParent()->GetSafeHwnd(), WM_REGIONDONE, (WPARAM)m_hItemToBeDraw, (LPARAM)pNode);
	}

	if (pNode)
	{
		delete pNode;
		pNode = NULL;
	}
//	CWnd::OnRButtonUp(nFlags, point);
}

int CIvsModulePreview::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_pPolygonCfg = new CFG_POLYGON[MAX_POLYGON_NUM];
	if (!m_pPolygonCfg)
	{
		return -1;
	}

	int nPtCnt = MAX_POLYGON_NUM >= MAX_EXCLUDEREGION_NUM ? MAX_POLYGON_NUM : MAX_EXCLUDEREGION_NUM;
	for (int i = 0; i < nPtCnt; i++)
	{
		m_pPolygonCfg[i].nX = 0;
		m_pPolygonCfg[i].nY = 0;
	}

	InitializeCriticalSection(&m_cs);

	return 0;
}

void CIvsModulePreview::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rt;
	GetClientRect(&rt);
	dc.FillSolidRect(&rt, RGB(120, 120, 120));
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CIvsModulePreview::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here

	DeleteCriticalSection(&m_cs);
}

void CIvsModulePreview::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (IsWindow(this->GetSafeHwnd()))
	{
		CRect rt;
		GetClientRect(&rt);

		m_fX = float(rt.Width() / 8192.0);
		m_fY = float(rt.Height() / 8192.0);
	}
}
