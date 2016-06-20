#if !defined(AFX_AREADRAW_H__118C76AC_0A7A_4BAE_9A25_A959FD0D478B__INCLUDED_)
#define AFX_AREADRAW_H__118C76AC_0A7A_4BAE_9A25_A959FD0D478B__INCLUDED_

#include <list>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AreaDraw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaDraw dialog

class CAreaDraw : public CDialog
{
// Construction
public:
	CAreaDraw(CWnd* pParent = NULL);   // standard constructor

	void InitDlg(CFG_MOTION_INFO* pMotionInfo);

	void AddWnd(const CFG_MOTION_WINDOW& stuMotionWnd);

	void DeleteWnd();

	const std::list<CFG_MOTION_WINDOW*>& GetMotionWndList()
	{
		return m_lsMotionWnd;
	}

	void SetAreathreshold(int nParam);

	void SetSensitivity(int nParam);

// Dialog Data
	//{{AFX_DATA(CAreaDraw)
	enum { IDD = IDD_AREA_DRAW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaDraw)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAreaDraw)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void	DrawRect(HDC hDc, CFG_RECT& rt);

	CFG_MOTION_WINDOW*	IsOnRect(CPoint& pt);

private:
	CFG_MOTION_INFO*				m_pMotionInfo;
	BOOL							m_bAdd;
	BOOL							m_bDraging;
	int								m_dwHalfLen;
	int								m_nAreaThreshold;
	int								m_nSensitivity;
	CFG_MOTION_WINDOW*				m_pCurrentRect;
	std::list<CFG_MOTION_WINDOW*>	m_lsMotionWnd;
	CRect							m_rtWnd;
	CPoint							m_ptStartPt;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREADRAW_H__118C76AC_0A7A_4BAE_9A25_A959FD0D478B__INCLUDED_)
