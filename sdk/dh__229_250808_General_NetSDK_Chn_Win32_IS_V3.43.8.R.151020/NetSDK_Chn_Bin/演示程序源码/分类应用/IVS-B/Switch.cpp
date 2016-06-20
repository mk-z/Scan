// Switch.cpp : implementation file
//

#include "stdafx.h"
#include "demoivsb.h"
#include "Switch.h"
#include "DemoIVSbDlg.h"
#include "RuleTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitch dialog


CSwitch::CSwitch(CWnd* pParent /*=NULL*/)
	: CDialog(CSwitch::IDD, pParent),
	m_hSelectItem(0),
	m_nChnCount(0)
{
	//{{AFX_DATA_INIT(CSwitch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSwitch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSwitch)
	DDX_Control(pDX, IDC_SWITCH_TREE_CHN, m_treeChn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSwitch, CDialog)
	//{{AFX_MSG_MAP(CSwitch)
	ON_NOTIFY(NM_CLICK, IDC_SWITCH_TREE_CHN, OnClickSwitchTreeChn)
	ON_BN_CLICKED(IDC_SWITCH_BTN_CHNSELALL, OnSwitchBtnChnselall)
	ON_BN_CLICKED(IDC_SWITCH_BTN_CHNCOUNTERSEL, OnSwitchBtnChncountersel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitch message handlers

BOOL CSwitch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	m_treeChn.ModifyStyle(TVS_CHECKBOXES, WS_BORDER, 0);
	m_treeChn.ModifyStyle(0, TVS_CHECKBOXES, 0);

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return TRUE;
	}

	NET_DEVICEINFO* pDevInfo = pMainDlg->getDevInfo();
	if (!pDevInfo)
	{
		AfxMessageBox(ConvertString(_T("Can't find DeviceInfo, try logout and login again")));
		return TRUE;
	}
	
	m_nChnCount = pDevInfo->byChanNum;

	TCHAR szChnName[32] = {0};
	HTREEITEM hItem = 0;

	CRect rt;
	GetClientRect(&rt);
	rt.left = 180 / 2 * 3;
	rt.top = 20 / 2 * 3;
	rt.right = 300 / 2 * 3;
	rt.bottom = 226 / 2 * 3;

	//通道树控件上每个节点绑定对应的通道信息
	for (int i = 0; i < m_nChnCount; i++)
	{
		//ChnTree
		_sntprintf(szChnName, _countof(szChnName), _T("%s%02d"), ConvertString(_T("Channel")), i + 1);
		hItem = m_treeChn.InsertItem(szChnName);

		m_treeChn.SetItemData(hItem, i);

		ZeroMemory(szChnName, sizeof(szChnName));
	}

	hItem = m_treeChn.GetRootItem();
	if (hItem)
	{
		m_treeChn.SelectItem(hItem);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
 *	双击通道节点，显示对应通道的可选规则
 */
void CSwitch::OnClickSwitchTreeChn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	CPoint pt;
	GetCursorPos(&pt);

	m_treeChn.ScreenToClient(&pt);
	HTREEITEM hItem = m_treeChn.HitTest(pt);

	if (!hItem)
	{
		return;
	}

	if (m_hSelectItem == hItem)
	{
		return;
	}
	m_hSelectItem = hItem;
	m_treeChn.SelectItem(hItem);

	int nChnID = m_treeChn.GetItemData(hItem);

	if (nChnID < 0 || nChnID >= m_nChnCount)
	{
		return;
	}

	TCHAR szChn[32] = {0};
	_sntprintf(szChn, _countof(szChn), _T("%s%02d"), ConvertString(_T("Channel")), nChnID + 1);
	SetDlgItemText(IDC_SWITCH_STATIC_CHN, szChn);

// 	ZeroMemory(szChn, sizeof(szChn));
// 	_sntprintf(szChn, 
// 			   _countof(szChn),
// 			   _T("%s%02d %s"), 
// 			   ConvertString(_T("Channel")), 
// 			   nChnID + 1,
// 			   ConvertString(_T("Supported RuleType")));
// 	SetDlgItemText(IDC_SWITCH_STATIC_RULE, szChn);
}
/*
 *	
 */
void CSwitch::OnOK() 
{
	// TODO: Add extra validation here
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	std::list<DWORD>* plsdwChannel = new std::list<DWORD>;
	if (plsdwChannel)
	{
		HTREEITEM hTreeItem = m_treeChn.GetRootItem();
		while(hTreeItem)
		{
			if (m_treeChn.GetCheck(hTreeItem))
			{
				DWORD dwChn = m_treeChn.GetItemData(hTreeItem);
				plsdwChannel->push_back(dwChn);
			}
			hTreeItem = m_treeChn.GetNextSiblingItem(hTreeItem);
		}

		if (!plsdwChannel->size())
		{
			delete plsdwChannel;
			plsdwChannel = NULL;
			return;
		}
		
		pMainDlg->startAlarmCallBack(plsdwChannel);
		
		DRAW_SetPen(g_nPreviewDrawPort, DRAW_ALARM, DRAW_PEN_DEFAULT, 1, RGB(255, 0, 0));
	}

	CDialog::OnOK();
}
/*
 *	
 */
void CSwitch::OnSwitchBtnChnselall() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeChn.GetRootItem();
	while(hItem)
	{
		m_treeChn.SetCheck(hItem);
		int nChn = m_treeChn.GetItemData(hItem);
		if (nChn < 0 && nChn >= g_MaxChannelCount)
		{
			hItem = m_treeChn.GetNextSiblingItem(hItem);
			continue;
		}

		hItem = m_treeChn.GetNextSiblingItem(hItem);
	}
}

void CSwitch::OnSwitchBtnChncountersel() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeChn.GetRootItem();
	while(hItem)
	{
		m_treeChn.SetCheck(hItem, FALSE);
		int nChn = m_treeChn.GetItemData(hItem);
		if (nChn < 0 && nChn >= g_MaxChannelCount)
		{
			hItem = m_treeChn.GetNextSiblingItem(hItem);
			continue;
		}
		
		hItem = m_treeChn.GetNextSiblingItem(hItem);
	}	
}
