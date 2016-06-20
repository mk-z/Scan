#if !defined(AFX_SWITCH_H__DC5B70B1_2B6D_410D_9A7D_67C225BE82F0__INCLUDED_)
#define AFX_SWITCH_H__DC5B70B1_2B6D_410D_9A7D_67C225BE82F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Switch.h : header file
//

class CRuleTreeCtrl;

/////////////////////////////////////////////////////////////////////////////
// CSwitch dialog

class CSwitch : public CDialog
{
private:
	HTREEITEM m_hSelectItem;
	int m_nChnCount;

// Construction
public:
	CSwitch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSwitch)
	enum { IDD = IDD_SWITCH };
	CTreeCtrl	m_treeChn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSwitch)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickSwitchTreeChn(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnSwitchBtnChnselall();
	afx_msg void OnSwitchBtnChncountersel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCH_H__DC5B70B1_2B6D_410D_9A7D_67C225BE82F0__INCLUDED_)
