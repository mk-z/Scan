#if !defined(AFX_CONFIG_H__671E9A78_9831_4C57_AE51_731CBCE26F45__INCLUDED_)
#define AFX_CONFIG_H__671E9A78_9831_4C57_AE51_731CBCE26F45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Config.h : header file
//

#include "ConfigGlobal.h"
#include "ConfigModule.h"
#include "ConfigRules.h"

/////////////////////////////////////////////////////////////////////////////
// CConfig dialog

class CConfig : public CDialog
{
public:
	void initConfigDlg(int nChannel);

	void uninitConfigDlg();

	void showPreview();
	
public:
	typedef enum DlgType{
		dlgNone = -1,
		dlgConfigGlobal,
		dlgConfigModule,
		dlgConfigRule,
	};
	DlgType			m_currentDlg;
	CConfigGlobal	m_dlgConfigGlobal;
	CConfigModule	m_dlgConfigModule;
	CConfigRules	m_dlgConfigRules;

// Construction
public:
	CConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfig)
	enum { IDD = IDD_CONFIG };
	CTabCtrl	m_tabConfig;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeConfigTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIG_H__671E9A78_9831_4C57_AE51_731CBCE26F45__INCLUDED_)
