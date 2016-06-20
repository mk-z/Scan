#if !defined(AFX_SUBDLGNUMBERSTATINFO_H__8EB87CC5_96DD_45FD_A287_50D0B2CCFDC6__INCLUDED_)
#define AFX_SUBDLGNUMBERSTATINFO_H__8EB87CC5_96DD_45FD_A287_50D0B2CCFDC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgNumberStatInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubDlgNumberStatInfo dialog

class CSubDlgNumberStatInfo : public CDialog
{
// Construction
public:
	CSubDlgNumberStatInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubDlgNumberStatInfo)
	enum { IDD = IDD_SUBDLG_RULE_NUMBERSTAT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgNumberStatInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	public:
	void InitConfig();
	void ShowRuleInfo(const RuleStruct* pRuleStruct);
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgNumberStatInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl	m_treeObjectType;
public:
	afx_msg void OnBnClickedNumsataBtnDrawdirection();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCbnSelchangeComboNumstatType();
	//afx_msg void OnEnChangeEditPeriod();
	afx_msg void OnEnChangeEditInterval();
	//afx_msg void OnEnChangeEditUpperlimit();
	afx_msg void OnBnClickedBtnRedraw();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickNumstatTreeObjtype(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGNUMBERSTATINFO_H__8EB87CC5_96DD_45FD_A287_50D0B2CCFDC6__INCLUDED_)
