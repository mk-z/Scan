// ConfigFaceRule.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "ConfigFaceRule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigFaceRule dialog


CConfigFaceRule::CConfigFaceRule(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigFaceRule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigFaceRule)
	m_strRuleName = _T("");
	m_bEnable = FALSE;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigFaceRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigFaceRule)
	DDX_Text(pDX, IDC_EDIT_RULENAME_TG, m_strRuleName);
	DDX_Check(pDX, IDC_CHECK_ENABLE_TG, m_bEnable);
	DDX_Control(pDX, IDC_LIST_OBJTYPE_TG, m_clObjType);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigFaceRule, CDialog)
	//{{AFX_MSG_MAP(CConfigFaceRule)
	ON_BN_CLICKED(IDC_BUTTON_SET_RULELINES_TG, OnBtnSetRulelinesTg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigFaceRule message handlers

void CConfigFaceRule::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CConfigFaceRule::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CConfigFaceRule::GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
									   CFG_FACEDETECT_INFO* pInfo, int nChannelId)
{
	if (pParentWnd != NULL)
	{
		m_pParentWnd = pParentWnd;
		
		m_lLoginId = lLoginId;
		
		m_nCurrentChannel = nChannelId;
		
		memset(&m_stuInfo, 0, sizeof(CFG_FACEDETECT_INFO));
		if (pInfo != NULL)
		{
			memcpy(&m_stuInfo, pInfo, sizeof(CFG_FACEDETECT_INFO));
		}
	}
	
	return;
}

void CConfigFaceRule::ShowRuleInfo()
{
	m_strRuleName = m_stuInfo.szRuleName;
	m_bEnable = m_stuInfo.bRuleEnable;

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
	return;
} 

void CConfigFaceRule::UpdateFalse()
{
	UpdateData(FALSE);
}

CFG_FACEDETECT_INFO* CConfigFaceRule::SaveRuleInfo()
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

	return &m_stuInfo;
}

BOOL CConfigFaceRule::RulenameIsExit()
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

void CConfigFaceRule::OnBtnSetRulelinesTg() 
{
	// TODO: Add your control notification handler code here
	CSceneShow* pSceneShowDlg = new CSceneShow();
	if (pSceneShowDlg == NULL)
	{
		return;
	}
	CString gTypeName[] = {DETECTREGION};
	pSceneShowDlg->Init(isDrawRules,EVENT_IVS_FACEDETECT, m_lLoginId, m_nCurrentChannel, this);
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


void CConfigFaceRule::SaveLinesInfo(CSceneShow* pSceneShowDlg) 
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

void CConfigFaceRule::InputEventRulesInPic(CPictrueDialog* pPicShow, float fProportionX, float fProportionY)
{
	HTREEITEM hSelectEventNode = m_pParentWnd->GetSelectEventNode();
	if (hSelectEventNode != NULL)
	{
		m_pParentWnd->InPutExitLinesToPicture(pPicShow, hSelectEventNode, fProportionX, fProportionY);
	}
	
}

BOOL CConfigFaceRule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
