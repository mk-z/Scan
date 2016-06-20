#if !defined(AFX_TABUSERMANAGEDLG_H__AD2D5CB1_80FE_49FF_976D_47D03ACF4EF8__INCLUDED_)
#define AFX_TABUSERMANAGEDLG_H__AD2D5CB1_80FE_49FF_976D_47D03ACF4EF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabUserManageDlg.h : header file
//
#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CTabUserManageDlg dialog

class CTabUserManageDlg : public CDialog
{
// Construction
public:
	//To be called by CClientDemo1Dlg. Clear dialogue box after device logged off. 
	void CleanUserManageInfo();
	//To be called by CClientDemo1Dlg. Call this interface to initialize whole dialogux box after logged in the device. 
	void InitUserManageInfo(long hLoginID);

	CTabUserManageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabUserManageDlg)
	enum { IDD = IDD_DIALOG_USERMANAGE };
	CTreeCtrl	m_treeLevels;
	CTreeCtrl	m_treeUsers;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabUserManageDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabUserManageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeUsers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddUser();
	afx_msg void OnModifyUser();
	afx_msg void OnDeleteUser();
	afx_msg void OnModifyPsw();
	afx_msg void OnAddGroup();
	afx_msg void OnDeleteGroup();
	afx_msg void OnModifyGroup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_hLoginID;
	void RefreshLevelList ();
	void InitTree();
// 	USER_MANAGE_INFO_EX m_usersInfo;
	USER_MANAGE_INFO_NEW m_usersInfoNew;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABUSERMANAGEDLG_H__AD2D5CB1_80FE_49FF_976D_47D03ACF4EF8__INCLUDED_)
