// PeaJointAction.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "PeaJointAction.h"
#include "Pub_Data.h"
// CPeaJointAction 对话框

IMPLEMENT_DYNAMIC(CPeaJointAction, CDialog)

CPeaJointAction::CPeaJointAction(CWnd* pParent /*=NULL*/)
	: CDialog(CPeaJointAction::IDD, pParent)
{
	
}

CPeaJointAction::~CPeaJointAction()
{
}

void CPeaJointAction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_SUPPORTCHANNEL, m_JointActionChannel);
	DDX_Control(pDX, IDC_EDIT_JOINTVIDEOTIME, m_JointRecTime);
	DDX_Control(pDX, IDC_CHECK_JOINTOUT, m_JointOut);
	DDX_Control(pDX, IDC_EDIT_JOINTOUTTIME, m_JointOutTime);
	DDX_Control(pDX, IDC_CHECK_JOINTTAKEPITCURECHANNEL, m_JointTakePicChannel);
	DDX_Control(pDX, IDC_EDIT_JOINTTAKELEVER, m_JoinTakePicLever);
	DDX_Control(pDX, IDC_CHECK_UPLOADFTP, m_TakePicFtpUp);
	DDX_Control(pDX, IDC_EDIT_JOINTPICTURECOUNT, m_TakePicCount);
	DDX_Control(pDX, IDC_CHECK_JOINTCOICE, m_JointVoice);
	DDX_Control(pDX, IDC_EDIT_JOINTVOICE, m_JointVoiceTime);
	DDX_Control(pDX, IDC_CHECK_JOINTEMAIL, m_JointEmail);
}


BEGIN_MESSAGE_MAP(CPeaJointAction, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPeaJointAction::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTONCANCEL, &CPeaJointAction::OnBnClickedButtoncancel)
END_MESSAGE_MAP()


// CPeaJointAction 消息处理程序
BOOL CPeaJointAction::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strText = _T("");
	
	m_JointActionChannel.SetCheck(g_PubData.m_iJointActionChannel);

	strText.Format(_T("%d"),g_PubData.m_iJointRecTime);
	m_JointRecTime.SetWindowText(strText);

	m_JointOut.SetCheck(g_PubData.m_iJointOut);

	strText.Format(_T("%d"),g_PubData.m_iJointOutTime);
	m_JointOutTime.SetWindowText(strText);

	m_JointTakePicChannel.SetCheck(g_PubData.m_iJointTakePicChannel);

	strText.Format(_T("%d"), g_PubData.m_iJoinTakePicLever);
	m_JoinTakePicLever.SetWindowText(strText);

	m_TakePicFtpUp.SetCheck(g_PubData.m_iTakePicFtpUp);

	strText.Format(_T("%d"), g_PubData.m_iTakePicCount);
	m_TakePicCount.SetWindowText(strText);

	m_JointVoice.SetCheck(g_PubData.m_iJointVoice);

	strText.Format(_T("%d"), g_PubData.m_iJointVoiceTime);
	m_JointVoiceTime.SetWindowText(strText);

	m_JointEmail.SetCheck(g_PubData.m_iJointEmail);

	

	return TRUE;
}

void CPeaJointAction::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strText = _T("");

	g_PubData.m_iJointActionChannel = m_JointActionChannel.GetCheck();

	m_JointRecTime.GetWindowText(strText);
	g_PubData.m_iJointRecTime = _ttoi(strText);

	g_PubData.m_iJointOut = m_JointOut.GetCheck();

	m_JointOutTime.GetWindowText(strText);
	g_PubData.m_iJointOutTime = _ttoi(strText);

	g_PubData.m_iJointTakePicChannel = m_JointTakePicChannel.GetCheck();

	m_JoinTakePicLever.GetWindowText(strText);
	g_PubData.m_iJoinTakePicLever = _ttoi(strText);

	g_PubData.m_iTakePicFtpUp = m_TakePicFtpUp.GetCheck();

	
	m_TakePicCount.GetWindowText(strText);
	g_PubData.m_iTakePicCount = _ttoi(strText);

	g_PubData.m_iJointVoice = m_JointVoice.GetCheck();

	m_JointVoiceTime.GetWindowText(strText);
	g_PubData.m_iJointVoiceTime = _ttoi(strText);

	g_PubData.m_iJointEmail = m_JointEmail.GetCheck();

	CDialog::OnOK();
}

void CPeaJointAction::OnBnClickedButtoncancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
