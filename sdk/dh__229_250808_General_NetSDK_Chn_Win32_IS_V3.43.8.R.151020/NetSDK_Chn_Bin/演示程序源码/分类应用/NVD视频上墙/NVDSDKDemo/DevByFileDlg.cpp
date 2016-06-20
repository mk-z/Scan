// DevByFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "DevByFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDevByFileDlg dialog


CDevByFileDlg::CDevByFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDevByFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDevByFileDlg)
	m_timeFrom = 0;
	m_timeTo = 0;
	m_dateTo = COleDateTime::GetCurrentTime();
	m_dateFrom = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	memset(&m_stuPlaybackParam, 0, sizeof(DEC_PLAYBACK_FILE_PARAM));
	m_lLoginHandle = 0;
	m_nChannelNum = 0;
}


void CDevByFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevByFileDlg)
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_ctlType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctlChannel);
	DDX_Control(pDX, IDC_LIST_RECORD_INFO, m_ctlRecordInfo);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_timeFrom);
	DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_timeTo);
	DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_dateTo);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_dateFrom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDevByFileDlg, CDialog)
	//{{AFX_MSG_MAP(CDevByFileDlg)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RECORD_INFO, OnDblclkListRecordInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL CDevByFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	m_ctlRecordInfo.SetExtendedStyle(m_ctlRecordInfo.GetExtendedStyle() | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlRecordInfo.InsertColumn(0, ConvertString("ID"), LVCFMT_LEFT, 50, -1);
	m_ctlRecordInfo.InsertColumn(1, ConvertString("size"), LVCFMT_LEFT, 60, 0);
	m_ctlRecordInfo.InsertColumn(2, ConvertString("Start time"), LVCFMT_LEFT, 150, 1);
	m_ctlRecordInfo.InsertColumn(3, ConvertString("End time"), LVCFMT_LEFT, 150, 2);

	CString strText = "";
	int nIndex = 0;
	for (int i = 0; i < m_nChannelNum; i++)
	{
		strText.Format("%d", i);
		nIndex = m_ctlChannel.AddString(strText);
		m_ctlChannel.SetItemData(nIndex, i);
	}
	m_ctlChannel.SetCurSel(0);

	nIndex = m_ctlType.AddString(ConvertString("All record"));
	m_ctlType.SetItemData(nIndex, 0);
	nIndex = m_ctlType.AddString(ConvertString("Alarm record"));
	m_ctlType.SetItemData(nIndex, 3);
	m_ctlType.SetCurSel(0);

	CTimeSpan timeSpan(1,0,0,0);
	CTime curTime = CTime::GetCurrentTime();
	CTime dateFrom = curTime - timeSpan;
	m_dateFrom.SetDateTime(dateFrom.GetYear(), dateFrom.GetMonth(), dateFrom.GetDay(), 
		dateFrom.GetHour(), dateFrom.GetMinute(), dateFrom.GetSecond());
	m_timeFrom = curTime;
	m_dateTo.SetDateTime(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), 
		curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
	m_timeTo = curTime;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// CDevByFileDlg message handlers

void CDevByFileDlg::OnButtonQuery() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = UpdateData(TRUE);
	if(bValid && (0 != m_lLoginHandle))
	{
		int nIndex = m_ctlChannel.GetCurSel();
		int nChannelId = (int)m_ctlChannel.GetItemData(nIndex);

		NET_TIME netTimeFrom = ConvertToDateTime(m_dateFrom,m_timeFrom);
		NET_TIME netTimeTo = ConvertToDateTime(m_dateTo,m_timeTo);

		nIndex = m_ctlType.GetCurSel();	
		int nRecordFileType = m_ctlType.GetItemData(nIndex);

		int nMaxLen = 2000 * sizeof(NET_RECORDFILE_INFO);
		int nFileCount = 0;
		BOOL bSuccess = CLIENT_QueryRecordFile(m_lLoginHandle, nChannelId, nRecordFileType,
			&netTimeFrom, &netTimeTo, NULL, m_netFileInfo, nMaxLen, &nFileCount, 5000, FALSE);
		if(bSuccess)
		{
			if(0 == nFileCount)
			{
				MessageBox(ConvertString("No record!"), ConvertString("Prompt"));
			}
			else
			{
				AddRecordInfoToListView(m_netFileInfo,nFileCount);
			}
		}
		else
		{
			MessageBox(ConvertString("Failed to query!"), ConvertString("Prompt"));
		}
	}
}

NET_TIME CDevByFileDlg::ConvertTime(CTime &date, CTime &time)
{
	NET_TIME netTime = {0};
	netTime.dwYear = date.GetYear();
	netTime.dwMonth = date.GetMonth();
	netTime.dwDay = date.GetDay();
	netTime.dwHour = time.GetHour();
	netTime.dwMinute = time.GetMinute();
	netTime.dwSecond =time.GetSecond();
	return netTime;
}

void CDevByFileDlg::AddRecordInfoToListView(LPNET_RECORDFILE_INFO pRecordFiles, int nFileCount)
{
	m_ctlRecordInfo.DeleteAllItems();

	for (int i = 0; i < nFileCount; i++)
	{
		NET_RECORDFILE_INFO netFileInfo = pRecordFiles[i];
		CString strNum;
		strNum.Format("%d",i);
		CString strFileLength;
		strFileLength.Format("%d",netFileInfo.size);
		CString strStartTime;
		strStartTime.Format(ConvertString("%d年 %d月 %d日  %d:%d:%d"),netFileInfo.starttime.dwYear,
			netFileInfo.starttime.dwMonth,netFileInfo.starttime.dwDay,netFileInfo.starttime.dwHour,
			netFileInfo.starttime.dwMinute,netFileInfo.starttime.dwSecond);
		CString strEndTime;
		strEndTime.Format(ConvertString("%d年 %d月 %d日  %d:%d:%d"),netFileInfo.endtime.dwYear,
			netFileInfo.endtime.dwMonth,netFileInfo.endtime.dwDay,netFileInfo.endtime.dwHour,
			netFileInfo.endtime.dwMinute,netFileInfo.endtime.dwSecond);

		int nIndex = m_ctlRecordInfo.GetItemCount();
		m_ctlRecordInfo.InsertItem(LVIF_TEXT|LVIF_STATE,nIndex,strNum,0,LVIS_SELECTED,0,0);
		
		m_ctlRecordInfo.SetItemText(nIndex,1,strFileLength);
		m_ctlRecordInfo.SetItemText(nIndex,2,strStartTime);
		m_ctlRecordInfo.SetItemText(nIndex,3,strEndTime);
	}
}

void CDevByFileDlg::OnDblclkListRecordInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(0 != m_ctlRecordInfo.GetItemCount())
	{
		if(0 < m_ctlRecordInfo.GetSelectedCount())
		{
			int nIndex = m_ctlRecordInfo.GetSelectionMark();
			if(-1 != nIndex)
			{
				m_stuPlaybackParam.stuRecordInfo = m_netFileInfo[nIndex];
				this->OnOK();
			}
		}
	}

	*pResult = 0;
}

NET_TIME CDevByFileDlg::ConvertToDateTime(const COleDateTime &date, const CTime &time)
{
	NET_TIME netTime = {0};
	int year = date.GetYear();
	if (year < 2000)
	{
		netTime.dwYear = 2000;
		netTime.dwMonth = 1;
		netTime.dwDay = 1;
		netTime.dwHour = 0;
		netTime.dwMinute = 0;
		netTime.dwSecond = 0;
	}
	else
	{
		netTime.dwYear = date.GetYear();
		netTime.dwMonth = date.GetMonth();
		netTime.dwDay = date.GetDay();
		netTime.dwHour = time.GetHour();
		netTime.dwMinute = time.GetMinute();
		netTime.dwSecond =time.GetSecond();
	}
	
	return netTime;
}

