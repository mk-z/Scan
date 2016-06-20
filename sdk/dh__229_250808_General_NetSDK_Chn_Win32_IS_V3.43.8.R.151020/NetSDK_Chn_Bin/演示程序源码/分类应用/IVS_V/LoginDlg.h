#if !defined(AFX_LOGINDLG_H__0E36A5FA_F7E1_4FFC_AF50_9AB339053294__INCLUDED_)
#define AFX_LOGINDLG_H__0E36A5FA_F7E1_4FFC_AF50_9AB339053294__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//
#include <VECTOR>
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{
// Construction
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	CLoginDlg(std::vector<BYTE> * pvecDvrType, std::vector<BYTE> * pvecDvrTypeOut, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_DLG_LOGIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	static int Logout(DWORD hLoginID);
	inline DWORD GetLoginHandle() { return m_hLoginID; }
	inline NET_DEVICEINFO &GetDevInfo() { return m_stDevInfo; }
	inline CFG_TASK_REMOTEDEVICE &GetLoginInfo() { return m_stDevLoginInfo; }
private:
	/// 登陆句柄
	LLONG         m_hLoginID;
	/// 设备信息
	NET_DEVICEINFO m_stDevInfo;
	/// 设备类型
	std::vector<BYTE>     *m_pvecDvrType; 
	std::vector<BYTE>     *m_pvecDvrTypeOut; 
	/// 设备登陆信息
	CFG_TASK_REMOTEDEVICE  m_stDevLoginInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__0E36A5FA_F7E1_4FFC_AF50_9AB339053294__INCLUDED_)
