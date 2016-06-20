// ConfigTrafficGateRule.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "ConfigTrafficGateRule.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigTrafficGateRule dialog


CConfigTrafficGateRule::CConfigTrafficGateRule(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigTrafficGateRule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigTrafficGateRule)
	m_nCarWayId = 0;
	m_strRuleName = _T("");
	m_nSpeedLowerLimit = 0;
	m_nSpeedUpperLimit = 0;
	m_nSpeedWeight = 0;
	m_nMetricDistance = 0;
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
	m_pParentWnd = NULL;
	m_lLoginId = 0;
	m_nCurrentChannel = 0;
	memset(&m_stuTrafficGateInfo, 0, sizeof(CFG_TRAFFICGATE_INFO));
}

void CConfigTrafficGateRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigTrafficGateRule)
	DDX_Control(pDX, IDC_LIST_OBJTYPE_TG, m_clObjType);
	DDX_Text(pDX, IDC_EDIT_CARWAYID_TG, m_nCarWayId);
	DDX_Text(pDX, IDC_EDIT_RULENAME_TG, m_strRuleName);
	DDX_Text(pDX, IDC_EDIT_SPEEDLL_TG, m_nSpeedLowerLimit);
	DDX_Text(pDX, IDC_EDIT_SPEEDUL_TG, m_nSpeedUpperLimit);
	DDX_Text(pDX, IDC_EDIT_SPEEDWGT_TG, m_nSpeedWeight);
	DDX_Text(pDX, IDC_EDIT_METRICDIS, m_nMetricDistance);
	DDX_Check(pDX, IDC_CHECK_ENABLE_TG, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigTrafficGateRule, CDialog)
	//{{AFX_MSG_MAP(CConfigTrafficGateRule)
	ON_BN_CLICKED(IDC_BUTTON_SET_RULELINES_TG, OnButtonSet)
	ON_EN_KILLFOCUS(IDC_EDIT_RULENAME_TG, OnKillfocusEditRulenameTg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigTrafficGateRule message handlers

BOOL CConfigTrafficGateRule::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	return TRUE;
}

void CConfigTrafficGateRule::GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
				CFG_TRAFFICGATE_INFO* pTrafficGateInfo, int nChannelId)
{
	if (pParentWnd != NULL)
	{
		m_pParentWnd = pParentWnd;
		
		m_lLoginId = lLoginId;

		m_nCurrentChannel = nChannelId;
		
		memset(&m_stuTrafficGateInfo, 0, sizeof(CFG_TRAFFICGATE_INFO));
		if (pTrafficGateInfo != NULL)
		{
			memcpy(&m_stuTrafficGateInfo, pTrafficGateInfo, sizeof(CFG_TRAFFICGATE_INFO));
		}
	}

	return;
}

void CConfigTrafficGateRule::ShowRuleInfo()
{
	m_strRuleName = m_stuTrafficGateInfo.szRuleName;
	m_bEnable = m_stuTrafficGateInfo.bRuleEnable;
	m_nMetricDistance = m_stuTrafficGateInfo.MetricDistance;
	m_nSpeedLowerLimit = m_stuTrafficGateInfo.nSpeedLowerLimit;
	m_nSpeedUpperLimit = m_stuTrafficGateInfo.nSpeedUpperLimit;
	m_nSpeedWeight = m_stuTrafficGateInfo.nSpeedWeight;
	m_nCarWayId = m_stuTrafficGateInfo.nLane;

	m_clObjType.DeleteAllItems();
	if (m_clObjType.GetHeaderCtrl())
	{
		int nColumCount = m_clObjType.GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < nColumCount; i++)
		{
			m_clObjType.DeleteColumn(0);
		}
	}

	m_clObjType.SetExtendedStyle(m_clObjType.GetExtendedStyle() | 
		LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_clObjType.InsertColumn(0, ConvertString("ObjectType"), LVCFMT_LEFT, 80, -1); 
	for(int i = 0; i < m_pParentWnd->m_nSupportedObjTypeNum; i++)
	{
		m_clObjType.InsertItem(LVIF_TEXT|LVIF_STATE,i,ConvertString(m_pParentWnd->m_gObjectTypeName[i]),0,LVIS_SELECTED,0,0);

		for(int k = 0; k < m_stuTrafficGateInfo.nObjectTypeNum; k++)
		{
			if(strcmp(m_stuTrafficGateInfo.szObjectTypes[k], m_pParentWnd->m_gObjectTypeName[i]) == 0)
			{
				m_clObjType.SetCheck(i, TRUE);
				break;
			}
		}
	}
	return;
} 

void CConfigTrafficGateRule::UpdateFalse()
{
	UpdateData(FALSE);
}

CFG_TRAFFICGATE_INFO* CConfigTrafficGateRule::SaveRuleInfo()
{
	BOOL bRet = UpdateData(TRUE);
	if (!bRet)
	{
		return NULL;
	}

	if ((m_strRuleName.GetLength() > 0) && (!RulenameIsExit()))
	{
		memset(m_stuTrafficGateInfo.szRuleName, 0, sizeof(char) * MAX_NAME_LEN);
		memcpy(m_stuTrafficGateInfo.szRuleName, m_strRuleName, m_strRuleName.GetLength());
	}
	else
	{
		MessageBox(ConvertString("Please input the rule name!"), ConvertString("Prompt"));
		return NULL;
	}
	
	if (m_bEnable)
	{
		m_stuTrafficGateInfo.bRuleEnable = true;
	}
	else
	{
		m_stuTrafficGateInfo.bRuleEnable = false;
	}
	m_stuTrafficGateInfo.MetricDistance = m_nMetricDistance;
	m_stuTrafficGateInfo.nSpeedLowerLimit = m_nSpeedLowerLimit;
	m_stuTrafficGateInfo.nSpeedUpperLimit = m_nSpeedUpperLimit;
	m_stuTrafficGateInfo.nSpeedWeight = m_nSpeedWeight;
	m_stuTrafficGateInfo.nLane = m_nCarWayId;

	int nObjCount = 0;
	memset(m_stuTrafficGateInfo.szObjectTypes, 0, sizeof(char) * MAX_NAME_LEN * MAX_OBJECT_LIST_SIZE);
	for(int i = 0; i < m_pParentWnd->m_nSupportedObjTypeNum; i++)
	{
		BOOL bSelect = m_clObjType.GetCheck(i);
		CString str = m_clObjType.GetItemText(i,0);
		if (bSelect)
		{
			memset(m_stuTrafficGateInfo.szObjectTypes[nObjCount], 0, sizeof(char) * MAX_NAME_LEN);
			memcpy(m_stuTrafficGateInfo.szObjectTypes[nObjCount], m_pParentWnd->m_gObjectTypeName[i], sizeof(char) * MAX_NAME_LEN);
			
			nObjCount++;		
		}
	}
	m_stuTrafficGateInfo.nObjectTypeNum = nObjCount;

	return &m_stuTrafficGateInfo;
}

void CConfigTrafficGateRule::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	CSceneShow* pSceneShowDlg = new CSceneShow();
	if (pSceneShowDlg == NULL)
	{
		return;
	}
	CString gTypeName[] = {ROADLINE, DETECTLINE};
	pSceneShowDlg->Init(isDrawRules, EVENT_IVS_TRAFFICGATE,m_lLoginId, m_nCurrentChannel, this);
	pSceneShowDlg->SetPaintType(2, gTypeName);
	pSceneShowDlg->m_stuPicShow.SetObjsMaxNumber(2, 2, 0, 0, 0,0,0,0);
	
	if (IDOK == pSceneShowDlg->DoModal())
	{
		SaveLinesInfo(pSceneShowDlg);
	}
	pSceneShowDlg->m_stuPicShow.DeleteRecourse();
	delete pSceneShowDlg;
	pSceneShowDlg = NULL;
}

void CConfigTrafficGateRule::InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY)
{
	HTREEITEM hSelectEventNode = m_pParentWnd->GetSelectEventNode();
	if (hSelectEventNode != NULL)
	{
		m_pParentWnd->InPutExitLinesToPicture(pPicShow, hSelectEventNode, fProportionX, fProportionY);
	}
	
}

void CConfigTrafficGateRule::SaveLinesInfo(CSceneShow* pSceneShowDlg) 
{
	int i;
	float fProportionX = pSceneShowDlg->m_fProportionX;      
	float fProportionY = pSceneShowDlg->m_fProportionY;
	CDrawLines* pDetectLine;
	list<CDrawObject*> lsDetectLines;
	lsDetectLines = pSceneShowDlg->m_stuPicShow.m_DrawObjectList[eDetectLine]; 
	if ((lsDetectLines.size() > pSceneShowDlg->m_stuPicShow.m_nMaxDetectLine) || (lsDetectLines.size() == 0))
	{
		MessageBox(ConvertString("failed!please check the detect line's set!"),ConvertString("Prompt"));
		return ;
	}
	
	{
		memset(m_stuTrafficGateInfo.stuDetectLine1, 0, sizeof(CFG_POLYLINE)*MAX_POLYLINE_NUM);
		m_stuTrafficGateInfo.nDetectLinePoint1 = 0;
		lsDetectLines = pSceneShowDlg->m_stuPicShow.m_DrawObjectList[eDetectLine];
		pDetectLine = (CDrawLines*)lsDetectLines.front(); 
		m_stuTrafficGateInfo.nDetectLinePoint1 = pDetectLine->m_nPointNum;
		for(i = 0; i < m_stuTrafficGateInfo.nDetectLinePoint1;i++)
		{
			m_stuTrafficGateInfo.stuDetectLine1[i].nX = pDetectLine->m_stuLinePoints[i].x / fProportionX;
			m_stuTrafficGateInfo.stuDetectLine1[i].nY = pDetectLine->m_stuLinePoints[i].y / fProportionY;
		}
		lsDetectLines.remove(pDetectLine);
	}

	memset(m_stuTrafficGateInfo.stuDetectLine2, 0, sizeof(CFG_POLYLINE)*MAX_POLYLINE_NUM);
	m_stuTrafficGateInfo.nDetectLinePoint2 = 0;
	if(lsDetectLines.size() >0)
	{
		
		pDetectLine = (CDrawLines*)lsDetectLines.front(); 
		m_stuTrafficGateInfo.nDetectLinePoint2 = pDetectLine->m_nPointNum;
		for(i = 0; i < m_stuTrafficGateInfo.nDetectLinePoint2;i++)
		{
			m_stuTrafficGateInfo.stuDetectLine2[i].nX = pDetectLine->m_stuLinePoints[i].x / fProportionX;
			m_stuTrafficGateInfo.stuDetectLine2[i].nY = pDetectLine->m_stuLinePoints[i].y / fProportionY;
		}
		lsDetectLines.remove(pDetectLine);
	}
	
	{
		lsDetectLines = pSceneShowDlg->m_stuPicShow.m_DrawObjectList[eRoadLine];
		if ((lsDetectLines.size()> pSceneShowDlg->m_stuPicShow.m_nMaxRoadLine)  || (lsDetectLines.size() == 0))
		{
			MessageBox(ConvertString("failed!please check the road line's set!"),ConvertString("Prompt"));
			return ;
		}
		while(lsDetectLines.size() > 0)
		{
			pDetectLine = (CDrawLines*)lsDetectLines.front();
			if (pDetectLine->m_leftRoadLine != NULL && pDetectLine->m_rightRoadLine != NULL)
			{
				memset(m_stuTrafficGateInfo.stuLeftLine, 0, sizeof(CFG_POLYLINE) * MAX_POLYLINE_NUM);
				m_stuTrafficGateInfo.nLeftLinePoint = 0;
				CDrawLines* pLeftLine = pDetectLine->m_leftRoadLine;
				m_stuTrafficGateInfo.nLeftLinePoint = pLeftLine->m_nPointNum;
				for (i = 0; i < m_stuTrafficGateInfo.nLeftLinePoint; i++)
				{
					m_stuTrafficGateInfo.stuLeftLine[i].nX = pLeftLine->m_stuLinePoints[i].x / fProportionX;
					m_stuTrafficGateInfo.stuLeftLine[i].nY = pLeftLine->m_stuLinePoints[i].y / fProportionY;
				}
				
				memset(m_stuTrafficGateInfo.stuRightLine, 0, sizeof(CFG_POLYLINE) * MAX_POLYLINE_NUM);
				m_stuTrafficGateInfo.nRightLinePoint = 0;
				CDrawLines* pRightLine = pDetectLine->m_rightRoadLine;
				m_stuTrafficGateInfo.nRightLinePoint = pRightLine->m_nPointNum;
				for (i = 0; i < m_stuTrafficGateInfo.nRightLinePoint; i++)
				{
					m_stuTrafficGateInfo.stuRightLine[i].nX = pRightLine->m_stuLinePoints[i].x / fProportionX;
					m_stuTrafficGateInfo.stuRightLine[i].nY = pRightLine->m_stuLinePoints[i].y / fProportionY;
				}
				lsDetectLines.remove(pLeftLine);
				lsDetectLines.remove(pRightLine);
			}
		}//while
	}
}

void CConfigTrafficGateRule::OnKillfocusEditRulenameTg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	RulenameIsExit();
}

BOOL CConfigTrafficGateRule::RulenameIsExit()
{
	BOOL bRet = m_pParentWnd->RuleNameHasExit(m_strRuleName, m_stuTrafficGateInfo.szRuleName);
	if (bRet)
	{
		m_strRuleName = "";
		MessageBox(ConvertString("This rule name has exit, Please input other rule name not exit!"), ConvertString("Prompt"));
		UpdateData(FALSE);

	}
	
	return bRet;
}

