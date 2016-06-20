// SetTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "SetTimeDlg.h"
#include "Pub_Data.h"

// CSetTimeDlg 对话框


IMPLEMENT_DYNAMIC(CSetTimeDlg, CDialog)

CSetTimeDlg::CSetTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetTimeDlg::IDD, pParent)
{

}

CSetTimeDlg::~CSetTimeDlg()
{

	DestroyWindow();
}

void CSetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_IP, m_eIp);
	DDX_Control(pDX, IDC_EDIT_TIME, m_eTime);
	DDX_Control(pDX, IDC_CHECK_NTP, m_StartNtp);
	DDX_Control(pDX, IDC_CHECKSUMMER, m_StartSummer);
	DDX_Control(pDX, IDC_EDIT_TIMEAREA, m_eTimeArea);

	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE, m_DeviceDate);
	DDX_Control(pDX, IDC_COMBO_STARTHOUR, m_DeviceHour);
	DDX_Control(pDX, IDC_COMBO_STARTMINUTE, m_DeviceMinute);
	DDX_Control(pDX, IDC_COMBO_STRATSECOND, m_DeviceSecond);
}


BEGIN_MESSAGE_MAP(CSetTimeDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSetTimeDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CSetTimeDlg::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTONGETTIME, &CSetTimeDlg::OnBnClickedButtongettime)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_NTP, &CSetTimeDlg::OnBnClickedCheckNtp)
END_MESSAGE_MAP()


// CSetTimeDlg 消息处理程序

BOOL CSetTimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(int i = 0; i< 60; i++)
	{
		CString strH = _T("");
		strH.Format(_T("%d"), i);
		m_DeviceMinute.AddString(strH);
		m_DeviceSecond.AddString(strH);
	}

	for(int i =0; i< 24; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		m_DeviceHour.AddString(str);
	}

	
	return TRUE;
}

void CSetTimeDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString strServer(_T(""));
	m_eIp.GetWindowText(strServer);

	CString strTimeinter(_T(""));
	m_eTime.GetWindowText(strTimeinter);
	int intervalTime = _ttoi(strTimeinter);
	m_ntpInfo.time_interval = intervalTime;
	m_ntpInfo.ntp_enable = m_StartNtp.GetCheck();
	m_ntpInfo.dst_enable = m_StartSummer.GetCheck();
	memset(m_ntpInfo.ntp_server_ip,'\0',sizeof(m_ntpInfo.ntp_server_ip));
	memcpy(m_ntpInfo.ntp_server_ip,strServer.GetBuffer(0), strServer.GetLength() );
	strServer.ReleaseBuffer();


	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DEVICE_NTP_INFO, (char *)&m_ntpInfo, sizeof(m_ntpInfo), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}

	COleDateTime cData;
	m_DeviceDate.GetTime(cData);
	m_deviceTime.time.year = cData.GetYear() - 1900;
	m_deviceTime.time.month = cData.GetMonth();
	m_deviceTime.time.date = cData.GetDay();
	m_deviceTime.time.hour = m_DeviceHour.GetCurSel();
	m_deviceTime.time.minute = m_DeviceMinute.GetCurSel();
	m_deviceTime.time.second = m_DeviceSecond.GetCurSel();
	m_deviceTime.time.weekday = cData.GetDayOfWeek();

	if(m_ntpInfo.ntp_enable == 1)
	{
		return;    //启用NTP 或者 夏令时 就不再设置时间
	}


	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_SET_DEVICE_TIME, (char *)&m_deviceTime, sizeof(m_deviceTime), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}


	return;
}

void CSetTimeDlg::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DEVICE_NTP_INFO, (char *)&m_ntpInfo, sizeof(m_ntpInfo),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_SET_DEVICE_TIME, (char *)&m_deviceTime, sizeof(m_deviceTime),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	ReFreshNtp();
	ReFreshTime();

}


int CSetTimeDlg::ReFreshNtp()
{
	
	CString strIp(m_ntpInfo.ntp_server_ip);
	m_eIp.SetWindowText(strIp);
	
	int interTime = m_ntpInfo.time_interval;
	CString strInterTime(_T(""));
	strInterTime.Format(_T("%d"), interTime);
	m_eTime.SetWindowText(strInterTime);


	int iStartNtp = m_ntpInfo.ntp_enable;
	if(iStartNtp == 1)
	{
		m_StartSummer.EnableWindow(TRUE);
	}
	else
	{
		m_StartSummer.EnableWindow(FALSE);
	}
	int iStartSummer = m_ntpInfo.dst_enable;
	m_StartNtp.SetCheck(iStartNtp);
	m_StartSummer.SetCheck(iStartSummer);

	return 0;
}

int CSetTimeDlg::ReFreshTime()
{
	m_DeviceHour.SetCurSel(m_deviceTime.time.hour);
	m_DeviceMinute.SetCurSel(m_deviceTime.time.minute);
	m_DeviceSecond.SetCurSel(m_deviceTime.time.second);

	if(m_deviceTime.time.month <= 0 || m_deviceTime.time.date <= 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return  -1;
	}

	COleDateTime cData(m_deviceTime.time.year+1900,m_deviceTime.time.month,m_deviceTime.time.date, 8, 0, 0);
	m_DeviceDate.SetTime(cData);

	
	return 0;
}
void CSetTimeDlg::OnBnClickedButtongettime()
{
	// TODO: 在此添加控件通知处理程序代码
	COleDateTime cTime = COleDateTime::GetCurrentTime();

	int year = cTime.GetYear();
	int month = cTime.GetMonth();
	int day = cTime.GetDay();
	COleDateTime deviceData(cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 0, 0, 0);
	m_DeviceDate.SetTime(deviceData);
	m_DeviceHour.SetCurSel(cTime.GetHour());
	m_DeviceMinute.SetCurSel(cTime.GetMinute());
	m_DeviceSecond.SetCurSel(cTime.GetSecond());
}

void CSetTimeDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CSetTimeDlg::OnBnClickedCheckNtp()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_StartNtp.GetCheck() == 1)
	{
		m_StartSummer.EnableWindow(TRUE);
	}
	else
	{
		m_StartSummer.EnableWindow(FALSE);
	}
}
