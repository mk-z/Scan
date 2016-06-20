// ConfigStrategy.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigStrategy.h"
#include "resource.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigStrategy dialog


CConfigStrategy::CConfigStrategy(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigStrategy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigStrategy)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigStrategy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigStrategy)
	DDX_Control(pDX, IDC_TAB_STRATEGY, m_tabStrategy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigStrategy, CDialog)
	//{{AFX_MSG_MAP(CConfigStrategy)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_WM_CANCELMODE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_STRATEGY, OnSelchangeTabStrategy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigStrategy message handlers

void CConfigStrategy::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	m_StrategyDownload.SaveAll();
	m_StrategyTrans.SaveAll();
	m_StrategyIPFileter.SetIPFilterCfg();
	m_StrategyEncryption.SetEncryptionCfg();
	//m_StrategyMacFilter.SetMacFilterCfg();
	((CClientDemo5Dlg*)AfxGetMainWnd())->SetStrategyConfigInfo(&m_StrategyTrans.m_stuDVRIPInfo,&m_StrategyDownload.m_stuDownload);
}

void CConfigStrategy::OnButtonLoad() 
{
	// TODO: Add your control notification handler code here
	CleanAll();	
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetStrategyConfigInfo();
	//m_StrategyIPFileter.GetIPFilterCfg();
	//m_StrategyMacFilter.GetMacFilterCfg();
}


void CConfigStrategy::SetDlgState(CWnd *pWnd, BOOL bShow)
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

void CConfigStrategy::DoTab(int nTab)
{
	//Confirm nTab value is within the threshold
	if(nTab > 3)
	{
		nTab = 3;
	}
	if(nTab < 0)
	{
		nTab = 0;
	}
	
	BOOL bTab[5];
	bTab[0]=bTab[1]=bTab[2]=bTab[3]=FALSE;
	bTab[nTab]=TRUE;
	
	//Display or hide dialogue box switch 
	SetDlgState(&m_StrategyDownload,bTab[0]);
	SetDlgState(&m_StrategyTrans,bTab[1]);
	SetDlgState(&m_StrategyIPFileter, bTab[2]);
	SetDlgState(&m_StrategyEncryption,bTab[3]);
	//SetDlgState(&m_StrategyMacFilter,bTab[4]);
}

void CConfigStrategy::InitTabCtl(void)
{
	CRect childRect;
	m_tabStrategy.GetClientRect(childRect);
	childRect.top += 4;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 30;

	m_StrategyDownload.Create(IDD_CONFIG_STRATEGY_DWONLOAD,&m_tabStrategy);
	m_StrategyDownload.MoveWindow(childRect);
	m_StrategyTrans.Create(IDD_CONFIG_STRATEGY_TRANS,&m_tabStrategy);
	m_StrategyTrans.MoveWindow(childRect);
	m_StrategyIPFileter.Create(IDD_CONFIG_STRATEGY_IPFILTER,&m_tabStrategy);
	m_StrategyIPFileter.MoveWindow(childRect);
	m_StrategyEncryption.Create(IDD_CONFIG_STRATEGY_ENCRYPTION,&m_tabStrategy);
	m_StrategyEncryption.MoveWindow(childRect);
	//m_StrategyMacFilter.Create(IDD_CONFIG_STRATEGY_MACFILTER,&m_tabStrategy);
	//m_StrategyMacFilter.MoveWindow(childRect);

	m_tabStrategy.InsertItem(0, ConvertString("record download"));
	m_tabStrategy.InsertItem(1, ConvertString("net transmission"));
	m_tabStrategy.InsertItem(2, ConvertString("Ip Fileter"));
	m_tabStrategy.InsertItem(3,ConvertString("Encrypt"));
	//m_tabStrategy.InsertItem(4,ConvertString("Mac Filter"));
	m_tabStrategy.SetCurSel(0);
	DoTab(0);
}

BOOL CConfigStrategy::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	
	InitTabCtl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigStrategy::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}
void CConfigStrategy::CleanAll()
{
	m_StrategyDownload.CleanAll();
	m_StrategyTrans.CleanAll();
	m_StrategyEncryption.CleanAll();
    m_StrategyIPFileter.ClearAll();

}

void CConfigStrategy::OnSelchangeTabStrategy(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_tabStrategy.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}








































































































































































































































































































































































































































































































































