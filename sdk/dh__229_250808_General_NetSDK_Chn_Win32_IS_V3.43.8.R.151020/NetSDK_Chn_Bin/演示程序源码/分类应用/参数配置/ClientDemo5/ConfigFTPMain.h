#if !defined(AFX_CONFIGFTPMAIN_H__253FD6D4_5BC2_4373_9586_EAB8195506DC__INCLUDED_)
#define AFX_CONFIGFTPMAIN_H__253FD6D4_5BC2_4373_9586_EAB8195506DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigFTPMain.h : header file
//
#include "ConfigFTPEx.h"
#include "ConfigFTP.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigFTPMain dialog

class CConfigFTPMain : public CDialog
{
// Construction
public:
	CConfigFTPMain(CWnd* pParent = NULL);   // standard constructor
	//Clear information
	void InitDlgInfo();
	void CleanAll();
// Dialog Data
	//{{AFX_DATA(CConfigFTPMain)
	enum { IDD = IDD_CONFIG_FTPMAIN };
	CTabCtrl	m_ctlFTPTab;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
    CConfigFTPEx m_TabFtpEx;
	CConfigFTP   m_TabFtpStorage;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigFTPMain)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigFTPMain)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonApply();
	afx_msg void OnSelchangeTabFtp(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitTabControl();
	void DoTab(int nTab);
	void SetDlgState(CWnd *pWnd, BOOL bShow);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGFTPMAIN_H__253FD6D4_5BC2_4373_9586_EAB8195506DC__INCLUDED_)
