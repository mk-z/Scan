#if !defined(AFX_WNDCONTAINER_H__86A07374_4AF8_4449_82C5_621FAB0F6BAE__INCLUDED_)
#define AFX_WNDCONTAINER_H__86A07374_4AF8_4449_82C5_621FAB0F6BAE__INCLUDED_

#include "MonitorWnd.h"	// Added by ClassView
#include <afxtempl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndContainer.h : header file
//
//////////////////////////////////////////////////////////////////////////

#define	CONTAINER_BACK_COLOR		RGB(255,255,255)

#define MAX_MONITORNUM				16

#define WINDOW_MONITOR_SPACE		1

/////////////////////////////////////////////////////////////////////////////
// CWndContainer window

class CWndContainer : public CWnd
{
// Construction
public:
	CWndContainer();

// Attributes
public:
	BOOL GetFullScreen();
	void SetFullScreen(BOOL bFlag);

	void SetMultiScreen(BOOL bFlag);
	BOOL GetMultiScreen();

	void SetAutoAdjustPos(BOOL bFlag);
	BOOL GetAutoAdjustPos();

// Operations
public:
	int SetShowPlayWindow(int nMonitorNum, int nPageNum=4);

	CWnd* GetPage(int nIndex);

	int GetCount() const;

	void SetActivePage(CWnd *pWnd, BOOL bRepaint = TRUE);
	void SetActivePage(int nMonitorID, BOOL bRepaint = TRUE);

	CWnd* GetActivePage();

	void SetDrawActivePage(BOOL bFlag, COLORREF clrTopLeft=RGB(255, 0, 0), COLORREF clrBottomRight=RGB(255, 0, 0));
	BOOL GetDrawActivePage();

	void SetShowPortion(int nPortion=100);
	int  GetShowPortion();

	virtual void UpdateWnd();

protected:
	BOOL AddPage(CWnd *pWnd, BOOL bRepaint = TRUE);

	CWnd* DelPage(CWnd *pWnd);

	CWnd* DelPage();

	CWnd* GetNextPage(CWnd *pWnd);

	CWnd *GetPrevPage(CWnd *pWnd);

	CWnd* GetTailPage();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndContainer)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWndContainer();

	virtual void OnVideoLButtonDown(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void OnVideoLButtonUp(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void OnVideoLButtonDblClk(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoRButtonDown(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoRButtonUp(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoMove(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoMoving(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndContainer)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void GetShowRect(LPRECT lpRect);

	void AdjustRect(LPRECT lpRect);

	virtual void CalcPageRect(LPRECT lpRect, int nIndex, int nPageCount);

	void DrawActivePage(BOOL bFlag);

private:
	CMonitorWnd m_WndMonitor[MAX_MONITORNUM];

	CList<CWnd *,CWnd *> m_PageList;

	CWnd* m_pActivePage;

	BOOL m_bDrawActive;

	COLORREF m_clrTopLeft;
	COLORREF m_clrBottomRight;

	BOOL m_bFullScreen;

	BOOL m_bMultiScreen;

	BOOL m_bAutoAdjustPos;

	int	m_nShowPortion;
	
	WINDOWPLACEMENT m_windowPlace;
	CWnd* m_wndParent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDCONTAINER_H__86A07374_4AF8_4449_82C5_621FAB0F6BAE__INCLUDED_)
