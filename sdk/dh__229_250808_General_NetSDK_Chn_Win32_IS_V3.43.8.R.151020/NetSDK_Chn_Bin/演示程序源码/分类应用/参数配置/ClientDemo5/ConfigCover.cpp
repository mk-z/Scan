// ConfigCover.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigCover.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigCover dialog


CConfigCover::CConfigCover(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigCover::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigCover)
		// NOTE: the ClassWizard will add member initialization here
//	m_bEncodeEnable = FALSE;
//	m_bPreViewEnable = FALSE;
	//}}AFX_DATA_INIT
	m_nChannelCount  = 0;
	m_nCurChannel    = -1;
	m_nVideoWidget   = -1;
	m_pstVideoWidget = NULL;
}


void CConfigCover::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigCover)
	DDX_Control(pDX, IDC_COMBO_VIDEOWIDGET, m_ctlVideoWidget);
//	DDX_Control(pDX, IDC_COMBO_TYPE, m_ctlCoverType);
	DDX_Control(pDX, IDC_LIST_COVERS, m_ctlCoverLst);
	DDX_Control(pDX, IDC_COMBO_CHANNO, m_ctlChannel);
//	DDX_Check(pDX, IDC_CHECK_ENCODEENA, m_bEncodeEnable);
//	DDX_Check(pDX, IDC_CHECK_PREVIEWENA, m_bPreViewEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigCover, CDialog)
	//{{AFX_MSG_MAP(CConfigCover)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNO, OnSelchangeComboChanno)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_COVERS, OnItemchangedListCovers)
	ON_WM_CANCELMODE()
//	ON_CBN_EDITCHANGE(IDC_COMBO_VIDEOWIDGET, OnEditchangeComboVideowidget)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEOWIDGET, OnSelchangeComboVideowidget)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigCover message handlers

BOOL CConfigCover::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	InitListView();
//	ConvertComboBox(m_ctlCoverType);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigCover::InitListView()
{
	m_ctlCoverLst.SetExtendedStyle(m_ctlCoverLst.GetExtendedStyle() | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlCoverLst.InsertColumn(0, ConvertString("area"),LVCFMT_LEFT,60,-1);
	m_ctlCoverLst.InsertColumn(1, ConvertString("Margin-left"),LVCFMT_LEFT,90,0);
	m_ctlCoverLst.InsertColumn(2, ConvertString("Margin-top"),LVCFMT_LEFT,90,1);
	m_ctlCoverLst.InsertColumn(3, ConvertString("Margin-right"),LVCFMT_LEFT,90,2);
	m_ctlCoverLst.InsertColumn(4, ConvertString("Margin-bottom"),LVCFMT_LEFT,90,3);
	m_ctlCoverLst.InsertColumn(5, ConvertString("PreviewBlend"),LVCFMT_LEFT,80,4);
	m_ctlCoverLst.InsertColumn(6, ConvertString("BlendMain"),LVCFMT_LEFT,80,5);
	m_ctlCoverLst.InsertColumn(7, ConvertString("BlendExtra1"),LVCFMT_LEFT,80,6);
	m_ctlCoverLst.InsertColumn(8, ConvertString("BlendExtra2"), LVCFMT_LEFT,80,7);
	m_ctlCoverLst.InsertColumn(9, ConvertString("BlendExtra3"), LVCFMT_LEFT,80,8);
	m_ctlCoverLst.InsertColumn(10, ConvertString("BlendSnapshot"), LVCFMT_LEFT,80,9);
	m_ctlCoverLst.InsertColumn(11, ConvertString("FrontColor-Red"), LVCFMT_LEFT,100,10);
	m_ctlCoverLst.InsertColumn(12, ConvertString("FrontColor-Green"), LVCFMT_LEFT,100,11);
	m_ctlCoverLst.InsertColumn(13, ConvertString("FrontColor-Blue"), LVCFMT_LEFT,100,12);
	m_ctlCoverLst.InsertColumn(14, ConvertString("FrontColor-Alpha"), LVCFMT_LEFT,100,13);
	m_ctlCoverLst.InsertColumn(15, ConvertString("BackColor-Red"),LVCFMT_LEFT,100,14);
	m_ctlCoverLst.InsertColumn(16, ConvertString("BackColor-Green"),LVCFMT_LEFT,100,15);
	m_ctlCoverLst.InsertColumn(17, ConvertString("BackColor-Blue"),LVCFMT_LEFT,100,16);
	m_ctlCoverLst.InsertColumn(18, ConvertString("BackColor-Alpha"),LVCFMT_LEFT,100,17);
}

void CConfigCover::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
//	if(m_nCurChannel > -1 && m_nCurChannel < 32)    
    if(m_nCurChannel >= MIN_CHANNEL_NUM_TAG && m_nCurChannel < MAX_CHANNEL_NUM_TAG)  
	{
		if(m_nVideoWidget == 2)
		{
			
			int nCount = m_ctlCoverLst.GetItemCount();
			if(nCount >= AV_CFG_Max_Video_Widget_Cover)
			{
				MessageBox(ConvertString("More than  Max number!"), ConvertString("Prompt"));
				return;
			}
			AV_CFG_VideoWidgetCover& CoverInfo = m_pstVideoWidget[m_nCurChannel].stuCovers[nCount];

			int nTmp     = 0;
			int nLeft    = 0;
			int nTop     = 0;
			int nRight   = 0;
			int nBottom  = 0;
			int nRet     = 0;

			CString strID;
			strID.Format("%d" , nCount + 1);

			// Rect Info
			//CString strLeft;
			nLeft = GetDlgItemInt(IDC_EDIT_MLEFT);
			nRet = JudgeCoordinate(nLeft);
			if(nRet)
			{
				CoverInfo.stuRect.nLeft = nLeft;
			}
			else
			{
				return;
			}	

			//CString strTop;
			nTop = GetDlgItemInt(IDC_EDIT_MTOP);
			nRet = JudgeCoordinate(nTop);
			if(nRet)
			{
				CoverInfo.stuRect.nTop = nTop;
			}
			else
			{
				return;
			}
					
			//CString strRight;
			nRight = GetDlgItemInt(IDC_EDIT_MRIGHT);
			nRet = JudgeCoordinate(nRight);
			if(nRet)
			{
				CoverInfo.stuRect.nRight = nRight;		
			}
			else
			{
				return;
			}
		
			//CString strBottom;
			nBottom = GetDlgItemInt(IDC_EDIT_MBOTTOM);
			nRet = JudgeCoordinate(nBottom);
			if(nRet)
			{
				CoverInfo.stuRect.nBottom = nBottom;	
			}
			else
			{
				return;
			}
			

			if(nLeft > nRight || nTop > nBottom)
			{
				MessageBox(ConvertString("Coordinate error!"), ConvertString("Prompt"));
				return;
			}

// 			strLeft.Format("%d", nLeft);
// 			strTop.Format("%d", nTop);
// 			strRight.Format("%d", nRight);
// 			strBottom.Format("%d", nBottom);
				
			//Blend Info
// 			CString strPreviewMain;
// 			if(((CButton*)(GetDlgItem(IDC_CHECK_PREVIEWBLEND)))->GetCheck())
// 			{
// 				strPreviewMain.Format(ConvertString("true"));
// 			}
// 			else
// 			{	
// 				strPreviewMain.Format(ConvertString("false"));
// 			}

			CoverInfo.bPreviewBlend = ((CButton*)(GetDlgItem(IDC_CHECK_PREVIEWBLEND)))->GetCheck();

// 			CString strBlendMain;
// 			if(((CButton*)(GetDlgItem(IDC_CHECK_BLENDMAIN)))->GetCheck())
// 			{
// 				strBlendMain.Format(ConvertString("true"));
// 			}
// 			else
// 			{	
// 				strBlendMain.Format(ConvertString("false"));
// 			}

			CoverInfo.bEncodeBlend = ((CButton*)(GetDlgItem(IDC_CHECK_BLENDMAIN)))->GetCheck();

// 			CString strBlendExtra1;
// 			if(((CButton *)(GetDlgItem(IDC_CHECK_BLENDEXTRA1)))->GetCheck())
// 			{
// 				strBlendExtra1.Format(ConvertString("true"));
// 			}
// 			else
// 			{
// 				strBlendExtra1.Format(ConvertString("false"));
// 			}

			CoverInfo.bEncodeBlendExtra1 = ((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA1)))->GetCheck();

// 			CString strBlendExtra2;
// 			if(((CButton *)(GetDlgItem(IDC_CHECK_BLENDEXTRA2)))->GetCheck())
// 			{
// 				strBlendExtra2.Format(ConvertString("true"));
// 			}
// 			else
// 			{
// 				strBlendExtra2.Format(ConvertString("false"));
// 			}

			CoverInfo.bEncodeBlendExtra2 = ((CButton *)(GetDlgItem(IDC_CHECK_BLENDEXTRA2)))->GetCheck();

// 			CString strBlendExtra3;
// 			if(((CButton *)(GetDlgItem(IDC_CHECK_BLENDEXTRA3)))->GetCheck())
// 			{
// 				strBlendExtra3.Format(ConvertString("true"));
// 			}
// 			else
// 			{
// 				strBlendExtra3.Format(ConvertString("false"));
// 			}

			CoverInfo.bEncodeBlendExtra3 = ((CButton *)(GetDlgItem(IDC_CHECK_BLENDEXTRA3)))->GetCheck();

// 			CString strBlendBlendSnapshot;
// 			if(((CButton *)(GetDlgItem(IDC_CHECK_BLENDSNAPSHOT)))->GetCheck())
// 			{
// 				strBlendBlendSnapshot.Format(ConvertString("true"));
// 			}
// 			else
// 			{	
// 				strBlendBlendSnapshot.Format(ConvertString("false"));
// 			}
			
			CoverInfo.bEncodeBlendSnapshot = ((CButton *)(GetDlgItem(IDC_CHECK_BLENDSNAPSHOT)))->GetCheck();

			//Front color
			//CString strFRed;
			nTmp = GetDlgItemInt(IDC_EDIT_FORE_RED);
			nRet = JudgeColor(nTmp);
			if(nRet)
			{
				//strFRed.Format("%d", nTmp);	
				CoverInfo.stuFrontColor.nRed = nTmp;
			}
			else
			{
				return;
			}
			
			//CString strFGreen;
			nTmp = GetDlgItemInt(IDC_EDIT_FORE_GREEN);
			nRet = JudgeColor(nTmp);
			if(nRet)
			{
				//strFGreen.Format("%d", nTmp);
				CoverInfo.stuFrontColor.nGreen = nTmp;
			}
			else
			{
				return;
			}

			//CString strFBlue;
			nTmp = GetDlgItemInt(IDC_EDIT_FORE_BLUE);
			nRet = JudgeColor(nTmp);
			if(nRet)
			{
				//strFBlue.Format("%d", nTmp);
				CoverInfo.stuFrontColor.nBlue = nTmp;
			}
			else
			{
				return;
			}
			
			//CString strFAlpha;
			nTmp = GetDlgItemInt(IDC_EDIT_FORE_ALPHA);
			nRet = JudgeColor(nTmp);
			if(nRet)
			{
				//strFAlpha.Format("%d", nTmp);
				CoverInfo.stuFrontColor.nAlpha = nTmp;
			}
			else
			{
				return;
			}
			


			//Back  color
			//CString strBRed;
			nTmp = GetDlgItemInt(IDC_EDIT_BACK_RED);
			nRet = JudgeColor(nTmp);
			if(nRet)
			{
				//strBRed.Format("%d", nTmp);	
				CoverInfo.stuBackColor.nRed = nTmp;
			}
			else
			{
				return;
			}
			
			
			//CString strBGreen;
			nTmp = GetDlgItemInt(IDC_EDIT_BACK_GREEN);
			nRet = JudgeColor(nTmp);
			if(nRet)
			{
				//strBGreen.Format("%d", nTmp);	
				CoverInfo.stuBackColor.nGreen = nTmp;
			}
			else
			{
				return;
			}
			

			//CString strBBlue;
			nTmp = GetDlgItemInt(IDC_EDIT_BACK_BLUE);
			nRet = JudgeColor(nTmp);
			if(nRet)
			{
				//strBBlue.Format("%d", nTmp);
				CoverInfo.stuBackColor.nBlue = nTmp;
			}
			else
			{
				return;
			}
			
			//CString strBAlpha;
			nTmp = GetDlgItemInt(IDC_EDIT_BACK_ALPHA);
			nRet = JudgeColor(nTmp);
			if(nRet)
			{
				//strBAlpha.Format("%d", nTmp);
				CoverInfo.stuBackColor.nAlpha = nTmp;
			}
			else
			{
				return;
			}

			ShowVideoWidget(m_pstVideoWidget[m_nCurChannel].stuCovers, nCount);
// 			InsertListView(strID, 
// 				strLeft, strTop, strRight, strBottom, 
// 				strPreviewMain, strBlendMain, strBlendExtra1, strBlendExtra2, strBlendExtra3, strBlendBlendSnapshot,
// 				strFRed, strFGreen, strFBlue, strFAlpha,
// 		strBRed, strBGreen, strBBlue, strBAlpha);
		
		}
		

	}


	
//	InsertListView(strID, strLeft, strTop, strRight, strBotton, strColor, strType, strEncodeEnable, strPreViewEnable);
}

void CConfigCover::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_ctlCoverLst.GetItemCount())
	{
		if(0 < m_ctlCoverLst.GetSelectedCount())
		{
			int nIndex = m_ctlCoverLst.GetSelectionMark();
			if(-1 != nIndex)
			{
				m_ctlCoverLst.DeleteItem(nIndex);
			}
		}
	}
}

void CConfigCover::OnButtonModify() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_ctlCoverLst.GetItemCount())
	{
		if(0 < m_ctlCoverLst.GetSelectedCount())
		{
			int nIndex = m_ctlCoverLst.GetSelectionMark();
			if(-1 != nIndex)
			{				
				int nTmp;
				BOOL nRet = FALSE;
				
				//Rect Info
				CString strLeft;
				nTmp = GetDlgItemInt(IDC_EDIT_MLEFT);
				nRet = JudgeCoordinate(nTmp);
				if(nRet)
				{
					strLeft.Format("%d",nTmp);
				}
				else
				{
					return;
				}

				CString strTop;
				nTmp = GetDlgItemInt(IDC_EDIT_MTOP);
				nRet = JudgeCoordinate(nTmp);
				if(nRet)
				{
					strTop.Format("%d", nTmp);
				}
				else
				{
					return;
				}

				CString strRight;
				nTmp = GetDlgItemInt(IDC_EDIT_MRIGHT);
				nRet = JudgeCoordinate(nTmp);
				if(nRet)
				{	
					strRight.Format("%d",nTmp);
				}
				else
				{
					return;
				}
				
				CString strBottom;
				nTmp = GetDlgItemInt(IDC_EDIT_MBOTTOM);
				nRet = JudgeCoordinate(nTmp);
				if(nRet)
				{
					strBottom.Format("%d",nTmp);
				}
				else
				{
					return;
				}

				// Blend Info

				CString strPreviewMain;
				if(((CButton*)(GetDlgItem(IDC_CHECK_PREVIEWBLEND)))->GetCheck())
				{
					strPreviewMain.Format(ConvertString("true"));
				}
				else
				{	
					strPreviewMain.Format(ConvertString("false"));
				}

				CString strBlendMain;
				if(((CButton*)(GetDlgItem(IDC_CHECK_BLENDMAIN)))->GetCheck())
				{
					strBlendMain.Format(ConvertString("true"));	
				}
				else
				{
					strBlendMain.Format(ConvertString("false"));	
				}
				
				CString strBlendExtra1;
				if(((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA1)))->GetCheck())
				{
					strBlendExtra1.Format(ConvertString("true"));	
				}
				else
				{
					strBlendExtra1.Format(ConvertString("false"));	
				}

				CString strBlendExtra2;
				if(((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA2)))->GetCheck())
				{
					strBlendExtra2.Format(ConvertString("true"));	
				}
				else
				{
					strBlendExtra2.Format(ConvertString("false"));	
				}

				CString strBlendExtra3;
				if(((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA3)))->GetCheck())
				{
					strBlendExtra3.Format(ConvertString("true"));	
				}
				else
				{
					strBlendExtra3.Format(ConvertString("false"));	
				}

				CString strBlendBlendSnapshot;
				if(((CButton*)(GetDlgItem(IDC_CHECK_BLENDSNAPSHOT)))->GetCheck())
				{
					strBlendBlendSnapshot.Format(ConvertString("true"));	
				}
				else
				{
					strBlendBlendSnapshot.Format(ConvertString("false"));	
				}


				//Front color
				CString strFRed;
				nTmp = GetDlgItemInt(IDC_EDIT_FORE_RED);
				nRet = JudgeColor(nTmp);
				if(nRet)
				{
					strFRed.Format("%d", nTmp);
				}
				else
				{
					return;
				}

				CString strFGreen;
				nTmp = GetDlgItemInt(IDC_EDIT_FORE_GREEN);
				nRet = JudgeColor(nTmp);
				if(nRet)
				{
					strFGreen.Format("%d", nTmp);
				}
				else
				{
					return;
				}

				CString strFBlue;
				nTmp = GetDlgItemInt(IDC_EDIT_FORE_BLUE);
				nRet = JudgeColor(nTmp);
				if(nRet)
				{
					strFBlue.Format("%d", nTmp);
				}
				else
				{
					return;
				}

				CString strFAlpha;
				nTmp = GetDlgItemInt(IDC_EDIT_FORE_ALPHA);
				nRet = JudgeColor(nTmp);
				if(nRet)
				{
					strFAlpha.Format("%d", nTmp);
				}
				else
				{
					return;
				}
				//Back color

				CString strBRed;
				nTmp = GetDlgItemInt(IDC_EDIT_BACK_RED);
				nRet = JudgeColor(nTmp);
				if(nRet)
				{
					strBRed.Format("%d", nTmp);
				}
				else
				{
					return;
				}

				CString strBGreen;
				nTmp = GetDlgItemInt(IDC_EDIT_BACK_GREEN);
				nRet = JudgeColor(nTmp);
				if(nRet)
				{
					strBGreen.Format("%d", nTmp);
				}
				else
				{
					return;
				}

				CString strBBlue;
				nTmp = GetDlgItemInt(IDC_EDIT_BACK_BLUE);
				nRet = JudgeColor(nTmp);
				if(nRet)
				{
					strBBlue.Format("%d", nTmp);
				}
				else
				{
					return;
				}

			
				CString strBAlpha;
				nTmp = GetDlgItemInt(IDC_EDIT_BACK_ALPHA);
				nRet = JudgeColor(nTmp);
				if(nRet)
				{
					strBAlpha.Format("%d", nTmp);
				}
				else
				{
					return;
				}	

				m_ctlCoverLst.SetItemText(nIndex, 1, strLeft);
				m_ctlCoverLst.SetItemText(nIndex, 2, strTop);
				m_ctlCoverLst.SetItemText(nIndex, 3, strRight);
				m_ctlCoverLst.SetItemText(nIndex, 4, strBottom);
				m_ctlCoverLst.SetItemText(nIndex, 5, strPreviewMain);
				m_ctlCoverLst.SetItemText(nIndex, 6, strBlendMain);
				m_ctlCoverLst.SetItemText(nIndex, 7, strBlendExtra1);
				m_ctlCoverLst.SetItemText(nIndex, 8, strBlendExtra2);
				m_ctlCoverLst.SetItemText(nIndex, 9, strBlendExtra3);
				m_ctlCoverLst.SetItemText(nIndex, 10, strBlendBlendSnapshot);
				m_ctlCoverLst.SetItemText(nIndex, 11, strFRed);
				m_ctlCoverLst.SetItemText(nIndex, 12, strFGreen);
				m_ctlCoverLst.SetItemText(nIndex, 13, strFBlue);
				m_ctlCoverLst.SetItemText(nIndex, 14, strFAlpha);
				m_ctlCoverLst.SetItemText(nIndex, 15, strBRed);
				m_ctlCoverLst.SetItemText(nIndex, 16, strBGreen);
				m_ctlCoverLst.SetItemText(nIndex, 17, strBBlue);
				m_ctlCoverLst.SetItemText(nIndex, 18, strBAlpha);
			}
		}
	}
}

void CConfigCover::InitDlgInfo(int nLength)
{
	m_ctlChannel.ResetContent();
	m_ctlVideoWidget.ResetContent();
	m_nChannelCount = nLength;
	
	if(m_pstVideoWidget)
	{
		delete[] m_pstVideoWidget;
		m_pstVideoWidget = NULL;
	}
	m_pstVideoWidget = new AV_CFG_VideoWidget[CHANNEL_NUM_LIMIT];
	if(NULL == m_pstVideoWidget)
	{
		return;
	}
	memset(m_pstVideoWidget, 0 , sizeof(AV_CFG_VideoWidget) * CHANNEL_NUM_LIMIT);



	CString str;
	int nIndex = 0;
	//Channel dropdown menu setup
	for(int i=0;i<m_nChannelCount;i++)
	{
		str.Format("%d",i+1);
		nIndex = m_ctlChannel.AddString(str);
		m_ctlChannel.SetItemData(nIndex,i);
		//Save channel video information 
	}

	//VideoWidget dropdown menu setup
	nIndex = 0;
	str.Format(ConvertString("ChannelTitle"));
	nIndex = m_ctlVideoWidget.AddString(str);
	
	str.Format(ConvertString("TimeTitle"));
	nIndex = m_ctlVideoWidget.AddString(str);

	str.Format(ConvertString("Covers"));
	nIndex = m_ctlVideoWidget.AddString(str);


	//Select channel 0
	if(0 < m_ctlChannel.GetCount())
	{
		m_ctlChannel.SetCurSel(0);
		OnSelchangeComboChanno();
	}
}

void CConfigCover::CleanAll()
{
// 	m_ctlChannel.SetCurSel(-1);
	m_ctlCoverLst.DeleteAllItems();
	m_ctlChannel.ResetContent();

	SetDlgItemText(IDC_EDIT_MLEFT, "");
	SetDlgItemText(IDC_EDIT_MTOP, "");
	SetDlgItemText(IDC_EDIT_MRIGHT, "");
	SetDlgItemText(IDC_EDIT_MBOTTOM, "");
	SetDlgItemText(IDC_EDIT_FORE_RED, "");
	SetDlgItemText(IDC_EDIT_FORE_GREEN, "");
	SetDlgItemText(IDC_EDIT_FORE_BLUE, "");
	SetDlgItemText(IDC_EDIT_FORE_ALPHA, "");
	SetDlgItemText(IDC_EDIT_BACK_RED, "");
	SetDlgItemText(IDC_EDIT_BACK_GREEN, "");
	SetDlgItemText(IDC_EDIT_BACK_BLUE, "");
	SetDlgItemText(IDC_EDIT_BACK_ALPHA, "");
	
	((CButton*)(GetDlgItem(IDC_CHECK_PREVIEWBLEND)))->SetCheck(false);
	((CButton*)(GetDlgItem(IDC_CHECK_BLENDMAIN)))->SetCheck(false);
	((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA1)))->SetCheck(false);
	((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA2)))->SetCheck(false);
	((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA3)))->SetCheck(false);
	((CButton*)(GetDlgItem(IDC_CHECK_BLENDSNAPSHOT)))->SetCheck(false);

	m_nChannelCount = 0;
	m_nCurChannel = -1;
	if(m_pstVideoWidget)
	{
		delete[] m_pstVideoWidget;
		m_pstVideoWidget = NULL;
	}

}

void CConfigCover::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	if(-1 != m_ctlChannel.GetCurSel())
	{
		SaveChannelInfo(m_nCurChannel,m_nVideoWidget);
		//Call father window to save data 
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetOneChannelOsdInfo(&m_pstVideoWidget[m_nCurChannel], m_nCurChannel);
			
	}
	else
	{
		MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
	}
}

void CConfigCover::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	//Call father window to read data 
	
	//First clear
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetCoverConfigInfo();	
}

void CConfigCover::SaveChannelInfo(int nNum, int nVideoWidget)
{
	if(-1 < nNum)
	{
	
		if(-1 < nVideoWidget)
		{
			if(0 == nVideoWidget) //ChannelTitle Info
			{
				SaveVideoWidgetChannelTitle(&m_pstVideoWidget[nNum].stuChannelTitle);
			}
			else if(1 == nVideoWidget) //TimeTitle Info
			{
				SaveVideoWidgetTimeTitle(&m_pstVideoWidget[nNum].stuTimeTitle);
			}
			else if(2 == nVideoWidget)	//Covers Info
			{
				SaveVideoWidgetCover(m_pstVideoWidget[nNum].stuCovers, &m_pstVideoWidget[nNum].nConverNum);
			}
		}
	}
}

void CConfigCover::OnSelchangeComboChanno() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = (int)m_ctlChannel.GetItemData(nIndex);

		//First save channel nformaiton
		SaveChannelInfo(m_nCurChannel, m_nVideoWidget);

		m_ctlVideoWidget.SetCurSel(0); // ChannelTitle

		GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);

		((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneChannelOsdInfo(&m_pstVideoWidget[nNum],nNum);

		ShowVideoWidgetChannelTitle(&m_pstVideoWidget[nNum].stuChannelTitle);
		
		m_nCurChannel = nNum;
		m_nVideoWidget = 0;
	}
}


void CConfigCover::OnItemchangedListCovers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pNMListView ==NULL)
	{
		return;
	}

	if (pNMListView->uNewState == 3/* && pNMListView->uOldState == 0*/)
	{
		int nIndex = pNMListView->iItem;
		if(-1 != nIndex)
		{
			CString strTmp;

			//Rect
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 1);
			SetDlgItemText(IDC_EDIT_MLEFT, strTmp);
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 2);
			SetDlgItemText(IDC_EDIT_MTOP, strTmp);
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 3);
			SetDlgItemText(IDC_EDIT_MRIGHT, strTmp);
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 4);
			SetDlgItemText(IDC_EDIT_MBOTTOM, strTmp);



			//Blend Info
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 5);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				((CButton*)(GetDlgItem(IDC_CHECK_PREVIEWBLEND)))->SetCheck(true);
			}
			else
			{
				((CButton*)(GetDlgItem(IDC_CHECK_PREVIEWBLEND)))->SetCheck(false);
			}

			strTmp = m_ctlCoverLst.GetItemText(nIndex, 6);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDMAIN)))->SetCheck(true);
			}
			else
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDMAIN)))->SetCheck(false);
			}
			
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 7);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA1)))->SetCheck(true);
			}
			else
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA1)))->SetCheck(false);
			}

			strTmp = m_ctlCoverLst.GetItemText(nIndex, 8);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA2)))->SetCheck(true);
			}
			else
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA2)))->SetCheck(false);
			}

			strTmp = m_ctlCoverLst.GetItemText(nIndex, 9);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA3)))->SetCheck(true);
			}
			else
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDEXTRA3)))->SetCheck(false);
			}

			strTmp = m_ctlCoverLst.GetItemText(nIndex, 10);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDSNAPSHOT)))->SetCheck(true);
			}
			else
			{
				((CButton*)(GetDlgItem(IDC_CHECK_BLENDSNAPSHOT)))->SetCheck(false);
			}

			//Front Color
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 11);
			SetDlgItemText(IDC_EDIT_FORE_RED, strTmp);
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 12);
			SetDlgItemText(IDC_EDIT_FORE_GREEN, strTmp);
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 13);
			SetDlgItemText(IDC_EDIT_FORE_BLUE, strTmp);
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 14);
			SetDlgItemText(IDC_EDIT_FORE_ALPHA, strTmp);


			//Back Color
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 15);
			SetDlgItemText(IDC_EDIT_BACK_RED, strTmp);
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 16);
			SetDlgItemText(IDC_EDIT_BACK_GREEN, strTmp);
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 17);
			SetDlgItemText(IDC_EDIT_BACK_BLUE, strTmp);
			strTmp = m_ctlCoverLst.GetItemText(nIndex, 18);
			SetDlgItemText(IDC_EDIT_BACK_ALPHA, strTmp);
		}
	}
	
	*pResult = 0;
}

void CConfigCover::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}
/*
void CConfigCover::OnEditchangeComboVideowidget() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlVideoWidget.GetCurSel();
	if(CB_ERR != nIndex)
	{
		SaveChannelInfo(m_nCurChannel, m_nVideoWidget);




	

	}
}
*/
void CConfigCover::OnSelchangeComboVideowidget() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlVideoWidget.GetCurSel();
	if(CB_ERR != nIndex && m_pstVideoWidget)
	{
		SaveChannelInfo(m_nCurChannel, m_nVideoWidget);
		if(0 == nIndex) // ChannelTitle Info
		{			
			GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
			ShowVideoWidgetChannelTitle(&m_pstVideoWidget[m_nCurChannel].stuChannelTitle);

		}
		else if(1 == nIndex) //TimeTitle Info
		{
			GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
			ShowVideoWidgetTimeTitle(&m_pstVideoWidget[m_nCurChannel].stuTimeTitle);
		}
		else if(2 == nIndex) //Covers Info
		{
			GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(TRUE);
			ShowVideoWidgetCover(m_pstVideoWidget[m_nCurChannel].stuCovers, m_pstVideoWidget[m_nCurChannel].nConverNum);
		}

		m_nVideoWidget = nIndex;
	}
}

void CConfigCover::ShowVideoWidgetChannelTitle(AV_CFG_VideoWidgetChannelTitle *pChannelTitleInfo)
{
	m_ctlCoverLst.DeleteAllItems();
	ShowVideoWidget(pChannelTitleInfo);
}
void CConfigCover::ShowVideoWidgetTimeTitle(AV_CFG_VideoWidgetTimeTitle *pTimeTitleInfo)
{
	m_ctlCoverLst.DeleteAllItems();
	ShowVideoWidget(pTimeTitleInfo);
}
void CConfigCover::ShowVideoWidgetCover(AV_CFG_VideoWidgetCover *pVideoWidgetCover, int nNum)
{
	m_ctlCoverLst.DeleteAllItems();
	for (int i = 0; i < nNum; ++i)
	{
		ShowVideoWidget(pVideoWidgetCover, i);
	}
}

void CConfigCover::SaveVideoWidgetChannelTitle(AV_CFG_VideoWidgetChannelTitle *pChannelTitleInfo)
{
	SaveVideoWidget(pChannelTitleInfo);
}
void CConfigCover::SaveVideoWidgetTimeTitle(AV_CFG_VideoWidgetTimeTitle *pTimeTitleInfo)
{
	SaveVideoWidget(pTimeTitleInfo);
}
void CConfigCover::SaveVideoWidgetCover(AV_CFG_VideoWidgetCover *pVideoWidgetCover, int *nNum)
{
	SaveVideoWidget(pVideoWidgetCover, nNum);
}

BOOL CConfigCover::JudgeColor(int nColor)
{
	if(nColor < 0 || nColor > 255)
	{
		MessageBox(ConvertString("Color range£º0~255!"), ConvertString("Prompt"));
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
BOOL CConfigCover::JudgeCoordinate(int nCoordinate)
{
	if (nCoordinate<0 || nCoordinate>8192)
	{
		MessageBox(ConvertString("Margin range£º0~8192!"), ConvertString("Prompt"));
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
