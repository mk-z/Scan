// PlaybackByFile.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo3.h"
#include "PlaybackByFile.h"
#include "ClientDemo3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlaybackByFile dialog


CPlaybackByFile::CPlaybackByFile(CWnd* pParent /*=NULL*/)
	: CDialog(CPlaybackByFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlaybackByFile)
	m_timeFrom = 0;
	m_timeTo = 0;
	m_dateFrom = COleDateTime::GetCurrentTime();
	m_dateTo = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	m_hLoginID = 0;
	m_nTimer = 0;
	m_dwTotalSize = 0;
	m_dwCurValue = 0;
}


void CPlaybackByFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlaybackByFile)
	DDX_Control(pDX, IDC_COMBO_PLAYMODE, m_ctlPlayMode);
	DDX_Control(pDX, IDC_PROGRESS_BYFILE, m_ctlLoadPro);
	DDX_Control(pDX, IDC_LIST_QUERYINFO, m_ctlListInfo);
	DDX_Control(pDX, IDC_COMBO_QUERYTYPE, m_ctlQueryType);
	DDX_Control(pDX, IDC_COMBO_CHANNELBYFILE, m_ctlChannel);
	DDX_DateTimeCtrl(pDX, IDC_TIME_FROM, m_timeFrom);
	DDX_DateTimeCtrl(pDX, IDC_TIME_TO, m_timeTo);
	DDX_DateTimeCtrl(pDX, IDC_DATE_FROM, m_dateFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATE_TO, m_dateTo);
    DDX_Control(pDX, IDC_COMBO_STREAM, m_ctlStreamType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlaybackByFile, CDialog)
	//{{AFX_MSG_MAP(CPlaybackByFile)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_PLAYBYFILE, OnButtonPlaybyfile)
	ON_BN_CLICKED(IDC_BUTTON_CLEANLIST, OnButtonCleanlist)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOADBYFILE, OnButtonDownloadbyfile)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_QUERYINFO, OnDblclkListQueryinfo)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_FARTHESTRECORD, OnButtonFarthestrecord)
	ON_BN_CLICKED(IDC_BUTTON_LOCK, OnButtonLock)
	ON_BN_CLICKED(IDC_BUTTON_UNLOCK, OnButtonUnlock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlaybackByFile message handlers

//Search
void CPlaybackByFile::OnButtonQuery() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = UpdateData(TRUE);
	if(bValid && (0 != m_hLoginID))
	{
		//Recorded file information
		//NET_RECORDFILE_INFO netFileInfo[2000];
		int nMaxLen = 2000 * sizeof(NET_RECORDFILE_INFO);
		int nFileCount = 0;

        // Set search type first
        int nStreamIndex = m_ctlStreamType.GetCurSel();
        DWORD dwStream = m_ctlStreamType.GetItemData(nStreamIndex);
        BOOL bRet = CLIENT_SetDeviceMode(m_hLoginID, DH_RECORD_STREAM_TYPE, &dwStream);
        if (TRUE != bRet)
        {
            MessageBox(ConvertString("Set stream type failed"), ConvertString("Prompt"));
        }
		//Recorded file tpye 
		int nRecordFileType = 0;
		int nIndex = m_ctlQueryType.GetCurSel();	
		DWORD dwItemData = m_ctlQueryType.GetItemData(nIndex);
		char *pchCardid = NULL;

		if (EM_LISTALL == dwItemData)		//Search all recorded file
		{
			nRecordFileType = 0;
		}
		else if(EM_ALARMALL == dwItemData)	//Search alarm record 
		{
			nRecordFileType = 3;
		}
		else if(EM_PICTURE == dwItemData)	//Image search(Only special series supported)
		{
			nRecordFileType = 9;
		}
		else if(EM_CARD == dwItemData)		//Search image by Card number.(Only special series supported)
		{
			nRecordFileType = 8;
			CString str;
			GetDlgItemText(IDC_EDIT_CARD,str);
			if(str != "")
			{
				pchCardid = new char[20];
				GetDlgItemText(IDC_EDIT_CARD,pchCardid,str.GetLength());
			}
		}

		//Channel number
		int nChannelId = 0;
		nIndex = m_ctlChannel.GetCurSel();
		nChannelId = (int)m_ctlChannel.GetItemData(nIndex);
		//Time
		NET_TIME netTimeFrom = ConvertToDateTime(m_dateFrom,m_timeFrom);
		NET_TIME netTimeTo = ConvertToDateTime(m_dateTo,m_timeTo);
		
		//Search
		BOOL bSuccess = CLIENT_QueryRecordFile(m_hLoginID,nChannelId,nRecordFileType,
			&netTimeFrom,&netTimeTo,pchCardid,m_netFileInfo,nMaxLen,&nFileCount,5000,FALSE);
		if(pchCardid != NULL)
		{
			delete[] pchCardid;
		}
		if(bSuccess)
		{
			if(0 == nFileCount)
			{
				MessageBox(ConvertString("NO record!"), ConvertString("Prompt"));
			}
			else
			{
				//Insert the searched results into ListView
				AddRecordInfoToListView(m_netFileInfo,nFileCount);
			}
		}
		else
		{
            int nError = CLIENT_GetLastError();
            if (NET_NO_RECORD_FOUND == nError)
            {
                MessageBox(ConvertString("NO record!"), ConvertString("Prompt"));
            }
            else
            {
                MessageBox(ConvertString("Query failed!"), ConvertString("Prompt"));
            }
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

//Play
void CPlaybackByFile::OnButtonPlaybyfile() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_ctlListInfo.GetItemCount())
	{
		if(0 < m_ctlListInfo.GetSelectedCount())
		{
			int nIndex = m_ctlListInfo.GetSelectionMark();
			if(-1 != nIndex)
			{
				NET_RECORDFILE_INFO fileInfo = {0};
				fileInfo = m_netFileInfo[nIndex];
				//To get play mode
				nIndex = m_ctlPlayMode.GetCurSel();
				if(CB_ERR != nIndex)
				{
					PlayBackMode ePlayMode = (PlayBackMode)m_ctlPlayMode.GetItemData(nIndex);
					int nChannelId = 0;
					int nIndex = m_ctlChannel.GetCurSel();
					nChannelId = (int)m_ctlChannel.GetItemData(nIndex);
					if(ePlayMode == EM_SERVERMODE)
					{
						((CClientDemo3Dlg *)AfxGetMainWnd())->PlayBackByFileServerMode(fileInfo,nChannelId);
					}
					else
					{
						((CClientDemo3Dlg *)AfxGetMainWnd())->PlayBackByFile(fileInfo,nChannelId);
					}
				}
			}
		}
		else
		{
			MessageBox(ConvertString("Please select first!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("NO record!"), ConvertString("Prompt"));
	}
}

//Clear list
void CPlaybackByFile::OnButtonCleanlist() 
{
	// TODO: Add your control notification handler code here
	m_ctlListInfo.DeleteAllItems();
}

//Download
void CPlaybackByFile::OnButtonDownloadbyfile() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	GetDlgItemText(IDC_BUTTON_DOWNLOADBYFILE,strText);
	if(strText == "Download" || strText == ConvertString("Download"))
	{
		if(0 != m_ctlListInfo.GetItemCount())
		{
			if(0 < m_ctlListInfo.GetSelectedCount())
			{
				int nIndex = m_ctlListInfo.GetSelectionMark();
				if(-1 != nIndex)
				{
					NET_RECORDFILE_INFO fileInfo = {0};
					fileInfo = m_netFileInfo[nIndex];
					BOOL bSuccess = ((CClientDemo3Dlg *)AfxGetMainWnd())->DownLoadByFile(fileInfo,TRUE);
					if(bSuccess)
					{
						SetDlgItemText(IDC_BUTTON_DOWNLOADBYFILE, ConvertString("Stop"));
					}
				}
			}
			else
			{
				MessageBox(ConvertString("Please select first!"),ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("NO record!"),ConvertString("Prompt"));
		}
	}
	else
	{
		NET_RECORDFILE_INFO fileInfo = {0};
		BOOL bSuccess = ((CClientDemo3Dlg *)AfxGetMainWnd())->DownLoadByFile(fileInfo,FALSE);
		if(bSuccess)
		{
			SetDlgItemText(IDC_BUTTON_DOWNLOADBYFILE,ConvertString("Download"));
			m_dwTotalSize = 0;
			m_dwCurValue = 0;
			long hDownLoadFile = ((CClientDemo3Dlg *)AfxGetMainWnd())->m_pDownLoadFile;
			if(0 != hDownLoadFile)
			{
				CLIENT_StopDownload(hDownLoadFile);
				((CClientDemo3Dlg *)AfxGetMainWnd())->m_pDownLoadFile = 0;
			}
			m_ctlLoadPro.SetRange32(0,0);
			m_ctlLoadPro.SetPos(0);
			Invalidate();
		}
	}
}

BOOL CPlaybackByFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	int nIndex = m_ctlQueryType.AddString(ConvertString("All"));
	m_ctlQueryType.SetItemData(nIndex,EM_LISTALL);
	nIndex = m_ctlQueryType.AddString(ConvertString("Alarm"));
	m_ctlQueryType.SetItemData(nIndex,EM_ALARMALL);

	m_ctlQueryType.SetCurSel(0);

	InitListView();

	m_ctlStreamType.ResetContent();
	nIndex = m_ctlStreamType.AddString(ConvertString("AllStream"));
	m_ctlStreamType.SetItemData(nIndex,EM_BOTH_STREAM);
	nIndex = m_ctlStreamType.AddString(ConvertString("MainStream"));
	m_ctlStreamType.SetItemData(nIndex,EM_MAIN_STREAM);
    nIndex = m_ctlStreamType.AddString(ConvertString("ExtraStrean"));
    m_ctlStreamType.SetItemData(nIndex,EM_EXTRA_STREAM);
	m_ctlStreamType.SetCurSel(EM_BOTH_STREAM);

    m_ctlPlayMode.ResetContent();
    nIndex = m_ctlPlayMode.AddString(ConvertString("direct"));
    m_ctlPlayMode.SetItemData(nIndex,EM_DIRECTMODE);
    nIndex = m_ctlPlayMode.AddString(ConvertString("callback"));
    m_ctlPlayMode.SetItemData(nIndex,EM_SERVERMODE);
    m_ctlPlayMode.SetCurSel(0);


	//Set current time 
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

	m_ctlLoadPro.SetRange32(0,(int)(m_dwTotalSize/100));
	m_ctlLoadPro.SetPos(0);
    if (0 == m_nTimer)
    {
        m_nTimer = SetTimer(1, 500, NULL);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//Set channel dropdown menu 
void CPlaybackByFile::InitComboBox(int nChannel,long lLoginID)
{
	m_hLoginID = lLoginID;
	m_ctlListInfo.DeleteAllItems();

    SetControlButton(TRUE);
    //GetDlgItem(IDC_COMBO_CHANNELBYFILE)->EnableWindow(TRUE);
    //GetDlgItem(IDC_COMBO_CHANNELBYFILE)->EnableWindow(TRUE);

	int nIndex = 0;
	CString str;
	m_ctlChannel.ResetContent();
	for(int i=0;i<nChannel;i++)
	{
		str.Format("%d",i);
		nIndex = m_ctlChannel.AddString(str);
		m_ctlChannel.SetItemData(nIndex,i);
	}
	m_ctlChannel.SetCurSel(0);
}

//ListView initialization
void CPlaybackByFile::InitListView()
{
	m_ctlListInfo.SetExtendedStyle(m_ctlListInfo.GetExtendedStyle() | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlListInfo.InsertColumn(0,ConvertString("Index"),LVCFMT_LEFT,50,-1);
	m_ctlListInfo.InsertColumn(1,ConvertString("Record Type"),LVCFMT_LEFT,60,0);
	m_ctlListInfo.InsertColumn(2,ConvertString("file size(KB)"),LVCFMT_LEFT,60,1);
	m_ctlListInfo.InsertColumn(3, ConvertString("Frame Num"), LVCFMT_LEFT,80,2);
	m_ctlListInfo.InsertColumn(4,ConvertString("Start time"),LVCFMT_LEFT,100,3);
	m_ctlListInfo.InsertColumn(5,ConvertString("End time"),LVCFMT_LEFT,100,4);
	m_ctlListInfo.InsertColumn(6,ConvertString("Disk No. "),LVCFMT_LEFT,50,5);
	m_ctlListInfo.InsertColumn(7,ConvertString("Lock file"),LVCFMT_LEFT,80,6);

}

//Turn time format CTime to NET_TIME type
NET_TIME CPlaybackByFile::ConvertTime(CTime date,CTime time)
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

//Insert searched results into ListView
void CPlaybackByFile::AddRecordInfoToListView(LPNET_RECORDFILE_INFO pRecordFiles, int nFileCount)
{
	m_ctlListInfo.DeleteAllItems();
    CString strRecordType[] = {ConvertString("CommonRecord") , ConvertString("AlarmRecord") , 
        ConvertString("MotionRecord") , ConvertString("CardRecord") , ConvertString("PicRecord") , 
        ConvertString("UnknowRecord")};

	for(int i=0;i<nFileCount;i++)
	{
		NET_RECORDFILE_INFO netFileInfo = pRecordFiles[i];
        CString strGetType;
        if( netFileInfo.nRecordFileType <0 || netFileInfo.nRecordFileType > 4)
        {
            strGetType = strRecordType[5];
        }
        else
        {
            strGetType = strRecordType[netFileInfo.nRecordFileType];
        }

		CString strNum;
		strNum.Format("%d",i);
		CString strFileName;
		strFileName.Format("%s",netFileInfo.filename);
		CString strFileLength;
		strFileLength.Format("%d",netFileInfo.size);
		CString strStartTime;
		strStartTime.Format(ConvertString("%dyear %dmonth %dday  %d:%d:%d"),netFileInfo.starttime.dwYear,
			netFileInfo.starttime.dwMonth,netFileInfo.starttime.dwDay,netFileInfo.starttime.dwHour,
			netFileInfo.starttime.dwMinute,netFileInfo.starttime.dwSecond);
		CString strEndTime;
		strEndTime.Format(ConvertString("%dyear %dmonth %dday  %d:%d:%d"),netFileInfo.endtime.dwYear,
			netFileInfo.endtime.dwMonth,netFileInfo.endtime.dwDay,netFileInfo.endtime.dwHour,
			netFileInfo.endtime.dwMinute,netFileInfo.endtime.dwSecond);
		CString strDisk;
		strDisk.Format("%d",netFileInfo.driveno);
		CString strLockfile;
		if(netFileInfo.bImportantRecID)
		{
			strLockfile = ConvertString("Yes");
		}
		else
		{
			strLockfile = ConvertString("No");
		}

		CString strFrameNum;
		strFrameNum.Format("%d", netFileInfo.framenum);

		//≤Â»Î––
		int nIndex = m_ctlListInfo.GetItemCount();
		m_ctlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE,nIndex,strNum,0,LVIS_SELECTED,0,0);
		m_ctlListInfo.SetItemText(nIndex,1,strGetType);
		m_ctlListInfo.SetItemText(nIndex,2,strFileLength);
		m_ctlListInfo.SetItemText(nIndex,3,strFrameNum);
		m_ctlListInfo.SetItemText(nIndex,4,strStartTime);
		m_ctlListInfo.SetItemText(nIndex,5,strEndTime);
		m_ctlListInfo.SetItemText(nIndex,6,strDisk);
		m_ctlListInfo.SetItemText(nIndex,7,strLockfile);
	}
}

//Double click to play
void CPlaybackByFile::OnDblclkListQueryinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(0 != m_ctlListInfo.GetItemCount())
	{
		if(0 < m_ctlListInfo.GetSelectedCount())
		{
			int nIndex = m_ctlListInfo.GetSelectionMark();
			if(-1 != nIndex)
			{
				NET_RECORDFILE_INFO fileInfo = {0};
				fileInfo = m_netFileInfo[nIndex];
				//To get play mode
				nIndex = m_ctlPlayMode.GetCurSel();
				if(CB_ERR != nIndex)
				{
					PlayBackMode ePlayMode = (PlayBackMode)m_ctlPlayMode.GetItemData(nIndex);
					int nChannelId = 0;
					int nIndex = m_ctlChannel.GetCurSel();
					nChannelId = (int)m_ctlChannel.GetItemData(nIndex);
					if(ePlayMode == EM_SERVERMODE)
					{
						((CClientDemo3Dlg *)AfxGetMainWnd())->PlayBackByFileServerMode(fileInfo, nChannelId);
					}
					else
					{
						((CClientDemo3Dlg *)AfxGetMainWnd())->PlayBackByFile(fileInfo, nChannelId);
					}
				}
			}
		}
	}
	
	*pResult = 0;
}

void CPlaybackByFile::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == m_nTimer)
	{
		m_ctlLoadPro.SetRange32(0,(int)(m_dwTotalSize/100));
		m_ctlLoadPro.SetPos((int)(m_dwCurValue/100));
	}

	CDialog::OnTimer(nIDEvent);
}

void CPlaybackByFile::SetControlButton(BOOL bFlag)
{
    GetDlgItem(IDC_COMBO_CHANNELBYFILE)->EnableWindow(bFlag);
    GetDlgItem(IDC_COMBO_PLAYMODE)->EnableWindow(bFlag);
    GetDlgItem(IDC_COMBO_QUERYTYPE)->EnableWindow(bFlag);
    GetDlgItem(IDC_DATE_FROM)->EnableWindow(bFlag);
    GetDlgItem(IDC_TIME_FROM)->EnableWindow(bFlag);
    GetDlgItem(IDC_DATE_TO)->EnableWindow(bFlag);
    GetDlgItem(IDC_TIME_TO)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_QUERY)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_PLAYBYFILE)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_CLEANLIST)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_FARTHESTRECORD)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_DOWNLOADBYFILE)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_LOCK)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_UNLOCK)->EnableWindow(bFlag);
    GetDlgItem(IDC_COMBO_STREAM)->EnableWindow(bFlag);

}

//Clear after log off 
void CPlaybackByFile::Clean()
{
	SetDlgItemText(IDC_BUTTON_DOWNLOADBYFILE, ConvertString("Download"));
	m_dwTotalSize = 0;
	m_dwCurValue = 0;
    SetControlButton(FALSE);
}

NET_TIME CPlaybackByFile::ConvertToDateTime(const COleDateTime &date, const CTime &time)
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

void CPlaybackByFile::OnButtonFarthestrecord() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = UpdateData(TRUE);
	if(bValid && (0 != m_hLoginID))
	{
		//Recorded file information
		//NET_RECORDFILE_INFO netFileInfo[2000];
		int nMaxLen = 1 * sizeof(NET_RECORDFILE_INFO);
		int nFileCount = 0;
		//Recorded file tpye 
		int nRecordFileType = 0;
		int nIndex = m_ctlQueryType.GetCurSel();	
		DWORD dwItemData = m_ctlQueryType.GetItemData(nIndex);
		char *pchCardid = NULL;

		if (EM_LISTALL == dwItemData)		//Search all recorded file
		{
			nRecordFileType = 0;
		}
		else if(EM_ALARMALL == dwItemData)	//Search alarm record 
		{
			nRecordFileType = 3;
		}
		else if(EM_PICTURE == dwItemData)	//Image search(Only special series supported)
		{
			nRecordFileType = 9;
		}
		else if(EM_CARD == dwItemData)		//Search image by Card number.(Only special series supported)
		{
			nRecordFileType = 8;
			CString str;
			GetDlgItemText(IDC_EDIT_CARD,str);
			if(str != "")
			{
				pchCardid = new char[20];
				GetDlgItemText(IDC_EDIT_CARD,pchCardid,str.GetLength());
			}
		}

		//Channel number
		int nChannelId = 0;
		nIndex = m_ctlChannel.GetCurSel();
		nChannelId = (int)m_ctlChannel.GetItemData(nIndex);
		//Time
		NET_TIME netTimeFrom = {0};
		NET_TIME netTimeTo = {0};
		netTimeFrom.dwYear = 2000;
		netTimeFrom.dwMonth = 1;
		netTimeFrom.dwDay = 1;
		netTimeTo.dwYear = 2099;
		netTimeTo.dwMonth = 12;
		netTimeTo.dwDay = 31;
		
		//Search
		BOOL bSuccess = CLIENT_QueryRecordFile(m_hLoginID,nChannelId,nRecordFileType,
			&netTimeFrom,&netTimeTo,pchCardid,m_netFileInfo,nMaxLen,&nFileCount,5000,FALSE);
		if(pchCardid != NULL)
		{
			delete[] pchCardid;
		}
		if(bSuccess)
		{
			if(0 == nFileCount)
			{
				MessageBox(ConvertString("NO record!"), ConvertString("Prompt"));
			}
			else
			{
				//Insert the searched results into ListView
				AddRecordInfoToListView(m_netFileInfo,nFileCount);
			}
		}
		else
		{
			MessageBox(ConvertString("Query failed!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

void CPlaybackByFile::OnButtonLock() 
{
	// TODO: Add your control notification handler code here
	if(m_hLoginID == 0)
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
		return;
	}
	int nIndex = m_ctlListInfo.GetNextItem(-1,LVNI_SELECTED);
	BOOL bSuccess = FALSE;
	if((nIndex != -1))
	{
		m_netFileInfo[nIndex].bImportantRecID = 1;
		bSuccess = CLIENT_ControlDevice(m_hLoginID,DH_MARK_IMPORTANT_RECORD,&m_netFileInfo[nIndex]);
		if(bSuccess)
		{
			OnButtonQuery();
			if(m_ctlListInfo.GetItemCount() > 0)
			{
				m_ctlListInfo.EnsureVisible(nIndex,FALSE);
				m_ctlListInfo.SetItemState(nIndex,LVNI_SELECTED|LVIS_ACTIVATING,LVNI_SELECTED|LVIS_ACTIVATING);
				if(m_netFileInfo[nIndex].bImportantRecID == 1)
				{
					MessageBox(ConvertString("File lock success!"));
					return;
				}
			}
		}
		MessageBox(ConvertString("File lock fail!"));
	}
	else
	{
		MessageBox(ConvertString("Please choose the file first!"));
	}
}

void CPlaybackByFile::OnButtonUnlock() 
{
	// TODO: Add your control notification handler code here
	if(m_hLoginID == 0)
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
		return;
	}
	int nIndex = m_ctlListInfo.GetNextItem(-1,LVNI_SELECTED);
	BOOL bSuccess = FALSE;
	if(nIndex != -1)
	{
		m_netFileInfo[nIndex].bImportantRecID = 0;
		bSuccess = CLIENT_ControlDevice(m_hLoginID,DH_MARK_IMPORTANT_RECORD,&m_netFileInfo[nIndex]);
		if(bSuccess)
		{
			OnButtonQuery();
			if(m_ctlListInfo.GetItemCount() > 0)
			{
				m_ctlListInfo.EnsureVisible(nIndex,FALSE);
				m_ctlListInfo.SetItemState(nIndex,LVNI_SELECTED|LVIS_ACTIVATING,LVNI_SELECTED|LVIS_ACTIVATING);
				if(m_netFileInfo[nIndex].bImportantRecID == 0)
				{
					MessageBox(ConvertString("File unlock success!"));
					return;
				}
			}
		}
		MessageBox(ConvertString("File unlock fail!"));
	}	
	else
	{
		MessageBox(ConvertString("Please choose the file first!"));
	}
}
