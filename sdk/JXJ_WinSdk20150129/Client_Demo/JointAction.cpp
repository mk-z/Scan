// m_jointAction.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "JointAction.h"
#include "Pub_Data.h"

// CJointAction 对话框


IMPLEMENT_DYNAMIC(CJointAction, CDialog)

CJointAction::CJointAction(CWnd* pParent /*=NULL*/)
	: CDialog(CJointAction::IDD, pParent)
{
	ZeroMemory(&m_jointAction, sizeof(m_jointAction));
	m_alarmType = 0;
}

CJointAction::~CJointAction()
{
	DestroyWindow();
}

void CJointAction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WRTNINGTYPE, m_JointWarnType);
	DDX_Control(pDX, IDC_CHECK_SUPPORTCHANNEL, m_JointVideoChannel);
	DDX_Control(pDX, IDC_CHECK_JOINTOUT, m_JointOut);
	DDX_Control(pDX, IDC_CHECK_JOINTTAKEPITCURECHANNEL, m_JointTakePic);
	DDX_Control(pDX, IDC_CHECK_JOINTCOICE, m_JointVoice);
	DDX_Control(pDX, IDC_CHECK_JOINTEMAIL, m_JointEmail);
	DDX_Control(pDX, IDC_EDIT_JOINTVIDEOTIME, m_eJointVideoTime);
	DDX_Control(pDX, IDC_EDIT_JOINTVOICE, m_eJointVoice);
	DDX_Control(pDX, IDC_EDIT_JOINTOUTTIME, m_JointOutTime);
	DDX_Control(pDX, IDC_EDIT_JOINTTAKELEVER, m_JointLever);
	DDX_Control(pDX, IDC_EDIT_JOINTPICTURECOUNT, m_JointPicCount);
	DDX_Control(pDX, IDC_CHECK_UPLOADFTP, m_PictureUpLoadFtp);
	DDX_Control(pDX, IDC_COMBO_CHOOSECHANNEL, m_chooseChannel);
	DDX_Control(pDX, IDC_STATIC_CHOOSECHANNEL, m_StaticText);


	DDX_Control(pDX, IDC_CHECK7, m_snapAction);
	DDX_Control(pDX, IDC_CHECK8, m_snapFtp);
	DDX_Control(pDX, IDC_CHECK10, m_recordAction);
	DDX_Control(pDX, IDC_CHECK9, m_outAction);
}


BEGIN_MESSAGE_MAP(CJointAction, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CJointAction::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CJointAction::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_WRTNINGTYPE, &CJointAction::OnCbnSelchangeComboWrtningtype)
	ON_CBN_SELCHANGE(IDC_COMBO_CHOOSECHANNEL, &CJointAction::OnCbnSelchangeComboChoosechannel)
END_MESSAGE_MAP()


// CJointAction 消息处理程序
BOOL CJointAction::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_JointWarnType.AddString(_T("移动侦测报警"));
		m_JointWarnType.AddString(_T("视频丢失报警"));
		m_JointWarnType.AddString(_T("遮挡报警"));
		m_JointWarnType.AddString(_T("探头报警"));
		m_JointWarnType.AddString(_T("智能分析视频诊断报警"));
		m_JointWarnType.AddString(_T("网络故障报警"));
		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 & DEV_CAP_PIR)
		{
			m_JointWarnType.AddString(_T("人体红外探测报警"));
		}
		
	}
	else
	{
		m_JointWarnType.AddString(_T("Motion detection"));
		m_JointWarnType.AddString(_T("Video loss"));
		m_JointWarnType.AddString(_T("Occlusion alarm"));
		m_JointWarnType.AddString(_T("IO alarm"));
		m_JointWarnType.AddString(_T("Intelligent video analysis of diagnosis and alarm"));
		m_JointWarnType.AddString(_T("Network fault alarm"));
		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].cap0 & DEV_CAP_PIR)
		{
			m_JointWarnType.AddString(_T("The human body infrared detection alarm"));
		}
	}
	

	m_recordAction.ShowWindow(SW_HIDE);
	m_outAction.ShowWindow(SW_HIDE);



 	m_chooseChannel.ShowWindow(SW_HIDE);
 	m_StaticText.ShowWindow(SW_HIDE);
	m_JointWarnType.SetCurSel(0);
	return TRUE;
}

void CJointAction::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_jointAction.alarm_type = m_JointWarnType.GetCurSel();

	m_jointAction.joint.joint_record_enable_channel = m_JointVideoChannel.GetCheck();
	m_jointAction.joint.joint_output_enable_channel = m_JointOut.GetCheck();
	m_jointAction.joint.joint_snap_enable_channel = m_JointTakePic.GetCheck();
	m_jointAction.joint.joint_beep_enable = m_JointVoice.GetCheck();
	m_jointAction.joint.joint_email_enable = m_JointEmail.GetCheck();

	if(m_PictureUpLoadFtp.GetCheck() == 1)
	{
		m_jointAction.process.joint_post_process[0] =  JOINT_SNAP_FTP;
	}
	else
	{
		m_jointAction.process.joint_post_process[0] = 0;
	}
	

	CString strText = _T("");

	m_eJointVideoTime.GetWindowText(strText);
	m_jointAction.joint.joint_record_second = _ttoi(strText);

	m_eJointVoice.GetWindowText(strText);
	m_jointAction.joint.joint_beep_second = _ttoi(strText);

	m_JointOutTime.GetWindowText(strText);
	m_jointAction.joint.joint_output_times = _ttoi(strText);

	m_JointLever.GetWindowText(strText);
	m_jointAction.joint.joint_snap_interval = _ttoi(strText);

	m_JointPicCount.GetWindowText(strText);
	m_jointAction.joint.joint_snap_times = _ttoi(strText);


	int ch_no = 0;
	if(m_JointWarnType.GetCurSel() == 3)
	{
		
		ch_no = m_chooseChannel.GetCurSel();
	}

	//////////////////////////////////报警联动
	m_alarmType = 0;


	if(m_snapAction.GetCheck() == 1)
	{
		m_alarmType |= JOINT_SNAP_SMTP;
	}
	if(m_snapFtp.GetCheck() == 1)
	{
		m_alarmType |= JOINT_SNAP_FTP;
	}

	m_jointAction.process.joint_post_process[0] = m_alarmType;


	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_JOINT_INFO, (char *)&m_jointAction, sizeof(m_jointAction), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return;
	}
}

void CJointAction::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_chooseChannel.GetCurSel() < 0 )
	{
		for(int i = 0; i< g_PubData.g_iIoWarningChannelNul; i++)
		{
			CString str = _T("");
			str.Format(_T("%d"), i);
			m_chooseChannel.AddString(str);
		}
		m_chooseChannel.SetCurSel(0);
	}

	ZeroMemory(&m_jointAction,sizeof(JJointAction));

	int ch_no = 0;
	if(m_JointWarnType.GetCurSel() == 3)
	{
		ch_no = m_chooseChannel.GetCurSel();
	}

	int iType = m_JointWarnType.GetCurSel();
	m_jointAction.alarm_type = iType;
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_JOINT_INFO, (char *)&m_jointAction, sizeof(m_jointAction),NULL, NULL );
	if( iRet != 0)
	{

		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();
}


int CJointAction::ReFreshWindow()
{
	m_JointWarnType.SetCurSel(m_jointAction.alarm_type);
	m_JointVideoChannel.SetCheck(m_jointAction.joint.joint_record_enable_channel);
	m_JointOut.SetCheck(m_jointAction.joint.joint_output_enable_channel);
	m_JointTakePic.SetCheck(m_jointAction.joint.joint_snap_enable_channel);
	m_JointVoice.SetCheck(m_jointAction.joint.joint_beep_enable);
	m_JointEmail.SetCheck(m_jointAction.joint.joint_email_enable);
	if(m_jointAction.process.joint_post_process[0] & JOINT_SNAP_FTP)
	{
		m_PictureUpLoadFtp.SetCheck(1);
	}
	else
	{
		m_PictureUpLoadFtp.SetCheck(0);
	}
	
	CString strText = _T("");

	strText.Format(_T("%d"), m_jointAction.joint.joint_record_second);
	m_eJointVideoTime.SetWindowText(strText);

	strText.Format(_T("%d"), m_jointAction.joint.joint_beep_second);
	m_eJointVoice.SetWindowText(strText);

	strText.Format(_T("%d"), m_jointAction.joint.joint_output_times);
	m_JointOutTime.SetWindowText(strText);

	strText.Format(_T("%d"), m_jointAction.joint.joint_snap_interval);
	m_JointLever.SetWindowText(strText);

	strText.Format(_T("%d"), m_jointAction.joint.joint_snap_times);
	m_JointPicCount.SetWindowText(strText);



	if(m_jointAction.process.joint_post_process[0] & JOINT_SNAP_SMTP)
		m_snapAction.SetCheck(1);
	else 
		m_snapAction.SetCheck(0);

	if(m_jointAction.process.joint_post_process[0] & JOINT_SNAP_FTP)
		m_snapFtp.SetCheck(1);
	else 
		m_snapFtp.SetCheck(0);

	return 0;
}
void CJointAction::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CJointAction::OnCbnSelchangeComboWrtningtype()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_JointWarnType.GetCurSel();
	ZeroMemory(&m_jointAction,sizeof(JJointAction));
	int ch_no = 0;
	if(m_JointWarnType.GetCurSel() == 3)
	{
		m_StaticText.ShowWindow(SW_SHOW);
		m_chooseChannel.ShowWindow(SW_SHOW);
		ch_no = m_chooseChannel.GetCurSel();
	}
	else
	{
		m_StaticText.ShowWindow(SW_HIDE);
		m_chooseChannel.ShowWindow(SW_HIDE);
	}
	m_jointAction.alarm_type = iIndex;
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_JOINT_INFO, (char *)&m_jointAction, sizeof(m_jointAction),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}
}

void CJointAction::OnCbnSelchangeComboChoosechannel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonFlash();
}
