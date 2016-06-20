// SystemMsgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "SystemMsgDlg.h"
#include "Pub_Data.h"

// CSystemMsgDlg 对话框


IMPLEMENT_DYNAMIC(CSystemMsgDlg, CDialog)

CSystemMsgDlg::CSystemMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemMsgDlg::IDD, pParent)
{

}

CSystemMsgDlg::~CSystemMsgDlg()
{
	DestroyWindow();
}

void CSystemMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VENDER, m_eVender);
	DDX_Control(pDX, IDC_EDIT_OUTTIME, m_eOutTime);
	DDX_Control(pDX, IDC_EDIT_VERSION, m_eVersion);
	DDX_Control(pDX, IDC_EDIT_HARDWAREVERSION, m_eHardwareVersion);
	DDX_Control(pDX, IDC_EDIT_INNUM, m_eInNum);
	DDX_Control(pDX, IDC_EDIT_OUTNUM, m_eOutNum);
	DDX_Control(pDX, IDC_EDIT_CHANNELNUM, m_eChannelNum);
	DDX_Control(pDX, IDC_EDIT_RS485, m_eRsNum485);
	DDX_Control(pDX, IDC_EDIT_RS232, m_eRsNum232);
	DDX_Control(pDX, IDC_COMBO_DEVICETYPE, m_cDeviceType);
	DDX_Control(pDX, IDC_COMBO_MACHINETYPE, m_cMachineType);
	DDX_Control(pDX, IDC_BUTTONSAVE, m_bSave);
}


BEGIN_MESSAGE_MAP(CSystemMsgDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTONFLASH, &CSystemMsgDlg::OnBnClickedButtonflash)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSystemMsgDlg 消息处理程序
BOOL CSystemMsgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_bSave.EnableWindow(FALSE);

	m_cDeviceType.AddString(_T("DVR"));
	m_cDeviceType.AddString(_T("DVS"));
	m_cDeviceType.AddString(_T("IPC"));
	m_cDeviceType.AddString(_T("IPNC"));
	m_cDeviceType.AddString(_T("NVR"));
	m_cDeviceType.AddString(_T("HVR"));
	m_cDeviceType.AddString(_T("DEC"));
	m_cDeviceType.AddString(_T("OTHER"));
	m_cDeviceType.EnableWindow(FALSE);


	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_cMachineType.AddString(_T("枪机"));
		m_cMachineType.AddString(_T("红外"));
		m_cMachineType.AddString(_T("半球"));
		m_cMachineType.AddString(_T("其它"));
		m_cMachineType.EnableWindow(FALSE);
	}
	else
	{
		m_cMachineType.AddString(_T("Rifle "));
		m_cMachineType.AddString(_T("Infrared"));
		m_cMachineType.AddString(_T("Halfsphere"));
		m_cMachineType.AddString(_T("Else"));
		m_cMachineType.EnableWindow(FALSE);
	}
	
	OnBnClickedButtonflash();

	return TRUE;
}

int CSystemMsgDlg::ReFreshWindow()
{
	CString strVender;
	strVender.Format(_T("%s"), m_Deviceinfo.manu_info);
	m_eVender.SetWindowText(strVender);

	CString strOutTime;
	strOutTime.Format(_T("%s"), m_Deviceinfo.release_date);
	m_eOutTime.SetWindowText(strOutTime);

	CString strVersion;
	strVersion.Format(_T("%s"), m_Deviceinfo.dev_version);
	m_eVersion.SetWindowText(strVersion);

	CString strHardwareVersion;
	strHardwareVersion.Format(_T("%s"), m_Deviceinfo.hw_version);
	m_eHardwareVersion.SetWindowText(strHardwareVersion);

	int puType = m_Deviceinfo.pu_type;
	m_cDeviceType.SetCurSel(puType);	

	int subType = m_Deviceinfo.sub_type;
	m_cMachineType.SetCurSel(subType);

	int diNum = m_Deviceinfo.di_num;
	g_PubData.g_iIoWarningChannelNul = m_Deviceinfo.di_num;
	CString strInNum(_T(""));
	strInNum.Format(_T("%d"),diNum);
	m_eInNum.SetWindowText(strInNum);
	
	int doNum = m_Deviceinfo.do_num;
	CString strOutNum = _T("");
	strOutNum.Format(_T("%d"),doNum);
	m_eOutNum.SetWindowText(strOutNum);

	int channelNum = m_Deviceinfo.channel_num;
	g_PubData.g_iChannelNo = m_Deviceinfo.channel_num; 
	CString strChannelNum = _T("");
	strChannelNum.Format(_T("%d"),channelNum);
	m_eChannelNum.SetWindowText(strChannelNum);

	int re232Num = m_Deviceinfo.rs232_num;
	CString strNum232 = _T("");
	strNum232.Format(_T("%d"),re232Num);
	m_eRsNum232.SetWindowText(strNum232);


	int rs485Num = m_Deviceinfo.rs485_num;
	CString strNum485 = _T("");
	strNum485.Format(_T("%d"),rs485Num);
	m_eRsNum485.SetWindowText(strNum485);

	return 0;
}
void CSystemMsgDlg::OnBnClickedButtonflash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DEVICE_INFO, (char *)&m_Deviceinfo, sizeof(m_Deviceinfo),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshWindow();

}


void CSystemMsgDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
