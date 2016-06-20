// IvsRulePreview.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "IvsRulePreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvsRulePreview

CIvsRulePreview::CIvsRulePreview():
m_bAddRegion(FALSE),
m_hItemToBeDraw(0),
m_dwRuleType(0),
m_pPolygonCfg(NULL),
m_iPtCnt(0),
m_fX(0.0),
m_fY(0.0),
m_bAddUpstairsLine(TRUE),
m_bAddDownstairsLine(FALSE),
m_bAddDirection(FALSE)
{
	ZeroMemory(&m_cfgRuleInfo, sizeof(m_cfgRuleInfo));
}

CIvsRulePreview::~CIvsRulePreview()
{
}


BEGIN_MESSAGE_MAP(CIvsRulePreview, CWnd)
	//{{AFX_MSG_MAP(CIvsRulePreview)
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
// CIvsRulePreview message handlers

void CIvsRulePreview::setRuleData(RuleStruct* pRuleStruct, BOOL bClear)
{
	if (!pRuleStruct)
	{
		return;
	}
	
	if (!pRuleStruct->pRuleBuf)
	{
		return;
	}
	
	CGuard guard(&m_cs);
	
	int iSize = g_getStructSize(pRuleStruct->RuleInfo.dwRuleType);
	if (iSize)
	{
		if (m_cfgRuleInfo.pRuleBuf)
		{
			delete m_cfgRuleInfo.pRuleBuf;
			m_cfgRuleInfo.pRuleBuf = NULL;
		}
		
		m_cfgRuleInfo.nRuleCount = 1;
		m_cfgRuleInfo.nRuleLen = sizeof(CFG_RULE_INFO) + iSize;
		m_cfgRuleInfo.pRuleBuf = new char[m_cfgRuleInfo.nRuleLen];
		if (!m_cfgRuleInfo.pRuleBuf)
		{
			AfxMessageBox(ConvertString(_T("Out of Memory")));
			return;
		}
		ZeroMemory(m_cfgRuleInfo.pRuleBuf, m_cfgRuleInfo.nRuleLen);
		
		m_dwRuleType = pRuleStruct->RuleInfo.dwRuleType;
		memcpy(m_cfgRuleInfo.pRuleBuf, &pRuleStruct->RuleInfo, sizeof(CFG_RULE_INFO));

		if (bClear)
		{
			CFG_CROSSLINE_INFO* pCrossLine = (CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf;
			char* pTmp = m_cfgRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO);
			strncpy(pTmp, pCrossLine->szRuleName, sizeof(pCrossLine->szRuleName));
			return;
		}

		memcpy(m_cfgRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO),
			pRuleStruct->pRuleBuf,
			iSize);
	}
}

void CIvsRulePreview::beginDraw(HTREEITEM hItem)
{
	if (!hItem)
	{
		return;
	}

	EnterCriticalSection(&m_cs);

	m_hItemToBeDraw = hItem;
	m_bAddRegion = TRUE;

	LeaveCriticalSection(&m_cs);

	AfxMessageBox(ConvertString(_T("Draw the rule line first")));
}

void CIvsRulePreview::drawIvsRuleCfgProc(long nPort, HDC hDc, LONG dwUser)
{
	CIvsRulePreview* pDlg = (CIvsRulePreview*)dwUser;
	if (!pDlg)
	{
		return;
	}

	int nErr = DRAW_Draw(g_nRuleCfgDrawPort, hDc, pDlg->GetSafeHwnd(), 0);

	CGuard guard(&pDlg->m_cs);

	if (pDlg->m_bAddDirection)
	{
		
		CRect rt;
		pDlg->GetClientRect(&rt);
		float fX = rt.Width() / 8192.;
		float fY = rt.Height() / 8192.;
		
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDc, hPen);

		MoveToEx(hDc, pDlg->m_pPolygonCfg[0].nX * fX, pDlg->m_pPolygonCfg[0].nY * fY, NULL);
		LineTo(hDc, pDlg->m_pPolygonCfg[1].nX * fX, pDlg->m_pPolygonCfg[1].nY * fY);

		SelectObject(hDc, hOldPen);
		DeleteObject(hPen);
	}
}

int CIvsRulePreview::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

	int nErr = 0;
	nErr = DRAW_SetPen(g_nRuleCfgDrawPort, DRAW_RULE, DRAW_PEN_SOLID, 1, RGB(0, 255, 0));
	if (0 != nErr)
	{
		return -1;
	}

	return 0;
}

void CIvsRulePreview::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rt;
	GetClientRect(&rt);
	dc.FillSolidRect(&rt, RGB(140, 140, 140));
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CIvsRulePreview::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pPolygonCfg)
	{
		delete []m_pPolygonCfg;
		m_pPolygonCfg = NULL;
	}

	if (m_cfgRuleInfo.pRuleBuf)
	{
		delete []m_cfgRuleInfo.pRuleBuf;
		m_cfgRuleInfo.pRuleBuf;
	}

	DeleteCriticalSection(&m_cs);
}

void CIvsRulePreview::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);
	
	if (m_bAddDirection)
	{
		m_pPolygonCfg[0].nX = point.x / m_fX;
		m_pPolygonCfg[0].nY = point.y / m_fY;
	}

	if (m_bAddRegion)
	{
		m_pPolygonCfg[m_iPtCnt].nX = point.x / m_fX;
		m_pPolygonCfg[m_iPtCnt].nY = point.y / m_fY;
		m_iPtCnt++;

		if (m_cfgRuleInfo.pRuleBuf)
		{
			CFG_CROSSFENCEDETECTION_INFO* pCrossFence = NULL;
			CFG_CROSSLINE_INFO* pCrossLine = NULL;
			CFG_CROSSREGION_INFO* pCrossRegion = NULL;
			CFG_MOVE_INFO* pMove = NULL;
			CFG_LEFT_INFO* pLeft = NULL;
			CFG_PARKINGDETECTION_INFO* pParking = NULL;
			CFG_PRESERVATION_INFO* pPreservation = NULL;
			CFG_RETROGRADEDETECTION_INFO* pRetro = NULL;
			CFG_STAY_INFO* pStay = NULL;
			CFG_TAKENAWAYDETECTION_INFO* pTakenAway = NULL;
			CFG_VIDEOABNORMALDETECTION_INFO* pVideoAbnormal = NULL;
			CFG_WANDER_INFO* pWander = NULL;

			char* pTmp = m_cfgRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO);

			switch (m_dwRuleType)
			{
				//1CrossFence
			case EVENT_IVS_CROSSFENCEDETECTION:
				pCrossFence = (CFG_CROSSFENCEDETECTION_INFO*)pTmp;
				pCrossFence->bRuleEnable = true;

				if (m_bAddUpstairsLine)
				{
					pCrossFence->nUpstairsLinePointNumber = m_iPtCnt;
					pCrossFence->stuUpstairsLine[m_iPtCnt - 1].nX = point.x / m_fX;
					pCrossFence->stuUpstairsLine[m_iPtCnt - 1].nY = point.y / m_fY;
				}

				if (m_bAddDownstairsLine)
				{
					pCrossFence->nDownstairsLinePointNumber = m_iPtCnt;
					pCrossFence->stuDownstairsLine[m_iPtCnt - 1].nX = point.x / m_fX;
					pCrossFence->stuDownstairsLine[m_iPtCnt - 1].nY = point.y / m_fY;
				}
				break;
				//2CrossLine
			case EVENT_IVS_CROSSLINEDETECTION:
				pCrossLine = (CFG_CROSSLINE_INFO*)pTmp;
				pCrossLine->bRuleEnable = true;
				pCrossLine->nDetectLinePoint = m_iPtCnt;
				pCrossLine->stuDetectLine[m_iPtCnt - 1].nX = point.x / m_fX;
				pCrossLine->stuDetectLine[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
				//3CrossRegion
			case EVENT_IVS_CROSSREGIONDETECTION:
				pCrossRegion = (CFG_CROSSREGION_INFO*)pTmp;
				pCrossRegion->bRuleEnable = true;
				pCrossRegion->nDetectRegionPoint = m_iPtCnt;
				pCrossRegion->stuDetectRegion[m_iPtCnt - 1].nX = point.x / m_fX;
				pCrossRegion->stuDetectRegion[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
				//4Move
			case EVENT_IVS_MOVEDETECTION:
				pMove = (CFG_MOVE_INFO*)pTmp;
				pMove->bRuleEnable = true;
				pMove->nDetectRegionPoint = m_iPtCnt;
				pMove->stuDetectRegion[m_iPtCnt - 1].nX = point.x / m_fX;
				pMove->stuDetectRegion[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
				//5Left
			case EVENT_IVS_LEFTDETECTION:
				pLeft = (CFG_LEFT_INFO*)pTmp;
				pLeft->bRuleEnable = true;
				pLeft->nDetectRegionPoint = m_iPtCnt;
				pLeft->stuDetectRegion[m_iPtCnt - 1].nX = point.x / m_fX;
				pLeft->stuDetectRegion[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
				//6Parking
			case EVENT_IVS_PARKINGDETECTION:
				pParking = (CFG_PARKINGDETECTION_INFO*)pTmp;
				pParking->bRuleEnable = true;
				pParking->nDetectRegionPoint = m_iPtCnt;
				pParking->stuDetectRegion[m_iPtCnt - 1].nX = point.x / m_fX;
				pParking->stuDetectRegion[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
				//7Preservation
			case EVENT_IVS_PRESERVATION:
				pPreservation = (CFG_PRESERVATION_INFO*)pTmp;
				pPreservation->bRuleEnable = true;
				pPreservation->nDetectRegionPoint = m_iPtCnt;
				pPreservation->stuDetectRegion[m_iPtCnt - 1].nX = point.x / m_fX;
				pPreservation->stuDetectRegion[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
				//8Retro
			case EVENT_IVS_RETROGRADEDETECTION:
				pRetro = (CFG_RETROGRADEDETECTION_INFO*)pTmp;
				pRetro->bRuleEnable = true;
				pRetro->nDetectRegionPoint = m_iPtCnt;
				pRetro->stuDetectRegion[m_iPtCnt - 1].nX = point.x / m_fX;
				pRetro->stuDetectRegion[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
				//9Stay
			case EVENT_IVS_STAYDETECTION:
				pStay = (CFG_STAY_INFO*)pTmp;
				pStay->bRuleEnable = true;
				pStay->nDetectRegionPoint = m_iPtCnt;
				pStay->stuDetectRegion[m_iPtCnt - 1].nX = point.x / m_fX;
				pStay->stuDetectRegion[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
				//10TakenAway
			case EVENT_IVS_TAKENAWAYDETECTION:
				pTakenAway = (CFG_TAKENAWAYDETECTION_INFO*)pTmp;
				pTakenAway->bRuleEnable = true;
				pTakenAway->nDetectRegionPoint = m_iPtCnt;
				pTakenAway->stuDetectRegion[m_iPtCnt - 1].nX = point.x / m_fX;
				pTakenAway->stuDetectRegion[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
				//11VideoAbnormal
			case EVENT_IVS_VIDEOABNORMALDETECTION:
				pVideoAbnormal = (CFG_VIDEOABNORMALDETECTION_INFO*)pTmp;
				pVideoAbnormal->bRuleEnable = true;
				break;
				//12Wander
			case EVENT_IVS_WANDERDETECTION:
				pWander = (CFG_WANDER_INFO*)pTmp;
				pWander->bRuleEnable = true;
				pWander->nDetectRegionPoint = m_iPtCnt;
				pWander->stuDetectRegion[m_iPtCnt - 1].nX = point.x / m_fX;
				pWander->stuDetectRegion[m_iPtCnt - 1].nY = point.y / m_fY;
				break;
			default:
				return;
				break;
			}
		}

		int nErr = DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
	}
}

void CIvsRulePreview::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);
	
	if (m_bAddDirection)
	{
		m_pPolygonCfg[1].nX = point.x / m_fX;
		m_pPolygonCfg[1].nY = point.y / m_fY;
	}

	if (m_bAddRegion)
	{
		if (m_iPtCnt >= MAX_POLYGON_NUM)
		{
			OnRButtonUp(nFlags, point);
			return;
		}

		m_pPolygonCfg[m_iPtCnt].nX = point.x / m_fX;
		m_pPolygonCfg[m_iPtCnt].nY = point.y / m_fY;
		
		if (m_cfgRuleInfo.pRuleBuf)
		{
			CFG_CROSSFENCEDETECTION_INFO* pCrossFence = NULL;
			CFG_CROSSLINE_INFO* pCrossLine = NULL;
			CFG_CROSSREGION_INFO* pCrossRegion = NULL;
			CFG_MOVE_INFO* pMove = NULL;
			CFG_LEFT_INFO* pLeft = NULL;
			CFG_PARKINGDETECTION_INFO* pParking = NULL;
			CFG_PRESERVATION_INFO* pPreservation = NULL;
			CFG_RETROGRADEDETECTION_INFO* pRetro = NULL;
			CFG_STAY_INFO* pStay = NULL;
			CFG_TAKENAWAYDETECTION_INFO* pTakenAway = NULL;
			CFG_VIDEOABNORMALDETECTION_INFO* pVideoAbnormal = NULL;
			CFG_WANDER_INFO* pWander = NULL;
			
			char* pTmp = m_cfgRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO);

			switch (m_dwRuleType)
			{
				//1CrossFence
			case EVENT_IVS_CROSSFENCEDETECTION:
				pCrossFence = (CFG_CROSSFENCEDETECTION_INFO*)pTmp;

				if (m_bAddUpstairsLine)
				{
					pCrossFence->nUpstairsLinePointNumber = m_iPtCnt + 1;
					pCrossFence->stuUpstairsLine[m_iPtCnt].nX = point.x / m_fX;
					pCrossFence->stuUpstairsLine[m_iPtCnt].nY = point.y / m_fY;
				}

				if (m_bAddDownstairsLine)
				{
					pCrossFence->nDownstairsLinePointNumber = m_iPtCnt + 1;
					pCrossFence->stuDownstairsLine[m_iPtCnt].nX = point.x / m_fX;
					pCrossFence->stuDownstairsLine[m_iPtCnt].nY = point.y / m_fY;
				}
				break;
				//2CrossLine
			case EVENT_IVS_CROSSLINEDETECTION:
				pCrossLine = (CFG_CROSSLINE_INFO*)pTmp;
				pCrossLine->nDetectLinePoint = m_iPtCnt + 1;
				pCrossLine->stuDetectLine[m_iPtCnt].nX= point.x / m_fX;
				pCrossLine->stuDetectLine[m_iPtCnt].nY = point.y / m_fY;
				break;
				//3CrossRegion
			case EVENT_IVS_CROSSREGIONDETECTION:
				pCrossRegion = (CFG_CROSSREGION_INFO*)pTmp;
				pCrossRegion->nDetectRegionPoint = m_iPtCnt + 1;
				pCrossRegion->stuDetectRegion[m_iPtCnt].nX = point.x / m_fX;
				pCrossRegion->stuDetectRegion[m_iPtCnt].nY = point.y / m_fY;
				break;
				//4Move
			case EVENT_IVS_MOVEDETECTION:
				pMove = (CFG_MOVE_INFO*)pTmp;
				pMove->nDetectRegionPoint = m_iPtCnt + 1;
				pMove->stuDetectRegion[m_iPtCnt].nX = point.x / m_fX;
				pMove->stuDetectRegion[m_iPtCnt].nY = point.y / m_fY;
				break;
				//5Left
			case EVENT_IVS_LEFTDETECTION:
				pLeft = (CFG_LEFT_INFO*)pTmp;
				pLeft->nDetectRegionPoint = m_iPtCnt + 1;
				pLeft->stuDetectRegion[m_iPtCnt].nX = point.x / m_fX;
				pLeft->stuDetectRegion[m_iPtCnt].nY = point.y / m_fY;
				break;
				//6Parking
			case EVENT_IVS_PARKINGDETECTION:
				pParking = (CFG_PARKINGDETECTION_INFO*)pTmp;
				pParking->nDetectRegionPoint = m_iPtCnt + 1;
				pParking->stuDetectRegion[m_iPtCnt].nX = point.x / m_fX;
				pParking->stuDetectRegion[m_iPtCnt].nY = point.y / m_fY;
				break;
				//7Preservation
			case EVENT_IVS_PRESERVATION:
				pPreservation = (CFG_PRESERVATION_INFO*)pTmp;
				pPreservation->nDetectRegionPoint = m_iPtCnt + 1;
				pPreservation->stuDetectRegion[m_iPtCnt].nX = point.x / m_fX;
				pPreservation->stuDetectRegion[m_iPtCnt].nY = point.y / m_fY;
				break;
				//8Retro
			case EVENT_IVS_RETROGRADEDETECTION:
				pRetro = (CFG_RETROGRADEDETECTION_INFO*)pTmp;
				pRetro->nDetectRegionPoint = m_iPtCnt + 1;
				pRetro->stuDetectRegion[m_iPtCnt].nX = point.x / m_fX;
				pRetro->stuDetectRegion[m_iPtCnt].nY = point.y / m_fY;
				break;
				//9Stay
			case EVENT_IVS_STAYDETECTION:
				pStay = (CFG_STAY_INFO*)pTmp;
				pStay->nDetectRegionPoint = m_iPtCnt + 1;
				pStay->stuDetectRegion[m_iPtCnt].nX = point.x / m_fX;
				pStay->stuDetectRegion[m_iPtCnt].nY = point.y / m_fY;
				break;
				//10TakenAway
			case EVENT_IVS_TAKENAWAYDETECTION:
				pTakenAway = (CFG_TAKENAWAYDETECTION_INFO*)pTmp;
				pTakenAway->nDetectRegionPoint = m_iPtCnt + 1;
				pTakenAway->stuDetectRegion[m_iPtCnt].nX = point.x / m_fX;
				pTakenAway->stuDetectRegion[m_iPtCnt].nY = point.y / m_fY;
				break;
				//11VideoAbnormal
			case EVENT_IVS_VIDEOABNORMALDETECTION:
				pVideoAbnormal = (CFG_VIDEOABNORMALDETECTION_INFO*)pTmp;
				break;
				//12Wander
			case EVENT_IVS_WANDERDETECTION:
				pWander = (CFG_WANDER_INFO*)pTmp;
				pWander->nDetectRegionPoint = m_iPtCnt + 1;
				pWander->stuDetectRegion[m_iPtCnt].nX = point.x / m_fX;
				pWander->stuDetectRegion[m_iPtCnt].nY = point.y / m_fY;
				break;
			default:
				break;
			}
		}
		
		DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
	}
}

void CIvsRulePreview::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGuard guard(&m_cs);
	
	if (!m_bAddRegion && !m_bAddDirection)
	{
		return;
	}

	if (m_cfgRuleInfo.pRuleBuf)
	{
		if (m_dwRuleType == EVENT_IVS_CROSSFENCEDETECTION)
		{
// 			char* pTmp = m_cfgRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO);
// 			CFG_CROSSFENCEDETECTION_INFO* pCrossFence = (CFG_CROSSFENCEDETECTION_INFO*)pTmp;
// 
// 			if (m_bAddUpstairsLine)
// 			{
// 				m_bAddUpstairsLine = FALSE;
// 				m_bAddDownstairsLine = TRUE;
// 				m_iPtCnt = 0;
// 				AfxMessageBox(ConvertString(_T("than draw downstairs line...")));
// 				return;
// 			}
// 
// 			if (m_bAddDownstairsLine)
// 			{
// 				m_bAddUpstairsLine = TRUE;
// 				m_bAddDownstairsLine = FALSE;
// 			}
		}
		else if (m_dwRuleType == EVENT_IVS_RETROGRADEDETECTION)
		{
			if (m_bAddDirection)
			{
				char* pTmp = m_cfgRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO);
				CFG_RETROGRADEDETECTION_INFO* pRetro = (CFG_RETROGRADEDETECTION_INFO*)pTmp;
				pRetro->nDirectionPoint = 2;
				memcpy(&pRetro->stuDirection[0], &m_pPolygonCfg[0], sizeof(CFG_POLYGON));
				memcpy(&pRetro->stuDirection[1], &m_pPolygonCfg[1], sizeof(CFG_POLYGON));
				
				DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);

				m_bAddDirection = FALSE;
			}
			else
			{
				AfxMessageBox(ConvertString(_T("than draw the direction...")));
				m_pPolygonCfg[0].nX = 0;
				m_pPolygonCfg[0].nY = 0;
				m_pPolygonCfg[1].nX = 0;
				m_pPolygonCfg[1].nY = 0;
				m_bAddDirection = TRUE;
			}
		}
		
		CFG_CROSSFENCEDETECTION_INFO* pCrossFence = NULL;
		CFG_CROSSLINE_INFO* pCrossLine = NULL;
		CFG_CROSSREGION_INFO* pCrossRegion = NULL;
		CFG_MOVE_INFO* pMove = NULL;
		CFG_LEFT_INFO* pLeft = NULL;
		CFG_PARKINGDETECTION_INFO* pParking = NULL;
		CFG_PRESERVATION_INFO* pPreservation = NULL;
		CFG_RETROGRADEDETECTION_INFO* pRetro = NULL;
		CFG_STAY_INFO* pStay = NULL;
		CFG_TAKENAWAYDETECTION_INFO* pTakenAway = NULL;
		CFG_VIDEOABNORMALDETECTION_INFO* pVideoAbnormal = NULL;
		CFG_WANDER_INFO* pWander = NULL;
		
		char* pTmp = m_cfgRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO);

		switch (m_dwRuleType)
		{
			//1CrossFence
		case EVENT_IVS_CROSSFENCEDETECTION:
			pCrossFence = (CFG_CROSSFENCEDETECTION_INFO*)pTmp;
			if (m_bAddUpstairsLine)
			{
				pCrossFence->nUpstairsLinePointNumber = m_iPtCnt;
				m_bAddUpstairsLine = FALSE;
				m_bAddDownstairsLine = TRUE;
				m_iPtCnt = 0;
				AfxMessageBox(ConvertString(_T("than draw downstairs line...")));
				return;
			}

			if (m_bAddDownstairsLine)
			{
				pCrossFence->nDownstairsLinePointNumber = m_iPtCnt;
				m_bAddUpstairsLine = TRUE;
				m_bAddDownstairsLine = FALSE;
			}
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//2CrossLine
		case EVENT_IVS_CROSSLINEDETECTION:
			pCrossLine = (CFG_CROSSLINE_INFO*)pTmp;
			pCrossLine->nDetectLinePoint = m_iPtCnt;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//3CrossRegion
		case EVENT_IVS_CROSSREGIONDETECTION:
			pCrossRegion = (CFG_CROSSREGION_INFO*)pTmp;
			pCrossRegion->nDetectRegionPoint = m_iPtCnt;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//4Move
		case EVENT_IVS_MOVEDETECTION:
			pMove = (CFG_MOVE_INFO*)pTmp;
			pMove->nDetectRegionPoint = m_iPtCnt;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//5Left
		case EVENT_IVS_LEFTDETECTION:
			pLeft = (CFG_LEFT_INFO*)pTmp;
			pLeft->nDetectRegionPoint = m_iPtCnt;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//6Parking
		case EVENT_IVS_PARKINGDETECTION:
			pParking = (CFG_PARKINGDETECTION_INFO*)pTmp;
			pParking->nDetectRegionPoint = m_iPtCnt;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//7Preservation
		case EVENT_IVS_PRESERVATION:
			pPreservation = (CFG_PRESERVATION_INFO*)pTmp;
			pPreservation->nDetectRegionPoint = m_iPtCnt;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//8Retro
		case EVENT_IVS_RETROGRADEDETECTION:
// 			pRetro = (CFG_RETROGRADEDETECTION_INFO*)pTmp;
// 			pRetro->nDetectRegionPoint = m_iPtCnt;
// 			if (m_bAddDirection)
// 			{
// 				char* pTmp = m_cfgRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO);
// 				CFG_RETROGRADEDETECTION_INFO* pRetro = (CFG_RETROGRADEDETECTION_INFO*)pTmp;
// 				pRetro->nDirectionPoint = 2;
// 				memcpy(&pRetro->stuDirection[0], &m_pPolygonCfg[0], sizeof(CFG_POLYGON));
// 				memcpy(&pRetro->stuDirection[1], &m_pPolygonCfg[1], sizeof(CFG_POLYGON));
// 				
// 				DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
// 				
// 				m_bAddDirection = FALSE;
// 			}
// 			else
// 			{
// 				AfxMessageBox(ConvertString(_T("than draw the direction...")));
// 				m_pPolygonCfg[0].nX = 0;
// 				m_pPolygonCfg[0].nY = 0;
// 				m_pPolygonCfg[1].nX = 0;
// 				m_pPolygonCfg[1].nY = 0;
// 				m_bAddDirection = TRUE;
// 			}
// 			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//9Stay
		case EVENT_IVS_STAYDETECTION:
			pStay = (CFG_STAY_INFO*)pTmp;
			pStay->nDetectRegionPoint = m_iPtCnt;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//10TakenAway
		case EVENT_IVS_TAKENAWAYDETECTION:
			pTakenAway = (CFG_TAKENAWAYDETECTION_INFO*)pTmp;
			pTakenAway->nDetectRegionPoint = m_iPtCnt;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//11VideoAbnormal
		case EVENT_IVS_VIDEOABNORMALDETECTION:
			pVideoAbnormal = (CFG_VIDEOABNORMALDETECTION_INFO*)pTmp;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
			//12Wander
		case EVENT_IVS_WANDERDETECTION:
			pWander = (CFG_WANDER_INFO*)pTmp;
			pWander->nDetectRegionPoint = m_iPtCnt;
			DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&m_cfgRuleInfo, 0);
			break;
		default:
			break;
		}
	}
	m_bAddRegion = FALSE;
	m_iPtCnt = 0;

	RuleStruct* pRuleStruct = new RuleStruct;
	if (!pRuleStruct)
	{
		return;
	}

	pRuleStruct->pRuleBuf = new char[m_cfgRuleInfo.nRuleLen - sizeof(CFG_RULE_INFO)];
	if (!pRuleStruct->pRuleBuf)
	{
		delete pRuleStruct;
		pRuleStruct = NULL;
		return;
	}

	memcpy(&pRuleStruct->RuleInfo, m_cfgRuleInfo.pRuleBuf, sizeof(CFG_RULE_INFO));
	pRuleStruct->RuleInfo.nRuleSize = m_cfgRuleInfo.nRuleLen - sizeof(CFG_RULE_INFO);

	char* pTmp = m_cfgRuleInfo.pRuleBuf;
	memcpy(pRuleStruct->pRuleBuf,
		   pTmp + sizeof(CFG_RULE_INFO),
		   pRuleStruct->RuleInfo.nRuleSize);

	::SendMessage(GetParent()->GetSafeHwnd(), WM_RULEDONE, (WPARAM)m_hItemToBeDraw, (LPARAM)pRuleStruct);
}

void CIvsRulePreview::OnSize(UINT nType, int cx, int cy) 
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
