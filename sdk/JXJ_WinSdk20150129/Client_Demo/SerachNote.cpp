// SerachNote.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "SerachNote.h"
#include "Pub_Data.h"
#include <WinSock.h>
// CSerachNote 对话框


IMPLEMENT_DYNAMIC(CSerachNote, CDialog)

CSerachNote::CSerachNote(CWnd* pParent /*=NULL*/)
	: CDialog(CSerachNote::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CSerachNote::~CSerachNote()
{
}

void CSerachNote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_DATE, m_StartDate);
	DDX_Control(pDX, IDC_START_TIME, m_StartTime);
	DDX_Control(pDX, IDC_END_DATE, m_EndDate);
	DDX_Control(pDX, IDC_END_TIME, m_EndTime);
	DDX_Control(pDX, IDC_COMBO_RECODE_TYPE, m_RecodeType);
	DDX_Control(pDX, IDC_LIST_RECODE, m_ListRecode);
	DDX_Control(pDX, IDC_COMBO_RECODEDEVICE, m_RecodeDevice);
}


BEGIN_MESSAGE_MAP(CSerachNote, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SERACH, &CSerachNote::OnBnClickedButtonSerach)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_RECODEDEVICE, &CSerachNote::OnCbnSelchangeComboRecodedevice)
END_MESSAGE_MAP()


// CSerachNote 消息处理程序
BOOL CSerachNote::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_iBeginNode = 0;
	m_iEndNode = 31;
	m_iSsid = -1;
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_RecodeType.AddString(_T("系统日志"));
		m_RecodeType.AddString(_T("告警日志"));
		m_RecodeType.AddString(_T("操作日志"));
		m_RecodeType.AddString(_T("网络日志"));
		m_RecodeType.AddString(_T("参数日志"));
		m_RecodeType.AddString(_T("异常日志"));
		m_RecodeType.AddString(_T("所有日志"));

		m_RecodeType.SetCurSel(0);

		m_ListRecode.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListRecode.InsertColumn(0 , _T("时间"), 2, 150, -1);
		m_ListRecode.InsertColumn(1 , _T("操作类型"), 2, 150,-1);
		m_ListRecode.InsertColumn(2 , _T("操作用户"), 2, 150,-1);
		m_ListRecode.InsertColumn(3 , _T("操作用户IP"), 2, 150,-1);
	}
	else
	{
		m_RecodeType.AddString(_T("system log"));
		m_RecodeType.AddString(_T("alarm log"));
		m_RecodeType.AddString(_T("operation log"));
		m_RecodeType.AddString(_T("web log"));
		m_RecodeType.AddString(_T("Parameter log"));
		m_RecodeType.AddString(_T("abnormal log"));
		m_RecodeType.AddString(_T("all log"));

		m_RecodeType.SetCurSel(0);

		m_ListRecode.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListRecode.InsertColumn(0 , _T("Time"), 2, 150, -1);
		m_ListRecode.InsertColumn(1 , _T("Operation type"), 2, 150,-1);
		m_ListRecode.InsertColumn(2 , _T("User"), 2, 150,-1);
		m_ListRecode.InsertColumn(3 , _T("Operation IP"), 2, 150,-1);
	}
	

	COleDateTime LimitData(1970,1,1,0,0,0);
	m_StartDate.SetRange(&LimitData, NULL);
	m_EndDate.SetRange(&LimitData, NULL);
	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();																	// 小时		//分钟			//秒
	COleDateTime startTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(), 0, 0, 0);
	COleDateTime endTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(), 23, 59, 59);

	m_StartTime.SetTime(startTime);
	m_EndTime.SetTime(endTime);

	int iCountDevice = g_PubData.g_strArrayPlaySuccessIp.GetCount();
	if(iCountDevice > 0)
	{
		for(int i = 0; i< iCountDevice; i++)
		{
			m_RecodeDevice.AddString(g_PubData.g_strArrayPlaySuccessIp.GetAt(i)); //添加IP
		}
		m_RecodeDevice.SetCurSel(0);
		g_PubData.g_iAttributeIng = 0;
	}
	else
	{
		//m_RecodeIp.EnableWindow(FALSE);
		//m_RecodeIp.SetWindowText(_T("没有设备"));
	}
	return TRUE;
}

void CSerachNote::OnBnClickedButtonSerach()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_PubData.g_iAttributeIng < 0)
	{
		//AfxMessageBox(_T("没有设备"));
		return;
	}
	if(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng] == NULL)
	{
		//AfxMessageBox(_T("没有设备"));
		return;
	}
	ZeroMemory(&m_operationLog, sizeof(JOperationLog));
	//查询条件
	CTime dateStart;
	CTime dateEnd;
	CTime timeStart;
	CTime timeEnd;

	m_StartDate.GetTime(dateStart);
	m_StartTime.GetTime(timeStart);
	m_EndDate.GetTime(dateEnd);
	m_EndTime.GetTime(timeEnd);
	
	time_t beg_time = LocalToUtc(dateStart, timeStart);//转换为UTC时间
	time_t end_time = LocalToUtc(dateEnd, timeEnd);
	
	m_operationLog.cond.beg_time = (LONG)(beg_time + (8 * 3600));
	m_operationLog.cond.end_time = (LONG)end_time + (8 * 3600);
	m_operationLog.cond.beg_node = m_iBeginNode;
	m_operationLog.cond.end_node = m_iEndNode;
	m_operationLog.cond.sess_id = m_iSsid;
	GetRecodeType(m_RecodeType.GetCurSel());

	if(m_iBeginNode == 0)
	{
		m_ListRecode.DeleteAllItems();
	}

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_OPERATION_LOG, (char *)&m_operationLog, sizeof(m_operationLog),NULL, NULL );
	if (iRet!=0)
	{
		MessageBox(_T("获取日志失败"));
		return ;
	}
	ReFreshWindow();
	//AddToList();
}


void CSerachNote::AddToList()
{
	
	//m_ListRecode.DeleteAllItems();

	int j = m_iBeginNode;
	for(int i = 0; i< (int)m_operationLog.node_count; i++)
	{
		//m_operationLog.item[i].times
		CString strText = _T("");
		time_t times = m_operationLog.item[i].times - (8 * 3600);
		tm local_time;
		localtime_s(&local_time, &times);
		CString strTime = _T("");
		strTime.Format(_T("%d-%2d-%2d %2d:%2d:%2d"),local_time.tm_year + 1900, local_time.tm_mon+1, local_time.tm_mday
											,local_time.tm_hour, local_time.tm_min, local_time.tm_sec);
		m_ListRecode.InsertItem(j, strTime);
		strText = _T("");
		if(m_operationLog.item[i].major_type  == J_LOG_MAJOR_SYSTEM)
		{
			if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_STARTUP)
			{
				strText = _T("开机");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_SHUTDOWN)
			{
				strText =_T("关机");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_REBOOT)
			{
				strText =_T("重启");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_ALL)
			{
				strText =_T("所有系统日志");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_ALARM)
		{
			if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_DI_START)
			{
				strText = _T("输入告警发生");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_DI_STOP)
			{
				strText =_T("输入告警停止");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_MD_START)
			{
				strText =_T("移动侦测告警发生");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_MD_STOP)
			{
				strText =_T("移动侦测告警停止");
			}
			if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_VL_START)
			{
				strText = _T("视频丢失告警发生");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_VL_STOP)
			{
				strText =_T("视频丢失告警停止");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_OD_START)
			{
				strText =_T("视频遮挡报警发生");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_OD_STOP)
			{
				strText =_T("视频遮挡报警停止");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_NETCARD_DISCONN)
			{
				strText =_T("网卡断线");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_NETCARD_RECONN)
			{
				strText =_T("网卡恢复连接");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_PIR_START)
			{
				strText =_T("人体红外探测告警发生");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_PIR_STOP)
			{
				strText =_T("人体红外探测告警停止");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_ALL)
			{
				strText =_T("所有告警日志");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_OPERATE)
		{			
				if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOGIN)
				{
					strText = _T("登陆");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOGOUT)
				{
					strText =_T("注销");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_ADD)
				{
					strText =_T("用户管理-增加");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_DEL)
				{
					strText =_T("用户管理-删除 ");
				}
				if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_MODI)
				{
					strText = _T("用户管理-修改");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_SETTIME)
				{
					strText =_T("设置系统时间");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_FORMAT_DISK)
				{
					strText =_T("格式化硬盘");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DEFAULT)
				{
					strText =_T("恢复默认");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_UPGRADE)
				{
					strText =_T("升级");
				}
				if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_PLAYBACK)
				{
					strText = _T("回放");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_PTZ)
				{
					strText =_T("云台控制");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_BACKUP)
				{
					strText =_T("备份");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_RECORD_START)
				{
					strText =_T("启动录像");
				}
				if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_RECORD_STOP)
				{
					strText = _T("停止录像");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_CLR_ALARM)
				{
					strText =_T("清除报警");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_TALKBACK_START)
				{
					strText =_T("对讲开始");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_TALKBACK_STOP)
				{
					strText =_T("对讲结束");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_DEL)
				{
					strText =_T("删除日志");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_EMPTY)
				{
					strText =_T("清空日志");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_BACKUP)
				{
					strText =_T("备份日志");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_MANUAL_RECORD_START)
				{
					strText =_T("手动启动录像");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_MANUAL_RECORD_STOP)
				{
					strText =_T("手动停止录像");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_FORMAT_DISK_U)
				{
					strText =_T("格式化U盘");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_CTRL_ALARM_OUT)
				{
					strText =_T("手动控制报警输出U盘");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DETECT_DEAL_PIX)
				{
					strText =_T("坏点检测");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DETECT_IRIS)
				{
					strText =_T("光圈校正");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_ALL)
				{
					strText =_T("所有告警日志");
				}		 
					 
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_NETWORK)
		{
				strText = _T("网络日志");
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_PARAM)
		{	 
				if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_NETWORK)
				{
					strText = _T("网络参数配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_UART)
				{
					strText =_T("串口参数配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PTZ)
				{
					strText =_T("云台参数配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_CHAN)
				{
					strText =_T("通道参数配置 ");
				}
				if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_VENC)
				{
					strText = _T("编码参数配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_TV)
				{
					strText =_T("TV参数配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PIC_ATTR)
				{
					strText =_T("图像属性配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_RECORD)
				{
					strText =_T("录像参数配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_MOTION)
				{
					strText =_T("移动侦测配置");
				}
				if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_VIDEOLOST)
				{
					strText = _T("视频丢失配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ALARMIN)
				{
					strText =_T("输入告警配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_POLL)
				{
					strText =_T("轮巡配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OVERLAY)
				{
					strText =_T("预览配置");
				}
				if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OSD)
				{
					strText = _T("OSD配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_COMM)
				{
					strText =_T("DVR 常规配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OD)
				{
					strText =_T("视频遮挡配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ROI)
				{
					strText =_T("感兴趣区域配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_FTP)
				{
					strText =_T("FTP 配置 ");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_UPNP)
				{
					strText =_T("UPNP 配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_SMTP)
				{
					strText =_T("SMTP 配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_NTP)
				{
					strText =_T("NTP 配置");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_DDNS)
				{
					strText =_T("DDNS 配置 ");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ALARMUP)
				{
					strText =_T("报警上传配置 ");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PIR)
				{
					strText =_T("人体红外探测配置 ");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_RTSP)
				{
					strText =_T("RTSP服务配置 ");
				}
				else if(m_operationLog.item[i].minor_type == J_PRARM_MINOR_ALL)
				{
					strText =_T("所有参数日志");
				}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_EXCEPTION)
		{ 
				if(m_operationLog.item[i].minor_type == J_EXCEPTION_HD_FULL)
				{
					strText = _T("硬盘满");
				}
				else if(m_operationLog.item[i].minor_type == J_EXCEPTION_HD_ERROR)
				{
					strText =_T("硬盘错误");
				}
				else if(m_operationLog.item[i].minor_type == J_EXCEPTION_NET_DISCONNECT)
				{
					strText =_T("网络断开");
				}
				else if(m_operationLog.item[i].minor_type == J_EXCEPTION_IP_CONFLICT)
				{
					strText =_T("IP冲突 ");
				}
				else if(m_operationLog.item[i].minor_type == J_EXCEPTION_MINOR_ALL)
				{
					strText = _T("所有异常日志");
				}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_ALL)
		{
			strText = _T("所有日志");
		}
		m_ListRecode.SetItemText(j, 1, strText);

		strText = _T("");
		strText.Format(_T("%s"), m_operationLog.item[i].user);
		m_ListRecode.SetItemText(j, 2, strText);

		struct in_addr addr1;
		memcpy(&addr1, &m_operationLog.item[i].ip, 4);

		char strIp[20];
		memset(strIp, '\0', sizeof(strIp));
	
		char *strip = inet_ntoa(addr1);
		strText = _T("");
		strText.Format(_T("%s"), strip);
		m_ListRecode.SetItemText(j, 3, strText);
		j++;
	}
}

void CSerachNote::AddToListEnglish()
{

	//m_ListRecode.DeleteAllItems();

	int j = m_iBeginNode;
	for(int i = 0; i< (int)m_operationLog.node_count; i++)
	{
		//m_operationLog.item[i].times
		CString strText = _T("");
		time_t times = m_operationLog.item[i].times - (8 * 3600);
		tm local_time;
		localtime_s(&local_time, &times);
		CString strTime = _T("");
		strTime.Format(_T("%d-%2d-%2d %2d:%2d:%2d"),local_time.tm_year + 1900, local_time.tm_mon+1, local_time.tm_mday
			,local_time.tm_hour, local_time.tm_min, local_time.tm_sec);
		m_ListRecode.InsertItem(j, strTime);
		strText = _T("");
		if(m_operationLog.item[i].major_type  == J_LOG_MAJOR_SYSTEM)
		{
			if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_STARTUP)
			{
				strText = _T("Starting up");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_SHUTDOWN)
			{
				strText =_T("Shut down");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_REBOOT)
			{
				strText =_T("Restar");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_ALL)
			{
				strText =_T("All the system log");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_ALARM)
		{
			if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_DI_START)
			{
				strText = _T("Input alarm start");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_DI_STOP)
			{
				strText =_T("Input alarm end");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_MD_START)
			{
				strText =_T("Mobile detection alarm start");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_MD_STOP)
			{
				strText =_T("Mobile detection alarm end");
			}
			if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_VL_START)
			{
				strText = _T("Video loss start");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_VL_STOP)
			{
				strText =_T("Video loss end");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_OD_START)
			{
				strText =_T("Video occlusion start");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_OD_STOP)
			{
				strText =_T("Video occlusion end");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_NETCARD_DISCONN)
			{
				strText =_T("Network disconnection");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_NETCARD_RECONN)
			{
				strText =_T("Card recovery.");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_PIR_START)
			{
				strText =_T("The human body infrared detection alarm.");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_PIR_STOP)
			{
				strText =_T("The human body infrared detection alarm stop.");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_ALL)
			{
				strText =_T("All alarm log");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_OPERATE)
		{			
			if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOGIN)
			{
				strText = _T("Login");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOGOUT)
			{
				strText =_T("Cancellation");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_ADD)
			{
				strText =_T("User management and increase");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_DEL)
			{
				strText =_T("User management and delete ");
			}
			if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_MODI)
			{
				strText = _T("User management and modify");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_SETTIME)
			{
				strText =_T("Set the system time");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_FORMAT_DISK)
			{
				strText =_T("Disk formatting");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DEFAULT)
			{
				strText =_T("Restore default");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_UPGRADE)
			{
				strText =_T("upgrade");
			}
			if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_PLAYBACK)
			{
				strText = _T("Playback");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_PTZ)
			{
				strText =_T("PTZ");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_BACKUP)
			{
				strText =_T("Backup");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_RECORD_START)
			{
				strText =_T("Start recording");
			}
			if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_RECORD_STOP)
			{
				strText = _T("End recording");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_CLR_ALARM)
			{
				strText =_T("Claear alarm");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_TALKBACK_START)
			{
				strText =_T("Talkback began");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_TALKBACK_STOP)
			{
				strText =_T("Intercom end");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_DEL)
			{
				strText =_T("Delete log");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_EMPTY)
			{
				strText =_T("clear log");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_BACKUP)
			{
				strText =_T("Backup log");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_MANUAL_RECORD_START)
			{
				strText =_T("Manual start the video");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_MANUAL_RECORD_STOP)
			{
				strText =_T("Manual stop recording");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_FORMAT_DISK_U)
			{
				strText =_T("The disk U");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_CTRL_ALARM_OUT)
			{
				strText =_T("Alarm output U wheel for manual control");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DETECT_DEAL_PIX)
			{
				strText =_T("Bad pixel detection");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DETECT_IRIS)
			{
				strText =_T("Aperture correction");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_ALL)
			{
				strText =_T("All alarm log");
			}		 

		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_NETWORK)
		{
			strText = _T("Web log");
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_PARAM)
		{	 
			if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_NETWORK)
			{
				strText = _T("Network parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_UART)
			{
				strText =_T("Serial port parameter settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PTZ)
			{
				strText =_T("PTZ parameter settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_CHAN)
			{
				strText =_T("Channel parameter setting ");
			}
			if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_VENC)
			{
				strText = _T("Encode parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_TV)
			{
				strText =_T("TV parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PIC_ATTR)
			{
				strText =_T("Img parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_RECORD)
			{
				strText =_T("Record parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_MOTION)
			{
				strText =_T("Mobile detection settings");
			}
			if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_VIDEOLOST)
			{
				strText = _T("Lost video settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ALARMIN)
			{
				strText =_T("Input alarm setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_POLL)
			{
				strText =_T("A round robin set");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OVERLAY)
			{
				strText =_T("Preview settings");
			}
			if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OSD)
			{
				strText = _T("OSD settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_COMM)
			{
				strText =_T("DVR settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OD)
			{
				strText =_T("Video block set");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ROI)
			{
				strText =_T("Interest Area");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_FTP)
			{
				strText =_T("FTP settings ");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_UPNP)
			{
				strText =_T("UPNP settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_SMTP)
			{
				strText =_T("SMTP settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_NTP)
			{
				strText =_T("NTP settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_DDNS)
			{
				strText =_T("DDNS settings ");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ALARMUP)
			{
				strText =_T("Upload alarm ");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PIR)
			{
				strText =_T("The human body infrared probe configuration ");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_RTSP)
			{
				strText =_T("The RTSP service configuration");
			}
			else if(m_operationLog.item[i].minor_type == J_PRARM_MINOR_ALL)
			{
				strText =_T("All parameter log ");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_EXCEPTION)
		{ 
			if(m_operationLog.item[i].minor_type == J_EXCEPTION_HD_FULL)
			{
				strText = _T("The disk is full");
			}
			else if(m_operationLog.item[i].minor_type == J_EXCEPTION_HD_ERROR)
			{
				strText =_T("A disk error");
			}
			else if(m_operationLog.item[i].minor_type == J_EXCEPTION_NET_DISCONNECT)
			{
				strText =_T("Network disconnection");
			}
			else if(m_operationLog.item[i].minor_type == J_EXCEPTION_IP_CONFLICT)
			{
				strText =_T("IP conflict ");
			}
			else if(m_operationLog.item[i].minor_type == J_EXCEPTION_MINOR_ALL)
			{
				strText = _T("All abnormal log");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_ALL)
		{
			strText = _T("All log");
		}
		m_ListRecode.SetItemText(j, 1, strText);

		strText = _T("");
		strText.Format(_T("%s"), m_operationLog.item[i].user);
		m_ListRecode.SetItemText(j, 2, strText);

		struct in_addr addr1;
		memcpy(&addr1, &m_operationLog.item[i].ip, 4);

		char strIp[20];
		memset(strIp, '\0', sizeof(strIp));

		char *strip = inet_ntoa(addr1);
		strText = _T("");
		strText.Format(_T("%s"), strip);
		m_ListRecode.SetItemText(j, 3, strText);
		j++;
	}
}
time_t CSerachNote::LocalToUtc(CTime dateStart, CTime timeStart)
{
	tm UtcTime;
	dateStart.GetGmtTm(&UtcTime);

	UtcTime.tm_hour = timeStart.GetHour();
	UtcTime.tm_min = timeStart.GetMinute();
	UtcTime.tm_sec = timeStart.GetSecond();
	return mktime(&UtcTime);
}

void CSerachNote::GetRecodeType(int iIndex)
{ 

	if(iIndex == 0)
	{
		m_operationLog.cond.type = J_LOG_MAJOR_SYSTEM;
	}
	else if(iIndex ==1)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_ALARM;
	}
	else if(iIndex ==2)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_OPERATE;
	}
	else if(iIndex ==3)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_NETWORK;
	}
	else if(iIndex ==4)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_PARAM;
	}
	else if(iIndex ==5)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_EXCEPTION;
	}
	else if(iIndex ==6)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_ALL;
	}
	
}

int CSerachNote::ReFreshWindow()
{
	if(g_PubData.g_iLanguageFlag == 0)
		AddToList();
	else
		AddToListEnglish();
	if(m_iEndNode < (int)m_operationLog.total_count)
	{
		m_iBeginNode += 32;
		m_iEndNode += 32;
		m_iSsid = m_operationLog.cond.sess_id;
		OnBnClickedButtonSerach();
	}
	else
	{
		m_iBeginNode = 0;
		m_iEndNode = 31;
		m_iSsid = -1;
	}
	return 0;
}
void CSerachNote::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CSerachNote::OnCbnSelchangeComboRecodedevice()
{
	// TODO: 在此添加控件通知处理程序代码
	g_PubData.g_iAttributeIng = m_RecodeDevice.GetCurSel();
}
