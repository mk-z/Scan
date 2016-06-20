// User_ModifyPsw.cpp : implementation file
//

#include "StdAfx.h"
#include "netsdkdemo.h"
#include "User_ModifyPsw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUser_ModifyPsw dialog


CUser_ModifyPsw::CUser_ModifyPsw(CWnd* pParent /*=NULL*/)
	: CDialog(CUser_ModifyPsw::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUser_ModifyPsw)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUser_ModifyPsw::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUser_ModifyPsw)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUser_ModifyPsw, CDialog)
	//{{AFX_MSG_MAP(CUser_ModifyPsw)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUser_ModifyPsw message handlers

BOOL CUser_ModifyPsw::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	if (!m_dev || !m_user_info)
	{
		return TRUE;
	}

	GetDlgItem(IDC_NAME_EDIT)->SetWindowText(m_user_info->userList[m_userIdx].name);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUser_ModifyPsw::SetEnvrmt(USER_MANAGE_INFO_EX *info, DWORD userIdx, DeviceNode *dev)
{
	m_dev = dev;
	m_user_info = info;
	m_userIdx = userIdx;
}

void CUser_ModifyPsw::OnBtnOk() 
{
	USER_INFO newInfo = {0};
	USER_INFO oldInfo = {0};
	char tmp1[DH_USER_PSW_LENGTH] = {0};
	char tmp2[DH_USER_PSW_LENGTH] = {0};
	GetDlgItem(IDC_NEW_PSW_EDIT1)->GetWindowText(tmp1, DH_USER_PSW_LENGTH);
	GetDlgItem(IDC_NEW_PSW_EDIT2)->GetWindowText(tmp2, DH_USER_PSW_LENGTH);
	if (strcmp(tmp1, tmp2) != 0)
	{
		MessageBox(ConvertString("Illegal input"));
		return;
	}

	memcpy(newInfo.passWord, tmp1, DH_USER_PSW_LENGTH);

	memcpy(oldInfo.name, m_user_info->userList[m_userIdx].name, DH_USER_PSW_LENGTH);
	GetDlgItem(IDC_OLD_PSW_EDIT)->GetWindowText(tmp1, DH_USER_PSW_LENGTH);
	memcpy(oldInfo.passWord, tmp1, DH_USER_PSW_LENGTH);

	BOOL bRet = CLIENT_OperateUserInfo(m_dev->LoginID, 6, (void *)&newInfo, &oldInfo, 1000);
	if (!bRet)
	{
		MessageBox(ConvertString("Failed to operate user info"));
	}
	else
	{
		EndDialog(0);
	}
}
