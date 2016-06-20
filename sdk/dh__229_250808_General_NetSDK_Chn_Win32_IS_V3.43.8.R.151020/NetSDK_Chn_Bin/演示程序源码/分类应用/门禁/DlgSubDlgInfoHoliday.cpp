// DlgSubDlgInfoHoliday.cpp : implementation file
//

#include "stdafx.h"
#include "accesscontrol.h"
#include "DlgSubDlgInfoHoliday.h"
#include "SubDlgSensorInfoDescription.h"
#include <VECTOR>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoHoliday dialog


CDlgSubDlgInfoHoliday::CDlgSubDlgInfoHoliday(CWnd* pParent /* = NULL */, NET_RECORDSET_HOLIDAY* p /* = NULL */, int nAccess /* = 1 */)
	: CDialog(CDlgSubDlgInfoHoliday::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSubDlgInfoHoliday)
	//}}AFX_DATA_INIT
	memset(&m_stuInfo, 0, sizeof(m_stuInfo));
	if (p != NULL)
	{
		memcpy(&m_stuInfo, p, sizeof(NET_RECORDSET_HOLIDAY));
	}
	m_stuInfo.dwSize = sizeof(m_stuInfo);

	m_emOperateType = Em_Operate_Type_Show;
    m_nAccessGroup  = nAccess;
}


void CDlgSubDlgInfoHoliday::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSubDlgInfoHoliday)
	DDX_Control(pDX, IDC_SUBDLG_INFO_HOLIDAY_DATETIMEPICKER_STARTDATE, m_StartDate);
	DDX_Control(pDX, IDC_SUBDLG_INFO_HOLIDAY_DATETIMEPICKER_ENDDATE, m_EndDate);
	DDX_Control(pDX, IDC_SUBDLG_INFO_HOLIDAY_CHECK_ENABLE, m_ckEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSubDlgInfoHoliday, CDialog)
	//{{AFX_MSG_MAP(CDlgSubDlgInfoHoliday)
	ON_BN_CLICKED(IDC_SUBDLG_INFO_HOLIDAY_BUTTON_DOORS, OnSubdlgInfoHolidayButtonDoors)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoHoliday private method

void CDlgSubDlgInfoHoliday::InitDlg()
{
	if (Em_Operate_Type_Show == m_emOperateType)
	{
		GetDlgItem(IDC_SUBDLG_INFO_HOLIDAY_EDIT_RECNO)->EnableWindow(FALSE);
		StuToDlg();
	}
	else if (Em_Operate_Type_Insert == m_emOperateType)
	{
		GetDlgItem(IDC_SUBDLG_INFO_HOLIDAY_EDIT_RECNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Get == m_emOperateType)
	{
		GetDlgItem(IDC_SUBDLG_INFO_HOLIDAY_EDIT_RECNO)->EnableWindow();
		m_StartDate.EnableWindow(FALSE);
		m_EndDate.EnableWindow(FALSE);
		GetDlgItem(IDC_SUBDLG_INFO_HOLIDAY_CHECK_ENABLE)->EnableWindow(FALSE);
        GetDlgItem(IDC_SUBDLG_INFO_HOLIDAY_EDIT_HOLIDAYNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Update == m_emOperateType)
	{
		StuToDlg();
		GetDlgItem(IDC_SUBDLG_INFO_HOLIDAY_EDIT_RECNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Remove == m_emOperateType)
	{
		StuToDlg();
		GetDlgItem(IDC_SUBDLG_INFO_HOLIDAY_EDIT_RECNO)->EnableWindow();
		m_StartDate.EnableWindow(FALSE);
		m_EndDate.EnableWindow(FALSE);
        GetDlgItem(IDC_SUBDLG_INFO_HOLIDAY_CHECK_ENABLE)->EnableWindow(FALSE);
        GetDlgItem(IDC_SUBDLG_INFO_HOLIDAY_EDIT_HOLIDAYNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Clear == m_emOperateType)
	{
		// ...
	}	
}

void CDlgSubDlgInfoHoliday::StuToDlg()
{
	// RecNo
	SetDlgItemInt(IDC_SUBDLG_INFO_HOLIDAY_EDIT_RECNO, m_stuInfo.nRecNo);
	
	// enable
	m_ckEnable.SetCheck(m_stuInfo.bEnable ? BST_CHECKED : BST_UNCHECKED);
	
	// start time
	SYSTEMTIME st = {0};
	st.wYear	= (WORD)m_stuInfo.stuStartTime.dwYear;
	st.wMonth	= (WORD)m_stuInfo.stuStartTime.dwMonth;
	st.wDay		= (WORD)m_stuInfo.stuStartTime.dwDay;
	m_StartDate.SetTime(&st);
	
	// end time
	st.wYear	= (WORD)m_stuInfo.stuEndTime.dwYear;
	st.wMonth	= (WORD)m_stuInfo.stuEndTime.dwMonth;
	st.wDay		= (WORD)m_stuInfo.stuEndTime.dwDay;
	m_EndDate.SetTime(&st);
	
	// door

    // holiday no
    SetDlgItemText(IDC_SUBDLG_INFO_HOLIDAY_EDIT_HOLIDAYNO, m_stuInfo.szHolidayNo);
}

void CDlgSubDlgInfoHoliday::DlgToStu()
{
	// RecNo
	m_stuInfo.nRecNo = GetDlgItemInt(IDC_SUBDLG_INFO_HOLIDAY_EDIT_RECNO);
	
	// enable
	if (m_ckEnable.GetCheck())
	{
		m_stuInfo.bEnable = TRUE;
	}
	else 
	{
		m_stuInfo.bEnable = FALSE;
	}
	
	// start time
	SYSTEMTIME st = {0};
	m_StartDate.GetTime(&st);
	m_stuInfo.stuStartTime.dwYear = st.wYear;
	m_stuInfo.stuStartTime.dwMonth = st.wMonth;
	m_stuInfo.stuStartTime.dwDay = st.wDay;
	
	// end time
	m_EndDate.GetTime(&st);
	m_stuInfo.stuEndTime.dwYear = st.wYear;
	m_stuInfo.stuEndTime.dwMonth = st.wMonth;
	m_stuInfo.stuEndTime.dwDay = st.wDay;
	
	// door

    // holiday no
    GetDlgItemText(IDC_SUBDLG_INFO_HOLIDAY_EDIT_HOLIDAYNO, m_stuInfo.szHolidayNo, sizeof(m_stuInfo.szHolidayNo) - 1);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoHoliday message handlers

BOOL CDlgSubDlgInfoHoliday::OnInitDialog() 
{
	CDialog::OnInitDialog();

	g_SetWndStaticText(this, SUBDLG_INFO_HOLIDAY);
	// TODO: Add extra initialization here
	InitDlg();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSubDlgInfoHoliday::OnSubdlgInfoHolidayButtonDoors() 
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

void CDlgSubDlgInfoHoliday::OnOK() 
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
