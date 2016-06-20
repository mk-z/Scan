// IvsGlobalPreview.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "IvsGlobalPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvsGlobalPreview

CIvsGlobalPreview::CIvsGlobalPreview():
m_bAddRegion(FALSE),
m_iPtCnt(0),
m_pPolygonCfg(NULL),
m_bCloseRegion(FALSE),
m_bAddStaff(FALSE),
m_emStaffType(EM_STAFF_TYPE_ERR),
m_iStaffCnt(0),
m_pStaffCfg(NULL)
{
	ZeroMemory(&m_stuGlobalInfo, sizeof(CFG_ANALYSEGLOBAL_INFO));
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
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIvsGlobalPreview message handlers

//获取本类已经有的区域
CFG_POLYGON* CIvsGlobalPreview::getRegion(int& nCnt)
{
	if (!m_pPolygonCfg)
	{
		nCnt = 0;
		return NULL;
	}
	
	nCnt = m_iPtCnt;
	
	return m_pPolygonCfg;
}

//封闭区域
BOOL CIvsGlobalPreview::closeRegion()
{
	return m_bCloseRegion;
}

//清除已有的区域
void CIvsGlobalPreview::clearRegion()
{
	for (int i = 0; i < MAX_POLYGON_NUM; i++)
	{
		m_pPolygonCfg[i].nX = -1;
		m_pPolygonCfg[i].nY = -1;
	}
	m_iPtCnt = 0;
	m_bCloseRegion = FALSE;
}

//设置绘图区域
void CIvsGlobalPreview::setGlobalInfo(CFG_ANALYSEGLOBAL_INFO* pGlobalInfo, BOOL bClear)
{
	CGuard guard(&m_cs);
	
	if (bClear)
	{
		ZeroMemory(&m_stuGlobalInfo, sizeof(m_stuGlobalInfo));
	}
	else
	{
		if (pGlobalInfo)
		{
			memcpy(&m_stuGlobalInfo, pGlobalInfo, sizeof(m_stuGlobalInfo));
		}
	}
}

CFG_ANALYSEGLOBAL_INFO CIvsGlobalPreview::getGlobalInfo()
{
	CGuard guard(&m_cs);
	CFG_ANALYSEGLOBAL_INFO stuGlobalInfo = {0};
	memcpy(&stuGlobalInfo, &m_stuGlobalInfo, sizeof(CFG_ANALYSEGLOBAL_INFO));
	return stuGlobalInfo;
}

void CIvsGlobalPreview::beginDraw(HTREEITEM hItem, EM_STAFF_TYPE emStaffType)
{
	if (!hItem)
	{
		return;
	}

	CGuard guard(&m_cs);

	m_bAddRegion = TRUE;
	m_hItemToBeDraw = hItem;

	if (emStaffType)
	{
		m_emStaffType = emStaffType;
		m_bAddRegion = FALSE;
		m_bAddStaff = TRUE;
	}
}

void CIvsGlobalPreview::endDraw()
{
	CGuard guard(&m_cs);

	m_bAddRegion = FALSE;
	m_bAddStaff = FALSE;

}

BOOL CIvsGlobalPreview::isDrawing()
{
	CGuard guard(&m_cs);

	if (m_bAddRegion || m_bAddStaff)
	{
		return TRUE;
	}

	return FALSE;
}

void CIvsGlobalPreview::drawIvsGlobalCfgProc(long nPort, HDC hDc, LONG dwUser)
{
	CIvsGlobalPreview* pDlg = (CIvsGlobalPreview*)dwUser;
	if (!pDlg)
	{
		return;
	}
	
	CGuard guard(&pDlg->m_cs);

	CFG_ANALYSEGLOBAL_INFO stuGlobalInfo = pDlg->getGlobalInfo();
	CFG_ANALYSEGLOBAL_INFO* pGlobalInfo = &stuGlobalInfo;
	if (!pGlobalInfo)
	{
		return;
	}

	CRect rt;
	pDlg->GetClientRect(&rt);
	float fX = rt.Width() / 8192.;
	float fY = rt.Height() / 8192.;

	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDc, hPen);

	int nPtCnt = 0;
	CFG_POLYGON* pCfgPolygon = NULL;

	//绘制标定区域和对应的标尺
	for (int i = 0; i < pGlobalInfo->nCalibrateAreaNum; i++)
	{
		//标定区域
		nPtCnt = pGlobalInfo->stuCalibrateArea[i].stuArea.nPointNum;
		pCfgPolygon = pGlobalInfo->stuCalibrateArea[i].stuArea.stuPolygon;

		int j = 0;
		MoveToEx(hDc, pCfgPolygon[0].nX * fX, pCfgPolygon[0].nY * fY, NULL);
		for (j = 0; j < nPtCnt; j++)
		{
			LineTo(hDc, pCfgPolygon[j].nX * fX, pCfgPolygon[j].nY * fY);
		}
		LineTo(hDc, pCfgPolygon[0].nX * fX, pCfgPolygon[0].nY * fY);

		//标尺
		for(j = 0; j < pGlobalInfo->stuCalibrateArea[i].nStaffNum; j++)
		{
			MoveToEx(hDc, 
					 pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nX * fX,
					 pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nY * fY,
					 NULL);
			LineTo(hDc,
				   pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nX * fX,
				   pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nY * fY);

			if (pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].emType == EM_STAFF_TYPE_HORIZONTAL)
			{
				MoveToEx(hDc,
						 pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nX * fX,
						 pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nY * fY - 3,
						 NULL);
				LineTo(hDc,
					   pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nX * fX,
					   (pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nY * fY + 3));
				
				MoveToEx(hDc,
						pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nX * fX,
						(pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nY * fY - 3),
					NULL);
				LineTo(hDc,
					   pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nX * fX,
					   (pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nY * fY + 3));
			}

			if (pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].emType == EM_STAFF_TYPE_VERTICAL)
			{
				MoveToEx(hDc,
					(pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nX * fX - 3),
					pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nY * fY,
					NULL);
				LineTo(hDc,
					(pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nX * fX + 3),
					pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuStartLocation.nY * fY);
								
				MoveToEx(hDc,
					(pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nX * fX - 3),
					pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nY * fY,
					NULL);
				LineTo(hDc,
					(pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nX * fX + 3),
					   pGlobalInfo->stuCalibrateArea[i].stuStaffs[j].stuEndLocation.nY * fY);
			}
		}
	}

	if (pDlg->m_bAddRegion)
	{
		pCfgPolygon = pDlg->getRegion(nPtCnt);
		if (pCfgPolygon && nPtCnt)
		{
			int i = 0;
			MoveToEx(hDc, pCfgPolygon[0].nX * fX, pCfgPolygon[0].nY * fY, NULL);
			for (i = 0; i <= nPtCnt; i++)
			{
				LineTo(hDc, pCfgPolygon[i].nX * fX, pCfgPolygon[i].nY * fY);
			}
		}
	}

	if (pDlg->m_bAddStaff)
	{
		pCfgPolygon = pDlg->getRegion(nPtCnt);
		if (pCfgPolygon && nPtCnt)
		{
			if (pDlg->m_emStaffType == EM_STAFF_TYPE_HORIZONTAL)
			{
				MoveToEx(hDc, pCfgPolygon[0].nX * fX, pCfgPolygon[0].nY * fY, NULL);
				LineTo(hDc, pCfgPolygon[1].nX * fX, pCfgPolygon[1].nY * fY);

				MoveToEx(hDc, pCfgPolygon[0].nX * fX, pCfgPolygon[0].nY * fY - 3, NULL);
				LineTo(hDc, pCfgPolygon[0].nX * fX, pCfgPolygon[0].nY * fY + 3);
				MoveToEx(hDc, pCfgPolygon[1].nX * fX, pCfgPolygon[1].nY * fY - 3, NULL);
				LineTo(hDc, pCfgPolygon[1].nX * fX, pCfgPolygon[1].nY * fY + 3);
			}
			
			if (pDlg->m_emStaffType == EM_STAFF_TYPE_VERTICAL)
			{
				MoveToEx(hDc, pCfgPolygon[0].nX * fX, pCfgPolygon[0].nY * fY, NULL);
				LineTo(hDc, pCfgPolygon[1].nX * fX, pCfgPolygon[1].nY * fY);

				MoveToEx(hDc, pCfgPolygon[0].nX * fX - 3, pCfgPolygon[0].nY * fY, NULL);
				LineTo(hDc, pCfgPolygon[0].nX * fX + 3, pCfgPolygon[0].nY * fY);
				MoveToEx(hDc, pCfgPolygon[1].nX * fX - 3, pCfgPolygon[1].nY * fY, NULL);
				LineTo(hDc, pCfgPolygon[1].nX * fX + 3, pCfgPolygon[1].nY * fY);
			}
		}
	}

	SelectObject(hDc, hOldPen);
	DeleteObject(hPen);
}

int CIvsGlobalPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_pPolygonCfg = new CFG_POLYGON[MAX_POLYGON_NUM];
	if (!m_pPolygonCfg)
	{
		return -1;
	}

	for (int i = 0; i < MAX_POLYGON_NUM; i++)
	{
		m_pPolygonCfg[i].nX = 0;
		m_pPolygonCfg[i].nY = 0;
	}

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
	if (m_pPolygonCfg)
	{
		delete []m_pPolygonCfg;
		m_pPolygonCfg = NULL;
	}

	DeleteCriticalSection(&m_cs);
}

void CIvsGlobalPreview::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);

	if (m_bAddRegion && m_bAddStaff)
	{
		return;
	}	

	if (m_bAddRegion)
	{
		if(m_iPtCnt < MAX_POLYGON_NUM)
		{
			m_pPolygonCfg[m_iPtCnt].nX = point.x / m_fX;
			m_pPolygonCfg[m_iPtCnt].nY = point.y / m_fY;
			m_iPtCnt++;
			return;
		}
		else
		{
			MessageBox(ConvertString(_T("The Number of the Points has been the maximum 20!Click the right mouse button to end painting")));
		}
	}

	if (m_bAddStaff)
	{
		m_pPolygonCfg[0].nX = point.x / m_fX;
		m_pPolygonCfg[0].nY = point.y / m_fY;
		m_iPtCnt++;
		return;
	}
}

void CIvsGlobalPreview::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);
	
	if (m_bAddRegion && m_bAddStaff)
	{
		return;
	}
	

	if (m_bAddRegion)
	{
		if(m_iPtCnt < MAX_POLYGON_NUM)
		{
			m_pPolygonCfg[m_iPtCnt].nX = point.x / m_fX;
			m_pPolygonCfg[m_iPtCnt].nY = point.y / m_fY;
			return;
		}
	}
	
	if (m_bAddStaff)
	{
		if (!m_iPtCnt)
		{
			return;
		}

		if (m_emStaffType == nStaffHor)
		{
			m_pPolygonCfg[1].nX = point.x / m_fX;
			m_pPolygonCfg[1].nY = m_pPolygonCfg[0].nY;
		}

		if (m_emStaffType == nStaffVer)
		{
			m_pPolygonCfg[1].nX = m_pPolygonCfg[0].nX;
			m_pPolygonCfg[1].nY = point.y / m_fY;
		}
	}
}

void CIvsGlobalPreview::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);

	if (m_bAddRegion)
	{
		GTNODEAREA* pNodeArea = new GTNODEAREA;
		if (!pNodeArea)
		{
			return;
		}
		ZeroMemory(pNodeArea, sizeof(GTNODEAREA));
		pNodeArea->nNodeType = nNodeArea;
		pNodeArea->CfgCalibrateAreaInfo.stuArea.nPointNum = m_iPtCnt;
		memcpy(pNodeArea->CfgCalibrateAreaInfo.stuArea.stuPolygon, 
			   m_pPolygonCfg, 
			   sizeof(CFG_POLYGON) * m_iPtCnt);

		m_bAddRegion = FALSE;
		m_iPtCnt = 0;

		::SendMessage(GetParent()->GetSafeHwnd(), WM_ZONEDONE, (WPARAM)m_hItemToBeDraw, (LPARAM)pNodeArea);
	}

	if (m_bAddStaff)
	{
		GTNODESTAFF* pNodeStaff = new GTNODESTAFF;
		if (!pNodeStaff)
		{
			return;
		}
		ZeroMemory(pNodeStaff, sizeof(GTNODESTAFF));
		pNodeStaff->nNodeType = m_emStaffType;
		pNodeStaff->CfgStaff.emType = m_emStaffType;
		pNodeStaff->CfgStaff.stuStartLocation.nX = m_pPolygonCfg[0].nX;
		pNodeStaff->CfgStaff.stuStartLocation.nY = m_pPolygonCfg[0].nY;
		pNodeStaff->CfgStaff.stuEndLocation.nX = m_pPolygonCfg[1].nX;
		pNodeStaff->CfgStaff.stuEndLocation.nY = m_pPolygonCfg[1].nY;

		m_bAddStaff = FALSE;
		m_iPtCnt = 0;

		::SendMessage(GetParent()->GetSafeHwnd(), WM_ZONEDONE, (WPARAM)m_hItemToBeDraw, (LPARAM)pNodeStaff);
	}
}

void CIvsGlobalPreview::OnSize(UINT nType, int cx, int cy) 
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
