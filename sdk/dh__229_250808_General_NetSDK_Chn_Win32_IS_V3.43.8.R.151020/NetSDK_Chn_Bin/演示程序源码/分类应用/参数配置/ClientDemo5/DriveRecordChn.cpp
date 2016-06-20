// DriveRecordChn.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "DriveRecordChn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DriveRecordChn dialog


DriveRecordChn::DriveRecordChn(CWnd* pParent /*=NULL*/)
	: CDialog(DriveRecordChn::IDD, pParent)
{
	//{{AFX_DATA_INIT(DriveRecordChn)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nChannel = 32 * MAX_CHANNEL_COUNT;
	memset(m_RecordMark, 0, MAX_CHANNEL_COUNT * sizeof(DWORD));
}


void DriveRecordChn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DriveRecordChn)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DriveRecordChn, CDialog)
	//{{AFX_MSG_MAP(DriveRecordChn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DriveRecordChn message handlers
BOOL DriveRecordChn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	InitDlgInfo();
	return TRUE;
}

void DriveRecordChn::InitDlgInfo()
{
	if ((32 * MAX_CHANNEL_COUNT) < m_nChannel)
	{
		return;
	}
	UINT uID[MAX_CHANNEL_COUNT] = {
			IDC_STATIC_RECORD1,
			IDC_STATIC_RECORD2,
			IDC_STATIC_RECORD3,
			IDC_STATIC_RECORD4,
			IDC_STATIC_RECORD5,
			IDC_STATIC_RECORD6,
			IDC_STATIC_RECORD7,
			IDC_STATIC_RECORD8,
			IDC_STATIC_RECORD9,
			IDC_STATIC_RECORD10,
			IDC_STATIC_RECORD11,
			IDC_STATIC_RECORD12,
			IDC_STATIC_RECORD13,
			IDC_STATIC_RECORD14,
			IDC_STATIC_RECORD15,
			IDC_STATIC_RECORD16
	};
	UINT uLabelID[MAX_CHANNEL_COUNT] = {
			IDC_STATIC_LABEL_RECORD1,
			IDC_STATIC_LABEL_RECORD2,
			IDC_STATIC_LABEL_RECORD3,
			IDC_STATIC_LABEL_RECORD4,
			IDC_STATIC_LABEL_RECORD5,
			IDC_STATIC_LABEL_RECORD6,
			IDC_STATIC_LABEL_RECORD7,
			IDC_STATIC_LABEL_RECORD8,
			IDC_STATIC_LABEL_RECORD9,
			IDC_STATIC_LABEL_RECORD10,
			IDC_STATIC_LABEL_RECORD11,
			IDC_STATIC_LABEL_RECORD12,
			IDC_STATIC_LABEL_RECORD13,
			IDC_STATIC_LABEL_RECORD14,
			IDC_STATIC_LABEL_RECORD15,
			IDC_STATIC_LABEL_RECORD16
	};
	// create 8*32 channel checkbox
	int i = 0;
	DWORD dwInit = 0;
	for (; i < MAX_CHANNEL_COUNT; i++)
	{
		m_chnRecord[i].Create(IDD_DIALOG_CHN,this);
		m_chnRecord[i].Attach(uID[i],this);
		m_chnRecord[i].SetChnState(dwInit,0);
		GetDlgItem(uLabelID[i])->ShowWindow(SW_HIDE);
	}
	// init channel state
	int iChnDlgCount = m_nChannel/32;
	int iChnCheckNum = m_nChannel%32;
	for (i = 0; i < iChnDlgCount; i++)
	{
		m_chnRecord[i].SetChnState(m_RecordMark[i],32);
		GetDlgItem(uLabelID[i])->ShowWindow(SW_SHOW);
	}
	if (0 != iChnCheckNum)
	{
		m_chnRecord[iChnDlgCount].SetChnState(m_RecordMark[iChnDlgCount],iChnCheckNum);
		GetDlgItem(uLabelID[iChnDlgCount])->ShowWindow(SW_SHOW);
	}
}

BOOL DriveRecordChn::SetRecordMark(DWORD* pRecordMark,int nChannel)
{
	if (NULL == pRecordMark)
	{
		return FALSE;
	}

	// save drive to record channel info
	memcpy(m_RecordMark, pRecordMark, MAX_CHANNEL_COUNT*sizeof(DWORD));
    m_nChannel = (32 * MAX_CHANNEL_COUNT) < nChannel ? 32 * MAX_CHANNEL_COUNT : nChannel;
	return TRUE;
}

DWORD* DriveRecordChn::GetRecordMark()
{
	// save each chndlg checked info

	return m_RecordMark;
}

void DriveRecordChn::OnOK() 
{
	// TODO: Add extra validation here
    if (32 * MAX_CHANNEL_COUNT < m_nChannel)
    {
        CDialog::OnOK();
        return;
    }

	for (int i = 0; i < MAX_CHANNEL_COUNT; i++)
	{
		m_chnRecord[i].GetChnState(&(m_RecordMark[i]), 32);
	}
	CDialog::OnOK();
}
