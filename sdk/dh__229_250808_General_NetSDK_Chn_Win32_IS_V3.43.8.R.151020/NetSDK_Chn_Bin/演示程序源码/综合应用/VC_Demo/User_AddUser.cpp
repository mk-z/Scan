// User_AddUser.cpp : implementation file
//

#include "StdAfx.h"
#include "netsdkdemo.h"
#include "User_AddUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUser_AddUser dialog


CUser_AddUser::CUser_AddUser(CWnd* pParent /*=NULL*/)
	: CDialog(CUser_AddUser::IDD, pParent)
{
	m_user_info = 0;
	m_dev = 0;
	//{{AFX_DATA_INIT(CUser_AddUser)
	//}}AFX_DATA_INIT
}


void CUser_AddUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUser_AddUser)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUser_AddUser, CDialog)
	//{{AFX_MSG_MAP(CUser_AddUser)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUser_AddUser message handlers


BOOL CUser_AddUser::OnInitDialog() 
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
	
	if (!m_user_info || !m_dev)
	{
		return TRUE;
	}
	
	int i;
	CString strRight;
	for (i = 0; i < m_user_info->dwRightNum; i++)
	{
		HTREEITEM hRoot;
		
		strRight.Format("%d: %s : %s", m_user_info->rightList[i].dwID, 
			m_user_info->rightList[i].name, 
			m_user_info->rightList[i].memo);
		hRoot = m_rightList.InsertItem(strRight, 0, 0, TVI_ROOT);
		m_rightList.SetItemData(hRoot, m_user_info->rightList[i].dwID);
		//	m_userList.Expand(hRoot, TVE_EXPAND);
	}

	for (i = 0; i < m_user_info->dwGroupNum; i++)
	{
		if (m_user_info->groupList[i].dwID == m_gpID)
		{
			RefreshRightList(m_user_info->groupList[i].dwRightNum, m_user_info->groupList[i].rights);
			GetDlgItem(IDC_GROUP_EDIT)->SetWindowText(m_user_info->groupList[i].name);
			break;
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUser_AddUser::SetEnvrmt(USER_MANAGE_INFO_EX *info, DWORD gpID, DeviceNode *dev)
{
	m_user_info = info;
	m_gpID = gpID;
	m_dev = dev;
}

void CUser_AddUser::OnBtnOk() 
{
	//construct user info
	USER_INFO urInfo = {0};
	urInfo.dwID = m_user_info->dwUserNum + 1;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowText(urInfo.name, DH_USER_NAME_LENGTH);
	GetDlgItem(IDC_PSW_EDIT)->GetWindowText(urInfo.passWord, DH_USER_PSW_LENGTH);
	GetDlgItem(IDC_MEMO_EDIT)->GetWindowText(urInfo.memo, DH_MEMO_LENGTH);
	urInfo.dwReusable = ((CButton*)GetDlgItem(IDC_CHECK_REUSEABLE))->GetCheck();
	
	urInfo.dwGroupID = m_gpID;

	int count = m_rightList.GetCount();
	HTREEITEM node = m_rightList.GetRootItem();
	int rIndex = 0;
	for (int i=0; i<count && node; i++)
	{
		if (m_rightList.GetCheck(node))
		{
			urInfo.rights[rIndex] = m_rightList.GetItemData(node);
			rIndex++;
		}
		node = m_rightList.GetNextItem(node, TVGN_NEXT);
	}
	urInfo.dwRightNum = rIndex;
	BOOL bRet = CLIENT_OperateUserInfo(m_dev->LoginID, 3/*type: add user*/, &urInfo, 0, 1000);
	if (!bRet)
	{
		MessageBox(ConvertString("Failed to operate user info"));
	}
	else
	{
		EndDialog(0);
	}
}

void CUser_AddUser::RefreshRightList(DWORD dwNum, DWORD *dwList)
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
	for(i=0; i<dwNum; i++)
	{
		DWORD dwData = m_rightList.GetItemData(node);
		for (int j=0; j<count; j++)
		{
			if (dwData == dwList[j])
			{
				m_rightList.SetCheck(node, TRUE);
				break;
			}
		}
		node = m_rightList.GetNextItem(node, TVGN_NEXT);
	}
}
