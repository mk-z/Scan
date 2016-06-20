// Config.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSPC.h"
#include "Config.h"
#include "DemoIVSPCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfig dialog


CConfig::CConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CConfig::IDD, pParent),
	m_currentDlg(DlgNone)
{

}


void CConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfig)
	DDX_Control(pDX, IDC_CONFIG_TAB, m_tabConfig);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfig, CDialog)
	//{{AFX_MSG_MAP(CConfig)
	ON_NOTIFY(TCN_SELCHANGE, IDC_CONFIG_TAB, OnSelchangeConfigTab)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfig message handlers

BOOL CConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_tabConfig.InsertItem(0, ConvertString(_T("GlobalConfig")));
	m_tabConfig.InsertItem(1, ConvertString(_T("ModuleConfig")));
	m_tabConfig.InsertItem(2, ConvertString(_T("RuleConfig")));

	CRect rt;
	m_tabConfig.GetClientRect(&rt);
	rt.top += 21;
	rt.left += 3;
	rt.right -= 3;
	rt.bottom -= 3;

	m_dlgConfigGlobal.Create(CConfigGlobal::IDD, &m_tabConfig);
	m_dlgConfigGlobal.MoveWindow(&rt, TRUE);
	m_dlgConfigGlobal.ShowWindow(SW_SHOW);
	m_currentDlg = DlgConfigGlobal;

	m_dlgConfigModule.Create(CConfigModule::IDD, &m_tabConfig);
	m_dlgConfigModule.MoveWindow(&rt, TRUE);

	m_dlgConfigRules.Create(CConfigRules::IDD, &m_tabConfig);
	m_dlgConfigRules.MoveWindow(&rt, TRUE);
	
	return TRUE;
}

void CConfig::OnSelchangeConfigTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_currentDlg == DlgConfigRule)
	{
		CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
		if (!pMainDlg)
		{
			return;
		}
		m_dlgConfigRules.ClosePreview(pMainDlg->GetRealPlayHandle());
	}

	switch(m_tabConfig.GetCurSel())
	{
	case 0:
		m_dlgConfigGlobal.ShowWindow(SW_SHOW);
		m_dlgConfigModule.ShowWindow(SW_HIDE);
		m_dlgConfigRules.ShowWindow(SW_HIDE);
		m_currentDlg = DlgConfigGlobal;
		break;
	case 1:
		m_dlgConfigGlobal.ShowWindow(SW_HIDE);
		m_dlgConfigModule.ShowWindow(SW_SHOW);
		m_dlgConfigRules.ShowWindow(SW_HIDE);
		m_currentDlg = DlgConfigModule;
		break;
	case 2:
		m_dlgConfigGlobal.ShowWindow(SW_HIDE);
		m_dlgConfigModule.ShowWindow(SW_HIDE);
		m_dlgConfigRules.ShowWindow(SW_SHOW);
		m_currentDlg = DlgConfigRule;
		break;
	default:
		break;
	}

	ShowPreview();

	*pResult = 0;
}

void CConfig::InitConfigDlg(int nChannel)
{
	UninitConfigDlg();

	m_dlgConfigGlobal.InitGlobalDlg(nChannel);
	m_dlgConfigModule.InitConfigModuleDlg(nChannel);
	m_dlgConfigRules.InitConfigRulesDlg(nChannel);
}

void CConfig::UninitConfigDlg()
{
	m_dlgConfigGlobal.UninitGlobalDlg();
	m_dlgConfigModule.UninitConfigModuleDlg();
	m_dlgConfigRules.UninitConfigRulesDlg();
}

void CConfig::ShowPreview()
{
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	switch(m_currentDlg)
	{
	case DlgConfigGlobal:
		m_dlgConfigGlobal.ShowPreview(pMainDlg->GetLoginHandle(), pMainDlg->GetCurrentChannel());
		break;
	case DlgConfigModule:
		m_dlgConfigModule.ShowPreview(pMainDlg->GetLoginHandle(), pMainDlg->GetCurrentChannel());
		break;
	case DlgConfigRule:
		m_dlgConfigRules.ShowPreview(pMainDlg->GetLoginHandle(), pMainDlg->GetCurrentChannel());
		break;
	default:
		break;
	}
}

void CConfig::OnDestroy() 
{
	CDialog::OnDestroy();
	
	UninitConfigDlg();
}
