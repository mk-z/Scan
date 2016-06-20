// Rule11VideoAbnormal.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "RuleVideoAbnormal.h"
#include "DemoIVSbDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRuleVideoAbnormal dialog


CRuleVideoAbnormal::CRuleVideoAbnormal(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleVideoAbnormal::IDD, pParent),
	m_pRule(NULL)
{
	//{{AFX_DATA_INIT(CRule11VideoAbnormal)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	for (int i = 0; i < 6; i++)
	{
		ZeroMemory(m_szArrDetectType[i], MAX_NAME_LEN);
	}

	strncpy(m_szArrDetectType[0], "Loss", strlen("Loss"));
	strncpy(m_szArrDetectType[1], "Cover", strlen("Cover"));
	strncpy(m_szArrDetectType[2], "Frozen", strlen("Frozen"));
	strncpy(m_szArrDetectType[3], "Light", strlen("Light"));
	strncpy(m_szArrDetectType[4], "Dark", strlen("Dark"));
	strncpy(m_szArrDetectType[5], "SceneChange", strlen("SceneChange"));
}


void CRuleVideoAbnormal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleVideoAbnormal)
	DDX_Control(pDX, IDC_RULE11_SLID_SENSI, m_slidSensi);
	DDX_Control(pDX, IDC_RULE11_TREE_ACTIONTYPE, m_treeDetectType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleVideoAbnormal, CDialog)
	//{{AFX_MSG_MAP(CRuleVideoAbnormal)
	ON_NOTIFY(NM_CLICK, IDC_RULE11_TREE_ACTIONTYPE, OnClickRule11TreeDetecttype)
	ON_EN_CHANGE(IDC_RULE11_EDT_MINDUR, OnChangeRule11EdtMindur)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRule11VideoAbnormal message handlers

void CRuleVideoAbnormal::initSubDlg()
{
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	
	CFG_CAP_ANALYSE_INFO* pCap = pMainDlg->getCapAnalyseInfo(pMainDlg->getCurrentChannel());
	if (!pCap)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < pCap->stSupportScenes.stScenes[0].nSupportRules; i++)
	{
		if (pCap->stSupportScenes.stScenes[0].stSpportRules[i].dwSupportedRule == EVENT_IVS_VIDEOABNORMALDETECTION)
		{
			break;
		}
	}

	//检测类型
	int nDetTypeNum = pCap->stSupportScenes.stScenes[0].stSpportRules[i].nSupportedDetectTypeNum;
	for (int j = 0; j < nDetTypeNum; j++)
	{
		HTREEITEM hItem = m_treeDetectType.InsertItem(ConvertString(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedDetectTypes[j]));
		char* p = new char[MAX_NAME_LEN];
		if (p)
		{
			ZeroMemory(p, MAX_NAME_LEN);
			strncpy(p,
					pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedDetectTypes[j],
					strlen(pCap->stSupportScenes.stScenes[0].stSpportRules[i].szSupportedDetectTypes[j]));
			m_treeDetectType.SetItemData(hItem, (DWORD)p);
		}
	}
	
	//最短持续时间
	SetDlgItemInt(IDC_RULE11_EDT_MINDUR, 0, FALSE);
	
	//灵敏度
	m_slidSensi.SetRange(1, 10);
	m_slidSensi.SetTicFreq(1);
	m_slidSensi.SetPos(5);
}

void CRuleVideoAbnormal::showRuleInfo(RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || pRuleStruct->RuleInfo.dwRuleType != EVENT_IVS_VIDEOABNORMALDETECTION)
	{
		return;
	}
	
	//Todo: show info
	if (!pRuleStruct->pRuleBuf)
	{
		return;
	}
	
	CFG_VIDEOABNORMALDETECTION_INFO* pRule = (CFG_VIDEOABNORMALDETECTION_INFO*)pRuleStruct->pRuleBuf;
	m_pRule = pRule;

	//检测类型
	HTREEITEM hItem = m_treeDetectType.GetRootItem();
	while(hItem)
	{
		CString strTmp = m_treeDetectType.GetItemText(hItem);
		for (int i = 0; i < pRule->nDetectType; i++)
		{
			char* p = (char*)m_treeDetectType.GetItemData(hItem);
			if (p)
			{
				if (strcmp(p, m_szArrDetectType[pRule->bDetectType[i]]) == 0)
				{
					m_treeDetectType.SetCheck(hItem);
					break;
				}				
			}
		}
		
		hItem = m_treeDetectType.GetNextSiblingItem(hItem);
	}

	//最短持续时间
	SetDlgItemInt(IDC_RULE11_EDT_MINDUR, pRule->nMinDuration, FALSE);

	//灵敏度
	m_slidSensi.SetPos(pRule->bSensitivity);
}

void CRuleVideoAbnormal::clearRuleInfo()
{
	HTREEITEM hItem = m_treeDetectType.GetRootItem();
	while(hItem)
	{
		char* p = (char*)m_treeDetectType.GetItemData(hItem);
		if (p)
		{
			delete p;
			p = NULL;
		}

		hItem = m_treeDetectType.GetNextSiblingItem(hItem);
	}
	m_treeDetectType.DeleteAllItems();
	m_pRule = NULL;
}

void CRuleVideoAbnormal::setRuleInfo(char* pRuleStruct, int nLen)
{
	if (!pRuleStruct || nLen != EVENT_IVS_VIDEOABNORMALDETECTION)
	{
		return;
	}
}

BOOL CRuleVideoAbnormal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRuleVideoAbnormal::OnClickRule11TreeDetecttype(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (!m_pRule)
	{
		return;
	}
	
	CPoint pt;
	GetCursorPos(&pt);
	m_treeDetectType.ScreenToClient(&pt);
	
	UINT uFlag = -1;
	HTREEITEM hSelectItem = m_treeDetectType.HitTest(pt, &uFlag);
	if (!hSelectItem)
	{
		return;
	}
	
	m_treeDetectType.SelectItem(hSelectItem);
	
	BOOL bCheck = FALSE;
	
	if (uFlag & TVHT_ONITEMSTATEICON)
	{
		if (m_treeDetectType.GetCheck(hSelectItem))
		{
			//turn to false
		}
		else
		{
			//turn to true
			bCheck = TRUE;
		}
	} 
	else
	{
		if (m_treeDetectType.GetCheck(hSelectItem))
		{
			bCheck = TRUE;
		} 
		else
		{
			bCheck = FALSE;
		}
	}
	
// 	if (bCheck)
// 	{
// 		m_pRule->nTypeNumber = 1;
// 		m_pRule->bDetectType[0] = 0;
// 	}
// 	else
// 	{
// 		m_pRule->nTypeNumber = 0;
// 		m_pRule->bDetectType[0] = 0;
// 	}
	
	HTREEITEM hItem = m_treeDetectType.GetRootItem();
	m_pRule->nDetectType = 0;
	ZeroMemory(m_pRule->bDetectType, 4);
	
	while(hItem)
	{
		if (hSelectItem == hItem)
		{
			if (bCheck)
			{
				char* p = (char*)m_treeDetectType.GetItemData(hItem);
				if (p)
				{
					for (int i = 0; i < 6; i++)
					{
						if (strcmp(p, m_szArrDetectType[i]) == 0)
						{
							m_pRule->bDetectType[m_pRule->nDetectType] = i;
							m_pRule->nDetectType++;
							break;
						}
					}
				}
			}
		} 
		else if (m_treeDetectType.GetCheck(hItem))
		{
			char* p = (char*)m_treeDetectType.GetItemData(hItem);
			if (p)
			{
				for (int i = 0; i < 3; i++)
				{
					if (strcmp(p, m_szArrDetectType[i]) == 0)
					{
						m_pRule->bDetectType[m_pRule->nDetectType] = i;
						m_pRule->nDetectType++;
						break;
					}
				}
			}
		}
		
		hItem = m_treeDetectType.GetNextSiblingItem(hItem);
	}
	
	*pResult = 0;
}

void CRuleVideoAbnormal::OnChangeRule11EdtMindur() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strMinDur;
		GetDlgItemText(IDC_RULE11_EDT_MINDUR, strMinDur);
		
		int iMinDur = atoi(strMinDur.GetBuffer(strMinDur.GetLength()));
		
		m_pRule->nMinDuration = iMinDur;
	}
}

void CRuleVideoAbnormal::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nCtrlID = pScrollBar->GetDlgCtrlID();
	if (nCtrlID == IDC_RULE11_SLID_SENSI)
	{
		CSliderCtrl* pSliderCtrl = (CSliderCtrl*)pScrollBar;
		if (pScrollBar && m_pRule)
		{
			m_pRule->bSensitivity = pSliderCtrl->GetPos();
		}
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
