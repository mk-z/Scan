// InterestArea.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "InterestArea.h"


// CInterestArea 对话框

IMPLEMENT_DYNAMIC(CInterestArea, CDialog)

CInterestArea::CInterestArea(CWnd* pParent /*=NULL*/)
	: CDialog(CInterestArea::IDD, pParent)
{
	ZeroMemory(&m_jRegion, sizeof(m_jRegion));
	m_bClear = FALSE;
}

CInterestArea::~CInterestArea()
{
	DestroyWindow();
}

void CInterestArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comChannel);
	DDX_Control(pDX, IDC_COMBO_QUALITY, m_VideoQuality);
	DDX_Control(pDX, IDC_CHECK_START, m_StartInterest);
	DDX_Control(pDX, IDC_CHECK_STARTPAINT, m_bStartPaint);
}


BEGIN_MESSAGE_MAP(CInterestArea, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CInterestArea::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CInterestArea::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, &CInterestArea::OnBnClickedButtonclear)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_STARTPAINT, &CInterestArea::OnBnClickedCheckStartpaint)
END_MESSAGE_MAP()


// CInterestArea 消息处理程序
BOOL CInterestArea::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comChannel.AddString(_T("0"));
	m_comChannel.SetCurSel(0);

	CString strText;
	for(int i = 1; i< 53; i++)
	{
		strText.Format(_T("%d"), i);
		m_VideoQuality.AddString(strText);
	}

	m_interestScreen.Create(IDD_DIALOG_INTERESTSCREEN, this);
	m_interestScreen.MoveWindow(30,100,520,300,TRUE);
	m_interestScreen.ShowWindow(SW_SHOW);

	return TRUE;
}

void CInterestArea::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if(g_PubData.g_iPlayWndFlag != 3 )
	{
		AVP_AddPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],NULL,m_interestScreen.GetSafeHwnd(),NULL,NULL);
	}
	
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_INTEREST_CODING, (char *)&m_jRegion, sizeof(m_jRegion),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshWindow();
	OnBnClickedCheckStartpaint();
}

void CInterestArea::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect cRect;
	m_interestScreen.GetWindowRect(cRect);
	int iDeviceWidth;
	int iDeviceHeight;
	iDeviceWidth = m_jRegion.max_width;
	iDeviceHeight = m_jRegion.max_height;

	m_jRegion.region.count = g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng];
	for(int i = 0; i < g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng]; i++)
	{

		m_jRegion.region.rect[i].left = (int)((m_interestScreen.m_StartPoint[i].x * iDeviceWidth) / cRect.Width());
		m_jRegion.region.rect[i].top = (int)((m_interestScreen.m_StartPoint[i].y * iDeviceHeight) / cRect.Height());
		m_jRegion.region.rect[i].right = (int)((m_interestScreen.m_EndPoint[i].x * iDeviceWidth) / cRect.Width());
		m_jRegion.region.rect[i].bottom = (int)((m_interestScreen.m_EndPoint[i].y *iDeviceHeight) /cRect.Height());
	}

	m_jRegion.enable = m_StartInterest.GetCheck();
	m_jRegion.qp_val = m_VideoQuality.GetCurSel();

	int iRet = -1;

	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_INTEREST_CODING, (char *)&m_jRegion, sizeof(m_jRegion), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return ;
	}

	
}


int CInterestArea::ReFreshWindow()
{

	g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng] = m_jRegion.region.count;
	m_StartInterest.SetCheck(m_jRegion.enable);
	m_VideoQuality.SetCurSel(m_jRegion.qp_val);

	for(int i = 0; i < g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng]; i++)
	{
		m_interestScreen.m_StartPoint[i].x = (m_jRegion.region.rect[i].left *520) / m_jRegion.max_width;
		m_interestScreen.m_StartPoint[i].y = (m_jRegion.region.rect[i].top *300)/ m_jRegion.max_height;
		m_interestScreen.m_EndPoint[i].x = (m_jRegion.region.rect[i].right *520) / m_jRegion.max_width;
		m_interestScreen.m_EndPoint[i].y = (m_jRegion.region.rect[i].bottom *300)/ m_jRegion.max_height;

	}
	return 0;
}
void CInterestArea::OnBnClickedButtonclear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_jRegion.region.count = g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng];
	for(int i = 0; i < g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng]; i++)
	{
		m_interestScreen.m_StartPoint[i].x = 0;
		m_interestScreen.m_StartPoint[i].y = 0;
		m_interestScreen.m_EndPoint[i].x = 0;
		m_interestScreen.m_EndPoint[i].y = 0;
	}
	
	m_jRegion.region.count = 0;
	g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng] = 0;
	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_INTEREST_CODING, (char *)&m_jRegion, sizeof(m_jRegion), TRUE);
	if( iRet != 0)
	{
		return ;
	}
	for(int i = 0; i< 4; i++)
	{
		m_interestScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
	}
}

void CInterestArea::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CInterestArea::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
void CInterestArea::OnBnClickedCheckStartpaint()
{
	// TODO: 在此添加控件通知处理程序代码
	int iDeviceWidth = m_jRegion.max_width;
	int iDeviceHeight = m_jRegion.max_height;

	if(m_bStartPaint.GetCheck() == 1)
	{
		//画出已经有的区域
		for(int i = 0; i < g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng]; i++)
		{
			m_interestScreen.DrawHideAlarmBorder(i,m_interestScreen.m_StartPoint[i].x, 
				m_interestScreen.m_StartPoint[i].y,
				(m_interestScreen.m_EndPoint[i].x - m_interestScreen.m_StartPoint[i].x), 
				(m_interestScreen.m_EndPoint[i].y - m_interestScreen.m_StartPoint[i].y));
		}

		g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng] = m_jRegion.region.count;
		for(int j = g_PubData.g_iCountInterset[g_PubData.g_iAttributeIng]; j < 4; j++)
		{
			m_interestScreen.m_cBorderDlg[j].ShowWindow(SW_HIDE);
		}
		m_interestScreen.m_bStartPaint = TRUE;
		g_PubData.g_bInterestDrawBorder = TRUE;
	}
	else
	{
		for(int i = 0; i< g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]; i++)
		{
			m_interestScreen.m_cBorderDlg[i].ShowWindow(SW_HIDE);
		}
		m_interestScreen.m_bStartPaint = FALSE;
		g_PubData.g_bInterestDrawBorder = FALSE;
	}
}

