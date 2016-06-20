// NetDiskSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "NetDiskSet.h"
#include "Pub_Data.h"


// CNetDiskSet 对话框



IMPLEMENT_DYNAMIC(CNetDiskSet, CDialog)

CNetDiskSet::CNetDiskSet(CWnd* pParent /*=NULL*/)
	: CDialog(CNetDiskSet::IDD, pParent)
{

}

CNetDiskSet::~CNetDiskSet()
{
	DestroyWindow();
}

void CNetDiskSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_START_NET_DISK, m_StartNetDisk);
	DDX_Control(pDX, IDC_COMBOPROTOCOL, m_comProtocol);
	DDX_Control(pDX, IDC_EDIT_DISK_IP, m_DiskIp);
	DDX_Control(pDX, IDC_EDIT_DISK_PORT, m_DiskPort);
	DDX_Control(pDX, IDC_EDIT_DISK_STARTMACHINENAME, m_StartMachineName);
	DDX_Control(pDX, IDC_EDIT_DISK_NAME, m_DiskName);
	DDX_Control(pDX, IDC_COMBO_RZTYPE, m_RZType);
	DDX_Control(pDX, IDC_EDIT_RZ_USER, m_RZuser);
	DDX_Control(pDX, IDC_EDIT_RZ_PASS, m_RZpass);
	DDX_Control(pDX, IDC_COMBO_LOGINRZTYPE, m_LoginRZtype);
	DDX_Control(pDX, IDC_EDITLOGIN_RZ_USER, m_LoginRZuser);
	DDX_Control(pDX, IDC_EDIT_LOGIN_RZ_PASS, m_LoginRZpass);
}


BEGIN_MESSAGE_MAP(CNetDiskSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CNetDiskSet::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CNetDiskSet::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CNetDiskSet 消息处理程序
BOOL CNetDiskSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comProtocol.AddString(_T("ISCSI"));

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_RZType.AddString(_T("无认证"));
		m_RZType.AddString(_T("CHAP 认证"));

		m_LoginRZtype.AddString(_T("无认证"));
		m_LoginRZtype.AddString(_T("CHAP 认证"));
	}
	else
	{
		m_RZType.AddString(_T("No authentication"));
		m_RZType.AddString(_T("CHAP 认证"));

		m_LoginRZtype.AddString(_T("No authentication"));
		m_LoginRZtype.AddString(_T("CHAP 认证"));
	}
	
	return TRUE;
}

void CNetDiskSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	m_netDisk.enable = m_StartNetDisk.GetCheck();
	m_netDisk.proto = m_comProtocol.GetCurSel();

	CString strText = _T("");

	m_DiskIp.GetWindowText(strText);
	memset(m_netDisk.disk_ip, '\0', sizeof(m_netDisk.disk_ip));
	memcpy(m_netDisk.disk_ip,strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_DiskPort.GetWindowText(strText);
	m_netDisk.iscsi_disk.disk_port = _ttoi(strText);

	m_StartMachineName.GetWindowText(strText);
	memset(m_netDisk.iscsi_disk.cli_name, '\0', sizeof(m_netDisk.iscsi_disk.cli_name));
	memcpy(m_netDisk.iscsi_disk.cli_name,strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_DiskName.GetWindowText(strText);
	memset(m_netDisk.iscsi_disk.tg_name, '\0', sizeof(m_netDisk.iscsi_disk.tg_name));
	memcpy(m_netDisk.iscsi_disk.tg_name,strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();


	m_netDisk.iscsi_disk.discovey_auth = m_RZType.GetCurSel();

	m_RZuser.SetWindowText(strText);
	memset(m_netDisk.disk_ip, '\0', sizeof(m_netDisk.disk_ip));
	memcpy(m_netDisk.disk_ip,strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_RZpass.GetWindowText(strText);
	memset(m_netDisk.iscsi_disk.dis_chap_usr, '\0', sizeof(m_netDisk.iscsi_disk.dis_chap_usr));
	memcpy(m_netDisk.iscsi_disk.dis_chap_usr,strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();


	m_netDisk.iscsi_disk.tg_chap_auth = m_LoginRZtype.GetCurSel();

	m_LoginRZuser.GetWindowText(strText);
	memset(m_netDisk.iscsi_disk.tg_chap_usr, '\0', sizeof(m_netDisk.iscsi_disk.tg_chap_usr));
	memcpy(m_netDisk.iscsi_disk.tg_chap_usr,strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_LoginRZpass.GetWindowText(strText);
	memset(m_netDisk.iscsi_disk.tg_chap_pwd, '\0', sizeof(m_netDisk.iscsi_disk.tg_chap_pwd));
	memcpy(m_netDisk.iscsi_disk.tg_chap_pwd,strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_NETWORK_DISK_CFG, (char *)&m_netDisk, sizeof(m_netDisk), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}
}

void CNetDiskSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_NETWORK_DISK_CFG, (char *)&m_netDisk, sizeof(m_netDisk),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();
}



int CNetDiskSet::ReFreshWindow()
{
	m_StartNetDisk.SetCheck(m_netDisk.enable);
	m_comProtocol.SetCurSel(m_netDisk.proto);

	CString strText = _T("");

	strText.Format(_T("%s"),m_netDisk.disk_ip);
	m_DiskIp.SetWindowText(strText);
	
	strText.Format(_T("%d"),m_netDisk.iscsi_disk.disk_port);
	m_DiskPort.SetWindowText(strText);

	strText.Format(_T("%s"), m_netDisk.iscsi_disk.cli_name);
	m_StartMachineName.SetWindowText(strText);

	strText.Format(_T("%s"), m_netDisk.iscsi_disk.tg_name);
	m_DiskName.SetWindowText(strText);

	m_RZType.SetCurSel(m_netDisk.iscsi_disk.discovey_auth);
	
	strText.Format(_T("%s"),m_netDisk.iscsi_disk.dis_chap_usr);
	m_RZuser.SetWindowText(strText);

	strText.Format(_T("%s"), m_netDisk.iscsi_disk.dis_chap_pwd);
	m_RZpass.SetWindowText(strText);

	m_LoginRZtype.SetCurSel(m_netDisk.iscsi_disk.tg_chap_auth);

	strText.Format(_T("%s"), m_netDisk.iscsi_disk.tg_chap_usr);
	m_LoginRZuser.SetWindowText(strText);

	strText.Format(_T("%s"), m_netDisk.iscsi_disk.tg_chap_pwd);
	m_LoginRZpass.SetWindowText(strText);
	return 0;
}

void CNetDiskSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
