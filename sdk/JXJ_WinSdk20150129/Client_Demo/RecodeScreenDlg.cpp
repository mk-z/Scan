// RecodeScreenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "RecodeScreenDlg.h"
#include "Pub_Data.h"
#include "Client_DemoDlg.h"
#include "VideoPlayBack.h"


// CRecodeScreenDlg 对话框

IMPLEMENT_DYNAMIC(CRecodeScreenDlg, CDialog)

CRecodeScreenDlg::CRecodeScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecodeScreenDlg::IDD, pParent)
{
	m_bPlayFileProgress = FALSE;
}

CRecodeScreenDlg::~CRecodeScreenDlg()
{
}

void CRecodeScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_PLAYPROGRESS, m_PlayProgress);
}


BEGIN_MESSAGE_MAP(CRecodeScreenDlg, CDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONUP()
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CRecodeScreenDlg 消息处理程序

BOOL CRecodeScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bDbclk = FALSE;

	return TRUE;
}
void CRecodeScreenDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CClient_DemoDlg *pDlg = (CClient_DemoDlg *)AfxGetMainWnd();
	if(!m_bDbclk)
	{
		this->MoveWindow(28,0,g_PubData.g_iStaticScreenWidth-28,g_PubData.g_iStaticScreenHeight - 32,TRUE);
		this->ShowWindow(SW_SHOW);
		m_bDbclk = TRUE;
		pDlg->m_videoPlayBack.m_VideoPlayBack.ShowWindow(SW_HIDE);
	}
	else
	{
		this->MoveWindow(30,270,650,255, TRUE);
		this->ShowWindow(SW_SHOW);
		m_bDbclk = FALSE;
		pDlg->m_videoPlayBack.m_VideoPlayBack.ShowWindow(SW_SHOW);
	}
	
	CRect cRect;
	this->GetClientRect(&cRect);
	this->GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->MoveWindow(0,0,cRect.Width(), cRect.Height() - 25, TRUE);
	this->GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_SLIDER_PLAYPROGRESS)->MoveWindow(50, cRect.Height()-18, cRect.Width()- 50,20, TRUE);
	this->GetDlgItem(IDC_SLIDER_PLAYPROGRESS)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->MoveWindow(0, cRect.Height()-15, 50, 20, TRUE);
	this->GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_STATIC_GROPU_PROGRESS)->MoveWindow(0, cRect.Height()-25, cRect.Width(),25, TRUE);
	this->GetDlgItem(IDC_STATIC_GROPU_PROGRESS)->ShowWindow(SW_SHOW);
		

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CRecodeScreenDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码


}

BOOL CRecodeScreenDlg::PreTranslateMessage(MSG* pMsg) 
{

	CVideoPlayBack *pDlg = (CVideoPlayBack *)AfxGetMainWnd();
	int buID;
	buID= GetWindowLong(pMsg->hwnd,GWL_ID);//由窗口句柄获得ID号，GetWindowLong为获得窗口的ID号。
	if(pMsg->message==WM_LBUTTONDOWN)   //按下 
	{	
		
	}
	if(pMsg->message==WM_LBUTTONUP)  //松开
	{  
		if(buID == IDC_SLIDER_PLAYPROGRESS)
		{
			m_bPlayFileProgress = TRUE;
			pDlg->m_PlayFiletime = m_PlayProgress.GetPos();
		}
	}


	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CRecodeScreenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	CBrush   brush(RGB(255,255,255)); 
	if(pWnd-> GetDlgCtrlID() == IDC_STATIC_SHOWRECODEVIDEO)
	{
		CRect   rect;  
		pDC->SelectObject(&brush);  
		CWnd   *p_staticwnd=GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO); 
		p_staticwnd-> GetWindowRect(&rect);  
		pDC-> Rectangle(&rect); 
		pDC->SetBkMode(TRANSPARENT); 
	}

	return   (HBRUSH)brush;
	//return hbr;
}

void CRecodeScreenDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonUp(nFlags, point);
}

//void CRecodeScreenDlg::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialog::OnMouseMove(nFlags, point);
//}
