#if !defined(AFX_DECODEPOLICYDLG_H__55D8117D_EBF3_4750_80AC_F7E4ADF700AE__INCLUDED_)
#define AFX_DECODEPOLICYDLG_H__55D8117D_EBF3_4750_80AC_F7E4ADF700AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DecodePolicyDlg.h : header file
//
#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// DecodePolicyDlg dialog

class DecodePolicyDlg : public CDialog
{
// Construction
public:
	DecodePolicyDlg(CWnd* pParent = NULL);   // standard constructor
	void SetDlgParam(LONG lLoginID);
	int m_nDecChannel;
	int m_lLoginID;
// Dialog Data
	//{{AFX_DATA(DecodePolicyDlg)
	enum { IDD = IDD_DLG_DECODEPOLICY };
	CComboBox	m_cbChannelID;
	CString	m_strTimeRegion;
	int		m_nDecodeTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DecodePolicyDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	DHDEV_DECODEPOLICY_CFG m_stuDecodePolicy;
	// Generated message map functions
	//{{AFX_MSG(DecodePolicyDlg)
	afx_msg void OnButtonSave();
	afx_msg void OnButtonRefresh();
	afx_msg void OnSelchangeComboChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECODEPOLICYDLG_H__55D8117D_EBF3_4750_80AC_F7E4ADF700AE__INCLUDED_)
