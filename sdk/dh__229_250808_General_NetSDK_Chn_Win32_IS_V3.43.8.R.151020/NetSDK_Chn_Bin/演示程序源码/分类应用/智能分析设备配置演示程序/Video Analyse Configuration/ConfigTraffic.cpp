// ConfigTraffic.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "Video Analyse ConfigurationDlg.h"
#include "ConfigTraffic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigTraffic dialog


CConfigTrafficScene::CConfigTrafficScene(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigTrafficScene::IDD, pParent)
{
	m_lLoginId = 0;
	m_nChannelCount = 0;
	m_nCurrentChannel = -1;
	m_nRePaintRoad = -1;

	memset(m_stuAnalysSceneInfo, 0, sizeof(CFG_ANALYSEGLOBAL_INFO)*MAX_CHANNEL_NUM);
	m_nSupportedSceneNum = 0;
	memset(m_gSceneName, 0, sizeof(char)*MAX_SCENE_LIST_SIZE*MAX_NAME_LEN);  
	//{{AFX_DATA_INIT(CConfigTraffic)
	m_dCameraDistance = 0.0;
	m_dCameraHight = 0.0;
	m_nFDPToCamDis = 0;
	m_nFDPX = 0;
	m_nFDPY = 0;
	m_nNDPToCamsDis = 0;
	m_nNDPX = 0;
	m_nNDPY = 0;
	//}}AFX_DATA_INIT
}


void CConfigTrafficScene::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigTraffic)
	DDX_Control(pDX, IDC_LIST_ROAD, m_clCarWayInfo);
	DDX_Control(pDX, IDC_COMBO_SCENE_T, m_cbScene);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_T, m_cbChannel);
	DDX_Text(pDX, IDC_EDIT_CAMERAD_T, m_dCameraDistance);
	DDX_Text(pDX, IDC_EDIT_CAMERAH_T, m_dCameraHight);
	DDX_Text(pDX, IDC_EDIT_FDPTCD_T, m_nFDPToCamDis);
	DDX_Text(pDX, IDC_EDIT_FDPX_T, m_nFDPX);
	DDV_MinMaxInt(pDX, m_nFDPX, 0, 8192);
	DDX_Text(pDX, IDC_EDIT_FDPY_T, m_nFDPY);
	DDV_MinMaxInt(pDX, m_nFDPY, 0, 8192);
	DDX_Text(pDX, IDC_EDIT_NDPTCD_T, m_nNDPToCamsDis);
	DDX_Text(pDX, IDC_EDIT_NDPX_T, m_nNDPX);
	DDV_MinMaxInt(pDX, m_nNDPX, 0, 8192);
	DDX_Text(pDX, IDC_EDIT_NDPY_T, m_nNDPY);
	DDV_MinMaxInt(pDX, m_nNDPY, 0, 8192);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigTrafficScene, CDialog)
	//{{AFX_MSG_MAP(CConfigTraffic)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_T, OnButtonSaveT)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_T, OnButtonRefreshT)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_T, OnSelchangeComboChannelT)
	ON_BN_CLICKED(IDC_BUTTON_ADDROAD, OnButtonAddroad)
	ON_BN_CLICKED(IDC_BUTTON_CHANGEROAD, OnButtonChangeroad)
	ON_BN_CLICKED(IDC_BUTTON_DELETROAD, OnButtonDeletroad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigTraffic message handlers

BOOL CConfigTrafficScene::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	memset(m_stuAnalysSceneInfo, 0, sizeof(CFG_ANALYSEGLOBAL_INFO) * MAX_CHANNEL_NUM);

	return TRUE;
}

void CConfigTrafficScene::OnButtonSaveT() 
{
	if(-1 != m_cbChannel.GetCurSel())
	{
		BOOL bRet = SaveChannelScene(m_nCurrentChannel);
		if (!bRet)
		{
			return;
		}
		//Call father window to save data
		((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->SetTrafficScene(m_nCurrentChannel, 
		m_stuAnalysSceneInfo[m_nCurrentChannel]);
	}
	else
	{
		MessageBox(ConvertString("please select the channel!"), ConvertString("Prompt"));
	}
}

void CConfigTrafficScene::OnButtonRefreshT() 
{
	ShowTrafficSceneInfo();
}

void CConfigTrafficScene::ShowTrafficSceneInfo()
{	
	//Call father window to read data 
	ShowChannelScene(m_nCurrentChannel);
}

void CConfigTrafficScene::OnSelchangeComboChannelT() 
{
	// save
	SaveChannelScene(m_nCurrentChannel);

	m_nCurrentChannel = m_cbChannel.GetCurSel();
	
	// show
	ShowChannelScene(m_nCurrentChannel);
}

void CConfigTrafficScene::Init(int nChannelCount)
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

	m_gDirection[0] = "north";
	m_gDirection[1] = "east north";
	m_gDirection[2] = "east";
	m_gDirection[3] = "east south";
	m_gDirection[4] = "south";
	m_gDirection[5] = "west south";
	m_gDirection[6] = "west";
	m_gDirection[7] = "west north";

	// get supported object type
	GetCannelObjTypes();
	// show scene info
	ShowTrafficSceneInfo();
}

void CConfigTrafficScene::GetCannelObjTypes()
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
		m_nSupportedSceneNum = pDeviceCap->nSupportedSceneNum;
		memcpy(m_gSceneName, pDeviceCap->szSceneName, MAX_SCENE_LIST_SIZE * MAX_NAME_LEN * sizeof(char));
	}

	m_cbScene.ResetContent();
	for(int i = 0; i < m_nSupportedSceneNum; i++)
	{
		nChannelId = m_cbScene.AddString(ConvertString(m_gSceneName[i]));
		m_cbScene.SetItemData(nChannelId, i);
	}

	m_lLoginId = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetLoginID();
}

void CConfigTrafficScene::Clear()
{
	m_dCameraDistance = 0;
	m_dCameraHight = 0;
	m_nFDPToCamDis = 0;
	m_nFDPX = 0;
	m_nFDPY = 0;
	m_nNDPToCamsDis = 0;
	m_nNDPX = 0;
	m_nNDPY = 0;

	UpdateData(FALSE);

	m_cbChannel.ResetContent();
	m_cbScene.ResetContent();
}

void CConfigTrafficScene::ShowChannelScene(int nChannelId)
{
	// get info
	BOOL bSuccess = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetTrafficScene(nChannelId, 
		m_stuAnalysSceneInfo[nChannelId]);
	if (!bSuccess)
	{
		return;
	}

	// show info
	int i;
	for(i = 0; i < m_nSupportedSceneNum; i++)
	{
		if (strcmp(m_stuAnalysSceneInfo[nChannelId].szSceneType, m_gSceneName[i]) == 0)
		{
			m_cbScene.SetCurSel(i);
			break;
		}
	}

	m_dCameraDistance = m_stuAnalysSceneInfo[nChannelId].CameraDistance;
	m_dCameraHight = m_stuAnalysSceneInfo[nChannelId].CameraHeight;
	
	m_nNDPX = m_stuAnalysSceneInfo[nChannelId].stuNearDetectPoint.nX;
	m_nNDPY = m_stuAnalysSceneInfo[nChannelId].stuNearDetectPoint.nY;
	m_nNDPToCamsDis = m_stuAnalysSceneInfo[nChannelId].nNearDistance;

	m_nFDPX = m_stuAnalysSceneInfo[nChannelId].stuFarDectectPoint.nX;
	m_nFDPY = m_stuAnalysSceneInfo[nChannelId].stuFarDectectPoint.nY;
	m_nFDPToCamDis = m_stuAnalysSceneInfo[nChannelId].nFarDistance;

	int nCarWayCount = m_stuAnalysSceneInfo[nChannelId].nLaneNum;
	nChannelId = 0;
	ShowCarWayInfo(m_stuAnalysSceneInfo[nChannelId]);

	UpdateData(FALSE);
}

void CConfigTrafficScene::ShowCarWayInfo(CFG_ANALYSEGLOBAL_INFO &stuAnalysSceneInfo)
{

	m_clCarWayInfo.DeleteAllItems();
	if (m_clCarWayInfo.GetHeaderCtrl())
	{
		int nColumCount = m_clCarWayInfo.GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < nColumCount; i++)
		{
			m_clCarWayInfo.DeleteColumn(0);
		}
	}
	
	m_clCarWayInfo.SetExtendedStyle(m_clCarWayInfo.GetExtendedStyle() | 
		LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_clCarWayInfo.InsertColumn(0, ConvertString("RoadId"), LVCFMT_LEFT, 50, -1); 
	m_clCarWayInfo.InsertColumn(1, ConvertString("Direction"), LVCFMT_LEFT, 80, -1);
	m_clCarWayInfo.InsertColumn(2, ConvertString("LeftLineX"), LVCFMT_LEFT, 80, -1); 
	m_clCarWayInfo.InsertColumn(3, ConvertString("LeftLineY"), LVCFMT_LEFT, 80, -1);
	m_clCarWayInfo.InsertColumn(4, ConvertString("LeftLineX2"), LVCFMT_LEFT, 80, -1); 
	m_clCarWayInfo.InsertColumn(5, ConvertString("LeftLineY2"), LVCFMT_LEFT, 80, -1);
	m_clCarWayInfo.InsertColumn(6, ConvertString("RightLineX"), LVCFMT_LEFT, 80, -1); 
	m_clCarWayInfo.InsertColumn(7, ConvertString("RightLineY"), LVCFMT_LEFT, 80, -1);
	m_clCarWayInfo.InsertColumn(8, ConvertString("RightLineX2"), LVCFMT_LEFT, 80, -1); 
	m_clCarWayInfo.InsertColumn(9, ConvertString("RightLineY2"), LVCFMT_LEFT, 80, -1);

	
	for(int i = 0; i < stuAnalysSceneInfo.nLaneNum; i++)
	{
		InsertRoadInfoToList(&(stuAnalysSceneInfo.stuLanes[i]), i);
	}
}

void CConfigTrafficScene::InsertRoadInfoToList(CFG_LANE* pLane, int nIndex)
{
	if (pLane == NULL)
	{
		return;
	}

	CString strCarWayInfo;

	strCarWayInfo.Format("%d", pLane->nLaneId);
	m_clCarWayInfo.InsertItem(LVIF_TEXT|LVIF_STATE,nIndex,strCarWayInfo,0,LVIS_SELECTED,0,0);
	
	m_clCarWayInfo.SetItemText(nIndex, 1, ConvertString(m_gDirection[pLane->nDirection]));
	
	strCarWayInfo.Format("%d(0~8192)", pLane->stuLeftLine[0].nX);
	m_clCarWayInfo.SetItemText(nIndex, 2, strCarWayInfo);
	
	strCarWayInfo.Format("%d(0~8192)", pLane->stuLeftLine[0].nY);
	m_clCarWayInfo.SetItemText(nIndex, 3, strCarWayInfo);
	
	strCarWayInfo.Format("%d(0~8192)", pLane->stuLeftLine[1].nX);
	m_clCarWayInfo.SetItemText(nIndex, 4, strCarWayInfo);
	
	strCarWayInfo.Format("%d(0~8192)", pLane->stuLeftLine[1].nY);
	m_clCarWayInfo.SetItemText(nIndex, 5, strCarWayInfo);
	
	strCarWayInfo.Format("%d(0~8192)", pLane->stuRightLine[0].nX);
	m_clCarWayInfo.SetItemText(nIndex, 6, strCarWayInfo);
	
	strCarWayInfo.Format("%d(0~8192)", pLane->stuRightLine[0].nY);
	m_clCarWayInfo.SetItemText(nIndex, 7, strCarWayInfo);
	
	strCarWayInfo.Format("%d(0~8192)", pLane->stuRightLine[1].nX);
	m_clCarWayInfo.SetItemText(nIndex, 8, strCarWayInfo);
	
	strCarWayInfo.Format("%d(0~8192)", pLane->stuRightLine[1].nY);
	m_clCarWayInfo.SetItemText(nIndex, 9, strCarWayInfo);
}

BOOL CConfigTrafficScene::SaveChannelScene(int nChannelId)
{
	BOOL bRet = UpdateData(TRUE);
	if (!bRet)
	{
		return FALSE;
	}
	// save info
	memset(m_stuAnalysSceneInfo[nChannelId].szSceneType, 0, MAX_NAME_LEN* sizeof(char));
	int nIndex = m_cbScene.GetCurSel();
	if (nChannelId != -1)
	{
		memcpy(m_stuAnalysSceneInfo[nChannelId].szSceneType, m_gSceneName[nIndex], MAX_NAME_LEN* sizeof(char));
	}
	
	m_stuAnalysSceneInfo[nChannelId].CameraDistance = m_dCameraDistance;
	m_stuAnalysSceneInfo[nChannelId].CameraHeight = m_dCameraHight;
	
	m_stuAnalysSceneInfo[nChannelId].stuNearDetectPoint.nX = m_nNDPX;
	m_stuAnalysSceneInfo[nChannelId].stuNearDetectPoint.nY = m_nNDPY;
	m_stuAnalysSceneInfo[nChannelId].nNearDistance = m_nNDPToCamsDis;
	
	m_stuAnalysSceneInfo[nChannelId].stuFarDectectPoint.nX = m_nFDPX;
	m_stuAnalysSceneInfo[nChannelId].stuFarDectectPoint.nY = m_nFDPY;
	m_stuAnalysSceneInfo[nChannelId].nFarDistance = m_nFDPToCamDis;

	// save road info
	int nCount = m_clCarWayInfo.GetItemCount();
	CFG_LANE stuRoadInfo = {0};
	for (int i = 0; i < nCount; i++)
	{
		memset(&stuRoadInfo, 0, sizeof(CFG_LANE));
		SaveRoadInfoFromList(stuRoadInfo, i);
		memcpy(&(m_stuAnalysSceneInfo[nChannelId].stuLanes[i]), &stuRoadInfo, sizeof(CFG_LANE));
	}

	m_stuAnalysSceneInfo[nChannelId].nLaneNum = nCount;

	return TRUE;
}

void CConfigTrafficScene::SaveRoadInfoFromList(CFG_LANE &stuRoadInfo, int i)
{
	CString strDirection;
	int nDirection;

	stuRoadInfo.nLaneId = atoi(m_clCarWayInfo.GetItemText(i, 0));
	strDirection = m_clCarWayInfo.GetItemText(i, 1);
	nDirection = -1;
	for(int k = 0; k < 8; k++)
	{
		if(strDirection == ConvertString(m_gDirection[k]))
		{
			nDirection = k;
			break;
		}
	}

	stuRoadInfo.nDirection = nDirection;
	stuRoadInfo.nLeftLineNum = 2;
	stuRoadInfo.stuLeftLine[0].nX = atoi(m_clCarWayInfo.GetItemText(i, 2));
	stuRoadInfo.stuLeftLine[0].nY = atoi(m_clCarWayInfo.GetItemText(i, 3));
	stuRoadInfo.stuLeftLine[1].nX = atoi(m_clCarWayInfo.GetItemText(i, 4));
	stuRoadInfo.stuLeftLine[1].nY = atoi(m_clCarWayInfo.GetItemText(i, 5));
	stuRoadInfo.nRightLineNum = 2;
	stuRoadInfo.stuRightLine[0].nX = atoi(m_clCarWayInfo.GetItemText(i, 6));
	stuRoadInfo.stuRightLine[0].nY = atoi(m_clCarWayInfo.GetItemText(i, 7));
	stuRoadInfo.stuRightLine[1].nX = atoi(m_clCarWayInfo.GetItemText(i, 8));
	stuRoadInfo.stuRightLine[1].nY = atoi(m_clCarWayInfo.GetItemText(i, 9));

}

void CConfigTrafficScene::OnButtonAddroad() 
{
	int nRoadCount = m_stuAnalysSceneInfo[m_nCurrentChannel].nLaneNum;
	if (nRoadCount >= MAX_LANE_NUM)
	{
		MessageBox(ConvertString("add failed! The road number has reached the max!"), ConvertString("Prompt"));
		return;
	}
	
	// show dlg
	m_nRePaintRoad = -1;
	CSceneShow* pSceneShowDlg = new CSceneShow();
	CString gTypeName[] = {ROADLINE};
	pSceneShowDlg->Init(isDrawSceneRoads,0, m_lLoginId, m_nCurrentChannel, this);
	pSceneShowDlg->SetPaintType(1, gTypeName);
	pSceneShowDlg->m_stuPicShow.SetObjsMaxNumber(2, 0, 0, 0, 0,0,0,0);

	if (IDOK == pSceneShowDlg->DoModal())
	{
		CFG_LANE pLaneInfo;
		SaveCarWayInfo(&pLaneInfo, pSceneShowDlg);
		pSceneShowDlg->m_stuPicShow.DeleteRecourse();

		// show in the list
		InsertRoadInfoToList(&pLaneInfo, nRoadCount);
	
		m_stuAnalysSceneInfo->nLaneNum++;
	}

	if (pSceneShowDlg != NULL)
	{
		delete pSceneShowDlg;
		pSceneShowDlg = NULL;
	}
}

void CConfigTrafficScene::InPutExitLinesToPictur(CPictrueDialog* pPicShow, float fProportionX, float fProportionY)
{	
	if (pPicShow == NULL)
	{
		return;
	}
	MAPCROSSLINE* pMapLine = NULL;
	CString strLineName;
	CFG_LANE* pLineInfo = NULL;

	int nCount = m_clCarWayInfo.GetItemCount();
	CFG_LANE stuRoadInfo = {0};
	for (int i = 0; i < nCount; i++)
	{
		if (m_nRePaintRoad == i)
		{
			continue;
		}

		pMapLine = new MAPCROSSLINE();
		strLineName.Format("Road%d", i);
		pPicShow->m_mRules[strLineName] = pMapLine;
		
		memset(&stuRoadInfo, 0, sizeof(CFG_LANE));
		SaveRoadInfoFromList(stuRoadInfo, i);
		pLineInfo = &stuRoadInfo;

		if (pLineInfo == NULL)
		{
			return;
		}

		int k;
		int nLeftPointNum = pLineInfo->nLeftLineNum; 
		POINT *pLeftPoint = new POINT[nLeftPointNum];
		for(k = 0; k < nLeftPointNum; k++)
		{
			pLeftPoint[k].x = pLineInfo->stuLeftLine[k].nX * fProportionX;
			pLeftPoint[k].y = pLineInfo->stuLeftLine[k].nY * fProportionY;
		}
		
		int nRightPointNum = pLineInfo->nRightLineNum;
		POINT *pRightPoint = new POINT[nRightPointNum];
		for(k = 0; k < nLeftPointNum; k++)
		{
			pRightPoint[k].x = pLineInfo->stuRightLine[k].nX * fProportionX;
			pRightPoint[k].y = pLineInfo->stuRightLine[k].nY * fProportionY;
		}
		
		CDrawLines* cleftObject = new CDrawLines(pLeftPoint, nLeftPointNum, eRoadLine);
		CDrawLines* crightObject = new CDrawLines(pRightPoint, nRightPointNum, eRoadLine);
		cleftObject->m_leftRoadLine = cleftObject;
		cleftObject->m_rightRoadLine = crightObject;
		crightObject->m_leftRoadLine = cleftObject;
		crightObject->m_rightRoadLine = crightObject;
		
		delete[] pLeftPoint;
		pLeftPoint = NULL;
		delete[] pRightPoint;
		pRightPoint = NULL;
		(*pMapLine)[eRoadLine].push_back(cleftObject);
		(*pMapLine)[eRoadLine].push_back(crightObject);
	}
}

void CConfigTrafficScene::SaveCarWayInfo(CFG_LANE* pLaneInfo, CSceneShow* pSceneShowDlg)
{
	if (pLaneInfo == NULL || pSceneShowDlg == NULL)
	{
		return;
	}

	memset(pLaneInfo, 0, sizeof(CFG_LANE));

	pLaneInfo->nLaneId = pSceneShowDlg->GetRoadID();
	pLaneInfo->nDirection = pSceneShowDlg->GetRoadDirection();

	int i = 0;
	float fProportionX = pSceneShowDlg->m_fProportionX;      
	float fProportionY = pSceneShowDlg->m_fProportionY;
	CDrawLines* pDetectLine;
	list<CDrawObject*> lsDetectLines;
	{
		lsDetectLines = pSceneShowDlg->m_stuPicShow.m_DrawObjectList[eRoadLine];
		if (lsDetectLines.size() > pSceneShowDlg->m_stuPicShow.m_nMaxRoadLine && lsDetectLines.size() == 0)
		{
			MessageBox(ConvertString("failed!please check the road line's set!"),ConvertString("Prompt"));
			return ;
		}
		while(lsDetectLines.size() > 0)
		{
			pDetectLine = (CDrawLines*)lsDetectLines.front();
			if (pDetectLine->m_leftRoadLine != NULL && pDetectLine->m_rightRoadLine != NULL)
			{
				CDrawLines* pLeftLine = pDetectLine->m_leftRoadLine;
				pLaneInfo->nLeftLineNum = pLeftLine->m_nPointNum;
				for (i = 0; i < pLaneInfo->nLeftLineNum; i++)
				{
					pLaneInfo->stuLeftLine[i].nX = pLeftLine->m_stuLinePoints[i].x / fProportionX;
					pLaneInfo->stuLeftLine[i].nY = pLeftLine->m_stuLinePoints[i].y / fProportionY;
				}
				
				CDrawLines* pRightLine = pDetectLine->m_rightRoadLine;
				pLaneInfo->nRightLineNum = pRightLine->m_nPointNum;
				for (i = 0; i < pLaneInfo->nRightLineNum; i++)
				{
					pLaneInfo->stuRightLine[i].nX = pRightLine->m_stuLinePoints[i].x / fProportionX;
					pLaneInfo->stuRightLine[i].nY = pRightLine->m_stuLinePoints[i].y / fProportionY;
				}
				lsDetectLines.remove(pLeftLine);
				lsDetectLines.remove(pRightLine);
			}
		}//while
	}
}

void CConfigTrafficScene::OnButtonChangeroad() 
{
	UpdateData(TRUE);

	int nSelectRoad = GetSelectRoadItem();   
	if (nSelectRoad == -1)
	{
		MessageBox(ConvertString("please select one road item to change!"), ConvertString("Prompt"));
		return;
	}
	m_nRePaintRoad = nSelectRoad;

	// show dlg
	CSceneShow* pSceneShowDlg = new CSceneShow();
	CString gTypeName[] = {ROADLINE};
	pSceneShowDlg->Init(isDrawSceneRoads, 0,m_lLoginId, m_nCurrentChannel, this);
	pSceneShowDlg->SetPaintType(1, gTypeName);
	pSceneShowDlg->m_stuPicShow.SetObjsMaxNumber(2, 0, 0, 0, 0,0,0,0);
	
	if (IDOK == pSceneShowDlg->DoModal())
	{
		CFG_LANE pLaneInfo;
		SaveCarWayInfo(&pLaneInfo, pSceneShowDlg);
		pSceneShowDlg->m_stuPicShow.DeleteRecourse();
		
		// show in the list
		m_clCarWayInfo.DeleteItem(nSelectRoad);
		InsertRoadInfoToList(&pLaneInfo, nSelectRoad);
		m_nRePaintRoad = -1;
	}

	if (pSceneShowDlg != NULL)
	{
		delete pSceneShowDlg;
		pSceneShowDlg = NULL;
	}
}

void CConfigTrafficScene::OnButtonDeletroad() 
{
	int nSelectRoad = GetSelectRoadItem();  
	if (nSelectRoad == -1)
	{
		MessageBox(ConvertString("please select one road item to delete!"), ConvertString("Prompt"));
		return;
	}

	int nRoadCount = m_stuAnalysSceneInfo[m_nCurrentChannel].nLaneNum;
	if (nRoadCount <= 0)
	{
		MessageBox(ConvertString("delet failed! There is no road to delet!"), ConvertString("Prompt"));
		return;
	}
	
	// delet from the list 
	m_clCarWayInfo.DeleteItem(nSelectRoad);

	// move the roads info
	for(int i = nSelectRoad; i < nRoadCount - 1; i++)
	{
		memcpy(&(m_stuAnalysSceneInfo[m_nCurrentChannel].stuLanes[i]), 
			&(m_stuAnalysSceneInfo[m_nCurrentChannel].stuLanes[i + 1]), 
			sizeof(CFG_LANE));
	}

	memset(&(m_stuAnalysSceneInfo[m_nCurrentChannel].stuLanes[nRoadCount -1]), 
		0, sizeof(CFG_LANE));

	m_stuAnalysSceneInfo[m_nCurrentChannel].nLaneNum--;
}

int CConfigTrafficScene::GetSelectRoadItem()
{
	int nSelectId = -1;

	for ( int i = 0; i < m_clCarWayInfo.GetItemCount(); i++ )
	{
		if ( m_clCarWayInfo.GetItemState(i, LVIS_SELECTED) & LVIS_SELECTED )
		{
			nSelectId = i;
			break;
		}
	}

	return nSelectId;
}

