// ZteCfgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "ZteCfgDlg.h"
#include "Pub_Data.h"

// CZteCfgDlg 对话框

IMPLEMENT_DYNAMIC(CZteCfgDlg, CDialog)

CZteCfgDlg::CZteCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZteCfgDlg::IDD, pParent)
{

}

CZteCfgDlg::~CZteCfgDlg()
{
}

void CZteCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ENABLEZTE, m_enableZTE);
	DDX_Control(pDX, IDC_EDIT_ID, m_id);
	DDX_Control(pDX, IDC_EDIT_USER, m_userName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Control(pDX, IDC_EDIT_IP, m_ip);
	DDX_Control(pDX, IDC_EDIT_PORT, m_port);
}


BEGIN_MESSAGE_MAP(CZteCfgDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CZteCfgDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CZteCfgDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CZteCfgDlg 消息处理程序
BOOL CZteCfgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;
}

void CZteCfgDlg::OnBnClickedButtonRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ZTE_PF_CFG, (char *)&m_ztePfCfg, sizeof(m_ztePfCfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}
	ReFreshWindow();
}

void CZteCfgDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	m_ztePfCfg.platformswitch = m_enableZTE.GetCheck();

	CString strText = _T("");

	m_id.GetWindowText(strText);
	memset(m_ztePfCfg.device_id, 0, sizeof(m_ztePfCfg.device_id));
	memcpy(m_ztePfCfg.device_id, strText.GetBuffer(0), strText.GetLength());

	m_userName.GetWindowText(strText);
	memset(m_ztePfCfg.username, 0, sizeof(m_ztePfCfg.username));
	memcpy(m_ztePfCfg.username, strText.GetBuffer(0), strText.GetLength());


	m_password.GetWindowText(strText);
	memset(m_ztePfCfg.password, 0, sizeof(m_ztePfCfg.password));
	memcpy(m_ztePfCfg.password, strText.GetBuffer(0), strText.GetLength());

	m_ip.GetWindowText(strText);
	memset(m_ztePfCfg.server_ip, 0, sizeof(m_ztePfCfg.server_ip));
	memcpy(m_ztePfCfg.server_ip, strText.GetBuffer(0), strText.GetLength());

	m_port.GetWindowText(strText);
	m_ztePfCfg.server_port = _ttoi(strText);

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ZTE_PF_CFG, (char *)&m_ztePfCfg, sizeof(m_ztePfCfg), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}
}



int CZteCfgDlg::ReFreshWindow()
{

	m_enableZTE.SetCheck(m_ztePfCfg.platformswitch);

	CString strText = _T("");

	strText.Format(_T("%s"), m_ztePfCfg.device_id);
	m_id.SetWindowText(strText);

	strText.Format(_T("%s"), m_ztePfCfg.username);
	m_userName.SetWindowText(strText);


	strText.Format(_T("%s"), m_ztePfCfg.password);
	m_password.SetWindowText(strText);


	strText.Format(_T("%s"), m_ztePfCfg.server_ip);
	m_ip.SetWindowText(strText);

	strText.Format(_T("%d"), m_ztePfCfg.server_port);
	m_port.SetWindowText(strText);

	return 0;
}
