// DevByTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "DevByTimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDevByTimeDlg dialog


CDevByTimeDlg::CDevByTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDevByTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDevByTimeDlg)
	m_timeTo = 0;
	m_timeFrom = 0;
	m_dateTo = COleDateTime::GetCurrentTime();
	m_dateFrom = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	memset(&m_stuPlaybackParam, 0, sizeof(DEC_PLAYBACK_TIME_PARAM));
	m_lLoginHandle = 0;
	m_nChannelNum = 0;
}


void CDevByTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevByTimeDlg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctlChannel);
	DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_dateTo);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_dateFrom);
	DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_timeTo);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_timeFrom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDevByTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CDevByTimeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDevByTimeDlg message handlers

void CDevByTimeDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	int nIndex = m_ctlChannel.GetCurSel();
	int nChannelId = (int)m_ctlChannel.GetItemData(nIndex);
	
	NET_TIME netTimeFrom = ConvertToDateTime(m_dateFrom,m_timeFrom);
	NET_TIME netTimeTo = ConvertToDateTime(m_dateTo,m_timeTo);

	m_stuPlaybackParam.nChannelID = nChannelId;
	m_stuPlaybackParam.startTime = netTimeFrom;
	m_stuPlaybackParam.endTime = netTimeTo;
	
	CDialog::OnOK();
}

BOOL CDevByTimeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	CString strText = "";
	int nIndex = 0;
	for (int i = 0; i < m_nChannelNum; i++)
	{
		strText.Format("%d", i);
		nIndex = m_ctlChannel.AddString(strText);
		m_ctlChannel.SetItemData(nIndex, i);
	}
	m_ctlChannel.SetCurSel(0);

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

NET_TIME CDevByTimeDlg::ConvertTime(CTime &date, CTime &time)
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
NET_TIME CDevByTimeDlg::ConvertToDateTime(const COleDateTime &date, const CTime &time)
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

