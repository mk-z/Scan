#if !defined(AFX_ADDUSERINFO_H__10DDAC29_0496_4B06_B170_6B1EE0C641BF__INCLUDED_)
#define AFX_ADDUSERINFO_H__10DDAC29_0496_4B06_B170_6B1EE0C641BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddUserInfo.h : header file
//
#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CAddUserInfo dialog

class CAddUserInfo : public CDialog
{
// Construction
public:
	//To be called by external to initialize whole dialogux box.  
// 	void InitAddUserInfoDlg(USER_MANAGE_INFO_EX *info, DWORD dwID, long hLoginID);
	void InitAddUserInfoDlg(USER_MANAGE_INFO_NEW *info, DWORD dwID, long hLoginID);

	CAddUserInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddUserInfo)
	enum { IDD = IDD_ADD_USER };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddUserInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddUserInfo)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsValid();
	CTreeCtrl	m_treeLevels;
	void InitLevelTree(DWORD dwNum, DWORD *dwList);
	long m_hLoginID;
	DWORD m_dwGroupID;
// 	USER_MANAGE_INFO_EX *m_usersInfo;
	USER_MANAGE_INFO_NEW *m_usersInfoNew;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDUSERINFO_H__10DDAC29_0496_4B06_B170_6B1EE0C641BF__INCLUDED_)
