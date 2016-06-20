#if !defined(AFX_PLAYWND_H__872D3A8B_3472_402F_A40D_CD7E44A4EE4B__INCLUDED_)
#define AFX_PLAYWND_H__872D3A8B_3472_402F_A40D_CD7E44A4EE4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayWnd.h : header file
//
//////////////////////////////////////////////////////////////////////////

#define	VIDEO_BACK_COLOR			RGB(128,0,128)

#define VIDEO_REPAINT				WM_USER + 1978
#define	VIDEO_MENU_BASE				WM_USER + 1979
#define	VIDEO_MENU_END				WM_USER + 1985
#define	VIDEO_MENU_FULLSCREEN		WM_USER + 1979
#define	VIDEO_MENU_MULTISCREEN		WM_USER + 1980
#define	VIDEO_MENU_AUTOADJUST		WM_USER + 1981

#define NAME_MENU_FULLSCREEN		"FullScreen"
#define NAME_MENU_MULTISCREEN		"MultiScreen"
#define NAME_MENU_AUTOADJUST		"AutoAdjust"

/////////////////////////////////////////////////////////////////////////////
// CPlayWnd window

class CPlayWnd : public CWnd
{
// Construction
public:
	CPlayWnd();

// Attributes
public:
	void SetWndID(int nID) { m_nWndID = nID; }
	int  GetWndID(void) { return m_nWndID; }
	BOOL ShowCaptureText(CString strText, LPRECT lpRect);
	void SetFlash(BOOL bFlag);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayWnd)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPlayWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlayWnd)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVideoMenu(UINT nID);
	afx_msg LRESULT OnRepaintWnd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nWndID;
	BOOL m_bDoing;
	int m_nNum;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYWND_H__872D3A8B_3472_402F_A40D_CD7E44A4EE4B__INCLUDED_)
