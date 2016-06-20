// RuleTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "RuleTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuleTreeCtrl

CRuleTreeCtrl::CRuleTreeCtrl() :
m_hSelectItem(0),
m_nNum(0)
{
}

CRuleTreeCtrl::~CRuleTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CRuleTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CRuleTreeCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
	ON_COMMAND(WM_ENABLEPIC, OnsetEnablePic)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleTreeCtrl message handlers

int CRuleTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CRuleTreeCtrl::OnDestroy() 
{
	CTreeCtrl::OnDestroy();
	
	// TODO: Add your message handler code here
	
	HTREEITEM hItem = GetRootItem();
	while(hItem)
	{
		RuleNodeInfo* pRuleNodeInfo = (RuleNodeInfo*)GetItemData(hItem);
		if (!pRuleNodeInfo)
		{
			hItem = GetNextSiblingItem(hItem);
			continue;
		}
		
		delete pRuleNodeInfo;
		pRuleNodeInfo = NULL;
		
		hItem = GetNextSiblingItem(hItem);
	}
}
/*
 *	
 */
void CRuleTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//	CTreeCtrl::OnLButtonUp(nFlags, point);
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	HTREEITEM hItem = HitTest(pt);
	if (!hItem)
	{
		return;
	}

	m_hSelectItem = hItem;
	SelectItem(hItem);

	if (GetCheck(hItem))
	{
		SetCheck(hItem, FALSE);
	} 
	else
	{
		SetCheck(hItem, TRUE);
	}
}
/*
 *	
*/
void CRuleTreeCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	CPoint pt;
	GetCursorPos(&pt);
	
	ScreenToClient(&pt);
	HTREEITEM hItem = HitTest(pt);
	if (!hItem)
	{
		return;
	}
	
	m_hSelectItem = hItem;
	SelectItem(hItem);
	
	RuleNodeInfo* pRuleNodeInfo = (RuleNodeInfo*)GetItemData(hItem);
	if (!pRuleNodeInfo)
	{
		return;
	}
	
	BOOL bEnPic = pRuleNodeInfo->bEnPic;
	
	CMenu menu;
	menu.CreatePopupMenu();
	if (bEnPic)
	{
		menu.AppendMenu(MF_STRING | MF_CHECKED, WM_ENABLEPIC, ConvertString(_T("EnPic")));
	} 
	else
	{
		menu.AppendMenu(MF_STRING | MF_UNCHECKED, WM_ENABLEPIC, ConvertString(_T("EnPic")));
	}
	
	ClientToScreen(&pt);
	menu.TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
	
	*pResult = 0;
}

/*
 *	
 */
void CRuleTreeCtrl::OnsetEnablePic()
{
	if (!m_hSelectItem)
	{
		return;
	}

	RuleNodeInfo* pRuleNodeInfo = (RuleNodeInfo*)GetItemData(m_hSelectItem);
	if (!pRuleNodeInfo)
	{
		return;
	}

	if (pRuleNodeInfo->bEnPic)
	{
		pRuleNodeInfo->bEnPic = FALSE;
	} 
	else
	{
		pRuleNodeInfo->bEnPic = TRUE;
	}
}


