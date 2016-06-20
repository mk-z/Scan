// RuleCfgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "IVSFDemo.h"
#include "RuleCfgdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuleCfgdlg dialog


CRuleCfgdlg::CRuleCfgdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleCfgdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRuleCfgdlg)
	m_nAccuracy = 0;
	m_nImportantRank = 0;
	m_nMaxCandidate = 0;
	m_strRuleName = _T("");
	m_nSimilarity = 0;
	m_bEye = FALSE;
	m_bEyeBrow = FALSE;
	m_bFace = FALSE;
	m_bMouth = FALSE;
	m_bNose = FALSE;
	//}}AFX_DATA_INIT
}


void CRuleCfgdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleCfgdlg)
	DDX_Control(pDX, IDC_COMBO_MODE, m_cbMode);
	DDX_Text(pDX, IDC_EDIT_ACCURACY, m_nAccuracy);
	DDX_Text(pDX, IDC_EDIT_IMPORTANTRANK, m_nImportantRank);
	DDX_Text(pDX, IDC_EDIT_MAXCANDIDATE, m_nMaxCandidate);
	DDX_Text(pDX, IDC_EDIT_RULENAME, m_strRuleName);
	DDX_Text(pDX, IDC_EDIT_SIMILARITY, m_nSimilarity);
	DDX_Check(pDX, IDC_CHECK_EYE, m_bEye);
	DDX_Check(pDX, IDC_CHECK_EYEBROW, m_bEyeBrow);
	DDX_Check(pDX, IDC_CHECK_FACE, m_bFace);
	DDX_Check(pDX, IDC_CHECK_MOUTH, m_bMouth);
	DDX_Check(pDX, IDC_CHECK_NOSE, m_bNose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleCfgdlg, CDialog)
	//{{AFX_MSG_MAP(CRuleCfgdlg)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, OnSelchangeComboMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleCfgdlg message handlers

BOOL CRuleCfgdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	int nIndex = 0;
	char Modes[3][32]= {"Normal", "Combined", "intelligent"};
	m_cbMode.ResetContent();
	for (int i = 0; i < 3; i++)
	{
		nIndex = m_cbMode.AddString(ConvertString(Modes[i]));
		m_cbMode.SetItemData(nIndex, i);
	}
	m_cbMode.SetCurSel(0);
	return TRUE;
}

void CRuleCfgdlg::ShowRuleInfo(CFG_FACERECOGNITION_INFO* pRuleInfo)
{
	if (pRuleInfo == NULL)
	{
		return;
	}
	
	m_nAccuracy = pRuleInfo->byAccuracy;
	m_nImportantRank = pRuleInfo->byImportantRank;
	m_nMaxCandidate = pRuleInfo->nMaxCandidate;
	m_nSimilarity = pRuleInfo->bySimilarity;
	m_strRuleName = pRuleInfo->szRuleName;

	int i = 0;
	for (i = 0; i < pRuleInfo->nAreaNum; i++)
	{
		if (pRuleInfo->byAreas[i] == 0)
		{
			m_bEyeBrow = true;
		}
		else if (pRuleInfo->byAreas[i] == 1)
		{
			m_bEye = true;
		}
		else if (pRuleInfo->byAreas[i] == 2)
		{
			m_bNose = true;
		}
		else if (pRuleInfo->byAreas[i] == 3)
		{
			m_bMouth = true;
		}
		else if (pRuleInfo->byAreas[i] == 4)
		{
			m_bFace = true;
		}
	}

	UpdateData(FALSE);
	for (i = 0; i < m_cbMode.GetCount(); i++)
	{
		if (pRuleInfo->byMode == m_cbMode.GetItemData(i))
		{
			m_cbMode.SetCurSel(i);
			break;
		}
	}
	OnSelchangeComboMode();
}

void CRuleCfgdlg::SaveRuleInfo(CFG_FACERECOGNITION_INFO* pRuleInfo)
{
	if (pRuleInfo == NULL)
	{
		return;
	}

    UpdateData(TRUE );
	
	memset(pRuleInfo, 0, sizeof(CFG_FACERECOGNITION_INFO));

	pRuleInfo->bRuleEnable = true;
	pRuleInfo->byAccuracy = m_nAccuracy;
	pRuleInfo->byImportantRank = m_nImportantRank;
	int nIndex = m_cbMode.GetCurSel();
	pRuleInfo->byMode = m_cbMode.GetItemData(nIndex);
	pRuleInfo->bySimilarity = m_nSimilarity;
	pRuleInfo->nMaxCandidate = m_nMaxCandidate;
	strncpy(pRuleInfo->szRuleName, (LPSTR)(LPCSTR)m_strRuleName, MAX_NAME_LEN);

	int nAreaNum = 0;
	if (m_bEyeBrow)
	{
		pRuleInfo->byAreas[nAreaNum++] = 0;
	}
	if (m_bEye)
	{
		pRuleInfo->byAreas[nAreaNum++] = 1;
	}
	if (m_bNose)
	{
		pRuleInfo->byAreas[nAreaNum++] = 2;
	}
	if (m_bMouth)
	{
		pRuleInfo->byAreas[nAreaNum++] = 3;
	}
	if (m_bFace)
	{
		pRuleInfo->byAreas[nAreaNum++] = 4;
	}
	pRuleInfo->nAreaNum = nAreaNum;
}

void CRuleCfgdlg::OnSelchangeComboMode() 
{
	int nIndex = m_cbMode.GetCurSel();
	int nVlue = m_cbMode.GetItemData(nIndex);
	
	if (nVlue == 1)
	{
		GetDlgItem(IDC_CHECK_EYEBROW)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_EYE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_MOUTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_NOSE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_FACE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_EYEBROW)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_EYE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_MOUTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_NOSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FACE)->EnableWindow(FALSE);
	}
}
