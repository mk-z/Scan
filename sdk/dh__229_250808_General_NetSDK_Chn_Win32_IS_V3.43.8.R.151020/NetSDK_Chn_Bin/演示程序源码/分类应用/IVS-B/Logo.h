#if !defined(AFX_LOGO_H__AFAAEBD9_517D_4CB3_938E_72669AC6FE44__INCLUDED_)
#define AFX_LOGO_H__AFAAEBD9_517D_4CB3_938E_72669AC6FE44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Logo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogo dialog

class CLogo : public CDialog
{
public:
	void stepIt();

// Construction
public:
	CLogo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogo)
	enum { IDD = IDD_SUBDLG_LOGO };
	CProgressCtrl	m_ctrlProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGO_H__AFAAEBD9_517D_4CB3_938E_72669AC6FE44__INCLUDED_)
