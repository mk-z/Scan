#if !defined(AFX_STRATEGYENCRYPTION_H__982D1A8A_C42E_4B4C_9862_F14388F8A9B2__INCLUDED_)
#define AFX_STRATEGYENCRYPTION_H__982D1A8A_C42E_4B4C_9862_F14388F8A9B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StrategyEncryption.h : header file
//
#include "dhnetsdk.h"
#include <string>
/////////////////////////////////////////////////////////////////////////////
// CStrategyEncryption dialog

class CStrategyEncryption : public CDialog
{
// Construction
public:
	CStrategyEncryption(CWnd* pParent = NULL);   // standard constructor
	void GetEncryptionCfg();
	void SetEncryptionCfg();
	// nChannelID 0 == m_ccbChannel CurSel 0
	BOOL SaveChannelKey(int nChannelID);
	void ShowChannelKey(int nChennelID);
	void CleanAll();
	LLONG       m_lLogin;
	int		   m_nChannel;
	int		   m_nChannelPreIndex;
	DHEDV_STREAM_ENCRYPT m_stuEncryption;
// Dialog Data
	//{{AFX_DATA(CStrategyEncryption)
	enum { IDD = IDD_CONFIG_STRATEGY_ENCRYPTION };
	CButton	m_ctlEncrypt;
	CComboBox	m_ccbWorkmode;
	CComboBox	m_ccbKeylength;
	CComboBox	m_ccbEncryption;
	CComboBox	m_ccbChannel;
	int		m_byKey[32];
	//}}AFX_DATA

// 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStrategyEncryption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStrategyEncryption)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnSelendcancelComboChannel();
	afx_msg void OnSelchangeComboEncryption();
	afx_msg void OnSelchangeComboWorkmode();
	afx_msg void OnSelchangeComboKeylength();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRATEGYENCRYPTION_H__982D1A8A_C42E_4B4C_9862_F14388F8A9B2__INCLUDED_)
