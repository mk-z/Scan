// SubDlgCfgDoorOpenTimeSection.cpp : implementation file
//

#include "stdafx.h"
#include "accesscontrol.h"
#include "SubDlgCfgDoorOpenTimeSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgCfgDoorOpenTimeSection dialog


CSubDlgCfgDoorOpenTimeSection::CSubDlgCfgDoorOpenTimeSection(CWnd* pParent /* = NULL */)
	: CDialog(CSubDlgCfgDoorOpenTimeSection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgCfgDoorOpenTimeSection)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_stuDoorTimeSection, 0, sizeof(m_stuDoorTimeSection));
}


void CSubDlgCfgDoorOpenTimeSection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgCfgDoorOpenTimeSection)
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_DTP_ET4, m_dtp4End);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_DTP_ET3, m_dtp3End);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_DTP_ET2, m_dtp2End);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_DTP_ET1, m_dtp1End);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_DTP_ST4, m_dtp4Start);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_DTP_ST3, m_dtp3Start);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_DTP_ST2, m_dtp2Start);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_DTP_ST1, m_dtp1Start);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_CMB_WEEKDAY, m_cmbWeekDay);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_CMB_OPENMETHOD4, m_cmbOpenMethod4);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_CMB_OPENMETHOD3, m_cmbOpenMethod3);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_CMB_OPENMETHOD2, m_cmbOpenMethod2);
	DDX_Control(pDX, IDC_DOOROPENTIMESECTION_CMB_OPENMETHOD1, m_cmbOpenMethod1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgCfgDoorOpenTimeSection, CDialog)
	//{{AFX_MSG_MAP(CSubDlgCfgDoorOpenTimeSection)
	ON_CBN_SELCHANGE(IDC_DOOROPENTIMESECTION_CMB_WEEKDAY, OnSelchangeDooropentimesectionCmbWeekday)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DOOROPENTIMESECTION_DTP_ST1, OnDatetimechangeDooropentimesectionDtpSt1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DOOROPENTIMESECTION_DTP_ET1, OnDatetimechangeDooropentimesectionDtpEt1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DOOROPENTIMESECTION_DTP_ST2, OnDatetimechangeDooropentimesectionDtpSt2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DOOROPENTIMESECTION_DTP_ET2, OnDatetimechangeDooropentimesectionDtpEt2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DOOROPENTIMESECTION_DTP_ST3, OnDatetimechangeDooropentimesectionDtpSt3)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DOOROPENTIMESECTION_DTP_ET3, OnDatetimechangeDooropentimesectionDtpEt3)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DOOROPENTIMESECTION_DTP_ST4, OnDatetimechangeDooropentimesectionDtpSt4)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DOOROPENTIMESECTION_DTP_ET4, OnDatetimechangeDooropentimesectionDtpEt4)
	ON_CBN_SELCHANGE(IDC_DOOROPENTIMESECTION_CMB_OPENMETHOD1, OnSelchangeDooropentimesectionCmbOpenmethod1)
	ON_CBN_SELCHANGE(IDC_DOOROPENTIMESECTION_CMB_OPENMETHOD2, OnSelchangeDooropentimesectionCmbOpenmethod2)
	ON_CBN_SELCHANGE(IDC_DOOROPENTIMESECTION_CMB_OPENMETHOD3, OnSelchangeDooropentimesectionCmbOpenmethod3)
	ON_CBN_SELCHANGE(IDC_DOOROPENTIMESECTION_CMB_OPENMETHOD4, OnSelchangeDooropentimesectionCmbOpenmethod4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgCfgDoorOpenTimeSection private method

void CSubDlgCfgDoorOpenTimeSection::InitDlg()
{
	unsigned int i = 0;

	// week day
	m_cmbWeekDay.ResetContent();
	for (i = 0; i < sizeof(stuDemoWeekDay) / sizeof(stuDemoWeekDay[0]); i++)
	{
		m_cmbWeekDay.InsertString(-1, ConvertString(stuDemoWeekDay[i].pszName));
	}
	m_cmbWeekDay.SetCurSel(0);
	
	// DateTimePickers...
	SYSTEMTIME stStart = {2000,1,1,1}, stEnd = {2000,1,1,1,23,59,59,0};
	m_dtp1Start.SetTime(&stStart);
	m_dtp1End.SetTime(&stEnd);
	m_dtp2Start.SetTime(&stStart);
	m_dtp2End.SetTime(&stEnd);
	m_dtp3Start.SetTime(&stStart);
	m_dtp3End.SetTime(&stEnd);
	m_dtp4Start.SetTime(&stStart);
	m_dtp4End.SetTime(&stEnd);

	// door open method
	m_cmbOpenMethod1.ResetContent();
	m_cmbOpenMethod2.ResetContent();
	m_cmbOpenMethod3.ResetContent();
	m_cmbOpenMethod4.ResetContent();
	for (i = 0; i < sizeof(stuDemoOpenMethod)/sizeof(stuDemoOpenMethod[0]); i++)
	{
		m_cmbOpenMethod1.InsertString(-1, ConvertString(stuDemoOpenMethod[i].szName));
		m_cmbOpenMethod2.InsertString(-1, ConvertString(stuDemoOpenMethod[i].szName));
		m_cmbOpenMethod3.InsertString(-1, ConvertString(stuDemoOpenMethod[i].szName));
		m_cmbOpenMethod4.InsertString(-1, ConvertString(stuDemoOpenMethod[i].szName));
	}
	m_cmbOpenMethod1.SetCurSel(-1);
	m_cmbOpenMethod2.SetCurSel(-1);
	m_cmbOpenMethod3.SetCurSel(-1);
	m_cmbOpenMethod4.SetCurSel(-1);	
}

void CSubDlgCfgDoorOpenTimeSection::StuToDlg()
{
	OnSelchangeDooropentimesectionCmbWeekday();
}

void CSubDlgCfgDoorOpenTimeSection::DlgToStu()
{
	GetTimeSectionFromDlg();
}

void CSubDlgCfgDoorOpenTimeSection::GetTimeSectionFromDlg()
{
	int nSel = m_cmbWeekDay.GetCurSel();
	SYSTEMTIME stBegin = {0}, stEnd = {0};
	for (int i = 0; i < MAX_DOOR_TIME_SECTION; i++)
	{
		CFG_DOOROPEN_TIMESECTION_INFO& stuTimeSection = m_stuDoorTimeSection[(em_WeekDay)nSel][i];
		switch (i)
		{
		case 0:
			stuTimeSection.emDoorOpenMethod = (CFG_DOOR_OPEN_METHOD)m_cmbOpenMethod1.GetCurSel();
			m_dtp1Start.GetTime(&stBegin);
			m_dtp1End.GetTime(&stEnd);
			break;
		case 1:
			stuTimeSection.emDoorOpenMethod = (CFG_DOOR_OPEN_METHOD)m_cmbOpenMethod2.GetCurSel();
			m_dtp2Start.GetTime(&stBegin);
			m_dtp2End.GetTime(&stEnd);
			break;
		case 2:
			stuTimeSection.emDoorOpenMethod = (CFG_DOOR_OPEN_METHOD)m_cmbOpenMethod3.GetCurSel();
			m_dtp3Start.GetTime(&stBegin);
			m_dtp3End.GetTime(&stEnd);
			break;
		case 3:
			stuTimeSection.emDoorOpenMethod = (CFG_DOOR_OPEN_METHOD)m_cmbOpenMethod4.GetCurSel();
			m_dtp4Start.GetTime(&stBegin);
			m_dtp4End.GetTime(&stEnd);
			break;
		}
		DTPToCfgTimePeriod(stBegin, stEnd, stuTimeSection.stuTime);
	}
}

void CSubDlgCfgDoorOpenTimeSection::CfgTimePeriodToDTP(const CFG_TIME_PERIOD& stuTimeSection, SYSTEMTIME& stBegin, SYSTEMTIME& stEnd)
{
	stBegin.wHour	= (WORD)stuTimeSection.stuStartTime.dwHour;
	stBegin.wMinute = (WORD)stuTimeSection.stuStartTime.dwMinute;
	stBegin.wSecond = (WORD)stuTimeSection.stuStartTime.dwSecond;
	stEnd.wHour		= (WORD)stuTimeSection.stuEndTime.dwHour;
	stEnd.wMinute	= (WORD)stuTimeSection.stuEndTime.dwMinute;
	stEnd.wSecond	= (WORD)stuTimeSection.stuEndTime.dwSecond;
}

void CSubDlgCfgDoorOpenTimeSection::DTPToCfgTimePeriod(const SYSTEMTIME& stuStart, const SYSTEMTIME& stuEnd, CFG_TIME_PERIOD& stuPeriod)
{
	stuPeriod.stuStartTime.dwHour = stuStart.wHour;
	stuPeriod.stuStartTime.dwMinute = stuStart.wMinute;
	stuPeriod.stuStartTime.dwSecond = stuStart.wSecond;
	stuPeriod.stuEndTime.dwHour = stuEnd.wHour;
	stuPeriod.stuEndTime.dwMinute = stuEnd.wMinute;
	stuPeriod.stuEndTime.dwSecond = stuEnd.wSecond;
}

void CSubDlgCfgDoorOpenTimeSection::ShowTimeSection(int nSeg, const CFG_DOOROPEN_TIMESECTION_INFO& stuTimeSection)
{
	SYSTEMTIME stBegin = {2000, 1, 1, 1}, stEnd = {2000, 1, 1, 1};
	CfgTimePeriodToDTP(stuTimeSection.stuTime, stBegin, stEnd);
	
	switch (nSeg)
	{
	case 0:
		m_dtp1Start.SetTime(&stBegin);
		m_dtp1End.SetTime(&stEnd);
		m_cmbOpenMethod1.SetCurSel((int)stuTimeSection.emDoorOpenMethod);
		break;
	case 1:
		m_dtp2Start.SetTime(&stBegin);
		m_dtp2End.SetTime(&stEnd);
		m_cmbOpenMethod2.SetCurSel((int)stuTimeSection.emDoorOpenMethod);
		break;
	case 2:
		m_dtp3Start.SetTime(&stBegin);
		m_dtp3End.SetTime(&stEnd);
		m_cmbOpenMethod3.SetCurSel((int)stuTimeSection.emDoorOpenMethod);
		break;
	case 3:
		m_dtp4Start.SetTime(&stBegin);
		m_dtp4End.SetTime(&stEnd);
		m_cmbOpenMethod4.SetCurSel((int)stuTimeSection.emDoorOpenMethod);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSubDlgCfgDoorOpenTimeSection message handlers

BOOL CSubDlgCfgDoorOpenTimeSection::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this, SUBDLG_CFG_DOOROPEN_TIMESECTION);
	// TODO: Add extra initialization here
	InitDlg();
	StuToDlg();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgCfgDoorOpenTimeSection::OnSelchangeDooropentimesectionCmbWeekday() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbWeekDay.GetCurSel();
	if (-1 == nSel)
	{
		return;
	}
	
	for (int i = 0; i < MAX_DOOR_TIME_SECTION; i++)
	{
		ShowTimeSection(i, m_stuDoorTimeSection[nSel][i]);
	}
}

void CSubDlgCfgDoorOpenTimeSection::OnDatetimechangeDooropentimesectionDtpSt1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CSubDlgCfgDoorOpenTimeSection::OnDatetimechangeDooropentimesectionDtpEt1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CSubDlgCfgDoorOpenTimeSection::OnDatetimechangeDooropentimesectionDtpSt2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CSubDlgCfgDoorOpenTimeSection::OnDatetimechangeDooropentimesectionDtpEt2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CSubDlgCfgDoorOpenTimeSection::OnDatetimechangeDooropentimesectionDtpSt3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CSubDlgCfgDoorOpenTimeSection::OnDatetimechangeDooropentimesectionDtpEt3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CSubDlgCfgDoorOpenTimeSection::OnDatetimechangeDooropentimesectionDtpSt4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CSubDlgCfgDoorOpenTimeSection::OnDatetimechangeDooropentimesectionDtpEt4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CSubDlgCfgDoorOpenTimeSection::OnSelchangeDooropentimesectionCmbOpenmethod1() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
}

void CSubDlgCfgDoorOpenTimeSection::OnSelchangeDooropentimesectionCmbOpenmethod2() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
}

void CSubDlgCfgDoorOpenTimeSection::OnSelchangeDooropentimesectionCmbOpenmethod3() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
}

void CSubDlgCfgDoorOpenTimeSection::OnSelchangeDooropentimesectionCmbOpenmethod4() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
}
