// TargetFilterPreview.cpp : 实现文件
//

#include "stdafx.h"
#include "IVSFDemo.h"
#include "TargetFilterPreview.h"
#include "ModuleCfgdlg.h"
#include <math.h>

#define PEN_WIDTH 2
#define HALF_BOX_WIDTH 4
#define MIN_RECTANGLE_SIZE 2


// CTargetFilterPreview

IMPLEMENT_DYNAMIC(CTargetFilterPreview, CWnd)

CTargetFilterPreview::CTargetFilterPreview()
: m_bDrawboxBig(false)
, m_bClickBoxBig(false)
, m_bClickBoxSmall(false)
, m_bDrawDetectRegion(FALSE)
, m_bDrawFilter(FALSE)
, m_bDragging(FALSE)
{
	m_pAnalyseModulesInfo = NULL;
	m_nChannel = 0;
	InitializeCriticalSection(&m_cs);
	m_pointDown.x = 0;
	m_pointDown.y = 0;
	memset(&m_pointDown, 0, sizeof(m_pointDown));
}

CTargetFilterPreview::~CTargetFilterPreview()
{
	DeleteCriticalSection(&m_cs);
}


BEGIN_MESSAGE_MAP(CTargetFilterPreview, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CTargetFilterPreview 消息处理程序

void DrawRectangle(HDC& hDc, POINT pointCenter, int nWidth, int nHeight, CTargetFilterPreview* pDlg)
{
	// 左上
	POINT leftTop;
	leftTop.x = pointCenter.x - nWidth / 2;
	leftTop.y = pointCenter.y - nHeight / 2;

	// 右上
	POINT rightTop;
	rightTop.x = pointCenter.x + nWidth / 2;
	rightTop.y = pointCenter.y - nHeight / 2;

	// 左下
	POINT leftBottom;
	leftBottom.x = pointCenter.x - nWidth / 2;
	leftBottom.y = pointCenter.y + nHeight / 2;

	// 右下
	POINT rightBottom;
	rightBottom.x = pointCenter.x + nWidth / 2;
	rightBottom.y = pointCenter.y + nHeight / 2;

	// 上
	MoveToEx(hDc, leftTop.x, leftTop.y, NULL);
	LineTo(hDc, rightTop.x, leftTop.y);
	MoveToEx(hDc, leftTop.x, leftTop.y, NULL);
	LineTo(hDc, leftBottom.x, leftBottom.y);

	MoveToEx(hDc, leftBottom.x, leftBottom.y, NULL);
	LineTo(hDc, rightBottom.x, rightBottom.y);

	MoveToEx(hDc, rightTop.x, rightTop.y, NULL);
	LineTo(hDc, rightBottom.x, rightBottom.y);


	// 开始画四个角的小box
	if (pDlg->m_bDrawboxBig || pDlg->m_bClickBoxBig || pDlg->m_bClickBoxSmall)
	{
		Rectangle(hDc, leftTop.x-HALF_BOX_WIDTH, leftTop.y-HALF_BOX_WIDTH, leftTop.x+HALF_BOX_WIDTH, leftTop.y+HALF_BOX_WIDTH);
		Rectangle(hDc, rightTop.x-HALF_BOX_WIDTH, rightTop.y-HALF_BOX_WIDTH, rightTop.x+HALF_BOX_WIDTH, rightTop.y+HALF_BOX_WIDTH);
		Rectangle(hDc, leftBottom.x-HALF_BOX_WIDTH, leftBottom.y-HALF_BOX_WIDTH, leftBottom.x+HALF_BOX_WIDTH, leftBottom.y+HALF_BOX_WIDTH);
		Rectangle(hDc, rightBottom.x-HALF_BOX_WIDTH, rightBottom.y-HALF_BOX_WIDTH, rightBottom.x+HALF_BOX_WIDTH, rightBottom.y+HALF_BOX_WIDTH);
	}
}


void _stdcall CTargetFilterPreview::DrawTargetFilterCfgProc(long nPort, HDC hDc, LONG dwUser)
{

	CTargetFilterPreview* pDlg = (CTargetFilterPreview*)dwUser;
	if (!pDlg)
	{
		return;
	}

	if (pDlg->m_pAnalyseModulesInfo == NULL)
	{
		return;
	}
	if (!IsWindow(pDlg->GetSafeHwnd()))
	{
		return;
	}

	CGuard guard(&pDlg->m_cs);

	CRect rt;
	pDlg->GetClientRect(&rt);

	float fFactorX = rt.Width() / 8192.;
	float fFactorY = rt.Height() / 8192.;

	// 1
	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDc, hPen);
	POINT pointCenter;
	pointCenter.x = pDlg->m_pAnalyseModulesInfo->stuModuleInfo[pDlg->m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX * fFactorX;
	pointCenter.y = pDlg->m_pAnalyseModulesInfo->stuModuleInfo[pDlg->m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY * fFactorY;
	int nWidth = pDlg->m_pAnalyseModulesInfo->stuModuleInfo[pDlg->m_nChannel].stuFilterMaxSize.nWidth * fFactorX;
	int nHeight = pDlg->m_pAnalyseModulesInfo->stuModuleInfo[pDlg->m_nChannel].stuFilterMaxSize.nHeight * fFactorX;
	DrawRectangle(hDc, pointCenter, nWidth, nHeight, pDlg);
	SelectObject(hDc, hOldPen);
	DeleteObject(hPen);

	// 2
	HPEN hPenRed = CreatePen(PS_SOLID, PEN_WIDTH, RGB(255, 0, 0));
	hOldPen = (HPEN)SelectObject(hDc, hPenRed);
	nWidth = pDlg->m_pAnalyseModulesInfo->stuModuleInfo[pDlg->m_nChannel].stuFilterMinSize.nWidth * fFactorX;
	nHeight = pDlg->m_pAnalyseModulesInfo->stuModuleInfo[pDlg->m_nChannel].stuFilterMinSize.nHeight * fFactorY;
	DrawRectangle(hDc, pointCenter, nWidth, nHeight, pDlg);
	SelectObject(hDc, hOldPen);
	DeleteObject(hPenRed);

	// DetectRegion
	if (pDlg->m_pAnalyseModulesInfo->stuModuleInfo[pDlg->m_nChannel].nDetectRegionPoint)
	{
		int nPtNum = pDlg->m_pAnalyseModulesInfo->stuModuleInfo[pDlg->m_nChannel].nDetectRegionPoint;
		CFG_POLYGON* pRegion = pDlg->m_pAnalyseModulesInfo->stuModuleInfo[pDlg->m_nChannel].stuDetectRegion;
		if (!pRegion || !nPtNum)
		{
			return;
		}
		
		HPEN hPenRed = CreatePen(PS_SOLID, PEN_WIDTH, RGB(0, 255, 0));
		hOldPen = (HPEN)SelectObject(hDc, hPenRed);
		MoveToEx(hDc, pRegion[0].nX * fFactorX, pRegion[0].nY * fFactorY, NULL);
		for (int i = 1; i < nPtNum; i++)
		{
			LineTo(hDc, pRegion[i].nX * fFactorX, pRegion[i].nY * fFactorY);
		}
		LineTo(hDc, pRegion[0].nX * fFactorX, pRegion[0].nY * fFactorY);
		SelectObject(hDc, hOldPen);
		DeleteObject(hPenRed);
	}
};



void CTargetFilterPreview::SetModuleInfo(CFG_ANALYSEMODULES_INFO* pAnalyseModulesInfo, int nChannel)
{
	m_pAnalyseModulesInfo = pAnalyseModulesInfo;
	m_nChannel = nChannel;
};


bool CheckPointOnRectangle(POINT pointCenter, int nWidth, int nHeight, POINT pointTest)
{
	bool bState = false;
	// 左上
	POINT leftTop;
	leftTop.x = pointCenter.x - nWidth / 2;
	leftTop.y = pointCenter.y - nHeight / 2;

	// 右上
	POINT rightTop;
	rightTop.x = pointCenter.x + nWidth / 2;
	rightTop.y = pointCenter.y - nHeight / 2;

	// 左下
	POINT leftBottom;
	leftBottom.x = pointCenter.x - nWidth / 2;
	leftBottom.y = pointCenter.y + nHeight / 2;

	// 右下
	POINT rightBottom;
	rightBottom.x = pointCenter.x + nWidth / 2;
	rightBottom.y = pointCenter.y + nHeight / 2;

	// 左
	if (leftTop.x - PEN_WIDTH <= pointTest.x && pointTest.x <= leftTop.x + PEN_WIDTH)
	{
		if (leftTop.y <= pointTest.y && pointTest.y <= leftBottom.y)
		{
			return true;
		}
	}

	// 上
	if (leftTop.x <= pointTest.x && pointTest.x <= rightTop.x)
	{
		if (leftTop.y - PEN_WIDTH <= pointTest.y && pointTest.y <= leftTop.y + PEN_WIDTH)
		{
			return true;
		}
	}

	// 右
	if (rightTop.x - PEN_WIDTH <= pointTest.x && pointTest.x <= rightTop.x + PEN_WIDTH)
	{
		if (rightTop.y <= pointTest.y && pointTest.y <= rightBottom.y)
		{
			return true;
		}
	}

	// 下
	if (leftBottom.x <= pointTest.x && pointTest.x <= rightBottom.x)
	{
		if (leftBottom.y - PEN_WIDTH <= pointTest.y && pointTest.y <= leftBottom.y + PEN_WIDTH)
		{
			return true;
		}
	}


	return bState;
}

bool CheckPointOnBox(POINT pointCenter, int nWidth, int nHeight, POINT point, BYTE& byPos)
{
	bool bState = false;
	// 左上
	POINT leftTop;
	leftTop.x = pointCenter.x - nWidth / 2;
	leftTop.y = pointCenter.y - nHeight / 2;

	// 右上
	POINT rightTop;
	rightTop.x = pointCenter.x + nWidth / 2;
	rightTop.y = pointCenter.y - nHeight / 2;

	// 左下
	POINT leftBottom;
	leftBottom.x = pointCenter.x - nWidth / 2;
	leftBottom.y = pointCenter.y + nHeight / 2;

	// 右下
	POINT rightBottom;
	rightBottom.x = pointCenter.x + nWidth / 2;
	rightBottom.y = pointCenter.y + nHeight / 2;

	if (leftTop.x - HALF_BOX_WIDTH <= point.x && point.x <= leftTop.x + HALF_BOX_WIDTH)
	{
		if (leftTop.y - HALF_BOX_WIDTH <= point.y && point.y <= leftTop.y + HALF_BOX_WIDTH)
		{
			byPos = 1;
			return true;
		}
	}

	if (rightTop.x - HALF_BOX_WIDTH <= point.x && point.x <= rightTop.x + HALF_BOX_WIDTH)
	{
		if (rightTop.y - HALF_BOX_WIDTH <= point.y && point.y <= rightTop.y + HALF_BOX_WIDTH)
		{
			byPos = 2;
			return true;
		}
	}

	if (leftBottom.x - HALF_BOX_WIDTH <= point.x && point.x <= leftBottom.x + HALF_BOX_WIDTH)
	{
		if (leftBottom.y - HALF_BOX_WIDTH <= point.y && point.y <= leftBottom.y + HALF_BOX_WIDTH)
		{
			byPos = 3;
			return true;
		}
	}

	if (rightBottom.x - HALF_BOX_WIDTH <= point.x && point.x <= rightBottom.x + HALF_BOX_WIDTH)
	{
		if (rightBottom.y - HALF_BOX_WIDTH <= point.y && point.y <= rightBottom.y + HALF_BOX_WIDTH)
		{
			byPos = 4;
			return true;
		}
	}

	return bState;
};


void CTargetFilterPreview::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCapture();
	if(m_pAnalyseModulesInfo == NULL)
	{
		return;
	}
	CGuard guard(&this->m_cs);

	CRect rt;
	this->GetClientRect(&rt);

	float fFactorX = rt.Width() / 8192.;
	float fFactorY = rt.Height() / 8192.;

	POINT pointCenter;
	pointCenter.x = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX * fFactorX;
	pointCenter.y = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY * fFactorY;

	int nWidth = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth * fFactorX;
	int nHeight = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight * fFactorY;


	//////////////////////////////////////////////////////////////////////////
	//
	if (m_bDrawDetectRegion)
	{
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].nDetectRegionPoint = 4;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[0].nX = point.x / fFactorX;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[0].nY = point.y / fFactorY;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[1].nX = point.x / fFactorX;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[1].nY = point.y / fFactorY;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[2].nX = point.x / fFactorX;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[2].nY = point.y / fFactorY;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[3].nX = point.x / fFactorX;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[3].nY = point.y / fFactorY;

		m_bDragging = TRUE;
		((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
	}

	if (m_bDrawFilter)
	{
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].nCalibrateBoxNum = 1;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX = point.x / fFactorX;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY = point.y / fFactorY;
		
		ZeroMemory(&m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize, sizeof(CFG_SIZE));
		ZeroMemory(&m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize, sizeof(CFG_SIZE));

		m_bDragging = TRUE;
		((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
	}
	else
	{
		m_bClickBoxBig = CheckPointOnBox(pointCenter, nWidth, nHeight, point, m_byPosBig);
		if (m_bClickBoxBig)
		{
			m_bDrawboxBig = false;
		}
		else
		{
			m_bDrawboxBig = CheckPointOnRectangle(pointCenter, nWidth, nHeight, point);
		}
		
		
		nWidth = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth * fFactorX;
		nHeight = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight * fFactorY;
		m_bClickBoxSmall = CheckPointOnBox(pointCenter, nWidth, nHeight, point, m_byPosSmall);
		
		
		m_pointDown.x = point.x;
		m_pointDown.y = point.y;
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CTargetFilterPreview::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture();
	m_bDrawboxBig = false;
	m_bClickBoxBig = false;
	m_bClickBoxSmall = false;

	if (m_bDrawDetectRegion)
	{
		m_bDragging = FALSE;
		m_bDrawDetectRegion = FALSE;
		((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
	}

	if (m_bDrawFilter)
	{
		m_bDragging = FALSE;
		m_bDrawFilter = FALSE;
		((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void CTargetFilterPreview::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_pAnalyseModulesInfo == NULL)
	{
		return;
	}

	CGuard guard(&this->m_cs);
	CRect rt;
	this->GetClientRect(&rt);

	float fFactorX = rt.Width() / 8192.;
	float fFactorY = rt.Height() / 8192.;

	POINT pointCenter;
	pointCenter.x = this->m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX * fFactorX;
	pointCenter.y = this->m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY * fFactorY;

	int nWidth = this->m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth * fFactorX;
	int nHeight = this->m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight * fFactorY;

	//////////////////////////////////////////////////////////////////////////
	//
	if (m_bDragging)
	{
		if (m_bDrawDetectRegion)
		{
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[1].nX = point.x / fFactorX;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[2].nX = point.x / fFactorX;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[2].nY = point.y / fFactorY;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[3].nY = point.y / fFactorY;
			
			if (point.x / fFactorX > 8192)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[1].nX = 8192;
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[2].nX = 8192;
			}

			if (point.y / fFactorY > 8192)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[2].nY = 8192;
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuDetectRegion[3].nY = 8192;
			}
// 			((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
		}
		
		if (m_bDrawFilter)
		{

			const CFG_POLYGON& stuCenterPoint = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs->stuCenterPoint;
			
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth = 2 * fabs(m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs->stuCenterPoint.nX * fFactorX - (float)point.x) / fFactorX;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight = 2 * fabs(m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs->stuCenterPoint.nY * fFactorY - point.y) / fFactorY;
			
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth = 2 * (fabs(m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs->stuCenterPoint.nX - point.x / fFactorX) - 100);
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight = 2 * (fabs(m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs->stuCenterPoint.nY - point.y / fFactorY) - 100);
			
			if (m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth < 0.0)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth = 0;
			}
			if (m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight < 0.0)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight = 0;
			}

			// 对超过窗口边界的情况做修正,统一到归一化坐标里比较
			CRect rtDlg;
			GetWindowRect(&rtDlg);
			float nMaxWidth = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth;
			float nMaxHeight = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight;
			float nMinWidth = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth;
			float nMinHeight = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight;

			// 如果越过左边框,以左边框为界
			if (((float)stuCenterPoint.nX - nMaxWidth / 2) < 0.0
				|| ((float)stuCenterPoint.nX - nMinWidth / 2) < 0.0)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth = __min(stuCenterPoint.nX, 8192 - stuCenterPoint.nX) * 2;
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth = __min(stuCenterPoint.nX, 8192 - stuCenterPoint.nX) * 2;
				
				((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
				return;
			}
			// 如果越过右边框,以右边框为界
			if ((stuCenterPoint.nX + nMaxWidth / 2) > (rt.Width() / fFactorX)
				|| (stuCenterPoint.nX + nMinWidth / 2) > (rt.Width() / fFactorX))
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth = __min(stuCenterPoint.nX, 8192 - stuCenterPoint.nX) * 2;
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth = __min(stuCenterPoint.nX, 8192 - stuCenterPoint.nX) * 2;

				((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
				return;

			}
			// 如果越过上边框,以上边框为界
			if ((stuCenterPoint.nY - nMaxHeight / 2) < 0
				|| (stuCenterPoint.nY - nMinHeight / 2) < 0)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight = __min(stuCenterPoint.nY, 8192 - stuCenterPoint.nY) * 2;
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight = __min(stuCenterPoint.nY, 8192 - stuCenterPoint.nY) * 2;

				((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
				return;

			}
			// 如果越过下边框,以下边框为界
			if ((stuCenterPoint.nY + nMaxHeight / 2) > (rtDlg.Height() / fFactorY)
				|| (stuCenterPoint.nY + nMinHeight / 2) > (rtDlg.Height() / fFactorY))
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight = __min(stuCenterPoint.nY, 8192 - stuCenterPoint.nY) * 2;
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight = __min(stuCenterPoint.nY, 8192 - stuCenterPoint.nY) * 2;
			
				((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
				return;

			}


// 			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth = point.x / fFactorX;

			//((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);
		}
	}
	else
	{
		// 移动矩形框
		if (m_bDrawboxBig)
		{
			int nMoveX = (m_pointDown.x - point.x)/fFactorX;
			int nMoveY = (m_pointDown.y - point.y)/fFactorY;

			this->m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX -= nMoveX;
			this->m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY -= nMoveY;

			if(m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX < m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth/2)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth/2;
			}


			if(m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY < m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight/2)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight/2;
			}

			if ((m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX + m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth/2) * fFactorX 
			> rt.Width())
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX = rt.Width()/fFactorX
					-(m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth/2);
			}

			if ((m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY + m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight/2)* fFactorY
			> rt.Height())
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY = rt.Height()/fFactorY
					-(m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight/2);
			}
		}
		else if (m_bClickBoxBig) //  扩大 大的和小的矩形框
		{
			point.x = point.x < 0 ? 0 : point.x;
			point.x = point.x > rt.Width() ? rt.Width() : point.x;
			point.y = point.y < 0 ? 0 : point.y;
			point.y = point.y > rt.Height() ? rt.Height(): point.y;

			float nMoveX = (point.x - m_pointDown.x)/fFactorX;
			float nMoveY = (point.y - m_pointDown.y)/fFactorY;

			if (m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth <= nMoveX + PEN_WIDTH
				||m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight <= nMoveY + PEN_WIDTH)
			{
				return;
			}
			
			switch(m_byPosBig)
			{
			case  1:
				{
					nMoveX = -nMoveX;
					nMoveY = -nMoveY;
				}
				break;
			case 2:
				{
					nMoveX = nMoveX;
					nMoveY = -nMoveY;
				}
				break;
			case 3:
				{
					nMoveX = -nMoveX;
					nMoveY = nMoveY;
				}
				break;
			case 4:
				{
					nMoveX = nMoveX;
					nMoveY = nMoveY;
				}
				break;
			default:
				break;
			}
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth  += nMoveX;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight += nMoveY;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth  += nMoveX;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight += nMoveY;



			bool bRet = false;
			if (m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth <= m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth + PEN_WIDTH/fFactorX;
				bRet = true;
			}

			if (m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight<=m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight=m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight + PEN_WIDTH/fFactorY;
				bRet = true;
			}
			if (bRet)
			{
				return;
			}
			

			nMoveX = (point.x - m_pointDown.x)/fFactorX;
			nMoveY = (point.y - m_pointDown.y)/fFactorY;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nX += nMoveX/2;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuCalibrateBoxs[0].stuCenterPoint.nY += nMoveY/2;
		}
		else if (m_bClickBoxSmall)// 只扩大小的矩形框
		{
			float nMoveX = (point.x - m_pointDown.x)/fFactorX;
			float nMoveY = (point.y - m_pointDown.y)/fFactorY;

			switch(m_byPosSmall)
			{
			case  1:
				{
					nMoveX = -nMoveX;
					nMoveY = -nMoveY;
				}
				break;
			case 2:
				{
					nMoveX = nMoveX;
					nMoveY = -nMoveY;
				}
				break;
			case 3:
				{
					nMoveX = -nMoveX;
					nMoveY = nMoveY;
				}
				break;
			case 4:
				{
					nMoveX = nMoveX;
					nMoveY = nMoveY;
				}
				break;
			default:
				break;
			}



			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth += 2 * nMoveX;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight += 2 * nMoveY;

			if (m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth <= HALF_BOX_WIDTH*MIN_RECTANGLE_SIZE/fFactorX)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth = HALF_BOX_WIDTH*MIN_RECTANGLE_SIZE/fFactorX;
			}
			if (m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight <= HALF_BOX_WIDTH*MIN_RECTANGLE_SIZE/fFactorY)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight = HALF_BOX_WIDTH*MIN_RECTANGLE_SIZE/fFactorY;
			}

			if (m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth >= m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth - 4*HALF_BOX_WIDTH/fFactorX)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nWidth = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nWidth - 4*HALF_BOX_WIDTH/fFactorX;
			}
			if (m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight >= m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight-4*HALF_BOX_WIDTH/fFactorY)
			{
				m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMinSize.nHeight = m_pAnalyseModulesInfo->stuModuleInfo[m_nChannel].stuFilterMaxSize.nHeight - 4*HALF_BOX_WIDTH/fFactorY;
			}
		}

		m_pointDown.x = point.x;
		m_pointDown.y = point.y;
	}

	
	((CModuleCfgdlg*)GetParent())->SetNewPosition(m_pAnalyseModulesInfo);

	CWnd::OnMouseMove(nFlags, point);
}
