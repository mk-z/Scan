#if !defined(AFX_RULE8RETROGRADATION_H__EADCBA6C_F34D_42EA_BDAF_096CDB5D1914__INCLUDED_)
#define AFX_RULE8RETROGRADATION_H__EADCBA6C_F34D_42EA_BDAF_096CDB5D1914__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleRetrogradation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleRetrogradation dialog

class CRuleRetrogradation : public CDialog
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
	CFG_RETROGRADEDETECTION_INFO* m_pRule;

// Construction
public:
	CRuleRetrogradation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRuleRetrogradation)
	enum { IDD = IDD_SUBDLG_RULE08_RETROGRA };
	CComboBox	m_cmbTriggerPos;
	CSliderCtrl	m_slidSensi;
	CTreeCtrl	m_treeObjType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleRetrogradation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRuleRetrogradation)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickRule8TreeObjtype(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeRule8CmbTriggerpos();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRule8RadioCfilter();
	afx_msg void OnRule8RadioGfilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULE8RETROGRADATION_H__EADCBA6C_F34D_42EA_BDAF_096CDB5D1914__INCLUDED_)
