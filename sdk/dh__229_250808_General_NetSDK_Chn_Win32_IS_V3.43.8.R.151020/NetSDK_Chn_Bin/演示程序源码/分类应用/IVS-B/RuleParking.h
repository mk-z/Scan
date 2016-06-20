#if !defined(AFX_RULE6PARKING_H__8BF13424_4192_4E75_8DCA_B904B25AEA38__INCLUDED_)
#define AFX_RULE6PARKING_H__8BF13424_4192_4E75_8DCA_B904B25AEA38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleParking.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleParking dialog

class CRuleParking : public CDialog
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
	CFG_PARKINGDETECTION_INFO* m_pRule;

// Construction
public:
	CRuleParking(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRuleParking)
	enum { IDD = IDD_SUBDLG_RULE06_PARKING };
	CComboBox	m_cmbTriggerPos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleParking)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRuleParking)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeRule6CmbTriggerpos();
	afx_msg void OnChangeRule6EdtMindur();
	afx_msg void OnRule6RadioCfilter();
	afx_msg void OnRule6RadioGfilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULE6PARKING_H__8BF13424_4192_4E75_8DCA_B904B25AEA38__INCLUDED_)
