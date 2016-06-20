#if !defined(AFX_MODIFYGROUPINFO_H__94AC029A_B993_4F00_8728_8B4A7822C9A8__INCLUDED_)
#define AFX_MODIFYGROUPINFO_H__94AC029A_B993_4F00_8728_8B4A7822C9A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyGroupInfo.h : header file
//
#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CModifyGroupInfo dialog

class CModifyGroupInfo : public CDialog
{
// Construction
public:
	void InitModifyGroupInfoDlg(USER_MANAGE_INFO_NEW/*USER_MANAGE_INFO_EX*/ *info, DWORD dwGroupID, long hLoginID);
	CModifyGroupInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyGroupInfo)
	enum { IDD = IDD_MODIFY_GROUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyGroupInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyGroupInfo)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsValid();
	void InitLevelTree(DWORD dwNum, DWORD *dwList);
	DWORD m_dwGroupID;
	long m_hLoginID;
	CTreeCtrl m_treeLevels;
// 	USER_MANAGE_INFO_EX *m_usersInfo;
	USER_MANAGE_INFO_NEW *m_usersInfoNew;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYGROUPINFO_H__94AC029A_B993_4F00_8728_8B4A7822C9A8__INCLUDED_)
