// StrategyTrans.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "StrategyTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrategyTrans dialog


CStrategyTrans::CStrategyTrans(CWnd* pParent /*=NULL*/)
	: CDialog(CStrategyTrans::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStrategyTrans)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStrategyTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStrategyTrans)
	DDX_Control(pDX, IDC_COMBO_TRANS, m_ccbTrans);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_cbEnable);
	//}}AFX_DATA_MAP
}

void CStrategyTrans::InitDlgInfo(CFG_DVRIP_INFO* pDVRIPInfo)
{
	if(NULL == pDVRIPInfo)
	{
		return ;
	}
    int nCheck = FALSE;
    int nDefaultPolicy = STREAM_POLICY_QUALITY; // 使能为FALSE时,默认显示画质优先
    if (STREAM_POLICY_NONE < pDVRIPInfo->emStreamPolicy)
    {
        nCheck = TRUE;
        nDefaultPolicy = pDVRIPInfo->emStreamPolicy;
    }
	m_cbEnable.SetCheck(nCheck);
	m_ccbTrans.SetCurSel(nDefaultPolicy - 2);
    memcpy(&m_stuDVRIPInfo, pDVRIPInfo, sizeof(CFG_DVRIP_INFO));
}
void CStrategyTrans::SaveAll(void)
{
	int nIndex = m_ccbTrans.GetCurSel();
	m_stuDVRIPInfo.emStreamPolicy = (EM_STREAM_POLICY)(m_ccbTrans.GetItemData(nIndex) + 2);
    if (0 == m_cbEnable.GetCheck())
    {
        m_stuDVRIPInfo.emStreamPolicy = STREAM_POLICY_NONE;
    }
}
void CStrategyTrans::CleanAll()
{
	m_ccbTrans.SetCurSel(-1);
	m_cbEnable.SetCheck(0);
    memset(&m_stuDVRIPInfo, 0, sizeof(CFG_DVRIP_INFO));
}
BEGIN_MESSAGE_MAP(CStrategyTrans, CDialog)
	//{{AFX_MSG_MAP(CStrategyTrans)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStrategyTrans message handlers

BOOL CStrategyTrans::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	int nIndex = m_ccbTrans.AddString(ConvertString("quality first"));
	m_ccbTrans.SetItemData(nIndex,0);
	nIndex = m_ccbTrans.AddString(ConvertString("fluency first"));
	m_ccbTrans.SetItemData(nIndex,1);
	nIndex = m_ccbTrans.AddString(ConvertString("auto"));
	m_ccbTrans.SetItemData(nIndex,2);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStrategyTrans::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}








































































































































































































































































































































































































































































































































