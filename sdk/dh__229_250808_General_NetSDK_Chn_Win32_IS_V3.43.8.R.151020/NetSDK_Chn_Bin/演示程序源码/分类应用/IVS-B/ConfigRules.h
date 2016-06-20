#if !defined(AFX_CONFIGRULES_H__BA4C96BC_A6DF_4930_8F29_34B8CDC7937A__INCLUDED_)
#define AFX_CONFIGRULES_H__BA4C96BC_A6DF_4930_8F29_34B8CDC7937A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigRules.h : header file
//

#include "RuleCrossFence.h"
#include "RuleCrossLine.h"
#include "RuleCrossRegion.h"
#include "RuleMove.h"
#include "RuleLeft.h"
#include "RuleParking.h"
#include "RulePreservation.h"
#include "RuleRetrogradation.h"
#include "RuleStay.h"
#include "RuleTakenAway.h"
#include "RuleVideoAbnormal.h"
#include "RuleWander.h"

class CIvsRulePreview;
/////////////////////////////////////////////////////////////////////////////
// CConfigRules dialog

class CConfigRules : public CDialog
{
public:
	void initConfigRulesDlg(int nChannel);
	void uninitConfigRulesDlg();

	void showSubRuleDlg(int nRuleType, BOOL bEnable = TRUE);
	void showSubRuleInfo(int nRuleType, RuleStruct* pRuleStruct);
	
	void showPreview(LONG lLoginHanlde, int nChannel);	
	void closePreview(LONG lRealPlayHandle);
	
	void setRuleTime(DWORD dwType, RuleStruct* pRule);

	static void _stdcall DrawIvsInfoRulesProc(long nPort,HDC hdc,LONG nUser);

	//将窗口上的信息填充到结构体里
//	void setRuleInfo(int nRuleType, char* pRuleStructBuf, int nLen);

	int getDrawPortNum()
	{
		return m_nDrawPortNum;
	}

public:
	friend class CDemoIVSbDlg;
	friend class CConfig;

private:
	CIvsRulePreview* m_pIvsRulePreview;
	BOOL m_bAddRule;

// Construction
public:
	CConfigRules(CWnd* pParent = NULL);   // standard constructor

public:
	CRuleCrossFence m_ruleCrossFence;
	CRuleCrossLine m_ruleCrossLine;
	CRuleCrossRegion m_ruleCrossRegion;
	CRuleMove m_ruleMove;
	CRuleLeft m_ruleLeft;
	CRuleParking m_ruleParking;
	CRulePreservation m_rulePreserv;
	CRuleRetrogradation m_ruleRetro;
	CRuleStay m_ruleStay;
	CRuleTakenAway m_ruleTakeAway;
	CRuleVideoAbnormal m_ruleVideoAbnormal;
	CRuleWander m_ruleWander;

// Dialog Data
	//{{AFX_DATA(CConfigRules)
	enum { IDD = IDD_CONFIG_RULES };
	CTreeCtrl	m_treeRuleList;
	CComboBox	m_cmbRuleType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigRules)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	afx_msg void OnClickCfgruleTreeRulelist(NMHDR* pNMHDR, LRESULT* pResult);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigRules)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCfgruleCmbRuletype();
	afx_msg void OnCfgruleBtnAddrule();
	afx_msg void OnCfgruleBtnDelrule();
	afx_msg void OnCfgruleBtnRedraw();
	afx_msg void OnCfgruleBtnGet();
	afx_msg void OnCfgruleBtnSet();
	afx_msg void OnDblclkCfgruleTreeRulelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnChangeCfgruleEdtRulename();
	afx_msg LRESULT OnRuleDone(WPARAM wParam, LPARAM lPara);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nPlayPortNum;
	int m_nDrawPortNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGRULES_H__BA4C96BC_A6DF_4930_8F29_34B8CDC7937A__INCLUDED_)
