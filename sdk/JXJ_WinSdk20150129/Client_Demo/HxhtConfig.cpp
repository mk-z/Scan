// HxhtConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HxhtConfig.h"
#include "Pub_Data.h"

// CHxhtConfig 对话框


IMPLEMENT_DYNAMIC(CHxhtConfig, CDialog)

CHxhtConfig::CHxhtConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CHxhtConfig::IDD, pParent)
{
	ZeroMemory(&m_HxhtConfig, sizeof(m_HxhtConfig));
}

CHxhtConfig::~CHxhtConfig()
{
}

void CHxhtConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DEVICEPUID, m_eDevicePuid);
	DDX_Control(pDX, IDC_EDIT_SERVERADDR, m_eServerAddr);
	DDX_Control(pDX, IDC_EDIT_SERVERPORT, m_eServerPort);
	DDX_Control(pDX, IDC_EDIT_VIDEOPORT, m_eVideoPort);
	DDX_Control(pDX, IDC_EDIT_AUDIOPORT, m_eAudioPort);
	DDX_Control(pDX, IDC_EDIT_MESSAGEPORT, m_eMessagePort);
	DDX_Control(pDX, IDC_EDIT_PLAYBACKPORT, m_ePlayBackPort);
	DDX_Control(pDX, IDC_EDIT_MAXVIDEOCOUNT, m_eMaxVideoCount);
	DDX_Control(pDX, IDC_COMBO_VIDEOSENDMODE, m_bVideoStreamMode);
	DDX_Control(pDX, IDC_CHECK_ENABLEPICTURE, m_bCheckEnablePicture);
	DDX_Control(pDX, IDC_CHECK_AUTOSERVERPORT, m_bCheckAudioSerPort);
	DDX_Control(pDX, IDC_COMBO_MAT, m_bNat);
}


BEGIN_MESSAGE_MAP(CHxhtConfig, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CHxhtConfig::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CHxhtConfig::OnBnClickedButtonFlash)
END_MESSAGE_MAP()


// CHxhtConfig 消息处理程序
BOOL CHxhtConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_bVideoStreamMode.AddString(_T("一般模式"));
		m_bVideoStreamMode.AddString(_T("天翼手机监控模式"));

		m_bNat.AddString(_T("开启"));
		m_bNat.AddString(_T("关闭"));
	}
	else
	{
		m_bVideoStreamMode.AddString(_T("Pattern"));
		m_bVideoStreamMode.AddString(_T("Tianyi mobile phone monitoring mode"));

		m_bNat.AddString(_T("Open"));
		m_bNat.AddString(_T("Close"));
	}
	

	return TRUE;
}

void CHxhtConfig::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText = _T("");
	m_eDevicePuid.GetWindowText(strText);
	memset(m_HxhtConfig.dev_id, '\0', sizeof(m_HxhtConfig.dev_id));
	memcpy(m_HxhtConfig.dev_id, strText.GetBuffer(0), strText.GetLength());
	
	m_eServerAddr.GetWindowText(strText);
	memset(m_HxhtConfig.svr_ip, '\0', sizeof(m_HxhtConfig.svr_ip));
	memcpy(m_HxhtConfig.svr_ip, strText.GetBuffer(0), strText.GetLength());
	
	strText.ReleaseBuffer();

	strText.Format(_T("%d"), m_HxhtConfig.svr_port);
	m_eServerPort.SetWindowText(strText);

	m_eVideoPort.GetWindowText(strText);
	m_HxhtConfig.video_port = _ttoi(strText);

	m_eAudioPort.GetWindowText(strText);
	m_HxhtConfig.audio_port = _ttoi(strText);

	m_eMessagePort.GetWindowText(strText);
	m_HxhtConfig.msg_port = _ttoi(strText);

	m_ePlayBackPort.GetWindowText(strText);
	m_HxhtConfig.pb_port = _ttoi(strText);

	m_eMaxVideoCount.GetWindowText(strText);
	m_HxhtConfig.max_video_conn = _ttoi(strText);

	m_HxhtConfig.video_trans_mode = m_bVideoStreamMode.GetCurSel();

	m_HxhtConfig.pic_upload = m_bCheckEnablePicture.GetCheck();

	m_HxhtConfig.port_map = m_bCheckAudioSerPort.GetCheck();

	m_HxhtConfig.dev_after_nat = m_bNat.GetCurSel();


	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HXHT_CONFIG, (char *)&m_HxhtConfig, sizeof(m_HxhtConfig),TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}
}

void CHxhtConfig::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HXHT_CONFIG, (char *)&m_HxhtConfig, sizeof(m_HxhtConfig),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshWindow();
}

int CHxhtConfig::ReFreshWindow()
{

	CString strText = _T("");
	strText.Format(_T("%s"), m_HxhtConfig.dev_id);
	m_eDevicePuid.SetWindowText(strText);

	strText.Format(_T("%s"), m_HxhtConfig.svr_ip);
	m_eServerAddr.SetWindowText(strText);

	strText.Format(_T("%d"), m_HxhtConfig.svr_port);
	m_eServerPort.SetWindowText(strText);

	strText.Format(_T("%d"), m_HxhtConfig.video_port);
	m_eVideoPort.SetWindowText(strText);

	strText.Format(_T("%d"), m_HxhtConfig.audio_port);
	m_eAudioPort.SetWindowText(strText);

	strText.Format(_T("%d"), m_HxhtConfig.msg_port);
	m_eMessagePort.SetWindowText(strText);

	strText.Format(_T("%d"), m_HxhtConfig.pb_port);
	m_ePlayBackPort.SetWindowText(strText);

	strText.Format(_T("%d"), m_HxhtConfig.max_video_conn);
	m_eMaxVideoCount.SetWindowText(strText);
	
	m_bVideoStreamMode.SetCurSel(m_HxhtConfig.video_trans_mode);

	m_bCheckEnablePicture.SetCheck(m_HxhtConfig.pic_upload);

	m_bCheckAudioSerPort.SetCheck(m_HxhtConfig.port_map);

	m_bNat.SetCurSel(m_HxhtConfig.dev_after_nat);

	return 0;
}
