// ModifyUserInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo1.h"
#include "ModifyUserInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyUserInfo dialog


CModifyUserInfo::CModifyUserInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyUserInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyUserInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwUserID = 0;
	m_usersInfoNew = 0;
	m_hLoginID = 0;
}


void CModifyUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyUserInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyUserInfo, CDialog)
	//{{AFX_MSG_MAP(CModifyUserInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyUserInfo message handlers

void CModifyUserInfo::OnOK() 
{
	// TODO: Add extra validation here
	if(!IsValid())
	{
		MessageBox(ConvertString("Please Input!"), ConvertString("Prompt"));
		return;
	}
	USER_INFO_NEW userInfoNew = {sizeof(USER_INFO_NEW)};
// 	USER_INFO_EX userInfo = {0};
	userInfoNew.dwID = m_usersInfoNew->userList[m_dwUserID].dwID;
	GetDlgItem(IDC_EDIT_NEWNAME)->GetWindowText(userInfoNew.name, DH_NEW_USER_NAME_LENGTH+1);
	memcpy(userInfoNew.passWord, m_usersInfoNew->userList[m_dwUserID].passWord, DH_NEW_USER_PSW_LENGTH);
	GetDlgItem(IDC_EDIT_NEWMEMO)->GetWindowText(userInfoNew.memo, DH_MEMO_LENGTH);
	userInfoNew.dwFouctionMask = ((CButton*)GetDlgItem(IDC_CHECK_NEWREUSEABLE))->GetCheck();
	userInfoNew.dwGroupID = m_usersInfoNew->userList[m_dwUserID].dwGroupID;
	
	int nCountItem = m_treeLevels.GetCount();
	HTREEITEM hItem = m_treeLevels.GetRootItem();
	int nIndex = 0;
	for (int i=0; i<nCountItem && hItem; i++)
	{
		if (m_treeLevels.GetCheck(hItem))
		{
			userInfoNew.rights[nIndex] = m_treeLevels.GetItemData(hItem);
			nIndex++;
		}
		hItem = m_treeLevels.GetNextItem(hItem, TVGN_NEXT);
	}
	userInfoNew.dwRightNum = nIndex;
	
// 	BOOL bRet = CLIENT_OperateUserInfoEx(m_hLoginID, 5, (void *)&userInfo, (void *)&m_usersInfo->userList[m_dwUserID], 1000);
	BOOL bRet = CLIENT_OperateUserInfoNew(m_hLoginID, 5, (void*)&userInfoNew, (void*)&m_usersInfoNew->userList[m_dwUserID], NULL, 1000);
	if (!bRet)
	{
		int nError = CLIENT_GetLastError();
		if(nError == NET_RETURN_DATA_ERROR)	MessageBox(ConvertString("checkout return data error!"), ConvertString("Prompt"));
		else if(nError == NET_ILLEGAL_PARAM) MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
		else if(nError == NET_USER_NOEXIST) MessageBox(ConvertString("The user is not existing!"), ConvertString("Prompt"));
		else if(nError == NET_USER_EXIST) MessageBox(ConvertString("The user is existing!"), ConvertString("Prompt"));
		else if(nError == NET_USER_RIGHTOVER) MessageBox(ConvertString("The user's right is out of the group's right!"), ConvertString("Prompt"));
		else MessageBox(ConvertString("Modify user info failed!"), ConvertString("Prompt"));
	}
	else
	{
		CDialog::OnOK();
	}
}

BOOL CModifyUserInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	//Create tree
	CRect rect;
	GetDlgItem(IDC_MODIFY_FRAME)->GetClientRect(&rect);
	GetDlgItem(IDC_MODIFY_FRAME)->ClientToScreen(&rect);
	ScreenToClient(&rect);
	BOOL bCreate = m_treeLevels.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES 
		| TVS_DISABLEDRAGDROP, rect, this, 0x1005);
	
	SetWindowLong(m_treeLevels.m_hWnd, GWL_STYLE, TVS_CHECKBOXES);
	m_treeLevels.ShowWindow(SW_SHOW);

	if (!m_usersInfoNew || !m_hLoginID)
	{
		return TRUE;
	}

	//Set group name 
	int i = 0;
	DWORD dwGroupID = m_usersInfoNew->userList[m_dwUserID].dwGroupID;
	for(i=0;i<(int)(m_usersInfoNew->dwGroupNum);i++)
	{
		if(m_usersInfoNew->groupList[i].dwID == dwGroupID)
		{
			CString str = m_usersInfoNew->groupList[i].name;
			SetDlgItemText(IDC_EDIT_GROUP,str);
			char szName[17] = {0};
			memcpy(szName, m_usersInfoNew->userList[m_dwUserID].name, 16);
			str = szName;
			SetDlgItemText(IDC_EDIT_USERNAME,str);
			SetDlgItemText(IDC_EDIT_NEWNAME,str);
			str = m_usersInfoNew->userList[m_dwUserID].memo;
			SetDlgItemText(IDC_EDIT_MEMO,str);
			SetDlgItemText(IDC_EDIT_NEWMEMO,str);
			DWORD dwSpecial = m_usersInfoNew->dwFouctionMask;
			if(dwSpecial == 0)
			{
				GetDlgItem(IDC_CHECK_NEWREUSEABLE)->EnableWindow(FALSE);
			}
			else
			{
				((CButton*)GetDlgItem(IDC_CHECK_REUSEABLE))->SetCheck(m_usersInfoNew->userList[m_dwUserID].dwFouctionMask);
				((CButton*)GetDlgItem(IDC_CHECK_NEWREUSEABLE))->SetCheck(m_usersInfoNew->userList[m_dwUserID].dwFouctionMask);
			}
			//Initialize right list 
			InitLevelTree(m_usersInfoNew->userList[m_dwUserID].dwRightNum,m_usersInfoNew->userList[m_dwUserID].rights);
			break;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModifyUserInfo::InitModifyUserInfoDlg(USER_MANAGE_INFO_NEW *info, DWORD dwID, long hLoginID)
{
	m_usersInfoNew = info;
	m_dwUserID = dwID;
	m_hLoginID = hLoginID;
}

void CModifyUserInfo::InitLevelTree(DWORD dwNum, DWORD *dwList)
{
	m_treeLevels.DeleteAllItems();
	//Right information 
	int i = 0;
	for(i=0;i<(int)m_usersInfoNew->dwRightNum;i++)
	{
		CString str;
		str.Format("%d: %s : %s      ",m_usersInfoNew->rightList[i].dwID,m_usersInfoNew->rightList[i].name,
			m_usersInfoNew->rightList[i].memo);
		HTREEITEM hRoot = m_treeLevels.InsertItem(str,TVI_ROOT,TVI_LAST);
		m_treeLevels.SetItemData(hRoot,m_usersInfoNew->rightList[i].dwID);
	}
	
	//Update right list 
	int nCountItem = m_treeLevels.GetCount();
	HTREEITEM hItem = m_treeLevels.GetRootItem();
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

BOOL CModifyUserInfo::IsValid()
{
	BOOL bValid = TRUE;
	CString str1;
	GetDlgItemText(IDC_EDIT_NEWNAME,str1);
	if(str1.IsEmpty())
	{
		bValid = FALSE;
	}
	return bValid;
}




































































































