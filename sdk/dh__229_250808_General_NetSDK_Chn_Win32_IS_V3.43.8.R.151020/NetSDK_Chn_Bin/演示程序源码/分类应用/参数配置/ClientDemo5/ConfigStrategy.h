#if !defined(AFX_CONFIGSTRATEGY_H__7CE4C30A_8837_45F0_933D_D9DEF82A371A__INCLUDED_)
#define AFX_CONFIGSTRATEGY_H__7CE4C30A_8837_45F0_933D_D9DEF82A371A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigStrategy.h : header file
#include "StrategyTrans.h"
#include "StrategyDownload.h"
#include "StrategyEncryption.h"
#include "IPFileterDlg.h"
#include "dhnetsdk.h"
#include "MacFilteDlg.h"
//

/////////////////////////////////////////////////////////////////////////////
// CConfigStrategy dialog

class CConfigStrategy : public CDialog
{
// Construction
public:
	CConfigStrategy(CWnd* pParent = NULL);   // standard constructor
	CStrategyDownload m_StrategyDownload;
	CStrategyTrans	  m_StrategyTrans;
	CIPFileterDlg     m_StrategyIPFileter;
	CStrategyEncryption m_StrategyEncryption;
	//CMacFilteDlg	  m_StrategyMacFilter;
	void CleanAll();
// Dialog Data
	//{{AFX_DATA(CConfigStrategy)
	enum { IDD = IDD_CONFIG_STRATEGY };
	CTabCtrl	m_tabStrategy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigStrategy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	void InitTabCtl(void);
	void SetDlgState(CWnd *pWnd, BOOL bShow);
	void DoTab(int nTab);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigStrategy)
	afx_msg void OnButtonApply();
	afx_msg void OnButtonLoad();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnSelchangeTabStrategy(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGSTRATEGY_H__7CE4C30A_8837_45F0_933D_D9DEF82A371A__INCLUDED_)
