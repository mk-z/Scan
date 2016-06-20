// VideoPlayBack.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "VideoPlayBack.h"
#include "Pub_Data.h"
#include "direct.h"     //mkdir 头文件
#include <cstdlib>
#include <math.h>

// CVideoPlayBack 对话框

int gNVRChn = 0; 

int gChannel = -1;

IMPLEMENT_DYNAMIC(CVideoPlayBack, CDialog)

CVideoPlayBack::CVideoPlayBack(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoPlayBack::IDD, pParent)
{
	for(int i = 0; i < REC_TYPE_MAX_COUNT; i++)
	{
		m_lRecFileSize[i] = 0;
		m_RecType[i]	  = 0;	
	}
	m_iListIndex = -1;
	m_bIsPasue = FALSE;
	m_HIPlayerPort = -1;
	m_lFrameCount = 0;
	m_iBeginNode = 0;
	m_iEndNode = 23;
	m_iSsid = -1;
	m_lstartTime = -1;
	m_lEndTime = -1;

	m_bClosePlayLocal = FALSE;
	m_bCloseDevice = FALSE;

	m_PlayFastTime = 1000;
	m_PlaySlowTime = 1000;
	m_SleepTime = 1000;
	m_nDownLoadFlag = -1;
	m_startPlayTime = 0;
	m_lRecHandle = NULL;
	m_downloadHandle = NULL;
	m_lDownLoad	= NULL;
	m_lDownLoadStartTime = -1;
	m_lDownLoadTotalTime = -1;
	m_nSpeed = 0;

}

CVideoPlayBack::~CVideoPlayBack()
{
	int iRet = -1;
	if(m_lRecHandle)
	{
		AVP_Stop(gChannel);
		AVP_ReleasePort(gChannel);
		JNetRecClose(m_lRecHandle);
		m_lRecHandle = NULL;
		gChannel = -1;
		Invalidate();
	}

	if(m_iDecPort >= 0)
	{
		AVP_DelPlayWnd(m_iDecPort, m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->GetSafeHwnd());
		m_iDecPort = -1;
		Invalidate();
	}
	if(m_HIPlayerPort >= 0)
	{
		AVP_DelPlayWnd(m_HIPlayerPort, m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->GetSafeHwnd());
		AVP_Stop(m_HIPlayerPort);
		AVP_ReleasePort(m_HIPlayerPort);
		m_HIPlayerPort = -1;
		Invalidate();
	}
	DestroyWindow();
}

void CVideoPlayBack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIDEOPLAYBACK, m_VideoPlayBack);
	DDX_Control(pDX, IDC_COMBOX_RECORDTYPE, m_RecordYype);
	DDX_Control(pDX, IDC_COMBO_STARTHOUR, m_StartHour);
	DDX_Control(pDX, IDC_COMBO_STARTMINUTE, m_StartMinute);
	DDX_Control(pDX, IDC_COMBO_STRATSECOND, m_StartSecond);
	DDX_Control(pDX, IDC_COMBO_ENDHOUR, m_EndHour);
	DDX_Control(pDX, IDC_EIDT_ENDMINUTE, m_EndMinute);
	DDX_Control(pDX, IDC_COMBO_ENDSECOND, m_EndSecond);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_StartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_EndTime);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_progressDownLoad);
	DDX_Control(pDX, IDC_COMBOX_DEVICE, m_ComDevice);
}


BEGIN_MESSAGE_MAP(CVideoPlayBack, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SERACHVIDEO, &CVideoPlayBack::OnBnClickedButtonSerachvideo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VIDEOPLAYBACK, &CVideoPlayBack::OnNMDblclkListVideoplayback)
	ON_NOTIFY(NM_CLICK, IDC_LIST_VIDEOPLAYBACK, &CVideoPlayBack::OnNMClickListVideoplayback)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CVideoPlayBack::OnBnClickedButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_PLAYFILE, &CVideoPlayBack::OnBnClickedButtonPlayfile)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CVideoPlayBack::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CVideoPlayBack::OnBnClickedButtonStop)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBOX_DEVICE, &CVideoPlayBack::OnCbnSelchangeComboxDevice)
	ON_BN_CLICKED(IDC_BUTTON_FLASHDEVICE, &CVideoPlayBack::OnBnClickedButtonFlashdevice)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_PLAYSLOW, &CVideoPlayBack::OnBnClickedButtonPlayslow)
	ON_BN_CLICKED(IDC_BUTTON_PLAYFAST, &CVideoPlayBack::OnBnClickedButtonPlayfast)
END_MESSAGE_MAP()


// CVideoPlayBack 消息处理程序
BOOL CVideoPlayBack::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_VideoPlayBack.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_VideoPlayBack.InsertColumn(0 , _T("ID"), 2, 50, -1);
		m_VideoPlayBack.InsertColumn(1 , _T("类型"), 2, 100, -1);
		m_VideoPlayBack.InsertColumn(2 , _T("开始时间"), 2, 150, -1);
		m_VideoPlayBack.InsertColumn(3 , _T("结束时间"), 2, 150, -1);
		m_VideoPlayBack.InsertColumn(4 , _T("录像时长(s)"), 2, 100, -1);
		m_VideoPlayBack.InsertColumn(5 , _T("录像大小(MB)"), 2, 90, -1);

		m_RecordYype.AddString(_T("定时录像"));
		m_RecordYype.AddString(_T("报警录像"));
		m_RecordYype.AddString(_T("移动报警"));
		m_RecordYype.AddString(_T("手动"));
		m_RecordYype.AddString(_T("丢失报警"));
		m_RecordYype.AddString(_T("遮挡报警"));
		m_RecordYype.AddString(_T("网络故障录像"));
		m_RecordYype.AddString(_T("人体红外检测告警录像"));
		m_RecordYype.AddString(_T("全部"));
	}
	else
	{
		m_VideoPlayBack.InsertColumn(0 , _T("ID"), 2, 50, -1);
		m_VideoPlayBack.InsertColumn(1 , _T("Type"), 2, 100, -1);
		m_VideoPlayBack.InsertColumn(2 , _T("StartTime"), 2, 150, -1);
		m_VideoPlayBack.InsertColumn(3 , _T("EndTime"), 2, 150, -1);
		m_VideoPlayBack.InsertColumn(4 , _T("Video Length(s)"), 2, 100, -1);
		m_VideoPlayBack.InsertColumn(5 , _T("Video Size(MB)"), 2, 90, -1);

		m_RecordYype.AddString(_T("Time"));
		m_RecordYype.AddString(_T("Alarm"));
		m_RecordYype.AddString(_T("Move Alarm"));
		m_RecordYype.AddString(_T("Manual"));
		m_RecordYype.AddString(_T("Lost Alarm"));
		m_RecordYype.AddString(_T("Hide Alarm"));
		m_RecordYype.AddString(_T("NetFault"));
		m_RecordYype.AddString(_T("PIR_RECODE"));
		m_RecordYype.AddString(_T("All"));
	}
	
	m_RecordYype.SetCurSel(0);

	for(int i= 0; i< 60; i++)
	{
		CString strText = _T("");
		strText.Format(_T("%d"), i);
		m_StartMinute.AddString(strText);
		m_StartSecond.AddString(strText);

		m_EndMinute.AddString(strText);
		m_EndSecond.AddString(strText);
	}

	COleDateTime LimitData(1970,1,1,0,0,0);
	m_StartTime.SetRange(&LimitData, NULL);
	m_EndTime.SetRange(&LimitData, NULL);


	for(int i =0; i< 24; i++)
	{
		CString strText = _T("");
		strText.Format(_T("%d"), i);
		m_StartHour.AddString(strText);
		m_EndHour.AddString(strText);
	}
	m_StartHour.SetCurSel(0);
	m_StartMinute.SetCurSel(0);
	m_StartSecond.SetCurSel(0);

	m_EndHour.SetCurSel(23);
	m_EndMinute.SetCurSel(59);
	m_EndSecond.SetCurSel(59);

	m_progressDownLoad.ShowWindow(SW_HIDE);
	m_iDecPort = -1;

	m_recodeScreenDlg.Create(IDD_DIALOG_RECODESCREEN, this);
	m_recodeScreenDlg.MoveWindow(30,270,650,255, TRUE);
	m_recodeScreenDlg.ShowWindow(SW_SHOW);

	CRect cRect;
	m_recodeScreenDlg.GetClientRect(&cRect);
	m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->MoveWindow(0,0,cRect.Width(), cRect.Height() - 25, TRUE);
	m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->ShowWindow(TRUE);

	m_recodeScreenDlg.GetDlgItem(IDC_SLIDER_PLAYPROGRESS)->MoveWindow(50, cRect.Height()-18, cRect.Width() - 50,20, TRUE);
	m_recodeScreenDlg.GetDlgItem(IDC_SLIDER_PLAYPROGRESS)->ShowWindow(SW_SHOW);

	m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->MoveWindow(0, cRect.Height()-15, 50, 20, TRUE);
	m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->ShowWindow(SW_SHOW);

	m_recodeScreenDlg.GetDlgItem(IDC_STATIC_GROPU_PROGRESS)->MoveWindow(0, cRect.Height()-25, cRect.Width(),25, TRUE);
	m_recodeScreenDlg.GetDlgItem(IDC_STATIC_GROPU_PROGRESS)->ShowWindow(SW_SHOW);


	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_strPasueS = _T("暂停");
		m_strPasueE = _T("播放");

		m_strStop = _T("停止");
	}
	else
	{
		m_strPasueS = _T("Pasue");
		m_strPasueE = _T("Play");

		m_strStop = _T("Stop");
	}

	GetDlgItem(IDC_STATIC_SPEED)->SetWindowText("1 X");
	return TRUE;
}

void CVideoPlayBack::OnBnClickedButtonSerachvideo()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_PubData.g_iPlayBack < 0)
	{
		//AfxMessageBox(_T("没有登陆设备"));
		return ;
	}
	int recType;
	int iIndex = m_RecordYype.GetCurSel();
	switch (iIndex)
	{
		case 0:
			recType = TIMER_RECODE;
			break;
		case 1:
			recType = ALARM_RECODE;
			break;
		case 2:
			recType = MOVE_RECODE;
			break;
		case 3:
			recType = MANUAL_RECODE;
			break;
		case 4:
			recType = LOST_RECODE;
			break;
		case 5:
			recType = HIDE_RECODE;
			break;
		case 6:
			recType = NET_FAULT_RECODE;
			break;
		case 7:
			recType = PIR_RECODE;
			break;
		case 8:
			recType = ALL_RECODE;
			break;
	}
//查询录像参数
	ZeroMemory(&m_storeLog, sizeof(JStoreLog));
	m_storeLog.rec_type = recType;
	m_SerachRecodeByType = recType;
	m_storeLog.beg_node = m_iBeginNode;
	m_storeLog.end_node = m_iEndNode;
	m_storeLog.sess_id = m_iSsid;

	if(m_iBeginNode == 0)
	{
		m_VideoPlayBack.DeleteAllItems();
	}
	COleDateTime timeStart;
	m_StartTime.GetTime(timeStart);
	m_storeLog.beg_time.year =  timeStart.GetYear() - 1900;
	m_storeLog.beg_time.month = timeStart.GetMonth();
	m_storeLog.beg_time.date = timeStart.GetDay();
	m_storeLog.beg_time.weekday = timeStart.GetDayOfWeek();
	m_storeLog.beg_time.hour = m_StartHour.GetCurSel();
	m_storeLog.beg_time.minute = m_StartMinute.GetCurSel();
	m_storeLog.beg_time.second = m_StartSecond.GetCurSel();
	
	COleDateTime timeEnd;
	m_EndTime.GetTime(timeEnd);
	m_storeLog.end_time.year =  timeEnd.GetYear() - 1900;
	m_storeLog.end_time.month = timeEnd.GetMonth();
	m_storeLog.end_time.date = timeEnd.GetDay();
	m_storeLog.end_time.weekday = timeEnd.GetDayOfWeek();
	m_storeLog.end_time.hour = m_EndHour.GetCurSel();
	m_storeLog.end_time.minute = m_EndMinute.GetCurSel();
	m_storeLog.end_time.second = m_EndSecond.GetCurSel();


	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iPlayBack],gNVRChn,PARAM_STORE_LOG, (char *)&m_storeLog, sizeof(m_storeLog),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox("查询失败");
		return;
	}

	ReFreshVideoList();
}

void CVideoPlayBack::ReFreshVideoList()
{
	if(g_PubData.g_iLanguageFlag == 0)
	{
		AddToList();
	}
	else
	{
		AddToListEnglish();
	}
	
	if(m_iEndNode < (int)m_storeLog.total_count) //每次最多只能取24条 ，分批取
	{
		m_iBeginNode += 24;
		m_iEndNode += 24;
		m_iSsid = m_storeLog.sess_id;
		OnBnClickedButtonSerachvideo();
	}
	else
	{
		m_iBeginNode = 0;
		m_iEndNode = 23;
		m_iSsid = -1;
	}
	
	return ;
}
void CVideoPlayBack::AddToList()
{
	int j = m_iBeginNode;

	
	for(int i = 0; i< (int)m_storeLog.node_count; i++)
	{
		CString strId(_T(""));
		strId.Format(_T("%d"),j+1);

		CString strType = _T("");
		if(m_SerachRecodeByType == ALL_RECODE)
		{
			if(m_storeLog.store[i].rec_type & TIMER_RECODE)
			{
				strType += _T(",定时录像");
			}
			if(m_storeLog.store[i].rec_type & ALARM_RECODE)
			{
				strType += _T(",报警录像");
			}
			if(m_storeLog.store[i].rec_type & MOVE_RECODE)
			{
				strType += _T(",移动报警");
			}
			if(m_storeLog.store[i].rec_type & MANUAL_RECODE)
			{
				strType += _T(",手动");
			}
			if(m_storeLog.store[i].rec_type & LOST_RECODE)
			{
				strType += _T(",丢失报警");
			}
			if(m_storeLog.store[i].rec_type & HIDE_RECODE)
			{
				strType += _T(",遮挡报警");
			}
			if(m_storeLog.store[i].rec_type & NET_FAULT_RECODE)
			{
				strType += _T(",网络故障录像");
			}
			if(m_storeLog.store[i].rec_type & PIR_RECODE)
			{
				strType += _T(",人体红外检测告警录像");
			}
			strType = strType.Right(strType.GetLength() - 1 );
		}
		else
		{
			if(m_storeLog.store[i].rec_type & TIMER_RECODE)
			{
				strType = _T("定时录像");
			}
			if(m_storeLog.store[i].rec_type & ALARM_RECODE)
			{
				strType = _T("报警录像");
			}
			if(m_storeLog.store[i].rec_type & MOVE_RECODE)
			{
				strType = _T("移动报警");
			}
			if(m_storeLog.store[i].rec_type & MANUAL_RECODE)
			{
				strType = _T("手动");
			}
			if(m_storeLog.store[i].rec_type & LOST_RECODE)
			{
				strType = _T("丢失报警");
			}
			if(m_storeLog.store[i].rec_type & HIDE_RECODE)
			{
				strType = _T("遮挡报警");
			}
			if(m_storeLog.store[i].rec_type & NET_FAULT_RECODE)
			{
				strType = _T("网络故障录像");
			}
			if(m_storeLog.store[i].rec_type & PIR_RECODE)
			{
				strType = _T("人体红外检测告警录像");
			}
		}


		CString strStartTime = _T("");
		CString strEndTime =_T("");
		CString StartTime = _T("");
		CString EndTime = _T("");
			
		strStartTime.Format(_T("%d-%02d-%02d-%02d:%02d:%02d"),m_storeLog.store[i].beg_time.year+1900,m_storeLog.store[i].beg_time.month,
			m_storeLog.store[i].beg_time.date, m_storeLog.store[i].beg_time.hour ,
			m_storeLog.store[i].beg_time.minute, m_storeLog.store[i].beg_time.second);

		strEndTime.Format(_T("%d-%02d-%02d-%02d:%02d:%02d"),m_storeLog.store[i].end_time.year+1900,m_storeLog.store[i].end_time.month,
			m_storeLog.store[i].end_time.date, m_storeLog.store[i].end_time.hour ,
			m_storeLog.store[i].end_time.minute, m_storeLog.store[i].end_time.second);
		//计算时间段的差
		COleDateTime  tStartDateTime;
		COleDateTime  tEndDateTime;
		tStartDateTime.SetDateTime(m_storeLog.store[i].beg_time.year+1900,m_storeLog.store[i].beg_time.month,
			m_storeLog.store[i].beg_time.date, m_storeLog.store[i].beg_time.hour ,
			m_storeLog.store[i].beg_time.minute, m_storeLog.store[i].beg_time.second);
		tEndDateTime.SetDateTime(m_storeLog.store[i].end_time.year+1900,m_storeLog.store[i].end_time.month,
			m_storeLog.store[i].end_time.date, m_storeLog.store[i].end_time.hour ,
			m_storeLog.store[i].end_time.minute, m_storeLog.store[i].end_time.second);

		m_RecType[j]	  = m_storeLog.store[i].rec_type;
		m_lRecFileSize[j] = m_storeLog.store[i].file_size;  //保存录像文件的大小  下载时计算进度


		COleDateTimeSpan tMinute = tEndDateTime - tStartDateTime;  // 计算两个日期时间的差值
		DOUBLE dMinute = tMinute.GetTotalSeconds();
		CString strFileTimes = _T("");
		strFileTimes.Format(_T("%ld"), (LONG)dMinute);

		CString strFileSize = _T("");//录像大小
		strFileSize.Format(_T("%d"), m_storeLog.store[i].file_size/(1024*1024));

		m_VideoPlayBack.InsertItem(j,strId );
		m_VideoPlayBack.SetItemText(j, 1, strType);
		m_VideoPlayBack.SetItemText(j, 2, strStartTime);
		m_VideoPlayBack.SetItemText(j, 3, strEndTime);
		m_VideoPlayBack.SetItemText(j, 4, strFileTimes);
		m_VideoPlayBack.SetItemText(j, 5, strFileSize);
		
		j++;
	}
}



void CVideoPlayBack::AddToListEnglish()
{
	int j = m_iBeginNode;

	
	for(int i = 0; i< (int)m_storeLog.node_count; i++)
	{
		CString strId(_T(""));
		strId.Format(_T("%d"),j+1);

		CString strType = _T("");
		if(m_SerachRecodeByType == ALL_RECODE)
		{
			if(m_storeLog.store[i].rec_type & TIMER_RECODE)
			{
				strType += _T(",TIMER_RECODE");
			}
			if(m_storeLog.store[i].rec_type & ALARM_RECODE)
			{
				strType += _T(",ALARM_RECODE");
			}
			if(m_storeLog.store[i].rec_type & MOVE_RECODE)
			{
				strType += _T(",MOVE_RECODE");
			}
			if(m_storeLog.store[i].rec_type & MANUAL_RECODE)
			{
				strType += _T(",MANUAL_RECODE");
			}
			if(m_storeLog.store[i].rec_type & LOST_RECODE)
			{
				strType += _T(",LOST_RECODE");
			}
			if(m_storeLog.store[i].rec_type & HIDE_RECODE)
			{
				strType += _T(",HIDE_RECODE");
			}
			if(m_storeLog.store[i].rec_type & NET_FAULT_RECODE)
			{
				strType += _T(",NET_FAULT_RECODE");
			}
			if(m_storeLog.store[i].rec_type & PIR_RECODE)
			{
				strType += _T(",PIR_RECODE");
			}
			strType = strType.Right(strType.GetLength() - 1 );
		}
		else
		{
			if(m_storeLog.store[i].rec_type & TIMER_RECODE)
			{
				strType = _T("TIMER_RECODE");
			}
			if(m_storeLog.store[i].rec_type & ALARM_RECODE)
			{
				strType = _T("ALARM_RECODE");
			}
			if(m_storeLog.store[i].rec_type & MOVE_RECODE)
			{
				strType = _T("MOVE_RECODE");
			}
			if(m_storeLog.store[i].rec_type & MANUAL_RECODE)
			{
				strType = _T("MANUAL_RECODE");
			}
			if(m_storeLog.store[i].rec_type & LOST_RECODE)
			{
				strType = _T("LOST_RECODE");
			}
			if(m_storeLog.store[i].rec_type & HIDE_RECODE)
			{
				strType = _T("HIDE_RECODE");
			}
			if(m_storeLog.store[i].rec_type & NET_FAULT_RECODE)
			{
				strType = _T("NET_FAULT_RECODE");
			}
			if(m_storeLog.store[i].rec_type & PIR_RECODE)
			{
				strType += _T("PIR_RECODE");
			}
		}
	
	


		CString strStartTime = _T("");
		CString strEndTime =_T("");
		CString StartTime = _T("");
		CString EndTime = _T("");

		strStartTime.Format(_T("%d-%02d-%02d-%02d:%02d:%02d"),m_storeLog.store[i].beg_time.year+1900,m_storeLog.store[i].beg_time.month,
			m_storeLog.store[i].beg_time.date, m_storeLog.store[i].beg_time.hour ,
			m_storeLog.store[i].beg_time.minute, m_storeLog.store[i].beg_time.second);

		strEndTime.Format(_T("%d-%02d-%02d-%02d:%02d:%02d"),m_storeLog.store[i].end_time.year+1900,m_storeLog.store[i].end_time.month,
			m_storeLog.store[i].end_time.date, m_storeLog.store[i].end_time.hour ,
			m_storeLog.store[i].end_time.minute, m_storeLog.store[i].end_time.second);
		//计算时间段的差
		COleDateTime  tStartDateTime;
		COleDateTime  tEndDateTime;
		tStartDateTime.SetDateTime(m_storeLog.store[i].beg_time.year+1900,m_storeLog.store[i].beg_time.month,
			m_storeLog.store[i].beg_time.date, m_storeLog.store[i].beg_time.hour ,
			m_storeLog.store[i].beg_time.minute, m_storeLog.store[i].beg_time.second);
		tEndDateTime.SetDateTime(m_storeLog.store[i].end_time.year+1900,m_storeLog.store[i].end_time.month,
			m_storeLog.store[i].end_time.date, m_storeLog.store[i].end_time.hour ,
			m_storeLog.store[i].end_time.minute, m_storeLog.store[i].end_time.second);


		m_lRecFileSize[j] = m_storeLog.store[i].file_size;  //保存录像文件的大小  下载时计算进度


		COleDateTimeSpan tMinute = tEndDateTime - tStartDateTime;  // 计算两个日期时间的差值
		DOUBLE dMinute = tMinute.GetTotalSeconds();
		CString strFileTimes = _T("");
		strFileTimes.Format(_T("%ld"), (LONG)dMinute);

		CString strFileSize = _T("");//录像大小
		strFileSize.Format(_T("%d"), m_storeLog.store[i].file_size/(1024*1024));

		m_VideoPlayBack.InsertItem(j,strId );
		m_VideoPlayBack.SetItemText(j, 1, strType);
		m_VideoPlayBack.SetItemText(j, 2, strStartTime);
		m_VideoPlayBack.SetItemText(j, 3, strEndTime);
		m_VideoPlayBack.SetItemText(j, 4, strFileTimes);
		m_VideoPlayBack.SetItemText(j, 5, strFileSize);
		j++;
	}
	}

int CVideoPlayBack::GetRecodeType(CString str)
{
	int iRet = -1;
	
	if(str == _T("定时录像"))
	{
		iRet = TIMER_RECODE;
	}
	else if(str == _T("报警录像"))
	{
		iRet = ALARM_RECODE;
	}
	else if(str == _T("移动报警"))
	{
		iRet = MOVE_RECODE;
	}
	else if(str == _T("手动"))
	{
		iRet = MANUAL_RECODE;
	}
	else if(str == _T("丢失报警"))
	{
		iRet = LOST_RECODE;
	}
	else if(str == _T("遮挡报警"))
	{
		iRet = HIDE_RECODE;
	}
	else if(str == _T("网络故障录像"))
	{
		iRet = NET_FAULT_RECODE;
	}
	else if(str == _T("人体红外检测告警录像"))
	{
		iRet = PIR_RECODE;
	}
	
	return iRet;
}
void CVideoPlayBack::OnNMDblclkListVideoplayback(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(m_strPasueS);
// 	m_bIsPasue = FALSE;


 	int iRet = -1;
// 	if(m_lRecHandle != NULL)
// 	{
// 		AVP_Stop(gChannel);
// 		AVP_ReleasePort(gChannel);
// 		JNetRecClose(m_lRecHandle);
// 		m_lRecHandle = NULL;
// 	}

	OnBnClickedButtonStop();

	int index = pNMItemActivate->iItem;
	if(index  < 0)
	{
		//AfxMessageBox(_T("请选择要播放的录像"));
		return ;
	}
	
	CString strStartTime = _T("");
	CString strEndTime = _T("");
	CString str1 = m_VideoPlayBack.GetItemText(index, 2);
	CString str2 = m_VideoPlayBack.GetItemText(index, 3);
	CString strType = m_VideoPlayBack.GetItemText(index, 1);

	m_Filetimes = _ttoi(m_VideoPlayBack.GetItemText(index, 4));  //录像时长
	m_PlayFiletime = 0;


	m_recodeScreenDlg.m_PlayProgress.SetRange(0, m_Filetimes);

	int iRec_type = GetRecodeType(strType);
	strStartTime = getDate(str1);
	strEndTime = getDate(str2);

	gChannel = AVP_GetFreePort();
	

	m_nSpeed = 0;
	m_lRecHandle = JNetRecOpen4Time(g_PubData.g_vLoginHandle[g_PubData.g_iPlayBack], "", gNVRChn, 0, strStartTime.GetBuffer(0), strEndTime.GetBuffer(0) , m_RecType[index],  1, JRecStream, this,  m_lRecHandle);
	if(m_lRecHandle > 0)
	{
		Sleep(1000);
		JNetRecCtrl(m_lRecHandle, JNET_PB_CTRL_START, NULL);
	}

	strStartTime.ReleaseBuffer();
	strEndTime.ReleaseBuffer();
	
	
	iRet = -1;
	// 设置显示窗口

	
	iRet = -1;
	AVP_SetPlayPriority(gChannel, AVPPlaySmooth);
	AVP_SetDataProtocol(gChannel,AVP_PROTOCOL_JPF);

	//AVP_EnableYUVDraw(gChannel,TRUE);
	// 设置通道使用的解码器
	iRet = AVP_SetCoder(gChannel,AVP_CODER_JXJ);
	if ( iRet!=AVPErrSuccess )
	{
		AfxMessageBox(_T("AVP_SetCoder  error!"));
		return;
	}
	// 设置显示窗口
	AVP_AddPlayWnd(gChannel,NULL, m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->GetSafeHwnd(),NULL,NULL);

	// 开启解码
	AVP_Play(gChannel);
	

	m_PlayFiletime = 0;
	m_recodeScreenDlg.m_PlayProgress.SetRange(0, m_Filetimes);

	m_PlayFastTime = 1000;
	m_PlaySlowTime = 1000;
	m_SleepTime = 1000;
	if(!m_bClosePlayLocal)
	{
		HANDLE hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)PlayThreadFun,this,0,0);
		CloseHandle(hThread);
	}

	*pResult = 0;

}

int CVideoPlayBack::JRecStream(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam)
{
	CVideoPlayBack *pDlg = (CVideoPlayBack *)pUserParam;
	j_frame_t *pFrame = (j_frame_t *)pBuff;
	//TRACE("--------%d    %d\r\n",  pFrame->timestamp_sec, pFrame->timestamp_usec);
	AVP_PutFrame(gChannel,pBuff);
	pDlg->m_PlayFiletime = (int)pFrame->timestamp_sec;
	return 0;
}


DWORD CVideoPlayBack::PlayDeviceThreadFun(LPVOID lpThreadParameter)
{
	CVideoPlayBack *pDlg = (CVideoPlayBack *)lpThreadParameter;
	while(1)
	{
		pDlg->m_bCloseDevice = TRUE;
		if(gChannel < 0 || !::IsWindow(pDlg->m_hWnd))
		{
			pDlg->m_bCloseDevice = FALSE;
			return 0;
		}
		Sleep(1000);

		pDlg->m_PlayFiletime ++;
		CString strText = _T("");
		strText.Format(_T("%d/%d"), pDlg->m_PlayFiletime, pDlg->m_Filetimes);
		if(gChannel < 0 || !::IsWindow(pDlg->m_hWnd))
		{
			pDlg->m_bCloseDevice = FALSE;
			return 0;
		}
		pDlg->m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->SetWindowText(strText);
		pDlg->m_recodeScreenDlg.m_PlayProgress.SetPos(pDlg->m_PlayFiletime);
		if(pDlg->m_PlayFiletime == pDlg->m_Filetimes)
		{
			pDlg->m_recodeScreenDlg.m_PlayProgress.SetPos(0);
			pDlg->m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->SetWindowText(_T("00/00"));
			pDlg->Invalidate();
			pDlg->m_bCloseDevice = FALSE;
			return 0;
		}

	}

	pDlg->m_bCloseDevice = FALSE;
	return 0;
}



void CVideoPlayBack::OnNMClickListVideoplayback(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_iListIndex = pNMItemActivate->iItem;
	g_PubData.m_iVideoIndex = m_iListIndex;
	*pResult = 0;
}

CString CVideoPlayBack::getDate(CString str)
{
	CString strStartYear = _T("");
	CString strStartMonth = _T("");
	CString strStartDay = _T("");
	CString strStartHour = _T("");
	CString strStartMinute = _T("");
	CString strStartSecond = _T("");

	strStartYear = str.Mid(0,4);
	strStartMonth = str.Mid(5,2);
	strStartDay = str.Mid(8,2);
	strStartHour = str.Mid(11,2);
	strStartMinute = str.Mid(14,2);
	strStartSecond = str.Mid(17,2);

	CString strStartTime = _T("");
	strStartTime = strStartYear + strStartMonth + strStartDay + strStartHour + strStartMinute + strStartSecond;
	return strStartTime;
}


void CVideoPlayBack::OnBnClickedButtonDownload()
{
	// TODO: 在此添加控件通知处理程序代

	m_progressDownLoad.SetPos(0);
	if(m_iListIndex < 0)
	{
		if(g_PubData.g_iLanguageFlag == 0)
			AfxMessageBox(_T("请选择要下载的录像"));
		else
			AfxMessageBox(_T("Please select the need to download the video!"));
		return ;
	}

	
	CStringArray strArrallSecons;
	CStringArray strArrKey;
	CStringArray strArrKeyValue;
	g_PubData.g_iniFile.GetAllSections(strArrallSecons);

	if(strArrallSecons.GetAt(0) == _T(""))
	{
		return;
	}
	g_PubData.g_iniFile.GetAllKeysAndValues(strArrallSecons.GetAt(0),strArrKey,strArrKeyValue);
	CString strPath = _T("");
	strPath = strArrKeyValue.GetAt(2);
	if(strPath == _T(""))
	{
		if(g_PubData.g_iLanguageFlag == 0)
			AfxMessageBox(_T("请先设置录像放置路径"));
		else
			AfxMessageBox( _T("Please set up the video placement path!"));
		return;
	}

	//文件夹不存在就创建
	if(!PathFileExists(strPath))
	{
		::_mkdir(strPath); 
	}
	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();	

	//录像的名称 = ip + 录像开始时间 + 后缀
	CString videoTime = _T("");
	CString strVideoName = g_PubData.g_strArrayPlaySuccessIp.GetAt(g_PubData.g_iPlayBack);
	videoTime.Format(_T("_%d%02d%02d%02d%02d%02d"),cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),
		cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	strVideoName += videoTime;
	strVideoName += _T(".jav");
	strPath += _T("\\");
	strPath += strVideoName;
	
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	int recType = -1;
	CString strRecType = _T("");
	strRecType = m_VideoPlayBack.GetItemText(m_iListIndex, 1);
	

	if(strRecType == _T("定时录像") || strRecType == _T("Time"))
	{
		recType = TIMER_RECODE;
	}
	if(strRecType == _T("报警录像") || strRecType == _T("Alarm"))
	{
		recType = ALARM_RECODE;
	}
	if(strRecType == _T("移动报警") || strRecType == _T("Move Alarm"))
	{
		recType = MOVE_RECODE;
	}
	if(strRecType == _T("手动") || strRecType == _T("Manual"))
	{
		recType = MANUAL_RECODE;
	}
	if(strRecType == _T("丢失报警") || strRecType == _T("Lost Alarm"))
	{
		recType = LOST_RECODE;
	}
	if(strRecType == _T("遮挡报警") || strRecType == _T("Hide Alarm"))
	{
		recType = HIDE_RECODE;
	}
	if(strRecType == _T("网络故障录像") || strRecType == _T("NetFault"))
	{
		recType = NET_FAULT_RECODE;
	}
	if(strRecType == _T("人体红外检测告警录像") || strRecType == _T("PIR_RECODE"))
	{
		recType = PIR_RECODE;
	}
	if(strRecType == _T("全部") || strRecType == _T("All"))
	{
		recType = ALL_RECODE;
	}
	

	CString strStartTime = _T("");
	CString strEndTime = _T("");
	CString str1 = m_VideoPlayBack.GetItemText(m_iListIndex, 2);
	CString str2 = m_VideoPlayBack.GetItemText(m_iListIndex, 3);
	CString str3 = m_VideoPlayBack.GetItemText(m_iListIndex, 4);
	strStartTime = getDate(str1);
	strEndTime = getDate(str2);
	m_lDownLoadTotalTime = _ttoi(str3);
	
	m_downloadHandle = JNetRecOpen4Time(g_PubData.g_vLoginHandle[g_PubData.g_iPlayBack], "", 0, 0, strStartTime.GetBuffer(0), strEndTime.GetBuffer(0) , 4096,  0, JRecDownload, this,  m_lRecHandle);
	if(m_downloadHandle > 0)
	{
		Sleep(1000);
		JNetRecCtrl(m_lRecHandle, JNET_PB_CTRL_START, NULL);

		m_lDownLoad  = AVP_CreateRecFile(strPath, AVP_PROTOCOL_JPF, Encoder_DM365);
	}


	strStartTime.ReleaseBuffer();
	strEndTime.ReleaseBuffer();
	m_progressDownLoad.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SERACHVIDEO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE);
	HANDLE hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)DownLoadProgress,this,0,0);
	CloseHandle(hThread);
}

int  CVideoPlayBack::JRecDownload(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam)
{
	CVideoPlayBack *pDlg = (CVideoPlayBack *)pUserParam;
	
	if(pBuff)
	{
		j_frame_t *pFrame = (j_frame_t *)pBuff;
		if(pDlg->m_lDownLoadStartTime == -1 && pFrame->frame_type != j_audio_frame) 
		{
			pDlg->m_lDownLoadStartTime = pFrame->timestamp_sec;
		}
		
		
		AVP_WriteRecFile(pDlg->m_lDownLoad, pBuff, dwRevLen, NULL, 0);

		if(pDlg->m_lDownLoadTotalTime == 0 )
			return 0;
		if(pFrame->timestamp_sec > 0 && pDlg->m_lDownLoadTotalTime > 0)
		{
			g_PubData.g_iDownLoadPos = (pFrame->timestamp_sec - pDlg->m_lDownLoadStartTime) / (pDlg->m_lDownLoadTotalTime / 100);
			TRACE("g_iDownLoadPos = %d , starttime = %ld, curtime = %ld, totaltime = %ld\r\n", g_PubData.g_iDownLoadPos,pDlg->m_lDownLoadStartTime, pFrame->timestamp_sec, pDlg->m_lDownLoadTotalTime);
		}
		
		if((pDlg->m_lDownLoadStartTime + pDlg->m_lDownLoadTotalTime) == pFrame->timestamp_sec)
		{

			TRACE("DownLoad Success\r\n");
			g_PubData.g_iDownLoadPos = 1000;
			pDlg->CloseDownload();
		}

		
	}
	return 0;
}

void  CVideoPlayBack::CloseDownload()
{
	if(m_lDownLoad)
	{
		AVP_CloseRecFile(m_lDownLoad);
		m_lDownLoad = NULL;
	}
	if(m_downloadHandle)
	{
		JNetRecClose(m_downloadHandle);
		m_downloadHandle = NULL;
	}
}

DWORD CVideoPlayBack::DownLoadProgress(LPVOID lpThreadParameter)
{
	CVideoPlayBack *pDlg = (CVideoPlayBack *)lpThreadParameter;
	while(g_PubData.g_iDownLoadPos != 1000 && g_PubData.g_iDownLoadPos >= 0)
	{
		Sleep(1000);
		pDlg->m_progressDownLoad.SetPos(g_PubData.g_iDownLoadPos);	
	}

	g_PubData.g_iDownLoadPos = 0;
	pDlg->m_lDownLoadStartTime	 = -1;
	pDlg->m_lDownLoadTotalTime	 = -1;
	
	pDlg->GetDlgItem(IDC_BUTTON_SERACHVIDEO)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(TRUE);
	pDlg->m_progressDownLoad.ShowWindow(SW_HIDE);

	return 0;
}

// int CVideoPlayBack::DownLoadStramCB(struct _jcu_stream_cb_s *handle, jcu_cb_parm_t *parm)
// {
// 	//TRACE("======================id %d, args %d, size %d data %x\n", parm->id, parm->args, parm->size, parm->data);
// 
// 	j_frame_t* pBufFrame = (j_frame_t*)parm->data;
// 	if (parm->id == JCU_STREAM_EV_OPEN)
// 	{
// 		return 0;
// 	}
// 	else if (parm->id == JCU_STREAM_EV_RECV)
// 	{
// 
// 		if(gVideoPlayback->m_lstartTime < 0 && (pBufFrame->frame_type == j_video_i_frame || pBufFrame->frame_type == j_video_p_frame || pBufFrame->frame_type == j_video_b_frame))
// 		{
// 			gVideoPlayback->m_lstartTime = pBufFrame->timestamp_sec;
// 		}
// 		;
// 		int iRet = -1;
// 		iRet = fwrite(parm->data,parm->size,1,fp);
// 		if( iRet != 1)
// 		{
// 			//AfxMessageBox("写入信息失败");
// 			return -1;
// 		}
// 		//TRACE("写入成功");
// 		long fileSize = ftell(fp);  //文件大小
// 		g_PubData.g_iDownLoadPos = fileSize /  (gVideoPlayback->m_lRecFileSize[gVideoPlayback->m_iListIndex] / 100);
// 		if(pBufFrame->frame_type == j_video_i_frame || pBufFrame->frame_type == j_video_p_frame || pBufFrame->frame_type == j_video_b_frame)
// 		{
// 			gVideoPlayback->m_lEndTime = pBufFrame->timestamp_sec;
// 		}
// 		gVideoPlayback->m_lFrameCount ++;
// 		return 0;
// 	}
// 	else if(parm->id == JCU_STREAM_EV_CLOSE)
// 	{
// 		if(m_downloadHandle == NULL)
// 			return -1;
// 		//TRACE("下载完成\n");
// 
// // 		STFileHead_1000 fileHead;   //文件头信息
// // 		STFileIndex_1001 fileIndex;	//文件索引信息
// // 
// // 		fileHead.m_dwMagic = READER_T_JPF;
// // 		fileHead.m_dwVersion = 0x01000002;
// // 		fileHead.m_lTimeZone = 0;
// // 		fileHead.m_iFileOffset = sizeof(stFileIndex_1001);
// // 		fileHead.m_iUserOffset = 0;
// // 
// // 		// 		m_lFrameCount	= 0;				// 帧数
// // 		// 		m_iRes1			= 0;				// 保留位
// // 		// 		m_tStart		= 0;				// 开始时间
// // 		// 		m_tEnd			= 0;				// 结束时间
// // 		// 		m_dwSize		= 0xFFFFFFFF;		// 下一索引位置
// // 		// 		m_dwProtocal	= READER_T_JPF;		// 协议类型,如:READER_T_JPF
// // 		// 		m_dwEncoder		= Encoder_3516;		// 创建的主机的CPU,见eEncoderType
// // 		// 		m_iRes2			= 0;				// 保留位
// // 		long fileSize = ftell(fp);
// // 		fileIndex.m_lFrameCount = gVideoPlayback->m_lFrameCount;
// // 		fileIndex.m_iRes1 = 0;
// // 		fileIndex.m_tStart = gVideoPlayback->m_lstartTime;
// // 		fileIndex.m_tEnd = gVideoPlayback->m_lEndTime;
// // 		fileIndex.m_dwSize = fileSize;
// // 		fileIndex.m_dwProtocal = READER_T_JPF;
// // 		fileIndex.m_dwEncoder = Encoder_3516;
// // 		fileIndex.m_iRes2 = 0;
// // 
// // 		fseek(fp, 0L , 0);
// // 		int iRet = -1;
// // 		iRet = fwrite((char *)&fileHead, sizeof(fileHead),1,fp);
// // 		if(iRet != 1)
// // 		{
// // 			//AfxMessageBox(_T("写入文件头失败"));
// // 			return 0;
// // 		}
// // 
// // 		iRet = fwrite((char *)&fileIndex, sizeof(fileIndex),1,fp);
// // 		if(iRet != 1)
// // 		{
// // 			//AfxMessageBox(_T("写入文件索引位置信息失败"));
// // 			return 0;
// // 		}
// // 
// // 		fclose(fp);
// // 		fp = NULL;
// // 
// // 		if(m_downloadHandle != NULL)
// // 		{
// // 			iRet = jcu_net_rec_close(m_downloadHandle);
// // 			if(iRet != 0)
// // 			{
// // 				//AfxMessageBox(_T("关闭录像失败"));
// // 				return -1;
// // 			}
// // 			m_downloadHandle = NULL;
// // 		}
// // 		
// 
// 		gVideoPlayback->m_progressDownLoad.SetPos(100);
// 		g_PubData.g_iDownLoadPos = 0;
// 		gVideoPlayback->GetDlgItem(IDC_BUTTON_SERACHVIDEO)->EnableWindow(TRUE);
// 		gVideoPlayback->GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(TRUE);
// 		if(g_PubData.g_iLanguageFlag == 0)
// 			AfxMessageBox(_T("下载完成"));
// 		else
// 			AfxMessageBox(_T("Download"), _T("Download success!"));
// 		gVideoPlayback->m_progressDownLoad.SetPos(0);
// 		gVideoPlayback->m_progressDownLoad.ShowWindow(SW_HIDE);
// 		return 0;
// 	}
// 	return 0;	
// 	
// }
// int CVideoPlayBack::DownLoadNotifyCB(struct _jcu_notify_cb_s *handle, jcu_cb_parm_t *parm)
// {
// 	gVideoPlayback->m_nDownLoadFlag = parm->args;
// 	if (parm->args != JCU_NOTIFY_ERR_0)
// 	{
// 		if(m_downloadHandle != NULL)
// 		{
// 			int iRet = jcu_net_rec_close(m_downloadHandle);
// 			if(iRet != 0)
// 			{
// 				return -1;
// 			}
// 			m_downloadHandle = NULL;
// 		}
// 		g_PubData.g_iDownLoadPos = 0;
// 		gVideoPlayback->GetDlgItem(IDC_BUTTON_SERACHVIDEO)->EnableWindow(TRUE);
// 		gVideoPlayback->GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(TRUE);
// 		gVideoPlayback->m_progressDownLoad.SetPos(0);
// 		gVideoPlayback->m_progressDownLoad.ShowWindow(SW_HIDE);
// 		AfxMessageBox(_T("Download"), _T("Download error!"));
// 		return -1;
// 	}
// 	return 0;
// }
void CVideoPlayBack::OnBnClickedButtonPlayfile()
{
	// TODO: 在此添加控件通知处理程序代码
	

	CString		strFile		= "";
	CString		strText		= "";
	time_t		tStart		= 0;		// 文件的开始时间
	time_t		tEnd		= 0;		// 文件的结束时间
	long		lSize		= 0;		// 文件的大小
	long		lProtocal	= 0;		// 文件的帧头协议
	long		lEncoder	= 0;		// 文件所用的编码器
	CFileDialog dlgFile(TRUE, _T("jav"),NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("jav Files (*.jav)|*.jav|All Files (*.*)|*.*||"),this);

	if ( dlgFile.DoModal()!=IDOK )
	{
		return;
	}
	strFile	= dlgFile.GetPathName(); 

	PlayVideoFile(strFile);

	
}


void CVideoPlayBack::PlayVideoFile(CString strFile)
{

	m_nSpeed = 0;
	GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(m_strPasueS);

	m_bIsPasue = FALSE;

	int iRet = -1;
	if(m_lRecHandle)
	{
		AVP_Stop(gChannel);
		AVP_ReleasePort(gChannel);
		JNetRecClose(m_lRecHandle);
		m_lRecHandle = NULL;
		gChannel = -1;
	}


	if(m_HIPlayerPort >= 0)
	{
		AVP_DelPlayWnd(m_HIPlayerPort, m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->GetSafeHwnd());
		AVP_Stop(m_HIPlayerPort);
		AVP_ReleasePort(m_HIPlayerPort);
		m_HIPlayerPort = -1;
	}

	
	time_t		tStart		= 0;		// 文件的开始时间
	time_t		tEnd		= 0;		// 文件的结束时间
	long		lSize		= 0;		// 文件的大小
	long		lProtocal	= 0;		// 文件的帧头协议
	long		lEncoder	= 0;		// 文件所用的编码器

	if ( AVP_GetFileInfo(strFile,&m_startPlayTime,&tEnd,&lSize,&lProtocal,&lEncoder)!=AVPErrSuccess )
	{
		// 文件不是合法的录像文件
		//AfxMessageBox(_T("文件不是合法的录像文件:\r\n%s\r\n"),strFile);
		AfxMessageBox(_T("获取文件信息失败"));
		return;
	}

	m_HIPlayerPort = AVP_GetFreePort();
	if(m_HIPlayerPort < 0)
	{
		AfxMessageBox( _T("AVP_GetFreePort error!"));
		return;
	}
	// 帧格式
	iRet = AVP_SetDataProtocol(m_HIPlayerPort,lProtocal);
	if(iRet != 0)
	{
		AfxMessageBox(_T("AVP_SetDataProtocol  error!"));
		return;
	}
	// 设置解码器
	iRet = AVP_SetCoder(m_HIPlayerPort,AVP_CODER_JXJ);
	if(iRet != 0)
	{
		AfxMessageBox(_T("AVP_SetCoder  error!"));
		return;
	}
	// 打开文件
	iRet = AVP_PlayFileName(m_HIPlayerPort,strFile,0);
	if(iRet != 0)
	{
		AfxMessageBox(_T("AVP_PlayFileName  error!"));
		return;
	}
	
	// 开始播放
	iRet = AVP_Play(m_HIPlayerPort);
	if(iRet != 0)
	{
		AfxMessageBox(_T("AVP_Play  error!"));
		return;
	}



 	m_Filetimes = AVP_GetFileTotalTimeS(m_HIPlayerPort);
 	m_PlayFiletime = 0;
	m_recodeScreenDlg.m_PlayProgress.SetRange(0, m_Filetimes);

	m_PlayFastTime = 1000;
	m_PlaySlowTime = 1000;
	m_SleepTime = 1000;
	if(!m_bClosePlayLocal)
	{
		HANDLE hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)PlayThreadFun,this,0,0);
		CloseHandle(hThread);
	}


	AVP_AddPlayWnd(m_HIPlayerPort, NULL, m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->GetSafeHwnd(),NULL, NULL);
	
}

DWORD CVideoPlayBack::PlayThreadFun(LPVOID lpThreadParameter)
{
	CVideoPlayBack *pDlg = (CVideoPlayBack *)lpThreadParameter;
	while(1)
	{
		pDlg->m_bClosePlayLocal = TRUE;
		if((pDlg->m_HIPlayerPort < 0 && pDlg->m_lRecHandle == NULL) || !::IsWindow(pDlg->m_hWnd))
		{
			pDlg->m_bClosePlayLocal = FALSE;
			return 0;
		}
		Sleep(pDlg->m_SleepTime);
		
		if(pDlg->m_recodeScreenDlg.m_bPlayFileProgress)    //拖动进度
		{
			if((pDlg->m_HIPlayerPort < 0 && pDlg->m_lRecHandle == NULL)|| !::IsWindow(pDlg->m_hWnd))
			{
				pDlg->m_bClosePlayLocal = FALSE;
				return 0;
			}
			pDlg->m_PlayFiletime = pDlg->m_recodeScreenDlg.m_PlayProgress.GetPos();
			if(pDlg->m_HIPlayerPort >= 0)
				AVP_Seek(pDlg->m_HIPlayerPort, pDlg->m_PlayFiletime);
			if(pDlg->m_lRecHandle)
				JNetRecCtrl(pDlg->m_lRecHandle, JNET_PB_CTRL_SET_TIME, (void *)pDlg->m_PlayFiletime);
			pDlg->m_recodeScreenDlg.m_bPlayFileProgress = FALSE;
			
		}
		else
		{
			if(pDlg->m_HIPlayerPort >= 0)
				pDlg->m_PlayFiletime = AVP_GetCurPlayTimeS(pDlg->m_HIPlayerPort);
// 			if(pDlg->m_lRecHandle)
// 				JNetRecCtrl(pDlg->m_lRecHandle, JNET_PB_CTRL_GET_TIME, &pDlg->m_PlayFiletime);

			
			pDlg->m_PlayFiletime = pDlg->m_PlayFiletime - pDlg->m_startPlayTime;
		}
	

		
		CString strText = _T("");
		strText.Format(_T("%d/%ld"), pDlg->m_PlayFiletime, pDlg->m_Filetimes);
		if((pDlg->m_HIPlayerPort < 0 && pDlg->m_lRecHandle == NULL) || !::IsWindow(pDlg->m_hWnd))
		{
			pDlg->m_bClosePlayLocal = FALSE;
			return 0;
		}
		pDlg->m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->SetWindowText(strText);
		pDlg->m_recodeScreenDlg.m_PlayProgress.SetPos(pDlg->m_PlayFiletime);

		if(pDlg->m_PlayFiletime  == pDlg->m_Filetimes)
		{
			pDlg->m_recodeScreenDlg.m_PlayProgress.SetPos(0);
			pDlg->m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->SetWindowText(_T("00/00"));
			pDlg->Invalidate();
			pDlg->m_bClosePlayLocal = FALSE;
			return 0;
		}
		
	}
	
	pDlg->m_bClosePlayLocal = FALSE;
	return 0;
}





//退出时销毁
void CVideoPlayBack::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	int iRet = -1;
	if(m_lRecHandle != NULL)
	{
		AVP_Stop(gChannel);
		AVP_ReleasePort(gChannel);
		JNetRecClose(m_lRecHandle);
		m_lRecHandle = NULL;
		gChannel = -1;
	}
	if(m_downloadHandle != NULL)
	{
		iRet = JNetRecClose(m_downloadHandle);
		if(iRet != 0)
		{
			//AfxMessageBox(_T("关闭录像下载失败"));
			return ;
		}
		m_downloadHandle = NULL;
	}

	if(m_HIPlayerPort >= 0)
	{
		AVP_DelPlayWnd(m_HIPlayerPort, m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->GetSafeHwnd());
		AVP_Stop(m_HIPlayerPort);
		AVP_ReleasePort(m_HIPlayerPort);
		m_HIPlayerPort = -1;
		
	}

	if(m_iDecPort >= 0)
	{
		AVP_DelPlayWnd(m_iDecPort, m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->GetSafeHwnd());
	}
	
}


//暂停播放录像
void CVideoPlayBack::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	
		if(!m_bIsPasue)
		{
			//HIPLAYER_Pause(m_HIPlayerPort, 0);
			if(m_HIPlayerPort >=  0)
			{
				AVP_Pause(m_HIPlayerPort);
// 				m_SleepTime = 1000;
// 				m_PlayFastTime = 1000;
// 				m_PlaySlowTime = 1000;
			}
			if(m_lRecHandle)
			{
				JNetRecCtrl(m_lRecHandle, JNET_PB_CTRL_PAUSE, NULL);
			}
			GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(m_strPasueE);
			UpdateWindow();
			m_bIsPasue = TRUE;
		}
		else
		{
			if(m_HIPlayerPort >=  0)
			{
				AVP_Play(m_HIPlayerPort);
			}
			if(m_lRecHandle)
			{
				JNetRecCtrl(m_lRecHandle, JNET_PB_CTRL_RESUME, NULL);
				GetDlgItem(IDC_STATIC_SPEED)->SetWindowText("1 X");
				m_nSpeed = 0;
			}
			GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(m_strPasueS);
			UpdateWindow();
//			HIPLAYER_Pause(m_HIPlayerPort, 1);
			m_bIsPasue = FALSE;
		}
	

// 	if(gChannel >= 0)
// 	{
// 		if(m_bIsPasue)
// 		{
// 			HIPLAYER_Pause(gChannel, 0);
// 			GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("暂停"));
// 			UpdateWindow();
// 			m_bIsPasue = FALSE;
// 		}
// 		else
// 		{
// 			GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("播放"));
// 			UpdateWindow();
// 			HIPLAYER_Pause(gChannel, 1);
// 			m_bIsPasue = TRUE;
// 		}
// 	}
	
}


//停止播放录像
void CVideoPlayBack::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码

	int iRet = -1;
	if(m_lRecHandle)
	{
		AVP_Stop(gChannel);
		AVP_ReleasePort(gChannel);
		JNetRecClose(m_lRecHandle);
		m_lRecHandle = NULL;
		gChannel = -1;
		Invalidate();
	}

	if(m_iDecPort >= 0)
	{
		AVP_DelPlayWnd(m_iDecPort, m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->GetSafeHwnd());
		m_iDecPort = -1;
		Invalidate();
	}
	if(m_HIPlayerPort >= 0)
	{
		AVP_DelPlayWnd(m_HIPlayerPort, m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->GetSafeHwnd());
		AVP_Stop(m_HIPlayerPort);
		AVP_ReleasePort(m_HIPlayerPort);
		m_HIPlayerPort = -1;
		Invalidate();
	}


	m_recodeScreenDlg.m_PlayProgress.SetPos(0);
	m_recodeScreenDlg.GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->SetWindowText(_T("00/00"));
	GetDlgItem(IDC_STATIC_SPEED)->SetWindowText("1 X");
// 	if(m_iDecPort >= 0)
// 	{
// 		AVP_DelPlayWnd(m_iDecPort);
// 		m_iDecPort = -1;
// 	}
// 
// 	if(gChannel >= 0)
// 	{
// 		AVP_DelPlayWnd(gChannel);
// 		gChannel = -1;
// 	}
}

HBRUSH CVideoPlayBack::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//IDC_STATIC_SHOW_PLAYBACK_VIDEO
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	CBrush   brush(RGB(255,255,255)); 
	if(pWnd-> GetDlgCtrlID() == IDC_STATIC_SHOW_PLAYBACK_VIDEO)
	{
		CRect   rect;  
		pDC->SelectObject(&brush);  
		CWnd   *p_staticwnd=GetDlgItem(IDC_STATIC_SHOW_PLAYBACK_VIDEO); 
		p_staticwnd-> GetWindowRect(&rect);  
		pDC-> Rectangle(&rect); 
		pDC->SetBkMode(TRANSPARENT); 
	}

	return   (HBRUSH)brush;
	//return hbr;
}

void CVideoPlayBack::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CVideoPlayBack::OnCbnSelchangeComboxDevice()
{
	// TODO: 在此添加控件通知处理程序代码
	g_PubData.g_iPlayBack = m_ComDevice.GetCurSel();
}

void CVideoPlayBack::OnBnClickedButtonFlashdevice()
{
	// TODO: 在此添加控件通知处理程序代码
	int iCountDevice = g_PubData.g_strArrayPlaySuccessIp.GetCount();
	m_ComDevice.ResetContent();
	if(iCountDevice > 0)
	{
		for(int i =0 ;i < iCountDevice; i++)
		{
			m_ComDevice.AddString(g_PubData.g_strArrayPlaySuccessIp.GetAt(i));
		}
		g_PubData.g_iPlayBack = 0;
		m_ComDevice.SetCurSel(0);
	}
}

void CVideoPlayBack::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 

	m_VideoPlayBack.Invalidate();
	UpdateWindow();
	CDialog::OnPaint();
	
}

void CVideoPlayBack::OnBnClickedButtonPlayslow()
{

	// TODO: 在此添加控件通知处理程序代码

	m_nSpeed --;
	if(m_nSpeed >= 0)
	{
		m_nSpeed --;
		OnBnClickedButtonPlayfast();
		return;
	}
	if(m_nSpeed < -4)
	{
		m_nSpeed = -4;
	}
	SetPlaySpeed();

	m_PlaySlowTime = 1000 * (pow((DOUBLE)2, abs(m_nSpeed)));
	if(m_PlaySlowTime > 16000)
	{
		return;
	}
	m_SleepTime = m_PlaySlowTime;
	CString	strText;
	strText.Format(_T("1/%d X"), (int)pow((DOUBLE)2, abs(m_nSpeed)));
	GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(strText);
	

}

void CVideoPlayBack::OnBnClickedButtonPlayfast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSpeed ++;
	if(m_nSpeed < 0)
	{
		m_nSpeed ++;
		OnBnClickedButtonPlayslow();
		return;
	}
	if(m_nSpeed > 4)
	{
		m_nSpeed = 4;
	}
	SetPlaySpeed();
	
	m_PlayFastTime = 1000/(pow((DOUBLE)2, m_nSpeed));
	if(m_PlayFastTime < 62)
	{
		return;
	}
	m_SleepTime = m_PlayFastTime;
	CString	strText;
	strText.Format(_T("%d X"), (int)pow((DOUBLE)2, m_nSpeed));
	GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(strText);
}


void CVideoPlayBack::SetPlaySpeed()
{

	int nPlaySpeed = 0;
	
	switch(m_nSpeed)
	{
	case 0:
		nPlaySpeed = AVPPlaySpeed_1X;
		break;
	case -1:
		nPlaySpeed = AVPPlaySpeed_1_2X;
		break;
	case -2:
		nPlaySpeed = AVPPlaySpeed_1_4X;
		break;
	case -3:
		nPlaySpeed = AVPPlaySpeed_1_8X;
		break;
	case -4:
		nPlaySpeed = AVPPlaySpeed_1_16X;
		break;
	case 1:
		nPlaySpeed = AVPPlaySpeed_2X;
		break;
	case 2:
		nPlaySpeed = AVPPlaySpeed_4X;
		break;
	case 3:
		nPlaySpeed = AVPPlaySpeed_8X;
		break;
	case 4:
		nPlaySpeed = AVPPlaySpeed_16X;
		break;

	}

	if(m_lRecHandle)
	{
		
		if(m_nSpeed >=0)
		{
			AVP_SetPlaySpeed(gChannel, nPlaySpeed);
			JNetRecCtrl(m_lRecHandle, JNET_PB_CTRL_FAST, (void *)nPlaySpeed);
		}
		else
		{
			AVP_SetPlaySpeed(gChannel, nPlaySpeed);	
			JNetRecCtrl(m_lRecHandle, JNET_PB_CTRL_SLOW, (void *)nPlaySpeed);
			
		}
	}
	if(m_HIPlayerPort >=0 )
	{
		AVP_SetPlaySpeed(m_HIPlayerPort, nPlaySpeed);
	}
	
	
	
}