// PerOscScreen.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "PerOscScreen.h"
#include "Pub_Data.h"

#define  DRAWCOLOR RGB(255,0,0)

// CPerOscScreen 对话框
CPerOscScreen *gPeroscScreen = NULL;

IMPLEMENT_DYNAMIC(CPerOscScreen, CDialog)

CPerOscScreen::CPerOscScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CPerOscScreen::IDD, pParent)
{
	gPeroscScreen = this;
}

CPerOscScreen::~CPerOscScreen()
{
//	//HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], NULL, NULL);
	DestroyWindow();
}

void CPerOscScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPerOscScreen, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CPerOscScreen 消息处理程序

BOOL CPerOscScreen::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ruleID = 0;
	m_ruleParam = 0;
	m_lineStartPoint = 0;
	m_lineEndPoint = 0;
	m_bStartLine = FALSE;
	m_bKeepWatch = FALSE;
	m_bLeft = FALSE;
	m_bTake = FALSE;
	m_bLbuttonUp = FALSE;
	m_bDBlbuttonDown = FALSE;
	m_iCountKeepWatchPoints = 0;
	m_iCountLeftPoints = 0;
	m_iCountTakePoints = 0;
	for(int i = 0; i < 0/*J_SDK_MAX_POLYGON_POINT*/; i++)
	{
		m_KeepWatchPoints[i] = 0;
		m_LeftPoints[i] = 0;
		m_TakePoints[i] = 0;
	}
	
	return TRUE;
}
void CPerOscScreen::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if(m_ruleParam == 0)
	{	
		m_bStartLine = TRUE;
		m_lineStartPoint = point;
		m_lineEndPoint = point;
	}
	else if(m_ruleParam == 1)
	{
		if(m_bDBlbuttonDown)
		{
			m_bDBlbuttonDown = FALSE;
			m_iCountKeepWatchPoints = 0;
			for(int i = 0; i < 0/*J_SDK_MAX_POLYGON_POINT*/; i++)
			{
				m_KeepWatchPoints[i] = 0;
			}

		}
		m_bKeepWatch = TRUE;
		if(m_iCountKeepWatchPoints == 0)
		{	
			m_KeepWatchPoints[m_iCountKeepWatchPoints] = point;
		}

		if(m_iCountKeepWatchPoints >= 7)
		{
			m_bKeepWatch = FALSE;
			return;
		}
	}
	else if(m_ruleParam == 2)
	{
		if(m_bDBlbuttonDown)
		{
			m_bDBlbuttonDown = FALSE;
			m_iCountLeftPoints = 0;
			for(int i = 0; i < 0/*J_SDK_MAX_POLYGON_POINT*/; i++)
			{
				m_LeftPoints[i] = 0;
			}
		}
		m_bLeft = TRUE;
		if(m_iCountLeftPoints == 0)
		{	
			m_LeftPoints[m_iCountLeftPoints] = point;
		}
		if(m_iCountLeftPoints >= 7)
		{
			m_bLeft = FALSE;
			return;
		}
			
	}
	else if(m_ruleParam == 3)
	{
		if(m_bDBlbuttonDown)
		{
			m_bDBlbuttonDown = FALSE;
			m_iCountTakePoints = 0;
			for(int i = 0; i < 0/*J_SDK_MAX_POLYGON_POINT*/; i++)
			{
				m_TakePoints[i] = 0;
			}
		}
		m_bTake = TRUE;
		if(m_iCountTakePoints == 0)
		{	
			m_TakePoints[m_iCountTakePoints] = point;
		}
		if(m_iCountTakePoints >= 7)
		{
			m_bTake = FALSE;
			return;
		}
	}
//	//HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], DrawCB, NULL);
	CDialog::OnLButtonDown(nFlags, point);
}

void CPerOscScreen::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC * pdc = GetWindowDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, GetSystemMetrics(SM_CXDRAG), RGB(75, 215, 40));
	CPen *pOldpen = pdc->SelectObject(&pen);
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);
	
	if(m_bStartLine && m_ruleParam == 0)
	{
		pdc->MoveTo(m_lineStartPoint);
		pdc->LineTo(point);
		m_lineEndPoint = point;
		m_bStartLine = FALSE;
	}
	else if(m_bKeepWatch && m_ruleParam == 1)
	{
		pdc->MoveTo(m_KeepWatchPoints[m_iCountKeepWatchPoints]);
		pdc->LineTo(point);
		m_iCountKeepWatchPoints ++;
		m_KeepWatchPoints[m_iCountKeepWatchPoints] = point;
	}
	else if(m_bLeft && m_ruleParam == 2)
	{
		pdc->MoveTo(m_LeftPoints[m_iCountLeftPoints]);
		pdc->LineTo(point);
		m_iCountLeftPoints ++;
		m_LeftPoints[m_iCountLeftPoints] = point;
	}
	else if(m_bTake && m_ruleParam == 3)
	{
		pdc->MoveTo(m_TakePoints[m_iCountTakePoints]);
		pdc->LineTo(point);
		pdc->MoveTo(m_TakePoints[m_iCountTakePoints]);
		m_iCountTakePoints ++;
		m_TakePoints[m_iCountTakePoints] = point;
	}

	
	CDialog::OnLButtonUp(nFlags, point);
}

void CPerOscScreen::OnMouseMove(UINT nFlags, CPoint point)
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
	dc.SelectStockObject(NULL_BRUSH ); //使用画刷

	CDC * pdc = GetWindowDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, GetSystemMetrics(SM_CXDRAG), RGB(75, 215, 40));
	CPen *pOldpen = pdc->SelectObject(&pen);
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);
	
	if (m_bStartLine && m_ruleParam == 0)   //根据是否有单击判断是否可以画矩形
	{
		pdc->MoveTo(m_lineStartPoint);
		pdc->LineTo(point);	
	}
	else if(m_bKeepWatch && m_ruleParam == 1)
	{
		pdc->MoveTo(m_KeepWatchPoints[m_iCountKeepWatchPoints]);
		pdc->LineTo(point);
	}
	else if(m_bLeft && m_ruleParam == 2)
	{
		pdc->MoveTo(m_LeftPoints[m_iCountLeftPoints]);
		pdc->LineTo(point);
	}
	else if(m_bTake && m_ruleParam == 3)
	{
		pdc->MoveTo(m_TakePoints[m_iCountTakePoints]);
		pdc->LineTo(point);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CPerOscScreen::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bDBlbuttonDown = TRUE;
	m_bKeepWatch = FALSE;
	m_bLeft = FALSE;
	m_bTake = FALSE;
	/*
	if(m_ruleParam == 1)
	{
		m_KeepWatchPoints[m_iCountKeepWatchPoints].x  = 0;
		m_KeepWatchPoints[m_iCountKeepWatchPoints].y  = 0;
		m_iCountKeepWatchPoints --;
	}
	if(m_ruleParam == 2)
	{
		m_LeftPoints[m_iCountLeftPoints].x = 0;
		m_LeftPoints[m_iCountLeftPoints].y = 0;
		m_iCountLeftPoints -- ;
	}
	if(m_ruleParam == 3)
	{
		m_TakePoints[m_iCountTakePoints].x = 0;
		m_TakePoints[m_iCountTakePoints].y = 0;
		m_iCountTakePoints -- ;
	}*/
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CPerOscScreen::RegDrawCallBack()
{
	//HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), DrawCB, this);
}

void CPerOscScreen::ExitDrawCallBack()
{
	//HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), NULL, this);
}

void CALLBACK CPerOscScreen::DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser)
{
	CRect cRect;
	gPeroscScreen->GetWindowRect(cRect);
	CPoint maxPoint(cRect.Width(), cRect.Height());
	if(gPeroscScreen->m_ruleParam == 0)
	{
		//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_lineStartPoint,&gPeroscScreen->m_lineEndPoint,&maxPoint);
	}
	if(gPeroscScreen->m_ruleParam == 1)
	{
		if(gPeroscScreen->m_iCountKeepWatchPoints > 0)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_KeepWatchPoints[0],&gPeroscScreen->m_KeepWatchPoints[1],&maxPoint);
		}
		if(gPeroscScreen->m_iCountKeepWatchPoints > 1)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_KeepWatchPoints[1],&gPeroscScreen->m_KeepWatchPoints[2],&maxPoint);
		}
		if(gPeroscScreen->m_iCountKeepWatchPoints > 2)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_KeepWatchPoints[2],&gPeroscScreen->m_KeepWatchPoints[3],&maxPoint);
		}
		if(gPeroscScreen->m_iCountKeepWatchPoints > 3)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_KeepWatchPoints[3],&gPeroscScreen->m_KeepWatchPoints[4],&maxPoint);
		}
		if(gPeroscScreen->m_iCountKeepWatchPoints > 4)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_KeepWatchPoints[4],&gPeroscScreen->m_KeepWatchPoints[5],&maxPoint);
		}
		if(gPeroscScreen->m_iCountKeepWatchPoints > 5)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_KeepWatchPoints[5],&gPeroscScreen->m_KeepWatchPoints[6],&maxPoint);
		}
		if(gPeroscScreen->m_iCountKeepWatchPoints > 6)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_KeepWatchPoints[6],&gPeroscScreen->m_KeepWatchPoints[7],&maxPoint);
		}
		if(gPeroscScreen->m_bDBlbuttonDown)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_KeepWatchPoints[gPeroscScreen->m_iCountKeepWatchPoints],&gPeroscScreen->m_KeepWatchPoints[0],&maxPoint);
		}
	}
	if(gPeroscScreen->m_ruleParam == 2)
	{
		if(gPeroscScreen->m_iCountLeftPoints > 0)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_LeftPoints[0],&gPeroscScreen->m_LeftPoints[1],&maxPoint);
		}
		if(gPeroscScreen->m_iCountLeftPoints > 1)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_LeftPoints[1],&gPeroscScreen->m_LeftPoints[2],&maxPoint);
		}
		if(gPeroscScreen->m_iCountLeftPoints > 2)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_LeftPoints[2],&gPeroscScreen->m_LeftPoints[3],&maxPoint);
		}
		if(gPeroscScreen->m_iCountLeftPoints > 3)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_LeftPoints[3],&gPeroscScreen->m_LeftPoints[4],&maxPoint);
		}
		if(gPeroscScreen->m_iCountLeftPoints > 4)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_LeftPoints[4],&gPeroscScreen->m_LeftPoints[5],&maxPoint);
		}
		if(gPeroscScreen->m_iCountLeftPoints > 5)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_LeftPoints[5],&gPeroscScreen->m_LeftPoints[6],&maxPoint);
		}
		if(gPeroscScreen->m_iCountLeftPoints > 6)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_LeftPoints[6],&gPeroscScreen->m_LeftPoints[7],&maxPoint);
		}
		if(gPeroscScreen->m_bDBlbuttonDown)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_LeftPoints[gPeroscScreen->m_iCountLeftPoints],&gPeroscScreen->m_LeftPoints[0],&maxPoint);
		}
	}
	if(gPeroscScreen->m_ruleParam == 3)
	{
		if(gPeroscScreen->m_iCountTakePoints > 0)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_TakePoints[0],&gPeroscScreen->m_TakePoints[1],&maxPoint);
		}
		if(gPeroscScreen->m_iCountTakePoints > 1)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_TakePoints[1],&gPeroscScreen->m_TakePoints[2],&maxPoint);
		}
		if(gPeroscScreen->m_iCountTakePoints > 2)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_TakePoints[2],&gPeroscScreen->m_TakePoints[3],&maxPoint);
		}
		if(gPeroscScreen->m_iCountTakePoints > 3)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_TakePoints[3],&gPeroscScreen->m_TakePoints[4],&maxPoint);
		}
		if(gPeroscScreen->m_iCountTakePoints > 4)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_TakePoints[4],&gPeroscScreen->m_TakePoints[5],&maxPoint);
		}
		if(gPeroscScreen->m_iCountTakePoints > 5)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_TakePoints[5],&gPeroscScreen->m_TakePoints[6],&maxPoint);
		}
		if(gPeroscScreen->m_iCountTakePoints > 6)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_TakePoints[6],&gPeroscScreen->m_TakePoints[7],&maxPoint);
		}
		if(gPeroscScreen->m_bDBlbuttonDown)
		{
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gPeroscScreen->m_TakePoints[gPeroscScreen->m_iCountTakePoints],&gPeroscScreen->m_TakePoints[0],&maxPoint);
		}
	}
}
