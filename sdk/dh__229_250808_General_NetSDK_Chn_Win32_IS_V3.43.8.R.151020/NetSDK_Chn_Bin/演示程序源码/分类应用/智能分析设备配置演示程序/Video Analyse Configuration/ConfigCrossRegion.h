#if !defined(AFX_CONFIGCROSSREGION_H__2B48235B_0243_4C9F_A094_766140D20A38__INCLUDED_)
#define AFX_CONFIGCROSSREGION_H__2B48235B_0243_4C9F_A094_766140D20A38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigCrossRegion.h : header file
//
#include "ConfigRules.h"
#include "SceneShow.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigCrossRegion dialog

class CConfigCrossRegion : public CDialog
{
// Construction
public:
	CConfigCrossRegion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigCrossRegion)
	enum { IDD = IDD_CONFIG_CROSSREGION_RULE };
	CComboBox	m_comboDirection;
	CComboBox	m_comboActionType;
	CString	m_strMaxTargets;
	CString	m_strMinDuration;
	CString	m_strMinTartgets;
	CString	m_strReportInterval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigCrossRegion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigCrossRegion)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonSetRulelinesTg();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboActiontypeTg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CFG_CROSSREGION_INFO m_stuInfo;

	CString	m_strRuleName;
	BOOL	m_bEnable;
	CListCtrl	m_clObjType;

	CConfigRules*		m_pParentWnd;
	long				m_lLoginId;
	int					m_nCurrentChannel;
public:
	void GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
		CFG_CROSSREGION_INFO* pInfo, int nChannelId);
	void ShowRuleInfo(void);
	void UpdateFalse();
	CFG_CROSSREGION_INFO* SaveRuleInfo();
	BOOL RulenameIsExit();
	void InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY);
	void SaveLinesInfo(CSceneShow* pSceneShowDlg) ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCROSSREGION_H__2B48235B_0243_4C9F_A094_766140D20A38__INCLUDED_)
