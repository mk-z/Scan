#if !defined(AFX_MONITORWND_H__5CB41425_81B9_40B3_AA0D_8DDD1A5488F7__INCLUDED_)
#define AFX_MONITORWND_H__5CB41425_81B9_40B3_AA0D_8DDD1A5488F7__INCLUDED_

#include "PlayWnd.h"	// Added by ClassView
#include <afxtempl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonitorWnd.h : header file
//
//////////////////////////////////////////////////////////////////////////
// window color
#define	MONITOR_BACK_COLOR			RGB(192,192,192)

// 
#define MAX_CHANNELNUM				16

// 
#define WINDOW_PAGE_SPACE			1

/////////////////////////////////////////////////////////////////////////////
// CMonitorWnd window

class CMonitorWnd : public CWnd
{
// Construction
public:
	CMonitorWnd();

// Attributes
public:
	// 
	void SetMonitorID(int nID) { m_nMonitorID = nID; }
	int  GetMonitorID(void) { return m_nMonitorID; }
	
	// 
	BOOL GetFullScreen();
	void SetFullScreen(BOOL bFlag);

	// 
	void SetMultiScreen(BOOL bFlag);
	BOOL GetMultiScreen();

	// 
	void SetAutoAdjustPos(BOOL bFlag);
	BOOL GetAutoAdjustPos();

// Operations
public:
	// 
	int SetShowPlayWindow(int nWindowNum, int nBeginNum=0);

	// 
	CWnd* GetPage(int nIndex);

	// 
	int GetCount() const;
	int GetCurCount();
	
	// 
	void SetActivePage(CWnd *pWnd, BOOL bRepaint = TRUE);

	// 
	CWnd* GetActivePage();

	// 
	void CleanActivePage();

	// 
	void SetDrawActivePage(BOOL bFlag, COLORREF clrTopLeft=RGB(255, 0, 0), COLORREF clrBottomRight=RGB(255, 0, 0));
	BOOL GetDrawActivePage();

	// 
	void SetShowPortion(int nPortion=100);
	int  GetShowPortion();

	// 
	virtual void UpdateWnd();

protected:
	// 
	BOOL AddPage(CWnd *pWnd, BOOL bRepaint = TRUE);

	// 
	CWnd* DelPage(CWnd *pWnd);

	// 
	CWnd* DelPage();

	// 
	CWnd* GetNextPage(CWnd *pWnd);

	// 
	CWnd *GetPrevPage(CWnd *pWnd);

	// 
	CWnd* GetTailPage();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitorWnd)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMonitorWnd();

	virtual void OnVideoLButtonDown(int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void OnVideoLButtonUp(int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void OnVideoLButtonDblClk(int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoRButtonDown(int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoRButtonUp(int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoMove(int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoMoving(int nWndID, WPARAM wParam, LPARAM lParam);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMonitorWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// 
	void GetShowRect(LPRECT lpRect);

	// 
	void AdjustRect(LPRECT lpRect);

	// 
	virtual void CalcPageRect(LPRECT lpRect, int nIndex, int nPageCount);

	// 
	void DrawActivePage(BOOL bFlag);

private:
	// 
	int m_nMonitorID;

	// 
	CPlayWnd m_WndVideo[MAX_CHANNELNUM];

	// 
	CList<CWnd *,CWnd *> m_PageList;

	// 
	CWnd* m_pActivePage;

	// 
	BOOL m_bDrawActive;

	// 
	COLORREF m_clrTopLeft;
	COLORREF m_clrBottomRight;

	// 
	BOOL m_bMultiScreen;

	// 
	BOOL m_bAutoAdjustPos;

	// 
	int	m_nShowPortion;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORWND_H__5CB41425_81B9_40B3_AA0D_8DDD1A5488F7__INCLUDED_)
