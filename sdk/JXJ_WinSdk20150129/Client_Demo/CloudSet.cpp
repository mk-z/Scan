// CloudSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "CloudSet.h"
#include "Pub_Data.h"

// CCloudSet 对话框


IMPLEMENT_DYNAMIC(CCloudSet, CDialog)

CCloudSet::CCloudSet(CWnd* pParent /*=NULL*/)
	: CDialog(CCloudSet::IDD, pParent)
{
	ZeroMemory(&m_ptzParamer, sizeof(m_ptzParamer));
}

CCloudSet::~CCloudSet()
{
	DestroyWindow();
}

void CCloudSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_Channel);
	DDX_Control(pDX, IDC_COMBO_CLOUDPROTOCOL, m_Protocol);
	DDX_Control(pDX, IDC_COMB_SERAILTYPE, m_SerialType);
	DDX_Control(pDX, IDC_COMB_CHECKBIT, m_CheckBit);
	DDX_Control(pDX, IDC_EDIT_RATE, m_CloudRate);
	DDX_Control(pDX, IDC_EDIT_DATABIT, m_CloudDataBit);
	DDX_Control(pDX, IDC_EDIT_STOPBIT, m_CloudStopBit);
	DDX_Control(pDX, IDC_EDIT_ADDRESS_STREAM, m_eAddressStream);
}


BEGIN_MESSAGE_MAP(CCloudSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CCloudSet::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CCloudSet::OnBnClickedButtonSave)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCloudSet 消息处理程序
BOOL CCloudSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Channel.AddString(_T("0"));
	m_Channel.SetCurSel(0);

	m_Protocol.AddString(_T("PELCO-D"));
	m_Protocol.AddString(_T("PELCO-P"));


	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_Protocol.AddString(_T("摇头机云台协议"));
		m_SerialType.AddString(_T("485串口"));
		m_SerialType.SetCurSel(0);

		m_CheckBit.AddString(_T("无校验"));
		m_CheckBit.AddString(_T("奇校验"));
		m_CheckBit.AddString(_T("偶校验"));
	}
	else
	{
		m_Protocol.AddString(_T("Shaking machine PTZ control protocol"));
		m_SerialType.AddString(_T("458 serial port"));
		m_SerialType.SetCurSel(0);

		m_CheckBit.AddString(_T("No parity"));
		m_CheckBit.AddString(_T("Odd parity"));
		m_CheckBit.AddString(_T("Even parity"));
	}


	return TRUE;
}

void CCloudSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PTZ_INFO, (char *)&m_ptzParamer, sizeof(m_ptzParamer),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

}

void CCloudSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	m_ptzParamer.protocol = m_Protocol.GetCurSel();
	m_ptzParamer.serial_no = m_SerialType.GetCurSel();
	CString strText = _T("");

	m_eAddressStream.GetWindowText(strText);
	m_ptzParamer.ptz_addr = _ttoi(strText);

	m_CloudRate.GetWindowText(strText);
	m_ptzParamer.baud_rate = _ttoi(strText);

	m_CloudDataBit.GetWindowText(strText);
	m_ptzParamer.data_bit = _ttoi(strText);

	m_CloudStopBit.GetWindowText(strText);
	m_ptzParamer.stop_bit = _ttoi(strText);

	m_ptzParamer.verify = m_CheckBit.GetCurSel();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PTZ_INFO, (char *)&m_ptzParamer, sizeof(m_ptzParamer), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}

}

int CCloudSet::ReFreshWindow()
{

	CString strText = _T("");

	strText.Format(_T("%d"), m_ptzParamer.baud_rate);
	m_CloudRate.SetWindowText(strText);

	strText.Format(_T("%d"), m_ptzParamer.data_bit);
	m_CloudDataBit.SetWindowText(strText);

	m_Protocol.SetCurSel(m_ptzParamer.protocol);
	m_SerialType.SetCurSel(m_ptzParamer.serial_no);

	
	strText.Format(_T("%d"), m_ptzParamer.ptz_addr);
	m_eAddressStream.SetWindowText(strText);

	

	strText.Format(_T("%d"), m_ptzParamer.stop_bit);
	m_CloudStopBit.SetWindowText(strText);

	m_CheckBit.SetCurSel(m_ptzParamer.verify);
	return 0;
}
HBRUSH CCloudSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//return (HBRUSH)::GetStockObject(WHITE_BRUSH);  
	return hbr;
}

void CCloudSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

