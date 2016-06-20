#if !defined(AFX_CONFIGWANDERRULE_H__726F72EC_324B_4020_AAD6_77035E9BFF13__INCLUDED_)
#define AFX_CONFIGWANDERRULE_H__726F72EC_324B_4020_AAD6_77035E9BFF13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigWanderRule.h : header file
//

#include "ConfigRules.h"
#include "SceneShow.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigWanderRule dialog

class CConfigWanderRule : public CDialog
{
// Construction
public:
	CConfigWanderRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigWanderRule)
	enum { IDD = IDD_CONFIG_WANDER_RULE };
	CString	m_strReportInterval;
	CString	m_strTriggerTargetsNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigWanderRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigWanderRule)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonSetRulelinesTg();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString	m_strRuleName;
	BOOL	m_bEnable;
	CListCtrl	m_clObjType;
	
	CConfigRules*		m_pParentWnd;
	long				m_lLoginId;
	int					m_nCurrentChannel;
	CFG_WANDER_INFO		m_stuInfo;
	
public:
	void UpdateFalse();
	void GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
		CFG_WANDER_INFO* pInfo, int nChannelId);
	void ShowRuleInfo(void);
	CFG_WANDER_INFO* SaveRuleInfo();
	BOOL RulenameIsExit();
	void InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY);
	void SaveLinesInfo(CSceneShow* pSceneShowDlg) ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGWANDERRULE_H__726F72EC_324B_4020_AAD6_77035E9BFF13__INCLUDED_)
