// WarningUpload.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "WarningUpload.h"
#include "Pub_Data.h"


// CWarningUpload 对话框





IMPLEMENT_DYNAMIC(CWarningUpload, CDialog)

CWarningUpload::CWarningUpload(CWnd* pParent /*=NULL*/)
	: CDialog(CWarningUpload::IDD, pParent)
{

}

CWarningUpload::~CWarningUpload()
{
	DestroyWindow();
}

void CWarningUpload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_STARTWARNINGUPLOAD, m_StartWarningUpLoad);
	DDX_Control(pDX, IDC_EDIT_WARNINGDEVICEIP, m_WarningDeviceIp);
	DDX_Control(pDX, IDC_EDIT_WARNINGDEVICEPORT, m_WarningDevicePort);
	DDX_Control(pDX, IDC_COMBO_WARNINGPROTOCOLTYPE, m_WarningProtocolType);
}


BEGIN_MESSAGE_MAP(CWarningUpload, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CWarningUpload::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CWarningUpload::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CWarningUpload 消息处理程序
BOOL CWarningUpload::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_WarningProtocolType.AddString(_T("0"));
	m_WarningProtocolType.SetCurSel(0);

	return TRUE;
}

void CWarningUpload::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	m_AlarmUploadCfg.enable = m_StartWarningUpLoad.GetCheck();

	CString strText;
	m_WarningDeviceIp.GetWindowText(strText);
	memset(m_AlarmUploadCfg.host, '\0', sizeof(m_AlarmUploadCfg.host));
	memcpy(m_AlarmUploadCfg.host,strText.GetBuffer(0),strText.GetLength());
	strText.ReleaseBuffer();

	m_WarningDevicePort.GetWindowText(strText);
	m_AlarmUploadCfg.port = _ttoi(strText);

	m_AlarmUploadCfg.type = m_WarningProtocolType.GetCurSel();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ALARM_UPLOAD_CFG, (char *)&m_AlarmUploadCfg, sizeof(m_AlarmUploadCfg), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return;
	}
}

void CWarningUpload::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ALARM_UPLOAD_CFG, (char *)&m_AlarmUploadCfg, sizeof(m_AlarmUploadCfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();
}


int CWarningUpload::ReFreshWindow()
{
	
	m_StartWarningUpLoad.SetCheck(m_AlarmUploadCfg.enable);

	CString strText;
	strText.Format(_T("%s"), m_AlarmUploadCfg.host);
	m_WarningDeviceIp.SetWindowText(strText);

	strText.Format(_T("%d"), m_AlarmUploadCfg.port);
	m_WarningDevicePort.SetWindowText(strText);

	m_WarningProtocolType.SetCurSel(m_AlarmUploadCfg.type);

	return 0;
}
void CWarningUpload::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
