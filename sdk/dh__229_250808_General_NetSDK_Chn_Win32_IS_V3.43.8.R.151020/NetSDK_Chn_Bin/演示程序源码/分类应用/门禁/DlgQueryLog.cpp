// DlgQueryLog.cpp : implementation file
//

#include "stdafx.h"
#include "AccessControl.h"
#include "DlgQueryLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQueryLog dialog


CDlgQueryLog::CDlgQueryLog(CWnd* pParent /* = NULL */, LLONG lLoginId /* = 0 */, NET_DEVICE_TYPE emDevType /* = NET_PRODUCT_NONE */, int nMaxPageSize /* = 10 */)
	: CDialog(CDlgQueryLog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQueryLog)
	m_nPageLines	= 10;
	m_timeEnd		= 0;
	m_timeBegin		= 0;
	m_dataEnd		= COleDateTime::GetCurrentTime();
	m_dataBegin		= COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	m_lLoginId		= lLoginId;
    m_lLogID        = 0;
	m_nStartNo		= 0;
	m_nMaxPageSize	= nMaxPageSize;
	m_emDevType		= emDevType;
}

void CDlgQueryLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQueryLog)
	DDX_Control(pDX, IDC_QUERYLOG_LIST_LOGLIST, m_logList);
	DDX_Control(pDX, IDC_QUERYLOG_COMBO_TYPE, m_cmbQueryType);
	DDX_Text(pDX, IDC_QUERYLOG_EDIT_PAGELINES, m_nPageLines);
	DDV_MinMaxInt(pDX, m_nPageLines, 1, 1024);
	DDX_DateTimeCtrl(pDX, IDC_QUERYLOG_DATETIMEPICKER_ENDTIME, m_timeEnd);
	DDX_DateTimeCtrl(pDX, IDC_QUERYLOG_DATETIMEPICKER_STARTTIME, m_timeBegin);
	DDX_DateTimeCtrl(pDX, IDC_QUERYLOG_DATETIMEPICKER_ENDDAY, m_dataEnd);
	DDX_DateTimeCtrl(pDX, IDC_QUERYLOG_DATETIMEPICKER_STARTDAY, m_dataBegin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQueryLog, CDialog)
	//{{AFX_MSG_MAP(CDlgQueryLog)
	ON_BN_CLICKED(IDC_QUERYLOG_BTN_QUERYSTOP, OnBtnQueryStop)
	ON_BN_CLICKED(IDC_QUERYLOG_BTN_QUERYSTART, OnBtnQueryStart)
	ON_BN_CLICKED(IDC_QUERYLOG_BTN_QUERYNEXT, OnBtnQueryNext)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_QUERYLOG_BTN_TOTALCOUNT, OnQuerylogBtnTotalCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// private method

void CDlgQueryLog::InitDlg()
{
	m_logList.SetExtendedStyle(m_logList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_logList.InsertColumn(0, ConvertString("seq", DLG_QUERYLOG), LVCFMT_LEFT,30,-1);
	m_logList.InsertColumn(1, ConvertString("type", DLG_QUERYLOG), LVCFMT_LEFT,150,-1);
	m_logList.InsertColumn(2, ConvertString("date", DLG_QUERYLOG),LVCFMT_LEFT,180,-1);
	m_logList.InsertColumn(3, ConvertString("content", DLG_QUERYLOG),LVCFMT_LEFT,420,-1);

    GetDlgItem(IDC_QUERYLOG_BTN_QUERYNEXT)->EnableWindow(FALSE);
    GetDlgItem(IDC_QUERYLOG_BTN_QUERYSTART)->EnableWindow(TRUE);
    GetDlgItem(IDC_QUERYLOG_BTN_QUERYSTOP)->EnableWindow(FALSE);
}

void CDlgQueryLog::InsertListViewItem(int nStartNo, const CString& strLogType, const CString& strLogTime, const CString& strLogContext)
{
	int nIndex = m_logList.GetItemCount();
	
	CString strIndex;
	strIndex.Format("%d", nStartNo + 1);
	m_logList.InsertItem(nIndex, "");
	
	m_logList.SetItemText(nIndex, 0, strIndex);
	m_logList.SetItemText(nIndex, 1, strLogType);
	m_logList.SetItemText(nIndex, 2, strLogTime);
	m_logList.SetItemText(nIndex, 3, strLogContext);
}

BOOL CDlgQueryLog::QueryStart()
{
    NET_IN_START_QUERYLOG stuIn = {sizeof(stuIn)};
    NET_OUT_START_QUERYLOG stuOut = {sizeof(stuOut)};
    LLONG lLogID = CLIENT_StartQueryLog(m_lLoginId, &stuIn, &stuOut, SDK_API_WAITTIME);
    if (lLogID != NULL)
    {
        m_logList.DeleteAllItems();
        m_nStartNo = 0;
        m_lLogID = lLogID;
        return TRUE;
    }
    CString csInfo;
    csInfo.Format("%s0x%08x", ConvertString("Start query failed:", DLG_QUERYLOG), CLIENT_GetLastError());
    MessageBox(csInfo, ConvertString("Prompt"));
    return FALSE;
}

int CDlgQueryLog::QueryNext()
{
    NET_IN_QUERYNEXTLOG stuIn = {sizeof(stuIn)};
    stuIn.nGetCount = m_nMaxPageSize;

    NET_OUT_QUERYNEXTLOG stuOut = {sizeof(stuOut)};
    stuOut.nMaxCount = m_nMaxPageSize;
    stuOut.pstuLogInfo = new NET_LOG_INFO[m_nMaxPageSize];
    if (NULL == stuOut.pstuLogInfo)
    {
        return -1;
    }
    memset(stuOut.pstuLogInfo, 0, sizeof(NET_LOG_INFO) * m_nMaxPageSize);
    int i = 0;
    for (i = 0; i < m_nMaxPageSize; i++)
    {
        stuOut.pstuLogInfo[i].dwSize = sizeof(NET_LOG_INFO);
        stuOut.pstuLogInfo[i].stuLogMsg.dwSize = sizeof(NET_LOG_MESSAGE);
    }
    if (CLIENT_QueryNextLog(m_lLogID, &stuIn, &stuOut, SDK_API_WAITTIME))
    {
        if (stuOut.nRetCount > 0)
        {
            m_logList.DeleteAllItems();
        }

        for (i = 0; i < __min(stuOut.nMaxCount, stuOut.nRetCount); i++)
        {
            NET_TIME& stuTime = stuOut.pstuLogInfo[i].stuTime;

            char szTime[64] = {0};
            _snprintf(szTime, sizeof(szTime) - 1, "%04d-%02d-%02d %02d:%02d:%02d",
                stuTime.dwYear, stuTime.dwMonth, stuTime.dwDay,
                stuTime.dwHour, stuTime.dwMinute, stuTime.dwSecond);

            InsertListViewItem(m_nStartNo++, 
                stuOut.pstuLogInfo[i].szLogType,
                szTime,
                stuOut.pstuLogInfo[i].stuLogMsg.szLogMessage);
        }
        delete []stuOut.pstuLogInfo;
        stuOut.pstuLogInfo = NULL;
        return stuOut.nRetCount;
    }
    delete []stuOut.pstuLogInfo;
    stuOut.pstuLogInfo = NULL;
    return 0;
}

BOOL CDlgQueryLog::QueryStop()
{
    return CLIENT_StopQueryLog(m_lLogID);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgQueryLog message handlers

BOOL CDlgQueryLog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this, DLG_QUERYLOG);

	InitDlg();
	OnQuerylogBtnTotalCount();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////
//
// start query
//
//////////////////////////////////////////////////////////////////////////
void CDlgQueryLog::OnBtnQueryStart() 
{
	// TODO: Add your control notification handler code here
    if (QueryStart())
    {
        GetDlgItem(IDC_QUERYLOG_BTN_QUERYSTART)->EnableWindow(FALSE);
        GetDlgItem(IDC_QUERYLOG_BTN_QUERYNEXT)->EnableWindow();
        GetDlgItem(IDC_QUERYLOG_BTN_QUERYSTOP)->EnableWindow();
    }
}
//////////////////////////////////////////////////////////////////////////
//
// query next
//
//////////////////////////////////////////////////////////////////////////
void CDlgQueryLog::OnBtnQueryNext() 
{
	// TODO: Add your control notification handler code here
    int nRet = QueryNext();
    if (nRet < m_nMaxPageSize)
    {
        // we got the last page
        GetDlgItem(IDC_QUERYLOG_BTN_QUERYNEXT)->EnableWindow(FALSE);
    }
}
//////////////////////////////////////////////////////////////////////////
//
// stop query
//
//////////////////////////////////////////////////////////////////////////
void CDlgQueryLog::OnBtnQueryStop() 
{
    // TODO: Add your control notification handler code here
    if (QueryStop())
    {
        GetDlgItem(IDC_QUERYLOG_BTN_QUERYSTART)->EnableWindow();
        GetDlgItem(IDC_QUERYLOG_BTN_QUERYNEXT)->EnableWindow(FALSE);
        GetDlgItem(IDC_QUERYLOG_BTN_QUERYSTOP)->EnableWindow(FALSE);
    }
}

void CDlgQueryLog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_lLogID != 0)
	{
        CLIENT_StopQueryLog(m_lLogID);
	}
}

void CDlgQueryLog::OnQuerylogBtnTotalCount() 
{
	// TODO: Add your control notification handler code here
	NET_IN_GETCOUNT_LOG_PARAM stuIn = {sizeof(stuIn)};
	NET_OUT_GETCOUNT_LOG_PARAM stuOut = {sizeof(stuOut)};
	if (CLIENT_QueryDevLogCount(m_lLoginId, &stuIn, &stuOut, SDK_API_WAITTIME))
	{
		SetDlgItemInt(IDC_QUERYLOG_EDT_TOTALCOUNT, stuOut.nLogCount);
	}
	else
	{
		CString csOut;
		csOut.Format("%s:0x%08x", ConvertString("Query log total count failed", DLG_QUERYLOG), CLIENT_GetLastError());
		MessageBox(csOut, ConvertString("Prompt"));
	}
}
