#if !defined(AFX_RULETREECTRL_H__663683BD_9C11_4776_9ECD_9E3FA9278C38__INCLUDED_)
#define AFX_RULETREECTRL_H__663683BD_9C11_4776_9ECD_9E3FA9278C38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleTreeCtrl.h : header file
//

#define WM_ENABLEPIC (WM_USER + 100)

/////////////////////////////////////////////////////////////////////////////
// CRuleTreeCtrl window

class CRuleTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CRuleTreeCtrl();

// Attributes
public:
	int m_nNum;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRuleTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRuleTreeCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnsetEnablePic();
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	HTREEITEM m_hSelectItem;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULETREECTRL_H__663683BD_9C11_4776_9ECD_9E3FA9278C38__INCLUDED_)
