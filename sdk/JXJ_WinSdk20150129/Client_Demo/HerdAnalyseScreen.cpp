// HerdAnalyseScreen.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HerdAnalyseScreen.h"
#include "Pub_Data.h"

// CHerdAnalyseScreen 对话框
#define  DRAWCOLOR RGB(255,0,0)

CHerdAnalyseScreen *gHerdScreen = NULL;

IMPLEMENT_DYNAMIC(CHerdAnalyseScreen, CDialog)

CHerdAnalyseScreen::CHerdAnalyseScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CHerdAnalyseScreen::IDD, pParent)
{
	gHerdScreen = this;
	for(int i = 0; i < 4; i++)
	{
		m_innerPoint[i] = 0;
		
		m_outerPoint[i] = 0;
	}
	m_nInnerNum = 0;
	m_nOuterNum = 0;
	m_bInner = FALSE;
	m_bOuter = FALSE;
}

CHerdAnalyseScreen::~CHerdAnalyseScreen()
{
}

void CHerdAnalyseScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHerdAnalyseScreen, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CHerdAnalyseScreen 消息处理程序
void CHerdAnalyseScreen::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_nInnerNum == 0 && m_nOuterNum == 0)
	{
		m_outerPoint[m_nOuterNum] = point;
		m_bOuter = TRUE;
		
	}
	else if(m_nInnerNum == 0 && m_nOuterNum == 4)
	{
		m_innerPoint[m_nInnerNum] = point;
		m_bInner = TRUE;
	}
	else if(m_nInnerNum == 4 && m_nOuterNum == 4)
	{
		for(int i = 0; i < 4; i++)
		{
			m_innerPoint[i] = 0;

			m_outerPoint[i] = 0;
		}
		m_nInnerNum = 0;
		m_nOuterNum = 0;
		m_bInner = FALSE;
		m_bOuter = FALSE;


		m_outerPoint[m_nOuterNum] = point;
		m_bOuter = TRUE;
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CHerdAnalyseScreen::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC * pdc = GetWindowDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, GetSystemMetrics(SM_CXDRAG), RGB(75, 215, 40));
	CPen *pOldpen = pdc->SelectObject(&pen);
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);


	if(m_nInnerNum == 0  && m_nOuterNum < 3)
	{
		pdc->MoveTo(m_outerPoint[m_nOuterNum]);
		pdc->LineTo(point);
		m_nOuterNum ++;
		m_outerPoint[m_nOuterNum] = point;

		if(m_nOuterNum == 3)
		{	
			pdc->MoveTo(m_outerPoint[m_nOuterNum]);
			pdc->LineTo(m_outerPoint[0]);
			m_nOuterNum ++;
			m_bOuter = FALSE;
		}

	}
	else if(m_nOuterNum == 4 && m_nInnerNum < 3)
	{
		
		pdc->MoveTo(m_innerPoint[m_nInnerNum]);
		pdc->LineTo(point);
		m_nInnerNum ++;
		m_innerPoint[m_nInnerNum] = point;

		if(m_nInnerNum == 3)
		{	
			pdc->MoveTo(m_innerPoint[m_nInnerNum]);
			pdc->LineTo(m_innerPoint[0]);
			m_nInnerNum ++;
			m_bInner = FALSE;
		}
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CHerdAnalyseScreen::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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

	if(m_nInnerNum == 0 && m_nOuterNum < 3 && m_bOuter)
	{
		pdc->MoveTo(m_outerPoint[m_nOuterNum]);
		pdc->LineTo(point);
	}
	else if(m_nOuterNum == 4 && m_nInnerNum < 3 && m_bInner)
	{
		pdc->MoveTo(m_innerPoint[m_nInnerNum]);
		pdc->LineTo(point);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CHerdAnalyseScreen::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonDblClk(nFlags, point);
}



void CHerdAnalyseScreen::RegDrawCallBack()
{
	////HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), DrawCB, this);
}

void CHerdAnalyseScreen::ExitDrawCallBack()
{
	////HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), NULL, this);
}


void CALLBACK CHerdAnalyseScreen::DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser)
{
	CRect cRect;
	gHerdScreen->GetWindowRect(cRect);
	CPoint maxPoint(cRect.Width(), cRect.Height());

	if(gHerdScreen->m_nInnerNum > 0)
	{
//		//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gHerdScreen->m_innerPoint[0],&gHerdScreen->m_innerPoint[1],&maxPoint);
	}
	if(gHerdScreen->m_nInnerNum > 1)
	{
//		//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gHerdScreen->m_innerPoint[1],&gHerdScreen->m_innerPoint[2],&maxPoint);
	}
	if(gHerdScreen->m_nInnerNum > 2)
	{
		////HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gHerdScreen->m_innerPoint[2],&gHerdScreen->m_innerPoint[3],&maxPoint);
	}
	if(gHerdScreen->m_nInnerNum > 3)
	{
		//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gHerdScreen->m_innerPoint[3],&gHerdScreen->m_innerPoint[0],&maxPoint);
	}

	if(gHerdScreen->m_nOuterNum > 0)
	{
		//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gHerdScreen->m_outerPoint[0],&gHerdScreen->m_outerPoint[1],&maxPoint);
	}
	if(gHerdScreen->m_nOuterNum > 1)
	{
		//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gHerdScreen->m_outerPoint[1],&gHerdScreen->m_outerPoint[2],&maxPoint);
	}
	if(gHerdScreen->m_nOuterNum > 2)
	{
		//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gHerdScreen->m_outerPoint[2],&gHerdScreen->m_outerPoint[3],&maxPoint);
	}
	if(gHerdScreen->m_nOuterNum > 3)
	{
		//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &gHerdScreen->m_outerPoint[3],&gHerdScreen->m_outerPoint[0],&maxPoint);
	}

}

