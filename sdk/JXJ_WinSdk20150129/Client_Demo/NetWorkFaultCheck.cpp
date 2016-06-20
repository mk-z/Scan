// NetWorkFaultCheck.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "NetWorkFaultCheck.h"
#include "Pub_Data.h"

// CNetWorkFaultCheck 对话框


IMPLEMENT_DYNAMIC(CNetWorkFaultCheck, CDialog)

CNetWorkFaultCheck::CNetWorkFaultCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CNetWorkFaultCheck::IDD, pParent)
{

}

CNetWorkFaultCheck::~CNetWorkFaultCheck()
{
	DestroyWindow();
}

void CNetWorkFaultCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_StartNetWorkFault, m_StartNetWorkFault);
	DDX_Control(pDX, IDC_CHECK_StartWifi, m_StartWifi);
	DDX_Control(pDX, IDC_CHECK_Start3G, m_Start3G);
	DDX_Control(pDX, IDC_COMBO_CABLENETWORK, m_CableNetWork);
	DDX_Control(pDX, IDC_CHECK_STARTCABLE, m_StartCableNetWork);
	DDX_Control(pDX, IDC_CHECK_StartAllCable, m_StartAllCableNetWork);
}


BEGIN_MESSAGE_MAP(CNetWorkFaultCheck, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CNetWorkFaultCheck::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CNetWorkFaultCheck::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_CHECK_StartNetWorkFault, &CNetWorkFaultCheck::OnBnClickedCheckStartnetworkfault)
	ON_CBN_SELCHANGE(IDC_COMBO_CABLENETWORK, &CNetWorkFaultCheck::OnCbnSelchangeComboCablenetwork)
	ON_BN_CLICKED(IDC_CHECK_StartAllCable, &CNetWorkFaultCheck::OnBnClickedCheckStartallcable)
END_MESSAGE_MAP()


// CNetWorkFaultCheck 消息处理程序
BOOL CNetWorkFaultCheck::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_StartWifi.EnableWindow(FALSE);
	m_Start3G.EnableWindow(FALSE);
	m_CableNetWork.EnableWindow(FALSE);
	m_StartCableNetWork.EnableWindow(FALSE);
	m_StartAllCableNetWork.EnableWindow(FALSE);

	CString strText;
	if(g_PubData.g_iLanguageFlag == 0)
		strText = _T("有限网卡");
	else
		strText = _T("Limited network");
	for(int i =0; i < g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].eth_num; i++)
	{
		CString str = _T("");
		str.Format(_T("%d"),i);
		strText += str;
		m_CableNetWork.AddString(strText);
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].eth_num > 0)
	{
		m_CableNetWork.SetCurSel(0);
	}

	return TRUE;
}

void CNetWorkFaultCheck::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	m_NetWorkFault.check_enable = m_StartNetWorkFault.GetCheck();
	int iNum = g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].eth_num;  //设备能力集获取的有限网卡个数
	if(iNum <= 1)
	{
		m_NetWorkFault.check_net_cards[1] = m_StartWifi.GetCheck();
		m_NetWorkFault.check_net_cards[2] = m_Start3G.GetCheck();
	}
	else
	{
		m_NetWorkFault.check_net_cards[iNum] = m_StartWifi.GetCheck();
		m_NetWorkFault.check_net_cards[iNum + 1] = m_Start3G.GetCheck();
	}
	if(m_StartAllCableNetWork.GetCheck() == 1)  //有线网卡全部启用
	{
		for(int i = 0; i< iNum; i++)
		{
			m_NetWorkFault.check_net_cards[i] = 1;
		}
	}
	else
	{
		int iIndex = m_CableNetWork.GetCurSel();
		m_NetWorkFault.check_net_cards[iIndex] = m_StartCableNetWork.GetCheck();
	}
	int iRet = -1;
	
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_NETWORKFAULTCHECK, (char *)&m_NetWorkFault, sizeof(m_NetWorkFault), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return;
	}
}

void CNetWorkFaultCheck::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 & DEV_CAP_NETWORK_FAULT)
	{
		GetDlgItem(IDC_BUTTON_FLASH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
		int iRet = -1;
;
		iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_NETWORKFAULTCHECK, (char *)&m_NetWorkFault, sizeof(m_NetWorkFault),NULL, NULL );
		if( iRet != 0)
		{
			AfxMessageBox(g_PubData.g_strGetMessage);
			return;
		}

		ReFreshWindow();
	}
	else 
	{
		//AfxMessageBox(_T("设备不支持网络故障检测"));
		GetDlgItem(IDC_BUTTON_FLASH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
		return;
	}
}

int CNetWorkFaultCheck::ReFreshWindow()
{
	
	
	m_StartNetWorkFault.SetCheck(m_NetWorkFault.check_enable);
	int iIndex = g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].eth_num;
	if(iIndex < 1)
	{
		iIndex += 1;
	}
	else
	{
		m_StartCableNetWork.SetCheck(m_NetWorkFault.check_net_cards[0]);
	}
	m_StartWifi.SetCheck(m_NetWorkFault.check_net_cards[iIndex]);
	m_Start3G.SetCheck(m_NetWorkFault.check_net_cards[iIndex + 1]);
	OnBnClickedCheckStartnetworkfault();
	return 0;
}



void CNetWorkFaultCheck::OnBnClickedCheckStartnetworkfault()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_StartNetWorkFault.GetCheck() == 1)
	{
		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 & DEV_CAP_WIFI) //根据能力集判断是否具有改功能
		{
			m_StartWifi.EnableWindow(TRUE);
		}
		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 & DEV_CAP_3G)
		{
			m_Start3G.EnableWindow(TRUE);
		}
		if(m_CableNetWork.GetCurSel() >= 0)
		{
			m_CableNetWork.EnableWindow(TRUE);
			m_StartCableNetWork.EnableWindow(TRUE);
			m_StartAllCableNetWork.EnableWindow(TRUE);
		}
	}
	else
	{
		m_StartWifi.EnableWindow(FALSE);
		m_Start3G.EnableWindow(FALSE);
		m_CableNetWork.EnableWindow(FALSE);
		m_StartCableNetWork.EnableWindow(FALSE);
		m_StartAllCableNetWork.EnableWindow(FALSE);
	}
}

void CNetWorkFaultCheck::OnCbnSelchangeComboCablenetwork()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_CableNetWork.GetCurSel();
	m_StartCableNetWork.SetCheck(m_NetWorkFault.check_net_cards[iIndex]);
}

void CNetWorkFaultCheck::OnBnClickedCheckStartallcable()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_StartAllCableNetWork.GetCheck() == 1)
	{
		m_StartCableNetWork.SetCheck(0);
	}
}
