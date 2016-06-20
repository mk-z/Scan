// User_ModifyGroup.cpp : implementation file
//

#include "StdAfx.h"
#include "netsdkdemo.h"
#include "User_ModifyGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUser_ModifyGroup dialog


CUser_ModifyGroup::CUser_ModifyGroup(CWnd* pParent /*=NULL*/)
	: CDialog(CUser_ModifyGroup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUser_ModifyGroup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUser_ModifyGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUser_ModifyGroup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUser_ModifyGroup, CDialog)
	//{{AFX_MSG_MAP(CUser_ModifyGroup)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUser_ModifyGroup message handlers

BOOL CUser_ModifyGroup::OnInitDialog() 
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
	
	RefreshRightList(m_user_info->groupList[m_gpIdx].dwRightNum, m_user_info->groupList[m_gpIdx].rights);
	
	GetDlgItem(IDC_GPNAME_OLD_EDIT)->SetWindowText(m_user_info->groupList[m_gpIdx].name);
	GetDlgItem(IDC_GPNAME_NEW_EDIT)->SetWindowText(m_user_info->groupList[m_gpIdx].name);
	
	GetDlgItem(IDC_GPMEMO_OLD_EDIT)->SetWindowText(m_user_info->groupList[m_gpIdx].memo);
	GetDlgItem(IDC_GPMEMO_NEW_EDIT)->SetWindowText(m_user_info->groupList[m_gpIdx].memo);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUser_ModifyGroup::SetEnvrmt(USER_MANAGE_INFO_EX *info, DWORD gpIdx, DeviceNode *dev)
{
	m_dev = dev;
	m_user_info = info;
	m_gpIdx = gpIdx;
}

void CUser_ModifyGroup::OnBtnOk() 
{
	USER_GROUP_INFO gpInfo = {0};
	gpInfo.dwID = m_user_info->groupList[m_gpIdx].dwID;
	GetDlgItem(IDC_GPNAME_NEW_EDIT)->GetWindowText(gpInfo.name, DH_USER_NAME_LENGTH);
	GetDlgItem(IDC_GPMEMO_NEW_EDIT)->GetWindowText(gpInfo.memo, DH_MEMO_LENGTH);
	
	int count = m_rightList.GetCount();
	HTREEITEM node = m_rightList.GetRootItem();
	int rIndex = 0;
	for (int i=0; i<count && node; i++)
	{
		if (m_rightList.GetCheck(node))
		{
			gpInfo.rights[rIndex] = m_rightList.GetItemData(node);
			rIndex++;
		}
		node = m_rightList.GetNextItem(node, TVGN_NEXT);
	}
	gpInfo.dwRightNum = rIndex;
	BOOL bRet = CLIENT_OperateUserInfo(m_dev->LoginID, 2, &gpInfo, &m_user_info->groupList[m_gpIdx], 1000);
	if (!bRet)
	{
		MessageBox(ConvertString("Failed to operate user info"));
	}
	else
	{
		EndDialog(0);
	}
}

void CUser_ModifyGroup::RefreshRightList(DWORD dwNum, DWORD *dwList)
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
