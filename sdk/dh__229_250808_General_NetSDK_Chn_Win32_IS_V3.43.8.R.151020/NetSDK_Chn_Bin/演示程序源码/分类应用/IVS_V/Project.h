#if !defined(AFX_PROJECT_H__FD45FC0A_2A58_4978_AACC_F5441AFB4AD3__INCLUDED_)
#define AFX_PROJECT_H__FD45FC0A_2A58_4978_AACC_F5441AFB4AD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Project.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectCfg dialog

class CProjectCfg : public CDialog
{
// Construction
public:
	CProjectCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProjectCfg)
	enum { IDD = IDD_DLG_PROJECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectCfg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECT_H__FD45FC0A_2A58_4978_AACC_F5441AFB4AD3__INCLUDED_)
