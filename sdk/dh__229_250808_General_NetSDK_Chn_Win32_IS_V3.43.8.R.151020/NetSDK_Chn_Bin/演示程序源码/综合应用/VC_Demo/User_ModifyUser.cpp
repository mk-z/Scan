// User_ModifyUser.cpp : implementation file
//

#include "StdAfx.h"
#include "netsdkdemo.h"
#include "User_ModifyUser.h"
//#include <atlbase.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUser_ModifyUser dialog


CUser_ModifyUser::CUser_ModifyUser(CWnd* pParent /*=NULL*/)
	: CDialog(CUser_ModifyUser::IDD, pParent)
{
	m_user_info = 0;
	m_dev = 0;
	//{{AFX_DATA_INIT(CUser_ModifyUser)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUser_ModifyUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUser_ModifyUser)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUser_ModifyUser, CDialog)
	//{{AFX_MSG_MAP(CUser_ModifyUser)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUser_ModifyUser message handlers

BOOL CUser_ModifyUser::OnInitDialog() 
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

	DWORD gpId = m_user_info->userList[m_userIdx].dwGroupID;
	for (i = 0; i < m_user_info->dwGroupNum; i++)
	{
		if (m_user_info->groupList[i].dwID == gpId)
		{
			GetDlgItem(IDC_GROUP_EDIT)->SetWindowText(m_user_info->groupList[i].name);
			break;
		}
	}

	GetDlgItem(IDC_NAME_OLD_EDIT)->SetWindowText(m_user_info->userList[m_userIdx].name);
	GetDlgItem(IDC_NAME_NEW_EDIT)->SetWindowText(m_user_info->userList[m_userIdx].name);
	((CButton*)GetDlgItem(IDC_CHECK_REUSEABLE))->SetCheck(m_user_info->userList[m_userIdx].dwFouctionMask);

	GetDlgItem(IDC_MEMO_OLD_EDIT)->SetWindowText(m_user_info->userList[m_userIdx].memo);
	GetDlgItem(IDC_MEMO_NEW_EDIT)->SetWindowText(m_user_info->userList[m_userIdx].memo);
	((CButton*)GetDlgItem(IDC_CHECK_REUSEABLE2))->SetCheck(m_user_info->userList[m_userIdx].dwFouctionMask);

	RefreshRightList(m_user_info->userList[m_userIdx].dwRightNum, m_user_info->userList[m_userIdx].rights);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUser_ModifyUser::SetEnvrmt(USER_MANAGE_INFO_EX *info, DWORD userIdx, DeviceNode *dev)
{
	m_dev = dev;
	m_user_info = info;
	m_userIdx = userIdx;
}

void CUser_ModifyUser::RefreshRightList(DWORD dwNum, DWORD *dwList)
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

void CUser_ModifyUser::OnBtnOk() 
{
	USER_INFO newInfo = {0};
	newInfo.dwID = m_user_info->userList[m_userIdx].dwID;
	GetDlgItem(IDC_NAME_NEW_EDIT)->GetWindowText(newInfo.name, DH_USER_NAME_LENGTH);
	memcpy(newInfo.passWord, m_user_info->userList[m_userIdx].passWord, DH_USER_PSW_LENGTH);
	GetDlgItem(IDC_MEMO_NEW_EDIT)->GetWindowText(newInfo.memo, DH_MEMO_LENGTH);
	newInfo.dwGroupID = m_user_info->userList[m_userIdx].dwGroupID; //这里需验证-linjy
	newInfo.dwReusable = ((CButton*)GetDlgItem(IDC_CHECK_REUSEABLE2))->GetCheck();
	
	int count = m_rightList.GetCount();
	HTREEITEM node = m_rightList.GetRootItem();
	int rIndex = 0;
	for (int i=0; i<count && node; i++)
	{
		if (m_rightList.GetCheck(node))
		{
			newInfo.rights[rIndex] = m_rightList.GetItemData(node);
			rIndex++;
		}
		node = m_rightList.GetNextItem(node, TVGN_NEXT);
	}
	newInfo.dwRightNum = rIndex;
	
	BOOL bRet = CLIENT_OperateUserInfo(m_dev->LoginID, 5, (void *)&newInfo, (void *)&m_user_info->userList[m_userIdx], 1000);
	if (!bRet)
	{
		MessageBox(ConvertString("Failed to operate user info"));
	}
	else
	{
		EndDialog(0);
	}
}
