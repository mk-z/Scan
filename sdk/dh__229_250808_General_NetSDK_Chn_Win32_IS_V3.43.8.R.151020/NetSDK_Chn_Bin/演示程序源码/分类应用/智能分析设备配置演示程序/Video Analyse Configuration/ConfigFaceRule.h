#if !defined(AFX_CONFIGFACERULE_H__18381DF8_015B_4350_83DA_283E51EB8F05__INCLUDED_)
#define AFX_CONFIGFACERULE_H__18381DF8_015B_4350_83DA_283E51EB8F05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigFaceRule.h : header file
//

#include "ConfigRules.h"
#include "SceneShow.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigFaceRule dialog

class CConfigFaceRule : public CDialog
{
// Construction
public:
	CConfigFaceRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigFaceRule)
	enum { IDD = IDD_COFNIG_FACEDETECT_RULE };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigFaceRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigFaceRule)
	virtual void OnCancel();
	virtual void OnOK();
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
	CFG_FACEDETECT_INFO	m_stuInfo;
	
public:
	void UpdateFalse();
	void GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
		CFG_FACEDETECT_INFO* pInfo, int nChannelId);
	void ShowRuleInfo(void);
	CFG_FACEDETECT_INFO* SaveRuleInfo();
	BOOL RulenameIsExit();
	void SaveLinesInfo(CSceneShow* pSceneShowDlg) ;

	void InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGFACERULE_H__18381DF8_015B_4350_83DA_283E51EB8F05__INCLUDED_)
