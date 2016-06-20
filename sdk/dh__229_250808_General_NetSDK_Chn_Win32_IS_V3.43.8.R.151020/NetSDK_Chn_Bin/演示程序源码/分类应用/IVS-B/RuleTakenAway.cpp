// RuleTakenAway.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "RuleTakenAway.h"
#include "DemoIVSbDlg.h"
#include "TargetFilter.h"
#include "Config.h"
#include "ConfigRules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRule10TakenAway dialog


CRuleTakenAway::CRuleTakenAway(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleTakenAway::IDD, pParent),
	m_pRule(NULL)
{
	//{{AFX_DATA_INIT(CRuleTakenAway)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRuleTakenAway::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleTakenAway)
	DDX_Control(pDX, IDC_RULE10_CMB_TRIGGERPOS, m_cmbTriggerPos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleTakenAway, CDialog)
	//{{AFX_MSG_MAP(CRuleTakenAway)
	ON_CBN_SELCHANGE(IDC_RULE10_CMB_TRIGGERPOS, OnSelchangeRule10CmbTriggerpos)
	ON_EN_CHANGE(IDC_RULE10_EDT_MINDUR, OnChangeRule10EdtMindur)
	ON_BN_CLICKED(IDC_RULE10_RADIO_CFILTER, OnRule10RadioCfilter)
	ON_BN_CLICKED(IDC_RULE10_RADIO_GFILTER, OnRule10RadioGfilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRule10TakenAway message handlers

void CRuleTakenAway::initSubDlg()
{
	//触发报警位置
	m_cmbTriggerPos.InsertString(0, ConvertString(_T("Center")));
	m_cmbTriggerPos.InsertString(1, ConvertString(_T("LCenter")));
	m_cmbTriggerPos.InsertString(2, ConvertString(_T("TCenter")));
	m_cmbTriggerPos.InsertString(3, ConvertString(_T("RCenter")));
	m_cmbTriggerPos.InsertString(4, ConvertString(_T("BCenter")));
	m_cmbTriggerPos.SetCurSel(-1);
	
	//最短持续时间
// 	SetDlgItemInt(IDC_RULE10_EDT_MINDUR, 0, FALSE);
}

void CRuleTakenAway::showRuleInfo(RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || pRuleStruct->RuleInfo.dwRuleType != EVENT_IVS_TAKENAWAYDETECTION)
	{
		return;
	}
	
	//Todo: show info
	if (!pRuleStruct->pRuleBuf)
	{
		return;
	}
	
	CFG_TAKENAWAYDETECTION_INFO* pRule = (CFG_TAKENAWAYDETECTION_INFO*)pRuleStruct->pRuleBuf;
	m_pRule = pRule;
	if (m_pRule->stuSizeFileter.nCalibrateBoxNum)
	{
		((CButton*)GetDlgItem(IDC_RULE10_RADIO_GFILTER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RULE10_RADIO_CFILTER))->SetCheck(TRUE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_RULE10_RADIO_GFILTER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RULE10_RADIO_CFILTER))->SetCheck(FALSE);
	}

	//触发报警位置
	m_cmbTriggerPos.SetCurSel(pRule->bTriggerPosition[0]);

	//最短持续时间
	SetDlgItemInt(IDC_RULE10_EDT_MINDUR, pRule->nMinDuration, FALSE);
}

void CRuleTakenAway::clearRuleInfo()
{
	m_cmbTriggerPos.ResetContent();
	m_pRule = NULL;
}

void CRuleTakenAway::setRuleInfo(char* pRuleStruct, int nLen)
{
	if (!pRuleStruct || nLen != EVENT_IVS_TAKENAWAYDETECTION)
	{
		return;
	}
}

void CRuleTakenAway::updateDraw()
{
	if (m_pRule)
	{
		CFG_ANALYSERULES_INFO stuRuleInfo = {0};
		stuRuleInfo.nRuleCount = 1;
		stuRuleInfo.nRuleLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_RETROGRADEDETECTION_INFO);
		
		CFG_RULE_INFO cfgRuleInfo = {0};
		cfgRuleInfo.dwRuleType = EVENT_IVS_TAKENAWAYDETECTION;
		cfgRuleInfo.nRuleSize = sizeof(CFG_RETROGRADEDETECTION_INFO);
		
		stuRuleInfo.pRuleBuf = new char[sizeof(CFG_RETROGRADEDETECTION_INFO) + sizeof(CFG_RULE_INFO)];
		if (!stuRuleInfo.pRuleBuf)
		{
			return;
		}
		memcpy(stuRuleInfo.pRuleBuf, &cfgRuleInfo, sizeof(CFG_RULE_INFO));
		memcpy(stuRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO), m_pRule, sizeof(CFG_RETROGRADEDETECTION_INFO));
		
		//为了能画图，让规则使能
		char* pTmp = stuRuleInfo.pRuleBuf;
		pTmp += sizeof(CFG_RULE_INFO);
		CFG_CROSSLINE_INFO* pRuleInfo = (CFG_CROSSLINE_INFO*)pTmp;
		if (!pRuleInfo->bRuleEnable)
		{
			pRuleInfo->bRuleEnable = true;
		}

		::DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&stuRuleInfo, 0);
		
		delete stuRuleInfo.pRuleBuf;
		stuRuleInfo.pRuleBuf = NULL;
	}
}

BOOL CRuleTakenAway::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRuleTakenAway::OnSelchangeRule10CmbTriggerpos() 
{
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		m_pRule->nTriggerPosition = 1;
		m_pRule->bTriggerPosition[0] = m_cmbTriggerPos.GetCurSel();
		
		updateDraw();
	}		
}

void CRuleTakenAway::OnChangeRule10EdtMindur() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strMinDur;
		GetDlgItemText(IDC_RULE10_EDT_MINDUR, strMinDur);
		
		int iMinDur = atoi(strMinDur.GetBuffer(strMinDur.GetLength()));
		
		m_pRule->nMinDuration = iMinDur;
	}
}

void CRuleTakenAway::OnRule10RadioCfilter() 
{
	// TODO: Add your control notification handler code here
	CTargetFilter filterDlg;
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	int nChannel = pMainDlg->getCurrentChannel();
	
	
	//初始化模块树控件
	CFG_ANALYSEMODULES_INFO* pAnalyseModulesInfo = pMainDlg->getAnalyseModuleInfo(nChannel);
	if(!pAnalyseModulesInfo)
	{
		return;
	}
	
	CFG_ANALYSEMODULES_INFO* pCfgModuleInfo = new CFG_ANALYSEMODULES_INFO;
	if (!pCfgModuleInfo)
	{
		return;
	}
	memcpy(pCfgModuleInfo, pAnalyseModulesInfo, sizeof(CFG_ANALYSEMODULES_INFO));
	ZeroMemory(pCfgModuleInfo->stuModuleInfo[0].szObjectType, MAX_NAME_LEN);
	strncpy(pCfgModuleInfo->stuModuleInfo[0].szObjectType, "Unknown", strlen("Unknown"));
	
	if (m_pRule->bSizeFileter)
	{
		if (!m_pRule->stuSizeFileter.nCalibrateBoxNum)
		{
			// 如果没有信息，传入初始值
			pCfgModuleInfo->stuModuleInfo[0].stuCalibrateBoxs[0].fRatio = 1.;
			pCfgModuleInfo->stuModuleInfo[0].stuCalibrateBoxs[0].stuCenterPoint.nX = 600;
			pCfgModuleInfo->stuModuleInfo[0].stuCalibrateBoxs[0].stuCenterPoint.nY = 600;
			
			pCfgModuleInfo->stuModuleInfo[0].stuFilterMaxSize.nWidth = 500;
			pCfgModuleInfo->stuModuleInfo[0].stuFilterMaxSize.nHeight = 500;
			
			pCfgModuleInfo->stuModuleInfo[0].stuFilterMinSize.nWidth = 300;
			pCfgModuleInfo->stuModuleInfo[0].stuFilterMinSize.nHeight = 300;
		}
		else
		{
			memcpy(pCfgModuleInfo->stuModuleInfo[0].stuCalibrateBoxs,
				m_pRule->stuSizeFileter.stuCalibrateBoxs,
				sizeof(CFG_CALIBRATEBOX_INFO));
			memcpy(&pCfgModuleInfo->stuModuleInfo[0].stuFilterMaxSize, 
				&m_pRule->stuSizeFileter.stuFilterMaxSize,
				sizeof(CFG_SIZE));
			memcpy(&pCfgModuleInfo->stuModuleInfo[0].stuFilterMinSize,
				&m_pRule->stuSizeFileter.stuFilterMinSize,
				sizeof(CFG_SIZE));
		}
		pCfgModuleInfo->stuModuleInfo[0].bBySize = m_pRule->stuSizeFileter.bBySize;
		pCfgModuleInfo->stuModuleInfo[0].nFilterType = m_pRule->stuSizeFileter.bFilterType;
		pCfgModuleInfo->stuModuleInfo[0].bFilterMaxSizeEnable = true;
		pCfgModuleInfo->stuModuleInfo[0].bFilterMinSizeEnable = true;
		pCfgModuleInfo->stuModuleInfo[0].nCalibrateBoxNum = 1;
	}
	
	filterDlg.Init(pCfgModuleInfo, nChannel);
	
	if (filterDlg.DoModal() == IDOK)
	{
		memcpy(m_pRule->stuSizeFileter.stuCalibrateBoxs,
			pCfgModuleInfo->stuModuleInfo[0].stuCalibrateBoxs,
			sizeof(CFG_CALIBRATEBOX_INFO) * MAX_CALIBRATEBOX_NUM);
		memcpy(&m_pRule->stuSizeFileter.stuFilterMaxSize,
			&pCfgModuleInfo->stuModuleInfo[0].stuFilterMaxSize,
			sizeof(CFG_SIZE));
		memcpy(&m_pRule->stuSizeFileter.stuFilterMinSize,
			&pCfgModuleInfo->stuModuleInfo[0].stuFilterMinSize,
			sizeof(CFG_SIZE));
		m_pRule->stuSizeFileter.abBySize = true;
		m_pRule->stuSizeFileter.bBySize = pCfgModuleInfo->stuModuleInfo[0].bBySize;
		m_pRule->stuSizeFileter.bFilterType = pCfgModuleInfo->stuModuleInfo[0].nFilterType;
		m_pRule->stuSizeFileter.bFilterMaxSizeEnable = true;
		m_pRule->stuSizeFileter.bFilterMinSizeEnable = true;
		m_pRule->stuSizeFileter.nCalibrateBoxNum = 1;
		
		m_pRule->bSizeFileter = TRUE;
	}
	
	if (pCfgModuleInfo)
	{
		delete pCfgModuleInfo;
		pCfgModuleInfo = NULL;
	}
	
	pMainDlg->m_pdlgConfig->m_dlgConfigRules.showPreview(pMainDlg->getLoginHandle(), pMainDlg->getCurrentChannel());
}

void CRuleTakenAway::OnRule10RadioGfilter() 
{
	// TODO: Add your control notification handler code here
	m_pRule->bSizeFileter = FALSE;
	m_pRule->stuSizeFileter.nCalibrateBoxNum = 0;
	
}
