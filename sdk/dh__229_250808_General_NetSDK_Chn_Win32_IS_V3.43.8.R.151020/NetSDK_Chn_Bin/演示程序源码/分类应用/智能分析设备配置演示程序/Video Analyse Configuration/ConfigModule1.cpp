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
	
	memset(m_gModules, 0, sizeof(CFG_ANALYSEMODULES_INFO)*MAX_CHANNEL_NUM);
	m_nMaxModeuleNum = 0;
	m_nMaxPointOfRegion = 0;
	m_nSupportedObjTypeNum = 0;
	memset(m_gObjectTypeName, 0, sizeof(char) * MAX_OBJECT_LIST_SIZE * MAX_NAME_LEN);  
}


void CConfigModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigModule)
	DDX_Control(pDX, IDC_COMBO_OBJTYPE, m_cbObjTypes);
//	DDX_Control(pDX, IDC_LIST_TRACKREG_M, m_lcTrackRegion);
//	DDX_Control(pDX, IDC_LIST_DETECTREG_M, m_lcDetecRegion);
//	DDX_Control(pDX, IDC_COMBO_MODULES_M, m_cbModules);
	DDX_Control(pDX, IDC_COMBO_FILTERTYPE_M, m_cbFilterType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_M, m_cbChannel);
	DDX_Check(pDX, IDC_CHECK_SNAP_M, m_bSnapEnable);
	DDX_Text(pDX, IDC_EDIT_MAXSY_M, m_nMaxSizeWidth);
	DDX_Text(pDX, IDC_EDIT_MINSY_M, m_nMinSizeWidth);
	DDX_Text(pDX, IDC_EDIT_MAXSX_M, m_nMaxSizeHight);
	DDX_Text(pDX, IDC_EDIT_MINSX_M, m_nMinSizeHight);
	DDX_Text(pDX, IDC_EDIT_MAXSA_M, m_nMaxSizeArea);
	DDX_Text(pDX, IDC_EDIT_MINSA_M, m_nMinSizeArea);
//	DDX_Text(pDX, IDC_EDIT_DRX, m_nDRX);
//	DDX_Text(pDX, IDC_EDIT_DRY, m_nDRY);
//	DDX_Text(pDX, IDC_EDIT_TRX, m_nTRX);
//	DDX_Text(pDX, IDC_EDIT_TRY, m_nTRY);
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
	ON_BN_CLICKED(IDC_BUTTON_SET_TRACKREGION, OnButtonSetTrackregion)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigModule message handlers

BOOL CConfigModule::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	memset(m_gModules, 0, sizeof(CFG_ANALYSEMODULES_INFO) * MAX_CHANNEL_NUM);
	return TRUE;
}

void CConfigModule::OnButtonRefreshM() 
{
	Refresh();
}

void CConfigModule::OnButtonSaveM() 
{
	if (-1 != m_cbChannel.GetCurSel())
	{
		SaveChannelModule(m_nCurrentChannel);
		((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->SetModule(m_nCurrentChannel, 
		m_gModules[m_nCurrentChannel]);
	}
	else
	{
		MessageBox(ConvertString("please select the channel!"), ConvertString("Prompt"));
	}
	
}


// void CConfigModule::OnButtonAdddrM() 
// {
// 	UpdateData(TRUE);
// 
// 	if (m_nCurrentModule == -1)
// 	{
// 		return;
// 	}
// 
// 	int nPointCount = m_gModules[m_nCurrentChannel].stuModuleInfo[m_nCurrentModule].nDetectRegionPoint;
// 	if (nPointCount >= m_nMaxPointOfRegion)
// 	{
// 		MessageBox(ConvertString("add failed! The point number has reached the max!"), ConvertString("Prompt"));
// 		return;
// 	}
// 
// 	m_gModules[m_nCurrentChannel].stuModuleInfo[m_nCurrentModule].nDetectRegionPoint++;
// // 	CString strBuf;
// // 	strBuf.Format("%d", m_nDRX);
// // 	m_lcDetecRegion.InsertItem(LVIF_TEXT|LVIF_STATE,nPointCount,strBuf,0,LVIS_SELECTED,0,0);
// // 	strBuf.Format("%d", m_nDRY);
// // 	m_lcDetecRegion.SetItemText(nPointCount, 1, strBuf);
// 
// 	m_nCurrentDRLine = nPointCount;
// }
// 
// void CConfigModule::OnButtonAddtrM() 
// {
// 	UpdateData(TRUE);
// 
// 	if (m_nCurrentModule == -1)
// 	{
// 		return;
// 	}
// 	
// 	int nPointCount = m_gModules[m_nCurrentChannel].stuModuleInfo[m_nCurrentModule].nTrackRegionPoint;
// 	if (nPointCount >= m_nMaxPointOfRegion)
// 	{
// 		MessageBox(ConvertString("add failed! The point number has reached the max!"), ConvertString("Prompt"));
// 		return;
// 	}
// 	
// 	m_gModules[m_nCurrentChannel].stuModuleInfo[m_nCurrentModule].nTrackRegionPoint++;
// // 	CString strBuf;
// // 	strBuf.Format("%d", m_nDRX);
// // 	m_lcTrackRegion.InsertItem(LVIF_TEXT|LVIF_STATE,nPointCount,strBuf,0,LVIS_SELECTED,0,0);
// // 	strBuf.Format("%d", m_nDRY);
// // 	m_lcTrackRegion.SetItemText(nPointCount, 1, strBuf);
// 	
// 	m_nCurrentTRLine = nPointCount;
// 	
// }
// 
// void CConfigModule::OnButtonDeletdrM() 
// {
// 	if (m_nCurrentTRLine == -1)
// 	{
// 		return;
// 	}
//     int nCount = m_gModules[m_nCurrentChannel].stuModuleInfo[m_nCurrentModule].nDetectRegionPoint;
// 	m_gModules[m_nCurrentChannel].stuModuleInfo[m_nCurrentModule].nDetectRegionPoint--;
// 	/*m_lcDetecRegion.DeleteItem(nCount - 1);*/
// 	m_nCurrentDRLine = -1;
// }
// 
// void CConfigModule::OnButtonDelettrM() 
// {
// 	if (m_nCurrentTRLine == -1)
// 	{
// 		return;
// 	}
// 
//     int nCount = m_gModules[m_nCurrentChannel].stuModuleInfo[m_nCurrentModule].nTrackRegionPoint;
// 	m_gModules[m_nCurrentChannel].stuModuleInfo[m_nCurrentModule].nTrackRegionPoint--;
// 	/*m_lcTrackRegion.DeleteItem(nCount - 1);*/
// 
// 	m_nCurrentTRLine = -1;
// }


// void CConfigModule::OnClickListDetectregM(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	// TODO: Add your control notification handler code here
// 	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// 	int nIndex = pNMListView->iItem;
// 	
// // 	m_nDRX = atoi(m_lcDetecRegion.GetItemText(nIndex,0));
// // 	m_nDRY = atoi(m_lcDetecRegion.GetItemText(nIndex,1));
// 	
// 	m_nCurrentDRLine = nIndex;
// 	
// 	UpdateData(FALSE);
// 	
// 	*pResult = 0;
// }

// void CConfigModule::OnClickListTrackregM(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	// TODO: Add your control notification handler code here
// 	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// 	int nIndex = pNMListView->iItem;
// 	
// // 	m_nTRX = atoi(m_lcTrackRegion.GetItemText(nIndex,0));
// // 	m_nTRY = atoi(m_lcTrackRegion.GetItemText(nIndex,1));
// 	
// 	m_nCurrentTRLine = nIndex;
// 	
// 	UpdateData(FALSE);
// 	
// 	*pResult = 0;
// }

// void CConfigModule::OnButtonSavedrM() 
// {
// 	UpdateData(TRUE);
// 
// 	if (m_nCurrentDRLine == -1)
// 	{
// 		return;
// 	}
// 	CString strBuf;
// 	strBuf.Format("%d", m_nDRX);
// 	m_lcDetecRegion.SetItemText(m_nCurrentDRLine, 0, strBuf);
// 	strBuf.Format("%d", m_nDRY);
// 	m_lcDetecRegion.SetItemText(m_nCurrentDRLine, 1, strBuf);
// 	return;
// }

// void CConfigModule::OnButtonSavetrM() 
// {
// 	UpdateData(TRUE);
// 
// 	if (m_nCurrentTRLine == -1)
// 	{
// 		return;
// 	}
// 
// 	CString strBuf;
// 	strBuf.Format("%d", m_nTRX);
// 	m_lcTrackRegion.SetItemText(m_nCurrentDRLine, 0, strBuf);
// 	strBuf.Format("%d", m_nTRY);
// 	m_lcTrackRegion.SetItemText(m_nCurrentDRLine, 1, strBuf);
// 	return;
// }

void CConfigModule::OnSelchangeComboChannelM() 
{
	SaveChannelModule(m_nCurrentChannel);

	if (-1 != m_cbChannel.GetCurSel())
	{
		m_nCurrentChannel = m_cbChannel.GetCurSel();
		ShowChannelModule(m_nCurrentChannel);
	}
}

// void CConfigModule::OnSelchangeComboModulesM() 
// {
// 	SaveModule(m_nCurrentModule, m_gModules[m_nCurrentChannel]);
// 
// 	m_nCurrentModule = m_cbModules.GetCurSel();
// 
// 	ShowModule(m_nCurrentModule, m_gModules[m_nCurrentChannel]);
// }

void CConfigModule::OnSelchangeComboFiltertypeM() 
{
	int nIndex = m_cbFilterType.GetCurSel();
	int nItemData = m_cbFilterType.GetItemData(nIndex);

	// 0:"ByLength",1:"ByArea"
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
}

void CConfigModule::OnButtonAddmod() 
{
	if (m_gModules[m_nCurrentChannel].nMoudlesNum >= m_nMaxModeuleNum)
	{
		MessageBox(ConvertString("add failed! The module number has reached the max!"), ConvertString("Prompt"));
		return;
	}

	SaveModule(m_nCurrentModule, m_gModules[m_nCurrentChannel]);

	int nModuleCount = m_gModules[m_nCurrentChannel].nMoudlesNum;
// 	char szBuffer[32] = {0};
// 	CString str;
// 	int nItemData = m_cbModules.GetItemData(nModuleCount - 1);
// 	str = ConvertString("Rule") + itoa(nItemData + 1, szBuffer, 10);
// 	int nIndex = m_cbModules.AddString(str);
// 	m_cbModules.SetItemData(nIndex, nModuleCount);
// 	m_cbModules.SetCurSel(nIndex);
	m_gModules[m_nCurrentChannel].nMoudlesNum++;

//	m_nCurrentModule = nIndex;
}

void CConfigModule::OnButtonDeletselmod() 
{
	int nIndex;
	//int nIndex = m_cbModules.GetCurSel();
	if (nIndex < 0)
	{
		MessageBox(ConvertString("Delete failed! There is no module to delete!"), ConvertString("Prompt"));
		return;
	}

// 	int nRuleNum = m_cbModules.GetItemData(nIndex);
// 	m_cbModules.DeleteString(nIndex);
// 	char szBuffer[10] = {0};
// 	
// 	for(int i = m_gModules[m_nCurrentChannel].nMoudlesNum - 1; i > nRuleNum; i--)
// 	{
// 		memcpy(&m_gModules[m_nCurrentChannel].stuModuleInfo[i -1], &m_gModules[m_nCurrentChannel].stuModuleInfo[i], sizeof(CFG_RULE_INFO));
// 		memset(&m_gModules[m_nCurrentChannel].stuModuleInfo[i], 0 , sizeof(CFG_RULE_INFO));
// 	}
// 	m_gModules[m_nCurrentChannel].nMoudlesNum--;
// 	
// 	nIndex = nIndex - 1;
// 	if (nIndex > 0)
// 	{
// 		m_cbModules.SetCurSel(nIndex);
// 		ShowModule(nIndex, m_gModules[m_nCurrentChannel]);
// 	}
// 	else
// 	{
// 		ClearModuleInfo();
// 		m_nCurrentModule = -1;
// 		Invalidate(TRUE);
// 	}
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
}

void CConfigModule::Refresh()
{
	// show
	ShowChannelModule(m_nCurrentChannel);
}

void CConfigModule::Clear()
{	
	m_cbChannel.ResetContent();

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
	
	m_cbObjTypes.ResetContent();
	m_cbFilterType.ResetContent();
//	m_cbModules.ResetContent();
	
// 	ClearList(&m_lcDetecRegion);
// 	ClearList(&m_lcTrackRegion);
// 	
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
// 	m_cbModules.ResetContent();
// 	for(int i = 0; i < nModuleCount; i++)
// 	{
// 		CString strModule;
// 		strModule = ConvertString("module") + itoa(i, szBuffer, 10);
// 		nIndex = m_cbModules.AddString(strModule);
// 		m_cbModules.SetItemData(nIndex, i);
// 	}
// 
// 	m_cbModules.SetCurSel(0);
	m_nCurrentModule = 0;

	ShowModule(m_nCurrentModule, m_gModules[m_nCurrentChannel]);
}

void CConfigModule::ShowModule(int nModuleId, CFG_ANALYSEMODULES_INFO stuModuleInfo)
{
	for(int i = 0; i < MAX_OBJECT_LIST_SIZE; i++)
	{
		if (strcmp(stuModuleInfo.stuModuleInfo[nModuleId].szObjectType, m_gObjectTypeName[i]) == 0)
		{
			m_cbObjTypes.SetCurSel(i);
		}
	}

	m_bSnapEnable = stuModuleInfo.stuModuleInfo[nModuleId].bSnapShot;
	m_cbFilterType.ResetContent();
 	int nIndex = m_cbFilterType.AddString(ConvertString("ByLength"));
	m_cbFilterType.SetItemData(nIndex, 0);
	nIndex = m_cbFilterType.AddString(ConvertString("ByArea"));
	m_cbFilterType.SetItemData(nIndex, 1);
	m_cbFilterType.SetCurSel(stuModuleInfo.stuModuleInfo[nModuleId].nFilterType);

	// 0:"ByLength",1:"ByArea"
	if (stuModuleInfo.stuModuleInfo[nModuleId].nFilterType == 0)
	{
		m_nMaxSizeHight = stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMaxSize.nHeight;
		m_nMaxSizeWidth = stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMaxSize.nWidth;

		m_nMinSizeHight = stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMinSize.nHeight;
		m_nMinSizeWidth = stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMinSize.nWidth;
	}
	else
	{
		m_nMaxSizeArea = stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMaxSize.nArea;
		m_nMinSizeArea = stuModuleInfo.stuModuleInfo[nModuleId].stuFilterMinSize.nArea;
	}

// 	ClearList(&m_lcDetecRegion);
// 	ClearList(&m_lcTrackRegion);
// 	m_lcDetecRegion.SetExtendedStyle(m_lcDetecRegion.GetExtendedStyle() | 
// 		LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
// 	m_lcDetecRegion.InsertColumn(0, ConvertString("X"), LVCFMT_LEFT, 60, -1); 
// 	m_lcDetecRegion.InsertColumn(1, ConvertString("Y"), LVCFMT_LEFT, 60, -1);
// 	CString strLocationX;
// 	CString strLocationY;
// 	for(i = 0; i < stuModuleInfo.stuModuleInfo[nModuleId].nDetectRegionPoint; i++)
// 	{
// 		strLocationX.Format("%d", stuModuleInfo.stuModuleInfo[nModuleId].stuDetectRegion[i].nX);
// 		strLocationY.Format("%d", stuModuleInfo.stuModuleInfo[nModuleId].stuDetectRegion[i].nY);
// 		m_lcDetecRegion.InsertItem(LVIF_TEXT|LVIF_STATE,i,strLocationX,0,LVIS_SELECTED,0,0);
// 		m_lcDetecRegion.SetItemText(i, 1, strLocationY);
// 	}
// 
// 	m_lcTrackRegion.SetExtendedStyle(m_lcTrackRegion.GetExtendedStyle() | 
// 		LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
// 	m_lcTrackRegion.InsertColumn(0, ConvertString("X"), LVCFMT_LEFT, 60, -1); 
// 	m_lcTrackRegion.InsertColumn(1, ConvertString("Y"), LVCFMT_LEFT, 60, -1);
// 	for(i = 0; i < stuModuleInfo.stuModuleInfo[nModuleId].nTrackRegionPoint; i++)
// 	{
// 		strLocationX.Format("%d", stuModuleInfo.stuModuleInfo[nModuleId].stuTrackRegion[i].nX);
// 		strLocationY.Format("%d", stuModuleInfo.stuModuleInfo[nModuleId].stuTrackRegion[i].nY);
// 		m_lcTrackRegion.InsertItem(LVIF_TEXT|LVIF_STATE,i,strLocationX,0,LVIS_SELECTED,0,0);
// 		m_lcTrackRegion.SetItemText(i, 1, strLocationY);
// 	}

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

// 	for (int i = 0; i < stuModuleInfo.stuModuleInfo[nModuleId].nDetectRegionPoint; i++)
// 	{
// 		stuModuleInfo.stuModuleInfo[nModuleId].stuDetectRegion[i].nX = atoi(m_lcDetecRegion.GetItemText(i,0));
// 		stuModuleInfo.stuModuleInfo[nModuleId].stuDetectRegion[i].nY = atoi(m_lcDetecRegion.GetItemText(i,1));
// 	}
// 	
// 	for (i = 0; i < stuModuleInfo.stuModuleInfo[nModuleId].nTrackRegionPoint; i++)
// 	{
// 		stuModuleInfo.stuModuleInfo[nModuleId].stuTrackRegion[i].nX = atoi(m_lcTrackRegion.GetItemText(i,0));
// 		stuModuleInfo.stuModuleInfo[nModuleId].stuTrackRegion[i].nY = atoi(m_lcTrackRegion.GetItemText(i,1));
// 	}
	
	return;
}



void CConfigModule::OnButtonSetDetectregion() 
{
	// TODO: Add your control notification handler code here
	
}

void CConfigModule::OnButtonSetTrackregion() 
{
	// TODO: Add your control notification handler code here
	
}
