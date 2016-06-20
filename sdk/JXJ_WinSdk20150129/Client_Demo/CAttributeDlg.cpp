// CAttributeDlg.cpp : 实现文件
//属性配置主窗口

#include "stdafx.h"
#include "Client_Demo.h"
#include "CAttributeDlg.h"
#include "Pub_Data.h"
#include "BorderDlg.h"


// CCAttributeDlg 对话框

IMPLEMENT_DYNAMIC(CCAttributeDlg, CDialog)

CCAttributeDlg::CCAttributeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCAttributeDlg::IDD, pParent)
{
	

}

CCAttributeDlg::~CCAttributeDlg()
{
	
}

void CCAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ATTRIBUTE, m_AttributeTree);
}


BEGIN_MESSAGE_MAP(CCAttributeDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ATTRIBUTE, &CCAttributeDlg::OnTvnSelchangedTreeAttribute)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
//	ON_WM_MOVE()
ON_WM_MOVE()
END_MESSAGE_MAP()


// CCAttributeDlg 消息处理程序
BOOL CCAttributeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(g_PubData.g_iLanguageFlag)
	{
		this->SetWindowText(_T("Property configuration"));
	}
	else
	{
		this->SetWindowText(_T("属性配置"));
	}
	m_hSelItem = NULL;
	if(g_PubData.g_iLanguageFlag == 0)
		InitTree();
	else
		InitTreeEnglish();
	return TRUE;
}

//初始化树列表
void CCAttributeDlg::InitTree()
{
	m_AttributeTree.ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS );
	HTREEITEM hRoot;
	HTREEITEM hRootChild1;
	HTREEITEM hItem;
	CString strRoot = _T("");
	strRoot = g_PubData.g_strArrayPlaySuccessIp.GetAt(g_PubData.g_iAttributeIng);
	hRoot = m_AttributeTree.InsertItem(strRoot);  //树顶端插入IP


	hRootChild1 = m_AttributeTree.InsertItem(_T("系统配置"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("系统信息"),1,1,hRootChild1);
		m_cSysMsgDlg.Create(CSystemMsgDlg::IDD, this);
		m_PageMap[hItem] = &m_cSysMsgDlg;
		m_AttributeTree.SelectItem(hItem);

	hItem = m_AttributeTree.InsertItem(_T("设备状态"),1,1,hRootChild1);
		m_deviceState.Create(MAKEINTRESOURCE(IDD_DIALOG_DEVICE_STATE), this);
		m_PageMap[hItem] = &m_deviceState;

	hItem = m_AttributeTree.InsertItem(_T("时间管理"),1,1,hRootChild1);
		m_cSetTimeDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_SETTIME),this);
		m_PageMap[hItem] = &m_cSetTimeDlg;

	hItem = m_AttributeTree.InsertItem(_T("用户管理"),1,1,hRootChild1);
		m_cUserDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_DEVICE_USER), this);
		m_PageMap[hItem] = &m_cUserDlg;

	hItem = m_AttributeTree.InsertItem(_T("系统维护"),1,1,hRootChild1);
		m_cUpdateDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_DEVICE_UPDATE),this);
		m_PageMap[hItem] = &m_cUpdateDlg;


	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 & DEV_CAP_IR )  //根据能力集判断是否支持
	{
		hItem = m_AttributeTree.InsertItem(_T("红外配置"),1,1,hRootChild1);
		m_iR_Cut.Create(MAKEINTRESOURCE(IDD_DIALOG_IRCUT_SET), this);
		m_PageMap[hItem] = &m_iR_Cut;
	}
	


	HTREEITEM hRootChild2;
	hRootChild2 = m_AttributeTree.InsertItem(_T("音视频配置"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("编码参数"),1,1,hRootChild2);
		m_cEncode.Create(MAKEINTRESOURCE(IDD_DIALOG_ENCODE),this);
		m_PageMap[hItem] = &m_cEncode;

	hItem = m_AttributeTree.InsertItem(_T("OSD配置"),1,1,hRootChild2);
		m_cOsdSetDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_OSDSET), this);
		m_PageMap[hItem] = &m_cOsdSetDlg;
	hItem = m_AttributeTree.InsertItem(_T("视频遮挡"),1,1,hRootChild2);
		m_videoHide.Create(MAKEINTRESOURCE(IDD_DIALOG_VIDEO_HIDE), this);
		m_PageMap[hItem] = &m_videoHide;

	hItem = m_AttributeTree.InsertItem(_T("图像参数"),1,1,hRootChild2);
		m_cPitcure.Create(MAKEINTRESOURCE(IDD_DIALOG_PICTURESET), this);
		m_PageMap[hItem] = &m_cPitcure;

	hItem = m_AttributeTree.InsertItem(_T("感兴趣区域"),1,1,hRootChild2);
		m_interest.Create(MAKEINTRESOURCE(IDD_DIALOG_INTERSET_AREA), this);
		m_PageMap[hItem] = &m_interest;

	hItem = m_AttributeTree.InsertItem(_T("自动切换码率"),1,1,hRootChild2);
		m_channelStream.Create(MAKEINTRESOURCE(IDD_DIALOG_CHANNEL_STREAM), this);
		m_PageMap[hItem] = &m_channelStream;

	if( g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 &  DEV_CAP_ELEVATOR_CFG ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("楼层配置"),1,1,hRootChild2);
		m_elevatorSet.Create(MAKEINTRESOURCE(IDD_DIALOG_ELEVATOR), this);
		m_PageMap[hItem] = &m_elevatorSet;
	}


	HTREEITEM hRootChild3;
	hRootChild3 = m_AttributeTree.InsertItem(_T("网络配置"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("网络参数"),1,1,hRootChild3);
		m_netParam.Create(MAKEINTRESOURCE(IDD_DIALOG_NET_PARAM), this);
		m_PageMap[hItem] = &m_netParam;
		
	hItem = m_AttributeTree.InsertItem(_T("PPPOE配置"),1,1,hRootChild3);
		m_pSet.Create(MAKEINTRESOURCE(IDD_DIALOG_PPPOESET), this);
		m_PageMap[hItem] = &m_pSet;

	hItem = m_AttributeTree.InsertItem(_T("DDNS配置"),1,1,hRootChild3);
		m_dnsSet.Create(MAKEINTRESOURCE(IDD_DIALOG_DNS_SET), this);
		m_PageMap[hItem] = &m_dnsSet;
	
	hItem = m_AttributeTree.InsertItem(_T("E-Mail配置"),1,1,hRootChild3);
		m_eMailSet.Create(MAKEINTRESOURCE(IDD_DIALOG_EMAIL_SET), this);
		m_PageMap[hItem] = &m_eMailSet;

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].upnp_enable == 1 )  //根据能力集判断是否支持
	{
		hItem = m_AttributeTree.InsertItem(_T("UPNP配置"),1,1,hRootChild3);
		m_upnpSet.Create(MAKEINTRESOURCE(IDD_DIALOG_UPNP_SET), this);
		m_PageMap[hItem] = &m_upnpSet;

	}
	
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ftp_enable == 1 )  //根据能力集判断是否支持
	{
		hItem = m_AttributeTree.InsertItem(_T("FTP配置"),1,1,hRootChild3);
		m_ftpSet.Create(MAKEINTRESOURCE(IDD_DIALOG_FTP_SET), this);
		m_PageMap[hItem] = &m_ftpSet;
	}
	

	hItem = m_AttributeTree.InsertItem(_T("GB28181配置"),1,1,hRootChild3);
		m_gbs8181.Create(MAKEINTRESOURCE(IDD_DIALOG_GB28181_SET), this);
		m_PageMap[hItem] = &m_gbs8181;

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 &  DEV_CAP_WIFI ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("WIFI配置"),1,1,hRootChild3);
		m_serachWifi.Create(MAKEINTRESOURCE(IDD_DIALOG_SERACH_WIFI), this);
		m_PageMap[hItem] = &m_serachWifi;
	}
	
	hItem = m_AttributeTree.InsertItem(_T("RTSP服务配置"),1,1,hRootChild3);
	m_rtspServer.Create(MAKEINTRESOURCE(IDD_DIALOG_RTSPSERVER), this);
	m_PageMap[hItem] = &m_rtspServer;


	hItem = m_AttributeTree.InsertItem(_T("网络连接状态"),1,1,hRootChild3);
		m_netStatus.Create(MAKEINTRESOURCE(IDD_DIALOG_NET_CONNECT_STATUS), this);
		m_PageMap[hItem] = &m_netStatus;

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].platform_type &  PF_HXHT ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("互信互通平台"), 1,1, hRootChild3);
			m_m_HxhtConfig.Create(MAKEINTRESOURCE(IDD_DIALOG_HXHT), this);
			m_PageMap[hItem] = &m_m_HxhtConfig;
	}

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].platform_type &  PF_HW ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("华为平台"), 1,1, hRootChild3);
		m_hwSetDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_HW_SET), this);
		m_PageMap[hItem] = &m_hwSetDlg;
	}


	
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].platform_type & PF_ZTE)
	{
		hItem = m_AttributeTree.InsertItem(_T("中兴平台"), 1,1, hRootChild3);
		m_zteCfg.Create(MAKEINTRESOURCE(IDD_DIALOG_ZTE), this);
		m_PageMap[hItem] = &m_zteCfg;
	}
		
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 &  DEV_CAP_NETWORK_FAULT ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("网络故障检测"),1,1,hRootChild3);
		m_NetworkFaultCheck.Create(MAKEINTRESOURCE(IDD_DIALOG_NetWorkFaultCheck), this);
		m_PageMap[hItem] = &m_NetworkFaultCheck;
	}
	


	HTREEITEM hRootChild4;
	hRootChild4 = m_AttributeTree.InsertItem(_T("存储配置"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("录像计划"),1,1,hRootChild4);
		m_videoPlan.Create(MAKEINTRESOURCE(IDD_DIALOG_VIDEO_PLAN), this);
		m_PageMap[hItem] = &m_videoPlan;
		
	hItem = m_AttributeTree.InsertItem(_T("网络磁盘"),1,1,hRootChild4);
		m_netdisk.Create(MAKEINTRESOURCE(IDD_DIALOG_NET_DISK_SET), this);
		m_PageMap[hItem] = &m_netdisk;
		
	HTREEITEM hRootChild5;
	hRootChild5 = m_AttributeTree.InsertItem(_T("报警配置"),1,1,hRoot);

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.supp_hide_alarm == 1)
	{
		hItem = m_AttributeTree.InsertItem(_T("遮挡报警"),1,1,hRootChild5);
		m_hideWarning.Create(MAKEINTRESOURCE(IDD_DIALOG_HIDE_WARNING),this);
		m_PageMap[hItem] = &m_hideWarning;
	}
	
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.supp_move_alarm == 1)
	{
		hItem = m_AttributeTree.InsertItem(_T("移动侦测"),1,1,hRootChild5);
		m_moveSense.Create(MAKEINTRESOURCE(IDD_DIALOG_MOVE_SENSE_SET), this);
		m_PageMap[hItem] = &m_moveSense;
	}
	

	hItem = m_AttributeTree.InsertItem(_T("探头报警"),1,1,hRootChild5);
		m_ioWarn.Create(MAKEINTRESOURCE(IDD_DIALOG_IOWARNING), this);
		m_PageMap[hItem] = &m_ioWarn;

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.supp_video_lost_alarm == 1)
	{
		hItem = m_AttributeTree.InsertItem(_T("丢失报警"),1,1,hRootChild5);
		m_lostWarn.Create(MAKEINTRESOURCE(IDD_DIALOG_LOST_WARNING), this);
		m_PageMap[hItem] = &m_lostWarn;
	}
	
	hItem = m_AttributeTree.InsertItem(_T("报警上传"),1,1,hRootChild5);
		m_upload.Create(MAKEINTRESOURCE(IDD_DIALOG_WARNING_UPLOAD), this);
		m_PageMap[hItem] = &m_upload;

	hItem = m_AttributeTree.InsertItem(_T("联动报警"),1,1,hRootChild5);
		m_jointAction.Create(MAKEINTRESOURCE(IDD_DIALOG_JOINT_ACTION), this);
		m_PageMap[hItem] = &m_jointAction;

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 & DEV_CAP_PIR)
	{
		hItem = m_AttributeTree.InsertItem(_T("人体红外检测"), 1, 1, hRootChild5);
		m_pirAlarm.Create(MAKEINTRESOURCE(IDD_DIALOG_PIR_ALARM), this);
		m_PageMap[hItem] = &m_pirAlarm;
	}

	
	HTREEITEM hRootChild6;
	hRootChild6 = m_AttributeTree.InsertItem(_T("串口配置"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("串口配置"),1,1,hRootChild6);
		m_serial.Create(MAKEINTRESOURCE(IDD_DIALOG_SERIAL_SET), this);
		m_PageMap[hItem] = &m_serial;
		
	hItem = m_AttributeTree.InsertItem(_T("云台配置"),1,1,hRootChild6);
		m_cloudSet.Create(MAKEINTRESOURCE(IDD_DIALOG_CLOUD_SET), this);
		m_PageMap[hItem] = &m_cloudSet;

	HTREEITEM hRootChild7;
	if(g_PubData.g_iLanguageFlag == 0)
	{
		hRootChild7 = m_AttributeTree.InsertItem(_T("智能分析"),1,1,hRoot);
		hItem = m_AttributeTree.InsertItem(_T("AVD配置"),1,1,hRootChild7);
	}
	else
	{
		hRootChild7 = m_AttributeTree.InsertItem(_T("Intelligent Analysis "),1,1,hRoot);
		hItem = m_AttributeTree.InsertItem(_T("AVD Config"),1,1,hRootChild7);
	}
		m_avdSet.Create(MAKEINTRESOURCE(IDD_DIALOG_AVD_SET), this);
		m_PageMap[hItem] = &m_avdSet;

	if(	g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_TRIP_WIRE_CAP || 
		g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_PERI_METER_CAP ||
		g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_LEFT_CAP ||
		g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_TAKE_CAP) 
	{
		if(g_PubData.g_iLanguageFlag == 0)
			hItem = m_AttributeTree.InsertItem(_T("peaosc配置"),1,1,hRootChild7);
		else
			hItem = m_AttributeTree.InsertItem(_T("Peaosc Config"),1,1,hRootChild7);

		m_peaoscCfg.Create(MAKEINTRESOURCE(IDD_DIALOG_PeaOsc), this);
		m_PageMap[hItem] = &m_peaoscCfg;
	}

	if (g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_HERD_CAP)
	{
		hItem = m_AttributeTree.InsertItem(_T("牧业分析"),1,1,hRootChild7);
		m_herdAnalyse.Create(MAKEINTRESOURCE(IDD_DIALOG_HerdAnalyse), this);
		m_PageMap[hItem] = &m_herdAnalyse;
	}
	
	if (g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_CPC_CAP)
	{
		hItem = m_AttributeTree.InsertItem(_T("越线人数统计"),1,1,hRootChild7);
		m_cpcSetDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_CPC), this);
		m_PageMap[hItem] = &m_cpcSetDlg;
	}

	m_AttributeTree.Expand(hRoot, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild1, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild2, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild3, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild4, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild5, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild6, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild7, TVE_EXPAND);
	
}

void CCAttributeDlg::InitTreeEnglish()
{
	m_AttributeTree.ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS );
	HTREEITEM hRoot;
	HTREEITEM hRootChild1;
	HTREEITEM hItem;
	CString strRoot = _T("");
	strRoot = g_PubData.g_strArrayPlaySuccessIp.GetAt(g_PubData.g_iAttributeIng);
	hRoot = m_AttributeTree.InsertItem(strRoot);  //树顶端插入IP


	hRootChild1 = m_AttributeTree.InsertItem(_T("System"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("System Setting"),1,1,hRootChild1);
	m_cSysMsgDlg.Create(CSystemMsgDlg::IDD, this);
	m_PageMap[hItem] = &m_cSysMsgDlg;
	m_AttributeTree.SelectItem(hItem);

	hItem = m_AttributeTree.InsertItem(_T("Device State"),1,1,hRootChild1);
	m_deviceState.Create(MAKEINTRESOURCE(IDD_DIALOG_DEVICE_STATE), this);
	m_PageMap[hItem] = &m_deviceState;

	hItem = m_AttributeTree.InsertItem(_T("Time Settting"),1,1,hRootChild1);
	m_cSetTimeDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_SETTIME),this);
	m_PageMap[hItem] = &m_cSetTimeDlg;

	hItem = m_AttributeTree.InsertItem(_T("Device User"),1,1,hRootChild1);
	m_cUserDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_DEVICE_USER), this);
	m_PageMap[hItem] = &m_cUserDlg;

	hItem = m_AttributeTree.InsertItem(_T("Device Upgrade"),1,1,hRootChild1);
	m_cUpdateDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_DEVICE_UPDATE),this);
	m_PageMap[hItem] = &m_cUpdateDlg;


	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 & DEV_CAP_IR )  //根据能力集判断是否支持
	{
		hItem = m_AttributeTree.InsertItem(_T("IrCut"),1,1,hRootChild1);
		m_iR_Cut.Create(MAKEINTRESOURCE(IDD_DIALOG_IRCUT_SET), this);
		m_PageMap[hItem] = &m_iR_Cut;
	}



	HTREEITEM hRootChild2;
	hRootChild2 = m_AttributeTree.InsertItem(_T("Video Setting"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("Encoding"),1,1,hRootChild2);
	m_cEncode.Create(MAKEINTRESOURCE(IDD_DIALOG_ENCODE),this);
	m_PageMap[hItem] = &m_cEncode;

	hItem = m_AttributeTree.InsertItem(_T("OSD Setting"),1,1,hRootChild2);
	m_cOsdSetDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_OSDSET), this);
	m_PageMap[hItem] = &m_cOsdSetDlg;
	hItem = m_AttributeTree.InsertItem(_T("Video Hide"),1,1,hRootChild2);
	m_videoHide.Create(MAKEINTRESOURCE(IDD_DIALOG_VIDEO_HIDE), this);
	m_PageMap[hItem] = &m_videoHide;

	hItem = m_AttributeTree.InsertItem(_T("Img"),1,1,hRootChild2);
	m_cPitcure.Create(MAKEINTRESOURCE(IDD_DIALOG_PICTURESET), this);
	m_PageMap[hItem] = &m_cPitcure;

	hItem = m_AttributeTree.InsertItem(_T("Interest Area"),1,1,hRootChild2);
	m_interest.Create(MAKEINTRESOURCE(IDD_DIALOG_INTERSET_AREA), this);
	m_PageMap[hItem] = &m_interest;

	hItem = m_AttributeTree.InsertItem(_T("AutoSwitch"),1,1,hRootChild2);
	m_channelStream.Create(MAKEINTRESOURCE(IDD_DIALOG_CHANNEL_STREAM), this);
	m_PageMap[hItem] = &m_channelStream;

	if( g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 &  DEV_CAP_ELEVATOR_CFG ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("Floor display configuration "),1,1,hRootChild2);
		m_elevatorSet.Create(MAKEINTRESOURCE(IDD_DIALOG_ELEVATOR), this);
		m_PageMap[hItem] = &m_elevatorSet;
	}


	HTREEITEM hRootChild3;
	hRootChild3 = m_AttributeTree.InsertItem(_T("IP Setting"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("NetWork"),1,1,hRootChild3);
	m_netParam.Create(MAKEINTRESOURCE(IDD_DIALOG_NET_PARAM), this);
	m_PageMap[hItem] = &m_netParam;

	hItem = m_AttributeTree.InsertItem(_T("PPPOE"),1,1,hRootChild3);
	m_pSet.Create(MAKEINTRESOURCE(IDD_DIALOG_PPPOESET), this);
	m_PageMap[hItem] = &m_pSet;

	hItem = m_AttributeTree.InsertItem(_T("DDNS"),1,1,hRootChild3);
	m_dnsSet.Create(MAKEINTRESOURCE(IDD_DIALOG_DNS_SET), this);
	m_PageMap[hItem] = &m_dnsSet;

	hItem = m_AttributeTree.InsertItem(_T("E-Mail"),1,1,hRootChild3);
	m_eMailSet.Create(MAKEINTRESOURCE(IDD_DIALOG_EMAIL_SET), this);
	m_PageMap[hItem] = &m_eMailSet;

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].upnp_enable == 1 )  //根据能力集判断是否支持
	{
		hItem = m_AttributeTree.InsertItem(_T("UPNP"),1,1,hRootChild3);
		m_upnpSet.Create(MAKEINTRESOURCE(IDD_DIALOG_UPNP_SET), this);
		m_PageMap[hItem] = &m_upnpSet;

	}

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ftp_enable == 1 )  //根据能力集判断是否支持
	{
		hItem = m_AttributeTree.InsertItem(_T("FTP"),1,1,hRootChild3);
		m_ftpSet.Create(MAKEINTRESOURCE(IDD_DIALOG_FTP_SET), this);
		m_PageMap[hItem] = &m_ftpSet;
	}


// 	hItem = m_AttributeTree.InsertItem(_T("GB28181"),1,1,hRootChild3);
// 	m_gbs8181.Create(MAKEINTRESOURCE(IDD_DIALOG_GB28181_SET), this);
// 	m_PageMap[hItem] = &m_gbs8181;

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 &  DEV_CAP_WIFI ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("WIFI"),1,1,hRootChild3);
		m_serachWifi.Create(MAKEINTRESOURCE(IDD_DIALOG_SERACH_WIFI), this);
		m_PageMap[hItem] = &m_serachWifi;
	}


	hItem = m_AttributeTree.InsertItem(_T("State of Network Connection "),1,1,hRootChild3);
	m_netStatus.Create(MAKEINTRESOURCE(IDD_DIALOG_NET_CONNECT_STATUS), this);
	m_PageMap[hItem] = &m_netStatus;

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].platform_type &  PF_HXHT ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("Hxht"), 1,1, hRootChild3);
		m_m_HxhtConfig.Create(MAKEINTRESOURCE(IDD_DIALOG_HXHT), this);
		m_PageMap[hItem] = &m_m_HxhtConfig;
	}

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].platform_type &  PF_HW ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("Huawei"), 1,1, hRootChild3);
		m_hwSetDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_HW_SET), this);
		m_PageMap[hItem] = &m_hwSetDlg;
	}

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 &  DEV_CAP_NETWORK_FAULT ) 
	{
		hItem = m_AttributeTree.InsertItem(_T("NetWord Fault"),1,1,hRootChild3);
		m_NetworkFaultCheck.Create(MAKEINTRESOURCE(IDD_DIALOG_NetWorkFaultCheck), this);
		m_PageMap[hItem] = &m_NetworkFaultCheck;
	}



	HTREEITEM hRootChild4;
	hRootChild4 = m_AttributeTree.InsertItem(_T("SD Card Recording Setting"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("Record Plan"),1,1,hRootChild4);
	m_videoPlan.Create(MAKEINTRESOURCE(IDD_DIALOG_VIDEO_PLAN), this);
	m_PageMap[hItem] = &m_videoPlan;

	hItem = m_AttributeTree.InsertItem(_T("Net Disk"),1,1,hRootChild4);
	m_netdisk.Create(MAKEINTRESOURCE(IDD_DIALOG_NET_DISK_SET), this);
	m_PageMap[hItem] = &m_netdisk;

	HTREEITEM hRootChild5;
	hRootChild5 = m_AttributeTree.InsertItem(_T("Alarm Setting"),1,1,hRoot);

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.supp_hide_alarm == 1)
	{
		hItem = m_AttributeTree.InsertItem(_T("Hide Alarm"),1,1,hRootChild5);
		m_hideWarning.Create(MAKEINTRESOURCE(IDD_DIALOG_HIDE_WARNING),this);
		m_PageMap[hItem] = &m_hideWarning;
	}

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.supp_move_alarm == 1)
	{
		hItem = m_AttributeTree.InsertItem(_T("MoveSense"),1,1,hRootChild5);
		m_moveSense.Create(MAKEINTRESOURCE(IDD_DIALOG_MOVE_SENSE_SET), this);
		m_PageMap[hItem] = &m_moveSense;
	}


	hItem = m_AttributeTree.InsertItem(_T("IO Alarm"),1,1,hRootChild5);
	m_ioWarn.Create(MAKEINTRESOURCE(IDD_DIALOG_IOWARNING), this);
	m_PageMap[hItem] = &m_ioWarn;

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.supp_video_lost_alarm == 1)
	{
		hItem = m_AttributeTree.InsertItem(_T("Lost Alarm"),1,1,hRootChild5);
		m_lostWarn.Create(MAKEINTRESOURCE(IDD_DIALOG_LOST_WARNING), this);
		m_PageMap[hItem] = &m_lostWarn;
	}


	hItem = m_AttributeTree.InsertItem(_T("Upload Alarm"),1,1,hRootChild5);
	m_upload.Create(MAKEINTRESOURCE(IDD_DIALOG_WARNING_UPLOAD), this);
	m_PageMap[hItem] = &m_upload;

	hItem = m_AttributeTree.InsertItem(_T("Joint Action"),1,1,hRootChild5);
	m_jointAction.Create(MAKEINTRESOURCE(IDD_DIALOG_JOINT_ACTION), this);
	m_PageMap[hItem] = &m_jointAction;

	HTREEITEM hRootChild6;
	hRootChild6 = m_AttributeTree.InsertItem(_T("SerialSetting"),1,1,hRoot);
	hItem = m_AttributeTree.InsertItem(_T("Serial"),1,1,hRootChild6);
	m_serial.Create(MAKEINTRESOURCE(IDD_DIALOG_SERIAL_SET), this);
	m_PageMap[hItem] = &m_serial;

	hItem = m_AttributeTree.InsertItem(_T("PTZ"),1,1,hRootChild6);
	m_cloudSet.Create(MAKEINTRESOURCE(IDD_DIALOG_CLOUD_SET), this);
	m_PageMap[hItem] = &m_cloudSet;

	HTREEITEM hRootChild7;
	if(g_PubData.g_iLanguageFlag == 0)
	{
		hRootChild7 = m_AttributeTree.InsertItem(_T("智能分析"),1,1,hRoot);
		hItem = m_AttributeTree.InsertItem(_T("AVD配置"),1,1,hRootChild7);
	}
	else
	{
		hRootChild7 = m_AttributeTree.InsertItem(_T("Intelligent Analysis "),1,1,hRoot);
		hItem = m_AttributeTree.InsertItem(_T("AVD Config"),1,1,hRootChild7);
	}
	m_avdSet.Create(MAKEINTRESOURCE(IDD_DIALOG_AVD_SET), this);
	m_PageMap[hItem] = &m_avdSet;

	if(	g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_TRIP_WIRE_CAP || 
		g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_PERI_METER_CAP ||
		g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_LEFT_CAP ||
		g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_TAKE_CAP) 
	{
		if(g_PubData.g_iLanguageFlag == 0)
			hItem = m_AttributeTree.InsertItem(_T("peaosc配置"),1,1,hRootChild7);
		else
			hItem = m_AttributeTree.InsertItem(_T("Peaosc Config"),1,1,hRootChild7);

		m_peaoscCfg.Create(MAKEINTRESOURCE(IDD_DIALOG_PeaOsc), this);
		m_PageMap[hItem] = &m_peaoscCfg;
	}

	if (g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_CPC_CAP)
	{
		hItem = m_AttributeTree.InsertItem(_T("越线人数统计"),1,1,hRootChild7);
		m_cpcSetDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_CPC), this);
		m_PageMap[hItem] = &m_cpcSetDlg;
	}

	m_AttributeTree.Expand(hRoot, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild1, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild2, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild3, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild4, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild5, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild6, TVE_EXPAND);
	m_AttributeTree.Expand(hRootChild7, TVE_EXPAND);

}
//改变树选中状态触发
void CCAttributeDlg::OnTvnSelchangedTreeAttribute(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	EnablePlayWnd(g_PubData.g_iPlayWndFlag); //关闭之前播放的视频
	EnableBorderDlg();
	HTREEITEM hSelItem = pNMTreeView->itemNew.hItem;
	if (hSelItem == m_AttributeTree.GetRootItem())       //不点击根节点
	{
		*pResult = 0;
		return;
	}

	PAGE_MAP::const_iterator it = m_PageMap.find(hSelItem);
	if( it != m_PageMap.end() )
	{
		CWnd * pSelPage = it->second;
		CRect rect;
		this->GetClientRect(&rect);

		CRect rectTree;
		m_AttributeTree.GetClientRect(&rectTree);

		pSelPage->MoveWindow(rectTree.Width()+20,20,rect.Width()-220,rectTree.Height()-60,TRUE);
		pSelPage->ShowWindow(SW_SHOW);
		FlashWnd(pSelPage);//当选中节点时调用相应节点的刷新函数
		
		if(m_hSelItem)
		{
			m_PageMap[m_hSelItem]->ShowWindow(SW_HIDE);

		}
		m_hSelItem = hSelItem;
	}
	
	*pResult = 0;
}

//调用相应配置窗口的刷新函数
void CCAttributeDlg::FlashWnd(CWnd *pSelPage)
{
	if(pSelPage == &m_cSetTimeDlg)
	{
		m_cSetTimeDlg.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_cUserDlg)
	{
		m_cUserDlg.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_cUpdateDlg)
	{
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_cEncode)
	{
		m_cEncode.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_cOsdSetDlg)
	{
		m_cOsdSetDlg.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 0;
	}
	else if(pSelPage == &m_videoHide)
	{
		m_videoHide.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 1;
	}
	else if(pSelPage == &m_cPitcure)
	{
		m_cPitcure.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 2;
	}
	else if(pSelPage == &m_netParam)
	{
		m_netParam.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_pSet)
	{
		m_pSet.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_eMailSet)
	{
		m_eMailSet.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_upnpSet)
	{
		m_upnpSet.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_ftpSet)
	{
		m_ftpSet.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_gbs8181)
	{
		m_gbs8181.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_videoPlan)
	{
		m_videoPlan.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_netdisk)
	{
		m_netdisk.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage ==&m_hideWarning)
	{
		m_hideWarning.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 4;
	}
	else if(pSelPage == &m_lostWarn)
	{
		m_lostWarn.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 6;
	}
	else if(pSelPage == &m_upload)
	{
		m_upload.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_serial)
	{
		m_serial.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_cloudSet)
	{
		m_cloudSet.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;

	}
	else if(pSelPage == &m_moveSense)
	{
		m_moveSense.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 5;
	}
	else if(pSelPage == &m_ioWarn)
	{
		m_ioWarn.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_interest)
	{
		m_interest.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 3;
	}
	else if(pSelPage == &m_dnsSet)
	{
		m_dnsSet.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_avdSet)
	{
		m_avdSet.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_netStatus)
	{
		m_netStatus.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_jointAction)
	{
		m_jointAction.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_serachWifi)
	{
		m_serachWifi.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_deviceState)
	{
		m_deviceState.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_channelStream)
	{
		m_channelStream.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_iR_Cut)
	{
		m_iR_Cut.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_NetworkFaultCheck)
	{
		m_NetworkFaultCheck.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_peaoscCfg)
	{
		m_peaoscCfg.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 7;
	}
	else if(pSelPage == &m_m_HxhtConfig)
	{
		m_m_HxhtConfig.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_hwSetDlg)
	{
		m_hwSetDlg.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_cpcSetDlg)
	{
		m_cpcSetDlg.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 8;
	}
	else if(pSelPage == &m_pirAlarm)
	{
		m_pirAlarm.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_rtspServer)
	{
		m_rtspServer.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_herdAnalyse)
	{
		m_herdAnalyse.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = 9;
	}
	else if(pSelPage == &m_elevatorSet)
	{
		m_elevatorSet.OnBnClickedButtonFlash();
		g_PubData.g_iPlayWndFlag = -1;
	}
	else if(pSelPage == &m_zteCfg)
	{
		m_zteCfg.OnBnClickedButtonRefresh();
		g_PubData.g_iPlayWndFlag = -1;
	}

}
void CCAttributeDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*if(g_PubData.g_iControlDevRet > 0 || g_PubData.g_iFormatProgress > 0 || upDev.percent > 0)
	{
		AfxMessageBox(_T("有未执行完的操作......"));
		return;
	}*/
	g_PubData.g_bUpgDeviceClose = FALSE;
	CDialog::OnClose();
}

void CCAttributeDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: 在此处添加消息处理程序代码

	EnablePlayWnd(g_PubData.g_iPlayWndFlag);
	//AVP_Stop(g_PubData.g_iChancel[g_PubData.g_iAttributeIng]);
	if(g_PubData.g_bOpenStreamInAttribute)  //在没有播放视频窗口，属性配置打开流的情况下 ， 关闭属性配置窗口的时候同时关闭流
	{
		if(g_PubData.g_vStreamHandle[g_PubData.g_iAttributeIng] != NULL)		
		{
			AVP_ReleasePort(g_PubData.g_iChancel[g_PubData.g_iAttributeIng]);	
			g_PubData.g_iChancel[g_PubData.g_iAttributeIng] = -1;
			JNetStreamClose(g_PubData.g_vStreamHandle[g_PubData.g_iAttributeIng]);
			g_PubData.g_vStreamHandle[g_PubData.g_iAttributeIng] = NULL;
			g_PubData.g_bOpenStreamInAttribute = FALSE;
		}	
	}
	m_cSysMsgDlg.SendMessage(WM_CLOSE);
}

//打开第二个窗口的时候关闭第一个播放的窗口
void CCAttributeDlg::EnablePlayWnd(int iIndex)
{
	if(g_PubData.g_vStreamHandle[g_PubData.g_iAttributeIng] == NULL)
	{
		return;
	}
	if(iIndex== 0)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],m_cOsdSetDlg.GetDlgItem(IDC_STATIC_SHOWSCREEN)->GetSafeHwnd());
	}
	else if(iIndex == 1)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], m_videoHide.m_HideScreen.GetSafeHwnd());
	}
	else if(iIndex == 2)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],m_cPitcure.GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
	}
	else if(iIndex == 3)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],m_interest.m_interestScreen.GetSafeHwnd());
	}
	else if(iIndex == 4)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], m_hideWarning.m_cHideAlarmScreen.GetSafeHwnd());
	}
	else if(iIndex == 5)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],m_moveSense.m_cMoveSenseScreen.GetSafeHwnd());
	}
	else if(iIndex == 6)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],m_lostWarn.GetDlgItem(IDC_STATIC_SHOWLOSTSCREEN)->GetSafeHwnd());
	}
	else if(iIndex == 7)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],m_peaoscCfg.m_peaoscScreen.GetSafeHwnd());
	}
	else if(iIndex == 8)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],m_cpcSetDlg.m_cpcScreen.GetSafeHwnd());
	}
	else if(iIndex == 9)
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],m_herdAnalyse.m_herdAnalyseScreen.GetSafeHwnd());
	}
	else
	{
		return;
	}
	iIndex = -1;
}
//void CCAttributeDlg::OnMove(int x, int y)
//{
//	CDialog::OnMove(x, y);
//
//	// TODO: 在此处添加消息处理程序代码
//}

void CCAttributeDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	if(g_PubData.g_bHideAlarmDrawBorder && g_PubData.g_iPlayWndFlag == 4)
	{
		m_hideWarning.OnBnClickedCheckStartpaint();
	}
	if(g_PubData.g_bMoveAlarmDrawBorder && g_PubData.g_iPlayWndFlag == 5)
	{
		m_moveSense.OnBnClickedCheckStartpaint();
	}
	if(g_PubData.g_bHideDrawBorder && g_PubData.g_iPlayWndFlag == 1)
	{
		m_videoHide.OnBnClickedCheckStartpaint();
	}
	if(g_PubData.g_bInterestDrawBorder && g_PubData.g_iPlayWndFlag == 3)
	{
		m_interest.OnBnClickedCheckStartpaint();
	}
}

void CCAttributeDlg::EnableBorderDlg()
{
	if(g_PubData.g_iPlayWndFlag == 4)//隐藏遮挡报警的区域
	{
		for(int i = 0; i < 4; i++)
		{
			m_hideWarning.m_cHideAlarmScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
		}
	}
	if(g_PubData.g_iPlayWndFlag == 5)
	{
		for(int i = 0; i< 4; i++)
		{
			m_moveSense.m_cMoveSenseScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
		}
	}

	if(g_PubData.g_iPlayWndFlag == 1)
	{
		for(int i = 0; i< 4; i++)
		{
			m_videoHide.m_HideScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
		}
	}

	if(g_PubData.g_iPlayWndFlag == 3)
	{
		for(int i = 0; i< 4; i++)
		{
			m_interest.m_interestScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
		}
	}
}