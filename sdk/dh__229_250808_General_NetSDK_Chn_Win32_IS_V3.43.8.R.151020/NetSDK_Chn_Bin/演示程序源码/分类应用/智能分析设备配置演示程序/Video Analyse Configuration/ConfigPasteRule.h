#if !defined(AFX_CONFIGPASTERULE_H__29854094_9258_45A8_BC8D_13D6B7C859B8__INCLUDED_)
#define AFX_CONFIGPASTERULE_H__29854094_9258_45A8_BC8D_13D6B7C859B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigPasteRule.h : header file
//

#include "ConfigRules.h"
#include "SceneShow.h"

/////////////////////////////////////////////////////////////////////////////
// CConfigPasteRule dialog

class CConfigPasteRule : public CDialog
{
// Construction
public:
	CConfigPasteRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigPasteRule)
	enum { IDD = IDD_CONFIG_PASTE_RULE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigPasteRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigPasteRule)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnSetRulelinesTg();
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
	CFG_PASTE_INFO		m_stuInfo;
	
public:
	void UpdateFalse();
	void GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
		CFG_PASTE_INFO* pInfo, int nChannelId);
	void ShowRuleInfo(void);
	CFG_PASTE_INFO* SaveRuleInfo();
	BOOL RulenameIsExit();

	void SaveLinesInfo(CSceneShow* pSceneShowDlg) ;
	void InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGPASTERULE_H__29854094_9258_45A8_BC8D_13D6B7C859B8__INCLUDED_)
