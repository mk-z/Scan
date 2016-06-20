// ConfigModule.cpp : implementation file
//

#include "stdafx.h"
#include "demoIVSPC.h"
#include "ConfigModule.h"
#include "DemoIVSPCDlg.h"
#include "IvsModulePreview.h"
#include "TargetFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CConfigModule::CConfigModule(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigModule::IDD, pParent)
	, m_pIvsModulePreview(NULL)
	, m_bAddModule(false)
	, m_bAddDetect(false)
{
	
}


void CConfigModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigModule)
	DDX_Control(pDX, IDC_CFGMOD_CMB_OBJTYPE, m_cmbObjType);
	DDX_Control(pDX, IDC_CFGMOD_SLID_SENSI, m_ctrlSlidSensi);
	DDX_Control(pDX, IDC_CFGMOD_TREE_TRACKREGION, m_treeTrackRegion);
	DDX_Control(pDX, IDC_CFGMOD_TREE_MODLIST, m_treeModuleList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigModule, CDialog)
	//{{AFX_MSG_MAP(CConfigModule)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_ADDDETEC, OnCfgmodBtnAdddetec)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_ADDMOD, OnCfgmodBtnAddmod)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_DELMOD, OnCfgmodBtnDelmod)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_DELREGION, OnCfgmodBtnDelregion)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CFGMOD_BTN_GET, OnCfgmodBtnGet)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_SET, OnCfgmodBtnSet)
	ON_MESSAGE(WM_REGIONDONE, OnRegionDone)
	ON_NOTIFY(NM_CLICK, IDC_CFGMOD_TREE_MODLIST, OnClickCfgmodTreeModlist)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_FILTER, OnCfgmodBtnFilter)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CFGMOD_BTN_REDRAW, CConfigModule::OnBnClickedCfgmodBtnRedraw)
END_MESSAGE_MAP()
/*
 *	wParam:节点的句柄; lParam:节点要绑定的结构体;
 */
LRESULT CConfigModule::OnRegionDone(WPARAM wParam, LPARAM lParam)
{
	HTREEITEM hItemToBeDraw = (HTREEITEM)wParam;
	MTNODE* pNode = (MTNODE*)lParam;
	if (!hItemToBeDraw || !pNode)
	{
		return -1;
	}

	BOOL bRet = FALSE;
	HTREEITEM hItem = m_treeTrackRegion.GetRootItem();
	if (hItem != hItemToBeDraw)
	{
		hItem = m_treeTrackRegion.GetChildItem(hItem);
		while(hItem)
		{
			if (hItem == hItemToBeDraw)
			{
				bRet = TRUE;
				break;
			}
			hItem = m_treeTrackRegion.GetNextSiblingItem(hItem);
		}
	}
	else
	{
		bRet = TRUE;
	}

	if (!bRet)
	{
		MessageBox(ConvertString("Add new region failed!"), ConvertString("Prompt"));
		return -1;
	}

	//更新新添加的检测/排除区域节点
	MTNODE* pNodeTree = (MTNODE*)m_treeTrackRegion.GetItemData(hItem);
	if (pNodeTree)
	{
		pNodeTree->nNodeType = pNode->nNodeType;
		pNodeTree->nPointCount = pNode->nPointCount;
		memcpy(pNodeTree->CfgPolygon, pNode->CfgPolygon, sizeof(pNode->CfgPolygon));
	}
	//m_treeTrackRegion.SetItemData(hItem, (DWORD)lParam);

	//更新对应的模块节点
	hItem = m_treeModuleList.GetSelectedItem();
	if (!hItem)
	{
		return -1;
	}

	CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
	if (!pModuleInfo)
	{
		return -1;
	}

	if (pNode->nNodeType == DetectZone)
	{
		pModuleInfo->nDetectRegionPoint = pNode->nPointCount;
		memcpy(pModuleInfo->stuDetectRegion, 
			   pNode->CfgPolygon, 
			   sizeof(CFG_POLYGON) * pNode->nPointCount);
	}

	//更新绘图区域
	m_pIvsModulePreview->SetModuleInfo(pModuleInfo, FALSE);
	return 1;
}

BOOL CConfigModule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	CRect rt;
	GetDlgItem(IDC_CFGMOD_STATIC_PREVIEW)->GetWindowRect(&rt);
	ScreenToClient(&rt);

	m_pIvsModulePreview = new CIvsModulePreview;
	if (!m_pIvsModulePreview)
	{
		return TRUE;
	}

	m_pIvsModulePreview->Create(NULL,
								NULL,
								WS_CHILD | WS_VISIBLE,
								CRect(0, 0, 0, 0),
								this,
								5001);
	m_pIvsModulePreview->MoveWindow(&rt);
	m_pIvsModulePreview->ShowWindow(SW_SHOW);

	return TRUE;  
}

void CConfigModule::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pIvsModulePreview)
	{
		if (m_pIvsModulePreview->GetSafeHwnd())
		{
			m_pIvsModulePreview->DestroyWindow();
		}
		
		delete m_pIvsModulePreview;
		m_pIvsModulePreview = NULL;
	}

	clearTreeTrackRegion();
}
/*
 *	
 */
void CConfigModule::clearTreeModuleList()
{
	HTREEITEM hItem = m_treeModuleList.GetRootItem();
	while(hItem)
	{
		CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
		if (pModuleInfo)
		{
			//delete pModuleInfo;
			//pModuleInfo = NULL;
		}
		
		hItem = m_treeModuleList.GetNextSiblingItem(hItem);
	}
	
	m_treeModuleList.DeleteAllItems();
}
/*
 *	
 */
void CConfigModule::clearTreeTrackRegion()
{
	HTREEITEM hItem = m_treeTrackRegion.GetRootItem();
	while(hItem)
	{
		MTNODE* pNode = (MTNODE*)m_treeTrackRegion.GetItemData(hItem);
		if (pNode)
		{
			delete pNode;
			pNode = NULL;
		}
		
		HTREEITEM hItemChild = m_treeTrackRegion.GetChildItem(hItem);
		while(hItemChild)
		{
			pNode = (MTNODE*)m_treeTrackRegion.GetItemData(hItemChild);
			if (pNode)
			{
				delete pNode;
				pNode = NULL;
			}
			
			hItemChild = m_treeTrackRegion.GetNextSiblingItem(hItemChild);
		}
		
		hItem = m_treeTrackRegion.GetNextSiblingItem(hItem);
	}
	m_treeTrackRegion.DeleteAllItems();
}

void CConfigModule::EnableAddModuleOrDetect()
{
	if(m_treeModuleList.GetCount() >= 1)
	{
		GetDlgItem(IDC_CFGMOD_BTN_ADDMOD)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CFGMOD_BTN_ADDMOD)->EnableWindow(TRUE);
	}
	

	if (m_treeTrackRegion.GetCount() >= 1)
	{
		GetDlgItem(IDC_CFGMOD_BTN_ADDDETEC)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CFGMOD_BTN_ADDDETEC)->EnableWindow(TRUE);
	}
};


/*
 *	
 */
void CConfigModule::InitConfigModuleDlg(int nChannel)
{
	if (nChannel == -1)
	{
		UninitConfigModuleDlg();
		return;
	}
	
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}	
	
	//
	TCHAR szChnName[32] = {0};
	_sntprintf(szChnName, _countof(szChnName)*sizeof(TCHAR), _T("%s%02d"), ConvertString(_T("Channel")), nChannel + 1);
	SetDlgItemText(IDC_CFGMOD_EDT_CHANNELNAME, szChnName);

	//初始化模块树控件
	CFG_ANALYSEMODULES_INFO* pAnalyseModulesInfo = pMainDlg->GetAnalyseModuleInfo(nChannel);
	if(!pAnalyseModulesInfo)
	{
		return;
	}

	CFG_MODULE_INFO* pModuleInfo = NULL;
	TCHAR szItem[32] = {0};
	HTREEITEM hItem = 0;


    int i = 0;
	//////////////////////////////////////////////////////////////////////////
	//2012-06-08
	for (i = 0; i < pAnalyseModulesInfo->nMoudlesNum; i++)
	{
		//在模块列表树控件中添加模块节点
		_sntprintf(szItem, _countof(szItem)*sizeof(TCHAR), _T("%s%02d"), ConvertString(_T("Module")), i + 1);
		hItem = m_treeModuleList.InsertItem(szItem);
		m_treeModuleList.SelectItem(hItem);

		//pModuleInfo = new CFG_MODULE_INFO;
		//ZeroMemory(pModuleInfo, sizeof(CFG_MODULE_INFO));
		//memcpy(pModuleInfo, &pAnalyseModulesInfo->stuModuleInfo[i], sizeof(CFG_MODULE_INFO));
		pModuleInfo = &pAnalyseModulesInfo->stuModuleInfo[i];
		m_treeModuleList.SetItemData(hItem, (DWORD)&pAnalyseModulesInfo->stuModuleInfo[i]);

		ZeroMemory(szItem, _countof(szItem));

		if (!pModuleInfo->nDetectRegionPoint)
		{
			continue;
		}

		//在检测区域树控件中添加检测节点
		hItem = m_treeTrackRegion.InsertItem(ConvertString(_T("DetectRegion")));
		m_treeTrackRegion.SelectItem(hItem);
		MTNODE* pNode = new MTNODE;
		ZeroMemory(pNode, sizeof(MTNODE));
		pNode->nNodeType = DetectZone;
		pNode->nPointCount = pModuleInfo->nDetectRegionPoint;
		memcpy(&pNode->CfgPolygon, pModuleInfo->stuDetectRegion, sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
		m_treeTrackRegion.SetItemData(hItem, (DWORD)pNode);
	}

	hItem = m_treeTrackRegion.GetRootItem();
	if (hItem)
	{
		m_treeTrackRegion.Expand(hItem, TVE_EXPAND);
	}
	//////////////////////////////////////////////////////////////////////////

	//初始化轨迹树控件，显示第一个模块的信息
	hItem = m_treeModuleList.GetRootItem();
	if (hItem)
	{
		m_treeModuleList.SelectItem(hItem);
	}

	pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
	if (!pModuleInfo)
	{
		return;
	}
	
	CFG_CAP_ANALYSE_INFO* pCapInfo
		= (CFG_CAP_ANALYSE_INFO*)pMainDlg->GetCapAnalyseInfo(pMainDlg->GetCurrentChannel());
	if (!pCapInfo)
	{
		return;
	}
	
	int nObjTypeCnt = pCapInfo->nSupportedObjectTypeNum;
	for (i = 0; i < nObjTypeCnt; i++)
	{
		m_cmbObjType.InsertString(i, ConvertString(pCapInfo->szObjectTypeName[i]));
		if (strcmp(pCapInfo->szObjectTypeName[i],
				   pModuleInfo->szObjectType) == 0)
		{
			m_cmbObjType.SetCurSel(i);
		}
	}


	m_ctrlSlidSensi.SetRange(1, 10);
	m_ctrlSlidSensi.SetPos(pModuleInfo->bSensitivity);

	EnableAddModuleOrDetect();
	
}

void CConfigModule::UninitConfigModuleDlg()
{
	SetDlgItemText(IDC_CFGMOD_EDT_CHANNELNAME, _T(""));

	clearTreeModuleList();
	clearTreeTrackRegion();
	m_cmbObjType.ResetContent();
}

void CConfigModule::ShowPreview(LONG lLoginHanlde, int nChannel)
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
			
			HTREEITEM hItem = m_treeModuleList.GetRootItem();
			if (!hItem)
			{
				return;
			}
			
			CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
			if (!pModuleInfo)
			{
				return;
			}
			
			LLONG m_lPlayID = 0;
			HWND hWnd = m_pIvsModulePreview->GetSafeHwnd();
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
				m_pIvsModulePreview->SetModuleInfo(pModuleInfo, FALSE);
				bRet
					= g_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, 
										   CIvsModulePreview::DrawIvsModuleCfgProc, 
										   (DWORD)m_pIvsModulePreview);
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
						MessageBox(ConvertString(_T("Fail to play!")), ConvertString("Prompt"));
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

void CConfigModule::ClosePreview(LONG lRealPlayHandle)
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
			GetDlgItem(IDC_CFGMOD_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->SetRealPlayHandel(0);
		}
	}
}

void CConfigModule::DrawIvsInfoModuleProc(long nPort,HDC hdc,LONG nUser)
{
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	CConfigModule* pDlgModule = (CConfigModule*)nUser;	
	CFG_MODULE_INFO* pModuleInfo = pDlgModule->GetSelectModule();
	if (!pModuleInfo)
	{
		return;
	}

	SetBkMode(hdc, TRANSPARENT);
	//SetDCPenColor(hdc, RGB(255, 0, 0));

	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(0, 0, 255));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	
	CRect rt;
	pDlgModule->GetDlgItem(IDC_CFGMOD_STATIC_PREVIEW)->GetClientRect(&rt);
	
	double fFactorX = rt.Width() / 8192.0;
	double fFactorY = rt.Height() / 8192.0;

	//绘制检测区域
	int nPtCount = pModuleInfo->nDetectRegionPoint;
	CFG_POLYGON* pCfgPolygon = pModuleInfo->stuDetectRegion;
	
	MoveToEx(hdc, (int)(pCfgPolygon[0].nX * fFactorX), (int)(pCfgPolygon[0].nY *fFactorY), NULL);
	int i =0;
	for ( i = 0; i < nPtCount; i++)
	{
		LineTo(hdc, (int)(pCfgPolygon[i].nX * fFactorX), (int)(pCfgPolygon[i].nY * fFactorY));
	}
	LineTo(hdc, (int)(pCfgPolygon[0].nX * fFactorX), (int)(pCfgPolygon[0].nY * fFactorY));

	//绘制排除区域
	for (i = 0; i < pModuleInfo->nExcludeRegionNum; i++)
	{
		nPtCount = pModuleInfo->stuExcludeRegion[i].nPointNum;
		pCfgPolygon = pModuleInfo->stuExcludeRegion[i].stuPolygon;
		
		MoveToEx(hdc, int(pCfgPolygon[0].nX * fFactorX), int(pCfgPolygon[0].nY *fFactorY), NULL);
		for (int j = 0; j < nPtCount; j++)
		{
			LineTo(hdc, int(pCfgPolygon[j].nX * fFactorX), int(pCfgPolygon[j].nY * fFactorY));
		}
		LineTo(hdc, int(pCfgPolygon[0].nX * fFactorX), int(pCfgPolygon[0].nY * fFactorY));
	}

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

CFG_MODULE_INFO* CConfigModule::GetSelectModule()
{
	HTREEITEM hItem = m_treeModuleList.GetSelectedItem();
	if (!hItem)
	{
		return NULL;
	}

	CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);

	return pModuleInfo;
}

/*
 *	添加检测区域
 */
void CConfigModule::OnCfgmodBtnAdddetec() 
{
	// TODO: Add your control notification handler code here
	//每个模块只有一个检测区域
	HTREEITEM hItem = m_treeTrackRegion.GetRootItem();
	if (hItem)
	{
		MessageBox(ConvertString("One module only has one detect region!"), ConvertString("Prompt"));
		return;
	}

	//添加检测区域节点
	hItem = m_treeTrackRegion.InsertItem(ConvertString(_T("DetectRegion")));
	m_treeTrackRegion.SelectItem(hItem);
	MTNODE* pNode = new MTNODE;
	if (!pNode)
	{
		return;
	}
	pNode->nNodeType = DetectZone;
	m_treeTrackRegion.SetItemData(hItem, (DWORD)pNode);

	//开始绘制检测区域
	m_pIvsModulePreview->BeginDraw(hItem, TRUE);

	EnableAddModuleOrDetect();
}

/*
 *	添加模块树控件节点
 */
void CConfigModule::OnCfgmodBtnAddmod() 
{
	// TODO: Add your control notification handler code here
	int nModuleCnt = m_treeModuleList.GetCount();
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	CFG_CAP_ANALYSE_INFO* pCapAnalyseInfo = pMainDlg->GetCapAnalyseInfo(pMainDlg->GetCurrentChannel());
	if (!pCapAnalyseInfo)
	{
		return;
	}

	if (nModuleCnt >= pCapAnalyseInfo->nMaxMoudles)
	{
		MessageBox(ConvertString(_T("Can't add module any more!")), ConvertString("Prompt"));
		return;
	}

	TCHAR szName[32] = {0};
	_snprintf(szName, _countof(szName) * sizeof(TCHAR), _T("%s%02d"), ConvertString(_T("Module")), nModuleCnt + 1);
	HTREEITEM hItem = m_treeModuleList.InsertItem(szName);

	CFG_ANALYSEMODULES_INFO* pAnalyseModulesInfo = pMainDlg->GetAnalyseModuleInfo(pMainDlg->GetCurrentChannel());
	if(!pAnalyseModulesInfo)
	{
		return;
	}

	m_treeModuleList.SetItemData(hItem, (DWORD)&pAnalyseModulesInfo->stuModuleInfo[0]);
	m_treeModuleList.SelectItem(hItem);
	
	clearTreeTrackRegion();
}

/*
 *	删除模块树控件节点
 */
void CConfigModule::OnCfgmodBtnDelmod() 
{
	// TODO: Add your control notification handler code here
	int nModuleCnt = m_treeModuleList.GetCount();
	if (nModuleCnt <= 1)
	{
		MessageBox(ConvertString("Module should be greater than 1!"), ConvertString("Prompt"));
		return;
	}

	HTREEITEM hItem = m_treeModuleList.GetSelectedItem();
	if (!hItem)
	{
		return;
	}

	CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
	if (!pModuleInfo)
	{
		return;
	}

	//清除对应的检测区域和排除区域节点和绘图信息
	clearTreeTrackRegion();
	m_pIvsModulePreview->SetModuleInfo(NULL, TRUE);
	m_treeModuleList.DeleteItem(hItem);
	m_treeModuleList.SelectItem(NULL);
	m_treeTrackRegion.SelectItem(NULL);
	EnableAddModuleOrDetect();
}
/*
 *	删除检测树控件节点
 */
void CConfigModule::OnCfgmodBtnDelregion() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeTrackRegion.GetSelectedItem();
	if (!hItem)
	{
		MessageBox(ConvertString("select the item to be deleted!"), ConvertString("Prompt"));
		return;
	}

	MTNODE* pNode = (MTNODE*)m_treeTrackRegion.GetItemData(hItem);
	if (!pNode)
	{
		m_treeTrackRegion.DeleteItem(hItem);
		return;
	}

	if (DetectZone == pNode->nNodeType)
	{
		clearTreeTrackRegion();

		hItem = m_treeModuleList.GetSelectedItem();
		if (!hItem)
		{
			return;
		}
		CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
		if (pModuleInfo)
		{
			pModuleInfo->nDetectRegionPoint = 0;
			ZeroMemory(pModuleInfo->stuDetectRegion, sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
		}

		m_pIvsModulePreview->SetModuleInfo(NULL, TRUE);

		m_treeTrackRegion.SelectItem(NULL);
	}

	

	EnableAddModuleOrDetect();
}
/*
 *	获取设备该通道的模块信息，并更新界面
 */
void CConfigModule::OnCfgmodBtnGet() 
{
	// TODO: Add your control notification handler code here
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	m_pIvsModulePreview->SetModuleInfo(NULL, TRUE);
	ClosePreview(pMainDlg->GetRealPlayHandle());
	Sleep(200);
	m_pIvsModulePreview->Invalidate(FALSE);
	UninitConfigModuleDlg();

	pMainDlg->RefreshModuleInfo();

	InitConfigModuleDlg(pMainDlg->GetCurrentChannel());
	ShowPreview(pMainDlg->GetLoginHandle(),
				pMainDlg->GetCurrentChannel());

	HTREEITEM hItem = m_treeTrackRegion.GetRootItem();
	if (hItem)
	{
		m_treeTrackRegion.Expand(hItem, TVE_EXPAND);
	}
}
/*
 *	保存并更新模块信息到设备
 */
void CConfigModule::OnCfgmodBtnSet() 
{
	// TODO: Add your control notification handler code here
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	CFG_ANALYSEMODULES_INFO* pModuleInfo 
		= pMainDlg->GetAnalyseModuleInfo(pMainDlg->GetCurrentChannel());
	if (!pModuleInfo)
	{
		return;
	}
	
	int nRestart = 0;
	int nError = 0;
	char szOutBuffer[32*1024] = {0};
	
	// save module info
	BOOL bRet = CLIENT_PacketData(CFG_CMD_ANALYSEMODULE, (char*)pModuleInfo, sizeof(CFG_ANALYSEMODULES_INFO),
								  szOutBuffer, 32 * 1024);
	
	if (bRet == FALSE)
	{
		MessageBox(ConvertString(_T("Packet data error!")), ConvertString("Prompt"));
	}
	else
	{
		BOOL bSuccess = CLIENT_SetNewDevConfig(pMainDlg->GetLoginHandle(), CFG_CMD_ANALYSEMODULE, 
									 pMainDlg->GetCurrentChannel(), szOutBuffer, 32 * 1024, 
									 &nError, &nRestart, 3000);		
		if (bSuccess)
		{
			MessageBox(ConvertString(_T("Set ModuleInfo Successfully!")), ConvertString("Prompt"));
		}
		else
		{
			MessageBox(ConvertString(_T("Set ModuleInfo Failed!")), ConvertString("Prompt"));
		}		
	}
}

void CConfigModule::OnClickCfgmodTreeModlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	CPoint pt;
	GetCursorPos(&pt);
	
	m_treeModuleList.ScreenToClient(&pt);
	HTREEITEM hItem = m_treeModuleList.HitTest(pt);
	if (!hItem)
	{
		return;
	}
	m_treeModuleList.SelectItem(hItem);

	CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
	if (!pModuleInfo)
	{
		return;
	}

	m_pIvsModulePreview->SetModuleInfo(pModuleInfo, FALSE);

	clearTreeTrackRegion();

	if (!pModuleInfo->nDetectRegionPoint)
	{
		return;
	}
	
	//在检测区域树控件中添加检测节点
	hItem = m_treeTrackRegion.InsertItem(ConvertString(_T("DetectRegion")));
	m_treeTrackRegion.SelectItem(hItem);
	MTNODE* pNode = new MTNODE;
	ZeroMemory(pNode, sizeof(MTNODE));
	pNode->nNodeType = DetectZone;
	pNode->nPointCount = pModuleInfo->nDetectRegionPoint;
	memcpy(&pNode->CfgPolygon, pModuleInfo->stuDetectRegion, sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
	m_treeTrackRegion.SetItemData(hItem, (DWORD)pNode);
}


void CConfigModule::OnCfgmodBtnFilter()
{
	CTargetFilter filterDlg ;
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	int nChannel = pMainDlg->GetCurrentChannel();

	//初始化模块树控件
	CFG_ANALYSEMODULES_INFO* pAnalyseModulesInfo = pMainDlg->GetAnalyseModuleInfo(nChannel);
	if(!pAnalyseModulesInfo)
	{
		return;
	}
	filterDlg.Init(&(pAnalyseModulesInfo->stuModuleInfo[0].stObjectFilter[0]), nChannel);
	if (filterDlg.DoModal() == IDOK)
	{

	}
	
	pAnalyseModulesInfo = pMainDlg->GetAnalyseModuleInfo(nChannel);
	if (!pAnalyseModulesInfo)
	{
		return;
	}

	CFG_OBJECT_SIZEFILTER_INFO *pObjectFilter = filterDlg.GetObjectFilter();
	memcpy(&(pAnalyseModulesInfo->stuModuleInfo[0].stObjectFilter[0]), pObjectFilter, sizeof(CFG_OBJECT_SIZEFILTER_INFO));

	ShowPreview(pMainDlg->GetLoginHandle(), pMainDlg->GetCurrentChannel());
};

void CConfigModule::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nCtrlID = pScrollBar->GetDlgCtrlID();
	if (nCtrlID == IDC_CFGMOD_SLID_SENSI)
	{
		CSliderCtrl* pSliderCtrl = (CSliderCtrl*)pScrollBar;

		HTREEITEM hItem = m_treeModuleList.GetSelectedItem();
		if (!hItem)
		{
			return;
		}
		CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
		if (pScrollBar && pModuleInfo)
		{
			pModuleInfo->bSensitivity = pSliderCtrl->GetPos();
		}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CConfigModule::OnBnClickedCfgmodBtnRedraw()
{
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hItem = m_treeTrackRegion.GetRootItem();
	if (hItem == NULL)
	{
		return;
	}

	m_treeTrackRegion.SelectItem(hItem);
	m_pIvsModulePreview->Redraw(hItem, TRUE);
}
