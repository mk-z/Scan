// HwSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HwSetDlg.h"
#include "Pub_Data.h"

// CHwSetDlg 对话框

IMPLEMENT_DYNAMIC(CHwSetDlg, CDialog)

CHwSetDlg::CHwSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHwSetDlg::IDD, pParent)
{
	ZeroMemory(&m_hwcfg, sizeof(m_hwcfg));
}

CHwSetDlg::~CHwSetDlg()
{
}

void CHwSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_hwDeviceId);
	DDX_Control(pDX, IDC_EDIT2, m_hwDevicePwd);
	DDX_Control(pDX, IDC_EDIT3, m_localMsgPort);
	DDX_Control(pDX, IDC_EDIT4, m_hwServerIp);
	DDX_Control(pDX, IDC_EDIT5, m_hwServerAddr);
	DDX_Control(pDX, IDC_EDIT6, m_hwServerPort);
	DDX_Control(pDX, IDC_COMBO_SERVERAREA, m_ServerArea);
}


BEGIN_MESSAGE_MAP(CHwSetDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CHwSetDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CHwSetDlg::OnBnClickedButtonFlash)
END_MESSAGE_MAP()


// CHwSetDlg 消息处理程序
BOOL CHwSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ServerArea.AddString(_T("安徽"));
	m_ServerArea.AddString(_T("北京"));
	m_ServerArea.AddString(_T("重庆"));
	m_ServerArea.AddString(_T("福建"));
	m_ServerArea.AddString(_T("甘肃"));
	m_ServerArea.AddString(_T("广东"));
	m_ServerArea.AddString(_T("广西"));
	m_ServerArea.AddString(_T("贵州"));
	m_ServerArea.AddString(_T("海南"));
	m_ServerArea.AddString(_T("河北"));
	m_ServerArea.AddString(_T("河南"));
	m_ServerArea.AddString(_T("黑龙江"));
	m_ServerArea.AddString(_T("湖南"));
	m_ServerArea.AddString(_T("湖北"));
	m_ServerArea.AddString(_T("吉林"));
	m_ServerArea.AddString(_T("江苏"));
	m_ServerArea.AddString(_T("江西"));
	m_ServerArea.AddString(_T("辽宁"));
	m_ServerArea.AddString(_T("内蒙古"));
	m_ServerArea.AddString(_T("宁夏"));
	m_ServerArea.AddString(_T("青海"));
	m_ServerArea.AddString(_T("山东"));
	m_ServerArea.AddString(_T("山西"));
	m_ServerArea.AddString(_T("陕西"));
	m_ServerArea.AddString(_T("上海"));
	m_ServerArea.AddString(_T("四川"));
	m_ServerArea.AddString(_T("天津"));
	m_ServerArea.AddString(_T("西藏"));
	m_ServerArea.AddString(_T("新疆"));
	m_ServerArea.AddString(_T("云南"));
	m_ServerArea.AddString(_T("浙江"));
	m_ServerArea.AddString(_T("香港"));
	m_ServerArea.AddString(_T("澳门"));
	m_ServerArea.AddString(_T("台湾"));
	
	return TRUE;
}

void CHwSetDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strText;

	m_hwDeviceId.GetWindowText(strText);
	memset(m_hwcfg.device_id, 0, sizeof(m_hwcfg.device_id));
	memcpy(m_hwcfg.device_id, strText.GetBuffer(0), strText.GetLength());

	m_hwDevicePwd.GetWindowText(strText);
	memset(m_hwcfg.device_pwd, 0, sizeof(m_hwcfg.device_pwd));
	memcpy(m_hwcfg.device_pwd, strText.GetBuffer(0), strText.GetLength());

	m_localMsgPort.GetWindowText(strText);
	m_hwcfg.msg_port = _ttoi(strText);


	m_hwcfg.server_area = m_ServerArea.GetCurSel() + 1;

	m_hwServerIp.GetWindowText(strText);
	memset(m_hwcfg.server_id, 0, sizeof(m_hwcfg.server_id));
	memcpy(m_hwcfg.server_id, strText.GetBuffer(0), strText.GetLength());

	m_hwServerAddr.GetWindowText(strText);
	memset(m_hwcfg.server_ip, 0, sizeof(m_hwcfg.server_ip));
	memcpy(m_hwcfg.server_ip, strText.GetBuffer(0), strText.GetLength());

	m_hwServerPort.GetWindowText(strText);
	m_hwcfg.server_port = _ttoi(strText);
	
	strText.ReleaseBuffer();


	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HW_PF_CFG, (char *)&m_hwcfg, sizeof(m_hwcfg), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}
}

void CHwSetDlg::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HW_PF_CFG, (char *)&m_hwcfg, sizeof(m_hwcfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();
}

int CHwSetDlg::ReFreshWindow()
{
	CString strText;
	strText.Format(_T("%s"), m_hwcfg.device_id);
	m_hwDeviceId.SetWindowText(strText);

	strText.Format(_T("%s"), m_hwcfg.device_pwd);
	m_hwDevicePwd.SetWindowText(strText);

	strText.Format(_T("%d"), m_hwcfg.msg_port);
	m_localMsgPort.SetWindowText(strText);

	m_ServerArea.SetCurSel(m_hwcfg.server_area - 1);

	strText.Format(_T("%s"), m_hwcfg.server_id);
	m_hwServerIp.SetWindowText(strText);

	strText.Format(_T("%s"), m_hwcfg.server_ip);
	m_hwServerAddr.SetWindowText(strText);

	strText.Format(_T("%d"), m_hwcfg.server_port);
	m_hwServerPort.SetWindowText(strText);

	return 0;
}

