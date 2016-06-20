// DeviceUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "DeviceUserDlg.h"
#include "Pub_Data.h"


// CDeviceUserDlg 对话框

IMPLEMENT_DYNAMIC(CDeviceUserDlg, CDialog)

CDeviceUserDlg::CDeviceUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceUserDlg::IDD, pParent)
{

}

CDeviceUserDlg::~CDeviceUserDlg()
{
	DestroyWindow();
}

void CDeviceUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USER, m_eUser);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ePassword);
	DDX_Control(pDX, IDC_EDIT_NEWUSER, m_NewUser);
	DDX_Control(pDX, IDC_EDIT_NEWPASSWORD, m_NewPassword);
}


BEGIN_MESSAGE_MAP(CDeviceUserDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CDeviceUserDlg::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDeviceUserDlg::OnBnClickedButtonSave)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDeviceUserDlg 消息处理程序

BOOL CDeviceUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_eUser.EnableWindow(FALSE);
	m_ePassword.EnableWindow(FALSE);

		//OnBnClickedButtonFlash();
	return TRUE;
}
void CDeviceUserDlg::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码


	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_USER_CONFIG, (char *)&m_userconfig, sizeof(m_userconfig),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshWindow();

}

void CDeviceUserDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strNewUser = _T("");
	CString strNewPassword = _T("");

	m_NewUser.GetWindowText(strNewUser);
	m_NewPassword.GetWindowText(strNewPassword);

	if(strNewUser == _T("") || strNewPassword == _T(""))
	{
		if(g_PubData.g_iLanguageFlag == 0)
			AfxMessageBox(_T("请填写完整"));
		else
			AfxMessageBox(_T("Please fill in the complete!"));
		return;
	}

	JUserModConfig userconfig;
	ZeroMemory(&userconfig,sizeof(JUserModConfig));
	
	CString strUser(_T(""));
	CString strPassword(_T(""));
	m_eUser.GetWindowText(strUser);
	m_ePassword.GetWindowText(strPassword);
	userconfig.local_right = m_userconfig.local_right;
	userconfig.remote_right = m_userconfig.remote_right;
	userconfig.reserve = m_userconfig.reserve;

	memset(userconfig.old_usrname, '\0' , sizeof(userconfig.old_usrname));
	memcpy(userconfig.old_usrname, strUser.GetBuffer(0), strUser.GetLength());
	strUser.ReleaseBuffer();

	memset(userconfig.old_password, '\0' , sizeof(userconfig.old_password));
	memcpy(userconfig.old_password, strPassword.GetBuffer(0), strPassword.GetLength());
	strPassword.ReleaseBuffer();

	memset(userconfig.new_username, '\0' , sizeof(userconfig.new_username));
	memcpy(userconfig.new_username, strNewUser.GetBuffer(0), strNewUser.GetLength());
	strNewUser.ReleaseBuffer();

	memset(userconfig.new_password, '\0' , sizeof(userconfig.new_password));
	memcpy(userconfig.new_password, strNewPassword.GetBuffer(0), strNewPassword.GetLength());
	strNewPassword.ReleaseBuffer();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_MODIFY_USER_CFG, (char *)&userconfig, sizeof(userconfig), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return ;
	}
	return;

}

int CDeviceUserDlg::ReFreshWindow()
{
	
	CString strText = _T("");
	strText.Format(_T("%s"), m_userconfig.username);
	m_eUser.SetWindowText(strText);

	strText.Format(_T("%s"), m_userconfig.password);
	CString strPassword(m_userconfig.password);
	m_ePassword.SetWindowText(strText);

	return 0;
}

void CDeviceUserDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
