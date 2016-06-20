// ConfigModule.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "Video Analyse ConfigurationDlg.h"
#include "ConfigModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigModule dialog


CConfigModule::CConfigModule(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigModule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigModule)
	m_bSnapEnable = FALSE;
	m_nMaxSizeWidth = 0;
	m_nMinSizeWidth = 0;
	m_nMaxSizeHight = 0;
	m_nMinSizeHight = 0;
	m_nMaxSizeArea = 0;
	m_nMinSizeArea = 0;
	m_nDRX = 0;
	m_nDRY = 0;
	m_nTRX = 0;
	m_nTRY = 0;
	//}}AFX_DATA_INIT
	m_nChannelCount = 0;
	m_nCurrentChannel = 0;
	m_nCurrentModule = 0;
	m_nCurrentDRLine = 0;
	m_nCurrentTRLine = 0;
	m_lLoginId = 0;
	m_nShowType = -1;
	
	memset(m_gModules, 0, sizeof(CFG_ANALYSEMODULES_INFO)*MAX_CHANNEL_NUM);
	m_nMaxModeuleNum = 0;
	m_nMaxPointOfRegion = 0;
	m_nSupportedObjTypeNum = 0;
	memset(m_gObjectTypeName, 0, sizeof(char) * MAX_OBJECT_LIST_SIZE * MAX_NAME_LEN);  
	m_pCurModuleInfo = NULL;
}


void CConfigModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigModule)
	DDX_Control(pDX, IDC_TREE_MODULE, m_treeModule);
	DDX_Control(pDX, IDC_COMBO_OBJTYPE, m_cbObjTypes);
	DDX_Control(pDX, IDC_COMBO_FILTERTYPE_M, m_cbFilterType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_M, m_cbChannel);
	DDX_Check(pDX, IDC_CHECK_SNAP_M, m_bSnapEnable);
	DDX_Text(pDX, IDC_EDIT_MAXSY_M, m_nMaxSizeWidth);
	DDX_Text(pDX, IDC_EDIT_MINSY_M, m_nMinSizeWidth);
	DDX_Text(pDX, IDC_EDIT_MAXSX_M, m_nMaxSizeHight);
	DDX_Text(pDX, IDC_EDIT_MINSX_M, m_nMinSizeHight);
	DDX_Text(pDX, IDC_EDIT_MAXSA_M, m_nMaxSizeArea);
	DDX_Text(pDX, IDC_EDIT_MINSA_M, m_nMinSizeArea);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigModule, CDialog)
	//{{AFX_MSG_MAP(CConfigModule)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_M, OnButtonRefreshM)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_M, OnButtonSaveM)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_M, OnSelchangeComboChannelM)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTERTYPE_M, OnSelchangeComboFiltertypeM)
	ON_BN_CLICKED(IDC_BUTTON_ADDMOD, OnButtonAddmod)
	ON_BN_CLICKED(IDC_BUTTON_DELETSELMOD, OnButtonDeletselmod)
	ON_BN_CLICKED(IDC_BUTTON_SET_DETECTREGION, OnButtonSetDetectregion)
//	ON_BN_CLICKED(IDC_BUTTON_SET_TRACKREGION, OnButtonSetTrackregion)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_MODULE, OnSelchangedTreeModule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigModule message handlers

BOOL CConfigModule::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	memset(m_gModules, 0, sizeof(CFG_ANALYSEMODULES_INFO) * MAX_CHANNEL_NUM);


	HTREEITEM hRoot = m_treeModule.InsertItem(ConvertString("AllModule"), NULL, NULL);
	m_treeModule.SetItemData(hRoot, NULL);
	m_treeModule.Expand(hRoot, TVE_EXPAND);


	return TRUE;
}

void CConfigModule::OnButtonRefreshM() 
{
	Refresh();
}

void CConfigModule::OnButtonSaveM() 
{
	BOOL bRet = UpdateData(TRUE);
	if (!bRet)
	{
		return;
	}

	this->SaveModuleByPoint(m_pCurModuleInfo);

	if (-1 != m_cbChannel.GetCurSel())
	{
		HTREEITEM hRoot = m_treeModule.GetRootItem();
		HTREEITEM hCurItem = m_treeModule.GetChildItem(hRoot);
		int index = 0;
		while(hCurItem != NULL)
		{
			CFG_MODULE_INFO* pModuleInfo = (CFG_MODULE_INFO*)(m_treeModule.GetItemData(hCurItem));
			if (pModuleInfo == NULL)
			{
				return;
			}
			memcpy(&(m_gModules[m_nCurrentChannel].stuModuleInfo[index]), pModuleInfo, sizeof(CFG_MODULE_INFO));

			hCurItem = m_treeModule.GetNextItem(hCurItem, TVGN_NEXT);
			index++;
		}

		m_gModules[m_nCurrentChannel].nMoudlesNum = index;

		//SaveChannelModule(m_nCurrentChannel);
		((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->SetModule(m_nCurrentChannel, 
		m_gModules[m_nCurrentChannel]);
	}
	else
	{
		MessageBox(ConvertString("please select the channel!"), ConvertString("Prompt"));
	}
	
}


void CConfigModule::OnSelchangeComboChannelM() 
{
	SaveChannelModule(m_nCurrentChannel);

	if (-1 != m_cbChannel.GetCurSel())
	{
		GetDevCapInfo();

		m_nCurrentChannel = m_cbChannel.GetCurSel();
		ShowChannelModule(m_nCurrentChannel);
	}
}

// 0:"ByLength",1:"ByArea"
void CConfigModule::ChangeUIForFilter(bool bEnableAll)
{	
	if (bEnableAll)
	{
		GetDlgItem(IDC_EDIT_MINSA_M)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAXSA_M)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MINSX_M)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MINSY_M)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAXSX_M)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAXSY_M)->EnableWindow(TRUE);
		return;
	}

	int nIndex = m_cbFilterType.GetCurSel();
	int nItemData = m_cbFilterType.GetItemData(nIndex);
	if (nItemData == 0)
	{
		GetDlgItem(IDC_EDIT_MINSA_M)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAXSA_M)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_EDIT_MINSX_M)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MINSY_M)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAXSX_M)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAXSY_M)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MINSA_M)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAXSA_M)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_EDIT_MINSX_M)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MINSY_M)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAXSX_M)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAXSY_M)->EnableWindow(FALSE);
	}
	return;
}

void CConfigModule::CleanTree()
{
	HTREEITEM hRoot = m_treeModule.GetRootItem();
	HTREEITEM hCurItem = m_treeModule.GetChildItem(hRoot);
	HTREEITEM hNextItem;
	DWORD dwData = 0;
	while(hCurItem != NULL)
	{
		dwData = m_treeModule.GetItemData(hCurItem);
		hNextItem = m_treeModule.GetNextItem(hCurItem, TVGN_NEXT);
		m_treeModule.DeleteItem(hCurItem);
		hCurItem = hNextItem;
		if (dwData != NULL)
		{
			CFG_MODULE_INFO* pModInfo = (CFG_MODULE_INFO*) dwData;
			delete pModInfo;
			pModInfo = NULL;
		}
	}
	m_treeModule.DeleteItem(hRoot);
	hRoot = m_treeModule.InsertItem(ConvertString("AllModule"), NULL, NULL);
	m_treeModule.SetItemData(hRoot, NULL);
	m_pCurModuleInfo = NULL;
}


void CConfigModule::OnSelchangeComboFiltertypeM() 
{
	ChangeUIForFilter();	
}

void CConfigModule::OnButtonAddmod() 
{
	if (m_treeModule.GetCount() - 1 >= m_nMaxModeuleNum)
	{
	 	MessageBox(ConvertString("add failed! The module number has reached the max!"), ConvertString("Prompt"));
	 	return;
 	}
 	
	HTREEITEM hRoot = m_treeModule.GetRootItem();
	char szBuffer[32] = {0};
	CString strModule;
	strModule = ConvertString("module") + itoa(	m_nCurrentNumber++, szBuffer, 10);
	HTREEITEM hInsertItem = m_treeModule.InsertItem(strModule, hRoot, NULL);
	CFG_MODULE_INFO* module = new CFG_MODULE_INFO;
	memset(module, 0, sizeof(CFG_MODULE_INFO));
	m_treeModule.SetItemData(hInsertItem, (DWORD)(module));
	m_treeModule.Expand(hRoot, TVE_EXPAND);

	m_treeModule.SelectItem(hInsertItem);
	m_treeModule.SetFocus();

	ShowModuleByPoint(module);


}

void CConfigModule::OnButtonDeletselmod() 
{
	HTREEITEM hSelItem = m_treeModule.GetSelectedItem();
	if (hSelItem == m_treeModule.GetRootItem() || hSelItem == NULL)
	{
		return;
	}


	HTREEITEM hPrevSlibingItem = m_treeModule.GetPrevSiblingItem(hSelItem);
	HTREEITEM hNextSlibingItem = m_treeModule.GetNextSiblingItem(hSelItem);
	HTREEITEM hItem = NULL; 
	hItem = (hPrevSlibingItem == NULL) ? (hNextSlibingItem) : (hPrevSlibingItem);
	if (hItem == NULL)
	{
		m_pCurModuleInfo = NULL;
	}
	else
	{
		m_pCurModuleInfo = (CFG_MODULE_INFO*)(m_treeModule.GetItemData(hItem));
		this->ShowModuleByPoint(m_pCurModuleInfo);
		m_treeModule.SelectItem(hItem);
		m_treeModule.SetFocus();

	}

	CFG_MODULE_INFO* p = (CFG_MODULE_INFO*)(m_treeModule.GetItemData(hSelItem));
	m_treeModule.DeleteItem(hSelItem);
	if (p != NULL)
	{
		delete p;
		p = NULL;
	}
 

	//Clean UI, when delete last item
	HTREEITEM hRoot = m_treeModule.GetRootItem();
	HTREEITEM hChild = m_treeModule.GetChildItem(hRoot);
	if (hChild == NULL)
	{
		this->ClearModuleInfo();
		return;
	}

}

void CConfigModule::Init(int nChannelCount)
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
	GetDevCapInfo();

	// show module info
	Refresh();
} 

void CConfigModule::GetDevCapInfo()
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
		m_nMaxModeuleNum = pDeviceCap->nMaxMoudles;
		m_nMaxPointOfRegion = pDeviceCap->nMaxPointOfRegion;
		m_nSupportedObjTypeNum = pDeviceCap->nSupportedObjectTypeNum;
		memcpy(m_gObjectTypeName, pDeviceCap->szObjectTypeName, MAX_OBJECT_LIST_SIZE * MAX_NAME_LEN * sizeof(char));
	}

	m_cbObjTypes.ResetContent();//m_nSupportedObjTypeNum
	for(int i = 0; i < m_nSupportedObjTypeNum; i++)
	{
		nChannelId = m_cbObjTypes.AddString(ConvertString(m_gObjectTypeName[i]));
		m_cbObjTypes.SetItemData(nChannelId, i);
	}

	m_lLoginId = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetLoginID();
}

void CConfigModule::Refresh()
{
	// show
	ShowChannelModule(m_nCurrentChannel);
}

void CConfigModule::Clear()
{	
	m_cbChannel.ResetContent();
	m_cbObjTypes.ResetContent();
	m_nMaxModeuleNum = 0;
	m_nMaxPointOfRegion = 0;
	m_nSupportedObjTypeNum = 0;
	m_nCurrentChannel = -1;

	ClearModuleInfo();
}

void CConfigModule::ClearModuleInfo()
{
	m_nMaxSizeHight = 0;
	m_nMaxSizeWidth = 0;
	m_nMinSizeHight = 0;
	m_nMinSizeWidth = 0;
	
	UpdateData(FALSE);
	
	m_bSnapEnable = FALSE;
	
	m_cbFilterType.ResetContent();
	((CButton*)(GetDlgItem(IDC_CHECK_SNAP_M)))->SetCheck(0);

	CleanTree();

	ChangeUIForFilter(true);
	return;
}

void CConfigModule::ClearList(CListCtrl* lcList)
{
	lcList->DeleteAllItems();
	if (lcList->GetHeaderCtrl())
	{
		int nColumCount = lcList->GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < nColumCount; i++)
		{
			lcList->DeleteColumn(0);
		}
	}
}

void CConfigModule::ShowChannelModule(int nChannelId)
{
	if (nChannelId == -1)
	{
		return;
	}
	// get info
	BOOL bSuccess = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetModule(nChannelId, 
		m_gModules[nChannelId]);
	if (!bSuccess)
	{
		return;
	}
	
	// show info
	int nModuleCount = m_gModules[nChannelId].nMoudlesNum;
	int nIndex = 0;
	char szBuffer[32] = {0};

	CleanTree();

	int i = 0;
	for (i = 0; i < nModuleCount; i++)
	{
		CString strModule;
		strModule = ConvertString("module") + itoa(i, szBuffer, 10);
		HTREEITEM hRoot = m_treeModule.GetRootItem();
		HTREEITEM hInsertItem = m_treeModule.InsertItem(strModule, hRoot, NULL);

		CFG_MODULE_INFO* module = new CFG_MODULE_INFO;
		memcpy(module, &(m_gModules[nChannelId].stuModuleInfo), sizeof(CFG_MODULE_INFO));
		m_treeModule.SetItemData(hInsertItem, (DWORD)(module));

		if (m_pCurModuleInfo == NULL)
		{
			m_pCurModuleInfo = module;
			m_treeModule.SelectItem(hInsertItem);
			m_treeModule.SetFocus();
		}
	}
	
	HTREEITEM hRoot = m_treeModule.GetRootItem();
	m_treeModule.Expand(hRoot, TVE_EXPAND);

	m_nCurrentNumber = nModuleCount;

	if (m_gModules[m_nCurrentChannel].nMoudlesNum)
	{
		ShowModuleByPoint(&(m_gModules[m_nCurrentChannel].stuModuleInfo[0]));
		
	}
}

void CConfigModule::SaveModuleByPoint(CFG_MODULE_INFO* pModuleInfo)
{
	if (pModuleInfo == NULL)
	{
		return;
	}

	UpdateData(TRUE);

	int nSel = m_cbObjTypes.GetCurSel();
	strcpy(pModuleInfo->szObjectType, m_gObjectTypeName[nSel]);

	pModuleInfo->bSnapShot = m_bSnapEnable;
	nSel = m_cbFilterType.GetCurSel();
	pModuleInfo->nFilterType = m_cbFilterType.GetItemData(nSel);
	if (pModuleInfo->nFilterType == 0)
	{
		pModuleInfo->bFilterMaxSizeEnable = true;
		pModuleInfo->bFilterMinSizeEnable = true;
		pModuleInfo->stuFilterMaxSize.nHeight = m_nMaxSizeHight;
		pModuleInfo->stuFilterMaxSize.nWidth = m_nMaxSizeWidth;
		pModuleInfo->stuFilterMinSize.nHeight = m_nMinSizeHight;
		pModuleInfo->stuFilterMinSize.nWidth = m_nMinSizeWidth;
	}
	else
	{
		pModuleInfo->stuFilterMaxSize.nArea = m_nMaxSizeArea;
		pModuleInfo->stuFilterMinSize.nArea = m_nMinSizeArea;
	}

	return;
}

void CConfigModule::ShowModuleByPoint(CFG_MODULE_INFO* pModuleInfo)
{
	if (pModuleInfo == NULL)
	{
		return;
	}

	for(int i = 0; i < MAX_OBJECT_LIST_SIZE; i++)
	{

		if (strcmp(pModuleInfo->szObjectType, m_gObjectTypeName[i]) == 0)
		{
			m_cbObjTypes.SetCurSel(i);
		}
	}
	
	m_bSnapEnable = pModuleInfo->bSnapShot;
	m_cbFilterType.ResetContent();
	int nIndex = m_cbFilterType.AddString(ConvertString("ByLength"));
	m_cbFilterType.SetItemData(nIndex, 0);
	nIndex = m_cbFilterType.AddString(ConvertString("ByArea"));
	m_cbFilterType.SetItemData(nIndex, 1);
	m_cbFilterType.SetCurSel(pModuleInfo->nFilterType);
	
	// 0:"ByLength",1:"ByArea"
	if (pModuleInfo->nFilterType == 0)
	{
		m_nMaxSizeHight = pModuleInfo->stuFilterMaxSize.nHeight;
		m_nMaxSizeWidth = pModuleInfo->stuFilterMaxSize.nWidth;
		
		m_nMinSizeHight = pModuleInfo->stuFilterMinSize.nHeight;
		m_nMinSizeWidth = pModuleInfo->stuFilterMinSize.nWidth;
	}
	else
	{
		m_nMaxSizeArea = pModuleInfo->stuFilterMaxSize.nArea;
		m_nMinSizeArea = pModuleInfo->stuFilterMinSize.nArea;
	}
	
	ChangeUIForFilter();
	UpdateData(FALSE);
	return;
}

void CConfigModule::SaveChannelModule(int nChannelId)
{
	UpdateData(TRUE);
	// save info
	SaveModule(m_nCurrentModule, m_gModules[m_nCurrentChannel]);
}

void CConfigModule::SaveModule(int nModuleId, CFG_ANALYSEMODULES_INFO &stuModuleInfo)
{
	int nIndex = m_cbObjTypes.GetCurSel();
	if (nIndex != -1)
	{
		memcpy(stuModuleInfo.stuModuleInfo[nModuleId].szObjectType, m_gObjectTypeName[nIndex], sizeof(char) * MAX_NAME_LEN);
	}
	
	if (m_bSnapEnable)
	{
		stuModuleInfo.stuModuleInfo[nModuleId].bSnapShot = true;
	}
	else
	{
		stuModuleInfo.stuModuleInfo[nModuleId].bSnapShot = false;
	}

	stuModuleInfo.stuModuleInfo[nModuleId].nFilterType = m_cbFilterType.GetCurSel();
	
	// 0:"ByLength",1:"ByArea"
	if (stuModuleInfo.stuModuleInfo[nModuleId].nFilterType == 0)
	{
		stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMaxSize.nHeight = m_nMaxSizeHight;
		stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMaxSize.nWidth = m_nMaxSizeWidth;
		
		stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMinSize.nHeight = m_nMinSizeHight;
		stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMinSize.nWidth = m_nMinSizeWidth;
	}
	else
	{
		stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMaxSize.nArea = m_nMaxSizeArea;
		stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMinSize.nArea = m_nMinSizeArea;
	}

	return;
}

void CConfigModule::InPutExitLinesToPicture(CPictrueDialog* pPicShow, float fProportionX, float fProportionY)
{
	if (m_pCurModuleInfo == NULL || pPicShow == NULL)
	{
		return;
	}

	MAPCROSSLINE* pMapLine = &(pPicShow->m_DrawObjectList);
	CString strLineName;
	
	int nPointNum = 0;
	POINT *pLinePoint= NULL; 

	nPointNum = m_pCurModuleInfo->nTrackRegionPoint;
	pLinePoint = new POINT[nPointNum]; 
	int i = 0;
	for(i = 0; i < nPointNum; i++)
	{
		pLinePoint[i].x = m_pCurModuleInfo->stuTrackRegion[i].nX * fProportionX;
		pLinePoint[i].y = m_pCurModuleInfo->stuTrackRegion[i].nY * fProportionY;
	}
	CDrawLines* cDrawObject = new CDrawLines(pLinePoint, nPointNum, eTrackRegion);
	(*pMapLine)[eTrackRegion].push_back(cDrawObject);
	cDrawObject = NULL;
	if (pLinePoint != NULL)
	{
		delete pLinePoint;
		pLinePoint = NULL;
	}
	

	nPointNum = m_pCurModuleInfo->nDetectRegionPoint;
	pLinePoint = new POINT[nPointNum]; 
	for(i = 0; i < nPointNum; i++)
	{
		pLinePoint[i].x = m_pCurModuleInfo->stuDetectRegion[i].nX * fProportionX;
		pLinePoint[i].y = m_pCurModuleInfo->stuDetectRegion[i].nY * fProportionY;
	}
	
	cDrawObject = new CDrawLines(pLinePoint, nPointNum, eDetectArea);
	(*pMapLine)[eDetectArea].push_back(cDrawObject);
	if (pLinePoint != NULL)
	{
		delete pLinePoint;
		pLinePoint = NULL;
	}

	
	return;
}

void CConfigModule::OnButtonSetDetectregion() 
{
	if (m_pCurModuleInfo == NULL)
	{
		MessageBox(ConvertString("please select a module!"), ConvertString("Prompt"));
		return;
	}

	CString gTypeName[] = {DETECTREGION, TRACKREGION};
	m_srceenShow.Init(isDrawModuleInfo,0, m_lLoginId, m_nCurrentChannel, this);
	m_srceenShow.SetPaintType(2, gTypeName);
	m_srceenShow.m_stuPicShow.SetObjsMaxNumber(0, 0, 0, 0, 0,1,0,1);
	
	if (IDOK == m_srceenShow.DoModal())
	{
		float fProportionX = m_srceenShow.m_fProportionX;      
		float fProportionY = m_srceenShow.m_fProportionY;
		list<CDrawObject*> listDrawObject =m_srceenShow.m_stuPicShow.m_DrawObjectList[eDetectArea];
		
		int nIndex = 0;
		std::list<CDrawObject*>::iterator iterDrawObject = listDrawObject.begin();
		for (; iterDrawObject != listDrawObject.end(); iterDrawObject++)
		{
			CDrawLines* drawLinesObj = (CDrawLines*)(*iterDrawObject);
			m_pCurModuleInfo->nDetectRegionPoint = drawLinesObj->m_nPointNum;
			for (int i = 0; i < drawLinesObj->m_nPointNum; i++)
			{	
				m_pCurModuleInfo->stuDetectRegion[i].nX = (drawLinesObj->m_stuLinePoints + i)->x / fProportionX;
				m_pCurModuleInfo->stuDetectRegion[i].nY = (drawLinesObj->m_stuLinePoints + i)->y / fProportionY;
			}
			
			nIndex++;
		}

		listDrawObject =m_srceenShow.m_stuPicShow.m_DrawObjectList[eTrackRegion];
		
		nIndex = 0;
		iterDrawObject = listDrawObject.begin();
		for (; iterDrawObject != listDrawObject.end(); iterDrawObject++)
		{
			CDrawLines* drawLinesObj = (CDrawLines*)(*iterDrawObject);
			m_pCurModuleInfo->nTrackRegionPoint = drawLinesObj->m_nPointNum;
			for (int i = 0; i < drawLinesObj->m_nPointNum; i++)
			{	
				m_pCurModuleInfo->stuTrackRegion[i].nX = (drawLinesObj->m_stuLinePoints + i)->x / fProportionX;
				m_pCurModuleInfo->stuTrackRegion[i].nY = (drawLinesObj->m_stuLinePoints + i)->y / fProportionY;
			}
			nIndex++;
		}
	
		m_srceenShow.m_stuPicShow.DeleteRecourse();
	}
	
}

void CConfigModule::OnSelchangedTreeModule(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;


	HTREEITEM hRoot =  m_treeModule.GetRootItem();
	CFG_MODULE_INFO* pModuleInfo = NULL;

	HTREEITEM hOldSel = pNMTreeView->itemOld.hItem;
	if ( (hOldSel != hRoot) && (hOldSel != NULL) )
	{
		pModuleInfo = (CFG_MODULE_INFO*)m_treeModule.GetItemData(hOldSel);
		this->SaveModuleByPoint(pModuleInfo);
 	}


	HTREEITEM hNewSel = pNMTreeView->itemNew.hItem;
	if ( (hNewSel == hRoot) || (hNewSel == NULL) )
	{
		return;
 	}
	pModuleInfo = NULL;
	pModuleInfo = (CFG_MODULE_INFO*)m_treeModule.GetItemData(hNewSel);
	m_pCurModuleInfo = pModuleInfo;
	this->ShowModuleByPoint(pModuleInfo);
	

	*pResult = 0;
}
