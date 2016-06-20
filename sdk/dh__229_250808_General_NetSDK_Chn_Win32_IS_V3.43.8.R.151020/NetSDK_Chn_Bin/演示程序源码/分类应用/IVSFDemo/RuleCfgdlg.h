#if !defined(AFX_RULECFGDLG_H__A0ACBD7B_DEAA_4790_A335_529022453C42__INCLUDED_)
#define AFX_RULECFGDLG_H__A0ACBD7B_DEAA_4790_A335_529022453C42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleCfgdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleCfgdlg dialog

class CRuleCfgdlg : public CDialog
{
// Construction
public:
	CRuleCfgdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRuleCfgdlg)
	enum { IDD = IDD_DIALOG_CFG_RULE };
	CComboBox	m_cbMode;
	int		m_nAccuracy;
	int		m_nImportantRank;
	int		m_nMaxCandidate;
	CString	m_strRuleName;
	int		m_nSimilarity;
	BOOL	m_bEye;
	BOOL	m_bEyeBrow;
	BOOL	m_bFace;
	BOOL	m_bMouth;
	BOOL	m_bNose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleCfgdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRuleCfgdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void           ShowRuleInfo(CFG_FACERECOGNITION_INFO* pRuleInfo);
	void           SaveRuleInfo(CFG_FACERECOGNITION_INFO* pRuleInfo);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULECFGDLG_H__A0ACBD7B_DEAA_4790_A335_529022453C42__INCLUDED_)
