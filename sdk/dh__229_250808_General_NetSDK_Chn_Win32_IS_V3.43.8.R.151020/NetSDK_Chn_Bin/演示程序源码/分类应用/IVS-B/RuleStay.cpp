// RuleStay.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "RuleStay.h"
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
// CRule9Stay dialog


CRuleStay::CRuleStay(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleStay::IDD, pParent),
	m_pRule(NULL)
{
	//{{AFX_DATA_INIT(CRuleStay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRuleStay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleStay)
	DDX_Control(pDX, IDC_RULE9_TREE_OBJTYPE, m_treeObjType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleStay, CDialog)
	//{{AFX_MSG_MAP(CRuleStay)
	ON_NOTIFY(NM_CLICK, IDC_RULE9_TREE_OBJTYPE, OnClickRule9TreeObjtype)
	ON_EN_CHANGE(IDC_RULE9_EDT_MINDUR, OnChangeRule9EdtMindur)
	ON_EN_CHANGE(IDC_RULE9_EDT_REPORTINTERVAL, OnChangeRule9EdtReportinterval)
	ON_BN_CLICKED(IDC_RULE9_RADIO_CFILTER, OnRule9RadioCfilter)
	ON_BN_CLICKED(IDC_RULE9_RADIO_GFILTER, OnRule9RadioGfilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleStay message handlers

void CRuleStay::initSubDlg()
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
		if (pCap->stSupportScenes.stScenes[0].stSpportRules[i].dwSupportedRule == EVENT_IVS_STAYDETECTION)
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
		
	//最短持续时间
// 	SetDlgItemInt(IDC_RULE9_EDT_MINDUR, 0, FALSE);
	
	//报告时间间隔
// 	SetDlgItemInt(IDC_RULE9_EDT_REPORTINTERVAL, 0, FALSE);
}

void CRuleStay::showRuleInfo(RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || pRuleStruct->RuleInfo.dwRuleType != EVENT_IVS_STAYDETECTION)
	{
		return;
	}
	
	//Todo: show info
	if (!pRuleStruct->pRuleBuf)
	{
		return;
	}
	
	CFG_STAY_INFO* pRule = (CFG_STAY_INFO*)pRuleStruct->pRuleBuf;
	m_pRule = pRule;
	if (m_pRule->stuSizeFileter.nCalibrateBoxNum)
	{
		((CButton*)GetDlgItem(IDC_RULE9_RADIO_GFILTER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RULE9_RADIO_CFILTER))->SetCheck(TRUE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_RULE9_RADIO_GFILTER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RULE9_RADIO_CFILTER))->SetCheck(FALSE);
	}

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
	
	int nObjTypeNum = pCap->nSupportedObjectTypeNum;	
	HTREEITEM hItem = 0;
	nObjTypeNum = pRule->nObjectTypeNum;
	
	for (int i = 0; i < nObjTypeNum; i++)
	{
		hItem = m_treeObjType.GetRootItem();
		while (hItem)
		{
			CString strTmp = m_treeObjType.GetItemText(hItem);
			if (strcmp(pRule->szObjectTypes[i], strTmp.GetBuffer(0)) == 0
				|| strcmp(ConvertString(pRule->szObjectTypes[i]), strTmp.GetBuffer(0)) == 0)
			{
				m_treeObjType.SetCheck(hItem);
			}
			
			hItem = m_treeObjType.GetNextSiblingItem(hItem);
		}
	}

	//最短持续时间
	SetDlgItemInt(IDC_RULE9_EDT_MINDUR, pRule->nMinDuration, FALSE);

	//报告时间间隔
	SetDlgItemInt(IDC_RULE9_EDT_REPORTINTERVAL, pRule->nReportInterval, FALSE);
}

void CRuleStay::clearRuleInfo()
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
	m_pRule = NULL;
}

void CRuleStay::setRuleInfo(char* pRuleStruct, int nLen)
{
	if (!pRuleStruct || nLen != EVENT_IVS_STAYDETECTION)
	{
		return;
	}
}

void CRuleStay::updateDraw()
{
	if (m_pRule)
	{
		CFG_ANALYSERULES_INFO stuRuleInfo = {0};
		stuRuleInfo.nRuleCount = 1;
		stuRuleInfo.nRuleLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_RETROGRADEDETECTION_INFO);
		
		CFG_RULE_INFO cfgRuleInfo = {0};
		cfgRuleInfo.dwRuleType = EVENT_IVS_RETROGRADEDETECTION;
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

BOOL CRuleStay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRuleStay::OnClickRule9TreeObjtype(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (!m_pRule)
	{
		return;
	}
	
	CPoint pt;
	GetCursorPos(&pt);
	m_treeObjType.ScreenToClient(&pt);
	
	HTREEITEM hItem = m_treeObjType.HitTest(pt);
	if (!hItem)
	{
		return;
	}
	
	m_treeObjType.SelectItem(hItem);
		
	if (m_treeObjType.GetCheck(hItem))
	{
		m_treeObjType.SetCheck(hItem, FALSE);
	}
	else
	{
		m_treeObjType.SetCheck(hItem);
	}
	
	CString strObjType;
	
	int i = 0;
	hItem = m_treeObjType.GetRootItem();
	while(hItem)
	{
		if (m_treeObjType.GetCheck(hItem))
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

void CRuleStay::OnChangeRule9EdtMindur() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strMinDur;
		GetDlgItemText(IDC_RULE9_EDT_MINDUR, strMinDur);
		
		int iMinDur = atoi(strMinDur.GetBuffer(strMinDur.GetLength()));
		
		m_pRule->nMinDuration = iMinDur;
	}
}

void CRuleStay::OnChangeRule9EdtReportinterval() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strInterval;
		GetDlgItemText(IDC_RULE9_EDT_REPORTINTERVAL, strInterval);
		
		int iMinDur = atoi(strInterval.GetBuffer(strInterval.GetLength()));
		
		m_pRule->nMinDuration = iMinDur;
	}
}

void CRuleStay::OnRule9RadioCfilter() 
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

void CRuleStay::OnRule9RadioGfilter() 
{
	// TODO: Add your control notification handler code here
	m_pRule->bSizeFileter = FALSE;
	m_pRule->stuSizeFileter.nCalibrateBoxNum = 0;
	
}
