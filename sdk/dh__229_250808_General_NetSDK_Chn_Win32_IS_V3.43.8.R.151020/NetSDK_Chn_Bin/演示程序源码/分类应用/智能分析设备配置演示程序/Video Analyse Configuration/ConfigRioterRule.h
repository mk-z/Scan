#if !defined(AFX_CONFIGRIOTERRULE_H__4F8B574A_40BD_4DDF_B22A_E6C7EB23851D__INCLUDED_)
#define AFX_CONFIGRIOTERRULE_H__4F8B574A_40BD_4DDF_B22A_E6C7EB23851D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigRioterRule.h : header file
//

#include "ConfigRules.h"
#include "SceneShow.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigRioterRule dialog

class CConfigRioterRule : public CDialog
{
// Construction
public:
	CConfigRioterRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigRioterRule)
	enum { IDD = IDD_CONFIG_RIOTER_RULE };
	CString	m_strAreaPercent;
	CString	m_strMinDuration;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigRioterRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigRioterRule)
	virtual void OnCancel();
	virtual void OnOK();
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
	CFG_RIOTER_INFO		m_stuInfo;
	
public:
	void UpdateFalse();
	void GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
		CFG_RIOTER_INFO* pInfo, int nChannelId);
	void ShowRuleInfo(void);
	CFG_RIOTER_INFO* SaveRuleInfo();
	BOOL RulenameIsExit();
	void InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY);
	void SaveLinesInfo(CSceneShow* pSceneShowDlg) ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGRIOTERRULE_H__4F8B574A_40BD_4DDF_B22A_E6C7EB23851D__INCLUDED_)
