// ConfigRules.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "Video Analyse ConfigurationDlg.h"
#include "ConfigRules.h"
#include "ConfigCrossLineRule.h"
#include "ConfigFaceRule.h"
#include "ConfigCrossRegion.h"
#include "ConfigWanderRule.h"
#include "ConfigRioterRule.h"
#include "ConfigPasteRule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_EVENT_RULE	EVENT_IVS_FACEDETECT

/////////////////////////////////////////////////////////////////////////////
// CConfigRules dialog


CConfigRules::CConfigRules(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigRules::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigRules)
	m_strAddRuleName = _T("");
	//}}AFX_DATA_INIT
	m_hPreSelectNode = NULL;
	m_dlgRule = NULL;
	m_lLogID = 0;
	m_lRealPlayHandle = 0;
	m_nChannelCount = 0;
	m_nCurrentChannel = -1;
	m_nMaxRuleNum = 10;
	m_nMaxRuleStructSize = 0;
	memset(m_childRect, 0, sizeof(CRect));
	memset(m_gChannelRules, 0, sizeof(CFG_ANALYSERULES_INFO)*MAX_CHANNEL_NUM);

	m_nSupportedObjTypeNum = 0;
	memset(m_gObjectTypeName, 0, sizeof(char)*MAX_OBJECT_LIST_SIZE*MAX_NAME_LEN);      // device supported object types
	m_nSupportedRulesNum = 0;							 
	memset(m_gRulesTypes, 0, sizeof(DWORD)*MAX_RULE_LIST_SIZE);						 // device supported event types
	m_fProportionX = 0;  
	m_fProportionY = 0;

	InitializeCriticalSection(&m_csRuleTree);
}

CConfigRules::~CConfigRules()
{
	for (int i = 0; i < MAX_CHANNEL_NUM; i++)
	{
		if (m_gChannelRules[i].pRuleBuf != NULL)
		{
			delete[] m_gChannelRules[i].pRuleBuf;
			m_gChannelRules[i].pRuleBuf = NULL;
		}
	}

	if (m_dlgRule != NULL)
	{
		delete m_dlgRule;
		m_dlgRule = NULL;
	}

	DeleteCriticalSection(&m_csRuleTree);
}

void CConfigRules::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigRules)
	DDX_Control(pDX, IDC_TREE_RULES, m_ctRuleTree);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_R, m_cbChannel);
	DDX_Text(pDX, IDC_EDIT_RULENAME, m_strAddRuleName);
	DDV_MaxChars(pDX, m_strAddRuleName, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigRules, CDialog)
	//{{AFX_MSG_MAP(CConfigRules)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_R, OnButtonSaveR)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_R, OnButtonRefreshR)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_R, OnSelchangeComboChannelR)
	ON_BN_CLICKED(IDC_BUTTON_ADDRULE_R, OnButtonAddruleR)
	ON_BN_CLICKED(IDC_BUTTON_DELETRULE_R, OnButtonDeletruleR)
//	ON_NOTIFY(NM_CLICK, IDC_TREE_RULES, OnClickTreeRules)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_RULES, OnSelchangedTreeRules)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigRules message handlers

BOOL CConfigRules::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	//m_cPictureWnd.Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 1981);
	GetDlgItem(IDC_STATIC_VEDIO)->GetWindowRect(&m_childRect);
	ScreenToClient(&m_childRect);	

	m_stuPicShow.Create(IDD_PICTURE_SHOW, this);
	GetProportion(m_childRect);
	m_stuPicShow.MoveWindow(m_childRect);

	memset(m_gChannelRules, 0 , sizeof(CFG_ANALYSERULES_INFO) * MAX_CHANNEL_NUM);

	m_lRealPlayHandle = 0;

// 	HTREEITEM hRoot = MyInsertItem(ConvertString("AllModule"), NULL, NULL);
// 	MySetItemData(hRoot, NULL);
// 	m_ctRuleTree.Expand(hRoot, TVE_EXPAND);
	return TRUE;
}

void CConfigRules::OnButtonSaveR() 
{
	// TODO: Add your control notification handler code here
	if (m_cbChannel.GetCurSel() != -1)
	{
		BOOL bSuccess = SaveChannelRuleInfo(m_nCurrentChannel);
		if (bSuccess)
		{
			((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->SetRule(m_nCurrentChannel, m_gChannelRules[m_nCurrentChannel]);
		}
	}
	else
	{
		MessageBox(ConvertString("please select the channel!"), ConvertString("Prompt"));
	}

	if (m_gChannelRules[m_nCurrentChannel].pRuleBuf)
	{
		delete[] m_gChannelRules[m_nCurrentChannel].pRuleBuf;
		m_gChannelRules[m_nCurrentChannel].pRuleBuf = NULL;
	}
	
}

void CConfigRules::OnButtonRefreshR() 
{
	Refresh();
}

void CConfigRules::OnSelchangeComboChannelR() 
{
	SaveChannelRuleInfo(m_nCurrentChannel);

	if (m_cbChannel.GetCurSel() != -1)
	{
		//clean the tree
		CleanRuleTree();

		GetDeviceCap();
		m_nCurrentChannel = m_cbChannel.GetCurSel();
		ShowChannelRule(m_nCurrentChannel);	
	}
}

void CConfigRules::OnButtonAddruleR() 
{
	UpdateData(TRUE);
	// get the type node
	int nRuleType = -1;
	HTREEITEM hSelectItem = m_ctRuleTree.GetSelectedItem();
	if (hSelectItem == NULL)
	{
		return;
	}
	
	DWORD dwItemData = MyGetItemData(hSelectItem);
	if (dwItemData <= MAX_EVENT_RULE && dwItemData > 1)
	{
		nRuleType = dwItemData;
	}
	else
	{
		HTREEITEM hParentItem = m_ctRuleTree.GetParentItem(hSelectItem);
		if (hParentItem != NULL)
		{
			nRuleType = MyGetItemData(hParentItem);
			hSelectItem = hParentItem;
		}
		else
		{
			return;
		}
	}

	int nRuleCount = GetNodeChildCount(hSelectItem);
	if (nRuleCount >= m_nMaxRuleNum)
	{
		MessageBox(ConvertString("add failed! The rule number has reached the max!"), ConvertString("Prompt"));
		return;
	}

	// save preselect node info
	if (m_hPreSelectNode != NULL)
	{
		BOOL bRet = SaveTreeNodeInfo(m_hPreSelectNode);		
		if (!bRet)
		{
			return;
		}
	}

	// tell if the current rule name has exit
	if (m_strAddRuleName.GetLength() > 0)
	{
		if (RuleNameHasExit(m_strAddRuleName, ""))
		{
			MessageBox(ConvertString("This rule name has exit, Please input other rule name not exit!"), ConvertString("Prompt"));
			return;
		}
	}
	else
	{
		MessageBox(ConvertString("Please input the add rule name first!"), ConvertString("Prompt"));
		return;
	}

	// creat a new rule node
	switch (nRuleType)
	{
	case EVENT_IVS_TRAFFICGATE:
		{
			CFG_TRAFFICGATE_INFO* pTrafficRuleInfo = new CFG_TRAFFICGATE_INFO();
			if (pTrafficRuleInfo == NULL)
			{
				return;
			}
			memset(pTrafficRuleInfo, 0, sizeof(CFG_TRAFFICGATE_INFO));
			memcpy(pTrafficRuleInfo->szRuleName, m_strAddRuleName, m_strAddRuleName.GetLength());  
			
			HTREEITEM hNewRuleNode = MyInsertItem(m_strAddRuleName, hSelectItem, TVI_LAST);
			MySetItemData(hNewRuleNode, (DWORD)pTrafficRuleInfo);
			m_ctRuleTree.SelectItem(hNewRuleNode);
			m_ctRuleTree.SetFocus();
			m_hPreSelectNode = hNewRuleNode;
			ShowTreeNodeInfo(hNewRuleNode);
		}
		break;
	case EVENT_IVS_FACEDETECT:
		{
			CFG_FACEDETECT_INFO* pInfo = new CFG_FACEDETECT_INFO();
			if (pInfo == NULL)
			{
				return;
			}
			memset(pInfo, 0, sizeof(CFG_FACEDETECT_INFO));
			memcpy(pInfo->szRuleName, m_strAddRuleName, m_strAddRuleName.GetLength());  
			
			HTREEITEM hNewRuleNode = MyInsertItem(m_strAddRuleName, hSelectItem, TVI_LAST);
			MySetItemData(hNewRuleNode, (DWORD)pInfo);
			m_ctRuleTree.SelectItem(hNewRuleNode);
			m_ctRuleTree.SetFocus();
			m_hPreSelectNode = hNewRuleNode;
			ShowTreeNodeInfo(hNewRuleNode);
		}
		break;
	case EVENT_IVS_CROSSLINEDETECTION:
		{
			CFG_CROSSLINE_INFO* pInfo = new CFG_CROSSLINE_INFO();
			if (pInfo == NULL)
			{
				return;
			}
			memset(pInfo, 0, sizeof(CFG_CROSSLINE_INFO));
			memcpy(pInfo->szRuleName, m_strAddRuleName, m_strAddRuleName.GetLength());  
			
			HTREEITEM hNewRuleNode = MyInsertItem(m_strAddRuleName, hSelectItem, TVI_LAST);
			MySetItemData(hNewRuleNode, (DWORD)pInfo);
			m_ctRuleTree.SelectItem(hNewRuleNode);
			m_ctRuleTree.SetFocus();
			m_hPreSelectNode = hNewRuleNode;
			ShowTreeNodeInfo(hNewRuleNode);
		}
		break;
	case EVENT_IVS_CROSSREGIONDETECTION:
		{
			CFG_CROSSREGION_INFO* pInfo = new CFG_CROSSREGION_INFO();
			if (pInfo == NULL)
			{
				return;
			}
			memset(pInfo, 0, sizeof(CFG_CROSSREGION_INFO));
			memcpy(pInfo->szRuleName, m_strAddRuleName, m_strAddRuleName.GetLength());  
			
			HTREEITEM hNewRuleNode = MyInsertItem(m_strAddRuleName, hSelectItem, TVI_LAST);
			MySetItemData(hNewRuleNode, (DWORD)pInfo);
			m_ctRuleTree.SelectItem(hNewRuleNode);
			m_ctRuleTree.SetFocus();
			m_hPreSelectNode = hNewRuleNode;
			ShowTreeNodeInfo(hNewRuleNode);
		}
		break;
	case EVENT_IVS_RIOTERDETECTION:
		{
			CFG_RIOTER_INFO* pInfo = new CFG_RIOTER_INFO();
			if (pInfo == NULL)
			{
				return;
			}
			memset(pInfo, 0, sizeof(CFG_RIOTER_INFO));
			memcpy(pInfo->szRuleName, m_strAddRuleName, m_strAddRuleName.GetLength());  
			
			HTREEITEM hNewRuleNode = MyInsertItem(m_strAddRuleName, hSelectItem, TVI_LAST);
			MySetItemData(hNewRuleNode, (DWORD)pInfo);
			m_ctRuleTree.SelectItem(hNewRuleNode);
			m_ctRuleTree.SetFocus();
			m_hPreSelectNode = hNewRuleNode;
			ShowTreeNodeInfo(hNewRuleNode);
		}
		break;
	case EVENT_IVS_PASTEDETECTION:
		{
			CFG_PASTE_INFO* pInfo = new CFG_PASTE_INFO();
			if (pInfo == NULL)
			{
				return;
			}
			memset(pInfo, 0, sizeof(CFG_PASTE_INFO));
			memcpy(pInfo->szRuleName, m_strAddRuleName, m_strAddRuleName.GetLength());  
			
			HTREEITEM hNewRuleNode = MyInsertItem(m_strAddRuleName, hSelectItem, TVI_LAST);
			MySetItemData(hNewRuleNode, (DWORD)pInfo);
			m_ctRuleTree.SelectItem(hNewRuleNode);
			m_ctRuleTree.SetFocus();
			m_hPreSelectNode = hNewRuleNode;
			ShowTreeNodeInfo(hNewRuleNode);
		}
		break;
	case EVENT_IVS_WANDERDETECTION:
		{
			CFG_WANDER_INFO* pInfo = new CFG_WANDER_INFO();
			if (pInfo == NULL)
			{
				return;
			}
			memset(pInfo, 0, sizeof(CFG_WANDER_INFO));
			memcpy(pInfo->szRuleName, m_strAddRuleName, m_strAddRuleName.GetLength());  
			
			HTREEITEM hNewRuleNode = MyInsertItem(m_strAddRuleName, hSelectItem, TVI_LAST);
			MySetItemData(hNewRuleNode, (DWORD)pInfo);
			m_ctRuleTree.SelectItem(hNewRuleNode);
			m_ctRuleTree.SetFocus();
			m_hPreSelectNode = hNewRuleNode;
			ShowTreeNodeInfo(hNewRuleNode);
		}
		break;
	default:
		break;
	}

	m_ctRuleTree.Expand(hSelectItem, TVE_EXPAND);

	return;
}

void CConfigRules::OnButtonDeletruleR() 
{
	HTREEITEM hSelectItem = m_ctRuleTree.GetSelectedItem();
	HTREEITEM hParentItem = m_ctRuleTree.GetParentItem(hSelectItem);
	if (hParentItem == NULL)
	{
		MessageBox(ConvertString("Please select the rule you want to delete!"), ConvertString("Prompt"));
		return;
	}

	int nRuleCount = GetNodeChildCount(hParentItem);
	if (nRuleCount <= 0)
	{
		MessageBox(ConvertString("delete failed! There is no rule to delete!"), ConvertString("Prompt"));
		return;
	}

	DWORD dwRuleType = MyGetItemData(hParentItem);
	DWORD dwRuleInfo = MyGetItemData(hSelectItem);
	m_ctRuleTree.SelectItem(hParentItem);
	m_ctRuleTree.SetFocus();
	m_ctRuleTree.DeleteItem(hSelectItem);

	switch(dwRuleType)
	{
	case EVENT_IVS_TRAFFICGATE:
		{
			CFG_TRAFFICGATE_INFO* pTrafficRuleInfo = (CFG_TRAFFICGATE_INFO*) dwRuleInfo;
			if(pTrafficRuleInfo != NULL)
			{
				delete pTrafficRuleInfo;
				pTrafficRuleInfo = NULL;
			}
		}
		break;
	case EVENT_IVS_WANDERDETECTION:
		{
			CFG_WANDER_INFO* pInfo = (CFG_WANDER_INFO*)dwRuleInfo;
			if (pInfo != NULL)
			{
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case EVENT_IVS_CROSSLINEDETECTION:
		{
			CFG_CROSSLINE_INFO* pInfo = (CFG_CROSSLINE_INFO*)dwRuleInfo;
			if (pInfo != NULL)
			{
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case EVENT_IVS_CROSSREGIONDETECTION:
		{
			CFG_CROSSREGION_INFO* pInfo = (CFG_CROSSREGION_INFO*)dwRuleInfo;
			if (pInfo != NULL)
			{
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case EVENT_IVS_PASTEDETECTION:
		{
			CFG_PASTE_INFO* pInfo = (CFG_PASTE_INFO*)dwRuleInfo;
			if (pInfo != NULL)
			{
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case EVENT_IVS_RIOTERDETECTION:
		{
			CFG_RIOTER_INFO* pInfo = (CFG_RIOTER_INFO*)dwRuleInfo;
			if (pInfo != NULL)
			{
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case EVENT_IVS_FACEDETECT:
		{
			CFG_FACEDETECT_INFO* pInfo = (CFG_FACEDETECT_INFO*)dwRuleInfo;
			if (pInfo != NULL)
			{
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	default:
		break;
	}

	ShowTreeNodeInfo(hParentItem);
	m_hPreSelectNode = hParentItem;
}

void CConfigRules::OnSelchangedTreeRules(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// save preinfo
	if (m_hPreSelectNode != NULL)
	{
		BOOL bRet = SaveTreeNodeInfo(m_hPreSelectNode);
		if (!bRet)
		{
			m_ctRuleTree.SelectItem(m_hPreSelectNode);
			m_ctRuleTree.SetFocus();
			return;
		}
	}
	
	//show select info
	HTREEITEM hSelectItem = m_ctRuleTree.GetSelectedItem();
	ShowTreeNodeInfo(hSelectItem);
	
#ifdef _DEBUG
	CString s;
	s.Format("OnSelchangedTreeRules m_hPreSelectNode %d -> %d \n",m_hPreSelectNode,hSelectItem);
	OutputDebugString(s);
#endif
	m_hPreSelectNode = hSelectItem;
	
	*pResult = 0;
}

CPictrueDialog* CConfigRules::GetPictrueWnd()
{
	return &m_stuPicShow;
}

void CConfigRules::GetProportion(CRect stuWindowSize)
{
	float fWidth;
	float fHeight;
	
	fWidth = stuWindowSize.Width();
	fHeight = stuWindowSize.Height();
	
	m_fProportionX = fWidth / PICTRUE_REAL_SIZE;
	m_fProportionY = fHeight / PICTRUE_REAL_SIZE;
}

void CConfigRules::Init(int nChannelCount)
{
	Clear();

	m_nChannelCount = nChannelCount;
	int nIndex = 0;
	char szBuffer[32] = {0};
	m_cbChannel.ResetContent();
	for(int i = 0; i < m_nChannelCount; i++)
	{
		CString str;
		str = ConvertString("channel") + itoa(i, szBuffer, 10);
		nIndex = m_cbChannel.AddString(str);
		m_cbChannel.SetItemData(nIndex, i);
	}
	
	m_cbChannel.SetCurSel(0);
	m_nCurrentChannel = 0;

	// get device cap
	GetDeviceCap();
	
	// show module info
	Refresh();
} 

void CConfigRules::GetDeviceCap()
{
	int nChannelId = m_cbChannel.GetCurSel();
	CFG_CAP_ANALYSE_INFO* pDeviceCap = NULL;
	if (-1 == nChannelId)
	{
		MessageBox(ConvertString("Please check one channel!"),ConvertString("Prompt"));
		return;
	}
	
	pDeviceCap = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetChannelCapInfo(nChannelId);
	
	if (pDeviceCap != NULL)
	{
		m_nMaxRuleNum = pDeviceCap->nMaxRules;
		m_nSupportedObjTypeNum = pDeviceCap->nSupportedObjectTypeNum;
		memcpy(m_gObjectTypeName, pDeviceCap->szObjectTypeName, MAX_OBJECT_LIST_SIZE * MAX_NAME_LEN * sizeof(char));

		m_nSupportedRulesNum = pDeviceCap->nSupportedRulesNum;
		memcpy(m_gRulesTypes, pDeviceCap->dwRulesType, sizeof(DWORD) * MAX_RULE_LIST_SIZE);
		m_nMaxRuleStructSize = GetRulesMaxStructSize(m_gRulesTypes, m_nSupportedRulesNum);

		int nIndex = 0;
		CString strAlarmList[] = {"", "ALL", "CROSSLINEDETECTION", "CROSSREGIONDETECTION",
			"PASTEDETECTION", "LEFTDETECTION","STAYDETECTION", "WANDERDETECTION",
			"PRESERVATION", "MOVEDETECTION", "TAILDETECTION", "RIOTERDETECTION", 
			"FIREDETECTION", "SMOKEDETECTION", "FIGHTDETECTION", "FLOWSTAT",
			"NUMBERSTAT", "CAMERACOVERDDETECTION", "CAMERAMOVEDDETECTION",
			"VIDEOABNORMALDETECTION", "VIDEOBADDETECTION", "TRAFFICCONTROL", "TRAFFICACCIDENT",
			 "TRAFFICJUNCTION", "TRAFFICGATE","TRAFFICSNAPSHOT","FACEDETECT"};
	
		m_ctRuleTree.DeleteAllItems();
		for(int i = 0; i < m_nSupportedRulesNum; i++)
		{
			int n = m_gRulesTypes[i];
			if (n >= 0 && n < sizeof(strAlarmList)/sizeof(strAlarmList[0]))
			{
				CString s = ConvertString(strAlarmList[n]);
				HTREEITEM hRootRuleItem = MyInsertItem(s, TVI_ROOT, TVI_LAST);
				MySetItemData(hRootRuleItem, m_gRulesTypes[i]);
			}
		}		
	}

	m_lLogID = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetLoginID();
}

int CConfigRules::GetRulesMaxStructSize(DWORD *pRulesTypes, int nRuleNum)
{
	if (pRulesTypes == NULL)
	{
		return 0;
	}

	int nMaxSize = 0;
	int nSize = sizeof(CFG_TRAFFICGATE_INFO);
	for (int i = 0; i < nRuleNum; i++)
	{
		if (pRulesTypes[i] == EVENT_IVS_TRAFFICGATE)
		{
			nSize = sizeof(CFG_TRAFFICGATE_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFICJUNCTION)
		{
			nSize = sizeof(CFG_TRAJUNCTION_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFICACCIDENT)
		{
			nSize = sizeof(CFG_TRAACCIDENT_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFICCONTROL)
		{
			nSize = sizeof(CFG_TRAFFICCONTROL_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_FACEDETECT)
		{
			nSize = sizeof(CFG_FACEDETECT_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_PASTEDETECTION)
		{
			nSize = sizeof(CFG_PASTE_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_CROSSLINEDETECTION)
		{
			nSize = sizeof(CFG_CROSSLINE_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_CROSSREGIONDETECTION)
		{
			nSize = sizeof(CFG_CROSSREGION_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_WANDERDETECTION)
		{
			nSize = sizeof(CFG_WANDER_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_RIOTERDETECTION)
		{
			nSize = sizeof(CFG_RIOTER_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFICJAM)
		{
			nSize = sizeof(CFG_TRAFFICJAM_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_RUNREDLIGHT)
		{
			nSize = sizeof(CFG_TRAFFIC_RUNREDLIGHT_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_OVERLINE)
		{
			nSize = sizeof(CFG_TRAFFIC_OVERLINE_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_RETROGRADE)
		{
			nSize = sizeof(CFG_TRAFFIC_RETROGRADE_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_TURNLEFT)
		{
			nSize = sizeof(CFG_TRAFFIC_TURNLEFT_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_TURNRIGHT)
		{
			nSize = sizeof(CFG_TRAFFIC_TURNRIGHT_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_UTURN)
		{
			nSize = sizeof(CFG_TRAFFIC_UTURN_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_OVERSPEED)
		{
			nSize = sizeof(CFG_TRAFFIC_OVERSPEED_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_UNDERSPEED)
		{
			nSize = sizeof(CFG_TRAFFIC_UNDERSPEED_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_PARKING)
		{
			nSize = sizeof(CFG_TRAFFIC_PARKING_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_WRONGROUTE)
		{
			nSize = sizeof(CFG_TRAFFIC_WRONGROUTE_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_CROSSLANE)
		{
			nSize = sizeof(CFG_TRAFFIC_CROSSLANE_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_OVERYELLOWLINE)
		{
			nSize = sizeof(CFG_TRAFFIC_OVERYELLOWLINE_INFO);
		}


		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE)
		{
			nSize = sizeof(CFG_TRAFFIC_YELLOWPLATEINLANE_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY)
		{
			nSize = sizeof(CFG_TRAFFIC_PEDESTRAINPRIORITY_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_VEHICLEINROUTE)
		{
			nSize = sizeof(CFG_TRAFFIC_VEHICLEINROUTE_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_PARKINGONYELLOWBOX)
		{
			nSize = sizeof(CFG_TRAFFIC_PARKINGONYELLOWBOX_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_PARKINGSPACEPARKING)
		{
			nSize = sizeof(CFG_TRAFFIC_PARKINGSPACEPARKING_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_PARKINGSPACENOPARKING)
		{
			nSize = sizeof(CFG_TRAFFIC_PARKINGSPACENOPARKING_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_PEDESTRAIN)
		{
			nSize = sizeof(CFG_TRAFFIC_PEDESTRAIN_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_THROW)
		{
			nSize = sizeof(CFG_TRAFFIC_THROW_INFO);
		}
		else if (pRulesTypes[i] == EVENT_IVS_TRAFFIC_IDLE)
		{
			nSize = sizeof(CFG_TRAFFIC_IDLE_INFO);
		}


		if (nSize > nMaxSize)
		{
			nMaxSize = nSize;
		}
	}

	return nMaxSize;
}

void CConfigRules::Clear()
{
	for(int i = 0; i < m_nChannelCount; i++)
	{
		if (m_gChannelRules[i].pRuleBuf != NULL)
		{
			delete m_gChannelRules[i].pRuleBuf;
			m_gChannelRules[i].pRuleBuf = NULL;
		}
	}

	if (m_ctRuleTree.GetCount() >0)
	{
		CleanRuleTree();
		//m_ctRuleTree.DeleteAllItems();
	}
	m_stuPicShow.DeleteRecourse();
	m_cbChannel.ResetContent();
	
	m_stuPicShow.DeleteRecourse();
 	m_stuPicShow.Invalidate(TRUE);

	if (m_dlgRule != NULL)
	{
		m_dlgRule->DestroyWindow();
		delete m_dlgRule;
		m_dlgRule = NULL;
	}

	//clear
	m_hPreSelectNode = NULL;
	m_lLogID = 0;
	m_lRealPlayHandle = 0;
	m_nChannelCount = 0;
	m_nCurrentChannel = -1;
	m_nMaxRuleNum = 10;
	m_nMaxRuleStructSize = 0;
	m_nSupportedObjTypeNum = 0;
	m_nSupportedRulesNum = 0;
	m_strAddRuleName = "";
	UpdateData(FALSE);

	Invalidate(TRUE);
}

void CConfigRules::Refresh()
{
	//clean the tree
	CleanRuleTree();
	// show
	ShowChannelRule(m_nCurrentChannel);
}

void CConfigRules::ShowChannelRule(int nChannelId)
{
	if (nChannelId == -1)
	{
		return;
	}
	// get rule info
	if (m_gChannelRules[nChannelId].pRuleBuf != NULL)
	{
		delete[] m_gChannelRules[nChannelId].pRuleBuf;
		m_gChannelRules[nChannelId].pRuleBuf = NULL;
	}

	int nBufLen = (sizeof(CFG_RULE_INFO) + m_nMaxRuleStructSize) * m_nMaxRuleNum;
	m_gChannelRules[nChannelId].pRuleBuf = new char[nBufLen];
	m_gChannelRules[nChannelId].nRuleLen = nBufLen;
	
	BOOL bSuccess = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetRule(nChannelId, 
		m_gChannelRules[nChannelId]);
	if (!bSuccess)
	{
		if (m_gChannelRules[nChannelId].pRuleBuf != NULL)
		{
			delete[] m_gChannelRules[nChannelId].pRuleBuf;
			m_gChannelRules[nChannelId].pRuleBuf = NULL;
		}
		return;
	}

// 	//clean the tree
// 	CleanRuleTree();

	//show rules
	CFG_RULE_INFO* pRuleInfo = NULL;
	int nHaveReadLen = 0;
	char szBuffer[32] = {0};
	CString strLeafName;
	int nChildNodeCount = 0;
	for(int i = 0; i < m_gChannelRules[nChannelId].nRuleCount; i++)
	{
		if (nHaveReadLen >= m_gChannelRules[nChannelId].nRuleLen)
		{
			break;
		}

		InsertChildNode2EvtTree(nChannelId,nHaveReadLen);
	}

	HTREEITEM hRootItem = m_ctRuleTree.GetRootItem();
	m_hPreSelectNode = hRootItem;

	m_ctRuleTree.SelectItem(hRootItem);
	ShowTreeNodeInfo(hRootItem);
	Invalidate(TRUE);

#ifdef _DEBUG
	CString s;
	s.Format("ShowChannelRule m_hPreSelectNode %d -> %d \n",m_hPreSelectNode,hRootItem);
	OutputDebugString(s);
#endif

	if (m_gChannelRules[nChannelId].pRuleBuf != NULL)
	{
		delete[] m_gChannelRules[nChannelId].pRuleBuf;
		m_gChannelRules[nChannelId].pRuleBuf = NULL;
	}
} 

void CConfigRules::InsertChildNode2EvtTree(int nChannelId,int &nHaveReadLen)
{
	if (nChannelId == -1)
	{
		return;
	}

	CFG_RULE_INFO* pRuleInfo = NULL;
	CString strLeafName;
	int nChildNodeCount = 0;
	pRuleInfo = (CFG_RULE_INFO*) (m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen);
	nHaveReadLen += sizeof(CFG_RULE_INFO);

	DWORD dwItemData = 0;
	bool bInsert = false;
	switch(pRuleInfo->dwRuleType)
	{
	case EVENT_IVS_TRAFFICGATE:
		{
			CFG_TRAFFICGATE_INFO* pTrafficInfo = new CFG_TRAFFICGATE_INFO();
			memset(pTrafficInfo, 0, sizeof(CFG_TRAFFICGATE_INFO));
			memcpy(pTrafficInfo, m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen, sizeof(CFG_TRAFFICGATE_INFO));
			nHaveReadLen += sizeof(CFG_TRAFFICGATE_INFO);
			strLeafName = pTrafficInfo->szRuleName;
			dwItemData = (DWORD)pTrafficInfo;

			bInsert = true;
		}
		break;
	case EVENT_IVS_CROSSLINEDETECTION:
		{
			CFG_CROSSLINE_INFO* pInfo = new CFG_CROSSLINE_INFO;
			memset(pInfo,0,sizeof(CFG_CROSSLINE_INFO));
			memcpy(pInfo,m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen,sizeof(CFG_CROSSLINE_INFO));
			nHaveReadLen += sizeof(CFG_CROSSLINE_INFO);
			strLeafName = pInfo->szRuleName;
			dwItemData = (DWORD)pInfo;

			if (NULL != pInfo)
			{
#ifdef _DEBUG
				CString s;
				s.Format("InsertChildNode2EvtTree nDetectLinePoint: %d (%d,%d) (%d,%d) !\n",
					pInfo->nDetectLinePoint,pInfo->stuDetectLine[0].nX,
					pInfo->stuDetectLine[0].nY,pInfo->stuDetectLine[1].nX,
					pInfo->stuDetectLine[1].nY);
				OutputDebugString(s);
#endif
			}

			bInsert = true;
		}
		break;
	case EVENT_IVS_CROSSREGIONDETECTION:
		{
			CFG_CROSSREGION_INFO* pInfo = new CFG_CROSSREGION_INFO;
			memset(pInfo,0,sizeof(CFG_CROSSREGION_INFO));
			memcpy(pInfo,m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen,sizeof(CFG_CROSSREGION_INFO));
			nHaveReadLen += sizeof(CFG_CROSSREGION_INFO);
			strLeafName = pInfo->szRuleName;
			dwItemData = (DWORD)pInfo;
			
			bInsert = true;
		}
		break;
	case EVENT_IVS_FACEDETECT:
		{
			CFG_FACEDETECT_INFO* pInfo = new CFG_FACEDETECT_INFO;
			memset(pInfo,0,sizeof(CFG_FACEDETECT_INFO));
			memcpy(pInfo,m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen,sizeof(CFG_FACEDETECT_INFO));
			nHaveReadLen += sizeof(CFG_FACEDETECT_INFO);
			strLeafName = pInfo->szRuleName;
			dwItemData = (DWORD)pInfo;
			
			bInsert = true;
		}
		break;
	case EVENT_IVS_WANDERDETECTION:
		{
			CFG_WANDER_INFO* pInfo = new CFG_WANDER_INFO;
			memset(pInfo,0,sizeof(CFG_WANDER_INFO));
			memcpy(pInfo,m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen,sizeof(CFG_WANDER_INFO));
			nHaveReadLen += sizeof(CFG_WANDER_INFO);
			strLeafName = pInfo->szRuleName;
			dwItemData = (DWORD)pInfo;
			
			bInsert = true;
		}
		break;
	case EVENT_IVS_PASTEDETECTION:
		{
			CFG_PASTE_INFO* pInfo = new CFG_PASTE_INFO;
			memset(pInfo,0,sizeof(CFG_PASTE_INFO));
			memcpy(pInfo,m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen,sizeof(CFG_PASTE_INFO));
			nHaveReadLen += sizeof(CFG_PASTE_INFO);
			strLeafName = pInfo->szRuleName;
			dwItemData = (DWORD)pInfo;
			
			bInsert = true;
		}
		break;
	case EVENT_IVS_RIOTERDETECTION:
		{
			CFG_RIOTER_INFO* pInfo = new CFG_RIOTER_INFO;
			memset(pInfo,0,sizeof(CFG_RIOTER_INFO));
			memcpy(pInfo,m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen,sizeof(CFG_RIOTER_INFO));
			nHaveReadLen += sizeof(CFG_RIOTER_INFO);
			strLeafName = pInfo->szRuleName;
			dwItemData = (DWORD)pInfo;
			
			bInsert = true;
		}
		break;
	default:
		break;
	}

	if (bInsert)
	{
		HTREEITEM pRootItem = FindTreeNode(pRuleInfo->dwRuleType);
		nChildNodeCount = GetNodeChildCount(pRootItem);
		HTREEITEM hLeefItem = MyInsertItem(strLeafName,pRootItem,TVI_LAST);
		MySetItemData(hLeefItem,dwItemData);
		m_ctRuleTree.Expand(pRootItem,TVE_EXPAND);
	}
}

void CConfigRules::CleanRuleTree()
{
	HTREEITEM hRoot = m_ctRuleTree.GetRootItem();
	DWORD dwRootData = 0;
	DWORD dwLeafData = 0;
	while (hRoot != NULL)
	{
		dwRootData = MyGetItemData(hRoot);
		if (m_ctRuleTree.ItemHasChildren(hRoot))
		{
			HTREEITEM hChildNode = m_ctRuleTree.GetChildItem(hRoot);
			HTREEITEM hNextNode = NULL;
			while (hChildNode != NULL)
			{
				hNextNode = m_ctRuleTree.GetNextItem(hChildNode,TVGN_NEXT);
				if (m_ctRuleTree.GetSelectedItem() == hChildNode)
				{
					m_ctRuleTree.SelectItem(hRoot);
				}
				dwLeafData = MyGetItemData(hChildNode);
				m_ctRuleTree.DeleteItem(hChildNode);
				switch (dwRootData )
				{
				case EVENT_IVS_TRAFFICGATE:
					{
						CFG_TRAFFICGATE_INFO* pTrafficGateInfo = (CFG_TRAFFICGATE_INFO*) dwLeafData;
						if (pTrafficGateInfo != NULL)
						{
							delete pTrafficGateInfo;
							pTrafficGateInfo = NULL;
						}
					}
					break;
				case EVENT_IVS_CROSSLINEDETECTION:
					{
						CFG_CROSSLINE_INFO* pInfo = (CFG_CROSSLINE_INFO*)dwLeafData;
						if (pInfo != NULL)
						{
							delete pInfo;
							pInfo = NULL;
						}
					}
					break;
				case EVENT_IVS_CROSSREGIONDETECTION:
					{
						CFG_CROSSREGION_INFO* pInfo = (CFG_CROSSREGION_INFO*)dwLeafData;
						if (pInfo != NULL)
						{
							delete pInfo;
							pInfo = NULL;
						}
					}
					break;
				case EVENT_IVS_FACEDETECT:
					{
						CFG_FACEDETECT_INFO* pInfo = (CFG_FACEDETECT_INFO*)dwLeafData;
						if (pInfo != NULL)
						{
							delete pInfo;
							pInfo = NULL;
						}
					}
					break;
				case EVENT_IVS_WANDERDETECTION:
					{
						CFG_WANDER_INFO* pInfo = (CFG_WANDER_INFO*)dwLeafData;
						if (pInfo != NULL)
						{
							delete pInfo;
							pInfo = NULL;
						}
					}
					break;
				case EVENT_IVS_RIOTERDETECTION:
					{
						CFG_RIOTER_INFO* pInfo = (CFG_RIOTER_INFO*)dwLeafData;
						if (pInfo != NULL)
						{
							delete pInfo;
							pInfo = NULL;
						}
					}
					break;
				case EVENT_IVS_PASTEDETECTION:
					{
						CFG_PASTE_INFO* pInfo = (CFG_PASTE_INFO*)dwLeafData;
						if (pInfo != NULL)
						{
							delete pInfo;
							pInfo = NULL;
						}
					}
					break;
				default:
					break;
	
				}
				hChildNode = hNextNode;
			}
		}
		hRoot = m_ctRuleTree.GetNextItem(hRoot, TVGN_NEXT);
	}

	return;
}

int CConfigRules::GetNodeChildCount(HTREEITEM hRootItem)
{
	int nCount = 0;
	if (!m_ctRuleTree.ItemHasChildren(hRootItem))
	{
		return 0;
	}

	HTREEITEM hChildItem = m_ctRuleTree.GetChildItem(hRootItem);

	while(hChildItem != NULL)
	{
		nCount++;
		hChildItem = m_ctRuleTree.GetNextItem(hChildItem, TVGN_NEXT);
	}

	return nCount;
}

HTREEITEM CConfigRules::FindTreeNode(DWORD Type)
{
	HTREEITEM hEventItem = m_ctRuleTree.GetRootItem();

	while(hEventItem != NULL)
	{
		DWORD dwItemData = MyGetItemData(hEventItem);
		if (dwItemData == Type)
		{
			return hEventItem;
		}

		hEventItem = m_ctRuleTree.GetNextItem(hEventItem, TVGN_NEXT);
	}

	return NULL;
}

BOOL CConfigRules::RuleNameHasExit(CString strNewRuleName, CString strCurrentRuleName)
{
	CString strItemText;
	HTREEITEM hRootItem = m_ctRuleTree.GetRootItem();

	while(hRootItem != NULL)
	{
		HTREEITEM hChileNode = m_ctRuleTree.GetChildItem(hRootItem);
		while(hChileNode != NULL)
		{
			strItemText = m_ctRuleTree.GetItemText(hChileNode);
			if (strItemText == strNewRuleName && strItemText != strCurrentRuleName)
			{
				return TRUE;
			}

			hChileNode = m_ctRuleTree.GetNextItem(hChileNode,TVGN_NEXT);
		}
		hRootItem = m_ctRuleTree.GetNextItem(hRootItem,TVGN_NEXT);
	}

	return FALSE;
}

BOOL CConfigRules::SaveTreeNodeInfo(HTREEITEM hTreeNode)
{
	DWORD dwItemData;

#ifdef _DEBUG
	CString s;
	s.Format("SaveTreeNodeInfo m_hPreSelectNode %d !\n",hTreeNode);
	OutputDebugString(s);
#endif

	dwItemData = MyGetItemData(m_hPreSelectNode);
// 	dwItemData = MyGetItemData(hTreeNode);
	if (dwItemData <= MAX_EVENT_RULE && dwItemData > 1)
	{// Event node
		return TRUE;
	}
	else
	{// Rule node	
		
		HTREEITEM hRootItem = m_ctRuleTree.GetParentItem(hTreeNode);
		if (hTreeNode == NULL)
		{
			return TRUE;
		}

		void* pRuleData = NULL;
		int nRuleDataLenth = 0;
		CString strRuleName;
		DWORD dwRootData = MyGetItemData(hRootItem);
		switch (dwRootData)
		{
		case  EVENT_IVS_TRAFFICGATE:
			{
				CConfigTrafficGateRule* pTrafficGateRule = (CConfigTrafficGateRule*) m_dlgRule;
				CFG_TRAFFICGATE_INFO* pTrafficGateRuleInfo = pTrafficGateRule->SaveRuleInfo();
				
				pRuleData = pTrafficGateRuleInfo;
				nRuleDataLenth = sizeof(CFG_TRAFFICGATE_INFO);
				strRuleName = pTrafficGateRuleInfo->szRuleName;
			}
			break;
		case EVENT_IVS_FACEDETECT:
			{
				CConfigFaceRule* pRule = (CConfigFaceRule*) m_dlgRule;
				CFG_FACEDETECT_INFO* pRuleInfo = pRule->SaveRuleInfo();
				
				pRuleData = pRuleInfo;
				nRuleDataLenth = sizeof(CFG_FACEDETECT_INFO);
				strRuleName = pRuleInfo->szRuleName;
			}
			break;
		case EVENT_IVS_CROSSLINEDETECTION:
			{
				CConfigCrossLineRule* pRule = (CConfigCrossLineRule*) m_dlgRule;
				CFG_CROSSLINE_INFO* pRuleInfo = pRule->SaveRuleInfo();
				
				pRuleData = pRuleInfo;
				nRuleDataLenth = sizeof(CFG_CROSSLINE_INFO);
				strRuleName = pRuleInfo->szRuleName;
			}
			break;
		case EVENT_IVS_CROSSREGIONDETECTION:
			{
				CConfigCrossRegion* pRule = (CConfigCrossRegion*) m_dlgRule;
				CFG_CROSSREGION_INFO* pRuleInfo = pRule->SaveRuleInfo();
				
				pRuleData = pRuleInfo;
				nRuleDataLenth = sizeof(CFG_CROSSREGION_INFO);
				strRuleName = pRuleInfo->szRuleName;
			}
			break;
		case EVENT_IVS_PASTEDETECTION:
			{
				CConfigPasteRule* pRule = (CConfigPasteRule*) m_dlgRule;
				CFG_PASTE_INFO* pRuleInfo = pRule->SaveRuleInfo();
				
				pRuleData = pRuleInfo;
				nRuleDataLenth = sizeof(CFG_PASTE_INFO);
				strRuleName = pRuleInfo->szRuleName;
			}
			break;
		case EVENT_IVS_RIOTERDETECTION:
			{
				CConfigRioterRule* pRule = (CConfigRioterRule*) m_dlgRule;
				CFG_RIOTER_INFO* pRuleInfo = pRule->SaveRuleInfo();
				
				pRuleData = pRuleInfo;
				nRuleDataLenth = sizeof(CFG_RIOTER_INFO);
				strRuleName = pRuleInfo->szRuleName;
			}
			break;
		case EVENT_IVS_WANDERDETECTION:
			{
				CConfigWanderRule* pRule = (CConfigWanderRule*) m_dlgRule;
				CFG_WANDER_INFO* pRuleInfo = pRule->SaveRuleInfo();
				
				pRuleData = pRuleInfo;
				nRuleDataLenth = sizeof(CFG_WANDER_INFO);
				strRuleName = pRuleInfo->szRuleName;
			}
			break;
		default:
			break;
		}

		if (dwItemData != NULL && pRuleData != NULL)
		{
			memcpy((void*)dwItemData, pRuleData, nRuleDataLenth);
			m_ctRuleTree.SetItemText(hTreeNode, strRuleName);
		}
		else if (pRuleData == NULL)
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

void CConfigRules::ShowTreeNodeInfo(HTREEITEM hTreeNode)
{
	if (hTreeNode == NULL)
	{
		m_stuPicShow.DeleteRecourse();
		return;
	}

	DWORD dwItemData;
	dwItemData = MyGetItemData(hTreeNode);
	if (dwItemData <= MAX_EVENT_RULE && dwItemData > 1)
	{// Event node
		if (m_dlgRule != NULL)
		{
			m_dlgRule->ShowWindow(SW_HIDE);
		}
		
		StartRealPay();
		InPutExitLinesToPicture(&m_stuPicShow, hTreeNode, m_fProportionX, m_fProportionY);
	
		m_stuPicShow.ShowWindow(SW_SHOW);
	}
	else
	{// Rule node
		m_stuPicShow.ShowWindow(SW_HIDE);
		StopRealPlay();
		if (m_dlgRule != NULL)
		{
			m_dlgRule->DestroyWindow();
			delete m_dlgRule;
			m_dlgRule = NULL;
		}

		HTREEITEM hRootItem = m_ctRuleTree.GetParentItem(hTreeNode);
		if (hRootItem == NULL)
		{
			return;
		}

		DWORD dwRootData = MyGetItemData(hRootItem);
		switch (dwRootData)
		{
		case EVENT_IVS_TRAFFICGATE:
			{
				CConfigTrafficGateRule* pTrafficGateRule = new CConfigTrafficGateRule();
				pTrafficGateRule->Create(IDD_CONFIG_TRAFFICGATE, this);
				pTrafficGateRule->MoveWindow(m_childRect);
				pTrafficGateRule->ShowWindow(SW_SHOW);
				
				pTrafficGateRule->GetRuleInfo(this, m_lLogID, (CFG_TRAFFICGATE_INFO*)dwItemData, m_nCurrentChannel);
				pTrafficGateRule->ShowRuleInfo();
				pTrafficGateRule->UpdateFalse();
				
				m_dlgRule = pTrafficGateRule;
			}
			break;
		case EVENT_IVS_FACEDETECT:
			{
				CConfigFaceRule* pInfo = new CConfigFaceRule();
				pInfo->Create(IDD_COFNIG_FACEDETECT_RULE,this);
				pInfo->MoveWindow(m_childRect);
				pInfo->ShowWindow(SW_SHOW);
				
				pInfo->GetRuleInfo(this, m_lLogID, (CFG_FACEDETECT_INFO*)dwItemData, m_nCurrentChannel);
				pInfo->ShowRuleInfo();
				pInfo->UpdateFalse();
				
				m_dlgRule = pInfo;
			}
			break;
		case EVENT_IVS_WANDERDETECTION:
			{
				CConfigWanderRule* pInfo = new CConfigWanderRule();
				pInfo->Create(IDD_CONFIG_WANDER_RULE,this);
				pInfo->MoveWindow(m_childRect);
				pInfo->ShowWindow(SW_SHOW);
				
				pInfo->GetRuleInfo(this, m_lLogID, (CFG_WANDER_INFO*)dwItemData, m_nCurrentChannel);
				pInfo->ShowRuleInfo();
				pInfo->UpdateFalse();
				
				m_dlgRule = pInfo;
			}
			break;
		case EVENT_IVS_RIOTERDETECTION:
			{
				CConfigRioterRule* pInfo = new CConfigRioterRule();
				pInfo->Create(IDD_CONFIG_RIOTER_RULE,this);
				pInfo->MoveWindow(m_childRect);
				pInfo->ShowWindow(SW_SHOW);
				
				pInfo->GetRuleInfo(this, m_lLogID, (CFG_RIOTER_INFO*)dwItemData, m_nCurrentChannel);
				pInfo->ShowRuleInfo();
				pInfo->UpdateFalse();
				
				m_dlgRule = pInfo;
			}
			break;
		case EVENT_IVS_PASTEDETECTION:
			{
				CConfigPasteRule* pInfo = new CConfigPasteRule();
				pInfo->Create(IDD_CONFIG_PASTE_RULE,this);
				pInfo->MoveWindow(m_childRect);
				pInfo->ShowWindow(SW_SHOW);
				
				pInfo->GetRuleInfo(this, m_lLogID, (CFG_PASTE_INFO*)dwItemData, m_nCurrentChannel);
				pInfo->ShowRuleInfo();
				pInfo->UpdateFalse();
				
				m_dlgRule = pInfo;
			}
			break;
		case EVENT_IVS_CROSSREGIONDETECTION:
			{
				CConfigCrossRegion* pInfo = new CConfigCrossRegion();
				pInfo->Create(IDD_CONFIG_CROSSREGION_RULE,this);
				pInfo->MoveWindow(m_childRect);
				pInfo->ShowWindow(SW_SHOW);
				
				pInfo->GetRuleInfo(this, m_lLogID, (CFG_CROSSREGION_INFO*)dwItemData, m_nCurrentChannel);
				pInfo->ShowRuleInfo();
				pInfo->UpdateFalse();
				
				m_dlgRule = pInfo;
			}
			break;
		case EVENT_IVS_CROSSLINEDETECTION:
			{
				CConfigCrossLineRule* pInfo = new CConfigCrossLineRule();
				pInfo->Create(IDD_COFNIG_CROSSLINE_RULE,this);
				pInfo->MoveWindow(m_childRect);
				pInfo->ShowWindow(SW_SHOW);
				
				pInfo->GetRuleInfo(this, m_lLogID, (CFG_CROSSLINE_INFO*)dwItemData, m_nCurrentChannel);
				pInfo->ShowRuleInfo();
				pInfo->UpdateFalse();
				
				m_dlgRule = pInfo;
			}
			break;
		default:
			break;
		}
	}

	return;
}

void CConfigRules::StopRealPlay()
{
	if (m_lRealPlayHandle != 0)
	{
		CLIENT_StopRealPlayEx(m_lRealPlayHandle);
		m_lRealPlayHandle = 0;
	}
}

void CConfigRules::StartRealPay()
{
	if (m_lRealPlayHandle == 0)
	{
		CLIENT_RigisterDrawFun(ChannelAutoDraw, (LDWORD)&m_stuPicShow);
		m_lRealPlayHandle = CLIENT_RealPlayEx(m_lLogID, m_nCurrentChannel, m_stuPicShow.m_hWnd);
	}
}

HTREEITEM CConfigRules::GetSelectEventNode()
{
	HTREEITEM hSelectItem = m_ctRuleTree.GetSelectedItem();
	HTREEITEM hParentItem = m_ctRuleTree.GetParentItem(hSelectItem);

	return hParentItem;
}

void CConfigRules::InPutExitLinesToPicture(CPictrueDialog* pPicShow, HTREEITEM hTreeNode, float fProportionX, float fProportionY)
{
	if (pPicShow == NULL || hTreeNode == NULL)
	{
		return;
	}

	MAPCROSSLINE* pMapLine = NULL;
	CString strRuleName;
	pPicShow->DeleteRecourse();

	int nCount = 0;
	DWORD dwChildData = 0;
	DWORD dwRuleType = MyGetItemData(hTreeNode);
	BOOL bHasChild = m_ctRuleTree.ItemHasChildren(hTreeNode);
	if (!bHasChild)
	{
		return;
	}
	HTREEITEM hSelectItem = m_ctRuleTree.GetSelectedItem();
	HTREEITEM hChildItem = m_ctRuleTree.GetChildItem(hTreeNode);
	char szBuffer[32] = {0};
	while (hChildItem != NULL)
	{
		if (hSelectItem == hChildItem)
		{
			hChildItem = m_ctRuleTree.GetNextItem(hChildItem,TVGN_NEXT);
			continue;
		}

		pMapLine = new MAPCROSSLINE();

		dwChildData = MyGetItemData(hChildItem);
		strRuleName = ConvertString("rule") + itoa(nCount, szBuffer, 10);
		pPicShow->m_mRules[strRuleName] = pMapLine;

		InputRuleInfo((*pMapLine), (void*)dwChildData, dwRuleType, fProportionX, fProportionY);
		nCount++;
		hChildItem = m_ctRuleTree.GetNextItem(hChildItem,TVGN_NEXT);
	}
}

void CConfigRules::InputRuleInfo(MAPCROSSLINE &pMapLine, void* pRuleInfo, DWORD dwRuleType, float fProportionX, float fProportionY)
{

	if (pRuleInfo == NULL)
	{
		return;
	}

	switch (dwRuleType)
	{
	case EVENT_IVS_TRAFFICGATE:
		{
			CFG_TRAFFICGATE_INFO* pTrafficGateRule = (CFG_TRAFFICGATE_INFO*)pRuleInfo;
			int i = 0;
			
			// detect line info
			int nDetectLinePoint1 = pTrafficGateRule->nDetectLinePoint1;
			if (nDetectLinePoint1 > 0)
			{
				POINT *pPoints = new POINT[nDetectLinePoint1];
				for(i = 0; i < nDetectLinePoint1; i++)
				{
					pPoints[i].x = pTrafficGateRule->stuDetectLine1[i].nX * fProportionX;
					pPoints[i].y = pTrafficGateRule->stuDetectLine1[i].nY * fProportionY;
				}
				CDrawObject* cObj = new CDrawLines(pPoints, nDetectLinePoint1, eDetectLine);
				pMapLine[eDetectLine].push_back(cObj);
				delete[] pPoints;
				pPoints = NULL;
			}
			
			
			int nDetectLinePoint2 = pTrafficGateRule->nDetectLinePoint2;
			if (nDetectLinePoint2 > 0)
			{
				POINT* pPoints = new POINT[nDetectLinePoint2];
				for(i = 0; i < nDetectLinePoint2; i++)
				{
					pPoints[i].x = pTrafficGateRule->stuDetectLine2[i].nX * fProportionX;
					pPoints[i].y = pTrafficGateRule->stuDetectLine2[i].nY * fProportionY;
				}
				CDrawObject* cObj = new CDrawLines(pPoints, nDetectLinePoint2, eDetectLine);
				pMapLine[eDetectLine].push_back(cObj);
				delete[] pPoints;
				pPoints = NULL;
			}
			
			// road info
			int nLeftPointNum = pTrafficGateRule->nLeftLinePoint; 
			int nRightPointNum = pTrafficGateRule->nRightLinePoint;
			if (nLeftPointNum > 0 && nRightPointNum > 0)
			{
				POINT *pLeftPoint = new POINT[nLeftPointNum];
				for(i = 0; i < nLeftPointNum; i++)
				{
					pLeftPoint[i].x = pTrafficGateRule->stuLeftLine[i].nX * fProportionX;
					pLeftPoint[i].y = pTrafficGateRule->stuLeftLine[i].nY * fProportionY;
				}
				
				
				POINT *pRightPoint = new POINT[nRightPointNum];
				for(i = 0; i < nLeftPointNum; i++)
				{
					pRightPoint[i].x = pTrafficGateRule->stuRightLine[i].nX * fProportionX;
					pRightPoint[i].y = pTrafficGateRule->stuRightLine[i].nY * fProportionY;
				}
				
				CDrawLines* cleftObject = new CDrawLines(pLeftPoint, nLeftPointNum, eRoadLine);
				CDrawLines* crightObject = new CDrawLines(pRightPoint, nRightPointNum, eRoadLine);
				cleftObject->m_leftRoadLine = cleftObject;
				cleftObject->m_rightRoadLine = crightObject;
				crightObject->m_leftRoadLine = cleftObject;
				crightObject->m_rightRoadLine = crightObject;
				
				pMapLine[eRoadLine].push_back(cleftObject);
				pMapLine[eRoadLine].push_back(crightObject);
				delete[] pRightPoint;
				pRightPoint = NULL;
				delete[] pLeftPoint;
				pLeftPoint = NULL;
			}
		}
		break;
	case EVENT_IVS_FACEDETECT:
		{
			CFG_FACEDETECT_INFO* pRule = (CFG_FACEDETECT_INFO*)pRuleInfo;

			int nDetectRegionPoint = pRule->nDetectRegionPoint;
			if (nDetectRegionPoint > 0)
			{
				POINT *pPoints = new POINT[nDetectRegionPoint];
				for(int i = 0; i < nDetectRegionPoint; i++)
				{
					pPoints[i].x = pRule->stuDetectRegion[i].nX * fProportionX;
					pPoints[i].y = pRule->stuDetectRegion[i].nY * fProportionY;
				}
				CDrawObject* cObj = new CDrawLines(pPoints, nDetectRegionPoint, eDetectArea);
				pMapLine[eDetectArea].push_back(cObj);
				delete[] pPoints;
				pPoints = NULL;
			}
			

		}
		break;
	case EVENT_IVS_WANDERDETECTION:
		{
			CFG_WANDER_INFO* pRule = (CFG_WANDER_INFO*)pRuleInfo;
			
			int nDetectRegionPoint = pRule->nDetectRegionPoint;
			if (nDetectRegionPoint > 0)
			{
				POINT *pPoints = new POINT[nDetectRegionPoint];
				for(int i = 0; i < nDetectRegionPoint; i++)
				{
					pPoints[i].x = pRule->stuDetectRegion[i].nX * fProportionX;
					pPoints[i].y = pRule->stuDetectRegion[i].nY * fProportionY;
				}
				CDrawObject* cObj = new CDrawLines(pPoints, nDetectRegionPoint, eDetectArea);
				pMapLine[eDetectArea].push_back(cObj);
				delete[] pPoints;
				pPoints = NULL;
			}
		}
		break;
	case EVENT_IVS_RIOTERDETECTION:
		{
			CFG_RIOTER_INFO* pRule = (CFG_RIOTER_INFO*)pRuleInfo;
			
			int nDetectRegionPoint = pRule->nDetectRegionPoint;
			if (nDetectRegionPoint > 0)
			{
				POINT *pPoints = new POINT[nDetectRegionPoint];
				for(int i = 0; i < nDetectRegionPoint; i++)
				{
					pPoints[i].x = pRule->stuDetectRegion[i].nX * fProportionX;
					pPoints[i].y = pRule->stuDetectRegion[i].nY * fProportionY;
				}
				CDrawObject* cObj = new CDrawLines(pPoints, nDetectRegionPoint, eDetectArea);
				pMapLine[eDetectArea].push_back(cObj);
				delete[] pPoints;
				pPoints = NULL;
			}
		}
		break;
	case EVENT_IVS_PASTEDETECTION:
		{
			CFG_PASTE_INFO* pRule = (CFG_PASTE_INFO*)pRuleInfo;
			
			int nDetectRegionPoint = pRule->nDetectRegionPoint;
			if (nDetectRegionPoint > 0)
			{
				POINT *pPoints = new POINT[nDetectRegionPoint];
				for(int i = 0; i < nDetectRegionPoint; i++)
				{
					pPoints[i].x = pRule->stuDetectRegion[i].nX * fProportionX;
					pPoints[i].y = pRule->stuDetectRegion[i].nY * fProportionY;
				}
				CDrawObject* cObj = new CDrawLines(pPoints, nDetectRegionPoint, eDetectArea);
				pMapLine[eDetectArea].push_back(cObj);
				delete[] pPoints;
				pPoints = NULL;
			}
		}
		break;
	case EVENT_IVS_CROSSLINEDETECTION:
		{
			CFG_CROSSLINE_INFO* pRule = (CFG_CROSSLINE_INFO*)pRuleInfo;
			
			int nDetectLinePoint = pRule->nDetectLinePoint;
			if (nDetectLinePoint > 0)
			{
				POINT *pPoints = new POINT[nDetectLinePoint];
				for(int i = 0; i < nDetectLinePoint; i++)
				{
					pPoints[i].x = pRule->stuDetectLine[i].nX * fProportionX;
					pPoints[i].y = pRule->stuDetectLine[i].nY * fProportionY;
				}
				CDrawObject* cObj = new CDrawLines(pPoints, nDetectLinePoint, eDetectLine);
				pMapLine[eDetectLine].push_back(cObj);
				delete[] pPoints;
				pPoints = NULL;
			}
		}
		break;
	case EVENT_IVS_CROSSREGIONDETECTION:
		{
			CFG_CROSSREGION_INFO* pRule = (CFG_CROSSREGION_INFO*)pRuleInfo;
			
			int nDetectRegionPoint = pRule->nDetectRegionPoint;
			if (nDetectRegionPoint > 0)
			{
				POINT *pPoints = new POINT[nDetectRegionPoint];
				for(int i = 0; i < nDetectRegionPoint; i++)
				{
					pPoints[i].x = pRule->stuDetectRegion[i].nX * fProportionX;
					pPoints[i].y = pRule->stuDetectRegion[i].nY * fProportionY;
				}
				CDrawObject* cObj = new CDrawLines(pPoints, nDetectRegionPoint, eDetectArea);
				pMapLine[eDetectArea].push_back(cObj);
				delete[] pPoints;
				pPoints = NULL;
			}
		}
		break;
	default:
		break;
	}
}

BOOL CConfigRules::SaveChannelRuleInfo(int nChannelId)
{
	if (m_hPreSelectNode != NULL)
	{
		BOOL bRet = SaveTreeNodeInfo(m_hPreSelectNode);
		if (!bRet)
		{
			return FALSE;
		}
	}
	

	delete[] m_gChannelRules[nChannelId].pRuleBuf;
	m_gChannelRules[nChannelId].pRuleBuf = NULL;
	int nBufLen = (sizeof(CFG_RULE_INFO) + m_nMaxRuleStructSize) * m_nMaxRuleNum;
	m_gChannelRules[nChannelId].pRuleBuf = new char[nBufLen];
	memset(m_gChannelRules[nChannelId].pRuleBuf, 0, nBufLen);
	m_gChannelRules[nChannelId].nRuleLen = nBufLen;
	m_gChannelRules[nChannelId].nRuleCount = 0;
	
	int nHaveReadLen = 0;
	DWORD dwRootData = 0;
	DWORD dwChildData = 0;
	HTREEITEM hRootItem = m_ctRuleTree.GetRootItem();
	while(hRootItem != NULL && nHaveReadLen < m_gChannelRules[nChannelId].nRuleLen)
	{
		dwRootData = MyGetItemData(hRootItem);
		HTREEITEM hChileNode = m_ctRuleTree.GetChildItem(hRootItem);
		while(hChileNode != NULL && nHaveReadLen < m_gChannelRules[nChannelId].nRuleLen)
		{
			dwChildData = MyGetItemData(hChileNode);
			CFG_RULE_INFO* pRuleInfo = (CFG_RULE_INFO*)(m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen);
			switch (dwRootData)
			{
			case EVENT_IVS_TRAFFICGATE:
				{
					pRuleInfo->dwRuleType = dwRootData; 
					pRuleInfo->nRuleSize = sizeof(CFG_TRAFFICGATE_INFO);
					nHaveReadLen += sizeof(CFG_RULE_INFO);
					
					memcpy(m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen, 
						(CFG_TRAFFICGATE_INFO*)dwChildData, sizeof(CFG_TRAFFICGATE_INFO));
					nHaveReadLen += sizeof(CFG_TRAFFICGATE_INFO);
				}
				break;
			case EVENT_IVS_CROSSLINEDETECTION:
				{
					pRuleInfo->dwRuleType = dwRootData; 
					pRuleInfo->nRuleSize = sizeof(CFG_CROSSLINE_INFO);
					nHaveReadLen += sizeof(CFG_RULE_INFO);
					
					memcpy(m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen, 
						(CFG_CROSSLINE_INFO*)dwChildData, sizeof(CFG_CROSSLINE_INFO));

					CFG_CROSSLINE_INFO* pInfo = (CFG_CROSSLINE_INFO*)dwChildData;
					if (NULL != pInfo)
					{
#ifdef _DEBUG
						CString s;
						s.Format("nDetectLinePoint: %d (%d,%d) (%d,%d) !\n",
							pInfo->nDetectLinePoint,pInfo->stuDetectLine[0].nX,
							pInfo->stuDetectLine[0].nY,pInfo->stuDetectLine[1].nX,
							pInfo->stuDetectLine[1].nY);
						OutputDebugString(s);
#endif
					}
					nHaveReadLen += sizeof(CFG_CROSSLINE_INFO);
				}
				break;
			case EVENT_IVS_CROSSREGIONDETECTION:
				{
					pRuleInfo->dwRuleType = dwRootData; 
					pRuleInfo->nRuleSize = sizeof(CFG_CROSSREGION_INFO);
					nHaveReadLen += sizeof(CFG_RULE_INFO);
					
					memcpy(m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen, 
						(CFG_CROSSREGION_INFO*)dwChildData, sizeof(CFG_CROSSREGION_INFO));
					nHaveReadLen += sizeof(CFG_CROSSREGION_INFO);
				}
				break;
			case EVENT_IVS_FACEDETECT:
				{
					pRuleInfo->dwRuleType = dwRootData; 
					pRuleInfo->nRuleSize = sizeof(CFG_FACEDETECT_INFO);
					nHaveReadLen += sizeof(CFG_RULE_INFO);
					
					memcpy(m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen, 
						(CFG_FACEDETECT_INFO*)dwChildData, sizeof(CFG_FACEDETECT_INFO));
					nHaveReadLen += sizeof(CFG_FACEDETECT_INFO);
				}
				break;
			case EVENT_IVS_WANDERDETECTION:
				{
					pRuleInfo->dwRuleType = dwRootData; 
					pRuleInfo->nRuleSize = sizeof(CFG_WANDER_INFO);
					nHaveReadLen += sizeof(CFG_RULE_INFO);
					
					memcpy(m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen, 
						(CFG_WANDER_INFO*)dwChildData, sizeof(CFG_WANDER_INFO));
					nHaveReadLen += sizeof(CFG_WANDER_INFO);
				}
				break;
			case EVENT_IVS_PASTEDETECTION:
				{
					pRuleInfo->dwRuleType = dwRootData; 
					pRuleInfo->nRuleSize = sizeof(CFG_PASTE_INFO);
					nHaveReadLen += sizeof(CFG_RULE_INFO);
					
					memcpy(m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen, 
						(CFG_PASTE_INFO*)dwChildData, sizeof(CFG_PASTE_INFO));
					nHaveReadLen += sizeof(CFG_PASTE_INFO);
				}
			case EVENT_IVS_RIOTERDETECTION:
				{
					pRuleInfo->dwRuleType = dwRootData; 
					pRuleInfo->nRuleSize = sizeof(CFG_RIOTER_INFO);
					nHaveReadLen += sizeof(CFG_RULE_INFO);
					
					memcpy(m_gChannelRules[nChannelId].pRuleBuf + nHaveReadLen, 
						(CFG_RIOTER_INFO*)dwChildData, sizeof(CFG_RIOTER_INFO));
					nHaveReadLen += sizeof(CFG_RIOTER_INFO);
				}
				break;
			default:
				break;
			}

			hChileNode = m_ctRuleTree.GetNextItem(hChileNode,TVGN_NEXT);

			m_gChannelRules[nChannelId].nRuleCount++;
		}

		hRootItem = m_ctRuleTree.GetNextItem(hRootItem,TVGN_NEXT);
	}

	return TRUE;
}


DWORD CConfigRules::MyGetItemData(HTREEITEM hItem)
{
	DWORD dwRet;
	if (hItem == 0)
	{
		return 0;
	}
	EnterCriticalSection(&m_csRuleTree);
	//dwRet = m_ctRuleTree.GetItemData(hItem);
	std::map<HTREEITEM,DWORD>::iterator it = m_mapTreeData.find(hItem);
	if (it != m_mapTreeData.end())
	{
		dwRet =it->second;
	}
	LeaveCriticalSection(&m_csRuleTree);
	
	return dwRet;
}
BOOL CConfigRules::MySetItemData(HTREEITEM hItem, DWORD dwData)
{
	BOOL bRet = TRUE;
	if (hItem == 0)
	{
		return 0;
	}
	EnterCriticalSection(&m_csRuleTree);
	std::map<HTREEITEM,DWORD>::iterator it = m_mapTreeData.find(hItem);
	if (it != m_mapTreeData.end())
	{
		it->second = dwData;
		bRet = 1;
	}
	else
	{
		m_mapTreeData.insert(std::map<HTREEITEM,DWORD>::value_type(hItem,dwData));
		bRet = 2;
	}
	//BOOL bRet = m_ctRuleTree.SetItemData(hItem,dwData);
	LeaveCriticalSection(&m_csRuleTree);

	return bRet;
}

BOOL CConfigRules::MyDeleteItem(HTREEITEM hItem)
{
	if (hItem == 0)
	{
		return 0;
	}
	EnterCriticalSection(&m_csRuleTree);
	std::map<HTREEITEM,DWORD>::iterator it = m_mapTreeData.find(hItem);
	if (it != m_mapTreeData.end())
	{
		m_mapTreeData.erase(it);
	}
	BOOL bRet = m_ctRuleTree.DeleteItem(hItem);
	LeaveCriticalSection(&m_csRuleTree);

	return bRet;
}

HTREEITEM CConfigRules::MyInsertItem(LPCTSTR lpszItem, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	if (lpszItem == 0 || hParent == 0|| hInsertAfter == 0)
	{
		return 0;
	}
	EnterCriticalSection(&m_csRuleTree);
	HTREEITEM hItemRet = m_ctRuleTree.InsertItem(lpszItem,hParent,hInsertAfter);
	LeaveCriticalSection(&m_csRuleTree);
	
	return hItemRet;
}