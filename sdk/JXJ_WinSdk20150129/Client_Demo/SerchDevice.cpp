// SerchDevice.cpp : 实现文件
//
#include "stdafx.h"
#include "Client_Demo.h"
#include "SerchDevice.h"
#include "Pub_Data.h"
#include "Client_DemoDlg.h"
//搜索回调


int gDevCount = 0;

// CSerchDevice 对话框

IMPLEMENT_DYNAMIC(CSerchDevice, CDialog)

CSerchDevice::CSerchDevice(CWnd* pParent /*=NULL*/)
	: CDialog(CSerchDevice::IDD, pParent)
{
	m_bIsAdd = false;
	m_bSerachDevice = FALSE;
	m_hBhandle = NULL;
}

CSerchDevice::~CSerchDevice()
{
	if(m_hBhandle)
	{
		int iRet = -1;
		iRet = JNetMBClose(m_hBhandle);
		if( 0 != iRet )
		{
			AfxMessageBox( _T("JNetMBClose error!"));
		}
	}
	
}

void CSerchDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_listSerchDevice);
	DDX_Control(pDX, IDC_EDIT_DEVICENAME, m_eDeviceName);
	DDX_Control(pDX, IDC_EDIT_DEVICE_IP, m_eDeviceIp);
	DDX_Control(pDX, IDC_EDIT_DEVICE_PORT, m_eDevicePort);
	DDX_Control(pDX, IDC_EDIT_USER_NAME, m_eUserName);
	DDX_Control(pDX, IDC_EDIT_USER_PASSWORD, m_eUserPassword);
}


BEGIN_MESSAGE_MAP(CSerchDevice, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SERACHDEVICE, &CSerchDevice::OnBnClickedButtonSerachdevice)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DEVICE, &CSerchDevice::OnNMDblclkListDevice)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSerchDevice::OnBnClickedButtonSave)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_DEVICE, &CSerchDevice::OnLvnColumnclickListDevice)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_LIST_DEVICE, &CSerchDevice::OnNMClickListDevice)
END_MESSAGE_MAP()
BOOL CSerchDevice::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_listSerchDevice.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_listSerchDevice.InsertColumn(0 , _T("设备ID"), 2, 100, -1);
		m_listSerchDevice.InsertColumn(1 , _T("设备类型"), 2, 100,-1);
		m_listSerchDevice.InsertColumn(2 , _T("设备版本"), 2, 100,-1);
		m_listSerchDevice.InsertColumn(3 , _T("设备IP"), 2, 100, -1);
		m_listSerchDevice.InsertColumn(4 , _T("设备MAC"), 2, 100, -1);
	}
	else
	{
		m_listSerchDevice.InsertColumn(0 , _T("ID"), 2, 100, -1);
		m_listSerchDevice.InsertColumn(1 , _T("Type"), 2, 100,-1);
		m_listSerchDevice.InsertColumn(2 , _T("Version"), 2, 100,-1);
		m_listSerchDevice.InsertColumn(3 , _T("IP"), 2, 100, -1);
		m_listSerchDevice.InsertColumn(4 , _T("MAC"), 2, 100, -1);
	}
	

	m_eUserName.SetWindowText(_T("admin"));
	m_eUserPassword.SetWindowText(_T("admin"));
	m_eDevicePort.SetWindowText(_T("3321"));


	m_eDeviceIp.SetWindowText(_T(""));
	m_eDeviceName.EnableWindow(FALSE);
	return true;
}

DWORD CSerchDevice::SerachDeviceClose(LPVOID lpThreadParameter)
{

	CSerchDevice *pDlg = (CSerchDevice *)lpThreadParameter;
	Sleep(5000);

	if(NULL == pDlg->m_hBhandle)
	{
		return 0;
	}
	int iRet = -1;
	iRet = JNetMBClose(pDlg->m_hBhandle);
	if( 0 != iRet )
	{
		AfxMessageBox( _T("JNetMBClose error!"));
		return 0;
	}
	pDlg->m_hBhandle = NULL;
	pDlg->GetDlgItem(IDC_STATIC_SHOWTEXT)->SetWindowText(_T("搜索完成"));
	pDlg->GetDlgItem(IDC_BUTTON_SERACHDEVICE)->SetWindowText(_T("搜索设备"));
	pDlg->m_bSerachDevice = FALSE;
	
	return 0;
}
// CSerchDevice 消息处理程序
void CSerchDevice::OnBnClickedButtonSerachdevice()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	if(m_bSerachDevice)
	{
		if(g_PubData.g_iLanguageFlag == 0)
			GetDlgItem(IDC_BUTTON_SERACHDEVICE)->SetWindowText(_T("搜索设备"));
		else
			GetDlgItem(IDC_BUTTON_SERACHDEVICE)->SetWindowText(_T("serach"));
		GetDlgItem(IDC_STATIC_SHOWTEXT)->SetWindowText(_T(""));
		if( m_hBhandle)
		{
			iRet = JNetMBClose(m_hBhandle);
			if( 0 != iRet )
			{
				AfxMessageBox( _T("JNetMBClose error!"));
				return;
			}
			m_hBhandle = NULL;
		}
		m_bSerachDevice = FALSE;
	}
	else
	{
		if(g_PubData.g_iLanguageFlag == 0)
		{
			GetDlgItem(IDC_BUTTON_SERACHDEVICE)->SetWindowText(_T("停止搜索"));
			//GetDlgItem(IDC_STATIC_SHOWTEXT)->ShowWindow()
			GetDlgItem(IDC_STATIC_SHOWTEXT)->SetWindowText(_T("正在搜索设备......."));
		}
		else
		{
			GetDlgItem(IDC_BUTTON_SERACHDEVICE)->SetWindowText(_T("Stop"));
			GetDlgItem(IDC_STATIC_SHOWTEXT)->SetWindowText(_T("Serach ......."));
		}
		
		m_listSerchDevice.DeleteAllItems();

		gDevCount  = 0;

	

		JNetMBOpen(GROUP_IP, GROUP_PORT, OnMBNotify, this, JNET_PRO_T_JPF, m_hBhandle);
		if(m_hBhandle)
		{
			if( JNetMBSearch(m_hBhandle,5) == 0 )
				m_bSerachDevice = TRUE;
		}
		
		//CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)SerachDeviceClose,this,0,0);
	}

	
	//
	
}
//回调函数
int  CSerchDevice::OnMBNotify(long lHandle,DWORD dwProtocol,int iErr,int iMsgID,LPCTSTR lpszDstID,void* pData,int iDataLen,void* pUserParam)
{

	if(NULL == lpszDstID || NULL == pData || NULL == pUserParam)
	{
		return -1;
	}
	CSerchDevice*		pDlg			= (CSerchDevice*)(pUserParam);
	ZeroMemory(&pDlg->m_devConfig,sizeof(pDlg->m_devConfig));
	try
	{
		j_Device_T *pDev = (j_Device_T *)(pData);
		int copy_size = 0;

		ZeroMemory(&pDlg->m_devConfig.stDev, sizeof(j_Device_T));

		if (iDataLen != sizeof(j_Device_T))
		{
			copy_size = sizeof(J_SysCfg_T);	
			if (pDev->SysSize < sizeof(J_SysCfg_T))
			{
				copy_size = pDev->SysSize;	

			}
			pDlg->m_devConfig.stDev.SysSize = sizeof(J_SysCfg_T);
			memcpy(&pDlg->m_devConfig.stDev.SysCfg, &pDev->SysCfg, copy_size);

			copy_size = sizeof(JNetworkInfo);	
			if (pDev->NetSize < sizeof(JNetworkInfo))
			{
				copy_size = pDev->NetSize;	

			}
			pDlg->m_devConfig.stDev.NetSize = sizeof(JNetworkInfo);
			memcpy(&pDlg->m_devConfig.stDev.NetworkInfo, &pDev->NetworkInfo, copy_size);
		}
		else 
		{
			memcpy(&pDlg->m_devConfig.stDev,pData,sizeof(j_Device_T));
		}
		if( 0 == pDlg->InsertDevListItem() )
		{
			gDevCount++;   
		}
	}
	catch(...)
	{
		return 0;
	}
	return 0;

}
CString CSerchDevice::GetDeviceType(int i)
{
	CString strType = _T("");
	switch(i) 
	{ 
	case J_DEV_IPC_6001: 
		strType = _T("3516普通枪机");
		break; 
	case J_DEV_IPC_6002: 
		strType = _T("3516红外护罩");
		break; 
	case J_DEV_IPC_6003: 
		strType = _T("3516红外大炮");
		break; 
	case J_DEV_IPC_6004: 
		strType = _T("3516红外中炮");
		break; 
	case J_DEV_IPC_6005: 
		strType = _T("3516半球");
		break; 
	case J_DEV_IPC_8001: 
		strType = _T("3518A普通枪机");
		break; 
	case J_DEV_IPC_8002: 
		strType = _T("3518A红外护罩");
		break; 
	case J_DEV_IPC_8003: 
		strType = _T("3518A红外大炮");
		break; 
	case J_DEV_IPC_8004: 
		strType = _T("3518A红外中炮");
		break; 
	case J_DEV_IPC_8005: 
		strType = _T("3518A半球");
		break; 
	case J_DEV_IPC_8101: 
		strType = _T("3518C普通枪机");
		break;
	case J_DEV_IPC_8102: 
		strType = _T("3518C红外护罩");
		break; 
	case J_DEV_IPC_8103: 
		strType = _T("3518C红外大炮");
		break; 
	case J_DEV_IPC_8104: 
		strType = _T("3518C红外中炮");
		break;
	case J_DEV_IPC_8105: 
		strType = _T("3518C半球");
		break; 
	case J_Dev_IPNC_:
		strType = _T("IPNC");
		break;
	case J_Dev_DVR_2_3520: 
		strType = _T("DVR 3520 16-D1");
		break; 
	case J_Dev_DVR_16_3531: 
		strType = _T("DVR 3531 16-D1(960)");
		break; 
	case J_Dev_DVR_4_3531: 
		strType = _T("DVR 3531 04-HD-SDI");
		break; 
	case J_Dev_NVR_1_3520: 
		strType = _T("NVR 3520 08-720P");
		break; 
	case J_Dev_NVR_16_3531: 
		strType = _T("NVR 3531 16-720P");
		break; 
	case J_Dev_NVR_9_3531: 
		strType = _T("NVR 3531 09-1080P");
		break; 
	case J_Dev_DECC_10_3531: 
		strType = _T("DEC CARD 720P 10in, 2out");
		break; 
	case J_Dev_DECB_13_3531: 
		strType = _T("DEC BOX  720P 13in, 2out");
		break; 
		
	default:
		strType = _T("NONE"); 
		break;
	}

	return strType;
}
//向列表插入数据
int CSerchDevice::InsertDevListItem()
{	
	try
	{
		CString str0(m_devConfig.stDev.SysCfg.serial_no);
		CString strip(m_devConfig.stDev.NetworkInfo.network[0].ip);
		CString strmac(m_devConfig.stDev.NetworkInfo.network[0].mac);
		for(int i = 0; i < gDevCount; i++ )
		{
			CString strText = m_listSerchDevice.GetItemText(i , 0);
			CString strText1 = m_listSerchDevice.GetItemText(i , 3);
			CString strText2 = m_listSerchDevice.GetItemText(i , 4);
			if(str0 == strText &&  strip == strText1 && strmac == strText2)
			{
				return -1;
			}
		}
		m_listSerchDevice.InsertItem(gDevCount,str0 );

		CString strType = _T("");
		strType = GetDeviceType(m_devConfig.stDev.SysCfg.dev_type);
		m_listSerchDevice.SetItemText(gDevCount, 1, strType);

		CString str2(m_devConfig.stDev.SysCfg.software_ver);
		m_listSerchDevice.SetItemText(gDevCount, 2, str2);

		CString str3(m_devConfig.stDev.NetworkInfo.network[0].ip);
		m_listSerchDevice.SetItemText(gDevCount, 3, str3);

		CString str4(m_devConfig.stDev.NetworkInfo.network[0].mac);
		m_listSerchDevice.SetItemText(gDevCount, 4, str4);
	}
	catch(...)
	{
		return -1;
	}
	return 0;
}
void CSerchDevice::OnNMDblclkListDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iIndex = pNMItemActivate->iItem;
	if( -1 == iIndex)
	{
		return ;
	}
	CString strName = m_listSerchDevice.GetItemText(iIndex, 0);
	m_eDeviceName.SetWindowText(strName);

	CString strIp = m_listSerchDevice.GetItemText(iIndex, 3);
	m_eDeviceIp.SetWindowText(strIp);

	/*CString strPort;
	strPort.Format(_T("%d"),g_DevCfg[iIndex].stDev.NetworkInfo.cmd_port);
	m_eDevicePort.SetWindowText(strPort);*/
}

void CSerchDevice::OnBnClickedButtonSave()
{
	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();
	g_PubData.g_strArrayLoginIp.RemoveAll();
	for(int i = 0; i< m_listSerchDevice.GetItemCount(); i++)
	{
		int iFlag = -1;
		CString strIp = m_listSerchDevice.GetItemText(i, 3);
		//多选时自动过滤重复的设备
		if( m_listSerchDevice.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			for(int j = 0; j< g_PubData.g_iCountDevice; j++)
			{
				//判断是否已经保存    
				if( g_PubData.g_strArraySavedIp.GetAt(j) ==  strIp)
				{
					iFlag = 1;
				}
			}
			if(iFlag < 0)//过滤
			{
				g_PubData.g_strArrayLoginIp.Add(strIp);
			}
		}

	}
	CString strDeviceIp = _T("");
	m_eDeviceIp.GetWindowText(strDeviceIp);
	if(g_PubData.g_strArrayLoginIp.GetCount() == 0  )
	{
		if(strDeviceIp == _T(""))
		{
			if(g_PubData.g_iLanguageFlag == 0)
				AfxMessageBox(_T("没有选择设备或设备已连接"));
			else
				AfxMessageBox( _T("No selected device or device is connected!"));
			return;
		}
		else
		{
			for(int i = 0; i< g_PubData.g_strArraySavedIp.GetCount(); i++)
			{
				if(strDeviceIp == g_PubData.g_strArraySavedIp.GetAt(i))
				{
					
					if(g_PubData.g_iLanguageFlag == 0)
						AfxMessageBox(_T("设备已连接"));
					else
						AfxMessageBox( _T("Device is connected!"));
					return;
				}
			}
		
			g_PubData.g_strArrayLoginIp.Add(strDeviceIp);	
		}
		
	}

	m_eUserName.GetWindowText(g_PubData.g_strUser);
	m_eUserPassword.GetWindowText(g_PubData.g_strPassword);
	CString strPort(_T(""));
	m_eDevicePort.GetWindowText(strPort);
	g_PubData.g_iDevicePort = _ttoi(strPort);
	m_bIsAdd = true;
	OnCancel();

}

void CSerchDevice::OnLvnColumnclickListDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int iSelectIndex = pNMLV->iSubItem;
	ListSort(iSelectIndex);
	*pResult = 0;
}

void CSerchDevice::ListSort(int index)
{
	for(int i =0 ; i< m_listSerchDevice.GetItemCount()-1; i++)
	{

		for(int j = 0; j< m_listSerchDevice.GetItemCount()- 1 - i; j++)
		{
			CString str1 = m_listSerchDevice.GetItemText(j, index);
			CString str2 = m_listSerchDevice.GetItemText(j+1, index);

			CString strid1 = m_listSerchDevice.GetItemText(j, 0);
			CString strid2 = m_listSerchDevice.GetItemText(j+1, 0);

			CString strType1 = m_listSerchDevice.GetItemText(j, 1);
			CString strtype2 = m_listSerchDevice.GetItemText(j+1, 1);

			CString strVersion1 = m_listSerchDevice.GetItemText(j, 2);
			CString strVersion2 = m_listSerchDevice.GetItemText(j+1, 2);

			CString strip1 = m_listSerchDevice.GetItemText(j, 3);
			CString strip2 = m_listSerchDevice.GetItemText(j+1, 3);

			CString strMAC1 = m_listSerchDevice.GetItemText(j, 4);
			CString strMAC2 = m_listSerchDevice.GetItemText(j+1, 4);
			if(str1 > str2)
			{
				ReplaceCstring(strid1, strid2);
				m_listSerchDevice.SetItemText(j, 0, strid1);
				m_listSerchDevice.SetItemText(j+1, 0, strid2);

				ReplaceCstring(strType1, strtype2);
				m_listSerchDevice.SetItemText(j, 1, strType1);
				m_listSerchDevice.SetItemText(j+1, 1, strtype2);

				ReplaceCstring(strVersion1, strVersion2);
				m_listSerchDevice.SetItemText(j, 2, strVersion1);
				m_listSerchDevice.SetItemText(j+1, 2, strVersion2);

				ReplaceCstring(strip1, strip2);
				m_listSerchDevice.SetItemText(j, 3, strip1);
				m_listSerchDevice.SetItemText(j+1, 3, strip2);

				ReplaceCstring(strMAC1, strMAC2);
				m_listSerchDevice.SetItemText(j, 4, strMAC1);
				m_listSerchDevice.SetItemText(j+1, 4, strMAC2);
				ReplaceCstring(str1, str2);

				m_listSerchDevice.SetItemText(j, index, str1);
				m_listSerchDevice.SetItemText(j+1, index, str2);

	
			}
		}
	}
}

void CSerchDevice::IpSort(CString strIp1, CString strIp2)
{
	
}
void CSerchDevice::ReplaceCstring(CString &str1, CString &str2)
{
	CString strTemp = _T("");
	strTemp = str1;
	str1 = str2;
	str2 = strTemp;
}
void CSerchDevice::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnClose();
}

HBRUSH CSerchDevice::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_SHOWTEXT )
	{
		//pDC->SetTextColor(RGB(255,0,0));  //字体颜色
		//pDC->SetBkColor(RGB(165, 165, 165));   //字体背景色  
		//return (HBRUSH)::GetStockObject(WHITE_BRUSH);  

	}

	return hbr;
}

void CSerchDevice::OnNMClickListDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
