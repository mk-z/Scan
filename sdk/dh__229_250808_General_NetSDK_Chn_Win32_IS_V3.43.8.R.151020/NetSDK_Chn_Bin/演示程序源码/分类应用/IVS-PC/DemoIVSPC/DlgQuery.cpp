// DlgQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "DemoIVSPC.h"
#include "DlgQuery.h"
#include "DemoIVSPCDlg.h"
#include "Utility.h"
#include <string>

#include "DrawFrame.h"
// CDlgQuery 对话框

IMPLEMENT_DYNAMIC(CDlgQuery, CDialog)

CDlgQuery::CDlgQuery(int nChannelCount,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQuery::IDD, pParent),
	m_nChannelCount(nChannelCount)
	, m_dwIndexStart(0)
	, m_dwIndexEnd(0)
{
	memset(&m_stuDoFindNumberStat_out, 0, sizeof(NET_OUT_DOFINDNUMBERSTAT));
}

CDlgQuery::CDlgQuery(CWnd* pParent /*=NULL*/)
: CDialog(CDlgQuery::IDD, pParent)
, m_dwIndexStart(0)
, m_dwIndexEnd(0)
{
	memset(&m_stuDoFindNumberStat_out, 0, sizeof(NET_OUT_DOFINDNUMBERSTAT));
}

CDlgQuery::~CDlgQuery()
{
	if(m_stuDoFindNumberStat_out.pstuNumberStat)
	{
		delete []m_stuDoFindNumberStat_out.pstuNumberStat;
		m_stuDoFindNumberStat_out.pstuNumberStat = NULL;
	}

	if (m_dlgDrawFrame)
	{
		delete m_dlgDrawFrame;
		m_dlgDrawFrame = NULL;
	}
}

void CDlgQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QUERY_CMB_CHANNEL,   m_cmbChannel);
	DDX_Control(pDX, IDC_QUERY_DTP_STARTDATE, m_dtpStartDate);
	DDX_Control(pDX, IDC_QUERY_DTP_STARTTIME, m_dtpStartTime);
	DDX_Control(pDX, IDC_QUERY_DTP_ENDDATE,   m_dtpEndDate);
	DDX_Control(pDX, IDC_QUERY_DTP_ENDTIME,   m_dtpEndTime);
	DDX_Control(pDX, IDC_QUERY_CMB_TYPES,     m_cmbTypes);
	DDX_Control(pDX, IDC_EDIT_BEGIN,          m_editBegin);
	DDX_Control(pDX, IDC_EDIT_COUNT,          m_editCount);
	DDX_Control(pDX, IDC_LIST_TYPE,           m_listResult);
}


BEGIN_MESSAGE_MAP(CDlgQuery, CDialog)

	ON_BN_CLICKED(ID_QUERY_START, CDlgQuery::OnBnClickedQueryStart)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, CDlgQuery::OnBnClickedBtnPreview)
	ON_BN_CLICKED(IDC_BTN_NEXT, CDlgQuery::OnBnClickedBtnNext)
	ON_MESSAGE(WM_MSG_SHOW, CDlgQuery::OnSelectRecord)
END_MESSAGE_MAP()

void CDlgQuery::InitQueryDlg(int nChanCount)
{
	if (nChanCount <= 0)
	{
		return ;
	}
	m_nChannelCount = nChanCount;
	


	//清空事件类型树
	m_listResult.DeleteAllItems();

	//清空组合框
	m_cmbChannel.ResetContent();

	TCHAR szItem[16] = {0};
	for (int i = 0; i < nChanCount; i++)
	{
		_sntprintf(szItem, _countof(szItem)*sizeof(TCHAR), ConvertString(_T("Channel%02d")), i + 1);
		m_cmbChannel.InsertString(i, szItem);
		ZeroMemory(szItem, _countof(szItem));
	}

	m_cmbChannel.SetCurSel(0);
	InitCommboxDate();
}
void CDlgQuery::UninitQueryDlg()
{
	m_listResult.DeleteAllItems();
	m_cmbChannel.ResetContent();
	m_cmbTypes.ResetContent();

	if (m_dlgDrawFrame)
	{
		m_dlgDrawFrame->UninitData();
		m_dlgDrawFrame->Invalidate();
	}
}

void CDlgQuery::InitCommboxDate()
{
	m_cmbTypes.ResetContent();
	m_cmbTypes.AddString(ConvertString("Minute"));
	m_cmbTypes.AddString(ConvertString("Hour"));
	m_cmbTypes.AddString(ConvertString("Day"));
	m_cmbTypes.AddString(ConvertString("Week"));
	m_cmbTypes.AddString(ConvertString("Month"));
	m_cmbTypes.AddString(ConvertString("Season"));
	m_cmbTypes.AddString(ConvertString("Year"));
	m_cmbTypes.SetCurSel(0);
}

// CDlgQuery 消息处理程序
BOOL CDlgQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	// TODO: Add extra initialization here
	CString strFormat ;
	// m_cmbTypes的初始化
	InitCommboxDate();

	//
	SYSTEMTIME stEndDate;
	m_dtpEndDate.GetTime(&stEndDate);

	stEndDate.wDay += 1;
	m_dtpEndTime.SetTime(&stEndDate);
	// m_editBegin初始化
	strFormat = "0";
	m_editBegin.SetWindowText(strFormat);
	// m_editCount 初始化
	m_editCount.SetWindowText("100");

    // m_listResult初始化
	m_listResult.SetExtendedStyle(m_listResult.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_listResult.InsertColumn(0, ConvertString("Num"), LVCFMT_LEFT, 40, -1);
	m_listResult.InsertColumn(1, ConvertString("ChannelID"), LVCFMT_LEFT, 80, -1);
	m_listResult.InsertColumn(2, ConvertString("Start Time"), LVCFMT_LEFT, 140, -1);
	m_listResult.InsertColumn(3, ConvertString("End Time"), LVCFMT_LEFT, 140, -1);
	m_listResult.InsertColumn(4, ConvertString("Entered Number"), LVCFMT_LEFT, 100, -1);
    m_listResult.InsertColumn(5, ConvertString("Exited Number"),  LVCFMT_LEFT, 100, -1);

	m_dlgDrawFrame = new CDrawFrame;
	m_dlgDrawFrame->Create(CDrawFrame::IDD, this);

	GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PREVIEW)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgQuery::ShowListResult( NET_OUT_DOFINDNUMBERSTAT &FindNumber)
{
	if(FindNumber.nCount > 100)
	{
		m_dwIndexStart = 0;
		m_dwIndexEnd = 99;
		GetDlgItem(IDC_BTN_PREVIEW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(TRUE);
		ShowListResultRange(FindNumber, 0, 100);
		Draw(m_stuDoFindNumberStat_out, 0, 100);
	}
	else
	{
		m_dwIndexStart = 0;
		m_dwIndexEnd = 0;
		GetDlgItem(IDC_BTN_PREVIEW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);
		ShowListResultRange(FindNumber, 0, FindNumber.nCount);
		Draw(m_stuDoFindNumberStat_out, 0, FindNumber.nCount);
	}
}

void CDlgQuery::ShowListResultRange(NET_OUT_DOFINDNUMBERSTAT &FindNumber, int nIndex, int nCount)
{
	int nRow = 0;
	CString cstrColText;
	DH_NUMBERSTAT *pCurNumerStat = NULL;
	m_listResult.DeleteAllItems();

	if (FindNumber.nCount <= 0 || FindNumber.pstuNumberStat == NULL)
	{
		return;
	}

	CString strNum;
	for (int i = nIndex; i < nIndex+nCount; i++)
	{
		pCurNumerStat = FindNumber.pstuNumberStat + i;
		strNum.Format("%d", i + 1);
		cstrColText.Format("%d", pCurNumerStat->nChannelID+1);

		nRow = m_listResult.GetItemCount() > 0 ? m_listResult.GetItemCount() - 1 : 0;
		nRow = m_listResult.InsertItem(nRow, "");
		m_listResult.SetItemText(nRow, 0, strNum);
		m_listResult.SetItemText(nRow, 1, cstrColText);
		cstrColText.Format("%04d-%02d-%02d %02d:%02d:%02d", 
			pCurNumerStat->stuStartTime.dwYear, pCurNumerStat->stuStartTime.dwMonth, 
			pCurNumerStat->stuStartTime.dwDay, pCurNumerStat->stuStartTime.dwHour,
			pCurNumerStat->stuStartTime.dwMinute, pCurNumerStat->stuStartTime.dwSecond);
		m_listResult.SetItemText(nRow, 2,cstrColText);
		cstrColText.Format("%04d-%02d-%02d %02d:%02d:%02d", 
			pCurNumerStat->stuEndTime.dwYear, pCurNumerStat->stuEndTime.dwMonth, 
			pCurNumerStat->stuEndTime.dwDay, pCurNumerStat->stuEndTime.dwHour,
			pCurNumerStat->stuEndTime.dwMinute, pCurNumerStat->stuEndTime.dwSecond);
		m_listResult.SetItemText(nRow, 3,cstrColText);
		cstrColText.Format("%d", pCurNumerStat->nEnteredSubTotal);
		m_listResult.SetItemText(nRow, 4, cstrColText);
		cstrColText.Format("%d", pCurNumerStat->nExitedSubtotal);
		m_listResult.SetItemText(nRow, 5, cstrColText);
	}
};

void CDlgQuery::OnBnClickedQueryStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空
	if (m_stuDoFindNumberStat_out.pstuNumberStat)
	{
		delete[]m_stuDoFindNumberStat_out.pstuNumberStat;
		m_stuDoFindNumberStat_out.pstuNumberStat = NULL;
	}
	memset(&m_stuDoFindNumberStat_out, 0, sizeof(m_stuDoFindNumberStat_out.pstuNumberStat));
	

	LONG lLogin = NULL;
	int nStatus = 0;
	BOOL bSuccess = FALSE;
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		lLogin = pMainDlg->GetLoginHandle();
	}
	if (NULL == lLogin)
	{
		MessageBox(ConvertString("Please Logon frist!"), ConvertString("Prompt"));
		return;
	}
	CString cstrTmp, strResult;
	int nIndex = 0;
	int nBeginNumber = 0;
	int nCount = 0;
	//设置查询参数
	NET_IN_FINDNUMBERSTAT stuFindNumberStat_in = {sizeof(NET_IN_FINDNUMBERSTAT)};
	NET_OUT_FINDNUMBERSTAT stuFindNumberStat_out = {0};
	NET_IN_DOFINDNUMBERSTAT stuDoFindNumberStat_in = {sizeof(NET_IN_DOFINDNUMBERSTAT)};
	
	stuFindNumberStat_in.nChannelID = m_cmbChannel.GetCurSel();
	stuFindNumberStat_in.nGranularityType = m_cmbTypes.GetCurSel();
	SYSTEMTIME sysTime = {0};
	m_dtpStartDate.GetTime(&sysTime);
	stuFindNumberStat_in.stStartTime.dwYear   =  sysTime.wYear;
	stuFindNumberStat_in.stStartTime.dwMonth  =  sysTime.wMonth;
	stuFindNumberStat_in.stStartTime.dwDay    =  sysTime.wDay;
	m_dtpStartTime.GetTime(&sysTime);
	stuFindNumberStat_in.stStartTime.dwHour   =  sysTime.wHour;
	stuFindNumberStat_in.stStartTime.dwMinute =  sysTime.wMinute;
	stuFindNumberStat_in.stStartTime.dwSecond =  sysTime.wSecond;
     
	m_dtpEndDate.GetTime(&sysTime);
	stuFindNumberStat_in.stEndTime.dwYear     = sysTime.wYear;
	stuFindNumberStat_in.stEndTime.dwMonth    = sysTime.wMonth;
	stuFindNumberStat_in.stEndTime.dwDay      = sysTime.wDay;
	m_dtpEndTime.GetTime(&sysTime);
	stuFindNumberStat_in.stEndTime.dwHour     = sysTime.wHour;
	stuFindNumberStat_in.stEndTime.dwMinute   = sysTime.wMinute;
	stuFindNumberStat_in.stEndTime.dwSecond   = sysTime.wSecond;
	stuFindNumberStat_in.nWaittime = 6000;
    
	LONG lFindNumberStat = CLIENT_StartFindNumberStat(lLogin, &stuFindNumberStat_in,&stuFindNumberStat_out);
	if (lFindNumberStat == NULL)
	{
		nStatus = 1;
		goto PRINT_EXIT;
	}
	m_editCount.GetWindowText(cstrTmp);
	nCount = atoi(cstrTmp.GetBuffer(0));
	if (nCount <= 0)
	{
		nStatus = 4;
		goto PRINT_EXIT;
	}
	stuDoFindNumberStat_in.nCount = nCount;
	stuDoFindNumberStat_in.nWaittime = 6000;
	m_editBegin.GetWindowText(cstrTmp);
	nBeginNumber = atoi(cstrTmp.GetBuffer(0));
	if (nBeginNumber > (int)stuFindNumberStat_out.dwTotalCount)
	{
		nStatus = 5;
		goto PRINT_EXIT;
	}
	stuDoFindNumberStat_in.nBeginNumber = nBeginNumber;
	memset(&m_stuDoFindNumberStat_out, 0 ,sizeof(m_stuDoFindNumberStat_out));
	m_stuDoFindNumberStat_out.dwSize = sizeof(m_stuDoFindNumberStat_out);
	try
	{
		m_stuDoFindNumberStat_out.pstuNumberStat = new DH_NUMBERSTAT[stuDoFindNumberStat_in.nCount];
	}
	catch (...)
	{
		nStatus = 2;
		goto PRINT_EXIT;
	}
	
	if (NULL== m_stuDoFindNumberStat_out.pstuNumberStat)
	{
		nStatus = 2;
		goto PRINT_EXIT;
	}
	for (nIndex= 0; nIndex < (int)stuDoFindNumberStat_in.nCount; nIndex++)
	{
		memset(m_stuDoFindNumberStat_out.pstuNumberStat+nIndex, 0, sizeof(DH_NUMBERSTAT));
		m_stuDoFindNumberStat_out.pstuNumberStat[nIndex].dwSize = sizeof(DH_NUMBERSTAT);
	}
	m_stuDoFindNumberStat_out.nBufferLen = stuDoFindNumberStat_in.nCount*sizeof(DH_NUMBERSTAT);
	bSuccess = CLIENT_DoFindNumberStat(lFindNumberStat, &stuDoFindNumberStat_in, &m_stuDoFindNumberStat_out);
	if ( bSuccess == -1 )
	{
		nStatus = 3;
		goto PRINT_EXIT;
	}
	ShowListResult(m_stuDoFindNumberStat_out);
	
	strResult = ConvertString("Result:");
	cstrTmp.Format("%d", m_stuDoFindNumberStat_out.nCount);
	strResult += cstrTmp;
	GetDlgItem(IDC_STATIC_SHOW_RESULT)->SetWindowText(strResult);
	nStatus = 0;
PRINT_EXIT:
	if (lFindNumberStat)
	{
		CLIENT_StopFindNumberStat(lFindNumberStat);
	}
	/*if (stuDoFindNumberStat_out.pstuNumberStat)
	{
		delete [] stuDoFindNumberStat_out.pstuNumberStat;
		stuDoFindNumberStat_out.pstuNumberStat = NULL;
	}*/
	switch( nStatus)
	{
	case 0:
		//MessageBox("查询成功...");
		break;
	case 1:
		MessageBox(ConvertString("Start query failed!"), ConvertString("Prompt"));
		break;
	case 2:
		MessageBox(ConvertString("Out Of Memory!"), ConvertString("Prompt"));
		break;
	case 3:
		MessageBox(ConvertString("Execute query failed!"), ConvertString("Prompt"));
		break;
	case 4:
		MessageBox(ConvertString("Query number should be greater than 0!"), ConvertString("Prompt"));
		break;
	case 5:
		MessageBox(ConvertString("Start number should be smaller than totall query number!"), ConvertString("Prompt"));
		break;
	}

	if (nStatus != 0)
	{
		//若查询失败，清空列表，重置上一页，下一页按钮
		ShowListResult(m_stuDoFindNumberStat_out);

		strResult = ConvertString("Query failed!");
		GetDlgItem(IDC_STATIC_SHOW_RESULT)->SetWindowText(strResult);
	}
}

void CDlgQuery::ResizeWnd()
{
	CRect rect;
	this->GetClientRect(rect);

	CRect rectListResult;
	m_listResult.GetClientRect(rectListResult);

	CRect rectFrame;
	rectFrame.left = 0;
	rectFrame.top = rectListResult.bottom+20;
	rectFrame.right = rect.right;
	rectFrame.bottom = rect.bottom -10;//rect.Height()-30-rectListResult.Height();
	m_dlgDrawFrame->MoveWindow(rectFrame);
	m_dlgDrawFrame->ShowWindow(SW_SHOWNORMAL);
	m_dlgDrawFrame->SetRectClient(rectFrame);

};
void CDlgQuery::OnBnClickedBtnPreview()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_dwIndexStart > 0 )
	{
		int nListCount = m_listResult.GetItemCount();
		m_dwIndexEnd = m_dwIndexStart -1 ;
		m_dwIndexStart -= 100;
		ShowListResultRange(m_stuDoFindNumberStat_out, m_dwIndexStart, m_dwIndexEnd-m_dwIndexStart+1);

		ShowPreNextEnable();
		Draw(m_stuDoFindNumberStat_out, m_dwIndexStart, m_dwIndexEnd-m_dwIndexStart+1);
	}
}

void CDlgQuery::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_dwIndexEnd +1 < m_stuDoFindNumberStat_out.nCount)
	{
		int nCount = m_stuDoFindNumberStat_out.nCount - m_dwIndexEnd-1;
		m_dwIndexStart = m_dwIndexEnd+1;
		m_dwIndexEnd += nCount<100?nCount:100;

		ShowListResultRange(m_stuDoFindNumberStat_out, m_dwIndexStart, m_dwIndexEnd - m_dwIndexStart +1);

		ShowPreNextEnable();
		Draw(m_stuDoFindNumberStat_out, m_dwIndexStart, m_dwIndexEnd-m_dwIndexStart+1);
	}
}


void CDlgQuery::Draw(NET_OUT_DOFINDNUMBERSTAT &FindNumber,int nIndexStart, int nCount)
{
	if (m_dlgDrawFrame)
	{
		m_dlgDrawFrame->InitData(FindNumber, nIndexStart, nCount, m_cmbTypes.GetCurSel());
		m_dlgDrawFrame->Invalidate();
	}
}


LRESULT CDlgQuery::OnSelectRecord(WPARAM wp, LPARAM lp)
{
	NET_TIME * ti = (NET_TIME*)lp;
	if (ti!=NULL)
	{
		CString strTimeStart;
		strTimeStart.Format("%04d-%02d-%02d %02d:%02d:%02d", 
			ti->dwYear, ti->dwMonth, ti->dwDay, ti->dwHour, ti->dwMinute, ti->dwSecond);

		m_listResult.SetFocus();
		int nCount = m_listResult.GetItemCount();
		for (int i = 0; i < nCount; ++i)
		{
			CString str = m_listResult.GetItemText(i, 2);
			if (str.CompareNoCase(strTimeStart) == 0)
			{
				m_listResult.EnsureVisible(i,FALSE);
				m_listResult.SetItemState(i,LVNI_SELECTED|LVIS_ACTIVATING,LVNI_SELECTED|LVIS_ACTIVATING);
			}
			else
			{
				m_listResult.SetItemState(i,0,LVNI_SELECTED|LVIS_ACTIVATING);
			}
		}
	}
	return S_OK;
};

void CDlgQuery::ShowPreNextEnable()
{
	if (m_dwIndexStart <= 0)
	{
		GetDlgItem(IDC_BTN_PREVIEW)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_PREVIEW)->EnableWindow(TRUE);
	}

	if (m_dwIndexEnd+1 == m_stuDoFindNumberStat_out.nCount)
	{
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(TRUE);
	}
};