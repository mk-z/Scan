#if !defined(AFX_STRATEGYDOWNLOAD_H__BF03AE22_1823_486F_A428_2A58BD13CB98__INCLUDED_)
#define AFX_STRATEGYDOWNLOAD_H__BF03AE22_1823_486F_A428_2A58BD13CB98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StrategyDownload.h : header file
//
#include "dhnetsdk.h"
/////////////////////////////////////////////////////////////////////////////
// CStrategyDownload dialog

class CStrategyDownload : public CDialog
{
// Construction
public:
	CStrategyDownload(CWnd* pParent = NULL);   // standard constructor
	void InitDlgInfo(DHDEV_DOWNLOAD_STRATEGY_CFG* pDownloadInfo);
	void SaveAll(void);
	void CleanAll(void);
	DHDEV_DOWNLOAD_STRATEGY_CFG	m_stuDownload;
// Dialog Data
	//{{AFX_DATA(CStrategyDownload)
	enum { IDD = IDD_CONFIG_STRATEGY_DWONLOAD };
	CComboBox	m_ccbDownload;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStrategyDownload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStrategyDownload)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRATEGYDOWNLOAD_H__BF03AE22_1823_486F_A428_2A58BD13CB98__INCLUDED_)
