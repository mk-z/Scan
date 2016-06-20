#if !defined(AFX_MACFILTEDLG_H__A1D26084_4C0E_493E_90EC_882EFAB16637__INCLUDED_)
#define AFX_MACFILTEDLG_H__A1D26084_4C0E_493E_90EC_882EFAB16637__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MacFilteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMacFilteDlg dialog

class CMacFilteDlg : public CDialog
{
// Construction
public:
	CMacFilteDlg(CWnd* pParent = NULL);   // standard constructor

	void GetMacFilterCfg();
	void SetMacFilterCfg();
	
	LLONG       m_lLogin;     // 登陆句柄
	bool	IsVlidateMac(char* strMac, CListBox& listbox);
	bool	IsValidityMacTolower(char* mac);
	// mac是否存在
	bool IsMacHas(char* strMac, CListBox& listbox);

// Dialog Data
	//{{AFX_DATA(CMacFilteDlg)
	enum { IDD = IDD_CONFIG_STRATEGY_MACFILTER };
	CEdit	m_editBlackMac;
	CEdit	m_editWhiteMac;
	CListBox	m_blackList;
	CListBox	m_whiteList;
	BOOL		m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMacFilteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMacFilteDlg)
	afx_msg void OnBtnMacInput();
	afx_msg void OnBtnWhiteAdd();
	afx_msg void OnBtnWhiteDel();
	afx_msg void OnBtnBlackAdd();
	afx_msg void OnBtnBlackDel();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioWhiteMac();
	afx_msg void OnRadioBlackMac();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL       m_bWhite;                     // 是否为白名单
	//DHDEV_MACFILTER_CFG	m_stuMacFilterCfg;    //  ip过滤配置
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACFILTEDLG_H__A1D26084_4C0E_493E_90EC_882EFAB16637__INCLUDED_)
