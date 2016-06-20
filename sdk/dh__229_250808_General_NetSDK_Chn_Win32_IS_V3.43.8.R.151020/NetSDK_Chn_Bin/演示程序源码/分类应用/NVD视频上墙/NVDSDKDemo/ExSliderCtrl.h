#if !defined(AFX_EXSLIDERCTRL_H__553DC98D_713D_4A69_AD1E_3C88036CC2EB__INCLUDED_)
#define AFX_EXSLIDERCTRL_H__553DC98D_713D_4A69_AD1E_3C88036CC2EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExSliderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExSliderCtrl window

class CExSliderCtrl : public CSliderCtrl
{
// Construction
public:
	CExSliderCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExSliderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExSliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExSliderCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bIsMouseDown;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXSLIDERCTRL_H__553DC98D_713D_4A69_AD1E_3C88036CC2EB__INCLUDED_)
