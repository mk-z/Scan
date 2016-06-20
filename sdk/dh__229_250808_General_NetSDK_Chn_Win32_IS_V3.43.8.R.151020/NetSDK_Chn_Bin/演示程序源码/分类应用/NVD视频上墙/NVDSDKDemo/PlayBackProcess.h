#if !defined(AFX_PLAYBACKPROCESS_H__53B79D82_F75A_4054_A65E_12D8FEDC130B__INCLUDED_)
#define AFX_PLAYBACKPROCESS_H__53B79D82_F75A_4054_A65E_12D8FEDC130B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayBackProcess.h : header file
//
#include "ExSliderCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPlayBackProcess dialog

class CPlayBackProcess : public CDialog
{
// Construction
public:
	void ExSliderButtonUp();
	void ExSliderButtonDown();
	CPlayBackProcess(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayBackProcess)
	enum { IDD = IDD_DLG_PLAYBACK_PROCESS };
	CExSliderCtrl	m_ctlProcess;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayBackProcess)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayBackProcess)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnReleasedcaptureSliderProcess(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBtnPlay();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nTimer;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYBACKPROCESS_H__53B79D82_F75A_4054_A65E_12D8FEDC130B__INCLUDED_)
