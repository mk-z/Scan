#if !defined(AFX_LOGINDLG_H__E6B6827D_DC08_4A90_ACAC_CE7CE921C96B__INCLUDED_)
#define AFX_LOGINDLG_H__E6B6827D_DC08_4A90_ACAC_CE7CE921C96B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

#define MSG_ERROR_PASSWORD			"Incorrect Password"
#define MSG_ERROR_USER				"User not Exist"
#define MSG_ERROR_TIMEOUT			"Login Timeout"
#define MSG_ERROR_RELOGGIN			"Curent User Has Logined"
#define MSG_ERROR_LOCKED			"Curent User Locked"
#define MSG_ERROR_BLACKLIST			"Curent User Invalid"
#define MSG_ERROR_BUSY				"System Busy"
#define MSG_ERROR_CONNECT			"Cant find host"
#define MSG_ERROR_OVER_MAX_CONNECT  "over max connect"
#define MSG_ERROR_NETWORK			"Network Error"

class CLoginDlg : public CDialog
{
// Construction
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor

	LLONG GetLogHandle(){ return m_lLogHandle; }
	BYTE GetChannelCount(){ return m_stDevInfo.byChanNum; }
	BYTE GetDevType(){ return m_stDevInfo.byDVRType; }
// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_DIALOG_DEVLOGIN };
	CString	m_strIP;
	CString	m_strPassWord;
	int		m_nPort;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	afx_msg void OnButtonLogin();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonLogout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CLoginDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	LLONG                m_lLogHandle;
	NET_DEVICEINFO      m_stDevInfo;

	void GetConnectError(int error);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__E6B6827D_DC08_4A90_ACAC_CE7CE921C96B__INCLUDED_)
