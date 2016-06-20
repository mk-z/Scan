// DecTourDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "DecTourDlg.h"
#include "NVDSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDecTourDlg dialog


CDecTourDlg::CDecTourDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDecTourDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDecTourDlg)
	//}}AFX_DATA_INIT
	m_hCurLoginID = 0;
	m_nDecChannel = 0;
}


void CDecTourDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDecTourDlg)
	DDX_Control(pDX, IDC_EDIT_TOURTIME, m_editTourTime);
	DDX_Control(pDX, IDC_TREE_COMBIN, m_treeCombins);
	DDX_Control(pDX, IDC_COMBO_TVID, m_TVID);
	DDX_Control(pDX, IDC_COMBO_DISMODE, m_disMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDecTourDlg, CDialog)
	//{{AFX_MSG_MAP(CDecTourDlg)
	ON_BN_CLICKED(IDC_BTN_ADD_COMBIN, OnBtnAddCombin)
	ON_BN_CLICKED(IDC_BTN_DEL_COMBIN, OnBtnDelCombin)
	ON_BN_CLICKED(IDC_BTN_TOUR_OK, OnBtnTourOk)
	ON_BN_CLICKED(IDC_BTN_QUERY_COMBIN, OnBtnQueryCombin)
	ON_CBN_SELENDOK(IDC_COMBO_TVID, OnSelendokComboTvid)
	ON_CBN_SELCHANGE(IDC_COMBO_DISMODE, OnSelchangeComboDismode)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_COMMAND_RANGE(IDC_CHECK_1, IDC_CHECK_16, OnCheck1)
	ON_BN_CLICKED(IDC_BTN_DEL_ALLCOMBIN, OnBtnDelAllcombin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecTourDlg message handlers

 BOOL CDecTourDlg::OnInitDialog() 
 {
 	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
 	
 	// TODO: Add extra initialization here
	CString strText = "";
	int nIndex = 0;
	for (int i = 0; i < m_nDecChannel; i++)
	{
		strText.Format("TV %d", i);
		nIndex = m_TVID.AddString(strText);
		m_TVID.SetItemData(nIndex, i);
	}
	m_TVID.SetCurSel(0);
 	
	nIndex = m_disMode.AddString(ConvertString("one screen"));
	m_disMode.SetItemData(nIndex, 1);
	nIndex = m_disMode.AddString(ConvertString("four screen"));
	m_disMode.SetItemData(nIndex, 4);
	nIndex = m_disMode.AddString(ConvertString("nine screen"));
	m_disMode.SetItemData(nIndex, 9);
	m_disMode.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDecTourDlg::OnBtnAddCombin() 
{
	// TODO: Add your control notification handler code here
	if (!UpdateTourTime())
	{
		return;
	}
	UpdateData(TRUE);
	if (m_hCurLoginID != 0)
	{
		int nIndex = m_TVID.GetCurSel();
		if (nIndex == -1)
		{
			return;
		}
		int nTVId = m_TVID.GetItemData(nIndex);

		nIndex = m_disMode.GetCurSel();
		if (nIndex == -1)
		{
			return;
		}
		int nSplitMode = m_disMode.GetItemData(nIndex);

		BYTE bEncoderChannnel[16] = {0};
		int nBufLen = 0;
		for (int i = 0; i < 16; i++)
		{
			if (((CButton *)GetDlgItem(IDC_CHECK_1+i))->GetCheck())
			{
				bEncoderChannnel[nBufLen++] = i;
			}
		}
		int nCombinID = CLIENT_AddTourCombin(m_hCurLoginID, nTVId, nSplitMode, bEncoderChannnel, nBufLen);
		if (nCombinID >= 0)
		{
			OnBtnQueryCombin();
		}
		else
		{
			MessageBox(ConvertString("Add tour combin failed!"), ConvertString("Prompt"));
		}
	}
}
void CDecTourDlg::OnBtnDelCombin() 
{
	// TODO: Add your control notification handler code here
	CString strTip = ConvertString("Do you really want to delete? delete will disable tour!");
	if (m_hCurLoginID != 0)
	{	
		int nCountItem = m_treeCombins.GetCount();
		if (nCountItem <= 0)
		{
			MessageBox(ConvertString("Have not select tour combin, please select first!"), ConvertString("Prompt"));
			return;
		}
		
		int nIndex = m_TVID.GetCurSel();
		if (nIndex == -1)
		{
			return;
		}
		int nTVId = m_TVID.GetItemData(nIndex);		
			
		DEC_TOUR_COMBIN stuDecTourInfo = {0};
		BOOL bSuccess = CLIENT_QueryDecoderTour(m_hCurLoginID, nTVId, &stuDecTourInfo, 2000);
		if (bSuccess)
		{
			HTREEITEM hsubItem = m_treeCombins.GetRootItem();
			BOOL bTipFlag = 0;
			for (int j = 0; j < nCountItem; j++)
			{
				if (stuDecTourInfo.bCombinState[j] && hsubItem && m_treeCombins.GetCheck(hsubItem))
				{
					stuDecTourInfo.nTourTime = m_tourTime;	
					stuDecTourInfo.bCombinID[j] = (int)m_treeCombins.GetItemData(hsubItem);
					stuDecTourInfo.bCombinState[j] = 0;
					stuDecTourInfo.nCombinNum = nCountItem;
					
					if (bTipFlag ==0)
					{
						if (MessageBox(strTip, ConvertString("Prompt"), MB_YESNO|MB_ICONQUESTION)==IDNO) 
						{
							return;
						}
						else
						{
							bTipFlag = 1;
						}
					}	
				}	
				hsubItem = m_treeCombins.GetNextItem(hsubItem,TVGN_NEXT);
			}
			
			CLIENT_SetDecoderTour(m_hCurLoginID, nTVId, &stuDecTourInfo, 2000);
		}
	
		HTREEITEM hItem = m_treeCombins.GetRootItem();
		for (int i = 0; i < nCountItem && hItem; i++)
		{
			if ( m_treeCombins.GetCheck(hItem))
			{
				int nCombinID = (int)m_treeCombins.GetItemData(hItem);
				BOOL bSuccess = CLIENT_DelTourCombin(m_hCurLoginID, nTVId, nCombinID);
				if (bSuccess)
				{
					//	OnBtnQueryCombin();
				}
				else
				{
					MessageBox(ConvertString("Delete tour combin failed!"), ConvertString("Prompt"));
				}
			}
			hItem = m_treeCombins.GetNextItem(hItem,TVGN_NEXT);
		}
		
		OnBtnQueryCombin();
	}
}

void CDecTourDlg::OnBtnDelAllcombin() 
{
	// TODO: Add your control notification handler code here
	if (m_hCurLoginID != 0)
	{
		int nIndex = m_TVID.GetCurSel();
		if (nIndex == -1)
		{
			return;
		}
		int nTVId = m_TVID.GetItemData(nIndex);

		int nCountItem = m_treeCombins.GetCount();

		CString strTip = ConvertString("Do you really want to delete? delete will disable tour!");
				
		DEC_TOUR_COMBIN stuDecTourInfo = {0};
		BOOL bSuccess = CLIENT_QueryDecoderTour(m_hCurLoginID, nTVId, &stuDecTourInfo, 2000);
		if (bSuccess)
		{
			HTREEITEM hsubItem = m_treeCombins.GetRootItem();
			BOOL bTipFlag = 0;
			for (int j = 0; j < nCountItem; j++)
			{
				if (stuDecTourInfo.bCombinState[j] && hsubItem && m_treeCombins.GetCheck(hsubItem))
				{
					stuDecTourInfo.nTourTime = m_tourTime;	
					stuDecTourInfo.bCombinID[j] = (int)m_treeCombins.GetItemData(hsubItem);
					stuDecTourInfo.bCombinState[j] = 0;
					stuDecTourInfo.nCombinNum = nCountItem;
					
					if (bTipFlag ==0)
					{
						if (MessageBox(strTip, ConvertString("Prompt"), MB_YESNO|MB_ICONQUESTION)==IDNO) 
						{
							return;
						}
						else
						{
							bTipFlag = 1;
						}
					}	
				}	
				hsubItem = m_treeCombins.GetNextItem(hsubItem,TVGN_NEXT);
			}
			
			CLIENT_SetDecoderTour(m_hCurLoginID, nTVId, &stuDecTourInfo, 2000);
		}

		HTREEITEM hItem = m_treeCombins.GetRootItem();
		for (int i = 0; i < nCountItem && hItem; i++)
		{
			int nCombinID = m_treeCombins.GetItemData(hItem);
			BOOL bSuccess = CLIENT_DelTourCombin(m_hCurLoginID, nTVId, nCombinID);

			hItem = m_treeCombins.GetNextItem(hItem,TVGN_NEXT);
		}

		OnBtnQueryCombin();
	}
}


void CDecTourDlg::OnBtnTourOk() 
{
	// TODO: Add your control notification handler code here
	if (m_hCurLoginID != 0)
	{
		int nIndex = m_TVID.GetCurSel();
		if (nIndex == -1)
		{
			return;
		}
		int nTVId = m_TVID.GetItemData(nIndex);

		if (!UpdateTourTime())
		{
			return;
		}
		UpdateData(TRUE);
		
		DEC_TOUR_COMBIN stuDecTourInfo = {0};
		stuDecTourInfo.nTourTime = m_tourTime;

		int nCountItem = m_treeCombins.GetCount();
		if (nCountItem <= 0)
		{
			MessageBox(ConvertString("No tour combin!"), ConvertString("Prompt"));
			return;
		}

		HTREEITEM hItem = m_treeCombins.GetRootItem();
		for (int i = 0; i < nCountItem && hItem; i++)
		{
			stuDecTourInfo.bCombinID[i] = m_treeCombins.GetItemData(hItem);
			if (m_treeCombins.GetCheck(hItem))
			{
				stuDecTourInfo.bCombinState[i] = 1;
			}
			else
			{
				stuDecTourInfo.bCombinState[i] = 0;
			}
			hItem = m_treeCombins.GetNextItem(hItem,TVGN_NEXT);
		}

		stuDecTourInfo.nCombinNum = nCountItem;
		BOOL bSuccess = CLIENT_SetDecoderTour(m_hCurLoginID, nTVId, &stuDecTourInfo, 2000);
		if (bSuccess)
		{
			MessageBox(ConvertString("Toure success!"), ConvertString("Prompt"));
		}
		else
		{
			MessageBox(ConvertString("Failed to tour!"), ConvertString("Prompt"));
		}

		OnBtnQueryCombin();
	}
}

void CDecTourDlg::SetDlgParam(LLONG lLoginID, int nDevChannel)
{
	m_hCurLoginID = lLoginID;
	m_nDecChannel = nDevChannel;
}

void CDecTourDlg::OnBtnQueryCombin() 
{
	// TODO: Add your control notification handler code here
	if (m_hCurLoginID != 0)
	{
		int nIndex = m_TVID.GetCurSel();
		if (nIndex == -1)
		{
			return;
		}

		int nTVId = m_TVID.GetItemData(nIndex);
		m_treeCombins.DeleteAllItems();

		// Query tour config
		DEC_TOUR_COMBIN stuDecTourInfo = {0};
		BOOL bSuccess = CLIENT_QueryDecoderTour(m_hCurLoginID, nTVId, &stuDecTourInfo, 2000);
		if (bSuccess)
		{
			m_tourTime = stuDecTourInfo.nTourTime;

			for (int k = 0; k < stuDecTourInfo.nCombinNum; k++)
			{
				BYTE bCombinID = stuDecTourInfo.bCombinID[k];
				BYTE bCombinState = stuDecTourInfo.bCombinState[k];

				// Query tour combin
				DEC_COMBIN_INFO stuDecCombinInfo = {0};
				BOOL bSuccess = CLIENT_QueryTourCombin(m_hCurLoginID, nTVId, bCombinID, &stuDecCombinInfo);
				if (bSuccess)
				{
					CString strItemText;
					strItemText.Format("%d: ", k+1);
					if (stuDecCombinInfo.nSplitType == 1)
					{
						strItemText += ConvertString("one screen");
						strItemText += " : ";
					}
					else if (stuDecCombinInfo.nSplitType == 4)
					{
						strItemText += ConvertString("four screen");
						strItemText += " : ";
					}
					
					for (int k = 0; k < stuDecCombinInfo.nSplitType; k++)
					{
						CString str;
						str.Format("%d ", stuDecCombinInfo.bDisChn[k] + 1);
						strItemText += str;
					}
					
					HTREEITEM hItem = m_treeCombins.InsertItem(strItemText,TVI_ROOT,TVI_LAST);
					m_treeCombins.SetItemData(hItem, stuDecCombinInfo.nCombinID);
					m_treeCombins.SetCheck(hItem, bCombinState ? TRUE:FALSE);
				}
				else
				{
					MessageBox(ConvertString("Failed to query tour combin!"), ConvertString("Prompt"));
				}
			}
		}
		else
		{
			MessageBox(ConvertString("Failed to query tour information!"), ConvertString("Prompt"));
		}
		UpdateTourTime(FALSE);
		UpdateData(FALSE);
	}
	else
	{
		MessageBox(ConvertString("Have not login!"), ConvertString("Prompt"));
	}

	return;	
}

void CDecTourDlg::OnSelendokComboTvid() 
{
	// TODO: Add your control notification handler code here
	OnBtnQueryCombin();
}

void CDecTourDlg::OnSelchangeComboDismode() 
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < 16; i++)
	{
		((CButton*)GetDlgItem(IDC_CHECK_1+i))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_1+i))->SetCheck(FALSE);
	}
}

void CDecTourDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

}

void CDecTourDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDecTourDlg::OnCheck1(UINT uID) 
{
	// TODO: Add your control notification handler code here
	if (((CButton *)GetDlgItem(uID))->GetCheck())
	{
		((CButton *)GetDlgItem(uID))->SetCheck(FALSE);
	}
	else
	{
		((CButton *)GetDlgItem(uID))->SetCheck(TRUE);
	}
	
	int nTotalCount = m_disMode.GetItemData(m_disMode.GetCurSel());
	int nCheckCount = 0;

	for (int i = 0; i < 16; i++)
	{
		if (((CButton *)GetDlgItem(IDC_CHECK_1+i))->GetCheck())
		{
			nCheckCount++;
		}
	}

	if (((CButton *)GetDlgItem(uID))->GetCheck())
	{
		((CButton *)GetDlgItem(uID))->SetCheck(FALSE);
		nCheckCount--;

		if (nCheckCount < nTotalCount)
		{
			for (int i = 0; i < 16; i++)
			{
				if (!((CButton *)GetDlgItem(IDC_CHECK_1+i))->IsWindowEnabled())
				{
					((CButton *)GetDlgItem(IDC_CHECK_1+i))->EnableWindow(TRUE);
				}
			}
		}
	}
	else
	{
		if (nCheckCount < nTotalCount)
		{
			((CButton *)GetDlgItem(uID))->SetCheck(TRUE);
			nCheckCount++;
		}

		if (nCheckCount >= nTotalCount)
		{
			for (int i = 0; i < 16; i++)
			{
				if (((CButton *)GetDlgItem(IDC_CHECK_1+i))->GetCheck() == 0)
				{
					((CButton *)GetDlgItem(IDC_CHECK_1+i))->EnableWindow(FALSE);
				}
			}
		}
	}
}

BOOL CDecTourDlg::UpdateTourTime(BOOL b)
{
	if (!b)
	{
		CString strTime;
		strTime.Format("%d", m_tourTime);
		m_editTourTime.SetWindowText(strTime);
		return TRUE;
	}
	CString str;
	m_editTourTime.GetWindowText(str);
	if (str.IsEmpty())
	{
		MessageBox(ConvertString("Input tour time first!"), ConvertString("Prompt"));
		return FALSE;
	}

	if (atoi(str.GetBuffer(0)) == 0)
	{
		MessageBox(ConvertString("Tour time must be a positive number!"), ConvertString("Prompt"));
		return FALSE;
	}

	m_tourTime = atoi(str.GetBuffer(0));
	return TRUE;
};


