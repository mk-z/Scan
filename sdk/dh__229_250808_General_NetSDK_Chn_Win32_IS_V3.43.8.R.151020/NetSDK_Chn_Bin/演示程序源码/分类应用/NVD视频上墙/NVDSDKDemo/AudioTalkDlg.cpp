// AudioTalkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NVDSDKDemo.h"
#include "AudioTalkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudioTalkDlg dialog


CAudioTalkDlg::CAudioTalkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioTalkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAudioTalkDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAudioTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAudioTalkDlg)
	DDX_Control(pDX, IDC_COMBO_ENC_TYPE, m_ctlEncodeType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAudioTalkDlg, CDialog)
	//{{AFX_MSG_MAP(CAudioTalkDlg)
	ON_BN_CLICKED(IDC_BTN_STARTTALK, OnBtnStarttalk)
	ON_BN_CLICKED(IDC_BTN_STOPTALK, OnBtnStoptalk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioTalkDlg message handlers

void CAudioTalkDlg::OnBtnStarttalk() 
{
	// TODO: Add your control notification handler code here
	
}

void CAudioTalkDlg::OnBtnStoptalk() 
{
	// TODO: Add your control notification handler code here
	
}
