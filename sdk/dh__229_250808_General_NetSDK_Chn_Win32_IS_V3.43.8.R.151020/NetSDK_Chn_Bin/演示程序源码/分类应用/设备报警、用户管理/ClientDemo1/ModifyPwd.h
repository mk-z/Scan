#if !defined(AFX_MODIFYPWD_H__E2A7D06B_17A7_4A1C_9E6A_88B6D5E63FEC__INCLUDED_)
#define AFX_MODIFYPWD_H__E2A7D06B_17A7_4A1C_9E6A_88B6D5E63FEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyPwd.h : header file
//
#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CModifyPwd dialog

class CModifyPwd : public CDialog
{
// Construction
public:
//	void InitModifyPwdInfoDlg(USER_MANAGE_INFO_EX *info, DWORD dwID, long hLoginID);
	void InitModifyPwdInfoDlg(USER_MANAGE_INFO_NEW *info, DWORD dwID, long hLoginID);
	
	CModifyPwd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyPwd)
	enum { IDD = IDD_MODIFY_PWD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyPwd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyPwd)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsValid();
	DWORD m_dwUserID;
	long m_hLoginID;
//	USER_MANAGE_INFO_EX *m_usersInfo;
	USER_MANAGE_INFO_NEW *m_usersInfoNew;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYPWD_H__E2A7D06B_17A7_4A1C_9E6A_88B6D5E63FEC__INCLUDED_)
