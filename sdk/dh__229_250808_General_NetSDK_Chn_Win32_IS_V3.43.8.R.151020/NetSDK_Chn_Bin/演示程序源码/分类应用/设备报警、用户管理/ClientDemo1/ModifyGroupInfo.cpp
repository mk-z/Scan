// ModifyGroupInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo1.h"
#include "ModifyGroupInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyGroupInfo dialog


CModifyGroupInfo::CModifyGroupInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyGroupInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyGroupInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwGroupID = 0;
//	m_usersInfo = 0;
	m_usersInfoNew = 0;
	m_hLoginID = 0;
}


void CModifyGroupInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyGroupInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyGroupInfo, CDialog)
	//{{AFX_MSG_MAP(CModifyGroupInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyGroupInfo message handlers

void CModifyGroupInfo::OnOK() 
{
	// TODO: Add extra validation here
	if(!IsValid())
	{
		MessageBox(ConvertString("Please Input!"), ConvertString("Prompt"));
		return;
	}
	
	USER_GROUP_INFO_NEW groupInfoNew = {sizeof(USER_GROUP_INFO_NEW)};
	// 	USER_GROUP_INFO_EX groupInfo = {0};
	groupInfoNew.dwID = m_usersInfoNew->groupList[m_dwGroupID].dwID;
	GetDlgItem(IDC_EDIT_NEWGROUPNAME)->GetWindowText(groupInfoNew.name, DH_USER_NAME_LENGTH_EX+1);
	GetDlgItem(IDC_EDIT_NEWMEMO)->GetWindowText(groupInfoNew.memo, DH_MEMO_LENGTH);
	
	int nCountItem = m_treeLevels.GetCount();
	HTREEITEM hItem = m_treeLevels.GetRootItem();
	int nIndex = 0;
	for (int i=0; i<nCountItem && hItem; i++)
	{
		if (m_treeLevels.GetCheck(hItem))
		{
			groupInfoNew.rights[nIndex] = m_treeLevels.GetItemData(hItem);
			nIndex++;
		}
		hItem = m_treeLevels.GetNextItem(hItem, TVGN_NEXT);
	}
	groupInfoNew.dwRightNum = nIndex;

	BOOL bRet = CLIENT_OperateUserInfoNew(m_hLoginID, 2, &groupInfoNew, &m_usersInfoNew->groupList[m_dwGroupID], NULL, 1000);
// 	BOOL bRet = CLIENT_OperateUserInfoEx(m_hLoginID, 2, &groupInfo, &m_usersInfo->groupList[m_dwGroupID], 1000);
	if (!bRet)
	{
		int nError = CLIENT_GetLastError();
		if(nError == NET_RETURN_DATA_ERROR)	MessageBox(ConvertString("checkout return data error!"), ConvertString("Prompt"));
		else if(nError == NET_ILLEGAL_PARAM) MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
		else if(nError == NET_GROUP_NOEXIST) MessageBox(ConvertString("The group don't exist!"), ConvertString("Prompt"));
		else if(nError == NET_GROUP_RIGHTUSE) MessageBox(ConvertString("one right of the group is in using, can't remove it."), ConvertString("Prompt"));
		else if(nError == NET_GROUP_SAMENAME) MessageBox(ConvertString("The new group name is existing!"), ConvertString("Prompt"));
		else MessageBox(ConvertString(" Modify group failed!"), ConvertString("Prompt"));
	}
	else
	{
		CDialog::OnOK();
	}
}

BOOL CModifyGroupInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//Create tree 
	g_SetWndStaticText(this);

	CRect rect;
	GetDlgItem(IDC_RLIST_FRAME)->GetClientRect(&rect);
	GetDlgItem(IDC_RLIST_FRAME)->ClientToScreen(&rect);
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
	char szBuf[DH_MEMO_LENGTH + 1] = {0};
	memcpy(szBuf, m_usersInfoNew->groupList[m_dwGroupID].name, DH_USER_NAME_LENGTH_EX);
	CString strBuf = szBuf;
	GetDlgItem(IDC_EDIT_GROUPNAME)->SetWindowText(strBuf);
	GetDlgItem(IDC_EDIT_NEWGROUPNAME)->SetWindowText(strBuf);
	
	memset(szBuf, 0, DH_MEMO_LENGTH + 1);
	memcpy(szBuf, m_usersInfoNew->groupList[m_dwGroupID].memo, DH_MEMO_LENGTH);
	strBuf = szBuf;
	GetDlgItem(IDC_EDIT_MEMO)->SetWindowText(strBuf);
	GetDlgItem(IDC_EDIT_NEWMEMO)->SetWindowText(strBuf);
	
	InitLevelTree(m_usersInfoNew->groupList[m_dwGroupID].dwRightNum, m_usersInfoNew->groupList[m_dwGroupID].rights);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModifyGroupInfo::InitModifyGroupInfoDlg(USER_MANAGE_INFO_NEW /*USER_MANAGE_INFO_EX*/ *info, DWORD dwGroupID, long hLoginID)
{
	m_usersInfoNew = info;
	// 	m_usersInfo = info;
	m_dwGroupID = dwGroupID;
	m_hLoginID = hLoginID;
}

void CModifyGroupInfo::InitLevelTree(DWORD dwNum, DWORD *dwList)
{
	m_treeLevels.DeleteAllItems();
	//Right information 
	int i = 0;
	for(i=0;i<(int)m_usersInfoNew->dwRightNum;i++)
	{
		CString str;
		str.Format("%d: %s : %s         ",m_usersInfoNew->rightList[i].dwID,m_usersInfoNew->rightList[i].name,
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

BOOL CModifyGroupInfo::IsValid()
{
	BOOL bValid = TRUE;
	CString str1;
	GetDlgItemText(IDC_EDIT_NEWGROUPNAME,str1);
	if(str1.IsEmpty())
	{
		bValid = FALSE;
	}
	return bValid;
}




































































































