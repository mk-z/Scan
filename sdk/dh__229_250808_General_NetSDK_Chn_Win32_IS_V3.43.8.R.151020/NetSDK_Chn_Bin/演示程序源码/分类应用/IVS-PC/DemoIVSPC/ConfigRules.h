#if !defined(AFX_CONFIGRULES_H__BA4C96BC_A6DF_4930_8F29_34B8CDC7937A__INCLUDED_)
#define AFX_CONFIGRULES_H__BA4C96BC_A6DF_4930_8F29_34B8CDC7937A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigRules.h : header file
//
#include "DemoIVSPC.h"


class CDemoIVSPCDlg;
class CIvsRulePreview;
class CSubDlgNumberStatInfo;

/////////////////////////////////////////////////////////////////////////////
// CConfigRules dialog

class CConfigRules : public CDialog
{
public:
	CConfigRules(CWnd* pParent = NULL);   // standard constructor

	void InitConfigRulesDlg(int nChannel);
	void UninitConfigRulesDlg();

	void ShowSubRuleDlg(int nRuleType);
	void ShowSubRuleInfo(int nRuleType, const RuleStruct* pRuleStruct);

	void ShowPreview(LONG lLoginHanlde, int nChannel);	
	void ClosePreview(LONG lRealPlayHandle);

	static void _stdcall DrawIvsInfoRulesProc(long nPort,HDC hdc,LONG nUser);

	void InitRule(CDemoIVSPCDlg* pMainDlg, int nChannel);
	void InitRuleInfo(HTREEITEM hItem);
	//将窗口上的信息填充到结构体里
	void SetRuleInfo(int nRuleType, char* pRuleStructBuf, int nLen);

	BOOL CopyNumberStatInfo(const CFG_ANALYSERULES_INFO *pInput, CFG_ANALYSERULES_INFO *pOutput);

	inline int GetDrawPortNum(){return m_nDrawPortNum;}

	CWnd * GetDrawRuleHandle();
	void CreateViewWindow();

	enum { IDD = IDD_CONFIG_RULES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

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
	afx_msg LRESULT OnRuleDarwHint(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeCfgruleEdtRulename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CComboBox	m_cmbRuleType;
	CTreeCtrl	m_treeRuleList;
	int m_nDrawPortNum;
	CIvsRulePreview *m_pIvsRulePreview;
    /// \var int m_nDrawType
	/// 绘制类型
	int m_nDrawType; // -1;不需要绘制，0：绘制区域，1：绘制方向 

	CSubDlgNumberStatInfo *m_pSubNumberStatInfo;
	
};

#endif // !defined(AFX_CONFIGRULES_H__BA4C96BC_A6DF_4930_8F29_34B8CDC7937A__INCLUDED_)
