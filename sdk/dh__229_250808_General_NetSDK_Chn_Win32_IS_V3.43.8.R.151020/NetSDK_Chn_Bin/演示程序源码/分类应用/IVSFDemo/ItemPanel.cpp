// ItemPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "ItemPanel.h"   
#include "IVSFDemo.h"

#define TIMEREVENTINSERTCHECK 1
#define TIMEREVENTINSERTING 2
#define INSERTCHECKSPEED 100
#define INSERTSPEED 1

#define pi 3.1415926

IMPLEMENT_DYNAMIC(CItemPanel, CWnd)

BEGIN_MESSAGE_MAP(CItemPanel, CWnd)
	ON_WM_MOUSEWHEEL()
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemPanel construction

CItemPanel::CItemPanel()
{
	m_nScrollWheelLines = 10;	
	m_pItems			= new Item*[MAX_ITEM_NUM];
	memset(m_pItems, 0, sizeof(Item*) * MAX_ITEM_NUM);
	m_nItems			= 0;
	m_nIncreaseSection	= 0;
	m_nBuffer			= 0;
	m_nCountPerPage = PANELHIGHT / UNIT_HEIGHT;
	if (PANELHIGHT % UNIT_HEIGHT)
	{
		m_nCountPerPage+=1;
	}
	m_nScrollClipHight = 0;
	m_nScrollCountPerPage = PANELHIGHT / SCROLL_UNIT;
	m_nTopIndex		= 0;
	m_nHitIndex		= 0;
	m_nBottomIndex	= 0xFFFFFFFF;
	m_nFocus		= 0xFFFFFFFF;  
	m_nInserting	= FALSE;
	VERIFY(m_font.CreateFont(
		14,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial")));			   // lpszFacename
}

void CItemPanel::InitialItems()
{
	for (int i=0;i<(m_nCountPerPage+1);i++)
	{
		CMatchItem *pItem = new CMatchItem();
		if(pItem->Create(this,CRect(0,0,0,0)))
		{
			pItem->ShowWindow(SW_SHOW);
		}
			m_ItemUIList[i]=pItem;
		}
	}

/////////////////////////////////////////////////////////////////////////////
// CItemPanel operations

BOOL CItemPanel::Create(CWnd* pParentWnd)
{
	BOOL bResult;
	CRect rect(0, 0, 0, 0);
	bResult = CWnd::CreateEx(WS_EX_CONTROLPARENT, NULL, _T("CItemPanel"), WS_CHILD | WS_TABSTOP |
		WS_VSCROLL | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, rect, pParentWnd, 0, NULL);
	InitialItems();
//	SetTimer(TIMEREVENTINSERTCHECK, INSERTCHECKSPEED, NULL );
	return bResult;
}

BOOL CItemPanel::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if ((m_nItems * UNIT_HEIGHT/SCROLL_UNIT)<m_nScrollCountPerPage)
	{
		return TRUE;
	} 
	// zDelta parameter is a multiple of WHEEL_DELTA 
	ScrollByVertical(zDelta / WHEEL_DELTA * m_nScrollWheelLines);

	return TRUE; 
}

void CItemPanel::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* /*pScrollBar*/) 
{ 
	switch (nSBCode)
	{
	case SB_BOTTOM:
		ScrollToVertical(m_nItems * UNIT_HEIGHT / SCROLL_UNIT - 1);
		break;
	case SB_LINEDOWN:
		ScrollByVertical(1);
		break;
	case SB_LINEUP:
		ScrollByVertical(-1);
		break;
	case SB_PAGEDOWN:
		ScrollByVertical(m_nCountPerPage);
		break;
	case SB_PAGEUP:
		ScrollByVertical(-m_nCountPerPage);
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_TRACKPOS;
		GetScrollInfo(SB_VERT,&si,SIF_TRACKPOS);
		ScrollToVertical(si.nTrackPos);
		break;
	case SB_TOP:
		ScrollToVertical(0);
		break;
	} 
}

void CItemPanel::UpdateVScroll(DWORD nScroll)
{
	SCROLLINFO pSclInfo;

	pSclInfo.cbSize = sizeof(pSclInfo);
	pSclInfo.fMask  = SIF_ALL & ~SIF_TRACKPOS;
	pSclInfo.nMin   = 0;
	pSclInfo.nMax   = (m_nItems * UNIT_HEIGHT / SCROLL_UNIT - 1);
	pSclInfo.nPage  = (m_nScrollCountPerPage);
	pSclInfo.nPos   = nScroll < 0xFFFFFFFF ? nScroll : GetScrollPos(SB_VERT);
	pSclInfo.nPos   = max(0, min(pSclInfo.nPos, pSclInfo.nMax - (int)pSclInfo.nPage + 1));
	SetScrollInfo(SB_VERT, &pSclInfo, TRUE);
}

void CItemPanel::ScrollByVertical(int nDelta)
{
	int nIndex = GetScrollPos(SB_VERT) + nDelta;
	nIndex = max(0, nIndex);
	nIndex = min(nIndex,m_nItems * UNIT_HEIGHT / SCROLL_UNIT - m_nScrollCountPerPage);
	ScrollVToPosition(nIndex); 
}
void CItemPanel::ScrollToVertical(DWORD nIndex)
{
	ScrollVToPosition(nIndex);
	return;
}

void CItemPanel::ScrollVToPosition(DWORD nIndex)
{ 
	int nTemp = GetScrollPos(SB_VERT);
	if (nTemp == nIndex)
	{
		return;
	}

	DWORD nTempIndex = nIndex;
	nIndex = nIndex * SCROLL_UNIT / UNIT_HEIGHT;

	m_nScrollClipHight = UNIT_HEIGHT - nTempIndex * SCROLL_UNIT % UNIT_HEIGHT;

	DWORD nScroll = 0;
	DWORD nLimit = m_nItems * UNIT_HEIGHT / SCROLL_UNIT;

	if (nLimit > (DWORD)m_nScrollCountPerPage) 
		nLimit -= m_nScrollCountPerPage;
	else 
		nLimit = 0;
	nIndex = min(nIndex, nLimit);

	m_nTopIndex = 0;
	m_nHitIndex = 0;
	m_nBottomIndex = 0xFFFFFFFF;

 	Item** ppItem = m_pItems;

	for (DWORD nItems = 0 ; nItems < m_nItems ; nItems++, ppItem++)
	{
		m_nTopIndex = nItems;

		if (nIndex < 1)
		{
			m_nHitIndex = nIndex;
			nScroll += nIndex;
			break;
		}

		nIndex -= 1;
		nScroll += 1;
	}

	if (m_nTopIndex == (m_nItems - PANELHIGHT/UNIT_HEIGHT))
	{
		m_nScrollClipHight = 0;		
	}
 
	UpdateVScroll(nTempIndex);

	CRect rc;
	GetClientRect(&rc);
	RedrawWindow(&rc, NULL, RDW_INVALIDATE);
}

void CItemPanel::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	Update();
	UpdateWindow(); 
	UpdateVScroll(0xFFFFFFFF);
}

void CItemPanel::Update()
{ 
	CRect rc;
	Invalidate();
}

void CItemPanel::OnPaint()
{	
	CRect rcClient, rcItem;
	CPaintDC dcx(this);
	GetClientRect(&rcClient);  

	CDC memDC;
	CBitmap memBitmap;
	memDC.CreateCompatibleDC(NULL);
	memBitmap.CreateCompatibleBitmap(&dcx,rcClient.Width(),rcClient.Height());

	CBitmap *pOldBit = memDC.SelectObject(&memBitmap);
	memDC.FillSolidRect(0, 0, rcClient.Width(), rcClient.Height(),PANELBACKGROUND);


	rcItem.SetRect(rcClient.left, rcClient.top, rcClient.right, 0);
	rcItem.top -= m_nHitIndex * UNIT_HEIGHT;
	rcItem.bottom = rcItem.top + UNIT_HEIGHT;

	int nIndex = m_nItems - m_nTopIndex-1;

	Item** ppItem = NULL;
	if (m_nScrollClipHight && m_nTopIndex!=0)
		ppItem = m_pItems + nIndex+1;
	else
		ppItem = m_pItems + nIndex;

	BOOL bFocus = (GetFocus() == this);

	if (m_nScrollClipHight && m_nScrollClipHight !=UNIT_HEIGHT && m_nTopIndex!=m_nItems-1 && m_nItems )
	{
		Item* pItem = *ppItem;
		CMatchItem *pUIItem = m_ItemUIList[m_nCountPerPage];
        memcpy(pUIItem->m_pItem, pItem, sizeof(Item));
		pUIItem->ShowWindow(TRUE);
		pUIItem->MoveWindow(0, m_nScrollClipHight-UNIT_HEIGHT, rcItem.Width(),UNIT_HEIGHT,FALSE);
		pUIItem->TestPtInWnd();
		pUIItem->Invalidate(FALSE);
		rcItem.top += m_nScrollClipHight;
		ppItem--;
		nIndex--;
	}  

	for (int i = 0;nIndex >= 0 && rcItem.top < rcClient.bottom ;nIndex--, ppItem--)
	{ 
		Item* pItem = *ppItem;

		if (rcItem.top >= rcClient.top/* && dc.RectVisible(&rcItem)*/)
		{	 
			CMatchItem *pUIItem = m_ItemUIList[i];
			memcpy(pUIItem->m_pItem, pItem, sizeof(Item));
			pUIItem->ShowWindow(TRUE);
			pUIItem->MoveWindow(0, rcItem.top, rcItem.Width(),UNIT_HEIGHT,FALSE);
			pUIItem->TestPtInWnd();
			pUIItem->Invalidate(FALSE);
			i++;		 
		}

		rcItem.top += UNIT_HEIGHT;
	} 

	m_nBottomIndex = nIndex + 1;

	if (m_nItems == 0)
	{
		memDC.SetViewportOrg(0, 0);
		GetClientRect(&rcClient);
		DrawEmptyNotification(memDC,rcClient);
	}

	rcItem.bottom = rcClient.bottom;

	if (memDC.RectVisible(&rcItem))
	{
		memDC.FillSolidRect(&rcItem,PANELBACKGROUND);
	}

	dcx.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&memDC,0,0,SRCCOPY);
	memBitmap.DeleteObject();
	memDC.DeleteDC(); 
} 

void CItemPanel::DrawEmptyNotification(CDC& dc, CRect& rcClient,int ndebug)
{
	CPoint ptText;
	CRect rcText;
	CSize szText;

	rcText.SetRect(rcClient.left, 16, rcClient.right, 0);
	rcText.bottom = (rcClient.top + rcClient.bottom) / 2;
	rcText.top = rcText.bottom - rcText.top; 
 
	dc.SetBkMode(TRANSPARENT);
	dc.SetBkColor(PANELBACKGROUND);
	dc.SetTextColor(RGB(0,0,0));
	dc.SelectObject(&m_font);
 
	CString nEmptyMsg(ConvertString("Nothing to be matched here!"));

	/*CString nEmptyMsg;
	nEmptyMsg.Format(_T("%d"),ndebug);*/

	szText		= dc.GetTextExtent(nEmptyMsg);
	ptText.x	= (rcText.left + rcText.right) / 2 - szText.cx / 2;
	ptText.y	= (rcText.top + rcText.bottom) / 2 - szText.cy / 2;

	dc.ExtTextOut(ptText.x, ptText.y, ETO_CLIPPED|ETO_OPAQUE, &rcText, nEmptyMsg, NULL);
	dc.ExcludeClipRect(&rcText);
}

void CItemPanel::InsertItem(Item stItem)
{
	Item* pItem = new Item;
	if (pItem == NULL)
	{
		return;
	}

	memcpy(pItem, &stItem, sizeof(stItem));

	m_pItems[m_nItems++] = pItem;

	if (TestPtInWnd())
	{
		return;
	}

	m_nScrollClipHight += INSERTCONFIGSPEED;
	m_nScrollClipHight = min(m_nScrollClipHight,UNIT_HEIGHT);
	m_nTopIndex = 0;
	Invalidate(TRUE);
	UpdateVScroll(0xFFFFFFFF);
	if (m_nScrollClipHight == UNIT_HEIGHT)
	{
		m_nAccelerate = 10;
		m_nScrollClipHight = 0;
		m_nInserting = FALSE;
		ScrollToVertical(0);
	}

	return ;
}

void CItemPanel::DeleteAllItems()
{
	for (int i = 0; i < MAX_ITEM_NUM; i++)
	{
		if (m_pItems[i] != NULL)
		{
			delete m_pItems[i];
			m_pItems[i] = NULL;
		}
	}

	m_nItems = 0;

	ActiveList_t::iterator it = m_ItemUIList.begin();
	while (it != m_ItemUIList.end())
	{
		it->second->ShowWindow(SW_HIDE);
		it++;
	}

	return;
}


CItemPanel::~CItemPanel()
{ 
	if (m_pItems)
	{
		Item** pIt = m_pItems;

		for(DWORD nCount = m_nItems;nCount;nCount--,pIt++)
		{
			if(*pIt)delete(*pIt);
		}
	}
	delete []m_pItems;

	for (int i=0;i<=m_nCountPerPage+1;i++)
	{
		CMatchItem *pItem = m_ItemUIList[i];
		delete pItem;
	}
}

BOOL CItemPanel::TestPtInWnd()
{
	CPoint point;
	GetCursorPos(&point);
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	if (rc.PtInRect(point))return TRUE; else return FALSE;
}

void CItemPanel::OnMouseMove( UINT nFlags, CPoint point )
{
	//((CFaceRecognizeDlg *)GetParent())->OnSetOutRange();
	CWnd::OnMouseMove(nFlags,point);
}

//CMatchItem Section

IMPLEMENT_DYNAMIC(CMatchItem, CWnd)

BEGIN_MESSAGE_MAP(CMatchItem, CWnd) 
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

CMatchItem::CMatchItem()
{
	m_pItem		= new Item();
	memset(m_pItem, 0, sizeof(Item));
	m_bOver		= FALSE;
	m_bOverPicSrc	= FALSE;
	m_bOverPicMatch	= FALSE;
	VERIFY(m_font.CreateFont(
		14,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial")));                 // lpszFacename
	VERIFY(m_fontBold.CreateFont(
		15,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial")));                 // lpszFacename
	m_rcRangeSrc.SetRect(IMAGE_MARGIN,IMAGE_MARGIN,IMAGE_WIDTH+IMAGE_MARGIN,IMAGE_HEIGHT - IMAGE_MARGIN);
	m_rcRangeMatch.SetRect(IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE + IMAGE_SPACE+IMAGE_ENLARGE,
							IMAGE_MARGIN,
							IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE + IMAGE_SPACE+IMAGE_ENLARGE + IMAGE_WIDTH,
							IMAGE_HEIGHT - IMAGE_MARGIN);
}

BOOL CMatchItem::Create(CWnd* pParentWnd, CRect rc)
{
	return CWnd::CreateEx(WS_EX_CONTROLPARENT, NULL, _T("CMatchItem"), WS_CHILD | WS_TABSTOP |
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS, rc, pParentWnd, 0, NULL);
}

void CMatchItem::OnPaint()
{
	CPaintDC dc(this); 
	CRect rc;
	GetClientRect(&rc);

	CDC memDC;
	CBitmap memBitmap;
	memDC.CreateCompatibleDC(NULL);
	memBitmap.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
	
	CBitmap *pOldBit = memDC.SelectObject(&memBitmap); 

	//background
	if (m_pItem->nIndex%2)
		memDC.FillSolidRect(0, 1, rc.Width(), rc.Height(),BACKGROUND_CONE);
	else
		memDC.FillSolidRect(0, 1, rc.Width(), rc.Height(),BACKGROUND_CTWO);
	if (m_bOver)
		memDC.FillSolidRect(0, 1, rc.Width(), rc.Height(),BACKGROUND_COVER);
	
	DrawText(&memDC,&rc);
	DrawImage(&memDC,&m_rcRangeSrc);
	DrawImage(&memDC,&m_rcRangeMatch,FALSE);
	DrawBackground(&memDC,&rc);

	dc.BitBlt(0,0,rc.Width(),rc.Height(),&memDC,0,0,SRCCOPY);
	memBitmap.DeleteObject();
	memDC.DeleteDC(); 
}  

void CMatchItem::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd::OnMouseMove( nFlags, point );  
	//((CFaceRecognizeDlg *)GetParent()->GetParent())->OnSetOutRange();
	BOOL bTemp;
	bTemp = m_bOver;
	//check if the point within client rect
	TestPtInWnd();
	SetCapture();
	POINT p2 = point;
	ClientToScreen(&p2);
	CWnd* wfp = WindowFromPoint(p2);
	if (wfp && wfp->m_hWnd != this->m_hWnd)
	{
		m_bOver= FALSE;
		ReleaseCapture();
	}
	//Redraw it only the status is changed.
	if (bTemp !=m_bOver)
	{
		Invalidate(TRUE); 
	}	

	//Enlarge the selected rectangle
	bTemp = m_bOverPicSrc;
	m_bOverPicSrc = TestPtInImageSrc(point);
	if (bTemp !=m_bOverPicSrc)
	{
		if (m_bOverPicSrc)
			m_rcRangeSrc.SetRect(MARGIN_ENLARGE,MARGIN_ENLARGE,IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE ,IMAGE_HEIGHT - MARGIN_ENLARGE);
		else
			m_rcRangeSrc.SetRect(IMAGE_MARGIN,IMAGE_MARGIN,IMAGE_WIDTH+IMAGE_MARGIN,IMAGE_HEIGHT - IMAGE_MARGIN);
		CRect rcTemp(MARGIN_ENLARGE,MARGIN_ENLARGE,IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE ,IMAGE_HEIGHT - MARGIN_ENLARGE);
		InvalidateRect(rcTemp);
	}

	bTemp = m_bOverPicMatch;
	m_bOverPicMatch = TestPtInImageMatch(point);
	if (bTemp !=m_bOverPicMatch)
	{
		if (m_bOverPicMatch)
			m_rcRangeMatch.SetRect(IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE + IMAGE_SPACE+MARGIN_ENLARGE,
									MARGIN_ENLARGE,
									IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE + IMAGE_SPACE+IMAGE_ENLARGE + IMAGE_WIDTH + IMAGE_ENLARGE,
									IMAGE_HEIGHT - MARGIN_ENLARGE);
		else
			m_rcRangeMatch.SetRect(IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE + IMAGE_SPACE+IMAGE_ENLARGE,
									IMAGE_MARGIN,
									IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE + IMAGE_SPACE+IMAGE_ENLARGE + IMAGE_WIDTH,
									IMAGE_HEIGHT - IMAGE_MARGIN);
		CRect rcTemp(IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE + IMAGE_SPACE+MARGIN_ENLARGE,
			MARGIN_ENLARGE,
			IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE + IMAGE_SPACE+IMAGE_ENLARGE + IMAGE_WIDTH + IMAGE_ENLARGE,
			IMAGE_HEIGHT - MARGIN_ENLARGE);
		InvalidateRect(rcTemp);
	} 
}

CMatchItem::~CMatchItem()
{
	delete m_pItem;
}

void CMatchItem::DrawBackground(CDC *pDC,CRect rc)
{ 
	CRect m_rcFrameSrc = rc;
	CRect m_rcContentSrc;
	m_rcContentSrc = m_rcFrameSrc;
	ExcludeFrame(m_rcContentSrc);
	pDC->ExcludeClipRect(m_rcContentSrc);
	pDC->FillSolidRect(rc,PANELBACKGROUND); 
}

void CMatchItem::DrawText(CDC *pDC,CRect rc)
{
	CPoint ptText;
	CRect rcText;  
	CString szOutputMsg;
	CString strTemp;

	int nRowSpace = 20;
	int nSectionSpace =8; 

	pDC->SetBkMode(TRANSPARENT);
	if (m_pItem->nIndex%2)
		pDC->SetBkColor(BACKGROUND_CONE);
	else
		pDC->SetBkColor(BACKGROUND_CTWO);
	if (m_bOver)
		pDC->SetBkColor(BACKGROUND_COVER);

	pDC->SetTextColor(RGB(255,255,255));
	pDC->SelectObject(&m_font);

	rcText.SetRect(rc.left, rc.top, rc.right, rc.bottom);
	//rcText.bottom	= (rc.top + 40);
	rcText.left		+= (2*IMAGE_WIDTH + IMAGE_SPACE + 4*IMAGE_MARGIN);

	ptText.x		= rcText.left + 20;
	ptText.y		= IMAGE_MARGIN;

	pDC->SelectObject(&m_fontBold);
	szOutputMsg = ConvertString("Target Information From Database");
	pDC->TextOut(ptText.x, ptText.y,szOutputMsg, szOutputMsg.GetLength());

	ptText.x		= rcText.left + 20;
	ptText.y		+= nRowSpace+2;
	strTemp.Format("        %s", m_pItem->strName);
	szOutputMsg = ConvertString("Name:") + strTemp;
	pDC->SelectObject(&m_font);
	pDC->TextOut(ptText.x, ptText.y,szOutputMsg, szOutputMsg.GetLength());

	ptText.x		= rcText.left + 20;
	ptText.y		+= nRowSpace;
	strTemp.Format("        %s", m_pItem->strIdCode);
	szOutputMsg = ConvertString("ID   Code:") + strTemp;
	pDC->TextOut(ptText.x, ptText.y, szOutputMsg, szOutputMsg.GetLength());

	ptText.x		= rcText.left + 20;
	ptText.y		+= nRowSpace;
	strTemp.Format("        %s", m_pItem->strBirthday);
	szOutputMsg = ConvertString("Birthday:") + strTemp;
	pDC->TextOut(ptText.x, ptText.y,szOutputMsg, szOutputMsg.GetLength());

	ptText.x		= rcText.left + 20;
	ptText.y		+= nRowSpace;
	strTemp.Format("        %s", m_pItem->strSex);
	szOutputMsg = ConvertString("Sex:") + strTemp; 
	pDC->TextOut(ptText.x, ptText.y,szOutputMsg, szOutputMsg.GetLength());
 
	ptText.x		= 15;
	ptText.y		= UNIT_HEIGHT - IMAGE_MARGIN - 20;

	CSize szText;
	szOutputMsg = ConvertString("Face From Video");
	szText		= pDC->GetTextExtent(szOutputMsg);
	ptText.x	= (IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE - MARGIN_ENLARGE - szText.cx)/2;
	pDC->SelectObject(&m_fontBold);
	pDC->TextOut(ptText.x, ptText.y,szOutputMsg, szOutputMsg.GetLength());
 
	szOutputMsg = ConvertString("Face From Database");
	szText		= pDC->GetTextExtent(szOutputMsg);
	ptText.x	= IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE + IMAGE_SPACE+MARGIN_ENLARGE + (IMAGE_WIDTH+IMAGE_MARGIN+IMAGE_ENLARGE - MARGIN_ENLARGE - szText.cx)/2;
	pDC->SelectObject(&m_fontBold);
	pDC->TextOut(ptText.x, ptText.y,szOutputMsg, szOutputMsg.GetLength());
}

void CMatchItem::DrawImage(CDC *pDC,CRect rcRange,BOOL isSrc)
{ 
	CRect rcFrame(&rcRange); 

	char szStrPath[256] = {0};
	if (isSrc)
	{
		strncpy(szStrPath, (const char*)m_pItem->strSrcImgPath, 256);
	}
	else
	{
		strncpy(szStrPath, (const char*)m_pItem->strFoundImgPath, 256);
	}

	int cx;
	int cy;
	cx = rcFrame.Width();
	cy = rcFrame.Height();

	int x = rcFrame.left + ( rcFrame.Width() - cx ) / 2;
	int y = rcFrame.top + ( rcFrame.Height() - cy ) / 2;

	CPicture cPic;
	cPic.LoadPicture(szStrPath);
	cPic.DrawPicture(pDC->GetSafeHdc(), x, y, cx, cy);
}

BOOL CMatchItem::TestPtInImageSrc(CPoint point)
{
	if (m_rcRangeSrc.PtInRect(point))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CMatchItem::TestPtInImageMatch(CPoint point)
{
	if (m_rcRangeMatch.PtInRect(point))
	{
		return TRUE;
	}
	return FALSE;
} 

void CMatchItem::TestPtInWnd()
{
	CPoint point;
	GetCursorPos(&point);
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	ExcludeFrame(rc);
	if (rc.PtInRect(point))m_bOver = TRUE; else m_bOver = FALSE;
}

void CMatchItem::ExcludeFrame(CRect& rcClient)
{
	rcClient.bottom -= 5;
	rcClient.top += 5;
	rcClient.left += 5;
	rcClient.right -= 5;
}
