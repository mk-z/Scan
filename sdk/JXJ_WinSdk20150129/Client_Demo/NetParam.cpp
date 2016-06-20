// NetParam.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "NetParam.h"
#include "Pub_Data.h"


// CNetParam 对话框


IMPLEMENT_DYNAMIC(CNetParam, CDialog)

CNetParam::CNetParam(CWnd* pParent /*=NULL*/)
	: CDialog(CNetParam::IDD, pParent)
{

}

CNetParam::~CNetParam()
{
	DestroyWindow();
}

void CNetParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SIGNPORT, m_SignPort);
	DDX_Control(pDX, IDC_COMBO_NETWORKCARDING, m_NetWorkCarding);
	DDX_Control(pDX, IDC_EDIT_DATAPORT, m_DataPort);
	DDX_Control(pDX, IDC_EDIT_WEBPORT, m_WebPort);
	DDX_Control(pDX, IDC_COMBO_NETWORKTYPE, m_NetWorkType);
	DDX_Control(pDX, IDC_EDIT_MACADDRESS, m_MacAddress);
	DDX_Control(pDX, IDC_CHECK_STARTDHCP, m_StartDhcp);
	DDX_Control(pDX, IDC_EDIT_IPADDR, m_IpAddr);
	DDX_Control(pDX, IDC_EDIT_CHILDNET, m_ChildNet);
	DDX_Control(pDX, IDC_EDIT_NETADDRESS, m_NetAddr);
	DDX_Control(pDX, IDC_CHECK_STARTAUTODNS, m_StartAtupDns);
	DDX_Control(pDX, IDC_EDIT_MAINDNS, m_MainDns);
	DDX_Control(pDX, IDC_EDIT_BACKUPDNS, m_BackUpDns);
	DDX_Control(pDX, IDC_CHECKSTARTTERRACE, m_StartTerrace);
	DDX_Control(pDX, IDC_EDIT_CMSADDR, m_CmsAddr);
	DDX_Control(pDX, IDC_EDIT_CMSPORT, m_CmsPort);
	DDX_Control(pDX, IDC_EDIT_PUID, m_Puid);
	DDX_Control(pDX, IDC_COMBO_TRANSPROTOCOL, m_TransProtocol);
	DDX_Control(pDX, IDC_EDIT_MDSADDR, m_MdsAddr);
	DDX_Control(pDX, IDC_EDIT_MDSPORT, m_MdsPort);
	DDX_Control(pDX, IDC_EDIT_TALKPORT, m_TalkPort);
}


BEGIN_MESSAGE_MAP(CNetParam, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CNetParam::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CNetParam::OnBnClickedButtonSave)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CNetParam 消息处理程序
BOOL CNetParam::OnInitDialog()
{
	CDialog::OnInitDialog();


	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_NetWorkCarding.AddString(_T("以太网"));
		m_NetWorkCarding.AddString(_T("WIFI"));
		m_NetWorkCarding.AddString(_T("3G"));
		m_NetWorkCarding.EnableWindow(FALSE);

		m_NetWorkType.AddString(_T("以太网"));
		m_NetWorkType.AddString(_T("WIFI"));
		m_NetWorkType.AddString(_T("3G"));

		m_TransProtocol.AddString(_T("TCP"));
		m_TransProtocol.AddString(_T("UDP"));
		m_TransProtocol.EnableWindow(FALSE);

	}
	else
	{
		m_NetWorkCarding.AddString(_T("Ethernet"));
		m_NetWorkCarding.AddString(_T("WIFI"));
		m_NetWorkCarding.AddString(_T("3G"));
		m_NetWorkCarding.EnableWindow(FALSE);

		m_NetWorkType.AddString(_T("Ethernet"));
		m_NetWorkType.AddString(_T("WIFI"));
		m_NetWorkType.AddString(_T("3G"));

		m_TransProtocol.AddString(_T("TCP"));
		m_TransProtocol.AddString(_T("UDP"));
		m_TransProtocol.EnableWindow(FALSE);

	}
	

//	OnBnClickedButtonFlash();
	
	return TRUE;
}

void CNetParam::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码


	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_NETWORK_INFO, (char *)&m_networkinfo, sizeof(m_networkinfo),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}

	iRet = -1;

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PLATFORM_INFO, (char *)&m_platform, sizeof(m_platform),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshWindow1();
	ReFreshWindow2();

}

void CNetParam::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strText(_T(""));

	m_networkinfo.cur_network = m_NetWorkCarding.GetCurSel();

	m_SignPort.GetWindowText(strText);
	m_networkinfo.cmd_port = _ttoi(strText);

	m_DataPort.GetWindowText(strText);
	m_networkinfo.data_port = _ttoi(strText);

	m_WebPort.GetWindowText(strText);
	m_networkinfo.web_port = _ttoi(strText);

	m_TalkPort.GetWindowText(strText);
	m_networkinfo.talk_port = _ttoi(strText);

	m_networkinfo.network->type = m_NetWorkType.GetCurSel();

	m_MacAddress.GetWindowText(strText);
	memset(m_networkinfo.network->mac, '\0', sizeof(m_networkinfo.network->mac));
	memcpy(m_networkinfo.network->mac, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_networkinfo.network->dhcp_enable = m_StartDhcp.GetCheck();

	m_IpAddr.GetWindowText(strText);
	memset(m_networkinfo.network->ip, '\0', sizeof(m_networkinfo.network->ip));
	memcpy(m_networkinfo.network->ip, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_ChildNet.GetWindowText(strText);
	memset(m_networkinfo.network->netmask, '\0', sizeof(m_networkinfo.network->netmask));
	memcpy(m_networkinfo.network->netmask, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_NetAddr.GetWindowText(strText);
	memset(m_networkinfo.network->gateway, '\0', sizeof(m_networkinfo.network->gateway));
	memcpy(m_networkinfo.network->gateway, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_networkinfo.auto_dns_enable = m_StartAtupDns.GetCheck();

	m_MainDns.GetWindowText(strText);
	memset(m_networkinfo.main_dns, '\0', sizeof(m_networkinfo.main_dns));
	memcpy(m_networkinfo.main_dns, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_BackUpDns.GetWindowText(strText);
	memset(m_networkinfo.backup_dns, '\0', sizeof(m_networkinfo.backup_dns));
	memcpy(m_networkinfo.backup_dns, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_NETWORK_INFO, (char *)&m_networkinfo, sizeof(m_networkinfo), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return ;
	}
	
	m_platform.is_con_cms = m_StartTerrace.GetCheck();

	m_CmsAddr.GetWindowText(strText);
	memset(m_platform.cms_ip, '\0', sizeof(m_platform.cms_ip));
	memcpy(m_platform.cms_ip, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_CmsPort.GetWindowText(strText);
	m_platform.cms_port = _ttoi(strText);

	m_MdsAddr.GetWindowText(strText);
	memset(m_platform.mds_ip, '\0', sizeof(m_platform.mds_ip));
	memcpy(m_platform.mds_ip, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_MdsPort.GetWindowText(strText);
	m_platform.mds_port = _ttoi(strText);

	m_Puid.GetWindowText(strText);
	memset(m_platform.pu_id, '\0', sizeof(m_platform.pu_id));
	memcpy(m_platform.pu_id, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_platform.protocol = m_TransProtocol.GetCurSel();

	iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PLATFORM_INFO, (char *)&m_platform, sizeof(m_platform), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}

}


int CNetParam::ReFreshWindow1()
{
	
	CString strText(_T(""));

	m_StartTerrace.SetCheck(m_platform.is_con_cms);

	strText.Format(_T("%s"), m_platform.cms_ip);
	m_CmsAddr.SetWindowText(strText);

	strText.Format(_T("%d"), m_platform.cms_port);
	m_CmsPort.SetWindowText(strText);

	strText.Format(_T("%s"), m_platform.mds_ip);
	m_MdsAddr.SetWindowText(strText);

	strText.Format(_T("%d"), m_platform.mds_port);
	m_MdsPort.SetWindowText(strText);

	strText.Format(_T("%s"), m_platform.pu_id);
	m_Puid.SetWindowText(strText);

	m_TransProtocol.SetCurSel(m_platform.protocol);
	return 0;
}
int CNetParam::ReFreshWindow2()
{
	
	CString strText = _T("");

	m_NetWorkCarding.SetCurSel(m_networkinfo.cur_network);

	strText.Format(_T("%d"),m_networkinfo.cmd_port);
	m_SignPort.SetWindowText(strText);

	strText.Format(_T("%d"), m_networkinfo.data_port);
	m_DataPort.SetWindowText(strText);

	strText.Format(_T("%d"), m_networkinfo.web_port);
	m_WebPort.SetWindowText(strText);

	strText.Format(_T("%d"), m_networkinfo.talk_port);
	m_TalkPort.SetWindowText(strText);

	m_NetWorkType.SetCurSel(m_networkinfo.network->type);

	strText.Format(_T("%s"), m_networkinfo.network->mac);
	m_MacAddress.SetWindowText(strText);

	m_StartDhcp.SetCheck(m_networkinfo.network->dhcp_enable);

	strText.Format(_T("%s"), m_networkinfo.network->ip);
	m_IpAddr.SetWindowText(strText);

	strText.Format(_T("%s"), m_networkinfo.network->netmask);
	m_ChildNet.SetWindowText(strText);

	strText.Format(_T("%s"), m_networkinfo.network->gateway);
	m_NetAddr.SetWindowText(strText);

	m_StartAtupDns.SetCheck(m_networkinfo.auto_dns_enable);

	strText.Format(_T("%s"), m_networkinfo.main_dns);
	m_MainDns.SetWindowText(strText);

	strText.Format(_T("%s"), m_networkinfo.backup_dns);
	m_BackUpDns.SetWindowText(strText);

	return 0;
}

void CNetParam::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
