// SubDlgNumberStatInfo.cpp : implementation file
//

#include "stdafx.h"
#include "demoIVSPC.h"
#include "SubDlgNumberStatInfo.h"
#include "GlobalDef.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDS_DARW_LINE			"Draw Line"
#define IDS_DARW_LINE_TIP       "Click left button twice to finish this move!"
#define IDS_DARW_REGION			"Draw Region"
#define IDS_DARW_REGION_TIP     "Right click to finish this move!"

/////////////////////////////////////////////////////////////////////////////
// CSubDlgNumberStatInfo dialog


CSubDlgNumberStatInfo::CSubDlgNumberStatInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgNumberStatInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgNumberStatInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSubDlgNumberStatInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgNumberStatInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_NUMSTAT_TREE_OBJTYPE, m_treeObjectType);
}


BEGIN_MESSAGE_MAP(CSubDlgNumberStatInfo, CDialog)
	//{{AFX_MSG_MAP(CSubDlgNumberStatInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_NUMSATA_BTN_DRAWDIRECTION, CSubDlgNumberStatInfo::OnBnClickedNumsataBtnDrawdirection)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO_NUMSTAT_TYPE, CSubDlgNumberStatInfo::OnCbnSelchangeComboNumstatType)
	//ON_EN_CHANGE(IDC_EDIT_PERIOD, &CSubDlgNumberStatInfo::OnEnChangeEditPeriod)
	ON_EN_CHANGE(IDC_EDIT_INTERVAL, CSubDlgNumberStatInfo::OnEnChangeEditInterval)
	//ON_EN_CHANGE(IDC_EDIT_UPPERLIMIT, &CSubDlgNumberStatInfo::OnEnChangeEditUpperlimit)
	ON_BN_CLICKED(IDC_BTN_REDRAW, CSubDlgNumberStatInfo::OnBnClickedBtnRedraw)
	ON_NOTIFY(NM_CLICK, IDC_NUMSTAT_TREE_OBJTYPE, CSubDlgNumberStatInfo::OnNMClickNumstatTreeObjtype)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgNumberStatInfo message handlers
void CSubDlgNumberStatInfo::ShowRuleInfo(const RuleStruct* pRuleStruct)
{
	if (!pRuleStruct || pRuleStruct->RuleInfo.dwRuleType != EVENT_IVS_NUMBERSTAT)
	{
		return;
	}
	
	//Todo: show info
	if (!pRuleStruct->pRuleBuf)
	{
		return;
	}
	m_treeObjectType.DeleteAllItems();
	CFG_NUMBERSTAT_INFO* pRule = (CFG_NUMBERSTAT_INFO*)pRuleStruct->pRuleBuf;
	if (pRule)
	{
		/// 设置支持物体类别
		HTREEITEM hItem = NULL;
        for (int nIndex= 0; nIndex < pRule->nObjectTypeNum; nIndex++)
        {
			hItem = m_treeObjectType.InsertItem(ConvertString(pRule->szObjectTypes[nIndex]));
			if (hItem)
			{
				m_treeObjectType.SetCheck(hItem);
			}
        }
		/// 设置周期
		char szFormatStr[MAX_PATH] = {0};
		sprintf(szFormatStr, "%d", pRule->nRecordInterval);
		this->GetDlgItem(IDC_EDIT_INTERVAL)->SetWindowText(szFormatStr);
		/// 设置数量统计类型
		CComboBox *pStatType = (CComboBox *)GetDlgItem(IDC_COMBO_NUMSTAT_TYPE);
		if (pStatType)
		{
			int nCurSel = 0;
			if (NET_EM_NUMSTAT_TYPE_REGION == pRule->emType)
			{
				//nCurSel = pStatType->AddString("Region");
				pStatType->SetCurSel(0);
				GetDlgItem(IDC_NUMSATA_BTN_DRAWDIRECTION)->SetWindowText(ConvertString(IDS_DARW_REGION));
			}
			else if (NET_EM_NUMSTAT_TYPE_ENTRANCE == pRule->emType)
			{
				//nCurSel = pStatType->AddString("Entrance");
				pStatType->SetCurSel(1);
				GetDlgItem(IDC_NUMSATA_BTN_DRAWDIRECTION)->SetWindowText(ConvertString(ConvertString(IDS_DARW_LINE)));
			}
		}
		
	}

}

void CSubDlgNumberStatInfo::OnBnClickedNumsataBtnDrawdirection()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cstrText;
	GetDlgItem(IDC_NUMSATA_BTN_DRAWDIRECTION)->GetWindowText(cstrText);
	if (cstrText.Compare(ConvertString(IDS_DARW_REGION)) == 0)
	{
		::SendMessage(GetParent()->GetSafeHwnd(), WM_RULE_DRAW, 0, (LPARAM)eRegionStart);
	}
	else
	{
		::SendMessage(GetParent()->GetSafeHwnd(), WM_RULE_DRAW, 0, (LPARAM)eDirctionStart);
	}
	
}

int CSubDlgNumberStatInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}

void CSubDlgNumberStatInfo::OnCbnSelchangeComboNumstatType()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox *pStatType = (CComboBox *)GetDlgItem(IDC_COMBO_NUMSTAT_TYPE);
	if (pStatType)
	{
		int nCurSel = pStatType->GetCurSel();
		if ( 0 == nCurSel)
		{
			GetDlgItem(IDC_NUMSATA_BTN_DRAWDIRECTION)->SetWindowText(ConvertString(IDS_DARW_REGION));
			GetDlgItem(IDC_STATIC_DRAW_TIP)->SetWindowText(ConvertString(IDS_DARW_REGION_TIP));
		}
		else if ( 1 == nCurSel)
		{
			GetDlgItem(IDC_NUMSATA_BTN_DRAWDIRECTION)->SetWindowText(ConvertString(IDS_DARW_LINE));
			GetDlgItem(IDC_STATIC_DRAW_TIP)->SetWindowText(ConvertString(IDS_DARW_LINE_TIP));
		}
	}
}
void CSubDlgNumberStatInfo::InitConfig()
{
	/// 设置数量统计类型
	CComboBox *pStatType = (CComboBox *)GetDlgItem(IDC_COMBO_NUMSTAT_TYPE);
	if (pStatType)
	{
		pStatType->Clear();
		pStatType->AddString(ConvertString("Region"));
		pStatType->AddString(ConvertString("Entrance"));
		pStatType->SetCurSel(0);
		GetDlgItem(IDC_STATIC_DRAW_TIP)->SetWindowText(ConvertString(IDS_DARW_LINE_TIP));
	}
}
/*
void CSubDlgNumberStatInfo::OnEnChangeEditPeriod()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int nPeriod = 0;
	CString cstrPeriod;
	GetDlgItemText(IDC_EDIT_PERIOD, cstrPeriod);
	nPeriod = atoi(cstrPeriod.GetBuffer());
	if (nPeriod > 0)
	{
		::SendMessage(GetParent()->GetSafeHwnd(), WM_UPDATE_NOTIFY, (WPARAM)IDC_EDIT_PERIOD, (LPARAM)nPeriod);
	}
}*/

void CSubDlgNumberStatInfo::OnEnChangeEditInterval()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int nData = 0;
	CString cstrData;
	GetDlgItemText(IDC_EDIT_INTERVAL, cstrData);
	nData = atoi(cstrData.GetBuffer(0));
	if (nData >= 0 && nData <= 10)
	{
		::SendMessage(GetParent()->GetSafeHwnd(), WM_UPDATE_NOTIFY, (WPARAM)IDC_EDIT_INTERVAL, (LPARAM)nData);
	}
}
/*
void CSubDlgNumberStatInfo::OnEnChangeEditUpperlimit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int nData = 0;
	CString cstrData;
	GetDlgItemText(IDC_EDIT_UPPERLIMIT, cstrData);
	nData = atoi(cstrData.GetBuffer());
	if (nData > 0)
	{
		::SendMessage(GetParent()->GetSafeHwnd(), WM_UPDATE_NOTIFY, (WPARAM)IDC_EDIT_UPPERLIMIT, (LPARAM)nData);
	}
}*/

void CSubDlgNumberStatInfo::OnBnClickedBtnRedraw()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cstrText;
	GetDlgItem(IDC_NUMSATA_BTN_DRAWDIRECTION)->GetWindowText(cstrText);
	if (cstrText.Compare(ConvertString(IDS_DARW_REGION)) == 0)
	{
		::SendMessage(GetParent()->GetSafeHwnd(), WM_RULE_DRAW, 0, (LPARAM)eRegionStart);
	}
	else
	{
		::SendMessage(GetParent()->GetSafeHwnd(), WM_RULE_DRAW, 0, (LPARAM)eDirctionStart);
	}
}

BOOL CSubDlgNumberStatInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	g_SetWndStaticText(this);
	m_treeObjectType.ModifyStyle( TVS_CHECKBOXES, 0 );
	m_treeObjectType.ModifyStyle( 0, TVS_CHECKBOXES );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSubDlgNumberStatInfo::OnNMClickNumstatTreeObjtype(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	/*HTREEITEM hItem = NULL;
	hItem = m_treeObjectType.GetRootItem();
	if (hItem != NULL)
	{
		m_treeObjectType.SetCheck(hItem);
	}*/
	
}
