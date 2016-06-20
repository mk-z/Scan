#if !defined(AFX_GLOBALCFG_H__C793C7DA_CFBB_4172_9FC6_4C11B3C7A750__INCLUDED_)
#define AFX_GLOBALCFG_H__C793C7DA_CFBB_4172_9FC6_4C11B3C7A750__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobalCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGlobalCfg dialog

class CGlobalCfg : public CDialog
{
// Construction
public:
	CGlobalCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGlobalCfg)
	enum { IDD = IDD_DLG_GLOBAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlobalCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGlobalCfg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBALCFG_H__C793C7DA_CFBB_4172_9FC6_4C11B3C7A750__INCLUDED_)
