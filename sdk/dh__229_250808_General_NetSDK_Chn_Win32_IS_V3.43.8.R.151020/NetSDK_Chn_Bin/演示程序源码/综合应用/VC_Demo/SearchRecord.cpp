 // SearchRecord.cpp : implementation file
//

#include "StdAfx.h"
#include "NetSDKDemo.h"
#include "SearchRecord.h"
#include "NetSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ISQUERYTYPE2 0  //是否采用单记录查询模式
/////////////////////////////////////////////////////////////////////////////
// CSearchRecord dialog
CPtrList  *g_ptrfilelist;
CFileListProtector fl(&g_ptrfilelist);

CSearchRecord::CSearchRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchRecord::IDD, pParent)
{
	m_downloadtotal = 0;
	m_downloadsize = 0;
	m_playCount = 0;
	m_playfile = 0;
	m_playCount = 0;
	memset(m_playList, 0, DH_MAX_CHANNUM*sizeof(FileInfoNode));
	//{{AFX_DATA_INIT(CSearchRecord)
	m_cardinput = _T("");
	m_channelsel = 1;
	m_enddate = 0;
	m_endtime = 0;
	m_startdate = 0;
	m_starttime = 0;
	//}}AFX_DATA_INIT
}


void CSearchRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchRecord)
	DDX_Control(pDX, IDC_SCH_RESULTLIST, m_resultlist);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_download_pos);
	DDX_Control(pDX, IDC_SCH_TYPE, m_sch_type);
	DDX_Control(pDX, IDC_SCH_DEVICESEL, m_devicesel);
	DDX_Text(pDX, IDC_SCH_CARDINPUT, m_cardinput);
	DDX_Text(pDX, IDC_SCH_CHANNELSEL, m_channelsel);
	DDX_DateTimeCtrl(pDX, IDC_SCH_ENDDATE, m_enddate);
	DDX_DateTimeCtrl(pDX, IDC_SCH_ENDTIME, m_endtime);
	DDX_DateTimeCtrl(pDX, IDC_SCH_STARTDATE, m_startdate);
	DDX_DateTimeCtrl(pDX, IDC_SCH_STARTTIME, m_starttime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchRecord, CDialog)
	//{{AFX_MSG_MAP(CSearchRecord)
	ON_BN_CLICKED(IDC_SCH_STARTSEARCH, OnSchStartsearch)
	ON_BN_CLICKED(IDC_SCH_DOWNLOAD, OnSchDownload)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SCH_PLAYBACK, OnPlayback)
	ON_BN_CLICKED(IDC__SCH_CLEAR_LIST, OnSchClearList)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_SCH_RESULTLIST, OnDblclkSchResultlist)
	ON_BN_CLICKED(IDC_ADD_TO_LIST, OnAddToList)
	ON_CBN_SELCHANGE(IDC_SCH_TYPE, OnSelchangeSchType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSearchRecord message handlers

void CSearchRecord::AddOneFileToList(NET_RECORDFILE_INFO *pfileinfo, int index)
{
	CString nStr;
	CString strST;
	CString strET;
	CTime stime, etime;
	POSITION nPos;
	
	FileInfoNode *plistinfo = new FileInfoNode;
	strST = g_TimeOutString(&pfileinfo->starttime);
	strET = g_TimeOutString(&pfileinfo->endtime);	

	m_resultlist.InsertItem(index, pfileinfo->filename);
	m_resultlist.SetItemText(index, 1, strST);
	m_resultlist.SetItemText(index, 2, strET);
	nStr.Format("%d", pfileinfo->size);
	m_resultlist.SetItemText(index, 3, nStr.GetBuffer(0));	

	memcpy(&plistinfo->fileinfo, pfileinfo, sizeof(NET_RECORDFILE_INFO));
	plistinfo->pDevice = (DeviceNode *)m_devicesel.GetItemData(m_devicesel.GetCurSel());
	nPos = g_ptrfilelist->AddTail(plistinfo);
	m_resultlist.SetItemData(index, (DWORD)plistinfo);	
}

void CSearchRecord::AddFileListInfo( NET_RECORDFILE_INFO *pfileinfo, int iMaxNum)
{
	for(int i = 0; i < iMaxNum; i++)
	{
		AddOneFileToList(&pfileinfo[i], i);
	}

}
void CSearchRecord::OnSchStartsearch() 
{
	NET_RECORDFILE_INFO ifileinfo[2000];
	DeviceNode *pInfo;
	int nSchType;
	CString	strCard = "";
	SYSTEMTIME systime;
	NET_TIME stime, etime;
	int nMaxNum;
	int nMaxLen = 2000 * sizeof(NET_RECORDFILE_INFO);
	
	if(!UpdateData(true))
	{
		return;
	}
	if(m_devicesel.GetCount() <= 0 || m_devicesel.GetCurSel() < 0)
	{
		MessageBox(ConvertString(MSG_SCHRECORD_NODEVICE), ConvertString(MSG_SCHRECORD_CHOOSEDEVICE));
		return;
	}
	if(m_channelsel <= 0/* || m_channelsel > DH_MAX_CHANNUM*/)
	{
		MessageBox(ConvertString(MSG_SCHRECORD_CHLNO_INVALID), ConvertString(MSG_SCHRECORD_CHLNO));	
		return;
	}

	nSchType = m_sch_type.GetCurSel();
	if (2 == nSchType) 
	{
		//卡号查询，查询类型为4
		nSchType = 4;
		GetDlgItemText(IDC_SCH_CARDINPUT, strCard);
	}

	CTime time = CTime(m_startdate.GetYear(),m_startdate.GetMonth(),m_startdate.GetDay(),
		m_starttime.GetHour(), m_starttime.GetMinute(), m_starttime.GetSecond());
	if(!time.GetAsSystemTime(systime) || !time.GetAsSystemTime(systime))
	{
		MessageBox(ConvertString(MSG_SCHRECORD_TIMEINPUT_ERR), ConvertString(MSG_SCHRECORD_TIMEINPUT));
		return;
	}
	g_systimetoprivatetime(&systime,&stime);
	
	time = CTime(m_enddate.GetYear(),m_enddate.GetMonth(),m_enddate.GetDay(),
		m_endtime.GetHour(), m_endtime.GetMinute(), m_endtime.GetSecond());
	if(!time.GetAsSystemTime(systime) || !time.GetAsSystemTime(systime))
	{
		MessageBox(ConvertString(MSG_SCHRECORD_TIMEINPUT_ERR), ConvertString(MSG_SCHRECORD_TIMEINPUT));
		return;
	}
	g_systimetoprivatetime(&systime,&etime);

	pInfo = (DeviceNode *)m_devicesel.GetItemData(m_devicesel.GetCurSel());
/*查询接口有两种实现方式，这里使用第一种*/
	if (!ISQUERYTYPE2) 
	{
		LONG ret = CLIENT_QueryRecordFile(pInfo->LoginID, 
								m_channelsel -1, 
								nSchType, 
								&stime,
								&etime,
								strCard.GetBuffer(0), 
								ifileinfo,
								nMaxLen,
                                &nMaxNum,
								5000/*,true*/);

		if(!ret)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			MessageBox(ConvertString(MSG_SCHRECORD_QUERYFAILED));
			return;
		}
		if(nMaxNum == 0)
		{
			MessageBox(ConvertString(MSG_SCHRECORD_NORECORD));
			return;
			
		}
		for(int i = 0; i < nMaxNum; i++)
		{
			sprintf(ifileinfo[i].filename,"%s  channel%02d" ,pInfo->Name, m_channelsel );
		}
		OnSchClearList();
		AddFileListInfo(ifileinfo, nMaxNum);
	}
		//第二种接口实现
	else 
	{
		LONG lHandle;
		lHandle = CLIENT_FindFile(pInfo->LoginID, 
								m_channelsel -1, 
								nSchType,
								strCard.GetBuffer(0), 
								&stime,
								&etime,
								false,
								2000);
		
		if (!lHandle)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			MessageBox(ConvertString(MSG_SCHRECORD_QUERYFAILED));
			return;
		}
		
		NET_RECORDFILE_INFO *ptempfileinfo = new(NET_RECORDFILE_INFO);
		BOOL ret;
		ret = CLIENT_FindNextFile(lHandle, ptempfileinfo);
		if (!ret)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			MessageBox(ConvertString(MSG_SCHRECORD_NORECORD));
			return;
		}

		//刷新列表
		OnSchClearList();
		int i = 0;
		while (ret == 1) {
			sprintf(ptempfileinfo->filename,"%s  channel%02d" ,pInfo->Name, m_channelsel);
			AddOneFileToList(ptempfileinfo, i);
			i++;			
			ret = CLIENT_FindNextFile(lHandle, ptempfileinfo);
			if (!ret)
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			}
		}
	}
	
}


int InitComboxSRCallback(const DeviceNode& node, DWORD dwUser)
{
	CSearchRecord* pThis = (CSearchRecord*)dwUser;
	if(!pThis)
	{
		return 1;
	}

	return pThis->InitComboxCallback_Imp(node);
}

int CSearchRecord::InitComboxCallback_Imp(const DeviceNode& node)
{
	//设备显示
	CString strDev;	

	strDev.Format(" %s ",node.Name);
	int nIndex = m_devicesel.GetCount();
	m_devicesel.InsertString(nIndex,strDev);
	m_devicesel.SetItemData(nIndex, (DWORD)(&node)); //设置保存当前设备指针值

	return 0;
}

BOOL CSearchRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	//DeviceNode *nDev;
	//CString strDev;	
	//POSITION nPos;

	m_devicesel.Clear();

	CDevMgr::GetDevMgr().For_EachDev(InitComboxSRCallback, (DWORD)this);

	/*
	//初始化可选择的设备
	nPos = g_ptrdevicelist->GetHeadPosition();

	for(int i = 0; i < g_ptrdevicelist->GetCount(); i ++ )
	{
		//设备显示格式
		nDev = (DeviceNode *)g_ptrdevicelist->GetNext(nPos);
		
		//设备显示
		strDev.Format(" %s ",nDev->Name);
		m_devicesel.InsertString(i,strDev);
		m_devicesel.SetItemData(i, (DWORD)nDev); //设置保存当前设备指针值
	}
	*/
	if (m_devicesel.GetCount() > 0) 
	{
		m_devicesel.SetCurSel(0);
	}

	//初始化其他控件
	m_sch_type.Clear();
	m_sch_type.InsertString(0, ConvertString(MSG_SCHRECORD_QUERYTYPE_LIST));
	m_sch_type.InsertString(1, ConvertString(MSG_SCHRECORD_QUERYTYPE_ALARM));
	m_sch_type.InsertString(2, ConvertString(MSG_SCHRECORD_QUERYTYPE_CARD));
	m_sch_type.SetCurSel(0);

	CTime cur_time = CTime ::GetCurrentTime();
	CTime time = CTime(cur_time.GetYear(),cur_time.GetMonth(), cur_time.GetDay(),
		cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
	m_enddate = time;
	m_endtime = time;
	m_startdate = time;
	m_starttime = time;

	m_pdownloadfile = NULL;	
	m_download_pos.SetRange(0,100);

	m_resultlist.SetExtendedStyle
		(m_resultlist.GetExtendedStyle()|LVS_EX_FULLROWSELECT);

	m_resultlist.InsertColumn(0, ConvertString(MSG_SCHRECORD_DVC_AND_CHL), LVCFMT_LEFT, 160, 0);
	m_resultlist.InsertColumn(1, ConvertString(MSG_SCHRECORD_STARTTIME), LVCFMT_LEFT, 160, 1);
	m_resultlist.InsertColumn(2, ConvertString(MSG_SCHRECORD_ENDTIME), LVCFMT_LEFT, 160, 2);
	m_resultlist.InsertColumn(3, ConvertString(MSG_SCHRECORD_SIZE), LVCFMT_LEFT, 160, 3);
	
	UpdataResultList();
	UpdateData(FALSE);

	return TRUE;
}

//主要用来处理进度条的问题，目前只支持一个文件的下载
void CALLBACK DownLoadPos(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, LDWORD dwUser)
{
	CSearchRecord * dlg = (CSearchRecord *)dwUser;
	
//	char tmp[100] = {0};
//	sprintf(tmp, "new imcome size: %d, total: %d\n", dwDownLoadSize, dwTotalSize);
//	OutputDebugString(tmp);
	
	dlg->UpdateDownloadPos(lPlayHandle, dwTotalSize, dwDownLoadSize);
}

//更新下载进度
void CSearchRecord::UpdateDownloadPos(LONG iHandle, DWORD dwTotal, DWORD dwDownload)
{
	if(m_pdownloadfile != iHandle)
	{
		MessageBox(ConvertString(MSG_SCHRECORD_DOWNLORD_CB_ERR));
		return;
	}
	m_downloadtotal = dwTotal;
	m_downloadsize = dwDownload;

	CString nstr;
	
	nstr.Format("%d / %d",dwDownload, dwTotal);
	GetDlgItem(IDC_EDIT1)->SetWindowText(nstr);
	if(-1 == m_downloadsize/* || m_downloadsize >= m_downloadtotal*/)
	{
		MessageBox(ConvertString(MSG_SCHRECORD_DOWNLOAD_FIN));
		if (m_pdownloadfile)
		{
			BOOL nRet = CLIENT_StopDownload(m_pdownloadfile);
			if (!nRet)
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			}
			m_pdownloadfile = NULL;	
		}
		((CButton *)GetDlgItem(IDC_SCH_DOWNLOAD))->SetWindowText(ConvertString(MSG_SCHRECORD_DOWNLOAD));
		GetDlgItem(IDC_SCH_PLAYBACK)->EnableWindow(TRUE);
	}
	else if (-2 == m_downloadsize)
	{
		MessageBox("not enough space in disk!");
		if (m_pdownloadfile)
		{
			BOOL nRet = CLIENT_StopDownload(m_pdownloadfile);
			if (!nRet)
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			}
			m_pdownloadfile = NULL;	
		}
		((CButton *)GetDlgItem(IDC_SCH_DOWNLOAD))->SetWindowText(ConvertString(MSG_SCHRECORD_DOWNLOAD));
		GetDlgItem(IDC_SCH_PLAYBACK)->EnableWindow(TRUE);
	}
}

void CSearchRecord::OnSchDownload() 
{
	FileInfoNode *plistinfo;

	if(m_pdownloadfile)
	{
		BOOL stopret = CLIENT_StopDownload(m_pdownloadfile);
		if (!stopret) 
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			MessageBox(ConvertString(MSG_SCHRECORD_STOPDLFAILED));
		}
		else
		{
			MessageBox(ConvertString(MSG_SCHRECORD_CANCELED));
			m_pdownloadfile = NULL;
			GetDlgItem(IDC_SCH_PLAYBACK)->EnableWindow(TRUE);
			((CButton *)GetDlgItem(IDC_SCH_DOWNLOAD))->SetWindowText(ConvertString(MSG_SCHRECORD_DOWNLOAD));
		}
		m_downloadtotal = 0;
		m_downloadsize = 0;
		return;
	}
	if(m_resultlist.GetItemCount() == 0 || m_resultlist.GetSelectionMark() < 0)
	{
		MessageBox(ConvertString(MSG_SCHRECORD_DOWNLOADFILE_SEL),  ConvertString(MSG_SCHRECORD_DOWNLOAD));
		return;
	}

	plistinfo = (FileInfoNode *)m_resultlist.GetItemData(m_resultlist.GetSelectionMark());

	//从resultlist中取得设备position，然后通过此值取得设备id
	//更改为直接获取设备信息指针
	LONG nDeviceId = plistinfo->pDevice->LoginID;

	CFileDialog dlg(FALSE,"*.dav","download.dav",OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
			"All File(*.dav)|*.*||",this);
	if(dlg.DoModal() != IDOK)
	{
		return;		
	}
	CString strName = dlg.GetPathName();

	m_pdownloadfile = CLIENT_DownloadByRecordFile(nDeviceId, &plistinfo->fileinfo, 
                                     strName.GetBuffer(0),DownLoadPos, (DWORD)this);

	if(m_pdownloadfile)
	{
		((CButton *)GetDlgItem(IDC_SCH_DOWNLOAD))->SetWindowText(ConvertString(MSG_SCHRECORD_CANCELDOWNLOAD));
		GetDlgItem(IDC_SCH_PLAYBACK)->EnableWindow(FALSE);
		SetTimer((UINT)this, 1000,NULL);			
	}
	else
	{
		((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		GetDlgItem(IDC_SCH_PLAYBACK)->EnableWindow(TRUE);
		MessageBox(ConvertString(MSG_SCHRECORD_STARTDLFAILED));
	}
}

void CSearchRecord::OnClose() 
{
	if(m_pdownloadfile)
	{
		BOOL nRet = CLIENT_StopDownload(m_pdownloadfile);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		m_pdownloadfile = NULL;
	}
	m_downloadtotal = 0;
	m_downloadsize = 0;
	KillTimer((int)this);
	CDialog::OnClose();
}

void CSearchRecord::OnPlayback() 
{
	if(m_resultlist.GetItemCount() == 0 || m_resultlist.GetSelectionMark() < 0)
	{
		MessageBox(ConvertString(MSG_SCHRECORD_PLAYFILE_SEL),  ConvertString(MSG_SCHRECORD_PLAY));
		return;
	}

	m_playfile = (FileInfoNode *)m_resultlist.GetItemData(m_resultlist.GetSelectionMark());

	CDialog::OnOK();	
}

void CSearchRecord::OnSchClearList() 
{
	POSITION nPos;
	FileInfoNode *pInfo;


	nPos = g_ptrfilelist->GetHeadPosition();
	for(int i = 0; i < g_ptrfilelist->GetCount(); i ++ )
	{
		pInfo = (FileInfoNode *)g_ptrfilelist->GetNext(nPos);
		delete pInfo;
	}
	g_ptrfilelist->RemoveAll();

	m_resultlist.DeleteAllItems();
}

void CSearchRecord::UpdataResultList()
{
	CString nStr;
	CString strST;
	CString strET;
	CTime stime, etime;

	FileInfoNode *pInfo ;

	m_resultlist.DeleteAllItems();
	POSITION nPos = g_ptrfilelist->GetHeadPosition();
	for(int i = 0; i < g_ptrfilelist->GetCount(); i++)
	{
		pInfo = (FileInfoNode *)g_ptrfilelist->GetNext(nPos);
		strST = g_TimeOutString(&pInfo->fileinfo.starttime );
		strET = g_TimeOutString(&pInfo->fileinfo.endtime );

		m_resultlist.InsertItem(i, pInfo->fileinfo.filename);
		m_resultlist.SetItemText(i, 1, strST);
		m_resultlist.SetItemText(i, 2, strET);
		nStr.Format("%d",pInfo->fileinfo.size);
		m_resultlist.SetItemText(i, 3, nStr.GetBuffer(0));

		m_resultlist.SetItemData(i, (DWORD)pInfo);
	}
	
}

void CSearchRecord::OnTimer(UINT_PTR nIDEvent) 
{
	OnButton1();

	if(m_pdownloadfile && m_downloadtotal)
	{
		m_download_pos.SetPos(m_downloadsize * 100/m_downloadtotal);
	}
	CDialog::OnTimer(nIDEvent);
}

void CSearchRecord::OnButton1() 
{
	int total, cur;
	total = 0;
	cur = 0;
	BOOL bret = CLIENT_GetDownloadPos(m_pdownloadfile, &total, &cur);
	if (bret)
	{
		char tmp[100] = {0};
		sprintf(tmp, "get download pos= %d, %d \n", total, cur);
		int o = 0;
		return;
	}
	else if(!bret)
	{
		((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
	}
}

void CSearchRecord::OnDblclkSchResultlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnPlayback();
	
	*pResult = 0;
}

void CSearchRecord::OnAddToList() 
{
	if(m_resultlist.GetItemCount() == 0 || m_resultlist.GetSelectionMark() < 0)
	{
		MessageBox(ConvertString(MSG_SCHRECORD_PLAYFILE_SEL), ConvertString(MSG_SCHRECORD_PLAY));
		return;
	}

	FileInfoNode *tmpNode = (FileInfoNode *)m_resultlist.GetItemData(m_resultlist.GetSelectionMark());
	if (!tmpNode)
	{
		return;
	}
	memcpy(&m_playList[m_playCount], tmpNode, sizeof(FileInfoNode));
	m_playCount++;
}

void CSearchRecord::OnSelchangeSchType() 
{
	if (m_sch_type.GetCurSel() == 2)
	{
		GetDlgItem(IDC_SCH_CARDINPUT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_SCH_CARDINPUT)->EnableWindow(FALSE);
	}
}
