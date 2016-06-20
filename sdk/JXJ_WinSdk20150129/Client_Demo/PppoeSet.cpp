// PppoeSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "PppoeSet.h"
#include "Pub_Data.h"


// CPppoeSet 对话框

IMPLEMENT_DYNAMIC(CPppoeSet, CDialog)

CPppoeSet::CPppoeSet(CWnd* pParent /*=NULL*/)
	: CDialog(CPppoeSet::IDD, pParent)
{

}

CPppoeSet::~CPppoeSet()
{
	DestroyWindow();
}

void CPppoeSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_STARTPPPOE, m_StartPPPOE);
	DDX_Control(pDX, IDC_COMBO_USENETWORK, m_UseNetWork);
	DDX_Control(pDX, IDC_EDIT_DEVICEIP, m_DeviceIp);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_UserName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_Password);
}


BEGIN_MESSAGE_MAP(CPppoeSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPppoeSet::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CPppoeSet::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPppoeSet 消息处理程序
BOOL CPppoeSet::OnInitDialog()
{
	CDialog::OnInitDialog();
//
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_UseNetWork.AddString(_T("以太网"));
	}
	else
	{
		m_UseNetWork.AddString(_T("Ethernet"));
	}
	
	m_UseNetWork.AddString(_T("WIFI"));
	m_UseNetWork.AddString(_T("3G"));

//	OnBnClickedButtonFlash();
	return TRUE;
}

void CPppoeSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strText(_T(""));

	m_pppoeInfo.enable = m_StartPPPOE.GetCheck();

	m_pppoeInfo.type = m_UseNetWork.GetCurSel();

	m_DeviceIp.GetWindowText(strText);
	memset(m_pppoeInfo.ip, '\0', sizeof(m_pppoeInfo.ip));
	memcpy(m_pppoeInfo.ip, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_UserName.GetWindowText(strText);
	memset(m_pppoeInfo.account, '\0', sizeof(m_pppoeInfo.account));
	memcpy(m_pppoeInfo.account, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_Password.GetWindowText(strText);
	memset(m_pppoeInfo.passwd, '\0', sizeof(m_pppoeInfo.passwd));
	memcpy(m_pppoeInfo.passwd, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PPPOE_INFOE, (char *)&m_pppoeInfo, sizeof(m_pppoeInfo), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}

}

void CPppoeSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PPPOE_INFOE, (char *)&m_pppoeInfo, sizeof(m_pppoeInfo),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();
	
}



int CPppoeSet::ReFreshWindow()
{
	CString strText(_T(""));

	m_StartPPPOE.SetCheck(m_pppoeInfo.enable);

	m_UseNetWork.SetCurSel(m_pppoeInfo.type);

	strText.Format(_T("%s"), m_pppoeInfo.ip);
	m_DeviceIp.SetWindowText(strText);

	strText.Format(_T("%s"), m_pppoeInfo.account);
	m_UserName.SetWindowText(strText);

	strText.Format(_T("%s"), m_pppoeInfo.passwd);
	m_Password.SetWindowText(strText);

	return 0;
}

//JDdnsConfig
void CPppoeSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
