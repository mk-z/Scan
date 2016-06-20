#if !defined(AFX_RULE2CROSSLINE_H__6F25704B_E0BB_4736_9929_99C12F75C708__INCLUDED_)
#define AFX_RULE2CROSSLINE_H__6F25704B_E0BB_4736_9929_99C12F75C708__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleCrossLine.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleCrossLine dialog

class CRuleCrossLine : public CDialog
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
	CFG_CROSSLINE_INFO* m_pRule;

// Construction
public:
	CRuleCrossLine(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRuleCrossLine)
	enum { IDD = IDD_SUBDLG_RULE02_CROSSLINE };
	CTreeCtrl	m_treeObjType;
	CComboBox	m_cmbTriggerPos;
	CComboBox	m_cmbDirection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleCrossLine)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRuleCrossLine)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeRule2CmbDirection();
	afx_msg void OnSelchangeRule2CmbTriggerpos();
	afx_msg void OnClickRule2TreeObjtype(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRule2RadioGfilter();
	afx_msg void OnRule2RadioCfilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULE2CROSSLINE_H__6F25704B_E0BB_4736_9929_99C12F75C708__INCLUDED_)
