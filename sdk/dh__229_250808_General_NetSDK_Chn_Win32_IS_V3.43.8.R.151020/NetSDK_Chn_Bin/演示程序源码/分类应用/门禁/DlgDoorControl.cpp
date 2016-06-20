// DlgDoorControl.cpp : implementation file
//

#include "stdafx.h"
#include "AccessControl.h"
#include "DlgDoorControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDoorControl dialog


CDlgDoorControl::CDlgDoorControl(CWnd* pParent /* = NULL */, LLONG lLoginID /* = 0 */)
	: CDialog(CDlgDoorControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDoorControl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lLoginID = lLoginID;
}


void CDlgDoorControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDoorControl)
	DDX_Control(pDX, IDC_DOORCTL_CMB_STATUS, m_cmbDoorStatus);
	DDX_Control(pDX, IDC_DOORCTL_CMB_CHN, m_cmbChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDoorControl, CDialog)
	//{{AFX_MSG_MAP(CDlgDoorControl)
	ON_BN_CLICKED(IDC_DOORCTL_BTN_OPEN, OnDoorctlBtnOpen)
	ON_BN_CLICKED(IDC_DOORCTL_BTN_CLOSE, OnDoorctlBtnClose)
	ON_BN_CLICKED(IDC_DOORCTL_BTN_QUERY, OnDoorctlBtnQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDoorControl private method

void CDlgDoorControl::InitDlg()
{
	int i = 0;

	m_cmbChannel.ResetContent();
	for (i = 0; i < 4; i++)
	{
		CString csInfo;
		csInfo.Format("%s%d", ConvertString("Channel", DLG_DOOR_CONTROL), i + 1);
		m_cmbChannel.InsertString(-1, csInfo);
	}
	m_cmbChannel.SetCurSel(0);

	m_cmbDoorStatus.ResetContent();
	for (i = 0; i < sizeof(stuDemoDoorStatus)/sizeof(stuDemoDoorStatus[0]); i++)
	{
		m_cmbDoorStatus.InsertString(-1, ConvertString(stuDemoDoorStatus[i].szInfo, DLG_DOOR_CONTROL));
	}
	m_cmbDoorStatus.SetCurSel(-1);
}


/////////////////////////////////////////////////////////////////////////////
// CDlgDoorControl message handlers

BOOL CDlgDoorControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this, DLG_DOOR_CONTROL);
	// TODO: Add extra initialization here
	InitDlg();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDoorControl::OnDoorctlBtnOpen() 
{
	// TODO: Add your control notification handler code here
	NET_CTRL_ACCESS_OPEN stuParam = {sizeof(stuParam)};
	stuParam.nChannelID = m_cmbChannel.GetCurSel();
	BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_ACCESS_OPEN, &stuParam, 3000);
	if (bRet)
	{
		CString csInfo;
		csInfo.Format("%s %d ok", ConvertString("Open door", DLG_DOOR_CONTROL), stuParam.nChannelID + 1);
		MessageBox(csInfo, ConvertString("Prompt"));
	}
	else
	{
		CString csInfo;
		csInfo.Format("%s %d failed:0x%08x", ConvertString("Open door", DLG_DOOR_CONTROL), stuParam.nChannelID + 1, CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
}

void CDlgDoorControl::OnDoorctlBtnClose() 
{
	// TODO: Add your control notification handler code here
	NET_CTRL_ACCESS_CLOSE stuParam = {sizeof(stuParam)};
	stuParam.nChannelID = m_cmbChannel.GetCurSel();
	BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_ACCESS_CLOSE, &stuParam, 3000);
	if (bRet)
	{
		CString csInfo;
		csInfo.Format("%s %d ok", ConvertString("Close door", DLG_DOOR_CONTROL), stuParam.nChannelID + 1);
		MessageBox(csInfo, ConvertString("Prompt"));
	}
	else
	{
		CString csInfo;
		csInfo.Format("%s %d failed:0x%08x", ConvertString("Close door", DLG_DOOR_CONTROL), stuParam.nChannelID + 1, CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}	
}

void CDlgDoorControl::OnDoorctlBtnQuery() 
{
	// TODO: Add your control notification handler code here
	NET_DOOR_STATUS_INFO stuParam = {sizeof(stuParam)};
	stuParam.nChannel = m_cmbChannel.GetCurSel();
	int nRetLen = 0;
	BOOL bRet = CLIENT_QueryDevState(m_lLoginID, DH_DEVSTATE_DOOR_STATE, (char*)&stuParam, sizeof(stuParam), &nRetLen, 3000);
	if (bRet)
	{
		m_cmbDoorStatus.SetCurSel((int)stuParam.emStateType);
	} 
	else
	{
		CString csInfo;
		csInfo.Format("%s:0x%08x", ConvertString("Query door status failed", DLG_DOOR_CONTROL), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
}
