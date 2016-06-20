// Ir_CutSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "Ir_CutSet.h"
#include "Pub_Data.h"



// CIr_CutSet 对话框

IMPLEMENT_DYNAMIC(CIr_CutSet, CDialog)

CIr_CutSet::CIr_CutSet(CWnd* pParent /*=NULL*/)
	: CDialog(CIr_CutSet::IDD, pParent)
{
	ZeroMemory(&m_IrcutCtrl, sizeof(m_IrcutCtrl));
}

CIr_CutSet::~CIr_CutSet()
{
	DestroyWindow();
}

void CIr_CutSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_AUTO_SWITCH, m_Radio1);
	DDX_Control(pDX, IDC_RADIO_MANUAL_SWITCH, m_Radio2);
	DDX_Control(pDX, IDC_RADIO_TIME_SWITCH, m_Radio3);
	DDX_Control(pDX, IDC_COMBO_SENSITIVE, m_Sensitive);
	DDX_Control(pDX, IDC_CHECK_START1, m_Start1);
	DDX_Control(pDX, IDC_DATASTART1, m_StartTime1);
	DDX_Control(pDX, IDC_DATAEND1, m_EndTime1);
	DDX_Control(pDX, IDC_CHECK_START2, m_Start2);
	DDX_Control(pDX, IDC_DATASTART2, m_StartTime2);
	DDX_Control(pDX, IDC_DATAEND2, m_EndTime2);
	DDX_Control(pDX, IDC_CHECK_START3, m_Start3);
	DDX_Control(pDX, IDC_DATASTART3, m_StartTime3);
	DDX_Control(pDX, IDC_DATAEND3, m_EndTime3);
	DDX_Control(pDX, IDC_CHECK_START4, m_Start4);
	DDX_Control(pDX, IDC_DATASTART4, m_StartTime4);
	DDX_Control(pDX, IDC_DATAEND4, m_EndTime4);
	DDX_Control(pDX, IDC_COMBO_SETCOLOR, m_SetColor);
	DDX_Control(pDX, IDC_COMBO_MODEL, m_Model);
}


BEGIN_MESSAGE_MAP(CIr_CutSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CIr_CutSet::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CIr_CutSet::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_CHECK_START1, &CIr_CutSet::OnBnClickedCheckStart1)
	ON_BN_CLICKED(IDC_CHECK_START2, &CIr_CutSet::OnBnClickedCheckStart2)
	ON_BN_CLICKED(IDC_CHECK_START3, &CIr_CutSet::OnBnClickedCheckStart3)
	ON_BN_CLICKED(IDC_CHECK_START4, &CIr_CutSet::OnBnClickedCheckStart4)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CIr_CutSet 消息处理程序
BOOL CIr_CutSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_Sensitive.AddString(_T("低灵敏度"));
		m_Sensitive.AddString(_T("高灵敏度"));

		m_SetColor.AddString(_T("自动彩转黑"));
		m_SetColor.AddString(_T("固定为彩色"));
		m_SetColor.AddString(_T("固定为黑白"));

		m_Model.AddString(_T("白天模式"));
		m_Model.AddString(_T("夜晚模式"));

	}
	else
	{
		m_Sensitive.AddString(_T("Low sensitivity"));
		m_Sensitive.AddString(_T("High sensitivity"));

		m_SetColor.AddString(_T("Automatic color to black"));
		m_SetColor.AddString(_T("Fixed color"));
		m_SetColor.AddString(_T("Fixed to the black and white"));

		m_Model.AddString(_T("Day mode"));
		m_Model.AddString(_T("Night mode"));

	}
	m_StartTime1.EnableWindow(FALSE);
	m_StartTime2.EnableWindow(FALSE);
	m_StartTime3.EnableWindow(FALSE);
	m_StartTime4.EnableWindow(FALSE);

	m_EndTime1.EnableWindow(FALSE);
	m_EndTime2.EnableWindow(FALSE);
	m_EndTime3.EnableWindow(FALSE);
	m_EndTime4.EnableWindow(FALSE);


	return TRUE;
}
void CIr_CutSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代

	if(m_Radio1.GetCheck() == 1)
	{
		m_IrcutCtrl.ircut_ctrl[0].switch_type = 0;
	}
	else if(m_Radio2.GetCheck() == 1)
	{
		m_IrcutCtrl.ircut_ctrl[0].switch_type = 1;
		
	}
	else if(m_Radio3.GetCheck() == 1)
	{
		m_IrcutCtrl.ircut_ctrl[0].switch_type = 2;
	}
	m_IrcutCtrl.ircut_ctrl[0].auto_c2b = m_SetColor.GetCurSel();
	m_IrcutCtrl.ircut_ctrl[0].auto_switch.sensitive = m_Sensitive.GetCurSel();
	m_IrcutCtrl.ircut_ctrl[0].manu_switch.open = m_Model.GetCurSel();

	m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[0].open = m_Start1.GetCheck();
	m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[1].open = m_Start2.GetCheck();
	m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[2].open = m_Start3.GetCheck();
	m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[3].open = m_Start4.GetCheck();

	if(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[0].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_StartTime1.GetTime(timeStart);
		m_EndTime1.GetTime(timeEnd);
		m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[0].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[0].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	if(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[1].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_StartTime2.GetTime(timeStart);
		m_EndTime2.GetTime(timeEnd);
		m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[1].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[1].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	if(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[2].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_StartTime3.GetTime(timeStart);
		m_EndTime3.GetTime(timeEnd);
		m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[2].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[2].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	if(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[3].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_StartTime4.GetTime(timeStart);
		m_EndTime4.GetTime(timeEnd);
		m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[3].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[3].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}


	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_IR_CUT_CFG, (char *)&m_IrcutCtrl, sizeof(m_IrcutCtrl), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}
}

void CIr_CutSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 & DEV_CAP_IR )//根据能力集判断是否支持
	{
		GetDlgItem(IDC_BUTTON_FLASH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_FLASH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
		return;
	}

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_IR_CUT_CFG, (char *)&m_IrcutCtrl, sizeof(m_IrcutCtrl),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshWindow();

}


int CIr_CutSet::ReFreshWindow()
{
	
	
	m_SetColor.SetCurSel(m_IrcutCtrl.ircut_ctrl[0].auto_c2b);

	if(m_IrcutCtrl.ircut_ctrl[0].switch_type == 0)
	{
		m_Radio1.SetCheck(1);
		m_Radio2.SetCheck(0);
		m_Radio3.SetCheck(0);	
	}
	else if(m_IrcutCtrl.ircut_ctrl[0].switch_type == 1)
	{
		m_Radio1.SetCheck(0);
		m_Radio2.SetCheck(1);
		m_Radio3.SetCheck(0);
	}
	else if(m_IrcutCtrl.ircut_ctrl[0].switch_type == 2)
	{
		m_Radio1.SetCheck(0);
		m_Radio2.SetCheck(0);
		m_Radio3.SetCheck(1);
	}
	m_Sensitive.SetCurSel(m_IrcutCtrl.ircut_ctrl[0].auto_switch.sensitive);
	m_Model.SetCurSel(m_IrcutCtrl.ircut_ctrl[0].manu_switch.open);

	m_Start1.SetCheck(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[0].open);
	m_Start2.SetCheck(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[1].open);
	m_Start3.SetCheck(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[2].open);
	m_Start4.SetCheck(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[3].open);
	if(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[0].open == 1)
	{
		m_StartTime1.EnableWindow(TRUE);
		m_EndTime1.EnableWindow(TRUE);
	}
	else
	{
		m_StartTime1.EnableWindow(FALSE);
		m_EndTime1.EnableWindow(FALSE);
	}

	if(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[1].open == 1)
	{	
		m_StartTime2.EnableWindow(TRUE);
		m_EndTime2.EnableWindow(TRUE);
	}
	else
	{
		m_StartTime2.EnableWindow(FALSE);
		m_EndTime2.EnableWindow(FALSE);
	}

	if(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[2].open == 1)
	{
		m_StartTime3.EnableWindow(TRUE);
		m_EndTime3.EnableWindow(TRUE);
	}
	else
	{
		m_StartTime3.EnableWindow(FALSE);
		m_EndTime3.EnableWindow(FALSE);
	}

	if(m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[3].open == 1)
	{
		m_StartTime4.EnableWindow(TRUE);
		m_EndTime4.EnableWindow(TRUE);
	}
	else
	{
		m_StartTime4.EnableWindow(FALSE);
		m_EndTime4.EnableWindow(FALSE);
	}

	int iTimeS1 =  m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[0].begin_sec;
	int iTimeS2 =  m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[1].begin_sec;
	int iTimeS3 =  m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[2].begin_sec;
	int iTimeS4 =  m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[3].begin_sec;

	int iTimeE1 = m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[0].end_sec;
	int iTimeE2 = m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[1].end_sec;
	int iTimeE3 = m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[2].end_sec;
	int iTimeE4 = m_IrcutCtrl.ircut_ctrl[0].timer_switch.seg_time[3].end_sec;

	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();																	// 小时		//分钟			//秒
	COleDateTime startTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS1/3600, (iTimeS1%3600)/60, (iTimeS1%3600)%60);
	COleDateTime startTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS2/3600, (iTimeS2%3600)/60, (iTimeS2%3600)%60);
	COleDateTime startTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS3/3600, (iTimeS3%3600)/60, (iTimeS3%3600)%60);
	COleDateTime startTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS4/3600, (iTimeS4%3600)/60, (iTimeS4%3600)%60);
	m_StartTime1.SetTime(startTime1);
	m_StartTime2.SetTime(startTime2);
	m_StartTime3.SetTime(startTime3);
	m_StartTime4.SetTime(startTime4);

	COleDateTime endTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE1/3600, (iTimeE1%3600)/60, (iTimeE1%3600)%60);
	COleDateTime endTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE2/3600, (iTimeE2%3600)/60, (iTimeE2%3600)%60);
	COleDateTime endTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE3/3600, (iTimeE3%3600)/60, (iTimeE3%3600)%60);
	COleDateTime endTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE4/3600, (iTimeE4%3600)/60, (iTimeE4%3600)%60);
	m_EndTime1.SetTime(endTime1);
	m_EndTime2.SetTime(endTime2);
	m_EndTime3.SetTime(endTime3);
	m_EndTime4.SetTime(endTime4);

	return 0;
}
void CIr_CutSet::OnBnClickedCheckStart1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_Start1.GetCheck() == 1)
	{
		m_StartTime1.EnableWindow(TRUE);
		m_EndTime1.EnableWindow(TRUE);
	}
	else if(m_Start1.GetCheck() == 0)
	{
		m_StartTime1.EnableWindow(FALSE);
		m_EndTime1.EnableWindow(FALSE);
	}
}

void CIr_CutSet::OnBnClickedCheckStart2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_Start2.GetCheck() == 1)
	{
		m_StartTime2.EnableWindow(TRUE);
		m_EndTime2.EnableWindow(TRUE);
	}
	else if(m_Start2.GetCheck() == 0)
	{
		m_StartTime2.EnableWindow(FALSE);
		m_EndTime2.EnableWindow(FALSE);
	}
}

void CIr_CutSet::OnBnClickedCheckStart3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_Start3.GetCheck() == 1)
	{
		m_StartTime3.EnableWindow(TRUE);
		m_EndTime3.EnableWindow(TRUE);
	}
	else if(m_Start3.GetCheck() == 0)
	{
		m_StartTime3.EnableWindow(FALSE);
		m_EndTime3.EnableWindow(FALSE);
	}
}

void CIr_CutSet::OnBnClickedCheckStart4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_Start4.GetCheck() == 1)
	{
		m_StartTime4.EnableWindow(TRUE);
		m_EndTime4.EnableWindow(TRUE);
	}
	else if(m_Start4.GetCheck() == 0)
	{
		m_StartTime4.EnableWindow(FALSE);
		m_EndTime4.EnableWindow(FALSE);
	}
}


void CIr_CutSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
