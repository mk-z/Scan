// LostWarning.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "LostWarning.h"
#include "Pub_Data.h"


// CLostWarning 对话框


IMPLEMENT_DYNAMIC(CLostWarning, CDialog)

CLostWarning::CLostWarning(CWnd* pParent /*=NULL*/)
	: CDialog(CLostWarning::IDD, pParent)
{
	ZeroMemory(&m_lostAlarm, sizeof(m_lostAlarm));
}

CLostWarning::~CLostWarning()
{
	DestroyWindow();
}

void CLostWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_START_LOST_WARNING, m_StartLostWarning);
	DDX_Control(pDX, IDC_COMBO_LOSTTIME_INTERVAL, m_LostTimeInterval);
}


BEGIN_MESSAGE_MAP(CLostWarning, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CLostWarning::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CLostWarning::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SETLOSTTIME, &CLostWarning::OnBnClickedButtonSetlosttime)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLostWarning 消息处理程序
BOOL CLostWarning::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(int i = 0; i< 61; i++)
	{
		CString strNo = _T("");
		strNo.Format(_T("%d"), i);
		m_LostTimeInterval.AddString(strNo);
	}

	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FLASH)->EnableWindow(FALSE);
	return TRUE;
}

void CLostWarning::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	m_lostAlarm.lost_enable = m_StartLostWarning.GetCheck();
	m_lostAlarm.detect_interval = m_LostTimeInterval.GetCurSel();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_LOST_ALARM, (char *)&m_lostAlarm, sizeof(m_lostAlarm), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return ;
	}
}

void CLostWarning::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_PubData.g_iPlayWndFlag != 6 )
	{
		AVP_AddPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],NULL, GetDlgItem(IDC_STATIC_SHOWLOSTSCREEN)->GetSafeHwnd(),NULL,NULL);
	}

	//根据能力集判断是否支持丢失告警功能
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.supp_video_lost_alarm != 1 )
	{
		//AfxMessageBox(_T("设备不支持丢失告警"));
		return;
	}
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FLASH)->EnableWindow(TRUE);
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_LOST_ALARM, (char *)&m_lostAlarm, sizeof(m_lostAlarm),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}
	ReFreshWindow();
}

void CLostWarning::OnBnClickedButtonSetlosttime()
{
	// TODO: 在此添加控件通知处理程序代码
	g_PubData.g_iShowTimeDlgFlag = 5;
	int id = m_cVideoTime.DoModal();
	if(id == IDOK)
	{
		int i = m_cVideoTime.m_iSelIndex;
		m_lostAlarm.week.days[i].seg[0].enable = m_cVideoTime.m_iVideoTime1;
		m_lostAlarm.week.days[i].seg[1].enable = m_cVideoTime.m_iVideoTime2;
		m_lostAlarm.week.days[i].seg[2].enable = m_cVideoTime.m_iVideoTime3;
		m_lostAlarm.week.days[i].seg[3].enable = m_cVideoTime.m_iVideoTime4;
		if(m_lostAlarm.week.days[i].seg[0].enable == 1)
		{
			m_lostAlarm.week.days[i].seg[0].time_start.hour = m_cVideoTime.m_STime1.GetHour();
			m_lostAlarm.week.days[i].seg[0].time_start.minute = m_cVideoTime.m_STime1.GetMinute();
			m_lostAlarm.week.days[i].seg[0].time_start.second = m_cVideoTime.m_STime1.GetSecond();

			m_lostAlarm.week.days[i].seg[0].time_end.hour = m_cVideoTime.m_ETime1.GetHour();
			m_lostAlarm.week.days[i].seg[0].time_end.minute = m_cVideoTime.m_ETime1.GetMinute();
			m_lostAlarm.week.days[i].seg[0].time_end.second = m_cVideoTime.m_ETime1.GetSecond();
		}

		if(m_lostAlarm.week.days[i].seg[1].enable == 1)
		{
			m_lostAlarm.week.days[i].seg[1].time_start.hour = m_cVideoTime.m_STime2.GetHour();
			m_lostAlarm.week.days[i].seg[1].time_start.minute = m_cVideoTime.m_STime2.GetMinute();
			m_lostAlarm.week.days[i].seg[1].time_start.second = m_cVideoTime.m_STime2.GetSecond();

			m_lostAlarm.week.days[i].seg[1].time_end.hour = m_cVideoTime.m_ETime2.GetHour();
			m_lostAlarm.week.days[i].seg[1].time_end.minute = m_cVideoTime.m_ETime2.GetMinute();
			m_lostAlarm.week.days[i].seg[1].time_end.second = m_cVideoTime.m_ETime2.GetSecond();
		}

		if(m_lostAlarm.week.days[i].seg[2].enable == 1)
		{
			m_lostAlarm.week.days[i].seg[2].time_start.hour = m_cVideoTime.m_STime3.GetHour();
			m_lostAlarm.week.days[i].seg[2].time_start.minute = m_cVideoTime.m_STime3.GetMinute();
			m_lostAlarm.week.days[i].seg[2].time_start.second = m_cVideoTime.m_STime3.GetSecond();

			m_lostAlarm.week.days[i].seg[2].time_end.hour = m_cVideoTime.m_ETime3.GetHour();
			m_lostAlarm.week.days[i].seg[2].time_end.minute = m_cVideoTime.m_ETime3.GetMinute();
			m_lostAlarm.week.days[i].seg[2].time_end.second = m_cVideoTime.m_ETime3.GetSecond();
		}

		if(m_lostAlarm.week.days[i].seg[3].enable == 1)
		{
			m_lostAlarm.week.days[i].seg[3].time_start.hour = m_cVideoTime.m_STime4.GetHour();
			m_lostAlarm.week.days[i].seg[3].time_start.minute = m_cVideoTime.m_STime4.GetMinute();
			m_lostAlarm.week.days[i].seg[3].time_start.second = m_cVideoTime.m_STime4.GetSecond();

			m_lostAlarm.week.days[i].seg[3].time_end.hour = m_cVideoTime.m_ETime4.GetHour();
			m_lostAlarm.week.days[i].seg[3].time_end.minute = m_cVideoTime.m_ETime4.GetMinute();
			m_lostAlarm.week.days[i].seg[3].time_end.second = m_cVideoTime.m_ETime4.GetSecond();
		}

		OnBnClickedButtonSave();
	}

}


void CLostWarning::ShowVideoTime(int iIndex)
{
	g_PubData.g_iVideoTime1 = m_lostAlarm.week.days[iIndex].seg[0].enable;
	g_PubData.g_iVideoTime2 = m_lostAlarm.week.days[iIndex].seg[1].enable;
	g_PubData.g_iVideoTime3 = m_lostAlarm.week.days[iIndex].seg[2].enable;
	g_PubData.g_iVideoTime4 = m_lostAlarm.week.days[iIndex].seg[3].enable;
	if(m_lostAlarm.week.days[iIndex].seg[0].enable == 1)
	{
		int iY = m_lostAlarm.week.days[iIndex].seg[0].time_start.hour;
		int iM = m_lostAlarm.week.days[iIndex].seg[0].time_start.minute;
		int iD = m_lostAlarm.week.days[iIndex].seg[0].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime1 = Stime;

		iY = m_lostAlarm.week.days[iIndex].seg[0].time_end.hour;
		iM = m_lostAlarm.week.days[iIndex].seg[0].time_end.minute;
		iD = m_lostAlarm.week.days[iIndex].seg[0].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime1 = Etime;

	}
	if(m_lostAlarm.week.days[iIndex].seg[1].enable == 1)
	{
		int iY = m_lostAlarm.week.days[iIndex].seg[1].time_start.hour;
		int iM = m_lostAlarm.week.days[iIndex].seg[1].time_start.minute;
		int iD = m_lostAlarm.week.days[iIndex].seg[1].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime2 = Stime;

		iY = m_lostAlarm.week.days[iIndex].seg[1].time_end.hour;
		iM = m_lostAlarm.week.days[iIndex].seg[1].time_end.minute;
		iD = m_lostAlarm.week.days[iIndex].seg[1].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime2 = Etime;
	}
	if(m_lostAlarm.week.days[iIndex].seg[2].enable == 1)
	{
		int iY = m_lostAlarm.week.days[iIndex].seg[2].time_start.hour;
		int iM = m_lostAlarm.week.days[iIndex].seg[2].time_start.minute;
		int iD = m_lostAlarm.week.days[iIndex].seg[2].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime3 = Stime;

		iY = m_lostAlarm.week.days[iIndex].seg[2].time_end.hour;
		iM = m_lostAlarm.week.days[iIndex].seg[2].time_end.minute;
		iD = m_lostAlarm.week.days[iIndex].seg[2].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime3 = Etime;
	}
	if(m_lostAlarm.week.days[iIndex].seg[3].enable == 1)
	{
		int iY = m_lostAlarm.week.days[iIndex].seg[3].time_start.hour;
		int iM = m_lostAlarm.week.days[iIndex].seg[3].time_start.minute;
		int iD = m_lostAlarm.week.days[iIndex].seg[3].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime4 = Stime;

		iY = m_lostAlarm.week.days[iIndex].seg[3].time_end.hour;
		iM = m_lostAlarm.week.days[iIndex].seg[3].time_end.minute;
		iD = m_lostAlarm.week.days[iIndex].seg[3].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime4 = Etime;
	}
}


int CLostWarning::ReFreshWindow()
{
	m_StartLostWarning.SetCheck(m_lostAlarm.lost_enable);
	m_LostTimeInterval.SetCurSel(m_lostAlarm.detect_interval);
	return 0;
}
void CLostWarning::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CLostWarning::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	
}
