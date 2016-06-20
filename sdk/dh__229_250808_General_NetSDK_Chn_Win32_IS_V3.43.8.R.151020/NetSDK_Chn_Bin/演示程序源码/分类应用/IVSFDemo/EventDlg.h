#if !defined(AFX_EVENTDLG_H__7AC9F80A_0D2B_4DBF_9691_C82D7034EF58__INCLUDED_)
#define AFX_EVENTDLG_H__7AC9F80A_0D2B_4DBF_9691_C82D7034EF58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EventDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEventDlg dialog

class CEventDlg : public CDialog
{
// Construction
public:
	CEventDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEventDlg)
	enum { IDD = IDD_DIALOG_IFS_EVENT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTDLG_H__7AC9F80A_0D2B_4DBF_9691_C82D7034EF58__INCLUDED_)
