// DlgMsgHandle.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "DlgMsgHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgHandle dialog


CDlgMsgHandle::CDlgMsgHandle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsgHandle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMsgHandle)
	m_bLog = FALSE;
	m_bLocalPrompt = FALSE;
	m_bMatrix = FALSE;
	m_bMMS = FALSE;
	m_bAlarmOut = FALSE;
	m_bRecord = FALSE;
	m_bMail = FALSE;
	m_bSnap = FALSE;
	m_bTour = FALSE;
	m_bUpload = FALSE;
	m_uMount = 0;
	m_uEventLatch = 0;
	m_uMatrixMask = 0;
	m_uAlarmLatch = 0;
	m_uRecLatch = 0;
	//}}AFX_DATA_INIT
}


void CDlgMsgHandle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMsgHandle)
	DDX_Check(pDX, IDC_CHECK_BLOG, m_bLog);
	DDX_Check(pDX, IDC_CHECK_LOCALTIP, m_bLocalPrompt);
	DDX_Check(pDX, IDC_CHECK_MATRIX_EN, m_bMatrix);
	DDX_Check(pDX, IDC_CHECK_MMSEN, m_bMMS);
	DDX_Check(pDX, IDC_CHECK_OUTPUT, m_bAlarmOut);
	DDX_Check(pDX, IDC_CHECK_RECORD, m_bRecord);
	DDX_Check(pDX, IDC_CHECK_SENDMAIL, m_bMail);
	DDX_Check(pDX, IDC_CHECK_SNAP, m_bSnap);
	DDX_Check(pDX, IDC_CHECK_TOUR, m_bTour);
	DDX_Check(pDX, IDC_CHECK_UPLOAD, m_bUpload);
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_uMount);
	DDV_MinMaxUInt(pDX, m_uMount, 0, 255);
	DDX_Text(pDX, IDC_EDIT_EVENTLATCH, m_uEventLatch);
	DDV_MinMaxUInt(pDX, m_uEventLatch, 0, 15);
	DDX_Text(pDX, IDC_EDIT_MATRIX_MASK, m_uMatrixMask);
	DDV_MinMaxUInt(pDX, m_uMatrixMask, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_ALARMLATCH, m_uAlarmLatch);
	DDV_MinMaxUInt(pDX, m_uAlarmLatch, 0, 300);
	DDX_Text(pDX, IDC_EDIT_RECLATCH, m_uRecLatch);
	DDV_MinMaxUInt(pDX, m_uRecLatch, 0, 300);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMsgHandle, CDialog)
	//{{AFX_MSG_MAP(CDlgMsgHandle)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgHandle message handlers
BOOL CDlgMsgHandle::InitChn()
{
	m_chnAlarmOut.Create(IDD_DIALOG_CHN, this);
	m_chnRecord.Create(IDD_DIALOG_CHN, this);
	m_chnSnap.Create(IDD_DIALOG_CHN, this);
	m_chnTour.Create(IDD_DIALOG_CHN, this);
	
	m_chnAlarmOut.Attach(IDC_STATIC_ALARMOUT, this);
	m_chnRecord.Attach(IDC_STATIC_RECORD, this);
	m_chnSnap.Attach(IDC_STATIC_SNAP, this);
// 	m_chnTour.Attach(IDC_STATIC_TOUR, this);

	GetDlgItem(IDC_CHECK_TOUR)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_TOUR)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHECK_MATRIX_EN)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_MATRIX_MASK)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_MATRIX_MASK)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_SNAPSHOT)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_AMOUNT)->ShowWindow(FALSE);

	return TRUE;
}

BOOL CDlgMsgHandle::SetMsgHandle(const DH_MSG_HANDLE& stuMsgHandle, int nAlarmInCount, int nAlarmOutCount, int nChannelCount)
{
	m_bLog = stuMsgHandle.bLog;
	m_bMatrix = stuMsgHandle.bMatrixEn;
	m_bMMS = stuMsgHandle.bMMSEn;
	m_bLocalPrompt = (stuMsgHandle.dwActionFlag&DH_ALARM_TIP)?1:0;
	m_bAlarmOut = (stuMsgHandle.dwActionFlag&DH_ALARM_OUT)?1:0;
	m_bRecord = (stuMsgHandle.dwActionFlag&DH_ALARM_RECORD)?1:0;
	m_bMail = (stuMsgHandle.dwActionFlag&DH_ALARM_MAIL)?1:0;
	m_bSnap = (stuMsgHandle.dwActionFlag&DH_ALARM_SNAP)?1:0;
	m_bTour = (stuMsgHandle.dwActionFlag&DH_ALARM_TOUR)?1:0;
	m_bUpload = (stuMsgHandle.dwActionFlag&DH_ALARM_UPLOAD)?1:0;

	m_uMount = stuMsgHandle.bySnapshotTimes;
	m_uEventLatch = stuMsgHandle.dwEventLatch;
	m_uAlarmLatch = stuMsgHandle.dwDuration;
	m_uRecLatch = stuMsgHandle.dwRecLatch;
	m_uMatrixMask = (unsigned short)stuMsgHandle.dwMatrix;

	m_chnAlarmOut.SetChnState((BYTE *)stuMsgHandle.byRelAlarmOut, nAlarmOutCount);
	m_chnRecord.SetChnState((BYTE *)stuMsgHandle.byRecordChannel, nChannelCount);
	m_chnSnap.SetChnState((BYTE *)stuMsgHandle.bySnap, nChannelCount);
	m_chnTour.SetChnState((BYTE *)stuMsgHandle.byTour, nChannelCount);

	return UpdateData(FALSE);
}

BOOL CDlgMsgHandle::SetMsgHandleEx(const DH_MSG_HANDLE_EX& stuMsgHandle, int nAlarmInCount, int nAlarmOutCount, int nChannelCount)
{
	m_bLog = stuMsgHandle.bLog;
	m_bMatrix = stuMsgHandle.bMatrixEn;
	m_bMMS = stuMsgHandle.bMMSEn;
	m_bLocalPrompt = (stuMsgHandle.dwActionFlag&DH_ALARM_TIP)?1:0;
	m_bAlarmOut = (stuMsgHandle.dwActionFlag&DH_ALARM_OUT)?1:0;
	m_bRecord = (stuMsgHandle.dwActionFlag&DH_ALARM_RECORD)?1:0;
	m_bMail = (stuMsgHandle.dwActionFlag&DH_ALARM_MAIL)?1:0;
	m_bSnap = (stuMsgHandle.dwActionFlag&DH_ALARM_SNAP)?1:0;
	m_bTour = (stuMsgHandle.dwActionFlag&DH_ALARM_TOUR)?1:0;
	m_bUpload = (stuMsgHandle.dwActionFlag&DH_ALARM_UPLOAD)?1:0;

	m_uMount = stuMsgHandle.bySnapshotTimes;
	m_uEventLatch = stuMsgHandle.dwEventLatch;
	m_uAlarmLatch = stuMsgHandle.dwDuration;
	m_uRecLatch = stuMsgHandle.dwRecLatch;
	m_uMatrixMask = (unsigned short)stuMsgHandle.dwMatrix;

	m_chnAlarmOut.SetChnState((BYTE *)stuMsgHandle.byRelAlarmOut, nAlarmOutCount);
	m_chnRecord.SetChnState((BYTE *)stuMsgHandle.byRecordChannel, nChannelCount);
	m_chnSnap.SetChnState((BYTE *)stuMsgHandle.bySnap, nChannelCount);
	m_chnTour.SetChnState((BYTE *)stuMsgHandle.byTour, nChannelCount);

	return UpdateData(FALSE);
}

BOOL CDlgMsgHandle::GetMsgHandle(DH_MSG_HANDLE& stuMsgHandle)
{
	if(UpdateData(TRUE) == FALSE)
	{
		return FALSE;
	}

	stuMsgHandle.bLog = m_bLog;
	stuMsgHandle.bMatrixEn = m_bMatrix;
	stuMsgHandle.bMMSEn = m_bMMS;

	stuMsgHandle.dwActionFlag = 0;
	stuMsgHandle.dwActionFlag |=  (m_bLocalPrompt > 0) ? DH_ALARM_TIP : 0;
	stuMsgHandle.dwActionFlag |=  (m_bAlarmOut > 0) ? DH_ALARM_OUT : 0;
	stuMsgHandle.dwActionFlag |=  (m_bRecord > 0) ? DH_ALARM_RECORD : 0;
	stuMsgHandle.dwActionFlag |=  (m_bMail > 0) ? DH_ALARM_MAIL : 0;
	stuMsgHandle.dwActionFlag |=  (m_bSnap > 0) ? DH_ALARM_SNAP : 0;
	stuMsgHandle.dwActionFlag |=  (m_bTour > 0) ? DH_ALARM_TOUR : 0;
	stuMsgHandle.dwActionFlag |=  (m_bUpload > 0) ? DH_ALARM_UPLOAD : 0;

	stuMsgHandle.bySnapshotTimes = m_uMount;
	stuMsgHandle.dwEventLatch = m_uEventLatch;
	stuMsgHandle.dwMatrix = m_uMatrixMask;
	stuMsgHandle.dwDuration = m_uAlarmLatch;
	stuMsgHandle.dwRecLatch = m_uRecLatch;
	m_chnAlarmOut.GetChnState(stuMsgHandle.byRelAlarmOut, DH_MAX_ALARMOUT_NUM);
	m_chnRecord.GetChnState(stuMsgHandle.byRecordChannel, DH_MAX_VIDEO_IN_NUM);
	m_chnSnap.GetChnState(stuMsgHandle.bySnap, DH_MAX_VIDEO_IN_NUM);
	m_chnTour.GetChnState(stuMsgHandle.byTour, DH_MAX_VIDEO_IN_NUM);
	
	return TRUE;
}

BOOL CDlgMsgHandle::GetMsgHandleEx(DH_MSG_HANDLE_EX& stuMsgHandle)
{
	if(UpdateData(TRUE) == FALSE)
	{
		return FALSE;
	}

	stuMsgHandle.bLog = m_bLog;
	stuMsgHandle.bMatrixEn = m_bMatrix;
	stuMsgHandle.bMMSEn = m_bMMS;

	stuMsgHandle.dwActionFlag = 0;
	stuMsgHandle.dwActionFlag |=  (m_bLocalPrompt > 0) ? DH_ALARM_TIP : 0;
	stuMsgHandle.dwActionFlag |=  (m_bAlarmOut > 0) ? DH_ALARM_OUT : 0;
	stuMsgHandle.dwActionFlag |=  (m_bRecord > 0) ? DH_ALARM_RECORD : 0;
	stuMsgHandle.dwActionFlag |=  (m_bMail > 0) ? DH_ALARM_MAIL : 0;
	stuMsgHandle.dwActionFlag |=  (m_bSnap > 0) ? DH_ALARM_SNAP : 0;
	stuMsgHandle.dwActionFlag |=  (m_bTour > 0) ? DH_ALARM_TOUR : 0;
	stuMsgHandle.dwActionFlag |=  (m_bUpload > 0) ? DH_ALARM_UPLOAD : 0;

	stuMsgHandle.bySnapshotTimes = m_uMount;
	stuMsgHandle.dwEventLatch = m_uEventLatch;
	stuMsgHandle.dwMatrix = m_uMatrixMask;
	stuMsgHandle.dwDuration = m_uAlarmLatch;
	stuMsgHandle.dwRecLatch = m_uRecLatch;
	m_chnAlarmOut.GetChnState(stuMsgHandle.byRelAlarmOut, DH_MAX_ALARMOUT_NUM_EX);
	m_chnRecord.GetChnState(stuMsgHandle.byRecordChannel, DH_MAX_VIDEO_IN_NUM_EX);
	m_chnSnap.GetChnState(stuMsgHandle.bySnap, DH_MAX_VIDEO_IN_NUM_EX);
	m_chnTour.GetChnState(stuMsgHandle.byTour, DH_MAX_VIDEO_IN_NUM_EX);
	
	return TRUE;
}


BOOL CDlgMsgHandle::Attach(UINT uID, CDialog* pAttachDlg)
{
	//get attached window rect
	RECT rect = {0};
	pAttachDlg->GetDlgItem(uID)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	//get self window rect
	RECT rectSelf = {0};
	this->GetClientRect(&rectSelf);
	ScreenToClient(&rectSelf);
	//calculte the rect
	rect.right = rect.left+rectSelf.right-rectSelf.left;
	rect.bottom = rect.top+rectSelf.bottom-rectSelf.top;
	//change the size of attach window to fix this window
	pAttachDlg->GetDlgItem(uID)->ShowWindow(SW_HIDE);

	this->MoveWindow(&rect, TRUE);
	this->ShowWindow(SW_SHOW);

	return TRUE;
}

BOOL CDlgMsgHandle::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	InitChn();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMsgHandle::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}
