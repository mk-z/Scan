#if !defined(AFX_CONFIGFILE_H__9033AA57_746A_474F_AC6B_2D8660E55733__INCLUDED_)
#define AFX_CONFIGFILE_H__9033AA57_746A_474F_AC6B_2D8660E55733__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigFile dialog

class CConfigFile : public CDialog
{
// Construction
public:
	friend void CALLBACK  ImportCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);
	friend void CALLBACK  ExportCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);
public:
	CConfigFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigFile)
	enum { IDD = IDD_DIALOG_CONFIG_FILE };
	CProgressCtrl	m_progressImport;
	CProgressCtrl	m_progressExport;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigFile)
	afx_msg void OnButtonImport();
	afx_msg void OnButtonStopImport();
	afx_msg void OnButtonExport();
	afx_msg void OnButtonStopExport();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnBtnFile();
	afx_msg void OnBtnFolder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_CSFolder;
	CString m_CSFile;
	LONG	m_lImport;
	LONG	m_lExport;

	DWORD	m_dwImportTotalSize;
	DWORD   m_dwImportDownloadSize;
	DWORD	m_dwExportTotalSize;
	DWORD	m_dwExportDownloadSize;

	UINT	m_Timer1;
	UINT	m_Timer2;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGFILE_H__9033AA57_746A_474F_AC6B_2D8660E55733__INCLUDED_)
