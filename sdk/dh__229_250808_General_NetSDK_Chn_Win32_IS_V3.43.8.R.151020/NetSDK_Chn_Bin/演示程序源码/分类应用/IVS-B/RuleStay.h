#if !defined(AFX_RULE9STAY_H__71579613_53A3_42BD_A7A0_646971F4FA0C__INCLUDED_)
#define AFX_RULE9STAY_H__71579613_53A3_42BD_A7A0_646971F4FA0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleStay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleStay dialog

class CRuleStay : public CDialog
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
	CFG_STAY_INFO* m_pRule;

// Construction
public:
	CRuleStay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRuleStay)
	enum { IDD = IDD_SUBDLG_RULE09_STAY };
	CTreeCtrl	m_treeObjType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleStay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRuleStay)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickRule9TreeObjtype(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeRule9EdtMindur();
	afx_msg void OnChangeRule9EdtReportinterval();
	afx_msg void OnRule9RadioCfilter();
	afx_msg void OnRule9RadioGfilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULE9STAY_H__71579613_53A3_42BD_A7A0_646971F4FA0C__INCLUDED_)
