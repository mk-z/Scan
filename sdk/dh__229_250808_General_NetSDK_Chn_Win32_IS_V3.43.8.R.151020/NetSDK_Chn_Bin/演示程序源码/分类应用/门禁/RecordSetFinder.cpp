// RecordSetFinder.cpp : implementation file
//

#include "stdafx.h"
#include "accesscontrol.h"
#include "RecordSetFinder.h"

#include "SubDlgInfoCard.h"
#include "DlgSubDlgInfoAccessRecord.h"
#include "DlgSubDlgInfoHoliday.h"
#include "DlgSubDlgInfoPassword.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordSetFinder dialog


CRecordSetFinder::CRecordSetFinder(CWnd* pParent /* = NULL */, LLONG lLoginID /* = 0 */, int nAccess /* = 1 */)
	: CDialog(CRecordSetFinder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecordSetFinder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lLoginID      = lLoginID;
    m_lFinder       = 0;
    m_nStartSeq     = 0;
	m_emDataType    = DataType_Access;
    m_nAccessGroup  = nAccess;
}


void CRecordSetFinder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecordSetFinder)
	DDX_Control(pDX, IDC_RECORDSETFINDER_CMB_RESULT, m_cmbResult);
	DDX_Control(pDX, IDC_RECORDSETFINDER_CMB_DATATYPE, m_cmbDataType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecordSetFinder, CDialog)
	//{{AFX_MSG_MAP(CRecordSetFinder)
    ON_BN_CLICKED(IDC_RECORDSETFINDER_BTN_QUERYSTART, OnRecordsetfinderBtnQueryStart)
    ON_BN_CLICKED(IDC_RECORDSETFINDER_BTN_QUERYNEXT, OnRecordsetfinderBtnQueryNext)
	ON_BN_CLICKED(IDC_RECORDSETFINDER_BTN_QUERYSTOP, OnRecordsetfinderBtnQueryStop)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_RECORDSETFINDER_CMB_RESULT, OnSelchangeRecordsetfinderCmbResult)
	ON_CBN_SELCHANGE(IDC_RECORDSETFINDER_CMB_DATATYPE, OnSelchangeRecordsetfinderCmbDatatype)
	ON_BN_CLICKED(IDC_RECORDSETFINDER_BTN_COUNT, OnRecordsetfinderBtnCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordSetFinder private method

void CRecordSetFinder::InitDlg()
{
    GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYSTART)->EnableWindow();
    GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYNEXT)->EnableWindow(FALSE);
    GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYSTOP)->EnableWindow(FALSE);
    GetDlgItem(IDC_RECORDSETFINDER_BTN_COUNT)->EnableWindow(FALSE);

	// data type
	m_cmbDataType.ResetContent();
    int nWidth = m_cmbDataType.GetDroppedWidth();
    m_cmbDataType.SetDroppedWidth(nWidth * 2);
	for (int i = 0; i < sizeof(stuDemoDataType)/sizeof(stuDemoDataType[0]); i++)
	{
		m_cmbDataType.InsertString(-1, ConvertString(stuDemoDataType[i].szName));
	}
	m_cmbDataType.SetCurSel(0);

	// max num
	SetDlgItemInt(IDC_RECORDSETFINDER_EDT_MAXNUM, 10);

	// ret num
	SetDlgItemInt(IDC_RECORDSETFINDER_EDT_RETNUM, 0);

	// result
	ClearResult();
}

void CRecordSetFinder::ClearResult()
{
	while (m_cmbResult.GetCount())
	{
		int nIndex = 0;
		void* dwData = m_cmbResult.GetItemDataPtr(nIndex);

		if (DataType_Card == m_emDataType)
		{
			NET_RECORDSET_ACCESS_CTL_CARD* p = (NET_RECORDSET_ACCESS_CTL_CARD*)dwData;
			if (p)
			{
				delete p;
				p = NULL;
			}
		}
		else if (DataType_Password == m_emDataType)
		{
			NET_RECORDSET_ACCESS_CTL_PWD* p = (NET_RECORDSET_ACCESS_CTL_PWD*)dwData;
			if (p)
			{
				delete p;
				p = NULL;
			}
		}
		else if (DataType_Access == m_emDataType)
		{
			NET_RECORDSET_ACCESS_CTL_CARDREC* p = (NET_RECORDSET_ACCESS_CTL_CARDREC*)dwData;
			if (p)
			{
				delete p;
				p = NULL;
			}
		}

		m_cmbResult.DeleteString(nIndex);
	}
	m_cmbResult.ResetContent();
}
//////////////////////////////////////////////////////////////////////////
//
// card
//
//////////////////////////////////////////////////////////////////////////
BOOL CRecordSetFinder::QueryCard()
{	
	LLONG lFinderID = 0;
	RecordSetFind_Card(m_lLoginID, lFinderID);
	if (lFinderID != 0)
	{
		RecordSetFindNext_Card(lFinderID);
		CLIENT_FindRecordClose(lFinderID);
		return TRUE;
	}
	else
	{
		CString csInfo;
		csInfo.Format("%s:%08x", ConvertString("Start to find failed", DLG_RECORDSET_FINDER), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}

	return FALSE;
}

void CRecordSetFinder::RecordSetFind_Card(LLONG lLoginId, LLONG& lFinderId)
{
	NET_IN_FIND_RECORD_PARAM stuIn = {sizeof(stuIn)};
	NET_OUT_FIND_RECORD_PARAM stuOut = {sizeof(stuOut)};
	
	stuIn.emType = NET_RECORD_ACCESSCTLCARD;
		
	if (CLIENT_FindRecord(lLoginId, &stuIn, &stuOut, SDK_API_WAITTIME))
	{
		lFinderId = stuOut.lFindeHandle;
	}
}

int CRecordSetFinder::RecordSetFindNext_Card(LLONG lFinderId)
{
	int i = 0, j = 0;
	int nMaxNum = GetDlgItemInt(IDC_RECORDSETFINDER_EDT_MAXNUM, NULL, TRUE);
	if (nMaxNum <= 0)
	{
		return -1;
	}
	NET_IN_FIND_NEXT_RECORD_PARAM stuIn = {sizeof(stuIn)};
	stuIn.lFindeHandle = lFinderId;
	stuIn.nFileCount = nMaxNum;
	
	NET_OUT_FIND_NEXT_RECORD_PARAM stuOut = {sizeof(stuOut)};
	stuOut.nMaxRecordNum = nMaxNum;
	
	NET_RECORDSET_ACCESS_CTL_CARD* pstuCard = new NET_RECORDSET_ACCESS_CTL_CARD[nMaxNum];
	if (NULL == pstuCard)
	{
		return -1;
	}
	memset(pstuCard, 0, sizeof(NET_RECORDSET_ACCESS_CTL_CARD) * nMaxNum);

	for (i = 0; i < nMaxNum; i++)
	{
		pstuCard[i].dwSize = sizeof(NET_RECORDSET_ACCESS_CTL_CARD);
	}
	stuOut.pRecordList = (void*)pstuCard;
	
	if (CLIENT_FindNextRecord(&stuIn, &stuOut, SDK_API_WAITTIME) >= 0)
    {
        if (stuOut.nRetRecordNum > 0)
        {
            ClearResult();
        }
		for (i = 0; i < __min(stuOut.nMaxRecordNum, stuOut.nRetRecordNum); i++)
		{
			CString csInfo;
			csInfo.Format("%d", m_nStartSeq + 1);
            m_nStartSeq++;
			int nIndex = m_cmbResult.InsertString(-1, csInfo);

			NET_RECORDSET_ACCESS_CTL_CARD* p = new NET_RECORDSET_ACCESS_CTL_CARD;
			if (p != NULL)
			{
				memcpy(p, &pstuCard[i], sizeof(NET_RECORDSET_ACCESS_CTL_CARD));
				m_cmbResult.SetItemDataPtr(nIndex, (void*)p);
			}
		}
		SetDlgItemInt(IDC_RECORDSETFINDER_EDT_RETNUM, stuOut.nRetRecordNum);
	}
	else
	{
		CString csInfo;
		csInfo.Format("%s:%08x", ConvertString("Find card failed", DLG_RECORDSET_FINDER), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}

	delete[] pstuCard;
	pstuCard = NULL;
    return stuOut.nRetRecordNum;
}

void CRecordSetFinder::ShowCard(NET_RECORDSET_ACCESS_CTL_CARD* pInfo)
{
	if (NULL == pInfo)
	{
		return;
	}
	CSubDlgInfoCard dlg(this, pInfo, m_nAccessGroup);
	dlg.DoModal();
}
//////////////////////////////////////////////////////////////////////////
//
// pwd
//
//////////////////////////////////////////////////////////////////////////
BOOL CRecordSetFinder::QueryPwd()
{
	LLONG lFinderID = 0;
	RecordSetFind_Pwd(m_lLoginID, lFinderID);
	if (lFinderID != 0)
	{
		RecordSetFindNext_Pwd(lFinderID);
		CLIENT_FindRecordClose(lFinderID);
		return TRUE;
	}
	else
	{
		CString csInfo;
		csInfo.Format("%s:%08x", ConvertString("Start to find failed", DLG_RECORDSET_FINDER), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
	
	return FALSE;
}

void CRecordSetFinder::RecordSetFind_Pwd(LLONG lLoginId, LLONG& lFinderId)
{
	NET_IN_FIND_RECORD_PARAM stuIn = {sizeof(stuIn)};
	NET_OUT_FIND_RECORD_PARAM stuOut = {sizeof(stuOut)};
	
	stuIn.emType = NET_RECORD_ACCESSCTLPWD;
	
	if (CLIENT_FindRecord(lLoginId, &stuIn, &stuOut, SDK_API_WAITTIME))
	{
		lFinderId = stuOut.lFindeHandle;
	}
}

int CRecordSetFinder::RecordSetFindNext_Pwd(LLONG lFinderId)
{
	int i = 0, j = 0;
	int nMaxNum = GetDlgItemInt(IDC_RECORDSETFINDER_EDT_MAXNUM, NULL, TRUE);
	if (nMaxNum <= 0)
	{
		return -1;
	}
	
	NET_IN_FIND_NEXT_RECORD_PARAM stuIn = {sizeof(stuIn)};
	stuIn.lFindeHandle = lFinderId;
	stuIn.nFileCount = nMaxNum;
	
	NET_OUT_FIND_NEXT_RECORD_PARAM stuOut = {sizeof(stuOut)};
	stuOut.nMaxRecordNum = nMaxNum;
	
	NET_RECORDSET_ACCESS_CTL_PWD* pstuPwd = new NET_RECORDSET_ACCESS_CTL_PWD[nMaxNum];
	if (NULL == pstuPwd)
	{
		return -1;
	}
	memset(pstuPwd, 0, sizeof(NET_RECORDSET_ACCESS_CTL_PWD) * nMaxNum);
	
	for (i = 0; i < nMaxNum; i++)
	{
		pstuPwd[i].dwSize = sizeof(NET_RECORDSET_ACCESS_CTL_PWD);
	}
	stuOut.pRecordList = (void*)pstuPwd;
	
	if (CLIENT_FindNextRecord(&stuIn, &stuOut, SDK_API_WAITTIME) >= 0)
	{
        if (stuOut.nRetRecordNum > 0)
        {
            ClearResult();
        }
		for (i = 0; i < __min(stuOut.nMaxRecordNum, stuOut.nRetRecordNum); i++)
		{
			CString csInfo;
			csInfo.Format("%d", m_nStartSeq + 1);
            m_nStartSeq++;
			int nIndex = m_cmbResult.InsertString(-1, csInfo);

			NET_RECORDSET_ACCESS_CTL_PWD* p = new NET_RECORDSET_ACCESS_CTL_PWD;
			if (p != NULL)
			{
				memcpy(p, &pstuPwd[i], sizeof(NET_RECORDSET_ACCESS_CTL_PWD));
				m_cmbResult.SetItemDataPtr(nIndex, (void*)p);
			}
		}
		SetDlgItemInt(IDC_RECORDSETFINDER_EDT_RETNUM, stuOut.nRetRecordNum);
	}
	else
	{
		CString csInfo;
		csInfo.Format("%s:%08x", ConvertString("Find pwd failed", DLG_RECORDSET_FINDER), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
	
	delete[] pstuPwd;
	pstuPwd = NULL;
    return stuOut.nRetRecordNum;
}

void CRecordSetFinder::ShowPwd(NET_RECORDSET_ACCESS_CTL_PWD* pInfo)
{
	if (NULL == pInfo)
	{
		return;
	}
	CDlgSubDlgInfoPassword dlg(this, pInfo, m_nAccessGroup);
	dlg.DoModal();
}
//////////////////////////////////////////////////////////////////////////
//
// cardrec
//
//////////////////////////////////////////////////////////////////////////
BOOL CRecordSetFinder::QueryCardRec()
{
	LLONG lFinderID = 0;
	RecordSetFind_CardRec(m_lLoginID, lFinderID);
	if (lFinderID != 0)
	{
		RecordSetFindNext_CardRec(lFinderID);
		CLIENT_FindRecordClose(lFinderID);
		return TRUE;
	}
	else
	{
		CString csInfo;
		csInfo.Format("%s:%08x", ConvertString("Start to find failed", DLG_RECORDSET_FINDER), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
	
	return FALSE;
}

void CRecordSetFinder::RecordSetFind_CardRec(LLONG lLoginId, LLONG& lFinderId)
{
	NET_IN_FIND_RECORD_PARAM stuIn = {sizeof(stuIn)};
	NET_OUT_FIND_RECORD_PARAM stuOut = {sizeof(stuOut)};
	
	stuIn.emType = NET_RECORD_ACCESSCTLCARDREC;
	
	if (CLIENT_FindRecord(lLoginId, &stuIn, &stuOut, SDK_API_WAITTIME))
	{
		lFinderId = stuOut.lFindeHandle;
        GetDlgItem(IDC_RECORDSETFINDER_EDT_MAXNUM)->EnableWindow(FALSE);
	}
}

int CRecordSetFinder::RecordSetFindNext_CardRec(LLONG lFinderId)
{
	int i = 0, j = 0;
	int nMaxNum = GetDlgItemInt(IDC_RECORDSETFINDER_EDT_MAXNUM, NULL, TRUE);
	if (nMaxNum <= 0)
	{
		return -1;
	}
	
	NET_IN_FIND_NEXT_RECORD_PARAM stuIn = {sizeof(stuIn)};
	stuIn.lFindeHandle = lFinderId;
	stuIn.nFileCount = nMaxNum;
	
	NET_OUT_FIND_NEXT_RECORD_PARAM stuOut = {sizeof(stuOut)};
	stuOut.nMaxRecordNum = nMaxNum;
	
	NET_RECORDSET_ACCESS_CTL_CARDREC* pstuCardRec = new NET_RECORDSET_ACCESS_CTL_CARDREC[nMaxNum];
	if (NULL == pstuCardRec)
	{
		return -1;
	}
	memset(pstuCardRec, 0, sizeof(NET_RECORDSET_ACCESS_CTL_CARDREC) * nMaxNum);
	
	for (i = 0; i < nMaxNum; i++)
	{
		pstuCardRec[i].dwSize = sizeof(NET_RECORDSET_ACCESS_CTL_CARDREC);
	}
	stuOut.pRecordList = (void*)pstuCardRec;
	
	if (CLIENT_FindNextRecord(&stuIn, &stuOut, SDK_API_WAITTIME) >= 0)
	{
        if (stuOut.nRetRecordNum > 0)
        {
            ClearResult();
        }
		for (i = 0; i < __min(stuOut.nMaxRecordNum, stuOut.nRetRecordNum); i++)
		{
			CString csInfo;
            csInfo.Format("%d", m_nStartSeq + 1);
            m_nStartSeq++;
			int nIndex = m_cmbResult.InsertString(-1, csInfo);

			NET_RECORDSET_ACCESS_CTL_CARDREC* p = new NET_RECORDSET_ACCESS_CTL_CARDREC;
			if (p != NULL)
			{
				memcpy(p, &pstuCardRec[i], sizeof(NET_RECORDSET_ACCESS_CTL_CARDREC));
				m_cmbResult.SetItemDataPtr(nIndex, (void*)p);
			}
		}
		SetDlgItemInt(IDC_RECORDSETFINDER_EDT_RETNUM, stuOut.nRetRecordNum);
	}
	else
	{
		CString csInfo;
		csInfo.Format("%s:%08x", ConvertString("Find CardRec failed", DLG_RECORDSET_FINDER), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
	
	delete[] pstuCardRec;
	pstuCardRec = NULL;
    return stuOut.nRetRecordNum;
}

void CRecordSetFinder::ShowCardRec(NET_RECORDSET_ACCESS_CTL_CARDREC* pInfo)
{
	if (NULL == pInfo)
	{
		return;
	}
	CDlgSubDlgInfoAccessRecord dlg(this, pInfo);
	dlg.DoModal();
}
/////////////////////////////////////////////////////////////////////////////
// CRecordSetFinder message handlers

BOOL CRecordSetFinder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this, DLG_RECORDSET_FINDER);
	// TODO: Add extra initialization here
	InitDlg();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////
//
// query start
//
//////////////////////////////////////////////////////////////////////////
void CRecordSetFinder::OnRecordsetfinderBtnQueryStart() 
{
	// TODO: Add your control notification handler code here
	ClearResult();
    
    LLONG lFinder = 0;

	switch (m_cmbDataType.GetCurSel())
	{
	case DataType_Card:
        RecordSetFind_Card(m_lLoginID, lFinder);
		break;
	case DataType_Password:
        RecordSetFind_Pwd(m_lLoginID, lFinder);
		break;
	case DataType_Access:
        RecordSetFind_CardRec(m_lLoginID, lFinder);
		break;
// 	case DataType_Holiday: // not support by BSC
// 		QueryHoliday();
		break;
	default:
		break;
    }

    if (lFinder != 0)
    {
        m_lFinder = lFinder;
        GetDlgItem(IDC_RECORDSETFINDER_CMB_DATATYPE)->EnableWindow(FALSE);
        GetDlgItem(IDC_RECORDSETFINDER_EDT_MAXNUM)->EnableWindow(FALSE);
        GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYSTART)->EnableWindow(FALSE);
        GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYNEXT)->EnableWindow();
        GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYSTOP)->EnableWindow();
        GetDlgItem(IDC_RECORDSETFINDER_BTN_COUNT)->EnableWindow();
    }
	m_emDataType = (DataType)m_cmbDataType.GetCurSel();
}
//////////////////////////////////////////////////////////////////////////
//
// query next
//
//////////////////////////////////////////////////////////////////////////
void CRecordSetFinder::OnRecordsetfinderBtnQueryNext()
{
	int nMaxNum = GetDlgItemInt(IDC_RECORDSETFINDER_EDT_MAXNUM, NULL, TRUE);
    if (nMaxNum <= 0)
    {
        return;
    }

    int nRet = 0;
    switch (m_cmbDataType.GetCurSel())
    {
    case DataType_Card:
        nRet = RecordSetFindNext_Card(m_lFinder);
        break;
    case DataType_Password:
        nRet = RecordSetFindNext_Pwd(m_lFinder);
        break;
    case DataType_Access:
        nRet = RecordSetFindNext_CardRec(m_lFinder);
        break;
    default:
        break;
    }
    if (nRet <= 0 || nRet < nMaxNum)
    {
        GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYNEXT)->EnableWindow(FALSE);
    }
    if (nRet > 0)
    {
        m_cmbResult.SetCurSel(0);
    }
}

void CRecordSetFinder::OnRecordsetfinderBtnQueryStop()
{
    CLIENT_FindRecordClose(m_lFinder);
    m_lFinder = 0;
    m_nStartSeq = 0;
    GetDlgItem(IDC_RECORDSETFINDER_CMB_DATATYPE)->EnableWindow();
    GetDlgItem(IDC_RECORDSETFINDER_EDT_MAXNUM)->EnableWindow();
    GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYSTART)->EnableWindow();
    GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYNEXT)->EnableWindow(FALSE);
    GetDlgItem(IDC_RECORDSETFINDER_BTN_QUERYSTOP)->EnableWindow(FALSE);
    GetDlgItem(IDC_RECORDSETFINDER_BTN_COUNT)->EnableWindow(FALSE);
}

void CRecordSetFinder::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	ClearResult();
    if (m_lFinder != 0)
    {
        CLIENT_FindRecordClose(m_lFinder);
    }
}

void CRecordSetFinder::OnSelchangeRecordsetfinderCmbResult() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbResult.GetCurSel();
	if (-1 == nSel)
	{
		return;
	}
	SetDlgItemInt(IDC_RECORDSETFINDER_EDT_RETNUM, 0);
	
	void* p = m_cmbResult.GetItemDataPtr(nSel);
    if (NULL == p)
    {
        return;
    }

	switch (m_cmbDataType.GetCurSel())
	{
	case DataType_Card:
		ShowCard((NET_RECORDSET_ACCESS_CTL_CARD*)p);
		break;
	case DataType_Access:
		ShowCardRec((NET_RECORDSET_ACCESS_CTL_CARDREC*)p);
		break;
	case DataType_Password:
		ShowPwd((NET_RECORDSET_ACCESS_CTL_PWD*)p);
		break;
// 	case DataType_Holiday:
// 		ShowHoliday((NET_RECORDSET_HOLIDAY*)p);
		break;
	default:
		break;
	}
}

void CRecordSetFinder::OnSelchangeRecordsetfinderCmbDatatype() 
{
	// TODO: Add your control notification handler code here
	ClearResult();
	SetDlgItemInt(IDC_RECORDSETFINDER_EDT_RETNUM, 0);
	m_emDataType = (DataType)m_cmbDataType.GetCurSel();
}

void CRecordSetFinder::OnRecordsetfinderBtnCount() 
{
	// TODO: Add your control notification handler code here
    NET_IN_QUEYT_RECORD_COUNT_PARAM stuIn = {sizeof(stuIn)};
    stuIn.lFindeHandle = m_lFinder;
    NET_OUT_QUEYT_RECORD_COUNT_PARAM stuOut = {sizeof(stuOut)};
    if (CLIENT_QueryRecordCount(&stuIn, &stuOut, SDK_API_WAITTIME))
    {
        CString csInfo;
        csInfo.Format("%s %d",
            ConvertString(("Total count is"), DLG_RECORDSET_FINDER),
            stuOut.nRecordCount);
        MessageBox(csInfo, ConvertString("Prompt"));
    }
    else
    {
        CString csInfo;
        csInfo.Format("%s:0x%08x",
            ConvertString("Get total count failed", DLG_RECORDSET_FINDER),
            CLIENT_GetLastError());
        MessageBox(csInfo, ConvertString("Prompt"));
    }
}
