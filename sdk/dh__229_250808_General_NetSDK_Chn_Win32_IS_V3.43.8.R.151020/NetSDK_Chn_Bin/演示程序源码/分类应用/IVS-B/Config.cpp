// Config.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSb.h"
#include "Config.h"
#include "DemoIVSbDlg.h"
#include "IvsGlobalPreview.h"
#include "IvsModulePreview.h"
#include "IvsRulePreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfig dialog


CConfig::CConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CConfig::IDD, pParent),
	m_currentDlg(dlgNone)
{
	//{{AFX_DATA_INIT(CConfig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
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
	g_SetWndStaticText(this);

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
	m_currentDlg = dlgConfigGlobal;

	m_dlgConfigModule.Create(CConfigModule::IDD, &m_tabConfig);
	m_dlgConfigModule.MoveWindow(&rt, TRUE);

	m_dlgConfigRules.Create(CConfigRules::IDD, &m_tabConfig);
	m_dlgConfigRules.MoveWindow(&rt, TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfig::OnSelchangeConfigTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_dlgConfigGlobal.m_pIvsGlobalPreview->isDrawing()
		&& m_currentDlg == dlgConfigGlobal)
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		m_tabConfig.SetCurSel(dlgConfigGlobal);
		return;
	}

	if (m_dlgConfigModule.m_pIvsModulePreview->isDrawing()
		&& m_currentDlg == dlgConfigModule)
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		m_tabConfig.SetCurSel(dlgConfigModule);
		return;
	}

	if ((m_dlgConfigRules.m_pIvsRulePreview->m_bAddRegion 
			|| m_dlgConfigRules.m_bAddRule)
		&& m_currentDlg == dlgConfigRule)
	{
		if (m_dlgConfigRules.m_cmbRuleType.GetCurSel() == -1)
		{
			AfxMessageBox(ConvertString(_T("Please select the rule type first")));
		} 
		else
		{
			AfxMessageBox(ConvertString(_T("Please draw the line of rule first or click right button to stop drawing")));
		}

		m_tabConfig.SetCurSel(dlgConfigRule);
		return;
	}

	if (m_currentDlg == dlgConfigRule)
	{
		CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
		if (!pMainDlg)
		{
			return;
		}
		m_dlgConfigRules.closePreview(pMainDlg->getRealPlayHandle());
	}

	switch(m_tabConfig.GetCurSel())
	{
	case 0:
		m_dlgConfigGlobal.ShowWindow(SW_SHOW);
		m_dlgConfigModule.ShowWindow(SW_HIDE);
		m_dlgConfigRules.ShowWindow(SW_HIDE);
		m_currentDlg = dlgConfigGlobal;
		break;
	case 1:
		m_dlgConfigGlobal.ShowWindow(SW_HIDE);
		m_dlgConfigModule.ShowWindow(SW_SHOW);
		m_dlgConfigRules.ShowWindow(SW_HIDE);
		m_currentDlg = dlgConfigModule;
		break;
	case 2:
		m_dlgConfigGlobal.ShowWindow(SW_HIDE);
		m_dlgConfigModule.ShowWindow(SW_HIDE);
		m_dlgConfigRules.ShowWindow(SW_SHOW);
		m_currentDlg = dlgConfigRule;
		m_dlgConfigRules.OnClickCfgruleTreeRulelist(NULL, NULL);
		break;
	default:
		break;
	}

	showPreview();

	*pResult = 0;
}

void CConfig::initConfigDlg(int nChannel)
{
	uninitConfigDlg();

	m_dlgConfigGlobal.initGlobalDlg(nChannel);
	m_dlgConfigModule.initConfigModuleDlg(nChannel);
	m_dlgConfigRules.initConfigRulesDlg(nChannel);
}

void CConfig::uninitConfigDlg()
{
	m_dlgConfigGlobal.uninitGlobalDlg();
	m_dlgConfigModule.uninitConfigModuleDlg();
	m_dlgConfigRules.uninitConfigRulesDlg();
}

void CConfig::showPreview()
{
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	switch(m_currentDlg)
	{
	case dlgConfigGlobal:
		m_dlgConfigGlobal.showPreview(pMainDlg->getLoginHandle(), pMainDlg->getCurrentChannel());
		break;
	case dlgConfigModule:
		m_dlgConfigModule.showPreview(pMainDlg->getLoginHandle(), pMainDlg->getCurrentChannel());
		break;
	case dlgConfigRule:
		m_dlgConfigRules.showPreview(pMainDlg->getLoginHandle(), pMainDlg->getCurrentChannel());
		break;
	default:
		break;
	}
}

void CConfig::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	uninitConfigDlg();
}
