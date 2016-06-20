// DeviceState.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "DeviceState.h"
#include "Pub_Data.h"


// CDeviceState 对话框


IMPLEMENT_DYNAMIC(CDeviceState, CDialog)

CDeviceState::CDeviceState(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceState::IDD, pParent)
{
	ZeroMemory(&m_DevWorkState, sizeof(m_DevWorkState));
}

CDeviceState::~CDeviceState()
{
	DestroyWindow();
}

void CDeviceState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICE_STATE, m_DeviceState);
	DDX_Control(pDX, IDC_COMBO_LOCOLSHOW, m_LocalShow);
	DDX_Control(pDX, IDC_LIST_DISKSTATE, m_ListDiskState);
	DDX_Control(pDX, IDC_LIST_CHANNELSTATE, m_ListChannelState);
}


BEGIN_MESSAGE_MAP(CDeviceState, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CDeviceState::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDeviceState::OnBnClickedButtonSave)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDeviceState 消息处理程序
BOOL CDeviceState::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_DeviceState.AddString(_T("正常"));
		m_DeviceState.AddString(_T("CPU使用率过高"));

		m_LocalShow.AddString(_T("正常"));
		m_LocalShow.AddString(_T("不正常"));

		m_ListDiskState.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListDiskState.InsertColumn(0 , _T("硬盘容量"), 2, 100, -1);
		m_ListDiskState.InsertColumn(1 , _T("硬盘剩余空间"), 2, 100,-1);
		m_ListDiskState.InsertColumn(2 , _T("硬盘状态"), 2, 200,-1);

		m_ListChannelState.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListChannelState.InsertColumn(0 , _T("是否录像"), 2, 80, -1);
		m_ListChannelState.InsertColumn(1 , _T("信号状态"), 2, 80,-1);
		m_ListChannelState.InsertColumn(2 , _T("通道硬件状态"), 2, 80,-1);
		m_ListChannelState.InsertColumn(3 , _T("实际码率"), 2, 80, -1);
		m_ListChannelState.InsertColumn(4 , _T("语音通道状态"), 2, 80, -1);
		m_ListChannelState.InsertColumn(5 , _T("报警输入口状态"), 2, 80, -1);
		m_ListChannelState.InsertColumn(6 , _T("报警输出口状态"), 2, 80, -1);
	}
	else
	{
		m_DeviceState.AddString(_T("Normal"));
		m_DeviceState.AddString(_T("High CPU usage"));

		m_LocalShow.AddString(_T("Normal"));
		m_LocalShow.AddString(_T("Not normal"));

		m_ListDiskState.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListDiskState.InsertColumn(0 , _T("Hard disk capacity"), 2, 100, -1);
		m_ListDiskState.InsertColumn(1 , _T("Hard disk space"), 2, 100,-1);
		m_ListDiskState.InsertColumn(2 , _T("The hard state"), 2, 200,-1);

		m_ListChannelState.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListChannelState.InsertColumn(0 , _T("Whether the video"), 2, 80, -1);
		m_ListChannelState.InsertColumn(1 , _T("Channel state"), 2, 80,-1);
		m_ListChannelState.InsertColumn(2 , _T("Channel hardware status"), 2, 80,-1);
		m_ListChannelState.InsertColumn(3 , _T("The actual rate"), 2, 80, -1);
		m_ListChannelState.InsertColumn(4 , _T("Voice channel state"), 2, 80, -1);
		m_ListChannelState.InsertColumn(5 , _T("Alarm input state"), 2, 80, -1);
		m_ListChannelState.InsertColumn(6 , _T("Alarm output status"), 2, 80, -1);
	}


	return TRUE;
}


void CDeviceState::ShowWndData()
{
	m_DeviceState.SetCurSel(m_DevWorkState.device_static);

	int iIndex = -1;
	CString strText = _T("");
	m_LocalShow.SetCurSel(m_DevWorkState.local_display);



	strText = _T("");
	m_ListDiskState.DeleteAllItems();
	for(int i = 0; i< J_SDK_MAX_DISK_NUMBER; i++)
	{
		if(m_DevWorkState.hd_static[i].volume <= 0)
		{
			break;
		}
		strText.Format(_T("%d"),m_DevWorkState.hd_static[i].volume);
		m_ListDiskState.InsertItem(i, strText);
		strText.Format(_T("%d"),m_DevWorkState.hd_static[i].free_space);
		m_ListDiskState.SetItemText(i, 1, strText);

		if(m_DevWorkState.hd_static[i].hd_static == 0)
		{
			strText = _T("正在使用");
		}
		else if(m_DevWorkState.hd_static[i].hd_static == 1)
		{
			strText = _T("未挂载");
		}
		else if(m_DevWorkState.hd_static[i].hd_static == 2)
		{
			strText = _T("已挂载未使用");
		}
		m_ListDiskState.SetItemText(i, 2, strText);
	}
	/*uint8_t  record_static;						//通道是否在录像：0－不录像；1－录像 
	uint8_t  signal_static;						//连接的信号状态：0－正常，  1－信号丢失  
	uint8_t  hardware_static;					//通道硬件状态：  0－正常，  1－异常（例如DSP异常） 
	uint8_t  res1;
	uint32_t bit_rate[J_SDK_MAX_STREAM_SIZE];	//实际码率 */
	m_ListChannelState.DeleteAllItems();
	for(int i = 0; i< J_SDK_MAX_CHN_SIZE; i++)
	{
		if(i > 0)
		{
			break;
		}
		if(m_DevWorkState.chn_static[i].record_static == 0)
		{
			strText = _T("否");
		}
		else if(m_DevWorkState.chn_static[i].record_static == 1)
		{
			strText = _T("是");
		}
		m_ListChannelState.InsertItem(i, strText);
		//strText.Format(_T("%d"), m_DevWorkState.chn_static[i].signal_static);
		if(m_DevWorkState.chn_static[i].signal_static == 0)
		{
			strText = _T("正常");
		}
		else if(m_DevWorkState.chn_static[i].signal_static == 1)
		{
			strText = _T("信号丢失");
		}
		m_ListChannelState.SetItemText(i, 1, strText);
		if(m_DevWorkState.chn_static[i].hardware_static == 0)
		{
			strText = _T("正常");
		}
		else if(m_DevWorkState.chn_static[i].hardware_static == 1)
		{
			strText = _T("异常");
		}
		m_ListChannelState.SetItemText(i, 2, strText);

		int iIndex = g_PubData.g_iStreamType[g_PubData.g_iAttributeIng];
		strText.Format(_T("%d"), m_DevWorkState.chn_static[i].bit_rate[iIndex-1]);
		m_ListChannelState.SetItemText(i, 3, strText);

		strText.Format(_T("%d"), m_DevWorkState.audio_chn_status[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("未使用");
		}
		else if(iIndex == 1)
		{
			strText = _T("使用中");
		}
		else if(iIndex == 0xff)
		{
			strText = _T("无效");
		}
		m_ListChannelState.SetItemText(i, 4, strText);

		strText.Format(_T("%d"), m_DevWorkState.alarm_in_static[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("没有报警");
		}
		else if(iIndex == 1)
		{
			strText = _T("有报警");
		}
		m_ListChannelState.SetItemText(i, 5, strText);

		strText.Format(_T("%d"), m_DevWorkState.alarm_out_static[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("没有报警");
		}
		else if(iIndex == 1)
		{
			strText = _T("有报警");
		}
		m_ListChannelState.SetItemText(i, 6, strText);

	}
}

void CDeviceState::ShowWndDataEnglish()
{
	m_DeviceState.SetCurSel(m_DevWorkState.device_static);

	int iIndex = -1;
	CString strText = _T("");
	m_LocalShow.SetCurSel(m_DevWorkState.local_display);



	strText = _T("");
	m_ListDiskState.DeleteAllItems();
	for(int i = 0; i< J_SDK_MAX_DISK_NUMBER; i++)
	{
		if(m_DevWorkState.hd_static[i].volume <= 0)
		{
			break;
		}
		strText.Format(_T("%d"),m_DevWorkState.hd_static[i].volume);
		m_ListDiskState.InsertItem(i, strText);
		strText.Format(_T("%d"),m_DevWorkState.hd_static[i].free_space);
		m_ListDiskState.SetItemText(i, 1, strText);

		if(m_DevWorkState.hd_static[i].hd_static == 0)
		{
			strText = _T("Is in use");
		}
		else if(m_DevWorkState.hd_static[i].hd_static == 1)
		{
			strText = _T("Unmounted");
		}
		else if(m_DevWorkState.hd_static[i].hd_static == 2)
		{
			strText = _T("The unused");
		}
		m_ListDiskState.SetItemText(i, 2, strText);
	}
	/*uint8_t  record_static;						//通道是否在录像：0－不录像；1－录像 
	uint8_t  signal_static;						//连接的信号状态：0－正常，  1－信号丢失  
	uint8_t  hardware_static;					//通道硬件状态：  0－正常，  1－异常（例如DSP异常） 
	uint8_t  res1;
	uint32_t bit_rate[J_SDK_MAX_STREAM_SIZE];	//实际码率 */
	m_ListChannelState.DeleteAllItems();
	for(int i = 0; i< J_SDK_MAX_CHN_SIZE; i++)
	{
		if(i > 0)
		{
			break;
		}
		if(m_DevWorkState.chn_static[i].record_static == 0)
		{
			strText = _T("No");
		}
		else if(m_DevWorkState.chn_static[i].record_static == 1)
		{
			strText = _T("Yes");
		}
		m_ListChannelState.InsertItem(i, strText);
		//strText.Format(_T("%d"), m_DevWorkState.chn_static[i].signal_static);
		if(m_DevWorkState.chn_static[i].signal_static == 0)
		{
			strText = _T("Normal");
		}
		else if(m_DevWorkState.chn_static[i].signal_static == 1)
		{
			strText = _T("Loss of signal");
		}
		m_ListChannelState.SetItemText(i, 1, strText);
		if(m_DevWorkState.chn_static[i].hardware_static == 0)
		{
			strText = _T("Normal");
		}
		else if(m_DevWorkState.chn_static[i].hardware_static == 1)
		{
			strText = _T("Abnormal");
		}
		m_ListChannelState.SetItemText(i, 2, strText);

		int iIndex = g_PubData.g_iStreamType[g_PubData.g_iAttributeIng];
		strText.Format(_T("%d"), m_DevWorkState.chn_static[i].bit_rate[iIndex-1]);
		m_ListChannelState.SetItemText(i, 3, strText);

		strText.Format(_T("%d"), m_DevWorkState.audio_chn_status[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("Not used");
		}
		else if(iIndex == 1)
		{
			strText = _T("In use");
		}
		else if(iIndex == 0xff)
		{
			strText = _T("Invalid");
		}
		m_ListChannelState.SetItemText(i, 4, strText);

		strText.Format(_T("%d"), m_DevWorkState.alarm_in_static[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("No alarm");
		}
		else if(iIndex == 1)
		{
			strText = _T("Alarm");
		}
		m_ListChannelState.SetItemText(i, 5, strText);

		strText.Format(_T("%d"), m_DevWorkState.alarm_out_static[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("No alarm");
		}
		else if(iIndex == 1)
		{
			strText = _T("Alarm");
		}
		m_ListChannelState.SetItemText(i, 6, strText);

	}
}
void CDeviceState::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代

	int iRet = -1;

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DEV_WORK_STATE, (char *)&m_DevWorkState, sizeof(m_DevWorkState),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	if(g_PubData.g_iLanguageFlag == 0)
	{
		ShowWndData();
	}
	else
	{
		ShowWndDataEnglish();
	}
	
}

void CDeviceState::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDeviceState::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
