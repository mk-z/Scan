// ClientDemo4Dlg.h : header file
//

#if !defined(AFX_CLIENTDEMO4DLG_H__9D297D32_70F7_43FB_B811_A7924197BDA8__INCLUDED_)
#define AFX_CLIENTDEMO4DLG_H__9D297D32_70F7_43FB_B811_A7924197BDA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDemo4Dlg dialog

class CClientDemo4Dlg : public CDialog
{
// Construction
public:
	BOOL m_bServer;
	CClientDemo4Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDemo4Dlg)
	enum { IDD = IDD_CLIENTDEMO4_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo4Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDemo4Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnRadioClient();
	afx_msg void OnRadioServer();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO4DLG_H__9D297D32_70F7_43FB_B811_A7924197BDA8__INCLUDED_)
