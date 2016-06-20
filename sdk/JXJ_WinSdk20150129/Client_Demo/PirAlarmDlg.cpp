// PirAlarmDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "PirAlarmDlg.h"
#include "Pub_Data.h"

// CPirAlarmDlg 对话框


IMPLEMENT_DYNAMIC(CPirAlarmDlg, CDialog)

CPirAlarmDlg::CPirAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPirAlarmDlg::IDD, pParent)
{

}

CPirAlarmDlg::~CPirAlarmDlg()
{
}

void CPirAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_enableAlarm);
	DDX_Control(pDX, IDC_COMBO_DETECTINTERVAL, m_detectInterval);
	DDX_Control(pDX, IDC_COMBO_WEEK, m_chooseWeek);
	DDX_Control(pDX, IDC_CHECK2, m_allDay);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_startTime1);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_startTime2);
	DDX_Control(pDX, IDC_DATETIMEPICKER5, m_startTime3);
	DDX_Control(pDX, IDC_DATETIMEPICKER7, m_startTime4);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_endTime1);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_endTime2);
	DDX_Control(pDX, IDC_DATETIMEPICKER6, m_endTime3);
	DDX_Control(pDX, IDC_DATETIMEPICKER9, m_endTime4);
	DDX_Control(pDX, IDC_CHECK3, m_enableTime1);
	DDX_Control(pDX, IDC_CHECK4, m_enableTime2);
	DDX_Control(pDX, IDC_CHECK5, m_enableTime3);
	DDX_Control(pDX, IDC_CHECK6, m_enableTime4);
}


BEGIN_MESSAGE_MAP(CPirAlarmDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CPirAlarmDlg::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPirAlarmDlg::OnBnClickedButtonSave)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEK, &CPirAlarmDlg::OnCbnSelchangeComboWeek)
	ON_BN_CLICKED(IDC_CHECK3, &CPirAlarmDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CPirAlarmDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CPirAlarmDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CPirAlarmDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK2, &CPirAlarmDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()





// CPirAlarmDlg 消息处理程序
BOOL CPirAlarmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(int i =0 ;i < 61; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		m_detectInterval.AddString(str);
	}

	m_chooseWeek.AddString(_T("星期日"));
	m_chooseWeek.AddString(_T("星期一"));
	m_chooseWeek.AddString(_T("星期二"));
	m_chooseWeek.AddString(_T("星期三"));
	m_chooseWeek.AddString(_T("星期四"));
	m_chooseWeek.AddString(_T("星期五"));
	m_chooseWeek.AddString(_T("星期六"));
	m_chooseWeek.AddString(_T("每天"));
	m_chooseWeek.SetCurSel(0);


	m_enableTime1.EnableWindow(TRUE);
	m_enableTime2.EnableWindow(TRUE);
	m_enableTime3.EnableWindow(TRUE);
	m_enableTime4.EnableWindow(TRUE);
	return TRUE;
}

void CPirAlarmDlg::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PIR_ALARM, (char *)&m_pirAlarmParam, sizeof(m_pirAlarmParam),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();
}


int CPirAlarmDlg::ReFreshWindow()
{

	m_enableAlarm.SetCheck(m_pirAlarmParam.alarm_enable);
	m_detectInterval.SetCurSel(m_pirAlarmParam.detect_interval);
	OnCbnSelchangeComboWeek();

	return 0;

}


void CPirAlarmDlg::SaveTime()
{
	COleDateTime timeStart1;
	COleDateTime timeEnd1;
	m_startTime1.GetTime(timeStart1);
	m_endTime1.GetTime(timeEnd1);

	COleDateTime timeStart2;
	COleDateTime timeEnd2;
	m_startTime2.GetTime(timeStart2);
	m_endTime2.GetTime(timeEnd2);

	COleDateTime timeStart3;
	COleDateTime timeEnd3;
	m_startTime3.GetTime(timeStart3);
	m_endTime3.GetTime(timeEnd3);

	COleDateTime timeStart4;
	COleDateTime timeEnd4;
	m_startTime4.GetTime(timeStart4);
	m_endTime4.GetTime(timeEnd4);


	int nIndex = m_chooseWeek.GetCurSel();
	m_pirAlarmParam.week.days[nIndex].seg[0].time_start.hour = timeStart1.GetHour();
	m_pirAlarmParam.week.days[nIndex].seg[0].time_start.minute = timeStart1.GetMinute();
	m_pirAlarmParam.week.days[nIndex].seg[0].time_start.second = timeStart1.GetSecond();

	m_pirAlarmParam.week.days[nIndex].seg[0].time_end.hour = timeEnd1.GetHour();
	m_pirAlarmParam.week.days[nIndex].seg[0].time_end.minute = timeEnd1.GetMinute();
	m_pirAlarmParam.week.days[nIndex].seg[0].time_end.second = timeEnd1.GetSecond();


	m_pirAlarmParam.week.days[nIndex].seg[1].time_start.hour = timeStart2.GetHour();
	m_pirAlarmParam.week.days[nIndex].seg[1].time_start.minute = timeStart2.GetMinute();
	m_pirAlarmParam.week.days[nIndex].seg[1].time_start.second = timeStart2.GetSecond();

	m_pirAlarmParam.week.days[nIndex].seg[1].time_end.hour = timeEnd2.GetHour();
	m_pirAlarmParam.week.days[nIndex].seg[1].time_end.minute = timeEnd2.GetMinute();
	m_pirAlarmParam.week.days[nIndex].seg[1].time_end.second = timeEnd2.GetSecond();


	m_pirAlarmParam.week.days[nIndex].seg[2].time_start.hour = timeStart3.GetHour();
	m_pirAlarmParam.week.days[nIndex].seg[2].time_start.minute = timeStart3.GetMinute();
	m_pirAlarmParam.week.days[nIndex].seg[2].time_start.second = timeStart3.GetSecond();
	
	m_pirAlarmParam.week.days[nIndex].seg[2].time_end.hour = timeEnd3.GetHour();
	m_pirAlarmParam.week.days[nIndex].seg[2].time_end.minute = timeEnd3.GetMinute();
	m_pirAlarmParam.week.days[nIndex].seg[2].time_end.second = timeEnd3.GetSecond();


	m_pirAlarmParam.week.days[nIndex].seg[3].time_start.hour = timeStart4.GetHour();
	m_pirAlarmParam.week.days[nIndex].seg[3].time_start.minute = timeStart4.GetMinute();
	m_pirAlarmParam.week.days[nIndex].seg[3].time_start.second = timeStart4.GetSecond();

	m_pirAlarmParam.week.days[nIndex].seg[3].time_end.hour = timeEnd4.GetHour();
	m_pirAlarmParam.week.days[nIndex].seg[3].time_end.minute = timeEnd4.GetMinute();
	m_pirAlarmParam.week.days[nIndex].seg[3].time_end.second = timeEnd4.GetSecond();
	m_pirAlarmParam.week.days[nIndex].day_id = nIndex;



}

void CPirAlarmDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pirAlarmParam.alarm_enable = m_enableAlarm.GetCheck();
	m_pirAlarmParam.detect_interval = m_detectInterval.GetCurSel();
	int nIndex = m_chooseWeek.GetCurSel();
	m_pirAlarmParam.week.days[nIndex].all_day_enable = m_allDay.GetCheck();
	m_pirAlarmParam.week.days[nIndex].seg[0].enable = m_enableTime1.GetCheck();
	m_pirAlarmParam.week.days[nIndex].seg[1].enable = m_enableTime2.GetCheck();
	m_pirAlarmParam.week.days[nIndex].seg[2].enable = m_enableTime3.GetCheck();
	m_pirAlarmParam.week.days[nIndex].seg[3].enable = m_enableTime4.GetCheck();
	SaveTime();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PIR_ALARM, (char *)&m_pirAlarmParam, sizeof(m_pirAlarmParam), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}


}


void CPirAlarmDlg::OnCbnSelchangeComboWeek()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_chooseWeek.GetCurSel();
	m_allDay.SetCheck(m_pirAlarmParam.week.days[nIndex].all_day_enable);
	m_enableTime1.SetCheck(m_pirAlarmParam.week.days[nIndex].seg[0].enable);
	m_enableTime2.SetCheck(m_pirAlarmParam.week.days[nIndex].seg[1].enable);
	m_enableTime3.SetCheck(m_pirAlarmParam.week.days[nIndex].seg[2].enable);
	m_enableTime4.SetCheck(m_pirAlarmParam.week.days[nIndex].seg[3].enable);

	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();		
	COleDateTime startTime1(cTime.GetYear(),
							cTime.GetMonth(),
							cTime.GetDay(),
							m_pirAlarmParam.week.days[nIndex].seg[0].time_start.hour,
							m_pirAlarmParam.week.days[nIndex].seg[0].time_start.minute,
							m_pirAlarmParam.week.days[nIndex].seg[0].time_start.second);

	COleDateTime startTime2(cTime.GetYear(),
							cTime.GetMonth(),
							cTime.GetDay(),
							m_pirAlarmParam.week.days[nIndex].seg[1].time_start.hour,
							m_pirAlarmParam.week.days[nIndex].seg[1].time_start.minute,
							m_pirAlarmParam.week.days[nIndex].seg[1].time_start.second);

	COleDateTime startTime3(cTime.GetYear(),
							cTime.GetMonth(),
							cTime.GetDay(),
							m_pirAlarmParam.week.days[nIndex].seg[2].time_start.hour,
							m_pirAlarmParam.week.days[nIndex].seg[2].time_start.minute,
							m_pirAlarmParam.week.days[nIndex].seg[2].time_start.second);

	COleDateTime startTime4(cTime.GetYear(),
							cTime.GetMonth(),
							cTime.GetDay(),
							m_pirAlarmParam.week.days[nIndex].seg[3].time_start.hour,
							m_pirAlarmParam.week.days[nIndex].seg[3].time_start.minute,
							m_pirAlarmParam.week.days[nIndex].seg[3].time_start.second);


	COleDateTime endTime1(cTime.GetYear(),
						cTime.GetMonth(),
						cTime.GetDay(),
						m_pirAlarmParam.week.days[nIndex].seg[0].time_end.hour,
						m_pirAlarmParam.week.days[nIndex].seg[0].time_end.minute,
						m_pirAlarmParam.week.days[nIndex].seg[0].time_end.second);

	COleDateTime endTime2(cTime.GetYear(),
						cTime.GetMonth(),
						cTime.GetDay(),
						m_pirAlarmParam.week.days[nIndex].seg[1].time_end.hour,
						m_pirAlarmParam.week.days[nIndex].seg[1].time_end.minute,
						m_pirAlarmParam.week.days[nIndex].seg[1].time_end.second);

	COleDateTime endTime3(cTime.GetYear(),
						cTime.GetMonth(),
						cTime.GetDay(),
						m_pirAlarmParam.week.days[nIndex].seg[2].time_end.hour,
						m_pirAlarmParam.week.days[nIndex].seg[2].time_end.minute,
						m_pirAlarmParam.week.days[nIndex].seg[2].time_end.second);

	COleDateTime endTime4(cTime.GetYear(),
						cTime.GetMonth(),
						cTime.GetDay(),
						m_pirAlarmParam.week.days[nIndex].seg[3].time_end.hour,
						m_pirAlarmParam.week.days[nIndex].seg[3].time_end.minute,
						m_pirAlarmParam.week.days[nIndex].seg[3].time_end.second);


	m_startTime1.SetTime(startTime1);
	m_startTime2.SetTime(startTime2);
	m_startTime3.SetTime(startTime3);
	m_startTime4.SetTime(startTime4);

	m_endTime1.SetTime(endTime1);
	m_endTime2.SetTime(endTime2);
	m_endTime3.SetTime(endTime3);
	m_endTime4.SetTime(endTime4);


	OnBnClickedCheck2();
	OnBnClickedCheck3();
	OnBnClickedCheck4();
	OnBnClickedCheck5();
	OnBnClickedCheck6();

}


void CPirAlarmDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_allDay.GetCheck() == 1)
	{
		
		m_enableTime1.EnableWindow(FALSE);
		m_enableTime2.EnableWindow(FALSE);
		m_enableTime3.EnableWindow(FALSE);
		m_enableTime4.EnableWindow(FALSE);
	}
	else
	{
		m_enableTime1.EnableWindow(TRUE);
		m_enableTime2.EnableWindow(TRUE);
		m_enableTime3.EnableWindow(TRUE);
		m_enableTime4.EnableWindow(TRUE);
	}

}

void CPirAlarmDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_enableTime1.GetCheck() == 1)
	{
		m_startTime1.EnableWindow(TRUE);
		m_endTime1.EnableWindow(TRUE);
	}
	else
	{
		m_startTime1.EnableWindow(FALSE);
		m_endTime1.EnableWindow(FALSE);
	}
}

void CPirAlarmDlg::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_enableTime2.GetCheck() == 1)
	{
		m_startTime2.EnableWindow(TRUE);
		m_endTime2.EnableWindow(TRUE);
	}
	else
	{
		m_startTime2.EnableWindow(FALSE);
		m_endTime2.EnableWindow(FALSE);
	}
}

void CPirAlarmDlg::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_enableTime3.GetCheck() == 1)
	{
		m_startTime3.EnableWindow(TRUE);
		m_endTime3.EnableWindow(TRUE);
	}
	else
	{
		m_startTime3.EnableWindow(FALSE);
		m_endTime3.EnableWindow(FALSE);
	}
}

void CPirAlarmDlg::OnBnClickedCheck6()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_enableTime4.GetCheck() == 1)
	{
		m_startTime4.EnableWindow(TRUE);
		m_endTime4.EnableWindow(TRUE);
	}
	else
	{
		m_startTime4.EnableWindow(FALSE);
		m_endTime4.EnableWindow(FALSE);
	}
}


