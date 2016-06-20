#if !defined(AFX_CONFIGALARMMOTIONAREABLOCK_H__148B9900_E678_4D77_95F1_A3B6A5DFAC81__INCLUDED_)
#define AFX_CONFIGALARMMOTIONAREABLOCK_H__148B9900_E678_4D77_95F1_A3B6A5DFAC81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigAlarmMotionAreaBlock.h : header file
//

#define		MSG_SELETED					WM_USER + 2007
#define		MSG_SHOW					WM_USER + 2008

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarmMotionAreaBlock window

class CConfigAlarmMotionAreaBlock : public CWnd
{
// Construction
public:
	CConfigAlarmMotionAreaBlock();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigAlarmMotionAreaBlock)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	afx_msg LRESULT OnSeleted(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShow(WPARAM wParam, LPARAM lParam);

// Implementation
public:
	virtual ~CConfigAlarmMotionAreaBlock();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConfigAlarmMotionAreaBlock)
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL IsSeleted(){return m_bSelected;}
	void SetPos(BYTE x, BYTE y);
	void SetStatus(BOOL selected){m_bSelected = selected;}
	
private:
	CBrush m_whiteBrush;
	CBrush m_blueBrush;
	CBrush *m_brush;
	BOOL   m_bSelected;
	BYTE   m_byX;
	BYTE   m_byY;
	
	CRect m_rect;
	CDC *m_thisDC;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGALARMMOTIONAREABLOCK_H__148B9900_E678_4D77_95F1_A3B6A5DFAC81__INCLUDED_)
