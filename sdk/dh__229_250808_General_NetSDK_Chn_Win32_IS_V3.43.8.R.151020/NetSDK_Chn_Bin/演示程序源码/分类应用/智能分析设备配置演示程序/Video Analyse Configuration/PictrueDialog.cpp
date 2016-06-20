// PictrueDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "PictrueDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictrueDialog dialog


CPictrueDialog::CPictrueDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPictrueDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPictrueDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	list<CDrawObject*> lsRoadLines;
	list<CDrawObject*> lsDetectLines;
	list<CDrawObject*> lsDetectRect;
	m_DrawObjectList.insert(std::make_pair(eRoadLine, lsRoadLines));
	m_DrawObjectList.insert(std::make_pair(eDetectLine, lsDetectLines));
	m_DrawObjectList.insert(std::make_pair(eDetectArea, lsDetectRect));
	
	m_pCurrentObj = NULL;
	m_pFirstLine = NULL;
	m_pSencondLine = NULL;
}

 CPictrueDialog::~CPictrueDialog()
 {
	 if (m_pCurrentObj != NULL)
	 {
		 delete m_pCurrentObj;
	 }

	 if(m_pFirstLine != NULL)
	 {
		 delete m_pFirstLine;
	 }

	 if (m_pSencondLine !=NULL)
	 {
		 delete m_pSencondLine;
	 }
 }
void CPictrueDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPictrueDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPictrueDialog, CDialog)
	//{{AFX_MSG_MAP(CPictrueDialog)
		// NOTE: the ClassWizard will add message map macros here
		ON_WM_LBUTTONDOWN()
		ON_WM_PAINT()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
    	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictrueDialog message handlers
BOOL CPictrueDialog::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rt;
	GetClientRect(&rt);
	CBrush br;
	br.CreateSolidBrush(PICTURE_BACK_COLOR);
	pDC->FillRect(&rt,&br);
	
	return TRUE;
	//	return CWnd::OnEraseBkgnd(pDC);
}

int CPictrueDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	::CoInitialize(NULL);
	
	return 0;
}

BOOL CPictrueDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{

	if (!ValidateObjCount())
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_MY_CROSS));
	}
	else
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}
	
	return TRUE;
}

void CPictrueDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	//DeleteRecourse();
	
	::CoUninitialize();
}

void CPictrueDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	
	HDC hdc = ::GetDC(GetSafeHwnd());
	CPictrueDialog::DecodeDrawFunc(0, hdc, (long)this);
	::ReleaseDC(GetSafeHwnd(), hdc);

}

void CALLBACK CPictrueDialog::DecodeDrawFunc(long nPort,HDC hDc,LONG nUser)
{
	CDC dc;
	dc.Attach(hDc);
	
	CPictrueDialog* pPictrueDlg = (CPictrueDialog*)nUser;
	
	pPictrueDlg->DrawBackGround(&dc);
	pPictrueDlg->DoDraw(&dc,TRUE);
	return;
}

void CPictrueDialog::DrawBackGround(CDC *pDC)
{
	if (pDC == NULL)
	{
		return;
	}

	CRect rt;
	GetClientRect(&rt);
	CBrush br;
	br.CreateSolidBrush(PICTURE_BACK_COLOR);
	pDC->FillRect(&rt,&br);
}

void CPictrueDialog::DoDraw(CDC *pDC, BOOL bToScreen)
{
	if (pDC == NULL)
	{
		return;
	}

	LISTLINE::iterator itLineList;
	MAPCROSSLINE::iterator itLines;
	if (m_mRules.size() > 0)
	{
		MAPRULES::iterator itRule = m_mRules.begin();
		while(itRule != m_mRules.end())
		{
			MAPCROSSLINE* pLines = itRule->second;
			itLines = pLines->begin();
			while (itLines != pLines->end() && pLines->size() > 0)
			{
				list<CDrawObject*> lsObjs = itLines->second;
				itLineList = lsObjs.begin();
				while(itLineList != lsObjs.end() && lsObjs.size() > 0)
				{
					CDrawObject* pObj = (*itLineList);
					pObj->DrawSelf(pDC);
					itLineList++;
				}
				itLines++;
			}// while (itLines! = mLines.end())
			itRule++;
		}// while(itRule != m_mRules.end())
	}

	if(m_DrawObjectList.size() > 0)
	{
		itLines = m_DrawObjectList.begin();
		while (itLines!=m_DrawObjectList.end())
		{
			list<CDrawObject*> lsObjs = itLines->second;
			itLineList = lsObjs.begin();
			while(itLineList != lsObjs.end() && lsObjs.size() > 0)
			{
				CDrawObject* pObj = (*itLineList);
				pObj->DrawSelf(pDC);
				itLineList++;
			}
			itLines++;
		}
	}
	
	if (m_pCurrentObj != NULL)
	{
		m_pCurrentObj->DrawSelf(pDC);
	}
	
	if(m_pFirstLine != NULL)
	{
		m_pFirstLine->DrawSelf(pDC);
	}
	
	if(m_pSencondLine != NULL)
	{
		m_pSencondLine->DrawSelf(pDC);
	}
}

void CPictrueDialog::DeleteUnfullLines()
{	
	int nType;
	if(m_DrawObjectList.size() > 0)
	{
		MAPCROSSLINE::iterator iter = m_DrawObjectList.begin();
		MAPCROSSLINE::iterator iterEnd = m_DrawObjectList.end();
		LISTLINE::iterator lsIter;
		while (iter!=iterEnd)
		{
			nType = iter->first;
			list<CDrawObject*> lsObjs = iter->second;
			lsIter = iter->second.begin();
			
			while(lsObjs.size() != 0)
			{
				if (nType == eRoadLine || nType == eDetectLine)
				{
					CDrawObject* pObj = lsObjs.front();
					CDrawLines* pObjLine = (CDrawLines*)pObj;
					lsObjs.pop_front();
					if (nType == eRoadLine && (pObjLine->m_leftRoadLine == NULL 
						|| pObjLine->m_rightRoadLine == NULL))
					{
						iter->second.erase(lsIter++);
					}
				}
				else
				{
					lsIter++;
					break;
				}
			}//while(lsObjs.size() != 0)

			iter++;
		}//while(iter!=iterEnd)
	}
}

BOOL CPictrueDialog::IsLineSegmentCross(POINT pFirst1, POINT pFirst2, POINT pSecond1, POINT pSecond2)
{
	long lLinep1;
	long lLinep2;
	lLinep1 = pFirst1.x * (pSecond1.y - pFirst2.y) +
		pFirst2.x * (pFirst1.y - pSecond1.y) +
		pSecond1.x * (pFirst2.y - pFirst1.y);
	lLinep2 = pFirst1.x * (pSecond2.y - pFirst2.y) +
		pFirst2.x * (pFirst1.y - pSecond2.y) +
		pSecond2.x * (pFirst2.y - pFirst1.y);
	if ( ((lLinep1 ^ lLinep2) >= 0 ) && !(lLinep1==0 && lLinep2==0))
	{
		return false;
	}
	lLinep1 = pSecond1.x * (pFirst1.y - pSecond2.y) +
		pSecond2.x * (pSecond1.y - pFirst1.y) +
		pFirst1.x * (pSecond2.y - pSecond1.y);
	lLinep2 = pSecond1.x * (pFirst2.y - pSecond2.y) +
		pSecond2.x * (pSecond1.y - pFirst2.y) +
		pFirst2.x * (pSecond2.y - pSecond1.y);
	if ( ((lLinep1 ^ lLinep2) >= 0 ) && !(lLinep1==0 && lLinep2==0))
	{
		return false;
	}

	return true;
}

POINT CPictrueDialog::GetCrossPoint(POINT p1, POINT p2, POINT q1, POINT q2)
{
	ASSERT(IsLineSegmentCross(p1,p2,q1,q2));
	POINT crossPoint;
	long lTempLeft;
	long lTempRight;

	lTempLeft = (q2.x - q1.x) * (p1.y - p2.y) - (p2.x - p1.x) * (q1.y - q2.y);
	lTempRight = (p1.y - q1.y) * (p2.x - p1.x) * (q2.x - q1.x) + q1.x * (q2.y - q1.y) * (p2.x - p1.x) - p1.x * (p2.y - p1.y) * (q2.x - q1.x);
    crossPoint.x =(int)( (double)lTempRight / (double)lTempLeft );

	lTempLeft = (p1.x - p2.x) * (q2.y - q1.y) - (p2.y - p1.y) * (q1.x - q2.x);
	lTempRight = p2.y * (p1.x - p2.x) * (q2.y - q1.y) + (q2.x- p2.x) * (q2.y - q1.y) * (p1.y - p2.y) - q2.y * (q1.x - q2.x) * (p2.y - p1.y);
	crossPoint.y =(int)( (double)lTempRight / (double)lTempLeft );
	return crossPoint;
}

BOOL CPictrueDialog::SetCross(CDrawLines* pCurrentLine,int emSelectScene)
{
	if (pCurrentLine == NULL)
	{
		return FALSE;
	}

	MAPCROSSLINE::iterator it = m_DrawObjectList.begin();
	while (it != m_DrawObjectList.end())
	{
		CString str;
		list<CDrawObject*> &lst = it->second;
		str.Format("SetCross sceneType:%d listSize:%d \n",it->first,lst.size());
		std::list<CDrawObject*>::iterator itLst = lst.begin();
		while (itLst != lst.end())
		{
			++itLst;
		}
#ifdef _DEBUG
		OutputDebugString(str);
#endif
		++it;
	}
	list<CDrawObject*> lsLins = m_DrawObjectList[emSelectScene];
	switch ( emSelectScene)
	{
	case eDetectLine:
		{
			CDrawLines* pDrawLine;
			while (lsLins.size() > 0)
			{
				pDrawLine = (CDrawLines*)lsLins.front();
				lsLins.pop_front();
				if(pDrawLine->m_stuLinePoints != NULL )
				{
				}
			}
			return 1;
		}
		break;
	case eRoadLine:
		{
			CDrawLines* pRoadLine;
			
			POINT p1;    
			POINT p2;   
			POINT p3;   
			POINT p4;    
			p3.x = pCurrentLine->m_stuLinePoints[0].x;
			p3.y = pCurrentLine->m_stuLinePoints[0].y;
			p4.x = pCurrentLine->m_stuLinePoints[1].x;
			p4.y = pCurrentLine->m_stuLinePoints[1].y;
			
			BOOL bCross = FALSE;
			POINT ptCrossLeft = {0};
			POINT ptCrossRight = {0};
			
			while (lsLins.size() > 0)
			{
				pRoadLine = (CDrawLines*)lsLins.front();
				lsLins.pop_front();
				if(pRoadLine->m_rightRoadLine != NULL && pRoadLine->m_leftRoadLine != NULL)
				{
					CDrawLines* pRightLine = pRoadLine->m_rightRoadLine;
					CDrawLines* pLeftLine = pRightLine->m_leftRoadLine;
					
					p1.x = pLeftLine->m_stuLinePoints[0].x;
					p1.y = pLeftLine->m_stuLinePoints[0].y;
					p2.x = pLeftLine->m_stuLinePoints[1].x;
					p2.y = pLeftLine->m_stuLinePoints[1].y;
					if (IsLineSegmentCross(p1,p2,p3,p4))
					{
						ptCrossLeft = GetCrossPoint(p1,p2,p3,p4);
					}
					else
					{
						continue;
					}
					
					p1.x = pRightLine->m_stuLinePoints[0].x;
					p1.y = pRightLine->m_stuLinePoints[0].y;
					p2.x = pRightLine->m_stuLinePoints[1].x;
					p2.y = pRightLine->m_stuLinePoints[1].y;
					if (IsLineSegmentCross(p1,p2,p3,p4))
					{
						ptCrossRight = GetCrossPoint(p1,p2,p3,p4);
						bCross = TRUE;
						break;
					}
					else
					{
						continue;
					}
					
					pRightLine->m_leftRoadLine = NULL;
					pRightLine->m_rightRoadLine = NULL;
					pLeftLine->m_leftRoadLine = NULL;
					pLeftLine->m_rightRoadLine = NULL;
				}//if
			}//while
			
			if (bCross)
			{
				pCurrentLine->m_stuLinePoints[0].x = ptCrossLeft.x;
				pCurrentLine->m_stuLinePoints[0].y = ptCrossLeft.y;
				pCurrentLine->m_stuLinePoints[1].x = ptCrossRight.x;
				pCurrentLine->m_stuLinePoints[1].y = ptCrossRight.y;
			}
			return bCross;
		}
		break;
	default:
		break;
	}

	return 0;
}

// if the rotation bigger than 45, return false 
BOOL CPictrueDialog::ValidateAngle(CRect &rt)
{
	BOOL bRet = TRUE; 
	
	double dAngle = 0;
	double dY = 0;
	double dX = 0;
	dY = (double)(rt.bottom - rt.top);
	dX = (double)(rt.right - rt.left);
	dX = abs(dX);
	dY = abs(dY);
	double dInput = dY/dX;
	
	dAngle = atan(dInput)*180.0/PI;
	if(dAngle < LIMIT_ANGLE)
	{
		bRet = FALSE;
	}
	
	return bRet;
}

BOOL CPictrueDialog::ValidateRect(CRect& rtLeft, CRect& rtRight)
{
	BOOL bProtrude=TRUE;	
	
	CVSPoint   OneFirst;
	CVSPoint   TwoFirst;
	CVSPoint   OneSecond;
	CVSPoint   TwoSecond;
	
	CPoint ptOne = rtLeft.TopLeft();
	CPoint ptTwo = rtRight.TopLeft();
	CPoint ptThree = rtLeft.BottomRight();
	CPoint ptFour = rtRight.BottomRight();
	OneFirst.m_dX = ptOne.x;
	OneFirst.m_dY = ptOne.y;
	TwoFirst.m_dX = ptThree.x;
	TwoFirst.m_dY = ptThree.y;
	OneSecond.m_dX = ptTwo.x;
	OneSecond.m_dY = ptTwo.y;
	TwoSecond.m_dX = ptFour.x;
	TwoSecond.m_dY = ptFour.y;
	
	if(LineIntersectLine(&OneFirst, &TwoFirst, &OneSecond, &TwoSecond))
		return FALSE;
	
	VTPOINT vtPoint, vtPoint_bk;
	vtPoint.push_back(&ptOne);
	vtPoint.push_back(&ptTwo);
	vtPoint.push_back(&ptThree);
	vtPoint.push_back(&ptFour);
	vtPoint_bk = vtPoint;
	
	CPoint pt[3];
	CRgn rgn;
	VTPOINT::iterator it;
	
	for(int i = 0; i < 4; i++)
	{
		vtPoint = vtPoint_bk;
		it = vtPoint.begin();
		for(int k = 0; k < i; k++)
		{
			it++;
		}
		
		CPoint* ptDel = *it;	
		vtPoint.erase(it);
		
		for(int j = 0; j < 3; j++)
		{
			pt[j] =  *(vtPoint[j]);	
		}
		
		rgn.CreatePolygonRgn(pt, 3, ALTERNATE);
		if(rgn.PtInRegion(ptDel->x, ptDel->y))
		{
			bProtrude = FALSE;	
			break;
		}
		
		rgn.DeleteObject(); 
	}
	
	return bProtrude;
}

BOOL CPictrueDialog::LineIntersectLine(CVSPoint* ptOneFirst, CVSPoint* ptTwoFirst,   
							      CVSPoint* ptOneSecond, CVSPoint* ptTwoSecond)   
{     
	return((max(ptOneFirst->m_dX,   ptTwoFirst->m_dX)       >=   min(ptOneSecond->m_dX,   ptTwoSecond->m_dX))   &&     
		(max(ptOneSecond->m_dX,   ptTwoSecond->m_dX)   >=   min(ptOneFirst->m_dX,   ptTwoFirst->m_dX))   &&     
		(max(ptOneFirst->m_dY,   ptTwoFirst->m_dY)       >=   min(ptOneSecond->m_dY,   ptTwoSecond->m_dY))   &&     
		(max(ptOneSecond->m_dY,   ptTwoSecond->m_dY)   >=   min(ptOneFirst->m_dY,   ptTwoFirst->m_dY))   &&     
		(Multiply(ptOneSecond,   ptTwoFirst,   ptOneFirst)     *   Multiply(ptTwoFirst,   ptTwoSecond,   ptOneFirst)     >=   0)   &&   
		(Multiply(ptOneFirst,   ptTwoSecond,   ptOneSecond)   *   Multiply(ptTwoSecond,   ptTwoFirst,   ptOneSecond)   >=   0));     
}     

// |P1P0|×|P2P0|     
double CPictrueDialog::Multiply(CVSPoint *sp,CVSPoint* ep,CVSPoint* op)   
{   
	return((sp->m_dX - op->m_dX) * (ep->m_dY - op->m_dY) - (ep->m_dX - op->m_dX) * (sp->m_dY - op->m_dY));   
}   

// if the selected object was reach the max number
BOOL CPictrueDialog::ValidateObjCount()
{
	int nLineCount;
	int nMaxNum;

	switch(m_emSelectScene)
	{
	case eDetectLine:
		{
			nMaxNum = m_nMaxDetectLine;
		}
		break;
	case eRoadLine:
		{
			nMaxNum = m_nMaxRoadLine;
			
		}
		break;
	case eStopLine:
		{
			nMaxNum = m_nMaxStopLine;
		}
		break;
	case ePostLine:
		{
			nMaxNum = m_nMaxPostLine;
		}
		break;
	case ePreLine:
		{
			nMaxNum = m_nMaxPreLine;
		}
		break;
	case eDetectArea:
		{
			nMaxNum = m_nMaxDetectRegion;
		}
		break;
	case eTrackRegion:
		{
			nMaxNum = m_nMaxTrackRegion;
		}
		break;
	case eStopLightRegion:
		{
			nMaxNum = m_nMaxRedRegion;
		}
		break;
	default:
		nMaxNum = 0;
		break;
	}

	nLineCount = m_DrawObjectList[m_emSelectScene].size();
	if (nLineCount >= nMaxNum)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// get rectangle of current line
CRect CPictrueDialog::GetRect(CDrawLines* pLine)
{
	int nleft = 0;
	int nright = 0;
	int nTop = 0;
	int nBottom = 0; 
	CRect crRect(0, 0, 0, 0);

	if (pLine->m_nPointNum < 1)
	{
		return crRect;
	}

	nleft = pLine->m_stuLinePoints[0].x;
	nright = nleft;
	nTop = nBottom = pLine->m_stuLinePoints[0].x;
	for(int i = 1; i < pLine->m_nPointNum; i++)
	{
		if (nleft > pLine->m_stuLinePoints[i].x)
		{
			nleft = pLine->m_stuLinePoints[i].x;
		}
		if (nright < pLine->m_stuLinePoints[i].x)
		{
			nright = pLine->m_stuLinePoints[i].x;
		}
		if (nTop > pLine->m_stuLinePoints[i].y)
		{
			nTop = pLine->m_stuLinePoints[i].y;
		}
		if (nBottom < pLine->m_stuLinePoints[i].y)
		{
			nBottom = pLine->m_stuLinePoints[i].y;
		}
	}

	crRect.bottom = nBottom + 10;
	crRect.top = nTop + 10;
	crRect.left = nleft + 10;
	crRect.right = nright + 10;
	
	return crRect;
}

// start draw line
void CPictrueDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	POINT* pPoints = NULL;

	if (m_pCurrentObj != NULL)
	{
		delete(m_pCurrentObj);
		m_pCurrentObj = NULL;
	}
	
	DeleteUnfullLines();

	switch(m_emSelectScene)
	{
	case eDetectLine:
	case eRoadLine:
	case eStopLine:
	case ePreLine:
	case ePostLine:
		{
			if(!ValidateObjCount())
			{
				pPoints = new POINT[2];
				pPoints[0].x = point.x;
				pPoints[0].y = point.y;
				pPoints[1].x = pPoints[0].x;
				pPoints[1].y = pPoints[0].y;
				m_pCurrentObj = new CDrawLines(pPoints, 2, m_emSelectScene);
				delete[] pPoints;
				pPoints = NULL;
			}
		}
		break;
	case eDetectArea:
	case eTrackRegion:
	case eStopLightRegion:
		{
			if(!ValidateObjCount())
			{
				pPoints = new POINT[4];
				pPoints[0].x = point.x;
				pPoints[0].y = point.y;
				pPoints[1].x = pPoints[0].x;
				pPoints[1].y = pPoints[0].y;
				pPoints[2].x = pPoints[0].x;
				pPoints[2].y = pPoints[0].y;
				pPoints[3].x = pPoints[0].x;
				pPoints[3].y = pPoints[0].y;
				m_pCurrentObj = new CDrawLines(pPoints, 4, m_emSelectScene);
				delete[] pPoints;
				pPoints = NULL;
			}
		}
	default:
		break;
	}

	if (pPoints != NULL)
	{
		delete[] pPoints;
		pPoints = NULL;
	}

}

// complete draw line
void CPictrueDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_pCurrentObj == NULL)
	{
		return;
	}

	// 修改当前线段对象的其它端点
	CDrawLines* pCurrentLine = (CDrawLines*)m_pCurrentObj;
	if (m_emSelectScene == eStopLightRegion || m_emSelectScene == eDetectArea || m_emSelectScene == eTrackRegion)
	{
		pCurrentLine->m_stuLinePoints[2].x = point.x;
		pCurrentLine->m_stuLinePoints[2].y = point.y;

		pCurrentLine->m_stuLinePoints[1].x = pCurrentLine->m_stuLinePoints[2].x;
		pCurrentLine->m_stuLinePoints[1].y = pCurrentLine->m_stuLinePoints[0].y;
		
		pCurrentLine->m_stuLinePoints[3].x = pCurrentLine->m_stuLinePoints[0].x;
		pCurrentLine->m_stuLinePoints[3].y = pCurrentLine->m_stuLinePoints[2].y;
	}
	else
	{
		pCurrentLine->m_stuLinePoints[1].x = point.x;
		pCurrentLine->m_stuLinePoints[1].y = point.y;
	}
	CRect crRect = GetRect((CDrawLines*)m_pCurrentObj);

	switch(m_emSelectScene)
	{
	case eDetectLine:
	case eStopLine:
	case ePreLine:
	case ePostLine:
		{
			if (SetCross(pCurrentLine,m_emSelectScene))
			{
				m_DrawObjectList[m_emSelectScene].push_back(m_pCurrentObj);
			}
			else
			{
				delete(m_pCurrentObj);
			}
			m_pCurrentObj = NULL;
			InvalidateRect(crRect, FALSE);
		}
		break;
	case eRoadLine:
		{
			if (ValidateAngle(crRect)) 
			{
				if (m_pFirstLine == NULL)
				{
					m_pFirstLine = (CDrawLines*)m_pCurrentObj;
				}
				else if (m_pFirstLine != NULL && m_pSencondLine == NULL)
				{
					m_pSencondLine = (CDrawLines*)m_pCurrentObj;
					CRect crRectF = GetRect(m_pFirstLine);
					CRect crRectS = GetRect(m_pSencondLine);
					BOOL bLegal = ValidateRect(crRectF,crRectS);
					if (bLegal)
					{
						m_pFirstLine->m_leftRoadLine = crRectF.left < crRectS.left ? m_pFirstLine : m_pSencondLine;
						m_pSencondLine->m_leftRoadLine = m_pFirstLine->m_leftRoadLine;
						m_pFirstLine->m_rightRoadLine = crRectF.left > crRectS.left ? m_pFirstLine : m_pSencondLine;
						m_pSencondLine->m_rightRoadLine = m_pFirstLine->m_rightRoadLine;

						m_DrawObjectList[eRoadLine].push_back(m_pFirstLine);
						m_DrawObjectList[eRoadLine].push_back(m_pSencondLine);
					}
					else
					{
						delete(m_pFirstLine);
						delete(m_pSencondLine);
					}
					m_pFirstLine = NULL;
					m_pSencondLine = NULL;
				}//else if (m_pFirstLine != NULL && m_pSencondLine != NULL)
			}//if (ValidateAngle(crRect))
			else
			{
				delete(m_pCurrentObj);
			}
			m_pCurrentObj = NULL;
		}
		break;
	case eStopLightRegion:
	case eTrackRegion:
	case eDetectArea:
		{
			m_DrawObjectList[m_emSelectScene].push_back(m_pCurrentObj);
			m_pCurrentObj = NULL;
			InvalidateRect(crRect, FALSE);
		}
		break;
	}

	InvalidateRect(crRect, FALSE);
}

// note the track
void CPictrueDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pCurrentObj == NULL)
	{
		return;
	}
	switch(m_emSelectScene)
	{
	case eDetectLine:
	case eRoadLine:
	case eStopLine:
	case ePreLine:
	case ePostLine:
		{
			CDrawLines* pCureentObj = (CDrawLines*) m_pCurrentObj;
			
			pCureentObj->m_stuLinePoints[1].x = point.x;
			pCureentObj->m_stuLinePoints[1].y = point.y;
			
			CRect rect = GetRect(pCureentObj);		
			rect.NormalizeRect();
			rect.InflateRect(10,10);
			InvalidateRect(rect, FALSE);
		}
		break;
	case eDetectArea:
	case eTrackRegion:
	case eStopLightRegion:
		{
			CDrawLines* pCureentObj = (CDrawLines*) m_pCurrentObj;

			pCureentObj->m_stuLinePoints[2].x = point.x;
			pCureentObj->m_stuLinePoints[2].y = point.y;

			pCureentObj->m_stuLinePoints[1].x = pCureentObj->m_stuLinePoints[2].x;
			pCureentObj->m_stuLinePoints[1].y = pCureentObj->m_stuLinePoints[0].y;

			pCureentObj->m_stuLinePoints[3].x = pCureentObj->m_stuLinePoints[0].x;
			pCureentObj->m_stuLinePoints[3].y = pCureentObj->m_stuLinePoints[2].y;

			CRect rect = GetRect(pCureentObj);
			rect.NormalizeRect();
			rect.InflateRect(10,10);
			InvalidateRect(rect, FALSE);
		}
		break;
	default:
		break;
	}
}

// delete all recourse
void CPictrueDialog::DeleteRecourse() 
{
	LISTLINE::iterator itLineList;
	MAPCROSSLINE::iterator itLines;
	if (m_mRules.size() > 0)
	{
		MAPRULES::iterator itRule = m_mRules.begin();
		while(itRule != m_mRules.end())
		{
			MAPCROSSLINE* pLines = itRule->second;
			itLines = pLines->begin();
			while (itLines != pLines->end())
			{
				list<CDrawObject*> lsObjs = itLines->second;
				itLineList = lsObjs.begin();
				while(itLineList != lsObjs.end())
				{
					CDrawObject* pObj = (*itLineList);
					delete pObj;
					lsObjs.erase(itLineList++);
				}
				pLines->erase(itLines++);
			}// while (itLines! = mLines.end())
			delete pLines;
			m_mRules.erase(itRule++);
		}// while(itRule != m_mRules.end())
	}
	m_mRules.clear();

	MAPCROSSLINE::iterator itMap = m_DrawObjectList.begin();
	while(itMap != m_DrawObjectList.end())
	{

		CString str;
		LISTLINE lsMenber = itMap->second;
		str.Format("DeleteRecourse sceneType:%d listSize:%d \n",itMap->first,lsMenber.size());
#ifdef _DEBUG
		OutputDebugString(str);
#endif

//		LISTLINE lsMenber = itMap->second;
		LISTLINE::iterator itList = lsMenber.begin();
		while (itList != lsMenber.end())
		{
			CDrawObject* pDrawObject = (*itList);
			delete pDrawObject;
			lsMenber.erase(itList++);
		}
		m_DrawObjectList.erase(itMap++);
	}
	m_DrawObjectList.clear();

	if (m_pCurrentObj != NULL)
	{
		delete(m_pCurrentObj);
		m_pCurrentObj = NULL;
	}
}

// set the max number foe all kinds object
void CPictrueDialog::SetObjsMaxNumber(int nRoadLine, int nDetectLine, int nStopLine,
									  int nPreLine, int nPostLine, int nDetectRegion,
									  int nRedLightRegion, int nTrackRegion)
{
	m_nMaxRoadLine = nRoadLine;
	m_nMaxDetectLine = nDetectLine;
	m_nMaxStopLine = nStopLine;
	m_nMaxPreLine = nPreLine;
	m_nMaxPostLine = nPostLine;
	m_nMaxDetectRegion = nDetectRegion;
	m_nMaxRedRegion = nRedLightRegion;
	m_nMaxTrackRegion = nTrackRegion;
}

// add line object
void CPictrueDialog::AddDrawLines(POINT* pLinePoints, int nPointNum, int nType)
{
	CDrawObject* cObj = new CDrawLines(pLinePoints, nPointNum, nType);
	m_DrawObjectList[nType].push_back(cObj);
}

//reload function add line object
void CPictrueDialog::AddDrawLines(POINT* pLeftPoints, int nLeftPointNum, 
								 POINT* pRightPoints, int nRightPointNum,int nType)
{
	CDrawLines* cleftObject = new CDrawLines(pLeftPoints, nLeftPointNum, nType);
	CDrawLines* crightObject = new CDrawLines(pRightPoints, nRightPointNum, nType);
	cleftObject->m_leftRoadLine = cleftObject;
	cleftObject->m_rightRoadLine = crightObject;
	crightObject->m_leftRoadLine = cleftObject;
	crightObject->m_rightRoadLine = crightObject;

	m_DrawObjectList[nType].push_back(cleftObject);
	m_DrawObjectList[nType].push_back(crightObject);
}

// add text object
void CPictrueDialog::AddDrawText(CString strText, float fValue)
{
	RECT stuRect;
	list<CDrawObject*> lsTextObject = m_DrawObjectList[eText];
    int nTextCount = lsTextObject.size();
	stuRect.left = m_Size.Width() - TEXT_WIDTH;
	stuRect.right = m_Size.Width();
	stuRect.top = TEXT_TOP_START + nTextCount * (TEXT_HEIGHT);
	stuRect.bottom = TEXT_TOP_START + (nTextCount + 1) * TEXT_HEIGHT;

	CDrawText* cTextObject = new CDrawText(strText, stuRect, fValue);
	m_DrawObjectList[eText].push_back(cTextObject);
}
// add text object(reload)
void CPictrueDialog::AddDrawText(CString strText, char fValue[][32], int nSize)
{
	RECT stuRect;
	list<CDrawObject*> lsTextObject = m_DrawObjectList[eText];
    int nTextCount = lsTextObject.size();
	stuRect.left = m_Size.Width() - TEXT_WIDTH;
	stuRect.right = m_Size.Width();
	stuRect.top = TEXT_TOP_START + nTextCount * (TEXT_HEIGHT);
	stuRect.bottom = TEXT_TOP_START + (nTextCount + 1) * TEXT_HEIGHT;
	
	CDrawText* cTextObject = new CDrawText(strText, stuRect, fValue, nSize);
	m_DrawObjectList[eText].push_back(cTextObject);
}

void CPictrueDialog::AddDrawText(CString strText, POINT TOP)
{
	RECT stuRect;
	list<CDrawObject*> lsTextObject = m_DrawObjectList[eText];
    int nTextCount = lsTextObject.size();
	stuRect.left = TOP.x;
	stuRect.right = TOP.x + TEXT_WIDTH;
	stuRect.top = TOP.y;
	stuRect.bottom = TOP.y + TEXT_HEIGHT;
	
	CDrawText* cTextObject = new CDrawText(strText, stuRect, 0);
	m_DrawObjectList[eText].push_back(cTextObject);
}

void CPictrueDialog::AddRules(CString strName, MAPCROSSLINE* pRuleLines)
{
	m_mRules[strName] = pRuleLines;
}

void CPictrueDialog::DeletRule(CString strName)
{
	MAPCROSSLINE* pRuleLines = NULL;
	pRuleLines = m_mRules[strName];
	if (pRuleLines != NULL)
	{
		MAPCROSSLINE::iterator itLines = pRuleLines->begin();
		while (itLines != pRuleLines->end())
		{
			LISTLINE lsLineList = itLines->second;
			LISTLINE::iterator itList = lsLineList.begin();
			while(itList != lsLineList.end())
			{
				CDrawObject* pDrawObject = (*itList);
				delete pDrawObject;
				lsLineList.erase(itList++);
			}

			pRuleLines->erase(itLines++);
		}
	}

	m_mRules.erase(strName);
} 