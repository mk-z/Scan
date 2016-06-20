#if !defined(AFX_CONFIGFTPEX_H__CB33BDDC_B5A8_439E_8CC3_565B05227CCC__INCLUDED_)
#define AFX_CONFIGFTPEX_H__CB33BDDC_B5A8_439E_8CC3_565B05227CCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigFTPEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigFTPEx dialog

class CConfigFTPEx : public CDialog
{
// Construction
public:
	CConfigFTPEx(CWnd* pParent = NULL);   // standard constructor
	
	CFG_NAS_INFO_EX *m_pstuNasInfoEx;
	void InitDlgInfo();
	void CleanAll();
	void InitListView();
	void ShowFtpEx(CFG_NAS_INFO_EX *m_pstuNasInfo);
	void InsertListView(CString strIndex, CString strEnable, CString strName, CString strPortocol, CString strAddress,
		CString strPort, CString strUser, CString strPassword, CString strDirectory, CString strEncoding);
	void SaveFtpExInfo(CFG_NAS_INFO_EX *m_pstuNasInfo);


// Dialog Data
	//{{AFX_DATA(CConfigFTPEx)
	enum { IDD = IDD_CONFIG_FTPEX };
	CButton	m_ctlEnable;
	CListCtrl	m_ctlFtpEx;
	CComboBox	m_ctlPortocol;
	CComboBox	m_ctlEncoding;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigFTPEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigFTPEx)
	afx_msg void OnButtonSave();
	afx_msg void OnButtonRead();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonModify();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedListFtpex(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGFTPEX_H__CB33BDDC_B5A8_439E_8CC3_565B05227CCC__INCLUDED_)
