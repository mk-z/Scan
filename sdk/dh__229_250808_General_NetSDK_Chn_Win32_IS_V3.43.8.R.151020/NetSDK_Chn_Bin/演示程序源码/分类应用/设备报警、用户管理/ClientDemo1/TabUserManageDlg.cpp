// TabUserManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo1.h"
#include "TabUserManageDlg.h"
#include "AddUserInfo.h"
#include "ModifyUserInfo.h"
#include "ModifyPwd.h"
#include "AddGroupInfo.h"
#include "ModifyGroupInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabUserManageDlg dialog


CTabUserManageDlg::CTabUserManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabUserManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabUserManageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hLoginID = 0;
}


void CTabUserManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabUserManageDlg)
	DDX_Control(pDX, IDC_TREE_LEVELS, m_treeLevels);
	DDX_Control(pDX, IDC_TREE_USERS, m_treeUsers);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabUserManageDlg, CDialog)
	//{{AFX_MSG_MAP(CTabUserManageDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_USERS, OnSelchangedTreeUsers)
	ON_BN_CLICKED(IDC_ADD_USER, OnAddUser)
	ON_BN_CLICKED(IDC_MODIFY_USER, OnModifyUser)
	ON_BN_CLICKED(IDC_DELETE_USER, OnDeleteUser)
	ON_BN_CLICKED(IDC_MODIFY_PSW, OnModifyPsw)
	ON_BN_CLICKED(IDC_ADD_GROUP, OnAddGroup)
	ON_BN_CLICKED(IDC_DELETE_GROUP, OnDeleteGroup)
	ON_BN_CLICKED(IDC_MODIFY_GROUP, OnModifyGroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabUserManageDlg message handlers

//To be called by CClientDemo1Dlg. Call this interface to initialize the whole dialogue box after logging in the device. 
void CTabUserManageDlg::InitUserManageInfo(long hLoginID)
{
	m_hLoginID = hLoginID;
	//To get user information 
	memset(&m_usersInfoNew, 0, sizeof(m_usersInfoNew));
	m_usersInfoNew.dwSize = sizeof(USER_MANAGE_INFO_NEW);
	int i;
	for (i=0; i<DH_NEW_MAX_RIGHT_NUM; i++)
	{
		m_usersInfoNew.rightList[i].dwSize = sizeof(OPR_RIGHT_NEW);
	}

	for (i=0; i<DH_MAX_GROUP_NUM; i++)
	{
		m_usersInfoNew.groupList[i].dwSize = sizeof(USER_GROUP_INFO_NEW);
	}

	for (i=0; i<DH_MAX_USER_NUM; i++)
	{
		m_usersInfoNew.userList[i].dwSize = sizeof(USER_INFO_NEW);
	}

	for (i=0; i<DH_MAX_GROUP_NUM; i++)
	{
		m_usersInfoNew.groupListEx[i].dwSize = sizeof(USER_GROUP_INFO_EX2);
	}

// 	BOOL bRet = CLIENT_QueryUserInfoEx(hLoginID, &m_usersInfo, 10000);
	BOOL bRet = CLIENT_QueryUserInfoNew(hLoginID, &m_usersInfoNew, NULL, 10000);
	if (!bRet)
	{
		MessageBox(ConvertString("Get user info failed!"), ConvertString("Prompt"));
	}
	else
	{
		//Create a tree 
		InitTree();
	}
}

//To be called by CClientDemo1Dlg. Clear dialogue box information after log off the device. 
void CTabUserManageDlg::CleanUserManageInfo()
{
	//Clear tree 
	m_treeUsers.DeleteAllItems();
	m_treeLevels.DeleteAllItems();
}

//Generate tree 
void CTabUserManageDlg::InitTree()
{
	//Clear tree 
	m_treeUsers.DeleteAllItems();
	m_treeLevels.DeleteAllItems();
#if 1
	//User information
	for (int i=0; i<(int)m_usersInfoNew.dwGroupNum; i++)
	{
		//Add user group
		char szGroupName[DH_USER_NAME_LENGTH_EX + 4] = {0};
		memcpy(szGroupName, m_usersInfoNew.groupList[i].name, DH_USER_NAME_LENGTH_EX);
		HTREEITEM hRoot = m_treeUsers.InsertItem(szGroupName, TVI_ROOT, TVI_LAST);
		m_treeUsers.SetItemData(hRoot,(DWORD)&(m_usersInfoNew.groupList[i]));
		//Add user
		for(int j=0;j<(int)m_usersInfoNew.dwUserNum;j++)
		{
			if (m_usersInfoNew.userList[j].dwGroupID == m_usersInfoNew.groupList[i].dwID)
			{
				char szNameBuf[DH_NEW_USER_NAME_LENGTH] = {0};
				memcpy(szNameBuf, m_usersInfoNew.userList[j].name, DH_NEW_USER_NAME_LENGTH);
				HTREEITEM hLeaf = m_treeUsers.InsertItem(szNameBuf, hRoot, TVI_LAST);
				m_treeUsers.SetItemData(hLeaf, (DWORD)j);
			}
		}
		m_treeUsers.Expand(hRoot,TVE_EXPAND);
	}
	//Right information 
	for(int k=0;k<(int)m_usersInfoNew.dwRightNum;k++)
	{
		CString str;
		str.Format("%d: %s : %s",m_usersInfoNew.rightList[k].dwID,m_usersInfoNew.rightList[k].name,
			m_usersInfoNew.rightList[k].memo);
		HTREEITEM hRoot = m_treeLevels.InsertItem(str,TVI_ROOT,TVI_LAST);
		m_treeLevels.SetItemData(hRoot,m_usersInfoNew.rightList[k].dwID);
	}
#else
	//User information 
	for(int i=0;i<(int)m_usersInfo.dwGroupNum;i++)
	{
		//Add user group 
		char szGroupName[DH_USER_NAME_LENGTH_EX + 4] = {0};
		memcpy(szGroupName, m_usersInfo.groupList[i].name, DH_USER_NAME_LENGTH_EX);
		HTREEITEM hRoot = m_treeUsers.InsertItem(szGroupName, TVI_ROOT, TVI_LAST);
		m_treeUsers.SetItemData(hRoot,(DWORD)&(m_usersInfo.groupList[i]));
		//Add user 
		for(int j=0;j<(int)m_usersInfo.dwUserNum;j++)
		{
			if(m_usersInfo.userList[j].dwGroupID == m_usersInfo.groupList[i].dwID)
			{
				char szNameBuf[20] = {0};
				memcpy(szNameBuf, m_usersInfo.userList[j].name, 16);
				HTREEITEM hLeaf = m_treeUsers.InsertItem(szNameBuf, hRoot, TVI_LAST);
				m_treeUsers.SetItemData(hLeaf,(DWORD)j);
			}
		}
		m_treeUsers.Expand(hRoot,TVE_EXPAND);
	}
	//Right information 
	for(int k=0;k<(int)m_usersInfo.dwRightNum;k++)
	{
		CString str;
		str.Format("%d: %s : %s",m_usersInfo.rightList[k].dwID,m_usersInfo.rightList[k].name,
			m_usersInfo.rightList[k].memo);
		HTREEITEM hRoot = m_treeLevels.InsertItem(str,TVI_ROOT,TVI_LAST);
		m_treeLevels.SetItemData(hRoot,m_usersInfo.rightList[k].dwID);
	}
#endif
	//Select one node
	HTREEITEM hSelItem = m_treeUsers.GetRootItem();
	if(hSelItem != NULL)
	{
		m_treeUsers.SelectItem(hSelItem);
		m_treeUsers.SetFocus();
		//Refresh right list according to the user. 
		RefreshLevelList();
	}
}

BOOL CTabUserManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabUserManageDlg::OnSelchangedTreeUsers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//Update right list 
	RefreshLevelList();

	*pResult = 0;
}

void CTabUserManageDlg::RefreshLevelList()
{
	DWORD dwNum;
	DWORD *dwList;
	HTREEITEM hSelItem = m_treeUsers.GetSelectedItem();
	if(hSelItem != NULL)
	{
		//To get binding data 
		DWORD dwTagData = m_treeUsers.GetItemData(hSelItem);
		if(dwTagData < DH_MAX_USER_NUM)		//User
		{
			dwNum = m_usersInfoNew.userList[dwTagData].dwRightNum;
			dwList = m_usersInfoNew.userList[dwTagData].rights;
		}
		else	//Group 
		{
			USER_GROUP_INFO_NEW *gpInfo = (USER_GROUP_INFO_NEW *)dwTagData;
// 			USER_GROUP_INFO_EX *gpInfo = (USER_GROUP_INFO_EX *)dwTagData;
			dwNum = gpInfo->dwRightNum;
			dwList = gpInfo->rights;
		}
	}
	//Update right list 
	int nCountItem = m_treeLevels.GetCount();
	HTREEITEM hItem = m_treeLevels.GetRootItem();
	int i =0;
	for(i=0;i<nCountItem;i++)
	{
		m_treeLevels.SetCheck(hItem,FALSE);
		hItem = m_treeLevels.GetNextItem(hItem,TVGN_NEXT);
	}
	
	for(i=0;i<(int)dwNum;i++)
	{
		hItem = m_treeLevels.GetRootItem();
		for(int j=0;j<nCountItem && hItem;j++)
		{
			DWORD dwData = m_treeLevels.GetItemData(hItem);
			if(dwData == dwList[i])
			{
				m_treeLevels.SetCheck(hItem,TRUE);
				break;
			}
			hItem = m_treeLevels.GetNextItem(hItem,TVGN_NEXT);
		}
	}
}

//Add user 
void CTabUserManageDlg::OnAddUser() 
{
	// TODO: Add your control notification handler code here
	if(0 < m_hLoginID)
	{
		HTREEITEM hSelItem = m_treeUsers.GetSelectedItem();
		if(hSelItem != NULL)
		{
			DWORD dwData = m_treeUsers.GetItemData(hSelItem);
			if(dwData < DH_MAX_USER_NUM)
			{
				hSelItem = m_treeUsers.GetParentItem(hSelItem);
			}
			if(hSelItem != NULL)
			{
				dwData = m_treeUsers.GetItemData(hSelItem);
				USER_GROUP_INFO_NEW *gpInfo = (USER_GROUP_INFO_NEW*)dwData;
// 				USER_GROUP_INFO_EX *gpInfo = (USER_GROUP_INFO_EX *)dwData;
				CAddUserInfo dlg;
// 				dlg.InitAddUserInfoDlg(&m_usersInfo,gpInfo->dwID,m_hLoginID);
				dlg.InitAddUserInfoDlg(&m_usersInfoNew,gpInfo->dwID,m_hLoginID);
				int nResponse = dlg.DoModal();
				if (nResponse == IDOK)
				{
					//To get user information 
// 					BOOL bRet = CLIENT_QueryUserInfoEx(m_hLoginID, &m_usersInfo, 10000);
					BOOL bRet = CLIENT_QueryUserInfoNew(m_hLoginID, &m_usersInfoNew, NULL, 10000);
					if (!bRet)
					{
						MessageBox(ConvertString("Get user info failed!"), ConvertString("Prompt"));
					}
					else
					{
						//Generate tree again
						InitTree();
					}
				}
			}
		}
		else
		{
			MessageBox(ConvertString("Please select group!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

//Modify user 
void CTabUserManageDlg::OnModifyUser() 
{
	// TODO: Add your control notification handler code here
	if(0 < m_hLoginID)
	{
		HTREEITEM hSelItem = m_treeUsers.GetSelectedItem();
		if(hSelItem != NULL)
		{
			DWORD dwData = m_treeUsers.GetItemData(hSelItem);
			if(dwData < DH_MAX_USER_NUM)
			{
				CModifyUserInfo dlg;
				dlg.InitModifyUserInfoDlg(/*&m_usersInfo*/&m_usersInfoNew,dwData,m_hLoginID);
				int nResponse = dlg.DoModal();
				if (nResponse == IDOK)
				{
					//Get user information 
					BOOL bRet = CLIENT_QueryUserInfoNew(m_hLoginID, &m_usersInfoNew, NULL, 3000);
// 					BOOL bRet = CLIENT_QueryUserInfoEx(m_hLoginID, &m_usersInfo, 3000);
					if (!bRet)
					{
						MessageBox(ConvertString("Get user info failed!"), ConvertString("Prompt"));
					}
					else
					{
						//Generate tree again 
						InitTree();
					}
				}
			}
			else
			{
				MessageBox(ConvertString("You selected group, please select user!"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("please select user!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

//Delete tree 
void CTabUserManageDlg::OnDeleteUser() 
{
	// TODO: Add your control notification handler code here
	if(0 < m_hLoginID)
	{
		HTREEITEM hSelItem = m_treeUsers.GetSelectedItem();
		if(hSelItem != NULL)
		{
			DWORD dwData = m_treeUsers.GetItemData(hSelItem);
			if(dwData < DH_MAX_USER_NUM)
			{
				BOOL bRet = CLIENT_OperateUserInfoNew(m_hLoginID, 4, (void *)&m_usersInfoNew.userList[dwData], 0, NULL, 10000);
//				BOOL bRet = CLIENT_OperateUserInfoEx(m_hLoginID, 4, (void *)&m_usersInfo.userList[dwData], 0, 10000);
				if (bRet)
				{
					//Get user information 
					BOOL bRet = CLIENT_QueryUserInfoNew(m_hLoginID, &m_usersInfoNew, NULL, 10000);
// 					BOOL bRet = CLIENT_QueryUserInfoEx(m_hLoginID, &m_usersInfo, 10000);
					if (!bRet)
					{
						MessageBox(ConvertString("Get user info failed!"), ConvertString("Prompt"));
					}
					else
					{
						//Generate tree again 
						InitTree();
					}
				}
				else
				{
					int nError = CLIENT_GetLastError();
					if(nError == NET_RETURN_DATA_ERROR)	MessageBox(ConvertString("checkout return data error!"), ConvertString("Prompt"));
					else if(nError == NET_ILLEGAL_PARAM) MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
					else if(nError == NET_USER_NOEXIST) MessageBox(ConvertString("the user is not existing!"), ConvertString("Prompt"));
					else MessageBox(ConvertString("remove user failed!"), ConvertString("Prompt"));
				}
			}
			else
			{
				MessageBox(ConvertString("You selected group, please select user!"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("please select user!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

//Modify password 
void CTabUserManageDlg::OnModifyPsw() 
{
	// TODO: Add your control notification handler code here
	if(0 < m_hLoginID)
	{
		HTREEITEM hSelItem = m_treeUsers.GetSelectedItem();
		if(hSelItem != NULL)
		{
			DWORD dwData = m_treeUsers.GetItemData(hSelItem);
			if(dwData < DH_MAX_USER_NUM)
			{
				CModifyPwd dlg;
				dlg.InitModifyPwdInfoDlg(&m_usersInfoNew/*&m_usersInfo*/,dwData,m_hLoginID);
				int nResponse = dlg.DoModal();
				if (nResponse == IDOK)
				{
					//Get user information 
// 					BOOL bRet = CLIENT_QueryUserInfoEx(m_hLoginID, &m_usersInfo, 10000);
					BOOL bRet = CLIENT_QueryUserInfoNew(m_hLoginID, &m_usersInfoNew, NULL, 10000);
					if (!bRet)
					{
						MessageBox(ConvertString("Get user info failed!"), ConvertString("Prompt"));
					}
					else
					{
						//Generate tree again 
						InitTree();
					}
				}
			}
			else
			{
				MessageBox(ConvertString("You selected group, please select user!"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("please select user!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

//Add group 
void CTabUserManageDlg::OnAddGroup() 
{
	// TODO: Add your control notification handler code here
	if(0 < m_hLoginID)
	{
		CAddGroupInfo dlg;
		dlg.InitAddGroupDlg(&m_usersInfoNew/*&m_usersInfo*/,m_hLoginID);
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			//Get user information 
// 			BOOL bRet = CLIENT_QueryUserInfoEx(m_hLoginID, &m_usersInfo, 10000);
			BOOL bRet = CLIENT_QueryUserInfoNew(m_hLoginID, &m_usersInfoNew, NULL, 10000);
			if (!bRet)
			{
				MessageBox(ConvertString("Get user info failed!"), ConvertString("Prompt"));
			}
			else
			{
				//Generate tree again 
				InitTree();
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

//Delete group 
void CTabUserManageDlg::OnDeleteGroup() 
{
	// TODO: Add your control notification handler code here
	if(0 < m_hLoginID)
	{
		HTREEITEM hSelItem = m_treeUsers.GetSelectedItem();
		if(hSelItem != NULL)
		{
			DWORD dwData = m_treeUsers.GetItemData(hSelItem);
			if(dwData > DH_MAX_USER_NUM)
			{
				USER_GROUP_INFO_NEW *groupInfoNew = (USER_GROUP_INFO_NEW*)dwData;
// 				USER_GROUP_INFO_EX *groupInfo = (USER_GROUP_INFO_EX *)dwData;
// 				BOOL bRet = CLIENT_OperateUserInfoEx(m_hLoginID, 1, (void *)groupInfo, 0, 10000);
				BOOL bRet = CLIENT_OperateUserInfoNew(m_hLoginID, 1, (void*)groupInfoNew, 0, NULL, 10000);
				if (bRet)
				{
					//To get user information 
// 					BOOL bRet = CLIENT_QueryUserInfoEx(m_hLoginID, &m_usersInfo, 10000);
					BOOL bRet = CLIENT_QueryUserInfoNew(m_hLoginID, &m_usersInfoNew, NULL, 10000);
					if (!bRet)
					{
						MessageBox(ConvertString("Get user info failed!"), ConvertString("Prompt"));
					}
					else
					{
						//Generate tree again 
						InitTree();
					}
				}
				else
				{
					int nError = CLIENT_GetLastError();
					if(nError == NET_RETURN_DATA_ERROR)	MessageBox(ConvertString("checkout return data error!"), ConvertString("Prompt"));
					else if(nError == NET_ILLEGAL_PARAM) MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
					else if(nError == NET_GROUP_NOEXIST) MessageBox(ConvertString("the group is not existing!"), ConvertString("Prompt"));
					else if(nError == NET_GROUP_HAVEUSER) MessageBox(ConvertString("there are any user under the group, you can't remove it!"), ConvertString("Prompt"));
					else MessageBox(ConvertString("Delete group failed!"), ConvertString("Prompt"));
				}
			}
			else
			{
				MessageBox(ConvertString("You have selected user, please select group!"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("Please select group first!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

//Modify group 
void CTabUserManageDlg::OnModifyGroup() 
{
	// TODO: Add your control notification handler code here
	if(0 < m_hLoginID)
	{
		HTREEITEM hSelItem = m_treeUsers.GetSelectedItem();
		if(hSelItem != NULL)
		{
			DWORD dwData = m_treeUsers.GetItemData(hSelItem);
			if(dwData > DH_MAX_USER_NUM)
			{
// 				USER_GROUP_INFO_EX *groupInfo = (USER_GROUP_INFO_EX *)dwData;
				USER_GROUP_INFO_NEW *groupInfoNew = (USER_GROUP_INFO_NEW*)dwData;
				int nCount = m_usersInfoNew.dwGroupNum;
				for (int i = 0; i < nCount; i++)
				{
					if (groupInfoNew->dwID == m_usersInfoNew.groupList[i].dwID)
					{
						CModifyGroupInfo dlg;
						dlg.InitModifyGroupInfoDlg(&m_usersInfoNew, i, m_hLoginID);
						int nResponse = dlg.DoModal();
						if (nResponse == IDOK)
						{
							//To get user information 
//							BOOL bRet = CLIENT_QueryUserInfoEx(m_hLoginID, &m_usersInfo, 10000);
							BOOL bRet = CLIENT_QueryUserInfoNew(m_hLoginID, &m_usersInfoNew, NULL, 10000);
							if (!bRet)
							{
								MessageBox(ConvertString("Get user info failed!"), ConvertString("Prompt"));
							}
							else
							{
								//Generate tree again 
								InitTree();
							}
						}
					}
				}
			}
			else
			{
				MessageBox(ConvertString("You have selected user, please select group!"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("Please select group first!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}




































































































