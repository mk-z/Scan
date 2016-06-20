#if !defined(AFX_PLAYCTRLPANNEL_H__0D11702E_4BD1_4C43_BB11_5A1AEC95C803__INCLUDED_)
#define AFX_PLAYCTRLPANNEL_H__0D11702E_4BD1_4C43_BB11_5A1AEC95C803__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayCtrlPannel.h : header file
//
#include "ExSliderCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CPlayCtrlPannel dialog

class CPlayCtrlPannel : public CDialog
{
// Construction
public:
	CPlayCtrlPannel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayCtrlPannel)
	enum { IDD = IDD_PANNEL_PLAYCTRL };
	CExSliderCtrl	m_play_position;
	UINT	m_play_frame;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayCtrlPannel)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayCtrlPannel)
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcapturePlayPosition(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCtrlPlay();
	afx_msg void OnCtrlPlaystop();
	afx_msg void OnCtrlStepplay();
	afx_msg void OnCtrlPlayfast();
	afx_msg void OnCtrlPlayslow();
	afx_msg void OnCtrlFramecontrol();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	
	void StartPlay();
	void StopPlay();
	
private:
	LONG lPlayCount;
	BOOL m_bPlaying;
	CBrush m_myBrush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYCTRLPANNEL_H__0D11702E_4BD1_4C43_BB11_5A1AEC95C803__INCLUDED_)
