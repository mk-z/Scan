#if !defined(AFX_IVSRULEPREVIEW_H__588A4A1E_E79A_49D5_939B_990B9926C968__INCLUDED_)
#define AFX_IVSRULEPREVIEW_H__588A4A1E_E79A_49D5_939B_990B9926C968__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IvsRulePreview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIvsRulePreview window

class CIvsRulePreview : public CWnd
{
public:
	void setRuleData(RuleStruct* pRuleStruct, BOOL bClear);

	void beginDraw(HTREEITEM hItem);
	
	//»æÍ¼»Øµ÷
	static void _stdcall drawIvsRuleCfgProc(long nPort, HDC hDc, LONG dwUser);

public:
	CRITICAL_SECTION	m_cs;
	DWORD		m_dwRuleType;

	friend class CDemoIVSbDlg;
	friend class CConfig;
	friend class CConfigRules;

private:
	CFG_ANALYSERULES_INFO m_cfgRuleInfo;
	CFG_POLYGON*	m_pPolygonCfg;
	int				m_iPtCnt;
	float	m_fX;
	float	m_fY;
	BOOL	m_bAddUpstairsLine;
	BOOL	m_bAddDownstairsLine;
	BOOL		m_bAddRegion;
	HTREEITEM	m_hItemToBeDraw;

	BOOL	m_bAddDirection;

// Construction
public:
	CIvsRulePreview();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIvsRulePreview)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIvsRulePreview();

	// Generated message map functions
protected:
	//{{AFX_MSG(CIvsRulePreview)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVSRULEPREVIEW_H__588A4A1E_E79A_49D5_939B_990B9926C968__INCLUDED_)
