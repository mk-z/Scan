// VideoHide.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "VideoHide.h"
#include "Pub_Data.h"

// CVideoHide 对话框


IMPLEMENT_DYNAMIC(CVideoHide, CDialog)

CVideoHide::CVideoHide(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoHide::IDD, pParent)
{
	m_bClear = FALSE;
}

CVideoHide::~CVideoHide()
{
	DestroyWindow();
}

void CVideoHide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comChannel);
	DDX_Control(pDX, IDC_CHECK_STARTHIDE, m_bStartHide);
	DDX_Control(pDX, IDC_CHECK_STARTPAINT, m_bStartPaint);
}


BEGIN_MESSAGE_MAP(CVideoHide, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CVideoHide::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CVideoHide::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CVideoHide::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_CHECK_STARTPAINT, &CVideoHide::OnBnClickedCheckStartpaint)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CVideoHide 消息处理程序
BOOL CVideoHide::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comChannel.AddString(_T("0"));
	m_comChannel.SetCurSel(0);

	m_HideScreen.Create(IDD_DIALOG_HIDESCREEN, this);
	m_HideScreen.MoveWindow(30,60,520,300,TRUE);
	m_HideScreen.ShowWindow(SW_SHOW);

//	OnBnClickedButtonFlash();
	

	return TRUE;
}

void CVideoHide::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代
	if(g_PubData.g_iPlayWndFlag != 1 )
	{
		AVP_AddPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],NULL, m_HideScreen.GetSafeHwnd(),NULL,NULL);
	}
	
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HIDE_INFO, (char *)&m_hideParam, sizeof(m_hideParam),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshWindow();
	for(int i = 0; i < 4; i++)
	{
		m_HideScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
	}


}

void CVideoHide::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect cRect;
	m_HideScreen.GetWindowRect(cRect);
	int iDeviceWidth;
	int iDeviceHeight;
	iDeviceWidth = m_hideParam.max_width;
	iDeviceHeight = m_hideParam.max_height;

	m_hideParam.hide_area.count = g_PubData.g_iCountHide[g_PubData.g_iAttributeIng];
	for(int i = 0; i < g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]; i++)
	{
		m_iLeft = m_HideScreen.m_StartPoint[i].x;
		m_iTop = m_HideScreen.m_StartPoint[i].y;
		m_iRight = m_HideScreen.m_EndPoint[i].x;
		m_iBottom = m_HideScreen.m_EndPoint[i].y;

		m_hideParam.hide_area.rect[i].left = (m_iLeft * iDeviceWidth) / cRect.Width();
		m_hideParam.hide_area.rect[i].top = (m_iTop * iDeviceHeight) / cRect.Height();
		m_hideParam.hide_area.rect[i].right = (m_iRight * iDeviceWidth) / cRect.Width();
		m_hideParam.hide_area.rect[i].bottom = (m_iBottom * iDeviceHeight) / cRect.Height();;
	}

	m_hideParam.hide_enable = m_bStartHide.GetCheck();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HIDE_INFO, (char *)&m_hideParam, sizeof(m_hideParam), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}

	for(int i = 0; i < 4; i++)
	{
		m_HideScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
	}

	
}


int CVideoHide::ReFreshWindow()
{
	m_bStartHide.SetCheck(m_hideParam.hide_enable);
	
	g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] = m_hideParam.hide_area.count;
	for(int i = 0; i < g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]; i++)
	{
		m_HideScreen.m_StartPoint[i].x = (m_hideParam.hide_area.rect[i].left *520) / m_hideParam.max_width;
		m_HideScreen.m_StartPoint[i].y = (m_hideParam.hide_area.rect[i].top *300)/ m_hideParam.max_height;
		m_HideScreen.m_EndPoint[i].x = (m_hideParam.hide_area.rect[i].right *520) / m_hideParam.max_width;
		m_HideScreen.m_EndPoint[i].y = (m_hideParam.hide_area.rect[i].bottom *300)/ m_hideParam.max_height;
	}
	return 0;
}
void CVideoHide::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码

	m_hideParam.hide_area.count = g_PubData.g_iCountHide[g_PubData.g_iAttributeIng];
	for(int i = 0; i < g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]; i++)
	{
		m_HideScreen.m_StartPoint[i].x = 0;
		m_HideScreen.m_StartPoint[i].y = 0;
		m_HideScreen.m_EndPoint[i].x = 0;
		m_HideScreen.m_EndPoint[i].y = 0;
	}

	g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] = 0;
	m_hideParam.hide_area.count = 0;

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HIDE_INFO, (char *)&m_hideParam, sizeof(m_hideParam), TRUE);
	if( iRet != 0)
	{
		//AfxMessageBox(_T("清空失败"));
		return ;
	}

	for(int i = 0; i < 4; i++)
	{
		m_HideScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
	}
}

void CVideoHide::OnBnClickedCheckStartpaint()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_bStartPaint.GetCheck() == 1)
	{
		g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] = m_hideParam.hide_area.count;
		m_HideScreen.m_bStartPaint = TRUE;
		g_PubData.g_bHideDrawBorder = TRUE;
	}
	else
	{
		m_HideScreen.m_bStartPaint = FALSE;
		g_PubData.g_bHideDrawBorder = FALSE;
	}
	for(int i = 0; i < 4; i++)
	{
		m_HideScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
	}

}

void CVideoHide::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CVideoHide::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	
}
