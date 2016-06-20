#if !defined(AFX_ADDDEVICE_H__D7DA1C6C_749E_407F_80A9_4771F5E84810__INCLUDED_)
#define AFX_ADDDEVICE_H__D7DA1C6C_749E_407F_80A9_4771F5E84810__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddDevice.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddDevice dialog

class CAddDevice : public CDialog
{
// Construction
public:
	CAddDevice(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddDevice)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddDevice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddDevice)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDDEVICE_H__D7DA1C6C_749E_407F_80A9_4771F5E84810__INCLUDED_)
