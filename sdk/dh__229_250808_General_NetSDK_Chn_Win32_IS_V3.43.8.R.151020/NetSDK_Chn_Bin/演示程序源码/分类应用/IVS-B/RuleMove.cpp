// RuleMove.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "RuleMove.h"
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
// CRuleMove dialog

CRuleMove::CRuleMove(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleMove::IDD, pParent),
	m_pRule(NULL)
{
	//{{AFX_DATA_INIT(CRuleMove)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	for (int i = 0; i < 3; i++)
	{
		ZeroMemory(m_szArrDetectType[i], MAX_NAME_LEN);
	}

	strncpy(m_szArrDetectType[0], "FastMove", strlen("FastMove"));
	strncpy(m_szArrDetectType[1], "AbruptSpeedup", strlen("AbruptSpeedup"));
	strncpy(m_szArrDetectType[2], "AbruptSlowdown", strlen("AbruptSlowdown"));
}

void CRuleMove::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleMove)
	DDX_Control(pDX, IDC_RULE4_SLID_SENSI, m_slidSensi);
	DDX_Control(pDX, IDC_RULE4_TREE_DETECTTYPE, m_treeDetectType);
	DDX_Control(pDX, IDC_RULE4_TREE_OBJTYPE, m_treeObjType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRuleMove, CDialog)
	//{{AFX_MSG_MAP(CRuleMove)
	ON_NOTIFY(NM_CLICK, IDC_RULE4_TREE_OBJTYPE, OnClickRule4TreeObjtype)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_RULE4_EDT_MINDUR, OnChangeRule4EdtMindur)
	ON_NOTIFY(NM_CLICK, IDC_RULE4_TREE_DETECTTYPE, OnClickRule4TreeDetecttype)
	ON_BN_CLICKED(IDC_RULE4_RADIO_CFILTER, OnRule4RadioCfilter)
	ON_BN_CLICKED(IDC_RULE4_RADIO_GFILTER, OnRule4RadioGfilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleMove message handlers

void CRuleMove::initSubDlg()
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
		if (pCap->stSupportScenes.stScenes[0].stSpportRules[i].dwSupportedRule == EVENT_IVS_MOVEDETECTION)
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

	//检测动作类型
	//目前只支持"快速移动"一种类型
// 	HTREEITEM hItem = m_treeDetectType.InsertItem(ConvertString("FastMove"));
// 	if (hItem)
// 	{
// 		m_treeDetectType.SetCheck(hItem, FALSE);
// 	}

	int k = 0;
	int nDetTypeNum = pCap->stSupportScenes.stScenes[0].stSpportRules[i].nSupportedDetectTypeNum;
	for (k = 0; k < nDetTypeNum; k++)
	{
		HTREEITEM hItem = m_treeDetectType.InsertItem(ConvertString(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedDetectTypes[k]));
		char* p = new char[MAX_NAME_LEN];
		if (p)
		{
			ZeroMemory(p, MAX_NAME_LEN);
			strncpy(p,
					pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedDetectTypes[k],
					strlen(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedDetectTypes[k]));
			m_treeDetectType.SetItemData(hItem, (DWORD)p);
		}
	}
	
	//灵敏度
	m_slidSensi.SetRange(1, 10);
	m_slidSensi.SetPos(5);
	
	//最短持续时间
}

void CRuleMove::showRuleInfo(RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || pRuleStruct->RuleInfo.dwRuleType != EVENT_IVS_MOVEDETECTION)
	{
		return;
	}
	
	//Todo: show info
	if (!pRuleStruct->pRuleBuf)
	{
		return;
	}
	
	CFG_MOVE_INFO* pRule = (CFG_MOVE_INFO*)pRuleStruct->pRuleBuf;
	m_pRule = pRule;
	if (m_pRule->stuSizeFileter.nCalibrateBoxNum)
	{
		((CButton*)GetDlgItem(IDC_RULE4_RADIO_GFILTER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RULE4_RADIO_CFILTER))->SetCheck(TRUE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_RULE4_RADIO_GFILTER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RULE4_RADIO_CFILTER))->SetCheck(FALSE);
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

	//检测动作类型
	//目前只支持"快速移动"一种类型
// 	if (m_pRule->bDetectType[0] == 0 && m_pRule->nTypeNumber == 1)
// 	{
// 		HTREEITEM hItem = m_treeDetectType.GetRootItem();
// 		if (hItem)
// 		{
// 			m_treeDetectType.SetCheck(hItem);
// 		}
// 	}

	hItem = m_treeDetectType.GetRootItem();
	while(hItem)
	{
		CString strTmp = m_treeDetectType.GetItemText(hItem);
		for (int i = 0; i < pRule->nTypeNumber; i++)
		{
			char* p = (char*)m_treeDetectType.GetItemData(hItem);
			if (p)
			{
				if (strcmp(p, m_szArrDetectType[pRule->bDetectType[i]]) == 0)
				{
					m_treeDetectType.SetCheck(hItem);
					break;
				}				
			}
		}

		hItem = m_treeDetectType.GetNextSiblingItem(hItem);
	}
	
	//灵敏度
	m_slidSensi.SetPos(pRule->bSensitivity);

	//最短持续时间
	SetDlgItemInt(IDC_RULE4_EDT_MINDUR, pRule->nMinDuration, FALSE);
}

void CRuleMove::clearRuleInfo()
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

	hItem = m_treeDetectType.GetRootItem();
	while(hItem)
	{
		char* p = (char*)m_treeDetectType.GetItemData(hItem);
		if (p)
		{
			delete []p;
			p = NULL;
		}

		hItem = m_treeDetectType.GetNextSiblingItem(hItem);
	}

	m_treeDetectType.DeleteAllItems();
	m_slidSensi.ClearSel(TRUE);
	m_pRule = NULL;
}

void CRuleMove::setRuleInfo(char* pRuleStruct, int nLen)
{
	if (!pRuleStruct || nLen != EVENT_IVS_MOVEDETECTION)
	{
		return;
	}
}

void CRuleMove::updateDraw()
{
	if (m_pRule)
	{
		CFG_ANALYSERULES_INFO stuRuleInfo = {0};
		stuRuleInfo.nRuleCount = 1;
		stuRuleInfo.nRuleLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_MOVE_INFO);
		
		CFG_RULE_INFO cfgRuleInfo = {0};
		cfgRuleInfo.dwRuleType = EVENT_IVS_MOVEDETECTION;
		cfgRuleInfo.nRuleSize = sizeof(CFG_MOVE_INFO);
		
		stuRuleInfo.pRuleBuf = new char[sizeof(CFG_MOVE_INFO) + sizeof(CFG_RULE_INFO)];
		if (!stuRuleInfo.pRuleBuf)
		{
			return;
		}
		memcpy(stuRuleInfo.pRuleBuf, &cfgRuleInfo, sizeof(CFG_RULE_INFO));
		memcpy(stuRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO), m_pRule, sizeof(CFG_MOVE_INFO));
		
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

BOOL CRuleMove::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	
	m_treeDetectType.ModifyStyle(TVS_CHECKBOXES, 0, 0);
	m_treeDetectType.ModifyStyle(0, TVS_CHECKBOXES, 0);
	
	m_treeObjType.ModifyStyle(TVS_CHECKBOXES, 0, 0);
	m_treeObjType.ModifyStyle(0, TVS_CHECKBOXES, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
 *	修改支持的检测物体类型
 */
void CRuleMove::OnClickRule4TreeObjtype(NMHDR* pNMHDR, LRESULT* pResult) 
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
 *	修改灵敏度
 */
void CRuleMove::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nCtrlID = pScrollBar->GetDlgCtrlID();
	if (nCtrlID == IDC_RULE4_SLID_SENSI)
	{
		CSliderCtrl* pSliderCtrl = (CSliderCtrl*)pScrollBar;
		if (pScrollBar && m_pRule)
		{
			m_pRule->bSensitivity = pSliderCtrl->GetPos();
		}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
/*
 *	修改最短持续时间
 */
void CRuleMove::OnChangeRule4EdtMindur() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strMinDur;
		GetDlgItemText(IDC_RULE4_EDT_MINDUR, strMinDur);
		
		int iMinDur = atoi(strMinDur.GetBuffer(strMinDur.GetLength()));
		
		m_pRule->nMinDuration = iMinDur;
	}
}
/*
 *	检测类型
 */
void CRuleMove::OnClickRule4TreeDetecttype(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (!m_pRule)
	{
		return;
	}
	
	CPoint pt;
	GetCursorPos(&pt);
	m_treeDetectType.ScreenToClient(&pt);
	
	UINT uFlag = -1;
	HTREEITEM hSelectItem = m_treeDetectType.HitTest(pt, &uFlag);
	if (!hSelectItem)
	{
		return;
	}
	
	m_treeDetectType.SelectItem(hSelectItem);
	
	BOOL bCheck = FALSE;
	
	if (uFlag & TVHT_ONITEMSTATEICON)
	{
		if (m_treeDetectType.GetCheck(hSelectItem))
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
		if (m_treeDetectType.GetCheck(hSelectItem))
		{
			bCheck = TRUE;
		} 
		else
		{
			bCheck = FALSE;
		}
	}

// 	if (bCheck)
// 	{
// 		m_pRule->nTypeNumber = 1;
// 		m_pRule->bDetectType[0] = 0;
// 	}
// 	else
// 	{
// 		m_pRule->nTypeNumber = 0;
// 		m_pRule->bDetectType[0] = 0;
// 	}

	HTREEITEM hItem = m_treeDetectType.GetRootItem();
	m_pRule->nTypeNumber = 0;
	ZeroMemory(m_pRule->bDetectType, 4);

	while(hItem)
	{
		if (hSelectItem == hItem)
		{
			if (bCheck)
			{
				char* p = (char*)m_treeDetectType.GetItemData(hItem);
				if (p)
				{
					for (int i = 0; i < 3; i++)
					{
						if (strcmp(p, m_szArrDetectType[i]) == 0)
						{
							m_pRule->bDetectType[m_pRule->nTypeNumber] = i;
							m_pRule->nTypeNumber++;
							break;
						}
					}
				}
			}
		} 
		else if (m_treeDetectType.GetCheck(hItem))
		{
			char* p = (char*)m_treeDetectType.GetItemData(hItem);
			if (p)
			{
				for (int i = 0; i < 3; i++)
				{
					if (strcmp(p, m_szArrDetectType[i]) == 0)
					{
						m_pRule->bDetectType[m_pRule->nTypeNumber] = i;
						m_pRule->nTypeNumber++;
						break;
					}
				}
			}
		}

		hItem = m_treeDetectType.GetNextSiblingItem(hItem);
	}
	
	*pResult = 0;
}

void CRuleMove::OnRule4RadioCfilter() 
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

void CRuleMove::OnRule4RadioGfilter() 
{
	// TODO: Add your control notification handler code here
	m_pRule->bSizeFileter = FALSE;
	m_pRule->stuSizeFileter.nCalibrateBoxNum = 0;	
}
