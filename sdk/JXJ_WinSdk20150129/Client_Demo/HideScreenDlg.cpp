// HideScreenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HideScreenDlg.h"
#include "Pub_Data.h"


#define  DRAWCOLOR RGB(255,0,0)


IMPLEMENT_DYNAMIC(CHideScreenDlg, CDialog)

CHideScreenDlg::CHideScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHideScreenDlg::IDD, pParent)
{
	for(int i= 0; i< 4; i++)
	{
		m_StartPoint[i] = FALSE;
		m_EndPoint[i] = 0;
		m_bStart[i] = 0;
	}

	m_bStartPaint = FALSE;
	
}

CHideScreenDlg::~CHideScreenDlg()
{
	DestroyWindow();
}

void CHideScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHideScreenDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CHideScreenDlg 消息处理程序

BOOL CHideScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	for(int i =0; i < 4; i++)
	{
		m_cBorderDlg[i].Create(IDD_DIALOG_BORDERDLG, this);
		m_cBorderDlg[i].SetOwner(this);
	}
	return TRUE;
}

void CHideScreenDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] >= 4 || !m_bStartPaint)
	{
		return;
	}
	m_bStart[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = TRUE;
	m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = point;
	m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = point;

	CDialog::OnLButtonDown(nFlags, point);
}

void CHideScreenDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] >= 4 || !m_bStart[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]])
	{
		return;
	}
	m_bStart[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = FALSE;

	//消隐最后的一个矩形（其原理跟拖动时矩形框绘制原理相同）
	CClientDC dc(this);
	dc.SetROP2(R2_BLACK); 
	dc.SelectStockObject(BLACK_BRUSH);
	dc.Rectangle(CRect(m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]]
	,m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]]));

	int x = m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].x;
	int y = m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].y;


	DrawHideAlarmBorder(g_PubData.g_iCountHide[g_PubData.g_iAttributeIng],
		m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].x,
		m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].y,
		point.x - m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].x,
		point.y - m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].y);

	g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] ++;

	CDialog::OnLButtonUp(nFlags, point);
}

void CHideScreenDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CClientDC dc(this);   //获取设备句柄

	//SetRop2 Specifies the new drawing mode.(MSDN)
	//R2_NOT   Pixel is the inverse of the screen color.(MSDN)
	//即：该函数用来定义绘制的颜色，而该参数则将颜色设置为原屏幕颜色的反色
	//这样，如果连续绘制两次的话，就可以恢复原来屏幕的颜色了（如下）
	//但是，这里的连续两次绘制却不是在一次消息响应中完成的
	//而是在第一次拖动响应的绘制可以显示（也就是看到的），第二次拖动绘制实现擦出（也就看不到了）
	dc.SetROP2(R2_BLACK);   //此为关键!!!
	dc.SelectStockObject(BLACK_BRUSH ); //使用画刷
	if (TRUE == m_bStart[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]])   //根据是否有单击判断是否可以画矩形
	{
		dc.Rectangle(CRect(m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]]
		,m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]])); 
		dc.Rectangle(CRect(m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]]
		,point));
		m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = point;
	}



	CDialog::OnMouseMove(nFlags, point);
}



void CHideScreenDlg::DrawHideAlarmBorder(int i, int iX, int iY, int iW, int iH)
{
	//m_cBorderDlg[i]->MoveWindow(iX, iY, iW, iH, TRUE);
	CRect cRect;
	this->GetClientRect(cRect);
	ClientToScreen(cRect);

	m_cBorderDlg[i].MoveWindow(cRect.left + iX, cRect.top + iY, iW, iH, TRUE);
	m_cBorderDlg[i].ShowWindow(SW_SHOW);
}


void CHideScreenDlg::RegDrawCallBack()
{
	//HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), DrawCB, this);
}

void CHideScreenDlg::ExitDrawCallBack()
{
	//HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), NULL, this);
}




void CALLBACK CHideScreenDlg::DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser)
{
// 	CRect cRect;
// 	gHideScreen->GetWindowRect(cRect);
// 	CPoint maxPoint(cRect.Width(), cRect.Height());
// 	if(g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] > 0)
// 	{
// 		
// 		for(int i = 0; i< g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]; i++)
// 		{
// 			CPoint point1(gHideScreen->m_StartPoint[i].x, gHideScreen->m_StartPoint[i].y);
// 			CPoint point2(gHideScreen->m_EndPoint[i].x, gHideScreen->m_StartPoint[i].y);
// 			CPoint point3(gHideScreen->m_EndPoint[i].x, gHideScreen->m_EndPoint[i].y);
// 			CPoint point4(gHideScreen->m_StartPoint[i].x, gHideScreen->m_EndPoint[i].y);
// 			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point1, &point2, &maxPoint);
// 			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point2, &point3, &maxPoint);
// 			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point3, &point4, &maxPoint);
// 			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point4, &point1, &maxPoint);
// 		}
// 	}
}