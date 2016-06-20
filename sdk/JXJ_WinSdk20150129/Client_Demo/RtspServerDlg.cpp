// RtspServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "RtspServerDlg.h"
#include "Pub_Data.h"


// CRtspServerDlg 对话框

IMPLEMENT_DYNAMIC(CRtspServerDlg, CDialog)

CRtspServerDlg::CRtspServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRtspServerDlg::IDD, pParent)
{

}

CRtspServerDlg::~CRtspServerDlg()
{
}

void CRtspServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_enable);
	DDX_Control(pDX, IDC_EDIT1, m_rtspServerPort);
}


BEGIN_MESSAGE_MAP(CRtspServerDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CRtspServerDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CRtspServerDlg::OnBnClickedButtonFlash)
	ON_EN_CHANGE(IDC_EDIT1, &CRtspServerDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CRtspServerDlg 消息处理程序

BOOL CRtspServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	return TRUE;
}

void CRtspServerDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rtspParam.enable = m_enable.GetCheck();

	CString str;
	m_rtspServerPort.GetWindowText(str);
	m_rtspParam.svr_port = _ttoi(str);


	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_RTSP_SVR_CFG, (char *)&m_rtspParam, sizeof(m_rtspParam), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return;
	}
}



void CRtspServerDlg::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_RTSP_SVR_CFG, (char *)&m_rtspParam, sizeof(m_rtspParam),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}
	ReFreshWindow();
}


int CRtspServerDlg::ReFreshWindow()
{
	
	m_enable.SetCheck(m_rtspParam.enable);

	CString str;
	str.Format(_T("%d"), m_rtspParam.svr_port);
	m_rtspServerPort.SetWindowText(str);
	
	return 0;
}

void CRtspServerDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
