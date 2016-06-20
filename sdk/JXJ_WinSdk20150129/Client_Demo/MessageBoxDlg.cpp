// MessageBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "MessageBoxDlg.h"

#include "Pub_Data.h"
// CMessageBoxDlg 对话框

IMPLEMENT_DYNAMIC(CMessageBoxDlg, CDialog)

CMessageBoxDlg::CMessageBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageBoxDlg::IDD, pParent)
{
	m_iRet = -1;
}

CMessageBoxDlg::~CMessageBoxDlg()
{
}

void CMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageBoxDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CMessageBoxDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMessageBoxDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMessageBoxDlg 消息处理程序
BOOL CMessageBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->SetWindowText(m_strTitle);
	this->GetDlgItem(IDC_STATIC_SHOWMESSAGE)->SetWindowText(m_strMsg);

	if(g_PubData.g_iLanguageFlag == 0)
	{
		this->GetDlgItem(IDOK)->SetWindowText(_T("确定"));
		this->GetDlgItem(IDCANCEL)->SetWindowText(_T("取消"));
	}
	else
	{
		this->GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		this->GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
	}

	return TRUE;
}

void CMessageBoxDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	m_iRet = 1;
	OnOK();
}

void CMessageBoxDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iRet = -1;
	OnCancel();
}

void CMessageBoxDlg::SetWndText(CString strTitle, CString strMsg)
{
	
}
