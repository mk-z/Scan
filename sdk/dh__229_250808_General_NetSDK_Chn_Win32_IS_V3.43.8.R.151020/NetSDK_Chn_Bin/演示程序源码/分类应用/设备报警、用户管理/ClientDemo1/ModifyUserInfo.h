#if !defined(AFX_MODIFYUSERINFO_H__F6B387BC_0511_4698_B9ED_4CB0CB985542__INCLUDED_)
#define AFX_MODIFYUSERINFO_H__F6B387BC_0511_4698_B9ED_4CB0CB985542__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyUserInfo.h : header file
//
#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CModifyUserInfo dialog

class CModifyUserInfo : public CDialog
{
// Construction
public:
// 	void InitModifyUserInfoDlg(USER_MANAGE_INFO_EX *info, DWORD dwID, long hLoginID);
	void InitModifyUserInfoDlg(USER_MANAGE_INFO_NEW *info, DWORD dwID, long hLoginID);
	CModifyUserInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyUserInfo)
	enum { IDD = IDD_MODIFY_USER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyUserInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyUserInfo)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsValid();
	void InitLevelTree(DWORD dwNum, DWORD *dwList);
// 	USER_MANAGE_INFO_EX *m_usersInfo;
	USER_MANAGE_INFO_NEW *m_usersInfoNew;
	CTreeCtrl m_treeLevels;
	long m_hLoginID;
	DWORD m_dwUserID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYUSERINFO_H__F6B387BC_0511_4698_B9ED_4CB0CB985542__INCLUDED_)
