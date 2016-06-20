#if !defined(AFX_DIALOGCONFIG_H__52B62973_FC32_4A23_B538_3947DD242444__INCLUDED_)
#define AFX_DIALOGCONFIG_H__52B62973_FC32_4A23_B538_3947DD242444__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogConfig dialog

class CDialogConfig : public CDialog
{
// Construction
public:
	CDialogConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogConfig)
	enum { IDD = IDD_DIALOG_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogConfig)
	virtual void OnOK();
	afx_msg void OnButtonChoseFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGCONFIG_H__52B62973_FC32_4A23_B538_3947DD242444__INCLUDED_)



