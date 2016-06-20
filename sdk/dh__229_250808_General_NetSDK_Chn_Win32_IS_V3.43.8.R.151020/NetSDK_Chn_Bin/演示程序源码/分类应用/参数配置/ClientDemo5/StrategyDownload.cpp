// StrategyDownload.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "StrategyDownload.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrategyDownload dialog


CStrategyDownload::CStrategyDownload(CWnd* pParent /*=NULL*/)
	: CDialog(CStrategyDownload::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStrategyDownload)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStrategyDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStrategyDownload)
	DDX_Control(pDX, IDC_COMBO_DOWNLOAD, m_ccbDownload);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStrategyDownload, CDialog)
	//{{AFX_MSG_MAP(CStrategyDownload)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStrategyDownload message handlers

BOOL CStrategyDownload::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	int nIndex = m_ccbDownload.AddString(ConvertString("normal download"));
	m_ccbDownload.SetItemData(nIndex,0);
	nIndex = m_ccbDownload.AddString(ConvertString("quickly download"));
	m_ccbDownload.SetItemData(nIndex,1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStrategyDownload::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CStrategyDownload::InitDlgInfo(DHDEV_DOWNLOAD_STRATEGY_CFG* pDownloadInfo)
{
	if(NULL == pDownloadInfo)
	{
		return ;
	}
	
	if(pDownloadInfo->bEnable ==TRUE)
	{
		m_ccbDownload.SetCurSel(1);
	}
	else if(pDownloadInfo->bEnable == FALSE)
	{
		m_ccbDownload.SetCurSel(0);
	}
	else
	{
		m_ccbDownload.SetCurSel(-1);
	}
}
void CStrategyDownload::CleanAll(void)
{
	m_ccbDownload.SetCurSel(-1);
}
void CStrategyDownload::SaveAll(void)
{
	int nIndex = m_ccbDownload.GetCurSel();
	m_stuDownload.bEnable = m_ccbDownload.GetItemData(nIndex);
	m_stuDownload.dwSize = sizeof(m_stuDownload);
}








































































































































































































































































































































































































































































































































