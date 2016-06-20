#if !defined(AFX_VIDEOOUTDLG_H__62326EAE_FD42_4287_807B_9103236BE8FC__INCLUDED_)
#define AFX_VIDEOOUTDLG_H__62326EAE_FD42_4287_807B_9103236BE8FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoOutDlg.h : header file
//

#include "dhnetsdk.h"
/////////////////////////////////////////////////////////////////////////////
// CVideoOutDlg dialog

class CVideoOutDlg : public CDialog
{
// Construction
public:
	CVideoOutDlg(CWnd* pParent = NULL);   // standard constructor
	void SetDlgParam(LLONG lLoginID);
	LLONG m_hCurLoginID;
	DEV_VIDEOOUT_INFO m_stVideoOut;

// Dialog Data
	//{{AFX_DATA(CVideoOutDlg)
	enum { IDD = IDD_DLG_VIDEOOUT };
	CComboBox	m_ctlResolution;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoOutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoOutDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOOUTDLG_H__62326EAE_FD42_4287_807B_9103236BE8FC__INCLUDED_)
