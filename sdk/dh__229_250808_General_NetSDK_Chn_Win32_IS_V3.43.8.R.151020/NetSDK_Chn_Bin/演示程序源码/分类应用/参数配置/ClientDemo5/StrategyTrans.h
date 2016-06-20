#if !defined(AFX_STRATEGYTRANS_H__701DF518_2E68_4FB1_BC81_F29E9BEFB617__INCLUDED_)
#define AFX_STRATEGYTRANS_H__701DF518_2E68_4FB1_BC81_F29E9BEFB617__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StrategyTrans.h : header file
//
#include "dhnetsdk.h"
/////////////////////////////////////////////////////////////////////////////
// CStrategyTrans dialog

class CStrategyTrans : public CDialog
{
// Construction
public:
	CStrategyTrans(CWnd* pParent = NULL);   // standard constructor
	void InitDlgInfo(CFG_DVRIP_INFO* pDVRIPInfo);
	void SaveAll(void);
	void CleanAll(void);
	CFG_DVRIP_INFO m_stuDVRIPInfo;
// Dialog Data
	//{{AFX_DATA(CStrategyTrans)
	enum { IDD = IDD_CONFIG_STRATEGY_TRANS };
	CComboBox	m_ccbTrans;
	CButton	m_cbEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStrategyTrans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStrategyTrans)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRATEGYTRANS_H__701DF518_2E68_4FB1_BC81_F29E9BEFB617__INCLUDED_)
