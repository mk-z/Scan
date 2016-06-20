// ConfigCrossRegion.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "ConfigCrossRegion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigCrossRegion dialog


CConfigCrossRegion::CConfigCrossRegion(CWnd* pParent /*=NULL*/)
:CDialog(CConfigCrossRegion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigCrossRegion)
	m_strRuleName = _T("");
	m_bEnable = FALSE;
	m_strMaxTargets = _T("");
	m_strMinDuration = _T("");
	m_strMinTartgets = _T("");
	m_strReportInterval = _T("");
	//}}AFX_DATA_INIT
	memset((void*)&m_stuInfo,0x0,sizeof(m_stuInfo));
}


void CConfigCrossRegion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigCrossRegion)
	DDX_Control(pDX, IDC_COMBO_DIRECT, m_comboDirection);
	DDX_Control(pDX, IDC_COMBO_ACTIONTYPE_TG, m_comboActionType);
	DDX_Text(pDX, IDC_EDIT_RULENAME_TG, m_strRuleName);
	DDX_Check(pDX, IDC_CHECK_ENABLE_TG, m_bEnable);
	DDX_Control(pDX, IDC_LIST_OBJTYPE_TG, m_clObjType);
	DDX_Text(pDX, IDC_EDIT_MaxTargets, m_strMaxTargets);
	DDX_Text(pDX, IDC_EDIT_MinDuration, m_strMinDuration);
	DDX_Text(pDX, IDC_EDIT_MinTargets, m_strMinTartgets);
	DDX_Text(pDX, IDC_EDIT_ReportInterval, m_strReportInterval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigCrossRegion, CDialog)
	//{{AFX_MSG_MAP(CConfigCrossRegion)
	ON_BN_CLICKED(IDC_BUTTON_SET_RULELINES_TG, OnButtonSetRulelinesTg)
	ON_CBN_SELCHANGE(IDC_COMBO_ACTIONTYPE_TG, OnSelchangeComboActiontypeTg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigCrossRegion message handlers

void CConfigCrossRegion::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CConfigCrossRegion::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CConfigCrossRegion::GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
									   CFG_CROSSREGION_INFO* pInfo, int nChannelId)
{
	if (pParentWnd != NULL)
	{
		m_pParentWnd = pParentWnd;
		
		m_lLoginId = lLoginId;
		
		m_nCurrentChannel = nChannelId;
		
		memset(&m_stuInfo, 0, sizeof(CFG_CROSSREGION_INFO));
		if (pInfo != NULL)
		{
			memcpy(&m_stuInfo, pInfo, sizeof(CFG_CROSSREGION_INFO));
		}
	}
	
	return;
}

void CConfigCrossRegion::ShowRuleInfo()
{
	m_strRuleName = m_stuInfo.szRuleName;
	m_bEnable = m_stuInfo.bRuleEnable;
	
	// IDC_EDIT_MaxTargets
	m_strMaxTargets.Format("%d",m_stuInfo.nMaxTargets);

	m_strMinTartgets.Format("%d",m_stuInfo.nMinTargets);

	m_strMinDuration.Format("%d",m_stuInfo.nMinDuration);

	m_strReportInterval.Format("%d",m_stuInfo.nReportInterval);

	bool bEnable = m_stuInfo.nActionType == 2 ? true:false;
	GetDlgItem(IDC_EDIT_MaxTargets)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MinTargets)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MinDuration)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ReportInterval)->EnableWindow(bEnable);

	// 
	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_ACTIONTYPE_TG);
		if (pBox)
		{
			int n = pBox->GetCount();
			if (m_stuInfo.nActionType < n)
			{
				pBox->SetCurSel(m_stuInfo.nActionType);
			}
		}
	}

	// IDC_COMBO_DIRECT
	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_DIRECT);
		if (pBox)
		{
			int n = pBox->GetCount();
			if (m_stuInfo.nDirection < n)
			{
				pBox->SetCurSel(m_stuInfo.nDirection);
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

void CConfigCrossRegion::UpdateFalse()
{
	UpdateData(FALSE);
}


CFG_CROSSREGION_INFO* CConfigCrossRegion::SaveRuleInfo()
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

	// IDC_EDIT_MaxTargets
	m_stuInfo.nMaxTargets = GetDlgItemInt(IDC_EDIT_MaxTargets);
	
	m_stuInfo.nMinTargets = GetDlgItemInt(IDC_EDIT_MinTargets);
	
	m_stuInfo.nMinDuration = GetDlgItemInt(IDC_EDIT_MinDuration);
	
	m_stuInfo.nReportInterval = GetDlgItemInt(IDC_EDIT_ReportInterval);
	
	// IDC_COMBO_ACTIONTYPE_TG
	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_ACTIONTYPE_TG);
		if (pBox)
		{
			m_stuInfo.nActionType = pBox->GetCurSel();
		}
	}
	
	// IDC_COMBO_DIRECT
	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_DIRECT);
		if (pBox)
		{
			m_stuInfo.nDirection = pBox->GetCurSel();
		}
	}
	
	return &m_stuInfo;
}
BOOL CConfigCrossRegion::RulenameIsExit()
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

void CConfigCrossRegion::InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY)
{
	HTREEITEM hSelectEventNode = m_pParentWnd->GetSelectEventNode();
	if (hSelectEventNode != NULL)
	{
		m_pParentWnd->InPutExitLinesToPicture(pPicShow, hSelectEventNode, fProportionX, fProportionY);
	}
	
}

void CConfigCrossRegion::OnButtonSetRulelinesTg() 
{
	// TODO: Add your control notification handler code here
	CSceneShow* pSceneShowDlg = new CSceneShow();
	if (pSceneShowDlg == NULL)
	{
		return;
	}
	CString gTypeName[] = {DETECTREGION};
	pSceneShowDlg->Init(isDrawRules,EVENT_IVS_CROSSREGIONDETECTION, m_lLoginId, m_nCurrentChannel, this);
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
void CConfigCrossRegion::SaveLinesInfo(CSceneShow* pSceneShowDlg) 
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

BOOL CConfigCrossRegion::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_DIRECT);
		if (pBox)
		{//0:Enter;1:Leave;2:Both
			pBox->AddString("Enter");
			pBox->AddString("Leave");
			pBox->AddString("Both");
		}
	}
	
	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_ACTIONTYPE_TG);
		if (pBox)
		{//0-出现 1-消失 2-在区域内 3-穿越区域
			pBox->AddString("出现");
			pBox->AddString("消失");
			pBox->AddString("在区域内");
			pBox->AddString("穿越区域");
		}
	}

	m_strMaxTargets.Format("%d",m_stuInfo.nMaxTargets);

	m_strMinTartgets.Format("%d",m_stuInfo.nMinTargets);

	m_strMinDuration.Format("%d",m_stuInfo.nMinDuration);

	m_strReportInterval.Format("%d",m_stuInfo.nReportInterval);

	bool bEnable = m_stuInfo.nActionType == 2 ? true:false;
	GetDlgItem(IDC_EDIT_MaxTargets)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MinTargets)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MinDuration)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ReportInterval)->EnableWindow(bEnable);

	g_SetWndStaticText(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigCrossRegion::OnSelchangeComboActiontypeTg() 
{
	// TODO: Add your control notification handler code here
	// IDC_COMBO_ACTIONTYPE_TG

	{
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_ACTIONTYPE_TG);
		if (pBox)
		{
			m_stuInfo.nActionType = pBox->GetCurSel();
		}
	}

	bool bEnable = m_stuInfo.nActionType == 2 ? true:false;
	GetDlgItem(IDC_EDIT_MaxTargets)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MinTargets)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MinDuration)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ReportInterval)->EnableWindow(bEnable);
}
