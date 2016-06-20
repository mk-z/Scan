// DlgSubDlgInfoPassword.cpp : implementation file
//

#include "stdafx.h"
#include "accesscontrol.h"
#include "DlgSubDlgInfoPassword.h"
#include "SubDlgSensorInfoDescription.h"
#include <VECTOR>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoPassword dialog


CDlgSubDlgInfoPassword::CDlgSubDlgInfoPassword(CWnd* pParent /* = NULL */, NET_RECORDSET_ACCESS_CTL_PWD* p /* = NULL */, int nAccess /* = 1 */)
	: CDialog(CDlgSubDlgInfoPassword::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSubDlgInfoPassword)
	//}}AFX_DATA_INIT
	memset(&m_stuInfo, 0, sizeof(m_stuInfo));
	if (p != NULL)
	{
		memcpy(&m_stuInfo, p, sizeof(NET_RECORDSET_ACCESS_CTL_PWD));
	}
	m_stuInfo.dwSize = sizeof(m_stuInfo);
	
	m_emOperateType = Em_Operate_Type_Show;
    m_nAccessGroup  = nAccess;
}


void CDlgSubDlgInfoPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSubDlgInfoPassword)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSubDlgInfoPassword, CDialog)
	//{{AFX_MSG_MAP(CDlgSubDlgInfoPassword)
	ON_BN_CLICKED(IDC_SUBDLG_INFO_PASSWORD_BTN_DOORS, OnSubdlgInfoPasswordBtnDoors)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoPassword private method

void CDlgSubDlgInfoPassword::InitDlg()
{
	
	if (Em_Operate_Type_Show == m_emOperateType)
	{
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_RECNO)->EnableWindow(FALSE);
		StuToDlg();
	}
	else if (Em_Operate_Type_Insert == m_emOperateType)
	{
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_RECNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Get == m_emOperateType)
	{
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_RECNO)->EnableWindow();
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_USERID)->EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_DOOROPENPWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_ALARMPWD)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Update == m_emOperateType)
	{
		StuToDlg();
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_RECNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Remove == m_emOperateType)
	{
		StuToDlg();
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_RECNO)->EnableWindow();
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_USERID)->EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_DOOROPENPWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_PASSWORD_EDIT_ALARMPWD)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Clear == m_emOperateType)
	{
		// ...
	}
}

void CDlgSubDlgInfoPassword::StuToDlg()
{
	// RecNo
	SetDlgItemInt(IDC_SUBDLG_INFO_PASSWORD_EDIT_RECNO, m_stuInfo.nRecNo);
	
	// user id
	SetDlgItemText(IDC_SUBDLG_INFO_PASSWORD_EDIT_USERID, m_stuInfo.szUserID);

	// pwd of opening door
	SetDlgItemText(IDC_SUBDLG_INFO_PASSWORD_EDIT_DOOROPENPWD, m_stuInfo.szDoorOpenPwd);

	// pwd of alarm
	SetDlgItemText(IDC_SUBDLG_INFO_PASSWORD_EDIT_ALARMPWD, m_stuInfo.szAlarmPwd);

	// doors
}

void CDlgSubDlgInfoPassword::DlgToStu()
{	
	// RecNo
	m_stuInfo.nRecNo = GetDlgItemInt(IDC_SUBDLG_INFO_PASSWORD_EDIT_RECNO, NULL, TRUE);

	// user id
	GetDlgItemText(IDC_SUBDLG_INFO_PASSWORD_EDIT_USERID, m_stuInfo.szUserID, sizeof(m_stuInfo.szUserID) - 1);

	// pwd of opening door
	GetDlgItemText(IDC_SUBDLG_INFO_PASSWORD_EDIT_DOOROPENPWD, m_stuInfo.szDoorOpenPwd, sizeof(m_stuInfo.szDoorOpenPwd) - 1);

	// pwd of alarm
	GetDlgItemText(IDC_SUBDLG_INFO_PASSWORD_EDIT_ALARMPWD, m_stuInfo.szAlarmPwd, sizeof(m_stuInfo.szAlarmPwd) - 1);

	// doos
}

BOOL CDlgSubDlgInfoPassword::Get()
{
	m_stuInfo.nRecNo = GetDlgItemInt(IDC_SUBDLG_INFO_PASSWORD_EDIT_RECNO, NULL, TRUE);
	return TRUE;
}

BOOL CDlgSubDlgInfoPassword::Update()
{
	return TRUE;
}

BOOL CDlgSubDlgInfoPassword::Remove()
{
	return TRUE;
}

void CDlgSubDlgInfoPassword::Clear()
{
	
}

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoPassword message handlers

void CDlgSubDlgInfoPassword::OnSubdlgInfoPasswordBtnDoors() 
{
	// TODO: Add your control notification handler code here
	std::vector<int> vecChn;
	int i = 0;
	for (; i < __min(m_stuInfo.nDoorNum, DH_MAX_DOOR_NUM); i++)
	{
		vecChn.push_back(m_stuInfo.sznDoors[i]);
	}
	
	CSubDlgSensorInfoDescription dlg(this, m_nAccessGroup);
	dlg.SetID(vecChn);
	if (IDOK == dlg.DoModal())
	{
		if (Em_Operate_Type_Insert == m_emOperateType
			|| Em_Operate_Type_Update == m_emOperateType)
		{
			vecChn.clear();
			vecChn = dlg.GetID();
			std::vector<int>::iterator it = vecChn.begin();
			for (i = 0; i < __min(vecChn.size(), DH_MAX_DOOR_NUM) && it != vecChn.end(); i++, it++)
			{
				m_stuInfo.sznDoors[i] = *it;
			}
			m_stuInfo.nDoorNum = __min(vecChn.size(), DH_MAX_DOOR_NUM);
		}
	}
}

BOOL CDlgSubDlgInfoPassword::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	g_SetWndStaticText(this, SUBDLG_INFO_PWD);
	// TODO: Add extra initialization here
	InitDlg();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSubDlgInfoPassword::OnOK() 
{
	// TODO: Add extra validation here
	switch (m_emOperateType)
	{
	case Em_Operate_Type_Show:
		{
			StuToDlg();
		}
		break;
	case Em_Operate_Type_Insert:
		{
			DlgToStu();
		}
		break;
	case Em_Operate_Type_Get:
		{
			DlgToStu();
		}
	case Em_Operate_Type_Update:
		{
			DlgToStu();
		}
		break;
	case Em_Operate_Type_Remove:
		{
			DlgToStu();
		}
		break;
	case Em_Operate_Type_Clear:
		break;
	default:
		break;
	}
	CDialog::OnOK();
}
