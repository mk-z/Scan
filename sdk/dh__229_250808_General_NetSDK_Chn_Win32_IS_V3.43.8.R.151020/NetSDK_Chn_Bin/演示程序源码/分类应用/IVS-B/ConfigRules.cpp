// ConfigRules.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "ConfigRules.h"
#include "DemoIVSbDlg.h"
#include "IvsRulePreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigRules dialog


CConfigRules::CConfigRules(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigRules::IDD, pParent),
	m_nPlayPortNum(450),
	m_nDrawPortNum(100),
	m_pIvsRulePreview(NULL),
	m_bAddRule(FALSE)
{
	//{{AFX_DATA_INIT(CConfigRules)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigRules::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigRules)
	DDX_Control(pDX, IDC_CFGRULE_TREE_RULELIST, m_treeRuleList);
	DDX_Control(pDX, IDC_CFGRULE_CMB_RULETYPE, m_cmbRuleType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigRules, CDialog)
	//{{AFX_MSG_MAP(CConfigRules)
	ON_CBN_SELCHANGE(IDC_CFGRULE_CMB_RULETYPE, OnSelchangeCfgruleCmbRuletype)
	ON_BN_CLICKED(IDC_CFGRULE_BTN_ADDRULE, OnCfgruleBtnAddrule)
	ON_BN_CLICKED(IDC_CFGRULE_BTN_DELRULE, OnCfgruleBtnDelrule)
	ON_BN_CLICKED(IDC_CFGRULE_BTN_REDRAW, OnCfgruleBtnRedraw)
	ON_BN_CLICKED(IDC_CFGRULE_BTN_GET, OnCfgruleBtnGet)
	ON_BN_CLICKED(IDC_CFGRULE_BTN_SET, OnCfgruleBtnSet)
	ON_NOTIFY(NM_DBLCLK, IDC_CFGRULE_TREE_RULELIST, OnDblclkCfgruleTreeRulelist)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_CFGRULE_TREE_RULELIST, OnClickCfgruleTreeRulelist)
	ON_EN_CHANGE(IDC_CFGRULE_EDT_RULENAME, OnChangeCfgruleEdtRulename)
	ON_MESSAGE(WM_RULEDONE, OnRuleDone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*
 *	WM_RULEDONE
 */
LRESULT CConfigRules::OnRuleDone(WPARAM wParam, LPARAM lPara)
{
	HTREEITEM hItemToBeDraw = (HTREEITEM)wParam;
	RuleStruct* pRuleStruct = (RuleStruct*)lPara;

	HTREEITEM hItem = 0;
	RuleStruct* pRuleNode = NULL;
	CFG_CROSSLINE_INFO* pCrossLine = NULL;
	int i = 0, j = 0;

	if (!hItemToBeDraw || !pRuleStruct)
	{
		goto ErrorHandle;
	}

	hItem = m_treeRuleList.GetSelectedItem();
	if (hItem != hItemToBeDraw)
	{
		goto ErrorHandle;
	}

	pRuleNode
		= (RuleStruct*)m_treeRuleList.GetItemData(hItem);
	if (!pRuleNode)
	{
		goto ErrorHandle;
	}

	if (pRuleNode->pRuleBuf)
	{
		delete []pRuleNode->pRuleBuf;
		pRuleNode->pRuleBuf;
	}

	pRuleNode->pRuleBuf = new char[pRuleStruct->RuleInfo.nRuleSize];
	if (!pRuleStruct->pRuleBuf)
	{
		goto ErrorHandle;
	}

	memcpy(&pRuleNode->RuleInfo, &pRuleStruct->RuleInfo, sizeof(CFG_RULE_INFO));
	memcpy(pRuleNode->pRuleBuf, pRuleStruct->pRuleBuf, pRuleStruct->RuleInfo.nRuleSize);

	setRuleTime(pRuleNode->RuleInfo.dwRuleType, pRuleNode);

	goto ErrorHandle;

ErrorHandle:
	//////////////////////////////////////////////////////////////////////////
	GetDlgItem(IDC_CFGRULE_BTN_ADDRULE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CFGRULE_BTN_DELRULE)->EnableWindow(TRUE);
	m_treeRuleList.EnableWindow(TRUE);
	m_bAddRule = FALSE;
	if (pRuleStruct)
	{
		showSubRuleDlg(pRuleStruct->RuleInfo.dwRuleType, TRUE);
		showSubRuleInfo(pRuleStruct->RuleInfo.dwRuleType, pRuleNode);
		if (pRuleStruct->pRuleBuf)
		{
			delete []pRuleStruct->pRuleBuf;
			pRuleStruct->pRuleBuf = NULL;
		}

		delete pRuleStruct;
		pRuleStruct = NULL;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CConfigRules message handlers

/*
 *	
 */
void CConfigRules::initConfigRulesDlg(int nChannel)
{
	if (nChannel == -1)
	{
		uninitConfigRulesDlg();
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}	

	TCHAR szChnName[32] = {0};
	_sntprintf(szChnName, _countof(szChnName), _T("%s%02d"), ConvertString(_T("Channel")), nChannel + 1);
	SetDlgItemText(IDC_CFGRULE_EDT_CHANNELNAME, szChnName);


	//////////////////////////////////////////////////////////////////////////
	//
	CFG_CAP_ANALYSE_INFO* pCapInfo = pMainDlg->getCapAnalyseInfo(nChannel);
	if (!pCapInfo)
	{
		return;
	}
	//初始化combobox控件
	int nChn = 0;
	int nSupportedRulesNum = 0;
	int i = 0;
	CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobal = pMainDlg->getAnalyseGlobalInfo(pMainDlg->getCurrentChannel());
	if (pAnalyseGlobal)
	{
		for (i = 0; i < pCapInfo->stSupportScenes.nScenes; i++)
		{
			if (strcmp(pAnalyseGlobal->szSceneType,
				pCapInfo->stSupportScenes.stScenes[i].szSceneName) == 0)
			{
				nSupportedRulesNum = pCapInfo->stSupportScenes.stScenes[i].nSupportRules;
				break;
			}
		}
	}

	DWORD* pdwRuleType = NULL;

	if (nSupportedRulesNum)
	{
		pdwRuleType = new DWORD[nSupportedRulesNum];
		if (!pdwRuleType)
		{
			return;
		}

		ZeroMemory(pdwRuleType, sizeof(DWORD) * nSupportedRulesNum);
	}

	for(int j = 0; j < nSupportedRulesNum; j++)
	{
		pdwRuleType[j] = pCapInfo->stSupportScenes.stScenes[i].stSpportRules[j].dwSupportedRule;
	}

	for (i = 0; i < nSupportedRulesNum; i++)
	{
		switch(pdwRuleType[i])
		{
			//0PasetRule
		case EVENT_IVS_PASTEDETECTION:
			break;
			//1CrossFence
		case EVENT_IVS_CROSSFENCEDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("CrossFence")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_CROSSFENCEDETECTION);
			break;
			//2CrossLine
		case EVENT_IVS_CROSSLINEDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("CrossLine")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_CROSSLINEDETECTION);
			break;
			//3CrossRegion
		case EVENT_IVS_CROSSREGIONDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("CrossRegion")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_CROSSREGIONDETECTION);
			break;
			//4Move
		case EVENT_IVS_MOVEDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("Move")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_MOVEDETECTION);
			break;
			//5Left
		case EVENT_IVS_LEFTDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("Left")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_LEFTDETECTION);
			break;
			//6Parking
		case EVENT_IVS_PARKINGDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("Parking")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_PARKINGDETECTION);
			break;
			//7Preservation
		case EVENT_IVS_PRESERVATION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("Preservation")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_PRESERVATION);
			break;
			//8Retro
		case EVENT_IVS_RETROGRADEDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("Retrograde")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_RETROGRADEDETECTION);
			break;
			//9Stay
		case EVENT_IVS_STAYDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("Stay")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_STAYDETECTION);
			break;
			//10TakenAway
		case EVENT_IVS_TAKENAWAYDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("TakenAway")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_TAKENAWAYDETECTION);
			break;
			//11VideoAbnormal
		case EVENT_IVS_VIDEOABNORMALDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("VideoAbnormal")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_VIDEOABNORMALDETECTION);
			break;
			//12Wander
		case EVENT_IVS_WANDERDETECTION:
			nChn = m_cmbRuleType.AddString(ConvertString(_T("Wander")));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_WANDERDETECTION);
			break;
		default:
			break;
		}
	}

	if (pdwRuleType)
	{
		delete []pdwRuleType;
		pdwRuleType = NULL;
	}

	showSubRuleDlg(-1, TRUE);

	//////////////////////////////////////////////////////////////////////////
	
	CFG_ANALYSERULES_INFO* pAnalyseRulesInfo = pMainDlg->getAnalyseRulesInfo(nChannel);
	if (!pAnalyseRulesInfo)
	{
		return;
	}

	char* pBuf = pAnalyseRulesInfo->pRuleBuf;
	if (!pBuf)
	{
		return;
	}

	//初始化树控件
	m_treeRuleList.ModifyStyle(TVS_CHECKBOXES, 0, 0);
	m_treeRuleList.ModifyStyle(0, TVS_CHECKBOXES, 0);

	RuleStruct* pRuleStruct = NULL;
	int nReadLen = 0;
	char* pszItem = NULL;
	HTREEITEM hItem = NULL;
	
	CFG_PASTE_INFO* pPaste = NULL;

	CFG_CROSSFENCEDETECTION_INFO* pCrossFence = NULL;
	CFG_CROSSLINE_INFO* pCrossLine = NULL;
	CFG_CROSSREGION_INFO* pCrossRegion = NULL;
	CFG_MOVE_INFO* pMove = NULL;
	CFG_LEFT_INFO* pLeft = NULL;
	CFG_PARKINGDETECTION_INFO* pParking = NULL;
	CFG_PRESERVATION_INFO* pPreservation = NULL;
	CFG_RETROGRADEDETECTION_INFO* pRetro = NULL;
	CFG_STAY_INFO* pStay = NULL;
	CFG_TAKENAWAYDETECTION_INFO* pTakenAway = NULL;
	CFG_VIDEOABNORMALDETECTION_INFO* pVideoAbnormal = NULL;
	CFG_WANDER_INFO* pWander = NULL;

	for (i = 0; i < pAnalyseRulesInfo->nRuleCount; i++)
	{
		CFG_RULE_INFO* pRuleInfo = (CFG_RULE_INFO*)(pBuf + nReadLen);
		
		pRuleStruct = new RuleStruct;
		if (!pRuleStruct)
		{
			break;
		}

		switch(pRuleInfo->dwRuleType)
		{
			//0贴条事件
		case EVENT_IVS_PASTEDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_PASTE_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}

			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_PASTE_INFO));

			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_PASTE_INFO);

			pszItem = ((CFG_PASTE_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			pPaste = (CFG_PASTE_INFO*)pRuleStruct->pRuleBuf;
			if (pPaste->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			break;
			//1翻越围栏
		case EVENT_IVS_CROSSFENCEDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_CROSSFENCEDETECTION_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}

			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_CROSSFENCEDETECTION_INFO));

			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_CROSSFENCEDETECTION_INFO);

			pszItem = ((CFG_CROSSFENCEDETECTION_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			pCrossFence = (CFG_CROSSFENCEDETECTION_INFO*)pRuleStruct->pRuleBuf;
			if (pCrossFence->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			break;
			//2穿越警戒线
		case EVENT_IVS_CROSSLINEDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_CROSSLINE_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}
			
			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_CROSSLINE_INFO));

			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_CROSSLINE_INFO);

			pszItem = ((CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			pCrossLine = (CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf;
			if (pCrossLine->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			break;
			//3区域入侵
		case EVENT_IVS_CROSSREGIONDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_CROSSREGION_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}

			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_CROSSREGION_INFO));

			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_CROSSREGION_INFO);

			pszItem = ((CFG_CROSSREGION_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pCrossRegion = (CFG_CROSSREGION_INFO*)pRuleStruct->pRuleBuf;
			if (pCrossRegion->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
			//4移动检测
		case EVENT_IVS_MOVEDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_MOVE_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}

			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_MOVE_INFO));

			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_MOVE_INFO);

			pszItem = ((CFG_MOVE_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pMove = (CFG_MOVE_INFO*)pRuleStruct->pRuleBuf;
			if (pMove->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
			//5物体遗留
		case EVENT_IVS_LEFTDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_LEFT_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}
			
			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_LEFT_INFO));
			
			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_LEFT_INFO);
			
			pszItem = ((CFG_LEFT_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pLeft = (CFG_LEFT_INFO*)pRuleStruct->pRuleBuf;
			if (pLeft->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
			//6非法停车
		case EVENT_IVS_PARKINGDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_PARKINGDETECTION_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}
			
			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_PARKINGDETECTION_INFO));
			
			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_PARKINGDETECTION_INFO);
			
			pszItem = ((CFG_PARKINGDETECTION_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pParking = (CFG_PARKINGDETECTION_INFO*)pRuleStruct->pRuleBuf;
			if (pParking->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
			//7物品保全
		case EVENT_IVS_PRESERVATION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_PRESERVATION_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}
			
			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_PRESERVATION_INFO));
			
			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_PRESERVATION_INFO);
			
			pszItem = ((CFG_PRESERVATION_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pPreservation = (CFG_PRESERVATION_INFO*)pRuleStruct->pRuleBuf;
			if (pPreservation->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
			//8人员逆行
		case EVENT_IVS_RETROGRADEDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_RETROGRADEDETECTION_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}
			
			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_RETROGRADEDETECTION_INFO));
			
			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_RETROGRADEDETECTION_INFO);
			
			pszItem = ((CFG_RETROGRADEDETECTION_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pRetro = (CFG_RETROGRADEDETECTION_INFO*)pRuleStruct->pRuleBuf;
			if (pRetro->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
			//9滞留事件
		case EVENT_IVS_STAYDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_STAY_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}
			
			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_STAY_INFO));
			
			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_STAY_INFO);
			
			pszItem = ((CFG_STAY_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pStay = (CFG_STAY_INFO*)pRuleStruct->pRuleBuf;
			if (pStay->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
			//10物品搬移
		case EVENT_IVS_TAKENAWAYDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_TAKENAWAYDETECTION_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}
			
			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_TAKENAWAYDETECTION_INFO));
			
			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_TAKENAWAYDETECTION_INFO);
			
			pszItem = ((CFG_TAKENAWAYDETECTION_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pTakenAway = (CFG_TAKENAWAYDETECTION_INFO*)pRuleStruct->pRuleBuf;
			if (pTakenAway->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
			//11视频异常
		case EVENT_IVS_VIDEOABNORMALDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_VIDEOABNORMALDETECTION_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}
			
			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_VIDEOABNORMALDETECTION_INFO));
			
			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_VIDEOABNORMALDETECTION_INFO);
			
			pszItem = ((CFG_VIDEOABNORMALDETECTION_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pVideoAbnormal = (CFG_VIDEOABNORMALDETECTION_INFO*)pRuleStruct->pRuleBuf;
			if (pVideoAbnormal->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
			//12徘徊检测
		case EVENT_IVS_WANDERDETECTION:
			pRuleStruct->pRuleBuf = new char[sizeof(CFG_WANDER_INFO)];
			if (!pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct;
				pRuleStruct = NULL;
				break;
			}
			
			memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
			memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_WANDER_INFO));
			
			nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_WANDER_INFO);
			
			pszItem = ((CFG_WANDER_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
			hItem = m_treeRuleList.InsertItem(pszItem);
			pWander = (CFG_WANDER_INFO*)pRuleStruct->pRuleBuf;
			if (pWander->bRuleEnable)
			{
				m_treeRuleList.SetCheck(hItem);
			}
			m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
			break;
		default:
			if (pRuleStruct)
			{
				delete pRuleStruct;
				pRuleStruct = NULL;
			}
			break;
		}
	}

	GetDlgItem(IDC_CFGRULE_BTN_DELRULE)->EnableWindow(FALSE);
}
/*
 *	
 */
void CConfigRules::uninitConfigRulesDlg()
{
	SetDlgItemText(IDC_CFGRULE_EDT_CHANNELNAME, _T(""));

	//先删除节点上的信息
	RuleStruct* pRuleStruct = NULL;
	HTREEITEM hItem = m_treeRuleList.GetRootItem();

	while(hItem)
	{
		pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
		if (pRuleStruct)
		{
			if (pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct->pRuleBuf;
				pRuleStruct->pRuleBuf = NULL;
			}

			delete pRuleStruct;
			pRuleStruct = NULL;
		}
		hItem = m_treeRuleList.GetNextSiblingItem(hItem);
	}

	//再删除节点
	m_treeRuleList.DeleteAllItems();

	SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, _T(""));
	m_cmbRuleType.ResetContent();

	//subDlgs
	m_ruleCrossFence.clearRuleInfo();
	m_ruleCrossLine.clearRuleInfo();
	m_ruleCrossRegion.clearRuleInfo();
	m_ruleMove.clearRuleInfo();
	m_ruleLeft.clearRuleInfo();
	m_ruleParking.clearRuleInfo();
	m_rulePreserv.clearRuleInfo();
	m_ruleRetro.clearRuleInfo();
	m_ruleStay.clearRuleInfo();
	m_ruleTakeAway.clearRuleInfo();
	m_ruleVideoAbnormal.clearRuleInfo();
	m_ruleWander.clearRuleInfo();

	showSubRuleDlg(-1, TRUE);
}
/*
 *	
 */
void CConfigRules::showSubRuleDlg(int nRuleType, BOOL bEnable)
{
	m_ruleCrossFence.ShowWindow(SW_HIDE);
	m_ruleCrossLine.ShowWindow(SW_HIDE);
	m_ruleCrossRegion.ShowWindow(SW_HIDE);
	m_ruleMove.ShowWindow(SW_HIDE);
	m_ruleLeft.ShowWindow(SW_HIDE);
	m_ruleParking.ShowWindow(SW_HIDE);
	m_rulePreserv.ShowWindow(SW_HIDE);
	m_ruleRetro.ShowWindow(SW_HIDE);
	m_ruleStay.ShowWindow(SW_HIDE);
	m_ruleTakeAway.ShowWindow(SW_HIDE);
	m_ruleVideoAbnormal.ShowWindow(SW_HIDE);
	m_ruleWander.ShowWindow(SW_HIDE);
	
	switch(nRuleType)
	{
		//0贴条事件
	case EVENT_IVS_PASTEDETECTION:
		break;
		//1
	case EVENT_IVS_CROSSFENCEDETECTION:
		m_ruleCrossFence.clearRuleInfo();
		m_ruleCrossFence.initSubDlg();
		m_ruleCrossFence.ShowWindow(SW_SHOW);
		m_ruleCrossFence.EnableWindow(bEnable);
		break;
		//2
	case EVENT_IVS_CROSSLINEDETECTION:
		m_ruleCrossLine.clearRuleInfo();
		m_ruleCrossLine.initSubDlg();
		m_ruleCrossLine.ShowWindow(SW_SHOW);
		m_ruleCrossLine.EnableWindow(bEnable);
		break;
		//3CrossRegion
	case EVENT_IVS_CROSSREGIONDETECTION:
		m_ruleCrossRegion.clearRuleInfo();
		m_ruleCrossRegion.initSubDlg();
		m_ruleCrossRegion.ShowWindow(SW_SHOW);
		m_ruleCrossRegion.EnableWindow(bEnable);
		break;
		//4Move
	case EVENT_IVS_MOVEDETECTION:
		m_ruleMove.clearRuleInfo();
		m_ruleMove.initSubDlg();
		m_ruleMove.ShowWindow(SW_SHOW);
		m_ruleMove.EnableWindow(bEnable);
		break;
		//5Left
	case EVENT_IVS_LEFTDETECTION:
		m_ruleLeft.clearRuleInfo();
		m_ruleLeft.initSubDlg();
		m_ruleLeft.ShowWindow(SW_SHOW);
		m_ruleLeft.EnableWindow(bEnable);
		break;
		//6Parking
	case EVENT_IVS_PARKINGDETECTION:
		m_ruleParking.clearRuleInfo();
		m_ruleParking.initSubDlg();
		m_ruleParking.ShowWindow(SW_SHOW);
		m_ruleParking.EnableWindow(bEnable);
		break;
		//7Preservation
	case EVENT_IVS_PRESERVATION:
		m_rulePreserv.clearRuleInfo();
		m_rulePreserv.initSubDlg();
		m_rulePreserv.ShowWindow(SW_SHOW);
		m_rulePreserv.EnableWindow(bEnable);
		break;
		//8Retro
	case EVENT_IVS_RETROGRADEDETECTION:
		m_ruleRetro.clearRuleInfo();
		m_ruleRetro.initSubDlg();
		m_ruleRetro.ShowWindow(SW_SHOW);
		m_ruleRetro.EnableWindow(bEnable);
		break;
		//9Stay
	case EVENT_IVS_STAYDETECTION:
		m_ruleStay.clearRuleInfo();
		m_ruleStay.initSubDlg();
		m_ruleStay.ShowWindow(SW_SHOW);
		m_ruleStay.EnableWindow(bEnable);
		break;
		//10TakenAway
	case EVENT_IVS_TAKENAWAYDETECTION:
		m_ruleTakeAway.clearRuleInfo();
		m_ruleTakeAway.initSubDlg();
		m_ruleTakeAway.ShowWindow(SW_SHOW);
		m_ruleTakeAway.EnableWindow(bEnable);
		break;
		//11VideoAbnormal
	case EVENT_IVS_VIDEOABNORMALDETECTION:
		m_ruleVideoAbnormal.clearRuleInfo();
		m_ruleVideoAbnormal.initSubDlg();
		m_ruleVideoAbnormal.ShowWindow(SW_SHOW);
		m_ruleVideoAbnormal.EnableWindow(bEnable);
		break;
		//12Wander
	case EVENT_IVS_WANDERDETECTION:
		m_ruleWander.clearRuleInfo();
		m_ruleWander.initSubDlg();
		m_ruleWander.ShowWindow(SW_SHOW);
		m_ruleWander.EnableWindow(bEnable);
		break;
	default:
		break;
	}
}
/*
 *	
 */
void CConfigRules::showSubRuleInfo(int nRuleType, RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || !pRuleStruct->pRuleBuf)
	{
		return;
	}

	CFG_PASTE_INFO* pPaste = NULL;

	CFG_CROSSFENCEDETECTION_INFO* pCrossFence = NULL;
	CFG_CROSSLINE_INFO* pCrossLine = NULL;
	CFG_CROSSREGION_INFO* pCrossRegion = NULL;
	CFG_MOVE_INFO* pMove = NULL;
	CFG_LEFT_INFO* pLeft = NULL;
	CFG_PARKINGDETECTION_INFO* pParking = NULL;
	CFG_PRESERVATION_INFO* pPreservation = NULL;
	CFG_RETROGRADEDETECTION_INFO* pRetro = NULL;
	CFG_STAY_INFO* pStay = NULL;
	CFG_TAKENAWAYDETECTION_INFO* pTakenAway = NULL;
	CFG_VIDEOABNORMALDETECTION_INFO* pVideoAbnormal = NULL;
	CFG_WANDER_INFO* pWander = NULL;

	switch(nRuleType)
	{
		//0贴条事件
	case EVENT_IVS_PASTEDETECTION:
		break;
		//1
	case EVENT_IVS_CROSSFENCEDETECTION:
		pCrossFence = (CFG_CROSSFENCEDETECTION_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pCrossFence->szRuleName);
		m_ruleCrossFence.showRuleInfo(pRuleStruct);
		break;
		//2
	case EVENT_IVS_CROSSLINEDETECTION:
		pCrossLine = (CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pCrossLine->szRuleName);
		m_ruleCrossLine.showRuleInfo(pRuleStruct);
		break;
		//3CrossRegion
	case EVENT_IVS_CROSSREGIONDETECTION:
		pCrossRegion = (CFG_CROSSREGION_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pCrossRegion->szRuleName);
		m_ruleCrossRegion.showRuleInfo(pRuleStruct);
		break;
		//4Move
	case EVENT_IVS_MOVEDETECTION:
		pMove = (CFG_MOVE_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pMove->szRuleName);
		m_ruleMove.showRuleInfo(pRuleStruct);
		break;
		//5Left
	case EVENT_IVS_LEFTDETECTION:
		pLeft = (CFG_LEFT_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pLeft->szRuleName);
		m_ruleLeft.showRuleInfo(pRuleStruct);
		break;
		//6Parking
	case EVENT_IVS_PARKINGDETECTION:
		pParking = (CFG_PARKINGDETECTION_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pParking->szRuleName);
		m_ruleParking.showRuleInfo(pRuleStruct);
		break;
		//7Preservation
	case EVENT_IVS_PRESERVATION:
		pPreservation = (CFG_PRESERVATION_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pPreservation->szRuleName);
		m_rulePreserv.showRuleInfo(pRuleStruct);
		break;
		//8Retro
	case EVENT_IVS_RETROGRADEDETECTION:
		pRetro = (CFG_RETROGRADEDETECTION_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pRetro->szRuleName);
		m_ruleRetro.showRuleInfo(pRuleStruct);
		break;
		//9Stay
	case EVENT_IVS_STAYDETECTION:
		pStay = (CFG_STAY_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pRuleStruct->pRuleBuf);
		m_ruleStay.showRuleInfo(pRuleStruct);
		break;
		//10TakenAway
	case EVENT_IVS_TAKENAWAYDETECTION:
		pTakenAway = (CFG_TAKENAWAYDETECTION_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pTakenAway->szRuleName);
		m_ruleTakeAway.showRuleInfo(pRuleStruct);
		break;
		//11VideoAbnormal
	case EVENT_IVS_VIDEOABNORMALDETECTION:
		pVideoAbnormal = (CFG_VIDEOABNORMALDETECTION_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pVideoAbnormal->szRuleName);
		m_ruleVideoAbnormal.showRuleInfo(pRuleStruct);
		break;
		//12Wander
	case EVENT_IVS_WANDERDETECTION:
		pWander = (CFG_WANDER_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pWander->szRuleName);
		m_ruleWander.showRuleInfo(pRuleStruct);
		break;
	default:
		break;
	}
}

void CConfigRules::showPreview(LONG lLoginHanlde, int nChannel)
{
	if (!lLoginHanlde || nChannel < 0)
	{
		return;
	}
	
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		if (pMainDlg->getLoginHandle())
		{
			if (pMainDlg->getRealPlayHandle())
			{
				::CLIENT_StopRealPlay(pMainDlg->getRealPlayHandle());
				//////////////////////////////////////////////////////////////////////////
				//
				s_PlayAPI.PLAY_Stop(g_nPlayPort);
				s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				
				//////////////////////////////////////////////////////////////////////////
				pMainDlg->setRealPlayHandel(0);
			}
			
			//////////////////////////////////////////////////////////////////////////
			
			int nPort = 450;
			LLONG m_lPlayID = 0;
			HWND hWnd = m_pIvsRulePreview->GetSafeHwnd();
			NET_DEVICEINFO* pDevInfo = pMainDlg->getDevInfo();
			int nChnCount = 0;
			if (pDevInfo)
			{
				nChnCount = pDevInfo->byChanNum;
			}
			
			//Enable stream
			BOOL bOpenRet = s_PlayAPI.PLAY_OpenStream(g_nPlayPort, 0, 0, 1024 * 900);
			if(bOpenRet)
			{	
				// 从码流中提取智能分析信息
				BOOL bRet = FALSE;
				
				bRet = s_PlayAPI.PLAY_RigisterDrawFun(m_nPlayPortNum, CIvsRulePreview::drawIvsRuleCfgProc, (DWORD)m_pIvsRulePreview);
				if (!bRet)
				{
					MessageBox(ConvertString("PLAY_RigisterDrawFun failed!"), ConvertString("Prompt"));
				}
				//Begin play 
				BOOL bPlayRet = s_PlayAPI.PLAY_Play(g_nPlayPort, hWnd);
				if(bPlayRet)
				{
					//Real-time play 
					m_lPlayID = CLIENT_RealPlay(pMainDlg->getLoginHandle(), nChannel, 0);
					if(0 != m_lPlayID)
					{
						pMainDlg->setRealPlayHandel(m_lPlayID);
						CLIENT_SetRealDataCallBackEx(m_lPlayID, RealDataCallBackEx, (DWORD)this, 0x1f);
					}
					else
					{
						s_PlayAPI.PLAY_Stop(g_nPlayPort);
						s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
						MessageBox(ConvertString("Fail to play!"), ConvertString("Prompt"));
					}
				}
				else
				{
					s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				}
			}
		}
	}
}

void CConfigRules::closePreview(LONG lRealPlayHandle)
{
	if (!lRealPlayHandle)
	{
		return;
	}
	
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		if (pMainDlg->getRealPlayHandle())
		{
			::CLIENT_StopRealPlay(pMainDlg->getRealPlayHandle());
			//////////////////////////////////////////////////////////////////////////
			//
			s_PlayAPI.PLAY_Stop(g_nPlayPort);
			s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			
			//////////////////////////////////////////////////////////////////////////
			GetDlgItem(IDC_CFGRULE_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->setRealPlayHandel(0);
		}
	}
}


void CConfigRules::setRuleTime(DWORD dwType, RuleStruct* pRuleStruct)
{
	if (!dwType || !pRuleStruct)
	{
		return;
	}
	
	switch(dwType)
	{
		//1CrossFence
	case EVENT_IVS_CROSSFENCEDETECTION:
		setRuleEnableTime<CFG_CROSSFENCEDETECTION_INFO>((CFG_CROSSFENCEDETECTION_INFO*)pRuleStruct->pRuleBuf);
		break;
		//2CrossLine
	case EVENT_IVS_CROSSLINEDETECTION:
		setRuleEnableTime<CFG_CROSSLINE_INFO>((CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf);
		break;
		//3CrossRegion
	case EVENT_IVS_CROSSREGIONDETECTION:
		setRuleEnableTime<CFG_CROSSREGION_INFO>((CFG_CROSSREGION_INFO*)pRuleStruct->pRuleBuf);
		break;
		//4Move
	case EVENT_IVS_MOVEDETECTION:
		setRuleEnableTime<CFG_MOVE_INFO>((CFG_MOVE_INFO*)pRuleStruct->pRuleBuf);
		break;
		//5Left
	case EVENT_IVS_LEFTDETECTION:
		setRuleEnableTime<CFG_LEFT_INFO>((CFG_LEFT_INFO*)pRuleStruct->pRuleBuf);
		break;
		//6Parking
	case EVENT_IVS_PARKINGDETECTION:
		setRuleEnableTime<CFG_PARKINGDETECTION_INFO>((CFG_PARKINGDETECTION_INFO*)pRuleStruct->pRuleBuf);
		break;
		//7Preservation
	case EVENT_IVS_PRESERVATION:
		setRuleEnableTime<CFG_PRESERVATION_INFO>((CFG_PRESERVATION_INFO*)pRuleStruct->pRuleBuf);
		break;
		//8Retro
	case EVENT_IVS_RETROGRADEDETECTION:
		setRuleEnableTime<CFG_RETROGRADEDETECTION_INFO>((CFG_RETROGRADEDETECTION_INFO*)pRuleStruct->pRuleBuf);
		break;
		//9Stay
	case EVENT_IVS_STAYDETECTION:
		setRuleEnableTime<CFG_STAY_INFO>((CFG_STAY_INFO*)pRuleStruct->pRuleBuf);
		break;
		//10TakenAway
	case EVENT_IVS_TAKENAWAYDETECTION:
		setRuleEnableTime<CFG_TAKENAWAYDETECTION_INFO>((CFG_TAKENAWAYDETECTION_INFO*)pRuleStruct->pRuleBuf);
		break;
		//11VideoAbnormal
	case EVENT_IVS_VIDEOABNORMALDETECTION:
		setRuleEnableTime<CFG_VIDEOABNORMALDETECTION_INFO>((CFG_VIDEOABNORMALDETECTION_INFO*)pRuleStruct->pRuleBuf);
		break;
		//12Wander
	case EVENT_IVS_WANDERDETECTION:
		setRuleEnableTime<CFG_WANDER_INFO>((CFG_WANDER_INFO*)pRuleStruct->pRuleBuf);
		break;
	default:
		break;
	}
}

void CConfigRules::DrawIvsInfoRulesProc(long nPort,HDC hdc,LONG nUser)
{
	CConfigRules* pRulesInfo = (CConfigRules*)nUser;
	
	int nErr = 0;

	HWND hWnd = pRulesInfo->GetDlgItem(IDC_CFGRULE_STATIC_PREVIEW)->GetSafeHwnd();

	nErr = DRAW_Draw(g_nRuleCfgDrawPort, hdc, hWnd, 0);
	if(nErr < 0)
	{
		return;
	}
}

// void CConfigRules::setRuleInfo(int nRuleType, char* pRuleStructBuf, int nLen)
// {
// }
/*
 *	
 */
BOOL CConfigRules::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	int nErr = DRAW_Open(g_nRuleCfgDrawPort);

	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	CRect rt;
	GetClientRect(&rt);
	rt.left = 526 / 2 * 3;
	rt.top = 64 / 2 * 3;
	rt.right = rt.left + 106 / 2 * 3;
	rt.bottom = rt.top + 288 / 2 * 3;

	m_ruleCrossFence.Create(CRuleCrossFence::IDD, this);
	m_ruleCrossFence.MoveWindow(&rt, TRUE);
	m_ruleCrossFence.ShowWindow(SW_HIDE);

	m_ruleCrossLine.Create(CRuleCrossLine::IDD, this);
	m_ruleCrossLine.MoveWindow(&rt, TRUE);

	m_ruleCrossRegion.Create(CRuleCrossRegion::IDD, this);
	m_ruleCrossRegion.MoveWindow(&rt, TRUE);
	m_ruleCrossRegion.ShowWindow(SW_HIDE);

	m_ruleMove.Create(CRuleMove::IDD, this);
	m_ruleMove.MoveWindow(&rt, TRUE);
	m_ruleMove.ShowWindow(SW_HIDE);

	m_ruleLeft.Create(CRuleLeft::IDD, this);
	m_ruleLeft.MoveWindow(&rt, TRUE);
	m_ruleLeft.ShowWindow(SW_HIDE);

	m_ruleParking.Create(CRuleParking::IDD, this);
	m_ruleParking.MoveWindow(&rt, TRUE);
	m_ruleParking.ShowWindow(SW_HIDE);

	m_rulePreserv.Create(CRulePreservation::IDD, this);
	m_rulePreserv.MoveWindow(&rt, TRUE);
	m_rulePreserv.ShowWindow(SW_HIDE);

	m_ruleRetro.Create(CRuleRetrogradation::IDD, this);
	m_ruleRetro.MoveWindow(&rt, TRUE);
	m_ruleRetro.ShowWindow(SW_HIDE);

	m_ruleStay.Create(CRuleStay::IDD, this);
	m_ruleStay.MoveWindow(&rt, TRUE);
	m_ruleStay.ShowWindow(SW_HIDE);

	m_ruleTakeAway.Create(CRuleTakenAway::IDD, this);
	m_ruleTakeAway.MoveWindow(&rt, TRUE);
	m_ruleTakeAway.ShowWindow(SW_HIDE);

	m_ruleVideoAbnormal.Create(CRuleVideoAbnormal::IDD, this);
	m_ruleVideoAbnormal.MoveWindow(&rt, TRUE);
	m_ruleVideoAbnormal.ShowWindow(SW_HIDE);

	m_ruleWander.Create(CRuleWander::IDD, this);
	m_ruleWander.MoveWindow(&rt, TRUE);
	m_ruleWander.ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CFGRULE_STATIC_PREVIEW)->GetWindowRect(&rt);
	ScreenToClient(&rt);

	m_pIvsRulePreview = new CIvsRulePreview;
	if (m_pIvsRulePreview)
	{
		m_pIvsRulePreview->Create(NULL,
								  NULL,
								  WS_CHILD,
								  CRect(0, 0, 0, 0),
								  this,
								  5002);
		m_pIvsRulePreview->MoveWindow(&rt);
		m_pIvsRulePreview->ShowWindow(SW_SHOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
 *	选择组合框下拉菜单，显示对应规则子窗口；
 *	如果当前选择的规则节点的绑定指针标示的类型
 *  和当前选择的类型不一致，则释放原指针的内存，
 *  new新类型对应的内存，表示规则信息更改。
 */
void CConfigRules::OnSelchangeCfgruleCmbRuletype() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
	if (!hItem)
	{
		return;
	}

	RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);

	int nChn = m_cmbRuleType.GetCurSel();
	DWORD dwRuleType = m_cmbRuleType.GetItemData(nChn);

	if (pRuleStruct->RuleInfo.dwRuleType)
	{
		//表示已有的节点
		if (dwRuleType == pRuleStruct->RuleInfo.dwRuleType)
		{
			//表示不修改该节点,直接显示信息即可
			showSubRuleDlg(dwRuleType, TRUE);
			showSubRuleInfo(dwRuleType, pRuleStruct);
			return;
		} 
		else
		{
			//表示要修改该节点的类型,重置该规则所有信息
			if (pRuleStruct->pRuleBuf)
			{
				delete []pRuleStruct->pRuleBuf;
				pRuleStruct->pRuleBuf = NULL;
			}

			int iSize = g_getStructSize(dwRuleType);
			pRuleStruct->pRuleBuf = new char[iSize];
			if (!pRuleStruct->pRuleBuf)
			{
				return;
			}
			ZeroMemory(pRuleStruct->pRuleBuf, iSize);

			pRuleStruct->RuleInfo.dwRuleType = dwRuleType;
			pRuleStruct->RuleInfo.nRuleSize = iSize;

			showSubRuleDlg(dwRuleType, FALSE);
			showSubRuleInfo(dwRuleType, pRuleStruct);

			setRuleTime(dwRuleType, pRuleStruct);

			//清空绘图
			DRAW_Reset(g_nRuleCfgDrawPort, DRAW_RULE);

			if (dwRuleType != EVENT_IVS_VIDEOABNORMALDETECTION)
			{
				//开始重新绘图
				m_pIvsRulePreview->setRuleData(pRuleStruct, FALSE);

				m_pIvsRulePreview->beginDraw(hItem);
			}
		}
	}
	else
	{
		//表示新增的节点
		int iSize = g_getStructSize(dwRuleType);
		pRuleStruct->pRuleBuf = new char[iSize];
		if (!pRuleStruct->pRuleBuf)
		{
			return;
		}
		ZeroMemory(pRuleStruct->pRuleBuf, iSize);
		
		//各个规则的第一个成员都一样，所以随便转换个类型，
		//填入临时的规则名称
		CString strRuleName;
		GetDlgItemText(IDC_CFGRULE_EDT_RULENAME, strRuleName);
		
		//修改规则名称，不能重复
		CFG_CROSSLINE_INFO* pCrossLine = (CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf;
		strncpy(pCrossLine->szRuleName, 
				strRuleName.GetBuffer(0), 
				strRuleName.GetLength());
		m_treeRuleList.SetItemText(hItem, pCrossLine->szRuleName);

		GetDlgItem(IDC_CFGRULE_EDT_RULENAME)->EnableWindow(TRUE);
		
		pRuleStruct->RuleInfo.dwRuleType = dwRuleType;
		pRuleStruct->RuleInfo.nRuleSize = iSize;
		
		showSubRuleDlg(dwRuleType, FALSE);
		showSubRuleInfo(dwRuleType, pRuleStruct);
		
		setRuleTime(dwRuleType, pRuleStruct);

		//清空绘图
		DRAW_Reset(g_nRuleCfgDrawPort, DRAW_RULE);
		
		if (dwRuleType != EVENT_IVS_VIDEOABNORMALDETECTION)
		{
			//开始重新绘图，其中视频异常规则无需绘图
			m_pIvsRulePreview->setRuleData(pRuleStruct, FALSE);

			m_pIvsRulePreview->beginDraw(hItem);
		}
		else
		{
			GetDlgItem(IDC_CFGRULE_BTN_ADDRULE)->EnableWindow(TRUE);
			GetDlgItem(IDC_CFGRULE_BTN_DELRULE)->EnableWindow(TRUE);
			m_bAddRule = FALSE;
			showSubRuleDlg(dwRuleType, TRUE);
			showSubRuleInfo(dwRuleType, pRuleStruct);
		}
	}

	m_treeRuleList.EnableWindow(TRUE);
}
/*
 *	添加规则
 */
void CConfigRules::OnCfgruleBtnAddrule() 
{
	// TODO: Add your control notification handler code here
	if (m_pIvsRulePreview->m_bAddRegion)
	{
		AfxMessageBox(ConvertString(_T("Please draw the line of rule first or click right button to stop drawing")));
		return;
	}

	//先判断当前规则总数是否满
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

	if (pCap->nMaxRules <= m_treeRuleList.GetCount())
	{
		AfxMessageBox(ConvertString(_T("Can't add rule any more!")));
		return;
	}

	//新增节点
	//先使新规则的信息清空，由用户后续输入修改
	m_treeRuleList.SelectItem(NULL);

	HTREEITEM hNewRuleItem = m_treeRuleList.InsertItem(ConvertString(_T("NewRule")));
	SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, ConvertString(_T("NewRule")));
	m_treeRuleList.SelectItem(hNewRuleItem);

	showSubRuleDlg(-1, TRUE);

	RuleStruct* pRuleStruct = new RuleStruct;
	if (!pRuleStruct)
	{
		return;
	}
	m_treeRuleList.SetItemData(hNewRuleItem, (DWORD)pRuleStruct);

	GetDlgItem(IDC_CFGRULE_EDT_RULENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CFGRULE_BTN_ADDRULE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CFGRULE_BTN_DELRULE)->EnableWindow(FALSE);
	m_treeRuleList.EnableWindow(FALSE);
	m_cmbRuleType.SetCurSel(-1);
	
	//清空绘图
	DRAW_Reset(g_nRuleCfgDrawPort, DRAW_RULE);

	m_bAddRule = TRUE;
}
/*
 *	删除选中的规则
 */
void CConfigRules::OnCfgruleBtnDelrule() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
	if (!hItem)
	{
		return;
	}

	RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
	if (!pRuleStruct)
	{
		return;
	}

	delete pRuleStruct->pRuleBuf;
	pRuleStruct->pRuleBuf = NULL;

	m_treeRuleList.DeleteItem(hItem);

	m_treeRuleList.SelectItem(NULL);
	GetDlgItem(IDC_CFGRULE_BTN_DELRULE)->EnableWindow(FALSE);
	SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, _T(""));
	m_cmbRuleType.SetCurSel(-1);

	DRAW_Reset(g_nRuleCfgDrawPort, DRAW_RULE);

	showSubRuleDlg(-1, TRUE);
}
/*
 *	擦除画面上的规则线条，重新绘图
 */
void CConfigRules::OnCfgruleBtnRedraw() 
{
	// TODO: Add your control notification handler code here
	if (m_pIvsRulePreview->m_bAddRegion
		|| m_bAddRule)
	{
		if (m_cmbRuleType.GetCurSel() == -1)
		{
			AfxMessageBox(ConvertString(_T("Please select the rule type first")));
		} 
		else
		{
			AfxMessageBox(ConvertString(_T("Please draw the line of rule first or click right button to stop drawing")));
		}
		return;
	}

	HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
	if (!hItem)
	{
		return;
	}

	RuleStruct* pRule = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
	if (!pRule)
	{
		return;
	}
	if (!pRule->pRuleBuf)
	{
		return;
	}

	m_pIvsRulePreview->setRuleData(pRule, TRUE);
	m_pIvsRulePreview->beginDraw(hItem);
}
/*
 *	获取规则信息并更新界面显示
 */
void CConfigRules::OnCfgruleBtnGet() 
{
	// TODO: Add your control notification handler code here
	if (m_pIvsRulePreview->m_bAddRegion
		|| m_bAddRule)
	{
		if (m_cmbRuleType.GetCurSel() == -1)
		{
			AfxMessageBox(ConvertString(_T("Please select the rule type first")));
		} 
		else
		{
			AfxMessageBox(ConvertString(_T("Please draw the line of rule first or click right button to stop drawing")));
		}
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	CFG_CAP_ANALYSE_INFO* pCap = (CFG_CAP_ANALYSE_INFO*)pMainDlg->getCapAnalyseInfo(pMainDlg->getCurrentChannel());
	if (!pMainDlg || !pCap)
	{
		return;
	}

	uninitConfigRulesDlg();

	//////////////////////////////////////////////////////////////////////////
	CFG_ANALYSERULES_INFO* pAnalyseRule = pMainDlg->getAnalyseRulesInfo(pMainDlg->getCurrentChannel());
	if (pAnalyseRule)
	{
		if (pAnalyseRule->pRuleBuf)
		{
			delete []pAnalyseRule->pRuleBuf;
			pAnalyseRule->pRuleBuf = NULL;
		}
	}
	else
	{
		pAnalyseRule = new CFG_ANALYSERULES_INFO;
		if (!pAnalyseRule)
		{
			return;
		}
	}
	
	ZeroMemory(pAnalyseRule, sizeof(CFG_ANALYSERULES_INFO));
	
	int nMaxRuleLen = pMainDlg->getMaxStuSize(pCap->stSupportScenes.stScenes[0].stSpportRules,
											  pCap->stSupportScenes.stScenes[0].nSupportRules);
	int nBufLen = (nMaxRuleLen + sizeof(CFG_RULE_INFO)) * pCap->stSupportScenes.stScenes[0].nSupportRules;
	
	pAnalyseRule->pRuleBuf = new char[nBufLen];
	if (!pAnalyseRule->pRuleBuf)
	{
		return;
	}
	pAnalyseRule->nRuleLen = nBufLen;
	
	pMainDlg->getRule(pMainDlg->getCurrentChannel(), pAnalyseRule);

	initConfigRulesDlg(pMainDlg->getCurrentChannel());

	DRAW_Reset(g_nRuleCfgDrawPort, DRAW_RULE);
}
/*
 *	将当前界面中包含的信息配置到设备上
 */
void CConfigRules::OnCfgruleBtnSet() 
{
	// TODO: Add your control notification handler code here
	if (m_pIvsRulePreview->m_bAddRegion
		|| m_bAddRule)
	{
		if (m_cmbRuleType.GetCurSel() == -1)
		{
			AfxMessageBox(ConvertString(_T("Please select the rule type first")));
		} 
		else
		{
			AfxMessageBox(ConvertString(_T("Please draw the line of rule first or click right button to stop drawing")));
		}
		return;
	}

	//当前规则数
	int iRuleCnt = m_treeRuleList.GetCount();

	//获得当前所有规则需要的内存大小
	int nTotleLen = 0;

	HTREEITEM hItem = m_treeRuleList.GetRootItem();
	while(hItem)
	{
		RuleStruct* pRuleStruct 
			= (RuleStruct*)m_treeRuleList.GetItemData(hItem);

		if (pRuleStruct)
		{
			nTotleLen += sizeof(CFG_RULE_INFO) 
						 + pRuleStruct->RuleInfo.nRuleSize;
		}

		hItem = m_treeRuleList.GetNextSiblingItem(hItem);
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	int iCurChn = pMainDlg->getCurrentChannel();
	CFG_ANALYSERULES_INFO* pRuleInfo = pMainDlg->getAnalyseRulesInfo(iCurChn);
	if (pRuleInfo)
	{
		pRuleInfo->nRuleCount = 0;
		pRuleInfo->nRuleLen = 0;
		
		if (pRuleInfo->pRuleBuf)
		{
			delete []pRuleInfo->pRuleBuf;
			pRuleInfo->pRuleBuf = new char[nTotleLen];
			if (!pRuleInfo->pRuleBuf)
			{
				return;
			}
		}
	}
	else
	{
		return;
	}


	ZeroMemory(pRuleInfo->pRuleBuf, nTotleLen);

	//将规则列表的信息填入
	hItem = m_treeRuleList.GetRootItem();
	int iTmp = 0;
	char* pTmp = pRuleInfo->pRuleBuf;

	while(hItem)
	{
		RuleStruct* pRuleStruct
			= (RuleStruct*)m_treeRuleList.GetItemData(hItem);
		if (pRuleStruct)
		{
			CFG_CROSSLINE_INFO* pCrossLine = (CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf;
			if (pCrossLine)
			{
				if (m_treeRuleList.GetCheck(hItem))
				{
					pCrossLine->bRuleEnable = true;
				} 
				else
				{
					pCrossLine->bRuleEnable = false;
				}
			}

			memcpy(pTmp + iTmp,
				   &pRuleStruct->RuleInfo,
				   sizeof(CFG_RULE_INFO));
			iTmp += sizeof(CFG_RULE_INFO);

			memcpy(pTmp + iTmp, 
				   pRuleStruct->pRuleBuf, 
				   pRuleStruct->RuleInfo.nRuleSize);
			iTmp += pRuleStruct->RuleInfo.nRuleSize;

			pRuleInfo->nRuleCount++;
		}
		
		hItem = m_treeRuleList.GetNextSiblingItem(hItem);
	}

	pRuleInfo->nRuleLen = iTmp;

	//////////////////////////////////////////////////////////////////////////

	char szOutBuf[32 * 1024] = {0};

	BOOL bRet 
		= ::CLIENT_PacketData(CFG_CMD_ANALYSERULE,
							  pRuleInfo,
							  sizeof(CFG_ANALYSERULES_INFO),
							  szOutBuf,
							  32 *1024);
	if (!bRet)
	{
		//Packet Data error
		return;
	}

	int iErr = 0;
	int iRestart = 0;

	bRet = ::CLIENT_SetNewDevConfig(pMainDlg->getLoginHandle(),
									CFG_CMD_ANALYSERULE,
									pMainDlg->getCurrentChannel(),
									szOutBuf,
									32 * 1024,
									&iErr,
									&iRestart);
	if (bRet)
	{
		AfxMessageBox(ConvertString(_T("Set RuleInfo Successfully")));
	}
	else
	{
		AfxMessageBox(ConvertString(_T("Set RuleInfo Failed")));
	}
}
/*
 *	选择树控件节点，显示对应子窗口和规则信息
 */
void CConfigRules::OnDblclkCfgruleTreeRulelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_pIvsRulePreview->m_bAddRegion
		|| m_bAddRule)
	{
		AfxMessageBox(ConvertString(_T("Please draw the line of rule first or click right button to stop drawing")));
		return;
	}

	*pResult = 0;
}

void CConfigRules::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	DRAW_Close(g_nRuleCfgDrawPort);

	if (m_pIvsRulePreview)
	{
		if (m_pIvsRulePreview->GetSafeHwnd())
		{
			m_pIvsRulePreview->DestroyWindow();
		}

		delete m_pIvsRulePreview;
		m_pIvsRulePreview = NULL;
	}
}
/*
 *	
 */
void CConfigRules::OnClickCfgruleTreeRulelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_pIvsRulePreview->m_bAddRegion
		|| m_bAddRule)
	{
		AfxMessageBox(ConvertString(_T("Please draw the line of rule first or click right button to stop drawing")));
		return;
	}

	CPoint pt;
	GetCursorPos(&pt);
	m_treeRuleList.ScreenToClient(&pt);

	UINT uiFlag = -1;
	HTREEITEM hItem = m_treeRuleList.HitTest(pt, &uiFlag);
	if (!hItem)
	{
// 		*pResult = 0;
// 		m_treeRuleList.SelectItem(NULL);
// 		return;
		hItem = m_treeRuleList.GetRootItem();
		if (!hItem)
		{
			return;
		}
	}

	GetDlgItem(IDC_CFGRULE_BTN_DELRULE)->EnableWindow(TRUE);

	m_treeRuleList.SelectItem(hItem);
	bool bRet = false;

	if (uiFlag == TVHT_ONITEMSTATEICON)
	{
		if (m_treeRuleList.GetCheck(hItem))
		{
			//turn to false
			bRet = false;
		} 
		else
		{
			//turn to true
			bRet = true;
		}
	}
	else
	{
		if (m_treeRuleList.GetCheck(hItem))
		{
			bRet = true;
		} 
		else
		{
			bRet = false;
		}
	}

	RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
	if (!pRuleStruct)
	{
		return;
	}
	
	CFG_CROSSFENCEDETECTION_INFO* pCrossFence = NULL;
	CFG_CROSSLINE_INFO* pCrossLine = NULL;
	CFG_CROSSREGION_INFO* pCrossRegion = NULL;
	CFG_MOVE_INFO* pMove = NULL;
	CFG_LEFT_INFO* pLeft = NULL;
	CFG_PARKINGDETECTION_INFO* pParking = NULL;
	CFG_PRESERVATION_INFO* pPreservation = NULL;
	CFG_RETROGRADEDETECTION_INFO* pRetro = NULL;
	CFG_STAY_INFO* pStay = NULL;
	CFG_TAKENAWAYDETECTION_INFO* pTakenAway = NULL;
	CFG_VIDEOABNORMALDETECTION_INFO* pVideoAbnormal = NULL;
	CFG_WANDER_INFO* pWander = NULL;

	switch(pRuleStruct->RuleInfo.dwRuleType)
	{
			//1
	case EVENT_IVS_CROSSFENCEDETECTION:
		pCrossFence = (CFG_CROSSFENCEDETECTION_INFO*)pRuleStruct->pRuleBuf;
		pCrossFence->bRuleEnable = bRet;
		break;
		//2CrossLine
	case EVENT_IVS_CROSSLINEDETECTION:
		pCrossLine = (CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf;
		pCrossLine->bRuleEnable = bRet;
		break;
		//3CrossRegion
	case EVENT_IVS_CROSSREGIONDETECTION:
		pCrossRegion = (CFG_CROSSREGION_INFO*)pRuleStruct->pRuleBuf;
		pCrossRegion->bRuleEnable = bRet;
		break;
		//4Move
	case EVENT_IVS_MOVEDETECTION:
		pMove = (CFG_MOVE_INFO*)pRuleStruct->pRuleBuf;
		pMove->bRuleEnable = bRet;
		break;
		//5Left
	case EVENT_IVS_LEFTDETECTION:
		pLeft = (CFG_LEFT_INFO*)pRuleStruct->pRuleBuf;
		pLeft->bRuleEnable = bRet;
		break;
		//6Parking
	case EVENT_IVS_PARKINGDETECTION:
		pParking = (CFG_PARKINGDETECTION_INFO*)pRuleStruct->pRuleBuf;
		pParking->bRuleEnable = bRet;
		break;
		//7Preservation
	case EVENT_IVS_PRESERVATION:
		pPreservation = (CFG_PRESERVATION_INFO*)pRuleStruct->pRuleBuf;
		pPreservation->bRuleEnable = bRet;
		break;
		//8Retro
	case EVENT_IVS_RETROGRADEDETECTION:
		pRetro = (CFG_RETROGRADEDETECTION_INFO*)pRuleStruct->pRuleBuf;
		pRetro->bRuleEnable = bRet;
		break;
		//9Stay
	case EVENT_IVS_STAYDETECTION:
		pStay = (CFG_STAY_INFO*)pRuleStruct->pRuleBuf;
		pStay->bRuleEnable = bRet;
		break;
		//10TakenAway
	case EVENT_IVS_TAKENAWAYDETECTION:
		pTakenAway = (CFG_TAKENAWAYDETECTION_INFO*)pRuleStruct->pRuleBuf;
		pTakenAway->bRuleEnable = bRet;
		break;
		//11VideoAbnormal
	case EVENT_IVS_VIDEOABNORMALDETECTION:
		pVideoAbnormal = (CFG_VIDEOABNORMALDETECTION_INFO*)pRuleStruct->pRuleBuf;
		pVideoAbnormal->bRuleEnable = bRet;
		break;
		//12Wander
	case EVENT_IVS_WANDERDETECTION:
		pWander = (CFG_WANDER_INFO*)pRuleStruct->pRuleBuf;
		pWander->bRuleEnable = bRet;
		break;
	default:
		AfxMessageBox(ConvertString(_T("No such rule type!")));
		break;
	}
	m_treeRuleList.SelectItem(NULL);
	
	for (int i = 0; i < m_cmbRuleType.GetCount(); i++)
	{
		if (pRuleStruct->RuleInfo.dwRuleType == m_cmbRuleType.GetItemData(i))
		{
			m_cmbRuleType.SetCurSel(i);
			bRet = TRUE;
			break;
		}
	}
	
	if (bRet)
	{
		int nErr = 0;
		nErr = DRAW_SetPen(g_nRuleCfgDrawPort, DRAW_RULE, DRAW_PEN_SOLID, 1, RGB(0, 255, 0));
		if (0 != nErr)
		{
			return;
		}
		
		CFG_ANALYSERULES_INFO stuRuleInfo = {0};
		stuRuleInfo.pRuleBuf = new char[pRuleStruct->RuleInfo.nRuleSize + sizeof(CFG_RULE_INFO)];
		if (!stuRuleInfo.pRuleBuf)
		{
			return;
		}
		memcpy(stuRuleInfo.pRuleBuf, &pRuleStruct->RuleInfo, sizeof(CFG_RULE_INFO));
		memcpy(stuRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO), pRuleStruct->pRuleBuf, pRuleStruct->RuleInfo.nRuleSize);
		stuRuleInfo.nRuleCount = 1;
		stuRuleInfo.nRuleLen = pRuleStruct->RuleInfo.nRuleSize + sizeof(CFG_RULE_INFO);

		//为了能画图，让规则使能
		char* pTmp = stuRuleInfo.pRuleBuf;
		pTmp += sizeof(CFG_RULE_INFO);
		CFG_CROSSLINE_INFO* pRuleInfo = (CFG_CROSSLINE_INFO*)pTmp;
		if (!pRuleInfo->bRuleEnable)
		{
			pRuleInfo->bRuleEnable = true;
		}
		
		nErr = DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&stuRuleInfo, 0);
		if (nErr < 0)
		{
			return;
		}
		
		delete []stuRuleInfo.pRuleBuf;
		stuRuleInfo.pRuleBuf = NULL;
		
		showSubRuleDlg(pRuleStruct->RuleInfo.dwRuleType, TRUE);
		
		//ToDo显示对应规则信息
		showSubRuleInfo(pRuleStruct->RuleInfo.dwRuleType, pRuleStruct);
	}
	else
	{
		//该节点还没有增加规则信息
		m_cmbRuleType.SetCurSel(-1);
		showSubRuleDlg(-1, TRUE);
	}
	
//	*pResult = 0;
}
/*
 *	更改规则名称
 */
void CConfigRules::OnChangeCfgruleEdtRulename() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
	if (hItem)
	{
		char szName[MAX_NAME_LEN] = {0};
		GetDlgItemText(IDC_CFGRULE_EDT_RULENAME, szName, MAX_NAME_LEN);
		m_treeRuleList.SetItemText(hItem, szName);

		RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
		if (!pRuleStruct)
		{
			return;
		}

		if (!pRuleStruct->pRuleBuf)
		{
			AfxMessageBox(ConvertString(_T("Select RuleType First!")));
			return;
		}
		
		CFG_CROSSFENCEDETECTION_INFO* pCrossFence = NULL;
		CFG_CROSSLINE_INFO* pCrossLine = NULL;
		CFG_CROSSREGION_INFO* pCrossRegion = NULL;
		CFG_MOVE_INFO* pMove = NULL;
		CFG_LEFT_INFO* pLeft = NULL;
		CFG_PARKINGDETECTION_INFO* pParking = NULL;
		CFG_PRESERVATION_INFO* pPreservation = NULL;
		CFG_RETROGRADEDETECTION_INFO* pRetro = NULL;
		CFG_STAY_INFO* pStay = NULL;
		CFG_TAKENAWAYDETECTION_INFO* pTakenAway = NULL;
		CFG_VIDEOABNORMALDETECTION_INFO* pVideoAbnormal = NULL;
		CFG_WANDER_INFO* pWander = NULL;

		switch (pRuleStruct->RuleInfo.dwRuleType)
		{
			//1
		case EVENT_IVS_CROSSFENCEDETECTION:
			pCrossFence = (CFG_CROSSFENCEDETECTION_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pCrossFence->szRuleName, szName, _countof(szName));
			break;
			//2CrossLine
		case EVENT_IVS_CROSSLINEDETECTION:
			pCrossLine = (CFG_CROSSLINE_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pCrossLine->szRuleName, szName, _countof(szName));
			break;
			//3CrossRegion
		case EVENT_IVS_CROSSREGIONDETECTION:
			pCrossRegion = (CFG_CROSSREGION_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pCrossRegion->szRuleName, szName, _countof(szName));
			break;
			//4Move
		case EVENT_IVS_MOVEDETECTION:
			pMove = (CFG_MOVE_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pMove->szRuleName, szName, _countof(szName));
			break;
			//5Left
		case EVENT_IVS_LEFTDETECTION:
			pLeft = (CFG_LEFT_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pLeft->szRuleName, szName, _countof(szName));
			break;
			//6Parking
		case EVENT_IVS_PARKINGDETECTION:
			pParking = (CFG_PARKINGDETECTION_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pParking->szRuleName, szName, _countof(szName));
			break;
			//7Preservation
		case EVENT_IVS_PRESERVATION:
			pPreservation = (CFG_PRESERVATION_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pPreservation->szRuleName, szName, _countof(szName));
			break;
			//8Retro
		case EVENT_IVS_RETROGRADEDETECTION:
			pRetro = (CFG_RETROGRADEDETECTION_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pRetro->szRuleName, szName, _countof(szName));
			break;
			//9Stay
		case EVENT_IVS_STAYDETECTION:
			pStay = (CFG_STAY_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pStay->szRuleName, szName, _countof(szName));
			break;
			//10TakenAway
		case EVENT_IVS_TAKENAWAYDETECTION:
			pTakenAway = (CFG_TAKENAWAYDETECTION_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pTakenAway->szRuleName, szName, _countof(szName));
			break;
			//11VideoAbnormal
		case EVENT_IVS_VIDEOABNORMALDETECTION:
			pVideoAbnormal = (CFG_VIDEOABNORMALDETECTION_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pVideoAbnormal->szRuleName, szName, _countof(szName));
			break;
			//12Wander
		case EVENT_IVS_WANDERDETECTION:
			pWander = (CFG_WANDER_INFO*)pRuleStruct->pRuleBuf;
			strncpy(pWander->szRuleName, szName, _countof(szName));
			break;
		default:
			AfxMessageBox(ConvertString(_T("No such rule type!")));
			break;
		}
	}
}
