// UserManage.cpp : implementation file
//

#include "StdAfx.h"
#include "netsdkdemo.h"
#include "netsdkdemodlg.h"
#include "UserManage.h"
#include "User_AddUser.h"
#include "USER_AddGroup.h"
#include "USER_ModifyUser.h"
#include "USER_ModifyGroup.h"
#include "USER_ModifyPsw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserManage dialog


CUserManage::CUserManage(CWnd* pParent /*=NULL*/)
	: CDialog(CUserManage::IDD, pParent)
{
	memset(&m_user_info, 0, sizeof(USER_MANAGE_INFO_EX));
	//{{AFX_DATA_INIT(CUserManage)
	//}}AFX_DATA_INIT
}


void CUserManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserManage)
	DDX_Control(pDX, IDC_USERLIST_TREE, m_userList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserManage, CDialog)
	//{{AFX_MSG_MAP(CUserManage)
	ON_BN_CLICKED(IDC_ADD_USER, OnAddUser)
	ON_BN_CLICKED(IDC_MODIFY_USER, OnModifyUser)
	ON_BN_CLICKED(IDC_ADD_GROUP, OnAddGroup)
	ON_BN_CLICKED(IDC_DELETE_USER, OnDeleteUser)
	ON_BN_CLICKED(IDC_MODIFY_PSW, OnModifyPsw)
	ON_BN_CLICKED(IDC_DELETE_GROUP, OnDeleteGroup)
	ON_BN_CLICKED(IDC_MODIFY_GROUP, OnModifyGroup)
	ON_NOTIFY(TVN_SELCHANGED, IDC_USERLIST_TREE, OnSelchangedUserlistTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserManage message handlers

BOOL CUserManage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	CRect rect;
	GetDlgItem(IDC_RLIST_FRAME)->GetClientRect(&rect);
	GetDlgItem(IDC_RLIST_FRAME)->ClientToScreen(&rect);
	ScreenToClient(&rect);

	BOOL bCreate = m_rightList.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES 
		| TVS_DISABLEDRAGDROP, rect, this, 0x1005);

	SetWindowLong(m_rightList.m_hWnd, GWL_STYLE, TVS_CHECKBOXES);

	m_rightList.ShowWindow(SW_SHOW);
	
	BOOL bRet = CLIENT_QueryUserInfoEx(m_dev->LoginID, &m_user_info, 1000);
	if (!bRet)
	{
		MessageBox(ConvertString("failed to get user info"));
	}
	int i;

	for (i = 0; i < m_user_info.dwGroupNum; i++)
	{
		HTREEITEM hRoot, hLeaf;
		
		hRoot = m_userList.InsertItem(m_user_info.groupList[i].name, 0, 0, TVI_ROOT);
		m_userList.SetItemData(hRoot, (DWORD)&(m_user_info.groupList[i]));
		for (int j = 0; j < m_user_info.dwUserNum; j++)
		{
			if (m_user_info.userList[j].dwGroupID == m_user_info.groupList[i].dwID)
			{
				hLeaf = m_userList.InsertItem(m_user_info.userList[j].name, 0, 0, hRoot);
				m_userList.SetItemData(hLeaf, (DWORD)j);
			}
		}
		m_userList.Expand(hRoot, TVE_EXPAND);
	}

	CString strRight;
	for (i = 0; i < m_user_info.dwRightNum; i++)
	{
		HTREEITEM hRoot;

		strRight.Format("%d: %s : %s", m_user_info.rightList[i].dwID, 
							m_user_info.rightList[i].name, 
							m_user_info.rightList[i].memo);
		hRoot = m_rightList.InsertItem(strRight, 0, 0, TVI_ROOT);
		m_rightList.SetItemData(hRoot, m_user_info.rightList[i].dwID);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserManage::SetDeviceId(DeviceNode *dev)
{
	m_dev = dev;
}

void CUserManage::OnAddUser() 
{
	HTREEITEM node = m_userList.GetSelectedItem();
	if (!node)
	{
		return;
	}
	DWORD dwData = m_userList.GetItemData(node);
	if (dwData < DH_MAX_USER_NUM) //叶节点 
	{
		HTREEITEM hRoot = m_userList.GetParentItem(node);
		if (!hRoot)
		{
			return;
		}
		dwData = m_userList.GetItemData(hRoot);
	}
	USER_GROUP_INFO *gpInfo = (USER_GROUP_INFO *)dwData;

	CUser_AddUser dlg;
	dlg.SetEnvrmt(&m_user_info, gpInfo->dwID, m_dev);
	if (0 == dlg.DoModal())
	{
		RefreshUserList();
	}
}

void CUserManage::OnModifyUser() 
{
	HTREEITEM node = m_userList.GetSelectedItem();
	if (!node)
	{
		return;
	}
	DWORD dwData = m_userList.GetItemData(node);
	if (dwData < DH_MAX_USER_NUM) //叶节点 
	{
		dwData = m_userList.GetItemData(node);
		CUser_ModifyUser dlg;
		dlg.SetEnvrmt(&m_user_info, dwData, m_dev);
		if (0 == dlg.DoModal())
		{
			RefreshUserList();
		}
	}
}

void CUserManage::OnDeleteUser() 
{
	HTREEITEM node = m_userList.GetSelectedItem();
	if (!node)
	{
		return;
	}
	DWORD dwData = m_userList.GetItemData(node);
	if (dwData < DH_MAX_USER_NUM)
	{
		BOOL bRet = CLIENT_OperateUserInfo(m_dev->LoginID, 4, (void *)&m_user_info.userList[dwData], 0, 10000);
		if (!bRet)
		{
			((CNetSDKDemoDlg *)AfxGetMainWnd())->LastError();
		}
	}
	RefreshUserList();
}

void CUserManage::OnModifyPsw() 
{
	HTREEITEM node = m_userList.GetSelectedItem();
	if (!node)
	{
		return;
	}
	DWORD dwData = m_userList.GetItemData(node);
	if (dwData < DH_MAX_USER_NUM) //叶节点 
	{
		dwData = m_userList.GetItemData(node);
		CUser_ModifyPsw dlg;
		dlg.SetEnvrmt(&m_user_info, dwData, m_dev);
		if (0 == dlg.DoModal())
		{
			RefreshUserList();
		}
	}
}

void CUserManage::OnAddGroup()
{
	CUser_AddGroup dlg;
	dlg.SetEnvrmt(&m_user_info, m_dev);
	if (0 == dlg.DoModal())
	{
		RefreshUserList();
	}
}

void CUserManage::OnDeleteGroup() 
{
	HTREEITEM node = m_userList.GetSelectedItem();
	if (!node)
	{
		return;
	}
	DWORD dwData = m_userList.GetItemData(node);
	if (dwData < DH_MAX_USER_NUM)
	{
		HTREEITEM hRoot = m_userList.GetParentItem(node);
		if (!hRoot)
		{
			return;
		}
		dwData = m_userList.GetItemData(hRoot);
	}
	USER_GROUP_INFO *gpInfo = (USER_GROUP_INFO *)dwData;
	BOOL bRet = CLIENT_OperateUserInfo(m_dev->LoginID, 1, (void *)gpInfo, 0, 10000);
	if (!bRet)
	{
		((CNetSDKDemoDlg *)AfxGetMainWnd())->LastError();
	}
	RefreshUserList();
}

void CUserManage::OnModifyGroup() 
{
	HTREEITEM node = m_userList.GetSelectedItem();
	if (!node)
	{
		return;
	}
	DWORD dwData = m_userList.GetItemData(node);
	if (dwData < DH_MAX_USER_NUM) //叶节点 
	{
		HTREEITEM hRoot = m_userList.GetParentItem(node);
		if (!hRoot)
		{
			return;
		}
		dwData = m_userList.GetItemData(hRoot);
	}

	USER_GROUP_INFO *gpInfo = (USER_GROUP_INFO *)dwData;
	int count = m_user_info.dwGroupNum;
	for (int i = 0; i < count; i++)
	{
		if (gpInfo->dwID == m_user_info.groupList[i].dwID)
		{
			CUser_ModifyGroup dlg;
			dlg.SetEnvrmt(&m_user_info, i, m_dev);
			if (0 == dlg.DoModal())
			{
				RefreshUserList();
			}
			break;
		}
	}
}

void CUserManage::RefreshRightList(DWORD dwNum, DWORD *dwList)
{
	if (m_dev->Info.byDVRType == NET_NB_SERIAL)
	{
		return;
	}
	
	int count = m_rightList.GetCount();
	HTREEITEM node = m_rightList.GetRootItem();
	int i;
	for (i=0; i<count; i++)
	{
		m_rightList.SetCheck(node, FALSE);
		node = m_rightList.GetNextItem(node, TVGN_NEXT);
	}

	node = m_rightList.GetRootItem();
	for(i=0; i<dwNum && node; i++)
	{
		DWORD dwData = m_rightList.GetItemData(node);
		for (int j=0; j<count; j++)
		{
			if (dwData == dwList[j])
			{
				BOOL bxx = m_rightList.SetCheck(node, TRUE);
				break;
			}
		}
		node = m_rightList.GetNextItem(node, TVGN_NEXT);
	}
}

void CUserManage::OnSelchangedUserlistTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM node = m_userList.GetSelectedItem();
	if (!node)
	{
		return;
	}
	DWORD dwData = m_userList.GetItemData(node);
	if (dwData < DH_MAX_USER_NUM) //叶节点 
	{
		RefreshRightList(m_user_info.userList[dwData].dwRightNum,m_user_info.userList[dwData].rights);
	}
	else
	{
		USER_GROUP_INFO *gpInfo = (USER_GROUP_INFO *)dwData;
		RefreshRightList(gpInfo->dwRightNum, gpInfo->rights);
	}
	*pResult = 0;
}

void CUserManage::RefreshUserList()
{
	BOOL bRet = CLIENT_QueryUserInfoEx(m_dev->LoginID, &m_user_info, 10000);
	if (!bRet)
	{
		MessageBox(ConvertString("failed to get user info"));
	}
	int i;
	HTREEITEM hRoot, hLeaf;

	m_userList.DeleteAllItems();
	m_rightList.DeleteAllItems();
	for (i = 0; i < m_user_info.dwGroupNum; i++)
	{
		hRoot = m_userList.InsertItem(m_user_info.groupList[i].name, 0, 0, TVI_ROOT);
		m_userList.SetItemData(hRoot, (DWORD)&(m_user_info.groupList[i]));
		for (int j = 0; j < m_user_info.dwUserNum; j++)
		{
			if (m_user_info.userList[j].dwGroupID == m_user_info.groupList[i].dwID)
			{
				hLeaf = m_userList.InsertItem(m_user_info.userList[j].name, 0, 0, hRoot);
				m_userList.SetItemData(hLeaf, (DWORD)j);
			}
		}
		m_userList.Expand(hRoot, TVE_EXPAND);
	}
	
	CString strRight;
	for (i = 0; i < m_user_info.dwRightNum; i++)
	{
		strRight.Format("%d: %s : %s", m_user_info.rightList[i].dwID, 
			m_user_info.rightList[i].name, 
			m_user_info.rightList[i].memo);
		hRoot = m_rightList.InsertItem(strRight, 0, 0, TVI_ROOT);
		m_rightList.SetItemData(hRoot, m_user_info.rightList[i].dwID);
	}

	hRoot = m_userList.GetRootItem();
	if (hRoot) 
	{
		m_userList.SelectItem(hRoot);
		m_userList.SetFocus();
	}
}
