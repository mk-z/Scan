// AddGroupInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo1.h"
#include "AddGroupInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddGroupInfo dialog


CAddGroupInfo::CAddGroupInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CAddGroupInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddGroupInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_usersInfoNew = 0;
	m_hLoginID = 0;
}


void CAddGroupInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddGroupInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddGroupInfo, CDialog)
	//{{AFX_MSG_MAP(CAddGroupInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddGroupInfo message handlers

void CAddGroupInfo::OnOK() 
{
	// TODO: Add extra validation here
	if(!IsValid())
	{
		MessageBox(ConvertString("Please Input!"), ConvertString("Prompt"));
		return;
	}

	USER_GROUP_INFO_NEW groupInfo = {sizeof(USER_GROUP_INFO_NEW)};
// 	USER_GROUP_INFO_EX groupInfo = {0};
	groupInfo.dwID = m_usersInfoNew->dwGroupNum + 1;
	GetDlgItem(IDC_EDIT_GROUPNAME)->GetWindowText(groupInfo.name, DH_USER_NAME_LENGTH_EX+1);
	GetDlgItem(IDC_EDIT_MEMO)->GetWindowText(groupInfo.memo, DH_MEMO_LENGTH);
	
	int nCountItem = m_treeLevels.GetCount();
	HTREEITEM hItem = m_treeLevels.GetRootItem();
	int nIndex = 0;
	for (int i=0; i<nCountItem && hItem; i++)
	{
		if (m_treeLevels.GetCheck(hItem))
		{
			groupInfo.rights[nIndex] = m_treeLevels.GetItemData(hItem);
			nIndex++;
		}
		hItem = m_treeLevels.GetNextItem(hItem, TVGN_NEXT);
	}
	groupInfo.dwRightNum = nIndex;

	BOOL bRet = CLIENT_OperateUserInfoNew(m_hLoginID, 0, &groupInfo, 0, NULL, 1000);
// 	BOOL bRet = CLIENT_OperateUserInfoEx(m_hLoginID, 0/*type: add user group*/, &groupInfo, 0, 1000);
	if (!bRet)
	{
		int nError = CLIENT_GetLastError();
		if(nError == NET_RETURN_DATA_ERROR)	MessageBox(ConvertString("checkout return data error!"), ConvertString("Prompt"));
		else if(nError == NET_ILLEGAL_PARAM) MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
		else if(nError == NET_GROUP_EXIST) MessageBox(ConvertString("The group is existing!"), ConvertString("Prompt"));
		else if(nError == NET_GROUP_RIGHTOVER) MessageBox(ConvertString("The group's right is out of the list's range."), ConvertString("Prompt"));
		else MessageBox(ConvertString("Add user group failed!"), ConvertString("Prompt"));
	}
	else
	{
		CDialog::OnOK();
	}
}

BOOL CAddGroupInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	//Create tree 
	CRect rect;
	GetDlgItem(IDC_RLIST_FRAME)->GetClientRect(&rect);
	GetDlgItem(IDC_RLIST_FRAME)->ClientToScreen(&rect);
	ScreenToClient(&rect);
	BOOL bCreate = m_treeLevels.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES 
		| TVS_DISABLEDRAGDROP, rect, this, 0x1005);
	
	SetWindowLong(m_treeLevels.m_hWnd, GWL_STYLE, TVS_CHECKBOXES);
	m_treeLevels.ShowWindow(SW_SHOW);
	
	//Right information 
	int i = 0;
	for(i=0;i<(int)m_usersInfoNew->dwRightNum;i++)
	{
		CString str;
		str.Format("%d: %s : %s                         ",m_usersInfoNew->rightList[i].dwID,m_usersInfoNew->rightList[i].name,
			m_usersInfoNew->rightList[i].memo);
		HTREEITEM hRoot = m_treeLevels.InsertItem(str,TVI_ROOT,TVI_LAST);
		m_treeLevels.SetItemData(hRoot,m_usersInfoNew->rightList[i].dwID);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddGroupInfo::InitAddGroupDlg(/*USER_MANAGE_INFO_EX*/USER_MANAGE_INFO_NEW *info, long hLoginID)
{
	m_usersInfoNew = info;
	// 	m_usersInfo = info;
	m_hLoginID = hLoginID;
}

BOOL CAddGroupInfo::IsValid()
{
	BOOL bValid = TRUE;
	CString str1;
	GetDlgItemText(IDC_EDIT_GROUPNAME,str1);
	if(str1.IsEmpty())
	{
		bValid = FALSE;
	}
	return bValid;
}
