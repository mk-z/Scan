// NetStatus.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "NetStatus.h"
#include "Pub_Data.h"

// CNetStatus 对话框



IMPLEMENT_DYNAMIC(CNetStatus, CDialog)

CNetStatus::CNetStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CNetStatus::IDD, pParent)
{

}

CNetStatus::~CNetStatus()
{
	DestroyWindow();
}

void CNetStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LIMITNETSTATUS, m_LimitStatus);
	DDX_Control(pDX, IDC_COMBO_WIRELESSSATUS, m_WireLessStatus);
	DDX_Control(pDX, IDC_COMBO_PPPOESTATUS, m_PppoeStatus);
}


BEGIN_MESSAGE_MAP(CNetStatus, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CNetStatus::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CNetStatus::OnBnClickedButtonSave)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CNetStatus 消息处理程序
BOOL CNetStatus::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_LimitStatus.AddString(_T("无连接"));
		m_LimitStatus.AddString(_T("正在连接"));
		m_LimitStatus.AddString(_T("成功"));

		m_WireLessStatus.AddString(_T("无连接"));
		m_WireLessStatus.AddString(_T("正在连接"));
		m_WireLessStatus.AddString(_T("成功"));

		m_PppoeStatus.AddString(_T("无连接"));
		m_PppoeStatus.AddString(_T("正在连接"));
		m_PppoeStatus.AddString(_T("成功"));
	}
	else
	{
		m_LimitStatus.AddString(_T("No connection"));
		m_LimitStatus.AddString(_T("Connecting to"));
		m_LimitStatus.AddString(_T("Success"));

		m_WireLessStatus.AddString(_T("No connection"));
		m_WireLessStatus.AddString(_T("Connecting to"));
		m_WireLessStatus.AddString(_T("Success"));

		m_PppoeStatus.AddString(_T("No connection"));
		m_PppoeStatus.AddString(_T("Connecting to"));
		m_PppoeStatus.AddString(_T("Success"));
	}
	

	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

	return TRUE;
}

void CNetStatus::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_NETWORK_STATUS, (char *)&m_netStatus, sizeof(m_netStatus),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}
	ReFreshWindow();
}

void CNetStatus::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
}

int CNetStatus::ReFreshWindow()
{

	m_LimitStatus.SetCurSel(m_netStatus.eth_st);
	m_WireLessStatus.SetCurSel(m_netStatus.wifi_st);
	m_PppoeStatus.SetCurSel(m_netStatus.pppoe_st);
	return 0;
}

void CNetStatus::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
