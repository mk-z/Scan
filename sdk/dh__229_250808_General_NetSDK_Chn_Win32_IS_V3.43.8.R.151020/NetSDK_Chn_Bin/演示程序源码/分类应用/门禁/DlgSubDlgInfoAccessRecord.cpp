// DlgSubDlgInfoAccessRecord.cpp : implementation file
//

#include "stdafx.h"
#include "accesscontrol.h"
#include "DlgSubDlgInfoAccessRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoAccessRecord dialog


CDlgSubDlgInfoAccessRecord::CDlgSubDlgInfoAccessRecord(CWnd* pParent /*=NULL*/, NET_RECORDSET_ACCESS_CTL_CARDREC* p)
	: CDialog(CDlgSubDlgInfoAccessRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSubDlgInfoAccessRecord)
	m_csCardNo = _T("");
	m_nDoorNo = 0;
	m_csPwd = _T("");
	m_nRecNo = 0;
	//}}AFX_DATA_INIT
	memset(&m_stuInfo, 0, sizeof(m_stuInfo));
	if (p != NULL)
	{
		memcpy(&m_stuInfo, p, sizeof(NET_RECORDSET_ACCESS_CTL_CARDREC));
	}
	m_stuInfo.dwSize = sizeof(m_stuInfo);

	m_emOperateType = Em_Operate_Type_Show;
}


void CDlgSubDlgInfoAccessRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSubDlgInfoAccessRecord)
	DDX_Control(pDX, IDC_SUBDLG_INFO_ACCESS_DATETIMEPICKER_TIME, m_Time);
	DDX_Control(pDX, IDC_SUBDLG_INFO_ACCESS_DATETIMEPICKER_DATE, m_Date);
	DDX_Control(pDX, IDC_SUBDLG_INFO_ACCESS_COMBO_METHOD, m_cmbMethod);
	DDX_Control(pDX, IDC_SUBDLG_INFO_ACCESS_CHECK_STATUS, m_ckStatus);
	DDX_Text(pDX, IDC_SUBDLG_INFO_ACCESS_EDIT_CARDNO, m_csCardNo);
	DDX_Text(pDX, IDC_SUBDLG_INFO_ACCESS_EDIT_DOORNO, m_nDoorNo);
	DDX_Text(pDX, IDC_SUBDLG_INFO_ACCESS_EDIT_PWD, m_csPwd);
	DDX_Text(pDX, IDC_SUBDLG_INFO_ACCESS_EDIT_RECNO, m_nRecNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSubDlgInfoAccessRecord, CDialog)
	//{{AFX_MSG_MAP(CDlgSubDlgInfoAccessRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoAccessRecord private method

void CDlgSubDlgInfoAccessRecord::InitDlg()
{
	m_cmbMethod.ResetContent();
	for (int i = 0; i < sizeof(stuDemoMethod) / sizeof(stuDemoMethod[0]); i++)
	{
		m_cmbMethod.InsertString(-1, ConvertString(stuDemoMethod[i].pszName, SUBDLG_INFO_ACCESS));
	}
    m_cmbMethod.SetDroppedWidth(160);
	
	if (Em_Operate_Type_Show == m_emOperateType)
	{
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_EDIT_RECNO)->EnableWindow(FALSE);
		StuToDlg();
	}
	else if (Em_Operate_Type_Insert == m_emOperateType)
	{
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_EDIT_RECNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Get == m_emOperateType)
	{
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_EDIT_RECNO)->EnableWindow();
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_EDIT_CARDNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_EDIT_PWD)->EnableWindow(FALSE);
		m_Date.EnableWindow(FALSE);
		m_Time.EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_CHECK_STATUS)->EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_COMBO_METHOD)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Update == m_emOperateType)
	{
		StuToDlg();
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_EDIT_RECNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Remove == m_emOperateType)
	{
		StuToDlg();
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_EDIT_RECNO)->EnableWindow();
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_EDIT_CARDNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_EDIT_PWD)->EnableWindow(FALSE);
		m_Date.EnableWindow(FALSE);
		m_Time.EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_CHECK_STATUS)->EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_ACCESS_COMBO_METHOD)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Clear == m_emOperateType)
	{
		// ...
	}
}

void CDlgSubDlgInfoAccessRecord::StuToDlg()
{
	// RecNo
	SetDlgItemInt(IDC_SUBDLG_INFO_ACCESS_EDIT_RECNO, m_stuInfo.nRecNo);
	
	// card
	SetDlgItemText(IDC_SUBDLG_INFO_ACCESS_EDIT_CARDNO, m_stuInfo.szCardNo);
	
	// pwd
	SetDlgItemText(IDC_SUBDLG_INFO_ACCESS_EDIT_PWD, m_stuInfo.szPwd);
	
	// time
	SYSTEMTIME st = {0};
	st.wYear	= (WORD)m_stuInfo.stuTime.dwYear;
	st.wMonth	= (WORD)m_stuInfo.stuTime.dwMonth;
	st.wDay		= (WORD)m_stuInfo.stuTime.dwDay;
	m_Date.SetTime(&st);
	st.wHour	= (WORD)m_stuInfo.stuTime.dwHour;
	st.wMinute	= (WORD)m_stuInfo.stuTime.dwMinute;
	st.wSecond	= (WORD)m_stuInfo.stuTime.dwSecond;
	m_Time.SetTime(&st);
	
	// status
	m_ckStatus.SetCheck(m_stuInfo.bStatus ? BST_CHECKED : BST_UNCHECKED);
	
	// open method
    BOOL bMethodFound = FALSE;
    for (int i = 0; i < sizeof(stuDemoMethod)/sizeof(stuDemoMethod[0]); i++)
    {
        if (m_stuInfo.emMethod == stuDemoMethod[i].emMethod)
        {
            bMethodFound = TRUE;
            m_cmbMethod.SetCurSel(i);
            break;
        }
    }
    if (!bMethodFound)
    {
        m_cmbMethod.SetCurSel(-1);
    }
	
	// door
	SetDlgItemInt(IDC_SUBDLG_INFO_ACCESS_EDIT_DOORNO, m_stuInfo.nDoor);
}

void CDlgSubDlgInfoAccessRecord::DlgToStu()
{
	// RecNo
	m_stuInfo.nRecNo = GetDlgItemInt(IDC_SUBDLG_INFO_ACCESS_EDIT_RECNO);
	
	// card
	GetDlgItemText(IDC_SUBDLG_INFO_ACCESS_EDIT_CARDNO, m_stuInfo.szCardNo, sizeof(m_stuInfo.szCardNo) - 1);
	
	// pwd
	GetDlgItemText(IDC_SUBDLG_INFO_ACCESS_EDIT_PWD, m_stuInfo.szPwd, sizeof(m_stuInfo.szPwd) - 1);
	
	// time
	SYSTEMTIME st = {0};
	m_Date.GetTime(&st);
	m_stuInfo.stuTime.dwYear = st.wYear;
	m_stuInfo.stuTime.dwMonth = st.wMonth;
	m_stuInfo.stuTime.dwDay = st.wDay;
	m_Time.GetTime(&st);
	m_stuInfo.stuTime.dwHour = st.wHour;
	m_stuInfo.stuTime.dwMinute = st.wMinute;
	m_stuInfo.stuTime.dwSecond = st.wSecond;
	
	// status
	if (m_ckStatus.GetCheck())
	{
		m_stuInfo.bStatus = TRUE;
	}
	else
	{
		m_stuInfo.bStatus = FALSE;
	}
	
	// open method
    int nMethodIndex = m_cmbMethod.GetCurSel();
    if (nMethodIndex > 0 && nMethodIndex < sizeof(stuDemoMethod)/sizeof(stuDemoMethod[0]))
    {
        m_stuInfo.emMethod = (NET_ACCESS_DOOROPEN_METHOD)stuDemoMethod[nMethodIndex].emMethod;
    }
    else
    {
        m_stuInfo.emMethod = NET_ACCESS_DOOROPEN_METHOD_UNKNOWN;
    }
	
	// door
	m_stuInfo.nDoor = GetDlgItemInt(IDC_SUBDLG_INFO_ACCESS_EDIT_DOORNO);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoAccessRecord message handlers

BOOL CDlgSubDlgInfoAccessRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	g_SetWndStaticText(this, SUBDLG_INFO_ACCESS);
	// TODO: Add extra initialization here
	InitDlg();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSubDlgInfoAccessRecord::OnOK() 
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
