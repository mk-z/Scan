#if !defined(AFX_IPFILETERDLG_H__682A0F8A_962E_47AC_8A99_A9425686E6E7__INCLUDED_)
#define AFX_IPFILETERDLG_H__682A0F8A_962E_47AC_8A99_A9425686E6E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPFileterDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIPFileterDlg dialog

class CIPFileterDlg : public CDialog
{
// Construction
public:
	CIPFileterDlg(CWnd* pParent = NULL);   // standard constructor

	void GetIPFilterCfg();
	void SetIPFilterCfg();
	void ClearAll();
	LLONG       m_lLogin;     // µÇÂ½¾ä±ú

// Dialog Data
	//{{AFX_DATA(CIPFileterDlg)
	enum { IDD = IDD_CONFIG_STRATEGY_IPFILTER };
	CIPAddressCtrl	m_ctlBlackIP;
	CIPAddressCtrl	m_ctlWhiteIP;
	CListBox	m_lsBlack;
	CListBox	m_lsWhite;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPFileterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIPFileterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonWlBrow();
	afx_msg void OnButtonAddWhite();
	afx_msg void OnButtonDelWhite();
	afx_msg void OnButtonAddBlack();
	afx_msg void OnButtonDelBlack();
	afx_msg void OnRadioBlack();
	afx_msg void OnRadioWhite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL       m_bWhite;                     // ÊÇ·ñÎª°×Ãûµ¥
	DHDEV_IPIFILTER_CFG	m_stuIPFilterCfg;    //  ip¹ýÂËÅäÖÃ
    AV_CFG_AccessFilter* m_pstuAccessFilter;   // IP¹ýÂËÅäÖÃ
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPFILETERDLG_H__682A0F8A_962E_47AC_8A99_A9425686E6E7__INCLUDED_)
