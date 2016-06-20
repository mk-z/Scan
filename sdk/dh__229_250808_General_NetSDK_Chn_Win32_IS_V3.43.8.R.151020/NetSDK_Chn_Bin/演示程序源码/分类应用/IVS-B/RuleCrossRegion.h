#if !defined(AFX_RULE3CROSSREGION_H__A11AF369_3983_4AE2_A64D_EAFD0906B0AC__INCLUDED_)
#define AFX_RULE3CROSSREGION_H__A11AF369_3983_4AE2_A64D_EAFD0906B0AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleCrossRegion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleCrossRegion dialog

class CRuleCrossRegion : public CDialog
{
public:
	void initSubDlg();

	//将规则信息显示在子窗口界面上
	void showRuleInfo(RuleStruct* pRuleStruct);
	
	//清除子窗口界面上的信息
	void clearRuleInfo();
	
	//将界面上的信息填充到结构体里
	void setRuleInfo(char* pRuleStruct, int nLen);

private:
	//更新绘图
	void updateDraw();

private:
	CFG_CROSSREGION_INFO* m_pRule;
	
// Construction
public:
	CRuleCrossRegion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRuleCrossRegion)
	enum { IDD = IDD_SUBDLG_RULE03_CROSSREGION };
	CTreeCtrl	m_treeObjType;
	CTreeCtrl	m_treeActionType;
	CComboBox	m_cmbDirection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleCrossRegion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRuleCrossRegion)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickRule3TreeObjtype(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickRule3TreeActiontype(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeRule3CmbDirection();
	afx_msg void OnChangeRule3EdtMintarg();
	afx_msg void OnChangeRule3EdtMaxtarg();
	afx_msg void OnChangeRule3EdtMindur();
	afx_msg void OnChangeRule3EdtReportinterval();
	afx_msg void OnRule3RadioCfilter();
	afx_msg void OnRule3RadioGfilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULE3CROSSREGION_H__A11AF369_3983_4AE2_A64D_EAFD0906B0AC__INCLUDED_)
