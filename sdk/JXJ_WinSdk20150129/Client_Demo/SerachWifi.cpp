// SerachWifi.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "SerachWifi.h"
#include "Pub_Data.h"
#include "WifiConnect.h"


// CSerachWifi 对话框


IMPLEMENT_DYNAMIC(CSerachWifi, CDialog)

CSerachWifi::CSerachWifi(CWnd* pParent /*=NULL*/)
	: CDialog(CSerachWifi::IDD, pParent)
{
	m_WifiState			= -1;  
	m_wifiPassword		= _T("");
	m_strSid			= _T("");
}

CSerachWifi::~CSerachWifi()
{
	DestroyWindow();
}

void CSerachWifi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WIFI, m_WifiList);
}


BEGIN_MESSAGE_MAP(CSerachWifi, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSerachWifi::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CSerachWifi::OnBnClickedButtonFlash)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_WIFI, &CSerachWifi::OnNMDblclkListWifi)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSerachWifi 消息处理程序
BOOL CSerachWifi::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_WifiList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
	m_WifiList.InsertColumn(0 , _T("服务区号"), 2, 100, -1);
	m_WifiList.InsertColumn(1 , _T("加密类型"), 2, 100,-1);
	m_WifiList.InsertColumn(2 , _T("认证方式"), 2, 100,-1);
	m_WifiList.InsertColumn(3 , _T("密钥管理方式"), 2, 100, -1);
	m_WifiList.InsertColumn(4 , _T("信号质量"), 2, 100, -1);
	m_WifiList.InsertColumn(5 , _T("传输速率"), 2, 100, -1);

	return TRUE;
}

void CSerachWifi::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CSerachWifi::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码

	if(g_PubData.g_jDevCap->cap0 & DEV_CAP_WIFI)
	{
		m_WifiList.DeleteAllItems();
		int iRet = -1;
		iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_WIFI_SEARCH, (char *)&m_wifiSerach, sizeof(m_wifiSerach),NULL, NULL );
		if( iRet != 0)
		{
			//AfxMessageBox(_T("搜索wifi失败"));
			return;
		}

		ReFreshWifiWindow();
	}
	else
	{
		//AfxMessageBox(_T("设备不支持wifi"));
		GetDlgItem(IDC_BUTTON_FLASH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
		return;
	}
}

int CSerachWifi::ReFreshWifiWindow()
{
	
	CString strText = _T("");
	for(int i = 0; i< (int)m_wifiSerach.count; i++)
	{
		strText.Format(_T("%s"), m_wifiSerach.wifi_ap[i].essid);
		m_WifiList.InsertItem(i, strText);
		if(m_wifiSerach.wifi_ap[i].encrypt_type == 0)
		{
			strText = _T("NONE");
		}
		else if(m_wifiSerach.wifi_ap[i].encrypt_type == 1)
		{
			strText = _T("WPA");
		}
		else if(m_wifiSerach.wifi_ap[i].encrypt_type == 2)
		{
			strText = _T("WPA2");
		}
		else if(m_wifiSerach.wifi_ap[i].encrypt_type == 3)
		{
			strText = _T("WEP");
		}
		m_WifiList.SetItemText(i, 1, strText);

		if(m_wifiSerach.wifi_ap[i].auth_mode == 0)
		{
			strText = _T("NONE");
		}
		else if(m_wifiSerach.wifi_ap[i].auth_mode == 1)
		{
			strText = _T("EAP");
		}
		else if(m_wifiSerach.wifi_ap[i].auth_mode == 2)
		{
			strText = _T("PSK");
		}
		else if(m_wifiSerach.wifi_ap[i].auth_mode == 3)
		{
			strText = _T("OPEN");
		}
		else if(m_wifiSerach.wifi_ap[i].auth_mode == 4)
		{
			strText = _T("SHARED");
		}
		m_WifiList.SetItemText(i, 2, strText);
		
		if(m_wifiSerach.wifi_ap[i].secret_key_type == 0)
		{
			strText = _T("NONE");
		}
		else if(m_wifiSerach.wifi_ap[i].secret_key_type == 1)
		{
			strText = _T("AES");
		}
		else if(m_wifiSerach.wifi_ap[i].secret_key_type == 2)
		{
			strText = _T("TKIP");
		}
		m_WifiList.SetItemText(i, 3, strText);

		strText.Format(_T("%d"), m_wifiSerach.wifi_ap[i].quality);
		m_WifiList.SetItemText(i, 4, strText);

		strText.Format(_T("%d"), m_wifiSerach.wifi_ap[i].bit_rate);
		m_WifiList.SetItemText(i, 5, strText);
	}
	return 0;
}
void CSerachWifi::GetWifiState()
{
	ZeroMemory(&m_wifiConfig, sizeof(JWifiConfig));

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_WIFI_INFO, (char *)&m_wifiConfig, sizeof(m_wifiConfig),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return;
	}

	ReFreshConnectWindow();

}
//控制wifi iIndex要控制的wifi  iState   wifi状态  //strPassword密码
void CSerachWifi::ControlWifi(int iIndex, int iState, CString strPassword)
{
	ZeroMemory(&m_wifiConfig, sizeof(JWifiConfig));
	memcpy(m_wifiConfig.essid,  m_wifiSerach.wifi_ap[iIndex].essid, J_SDK_MAX_ID_LEN);

	memcpy(m_wifiConfig.pwd,strPassword.GetBuffer(0), strPassword.GetLength());
	strPassword.ReleaseBuffer();
	m_wifiConfig.wifi_enable = iState;
	m_wifiConfig.encrypt_type = m_wifiSerach.wifi_ap[iIndex].encrypt_type;
	m_wifiConfig.auth_mode = m_wifiSerach.wifi_ap[iIndex].auth_mode;
	m_wifiConfig.secret_key_type = m_wifiSerach.wifi_ap[iIndex].secret_key_type	;

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_WIFI_INFO, (char *)&m_wifiConfig, sizeof(m_wifiConfig), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return;
	}
}


void CSerachWifi::OnNMDblclkListWifi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = pNMItemActivate->iItem;
	if(iIndex < 0 )
	{
		AfxMessageBox(_T("请选择一个wifi进行配置"));
		return;
	}

	
	/*uint8_t essid[J_SDK_MAX_ID_LEN];		//服务区别号
	uint8_t pwd[J_SDK_MAX_PWD_LEN];			//密码
	uint32_t wifi_enable;					//0：断开，1：连接
	uint32_t encrypt_type;					//加密类型0:NONE  1:WPA  2:WPA2 3:WEP
	uint32_t auth_mode;						//认证方式0:NONE  1:EAP 2:PSK 3:OPEN 4:SHARED 
	uint32_t secret_key_type;				//密钥管理方式 0:NONE  1:AES 2:TKIP 只对应于加密类型为WPA/WPA2的情况
	uint32_t wifi_st;						//无线网卡连接状态 0 无连接 1 正在连接2 成功*/

	GetWifiState();
	Sleep(1000);
	CString strText = m_WifiList.GetItemText(iIndex, 0);
	if(m_WifiState == 2 && m_strSid == strText)  
	{
		int iRet = -1;
		iRet = MessageBox("该信号已连接,是否断开 ？","断开询问",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL); 

		if(iRet == IDYES)
		{
			GetDlgItem(IDC_STATIC_WIFISTATE)->SetWindowText(_T("正在断开......"));
			ControlWifi(iIndex, 0, m_wifiPassword);
			Sleep(3000);
			
			GetDlgItem(IDC_STATIC_WIFISTATE)->SetWindowText(_T(""));
			AfxMessageBox(_T("已断开"));
			
		}
		return;
	}
	CWifiConnect wifiConnect;
	int iRet = wifiConnect.DoModal();
	if(iRet == IDOK)
	{
		ControlWifi(iIndex, 1, wifiConnect.m_StrPassword);
		GetDlgItem(IDC_STATIC_WIFISTATE)->SetWindowText(_T("正在连接......"));
		Sleep(7000);
		GetWifiState();
		Sleep(1000);
		if(m_WifiState == 2  && m_strSid == strText)
		{
			AfxMessageBox(_T("连接成功!"));
			GetDlgItem(IDC_STATIC_WIFISTATE)->SetWindowText(_T(""));
		}
		else
		{
			GetDlgItem(IDC_STATIC_WIFISTATE)->SetWindowText(_T(""));
			AfxMessageBox(_T("连接错误!"));	
		}
	}
	
	*pResult = 0;
}

int  CSerachWifi::ReFreshConnectWindow()
{
	m_WifiState = m_wifiConfig.wifi_st;
	m_strSid.Format(_T("%s"), m_wifiConfig.essid);
	m_wifiPassword.Format(_T("%s"), m_wifiConfig.pwd);
	return 0;
}
HBRUSH CSerachWifi::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_WIFISTATE )
 	{
 		pDC->SetTextColor(RGB(255,0,0));  //字体颜色
 		//pDC->SetBkColor(RGB(0, 0, 255));   //字体背景色  
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);  
 
 	}
 	
	return hbr;
	
}

void CSerachWifi::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
