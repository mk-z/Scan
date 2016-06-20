// EMailSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "EMailSet.h"
#include "Pub_Data.h"

// CEMailSet 对话框



IMPLEMENT_DYNAMIC(CEMailSet, CDialog)

CEMailSet::CEMailSet(CWnd* pParent /*=NULL*/)
	: CDialog(CEMailSet::IDD, pParent)
{
	ZeroMemory(&m_smtpParam, sizeof(m_smtpParam));
}

CEMailSet::~CEMailSet()
{
	DestroyWindow();
}

void CEMailSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SMTPSERVER, m_SmtpServer);
	DDX_Control(pDX, IDC_EDIT_EMAILADDR, m_EmailAddr);
	DDX_Control(pDX, IDC_EDIT_SMTPUSER, m_SmtpUser);
	DDX_Control(pDX, IDC_EDIT_SMTPPASSWORD, m_SmtpPassword);
	DDX_Control(pDX, IDC_EDIT_SMTPPORT, m_SmtpPort);
	DDX_Control(pDX, IDC_EDIT_EMAILRESIVE1, m_EmailResive1);
	DDX_Control(pDX, IDC_EDIT_EMAILRESIVE2, m_EmailResive2);
	DDX_Control(pDX, IDC_EDIT_EmailResive3, m_EmailResive3);
	DDX_Control(pDX, IDC_CHECK_SSL, m_SSL);
}


BEGIN_MESSAGE_MAP(CEMailSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CEMailSet::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CEMailSet::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CEMailSet 消息处理程序
BOOL CEMailSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	///OnBnClickedButtonFlash();
	return TRUE;
}

void CEMailSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText(_T(""));

	m_SmtpServer.GetWindowText(strText);
	memset(m_smtpParam.mail_ip, '\0', sizeof(m_smtpParam.mail_ip));
	memcpy(m_smtpParam.mail_ip, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_EmailAddr.GetWindowText(strText);
	memset(m_smtpParam.mail_addr, '\0', sizeof(m_smtpParam.mail_addr));
	memcpy(m_smtpParam.mail_addr, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_SmtpUser.GetWindowText(strText);
	memset(m_smtpParam.mail_usr, '\0', sizeof(m_smtpParam.mail_usr));
	memcpy(m_smtpParam.mail_usr, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_SmtpPassword.GetWindowText(strText);
	memset(m_smtpParam.mail_pwd, '\0', sizeof(m_smtpParam.mail_pwd));
	memcpy(m_smtpParam.mail_pwd, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_SmtpPort.GetWindowText(strText);
	m_smtpParam.mail_port = _ttoi(strText);

	m_EmailResive1.GetWindowText(strText);
	memset(m_smtpParam.mail_rctp1, '\0', sizeof(m_smtpParam.mail_rctp1));
	memcpy(m_smtpParam.mail_rctp1, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_EmailResive2.GetWindowText(strText);
	memset(m_smtpParam.mail_rctp2, '\0', sizeof(m_smtpParam.mail_rctp2));
	memcpy(m_smtpParam.mail_rctp2, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_EmailResive3.GetWindowText(strText);
	memset(m_smtpParam.mail_rctp3, '\0', sizeof(m_smtpParam.mail_rctp3));
	memcpy(m_smtpParam.mail_rctp3, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_smtpParam.ssl_enable = m_SSL.GetCheck();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_SMTP_INFO, (char *)&m_smtpParam, sizeof(m_smtpParam), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}
}

void CEMailSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_SMTP_INFO, (char *)&m_smtpParam, sizeof(m_smtpParam),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}
	ReFreshWindow();
}


int CEMailSet::ReFreshWindow()
{   
	CString strText(_T(""));

	strText.Format(_T("%s"), m_smtpParam.mail_ip);
	m_SmtpServer.SetWindowText(strText);

	strText.Format(_T("%s"), m_smtpParam.mail_addr);
	m_EmailAddr.SetWindowText(strText);

	strText.Format(_T("%s"), m_smtpParam.mail_usr);
	m_SmtpUser.SetWindowText(strText);

	strText.Format(_T("%s"), m_smtpParam.mail_pwd);
	m_SmtpPassword.SetWindowText(strText);

	strText.Format(_T("%d"), m_smtpParam.mail_port);
	m_SmtpPort.SetWindowText(strText);

	strText.Format(_T("%s"), m_smtpParam.mail_rctp1);
	m_EmailResive1.SetWindowText(strText);

	strText.Format(_T("%s"), m_smtpParam.mail_rctp2);
	m_EmailResive2.SetWindowText(strText);

	strText.Format(_T("%s"), m_smtpParam.mail_rctp3);
	m_EmailResive3.SetWindowText(strText);

	m_SSL.SetCheck(m_smtpParam.ssl_enable);
	return 0;
}
void CEMailSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
