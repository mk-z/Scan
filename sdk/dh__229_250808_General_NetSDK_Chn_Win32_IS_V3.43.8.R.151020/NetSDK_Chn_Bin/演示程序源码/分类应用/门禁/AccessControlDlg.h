// AccessControlDlg.h : header file
//

#if !defined(AFX_ACCESSCONTROLDLG_H__6240938B_BDB6_4D4D_94D3_5D4E34AB289C__INCLUDED_)
#define AFX_ACCESSCONTROLDLG_H__6240938B_BDB6_4D4D_94D3_5D4E34AB289C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define WM_DEVICE_DISCONNECTED	(WM_USER+200)

/////////////////////////////////////////////////////////////////////////////
// CAccessControlDlg dialog

class CAccessControlDlg : public CDialog
{
// Construction
public:
	CAccessControlDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	//{{AFX_DATA(CAccessControlDlg)
	enum { IDD = IDD_ACCESSCONTROL_DIALOG };
	CListBox	m_lstPrint;
	CComboBox	m_cmbControlQueryType;
	CComboBox	m_cmbConfig;
	CIPAddressCtrl	m_DvrIPAddr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccessControlDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAccessControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnDeviceDisconnected(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLogout();
	afx_msg void OnBtnCapability();
	afx_msg void OnBtnSubscibe();
	afx_msg void OnBtnRecordsetControl();
	afx_msg void OnBtnRecordsetFind();
	afx_msg void OnBtnControlQuery();
	afx_msg void OnBtnConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void		InitDlg();
	BOOL		InitNetSDK();
	void		ShowLoginErrorReason(int nError);
	void		PrintInfo(const CString& csInfo);
    BOOL        GetAccessCount(int& nCount);

private:
	// 控制&查询类型
	void		CQofVersion();
	void		CQofReboot();
	void		CQofRestoreAll();
	void		CQofDoor();
	void		CQofLog();
	void		CQofMac();
	void		CQofTime();
	void		CQofUpgrade();
	void		CQofModifyPwd();

private:
	// 配置类型
	void		CFGofNetwork();
	void		CFGofAccessControlGeneral();
	void		CFGofAccessControl();
	void		CFGofAccessTimeSechdule();
	void		CFGofNTP();

private:
	LLONG		m_lLoginID;
	NET_DEVICE_TYPE	m_emType;
	int			m_nVideoInput;
	int			m_nAlarmIn;
	int			m_nAlarmOut;
	int			m_nAccessGroup;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCESSCONTROLDLG_H__6240938B_BDB6_4D4D_94D3_5D4E34AB289C__INCLUDED_)
