// DlgCfgTimeSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "accesscontrol.h"
#include "DlgCfgTimeSchedule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgTimeSchedule dialog


CDlgCfgTimeSchedule::CDlgCfgTimeSchedule(CWnd* pParent /* = NULL */, LLONG lLoginID /* = 0 */)
	: CDialog(CDlgCfgTimeSchedule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgTimeSchedule)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lLoginID = lLoginID;
	memset(&m_stuInfo, 0, sizeof(m_stuInfo));
}


void CDlgCfgTimeSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgTimeSchedule)
	DDX_Control(pDX, IDC_TIMESCHEDULE_DTP4_START, m_dtp4Start);
	DDX_Control(pDX, IDC_TIMESCHEDULE_DTP3_START, m_dtp3Start);
	DDX_Control(pDX, IDC_TIMESCHEDULE_DTP2_START, m_dtp2Start);
	DDX_Control(pDX, IDC_TIMESCHEDULE_DTP1_START, m_dtp1Start);
	DDX_Control(pDX, IDC_TIMESCHEDULE_DTP4_END, m_dtp4End);
	DDX_Control(pDX, IDC_TIMESCHEDULE_DTP3_END, m_dtp3End);
	DDX_Control(pDX, IDC_TIMESCHEDULE_DTP2_END, m_dtp2End);
	DDX_Control(pDX, IDC_TIMESCHEDULE_DTP1_END, m_dtp1End);
	DDX_Control(pDX, IDC_TIMESCHEDULE_CMB_WEEKDAY, m_cmbWeekDay);
	DDX_Control(pDX, IDC_TIMESCHEDULE_CMB_INDEX, m_cmbIndex);
	DDX_Control(pDX, IDC_TIMESCHEDULE_CHK_SEG4_ENABLE, m_chkSeg4);
	DDX_Control(pDX, IDC_TIMESCHEDULE_CHK_SEG3_ENABLE, m_chkSeg3);
	DDX_Control(pDX, IDC_TIMESCHEDULE_CHK_SEG2_ENABLE, m_chkSeg2);
	DDX_Control(pDX, IDC_TIMESCHEDULE_CHK_SEG1_ENABLE, m_chkSeg1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgTimeSchedule, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgTimeSchedule)
	ON_BN_CLICKED(IDC_TIMESCHEDULE_BTN_GET, OnTimescheduleBtnGet)
	ON_BN_CLICKED(IDC_TIMESCHEDULE_BTN_SET, OnTimescheduleBtnSet)
	ON_CBN_SELCHANGE(IDC_TIMESCHEDULE_CMB_INDEX, OnSelchangeTimescheduleCmbIndex)
	ON_CBN_SELCHANGE(IDC_TIMESCHEDULE_CMB_WEEKDAY, OnSelchangeTimescheduleCmbWeekday)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIMESCHEDULE_DTP1_START, OnDatetimechangeTimescheduleDtp1Start)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIMESCHEDULE_DTP1_END, OnDatetimechangeTimescheduleDtp1End)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIMESCHEDULE_DTP2_START, OnDatetimechangeTimescheduleDtp2Start)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIMESCHEDULE_DTP2_END, OnDatetimechangeTimescheduleDtp2End)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIMESCHEDULE_DTP3_START, OnDatetimechangeTimescheduleDtp3Start)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIMESCHEDULE_DTP3_END, OnDatetimechangeTimescheduleDtp3End)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIMESCHEDULE_DTP4_START, OnDatetimechangeTimescheduleDtp4Start)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIMESCHEDULE_DTP4_END, OnDatetimechangeTimescheduleDtp4End)
	ON_BN_CLICKED(IDC_TIMESCHEDULE_CHK_SEG1_ENABLE, OnTimescheduleChkSeg1Enable)
	ON_BN_CLICKED(IDC_TIMESCHEDULE_CHK_SEG2_ENABLE, OnTimescheduleChkSeg2Enable)
	ON_BN_CLICKED(IDC_TIMESCHEDULE_CHK_SEG3_ENABLE, OnTimescheduleChkSeg3Enable)
	ON_BN_CLICKED(IDC_TIMESCHEDULE_CHK_SEG4_ENABLE, OnTimescheduleChkSeg4Enable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgTimeSchedule private method

void CDlgCfgTimeSchedule::InitDlg()
{
	unsigned int i = 0;

	// Index
	m_cmbIndex.ResetContent();
	for (i = 0; i < 128; i++)
	{
		CString csInfo;
		csInfo.Format("%d", i + 1);
		m_cmbIndex.InsertString(-1, csInfo);
	}
	m_cmbIndex.SetCurSel(0);
	
	// WeekDay
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
	m_chkSeg1.SetCheck(BST_UNCHECKED);
	m_chkSeg2.SetCheck(BST_UNCHECKED);
	m_chkSeg3.SetCheck(BST_UNCHECKED);
	m_chkSeg4.SetCheck(BST_UNCHECKED);
}

void CDlgCfgTimeSchedule::StuToDlg()
{
	OnSelchangeTimescheduleCmbWeekday();
}

void CDlgCfgTimeSchedule::DlgToStu()
{
	GetTimeSectionFromDlg();
}

BOOL CDlgCfgTimeSchedule::GetConfigFromDevice()
{
	int nChn = m_cmbIndex.GetCurSel();
	if (-1 == nChn)
	{
		return FALSE;
	}
	
	char szJsonBuf[1024 * 40] = {0};
	int nerror = 0;
	BOOL bRet = CLIENT_GetNewDevConfig((LLONG)m_lLoginID, CFG_CMD_ACCESSTIMESCHEDULE, nChn, szJsonBuf, 1024*40, &nerror, 3000);
	
	if (bRet)
	{
		DWORD dwRetLen = 0;
		bRet = CLIENT_ParseData(CFG_CMD_ACCESSTIMESCHEDULE, szJsonBuf, (void*)&m_stuInfo, sizeof(m_stuInfo), &dwRetLen);
		if (!bRet)
		{
			MessageBox(ConvertString(CString("parse TimeSchedule error..."), DLG_CFG_TIME_SCHEDULE), ConvertString("Prompt"));
			return FALSE;
		}
	}
	else
	{			
		CString csErr;
		csErr.Format("%s %08x...\r\n\r\n%s", ConvertString("QueryConfig TimeSchedule error:", DLG_CFG_TIME_SCHEDULE),
			CLIENT_GetLastError(), szJsonBuf);
		MessageBox(csErr, ConvertString("Prompt"));
		return FALSE;
	}
	return TRUE;
}

BOOL CDlgCfgTimeSchedule::SetConfigToDevice()
{
	int nChn = m_cmbIndex.GetCurSel();
	if (-1 == nChn)
	{
		return FALSE;
	}
	
	char szJsonBuf[1024 * 40] = {0};
	BOOL bRet = CLIENT_PacketData(CFG_CMD_ACCESSTIMESCHEDULE, &m_stuInfo, sizeof(m_stuInfo), szJsonBuf, sizeof(szJsonBuf));
	if (!bRet)
	{
		MessageBox(ConvertString(CString("packet TimeSchedule error..."), DLG_CFG_TIME_SCHEDULE), ConvertString("Prompt"));
		return FALSE;
	} 
	else
	{		
		int nerror = 0;
		int nrestart = 0;
		
		bRet = CLIENT_SetNewDevConfig((LLONG)m_lLoginID, CFG_CMD_ACCESSTIMESCHEDULE, nChn, szJsonBuf, 1024*40, &nerror, &nrestart, 0);
		if (!bRet)
		{
			CString csErr;
			csErr.Format("%s %08x...", ConvertString("SetupConfig Alarm failed:", DLG_CFG_TIME_SCHEDULE), CLIENT_GetLastError());
			MessageBox(csErr, ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			MessageBox(ConvertString(CString("SetConfig Alarm ok!"), DLG_CFG_TIME_SCHEDULE), ConvertString("Prompt"));
		}
	}
	return TRUE;
}

void CDlgCfgTimeSchedule::ShowTimeSection(int nSeg, const CFG_TIME_SECTION& stuTimeSection)
{
	SYSTEMTIME stBegin = {2000, 1, 1, 1}, stEnd = {2000, 1, 1, 1};
	CfgTimeSectionToDTP(stuTimeSection, stBegin, stEnd);
	
	switch (nSeg)
	{
	case 0:
		m_dtp1Start.SetTime(&stBegin);
		m_dtp1End.SetTime(&stEnd);
		m_chkSeg1.SetCheck(stuTimeSection.dwRecordMask ? BST_CHECKED : BST_UNCHECKED);
		break;
	case 1:
		m_dtp2Start.SetTime(&stBegin);
		m_dtp2End.SetTime(&stEnd);
		m_chkSeg2.SetCheck(stuTimeSection.dwRecordMask ? BST_CHECKED : BST_UNCHECKED);
		break;
	case 2:
		m_dtp3Start.SetTime(&stBegin);
		m_dtp3End.SetTime(&stEnd);
		m_chkSeg3.SetCheck(stuTimeSection.dwRecordMask ? BST_CHECKED : BST_UNCHECKED);
		break;
	case 3:
		m_dtp4Start.SetTime(&stBegin);
		m_dtp4End.SetTime(&stEnd);
		m_chkSeg4.SetCheck(stuTimeSection.dwRecordMask ? BST_CHECKED : BST_UNCHECKED);
		break;
	}
}

void CDlgCfgTimeSchedule::GetTimeSectionFromDlg()
{
	int nSel = m_cmbWeekDay.GetCurSel();
	SYSTEMTIME stBegin = {0}, stEnd = {0};
	for (int i = 0; i < MAX_DOOR_TIME_SECTION; i++)
	{
		CFG_TIME_SECTION& stuTimeSection = m_stuInfo.stuTime[(em_WeekDay)nSel][i];
		switch (i)
		{
		case 0:
			stuTimeSection.dwRecordMask = m_chkSeg1.GetCheck();
			m_dtp1Start.GetTime(&stBegin);
			m_dtp1End.GetTime(&stEnd);
			break;
		case 1:
			stuTimeSection.dwRecordMask = m_chkSeg2.GetCheck();
			m_dtp2Start.GetTime(&stBegin);
			m_dtp2End.GetTime(&stEnd);
			break;
		case 2:
			stuTimeSection.dwRecordMask = m_chkSeg3.GetCheck();
			m_dtp3Start.GetTime(&stBegin);
			m_dtp3End.GetTime(&stEnd);
			break;
		case 3:
			stuTimeSection.dwRecordMask = m_chkSeg4.GetCheck();
			m_dtp4Start.GetTime(&stBegin);
			m_dtp4End.GetTime(&stEnd);
			break;
		}
		DTPToCfgTimeSection(stBegin, stEnd, stuTimeSection);
	}
}

void CDlgCfgTimeSchedule::CfgTimeSectionToDTP(const CFG_TIME_SECTION& stuTimeSection, SYSTEMTIME& stBegin, SYSTEMTIME& stEnd)
{
	stBegin.wHour = stuTimeSection.nBeginHour;
	stBegin.wMinute = stuTimeSection.nBeginMin;
	stBegin.wSecond = stuTimeSection.nBeginSec;
	stEnd.wHour = stuTimeSection.nEndHour;
	stEnd.wMinute = stuTimeSection.nEndMin;
	stEnd.wSecond = stuTimeSection.nEndSec;
}

void CDlgCfgTimeSchedule::DTPToCfgTimeSection(const SYSTEMTIME& stBegin, const SYSTEMTIME& stEnd, CFG_TIME_SECTION& stuTimeSection)
{
	stuTimeSection.nBeginHour = stBegin.wHour;
	stuTimeSection.nBeginMin = stBegin.wMinute;
	stuTimeSection.nBeginSec = stBegin.wSecond;
	stuTimeSection.nEndHour = stEnd.wHour;
	stuTimeSection.nEndMin = stEnd.wMinute;
	stuTimeSection.nEndSec = stEnd.wSecond;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgTimeSchedule message handlers

BOOL CDlgCfgTimeSchedule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this, DLG_CFG_TIME_SCHEDULE);
	// TODO: Add extra initialization here
	InitDlg();
	OnTimescheduleBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCfgTimeSchedule::OnTimescheduleBtnGet() 
{
	// TODO: Add your control notification handler code here
	if (GetConfigFromDevice())
	{
		StuToDlg();
	}
}

void CDlgCfgTimeSchedule::OnTimescheduleBtnSet() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	SetConfigToDevice();
}

void CDlgCfgTimeSchedule::OnSelchangeTimescheduleCmbIndex() 
{
	// TODO: Add your control notification handler code here
	OnTimescheduleBtnGet();
}

void CDlgCfgTimeSchedule::OnSelchangeTimescheduleCmbWeekday() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbWeekDay.GetCurSel();
	if (-1 == nSel)
	{
		return;
	}
	
	for (int i = 0; i < MAX_DOOR_TIME_SECTION; i++)
	{
		ShowTimeSection(i, m_stuInfo.stuTime[nSel][i]);
	}
}

void CDlgCfgTimeSchedule::OnDatetimechangeTimescheduleDtp1Start(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CDlgCfgTimeSchedule::OnDatetimechangeTimescheduleDtp1End(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CDlgCfgTimeSchedule::OnDatetimechangeTimescheduleDtp2Start(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CDlgCfgTimeSchedule::OnDatetimechangeTimescheduleDtp2End(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CDlgCfgTimeSchedule::OnDatetimechangeTimescheduleDtp3Start(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CDlgCfgTimeSchedule::OnDatetimechangeTimescheduleDtp3End(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CDlgCfgTimeSchedule::OnDatetimechangeTimescheduleDtp4Start(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CDlgCfgTimeSchedule::OnDatetimechangeTimescheduleDtp4End(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	*pResult = 0;
}

void CDlgCfgTimeSchedule::OnTimescheduleChkSeg1Enable() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
}

void CDlgCfgTimeSchedule::OnTimescheduleChkSeg2Enable() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
}

void CDlgCfgTimeSchedule::OnTimescheduleChkSeg3Enable() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
}

void CDlgCfgTimeSchedule::OnTimescheduleChkSeg4Enable() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
}
