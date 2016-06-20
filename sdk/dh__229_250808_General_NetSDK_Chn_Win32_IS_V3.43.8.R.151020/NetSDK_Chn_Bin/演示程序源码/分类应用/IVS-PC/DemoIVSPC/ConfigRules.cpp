// ConfigRules.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSPC.h"
#include "ConfigRules.h"
#include "DemoIVSPCDlg.h"
#include "GlobalDef.h"
#include "IvsRulePreview.h"
#include "SubDlgNumberStatInfo.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CConfigRules::CConfigRules(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigRules::IDD, pParent),
	m_nDrawPortNum(100),
	m_pIvsRulePreview(NULL),
	m_nDrawType(-1)
{
	
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
	ON_MESSAGE(WM_RULE_DRAW, OnRuleDarwHint)
	ON_MESSAGE(WM_UPDATE_NOTIFY, OnUpdateNotify)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_CFGRULE_EDT_RULENAME, CConfigRules::OnEnChangeCfgruleEdtRulename)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

/// 拷贝人数统计信息
BOOL CConfigRules::CopyNumberStatInfo(const CFG_ANALYSERULES_INFO *pInput, CFG_ANALYSERULES_INFO *pOutput)
{
	if (pInput == NULL || pOutput == NULL)
	{
		return FALSE;
	}
	int nReadBufLen = 0;
	for (int nIndexRule = 0; nIndexRule <pInput->nRuleCount; nIndexRule++)
	{
		if (nReadBufLen > pInput->nRuleLen)
		{
			break;
		}
		CFG_RULE_INFO *pRuleHeaderInfo = (CFG_RULE_INFO *)(pInput->pRuleBuf + nReadBufLen);
		nReadBufLen += sizeof(CFG_RULE_INFO);
		if (NULL == pInput)
		{
			break;
		}
		if (pRuleHeaderInfo->dwRuleType == EVENT_IVS_NUMBERSTAT &&
			pRuleHeaderInfo->nRuleSize  == sizeof(CFG_NUMBERSTAT_INFO))
		{
			CFG_RULE_INFO *pOutputHeaderInfo = (CFG_RULE_INFO *)(pOutput->pRuleBuf);
			if (pOutputHeaderInfo->dwRuleType == EVENT_IVS_NUMBERSTAT &&
				pOutputHeaderInfo->nRuleSize  == sizeof(CFG_NUMBERSTAT_INFO))
			{
				memcpy(pOutput->pRuleBuf, pInput->pRuleBuf + nReadBufLen, sizeof(CFG_NUMBERSTAT_INFO));
			    break;
			}
		}
		nReadBufLen += pRuleHeaderInfo->nRuleSize;
	}
	return TRUE;
}
// CConfigRules message handlers
afx_msg LRESULT CConfigRules::OnUpdateNotify(WPARAM wParam, LPARAM lParam)
{
	int nCtrlID =(int)wParam;
	CFG_NUMBERSTAT_INFO *pNumberStat = NULL;
	HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
	if (hItem)
	{
		RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
		if (!pRuleStruct)
		{
			return 0;
		}
		if (!pRuleStruct->pRuleBuf)
		{
			MessageBox(ConvertString(_T("Select RuleType First!")), ConvertString("Prompt"));
			return 0;
		}
		switch (pRuleStruct->RuleInfo.dwRuleType)
		{
		case EVENT_IVS_NUMBERSTAT:
			pNumberStat = (CFG_NUMBERSTAT_INFO*)pRuleStruct->pRuleBuf;
			break;
		default:
			MessageBox(ConvertString(_T("No such rule type!")), ConvertString("Prompt"));
			break;
		}
	}
	else
	{
		return 0;
	}
	switch(nCtrlID)
	{
	case IDC_EDIT_PERIOD:
		{
			if (pNumberStat)
			{
				pNumberStat->nPeriod = (int)lParam;
			}
		}
		break;
	case IDC_EDIT_UPPERLIMIT:
		{
			if (pNumberStat)
			{
				pNumberStat->nUpperLimit = (int)lParam;
			}
		}
		break;
	case IDC_EDIT_INTERVAL:
		{
			if (pNumberStat)
			{
				pNumberStat->nRecordInterval = (int)lParam;
			}
		}
		break;
	default:
		break;
	}
	return 0;
}
afx_msg LRESULT CConfigRules::OnRuleDarwHint(WPARAM wParam, LPARAM lParam)
{
	eRuleState eHint = (eRuleState)lParam;
	if (eHint == eRegionStart)
	{
		///开始划区域，提示
		if (m_pIvsRulePreview)
		{
			m_pIvsRulePreview->InitState(eRegionStart);
			HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
			if (!hItem)
			{
				return 0;
			}

			RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
			if (!pRuleStruct)
			{
				return 0;
			}
			CFG_ANALYSERULES_INFO stuRuleInfo = {0};
			stuRuleInfo.pRuleBuf = new char[pRuleStruct->RuleInfo.nRuleSize + sizeof(CFG_RULE_INFO)];
			if (stuRuleInfo.pRuleBuf)
			{
				memcpy(stuRuleInfo.pRuleBuf, &pRuleStruct->RuleInfo, sizeof(CFG_RULE_INFO));
				memcpy(stuRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO), pRuleStruct->pRuleBuf, pRuleStruct->RuleInfo.nRuleSize);
				stuRuleInfo.nRuleCount = 1;
				stuRuleInfo.nRuleLen = pRuleStruct->RuleInfo.nRuleSize + sizeof(CFG_RULE_INFO);
				m_pIvsRulePreview->InitDarwData(m_nDrawPortNum, &stuRuleInfo);
				delete []stuRuleInfo.pRuleBuf;
				stuRuleInfo.pRuleBuf = NULL;
			}
			m_nDrawType = 0;
		}

	}
	else if ( eHint == eRegionEnd)
	{
		///划区域结束，提示
		MessageBox(ConvertString("Finish to draw region!"), ConvertString("Prompt"));
		if (m_pIvsRulePreview)
		{
			CFG_NUMBERSTAT_INFO *pNumberStatInfo = m_pIvsRulePreview->GetNumberStatInfo();
			HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
			if (!hItem)
			{
				return 0;
			}

			RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
			if (!pRuleStruct)
			{
				return 0;
			}
			if (pRuleStruct->RuleInfo.dwRuleType == EVENT_IVS_NUMBERSTAT  && 
				pRuleStruct->RuleInfo.nRuleSize == sizeof(CFG_NUMBERSTAT_INFO))
			{
				memcpy(pRuleStruct->pRuleBuf, pNumberStatInfo, sizeof(CFG_NUMBERSTAT_INFO));
			}
		}
		m_nDrawType = -1;
		
	}
	else if ( eHint == eDirctionStart)
	{
		///开始划方向，提示
		if (m_pIvsRulePreview)
		{
			m_pIvsRulePreview->InitState(eDirctionStart);
			HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
			if (!hItem)
			{
				return 0;
			}

			RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
			if (!pRuleStruct)
			{
				return 0;
			}
			CFG_ANALYSERULES_INFO stuRuleInfo = {0};
			stuRuleInfo.pRuleBuf = new char[pRuleStruct->RuleInfo.nRuleSize + sizeof(CFG_RULE_INFO)];
			if (stuRuleInfo.pRuleBuf)
			{
				memcpy(stuRuleInfo.pRuleBuf, &pRuleStruct->RuleInfo, sizeof(CFG_RULE_INFO));
				memcpy(stuRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO), pRuleStruct->pRuleBuf, pRuleStruct->RuleInfo.nRuleSize);
				stuRuleInfo.nRuleCount = 1;
				stuRuleInfo.nRuleLen = pRuleStruct->RuleInfo.nRuleSize + sizeof(CFG_RULE_INFO);
				m_pIvsRulePreview->InitDarwData(m_nDrawPortNum, &stuRuleInfo);
				delete []stuRuleInfo.pRuleBuf;
				stuRuleInfo.pRuleBuf = NULL;
			}
		}
		m_nDrawType = 1;
	}
	else if ( eHint == eDirctionEnd )
	{
		///划方向结束，提示
		MessageBox(ConvertString("Finish to draw line!"), ConvertString("Prompt"));
		if (m_pIvsRulePreview)
		{
			CFG_NUMBERSTAT_INFO *pNumberStatInfo = m_pIvsRulePreview->GetNumberStatInfo();
			HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
			if (!hItem)
			{
				return 0;
			}

			RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
			if (!pRuleStruct)
			{
				return 0;
			}
			if (pRuleStruct->RuleInfo.dwRuleType == EVENT_IVS_NUMBERSTAT  && 
				pRuleStruct->RuleInfo.nRuleSize == sizeof(CFG_NUMBERSTAT_INFO))
			{
				memcpy(pRuleStruct->pRuleBuf, pNumberStatInfo, sizeof(CFG_NUMBERSTAT_INFO));
			}
		}
		m_nDrawType = -1;
	}
	return 0;
}
/*
 *	
 */
void CConfigRules::InitConfigRulesDlg(int nChannel)
{
	if (nChannel == -1)
	{
		UninitConfigRulesDlg();
		return;
	}

	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}	

	TCHAR szChnName[32] = {0};
	_sntprintf(szChnName, _countof(szChnName) * sizeof(TCHAR), ConvertString(_T("Channel%02d")), nChannel + 1);
	SetDlgItemText(IDC_CFGRULE_EDT_CHANNELNAME, szChnName);
    
	//初始化combobox控件
	int nChn = 0;
	int nSupportedRulesNum = 0;
	CFG_CAP_ANALYSE_INFO* pCapInfo = pMainDlg->GetCapAnalyseInfo(nChannel);
	if (!pCapInfo)
	{
		return;
	}
	int i = 0;
	CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobal = pMainDlg->GetAnalyseGlobalInfo(pMainDlg->GetCurrentChannel());
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

	if (!nSupportedRulesNum)
	{
		return;
	}

	DWORD* pdwRuleType = new DWORD[nSupportedRulesNum];
	ZeroMemory(pdwRuleType, sizeof(DWORD) * nSupportedRulesNum);
	for(int j = 0; j < nSupportedRulesNum; j++)
	{
		pdwRuleType[j] = pCapInfo->stSupportScenes.stScenes[i].stSpportRules[j].dwSupportedRule;
	}

	for (i = 0; i < nSupportedRulesNum; i++)
	{
		switch(pdwRuleType[i])
		{
		case EVENT_IVS_NUMBERSTAT:
            nChn = m_cmbRuleType.AddString(ConvertString("NumberState"));
			m_cmbRuleType.SetItemData(nChn, EVENT_IVS_NUMBERSTAT);
			break;
		default:
			break;
		}
	}

	delete []pdwRuleType;
	pdwRuleType = NULL;
	
	InitRule(pMainDlg, nChannel);
	CreateViewWindow();
}

void CConfigRules::CreateViewWindow()
{
	/// 创建规则绘制图像
	if (m_pIvsRulePreview)
	{
		delete m_pIvsRulePreview;
		m_pIvsRulePreview = NULL;
	}
	m_pIvsRulePreview = new CIvsRulePreview();
	if (NULL == m_pIvsRulePreview)
	{
		return ;
	}
	CRect rt;
	GetDlgItem(IDC_CFGRULE_STATIC_PREVIEW)->GetWindowRect(&rt);
	ScreenToClient(&rt);
	m_pIvsRulePreview->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0),this, 5001);
	m_pIvsRulePreview->MoveWindow(&rt);
	m_pIvsRulePreview->ShowWindow(SW_SHOW);
};

void CConfigRules::UninitConfigRulesDlg()
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
}

void CConfigRules::ShowSubRuleDlg(int nRuleType)
{
	m_pSubNumberStatInfo->ShowWindow(SW_HIDE);
	switch(nRuleType)
	{
	case EVENT_IVS_NUMBERSTAT:
		m_pSubNumberStatInfo->ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}

void CConfigRules::ShowSubRuleInfo(int nRuleType, const RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || !pRuleStruct->pRuleBuf)
	{
		return;
	}

	CFG_NUMBERSTAT_INFO*  pNumberStatInfo = NULL;
	switch(nRuleType)
	{
	case EVENT_IVS_NUMBERSTAT:
		pNumberStatInfo = (CFG_NUMBERSTAT_INFO*)pRuleStruct->pRuleBuf;
		SetDlgItemText(IDC_CFGRULE_EDT_RULENAME, pNumberStatInfo->szRuleName);
		m_pSubNumberStatInfo->ShowRuleInfo(pRuleStruct);
		break;
	default:
		break;
	}
}

void CConfigRules::ShowPreview(LONG lLoginHanlde, int nChannel)
{
	if (!lLoginHanlde || nChannel < 0)
	{
		return;
	}
	
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		if (pMainDlg->GetLoginHandle())
		{
			if (pMainDlg->GetRealPlayHandle())
			{
				::CLIENT_StopRealPlay(pMainDlg->GetRealPlayHandle());
				g_PlayAPI.PLAY_Stop(g_nPlayPort);
				g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				pMainDlg->SetRealPlayHandel(0);
			}
			
			LLONG m_lPlayID = 0;
			HWND hWnd = GetDlgItem(IDC_CFGRULE_STATIC_PREVIEW)->GetSafeHwnd();
			NET_DEVICEINFO* pDevInfo = pMainDlg->GetDevInfo();
			int nChnCount = 0;
			if (pDevInfo)
			{
				nChnCount = pDevInfo->byChanNum;
			}
			
			//Enable stream
			BOOL bOpenRet = g_PlayAPI.PLAY_OpenStream(g_nPlayPort, 0, 0, 1024 * 900);
			if(bOpenRet)
			{	
				// 从码流中提取智能分析信息
				BOOL bRet = FALSE;
				
				bRet = g_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, CIvsRulePreview::DrawIvsRuleCfgProc, (DWORD)this);
				if (!bRet)
				{
					MessageBox(ConvertString("PLAY_RigisterDrawFun failed!"), ConvertString("Prompt"));
				}
				//Begin play 
				BOOL bPlayRet = g_PlayAPI.PLAY_Play(g_nPlayPort, hWnd);
				if(bPlayRet)
				{
					//Real-time play 
					m_lPlayID = CLIENT_RealPlay(pMainDlg->GetLoginHandle(), nChannel, 0);
					if(0 != m_lPlayID)
					{
						pMainDlg->SetRealPlayHandel(m_lPlayID);
						//Callback monitor data and then save 
						CLIENT_SetRealDataCallBackEx(m_lPlayID, RealDataCallBackEx, (LDWORD)this, 0x1f);
					}
					else
					{
						g_PlayAPI.PLAY_Stop(g_nPlayPort);
						g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
						int x = ::CLIENT_GetLastError();
						MessageBox(ConvertString("Fail to play!"), ConvertString("Prompt"));
					}
				}
				else
				{
						g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				}
			}
		}
	}
}

void CConfigRules::ClosePreview(LONG lRealPlayHandle)
{
	if (!lRealPlayHandle)
	{
		return;
	}
	
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		if (pMainDlg->GetRealPlayHandle())
		{
			::CLIENT_StopRealPlay(pMainDlg->GetRealPlayHandle());
			g_PlayAPI.PLAY_Stop(g_nPlayPort);
			g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			GetDlgItem(IDC_CFGRULE_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->SetRealPlayHandel(0);
		}
	}
}

void CConfigRules::DrawIvsInfoRulesProc(long nPort,HDC hdc,LONG nUser)
{
	CConfigRules* pRulesInfo = (CConfigRules*)nUser;
	HTREEITEM hItem = pRulesInfo->m_treeRuleList.GetSelectedItem();
	if (!hItem)
	{
		return;
	}

	RuleStruct* pRuleStruct = (RuleStruct*)pRulesInfo->m_treeRuleList.GetItemData(hItem);
	if (!pRulesInfo)
	{
		return;
	}
	int nErr = 0;
	HWND hWnd = pRulesInfo->GetDlgItem(IDC_CFGRULE_STATIC_PREVIEW)->GetSafeHwnd();
	nErr = DRAW_Draw(pRulesInfo->GetDrawPortNum(), hdc, hWnd, 0);
	if(nErr < 0)
	{
		return;
	}
}

void CConfigRules::SetRuleInfo(int nRuleType, char* pRuleStructBuf, int nLen)
{
	if (!pRuleStructBuf)
	{
		return;
	}

	switch(nRuleType)
	{
	case EVENT_IVS_NUMBERSTAT:
	default:
		break;
	}
}
 
BOOL CConfigRules::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	m_treeRuleList.ModifyStyle( TVS_CHECKBOXES, 0 );
	m_treeRuleList.ModifyStyle( 0, TVS_CHECKBOXES );
	
	DRAW_Startup();
	
	int nErr = DRAW_Open(m_nDrawPortNum);

	// TODO: Add extra initialization here
	CRect rt;
	GetClientRect(&rt);
	rt.left = 526 / 2 * 3;
	rt.top = 64 / 2 * 3;
	rt.right = rt.left + 106 / 2 * 3;
	rt.bottom = rt.top + 288 / 2 * 3;

	m_pSubNumberStatInfo = new CSubDlgNumberStatInfo;
	if (NULL == m_pSubNumberStatInfo)
	{
		return FALSE;
	}
	m_pSubNumberStatInfo->Create(CSubDlgNumberStatInfo::IDD, this);
	m_pSubNumberStatInfo->InitConfig();
	m_pSubNumberStatInfo->MoveWindow(&rt, TRUE);
	m_pSubNumberStatInfo->ShowWindow(SW_HIDE);
	return TRUE; 
}
/*
 *	选择组合框下拉菜单，显示对应规则子窗口
 */
void CConfigRules::OnSelchangeCfgruleCmbRuletype() 
{
	// TODO: Add your control notification handler code here
	//选择combobox选项，显示对应的规则配置子窗口
 	int nChn = m_cmbRuleType.GetCurSel();
	int nRuleType = m_cmbRuleType.GetItemData(nChn);
	ShowSubRuleDlg(nRuleType);
}
/*
 *	添加规则
 */
void CConfigRules::OnCfgruleBtnAddrule() 
{
	// TODO: Add your control notification handler code here
	//先判断当前规则总数是否满
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	CFG_CAP_ANALYSE_INFO* pCap = pMainDlg->GetCapAnalyseInfo(pMainDlg->GetCurrentChannel());
	if (!pCap)
	{
		return;
	}

	if (pCap->nMaxRules <= (int)m_treeRuleList.GetCount())
	{
		MessageBox(ConvertString("Can't add rule!"), ConvertString("Prompt"));
		return;
	}

	//新增节点
	//根据当前界面上的信息，配置给新添加的规则
	CString strName;
	GetDlgItemText(IDC_CFGRULE_EDT_RULENAME, strName);

	HTREEITEM hItem = m_treeRuleList.InsertItem(strName);
	if (!hItem)
	{
		return;
	}

	RuleStruct* pRuleStruct = new RuleStruct;
	if (!pRuleStruct)
	{
		return;
	}

	int nChn = m_cmbRuleType.GetCurSel();
	if (nChn < 0)
	{
		delete []pRuleStruct;
		pRuleStruct = NULL;
		return;
	}

	int nType = m_cmbRuleType.GetItemData(nChn);
	int nSize = g_getStructSize(nType);

	pRuleStruct->RuleInfo.dwRuleType = nType;
	pRuleStruct->RuleInfo.nRuleSize = nSize;

	pRuleStruct->pRuleBuf = new char[nSize];
	if (!pRuleStruct)
	{
		delete []pRuleStruct;
		pRuleStruct = NULL;
		return;
	}
	ZeroMemory(pRuleStruct->pRuleBuf, nSize);

	//ToDo填充规则信息到结构体
	SetRuleInfo(nType, pRuleStruct->pRuleBuf, nSize);

	m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);
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

	int nItemCount = m_treeRuleList.GetCount();
	if (nItemCount == 1)
	{
		MessageBox(ConvertString("Rule must be greater than 0!"), ConvertString("Prompt"));
		return ;
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

	DRAW_Reset(m_nDrawPortNum, DRAW_RULE);

	ShowSubRuleDlg(-1);
}
/*
 *	擦除画面上的规则线条，重新绘图
 */
void CConfigRules::OnCfgruleBtnRedraw() 
{
	// TODO: Add your control notification handler code here
	if (m_nDrawType == 0)
	{
		OnRuleDarwHint(NULL, (LPARAM)eRegionStart);
	}
	else if (m_nDrawType == 1)
	{
		OnRuleDarwHint(NULL, (LPARAM)eDirctionStart);
	}
	else
	{
		MessageBox(ConvertString(_T("The Draw is finished, you need not redraw it again!")), ConvertString("Prompt"));
	}
}
/*
 *	获取规则信息并更新界面显示
 */
void CConfigRules::OnCfgruleBtnGet() 
{
	// TODO: Add your control notification handler code here
	if (m_nDrawType == 0 || m_nDrawType ==1)
	{
		if (m_cmbRuleType.GetCurSel() == -1)
		{
			MessageBox(ConvertString(_T("Please select the rule type first!")), ConvertString("Prompt"));
		} 
		else
		{
			MessageBox(ConvertString(_T("Please finish draw rule first!")), ConvertString("Prompt"));
		}
		return;
	}
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	UninitConfigRulesDlg();

	//pMainDlg->RefreshGlobalInfo();
	pMainDlg->RefreshRuleInfo();

	InitConfigRulesDlg(pMainDlg->GetCurrentChannel());

	//m_pSubNumberStatInfo->ShowWindow(SW_HIDE);
}


/*
 *	将当前界面中包含的信息配置到设备上
 */
void CConfigRules::OnCfgruleBtnSet() 
{

	// TODO: Add your control notification handler code here
	if (m_nDrawType == 0 || m_nDrawType ==1)
	{
		if (m_cmbRuleType.GetCurSel() == -1)
		{
			MessageBox(ConvertString(_T("Please select the rule type first!")), ConvertString("Prompt"));
		} 
		else
		{
			MessageBox(ConvertString(_T("Please finish draw rule first!")), ConvertString("Prompt"));
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

	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	int iCurChn = pMainDlg->GetCurrentChannel();
	CFG_ANALYSERULES_INFO* pRuleInfo = pMainDlg->GetAnalyseRulesInfo(iCurChn);
	if (pRuleInfo)
	{
		pRuleInfo->nRuleCount = 0;
		pRuleInfo->nRuleLen = 0;

		if (pRuleInfo->pRuleBuf)
		{
			/////**********************************/////
			///测试内存泄露用
			//delete []pRuleInfo->pRuleBuf;
			pRuleInfo->pRuleBuf = new char[nTotleLen];
			if (!pRuleInfo->pRuleBuf)
			{
				return;
			}
		}
	}
	else
	{
		if (pRuleInfo->pRuleBuf)
		{
			delete []pRuleInfo->pRuleBuf;
			pRuleInfo->pRuleBuf = NULL;
		}

		if (!pRuleInfo->pRuleBuf)
		{
			pRuleInfo->pRuleBuf = new char[nTotleLen];
			if (!pRuleInfo->pRuleBuf)
			{
				return;
			}
		}
	}

	
	ZeroMemory(pRuleInfo->pRuleBuf, nTotleLen);

	//将规则列表的信息填入
	hItem = m_treeRuleList.GetRootItem();
	int iTmp = 0;
	char* pTmp = pRuleInfo->pRuleBuf;

	while(hItem)
	{
		RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
		if (pRuleStruct)
		{
			CFG_NUMBERSTAT_INFO* pComRule = (CFG_NUMBERSTAT_INFO*)pRuleStruct->pRuleBuf;
			if (pComRule)
			{
				if (m_treeRuleList.GetCheck(hItem))
				{
					pComRule->bRuleEnable = true;
				} 
				else
				{
					pComRule->bRuleEnable = false;
				}
			}

			memcpy(pTmp + iTmp, &pRuleStruct->RuleInfo, sizeof(CFG_RULE_INFO));
			iTmp += sizeof(CFG_RULE_INFO);

			memcpy(pTmp + iTmp, pRuleStruct->pRuleBuf, pRuleStruct->RuleInfo.nRuleSize);
			iTmp += pRuleStruct->RuleInfo.nRuleSize;

			pRuleInfo->nRuleCount++;
		}

		hItem = m_treeRuleList.GetNextSiblingItem(hItem);
	}

	pRuleInfo->nRuleLen = iTmp;

	//////////////////////////////////////////////////////////////////////////

	char szOutBuf[32 * 1024] = {0};

	BOOL bRet = ::CLIENT_PacketData(CFG_CMD_ANALYSERULE, pRuleInfo,
										sizeof(CFG_ANALYSERULES_INFO), szOutBuf, 32 *1024);
	if (!bRet)
	{
		return;
	}

	int iErr = 0;
	int iRestart = 0;

	bRet = ::CLIENT_SetNewDevConfig(pMainDlg->GetLoginHandle(), CFG_CMD_ANALYSERULE,
										pMainDlg->GetCurrentChannel(), szOutBuf, 32 * 1024, &iErr, &iRestart);
	if (bRet)
	{
		MessageBox(ConvertString(_T("Set RuleInfo Successfully!")), ConvertString("Prompt"));
	}
	else
	{
		MessageBox(ConvertString(_T("Set RuleInfo Failed!")), ConvertString("Prompt"));
	}
	
}
/*
 *	选择树控件节点，显示对应子窗口和规则信息
 */
void CConfigRules::OnDblclkCfgruleTreeRulelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeRuleList.GetSelectedItem();
	if (!hItem)
	{
		*pResult = 0;
		return;
	}
	
	InitRuleInfo(hItem);
	
	*pResult = 0;
}

void CConfigRules::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	if (m_pIvsRulePreview)
	{
		if (m_pIvsRulePreview->GetSafeHwnd())
		{
			m_pIvsRulePreview->DestroyWindow();
		}

		delete m_pIvsRulePreview;
		m_pIvsRulePreview = NULL;
	}
	if (m_pSubNumberStatInfo)
	{
		if (m_pSubNumberStatInfo->GetSafeHwnd())
		{
			m_pSubNumberStatInfo->DestroyWindow();
		}

		delete m_pSubNumberStatInfo;
		m_pSubNumberStatInfo = NULL;
	}
	DRAW_Close(m_nDrawPortNum);
	DRAW_Cleanup();

	UninitConfigRulesDlg();
}

CWnd *CConfigRules::GetDrawRuleHandle()
{
	CWnd* hWnd = NULL;
	if (m_pIvsRulePreview)
	{
		hWnd = m_pIvsRulePreview;
	}
	return hWnd;
}

void CConfigRules::OnEnChangeCfgruleEdtRulename()
{
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
			MessageBox(ConvertString(_T("Select RuleType First!")), ConvertString("Prompt"));
			return;
		}

		CFG_NUMBERSTAT_INFO *pNumberStat = NULL;

		switch (pRuleStruct->RuleInfo.dwRuleType)
		{
		case EVENT_IVS_NUMBERSTAT:
			pNumberStat = (CFG_NUMBERSTAT_INFO*)pRuleStruct->pRuleBuf;
			if (pNumberStat)
			{
				strncpy(pNumberStat->szRuleName, szName, _countof(szName));
			}
			break;
		default:
			MessageBox(ConvertString(_T("No such rule type!")), ConvertString("Prompt"));
			break;
		}
	}
}

void CConfigRules::InitRule(CDemoIVSPCDlg* pMainDlg, int nChannel)
{
	CFG_ANALYSERULES_INFO* pAnalyseRulesInfo = pMainDlg->GetAnalyseRulesInfo(nChannel);
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
	int nReadLen = 0;
	char* pszItem = NULL;
	HTREEITEM hItem = NULL;

	for (int i = 0; i < pAnalyseRulesInfo->nRuleCount; i++)
	{
		CFG_RULE_INFO* pRuleInfo = (CFG_RULE_INFO*)(pBuf + nReadLen);
		CFG_NUMBERSTAT_INFO *pNumberStat = NULL;
		RuleStruct* pRuleStruct = NULL;
		pRuleStruct = new RuleStruct;
		if (!pRuleStruct)
		{
			break;
		}
		ZeroMemory(pRuleStruct, sizeof(RuleStruct));

		switch(pRuleInfo->dwRuleType)
		{
		case EVENT_IVS_NUMBERSTAT:
			{
				pRuleStruct->pRuleBuf = new char[sizeof(CFG_NUMBERSTAT_INFO)];
				if (NULL == pRuleStruct->pRuleBuf)
				{
					delete pRuleStruct;
					pRuleStruct = NULL;
					break;
				}

				memcpy(&pRuleStruct->RuleInfo, pBuf + nReadLen, sizeof(CFG_RULE_INFO));
				memcpy(pRuleStruct->pRuleBuf, pBuf + nReadLen + sizeof(CFG_RULE_INFO), sizeof(CFG_NUMBERSTAT_INFO));

				nReadLen += sizeof(CFG_RULE_INFO) + sizeof(CFG_NUMBERSTAT_INFO);

				pszItem = ((CFG_NUMBERSTAT_INFO*)pRuleStruct->pRuleBuf)->szRuleName;
				hItem = m_treeRuleList.InsertItem(pszItem);
				pNumberStat = (CFG_NUMBERSTAT_INFO*)pRuleStruct->pRuleBuf;
				if (pNumberStat->bRuleEnable)
				{
					m_treeRuleList.SetCheck(hItem);
					m_treeRuleList.SelectItem(hItem);
				}
				m_treeRuleList.SetItemData(hItem, (DWORD)pRuleStruct);

				InitRuleInfo(hItem);
			}
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

	if (pAnalyseRulesInfo->nRuleCount == 1)
	{
		GetDlgItem(IDC_CFGRULE_BTN_ADDRULE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CFGRULE_BTN_DELRULE)->EnableWindow(FALSE);
	}
}

void CConfigRules::InitRuleInfo(HTREEITEM hItem)
{
	const RuleStruct* pRuleStruct = (RuleStruct*)m_treeRuleList.GetItemData(hItem);
	if (!pRuleStruct)
	{
		return;
	}

	BOOL bRet = FALSE;
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
		nErr = DRAW_SetPen(100, DRAW_RULE, DRAW_PEN_SOLID, PEN_WIDTH, RGB(0, 255, 0));
		if (0 != nErr)
		{
			return;
		}

		CFG_ANALYSERULES_INFO stuRuleInfo = {0};
		stuRuleInfo.pRuleBuf = new char[pRuleStruct->RuleInfo.nRuleSize + sizeof(CFG_RULE_INFO)];
		memcpy(stuRuleInfo.pRuleBuf, &pRuleStruct->RuleInfo, sizeof(CFG_RULE_INFO));
		memcpy(stuRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO), pRuleStruct->pRuleBuf, pRuleStruct->RuleInfo.nRuleSize);
		stuRuleInfo.nRuleCount = 1;
		stuRuleInfo.nRuleLen = pRuleStruct->RuleInfo.nRuleSize + sizeof(CFG_RULE_INFO);

		DRAW_Reset(100, DRAW_RULE);
		nErr = DRAW_InputRuleData(100, 0, (unsigned char*)&stuRuleInfo, 0);
		if (nErr < 0)
		{
			return;
		}

		delete []stuRuleInfo.pRuleBuf;
		stuRuleInfo.pRuleBuf = NULL;

		ShowSubRuleDlg(pRuleStruct->RuleInfo.dwRuleType);
		ShowSubRuleInfo(pRuleStruct->RuleInfo.dwRuleType, pRuleStruct);
	}
}
