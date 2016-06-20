// ChannelStream.cpp : 实现文件
//通道码率切换窗口

#include "stdafx.h"
#include "Client_Demo.h"
#include "ChannelStream.h"
#include "Pub_Data.h"

// CChannelStream 对话框



IMPLEMENT_DYNAMIC(CChannelStream, CDialog)

CChannelStream::CChannelStream(CWnd* pParent /*=NULL*/)
	: CDialog(CChannelStream::IDD, pParent)
{
	ZeroMemory(&m_autoBit, sizeof(m_autoBit));
}

CChannelStream::~CChannelStream()
{
	DestroyWindow();
}

void CChannelStream::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_STARTAUTOSTREAM, m_StartAutoStream);
	DDX_Control(pDX, IDC_COMBO_REPLACETYPE, m_ReplaceType);
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_StreamType);
	DDX_Control(pDX, IDC_EDIT_STREAM_HIGH, m_StreamHigh);
	DDX_Control(pDX, IDC_EDIT_STREAM_LOW, m_StreamLow);
	DDX_Control(pDX, IDC_CHECK_START1, m_StreamStart1);
	DDX_Control(pDX, IDC_CHECK_START2, m_StreamStart2);
	DDX_Control(pDX, IDC_CHECK_START3, m_StreamStart3);
	DDX_Control(pDX, IDC_CHECK_START4, m_StreamStart4);
	DDX_Control(pDX, IDC_DATASTART1, m_StreamStartTime1);
	DDX_Control(pDX, IDC_DATAEND1, m_StreamEndTime1);
	DDX_Control(pDX, IDC_DATASTART2, m_StreamStartTime2);
	DDX_Control(pDX, IDC_DATAEND2, m_StreamEndtime2);
	DDX_Control(pDX, IDC_DATASTART3, m_StreamStartTime3);
	DDX_Control(pDX, IDC_DATAEND3, m_StreamEndTime3);
	DDX_Control(pDX, IDC_DATASTART4, m_StreamStartTime4);
	DDX_Control(pDX, IDC_DATAEND4, m_StreamEndTime4);
	DDX_Control(pDX, IDC_EDIT_STREAM_HIGH2, m_SecondStreamHigh);
	DDX_Control(pDX, IDC_EDIT_STREAM_LOW2, m_SecondStreamLow);
	DDX_Control(pDX, IDC_EDIT_STREAM_HIGH3, m_ThirdStreamHigh);
	DDX_Control(pDX, IDC_EDIT_STREAM_LOW3, m_ThirdStreamLow);
}


BEGIN_MESSAGE_MAP(CChannelStream, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CChannelStream::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CChannelStream::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_CHECK_START1, &CChannelStream::OnBnClickedCheckStart1)
	ON_BN_CLICKED(IDC_CHECK_START2, &CChannelStream::OnBnClickedCheckStart2)
	ON_BN_CLICKED(IDC_CHECK_START3, &CChannelStream::OnBnClickedCheckStart3)
	ON_BN_CLICKED(IDC_CHECK_START4, &CChannelStream::OnBnClickedCheckStart4)
	ON_CBN_SELCHANGE(IDC_COMBO_REPLACETYPE, &CChannelStream::OnCbnSelchangeComboReplacetype)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CChannelStream 消息处理程序
BOOL CChannelStream::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_ReplaceType.AddString(_T("按时间段切换"));
		m_ReplaceType.AddString(_T("按ircut的状态切换"));
	}
	else
	{
		m_ReplaceType.AddString(_T("Switch on time"));
		m_ReplaceType.AddString(_T("According to the state switching ircut"));
	}


	m_StreamStartTime1.EnableWindow(FALSE);
	m_StreamEndTime1.EnableWindow(FALSE);

	m_StreamStartTime2.EnableWindow(FALSE);
	m_StreamEndtime2.EnableWindow(FALSE);

	m_StreamStartTime3.EnableWindow(FALSE);
	m_StreamEndTime3.EnableWindow(FALSE);

	m_StreamStartTime4.EnableWindow(FALSE);
	m_StreamEndTime4.EnableWindow(FALSE);

	
	return TRUE;
}
void CChannelStream::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_autoBit.venc[0].enable = m_StartAutoStream.GetCheck();
	m_autoBit.venc[0].type = m_ReplaceType.GetCurSel();
	m_autoBit.venc[0].sub_type = m_StreamType.GetCurSel();

	CString strText = _T("");
	m_StreamHigh.GetWindowText(strText);
	m_autoBit.venc[0].high_er[0] = _ttoi(strText);

	m_StreamLow.GetWindowText(strText);
	m_autoBit.venc[0].low_er[0] = _ttoi(strText);

	m_SecondStreamHigh.GetWindowText(strText);
	m_autoBit.venc[0].high_er[1] = _ttoi(strText);

	m_SecondStreamLow.GetWindowText(strText);
	m_autoBit.venc[0].low_er[1] = _ttoi(strText);


	m_ThirdStreamHigh.GetWindowText(strText);
	m_autoBit.venc[0].high_er[2] = _ttoi(strText);

	m_ThirdStreamLow.GetWindowText(strText);
	m_autoBit.venc[0].low_er[2] = _ttoi(strText);

	m_autoBit.venc[0].time_seg[0].open = m_StreamStart1.GetCheck();
	m_autoBit.venc[0].time_seg[1].open = m_StreamStart2.GetCheck();
	m_autoBit.venc[0].time_seg[2].open = m_StreamStart3.GetCheck();
	m_autoBit.venc[0].time_seg[3].open = m_StreamStart4.GetCheck();

	if(m_autoBit.venc[0].time_seg[0].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_StreamStartTime1.GetTime(timeStart);
		m_StreamEndTime1.GetTime(timeEnd);
		m_autoBit.venc[0].time_seg[0].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_autoBit.venc[0].time_seg[0].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	if(m_autoBit.venc[0].time_seg[1].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_StreamStartTime2.GetTime(timeStart);
		m_StreamEndtime2.GetTime(timeEnd);
		m_autoBit.venc[0].time_seg[1].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_autoBit.venc[0].time_seg[1].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	if(m_autoBit.venc[0].time_seg[2].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_StreamStartTime3.GetTime(timeStart);
		m_StreamEndTime3.GetTime(timeEnd);
		m_autoBit.venc[0].time_seg[2].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_autoBit.venc[0].time_seg[2].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	if(m_autoBit.venc[0].time_seg[3].open == 1)
	{
		COleDateTime timeStart;
		COleDateTime timeEnd;
		m_StreamStartTime4.GetTime(timeStart);
		m_StreamEndTime4.GetTime(timeEnd);
		m_autoBit.venc[0].time_seg[3].begin_sec = timeStart.GetHour()*3600 + timeStart.GetMinute()*60 + timeStart.GetSecond();
		m_autoBit.venc[0].time_seg[3].end_sec = timeEnd.GetHour()*3600 + timeEnd.GetMinute()*60 + timeEnd.GetSecond();
	}

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_VENC_AUTO_SWITCH, (char *)&m_autoBit, sizeof(m_autoBit), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return;
	}

}

void CChannelStream::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_VENC_AUTO_SWITCH, (char *)&m_autoBit, sizeof(m_autoBit),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}
}

int CChannelStream::ReFreshWindow()
{
	
	m_StartAutoStream.SetCheck(m_autoBit.venc[0].enable);
	m_ReplaceType.SetCurSel(m_autoBit.venc[0].type);
	if(g_PubData.g_iLanguageFlag == 0)
	{
		if(m_autoBit.venc[0].type == 0)
		{
			m_StreamType.ResetContent();
			m_StreamType.AddString(_T("在时间段内切换成低码率"));
			m_StreamType.AddString(_T("在时间段内切换为高码率"));
		}
		else if(m_autoBit.venc[0].type == 1)
		{
			m_StreamType.ResetContent();
			m_StreamType.AddString(_T("非红外模式设置为高码率"));
			m_StreamType.AddString(_T("非红外模式设置为低码率"));
		}
	}
	else
	{
		if(m_autoBit.venc[0].type == 0)
		{
			m_StreamType.ResetContent();
			m_StreamType.AddString(_T("Switch to low bit rate in the period."));
			m_StreamType.AddString(_T("Switch to high bit rate in the period."));
		}
		else if(m_autoBit.venc[0].type == 1)
		{
			m_StreamType.ResetContent();
			m_StreamType.AddString(_T("Non infrared mode is set to high bit rate"));
			m_StreamType.AddString(_T("Non infrared mode is set to low bit rate"));
		}
	}
	
	m_StreamType.SetCurSel(m_autoBit.venc[0].sub_type);

	CString strText = _T("");
	strText.Format(_T("%d"), m_autoBit.venc[0].high_er[0]);
	m_StreamHigh.SetWindowText(strText);
	strText.Format(_T("%d"), m_autoBit.venc[0].low_er[0]);
	m_StreamLow.SetWindowText(strText);

	strText = _T("");
	strText.Format(_T("%d"), m_autoBit.venc[0].high_er[1]);
	m_SecondStreamHigh.SetWindowText(strText);
	strText.Format(_T("%d"), m_autoBit.venc[0].low_er[1]);
	m_SecondStreamLow.SetWindowText(strText);

	strText = _T("");
	strText.Format(_T("%d"), m_autoBit.venc[0].high_er[2]);
	m_ThirdStreamHigh.SetWindowText(strText);
	strText.Format(_T("%d"), m_autoBit.venc[0].low_er[2]);
	m_ThirdStreamLow.SetWindowText(strText);



	m_StreamStart1.SetCheck(m_autoBit.venc[0].time_seg[0].open);
	m_StreamStart2.SetCheck(m_autoBit.venc[0].time_seg[1].open);
	m_StreamStart3.SetCheck(m_autoBit.venc[0].time_seg[2].open);
	m_StreamStart4.SetCheck(m_autoBit.venc[0].time_seg[3].open);
	if(m_autoBit.venc[0].time_seg[0].open == 1)
	{
		m_StreamStartTime1.EnableWindow(TRUE);
		m_StreamEndTime1.EnableWindow(TRUE);
	}
	if(m_autoBit.venc[0].time_seg[1].open == 1)
	{
		m_StreamStartTime2.EnableWindow(TRUE);
		m_StreamEndtime2.EnableWindow(TRUE);
	}
	if(m_autoBit.venc[0].time_seg[2].open == 1)
	{
		m_StreamStartTime3.EnableWindow(TRUE);
		m_StreamEndTime3.EnableWindow(TRUE);
	}
	if(m_autoBit.venc[0].time_seg[3].open == 1)
	{
		m_StreamStartTime4.EnableWindow(TRUE);
		m_StreamEndTime4.EnableWindow(TRUE);
	}

	int iTimeS1 =  m_autoBit.venc[0].time_seg[0].begin_sec;
	int iTimeS2 =  m_autoBit.venc[0].time_seg[1].begin_sec;
	int iTimeS3 =  m_autoBit.venc[0].time_seg[2].begin_sec;
	int iTimeS4 =  m_autoBit.venc[0].time_seg[3].begin_sec;

	int iTimeE1 = m_autoBit.venc[0].time_seg[0].end_sec;
	int iTimeE2 = m_autoBit.venc[0].time_seg[1].end_sec;
	int iTimeE3 = m_autoBit.venc[0].time_seg[2].end_sec;
	int iTimeE4 = m_autoBit.venc[0].time_seg[3].end_sec;

	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();																	// 小时		//分钟			//秒
	COleDateTime startTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS1/3600, (iTimeS1%3600)/60, (iTimeS1%3600)%60);
	COleDateTime startTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS2/3600, (iTimeS2%3600)/60, (iTimeS2%3600)%60);
	COleDateTime startTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS3/3600, (iTimeS3%3600)/60, (iTimeS3%3600)%60);
	COleDateTime startTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS4/3600, (iTimeS4%3600)/60, (iTimeS4%3600)%60);
	m_StreamStartTime1.SetTime(startTime1);
	m_StreamStartTime2.SetTime(startTime2);
	m_StreamStartTime3.SetTime(startTime3);
	m_StreamStartTime4.SetTime(startTime4);

	COleDateTime endTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE1/3600, (iTimeE1%3600)/60, (iTimeE1%3600)%60);
	COleDateTime endTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE2/3600, (iTimeE2%3600)/60, (iTimeE2%3600)%60);
	COleDateTime endTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE3/3600, (iTimeE3%3600)/60, (iTimeE3%3600)%60);
	COleDateTime endTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE4/3600, (iTimeE4%3600)/60, (iTimeE4%3600)%60);
	m_StreamEndTime1.SetTime(endTime1);
	m_StreamEndtime2.SetTime(endTime2);
	m_StreamEndTime3.SetTime(endTime3);
	m_StreamEndTime4.SetTime(endTime4);

	return 0;
}


void CChannelStream::OnBnClickedCheckStart1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_StreamStart1.GetCheck() == 1)
	{
		m_StreamStartTime1.EnableWindow(TRUE);
		m_StreamEndTime1.EnableWindow(TRUE);
	}
	else
	{
		m_StreamStartTime1.EnableWindow(FALSE);
		m_StreamEndTime1.EnableWindow(FALSE);
	}
}

void CChannelStream::OnBnClickedCheckStart2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_StreamStart2.GetCheck() == 1)
	{
		m_StreamStartTime2.EnableWindow(TRUE);
		m_StreamEndtime2.EnableWindow(TRUE);
	}
	else
	{
		m_StreamStartTime2.EnableWindow(FALSE);
		m_StreamEndtime2.EnableWindow(FALSE);
	}
}

void CChannelStream::OnBnClickedCheckStart3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_StreamStart3.GetCheck() == 1)
	{
		m_StreamStartTime3.EnableWindow(TRUE);
		m_StreamEndTime3.EnableWindow(TRUE);
	}
	else
	{
		m_StreamStartTime3.EnableWindow(FALSE);
		m_StreamEndTime3.EnableWindow(FALSE);
	}
}

void CChannelStream::OnBnClickedCheckStart4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_StreamStart4.GetCheck() == 1)
	{
		m_StreamStartTime4.EnableWindow(TRUE);
		m_StreamEndTime4.EnableWindow(TRUE);
	}
	else
	{
		m_StreamStartTime4.EnableWindow(FALSE);
		m_StreamEndTime4.EnableWindow(FALSE);
	}
}

void CChannelStream::OnCbnSelchangeComboReplacetype()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_ReplaceType.GetCurSel() == 0)
	{
		m_StreamType.ResetContent();
		m_StreamType.AddString(_T("在时间段内切换成低码率"));
		m_StreamType.AddString(_T("在时间段内切换为高码率"));
	}
	else if(m_ReplaceType.GetCurSel() == 1)
	{
		m_StreamType.ResetContent();
		m_StreamType.AddString(_T("非红外模式设置为高码率"));
		m_StreamType.AddString(_T("非红外模式设置为低码率"));
	}
}

void CChannelStream::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

