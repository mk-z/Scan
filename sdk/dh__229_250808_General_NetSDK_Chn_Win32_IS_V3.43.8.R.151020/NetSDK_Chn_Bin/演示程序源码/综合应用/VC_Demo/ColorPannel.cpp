// ColorPannel.cpp : implementation file
//

#include "StdAfx.h"
#include "netsdkdemo.h"
#include "ColorPannel.h"
#include "NetSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorPannel dialog


CColorPannel::CColorPannel(CWnd* pParent /*=NULL*/)
	: CDialog(CColorPannel::IDD, pParent)
{
	m_myBrush.CreateSolidBrush(RGB(220,220,220));
	//{{AFX_DATA_INIT(CColorPannel)
	//}}AFX_DATA_INIT
}


void CColorPannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorPannel)
	DDX_Control(pDX, IDC_SLIDER_SATURTION, m_slider_saturation);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_slider_hue);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_slider_contrast);
	DDX_Control(pDX, IDC_SLIDER_BRIGHT, m_slider_bright);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorPannel, CDialog)
	//{{AFX_MSG_MAP(CColorPannel)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BRIGHT, OnReleasedcaptureSliderBright)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CONTRAST, OnReleasedcaptureSliderContrast)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SATURTION, OnReleasedcaptureSliderSaturtion)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_HUE, OnReleasedcaptureSliderHue)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPannel message handlers

void CColorPannel::OnReleasedcaptureSliderBright(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos = m_slider_bright.GetPos();
		
	((CNetSDKDemoDlg *)GetParent())->CtrlColor_Bright(pos);
	
	*pResult = 0;
}

void CColorPannel::OnReleasedcaptureSliderContrast(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos = m_slider_contrast.GetPos();
	
	((CNetSDKDemoDlg *)GetParent())->CtrlColor_Contrast(pos);
	
	*pResult = 0;
}

void CColorPannel::OnReleasedcaptureSliderSaturtion(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos = m_slider_saturation.GetPos();
	
	((CNetSDKDemoDlg *)GetParent())->CtrlColor_Saturation(pos);
	
	*pResult = 0;
}

void CColorPannel::OnReleasedcaptureSliderHue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos = m_slider_hue.GetPos();
	
	((CNetSDKDemoDlg *)GetParent())->CtrlColor_Hue(pos);
	
	*pResult = 0;
}

void CColorPannel::UpdateVideoDisplay(int nMode, BYTE byPos)
{
	CSliderCtrl *pSlider;
	CStatic  *pStatic;
	switch(nMode) {
	case VIDEO_BRIGHT:
		pSlider = &m_slider_bright;
		pStatic = (CStatic *)GetDlgItem(IDC_INT_BRIGHT);
		break;
	case VIDEO_CONTRAST:
		pSlider = &m_slider_contrast;
		pStatic = (CStatic *)GetDlgItem(IDC_INT_CONTRAST);
		break;
	case VIDEO_HUE:
		pSlider = &m_slider_hue;
		pStatic = (CStatic *)GetDlgItem(IDC_INT_HUE);
		break;
	case VIDEO_SATURATION:
		pSlider = &m_slider_saturation;
		pStatic = (CStatic *)GetDlgItem(IDC_INT_SATURTION);
		break;
	default:
		return;
	}
	pSlider->SetPos(byPos);
	CString str;
	str.Format("[%03d]", byPos);
	pStatic->SetWindowText(str);
}

BOOL CColorPannel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	g_SetWndStaticText(this);

	m_slider_bright.SetRange(0,255);
	m_slider_contrast.SetRange(0,255);
	m_slider_hue.SetRange(0,255);
	m_slider_saturation.SetRange(0,255);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CColorPannel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);
	
	return m_myBrush;
	
	// TODO: Return a different brush if the default is not desired
//	return hbr;
}

BOOL CColorPannel::PreTranslateMessage(MSG* pMsg) 
{
	if (WM_KEYDOWN == pMsg->message && 
		(VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);

}
