#if !defined(AFX_CONFIGDLG_H__BFE98169_9128_40CD_AC12_19109F22B457__INCLUDED_)
#define AFX_CONFIGDLG_H__BFE98169_9128_40CD_AC12_19109F22B457__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog
class CSenceCfgdlg;
class CRuleCfgdlg;
class CModuleCfgdlg;
class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor
	void         Init(LLONG lLogHandle);
	void         SetChannelNum(int nChannel);
	int          GetSelectTabPlayPort(void);
	void         OpenChannelStream(void);
	void         CloseStream();
	void         GetConfigInfo();

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_DIALOG_CONFIG };
	CTabCtrl	m_ctlMainTab;
	CComboBox	m_cbChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonSave();
	afx_msg void OnSelchangeTabConfig(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonRead();
	afx_msg void OnSelchangeComboChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void         InitTabControl();
	void         DoTab(int nTab);
	void         SetDlgState(CWnd *pWnd, BOOL bShow);

private:
	int            m_nChannelNum;
	LLONG          m_lLogHandle;
	LLONG          m_lRealPlayHandle;
	int            m_nSelectTab;
	CRITICAL_SECTION  m_csSelectTab;
	int            m_nSelectChannel;
	
	CSenceCfgdlg*  m_pSceneDlg;
	CRuleCfgdlg*   m_pRuleDlg;
	CModuleCfgdlg* m_pModuleDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__BFE98169_9128_40CD_AC12_19109F22B457__INCLUDED_)
