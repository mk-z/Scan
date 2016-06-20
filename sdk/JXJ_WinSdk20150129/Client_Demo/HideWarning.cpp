// HideWarning.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HideWarning.h"
#include "Pub_Data.h"
#include "BorderDlg.h"



// CHideWarning 对话框

IMPLEMENT_DYNAMIC(CHideWarning, CDialog)

CHideWarning::CHideWarning(CWnd* pParent /*=NULL*/)
	: CDialog(CHideWarning::IDD, pParent)
{
	ZeroMemory(&m_hideAlarm, sizeof(m_hideAlarm));
}

CHideWarning::~CHideWarning()
{
	DestroyWindow();
}	

void CHideWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_Channel);
	DDX_Control(pDX, IDC_CHECK_STARTHIDEALARM, m_StartHideAlarm);
	DDX_Control(pDX, IDC_COMBO_RESPONSE, m_Response);
	DDX_Control(pDX, IDC_COMBO_SENSESECOND, m_SenseSecond);
	DDX_Control(pDX, IDC_CHECK_STARTPAINT, m_bStartPaint);
}


BEGIN_MESSAGE_MAP(CHideWarning, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CHideWarning::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CHideWarning::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_HIDETIME, &CHideWarning::OnBnClickedButtonHidetime)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CHideWarning::OnBnClickedButtonClear)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_STARTPAINT, &CHideWarning::OnBnClickedCheckStartpaint)
END_MESSAGE_MAP()


// CHideWarning 消息处理程序

BOOL CHideWarning::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_Channel.AddString(_T("0"));
	m_Channel.SetCurSel(0);

	for(int i = 1; i< 6; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		m_Response.AddString(str);
	}

	for(int i = 0; i< 61; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		m_SenseSecond.AddString(str);
	}

	m_cHideAlarmScreen.Create(IDD_DIALOG_HIDEALARM_SCREEN, this);
	m_cHideAlarmScreen.MoveWindow(30,100,520,300,TRUE);
	m_cHideAlarmScreen.ShowWindow(SW_SHOW);
	
	return TRUE;
}

void CHideWarning::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CRect cRect;
	m_cHideAlarmScreen.GetWindowRect(cRect);
	int iDeviceWidth;
	int iDeviceHeight;
	iDeviceWidth = m_hideAlarm.max_width;
	iDeviceHeight = m_hideAlarm.max_height;

	m_hideAlarm.hide_enable = m_StartHideAlarm.GetCheck();
	m_hideAlarm.detect_interval = m_SenseSecond.GetCurSel();
	m_hideAlarm.sensitive_level = m_Response.GetCurSel();

	m_hideAlarm.detect_area.count = g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng];
	for(int i = 0; i < g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]; i++)
	{
		m_hideAlarm.detect_area.rect[i].left = (int)((m_cHideAlarmScreen.m_StartPoint[i].x * iDeviceWidth)/cRect.Width());
		m_hideAlarm.detect_area.rect[i].top = (int)((m_cHideAlarmScreen.m_StartPoint[i].y * iDeviceHeight) /cRect.Height());
		m_hideAlarm.detect_area.rect[i].right = (int)((m_cHideAlarmScreen.m_EndPoint[i].x * iDeviceWidth) / cRect.Width());
		m_hideAlarm.detect_area.rect[i].bottom = (int)((m_cHideAlarmScreen.m_EndPoint[i].y * iDeviceHeight) / cRect.Height());
	}

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HIDE_ALARM, (char *)&m_hideAlarm, sizeof(m_hideAlarm), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}
	

}

void CHideWarning::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_PubData.g_iPlayWndFlag != 4 )
	{
		AVP_AddPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], NULL,m_cHideAlarmScreen.GetSafeHwnd(),NULL, NULL);
	}

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HIDE_ALARM, (char *)&m_hideAlarm, sizeof(m_hideAlarm),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return;
	}
	ReFreshWindow();
	OnBnClickedCheckStartpaint();
}



int CHideWarning::ReFreshWindow()
{
	m_StartHideAlarm.SetCheck(m_hideAlarm.hide_enable);
	m_SenseSecond.SetCurSel(m_hideAlarm.detect_interval);
	m_Response.SetCurSel(m_hideAlarm.sensitive_level);


	g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng] = m_hideAlarm.detect_area.count;
	for(int i = 0; i < g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]; i++)
	{
		m_cHideAlarmScreen.m_StartPoint[i].x = (m_hideAlarm.detect_area.rect[i].left *520) / m_hideAlarm.max_width;
		m_cHideAlarmScreen.m_StartPoint[i].y = (m_hideAlarm.detect_area.rect[i].top *300)/ m_hideAlarm.max_height;
		m_cHideAlarmScreen.m_EndPoint[i].x = (m_hideAlarm.detect_area.rect[i].right *520) / m_hideAlarm.max_width;
		m_cHideAlarmScreen.m_EndPoint[i].y = (m_hideAlarm.detect_area.rect[i].bottom *300)/ m_hideAlarm.max_height;
	}

	return 0;
}
void CHideWarning::OnBnClickedButtonHidetime()
{
	// TODO: 在此添加控件通知处理程序代码
	g_PubData.g_iShowTimeDlgFlag = 2;
	int id = m_cVideoTime.DoModal();
	if(id == IDOK)
	{
		int i = m_cVideoTime.m_iSelIndex;
		m_hideAlarm.week.days[i].seg[0].enable = m_cVideoTime.m_iVideoTime1;
		m_hideAlarm.week.days[i].seg[1].enable = m_cVideoTime.m_iVideoTime2;
		m_hideAlarm.week.days[i].seg[2].enable = m_cVideoTime.m_iVideoTime3;
		m_hideAlarm.week.days[i].seg[3].enable = m_cVideoTime.m_iVideoTime4;
		if(m_hideAlarm.week.days[i].seg[0].enable == 1)
		{
			m_hideAlarm.week.days[i].seg[0].time_start.hour = m_cVideoTime.m_STime1.GetHour();
			m_hideAlarm.week.days[i].seg[0].time_start.minute = m_cVideoTime.m_STime1.GetMinute();
			m_hideAlarm.week.days[i].seg[0].time_start.second = m_cVideoTime.m_STime1.GetSecond();

			m_hideAlarm.week.days[i].seg[0].time_end.hour = m_cVideoTime.m_ETime1.GetHour();
			m_hideAlarm.week.days[i].seg[0].time_end.minute = m_cVideoTime.m_ETime1.GetMinute();
			m_hideAlarm.week.days[i].seg[0].time_end.second = m_cVideoTime.m_ETime1.GetSecond();
		}

		if(m_hideAlarm.week.days[i].seg[1].enable == 1)
		{
			m_hideAlarm.week.days[i].seg[1].time_start.hour = m_cVideoTime.m_STime2.GetHour();
			m_hideAlarm.week.days[i].seg[1].time_start.minute = m_cVideoTime.m_STime2.GetMinute();
			m_hideAlarm.week.days[i].seg[1].time_start.second = m_cVideoTime.m_STime2.GetSecond();

			m_hideAlarm.week.days[i].seg[1].time_end.hour = m_cVideoTime.m_ETime2.GetHour();
			m_hideAlarm.week.days[i].seg[1].time_end.minute = m_cVideoTime.m_ETime2.GetMinute();
			m_hideAlarm.week.days[i].seg[1].time_end.second = m_cVideoTime.m_ETime2.GetSecond();
		}

		if(m_hideAlarm.week.days[i].seg[2].enable == 1)
		{
			m_hideAlarm.week.days[i].seg[2].time_start.hour = m_cVideoTime.m_STime3.GetHour();
			m_hideAlarm.week.days[i].seg[2].time_start.minute = m_cVideoTime.m_STime3.GetMinute();
			m_hideAlarm.week.days[i].seg[2].time_start.second = m_cVideoTime.m_STime3.GetSecond();

			m_hideAlarm.week.days[i].seg[2].time_end.hour = m_cVideoTime.m_ETime3.GetHour();
			m_hideAlarm.week.days[i].seg[2].time_end.minute = m_cVideoTime.m_ETime3.GetMinute();
			m_hideAlarm.week.days[i].seg[2].time_end.second = m_cVideoTime.m_ETime3.GetSecond();
		}

		if(m_hideAlarm.week.days[i].seg[3].enable == 1)
		{
			m_hideAlarm.week.days[i].seg[3].time_start.hour = m_cVideoTime.m_STime4.GetHour();
			m_hideAlarm.week.days[i].seg[3].time_start.minute = m_cVideoTime.m_STime4.GetMinute();
			m_hideAlarm.week.days[i].seg[3].time_start.second = m_cVideoTime.m_STime4.GetSecond();

			m_hideAlarm.week.days[i].seg[3].time_end.hour = m_cVideoTime.m_ETime4.GetHour();
			m_hideAlarm.week.days[i].seg[3].time_end.minute = m_cVideoTime.m_ETime4.GetMinute();
			m_hideAlarm.week.days[i].seg[3].time_end.second = m_cVideoTime.m_ETime4.GetSecond();
		}
		OnBnClickedButtonSave();
	}
}


void CHideWarning::ShowVideoTime(int iIndex)
{

	g_PubData.g_iVideoTime1 = m_hideAlarm.week.days[iIndex].seg[0].enable;
	g_PubData.g_iVideoTime2 = m_hideAlarm.week.days[iIndex].seg[1].enable;
	g_PubData.g_iVideoTime3 = m_hideAlarm.week.days[iIndex].seg[2].enable;
	g_PubData.g_iVideoTime4 = m_hideAlarm.week.days[iIndex].seg[3].enable;
	if(m_hideAlarm.week.days[iIndex].seg[0].enable == 1)
	{
		int iY = m_hideAlarm.week.days[iIndex].seg[0].time_start.hour;
		int iM = m_hideAlarm.week.days[iIndex].seg[0].time_start.minute;
		int iD = m_hideAlarm.week.days[iIndex].seg[0].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime1 = Stime;

		iY = m_hideAlarm.week.days[iIndex].seg[0].time_end.hour;
		iM = m_hideAlarm.week.days[iIndex].seg[0].time_end.minute;
		iD = m_hideAlarm.week.days[iIndex].seg[0].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime1 = Etime;

	}
	if(m_hideAlarm.week.days[iIndex].seg[1].enable == 1)
	{
		int iY = m_hideAlarm.week.days[iIndex].seg[1].time_start.hour;
		int iM = m_hideAlarm.week.days[iIndex].seg[1].time_start.minute;
		int iD = m_hideAlarm.week.days[iIndex].seg[1].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime2 = Stime;

		iY = m_hideAlarm.week.days[iIndex].seg[1].time_end.hour;
		iM = m_hideAlarm.week.days[iIndex].seg[1].time_end.minute;
		iD = m_hideAlarm.week.days[iIndex].seg[1].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime2 = Etime;
	}
	if(m_hideAlarm.week.days[iIndex].seg[2].enable == 1)
	{
		int iY = m_hideAlarm.week.days[iIndex].seg[2].time_start.hour;
		int iM = m_hideAlarm.week.days[iIndex].seg[2].time_start.minute;
		int iD = m_hideAlarm.week.days[iIndex].seg[2].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime3 = Stime;

		iY = m_hideAlarm.week.days[iIndex].seg[2].time_end.hour;
		iM = m_hideAlarm.week.days[iIndex].seg[2].time_end.minute;
		iD = m_hideAlarm.week.days[iIndex].seg[2].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime3 = Etime;
	}
	if(m_hideAlarm.week.days[iIndex].seg[3].enable == 1)
	{
		int iY = m_hideAlarm.week.days[iIndex].seg[3].time_start.hour;
		int iM = m_hideAlarm.week.days[iIndex].seg[3].time_start.minute;
		int iD = m_hideAlarm.week.days[iIndex].seg[3].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime4 = Stime;

		iY = m_hideAlarm.week.days[iIndex].seg[3].time_end.hour;
		iM = m_hideAlarm.week.days[iIndex].seg[3].time_end.minute;
		iD = m_hideAlarm.week.days[iIndex].seg[3].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime4 = Etime;
	}
}


void CHideWarning::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_hideAlarm.detect_area.count = g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng];
	for(int i = 0; i < g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]; i++)
	{
		m_cHideAlarmScreen.m_StartPoint[i].x = 0;
		m_cHideAlarmScreen.m_StartPoint[i].y = 0;
		m_cHideAlarmScreen.m_EndPoint[i].x = 0;
		m_cHideAlarmScreen.m_EndPoint[i].y = 0;
	}

	g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng] = 0;
	m_hideAlarm.detect_area.count = 0;

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HIDE_ALARM, (char *)&m_hideAlarm, sizeof(m_hideAlarm), TRUE);
	if( iRet != 0)
	{
		return;
	}

	for(int i = 0; i< 4; i++)
	{
		m_cHideAlarmScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
	}
}

void CHideWarning::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CHideWarning::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CHideWarning::OnBnClickedCheckStartpaint()  //开始画图
{
	// TODO: 在此添加控件通知处理程序代码
	int iDeviceWidth = m_hideAlarm.max_width;
	int iDeviceHeight = m_hideAlarm.max_height;

	if(m_bStartPaint.GetCheck() == 1)
	{
		//画出已经有的区域
		for(int i = 0; i < g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]; i++)
		{
			m_cHideAlarmScreen.DrawHideAlarmBorder(i,m_cHideAlarmScreen.m_StartPoint[i].x, 
				m_cHideAlarmScreen.m_StartPoint[i].y,
				(m_cHideAlarmScreen.m_EndPoint[i].x - m_cHideAlarmScreen.m_StartPoint[i].x), 
				(m_cHideAlarmScreen.m_EndPoint[i].y - m_cHideAlarmScreen.m_StartPoint[i].y));
		}
		g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng] = m_hideAlarm.detect_area.count;
		for(int j = g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]; j < 4; j++)
		{
			m_cHideAlarmScreen.m_cBorderDlg[j].ShowWindow(SW_HIDE);
		}
		m_cHideAlarmScreen.m_bStartPaint = TRUE;
		g_PubData.g_bHideAlarmDrawBorder = TRUE;
	}
	else
	{
		for(int i = 0; i< g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]; i++)
		{
			m_cHideAlarmScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
		}
		m_cHideAlarmScreen.m_bStartPaint = FALSE;
		g_PubData.g_bHideAlarmDrawBorder = FALSE;
	}
}
