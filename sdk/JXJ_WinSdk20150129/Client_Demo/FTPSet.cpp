// FTPSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "FTPSet.h"
#include "Pub_Data.h"

// CFTPSet 对话框



IMPLEMENT_DYNAMIC(CFTPSet, CDialog)

CFTPSet::CFTPSet(CWnd* pParent /*=NULL*/)
	: CDialog(CFTPSet::IDD, pParent)
{
	ZeroMemory(&m_ftpParam, sizeof(m_ftpParam));
}

CFTPSet::~CFTPSet()
{
	DestroyWindow();	
}

void CFTPSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FTPIP, m_FtpIp);
	DDX_Control(pDX, IDC_EDITFTPPORT, m_FtpPort);
	DDX_Control(pDX, IDC_EDIT_FTPPATH, m_FtpPath);
	DDX_Control(pDX, IDC_EDIT_FTPUSER, m_FtpUser);
	DDX_Control(pDX, IDC_EDIT_FTPPASSWORD, m_FtpPassword);
}


BEGIN_MESSAGE_MAP(CFTPSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CFTPSet::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CFTPSet::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFTPSet 消息处理程序
BOOL CFTPSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	//OnBnClickedButtonFlash();
	return TRUE;
}

void CFTPSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strText(_T(""));

	m_FtpIp.GetWindowText(strText);
	memset(m_ftpParam.ftp_ip, '\0', sizeof(m_ftpParam.ftp_ip));
	memcpy(m_ftpParam.ftp_ip, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_FtpPort.GetWindowText(strText);
	m_ftpParam.ftp_port = _ttoi(strText);

	m_FtpPath.GetWindowText(strText);
	memset(m_ftpParam.ftp_path, '\0', sizeof(m_ftpParam.ftp_path));
	memcpy(m_ftpParam.ftp_path, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_FtpUser.GetWindowText(strText);
	memset(m_ftpParam.ftp_usr, '\0', sizeof(m_ftpParam.ftp_usr));
	memcpy(m_ftpParam.ftp_usr, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_FtpPassword.GetWindowText(strText);
	memset(m_ftpParam.ftp_pwd, '\0', sizeof(m_ftpParam.ftp_pwd));
	memcpy(m_ftpParam.ftp_pwd, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_FTP_INFO, (char *)&m_ftpParam, sizeof(m_ftpParam),TRUE );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return ;
	}
	
}



void CFTPSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_FTP_INFO, (char *)&m_ftpParam, sizeof(m_ftpParam),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}
	ReFreshWindow();
}


int CFTPSet::ReFreshWindow()
{

	CString strText(_T(""));
	strText.Format(_T("%s"),m_ftpParam.ftp_ip);
	
	m_FtpIp.SetWindowText(strText);

	strText.Format(_T("%d"),m_ftpParam.ftp_port);
	m_FtpPort.SetWindowText(strText);

	strText.Format(_T("%s"),m_ftpParam.ftp_path);
	m_FtpPath.SetWindowText(strText);

	strText.Format(_T("%s"),m_ftpParam.ftp_usr);
	m_FtpUser.SetWindowText(strText);

	strText.Format(_T("%s"),m_ftpParam.ftp_pwd);
	m_FtpPassword.SetWindowText(strText);
	return 0;
}
void CFTPSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
