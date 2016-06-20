// SceneShow.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "SceneShow.h"
#include "ConfigTraffic.h"
#include "ConfigTrafficGateRule.h"
#include "ConfigModule.h"
#include "ConfigFaceRule.h"
#include "ConfigCrossLineRule.h"
#include "ConfigCrossRegion.h"
#include "ConfigPasteRule.h"
#include "ConfigRioterRule.h"
#include "ConfigWanderRule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSceneShow dialog


CSceneShow::CSceneShow(CWnd* pParent /*=NULL*/)
	: CDialog(CSceneShow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSceneShow)
	m_nRoadId = 0;
	m_nRadioId = -1;
	//}}AFX_DATA_INIT

	m_nDrawType = 0;
	m_lLoginId = 0;
	m_lPlayHandle = 0;
	m_nChannelId = 0;
	m_nPaintTypeCount = 0;
	m_dlgSourceWindow = NULL;
	m_nSelectPaintType = -1;;
	m_nDirection = -1;

	m_fProportionX = 0;      
	m_fProportionY = 0;
}


void CSceneShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSceneShow)
	DDX_Control(pDX, IDC_COMBO_DIRECTION, m_cbDirection);
	DDX_Text(pDX, IDC_EDIT_ROADID, m_nRoadId);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadioId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSceneShow, CDialog)
	//{{AFX_MSG_MAP(CSceneShow)
	ON_BN_CLICKED(IDC_BUTTON_REPAINT, OnButtonRepaint)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSceneShow message handlers

BOOL CSceneShow::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	m_stuPicShow.Create(IDD_PICTURE_SHOW, this);
	CRect screenRect;
	GetDlgItem(IDC_STATIC_SHOW)->GetWindowRect(&screenRect);
	ScreenToClient(&screenRect);
	GetProportion(screenRect);
	m_stuPicShow.MoveWindow(screenRect);
	m_stuPicShow.ShowWindow(SW_SHOW);

 	CLIENT_RigisterDrawFun(ChannelAutoDraw, (LDWORD)&m_stuPicShow);
 	m_lPlayHandle = CLIENT_RealPlayEx(m_lLoginId, m_nChannelId, m_stuPicShow.m_hWnd); 

	if (m_nDrawType == isDrawSceneRoads)
	{
		int nIndex = 0;
		CString gDirection[] = {"north", "east north", "east", "east south", "south", "west south", "west", "west north"};
		
		m_cbDirection.ResetContent();
		for(int i = 0; i < 8; i++)
		{
			nIndex = m_cbDirection.AddString(ConvertString(gDirection[i]));
			m_cbDirection.SetItemData(i, i);
		}
		m_cbDirection.SetCurSel(0);

		GetDlgItem(IDC_STATIC_ROADID)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_ROADID)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DIRECTION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_DIRECTION)->ShowWindow(SW_SHOW);
	}
	
	CString strDlgName;
	if (m_dlgSourceWindow != NULL)
	{
		if (m_nDrawType == isDrawSceneRoads)
		{
			CConfigTrafficScene* pWnd = (CConfigTrafficScene*)m_dlgSourceWindow;
			pWnd->InPutExitLinesToPictur(&m_stuPicShow, m_fProportionX, m_fProportionY);
			strDlgName = "RoadSet";
		}
		else if (m_nDrawType == isDrawRules)
		{
			switch(m_nSubDrawType)
			{
			case EVENT_IVS_TRAFFICGATE:
				{
					CConfigTrafficGateRule* pWnd = (CConfigTrafficGateRule*)m_dlgSourceWindow;
					pWnd->InputEventRulesInPic(&m_stuPicShow, m_fProportionX, m_fProportionY);
				}
				break;
			case EVENT_IVS_FACEDETECT:
				{
					CConfigFaceRule* pWnd = (CConfigFaceRule*)m_dlgSourceWindow;
					pWnd->InputEventRulesInPic(&m_stuPicShow, m_fProportionX, m_fProportionY);
				}
				break;
			case EVENT_IVS_WANDERDETECTION:
				{
					CConfigWanderRule* pWnd = (CConfigWanderRule*)m_dlgSourceWindow;
					pWnd->InputEventRulesInPic(&m_stuPicShow, m_fProportionX, m_fProportionY);
				}
				break;
			case EVENT_IVS_PASTEDETECTION:
				{
					CConfigPasteRule* pWnd = (CConfigPasteRule*)m_dlgSourceWindow;
					pWnd->InputEventRulesInPic(&m_stuPicShow, m_fProportionX, m_fProportionY);
				}
				break;
			case EVENT_IVS_CROSSLINEDETECTION:
				{
					CConfigCrossLineRule* pWnd = (CConfigCrossLineRule*)m_dlgSourceWindow;
					pWnd->InputEventRulesInPic(&m_stuPicShow, m_fProportionX, m_fProportionY);
				}
				break;
			case EVENT_IVS_CROSSREGIONDETECTION:
				{
					CConfigCrossRegion* pWnd = (CConfigCrossRegion*)m_dlgSourceWindow;
					pWnd->InputEventRulesInPic(&m_stuPicShow, m_fProportionX, m_fProportionY);
				}
				break;
			case EVENT_IVS_RIOTERDETECTION:
				{
					CConfigRioterRule* pWnd = (CConfigRioterRule*)m_dlgSourceWindow;
					pWnd->InputEventRulesInPic(&m_stuPicShow, m_fProportionX, m_fProportionY);
				}
				break;
			default:
				break;
			}
			strDlgName = "RuleSet";
		}
		else if (m_nDrawType == isDrawModuleInfo)
		{
			CConfigModule* pWnd = (CConfigModule*)m_dlgSourceWindow;
			pWnd->InPutExitLinesToPicture(&m_stuPicShow, m_fProportionX, m_fProportionY);
			SetDlgItemText(IDC_BUTTON_REPAINT,ConvertString("Repaint"));
			strDlgName = "DetectandTrackRegionSet";
		}
	}

	SetWindowText(ConvertString(strDlgName));

	for(int i = 0; i < m_nPaintTypeCount; i++)
	{
		if (i == 0)
		{
			GetDlgItem(IDC_RADIO1)->SetWindowText(ConvertString(m_gPaintType[i]));
			GetDlgItem(IDC_RADIO1)->ShowWindow(SW_SHOW);
		}
		else if (i == 1)
		{
			GetDlgItem(IDC_RADIO2)->SetWindowText(ConvertString(m_gPaintType[i]));
			GetDlgItem(IDC_RADIO2)->ShowWindow(SW_SHOW);
		}
		else if (i == 2)
		{
			GetDlgItem(IDC_RADIO3)->SetWindowText(ConvertString(m_gPaintType[i]));
			GetDlgItem(IDC_RADIO3)->ShowWindow(SW_SHOW);
		}
		else if (i == 3)
		{
			GetDlgItem(IDC_RADIO4)->SetWindowText(ConvertString(m_gPaintType[i]));
			GetDlgItem(IDC_RADIO4)->ShowWindow(SW_SHOW);
		}
		else if (i == 4)
		{
			GetDlgItem(IDC_RADIO5)->SetWindowText(ConvertString(m_gPaintType[i]));
			GetDlgItem(IDC_RADIO5)->ShowWindow(SW_SHOW);
		}
	}

	ClearRadioState();
	CButton* cRadio = (CButton*)GetDlgItem(IDC_RADIO1);
	cRadio->SetCheck(TRUE);
	GetSelectPaintType(0);
	m_stuPicShow.m_emSelectScene = m_nSelectPaintType;
	return TRUE;
}


void CSceneShow::OnOK() 
{
	BOOL bRet = UpdateData(TRUE);
	if (!bRet)
	{
		return;
	}
	// save info
	if (m_nDrawType == isDrawSceneRoads)
	{
		int nIndex = m_cbDirection.GetCurSel();
		m_nDirection = m_cbDirection.GetItemData(nIndex);
	}

	if (m_lPlayHandle != 0)
	{
		CLIENT_StopRealPlayEx(m_lPlayHandle);
		m_lPlayHandle = 0;
	}

	m_stuPicShow.DestroyWindow();
/*	ClearRadioState();*/

	CDialog::OnOK();
}

void CSceneShow::OnCancel() 
{
	// not save info
	if (m_lPlayHandle != 0)
	{
		CLIENT_StopRealPlayEx(m_lPlayHandle);
		m_lPlayHandle = 0;
	}

	m_stuPicShow.DeleteRecourse();
	m_stuPicShow.DestroyWindow();

	CDialog::OnCancel();
}

void CSceneShow::ClearRadioState()
{
	CButton* cRadio;
	cRadio = (CButton*)GetDlgItem(IDC_RADIO1);
	cRadio->SetCheck(FALSE);
	cRadio = (CButton*)GetDlgItem(IDC_RADIO2);
	cRadio->SetCheck(FALSE);
	cRadio = (CButton*)GetDlgItem(IDC_RADIO3);
	cRadio->SetCheck(FALSE);
	cRadio = (CButton*)GetDlgItem(IDC_RADIO4);
	cRadio->SetCheck(FALSE);
	cRadio = (CButton*)GetDlgItem(IDC_RADIO5);
	cRadio->SetCheck(FALSE);
}

void CSceneShow::GetProportion(CRect stuWindowSize)
{
	float fWidth;
	float fHeight;
	
	fWidth = stuWindowSize.Width();
	fHeight = stuWindowSize.Height();
	
	m_fProportionX = fWidth / PICTRUE_REAL_SIZE;
	m_fProportionY = fHeight / PICTRUE_REAL_SIZE;
}

void CSceneShow::Init(int nDrawType,int nSubDrawType, long lLoginId, int nChannelId, CWnd* pWnd)
{
	m_nDrawType = nDrawType;
	m_nSubDrawType = nSubDrawType;
	m_lLoginId = lLoginId;
	m_dlgSourceWindow = pWnd;
	m_nChannelId = nChannelId;
}

void CSceneShow::SetPaintType(int nTypeCount, CString* pTypeName)
{
	if (pTypeName == NULL)
	{
		return;
	}

	m_nPaintTypeCount = nTypeCount;
	for(int i = 0; i < nTypeCount; i++)
	{
		m_gPaintType[i] = pTypeName[i];
	}
}

void CSceneShow::OnButtonRepaint() 
{
	UpdateData(TRUE);

	if (m_nRadioId != -1)
	{
		GetSelectPaintType(m_nRadioId);
	}
	m_stuPicShow.m_emSelectScene = m_nSelectPaintType;

	std::list<CDrawObject*>::iterator itSelect = m_stuPicShow.m_DrawObjectList[m_nSelectPaintType].begin();
	
	while(itSelect != m_stuPicShow.m_DrawObjectList[m_nSelectPaintType].end())
	{
		CDrawObject* pObj = (*itSelect);
		delete pObj;
		m_stuPicShow.m_DrawObjectList[m_nSelectPaintType].erase(itSelect++);
	}
	m_stuPicShow.Invalidate(TRUE);
}

void CSceneShow::GetSelectPaintType(int nIndex)
{
	if (m_gPaintType[nIndex] == ROADLINE)
	{
		m_nSelectPaintType = eRoadLine;
	}
	else if (m_gPaintType[nIndex] == PRELINE)
	{
		m_nSelectPaintType = ePreLine;
	}
	else if (m_gPaintType[nIndex] == DETECTLINE)
	{
		m_nSelectPaintType = eDetectLine;
	}
	else if (m_gPaintType[nIndex] == POSTLINE)
	{
		m_nSelectPaintType = ePostLine;
	}
	else if (m_gPaintType[nIndex] == DETECTREGION)
	{
		m_nSelectPaintType = eDetectArea;
	}
	else if (m_gPaintType[nIndex] == TRACKREGION)
	{
		m_nSelectPaintType = eTrackRegion;
	}
	else if (m_gPaintType[nIndex] == REDLIGHTREGION)
	{
		m_nSelectPaintType = eStopLightRegion;
	}
	else if (m_gPaintType[nIndex] == STOPLINE)
	{
		m_nSelectPaintType = eStopLine;
	}
}


void CSceneShow::OnRadio1() 
{
	UpdateData(TRUE);
	if (m_nRadioId != -1)
	{
		GetSelectPaintType(m_nRadioId);
	}
	
	m_stuPicShow.m_emSelectScene = m_nSelectPaintType;
}


