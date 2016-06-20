// SearchTVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NVDSDKDemo.h"
#include "SearchTVDlg.h"
#include "dhnetsdk.h"
#include "NVDSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Get parent dialog hand
#define GET_PARENT_CONTAINER			((CWndContainer *)(this->GetParent()))

/////////////////////////////////////////////////////////////////////////////
// CSearchTVDlg dialog


CSearchTVDlg::CSearchTVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchTVDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchTVDlg)
	//}}AFX_DATA_INIT
	m_hCurLoginID = 0;
	m_nDecChannel = 0;
	m_nCurTvID = 0;
	memset(&m_stuDevTvInfo, 0, sizeof(m_stuDevTvInfo));
}


void CSearchTVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchTVDlg)
	DDX_Control(pDX, IDC_COMBO_TVID, m_ctlDecTV);
	DDX_Control(pDX, IDC_LIST_TVID, m_ctlSearchTVList);
//	DDX_Text(pDX, IDC_EDIT_DECODEPOLICY, m_nDecodePolicy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchTVDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchTVDlg)
	ON_BN_CLICKED(IDC_BTN_SEARCH_OK, OnBtnSearchOk)
	ON_BN_CLICKED(IDC_BUT_CHANGEENABLE, OnButChangeenable)
	ON_BN_CLICKED(IDC_BTN_WORK, OnBtnWork)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchTVDlg message handlers

BOOL CSearchTVDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	m_ctlSearchTVList.SetExtendedStyle(m_ctlSearchTVList.GetExtendedStyle() | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlSearchTVList.InsertColumn(0, ConvertString("screen id"), LVCFMT_LEFT, 50, -1);
	m_ctlSearchTVList.InsertColumn(1, ConvertString("connect mode"), LVCFMT_LEFT, 80, 0);
	m_ctlSearchTVList.InsertColumn(2, ConvertString("service type"), LVCFMT_LEFT, 80, 1);
	m_ctlSearchTVList.InsertColumn(3, "IP", LVCFMT_LEFT, 90, 2);
	m_ctlSearchTVList.InsertColumn(4, "PORT", LVCFMT_LEFT, 60, 3);
	m_ctlSearchTVList.InsertColumn(5, ConvertString("Channel"), LVCFMT_LEFT, 50, 4);
	m_ctlSearchTVList.InsertColumn(6, ConvertString("UserName"), LVCFMT_LEFT, 80, 5);
	m_ctlSearchTVList.InsertColumn(7, ConvertString("Password"), LVCFMT_LEFT, 80, 6);
	m_ctlSearchTVList.InsertColumn(8, ConvertString("video enable"), LVCFMT_LEFT, 50, 7);
	m_ctlSearchTVList.InsertColumn(9, ConvertString("listen port"), LVCFMT_LEFT, 50, 8);
	m_ctlSearchTVList.InsertColumn(10, ConvertString("Stream Type"), LVCFMT_LEFT, 50, 8);
	m_ctlSearchTVList.InsertColumn(11, ConvertString("Snap Mode"), LVCFMT_LEFT, 50, 8);
	
	CString strText = "";
	int nIndex = 0;
	for (int i = 0; i < m_nDecChannel; i++)
	{
		strText.Format("TV %d", i);
		nIndex = m_ctlDecTV.AddString(strText);
		m_ctlDecTV.SetItemData(nIndex, i);
	}
	m_ctlDecTV.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchTVDlg::OnBtnSearchOk() 
{
    // TODO: Add your control notification handler code here
    int nIndex = m_ctlDecTV.GetCurSel();
    if (nIndex != -1)
    {
        int nTVId = m_ctlDecTV.GetItemData(nIndex);
        if (nTVId >= 0 && nTVId < MAX_DEC_TV_NUM)
        {
            m_nCurTvID = nTVId;
            BOOL bRet = CLIENT_QueryDecoderTVInfo(m_hCurLoginID, nTVId, &m_stuDevTvInfo[nTVId], 2000);
            if (bRet)
            {
                m_ctlSearchTVList.DeleteAllItems();
                
                for (int i = 0; i < m_stuDevTvInfo[nTVId].nSplitType; i++)
                {
                    CString strIp = "";
                    CString strUser = "";
                    CString strPwd = "";
                    CString strEnable = "";
                    CString strWorkMode = "";
                    CString strConnType = "";
                    CString strStreamType = "";
                    CString strSnapMode = "";
                    
                    strIp.Format("%s", m_stuDevTvInfo[nTVId].stuDevInfo[i].szDevIp);
                    strUser.Format("%s", m_stuDevTvInfo[nTVId].stuDevInfo[i].szDevUser);
                    strPwd.Format("%s", m_stuDevTvInfo[nTVId].stuDevInfo[i].szDevPwd);
                    
                    if (m_stuDevTvInfo[nTVId].stuDevInfo[i].bDevChnEnable)
                    {
                        strEnable = "True";
                    }
                    else
                    {
                        strEnable = "False";
                    }
                    
                    if (m_stuDevTvInfo[nTVId].stuDevInfo[i].nStreamType == 0) 
                    {
                        strStreamType = ConvertString("Main");
                    }
                    else if(m_stuDevTvInfo[nTVId].stuDevInfo[i].nStreamType == 2) 
                    {
                        strStreamType = ConvertString("Snap");
                    }
                    else
                    {
                        strStreamType = ConvertString("Sub");
                    }
                    
                    if (m_stuDevTvInfo[nTVId].stuDevInfo[i].byWorkMode == 0)
                    {
                        strWorkMode = ConvertString("Direct connect");
                    }
                    else if (m_stuDevTvInfo[nTVId].stuDevInfo[i].byWorkMode == 1)
                    {
                        strWorkMode = ConvertString("Transmit");
                    }
                    
                    if (m_stuDevTvInfo[nTVId].stuDevInfo[i].byConnType == 0)
                    {
                        strConnType = "TCP";
                    }
                    else if (m_stuDevTvInfo[nTVId].stuDevInfo[i].byConnType == 1)
                    {
                        strConnType = "UDP";
                    }
                    else if (m_stuDevTvInfo[nTVId].stuDevInfo[i].byConnType == 2)
                    {
                        strConnType = ConvertString("Multicast");
                    }
                    
                    if (m_stuDevTvInfo[nTVId].stuDevInfo[i].bySnapMode == 0)
                    {
                        strSnapMode = ConvertString("One Frame");
                    }
                    else
                    {
                        strSnapMode = ConvertString("On Time");
                    }
                    
                    InsertListView(m_stuDevTvInfo[nTVId].stuDevInfo[i].nDevChannel, i, strIp, m_stuDevTvInfo[nTVId].stuDevInfo[i].wDevPort, strUser, strPwd, strEnable, strWorkMode, strConnType,
                        m_stuDevTvInfo[nTVId].stuDevInfo[i].wListenPort, strStreamType, strSnapMode);		
                }
            }
            else
            {
                MessageBox(ConvertString("Failed to query!"), ConvertString("Prompt"));
            }
        }
    }	
}

void CSearchTVDlg::SetDlgParam(LLONG lLoginID, int nDevChannel)
{
	m_hCurLoginID = lLoginID;
	m_nDecChannel = nDevChannel;
}

void CSearchTVDlg::InsertListView(int nChannelId, int nWndId, CString strIp,
								  int nPort, CString strUser, CString strPwd,
								  CString strEnable, CString strWorkMode, 
								  CString strConnType, int nListenPort, 
								  CString strStreamType, CString strSnapMode)
{
	int nIndex = m_ctlSearchTVList.GetItemCount();

	CString strWndID = "";
	strWndID.Format("%d", nWndId);
	m_ctlSearchTVList.InsertItem(LVIF_TEXT|LVIF_STATE, nIndex, strWndID, 0, LVIS_SELECTED, 0, NULL);

	m_ctlSearchTVList.SetItemText(nIndex, 1, strWorkMode);
	m_ctlSearchTVList.SetItemText(nIndex, 2, strConnType);
	m_ctlSearchTVList.SetItemText(nIndex, 3, strIp);

	CString strPort = "";
	strPort.Format("%d", nPort);
	m_ctlSearchTVList.SetItemText(nIndex, 4, strPort);

	CString strChannel = "";
	strChannel.Format("%d", nChannelId);
	m_ctlSearchTVList.SetItemText(nIndex, 5, strChannel);
	
	m_ctlSearchTVList.SetItemText(nIndex, 6, strUser);
	m_ctlSearchTVList.SetItemText(nIndex, 7, strPwd);
	m_ctlSearchTVList.SetItemText(nIndex, 8, strEnable);

	CString strListenPort = "";
	strListenPort.Format("%d", nListenPort);
	m_ctlSearchTVList.SetItemText(nIndex, 9, strListenPort);

	m_ctlSearchTVList.SetItemText(nIndex, 10, strStreamType);

	m_ctlSearchTVList.SetItemText(nIndex, 11, strSnapMode);
}

void CSearchTVDlg::OnButChangeenable() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	if (pParentDlg == NULL)
	{
		return;
	}

	if (m_ctlSearchTVList.GetItemCount() <= 0)
	{
		return;
	}
	
	// 得到当前list选项
	int nItem = m_ctlSearchTVList.GetSelectionMark();
	if( nItem < 0 )	
	{
		MessageBox(ConvertString("Please select first!"), ConvertString("Prompt"));
		return;
	}
	
	// 发送切换命令到解码器
	DEV_ENCODER_INFO stuEncoderInfo = {0};
	stuEncoderInfo = m_stuDevTvInfo[m_nCurTvID].stuDevInfo[nItem];
	stuEncoderInfo.bDevChnEnable = !stuEncoderInfo.bDevChnEnable;

	if (stuEncoderInfo.byWorkMode != 0)
	{
		return;
	}

	LLONG lHandle = CLIENT_SwitchDecTVEncoder(m_hCurLoginID, stuEncoderInfo.byEncoderID, &stuEncoderInfo);
	if (lHandle == 0)
	{
		MessageBox(ConvertString("Switch failed!"), ConvertString("Prompt"));
	}
	else
	{
		Sleep(1000);
		OnBtnSearchOk(); 
	}
}

void CSearchTVDlg::OnBtnWork() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	if (pParentDlg == NULL)
	{
		return;
	}

	if (m_ctlSearchTVList.GetItemCount() <= 0)
	{
		return;
	}
	
	int nItem = m_ctlSearchTVList.GetSelectionMark();
	if( nItem < 0 )	
	{
		MessageBox(ConvertString("Please select first!"), ConvertString("Prompt"));
		return;
	}
	
	DEV_ENCODER_INFO stuEncoderInfo = {0};
	stuEncoderInfo = m_stuDevTvInfo[m_nCurTvID].stuDevInfo[nItem];
	if (stuEncoderInfo.byWorkMode == 0)
	{
		stuEncoderInfo.byWorkMode = 1;
	}
	else
	{
		stuEncoderInfo.byWorkMode = 0;
	}

	LLONG lHandle = CLIENT_SwitchDecTVEncoder(m_hCurLoginID, stuEncoderInfo.byEncoderID, &stuEncoderInfo);
	if (lHandle == 0)
	{
		MessageBox(ConvertString("Switch failed!"), ConvertString("Prompt"));
	}
	else
	{
		Sleep(1000);
		OnBtnSearchOk(); 
	}
}

void CSearchTVDlg::OnButtonSnap() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	if (pParentDlg == NULL)
	{
		return;
	}

	if (m_ctlSearchTVList.GetItemCount() <= 0)
	{
		return;
	}
	
	int nItem = m_ctlSearchTVList.GetSelectionMark();
	if( nItem < 0 )	
	{
		MessageBox(ConvertString("Please select first!"), ConvertString("Prompt"));
		return;
	}
	
	DEV_ENCODER_INFO stuEncoderInfo = {0};
	stuEncoderInfo = m_stuDevTvInfo[m_nCurTvID].stuDevInfo[nItem];
	if (stuEncoderInfo.nStreamType != 2)
	{
		MessageBox(ConvertString("Please select snap mode first!"), ConvertString("Prompt"));
		return;
	}
	
	if (stuEncoderInfo.bySnapMode == 0)
	{
		stuEncoderInfo.bySnapMode = 1;
	}
	else
	{
		stuEncoderInfo.bySnapMode = 0;
	}

	LLONG lHandle = CLIENT_SwitchDecTVEncoder(m_hCurLoginID, stuEncoderInfo.byEncoderID, &stuEncoderInfo);
	if (lHandle == 0)
	{
		MessageBox(ConvertString("Switch failed!"), ConvertString("Prompt"));
	}
	else
	{
		Sleep(1000);
		OnBtnSearchOk(); 
	}
}
