// RuleCrossLine.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "RuleCrossLine.h"
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
// CRuleCrossLine dialog

CRuleCrossLine::CRuleCrossLine(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleCrossLine::IDD, pParent),
	m_pRule(NULL)
{
	//{{AFX_DATA_INIT(CRuleCrossLine)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRuleCrossLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleCrossLine)
	DDX_Control(pDX, IDC_RULE2_TREE_OBJTYPE, m_treeObjType);
	DDX_Control(pDX, IDC_RULE2_CMB_TRIGGERPOS, m_cmbTriggerPos);
	DDX_Control(pDX, IDC_RULE2_CMB_DIRECTION, m_cmbDirection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleCrossLine, CDialog)
	//{{AFX_MSG_MAP(CRuleCrossLine)
	ON_CBN_SELCHANGE(IDC_RULE2_CMB_DIRECTION, OnSelchangeRule2CmbDirection)
	ON_CBN_SELCHANGE(IDC_RULE2_CMB_TRIGGERPOS, OnSelchangeRule2CmbTriggerpos)
	ON_NOTIFY(NM_CLICK, IDC_RULE2_TREE_OBJTYPE, OnClickRule2TreeObjtype)
	ON_BN_CLICKED(IDC_RULE2_RADIO_GFILTER, OnRule2RadioGfilter)
	ON_BN_CLICKED(IDC_RULE2_RADIO_CFILTER, OnRule2RadioCfilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleCrossLine message handlers

void CRuleCrossLine::initSubDlg()
{
	//支持的物体类型
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	
	CFG_CAP_ANALYSE_INFO* pCap = pMainDlg->getCapAnalyseInfo(pMainDlg->getCurrentChannel());
	if (!pCap)
	{
		return;
	}
	
	int i = 0;
	for (i = 0; i < pCap->stSupportScenes.stScenes[0].nSupportRules; i++)
	{
		if (pCap->stSupportScenes.stScenes[0].stSpportRules[i].dwSupportedRule == EVENT_IVS_CROSSLINEDETECTION)
		{
			break;
		}
	}
	
	int nObjTypeNum = pCap->stSupportScenes.stScenes[0].stSpportRules[i].nSupportedObjectTypeNum;
	for (int j = 0; j < nObjTypeNum; j++)
	{
		HTREEITEM hItem = m_treeObjType.InsertItem(ConvertString(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szObjectTypeName[j]));
		char* p = new char[MAX_NAME_LEN];
		if (p)
		{
			ZeroMemory(p, MAX_NAME_LEN);
			strncpy(p, 
					pCap->stSupportScenes.stScenes[0].stSpportRules[i].szObjectTypeName[j],
					strlen(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szObjectTypeName[j]));
			m_treeObjType.SetItemData(hItem, (DWORD)p);
		}
	}
	
	//方向
	m_cmbDirection.InsertString(0, ConvertString(_T("L->R")));
	m_cmbDirection.InsertString(1, ConvertString(_T("R->L")));
	m_cmbDirection.InsertString(2, ConvertString(_T("Both")));
	m_cmbDirection.SetCurSel(-1);

	//触发报警位置
	m_cmbTriggerPos.InsertString(0, ConvertString(_T("Center")));
	m_cmbTriggerPos.InsertString(1, ConvertString(_T("LCenter")));
	m_cmbTriggerPos.InsertString(2, ConvertString(_T("TCenter")));
	m_cmbTriggerPos.InsertString(3, ConvertString(_T("RCenter")));
	m_cmbTriggerPos.InsertString(4, ConvertString(_T("BCenter")));
	m_cmbTriggerPos.SetCurSel(-1);
}

void CRuleCrossLine::showRuleInfo(RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || pRuleStruct->RuleInfo.dwRuleType != EVENT_IVS_CROSSLINEDETECTION)
	{
		return;
	}
	
	//Todo: show info
	if (!pRuleStruct->pRuleBuf)
	{
		return;
	}
	
	CFG_CROSSLINE_INFO* pRule = (CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf;
	m_pRule = pRule;
	if (m_pRule->stuSizeFileter.nCalibrateBoxNum)
	{
		((CButton*)GetDlgItem(IDC_RULE2_RADIO_GFILTER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RULE2_RADIO_CFILTER))->SetCheck(TRUE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_RULE2_RADIO_GFILTER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RULE2_RADIO_CFILTER))->SetCheck(FALSE);
	}
	
	//支持的物体类型
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	
	HTREEITEM hItem = m_treeObjType.GetRootItem();

	while(hItem)
	{
		CString strTmp = m_treeObjType.GetItemText(hItem);
		for (int i = 0; i < pRule->nObjectTypeNum; i++)
		{
			if (strcmp(pRule->szObjectTypes[i], strTmp.GetBuffer(0)) == 0
				|| strcmp(ConvertString(pRule->szObjectTypes[i]), strTmp.GetBuffer(0)) == 0)
			{
				m_treeObjType.SetCheck(hItem);
			}
		}

		hItem = m_treeObjType.GetNextSiblingItem(hItem);
	}
	
	//方向
	m_cmbDirection.SetCurSel(pRule->nDirection);
	
	//触发报警位置
	m_cmbTriggerPos.SetCurSel(pRule->bTriggerPosition[0]);
}

void CRuleCrossLine::clearRuleInfo()
{	
	HTREEITEM hItem = m_treeObjType.GetRootItem();
	while(hItem)
	{
		char* pszObjType = (char*)m_treeObjType.GetItemData(hItem);
		if (pszObjType)
		{
			delete []pszObjType;
			pszObjType = NULL;
		}
		
		hItem = m_treeObjType.GetNextSiblingItem(hItem);
	}

	m_treeObjType.DeleteAllItems();
	m_cmbDirection.ResetContent();
	m_cmbTriggerPos.ResetContent();
	m_pRule = NULL;
}

void CRuleCrossLine::setRuleInfo(char* pRuleStruct, int nLen)
{
	if (!pRuleStruct || nLen != EVENT_IVS_CROSSLINEDETECTION)
	{
		return;
	}
}

BOOL CRuleCrossLine::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	
	//支持的物体类型
	m_treeObjType.ModifyStyle(TVS_CHECKBOXES, 0, 0);
	m_treeObjType.ModifyStyle(0, TVS_CHECKBOXES, 0);

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return TRUE;
	}
	
	CFG_CAP_ANALYSE_INFO* pCap = pMainDlg->getCapAnalyseInfo(pMainDlg->getCurrentChannel());
	if (!pCap)
	{
		return TRUE;
	}
	
	int nObjTypeNum = pCap->nSupportedObjectTypeNum;
	for (int i = 0; i < nObjTypeNum; i++)
	{
		m_treeObjType.InsertItem(ConvertString(pCap->szObjectTypeName[i]));
	}
	
	//方向
	m_cmbDirection.InsertString(0, ConvertString(_T("L->R")));
	m_cmbDirection.InsertString(1, ConvertString(_T("R->L")));
	m_cmbDirection.InsertString(2, ConvertString(_T("Both")));
	m_cmbDirection.SetCurSel(-1);

	//触发报警位置
	m_cmbTriggerPos.InsertString(0, ConvertString(_T("Center")));
	m_cmbTriggerPos.InsertString(1, ConvertString(_T("LCenter")));
	m_cmbTriggerPos.InsertString(2, ConvertString(_T("TCenter")));
	m_cmbTriggerPos.InsertString(3, ConvertString(_T("RCenter")));
	m_cmbTriggerPos.InsertString(4, ConvertString(_T("BCenter")));
	m_cmbTriggerPos.SetCurSel(-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRuleCrossLine::updateDraw()
{
	if (m_pRule)
	{
		CFG_ANALYSERULES_INFO stuRuleInfo = {0};
		stuRuleInfo.nRuleCount = 1;
		stuRuleInfo.nRuleLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_CROSSLINE_INFO);
		
		CFG_RULE_INFO cfgRuleInfo = {0};
		cfgRuleInfo.dwRuleType = EVENT_IVS_CROSSLINEDETECTION;
		cfgRuleInfo.nRuleSize = sizeof(CFG_CROSSLINE_INFO);
		
		stuRuleInfo.pRuleBuf = new char[sizeof(CFG_CROSSLINE_INFO) + sizeof(CFG_RULE_INFO)];
		if (!stuRuleInfo.pRuleBuf)
		{
			return;
		}
		memcpy(stuRuleInfo.pRuleBuf, &cfgRuleInfo, sizeof(CFG_RULE_INFO));
		memcpy(stuRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO), m_pRule, sizeof(CFG_CROSSLINE_INFO));
		
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
/*
 *	修改判定方向
 */
void CRuleCrossLine::OnSelchangeRule2CmbDirection() 
{
	// TODO: Add your control notification handler code here	
	if (m_pRule)
	{
		m_pRule->nDirection = m_cmbDirection.GetCurSel();
		
		updateDraw();
	}
}

/*
 *	修改触发报警位置
 */
void CRuleCrossLine::OnSelchangeRule2CmbTriggerpos() 
{
	// TODO: Add your control notification handler code here	
	if (m_pRule)
	{
		m_pRule->nTriggerPosition = 1;
		m_pRule->bTriggerPosition[0] = m_cmbTriggerPos.GetCurSel();
		
		updateDraw();
	}	
}
/*
 *	修改支持的检测物体类型
 */
void CRuleCrossLine::OnClickRule2TreeObjtype(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (!m_pRule)
	{
		return;
	}
	
	CPoint pt;
	GetCursorPos(&pt);
	m_treeObjType.ScreenToClient(&pt);
	
	UINT uFlag = -1;
	HTREEITEM hSelectItem = m_treeObjType.HitTest(pt, &uFlag);
	if (!hSelectItem)
	{
		return;
	}
	
	m_treeObjType.SelectItem(hSelectItem);

	BOOL bCheck = FALSE;

	if (uFlag & TVHT_ONITEMSTATEICON)
	{
		if (m_treeObjType.GetCheck(hSelectItem))
		{
			//turn to false
		}
		else
		{
			//turn to true
			bCheck = TRUE;
		}
	} 
	else
	{
		if (m_treeObjType.GetCheck(hSelectItem))
		{
			bCheck = TRUE;
		} 
		else
		{
			bCheck = FALSE;
		}
	}

	CString strObjType;
	
	int i = 0;
	HTREEITEM hItem = m_treeObjType.GetRootItem();
	ZeroMemory(m_pRule->szObjectTypes, sizeof(m_pRule->szObjectTypes));
	m_pRule->nObjectTypeNum = 0;

	while(hItem)
	{
		if (hSelectItem == hItem)
		{
			if (bCheck)
			{
				char* pszObjType = (char*)m_treeObjType.GetItemData(hItem);
				if (pszObjType)
				{
					strncpy(m_pRule->szObjectTypes[i],
							pszObjType,
							(strlen(pszObjType) > MAX_NAME_LEN ? MAX_NAME_LEN : strlen(pszObjType)));
				}
				i++;
			}
		}
		else if (m_treeObjType.GetCheck(hItem))
		{
			char* pszObjType = (char*)m_treeObjType.GetItemData(hItem);
			if (pszObjType)
			{
				strncpy(m_pRule->szObjectTypes[i],
					pszObjType,
					(strlen(pszObjType) > MAX_NAME_LEN ? MAX_NAME_LEN : strlen(pszObjType)));
			}
			i++;
		}
		hItem = m_treeObjType.GetNextSiblingItem(hItem);
	}
	m_pRule->nObjectTypeNum = i;

	*pResult = 0;
}

void CRuleCrossLine::OnRule2RadioCfilter() 
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

void CRuleCrossLine::OnRule2RadioGfilter() 
{
	// TODO: Add your control notification handler code here
	m_pRule->bSizeFileter = FALSE;
	m_pRule->stuSizeFileter.nCalibrateBoxNum = 0;	
}
