// ConfigFTPMain.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigFTPMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigFTPMain dialog


CConfigFTPMain::CConfigFTPMain(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigFTPMain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigFTPMain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigFTPMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigFTPMain)
	DDX_Control(pDX, IDC_TAB_FTP, m_ctlFTPTab);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigFTPMain, CDialog)
	//{{AFX_MSG_MAP(CConfigFTPMain)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FTP, OnSelchangeTabFtp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CConfigFTPMain::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//Initialize TabControl control
	InitTabControl();
	g_SetWndStaticText(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CConfigFTPMain message handlers

//Initialize TabControl control 
void CConfigFTPMain::InitTabControl()
{
	CRect childRect;
	m_ctlFTPTab.GetClientRect(childRect);
	childRect.top += 4;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 30;
	
	//Create non-mode dialogue box. Specified tag control is non-mode father dialogue box
	m_TabFtpEx.Create(IDD_CONFIG_FTPEX, &m_ctlFTPTab);
	m_TabFtpEx.MoveWindow(childRect);
	m_TabFtpStorage.Create(IDD_CONFIG_FTP, &m_ctlFTPTab);
	m_TabFtpStorage.MoveWindow(childRect);
	
	m_ctlFTPTab.InsertItem(0, ConvertString("FTPEX Config"));
	m_ctlFTPTab.InsertItem(1, ConvertString("TimeSchedule Config"));
	
	m_ctlFTPTab.SetCurSel(0);
	DoTab(0);
}

void CConfigFTPMain::InitDlgInfo()
{
    m_TabFtpEx.InitDlgInfo();
	m_TabFtpStorage.InitFtpInfo();
}

//Clear 
void CConfigFTPMain::CleanAll()
{
	m_TabFtpEx.CleanAll();
    m_TabFtpStorage.CleanAll();
}

void CConfigFTPMain::DoTab(int nTab)
{
	//Check nTab is within the threshold
	if(nTab>1)
	{
		nTab=1;
	}
	if(nTab<0)
	{
		nTab=0;
	}
	
	BOOL bTab[3];
	bTab[0]=bTab[1]=FALSE;
	bTab[nTab]=TRUE;
	
	//Hide or display dialogue box 
	SetDlgState(&m_TabFtpEx,bTab[0]);
	SetDlgState(&m_TabFtpStorage,bTab[1]);

}

void CConfigFTPMain::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
	}
}
void CConfigFTPMain::OnButtonLoad() 
{
	// TODO: Add your control notification handler code here
	m_TabFtpEx.SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON_READ, BN_CLICKED));
	m_TabFtpStorage.SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON_READ_FTP, BN_CLICKED));
}

void CConfigFTPMain::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	m_TabFtpEx.SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON_SAVE, BN_CLICKED));
	m_TabFtpStorage.SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON_SAVE_FTP, BN_CLICKED));
}

void CConfigFTPMain::OnSelchangeTabFtp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_ctlFTPTab.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}
