// RulePreservation.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "RulePreservation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulePreservation dialog


CRulePreservation::CRulePreservation(CWnd* pParent /*=NULL*/)
	: CDialog(CRulePreservation::IDD, pParent),
	m_pRule(NULL)
{
	//{{AFX_DATA_INIT(CRulePreservation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRulePreservation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRulePreservation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRulePreservation, CDialog)
	//{{AFX_MSG_MAP(CRulePreservation)
	ON_EN_CHANGE(IDC_RULE7_EDT_MINDUR, OnChangeRule7EdtMindur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRulePreservation message handlers

void CRulePreservation::initSubDlg()
{
	//最短持续时间
// 	SetDlgItemInt(IDC_RULE7_EDT_MINDUR, 0, FALSE);
}

void CRulePreservation::showRuleInfo(RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || pRuleStruct->RuleInfo.dwRuleType != EVENT_IVS_PRESERVATION)
	{
		return;
	}
	
	//Todo: show info
	if (!pRuleStruct->pRuleBuf)
	{
		return;
	}
	
	CFG_PRESERVATION_INFO* pRule = (CFG_PRESERVATION_INFO*)pRuleStruct->pRuleBuf;
	m_pRule = pRule;

	//最短持续时间
	SetDlgItemInt(IDC_RULE7_EDT_MINDUR, pRule->nMinDuration, FALSE);
}

void CRulePreservation::clearRuleInfo()
{
	m_pRule = NULL;
}

void CRulePreservation::setRuleInfo(char* pRuleStruct, int nLen)
{
	if (!pRuleStruct || nLen != EVENT_IVS_PRESERVATION)
	{
		return;
	}
}

void CRulePreservation::updateDraw()
{
	if (m_pRule)
	{
		CFG_ANALYSERULES_INFO stuRuleInfo = {0};
		stuRuleInfo.nRuleCount = 1;
		stuRuleInfo.nRuleLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_PRESERVATION_INFO);
		
		CFG_RULE_INFO cfgRuleInfo = {0};
		cfgRuleInfo.dwRuleType = EVENT_IVS_PRESERVATION;
		cfgRuleInfo.nRuleSize = sizeof(CFG_PRESERVATION_INFO);
		
		stuRuleInfo.pRuleBuf = new char[sizeof(CFG_PRESERVATION_INFO) + sizeof(CFG_RULE_INFO)];
		if (!stuRuleInfo.pRuleBuf)
		{
			return;
		}
		memcpy(stuRuleInfo.pRuleBuf, &cfgRuleInfo, sizeof(CFG_RULE_INFO));
		memcpy(stuRuleInfo.pRuleBuf + sizeof(CFG_RULE_INFO), m_pRule, sizeof(CFG_PRESERVATION_INFO));
		
		//为了能画图，让规则使能
		char* pTmp = stuRuleInfo.pRuleBuf;
		pTmp += sizeof(CFG_RULE_INFO);
		CFG_CROSSLINE_INFO* pRuleInfo = (CFG_CROSSLINE_INFO*)pTmp;
		if (!pRuleInfo->bRuleEnable)
		{
			pRuleInfo->bRuleEnable = true;
		}

		::DRAW_InputRuleData(g_nRuleCfgDrawPort, 0, (unsigned char*)&stuRuleInfo, 0);
		
		delete stuRuleInfo.pRuleBuf;
		stuRuleInfo.pRuleBuf = NULL;
	}
}

BOOL CRulePreservation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
 *	修改最短持续时间
 */
void CRulePreservation::OnChangeRule7EdtMindur() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_pRule)
	{
		CString strMinDur;
		GetDlgItemText(IDC_RULE7_EDT_MINDUR, strMinDur);
		
		int iMinDur = atoi(strMinDur.GetBuffer(strMinDur.GetLength()));
		
		m_pRule->nMinDuration = iMinDur;
	}	
}
