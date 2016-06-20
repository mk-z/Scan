#if !defined(AFX_RULE4MOVE_H__11A3F3D1_D3A2_4791_AB99_5DD88052E261__INCLUDED_)
#define AFX_RULE4MOVE_H__11A3F3D1_D3A2_4791_AB99_5DD88052E261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleMove.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleMove dialog

class CRuleMove : public CDialog
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
	CFG_MOVE_INFO* m_pRule;
	// 检测类型 目前只支持第一种
	char m_szArrDetectType[3][MAX_NAME_LEN];

// Construction
public:
	CRuleMove(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRuleMove)
	enum { IDD = IDD_SUBDLG_RULE04_MOVE };
	CSliderCtrl	m_slidSensi;
	CTreeCtrl	m_treeDetectType;
	CTreeCtrl	m_treeObjType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleMove)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRuleMove)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickRule4TreeObjtype(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeRule4EdtMindur();
	afx_msg void OnClickRule4TreeDetecttype(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRule4RadioCfilter();
	afx_msg void OnRule4RadioGfilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULE4MOVE_H__11A3F3D1_D3A2_4791_AB99_5DD88052E261__INCLUDED_)
