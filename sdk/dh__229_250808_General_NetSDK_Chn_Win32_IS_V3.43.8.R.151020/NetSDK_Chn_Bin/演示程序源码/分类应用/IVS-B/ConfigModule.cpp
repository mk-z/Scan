// ConfigModule.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "ConfigModule.h"
#include "DemoIVSbDlg.h"
#include "IvsModulePreview.h"
#include "TargetFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigModule dialog


CConfigModule::CConfigModule(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigModule::IDD, pParent),
	m_pIvsModulePreview(NULL)
{
	//{{AFX_DATA_INIT(CConfigModule)
	//}}AFX_DATA_INIT
}


void CConfigModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigModule)
	DDX_Control(pDX, IDC_CFGMOD_CMB_OBJTYPE, m_cmbObjType);
	DDX_Control(pDX, IDC_CFGMOD_CHK_ENCAP, m_chkEnCapture);
	DDX_Control(pDX, IDC_CFGMOD_CMB_BANLANCE, m_cmbBalance);
	DDX_Control(pDX, IDC_CFGMOD_SLID_SENSI, m_ctrlSlidSensi);
	DDX_Control(pDX, IDC_CFGMOD_TREE_TRACKREGION, m_treeTrackRegion);
	DDX_Control(pDX, IDC_CFGMOD_TREE_MODLIST, m_treeModuleList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigModule, CDialog)
	//{{AFX_MSG_MAP(CConfigModule)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_ADDDETEC, OnCfgmodBtnAdddetec)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_ADDEXCLUD, OnCfgmodBtnAddexclud)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_ADDMOD, OnCfgmodBtnAddmod)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_DELMOD, OnCfgmodBtnDelmod)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_DELREGION, OnCfgmodBtnDelregion)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CFGMOD_BTN_GET, OnCfgmodBtnGet)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_SET, OnCfgmodBtnSet)
	ON_MESSAGE(WM_REGIONDONE, OnRegionDone)
	ON_NOTIFY(NM_CLICK, IDC_CFGMOD_TREE_MODLIST, OnClickCfgmodTreeModlist)
	ON_NOTIFY(NM_CLICK, IDC_CFGMOD_TREE_TRACKREGION, OnClickCfgmodTreeTrackregion)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CFGMOD_BTN_REDRAW, OnCfgmodBtnRedraw)
	ON_BN_CLICKED(IDC_CFGMOD_BTN_FILTER, OnCfgmodBtnFilter)
	ON_CBN_SELCHANGE(IDC_CFGMOD_CMB_BANLANCE, OnSelchangeCfgmodCmbBanlance)
	ON_CBN_SELCHANGE(IDC_CFGMOD_CMB_OBJTYPE, OnSelchangeCfgmodCmbObjtype)
	//}}AFX_MSG_MAP
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
		return 0;
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
		AfxMessageBox(ConvertString(_T("Add new region failed!")));
		return 0;
	}

	//更新新添加的检测/排除区域节点
	pNode = (MTNODE*)m_treeTrackRegion.GetItemData(hItem);
	if (pNode)
	{
		delete pNode;
		pNode = (MTNODE*)lParam;
	}
	m_treeTrackRegion.SetItemData(hItem, (DWORD)lParam);

	//更新对应的模块节点
	hItem = m_treeModuleList.GetSelectedItem();
	if (!hItem)
	{
		return 0;
	}

	CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
	if (!pModuleInfo)
	{
		return 0;
	}

	if (pNode->nNodeType == nDetectZone)
	{
		pModuleInfo->nDetectRegionPoint = pNode->nPointCount;
		memcpy(pModuleInfo->stuDetectRegion, 
			   pNode->CfgPolygon, 
			   sizeof(CFG_POLYGON) * pNode->nPointCount);
	}

	if (pNode->nNodeType == nExcludeZone)
	{
		int nExcluNum = pModuleInfo->nExcludeRegionNum;
		pModuleInfo->stuExcludeRegion[nExcluNum].nPointNum = pNode->nPointCount;
		memcpy(&pModuleInfo->stuExcludeRegion[nExcluNum].stuPolygon,
			   pNode->CfgPolygon,
			   sizeof(CFG_POLYGON) * pNode->nPointCount);
		pModuleInfo->nExcludeRegionNum++;
	}

	//更新绘图区域
	m_pIvsModulePreview->setModuleInfo(pModuleInfo, FALSE);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CConfigModule message handlers

BOOL CConfigModule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	CRect rt;
	GetDlgItem(IDC_CFGMOD_STATIC_PREVIEW)->GetWindowRect(&rt);
	ScreenToClient(&rt);

	m_pIvsModulePreview = new CIvsModulePreview;
	if (m_pIvsModulePreview)
	{
		m_pIvsModulePreview->Create(NULL,
									NULL,
									WS_CHILD | WS_VISIBLE,
									CRect(0, 0, 0, 0),
									this,
									5001);
		m_pIvsModulePreview->MoveWindow(&rt);
		m_pIvsModulePreview->ShowWindow(SW_SHOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
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
			delete pModuleInfo;
			pModuleInfo = NULL;
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
/*
 *	
 */
void CConfigModule::initConfigModuleDlg(int nChannel)
{
	if (nChannel == -1)
	{
		uninitConfigModuleDlg();
		return;
	}
	
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}	
	
	//
	TCHAR szChnName[32] = {0};
	_sntprintf(szChnName,
			   _countof(szChnName),
			   _T("%s%02d"), 
			   ConvertString(_T("Channel")),
			   nChannel + 1);
	SetDlgItemText(IDC_CFGMOD_EDT_CHANNELNAME, szChnName);

	//初始化模块树控件
	CFG_ANALYSEMODULES_INFO* pAnalyseModulesInfo = pMainDlg->getAnalyseModuleInfo(nChannel);
	if(!pAnalyseModulesInfo)
	{
		return;
	}

	CFG_MODULE_INFO* pModuleInfo = NULL;
	TCHAR szItem[32] = {0};
	HTREEITEM hItem = 0;

	//////////////////////////////////////////////////////////////////////////
	//2012-06-08
	int i = 0;
	for (i = 0; i < pAnalyseModulesInfo->nMoudlesNum; i++)
	{
		//在模块列表树控件中添加模块节点
		_sntprintf(szItem, _countof(szItem), _T("%s%02d"), ConvertString(_T("Module")), i + 1);
		hItem = m_treeModuleList.InsertItem(szItem);

		pModuleInfo = new CFG_MODULE_INFO;
		if (!pModuleInfo)
		{
			break;
		}
		ZeroMemory(pModuleInfo, sizeof(CFG_MODULE_INFO));
		memcpy(pModuleInfo, &pAnalyseModulesInfo->stuModuleInfo[i], sizeof(CFG_MODULE_INFO));
		m_treeModuleList.SetItemData(hItem, (DWORD)pModuleInfo);

		ZeroMemory(szItem, sizeof(szItem));

		if (!pModuleInfo->nDetectRegionPoint)
		{
			continue;
		}

		//在检测区域树控件中添加检测节点
		hItem = m_treeTrackRegion.InsertItem(ConvertString(_T("DetectRegion")));
		MTNODE* pNode = new MTNODE;
		if (!pNode)
		{
			continue;
		}
		ZeroMemory(pNode, sizeof(MTNODE));
		pNode->nNodeType = nDetectZone;
		pNode->nPointCount = pModuleInfo->nDetectRegionPoint;
		memcpy(&pNode->CfgPolygon, pModuleInfo->stuDetectRegion, sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
		m_treeTrackRegion.SetItemData(hItem, (DWORD)pNode);

		//在检测节点下，添加排除区域节点
		for (int j = 0; j < pAnalyseModulesInfo->stuModuleInfo[i].nExcludeRegionNum; j++)
		{
			_sntprintf(szItem, _countof(szItem), _T("%s%d"), ConvertString(_T("ExcludeRegion")), j + 1);
			HTREEITEM hChildItem = m_treeTrackRegion.InsertItem(szItem, hItem);

			pNode = new MTNODE;
			if (!pNode)
			{
				continue;
			}
			ZeroMemory(pNode, sizeof(MTNODE));
			pNode->nNodeType = nExcludeZone;
			pNode->nPointCount = pModuleInfo->stuExcludeRegion[j].nPointNum;
			memcpy(&pNode->CfgPolygon, 
				   &pModuleInfo->stuExcludeRegion[j].stuPolygon,
				   sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
			m_treeTrackRegion.SetItemData(hChildItem, (DWORD)pNode);

			ZeroMemory(szItem, sizeof(szItem));
		}
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
		= (CFG_CAP_ANALYSE_INFO*)pMainDlg->getCapAnalyseInfo(pMainDlg->getCurrentChannel());
	if (!pCapInfo)
	{
		return;
	}
	
	int nObjTypeCnt = pCapInfo->nSupportedObjectTypeNum;
	for (i = 0; i < nObjTypeCnt; i++)
	{
		m_cmbObjType.InsertString(i, ConvertString(pCapInfo->szObjectTypeName[i]));
		if (strcmp(pCapInfo->szObjectTypeName[i],
				   pModuleInfo->szObjectType) == 0
			|| strcmp(ConvertString(pCapInfo->szObjectTypeName[i]),
					  ConvertString(pModuleInfo->szObjectType)) == 0)
		{
			m_cmbObjType.SetCurSel(i);
		}
	}


	m_ctrlSlidSensi.SetRange(1, 10);
	m_ctrlSlidSensi.SetPos(pModuleInfo->bSensitivity);

	m_cmbBalance.ResetContent();
	m_cmbBalance.InsertString(0, ConvertString(_T("Compromise")));
	m_cmbBalance.InsertString(1, ConvertString(_T("LessLeak")));
	m_cmbBalance.InsertString(2, ConvertString(_T("LessError")));
	if (pModuleInfo->abDetectBalance)
	{
		m_cmbBalance.SetCurSel(pModuleInfo->nDetectBalance);
	} 
	else
	{
		m_cmbBalance.SetCurSel(-1);
	}

	if (pModuleInfo->bSnapShot)
	{
		m_chkEnCapture.SetCheck(BST_CHECKED);
	} 
	else
	{
		m_chkEnCapture.SetCheck(BST_UNCHECKED);
	}
}

void CConfigModule::uninitConfigModuleDlg()
{
	if (m_pIvsModulePreview->isDrawing())
	{
		m_pIvsModulePreview->endDraw();
	}

	SetDlgItemText(IDC_CFGMOD_EDT_CHANNELNAME, _T(""));

	clearTreeModuleList();
	clearTreeTrackRegion();
	m_cmbObjType.ResetContent();
	m_cmbBalance.ResetContent();
}

void CConfigModule::showPreview(LONG lLoginHanlde, int nChannel)
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
			
			int nPort = 450;
			LLONG m_lPlayID = 0;
			HWND hWnd = m_pIvsModulePreview->GetSafeHwnd();
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
				m_pIvsModulePreview->setModuleInfo(pModuleInfo, FALSE);
				bRet = s_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, 
										   CIvsModulePreview::drawIvsModuleCfgProc, 
										   (DWORD)m_pIvsModulePreview);

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
			else
			{
				s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			}
		}
	}
}

void CConfigModule::closePreview(LONG lRealPlayHandle)
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
			GetDlgItem(IDC_CFGMOD_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->setRealPlayHandel(0);
		}
	}
}

void CConfigModule::DrawIvsInfoModuleProc(long nPort,HDC hdc,LONG nUser)
{
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	CConfigModule* pDlgModule = (CConfigModule*)nUser;	
	CFG_MODULE_INFO* pModuleInfo = pDlgModule->getSelectModule();
	if (!pModuleInfo)
	{
		return;
	}

	SetBkMode(hdc, TRANSPARENT);
	SetDCPenColor(hdc, RGB(255, 0, 0));

	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	
	CRect rt;
	pDlgModule->GetDlgItem(IDC_CFGMOD_STATIC_PREVIEW)->GetClientRect(&rt);
	
	float fFactorX = rt.Width() / 8192.;
	float fFactorY = rt.Height() / 8192.;

	//绘制检测区域
	int nPtCount = pModuleInfo->nDetectRegionPoint;
	CFG_POLYGON* pCfgPolygon = pModuleInfo->stuDetectRegion;
	
	MoveToEx(hdc, pCfgPolygon[0].nX * fFactorX, pCfgPolygon[0].nY *fFactorY, NULL);

	int i = 0;
	for (i = 0; i < nPtCount; i++)
	{
		LineTo(hdc, pCfgPolygon[i].nX * fFactorX, pCfgPolygon[i].nY * fFactorY);
	}
	LineTo(hdc, pCfgPolygon[0].nX * fFactorX, pCfgPolygon[0].nY * fFactorY);

	//绘制排除区域
	for (i = 0; i < pModuleInfo->nExcludeRegionNum; i++)
	{
		nPtCount = pModuleInfo->stuExcludeRegion[i].nPointNum;
		pCfgPolygon = pModuleInfo->stuExcludeRegion[i].stuPolygon;
		
		MoveToEx(hdc, pCfgPolygon[0].nX * fFactorX, pCfgPolygon[0].nY *fFactorY, NULL);
		for (int j = 0; j < nPtCount; j++)
		{
			LineTo(hdc, pCfgPolygon[j].nX * fFactorX, pCfgPolygon[j].nY * fFactorY);
		}
		LineTo(hdc, pCfgPolygon[0].nX * fFactorX, pCfgPolygon[0].nY * fFactorY);
	}

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

CFG_MODULE_INFO* CConfigModule::getSelectModule()
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
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	//每个模块只有一个检测区域
	HTREEITEM hItem = m_treeTrackRegion.GetRootItem();
	if (hItem)
	{
		return;
	}

	//添加检测区域节点
	hItem = m_treeTrackRegion.InsertItem(ConvertString(_T("DetectRegion")));
	MTNODE* pNode = new MTNODE;
	if (!pNode)
	{
		return;
	}
	pNode->nNodeType = nDetectZone;
	m_treeTrackRegion.SetItemData(hItem, (DWORD)pNode);

	//开始绘制检测区域
	m_pIvsModulePreview->beginDraw(hItem, TRUE);
}
/*
 *	添加排除区域
 */
void CConfigModule::OnCfgmodBtnAddexclud() 
{
	// TODO: Add your control notification handler code here
	// 还没有检测区，无法添加排除区或者正在画图，需要结束之前的绘图操作
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	HTREEITEM hItem = m_treeTrackRegion.GetRootItem();
	if (!hItem)
	{
		return;
	}	

	//添加排除区域节点
	hItem = m_treeTrackRegion.InsertItem(ConvertString(_T("ExcludeRegion")), hItem);
	MTNODE* pNode = new MTNODE;
	if (!pNode)
	{
		return;
	}
	pNode->nNodeType = nExcludeZone;
	m_treeTrackRegion.SetItemData(hItem, (DWORD)pNode);

	HTREEITEM hRootItem = m_treeTrackRegion.GetRootItem();
	m_treeTrackRegion.Expand(hRootItem, TVE_EXPAND);

	//开始绘制排除区域
	m_pIvsModulePreview->beginDraw(hItem, FALSE);
}
/*
 *	添加模块树控件节点
 */
void CConfigModule::OnCfgmodBtnAddmod() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	int nModuleCnt = m_treeModuleList.GetCount();
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	CFG_CAP_ANALYSE_INFO* pCapAnalyseInfo = pMainDlg->getCapAnalyseInfo(pMainDlg->getCurrentChannel());
	if (!pCapAnalyseInfo)
	{
		return;
	}

	if (nModuleCnt >= pCapAnalyseInfo->nMaxMoudles)
	{
		AfxMessageBox(ConvertString(_T("Can't add module any more")));
		return;
	}

	TCHAR szName[32] = {0};
	_snprintf(szName, _countof(szName), _T("%s%02d"), ConvertString(_T("Module")), nModuleCnt + 1);
	HTREEITEM hItem = m_treeModuleList.InsertItem(szName);
	CFG_MODULE_INFO* pModuleInfo = new CFG_MODULE_INFO;
	if (!pModuleInfo)
	{
		return;
	}
	ZeroMemory(pModuleInfo, sizeof(pModuleInfo));
	m_treeModuleList.SetItemData(hItem, (DWORD)pModuleInfo);
	m_treeModuleList.SelectItem(hItem);
	
	clearTreeTrackRegion();
}
/*
 *	删除模块树控件节点
 */
void CConfigModule::OnCfgmodBtnDelmod() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	HTREEITEM hItem = m_treeModuleList.GetSelectedItem();
	if (!hItem)
	{
		return;
	}

	// 目前有且仅有一个模块，不能删除这个模块
	AfxMessageBox(ConvertString(_T("Can't delete the last module")));

// 	CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
// 	if (!pModuleInfo)
// 	{
// 		return;
// 	}
// 
// 	//清除对应的检测区域和排除区域节点和绘图信息
// 	clearTreeTrackRegion();
// 	m_pIvsModulePreview->setModuleInfo(NULL, TRUE);
// 
// 	//清除模块信息节点
// 	delete pModuleInfo;
// 	pModuleInfo = NULL;
// 
// 	m_treeModuleList.DeleteItem(hItem);
// 
// 	m_treeModuleList.SelectItem(NULL);
// 	m_treeTrackRegion.SelectItem(NULL);
}
/*
 *	删除检测树控件节点
 */
void CConfigModule::OnCfgmodBtnDelregion() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	HTREEITEM hItem = m_treeTrackRegion.GetSelectedItem();
	if (!hItem)
	{
		return;
	}

	MTNODE* pNode = (MTNODE*)m_treeTrackRegion.GetItemData(hItem);
	if (!pNode)
	{
		m_treeTrackRegion.DeleteItem(hItem);
		return;
	}

	if (nDetectZone == pNode->nNodeType)
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

			pModuleInfo->nExcludeRegionNum = 0;
			ZeroMemory(pModuleInfo->stuExcludeRegion,
					   sizeof(CFG_REGION) * MAX_EXCLUDEREGION_NUM);
		}

		m_pIvsModulePreview->setModuleInfo(NULL, TRUE);

		m_treeTrackRegion.SelectItem(NULL);
		return;
	}

	if (nExcludeZone == pNode->nNodeType)
	{
		delete pNode;
		pNode = NULL;
		m_treeTrackRegion.DeleteItem(hItem);
		
		hItem = m_treeModuleList.GetSelectedItem();
		CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
		if (!pModuleInfo)
		{
			return;
		}

		//获取检测区域节点的信息
		hItem = m_treeTrackRegion.GetRootItem();
		if (!hItem)
		{
			return;
		}
		pNode = (MTNODE*)m_treeTrackRegion.GetItemData(hItem);
		if (!pNode)
		{
			return;
		}
		pModuleInfo->nDetectRegionPoint = pNode->nPointCount;
		memcpy(pModuleInfo->stuDetectRegion,
			   pNode->CfgPolygon, 
			   sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);

		//检测区信息不变，但是排除区信息减少
		ZeroMemory(pModuleInfo->stuExcludeRegion, 
				   sizeof(CFG_REGION) * MAX_EXCLUDEREGION_NUM);
		pModuleInfo->nExcludeRegionNum = 0;

		//获取排除区域节点的信息
		hItem = m_treeTrackRegion.GetChildItem(hItem);
		int i = 0;
		while(hItem)
		{
			pNode = (MTNODE*)m_treeTrackRegion.GetItemData(hItem);
			if (!pNode)
			{
				hItem = m_treeTrackRegion.GetNextSiblingItem(hItem);
				continue;
			}

			pModuleInfo->stuExcludeRegion[i].nPointNum = pNode->nPointCount;
			memcpy(pModuleInfo->stuExcludeRegion[i].stuPolygon, 
				   pNode->CfgPolygon, 
				   sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
			pModuleInfo->nExcludeRegionNum++;

			hItem = m_treeTrackRegion.GetNextSiblingItem(hItem);
			i++;
		}

		m_pIvsModulePreview->setModuleInfo(pModuleInfo, FALSE);

		m_treeTrackRegion.SelectItem(NULL);
	}
}
/*
 *	获取设备该通道的模块信息，并更新界面
 */
void CConfigModule::OnCfgmodBtnGet() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	m_pIvsModulePreview->setModuleInfo(NULL, TRUE);
	closePreview(pMainDlg->getRealPlayHandle());
	Sleep(200);
	m_pIvsModulePreview->Invalidate(FALSE);
	uninitConfigModuleDlg();

	CFG_ANALYSEMODULES_INFO* pAnalyseModuleInfo = pMainDlg->getAnalyseModuleInfo(pMainDlg->getCurrentChannel());
	if (!pAnalyseModuleInfo)
	{
		return;
// 		pAnalyseModuleInfo = new CFG_ANALYSEMODULES_INFO;
// 		if (!pAnalyseModuleInfo)
// 		{
// 			return;
// 		}
// 		ZeroMemory(pAnalyseModuleInfo, sizeof(CFG_ANALYSEMODULES_INFO));
	}
	pMainDlg->getModule(pMainDlg->getCurrentChannel(), pAnalyseModuleInfo);

	initConfigModuleDlg(pMainDlg->getCurrentChannel());
	showPreview(pMainDlg->getLoginHandle(),
				pMainDlg->getCurrentChannel());

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
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	CFG_ANALYSEMODULES_INFO* pModuleInfo 
		= pMainDlg->getAnalyseModuleInfo(pMainDlg->getCurrentChannel());
	if (!pModuleInfo)
	{
		return;
	}

	int nModuleCnt = 0;
	HTREEITEM hItem = m_treeModuleList.GetRootItem();
	while(hItem)
	{
		CFG_MODULE_INFO* pModule = (CFG_MODULE_INFO*)m_treeTrackRegion.GetItemData(hItem);
		if (pModule)
		{
			memcpy(&pModuleInfo->stuModuleInfo[nModuleCnt],
				   pModule,
				   sizeof(CFG_MODULE_INFO));
			nModuleCnt++;
			pModuleInfo->nMoudlesNum = nModuleCnt;
		}
		hItem = m_treeModuleList.GetNextSiblingItem(hItem);
	}
	
	int nRestart = 0;
	int nError = 0;
	char szOutBuffer[32*1024] = {0};
	
	// save module info
	BOOL bRet = CLIENT_PacketData(CFG_CMD_ANALYSEMODULE, 
								  (char*)pModuleInfo, 
								  sizeof(CFG_ANALYSEMODULES_INFO),
								  szOutBuffer, 
								  32 * 1024);
	
	if (bRet == FALSE)
	{
		AfxMessageBox(ConvertString(_T("Packet data error")));
	}
	else
	{
		BOOL bSuccess
			= CLIENT_SetNewDevConfig(pMainDlg->getLoginHandle(), 
									 CFG_CMD_ANALYSEMODULE, 
									 pMainDlg->getCurrentChannel(), 
									 szOutBuffer, 
									 32 * 1024, 
									 &nError, 
									 &nRestart, 
									 3000);		
		if (bSuccess)
		{
			AfxMessageBox(ConvertString(_T("Set ModuleInfo Successfully")));
		}
		else
		{
			AfxMessageBox(ConvertString(_T("Set ModuleInfo Failed")));
		}		
	}
}

void CConfigModule::OnClickCfgmodTreeModlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}
//	*pResult = 0;

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

	m_pIvsModulePreview->setModuleInfo(pModuleInfo, FALSE);

	clearTreeTrackRegion();

	if (!pModuleInfo->nDetectRegionPoint)
	{
		return;
	}
	
	//在检测区域树控件中添加检测节点
	hItem = m_treeTrackRegion.InsertItem(ConvertString(_T("DetectRegion")));
	MTNODE* pNode = new MTNODE;
	if (!pNode)
	{
		return;
	}
	ZeroMemory(pNode, sizeof(MTNODE));
	pNode->nNodeType = nDetectZone;
	pNode->nPointCount = pModuleInfo->nDetectRegionPoint;
	memcpy(&pNode->CfgPolygon, pModuleInfo->stuDetectRegion, sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
	m_treeTrackRegion.SetItemData(hItem, (DWORD)pNode);
	
	TCHAR szItem[32] = {0};
	//在检测节点下，添加排除区域节点
	for (int j = 0; j < pModuleInfo->nExcludeRegionNum; j++)
	{
		_sntprintf(szItem, _countof(szItem), ConvertString(_T("ExcludeRegion")), j + 1);
		HTREEITEM hChildItem = m_treeTrackRegion.InsertItem(szItem, hItem);
		
		pNode = new MTNODE;
		if (!pNode)
		{
			continue;
		}
		ZeroMemory(pNode, sizeof(MTNODE));
		pNode->nNodeType = nExcludeZone;
		pNode->nPointCount = pModuleInfo->stuExcludeRegion[j].nPointNum;
		memcpy(&pNode->CfgPolygon, 
				&pModuleInfo->stuExcludeRegion[j].stuPolygon,
				sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
		m_treeTrackRegion.SetItemData(hChildItem, (DWORD)pNode);
		
		ZeroMemory(szItem, sizeof(szItem));
	}
}

void CConfigModule::OnClickCfgmodTreeTrackregion(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	CPoint pt;
	GetCursorPos(&pt);
	m_treeTrackRegion.ScreenToClient(&pt);

	HTREEITEM hItem = m_treeTrackRegion.HitTest(pt);
	if (hItem)
	{
		m_treeTrackRegion.SelectItem(hItem);
		MTNODE* pNode = (MTNODE*)m_treeTrackRegion.GetItemData(hItem);
	}
	else
	{
		m_treeTrackRegion.SelectItem(NULL);
	}
	
	*pResult = 0;
}

void CConfigModule::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

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

void CConfigModule::OnCfgmodBtnRedraw() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	// 如果没有配置任何检测区，无需重绘
	if (!m_treeTrackRegion.GetRootItem())
	{
		return;
	}

	// 清除已有检测区和排除区
	clearTreeTrackRegion();
	m_treeTrackRegion.DeleteAllItems();
	m_pIvsModulePreview->setModuleInfo(NULL, TRUE);
	
	// 应当已经选择可配置的模块
	HTREEITEM hModuleItem = m_treeModuleList.GetSelectedItem();
	if (!hModuleItem)
	{
		return;
	}

	// 获取模块配置信息
	CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hModuleItem);
	if (!pModuleInfo)
	{
		return;
	}

	pModuleInfo->nDetectRegionPoint = 0;
	ZeroMemory(pModuleInfo->stuDetectRegion, sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
	pModuleInfo->nExcludeRegionNum = 0;
	ZeroMemory(pModuleInfo->stuExcludeRegion, sizeof(CFG_REGION) * MAX_EXCLUDEREGION_NUM);

	OnCfgmodBtnAdddetec();
}

void CConfigModule::OnCfgmodBtnFilter() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsModulePreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	CTargetFilter filterDlg ;
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

	CFG_ANALYSEMODULES_INFO* pInfo = new CFG_ANALYSEMODULES_INFO;
	if (!pInfo)
	{
		return;
	}

	memcpy(pInfo, pAnalyseModulesInfo, sizeof(CFG_ANALYSEMODULES_INFO));
	if (strcmp(pInfo->stuModuleInfo[0].szObjectType, "Human") == 0)
	{
		// 如果不是默认的检测物体类型Unknown，则应调用特定物体过滤信息
		CFG_MODULE_INFO& stuModuleInfo = pInfo->stuModuleInfo[0];

		stuModuleInfo.nObjectFilterNum = 1;
		strncpy(stuModuleInfo.stObjectFilter[0].szObjectType, "Human", strlen("Human"));

		stuModuleInfo.abBySize = stuModuleInfo.stObjectFilter[0].stSizeFilter.abBySize;
		stuModuleInfo.bBySize = stuModuleInfo.stObjectFilter[0].stSizeFilter.bBySize;
		stuModuleInfo.nFilterType = stuModuleInfo.stObjectFilter[0].stSizeFilter.bFilterType;
		stuModuleInfo.bFilterTypeEnable = stuModuleInfo.stObjectFilter[0].stSizeFilter.bFilterTypeEnable;

		stuModuleInfo.nCalibrateBoxNum = stuModuleInfo.stObjectFilter[0].stSizeFilter.nCalibrateBoxNum;
		memcpy(&stuModuleInfo.stuCalibrateBoxs[0],
			   &stuModuleInfo.stObjectFilter[0].stSizeFilter.stuCalibrateBoxs[0],
			   sizeof(CFG_CALIBRATEBOX_INFO));

		stuModuleInfo.bFilterMaxSizeEnable = stuModuleInfo.stObjectFilter[0].stSizeFilter.bFilterMaxSizeEnable;
		stuModuleInfo.bFilterMinSizeEnable = stuModuleInfo.stObjectFilter[0].stSizeFilter.bFilterMinSizeEnable;
		memcpy(&stuModuleInfo.stuFilterMaxSize, 
			   &stuModuleInfo.stObjectFilter[0].stSizeFilter.stuFilterMaxSize, 
			   sizeof(CFG_SIZE));
		memcpy(&stuModuleInfo.stuFilterMinSize,
			   &stuModuleInfo.stObjectFilter[0].stSizeFilter.stuFilterMinSize,
			   sizeof(CFG_SIZE));
	}

	filterDlg.Init(pInfo, nChannel);
	if (filterDlg.DoModal() == IDOK)
	{
		HTREEITEM hItem = m_treeModuleList.GetRootItem();
		if (hItem)
		{
			CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hItem);
			if (pModuleInfo)
			{
				if (strcmp(pInfo->stuModuleInfo[0].szObjectType, "Human") == 0)
				{
					// 如果不是默认的物体类型
					CFG_MODULE_INFO& stuModuleInfoSrc = pInfo->stuModuleInfo[0];

					pModuleInfo->nObjectFilterNum = 1;

					CFG_SIZEFILTER_INFO& stuFilterInfoDst = pModuleInfo->stObjectFilter[0].stSizeFilter;
					strncpy(pModuleInfo->stObjectFilter[0].szObjectType, "Human", strlen("Human"));
					stuFilterInfoDst.abBySize = stuModuleInfoSrc.abBySize;
					stuFilterInfoDst.bBySize = stuModuleInfoSrc.bBySize;
					stuFilterInfoDst.bFilterTypeEnable = stuModuleInfoSrc.bFilterTypeEnable;
					stuFilterInfoDst.bFilterType = stuModuleInfoSrc.nFilterType;

					stuFilterInfoDst.nCalibrateBoxNum = stuModuleInfoSrc.nCalibrateBoxNum;
					memcpy(&stuFilterInfoDst.stuCalibrateBoxs[0],
						   &stuModuleInfoSrc.stuCalibrateBoxs[0],
						   sizeof(CFG_CALIBRATEBOX_INFO));

					stuFilterInfoDst.bFilterMaxSizeEnable = stuModuleInfoSrc.bFilterMaxSizeEnable;
					stuFilterInfoDst.bFilterMinSizeEnable = stuModuleInfoSrc.bFilterMinSizeEnable;
					memcpy(&stuFilterInfoDst.stuFilterMaxSize,
						   &stuModuleInfoSrc.stuFilterMaxSize,
						   sizeof(CFG_SIZE));
					memcpy(&stuFilterInfoDst.stuFilterMinSize,
						   &stuModuleInfoSrc.stuFilterMinSize,
						   sizeof(CFG_SIZE));
				}
				else
				{
					// 如果是默认的物体类型
					// 目前模块配置只有一个模块
					memcpy(pModuleInfo->stuCalibrateBoxs,
						   pInfo->stuModuleInfo[0].stuCalibrateBoxs,
				  		   sizeof(CFG_CALIBRATEBOX_INFO) * MAX_CALIBRATEBOX_NUM);
					memcpy(&pModuleInfo->stuFilterMaxSize,
						   &pInfo->stuModuleInfo[0].stuFilterMaxSize,
						   sizeof(CFG_SIZE));
					memcpy(&pModuleInfo->stuFilterMinSize,
						   &pInfo->stuModuleInfo[0].stuFilterMinSize,
						   sizeof(CFG_SIZE));
					pModuleInfo->abBySize = true;
					pModuleInfo->bBySize = pInfo->stuModuleInfo[0].bBySize;
					pModuleInfo->nFilterType = pInfo->stuModuleInfo[0].nFilterType;
					pModuleInfo->bFilterTypeEnable = pInfo->stuModuleInfo[0].bFilterTypeEnable;
					pModuleInfo->bFilterMaxSizeEnable = true;
					pModuleInfo->bFilterMinSizeEnable = true;
					pModuleInfo->nCalibrateBoxNum = 1;
					pInfo->stuModuleInfo[0].bFilterMaxSizeEnable = true;
					pInfo->stuModuleInfo[0].bFilterMinSizeEnable = true;
					pInfo->stuModuleInfo[0].nCalibrateBoxNum = 1;
				}
			}
		}
	}
	delete pInfo;
	pInfo = NULL;

	showPreview(pMainDlg->getLoginHandle(), pMainDlg->getCurrentChannel());
}

void CConfigModule::OnSelchangeCfgmodCmbBanlance() 
{
	// TODO: Add your control notification handler code here
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

	pAnalyseModulesInfo->stuModuleInfo[0].abDetectBalance = true;
	pAnalyseModulesInfo->stuModuleInfo[0].nDetectBalance = m_cmbBalance.GetCurSel();

	HTREEITEM hModuleItem = m_treeModuleList.GetRootItem();
// 	for (int i = 0; i < nChannel; i++)
// 	{
// 		hModuleItem = m_treeTrackRegion.GetNextSiblingItem(hModuleItem);
// 	}
	if (!hModuleItem)
	{
		return;
	}

	CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)m_treeModuleList.GetItemData(hModuleItem);
	if (!pModuleInfo)
	{
		return;
	}

	pModuleInfo->abDetectBalance = true;
	pModuleInfo->nDetectBalance = m_cmbBalance.GetCurSel();
}

void CConfigModule::OnSelchangeCfgmodCmbObjtype() 
{
	// TODO: Add your control notification handler code here
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

	char *szObjTypeName[] = {"Unknown", "Human"};
	int nObjNum = _countof(szObjTypeName);

	CString strItem;

	for (int i = 0; i < _countof(szObjTypeName); i++)
	{
		m_cmbObjType.GetLBText(m_cmbObjType.GetCurSel(), strItem);
		if (strcmp(szObjTypeName[i], strItem.GetBuffer(0)) == 0
			|| strcmp(ConvertString(szObjTypeName[i]), strItem.GetBuffer(0)) == 0)
		{
			ZeroMemory(pModuleInfo->szObjectType, MAX_NAME_LEN);
			strncpy(pModuleInfo->szObjectType, szObjTypeName[i], strlen(szObjTypeName[i]));

			CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
			if (pMainDlg)
			{
				CFG_ANALYSEMODULES_INFO* pAnalyseModuleInfo = (CFG_ANALYSEMODULES_INFO*)pMainDlg->getAnalyseModuleInfo(pMainDlg->getCurrentChannel());
				if (pAnalyseModuleInfo)
				{
					if (strcmp(strItem.GetBuffer(0), "Unknown") == 0
						|| strcmp(strItem.GetBuffer(0), ConvertString("Unknown")) == 0)
					{
						ZeroMemory(pAnalyseModuleInfo->stuModuleInfo[0].szObjectType, MAX_NAME_LEN);
						strncpy(pAnalyseModuleInfo->stuModuleInfo[0].szObjectType, 
								szObjTypeName[i], 
								strlen(szObjTypeName[i]));
					}
					else
					{
						ZeroMemory(pAnalyseModuleInfo->stuModuleInfo[0].szObjectType, MAX_NAME_LEN);
						strncpy(pAnalyseModuleInfo->stuModuleInfo[0].szObjectType, 
								szObjTypeName[i], 
								strlen(szObjTypeName[i]));
						ZeroMemory(pAnalyseModuleInfo->stuModuleInfo[0].stObjectFilter[0].szObjectType, MAX_NAME_LEN);
						strncpy(pAnalyseModuleInfo->stuModuleInfo[0].stObjectFilter->szObjectType, 
								szObjTypeName[i], 
								strlen(szObjTypeName[i]));
					}
				}
			}
			break;
		}
	}
}
