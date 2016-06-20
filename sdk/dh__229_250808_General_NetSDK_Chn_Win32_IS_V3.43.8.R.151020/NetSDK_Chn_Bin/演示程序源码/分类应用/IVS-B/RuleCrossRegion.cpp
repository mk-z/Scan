// RuleCrossRegion.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "RuleCrossRegion.h"
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
// CRule3CrossRegion dialog


CRuleCrossRegion::CRuleCrossRegion(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleCrossRegion::IDD, pParent),
	m_pRule(NULL)
{
	//{{AFX_DATA_INIT(CRule3CrossRegion)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRuleCrossRegion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleCrossRegion)
	DDX_Control(pDX, IDC_RULE3_TREE_OBJTYPE, m_treeObjType);
	DDX_Control(pDX, IDC_RULE3_TREE_ACTIONTYPE, m_treeActionType);
	DDX_Control(pDX, IDC_RULE3_CMB_DIRECTION, m_cmbDirection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleCrossRegion, CDialog)
	//{{AFX_MSG_MAP(CRuleCrossRegion)
	ON_NOTIFY(NM_CLICK, IDC_RULE3_TREE_OBJTYPE, OnClickRule3TreeObjtype)
	ON_NOTIFY(NM_CLICK, IDC_RULE3_TREE_ACTIONTYPE, OnClickRule3TreeActiontype)
	ON_CBN_SELCHANGE(IDC_RULE3_CMB_DIRECTION, OnSelchangeRule3CmbDirection)
	ON_EN_CHANGE(IDC_RULE3_EDT_MINTARG, OnChangeRule3EdtMintarg)
	ON_EN_CHANGE(IDC_RULE3_EDT_MAXTARG, OnChangeRule3EdtMaxtarg)
	ON_EN_CHANGE(IDC_RULE3_EDT_MINDUR, OnChangeRule3EdtMindur)
	ON_EN_CHANGE(IDC_RULE3_EDT_REPORTINTERVAL, OnChangeRule3EdtReportinterval)
	ON_BN_CLICKED(IDC_RULE3_RADIO_CFILTER, OnRule3RadioCfilter)
	ON_BN_CLICKED(IDC_RULE3_RADIO_GFILTER, OnRule3RadioGfilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRule3CrossRegion message handlers

void CRuleCrossRegion::initSubDlg()
{
	m_pRule = NULL;

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
		if (pCap->stSupportScenes.stScenes[0].stSpportRules[i].dwSupportedRule == EVENT_IVS_CROSSREGIONDETECTION)
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

	//检测动作列表
	int nActionType = pCap->stSupportScenes.stScenes[0].stSpportRules[i].nSupportedActionsNum;
	for (int k = 0; k < nActionType; k++)
	{
		HTREEITEM hItem = NULL;
		if (0 == strcmp(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedActions[k], "Appear"))
		{
			hItem = m_treeActionType.InsertItem(ConvertString(_T("Appear")));
			m_treeActionType.SetItemData(hItem, (DWORD)0);
		}
		else if (0 == strcmp(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedActions[k], "Disappear"))
		{
			hItem = m_treeActionType.InsertItem(ConvertString(_T("Disappear")));
			m_treeActionType.SetItemData(hItem, (DWORD)1);
		}
		else if (0 == strcmp(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedActions[k], "Inside"))
		{
			hItem = m_treeActionType.InsertItem(ConvertString(_T("In the region")));
			m_treeActionType.SetItemData(hItem, (DWORD)2);
		}
		else if (0 == strcmp(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedActions[k], "Cross"))
		{
			hItem = m_treeActionType.InsertItem(ConvertString(_T("Cross the region")));
			m_treeActionType.SetItemData(hItem, (DWORD)3);
		}
	}
	
	//方向
	m_cmbDirection.InsertString(0, ConvertString(_T("Enter")));
	m_cmbDirection.InsertString(1, ConvertString(_T("Leave")));
	m_cmbDirection.InsertString(2, ConvertString(_T("Both")));
	m_cmbDirection.SetCurSel(-1);

	//最小目标个数
// 	SetDlgItemInt(IDC_RULE3_EDT_MINTARG, 0, FALSE);
	
	//最大目标个数
// 	SetDlgItemInt(IDC_RULE3_EDT_MAXTARG, 0, FALSE);
	
	//最短持续时间
// 	SetDlgItemInt(IDC_RULE3_EDT_MINDUR, 0, FALSE);
	
	//报告间隔时间
// 	SetDlgItemInt(IDC_RULE3_EDT_REPORTINTERVAL, 0, FALSE);

	m_cmbDirection.EnableWindow(FALSE);
	GetDlgItem(IDC_RULE3_EDT_MINTARG)->EnableWindow(FALSE);
	GetDlgItem(IDC_RULE3_EDT_MAXTARG)->EnableWindow(FALSE);
	GetDlgItem(IDC_RULE3_EDT_MINDUR)->EnableWindow(FALSE);
	GetDlgItem(IDC_RULE3_EDT_REPORTINTERVAL)->EnableWindow(FALSE);
}

void CRuleCrossRegion::showRuleInfo(RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || pRuleStruct->RuleInfo.dwRuleType != EVENT_IVS_CROSSREGIONDETECTION)
	{
		return;
	}
	
	m_cmbDirection.EnableWindow(FALSE);
	GetDlgItem(IDC_RULE3_EDT_MINTARG)->EnableWindow(FALSE);
	GetDlgItem(IDC_RULE3_EDT_MAXTARG)->EnableWindow(FALSE);
	GetDlgItem(IDC_RULE3_EDT_MINDUR)->EnableWindow(FALSE);
	GetDlgItem(IDC_RULE3_EDT_REPORTINTERVAL)->EnableWindow(FALSE);
	
	//Todo: show info
	if (!pRuleStruct->pRuleBuf)
	{
		return;
	}
	
	CFG_CROSSREGION_INFO* pRule = (CFG_CROSSREGION_INFO*)pRuleStruct->pRuleBuf;
	m_pRule = pRule;
	if (m_pRule->stuSizeFileter.nCalibrateBoxNum)
	{
		((CButton*)GetDlgItem(IDC_RULE3_RADIO_GFILTER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RULE3_RADIO_CFILTER))->SetCheck(TRUE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_RULE3_RADIO_GFILTER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RULE3_RADIO_CFILTER))->SetCheck(FALSE);
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
		
	//检测动作列表
	for (int i = 0; i < pRule->nActionType; i++)
	{
		hItem = m_treeActionType.GetRootItem();
		while(hItem)
		{
			DWORD dwActionType = m_treeActionType.GetItemData(hItem);
			if (dwActionType == pRule->bActionType[i])
			{
				m_treeActionType.SetCheck(hItem);
				break;
			}

			hItem = m_treeActionType.GetNextSiblingItem(hItem);
		}
	}
	
	//方向
	m_cmbDirection.SetCurSel(pRule->nDirection);

	//最小目标个数
	SetDlgItemInt(IDC_RULE3_EDT_MINTARG, pRule->nMinTargets, FALSE);

	//最大目标个数
	SetDlgItemInt(IDC_RULE3_EDT_MAXTARG, pRule->nMaxTargets, FALSE);

	//最短持续时间
	SetDlgItemInt(IDC_RULE3_EDT_MINDUR, pRule->nMinDuration, FALSE);

	//报告间隔时间
	SetDlgItemInt(IDC_RULE3_EDT_REPORTINTERVAL, pRule->nReportInterval, FALSE);
}

void CRuleCrossRegion::clearRuleInfo()
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
	m_treeActionType.DeleteAllItems();
	m_cmbDirection.ResetContent();
	m_pRule = NULL;
}

void CRuleCrossRegion::setRuleInfo(char* pRuleStruct, int nLen)
{
	if (!pRuleStruct || nLen != EVENT_IVS_CROSSREGIONDETECTION)
	{
		return;
	}
}

BOOL CRuleCrossRegion::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	m_treeActionType.ModifyStyle(TVS_CHECKBOXES, 0, 0);
	m_treeActionType.ModifyStyle(0, TVS_CHECKBOXES, 0);

	m_treeObjType.ModifyStyle(TVS_CHECKBOXES, 0, 0);
	m_treeObjType.ModifyStyle(0, TVS_CHECKBOXES, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRuleCrossRegion::updateDraw()
{
	if (m_pRule)
	{
		CFG_ANALYSERULES_INFO stuRuleInfo = {0};
		stuRuleInfo.nRuleCount = 1;
		stuRuleInfo.nRuleLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_CROSSREGION_INFO);
		
		CFG_RULE_INFO cfgRuleInfo = {0};
		cfgRuleInfo.dwRuleType = EVENT_IVS_CROSSREGIONDETECTION;
		cfgRuleInfo.nRuleSize = sizeof(CFG_CROSSREGION_INFO);
		
		stuRuleInfo.pRuleBuf = new char[sizeof(CFG_CROSSREGION_INFO) + sizeof(CFG_RULE_INFO)];
		if (!stuRuleInfo.pRuleBuf)
		{
			return;
		}
		memcpy(stuRuleInfo.pRuleBuf, &cfgRuleInfo, sizeof(CFG_RULE_INFO));
		memcpy(stuRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO), m_pRule, sizeof(CFG_CROSSREGION_INFO));
		
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
 *	修改支持的检测物体类型
 */
void CRuleCrossRegion::OnClickRule3TreeObjtype(NMHDR* pNMHDR, LRESULT* pResult) 
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
/*
 *	修改支持的动作列表
 */
void CRuleCrossRegion::OnClickRule3TreeActiontype(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint pt;
	GetCursorPos(&pt);
	m_treeActionType.ScreenToClient(&pt);

	UINT uFlag = -1;
	HTREEITEM hSelectItem = m_treeActionType.HitTest(pt, &uFlag);
	if (!hSelectItem)
	{
		return;
	}

	BOOL bCheck = FALSE;

	if (uFlag & TVHT_ONITEMSTATEICON)
	{
		if (m_treeActionType.GetCheck(hSelectItem))
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
		if (m_treeActionType.GetCheck(hSelectItem))
		{
			bCheck = TRUE;
		}
	}

	if (m_treeActionType.GetItemData(hSelectItem) == 2)
	{
		//in the region
		m_cmbDirection.EnableWindow(FALSE);
		GetDlgItem(IDC_RULE3_EDT_MINTARG)->EnableWindow(TRUE);
		GetDlgItem(IDC_RULE3_EDT_MAXTARG)->EnableWindow(TRUE);
		GetDlgItem(IDC_RULE3_EDT_MINDUR)->EnableWindow(TRUE);
		GetDlgItem(IDC_RULE3_EDT_REPORTINTERVAL)->EnableWindow(TRUE);
	} 
	else if (m_treeActionType.GetItemData(hSelectItem) == 3)
	{
		//cross the region
		m_cmbDirection.EnableWindow(TRUE);
		GetDlgItem(IDC_RULE3_EDT_MINTARG)->EnableWindow(FALSE);
		GetDlgItem(IDC_RULE3_EDT_MAXTARG)->EnableWindow(FALSE);
		GetDlgItem(IDC_RULE3_EDT_MINDUR)->EnableWindow(FALSE);
		GetDlgItem(IDC_RULE3_EDT_REPORTINTERVAL)->EnableWindow(FALSE);
	}	
	else
	{
		m_cmbDirection.EnableWindow(FALSE);
		GetDlgItem(IDC_RULE3_EDT_MINTARG)->EnableWindow(FALSE);
		GetDlgItem(IDC_RULE3_EDT_MAXTARG)->EnableWindow(FALSE);
		GetDlgItem(IDC_RULE3_EDT_MINDUR)->EnableWindow(FALSE);
		GetDlgItem(IDC_RULE3_EDT_REPORTINTERVAL)->EnableWindow(FALSE);
	}
	
	m_pRule->nActionType = 0;
	ZeroMemory(m_pRule->bActionType, sizeof(m_pRule->bActionType));

	int i = 0;
	HTREEITEM hItem = m_treeActionType.GetRootItem();
	while(hItem)
	{
		if (hItem == hSelectItem)
		{
			if (bCheck)
			{
				m_pRule->bActionType[i] = m_treeActionType.GetItemData(hItem);
				i++;
			}
		} 
		else
		{
			if (m_treeActionType.GetCheck(hItem))
			{
				m_pRule->bActionType[i] = m_treeActionType.GetItemData(hItem);
				i++;
			}
		}
		hItem = m_treeActionType.GetNextSiblingItem(hItem);
	}

	m_pRule->nActionType = i;

	*pResult = 0;
}
/*
 *	修改判定方向
 */
void CRuleCrossRegion::OnSelchangeRule3CmbDirection() 
{
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		m_pRule->nDirection = m_cmbDirection.GetCurSel();
		
		updateDraw();
	}	
}
/*
 *	修改最小目标个数
 */
void CRuleCrossRegion::OnChangeRule3EdtMintarg() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strMinTarg;
		GetDlgItemText(IDC_RULE3_EDT_MINTARG, strMinTarg);
		
		int iMinTarg= atoi(strMinTarg.GetBuffer(strMinTarg.GetLength()));
		
		m_pRule->nMinTargets = iMinTarg;
	}
}
/*
 *	修改最大目标个数
 */
void CRuleCrossRegion::OnChangeRule3EdtMaxtarg() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strMaxTarg;
		GetDlgItemText(IDC_RULE3_EDT_MAXTARG, strMaxTarg);
		
		int iMaxTarg = atoi(strMaxTarg.GetBuffer(strMaxTarg.GetLength()));
		
		m_pRule->nMaxTargets = iMaxTarg;
	}
}
/*
 *	修改最短持续时间
 */
void CRuleCrossRegion::OnChangeRule3EdtMindur() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strMinDur;
		GetDlgItemText(IDC_RULE3_EDT_MINDUR, strMinDur);
		
		int iMinDur = atoi(strMinDur.GetBuffer(strMinDur.GetLength()));
		
		m_pRule->nMinDuration = iMinDur;
	}
}
/*
 *	修改报告时间间隔
 */
void CRuleCrossRegion::OnChangeRule3EdtReportinterval() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strInterval;
		GetDlgItemText(IDC_RULE3_EDT_REPORTINTERVAL, strInterval);
		
		int iInterval = atoi(strInterval.GetBuffer(strInterval.GetLength()));
		
		m_pRule->nReportInterval = iInterval;
	}
}

void CRuleCrossRegion::OnRule3RadioCfilter() 
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

void CRuleCrossRegion::OnRule3RadioGfilter() 
{
	// TODO: Add your control notification handler code here
	m_pRule->bSizeFileter = FALSE;
	m_pRule->stuSizeFileter.nCalibrateBoxNum = 0;	
}
