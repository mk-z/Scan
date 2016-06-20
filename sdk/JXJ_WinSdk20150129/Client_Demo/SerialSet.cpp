// SerialSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "SerialSet.h"
#include "Pub_Data.h"

// CSerialSet 对话框



IMPLEMENT_DYNAMIC(CSerialSet, CDialog)

CSerialSet::CSerialSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialSet::IDD, pParent)
{

}

CSerialSet::~CSerialSet()
{
	DestroyWindow();
}

void CSerialSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB_SERAILTYPE, m_SerialType);
	DDX_Control(pDX, IDC_COMB_CHECKBIT, m_CheckBit);
	DDX_Control(pDX, IDC_EDIT_DATABIT, m_DataBit);
	DDX_Control(pDX, IDC_EDIT_STOPBIT, m_StopBit);
	DDX_Control(pDX, IDC_EDIT_BAUDRATE, m_BaudRate);
}


BEGIN_MESSAGE_MAP(CSerialSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CSerialSet::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSerialSet::OnBnClickedButtonSave)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSerialSet 消息处理程序
BOOL CSerialSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_SerialType.AddString(_T("485串口"));
		m_SerialType.SetCurSel(0);

		m_CheckBit.AddString(_T("无校验"));
		m_CheckBit.AddString(_T("奇校验"));
		m_CheckBit.AddString(_T("偶校验"));
	}
	else
	{
		m_SerialType.AddString(_T("458 serial port"));
		m_SerialType.SetCurSel(0);

		m_CheckBit.AddString(_T("No parity"));
		m_CheckBit.AddString(_T("Odd parity"));
		m_CheckBit.AddString(_T("Even parity"));
	}
	

//	OnBnClickedButtonFlash();
	return TRUE;
}

void CSerialSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_SERIAL_INFO, (char *)&m_serialParam, sizeof(m_serialParam),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();
}

void CSerialSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_serialParam.serial_no = m_SerialType.GetCurSel();
	CString strText = _T("");
	m_BaudRate.GetWindowText(strText);
	m_serialParam.baud_rate = _ttoi(strText);
	m_DataBit.GetWindowText(strText);
	m_serialParam.data_bit = _ttoi(strText);
	m_StopBit.GetWindowText(strText);
	m_serialParam.stop_bit = _ttoi(strText);
	m_serialParam.verify = m_CheckBit.GetCurSel();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_SERIAL_INFO, (char *)&m_serialParam, sizeof(m_serialParam), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return;
	}
}


int CSerialSet::ReFreshWindow()
{

	m_SerialType.SetCurSel(m_serialParam.serial_no);
	CString strText = _T("");
	strText.Format(_T("%d"), m_serialParam.baud_rate);
	m_BaudRate.SetWindowText(strText);
	strText.Format(_T("%d"), m_serialParam.data_bit);
	m_DataBit.SetWindowText(strText);
	strText.Format(_T("%d"), m_serialParam.stop_bit);
	m_StopBit.SetWindowText(strText);
	m_CheckBit.SetCurSel(m_serialParam.verify);

	return 0;
}

void CSerialSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
