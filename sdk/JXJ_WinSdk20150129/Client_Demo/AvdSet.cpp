// AvdSet.cpp : 实现文件
//AVD配置窗口

#include "stdafx.h"
#include "Client_Demo.h"
#include "AvdSet.h"
#include "Pub_Data.h"


// CAvdSet 对话框


IMPLEMENT_DYNAMIC(CAvdSet, CDialog)

CAvdSet::CAvdSet(CWnd* pParent /*=NULL*/)
	: CDialog(CAvdSet::IDD, pParent)
{

	ZeroMemory(&m_AvdConfig, sizeof(JAvdConfig));
	m_iSaveIndex = 0;
	for(int i =0 ;i< MAX_IVS_AVD_RULES; i++)
	{
		m_iIfCheck[i]		= -1;
		m_iLever[i]			= -1;
		m_iWarnTime[i]		= -1;
		m_iSaveIndexAll[i]  = -1;
	}
}

CAvdSet::~CAvdSet()
{
	DestroyWindow();
}

void CAvdSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_STARTAVD, m_StartAvd);
	DDX_Control(pDX, IDC_COMBO_DIAGNOSERULE, m_DiagnRule);
	DDX_Control(pDX, IDC_CHECK_IFCHECK, m_IfCheck);
	DDX_Control(pDX, IDC_COMBO_SENSIVITY, m_Sensivity);
	DDX_Control(pDX, IDC_COMBO_WARNINGTIME, m_WarningTime);
	DDX_Control(pDX, IDC_CHECK_START1, m_Start1);
	DDX_Control(pDX, IDC_CHECK_START2, m_Start2);
	DDX_Control(pDX, IDC_CHECK_START3, m_start3);
	DDX_Control(pDX, IDC_CHECK_START4, m_Start4);
	DDX_Control(pDX, IDC_DATASTART1, m_StartData1);
	DDX_Control(pDX, IDC_DATASTART2, m_SatrtData2);
	DDX_Control(pDX, IDC_DATASTART3, m_SatrtData3);
	DDX_Control(pDX, IDC_DATASTART4, m_SatrtData4);
	DDX_Control(pDX, IDC_DATAEND1, m_EndData1);
	DDX_Control(pDX, IDC_DATAEND2, m_EndData2);
	DDX_Control(pDX, IDC_DATAEND3, m_EndData3);
	DDX_Control(pDX, IDC_DATAEND4, m_EndData4);
}


BEGIN_MESSAGE_MAP(CAvdSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CAvdSet::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CAvdSet::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_CHECK_START1, &CAvdSet::OnBnClickedCheckStart1)
	ON_BN_CLICKED(IDC_CHECK_START2, &CAvdSet::OnBnClickedCheckStart2)
	ON_BN_CLICKED(IDC_CHECK_START3, &CAvdSet::OnBnClickedCheckStart3)
	ON_BN_CLICKED(IDC_CHECK_START4, &CAvdSet::OnBnClickedCheckStart4)
	ON_CBN_SELCHANGE(IDC_COMBO_DIAGNOSERULE, &CAvdSet::OnCbnSelchangeComboDiagnoserule)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CAvdSet 消息处理程序
BOOL CAvdSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_DiagnRule.AddString(_T("亮度异常"));
		m_DiagnRule.AddString(_T("清晰度异常"));
		m_DiagnRule.AddString(_T("噪声异常"));
		m_DiagnRule.AddString(_T("偏色"));
		m_DiagnRule.AddString(_T("场景变换"));
	}
	else
	{
		m_DiagnRule.AddString(_T("Brightness "));
		m_DiagnRule.AddString(_T("Clarity"));
		m_DiagnRule.AddString(_T("Noise"));
		m_DiagnRule.AddString(_T("Colour cast"));
		m_DiagnRule.AddString(_T("Scene Change"));
	}
	
	m_DiagnRule.SetCurSel(0);

	for(int i  = 0; i< 5; i++)
	{
		CString str = _T("");
		str.Format(_T("%d"), i);
		m_Sensivity.AddString(str);
	}

	for(int i = 0; i< 21; i++)
	{
		CString str = _T("");
		str.Format(_T("%d"), i);
		m_WarningTime.AddString(str);
	}


	m_WarningTime.EnableWindow(FALSE);// 暂不支持
	m_StartData1.EnableWindow(FALSE);
	m_SatrtData2.EnableWindow(FALSE);
	m_SatrtData3.EnableWindow(FALSE);
	m_SatrtData4.EnableWindow(FALSE);
	m_EndData1.EnableWindow(FALSE);
	m_EndData2.EnableWindow(FALSE);
	m_EndData3.EnableWindow(FALSE);
	m_EndData4.EnableWindow(FALSE);


	return TRUE;
}

void CAvdSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	m_AvdConfig.enable = m_StartAvd.GetCheck();

	m_AvdConfig.sched_time[0].open = m_Start1.GetCheck();
	m_AvdConfig.sched_time[1].open = m_Start2.GetCheck();
	m_AvdConfig.sched_time[2].open = m_start3.GetCheck();
	m_AvdConfig.sched_time[3].open = m_Start4.GetCheck();

	SetAvdRule();
	int i = m_DiagnRule.GetCurSel();
	m_AvdConfig.avd_rule[i].enable = m_IfCheck.GetCheck();
	m_AvdConfig.avd_rule[i].level = m_Sensivity.GetCurSel();
	m_AvdConfig.avd_rule[i].alarm_times = m_WarningTime.GetCurSel();


	if(m_AvdConfig.sched_time[0].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_StartData1.GetTime(timeStart);
		m_EndData1.GetTime(timeEnd);
		m_AvdConfig.sched_time[0].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_AvdConfig.sched_time[0].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}
	
	if(m_AvdConfig.sched_time[1].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_SatrtData2.GetTime(timeStart);
		m_EndData2.GetTime(timeEnd);
		m_AvdConfig.sched_time[1].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_AvdConfig.sched_time[1].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	if(m_AvdConfig.sched_time[2].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_SatrtData3.GetTime(timeStart);
		m_EndData3.GetTime(timeEnd);
		m_AvdConfig.sched_time[2].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_AvdConfig.sched_time[2].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	if(m_AvdConfig.sched_time[3].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_SatrtData4.GetTime(timeStart);
		m_EndData4.GetTime(timeEnd);
		m_AvdConfig.sched_time[3].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_AvdConfig.sched_time[3].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	int iRet = -1;
	JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_AVD_CFG, (char *)&m_AvdConfig, sizeof(JAvdConfig), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(_T("Save Failed!"));
		return ;
	}
	
}

void CAvdSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_AVD_CFG, (char *)&m_AvdConfig, sizeof(JAvdConfig),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(_T("Failed to get"));
		return ;
	}

	RefreshWindow();
	
}


int CAvdSet::RefreshWindow()
{

	m_StartAvd.SetCheck(m_AvdConfig.enable);

	int i = m_DiagnRule.GetCurSel();
	m_IfCheck.SetCheck(m_AvdConfig.avd_rule[i].enable);
	m_Sensivity.SetCurSel(m_AvdConfig.avd_rule[i].level);
	m_WarningTime.SetCurSel(m_AvdConfig.avd_rule[i].alarm_times);

	m_Start1.SetCheck(m_AvdConfig.sched_time[0].open);
	m_Start2.SetCheck(m_AvdConfig.sched_time[1].open);
	m_start3.SetCheck(m_AvdConfig.sched_time[2].open);
	m_Start4.SetCheck(m_AvdConfig.sched_time[3].open);
	if(m_AvdConfig.sched_time[0].open == 1)
	{
		m_StartData1.EnableWindow(TRUE);
		m_EndData1.EnableWindow(TRUE);
	}
	else
	{
		m_StartData1.EnableWindow(FALSE);
		m_EndData1.EnableWindow(FALSE);
	}
	if(m_AvdConfig.sched_time[1].open == 1)
	{
		m_SatrtData2.EnableWindow(TRUE);
		m_EndData2.EnableWindow(TRUE);
	}
	else
	{
		m_SatrtData2.EnableWindow(FALSE);
		m_EndData2.EnableWindow(FALSE);
	}
	if(m_AvdConfig.sched_time[2].open == 1)
	{
		m_SatrtData3.EnableWindow(TRUE);
		m_EndData3.EnableWindow(TRUE);
	}
	else
	{
		m_SatrtData3.EnableWindow(FALSE);
		m_EndData3.EnableWindow(FALSE);
	}
	if(m_AvdConfig.sched_time[3].open == 1)
	{
		m_SatrtData4.EnableWindow(TRUE);
		m_EndData4.EnableWindow(TRUE);
	}
	else
	{
		m_SatrtData4.EnableWindow(FALSE);
		m_EndData4.EnableWindow(FALSE);
	}
	

	int iTimeS1 =  m_AvdConfig.sched_time[0].begin_sec;
	int iTimeS2 =  m_AvdConfig.sched_time[1].begin_sec;
	int iTimeS3 =  m_AvdConfig.sched_time[2].begin_sec;
	int iTimeS4 =  m_AvdConfig.sched_time[3].begin_sec;

	int iTimeE1 = m_AvdConfig.sched_time[0].end_sec;
	int iTimeE2 = m_AvdConfig.sched_time[1].end_sec;
	int iTimeE3 = m_AvdConfig.sched_time[2].end_sec;
	int iTimeE4 = m_AvdConfig.sched_time[3].end_sec;
	
	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();																	// 小时		//分钟			//秒
	COleDateTime startTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS1/3600, (iTimeS1%3600)/60, (iTimeS1%3600)%60);
	COleDateTime startTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS2/3600, (iTimeS2%3600)/60, (iTimeS2%3600)%60);
	COleDateTime startTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS3/3600, (iTimeS3%3600)/60, (iTimeS3%3600)%60);
	COleDateTime startTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS4/3600, (iTimeS4%3600)/60, (iTimeS4%3600)%60);
	m_StartData1.SetTime(startTime1);
	m_SatrtData2.SetTime(startTime2);
	m_SatrtData3.SetTime(startTime3);
	m_SatrtData4.SetTime(startTime4);

	COleDateTime endTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE1/3600, (iTimeE1%3600)/60, (iTimeE1%3600)%60);
	COleDateTime endTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE2/3600, (iTimeE2%3600)/60, (iTimeE2%3600)%60);
	COleDateTime endTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE3/3600, (iTimeE3%3600)/60, (iTimeE3%3600)%60);
	COleDateTime endTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE4/3600, (iTimeE4%3600)/60, (iTimeE4%3600)%60);
	m_EndData1.SetTime(endTime1);
	m_EndData2.SetTime(endTime2);
	m_EndData3.SetTime(endTime3);
	m_EndData4.SetTime(endTime4);

	return 0;
}
void CAvdSet::OnBnClickedCheckStart1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if(m_Start1.GetCheck() == 1)
	{
		m_StartData1.EnableWindow(TRUE);
		m_EndData1.EnableWindow(TRUE);
	}
	else
	{
		m_StartData1.EnableWindow(FALSE);
		m_EndData1.EnableWindow(FALSE);
	}
}

void CAvdSet::OnBnClickedCheckStart2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_Start2.GetCheck() == 1)
	{
		m_SatrtData2.EnableWindow(TRUE);
		m_EndData2.EnableWindow(TRUE);
	}
	else
	{
		m_SatrtData2.EnableWindow(FALSE);
		m_EndData2.EnableWindow(FALSE);
	}
}

void CAvdSet::OnBnClickedCheckStart3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_start3.GetCheck() == 1)
	{
		m_SatrtData3.EnableWindow(TRUE);
		m_EndData3.EnableWindow(TRUE);
	}
	else
	{
		m_SatrtData3.EnableWindow(FALSE);
		m_EndData3.EnableWindow(FALSE);
	}
}

void CAvdSet::OnBnClickedCheckStart4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_Start4.GetCheck() == 1)
	{
		m_SatrtData4.EnableWindow(TRUE);
		m_EndData4.EnableWindow(TRUE);
	}
	else
	{
		m_SatrtData4.EnableWindow(FALSE);
		m_EndData4.EnableWindow(FALSE);
	}
}

void CAvdSet::OnCbnSelchangeComboDiagnoserule()
{
	// TODO: 在此添加控件通知处理程序代码

	//保存设置的视频诊断信息
	m_iIfCheck[m_iSaveIndex] = m_IfCheck.GetCheck();
	m_iLever[m_iSaveIndex] = m_Sensivity.GetCurSel();
	m_iWarnTime[m_iSaveIndex] = m_WarningTime.GetCurSel();
	m_iSaveIndexAll[m_iSaveIndex] = m_iSaveIndex;

	int i = m_DiagnRule.GetCurSel();
	m_IfCheck.SetCheck(m_AvdConfig.avd_rule[i].enable);
	m_Sensivity.SetCurSel(m_AvdConfig.avd_rule[i].level);
	m_WarningTime.SetCurSel(m_AvdConfig.avd_rule[i].alarm_times);
	m_iSaveIndex = i;  //保存该次索引
	
}

void CAvdSet::SetAvdRule()
{
	for(int i =0; i< MAX_IVS_AVD_RULES; i++)
	{
		for(int j = 0; j< MAX_IVS_AVD_RULES; j++)
		{
			if(i == m_iSaveIndexAll[j])
			{
				m_AvdConfig.avd_rule[i].enable = m_iIfCheck[i];
				m_AvdConfig.avd_rule[i].level = m_iLever[i];
				m_AvdConfig.avd_rule[i].alarm_times = m_iWarnTime[i];
			}	
		}	
	}
}

void CAvdSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnClose();
}

void CAvdSet::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
