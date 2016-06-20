// ConfigWanderRule.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "ConfigWanderRule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigWanderRule dialog


CConfigWanderRule::CConfigWanderRule(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigWanderRule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigWanderRule)
	m_strRuleName = _T("");
	m_bEnable = FALSE;
	m_strReportInterval = _T("");
	m_strTriggerTargetsNum = _T("");
	//}}AFX_DATA_INIT

	memset((void*)&m_stuInfo,0x0,sizeof(m_stuInfo));
}


void CConfigWanderRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigWanderRule)
	DDX_Text(pDX, IDC_EDIT_RULENAME_TG, m_strRuleName);
	DDX_Check(pDX, IDC_CHECK_ENABLE_TG, m_bEnable);
	DDX_Control(pDX, IDC_LIST_OBJTYPE_TG, m_clObjType);
	DDX_Text(pDX, IDC_EDIT_ReportInterval, m_strReportInterval);
	DDX_Text(pDX, IDC_EDIT_TriggerTargetsNumber, m_strTriggerTargetsNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigWanderRule, CDialog)
	//{{AFX_MSG_MAP(CConfigWanderRule)
	ON_BN_CLICKED(IDC_BUTTON_SET_RULELINES_TG, OnButtonSetRulelinesTg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigWanderRule message handlers

void CConfigWanderRule::GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
								  CFG_WANDER_INFO* pInfo, int nChannelId)
{
	if (pParentWnd != NULL)
	{
		m_pParentWnd = pParentWnd;
		
		m_lLoginId = lLoginId;
		
		m_nCurrentChannel = nChannelId;
		
		memset(&m_stuInfo, 0, sizeof(CFG_WANDER_INFO));
		if (pInfo != NULL)
		{
			memcpy(&m_stuInfo, pInfo, sizeof(CFG_WANDER_INFO));
		}
	}
	
	return;
}

void CConfigWanderRule::ShowRuleInfo()
{
	m_strRuleName = m_stuInfo.szRuleName;
	m_bEnable = m_stuInfo.bRuleEnable;
	
	m_strTriggerTargetsNum.Format("%d",m_stuInfo.nTriggerTargetsNumber);
	
	m_strReportInterval.Format("%d",m_stuInfo.nReportInterval);

	// 
	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_TriggerPosition);
		if (pBox)
		{
			int n = pBox->GetCount();
			if (m_stuInfo.nTriggerPosition < n)
			{
				pBox->SetCurSel(m_stuInfo.nTriggerPosition);
			}
		}
	}

	// m_clObjType
	{
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
			
			for(int k = 0; k < m_stuInfo.nObjectTypeNum; k++)
			{
				if(strcmp(m_stuInfo.szObjectTypes[k], m_pParentWnd->m_gObjectTypeName[i]) == 0)
				{
					m_clObjType.SetCheck(i, TRUE);
					break;
				}
			}
		}
	}
	return;
} 

void CConfigWanderRule::UpdateFalse()
{
	UpdateData(FALSE);
}

void CConfigWanderRule::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CConfigWanderRule::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

CFG_WANDER_INFO* CConfigWanderRule::SaveRuleInfo()
{
	BOOL bRet = UpdateData(TRUE);
	if (!bRet)
	{
		return NULL;
	}
	if ((m_strRuleName.GetLength() > 0) && (!RulenameIsExit()))
	{
		memset(m_stuInfo.szRuleName, 0, sizeof(char) * MAX_NAME_LEN);
		memcpy(m_stuInfo.szRuleName, m_strRuleName, m_strRuleName.GetLength());
	}
	else
	{
		MessageBox(ConvertString("Please input the rule name!"), ConvertString("Prompt"));
		return NULL;
	}
	
	// m_clObjType
	{
		int nObjCount = 0;
		memset(m_stuInfo.szObjectTypes, 0, sizeof(char) * MAX_NAME_LEN * MAX_OBJECT_LIST_SIZE);
		for(int i = 0; i < m_pParentWnd->m_nSupportedObjTypeNum; i++)
		{
			BOOL bSelect = m_clObjType.GetCheck(i);
			CString str = m_clObjType.GetItemText(i,0);
			if (bSelect)
			{
				memset(m_stuInfo.szObjectTypes[nObjCount], 0, sizeof(char) * MAX_NAME_LEN);
				memcpy(m_stuInfo.szObjectTypes[nObjCount], m_pParentWnd->m_gObjectTypeName[i], sizeof(char) * MAX_NAME_LEN);
				
				nObjCount++;		
			}
		}
		m_stuInfo.nObjectTypeNum = nObjCount;
	}
	

	m_stuInfo.nReportInterval = GetDlgItemInt(IDC_EDIT_ReportInterval);
	m_stuInfo.nTriggerTargetsNumber = GetDlgItemInt(IDC_EDIT_TriggerTargetsNumber);
	
	// IDC_COMBO_ACTIONTYPE_TG
	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_TriggerPosition);
		if (pBox)
		{
			m_stuInfo.nTriggerPosition = pBox->GetCurSel();
		}
	}
	return &m_stuInfo;
}
BOOL CConfigWanderRule::RulenameIsExit()
{
	BOOL bRet = m_pParentWnd->RuleNameHasExit(m_strRuleName, m_stuInfo.szRuleName);
	if (bRet)
	{
		m_strRuleName = "";
		MessageBox(ConvertString("This rule name has exit, Please input other rule name not exit!"), ConvertString("Prompt"));
		UpdateData(FALSE);
		
	}
	
	return bRet;
}

void CConfigWanderRule::InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY)
{
	HTREEITEM hSelectEventNode = m_pParentWnd->GetSelectEventNode();
	if (hSelectEventNode != NULL)
	{
		m_pParentWnd->InPutExitLinesToPicture(pPicShow, hSelectEventNode, fProportionX, fProportionY);
	}
	
}

void CConfigWanderRule::OnButtonSetRulelinesTg() 
{
	// TODO: Add your control notification handler code here
	CSceneShow* pSceneShowDlg = new CSceneShow();
	if (pSceneShowDlg == NULL)
	{
		return;
	}
	CString gTypeName[] = {DETECTREGION};
	pSceneShowDlg->Init(isDrawRules,EVENT_IVS_WANDERDETECTION, m_lLoginId, m_nCurrentChannel, this);
	pSceneShowDlg->SetPaintType(1, gTypeName);
	pSceneShowDlg->m_stuPicShow.SetObjsMaxNumber(0, 0, 0, 0, 0,4,0,0);
	
	if (IDOK == pSceneShowDlg->DoModal())
	{
		SaveLinesInfo(pSceneShowDlg);
	}
	pSceneShowDlg->m_stuPicShow.DeleteRecourse();
	delete pSceneShowDlg;
	pSceneShowDlg = NULL;
}


void CConfigWanderRule::SaveLinesInfo(CSceneShow* pSceneShowDlg) 
{
	int i;
	float fProportionX = pSceneShowDlg->m_fProportionX;      
	float fProportionY = pSceneShowDlg->m_fProportionY;
	CDrawLines* pDetectLine;
	list<CDrawObject*> lsDetectLines;
	lsDetectLines = pSceneShowDlg->m_stuPicShow.m_DrawObjectList[eDetectArea]; 
	if ((lsDetectLines.size() > pSceneShowDlg->m_stuPicShow.m_nMaxDetectRegion) || (lsDetectLines.size() == 0))
	{
		MessageBox(ConvertString("failed!please check the detect line's set!"),ConvertString("Prompt"));
		return ;
	}
	
	{
		memset(m_stuInfo.stuDetectRegion, 0, sizeof(CFG_POLYGON)*MAX_POLYGON_NUM);
		m_stuInfo.nDetectRegionPoint = 0;
		lsDetectLines = pSceneShowDlg->m_stuPicShow.m_DrawObjectList[eDetectArea];
		pDetectLine = (CDrawLines*)lsDetectLines.front(); 
		m_stuInfo.nDetectRegionPoint = pDetectLine->m_nPointNum;
		for(i = 0; i < m_stuInfo.nDetectRegionPoint;i++)
		{
			m_stuInfo.stuDetectRegion[i].nX = pDetectLine->m_stuLinePoints[i].x / fProportionX;
			m_stuInfo.stuDetectRegion[i].nY = pDetectLine->m_stuLinePoints[i].y / fProportionY;
		}
		lsDetectLines.remove(pDetectLine);
	}
	
}

BOOL CConfigWanderRule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_TriggerPosition);
		if (pBox)
		{//0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
			pBox->AddString("框中心");
			pBox->AddString("框左端中心");
			pBox->AddString("框顶端中心");
			pBox->AddString("框右端中心");
			pBox->AddString("框底端中心");
		}
	}
	
	m_strTriggerTargetsNum.Format("%d",m_stuInfo.nTriggerTargetsNumber);

	m_strReportInterval.Format("%d",m_stuInfo.nReportInterval);
	
	g_SetWndStaticText(this);		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
