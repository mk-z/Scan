#if !defined(AFX_ADDDECODERDLG_H__A2EC4CC6_E65A_4C57_A907_9388F96FD8DC__INCLUDED_)
#define AFX_ADDDECODERDLG_H__A2EC4CC6_E65A_4C57_A907_9388F96FD8DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddDecoderDlg.h : header file
//
#include "dhnetsdk.h"
/////////////////////////////////////////////////////////////////////////////
// CAddDecoderDlg dialog

class CAddDecoderDlg : public CDialog
{
// Construction
public:
	CAddDecoderDlg(CWnd* pParent = NULL);   // standard constructor

public:
	LLONG m_lLoginHandle;
	int m_nMonitorNum;

// Dialog Data
	//{{AFX_DATA(CAddDecoderDlg)
	enum { IDD = IDD_DLG_ADD_DECODER };
	CString	m_strDecIp;
	CString	m_strDecName;
	UINT	m_nDecPort;
	CString	m_strDecPwd;
	CString	m_strDecUser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddDecoderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddDecoderDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void ShowLoginErrorReason(int nError);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDDECODERDLG_H__A2EC4CC6_E65A_4C57_A907_9388F96FD8DC__INCLUDED_)
