// IoWarning.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "IoWarning.h"
#include "Pub_Data.h"

// CIoWarning 对话框





IMPLEMENT_DYNAMIC(CIoWarning, CDialog)

CIoWarning::CIoWarning(CWnd* pParent /*=NULL*/)
	: CDialog(CIoWarning::IDD, pParent)
{

}

CIoWarning::~CIoWarning()
{
	DestroyWindow();
}

void CIoWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_channel);
	DDX_Control(pDX, IDC_CHECK_STARTIO, m_StartIo);
	DDX_Control(pDX, IDC_COMBO_IOTYPE, m_IoType);
	DDX_Control(pDX, IDC_COMBO_SECONDS, m_Seconds);
}


BEGIN_MESSAGE_MAP(CIoWarning, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CIoWarning::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CIoWarning::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SETTIME, &CIoWarning::OnBnClickedButtonSettime)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, &CIoWarning::OnCbnSelchangeComboChannel)
END_MESSAGE_MAP()


// CIoWarning 消息处理程序
BOOL CIoWarning::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_IoType.AddString(_T("常闭探头"));
		m_IoType.AddString(_T("常开探头"));
	}
	else
	{
		m_IoType.AddString(_T("Normal close"));
		m_IoType.AddString(_T("Normally open"));
	}
	

	for(int i = 0; i< 61; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		m_Seconds.AddString(str);
	}


	//OnBnClickedButtonFlash();

	return TRUE;
}

void CIoWarning::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_channel.GetCurSel() < 0 )
	{
		for(int i = 0; i< g_PubData.g_iIoWarningChannelNul; i++)
		{
			CString str = _T("");
			str.Format(_T("%d"), i);
			m_channel.AddString(str);
		}
		m_channel.SetCurSel(0);
		m_iSelChannel = 0;
	}

	OnCbnSelchangeComboChannel();
}

void CIoWarning::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_channel.GetCurSel();
	m_ioAlarm[i].alarm_enable = m_StartIo.GetCheck();
	m_ioAlarm[i].io_type = m_IoType.GetCurSel();
	m_ioAlarm[i].detect_interval = m_Seconds.GetCurSel();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_IO_ALARM, (char *)&m_ioAlarm[i], sizeof(m_ioAlarm[i]), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}
	
}


int CIoWarning::ReFreshWindow()
{


	int i = m_channel.GetCurSel();
	
	m_StartIo.SetCheck(m_ioAlarm[i].alarm_enable);
	m_IoType.SetCurSel(m_ioAlarm[i].io_type);
	m_Seconds.SetCurSel(m_ioAlarm[i].detect_interval);
	return 0;
}
void CIoWarning::OnBnClickedButtonSettime()
{
	// TODO: 在此添加控件通知处理程序代码
	int j = m_channel.GetCurSel();
	g_PubData.g_iShowTimeDlgFlag = 4;
	int id = m_cVideoTime.DoModal();
	if(id == IDOK)
	{
		int i = m_cVideoTime.m_iSelIndex;
		m_ioAlarm[j].week.days[i].seg[0].enable = m_cVideoTime.m_iVideoTime1;
		m_ioAlarm[j].week.days[i].seg[1].enable = m_cVideoTime.m_iVideoTime2;
		m_ioAlarm[j].week.days[i].seg[2].enable = m_cVideoTime.m_iVideoTime3;
		m_ioAlarm[j].week.days[i].seg[3].enable = m_cVideoTime.m_iVideoTime4;
		if(m_ioAlarm[j].week.days[i].seg[0].enable == 1)
		{
			m_ioAlarm[j].week.days[i].seg[0].time_start.hour = m_cVideoTime.m_STime1.GetHour();
			m_ioAlarm[j].week.days[i].seg[0].time_start.minute = m_cVideoTime.m_STime1.GetMinute();
			m_ioAlarm[j].week.days[i].seg[0].time_start.second = m_cVideoTime.m_STime1.GetSecond();

			m_ioAlarm[j].week.days[i].seg[0].time_end.hour = m_cVideoTime.m_ETime1.GetHour();
			m_ioAlarm[j].week.days[i].seg[0].time_end.minute = m_cVideoTime.m_ETime1.GetMinute();
			m_ioAlarm[j].week.days[i].seg[0].time_end.second = m_cVideoTime.m_ETime1.GetSecond();
		}

		if(m_ioAlarm[j].week.days[i].seg[1].enable == 1)
		{
			m_ioAlarm[j].week.days[i].seg[1].time_start.hour = m_cVideoTime.m_STime2.GetHour();
			m_ioAlarm[j].week.days[i].seg[1].time_start.minute = m_cVideoTime.m_STime2.GetMinute();
			m_ioAlarm[j].week.days[i].seg[1].time_start.second = m_cVideoTime.m_STime2.GetSecond();

			m_ioAlarm[j].week.days[i].seg[1].time_end.hour = m_cVideoTime.m_ETime2.GetHour();
			m_ioAlarm[j].week.days[i].seg[1].time_end.minute = m_cVideoTime.m_ETime2.GetMinute();
			m_ioAlarm[j].week.days[i].seg[1].time_end.second = m_cVideoTime.m_ETime2.GetSecond();
		}

		if(m_ioAlarm[j].week.days[i].seg[2].enable == 1)
		{
			m_ioAlarm[j].week.days[i].seg[2].time_start.hour = m_cVideoTime.m_STime3.GetHour();
			m_ioAlarm[j].week.days[i].seg[2].time_start.minute = m_cVideoTime.m_STime3.GetMinute();
			m_ioAlarm[j].week.days[i].seg[2].time_start.second = m_cVideoTime.m_STime3.GetSecond();

			m_ioAlarm[j].week.days[i].seg[2].time_end.hour = m_cVideoTime.m_ETime3.GetHour();
			m_ioAlarm[j].week.days[i].seg[2].time_end.minute = m_cVideoTime.m_ETime3.GetMinute();
			m_ioAlarm[j].week.days[i].seg[2].time_end.second = m_cVideoTime.m_ETime3.GetSecond();
		}

		if(m_ioAlarm[j].week.days[i].seg[3].enable == 1)
		{
			m_ioAlarm[j].week.days[i].seg[3].time_start.hour = m_cVideoTime.m_STime4.GetHour();
			m_ioAlarm[j].week.days[i].seg[3].time_start.minute = m_cVideoTime.m_STime4.GetMinute();
			m_ioAlarm[j].week.days[i].seg[3].time_start.second = m_cVideoTime.m_STime4.GetSecond();

			m_ioAlarm[j].week.days[i].seg[3].time_end.hour = m_cVideoTime.m_ETime4.GetHour();
			m_ioAlarm[j].week.days[i].seg[3].time_end.minute = m_cVideoTime.m_ETime4.GetMinute();
			m_ioAlarm[j].week.days[i].seg[3].time_end.second = m_cVideoTime.m_ETime4.GetSecond();
		}
		OnBnClickedButtonSave();
	}
}


void CIoWarning::ShowVideoTime(int iIndex)
{

	int i = m_iSelChannel;//m_channel.GetCurSel();
	g_PubData.g_iVideoTime1 = m_ioAlarm[i].week.days[iIndex].seg[0].enable;
	g_PubData.g_iVideoTime2 = m_ioAlarm[i].week.days[iIndex].seg[1].enable;
	g_PubData.g_iVideoTime3 = m_ioAlarm[i].week.days[iIndex].seg[2].enable;
	g_PubData.g_iVideoTime4 = m_ioAlarm[i].week.days[iIndex].seg[3].enable;
	if(m_ioAlarm[i].week.days[iIndex].seg[0].enable == 1)
	{
		int iY = m_ioAlarm[i].week.days[iIndex].seg[0].time_start.hour;
		int iM = m_ioAlarm[i].week.days[iIndex].seg[0].time_start.minute;
		int iD = m_ioAlarm[i].week.days[iIndex].seg[0].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime1 = Stime;

		iY = m_ioAlarm[i].week.days[iIndex].seg[0].time_end.hour;
		iM = m_ioAlarm[i].week.days[iIndex].seg[0].time_end.minute;
		iD = m_ioAlarm[i].week.days[iIndex].seg[0].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime1 = Etime;

	}
	if(m_ioAlarm[i].week.days[iIndex].seg[1].enable == 1)
	{
		int iY = m_ioAlarm[i].week.days[iIndex].seg[1].time_start.hour;
		int iM = m_ioAlarm[i].week.days[iIndex].seg[1].time_start.minute;
		int iD = m_ioAlarm[i].week.days[iIndex].seg[1].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime2 = Stime;

		iY = m_ioAlarm[i].week.days[iIndex].seg[1].time_end.hour;
		iM = m_ioAlarm[i].week.days[iIndex].seg[1].time_end.minute;
		iD = m_ioAlarm[i].week.days[iIndex].seg[1].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime2 = Etime;
	}
	if(m_ioAlarm[i].week.days[iIndex].seg[2].enable == 1)
	{
		int iY = m_ioAlarm[i].week.days[iIndex].seg[2].time_start.hour;
		int iM = m_ioAlarm[i].week.days[iIndex].seg[2].time_start.minute;
		int iD = m_ioAlarm[i].week.days[iIndex].seg[2].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime3 = Stime;

		iY = m_ioAlarm[i].week.days[iIndex].seg[2].time_end.hour;
		iM = m_ioAlarm[i].week.days[iIndex].seg[2].time_end.minute;
		iD = m_ioAlarm[i].week.days[iIndex].seg[2].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime3 = Etime;
	}
	if(m_ioAlarm[i].week.days[iIndex].seg[3].enable == 1)
	{
		int iY = m_ioAlarm[i].week.days[iIndex].seg[3].time_start.hour;
		int iM = m_ioAlarm[i].week.days[iIndex].seg[3].time_start.minute;
		int iD = m_ioAlarm[i].week.days[iIndex].seg[3].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime4 = Stime;

		iY = m_ioAlarm[i].week.days[iIndex].seg[3].time_end.hour;
		iM = m_ioAlarm[i].week.days[iIndex].seg[3].time_end.minute;
		iD = m_ioAlarm[i].week.days[iIndex].seg[3].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime4 = Etime;
	}
}
void CIoWarning::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CIoWarning::OnCbnSelchangeComboChannel()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_channel.GetCurSel();

	m_iSelChannel = i;

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],i,PARAM_IO_ALARM, (char *)&m_ioAlarm[i], sizeof(m_ioAlarm[i]),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();

}
