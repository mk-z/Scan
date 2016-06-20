// ConfigGlobal.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSb.h"
#include "ConfigGlobal.h"
#include "DemoIVSbDlg.h"
#include "IvsGlobalPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigGlobal dialog


CConfigGlobal::CConfigGlobal(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigGlobal::IDD, pParent),
	m_pIvsGlobalPreview(NULL)
{
	//{{AFX_DATA_INIT(CConfigGlobal)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_colorPen = RGB(0, 0, 255);
}


void CConfigGlobal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigGlobal)
	DDX_Control(pDX, IDC_CFGGLO_TREE_REGION, m_treeRegion);
	DDX_Control(pDX, IDC_CFGGLO_EDT_CHANNELNAME, m_edtChnName);
	DDX_Control(pDX, IDC_CFGGLO_CMB_SCENE, m_cmbScene);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigGlobal, CDialog)
	//{{AFX_MSG_MAP(CConfigGlobal)
	ON_CBN_SELCHANGE(IDC_CFGGLO_CMB_SCENE, OnSelchangeCfggloCmbScene)
	ON_NOTIFY(NM_CLICK, IDC_CFGGLO_TREE_REGION, OnClickCfggloTreeRegion)
	ON_BN_CLICKED(IDC_CFGGLO_BTN_ADDAERA, OnCfggloBtnAddaera)
	ON_BN_CLICKED(IDC_CFGGLO_BTN_ADDRULER, OnCfggloBtnAddruler)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_ZONEDONE, OnZoneDone)
	ON_BN_CLICKED(IDC_CFGGLO_BTN_DELAREA, OnCfggloBtnDelarea)
	ON_BN_CLICKED(IDC_CFGGLO_BTN_DELRULER, OnCfggloBtnDelruler)
	ON_BN_CLICKED(IDC_CFGGLO_BTN_GET, OnCfggloBtnGet)
	ON_BN_CLICKED(IDC_CFGGLO_BTN_SET, OnCfggloBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*
 *	WM_ZONEDONE消息响应
 */
LRESULT CConfigGlobal::OnZoneDone(WPARAM wParam, LPARAM lParam)
{
	HTREEITEM hItemToBeDraw = (HTREEITEM)wParam;
	GTNODETYPE* pNode = (GTNODETYPE*)lParam;

	if (!hItemToBeDraw || !pNode)
	{
		return 0;
	}

	GTNODETYPE* pNodeType = NULL;
	GTNODEAREA* pNodeArea = NULL;
	GTNODESTAFF* pNodeStaff = NULL;
	if (pNode->nNodeType == nNodeArea)
	{
		pNodeArea = (GTNODEAREA*)lParam;
	}
	else if (pNode->nNodeType == EM_STAFF_TYPE_HORIZONTAL
			 || pNode->nNodeType == EM_STAFF_TYPE_VERTICAL)
	{
		pNodeStaff = (GTNODESTAFF*)lParam;
	}

	BOOL bRet = FALSE;

	HTREEITEM hItem = m_treeRegion.GetRootItem();
	while (hItem)
	{
		if (hItem == hItemToBeDraw)
		{
			bRet = TRUE;
			break;
		}

		HTREEITEM hItemChild = m_treeRegion.GetChildItem(hItem);
		while(hItemChild)
		{
			if (hItemChild == hItemToBeDraw)
			{
				bRet = TRUE;
				break;
			}
			hItemChild = m_treeRegion.GetNextSiblingItem(hItemChild);
		}
		if (bRet)
		{
			break;
		}

		hItem = m_treeRegion.GetNextSiblingItem(hItem);
	}

	if (!bRet)
	{
		goto ErrorHandle;
		return 0;
	}

	pNodeType = (GTNODETYPE*)m_treeRegion.GetItemData(hItemToBeDraw);
	if (pNodeType->nNodeType != pNode->nNodeType)
	{
		goto ErrorHandle;
		return 0;
	}

	if (pNode->nNodeType == nNodeArea)
	{
		//更新树节点信息
		GTNODEAREA* pNodeAreaOld = (GTNODEAREA*)m_treeRegion.GetItemData(hItemToBeDraw);

		memcpy(&pNodeAreaOld->CfgCalibrateAreaInfo.stuArea,
			   &pNodeArea->CfgCalibrateAreaInfo.stuArea,
			   sizeof(CFG_REGION));

		delete pNodeArea;
		pNodeArea = NULL;

		//更新绘图结构体
		updateTreeRegion();
	} 
	else if (pNode->nNodeType == nStaffHor
			 || pNode->nNodeType == nStaffVer)
	{
		//更新树节点信息
		GTNODESTAFF* pNodeStaffOld = (GTNODESTAFF*)m_treeRegion.GetItemData(hItemToBeDraw);

		memcpy(&pNodeStaffOld->CfgStaff.stuStartLocation,
			   &pNodeStaff->CfgStaff.stuStartLocation,
			   sizeof(CFG_POLYGON));
		memcpy(&pNodeStaffOld->CfgStaff.stuEndLocation,
			   &pNodeStaff->CfgStaff.stuEndLocation,
			   sizeof(CFG_POLYGON));
		delete pNodeStaff;
		pNodeStaff = NULL;

		//更新绘图结构体
		updateTreeRegion();
	}

	return 0;

ErrorHandle:
	if (pNodeArea)
	{
		delete pNodeArea;
		pNodeArea = NULL;
	}
	if (pNodeStaff)
	{
		delete pNodeStaff;
		pNodeStaff = NULL;
	}

	return 0;
}
/*
 *	更新绘图用de全局配置结构体信息
 */
CFG_ANALYSEGLOBAL_INFO CConfigGlobal::updateTreeRegion()
{
	CFG_ANALYSEGLOBAL_INFO stuGlobalInfo = m_pIvsGlobalPreview->getGlobalInfo();
	CFG_ANALYSEGLOBAL_INFO* pGlobalInfo = &stuGlobalInfo;//m_pIvsGlobalPreview->getGlobalInfo();


	int nAreaCnt = 0;
	int nStaffCnt = 0;
	TCHAR szItem[32] = {0};

	HTREEITEM hItem = m_treeRegion.GetRootItem();
	if (!hItem)
	{
		m_pIvsGlobalPreview->setGlobalInfo(NULL, TRUE);
		return stuGlobalInfo;
	}

	for (int i = 0; i < MAX_CALIBRATEBOX_NUM; i++)
	{
		ZeroMemory(&pGlobalInfo->stuCalibrateArea[i].stuArea, sizeof(CFG_REGION));
		pGlobalInfo->stuCalibrateArea[i].nStaffNum = 0;
		ZeroMemory(pGlobalInfo->stuStaffs, sizeof(CFG_STAFF) * MAX_STAFF_NUM);
	}

	while(hItem)
	{
		nStaffCnt = 0;

		_sntprintf(szItem, 
				   _countof(szItem), 
				   ConvertString(_T("%s%d")),
				   ConvertString(_T("CalibrateZone")), 
				   nAreaCnt + 1);
		m_treeRegion.SetItemText(hItem, szItem);

		GTNODEAREA* pNodeArea = (GTNODEAREA*)m_treeRegion.GetItemData(hItem);
		if (pNodeArea)
		{
			pNodeArea->CfgCalibrateAreaInfo.nStaffNum = 0;
			ZeroMemory(pNodeArea->CfgCalibrateAreaInfo.stuStaffs,
					   sizeof(CFG_STAFF) * MAX_STAFF_NUM);
			memcpy(&pGlobalInfo->stuCalibrateArea[nAreaCnt],
				   &pNodeArea->CfgCalibrateAreaInfo,
				   sizeof(CFG_CALIBRATEAREA_INFO));

			HTREEITEM hChild = m_treeRegion.GetChildItem(hItem);
			while(hChild)
			{
				GTNODESTAFF* pStaff = (GTNODESTAFF*)m_treeRegion.GetItemData(hChild);
				if (pStaff)
				{
					pGlobalInfo->stuCalibrateArea[nAreaCnt].nStaffNum++;
					memcpy(&pGlobalInfo->stuCalibrateArea[nAreaCnt].stuStaffs[nStaffCnt],
						   &pStaff->CfgStaff,
						   sizeof(CFG_STAFF));
					pNodeArea->CfgCalibrateAreaInfo.nStaffNum++;
					memcpy(&pNodeArea->CfgCalibrateAreaInfo.stuStaffs[nStaffCnt],
						   &pStaff->CfgStaff,
						   sizeof(CFG_STAFF));

					nStaffCnt++;
				}
				hChild = m_treeRegion.GetNextSiblingItem(hChild);
			}

			nAreaCnt++;
		}

		ZeroMemory(szItem, _countof(szItem));
		hItem = m_treeRegion.GetNextSiblingItem(hItem);
	}

	pGlobalInfo->nCalibrateAreaNum = nAreaCnt;

	m_pIvsGlobalPreview->setGlobalInfo(pGlobalInfo, FALSE);

	return stuGlobalInfo;
}
/////////////////////////////////////////////////////////////////////////////
// CConfigGlobal message handlers

BOOL CConfigGlobal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	CRect rt;
	GetDlgItem(IDC_CFGGLO_STATIC_PREVIEW)->GetWindowRect(&rt);
	ScreenToClient(&rt);

	m_pIvsGlobalPreview = new CIvsGlobalPreview;
	if (m_pIvsGlobalPreview)
	{
		m_pIvsGlobalPreview->Create(NULL,
									NULL,
									WS_CHILD,
									CRect(0, 0, 0, 0),
									this,
									5000);
		m_pIvsGlobalPreview->MoveWindow(&rt);
		m_pIvsGlobalPreview->ShowWindow(SW_SHOW);
	}

	GetDlgItem(IDC_CFGGLO_BTN_ADDRULER)->EnableWindow(FALSE);
	GetDlgItem(IDC_CFGGLO_BTN_DELRULER)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigGlobal::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pIvsGlobalPreview)
	{
		if (m_pIvsGlobalPreview->GetSafeHwnd())
		{
			m_pIvsGlobalPreview->DestroyWindow();
		}
		
		delete m_pIvsGlobalPreview;
		m_pIvsGlobalPreview = NULL;
	}

	HTREEITEM hItem = m_treeRegion.GetRootItem();
	while(hItem)
	{
		HTREEITEM hChild = m_treeRegion.GetChildItem(hItem);
		while(hChild)
		{
			GTNODESTAFF* pStaff = (GTNODESTAFF*)m_treeRegion.GetItemData(hChild);
			if (pStaff)
			{
				delete pStaff;
				pStaff = NULL;
			}
			hChild = m_treeRegion.GetNextSiblingItem(hChild);
		}

		GTNODEAREA* pArea = (GTNODEAREA*)m_treeRegion.GetItemData(hItem);
		if (pArea)
		{
			delete pArea;
			pArea = NULL;
		}
		hItem = m_treeRegion.GetNextSiblingItem(hItem);
	}
}

/*
 *	
 */
void CConfigGlobal::initGlobalDlg(int nChannel)
{
	if (nChannel == -1)
	{
		uninitGlobalDlg();
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}	

	TCHAR szChnName[32] = {0};
	_sntprintf(szChnName, _countof(szChnName), _T("%s%02d"), ConvertString(_T("Channel")), nChannel + 1);
	SetDlgItemText(IDC_CFGGLO_EDT_CHANNELNAME, szChnName);

	int nChnID = 0;
	CFG_CAP_ANALYSE_INFO* pDevCapInfo = pMainDlg->getCapAnalyseInfo(nChannel);
	//////////////////////////////////////////////////////////////////////////
	//2012-06-06
	int i = 0;
	CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobal = pMainDlg->getAnalyseGlobalInfo(nChannel);

	//////////////////////////////////////////////////////////////////////////
	//2012-06-08
	if (pDevCapInfo && pAnalyseGlobal)
	{
		for (int i = 0; i < pDevCapInfo->stSupportScenes.nScenes; i++)
//		for (int i = 0; i < pDevCapInfo->nSupportedSceneNum; i++)
		{
//			nChnID = m_cmbScene.AddString(ConvertString(pDevCapInfo->szSceneName[i]));
			nChnID = m_cmbScene.InsertString(-1, ConvertString(pDevCapInfo->stSupportScenes.stScenes[i].szSceneName));
			
			CFG_ANALYSEGLOBAL_INFO* pGloInfo = new CFG_ANALYSEGLOBAL_INFO;
			if (!pGloInfo)
			{
				continue;
			}
			ZeroMemory(pGloInfo, sizeof(CFG_ANALYSEGLOBAL_INFO));
			m_cmbScene.SetItemData(nChnID, (DWORD)pGloInfo);

// 			if (strcmp(pDevCapInfo->szSceneName[i],
			if (strcmp(pDevCapInfo->stSupportScenes.stScenes[i].szSceneName,
					   pAnalyseGlobal->szSceneType) == 0)
			{
				memcpy(pGloInfo, pAnalyseGlobal, sizeof(CFG_ANALYSEGLOBAL_INFO));
				m_cmbScene.SetCurSel(nChnID);
			}
		}

		GTNODEAREA* pNodeArea = NULL;
		GTNODESTAFF* pNodeStaff = NULL;
		HTREEITEM hItem = 0;

		for (int j = 0; j < pAnalyseGlobal->nCalibrateAreaNum; j++)
		{
			//标定区域节点
			TCHAR szArea[32] = {0};
			_sntprintf(szArea, _countof(szArea), _T("%s%d"), ConvertString(_T("CalibrateZone")), j + 1);
			hItem = m_treeRegion.InsertItem(szArea);
			pNodeArea = new GTNODEAREA;
			if (!pNodeArea)
			{
				continue;
			}
			pNodeArea->nNodeType = nNodeArea;
			memcpy(&pNodeArea->CfgCalibrateAreaInfo, 
				   &pAnalyseGlobal->stuCalibrateArea[j],
				   sizeof(CFG_CALIBRATEAREA_INFO));
			m_treeRegion.SetItemData(hItem, (DWORD)pNodeArea);

			//标尺节点
			for (int k = 0; k < pAnalyseGlobal->stuCalibrateArea[j].nStaffNum; k++)
			{
				ZeroMemory(szArea, sizeof(szArea));
				if (pAnalyseGlobal->stuCalibrateArea[j].stuStaffs[k].emType == EM_STAFF_TYPE_HORIZONTAL)
				{
					_sntprintf(szArea, _countof(szArea), ConvertString(_T("HorStaff")));
				}
				else if (pAnalyseGlobal->stuCalibrateArea[j].stuStaffs[k].emType == EM_STAFF_TYPE_VERTICAL)
				{
					_sntprintf(szArea, _countof(szArea), ConvertString(_T("VerStaff")));
				}
				HTREEITEM hItemStaff = m_treeRegion.InsertItem(szArea, hItem);

				pNodeStaff = new GTNODESTAFF;
				if (!pNodeStaff)
				{
					continue;
				}

				ZeroMemory(pNodeStaff, sizeof(GTNODESTAFF));
				switch(pAnalyseGlobal->stuCalibrateArea[j].stuStaffs[k].emType)
				{
				case EM_STAFF_TYPE_HORIZONTAL:
					pNodeStaff->nNodeType = nStaffHor;
					break;
				case EM_STAFF_TYPE_VERTICAL:
					pNodeStaff->nNodeType = nStaffVer;
					break;
				}

				memcpy(&pNodeStaff->CfgStaff, 
					   &pAnalyseGlobal->stuCalibrateArea[j].stuStaffs[k],
					   sizeof(CFG_STAFF));
				m_treeRegion.SetItemData(hItemStaff, (DWORD)pNodeStaff);
			}
			m_treeRegion.Expand(hItem, TVE_EXPAND);
		}

		hItem = m_treeRegion.GetRootItem();
		if (hItem)
		{
			m_treeRegion.SelectItem(hItem);
			GetDlgItem(IDC_CFGGLO_BTN_ADDRULER)->EnableWindow(TRUE);
			GetDlgItem(IDC_CFGGLO_BTN_DELRULER)->EnableWindow(FALSE);
		}
		else
		{
			m_treeRegion.SelectItem(NULL);
		}
	}
}
/*
 *	
 */
void CConfigGlobal::uninitGlobalDlg()
{
	if (m_pIvsGlobalPreview->isDrawing())
	{
		m_pIvsGlobalPreview->endDraw();
	}

	int nCount = m_cmbScene.GetCount();

	for (int i = 0; i < m_cmbScene.GetCount(); i++)
	{
		CFG_ANALYSEGLOBAL_INFO* pGloInfo = (CFG_ANALYSEGLOBAL_INFO*)m_cmbScene.GetItemData(i);
		if (pGloInfo)
		{
			delete pGloInfo;
			pGloInfo = NULL;
		}
	}
	m_cmbScene.ResetContent();

	HTREEITEM hItem = m_treeRegion.GetRootItem();
	while (hItem)
	{
		GTNODETYPE* pNodeType = (GTNODETYPE*)m_treeRegion.GetItemData(hItem);
		if (pNodeType)
		{
			if (pNodeType->nNodeType == nNodeArea)
			{
				GTNODEAREA* pArea = (GTNODEAREA*)m_treeRegion.GetItemData(hItem);
				if (pArea)
				{
					delete pArea;
					pArea = NULL;
				}

				HTREEITEM hItemChild = m_treeRegion.GetChildItem(hItem);
				while(hItemChild)
				{
					pNodeType = (GTNODETYPE*)m_treeRegion.GetItemData(hItemChild);
					if (pNodeType->nNodeType == nStaffHor
						|| pNodeType->nNodeType == nStaffVer)
					{
						GTNODESTAFF* pStaff = (GTNODESTAFF*)m_treeRegion.GetItemData(hItemChild);
						if (pStaff)
						{
							delete pStaff;
							pStaff = NULL;
						}
					}
					hItemChild = m_treeRegion.GetNextSiblingItem(hItemChild);
				}
			}
			hItem = m_treeRegion.GetNextSiblingItem(hItem);
		}
	}
	m_treeRegion.DeleteAllItems();
}

void CConfigGlobal::showPreview(LONG lLoginHanlde, int nChannel)
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
			HWND hWnd = m_pIvsGlobalPreview->GetSafeHwnd();//GetDlgItem(IDC_CFGGLO_STATIC_PREVIEW)->GetSafeHwnd();
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
				updateTreeRegion();
				bRet = s_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, 
										   CIvsGlobalPreview::drawIvsGlobalCfgProc, 
										   (DWORD)m_pIvsGlobalPreview);
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

void CConfigGlobal::closePreview(LONG lRealPlayHandle)
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
			GetDlgItem(IDC_CFGGLO_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->setRealPlayHandel(0);
		}
	}
}

// void CConfigGlobal::DrawIvsInfoGlobalProc(long nPort, HDC hdc, LONG nUser)
// {
// }
/*
 *	选择场景，选择的变化还将影响到模块配置和规则配置的内容，目前只支持两种场景，且对应的模块和规则信息相同
 */
void CConfigGlobal::OnSelchangeCfggloCmbScene() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsGlobalPreview->isDrawing())
	{
		m_pIvsGlobalPreview->endDraw();
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	CFG_CAP_ANALYSE_INFO* pCapInfo
		= pMainDlg->getCapAnalyseInfo(pMainDlg->getCurrentChannel());
	CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobal 
		= pMainDlg->getAnalyseGlobalInfo(pMainDlg->getCurrentChannel());

	if (!pCapInfo || !pAnalyseGlobal)
	{
		return;
	}

	CString strScenType;
	m_cmbScene.GetLBText(m_cmbScene.GetCurSel(), strScenType);
	if (strcmp(strScenType.GetBuffer(0), pAnalyseGlobal->szSceneType) == 0
		|| strcmp(strScenType.GetBuffer(0), ConvertString(pAnalyseGlobal->szSceneType)) == 0)
	{
		// 场景类型没有变化
		return;
	}
	else
	{
		//场景类型发生变化
		int nSel = m_cmbScene.GetCurSel();
		if (nSel != 0 && nSel != 1)
		{
			return;
		}

		strncpy(pAnalyseGlobal->szSceneType, 
				pCapInfo->stSupportScenes.stScenes[nSel].szSceneName,
				MAX_NAME_LEN);

		m_pIvsGlobalPreview->setGlobalInfo(NULL, TRUE);

		HTREEITEM hItem = m_treeRegion.GetRootItem();
		while (hItem)
		{
			GTNODETYPE* pNodeType = (GTNODETYPE*)m_treeRegion.GetItemData(hItem);
			if (pNodeType)
			{
				if (pNodeType->nNodeType == nNodeArea)
				{
					GTNODEAREA* pArea = (GTNODEAREA*)m_treeRegion.GetItemData(hItem);
					if (pArea)
					{
						delete pArea;
						pArea = NULL;
					}
					
					HTREEITEM hItemChild = m_treeRegion.GetChildItem(hItem);
					while(hItemChild)
					{
						pNodeType = (GTNODETYPE*)m_treeRegion.GetItemData(hItemChild);
						if (pNodeType->nNodeType == nStaffHor
							|| pNodeType->nNodeType == nStaffVer)
						{
							GTNODESTAFF* pStaff = (GTNODESTAFF*)m_treeRegion.GetItemData(hItemChild);
							if (pStaff)
							{
								delete pStaff;
								pStaff = NULL;
							}
						}
						hItemChild = m_treeRegion.GetNextSiblingItem(hItemChild);
					}
				}
				hItem = m_treeRegion.GetNextSiblingItem(hItem);
			}
		}
		m_treeRegion.DeleteAllItems();
	}
}
/*
 *	获取选择的标尺节点的绑定信息
 */
void CConfigGlobal::OnClickCfggloTreeRegion(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsGlobalPreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}
	
	*pResult = 0;

	CPoint pt;
	GetCursorPos(&pt);
	m_treeRegion.ScreenToClient(&pt);

	HTREEITEM hItem = m_treeRegion.HitTest(pt);
	if (hItem)
	{
		m_treeRegion.SelectItem(hItem);
		GTNODETYPE* pType = (GTNODETYPE*)m_treeRegion.GetItemData(hItem);
		if (pType->nNodeType == EM_STAFF_TYPE_HORIZONTAL
			|| pType->nNodeType == EM_STAFF_TYPE_VERTICAL)
		{
			GTNODESTAFF* pStaff = (GTNODESTAFF*)m_treeRegion.GetItemData(hItem);
			if (!pStaff)
			{
				return;
			}

			CButton* pBtn = NULL;

			switch (pStaff->nNodeType)
			{
			case EM_STAFF_TYPE_HORIZONTAL:
				pBtn = (CButton*)GetDlgItem(IDC_CFGGLO_RADIO_HRULER);
				if (pBtn)
				{
					pBtn->SetCheck(BST_CHECKED);
				}
				pBtn = (CButton*)GetDlgItem(IDC_CFGGLO_RADIO_VRULER);
				if (pBtn)
				{
					pBtn->SetCheck(BST_UNCHECKED);
				}
				break;
			case EM_STAFF_TYPE_VERTICAL:
				pBtn = (CButton*)GetDlgItem(IDC_CFGGLO_RADIO_HRULER);
				if (pBtn)
				{
					pBtn->SetCheck(BST_UNCHECKED);
				}
				pBtn = (CButton*)GetDlgItem(IDC_CFGGLO_RADIO_VRULER);
				if (pBtn)
				{
					pBtn->SetCheck(BST_CHECKED);
				}
				break;
			}

			CString strLen;
			strLen.Format(_T("%f"), pStaff->CfgStaff.nLenth);
			SetDlgItemText(IDC_CFGGLO_EDT_REALLEN, strLen);

			GetDlgItem(IDC_CFGGLO_BTN_ADDRULER)->EnableWindow(FALSE);
			GetDlgItem(IDC_CFGGLO_BTN_DELRULER)->EnableWindow(TRUE);
		}

		if (pType->nNodeType == nNodeArea)
		{
			GetDlgItem(IDC_CFGGLO_BTN_ADDRULER)->EnableWindow(TRUE);
			GetDlgItem(IDC_CFGGLO_BTN_DELRULER)->EnableWindow(FALSE);
		}
	} 
	else
	{
		m_treeRegion.SelectItem(NULL);
	}
}
/*
 *	添加标定区域
 */
void CConfigGlobal::OnCfggloBtnAddaera() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsGlobalPreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	HTREEITEM hZoneItem = m_treeRegion.GetRootItem();
	int nCnt = 0;
	while(hZoneItem)
	{
		nCnt++;
		hZoneItem = m_treeRegion.GetNextSiblingItem(hZoneItem);
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	CFG_CAP_ANALYSE_INFO* pCapInfo 
		= (CFG_CAP_ANALYSE_INFO*)pMainDlg->getCapAnalyseInfo(pMainDlg->getCurrentChannel());
	if (!pCapInfo)
	{
		return;
	}

	int nMaxAreaNum
		= pCapInfo->stSupportScenes.stScenes[m_cmbScene.GetCurSel()].nMaxCalibrateAreaNum;
	if (nCnt >= nMaxAreaNum)
	{
		AfxMessageBox(ConvertString(_T("Can't add CalibrateZone any more")));
		return;
	}

	//添加标定区域节点
	TCHAR szItem[32] = {0};
	_sntprintf(szItem, _countof(szItem), _T("%s%d"), ConvertString(_T("CalibrateZone")), nCnt + 1);

	HTREEITEM hItemZone = m_treeRegion.InsertItem(szItem);
	GTNODEAREA* pNodeArea = new GTNODEAREA;
	if (!pNodeArea)
	{
		m_treeRegion.DeleteItem(hItemZone);
		return;
	}
	ZeroMemory(pNodeArea, sizeof(GTNODEAREA));
	pNodeArea->nNodeType = nNodeArea;
	m_treeRegion.SetItemData(hItemZone, (DWORD)pNodeArea);

	//开始绘图
	m_pIvsGlobalPreview->beginDraw(hItemZone, EM_STAFF_TYPE_ERR);
}
/*
 *	添加标尺
 */
void CConfigGlobal::OnCfggloBtnAddruler() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsGlobalPreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	HTREEITEM hAreaItem = m_treeRegion.GetSelectedItem();
	if (!hAreaItem)
	{
		return;
	}
	GTNODETYPE* pNodeType = (GTNODETYPE*)m_treeRegion.GetItemData(hAreaItem);
	if (!pNodeType)
	{
		return;
	}

	if (pNodeType->nNodeType != nNodeArea)
	{
		return;
	}

	int nCnt = 0;
	HTREEITEM hItem = m_treeRegion.GetChildItem(hAreaItem);
	while(hItem)
	{
		nCnt++;
		hItem = m_treeRegion.GetNextSiblingItem(hItem);
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	
	CFG_CAP_ANALYSE_INFO* pCapInfo 
		= (CFG_CAP_ANALYSE_INFO*)pMainDlg->getCapAnalyseInfo(pMainDlg->getCurrentChannel());
	if (!pCapInfo)
	{
		return;
	}

	if (nCnt >= pCapInfo->nMaxRules)
	{
		AfxMessageBox(ConvertString(_T("Can't add staff any more")));
		return;
	}

	//添加标定区域标尺节点	
	HTREEITEM hItemStaff = 0;
	GTNODESTAFF* pNodeStaff = new GTNODESTAFF;
	if (!pNodeStaff)
	{
		return;
	}

	CString strLen;
	GetDlgItemText(IDC_CFGGLO_EDT_REALLEN, strLen);
	if (!strLen.GetLength())
	{
		AfxMessageBox(ConvertString(_T("Staff's length error")));
		delete pNodeStaff;
		return;
	}



	pNodeStaff->CfgStaff.nLenth
		= atof(strLen.GetBuffer(strLen.GetLength()));

	CButton* pBtn = (CButton*)GetDlgItem(IDC_CFGGLO_RADIO_HRULER);
	if (pBtn->GetCheck())
	{
		hItemStaff = m_treeRegion.InsertItem(ConvertString(_T("HorStaff")), hAreaItem);
		pNodeStaff->nNodeType = nStaffHor;
		pNodeStaff->CfgStaff.emType = EM_STAFF_TYPE_HORIZONTAL;
	}
	
	pBtn = (CButton*)GetDlgItem(IDC_CFGGLO_RADIO_VRULER);
	if (pBtn->GetCheck())
	{
		hItemStaff = m_treeRegion.InsertItem(ConvertString(_T("VerStaff")), hAreaItem);
		pNodeStaff->nNodeType = nStaffVer;
		pNodeStaff->CfgStaff.emType = EM_STAFF_TYPE_VERTICAL;
	}
	m_treeRegion.SetItemData(hItemStaff, (DWORD)pNodeStaff);
	
	//开始绘图
	m_pIvsGlobalPreview->beginDraw(hItemStaff, pNodeStaff->CfgStaff.emType);
}
/*
 *	删除标定区域
 */
void CConfigGlobal::OnCfggloBtnDelarea() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsGlobalPreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	HTREEITEM hItem = m_treeRegion.GetSelectedItem();
	if (!hItem)
	{
		return;
	}
	
	GTNODETYPE* pNode = (GTNODETYPE*)m_treeRegion.GetItemData(hItem);
	if (pNode->nNodeType != nNodeArea)
	{
		return;
	}
	
	GTNODEAREA* pArea = (GTNODEAREA*)m_treeRegion.GetItemData(hItem);
	
	HTREEITEM hChild = m_treeRegion.GetChildItem(hItem);
	while(hChild)
	{
		GTNODESTAFF* pStaff = (GTNODESTAFF*)m_treeRegion.GetItemData(hChild);
		if (pStaff)
		{
			delete pStaff;
			pStaff = NULL;
		}
		hChild = m_treeRegion.GetNextSiblingItem(hChild);
	}
	
	delete pArea;
	pArea = NULL;
	m_treeRegion.DeleteItem(hItem);

	updateTreeRegion();	
}
/*
 *	删除标尺
 */
void CConfigGlobal::OnCfggloBtnDelruler() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsGlobalPreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	HTREEITEM hItem = m_treeRegion.GetSelectedItem();
	if (!hItem)
	{
		return;
	}
	
	GTNODETYPE* pNode = (GTNODETYPE*)m_treeRegion.GetItemData(hItem);
	if (pNode->nNodeType == nStaffVer
		|| pNode->nNodeType == nStaffHor)
	{
		GTNODESTAFF* pStaff = (GTNODESTAFF*)m_treeRegion.GetItemData(hItem);
		if (pStaff)
		{
			delete pStaff;
			pStaff = NULL;
		}

		m_treeRegion.DeleteItem(hItem);

		updateTreeRegion();
	}	
}
/*
 *	重新从设备获取全局配置信息，并更新到界面
 */
void CConfigGlobal::OnCfggloBtnGet() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsGlobalPreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	int nChannel = pMainDlg->getCurrentChannel();
	CFG_ANALYSEGLOBAL_INFO* pGlobalInfo
		= (CFG_ANALYSEGLOBAL_INFO*)pMainDlg->getAnalyseGlobalInfo(nChannel);
	if (nChannel < 0 || !pGlobalInfo)
	{
		return;
	}
	
	int nErr = 0;
	char szOutBuffer[32 * 1024] = {0};
	
	// get global info
	BOOL bSuccess
		= CLIENT_GetNewDevConfig(pMainDlg->getLoginHandle(), 
								CFG_CMD_ANALYSEGLOBAL, 
								nChannel,
								szOutBuffer, 
								32 * 1024, 
								&nErr);
	if (bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet
			= CLIENT_ParseData(CFG_CMD_ANALYSEGLOBAL, 
							   szOutBuffer, 
							   (char*)pGlobalInfo, 
						   	   sizeof(CFG_ANALYSEGLOBAL_INFO),
							   &nRetLen);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Parser data error"), ConvertString("Prompt"));
			return;
		}
	}//if(bSuccess)
	else
	{
		MessageBox(ConvertString("Get GlobalInfo failed"), ConvertString("Prompt"));
		return;
	}

	closePreview(pMainDlg->getRealPlayHandle());
	uninitGlobalDlg();

	initGlobalDlg(nChannel);
	m_pIvsGlobalPreview->setGlobalInfo(NULL, TRUE);
	m_pIvsGlobalPreview->Invalidate(FALSE);
	showPreview(pMainDlg->getLoginHandle(), nChannel);
}
/*
 *	将界面上的配置信息打包上传到设备
 */
void CConfigGlobal::OnCfggloBtnSet() 
{
	// TODO: Add your control notification handler code here
	// 如果正在绘图，需要先结束绘图
	if (m_pIvsGlobalPreview->isDrawing())
	{
		AfxMessageBox(ConvertString(_T("You haven't draw it yet")));
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	
	int nChannel = pMainDlg->getCurrentChannel();
	CFG_ANALYSEGLOBAL_INFO* pGlobalInfo
		= (CFG_ANALYSEGLOBAL_INFO*)pMainDlg->getAnalyseGlobalInfo(nChannel);
	CFG_CAP_ANALYSE_INFO* pCap = pMainDlg->getCapAnalyseInfo(nChannel);
	if (nChannel < 0 || !pGlobalInfo || !pCap)
	{
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	//
	int nSel = m_cmbScene.GetCurSel();
	if (nSel != 0 && nSel != 1)
	{
		return;
	}
	
	strncpy(pGlobalInfo->szSceneType,
			pCap->stSupportScenes.stScenes[nSel].szSceneName,
			MAX_NAME_LEN);

	HTREEITEM hAreaItem = m_treeRegion.GetRootItem();
// 	if (!hAreaItem)
// 	{
// 		return;
// 	}

	//填入标定区域信息
	ZeroMemory(pGlobalInfo->stuCalibrateArea,
			   sizeof(CFG_CALIBRATEAREA_INFO) * MAX_CALIBRATEBOX_NUM);
	pGlobalInfo->nCalibrateAreaNum = 0;
	int nAreaNum = 0;

	while(hAreaItem)
	{
		GTNODEAREA* pArea = (GTNODEAREA*)m_treeRegion.GetItemData(hAreaItem);
		if (!pArea)
		{
			hAreaItem = m_treeRegion.GetNextSiblingItem(hAreaItem);
			continue;
		}

		memcpy(&pGlobalInfo->stuCalibrateArea[nAreaNum],
			   &pArea->CfgCalibrateAreaInfo,
			   sizeof(CFG_CALIBRATEAREA_INFO));
		pGlobalInfo->nCalibrateAreaNum++;

		hAreaItem = m_treeRegion.GetNextSiblingItem(hAreaItem);
		nAreaNum++;

		HTREEITEM hStaff = m_treeRegion.GetChildItem(hAreaItem);
		if (!hStaff)
		{
			continue;
		}

		//填入标尺信息
		ZeroMemory(pGlobalInfo->stuCalibrateArea[nAreaNum].stuStaffs,
				   sizeof(CFG_STAFF) * MAX_STAFF_NUM);
		pGlobalInfo->stuCalibrateArea[nAreaNum].nStaffNum = 0;
		int nStaffNum = 0;

		while(hStaff)
		{
			GTNODESTAFF* pStaff = (GTNODESTAFF*)m_treeRegion.GetItemData(hStaff);
			if (!pStaff)
			{
				hStaff = m_treeRegion.GetNextSiblingItem(hStaff);
				continue;
			}

			memcpy(&pGlobalInfo->stuCalibrateArea[nAreaNum].stuStaffs[nStaffNum],
				   &pStaff->CfgStaff,
				   sizeof(CFG_STAFF));

			hStaff = m_treeRegion.GetNextSiblingItem(hStaff);
			nStaffNum++;
		}

		pGlobalInfo->stuCalibrateArea[nAreaNum].nStaffNum = nStaffNum;

	}

	pGlobalInfo->nCalibrateAreaNum = nAreaNum;
	
	int nErr = 0;
	char szOutBuffer[32 * 1024] = {0};
	
	// set global info
	BOOL bRet
		= CLIENT_PacketData(CFG_CMD_ANALYSEGLOBAL, 
							(LPVOID)pGlobalInfo,
							sizeof(CFG_ANALYSEGLOBAL_INFO),
							szOutBuffer,  
							32 * 1024);
	if (!bRet)
	{
		AfxMessageBox(ConvertString(_T("Packet data error")));
		return;
	}
	
	int nRetLen = 0;
	bRet = CLIENT_SetNewDevConfig(pMainDlg->getLoginHandle(), 
								  CFG_CMD_ANALYSEGLOBAL, 
								  nChannel,
								  szOutBuffer, 
								  32 * 1024, 
								  &nErr,
								  &nRetLen);
	if (bRet)
	{
		AfxMessageBox(ConvertString(_T("Set GlobalInfo Successfully")));
	}
	else
	{
		AfxMessageBox(ConvertString(_T("Set GlobalInfo Failed")));
		return;
	}
}
