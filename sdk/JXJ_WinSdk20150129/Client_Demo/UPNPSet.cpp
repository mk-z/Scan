// UPNPSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "UPNPSet.h"
#include "Pub_Data.h"


// CUPNPSet 对话框



IMPLEMENT_DYNAMIC(CUPNPSet, CDialog)

CUPNPSet::CUPNPSet(CWnd* pParent /*=NULL*/)
	: CDialog(CUPNPSet::IDD, pParent)
{

}

CUPNPSet::~CUPNPSet()
{
	DestroyWindow();
}

void CUPNPSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_STARTUPNP, m_StartUpnp);
	DDX_Control(pDX, IDC_COMBO_SHINETYPE, m_ShineType);
	DDX_Control(pDX, IDC_EDIT_SERVERIP, m_SerVerIp);
	DDX_Control(pDX, IDC_COMBO_NETCARDSHINE, m_NetCardShine);
	DDX_Control(pDX, IDC_EDIT_DATA_PORT, m_DataPORT);
	DDX_Control(pDX, IDC_EDIT_WEBPORT, m_WebPort);
	DDX_Control(pDX, IDC_COMBO_UPNPUPDATETIME, m_UPNPUpdateTime);
	DDX_Control(pDX, IDC_EDIT_TALK_PORT, m_UPNPTalkPort);
	DDX_Control(pDX, IDC_EDIT_CMD_PORT, m_UPNPCmdPort);
	DDX_Control(pDX, IDC_EDIT_DATA_STATUS, m_DataStatus);
	DDX_Control(pDX, IDC_EDIT_WEB_STATUS, m_WebStatus);
	DDX_Control(pDX, IDC_EDIT_CMD_STATUS, m_CmdStatus);
	DDX_Control(pDX, IDC_EDIT_TALK_STATUS, m_TalkStatus);
}


BEGIN_MESSAGE_MAP(CUPNPSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CUPNPSet::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CUPNPSet::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CUPNPSet 消息处理程序
BOOL CUPNPSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_ShineType.AddString(_T("固定映射"));
		m_ShineType.AddString(_T("自动映射"));
		m_ShineType.EnableWindow(FALSE);

		m_NetCardShine.AddString(_T("本机网卡映射"));
		m_NetCardShine.AddString(_T("无限网卡映射"));
	}
	else
	{
		m_ShineType.AddString(_T("A fixed mapping"));
		m_ShineType.AddString(_T("Automatic mapping"));
		m_ShineType.EnableWindow(FALSE);

		m_NetCardShine.AddString(_T("The machine card mapping"));
		m_NetCardShine.AddString(_T("Wireless network mapping"));
		
	}
	


	m_DataStatus.EnableWindow(FALSE);
	m_WebStatus.EnableWindow(FALSE);
	m_CmdStatus.EnableWindow(FALSE);
	m_TalkStatus.EnableWindow(FALSE);

	


	for(int i = 1; i< 49; i++)
	{
		CString str(_T(""));
		str.Format(_T("%d"), i);
		m_UPNPUpdateTime.AddString(str);
	}


//	OnBnClickedButtonFlash();

	return TRUE;
}


void CUPNPSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码


	CString strText(_T(""));

	m_upnpParam.upnp_enable = m_StartUpnp.GetCheck();

	m_upnpParam.upnp_model = m_ShineType.GetCurSel();

	m_SerVerIp.GetWindowText(strText);
	memset(m_upnpParam.upnp_ip, '\0', sizeof(m_upnpParam.upnp_ip));
	memcpy(m_upnpParam.upnp_ip, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_upnpParam.upnp_eth_no = m_NetCardShine.GetCurSel();

	m_DataPORT.GetWindowText(strText);
	m_upnpParam.upnp_data_port = _ttoi(strText);

	m_DataStatus.GetWindowText(strText);
	m_upnpParam.upnp_data_port_result = _ttoi(strText);

	m_WebPort.GetWindowText(strText);
	m_upnpParam.upnp_web_port = _ttoi(strText);

	m_WebStatus.GetWindowText(strText);
	m_upnpParam.upnp_web_port_result = _ttoi(strText);

	m_upnpParam.upnp_refresh_time = m_UPNPUpdateTime.GetCurSel();

	m_UPNPCmdPort.GetWindowText(strText);
	m_upnpParam.upnp_cmd_port = _ttoi(strText);

	m_UPNPTalkPort.GetWindowText(strText);
	m_upnpParam.upnp_talk_port = _ttoi(strText);

	m_CmdStatus.GetWindowText(strText);
	m_upnpParam.upnp_cmd_port_result = _ttoi(strText);

	m_TalkStatus.GetWindowText(strText);
	m_upnpParam.upnp_talk_port_result = _ttoi(strText);

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_UPNP_INFO, (char *)&m_upnpParam, sizeof(m_upnpParam), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}
	
}


void CUPNPSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_UPNP_INFO, (char *)&m_upnpParam, sizeof(m_upnpParam),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshWindow();
}


int CUPNPSet::ReFreshWindow()
{    

	CString strText(_T(""));

	m_StartUpnp.SetCheck(m_upnpParam.upnp_enable);
	m_ShineType.SetCurSel(m_upnpParam.upnp_model);

	strText.Format(_T("%s"),m_upnpParam.upnp_ip);
	m_SerVerIp.SetWindowText(strText);

	m_NetCardShine.SetCurSel(m_upnpParam.upnp_eth_no);

	strText.Format(_T("%d"), m_upnpParam.upnp_data_port);
	m_DataPORT.SetWindowText(strText);

	strText.Format(_T("%d"), m_upnpParam.upnp_data_port_result);
	m_DataStatus.SetWindowText(strText);

	strText.Format(_T("%d"), m_upnpParam.upnp_web_port);
	m_WebPort.SetWindowText(strText);

	strText.Format(_T("%d"), m_upnpParam.upnp_web_port_result);
	m_WebStatus.SetWindowText(strText);

	m_UPNPUpdateTime.SetCurSel(m_upnpParam.upnp_refresh_time);

	strText.Format(_T("%d"), m_upnpParam.upnp_cmd_port);
	m_UPNPCmdPort.SetWindowText(strText);

	strText.Format(_T("%d"),m_upnpParam.upnp_talk_port);
	m_UPNPTalkPort.SetWindowText(strText);

	strText.Format(_T("%d"), m_upnpParam.upnp_cmd_port_result);
	m_CmdStatus.SetWindowText(strText);

	strText.Format(_T("%d"), m_upnpParam.upnp_talk_port_result);
	m_TalkStatus.SetWindowText(strText);

	return 0;
}
void CUPNPSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
