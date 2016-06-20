#if !defined(AFX_CONFIGCROSSLINERULE_H__E117137E_5665_4625_A7D1_31293D3E3B90__INCLUDED_)
#define AFX_CONFIGCROSSLINERULE_H__E117137E_5665_4625_A7D1_31293D3E3B90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigCrossLineRule.h : header file
//

#include "ConfigRules.h"
#include "SceneShow.h"

/////////////////////////////////////////////////////////////////////////////
// CConfigCrossLineRule dialog

class CConfigCrossLineRule : public CDialog
{
// Construction
public:
	CConfigCrossLineRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigCrossLineRule)
	enum { IDD = IDD_COFNIG_CROSSLINE_RULE };
	CString	m_strRuleName;
	BOOL	m_bEnable;
	CListCtrl	m_clObjType;
	CString	m_strDirection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigCrossLineRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigCrossLineRule)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetRulelinesTg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CConfigRules*		m_pParentWnd;
	long				m_lLoginId;
	int					m_nCurrentChannel;
	CFG_CROSSLINE_INFO	m_stuInfo;

public:
	void UpdateFalse();
	void GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
		CFG_CROSSLINE_INFO* pInfo, int nChannelId);
	void ShowRuleInfo(void);
	CFG_CROSSLINE_INFO* SaveRuleInfo();
	BOOL RulenameIsExit();
	void InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY);
	void SaveLinesInfo(CSceneShow* pSceneShowDlg) ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCROSSLINERULE_H__E117137E_5665_4625_A7D1_31293D3E3B90__INCLUDED_)
