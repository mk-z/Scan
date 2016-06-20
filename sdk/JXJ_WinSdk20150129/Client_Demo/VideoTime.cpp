// VideoTime.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "VideoTime.h"
#include "VideoPlan.h"
#include "Pub_Data.h"
#include "HideWarning.h"
#include "MoveSenseSet.h"
#include "IoWarning.h"
#include "LostWarning.h"
#include "HerdAnalyse.h"


// CVideoTime 对话框

IMPLEMENT_DYNAMIC(CVideoTime, CDialog)

CVideoTime::CVideoTime(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoTime::IDD, pParent)
{
	m_iVideoTime1 = 0;
	m_iVideoTime2 = 0;
	m_iVideoTime3 = 0;
	m_iVideoTime4 = 0;

	m_iSelIndex = -1;
}

CVideoTime::~CVideoTime()
{
}

void CVideoTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WEEK, m_comWeek);
	//DDX_Control(pDX, IDC_CHECK_FULLDAY, m_FullDay);
	DDX_Control(pDX, IDC_CHECK_VIDEOTIME1, m_VideTime1);
	DDX_Control(pDX, IDC_CHECK_VIDEOTIME2, m_VideoTime2);
	DDX_Control(pDX, IDC_CHECK_VIDEOTIME3, m_VideoTime3);
	DDX_Control(pDX, IDC_CHECK_VIDEOTIME4, m_VideoTime4);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StartTime1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_EndTime1);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_StartTime2);
	DDX_Control(pDX, IDC_DATETIMEPICKER5, m_StartTime3);
	DDX_Control(pDX, IDC_DATETIMEPICKER7, m_StartTime4);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_EndTime2);
	DDX_Control(pDX, IDC_DATETIMEPICKER6, m_EndTime3);
	DDX_Control(pDX, IDC_DATETIMEPICKER8, m_EndTime4);
}


BEGIN_MESSAGE_MAP(CVideoTime, CDialog)

//	ON_BN_CLICKED(IDC_CHECK_FULLDAY, &CVideoTime::OnBnClickedCheckFullday)
	ON_BN_CLICKED(IDC_CHECK_VIDEOTIME1, &CVideoTime::OnBnClickedCheckVideotime1)
	ON_BN_CLICKED(IDC_CHECK_VIDEOTIME2, &CVideoTime::OnBnClickedCheckVideotime2)
	ON_BN_CLICKED(IDC_CHECK_VIDEOTIME3, &CVideoTime::OnBnClickedCheckVideotime3)
	ON_BN_CLICKED(IDC_CHECK_VIDEOTIME4, &CVideoTime::OnBnClickedCheckVideotime4)
	ON_BN_CLICKED(IDOK, &CVideoTime::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEK, &CVideoTime::OnCbnSelchangeComboWeek)
END_MESSAGE_MAP()


// CVideoTime 消息处理程序
BOOL CVideoTime::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_comWeek.AddString(_T("星期日"));
		m_comWeek.AddString(_T("星期一"));
		m_comWeek.AddString(_T("星期二"));
		m_comWeek.AddString(_T("星期三"));
		m_comWeek.AddString(_T("星期四"));
		m_comWeek.AddString(_T("星期五"));
		m_comWeek.AddString(_T("星期六"));
		m_comWeek.AddString(_T("每天"));
	}
	else
	{
		m_comWeek.AddString(_T("Sunday"));
		m_comWeek.AddString(_T("Monday"));
		m_comWeek.AddString(_T("Tuesday"));
		m_comWeek.AddString(_T("Wednesday"));
		m_comWeek.AddString(_T("Thursday"));
		m_comWeek.AddString(_T("Friday"));
		m_comWeek.AddString(_T("Saturday"));
		m_comWeek.AddString(_T("Everyday"));
	}
	
	m_comWeek.SetCurSel(0);
	

	m_StartTime1.EnableWindow(FALSE);
	m_EndTime1.EnableWindow(FALSE);

	m_StartTime2.EnableWindow(FALSE);
	m_EndTime2.EnableWindow(FALSE);

	m_StartTime3.EnableWindow(FALSE);
	m_EndTime3.EnableWindow(FALSE);

	m_StartTime4.EnableWindow(FALSE);
	m_EndTime4.EnableWindow(FALSE);

	OnCbnSelchangeComboWeek();
	return TRUE;
}


void CVideoTime::OnBnClickedCheckFullday()
{
	// TODO: 在此添加控件通知处理程序代码
	/*if(m_FullDay.GetCheck() == 1)
	{
		m_VideTime1.EnableWindow(FALSE);
		m_VideoTime2.EnableWindow(FALSE);
		m_VideoTime3.EnableWindow(FALSE);
		m_VideoTime4.EnableWindow(FALSE);
	}
	else
	{
		m_VideTime1.EnableWindow(TRUE);
		m_VideoTime2.EnableWindow(TRUE);
		m_VideoTime3.EnableWindow(TRUE);
		m_VideoTime4.EnableWindow(TRUE);
	}*/
}

void CVideoTime::OnBnClickedCheckVideotime1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_VideTime1.GetCheck() == 1)
	{
		m_StartTime1.EnableWindow(TRUE);
		m_EndTime1.EnableWindow(TRUE);
		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime startTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),0, 0, 0);
		COleDateTime endTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),23, 59, 59);	
		m_StartTime1.SetTime(startTime);
		m_EndTime1.SetTime(endTime);
	}
	else
	{
		m_StartTime1.EnableWindow(FALSE);
		m_EndTime1.EnableWindow(FALSE);
	}
	
}

void CVideoTime::OnBnClickedCheckVideotime2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_VideoTime2.GetCheck() == 1)
	{
		m_StartTime2.EnableWindow(TRUE);
		m_EndTime2.EnableWindow(TRUE);
		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime startTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),0, 0, 0);
		COleDateTime endTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),23, 59, 59);	
		m_StartTime2.SetTime(startTime);
		m_EndTime2.SetTime(endTime);
	}
	else
	{
		m_StartTime2.EnableWindow(FALSE);
		m_EndTime2.EnableWindow(FALSE);
	}
}

void CVideoTime::OnBnClickedCheckVideotime3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_VideoTime3.GetCheck() == 1)
	{
		m_StartTime3.EnableWindow(TRUE);
		m_EndTime3.EnableWindow(TRUE);
		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime startTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),0, 0, 0);
		COleDateTime endTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),23, 59, 59);	
		m_StartTime3.SetTime(startTime);
		m_EndTime3.SetTime(endTime);
	}
	else
	{
		m_StartTime3.EnableWindow(FALSE);
		m_EndTime3.EnableWindow(FALSE);
	}
}

void CVideoTime::OnBnClickedCheckVideotime4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_VideoTime4.GetCheck() == 1)
	{
		m_StartTime4.EnableWindow(TRUE);
		m_EndTime4.EnableWindow(TRUE);
		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime startTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),0, 0, 0);
		COleDateTime endTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),23, 59, 59);	
		m_StartTime4.SetTime(startTime);
		m_EndTime4.SetTime(endTime);
	}
	else
	{
		m_StartTime4.EnableWindow(FALSE);
		m_EndTime4.EnableWindow(FALSE);
	}
}

void CVideoTime::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iSelIndex = m_comWeek.GetCurSel();

	if(m_VideTime1.GetCheck() == 1)
	{
		m_StartTime1.GetTime(m_STime1);
		m_EndTime1.GetTime(m_ETime1);
	}
	if(m_VideoTime2.GetCheck() == 1)
	{
		m_StartTime2.GetTime(m_STime2);
		m_EndTime2.GetTime(m_ETime2);
	}
	if(m_VideoTime3.GetCheck() == 1)
	{
		m_StartTime3.GetTime(m_STime3);
		m_EndTime3.GetTime(m_ETime3);
	}
	if(m_VideoTime4.GetCheck() == 1)
	{
		m_StartTime4.GetTime(m_STime4);
		m_EndTime4.GetTime(m_ETime4);
	}
	m_iVideoTime1 = m_VideTime1.GetCheck();
	m_iVideoTime2 = m_VideoTime2.GetCheck();
	m_iVideoTime3 = m_VideoTime3.GetCheck();
	m_iVideoTime4 = m_VideoTime4.GetCheck();
	OnOK();
}

void CVideoTime::OnCbnSelchangeComboWeek()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_comWeek.GetCurSel();
	if(g_PubData.g_iShowTimeDlgFlag == 1)
	{
		CVideoPlan *pDlg=(CVideoPlan *)AfxGetMainWnd();
		pDlg->ShowVideoTime(iIndex);
	}
	else if(g_PubData.g_iShowTimeDlgFlag == 2)
	{
		CHideWarning *pDlg=(CHideWarning *)AfxGetMainWnd();
		pDlg->ShowVideoTime(iIndex);
	}
	else if(g_PubData.g_iShowTimeDlgFlag == 3)
	{
		CMoveSenseSet *pDlg=(CMoveSenseSet *)AfxGetMainWnd();
		pDlg->ShowVideoTime(iIndex);
	}
	else if(g_PubData.g_iShowTimeDlgFlag == 4)
	{
		CIoWarning *pDlg=(CIoWarning *)AfxGetMainWnd();
		pDlg->ShowVideoTime(iIndex);
	}
	else if(g_PubData.g_iShowTimeDlgFlag == 5)
	{
		CLostWarning *pDlg=(CLostWarning *)AfxGetMainWnd();
		pDlg->ShowVideoTime(iIndex);
	}
	else if(g_PubData.g_iShowTimeDlgFlag == 6)
	{
		CHerdAnalyse *pDlg=(CHerdAnalyse *)AfxGetMainWnd();
		pDlg->ShowVideoTime(iIndex);
	}
	EnableTimeCheck();
}


void CVideoTime::EnableTimeCheck()
{
	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();	
	COleDateTime startTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),0, 0, 0);
	COleDateTime endTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),23, 59, 59);	
	if(g_PubData.g_iVideoTime1 == 1)
	{
		m_VideTime1.SetCheck(1);
		m_StartTime1.SetTime(g_PubData.g_STime1);
		m_EndTime1.SetTime(g_PubData.g_ETime1);
		m_StartTime1.EnableWindow(TRUE);
		m_EndTime1.EnableWindow(TRUE);
	}
	else
	{
		m_VideTime1.SetCheck(0);
		m_StartTime1.SetTime(startTime);
		m_EndTime1.SetTime(endTime);
		m_StartTime1.EnableWindow(FALSE);
		m_EndTime1.EnableWindow(FALSE);
	}

	if(g_PubData.g_iVideoTime2 == 1)
	{
		m_VideoTime2.SetCheck(1);
		m_StartTime2.SetTime(g_PubData.g_STime2);
		m_EndTime2.SetTime(g_PubData.g_ETime2);
		m_StartTime2.EnableWindow(TRUE);
		m_EndTime2.EnableWindow(TRUE);
	}
	else
	{
		m_VideoTime2.SetCheck(0);
		m_StartTime2.SetTime(startTime);
		m_EndTime2.SetTime(endTime);
		m_StartTime2.EnableWindow(FALSE);
		m_EndTime2.EnableWindow(FALSE);
	}

	if(g_PubData.g_iVideoTime3 == 1)
	{
		m_VideoTime3.SetCheck(1);
		m_StartTime3.SetTime(g_PubData.g_STime3);
		m_EndTime3.SetTime(g_PubData.g_ETime3);
		m_StartTime3.EnableWindow(TRUE);
		m_EndTime3.EnableWindow(TRUE);
	}
	else
	{
		m_VideoTime3.SetCheck(0);
		m_StartTime3.SetTime(startTime);
		m_EndTime3.SetTime(endTime);
		m_StartTime3.EnableWindow(FALSE);
		m_EndTime3.EnableWindow(FALSE);
	}

	if(g_PubData.g_iVideoTime4 == 1)
	{
		m_VideoTime4.SetCheck(1);
		m_StartTime4.SetTime(g_PubData.g_STime4);
		m_EndTime4.SetTime(g_PubData.g_ETime4);
		m_StartTime4.EnableWindow(TRUE);
		m_EndTime4.EnableWindow(TRUE);
	}
	else
	{
		m_VideoTime4.SetCheck(0);
		m_StartTime4.SetTime(startTime);
		m_EndTime4.SetTime(endTime);
		m_StartTime4.EnableWindow(FALSE);
		m_EndTime4.EnableWindow(FALSE);
	}
}