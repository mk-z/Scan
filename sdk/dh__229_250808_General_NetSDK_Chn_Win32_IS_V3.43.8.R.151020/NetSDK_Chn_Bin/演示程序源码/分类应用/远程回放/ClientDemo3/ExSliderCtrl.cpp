// ExSliderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo3.h"
#include "ExSliderCtrl.h"
#include "ClientDemo3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExSliderCtrl

CExSliderCtrl::CExSliderCtrl()
{
	m_bIsMouseDown = FALSE;
}

CExSliderCtrl::~CExSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CExSliderCtrl, CSliderCtrl)
	//{{AFX_MSG_MAP(CExSliderCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExSliderCtrl message handlers

void CExSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bIsMouseDown)
	{
		m_bIsMouseDown = TRUE;
		((CClientDemo3Dlg*)GetParent())->ExSliderButtonDown();
	}
	
	CSliderCtrl::OnLButtonDown(nFlags, point);
}

void CExSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bIsMouseDown)
	{
		m_bIsMouseDown = FALSE;
		((CClientDemo3Dlg*)GetParent())->ExSliderButtonUp();
	}
	
	CSliderCtrl::OnLButtonUp(nFlags, point);
}
