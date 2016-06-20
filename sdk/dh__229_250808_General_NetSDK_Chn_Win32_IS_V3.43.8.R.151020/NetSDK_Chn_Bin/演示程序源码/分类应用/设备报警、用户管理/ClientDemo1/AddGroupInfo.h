#if !defined(AFX_ADDGROUPINFO_H__15946057_7B77_4E1F_BBEE_F8A9F5A8A719__INCLUDED_)
#define AFX_ADDGROUPINFO_H__15946057_7B77_4E1F_BBEE_F8A9F5A8A719__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddGroupInfo.h : header file
//
#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CAddGroupInfo dialog

class CAddGroupInfo : public CDialog
{
// Construction
public:
// 	void InitAddGroupDlg(USER_MANAGE_INFO_EX *info, long hLoginID);
	void InitAddGroupDlg(USER_MANAGE_INFO_NEW *info, long hLoginID);
	
	CAddGroupInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddGroupInfo)
	enum { IDD = IDD_ADD_GROUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddGroupInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddGroupInfo)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsValid();
	LLONG m_hLoginID;
	CTreeCtrl m_treeLevels;
// 	USER_MANAGE_INFO_EX *m_usersInfo;
	USER_MANAGE_INFO_NEW *m_usersInfoNew;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDGROUPINFO_H__15946057_7B77_4E1F_BBEE_F8A9F5A8A719__INCLUDED_)
