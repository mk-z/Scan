#if !defined(AFX_PANNELENCODER_H__4801D331_51EA_429B_B776_9DF2702C7A7A__INCLUDED_)
#define AFX_PANNELENCODER_H__4801D331_51EA_429B_B776_9DF2702C7A7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PannelEncoder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPannelEncoder dialog

class CPannelEncoder : public CDialog
{
// Construction
public:
	CPannelEncoder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPannelEncoder)
	enum { IDD = IDD_PANNEL_ENCODER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPannelEncoder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPannelEncoder)
	afx_msg void OnBtnAddEncoder();
	afx_msg void OnBtnDelEncoder();
	afx_msg void OnBtnPlaybackFile();
	afx_msg void OnBtnPlaybackTime();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANNELENCODER_H__4801D331_51EA_429B_B776_9DF2702C7A7A__INCLUDED_)
