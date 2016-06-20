// CpcScreen.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "CpcScreen.h"
#include "Pub_Data.h"

// CCpcScreen 对话框

#define  DRAWCOLOR RGB(255,0,0)
IMPLEMENT_DYNAMIC(CCpcScreen, CDialog)

CCpcScreen::CCpcScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CCpcScreen::IDD, pParent)
{

	
}

CCpcScreen::~CCpcScreen()
{
}

void CCpcScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCpcScreen, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CCpcScreen 消息处理程序
BOOL CCpcScreen::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;
}

void CCpcScreen::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	
	m_bDraw = TRUE;
	m_cpcPoint[m_iCountPoint] = point;
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CCpcScreen::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC * pdc = GetWindowDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, GetSystemMetrics(SM_CXDRAG), RGB(75, 215, 40));
	CPen *pOldpen = pdc->SelectObject(&pen);
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);

	m_iCountPoint ++;
	m_cpcPoint[m_iCountPoint] = point;

	pdc->MoveTo(m_cpcPoint[m_iCountPoint -1]);
	pdc->LineTo(point);
	if(m_bDraw)
	{
		m_bDraw = FALSE;
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CCpcScreen::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!m_bDraw)
	{
		return;
	}

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

	pdc->MoveTo(m_cpcPoint[m_iCountPoint]);
	pdc->LineTo(point);
	CDialog::OnMouseMove(nFlags, point);
}


void CCpcScreen::RegDrawCallBack()
{
	
}

void CCpcScreen::ExitDrawCallBack()
{
	
}


void CALLBACK CCpcScreen::DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser)
{
	CRect cRect;
	
	
}
