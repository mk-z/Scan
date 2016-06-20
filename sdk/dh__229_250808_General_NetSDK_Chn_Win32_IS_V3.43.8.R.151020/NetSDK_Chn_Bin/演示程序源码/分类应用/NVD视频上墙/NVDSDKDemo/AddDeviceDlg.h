#if !defined(AFX_ADDDEVICEDLG_H__B10609C7_400D_47C0_B9E9_1EA2D6194F83__INCLUDED_)
#define AFX_ADDDEVICEDLG_H__B10609C7_400D_47C0_B9E9_1EA2D6194F83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddDeviceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddDeviceDlg dialog

class CAddDeviceDlg : public CDialog
{
// Construction
public:
	CAddDeviceDlg(CWnd* pParent = NULL);   // standard constructor

public:
	LONG m_lLoginHandle;
	int m_nMonitorNum;
	DWORD m_dwStreamType;

// Dialog Data
	//{{AFX_DATA(CAddDeviceDlg)
	enum { IDD = IDD_DLG_ADD_DEVICE };
	CString	m_strDevIp;
	CString	m_strDevName;
	UINT	m_nDevPort;
	CString	m_strDevPwd;
	CString	m_strDevUser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddDeviceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddDeviceDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	void ShowLoginErrorReason(int nError);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDDEVICEDLG_H__B10609C7_400D_47C0_B9E9_1EA2D6194F83__INCLUDED_)
