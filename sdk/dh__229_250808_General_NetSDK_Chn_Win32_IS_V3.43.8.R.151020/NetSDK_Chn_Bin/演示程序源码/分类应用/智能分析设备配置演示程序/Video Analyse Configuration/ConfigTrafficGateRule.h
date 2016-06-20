#if !defined(AFX_CONFIGTRAFFICGATERULE_H__EAE15FB1_007C_4A69_AE07_D5E0252A1734__INCLUDED_)
#define AFX_CONFIGTRAFFICGATERULE_H__EAE15FB1_007C_4A69_AE07_D5E0252A1734__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigTrafficGateRule.h : header file
//
#include "ConfigRules.h"
#include "SceneShow.h"
typedef list<CDrawObject*>                 LISTLINE;
/////////////////////////////////////////////////////////////////////////////
// CConfigTrafficGateRule dialog

class CConfigTrafficGateRule : public CDialog
{
// Construction
public:
	CConfigTrafficGateRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigTrafficGateRule)
	enum { IDD = IDD_CONFIG_TRAFFICGATE };
	CListCtrl	m_clObjType;
	int		m_nCarWayId;
	CString	m_strRuleName;
	int		m_nSpeedLowerLimit;
	int		m_nSpeedUpperLimit;
	int		m_nSpeedWeight;
	double  m_nMetricDistance;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigTrafficGateRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigTrafficGateRule)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSet();
	afx_msg void OnKillfocusEditRulenameTg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private: 
	CConfigRules* m_pParentWnd;
	long m_lLoginId;
	int m_nCurrentChannel;
	CFG_TRAFFICGATE_INFO m_stuTrafficGateInfo;

	BOOL RulenameIsExit();

public:
	void GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
		CFG_TRAFFICGATE_INFO* pTrafficGateInfo, int nChannelId);
	void ShowRuleInfo(void);
	void UpdateFalse();
	CFG_TRAFFICGATE_INFO* SaveRuleInfo(void);
	void SaveLinesInfo(CSceneShow* pSceneShowDlg);
	void InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGTRAFFICGATERULE_H__EAE15FB1_007C_4A69_AE07_D5E0252A1734__INCLUDED_)
