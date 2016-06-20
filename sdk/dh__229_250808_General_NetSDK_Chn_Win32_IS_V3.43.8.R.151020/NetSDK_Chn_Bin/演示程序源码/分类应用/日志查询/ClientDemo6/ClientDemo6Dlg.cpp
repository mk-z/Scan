// ClientDemo6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo6.h"
#include "ClientDemo6Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEMO_SDK_WAITTIME 10000 
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo6Dlg dialog

CClientDemo6Dlg::CClientDemo6Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDemo6Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDemo6Dlg)
	m_nPort = 37777;
	m_strUserName = _T("admin");
	m_strPwd = _T("admin");
	m_timeBegin = 0;
	m_timeEnd = 0;
	m_dataBegin = COleDateTime::GetCurrentTime();;
	m_dataEnd = COleDateTime::GetCurrentTime();;
	m_nPageLine = 0;
	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_LoginID = 0;
}

void CClientDemo6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDemo6Dlg)
	DDX_Control(pDX, IDC_LIST_RESULT, m_ctlQueryResult);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ctlQueryType);
	DDX_Control(pDX, IDC_IPADDRESS_DVRIP, m_ctlDvrIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_DVRPWD, m_strPwd);
	DDX_Text(pDX, IDC_EDIT_PAGELINES, m_nPageLine);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTDAY,  m_dataBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTTIME, m_timeBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDDAY, m_dataEnd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDTIME, m_timeEnd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDemo6Dlg, CDialog)
	//{{AFX_MSG_MAP(CClientDemo6Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_QUERYXML, OnButtonQueryxml)
	ON_BN_CLICKED(IDC_BUTTON_PREPAGE, OnButtonPrePage)
	ON_BN_CLICKED(IDC_BUTTON_NEXTPAGE, OnButtonNextPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo6Dlg message handlers

BOOL CClientDemo6Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ctlDvrIP.SetAddress(171,35,0,189);
	InitListView();
		
	m_ctlQueryType.ResetContent();
	int nIndex = m_ctlQueryType.AddString(ConvertString("all log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_ALL);
	nIndex = m_ctlQueryType.AddString(ConvertString("system log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_SYSTEM);
	nIndex = m_ctlQueryType.AddString(ConvertString("config log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_CONFIG);
	nIndex = m_ctlQueryType.AddString(ConvertString("storage log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_STORAGE);
	nIndex = m_ctlQueryType.AddString(ConvertString("alarm log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_ALARM);
	nIndex = m_ctlQueryType.AddString(ConvertString("record log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_RECORD);
	nIndex = m_ctlQueryType.AddString(ConvertString("accounts log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_ACCOUNT);
	nIndex = m_ctlQueryType.AddString(ConvertString("clean log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_CLEAR);
	nIndex = m_ctlQueryType.AddString(ConvertString("callback log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_PLAYBACK);
	nIndex = m_ctlQueryType.AddString(ConvertString("manager log"));
	m_ctlQueryType.SetItemData(nIndex,DHLOG_MANAGER);
	m_ctlQueryType.SetCurSel(0);
	
	InitNetSDK();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDemo6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDemo6Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDemo6Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDemo6Dlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{
		int err=0;
		char *pchDVRIP;
		CString strDvrIP = GetDvrIP();
		pchDVRIP = (LPSTR)(LPCSTR)strDvrIP;
		WORD wDVRPort=(WORD)m_nPort;
		char *pchUserName=(LPSTR)(LPCSTR)m_strUserName;
		char *pchPassword=(LPSTR)(LPCSTR)m_strPwd;
		NET_DEVICEINFO deviceInfo;

		LLONG lRet = CLIENT_Login(pchDVRIP,wDVRPort,pchUserName,pchPassword,&deviceInfo,&err);
		if(0 == lRet)
		{
			m_LoginID = 0;
			MessageBox(ConvertString("Login failed!"), ConvertString("Prompt"));
		}
		else
		{
			m_LoginID = lRet;
			GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_QUERY)->EnableWindow(TRUE);

			//tell the device's log style
			memset(&m_stuEnable, 0, sizeof(DH_DEV_ENABLE_INFO));
			int nRetLen = 0;
			BOOL bRet = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_DEVALL_INFO, (char*)&m_stuEnable, sizeof(DH_DEV_ENABLE_INFO), &nRetLen, DEMO_SDK_WAITTIME);
		
			if (!bRet)
			{
				MessageBox(ConvertString("Get device cap failed!"), ConvertString("Prompt"));
			}

			if (m_stuEnable.IsFucEnable[EN_LOG] != 0)
			{
				m_nPageLine = 100;
				CTimeSpan timeSpan(1,0,0,0);
				CTime curTime = CTime::GetCurrentTime();
				CTime yesterday = curTime - timeSpan;
				m_dataBegin.SetDateTime(yesterday.GetYear(), yesterday.GetMonth(), yesterday.GetDay(), 
		yesterday.GetHour(), yesterday.GetMinute(), yesterday.GetSecond());
				m_timeBegin = yesterday;
				m_dataEnd.SetDateTime(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), 
		curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
				m_timeEnd = curTime;
				UpdateData(FALSE);

				GetDlgItem(IDC_DATETIMEPICKER_STARTDAY)->EnableWindow(TRUE);
				GetDlgItem(IDC_DATETIMEPICKER_STARTTIME)->EnableWindow(TRUE);
				GetDlgItem(IDC_DATETIMEPICKER_ENDDAY)->EnableWindow(TRUE);
				GetDlgItem(IDC_DATETIMEPICKER_ENDTIME)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT_PAGELINES)->EnableWindow(TRUE);
			}
		}
	}
}

void CClientDemo6Dlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	m_ctlQueryResult.DeleteAllItems();

	BOOL bRet = CLIENT_Logout(m_LoginID);
	if(bRet)
	{
		m_LoginID=0;
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_QUERY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_STARTDAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_STARTTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_ENDDAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_ENDTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PAGELINES)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PREPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_NEXTPAGE)->EnableWindow(FALSE);
	}
	else
	{
		MessageBox(ConvertString("Logout failed!"), ConvertString("Prompt"));
	}
}

void CClientDemo6Dlg::InitNetSDK()
{
	BOOL ret = CLIENT_Init(DisConnectFunc, (DWORD)this);
	if (!ret)
	{
		MessageBox(ConvertString("Initialize SDK failed!"), ConvertString("Prompt"));
	}

	// 初始化成功后设置网络参数
	NET_PARAM stuNetParam = {0};
	// 目前仅单独设置获取设备信息时间（部分设备因性能问题，没法在默认时间内完成，其他参数暂时保持默认）
	stuNetParam.nGetDevInfoTime = 3000;
	CLIENT_SetNetworkParam(&stuNetParam);
}

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CClientDemo6Dlg *dlg = (CClientDemo6Dlg *)dwUser;
	dlg->DeviceDisConnect(lLoginID, pchDVRIP,nDVRPort);
}

void CClientDemo6Dlg::DeviceDisConnect(LONG lLoginID, char *sDVRIP, LONG nDVRPort)
{
	MessageBox(ConvertString("Network disconnected!"), ConvertString("Prompt"));
	
}

void CClientDemo6Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(0 != m_LoginID)
	{
		BOOL bLogout = CLIENT_Logout(m_LoginID);
	}
	
	CLIENT_Cleanup();
}

CString CClientDemo6Dlg::GetDvrIP()
{
	CString strRet="";
	BYTE nField0,nField1,nField2,nField3;
	m_ctlDvrIP.GetAddress(nField0,nField1,nField2,nField3);
	strRet.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);
	return strRet;
}

void CClientDemo6Dlg::OnButtonQuery() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_nPageLine > 100)
	{
		MessageBox(ConvertString("PageLine was limited!"), ConvertString("Prompt"));
		return;
	}

	if(0 != m_LoginID)
	{
		if (m_stuEnable.IsFucEnable[EN_LOG] == 0)
		{
			char* recBuf = new char[1024*sizeof(DH_LOG_ITEM)];
			memset(recBuf, 0, 1024*sizeof(DH_LOG_ITEM));
			int nRetLen = 0;
			int nIndex = m_ctlQueryType.GetCurSel();
			if(CB_ERR != nIndex)
			{
				BOOL bSuccess = CLIENT_QueryLogEx(m_LoginID,DHLOG_ALL,recBuf,1024*sizeof(DH_LOG_ITEM),&nRetLen, NULL, 10000);
				if(bSuccess)
				{
					if ((nRetLen%sizeof(DH_LOG_ITEM)) == 0)
					{
						m_ctlQueryResult.DeleteAllItems();
						DisplayQueryResult(recBuf,nRetLen);
						if(0 == m_ctlQueryResult.GetItemCount())
						{
							MessageBox(ConvertString("No record!"), ConvertString("Prompt"));
						}
					}
					else
					{
						m_ctlQueryResult.DeleteAllItems();
						MessageBox(ConvertString("Checkout error"), ConvertString("Prompt"));
					}
				}
				else
				{
					m_ctlQueryResult.DeleteAllItems();
					MessageBox(ConvertString("Query log failed!"), ConvertString("Prompt"));
				}
			}

			delete[] recBuf;
		}
		else
		{
			if (m_dataBegin > m_dataEnd || (m_dataBegin == m_dataEnd && m_timeBegin > m_timeEnd))
			{
				MessageBox(ConvertString("Bad time set!"), ConvertString("Prompt"));
				return;
			}

			QUERY_DEVICE_LOG_PARAM stuLogParam;
			memset(&stuLogParam, 0, sizeof(QUERY_DEVICE_LOG_PARAM));
			int nIndex = m_ctlQueryType.GetCurSel();
			stuLogParam.emLogType = (DH_LOG_QUERY_TYPE)nIndex;
			stuLogParam.nStartNum = 0;
			stuLogParam.nEndNum = m_nPageLine -1;
			stuLogParam.nLogStuType = 1;
			m_nPreEndNum = stuLogParam.nEndNum + 1;
			m_nPreStartNum = stuLogParam.nStartNum;
			stuLogParam.stuStartTime.dwYear = m_dataBegin.GetYear();
			stuLogParam.stuStartTime.dwMonth = m_dataBegin.GetMonth();
			stuLogParam.stuStartTime.dwDay = m_dataBegin.GetDay();
			stuLogParam.stuStartTime.dwHour = m_timeBegin.GetHour();
			stuLogParam.stuStartTime.dwMinute = m_timeBegin.GetMinute();
			stuLogParam.stuStartTime.dwSecond = m_timeBegin.GetSecond();

			stuLogParam.stuEndTime.dwYear = m_dataEnd.GetYear();
			stuLogParam.stuEndTime.dwMonth = m_dataEnd.GetMonth();
			stuLogParam.stuEndTime.dwDay = m_dataEnd.GetDay();
			stuLogParam.stuEndTime.dwHour = m_timeEnd.GetHour();
			stuLogParam.stuEndTime.dwMinute = m_timeEnd.GetMinute();
			stuLogParam.stuEndTime.dwSecond = m_timeEnd.GetSecond();

			DH_DEVICE_LOG_ITEM_EX* szLogInfos = new DH_DEVICE_LOG_ITEM_EX[1024];
			int nRetLogNum = 0;
			BOOL bRet = CLIENT_QueryDeviceLog(m_LoginID, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum, DEMO_SDK_WAITTIME);
			if (bRet)
			{
				//display log info
				if (nRetLogNum <= 0)
				{
					MessageBox(ConvertString("No record!"), ConvertString("Prompt"));
					return;
				}
				// not enough, continue
				else if (nRetLogNum < m_nPageLine)
				{
					DisPlayNewLogInfo(szLogInfos, nRetLogNum);

					int nTotal = nRetLogNum;
					do 
					{
						memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
						stuLogParam.nStartNum = m_nPreStartNum + nTotal;
						stuLogParam.nEndNum = m_nPreEndNum - 1;
						bRet = CLIENT_QueryDeviceLog(m_LoginID, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum, 3*DEMO_SDK_WAITTIME);
						if (bRet)
						{
							// no more
							if (nRetLogNum <= 0)
							{
								break;
							}
							DisPlayNewLogInfo(szLogInfos, nRetLogNum, TRUE);
							nTotal += nRetLogNum;
						}
						else
						{
							MessageBox(ConvertString("Query log failed!"), ConvertString("Prompt"));
							return;
						}

					} while (nTotal < m_nPageLine);
				}
				else
				{
					DisPlayNewLogInfo(szLogInfos, nRetLogNum);
				}

				//tell if there has more logs
				memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
				stuLogParam.nStartNum = m_nPreEndNum;
				stuLogParam.nEndNum = m_nPreEndNum + 2;
				bRet = CLIENT_QueryDeviceLog(m_LoginID, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum, DEMO_SDK_WAITTIME);
				if (nRetLogNum > 0)
				{
					GetDlgItem(IDC_BUTTON_PREPAGE)->EnableWindow(FALSE);
					GetDlgItem(IDC_BUTTON_NEXTPAGE)->EnableWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_BUTTON_PREPAGE)->EnableWindow(FALSE);
					GetDlgItem(IDC_BUTTON_NEXTPAGE)->EnableWindow(FALSE);
				}
			}
			else
			{
				m_ctlQueryResult.DeleteAllItems();
				MessageBox(ConvertString("Query log failed!"), ConvertString("Prompt"));
			}

			delete[] szLogInfos;
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo6Dlg::InitListView()
{
	m_ctlQueryResult.SetExtendedStyle(m_ctlQueryResult.GetExtendedStyle() | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlQueryResult.InsertColumn(0, ConvertString(""), LVCFMT_LEFT,30,-1);
	m_ctlQueryResult.InsertColumn(1, ConvertString("type"), LVCFMT_LEFT,120,-1);
	m_ctlQueryResult.InsertColumn(2, ConvertString("date"),LVCFMT_LEFT,200,0);
	m_ctlQueryResult.InsertColumn(3, ConvertString("content"),LVCFMT_LEFT,390,1);
}

int/*void*/ CClientDemo6Dlg::TransLogInfo(void *pLoginfo, int nStructType, CString &strLogType, CString &strLogTime, CString &strLogContext)
{
	int nRet = 1;
	if (pLoginfo == NULL)
	{
		nRet = 0;
		return nRet;
	}

	DHDEVTIME stuTime = {0};
	int nLogType = 0;
	DH_LOG_ITEM *pLogItem = NULL;
	if (nStructType == 0)
	{
		// new log 
		DH_DEVICE_LOG_ITEM_EX *pLog = (DH_DEVICE_LOG_ITEM_EX*)pLoginfo;
		nLogType = pLog->nLogType;
		memcpy(&stuTime, &pLog->stuOperateTime, sizeof(DHDEVTIME));
		strLogContext = pLog->szDetailContext;
	}
	else if (nStructType == 1)
	{
		// old log
		pLogItem = (DH_LOG_ITEM*)pLoginfo;
		nLogType = pLogItem->type;
		memcpy(&stuTime, &pLogItem->time, sizeof(DHDEVTIME));
	}

	strLogTime.Format("%d-%d-%d %d:%d:%d", stuTime.year+2000, stuTime.month, stuTime.day, stuTime.hour, stuTime.minute, stuTime.second);
	switch(nLogType)
	{
	case DH_LOG_REBOOT:	
		{
			strLogType = ConvertString("Restart Device");
			if (pLogItem != NULL)
			{
				if (0 == pLogItem->data)
				{
					strLogContext = ConvertString("Normal Reboot!");
				}
				else
				{
					strLogContext = ConvertString("Exceptional Reboot!");
				}
			}
		}
		break;
	case DH_LOG_SHUT:
		{
			strLogType = ConvertString("Shut Device");
			if (pLogItem != NULL)
			{
				DHDEVTIME *shutTime = (DHDEVTIME*)pLogItem->context;
				strLogContext.Format(ConvertString("Shut DVR, time:%d-%d-%d %d:%d:%d"), shutTime->year+2000, shutTime->month,
				shutTime->day, shutTime->hour, shutTime->minute, shutTime->second);
			}
		}
		break;
	case DH_LOG_REPORTSTOP:
		{
			strLogType = ConvertString("Report Stop");
		}
		break;
	case DH_LOG_REPORTSTART:
		{
			strLogType = ConvertString("Report Start");
		}
		break;
	case DH_LOG_UPGRADE:
		{
			strLogType = ConvertString("Upgrade Device");
			if (pLogItem !=NULL)
			{		
				DHDEVTIME *shutTime = (DHDEVTIME*)pLogItem->context;
				strLogContext.Format(ConvertString("time:%d-%d-%d %d:%d:%d"), shutTime->year+2000, shutTime->month,
					shutTime->day, shutTime->hour, shutTime->minute, shutTime->second);
				if (0 == pLogItem->data)
				{
					strLogContext = ConvertString("Upgrade successful, ") + strLogContext;
				} 
				else
				{
					strLogContext = ConvertString("Upgrade failed, ") + strLogContext;
				}
			}

		}
		break;
	case DH_LOG_SYSTIME_UPDATE:
		{
			strLogType = ConvertString("System Time Upgrade");
			if (pLogItem != NULL)
			{
				strLogContext = ConvertString("System Time Upgrade");
			}
		}
		break;
	case DH_LOG_GPS_TIME_UPDATE:
		{
			strLogType = ConvertString("GPS Time Upgrade");
			if (pLogItem != NULL)
			{
				strLogContext = ConvertString("GPS Time Upgrade");
			}
		}
		break;
	case DH_LOG_AUDIO_TALKBACK:
		{
			strLogType = ConvertString("Audio Talkback");
			if (pLogItem != NULL)
			{
				if (0 == pLogItem->data)
				{
					strLogContext = ConvertString("Audio Talkback OFF");
				} 
				else
				{
					strLogContext = ConvertString("Audio Talkback ON");
				}
			}
		}
		break;
	case DH_LOG_COMM_ADAPTER:
		{
			strLogType = ConvertString("COMM Adapter");
			if (pLogItem != NULL)
			{
				if (0 == pLogItem->data)
				{
					strLogContext = ConvertString("COMM Adapter OFF");
				} 
				else
				{
					strLogContext = ConvertString("COMM Adapter ON");
				}
			}
		}
		break;
	case DH_LOG_NET_TIMING:
		{
			strLogType = ConvertString("Time Update");
			if (pLogItem != NULL)
			{
				strLogContext = ConvertString("Time Update");
			}
		}
		break;
	case DH_LOG_CONFSAVE:
		{
			strLogType = ConvertString("Save Config Info");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("config type: "));
				strLogContext += ConvertCfgType(pLogItem);
			}

		}
		break;
	case DH_LOG_CONFLOAD:
		{
			strLogType = ConvertString("Load Config Info");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("config type: "));
				strLogContext += ConvertCfgType(pLogItem);
			}

		}
		break;
	case DH_LOG_FSERROR:
		{
			strLogType = ConvertString("File System Error");
			if (pLogItem != NULL)
			{
				strLogContext = ConvertString("File system appears error");
			}
		}
		break;
	case DH_LOG_HDD_WERR:
		{
			strLogType = ConvertString("Write DISK Error");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Disk number:%d"), pLogItem->data);
			}
		
		}
		break;
	case DH_LOG_HDD_RERR:
		{
			strLogType = ConvertString("Read DISK Error");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Disk number:%d"), pLogItem->data);
			}
		
		}
		break;
	case DH_LOG_HDD_TYPE:
		{
			strLogType = ConvertString("Set DISK Type");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Disk number:%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_FORMAT:
		{
			strLogType = ConvertString("Format DISK");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Disk number:%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_NOSPACE: 
		{
			strLogType = ConvertString("Storage device is no space");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("The residual percentage of storage device is:%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_TYPE_RW:	
		{
			strLogType = ConvertString("Set Storage device Type");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Storage device No.%d(read-write)"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_TYPE_RO:	
		{
			strLogType = ConvertString("Set Storage device Type");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Storage device No.%d(read-only)"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_TYPE_RE:	
		{
			strLogType = ConvertString("Set Storage device Type");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Storage device No.%d(Redundancye)"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_TYPE_SS:
		{
			strLogType = ConvertString("Set Storage device Type");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Storage device No.%d(snapshot)"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_NONE:
		{
			strLogType = ConvertString("No hard disk recording");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Storage device No.%d(snapshot)"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_NOWORKHDD:
		{
			strLogType = ConvertString("None WORKHDD");
			if (pLogItem != NULL)
			{
				strLogContext = ConvertString("There is no work disk");
			}
		}
		break;	
	case DH_LOG_HDD_TYPE_BK:	
		{
			strLogType = ConvertString("Set Storage device Type");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Storage device No.%d(Backup)"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_TYPE_REVERSE:	
		{
			strLogType = ConvertString("Set Storage device Type");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Storage device No.%d(Reverse)"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_START_INFO:
		{
			//记录开机时的硬盘信息
			strLogType = ConvertString("Storage device infomation");
			if (pLogItem != NULL)
			{
				strLogContext.Format("%s:%d %s:%s", ConvertString("HDD amount"), pLogItem->data,
													ConvertString("Working HDD"), pLogItem->context);
			}
		}
		break;
	case DH_LOG_HDD_WORKING_DISK:
		{
			strLogType = ConvertString("Storage device work disk");
		}
		break;
	case DH_LOG_HDD_OTHER_ERROR:
		{
			strLogType = ConvertString("Storage device other errors");
		}
		break;
	case DH_LOG_HDD_SLIGHT_ERR:
		{
			//硬盘轻微问题
			strLogType = ConvertString("Storage device problem");
		}
		break;
	case DH_LOG_HDD_SERIOUS_ERR:
		{
			//硬盘严重问题
			strLogType = ConvertString("Storage device problem");
		}	
		break;
	case DH_LOG_HDD_NOSPACE_END: 
		{
			strLogType = ConvertString("Storage device is no space end");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Current DISK is enough space，disk number：%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_HDD_TYPE_RAID_CONTROL: 
		{
			strLogType = ConvertString("Raid Operation");
		}
		break;
	case DH_LOG_HDD_TEMPERATURE_HIGH: 
		{
			strLogType = ConvertString("Temperature too high");
		}
		break;
	case DH_LOG_HDD_TEMPERATURE_LOW: 
		{
			strLogType = ConvertString("Temperature too low");
		}
		break;
	case DH_LOG_HDD_ESATA_REMOVE: 
		{
			strLogType = ConvertString("Remove eSATA");
		}
	    break;
	case DH_LOG_ALM_IN:
		{
			strLogType = ConvertString("Alarm Input");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Alarm Input，channel：%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_NETALM_IN:	
		{
			strLogType = ConvertString("Net Alarm Input");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Alarm Input，channel：%s"), pLogItem->context);
			}
		}
		break;
	case DH_LOG_ALM_END:
		{
			strLogType = ConvertString("Alarm Input End");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Alarm Input End，channel：%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_LOSS_IN:	
		{
			strLogType = ConvertString("Video Loss");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_LOSS_END:
		{
			strLogType = ConvertString("Video Loss End");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_MOTION_IN:	
		{
			strLogType = ConvertString("Motion Detect");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_MOTION_END:	
		{
			strLogType = ConvertString("Motion Detect End");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_ALM_BOSHI:	
		{
			strLogType = ConvertString("Alarm Alarm Input");
		}
		break;
	case DH_LOG_NET_ABORT:
		{	
			strLogType = ConvertString("Network Disconnect");
			
			if (pLogItem != NULL && 1 == pLogItem->data)
			{
				strLogContext.Format(ConvertString("Wireless"));
			}
		}
		break;
	case DH_LOG_NET_ABORT_RESUME:	
		{
			strLogType = ConvertString("Network Resumed");
			
			if (pLogItem != NULL && 1 == pLogItem->data)
			{
				strLogContext.Format(ConvertString("Wireless"));
			}
		}
		break;
	case DH_LOG_CODER_BREAKDOWN:	
		{
			strLogType = ConvertString("CODER Error");
			if(pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("CODER Error"));
			}
		}
		break;
	case DH_LOG_CODER_BREAKDOWN_RESUME:
		{
			strLogType = ConvertString("CODER Error Resumed");
			if(pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("CODER Error Resumed"));
			}
		}
		break;
	case DH_LOG_BLIND_IN:	
		{		
			strLogType = ConvertString("Camera Mask Detect");
			if(pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_BLIND_END:
		{	
			strLogType = ConvertString("Camera Mask Detect End");
			if(pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
		}
		break;
	case DH_LOG_ALM_TEMP_HIGH:
		{
			strLogType = ConvertString("Temperature Alarm");
			if(pLogItem != NULL)
			{
				strLogContext.Format("%s", ConvertString("Temperature is too high"));
			}
		}
		break;
	case DH_LOG_ALM_VOLTAGE_LOW:	
		{
			strLogType = ConvertString("Temperature Alarm");
			if(pLogItem != NULL)
			{
				strLogContext.Format("%s", ConvertString("Temperature is too low"));
			}
		}
		break;
	case DH_LOG_ALM_BATTERY_LOW:	
		{
			strLogType = ConvertString("Battery Alarm");
			if(pLogItem != NULL)
			{
				strLogContext.Format("%s", ConvertString("Low Battery"));
			}
		}
		break;
	case DH_LOG_ALM_ACC_BREAK:
		{
			strLogType = ConvertString("ACC OFF");
			if(pLogItem != NULL)
			{
				strLogContext.Format("%s", ConvertString("ACC OFF"));
			}
		}
		break;
	case DH_LOG_ALM_ACC_RES:
		{
			strLogType = ConvertString("ACC ON");
			if(pLogItem != NULL)
			{
				strLogContext.Format("%s", ConvertString("ACC ON"));
			}
		}
		break;
	case DH_LOG_GPS_SIGNAL_LOST:
		{
			strLogType = ConvertString("GPS No Signal");
		}
		break;
	case DH_LOG_GPS_SIGNAL_RESUME:
		{
			strLogType = ConvertString("GPS Signal Resumed");
		}
		break;
	case DH_LOG_3G_SIGNAL_LOST:
		{
			strLogType = ConvertString("3G No Signal");
		}
		break;
	case DH_LOG_3G_SIGNAL_RESUME:
		{
			strLogType = ConvertString("3G Signal Resumed");
		}
		break;
	case DH_LOG_ALM_IPC_IN:
		{
			strLogType = ConvertString("IPC Alarm ON");
		}
		break;
	case DH_LOG_ALM_IPC_END:
		{
			strLogType = ConvertString("IPC Alarm OFF");
		}
		break;
	case DH_LOG_ALM_DIS_IN:
		{
			strLogType = ConvertString("Disconnet Alarm");
		}
		break;
	case DH_LOG_ALM_DIS_END:
		{
			strLogType = ConvertString("Disconnet Resumed");
		}
		break;
	case DH_LOG_INFRAREDALM_IN :
		{
			strLogType = ConvertString("Infrared Alarm");
			if(pLogItem != NULL)
			{
				strLogContext.Format("Channel No.%d", pLogItem->data);
			}
		}
		break;
	case DH_LOG_INFRAREDALM_END:
		{
			strLogType = ConvertString("Infrared Alarm End");
			if(pLogItem != NULL)
			{
				strLogContext.Format("Channel No.%d", pLogItem->data);
			}
		}
		break;
	case DH_LOG_IPCONFLICT:
		{
			strLogType = ConvertString("IP Conflict");
			
			if (pLogItem != NULL && 1 == pLogItem->data)
			{
				strLogContext.Format(ConvertString("Wireless"));
			}
		}
		break;
	case DH_LOG_IPCONFLICT_RESUME:			
		{
			strLogType = ConvertString("IP Conflict Resumed");
			
			if (pLogItem != NULL && 1 == pLogItem->data)
			{
				strLogContext.Format(ConvertString("Wireless"));
			}
		}
		break;
	case DH_LOG_SDPLUG_IN:       
		{
			strLogType = ConvertString("SD card Alarm");
			if (pLogItem != NULL)
			{
				strLogContext.Format("%s",ConvertString("SD card inserted"));
			}
		}
		break;					
	case DH_LOG_SDPLUG_OUT:      
		{
			strLogType = ConvertString("SD card Alarm");
			if (pLogItem != NULL)
			{
				strLogContext.Format("%s",ConvertString("SD card pulled out"));
			}
		}
		break;
	case DH_LOG_NET_PORT_BIND_FAILED:
		{
			strLogType = ConvertString("Failed to bind port");
		}
		break;
	case DH_LOG_HDD_BEEP_RESET:      
		{
			strLogType = ConvertString("Beep reset alarm");
			if (pLogItem != NULL)
			{
				strLogContext.Format("%s",ConvertString("Hard disk error beep reset"));
			}
		}
		break;
	case DH_LOG_MAC_CONFLICT:
		{
			strLogType = ConvertString("MAC Conflict");
		}
		break;
	case DH_LOG_MAC_CONFLICT_RESUME:
		{
			strLogType = ConvertString("MAC Conflict Resumed");
		}
		break;
	case DH_LOG_ALARM_OUT:
		{
			strLogType = ConvertString("Alarm out status");
		}
		break;
	case DH_LOG_ALM_RAID_STAT_EVENT:
		{
			strLogType = ConvertString("Raid status changed");
		}
		break;
	case DH_LOG_ABLAZE_ON:
		{
			strLogType = ConvertString("Ablaze ON");
		}
		break;
	case DH_LOG_ABLAZE_OFF:
		{
			strLogType = ConvertString("Ablaze OFF");
		}
		break;
	case DH_LOG_INTELLI_ALARM_PLUSE:
		{
			strLogType = ConvertString("Intelligent pluse alarm");
		}
		break;
	case DH_LOG_INTELLI_ALARM_IN:
		{
			strLogType = ConvertString("Intelligent alarm begin");
		}
		break;
	case DH_LOG_INTELLI_ALARM_END:
		{
			strLogType = ConvertString("Intelligent alarm end");
		}
		break;
	case DH_LOG_3G_SIGNAL_SCAN:
		{
			strLogType = ConvertString("3G Signal Scan");
		}
		break;
	case DH_LOG_GPS_SIGNAL_SCAN:
		{
			strLogType = ConvertString("GPS Signal Scan");
		}
		break;
	case DH_LOG_AUTOMATIC_RECORD:
		{
			strLogType = ConvertString("Automatic Record");
			if (pLogItem != NULL)
			{
				strLogContext = ConvertString("Start automatic recording, channel: ");
				DWORD dwMask = *(DWORD*)pLogItem->context;
				DWORD dwPos = 1;
				CString str = "";
				for (int i = 0; i < 32; i++)
				{
					if ((dwMask & dwPos) != 0)
					{
						str.Format("%d ", i);
						strLogContext += str;
					}
					
					dwPos = dwPos << 1;
				}
			}
		}
		break;
	case DH_LOG_MANUAL_RECORD:
		{
			strLogType = ConvertString("Manual recording is beginning");
			if (pLogItem != NULL)
			{
				strLogContext = ConvertString("Manual recording is beginning, channel: ");
				DWORD dwMask = *(DWORD*)pLogItem->context;
				DWORD dwPos = 1;
				CString str = "";
				for (int i = 0; i < 32; i++)
				{
					if ((dwMask & dwPos) != 0)
					{
						str.Format("%d ", i);
						strLogContext += str;
					}
					
					dwPos = dwPos << 1;
				}
			}
		}
		break;
	case DH_LOG_CLOSED_RECORD:
		{
			strLogType = ConvertString("Stop Manual Recording");
			if (pLogItem != NULL)
			{
				strLogContext = ConvertString("Stop manual recording, channel: ");
				DWORD dwMask = *(DWORD*)pLogItem->context;
				DWORD dwPos = 1;
				CString str = "";
				for (int i = 0; i < 32; i++)
				{
					if ((dwMask & dwPos) != 0)
					{
						str.Format("%d ", i);
						strLogContext += str;
					}
					
					dwPos = dwPos << 1;
				}
			}
		}
		break;
	case DH_LOG_LOGIN:
		{
			strLogType = ConvertString("Login");
			
			if (pLogItem != NULL)
			{
				char szContext[12] = {0};
				char szUnicodeInfo[24] = {0};
				char szContextInfo[24] = {0};
				
				memcpy(szContext, pLogItem->context, 8);
				int nNum = MultiByteToWideChar(CP_UTF8, 0, szContext, strlen(szContext), (LPWSTR)szUnicodeInfo, 24);
				nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)szUnicodeInfo, nNum, szContextInfo, 24, NULL, NULL);
				
				strLogContext.Format(ConvertString("User login：%s"), szContextInfo);
			}
		}
		break;
	case DH_LOG_LOGOUT:
		{
			strLogType = ConvertString("Logout");
			
			if (pLogItem != NULL)
			{
				char szContext[12] = {0};
				char szUnicodeInfo[24] = {0};
				char szContextInfo[24] = {0};
				
				memcpy(szContext, pLogItem->context, 8);
				int nNum = MultiByteToWideChar(CP_UTF8, 0, szContext, strlen(szContext), (LPWSTR)szUnicodeInfo, 24);
				nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)szUnicodeInfo, nNum, szContextInfo, 24, NULL, NULL);
				
				strLogContext.Format(ConvertString("User logout：%s"), szContextInfo);
			}
		}
		break;
	case DH_LOG_ADD_USER:
		{
			strLogType = ConvertString("Add User");
			
			if (pLogItem != NULL)
			{
				char szContext[12] = {0};
				char szUnicodeInfo[24] = {0};
				char szContextInfo[24] = {0};
				
				memcpy(szContext, pLogItem->context, 8);
				int nNum = MultiByteToWideChar(CP_UTF8, 0, szContext, strlen(szContext), (LPWSTR)szUnicodeInfo, 24);
				nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)szUnicodeInfo, nNum, szContextInfo, 24, NULL, NULL);
				
				strLogContext.Format(ConvertString("Add user：%s"), szContextInfo);
			}
		}
		break;
	case DH_LOG_DELETE_USER:
		{
			strLogType = ConvertString("Delete User");
			
			if (pLogItem != NULL)
			{
				char szContext[12] = {0};
				char szUnicodeInfo[24] = {0};
				char szContextInfo[24] = {0};
				
				memcpy(szContext, pLogItem->context, 8);
				int nNum = MultiByteToWideChar(CP_UTF8, 0, szContext, strlen(szContext), (LPWSTR)szUnicodeInfo, 24);
				nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)szUnicodeInfo, nNum, szContextInfo, 24, NULL, NULL);
				
				strLogContext.Format(ConvertString("Delete user：%s"), szContextInfo);
			}
		}
		break;
	case DH_LOG_MODIFY_USER:
		{
			strLogType = ConvertString("Modify User");
			
			if (pLogItem != NULL)
			{
				char szContext[12] = {0};
				char szUnicodeInfo[24] = {0};
				char szContextInfo[24] = {0};
				
				memcpy(szContext, pLogItem->context, 8);
				int nNum = MultiByteToWideChar(CP_UTF8, 0, szContext, strlen(szContext), (LPWSTR)szUnicodeInfo, 24);
				nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)szUnicodeInfo, nNum, szContextInfo, 24, NULL, NULL);
				
				strLogContext.Format(ConvertString("Modify user info：%s"), szContextInfo);
			}
		}
		break;
	case DH_LOG_ADD_GROUP:
		{
			strLogType = ConvertString("Add User Group");
			
			if (pLogItem != NULL)
			{
				char szContext[12] = {0};
				char szUnicodeInfo[24] = {0};
				char szContextInfo[24] = {0};
				
				memcpy(szContext, pLogItem->context, 8);
				int nNum = MultiByteToWideChar(CP_UTF8, 0, szContext, strlen(szContext), (LPWSTR)szUnicodeInfo, 24);
				nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)szUnicodeInfo, nNum, szContextInfo, 24, NULL, NULL);
				
				strLogContext.Format(ConvertString("Add user group：group name：%s"), szContextInfo);
			}
		}
		break;
	case DH_LOG_DELETE_GROUP:
		{
			strLogType = ConvertString("Delete User Group");
			
			if (pLogItem != NULL)
			{
				char szContext[12] = {0};
				char szUnicodeInfo[24] = {0};
				char szContextInfo[24] = {0};
				
				memcpy(szContext, pLogItem->context, 8);
				int nNum = MultiByteToWideChar(CP_UTF8, 0, szContext, strlen(szContext), (LPWSTR)szUnicodeInfo, 24);
				nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)szUnicodeInfo, nNum, szContextInfo, 24, NULL, NULL);
				
				strLogContext.Format(ConvertString("Delete user group：group name：%s"), szContextInfo);
			}
		}
		break;
	case DH_LOG_MODIFY_GROUP:
		{
			strLogType = ConvertString("Modify User Group");
			
			if (pLogItem != NULL)
			{
				char szContext[12] = {0};
				char szUnicodeInfo[24] = {0};
				char szContextInfo[24] = {0};
				
				memcpy(szContext, pLogItem->context, 8);
				int nNum = MultiByteToWideChar(CP_UTF8, 0, szContext, strlen(szContext), (LPWSTR)szUnicodeInfo, 24);
				nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)szUnicodeInfo, nNum, szContextInfo, 24, NULL, NULL);
				
				strLogContext.Format(ConvertString("Modify user group：group name：%s"), szContextInfo);
			}
		}
		break;
	case DH_LOG_NET_LOGIN:
		{
			strLogType = ConvertString("Net User Login");
			
			if (pLogItem != NULL)
			{
				strLogContext.Format("IP: %d.%d.%d.%d", pLogItem->context[0], pLogItem->context[1], pLogItem->context[2], pLogItem->context[3]);
			}
		}
		break;
	case DH_LOG_MODIFY_PASSWORD:
		{
			strLogType = ConvertString("Net User Modify Password");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("Who Modify Password"), (char*)pLogItem->context);
			}
		}
		break;
	case DH_LOG_CLEAR:
		{
			strLogType = ConvertString("clean log");
			if (pLogItem != NULL)
			{
				strLogContext.Format(ConvertString("clean log"));
			}
		}
		break;
	case DH_LOG_SEARCHLOG:	
		{
			strLogType = ConvertString("Search Log");
			
			if (pLogItem != NULL)
			{
				char szContext[12] = {0};
				char szUnicodeInfo[24] = {0};
				char szContextInfo[24] = {0};
				
				memcpy(szContext, pLogItem->context, 8);
				int nNum = MultiByteToWideChar(CP_UTF8, 0, szContext, strlen(szContext), (LPWSTR)szUnicodeInfo, 24);
				nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)szUnicodeInfo, nNum, szContextInfo, 24, NULL, NULL);
				
				strLogContext.Format(ConvertString("Search Log: %s"), szContextInfo);
			}
		}
		break;
	case DH_LOG_SEARCH:			
		{
			strLogType = ConvertString("Record Search");
			
			if (pLogItem != NULL)
			{
				LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)pLogItem->context;
				if (255 == shutTime->channel)
				{
					strLogContext.Format(ConvertString("Record Search: Channel No. %s"), ConvertString("all"));
				}
				else
				{
					strLogContext.Format(ConvertString("Record Search: Channel No. %d"), shutTime->channel);
				}
			}
		}
		break;
	case DH_LOG_DOWNLOAD:		
		{
			strLogType = ConvertString("Record Download");
			if (pLogItem != NULL)
			{
				LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)pLogItem->context;
				strLogContext.Format(ConvertString("Record Download, Channel No. %d"), shutTime->channel);		
			}
		}
		break;
	case DH_LOG_PLAYBACK:		
		{
			strLogType = ConvertString("Record Playback");
			if (pLogItem != NULL)
			{
				LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)pLogItem->context;
				strLogContext.Format(ConvertString("Record Playback, Channel No. %d"), shutTime->channel);	
			}
		}
		break;
	case DH_PLAY_PAUSE:
		{
			strLogType = ConvertString("Record pause");
			if (pLogItem != NULL)
			{
				LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)pLogItem->context;
				strLogContext.Format(ConvertString("Record pause, Channel No. %d"), shutTime->channel);
			}
		}
		break;
	case DH_LOG_BACKUP:			
		{
			strLogType = ConvertString("Record Backup");
			if (pLogItem != NULL)
			{
				LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)pLogItem->context;
				strLogContext.Format(ConvertString("Record Backup, Channel No. %d"), shutTime->channel);
			}
		}
		break;
	case DH_LOG_BACKUPERROR:		
		{
			strLogType = ConvertString("Record Backup");
			if (pLogItem != NULL)
			{
				strLogContext.Format("%s",ConvertString("Record Backup Error"));
			}
		}
		break;
	case DH_LOG_BACK_UPRT:
		{
			strLogType = ConvertString("Real-time Backup");
		}
		break;
	case DH_LOG_BACKUPCLONE:
		{
			strLogType = ConvertString("Backup Clone");
		}
		break;
	case DH_LOG_DISK_CHANGED:
		{
			strLogType = ConvertString("Disk Changed");
		}
		break;
	case DH_LOG_IMAGEPLAYBACK:
		{
			strLogType = ConvertString("Image Playback");
		}
		break;
	case DH_LOG_LOCKFILE:
		{
			strLogType = ConvertString("Lock File");
		}
		break;
	case DH_LOG_UNLOCKFILE:
		{
			strLogType = ConvertString("Unlock File");
		}
		break;
	case DH_LOG_ATMPOS:
		{
			strLogType = ConvertString("ATM POS");
		}
		break;
	case DH_LOG_TIME_UPDATE:
		{
			strLogType = ConvertString("Time Update");
			if (pLogItem != NULL)
			{
				strLogContext.Format("%s",ConvertString("Time Update"));
			}
		}
		break;
	case DH_LOG_REMOTE_STATE:
		{
			strLogType = ConvertString("Remote State");
		}
		break;
	case DH_LOG_USER_DEFINE:
		{
			strLogType = ConvertString("User Define");
		}
		break;
	default:
		{
			nRet = 0;
		}
	}
	return nRet;
}

void CClientDemo6Dlg::DisplayQueryResult(char *recBuf, int nLength)
{
	CString strLogType;
	CString strLogTime;
	CString strLogContext;
	int nCount = nLength/sizeof(DH_LOG_ITEM);
	for(int i=0;i<nCount;i++)
	{
		DH_LOG_ITEM *pLogItem = (DH_LOG_ITEM*)(recBuf+i*sizeof(DH_LOG_ITEM));
		
		if(!TransLogInfo(pLogItem, 1, strLogType, strLogTime, strLogContext))
		{
			continue;
		}
		
		int nIndex = m_ctlQueryType.GetCurSel();
		if(CB_ERR != nIndex)
		{
			DH_LOG_QUERY_TYPE eQueryType = (DH_LOG_QUERY_TYPE)m_ctlQueryType.GetItemData(nIndex);
			if(JudgeType(eQueryType,pLogItem->type))
			{
				InsertListViewItem(strLogType,strLogTime,strLogContext);
			}
			else
			{
				CString strTemp;
				strTemp.Format("%s%d",ConvertString("the log information is not to the content of the query,please check-up device, the return log type is:"), pLogItem->type);
				MessageBox(strTemp);
				break;
			}
		}// if
	}// for
}

void CClientDemo6Dlg::InsertListViewItem(CString strLogType, CString strLogTime, CString strLogContext)
{
	int nIndex = m_ctlQueryResult.GetItemCount();
	CString strIndex;
	strIndex.Format("%d", nIndex + 1);
	m_ctlQueryResult.InsertItem(LVIF_TEXT|LVIF_STATE,nIndex, strIndex, 0,LVIS_SELECTED,0,0);
	
	m_ctlQueryResult.SetItemText(nIndex,1,strLogType);
	m_ctlQueryResult.SetItemText(nIndex,2,strLogTime);
	m_ctlQueryResult.SetItemText(nIndex,3,strLogContext);
}

BOOL CClientDemo6Dlg::JudgeType(int nQueryType, int nInfoType)
{
	BOOL bShow = FALSE;
	switch (nQueryType)
	{
	case DHLOG_ALL:
	case DHLOG_SYSTEM:
	case DHLOG_CONFIG:
	case DHLOG_STORAGE:
	case DHLOG_ALARM:
	case DHLOG_RECORD:
	case DHLOG_ACCOUNT:
	case DHLOG_CLEAR:
	case DHLOG_PLAYBACK:
	case DHLOG_MANAGER:
		bShow = TRUE;
		break;
	default:
		break;
	}
	if (bShow) // 大类正确
	{
		if (DHLOG_ALL == nQueryType) // 全
		{
			return (nInfoType >= ((DHLOG_SYSTEM - 1) << 8)) && (nInfoType < (DHLOG_MANAGER << 8));
		}
		else // 其他
		{
			return (nInfoType >= ((nQueryType - 1) << 8)) && (nInfoType < (nQueryType << 8));
		}
	}
	return bShow;
}

void CClientDemo6Dlg::OnButtonQueryxml() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_LoginID)
	{
		char recBuf[8000*sizeof(DH_NEWLOG_ITEM)];
		memset(recBuf, 0, 8000*sizeof(DH_NEWLOG_ITEM));
		int nRetLen = 0;
		int nIndex = m_ctlQueryType.GetCurSel();
		if(CB_ERR != nIndex)
		{
			DH_LOG_QUERY_TYPE eQueryType = (DH_LOG_QUERY_TYPE)m_ctlQueryType.GetItemData(nIndex);
			int nSubType = 1;
			BOOL bSuccess = CLIENT_QueryLogEx(m_LoginID,eQueryType,recBuf,8000*sizeof(DH_NEWLOG_ITEM),&nRetLen, &nSubType, 30000);
			if(bSuccess)
			{
				if ((nRetLen%sizeof(DH_NEWLOG_ITEM)) == 0)
				{
					m_ctlQueryResult.DeleteAllItems();
					DisplayQueryXMLResult(recBuf,nRetLen);
				}
				else
				{
					m_ctlQueryResult.DeleteAllItems();
					MessageBox(ConvertString("Checkout error"), ConvertString("Prompt"));
				}
			}
			else
			{
				m_ctlQueryResult.DeleteAllItems();
				MessageBox(ConvertString("Query log failed!"), ConvertString("Prompt"));
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo6Dlg::DisplayQueryXMLResult(char *recBuf, int nLength)
{
	CString strLogType;
	CString strLogTime;
	CString strLogContext;
	CString strOperator;
	int nCount = nLength/sizeof(DH_NEWLOG_ITEM);
	for(int i=0;i<nCount;i++)
	{
		DH_NEWLOG_ITEM *pLogItem = (DH_NEWLOG_ITEM*)(recBuf+i*sizeof(DH_NEWLOG_ITEM));
		strLogTime.Format("%d-%d-%d %d:%d:%d", pLogItem->time.year+2000, pLogItem->time.month,
			pLogItem->time.day, pLogItem->time.hour, pLogItem->time.minute, pLogItem->time.second);
		strOperator.Format(ConvertString("Operator：%s;"),pLogItem->szOperator);
		switch(pLogItem->type)
		{
		case DH_NEWLOG_REBOOT:
			{
				strLogType = ConvertString("Restart DVR");
				if (0 == pLogItem->data)
				{
					strLogContext = ConvertString("Restart DVR successfully!");
				}
				else
				{
					strLogContext = ConvertString("Restart DVR failed!");
				}
			}
			break;
		case DH_NEWLOG_SHUT:
			{
				strLogType = ConvertString("Shut DVR");
				DHDEVTIME *shutTime = (DHDEVTIME*)pLogItem->context;
				strLogContext.Format(ConvertString("Shut DVR，time：%d-%d-%d %d:%d:%d"), shutTime->year+2000, shutTime->month,
								shutTime->day, shutTime->hour, shutTime->minute, shutTime->second);
			}
			break;
		case DH_NEWLOG_REPORTSTOP:
			{
				strLogType = ConvertString("Report Stop");
			}
			break;
		case DH_NEWLOG_REPORTSTART:
			{
				strLogType = ConvertString("Report Start");
			}
		    break;
		case DH_NEWLOG_UPGRADE:
			{
				strLogType = ConvertString("Upgrade Device");
				if (pLogItem !=NULL)
				{		
					DHDEVTIME *shutTime = (DHDEVTIME*)pLogItem->context;
					strLogContext.Format(ConvertString("time:%d-%d-%d %d:%d:%d"), shutTime->year+2000, shutTime->month,
						shutTime->day, shutTime->hour, shutTime->minute, shutTime->second);
					if (0 == pLogItem->data)
					{
						strLogContext = ConvertString("Upgrade successful, ") + strLogContext;
					} 
					else
					{
						strLogContext = ConvertString("Upgrade failed, ") + strLogContext;
					}
				}
			}
		    break;
		case DH_NEWLOG_SYSTIME_UPDATE:
			{
				strLogType = ConvertString("System Time Upgrade");
				if (pLogItem != NULL)
				{
					strLogContext = ConvertString("System Time Upgrade");
				}
			}
			break;
		case DH_NEWLOG_GPS_TIME_UPDATE:
			{
				strLogType = ConvertString("GPS Time Upgrade");
				if (pLogItem != NULL)
				{
					strLogContext = ConvertString("GPS Time Upgrade");
				}
			}
		    break;
		case DH_NEWLOG_AUDIO_TALKBACK:
			{
				strLogType = ConvertString("Audio Talkback");
				if (pLogItem != NULL)
				{
					if (0 == pLogItem->data)
					{
						strLogContext = ConvertString("Audio Talkback OFF");
					} 
					else
					{
						strLogContext = ConvertString("Audio Talkback ON");
					}
				}
			}
			break;
		case DH_NEWLOG_COMM_ADAPTER:
			{
				strLogType = ConvertString("COMM Adapter");
				if (pLogItem != NULL)
				{
					if (0 == pLogItem->data)
					{
						strLogContext = ConvertString("COMM Adapter OFF");
					} 
					else
					{
						strLogContext = ConvertString("COMM Adapter ON");
					}
				}
			}
			break;
		case DH_NEWLOG_NET_TIMING:
			{
				strLogType = ConvertString("Time Update");
				if (pLogItem != NULL)
				{
					strLogContext = ConvertString("Time Update");
				}
			}
		    break;
		case DH_NEWLOG_CONFSAVE:
			{
				strLogType = ConvertString("Save Config Info");
				strLogContext.Format(ConvertString("Save config info，config type：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_CONFLOAD:
			{
				strLogType = ConvertString("Load Config Info");
				strLogContext.Format(ConvertString("Load config info，config type：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_FSERROR:
			{
				strLogType = ConvertString("File System Error");
				strLogContext = ConvertString("File system appears error");
			}
			break;
		case DH_NEWLOG_HDD_WERR:
			{
				strLogType = ConvertString("Write DISK Error");
				strLogContext.Format(ConvertString("Write disk error，disk number：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_HDD_RERR:
			{
				strLogType = ConvertString("Read DISK Error");
				strLogContext.Format(ConvertString("Read disk error，disk number：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_HDD_TYPE:
			{
				strLogType = ConvertString("Set DISK Type");
				strLogContext.Format(ConvertString("Set disk type，disk number：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_HDD_FORMAT:
			{
				strLogType = ConvertString("Format DISK");
				strLogContext.Format(ConvertString("Format the disk，disk number：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_HDD_NOSPACE:
			{
				strLogType = ConvertString("No Space");
				strLogContext.Format(ConvertString("Current DISK is not enough space，disk number：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_HDD_TYPE_RW:	
			{
				strLogType = ConvertString("Set Storage device Type");
				if (pLogItem != NULL)
				{
					strLogContext.Format(ConvertString("Storage device No.%d(read-write)"), pLogItem->data);
				}
			}
			break;
		case DH_NEWLOG_HDD_TYPE_RO:	
			{
				strLogType = ConvertString("Set Storage device Type");
				if (pLogItem != NULL)
				{
					strLogContext.Format(ConvertString("Storage device No.%d(read-only)"), pLogItem->data);
				}
			}
			break;
		case DH_NEWLOG_HDD_TYPE_RE:	
			{
				strLogType = ConvertString("Set Storage device Type");
				if (pLogItem != NULL)
				{
					strLogContext.Format(ConvertString("Storage device No.%d(Redundancye)"), pLogItem->data);
				}
			}
			break;
		case DH_NEWLOG_HDD_TYPE_SS:
			{
				strLogType = ConvertString("Set Storage device Type");
				if (pLogItem != NULL)
				{
					strLogContext.Format(ConvertString("Storage device No.%d(snapshot)"), pLogItem->data);
				}
			}
			break;
		case DH_NEWLOG_HDD_NONE:
			{
				strLogType = ConvertString("No hard disk recording");
				if (pLogItem != NULL)
				{
					strLogContext.Format(ConvertString("Storage device No.%d(snapshot)"), pLogItem->data);
				}
			}
			break;
		case DH_NEWLOG_HDD_NOWORKHDD:
			{
				strLogType = ConvertString("None WORKHDD");
				if (pLogItem != NULL)
				{
					strLogContext = ConvertString("There is no work disk");
				}
			}
			break;	
		case DH_NEWLOG_HDD_TYPE_BK:	
			{
				strLogType = ConvertString("Set Storage device Type");
				if (pLogItem != NULL)
				{
					strLogContext.Format(ConvertString("Storage device No.%d(Backup)"), pLogItem->data);
				}
			}
			break;
		case DH_NEWLOG_HDD_TYPE_REVERSE:	
			{
				strLogType = ConvertString("Set Storage device Type");
				if (pLogItem != NULL)
				{
					strLogContext.Format(ConvertString("Storage device No.%d(Reverse)"), pLogItem->data);
				}
			}
		    break;
		case DH_NEWLOG_HDD_SLIGHT_ERR:
			{
				//硬盘轻微问题
				strLogType = ConvertString("Storage device problem");
			}
			break;
		case DH_NEWLOG_HDD_SERIOUS_ERR:
			{
				//硬盘严重问题
				strLogType = ConvertString("Storage device problem");
			}	
			break;
		case DH_NEWLOG_HDD_NOSPACE_END: 
			{
				strLogType = ConvertString("Storage device is no space end");
				if (pLogItem != NULL)
				{
					strLogContext.Format(ConvertString("Current DISK is enough space，disk number：%d"), pLogItem->data);
				}
			}
		    break;
		case DH_NEWLOG_HDD_TYPE_RAID_CONTROL: 
			{
				strLogType = ConvertString("Raid Operation");
			}
		    break;
		case DH_NEWLOG_HDD_TEMPERATURE_HIGH: 
			{
				strLogType = ConvertString("Temperature too high");
			}
			break;
		case DH_NEWLOG_HDD_TEMPERATURE_LOW: 
			{
				strLogType = ConvertString("Temperature too low");
			}
			break;
		case DH_NEWLOG_HDD_ESATA_REMOVE: 
			{
				strLogType = ConvertString("Remove eSATA");
			}
	        break;
		case DH_NEWLOG_ALM_IN:
			{
				strLogType = ConvertString("Alarm Input");
				strLogContext.Format(ConvertString("Alarm Input，channel：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_NETALM_IN:
			{
				strLogType = ConvertString("Network Alarm");
				strLogContext.Format(ConvertString("Network Alarm，channel：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_LOSS_IN:
			{
				strLogType = ConvertString("Video Lost");
			}
			break;
		case DH_NEWLOG_LOSS_END:
			{
				strLogType = ConvertString("Video Lost End");
			}
			break;
		case DH_NEWLOG_MOTION_IN:	
			{
				strLogType = ConvertString("Motion Detect");
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_MOTION_END:	
			{
				strLogType = ConvertString("Motion Detect End");
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_ALM_BOSHI:	
			{
				strLogType = ConvertString("Alarm Alarm Input");
			}
			break;
		case DH_NEWLOG_NET_ABORT:
			{	
				strLogType = ConvertString("Network Disconnect");
			
				if (1 == pLogItem->data)
				{
					strLogContext.Format(ConvertString("Wireless"));
				}
			}
			break;
		case DH_NEWLOG_NET_ABORT_RESUME:	
			{
				strLogType = ConvertString("Network Resumed");
				
				if (1 == pLogItem->data)
				{
					strLogContext.Format(ConvertString("Wireless"));
				}
			}
			break;
		case DH_NEWLOG_CODER_BREAKDOWN:	
			{
				strLogType = ConvertString("CODER Error");
				strLogContext.Format(ConvertString("CODER Error"));
			}
			break;
		case DH_NEWLOG_CODER_BREAKDOWN_RESUME:
			{
				strLogType = ConvertString("CODER Error Resumed");
				strLogContext.Format(ConvertString("CODER Error Resumed"));
			}
			break;
		case DH_NEWLOG_BLIND_IN:	
			{		
				strLogType = ConvertString("Camera Mask Detect");
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_BLIND_END:
			{	
				strLogType = ConvertString("Camera Mask Detect End");
				strLogContext.Format(ConvertString("Channel No.：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_ALM_TEMP_HIGH:
			{
				strLogType = ConvertString("Temperature Alarm");
				strLogContext.Format("%s", ConvertString("Temperature is too high"));
			}
			break;
		case DH_NEWLOG_ALM_VOLTAGE_LOW:	
			{
				strLogType = ConvertString("Temperature Alarm");
				strLogContext.Format("%s", ConvertString("Temperature is too low"));
			}
			break;
		case DH_NEWLOG_ALM_BATTERY_LOW:	
			{
				strLogType = ConvertString("Battery Alarm");
				strLogContext.Format("%s", ConvertString("Low Battery"));
			}
			break;
		case DH_NEWLOG_ALM_ACC_BREAK:
			{
				strLogType = ConvertString("ACC OFF");
				strLogContext.Format("%s", ConvertString("ACC OFF"));
			}
			break;
		case DH_NEWLOG_ALM_ACC_RES:
			{
				strLogType = ConvertString("ACC ON");
				if(pLogItem != NULL)
				{
					strLogContext.Format("%s", ConvertString("ACC ON"));
				}
			}
		    break;
		case DH_NEWLOG_GPS_SIGNAL_LOST:
			{
				strLogType = ConvertString("GPS No Signal");
			}
			break;
		case DH_NEWLOG_GPS_SIGNAL_RESUME:
			{
				strLogType = ConvertString("GPS Signal Resumed");
			}
			break;
		case DH_NEWLOG_3G_SIGNAL_LOST:
			{
				strLogType = ConvertString("3G No Signal");
			}
			break;
		case DH_NEWLOG_3G_SIGNAL_RESUME:
			{
				strLogType = ConvertString("3G Signal Resumed");
			}
		    break;
		case DH_NEWLOG_ALM_IPC_IN:
			{
				strLogType = ConvertString("IPC Alarm ON");
			}
			break;
		case DH_NEWLOG_ALM_IPC_END:
			{
				strLogType = ConvertString("IPC Alarm OFF");
			}
			break;
		case DH_NEWLOG_ALM_DIS_IN:
			{
				strLogType = ConvertString("Disconnet Alarm");
			}
			break;
		case DH_NEWLOG_ALM_DIS_END:
			{
				strLogType = ConvertString("Disconnet Resumed");
			}
		    break;
		case DH_NEWLOG_INFRAREDALM_IN :
			{
				strLogType = ConvertString("Infrared Alarm");
				strLogContext.Format("Channel No.%d", pLogItem->data);
			}
			break;
		case DH_NEWLOG_INFRAREDALM_END:
			{
				strLogType = ConvertString("Infrared Alarm End");
				strLogContext.Format("Channel No.%d", pLogItem->data);
			}
			break;
		case DH_NEWLOG_IPCONFLICT:
			{
				strLogType = ConvertString("IP Conflict");
				
				if (1 == pLogItem->data)
				{
					strLogContext.Format(ConvertString("Wireless"));
				}
			}
			break;
		case DH_NEWLOG_IPCONFLICT_RESUME:			
			{
				strLogType = ConvertString("IP Conflict Resumed");
				
				if (1 == pLogItem->data)
				{
					strLogContext.Format(ConvertString("Wireless"));
				}
			}
			break;
		case DH_NEWLOG_SDPLUG_IN:       
			{
				strLogType = ConvertString("SD card Alarm");
				strLogContext.Format("%s",ConvertString("SD card inserted"));
			}
			break;					
		case DH_NEWLOG_SDPLUG_OUT:      
			{
				strLogType = ConvertString("SD card Alarm");
				strLogContext.Format("%s",ConvertString("SD card pulled out"));
			}
			break;
		case DH_NEWLOG_NET_PORT_BIND_FAILED:
			{
				strLogType = ConvertString("Failed to bind port");
			}
			break;
		case DH_NEWLOG_HDD_BEEP_RESET:      
			{
				strLogType = ConvertString("Beep reset alarm");
				strLogContext.Format("%s",ConvertString("Hard disk error beep reset"));
			}
			break;
		case DH_NEWLOG_MAC_CONFLICT:
			{
				strLogType = ConvertString("MAC Conflict");
			}
			break;
		case DH_NEWLOG_MAC_CONFLICT_RESUME:
			{
				strLogType = ConvertString("MAC Conflict Resumed");
			}
			break;
		case DH_NEWLOG_ALARM_OUT:
			{
				strLogType = ConvertString("Alarm out status");
			}
			break;
		case DH_NEWLOG_ALM_RAID_STAT_EVENT:
			{
				strLogType = ConvertString("Raid status changed");
			}
			break;
		case DH_NEWLOG_ABLAZE_ON:
			{
				strLogType = ConvertString("Ablaze ON");
			}
			break;
		case DH_NEWLOG_ABLAZE_OFF:
			{
				strLogType = ConvertString("Ablaze OFF");
			}
		    break;
		case DH_NEWLOG_INTELLI_ALARM_PLUSE:
			{
				strLogType = ConvertString("Intelligent pluse alarm");
			}
			break;
		case DH_NEWLOG_INTELLI_ALARM_IN:
			{
				strLogType = ConvertString("Intelligent alarm begin");
			}
			break;
		case DH_NEWLOG_INTELLI_ALARM_END:
			{
				strLogType = ConvertString("Intelligent alarm end");
			}
			break;
		case DH_NEWLOG_3G_SIGNAL_SCAN:
			{
				strLogType = ConvertString("3G Signal Scan");
			}
			break;
		case DH_NEWLOG_GPS_SIGNAL_SCAN:
			{
				strLogType = ConvertString("GPS Signal Scan");
			}
		    break;
		case DH_NEWLOG_AUTOMATIC_RECORD:
			{
				strLogType = ConvertString("Automatic Record");
			}
			break;
		case DH_NEWLOG_MANUAL_RECORD:
			{
				strLogType = ConvertString("Manual recording is beginning");
				strLogContext.Format(ConvertString("Manual recording is beginning，channel mask：0x%x"), *(DWORD*)pLogItem->context);
			}
			break;
		case DH_NEWLOG_CLOSED_RECORD:
			{
				strLogType = ConvertString("Stop Manual Recording");
				strLogContext.Format(ConvertString("Stop manual recording，channel mask：0x%x"), *(DWORD*)pLogItem->context);
			}
			break;
		case DH_NEWLOG_LOGIN:
			{
				strLogType = ConvertString("Login");
				strLogContext.Format(ConvertString("User login：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_LOGOUT:
			{
				strLogType = ConvertString("Logout");
				strLogContext.Format(ConvertString("User logout：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_ADD_USER:
			{
				strLogType = ConvertString("Add User");
				strLogContext.Format(ConvertString("Add user：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_DELETE_USER:
			{
				strLogType = ConvertString("Delete User");
				strLogContext.Format(ConvertString("Delete user：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_MODIFY_USER:
			{
				strLogType = ConvertString("Modify User");
				strLogContext.Format(ConvertString("Modify user info：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_ADD_GROUP:
			{
				strLogType = ConvertString("Add User Group");
				strLogContext.Format(ConvertString("Add user group：group name：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_DELETE_GROUP:
			{
				strLogType = ConvertString("Delete User Group");
				strLogContext.Format(ConvertString("Delete user group：group name：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_MODIFY_GROUP:
			{
				strLogType = ConvertString("Modify User Group");
				strLogContext.Format(ConvertString("Modify user group：group name：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_NET_LOGIN:
			{
				strLogType = ConvertString("Net User Login");
				
				if (pLogItem != NULL)
				{
					strLogContext.Format("IP: %d.%d.%d.%d", pLogItem->context[0], pLogItem->context[1], pLogItem->context[2], pLogItem->context[3]);
				}
			}
		    break;
		case DH_NEWLOG_CLEAR:
			{
				strLogType = ConvertString("clean log");
				strLogContext.Format(ConvertString("Clean log，User name：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_SEARCHLOG:
			{
				strLogType = ConvertString("Search Log");
				strLogContext.Format(ConvertString("Search log，User name：%s"), pLogItem->context);
			}
			break;
		case DH_NEWLOG_SEARCH:
			{
				strLogType = ConvertString("Query Recording");
				LOG_ITEM_RECORD logRecord = {0};
				memcpy(&logRecord, pLogItem->context, sizeof(LOG_ITEM_RECORD));
				strLogContext.Format(ConvertString("Query recording，recording info：time%d-%d-%d %d:%d:%d，channel%d，type%d"),logRecord.time.year+2000, logRecord.time.month, logRecord.time.day,
					logRecord.time.hour, logRecord.time.minute, logRecord.time.second, logRecord.channel,
					logRecord.type);
			}
			break;
		case DH_NEWLOG_DOWNLOAD:
			{
				strLogType = ConvertString("Download Recording File");
				LOG_ITEM_RECORD logRecord = {0};
				memcpy(&logRecord, pLogItem->context, sizeof(LOG_ITEM_RECORD));
				strLogContext.Format(ConvertString("Download recording file，recording info：time%d-%d-%d %d:%d:%d，channel%d，type%d"),logRecord.time.year+2000, logRecord.time.month, logRecord.time.day,
					logRecord.time.hour, logRecord.time.minute, logRecord.time.second, logRecord.channel,
					logRecord.type);
			}
			break;
		case DH_NEWLOG_PLAYBACK:
			{
				strLogType = ConvertString("PlayBack");
				LOG_ITEM_RECORD logRecord = {0};
				memcpy(&logRecord, pLogItem->context, sizeof(LOG_ITEM_RECORD));
				strLogContext.Format(ConvertString("PlayBack，recording info：time%d-%d-%d %d:%d:%d，channel%d，type%d"),logRecord.time.year+2000, logRecord.time.month, logRecord.time.day,
					logRecord.time.hour, logRecord.time.minute, logRecord.time.second, logRecord.channel,
					logRecord.type);
			}
			break;
		case DH_NEWLOG_BACKUP:
			{
				strLogType = ConvertString("Backup Recording File");
				LOG_ITEM_RECORD logRecord = {0};
				memcpy(&logRecord, pLogItem->context, sizeof(LOG_ITEM_RECORD));
				strLogContext.Format(ConvertString("Backup recording file，recording info：time%d-%d-%d %d:%d:%d，channel%d，type%d"),logRecord.time.year+2000, logRecord.time.month, logRecord.time.day,
					logRecord.time.hour, logRecord.time.minute, logRecord.time.second, logRecord.channel,
					logRecord.type);
			}
			break;
		case DH_NEWLOG_BACKUPERROR:
			{
				strLogType = ConvertString("Backup Recording File Failed");
			}
			break;
		case DH_NEWLOG_HDD_START_INFO:
			{
				strLogType = ConvertString("Note the boot-strap's hard disk info");
				strLogContext.Format(ConvertString("Note the boot-strap's hard disk info, %d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_HDD_WORKING_DISK:
			{
				strLogType = ConvertString("Note the disk number after the disk change");
				strLogContext.Format(ConvertString("Note the disk number after the disk change，disk number：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_HDD_OTHER_ERROR:
			{
				strLogType = ConvertString("Disk Other Error");
				strLogContext.Format(ConvertString("Disk Other Error，disk number：%d"), pLogItem->data);
			}
			break;
		case DH_NEWLOG_BACK_UPRT:
			{
				strLogType = ConvertString("Real-time Backup");
			}
			break;
		case DH_NEWLOG_BACKUPCLONE:
			{
				strLogType = ConvertString("Backup Clone");
			}
			break;
		case DH_NEWLOG_DISK_CHANGED:
			{
				strLogType = ConvertString("Disk Changed");
			}
			break;
		case DH_NEWLOG_IMAGEPLAYBACK:
			{
				strLogType = ConvertString("Image Playback");
			}
			break;
		case DH_NEWLOG_LOCKFILE:
			{
				strLogType = ConvertString("Lock File");
			}
			break;
		case DH_NEWLOG_UNLOCKFILE:
			{
				strLogType = ConvertString("Unlock File");
			}
			break;
		case DH_NEWLOG_ATMPOS:
			{
				strLogType = ConvertString("ATM POS");
			}
			break;
		case DH_NEWLOG_TIME_UPDATE:
			{
				strLogType = ConvertString("Time Update");
				if (pLogItem != NULL)
				{
					strLogContext.Format("%s",ConvertString("Time Update"));
				}
			}
			break;
		case DH_NEWLOG_REMOTE_STATE:
			{
				strLogType = ConvertString("Remote State");
			}
			break;
		case DH_NEWLOG_USER_DEFINE:
			{
				strLogType = ConvertString("User Define");
			}
			break;
		default:
			break;
		}
		strLogContext = strOperator+strLogContext;
		InsertListViewItem(strLogType,strLogTime,strLogContext);
	}
	CString strNum;
	strNum.Format("%d", m_ctlQueryResult.GetItemCount());
	MessageBox(strNum, ConvertString("Prompt"));
}

CString CClientDemo6Dlg::ConvertCfgType(const DH_LOG_ITEM* pLogItem)
{
	if (pLogItem==NULL)
	{
		return "";
	}

	CString strCfgType = "";
	int nCfgType = (int)pLogItem->data;
	switch(nCfgType)
	{
	case 0:
		strCfgType = ConvertString("normal config");
		break;
	case 1:
		strCfgType = ConvertString("COM config");
		break;
	case 2:
		strCfgType = ConvertString("Network config");
	    break;
	case 3:
		strCfgType = ConvertString("Record config");
	    break;
	case 4:
		strCfgType = ConvertString("Image Setting");
		break;
	case 5:
		strCfgType = ConvertString("PTZ config");
		break;
	case 6:
		strCfgType = ConvertString("Dynamic Detecting config");
	    break;
	case 7:
		strCfgType = ConvertString("Alarm config");
	    break;
	case 8:
		strCfgType = ConvertString("Show Setting");
	    break;
	case 10:
		strCfgType = ConvertString("Channel Title Setting");
	    break;
	case 11:
		strCfgType = ConvertString("Mail Setting");
	    break;
	case 12:
		strCfgType = ConvertString("Preview Setting");
	    break;
	case 13:
		strCfgType = ConvertString("pppoe setting");
	    break;
	case 14:
		strCfgType = ConvertString("DDNS setting");
	    break;
	case 15:
		strCfgType = ConvertString("Realplay Capture Setting");
	    break;
	case 16:
		strCfgType = ConvertString("coding information");
	    break;
	case 18:
		strCfgType = ConvertString("Auto Maintain");
		break;
	case 19:
		strCfgType = ConvertString("ntp config");
		break;
	case 24:
		strCfgType = ConvertString("DSP Max Rate");
		break;
	case 29:
		strCfgType = ConvertString("Water Mark");
		break;
	case 30:
		strCfgType = ConvertString("MATRIX");
		break;
	case 34:
		strCfgType = ConvertString("Video Cover");
		break;
	case 35:
		strCfgType = ConvertString("DHCP");
		break;
	case 36:
		strCfgType = ConvertString("WEB");
		break;
	case 37:
		strCfgType = ConvertString("FTP config");
		break;
	case 38:
		strCfgType = ConvertString("Camera Properties config");
		break;
	case 39:
		strCfgType = ConvertString("Wireless Module config");
		break;
	case 40:
		strCfgType = ConvertString("DNS");
		break;
	case 42:
		strCfgType = ConvertString("Download Recording File");
		break;
	case 43:
		strCfgType = ConvertString("Audio Format");
		break;
	case 44:
		strCfgType = ConvertString("Video OSD config");
		break;
	case 46:
		strCfgType = ConvertString("Machine config");
		break;
	case 49:
		strCfgType = ConvertString("UPNP");
		break;
	case 60:
		strCfgType = ConvertString("Local alarmName config");
		break;
	case 61:
		strCfgType = ConvertString("Alarm in method config");
		break;
	case  100:
		strCfgType.Format("%s:%d.%d.%d.%d", ConvertString("IP Modify"), pLogItem->context[0], pLogItem->context[1], pLogItem->context[2], pLogItem->context[3]);
		break;
	case  101:
		strCfgType.Format("%s:%d.%d.%d.%d", ConvertString("Gateway Modify"), pLogItem->context[0], pLogItem->context[1], pLogItem->context[2], pLogItem->context[3]);
		break;
	case  102:
		strCfgType.Format("%s:%d.%d.%d.%d", ConvertString("Subnetwork Modify"), pLogItem->context[0], pLogItem->context[1], pLogItem->context[2], pLogItem->context[3]);
		break;
	case 120:
		strCfgType = ConvertString("Alarm center config");
		break;
	case 123:
		strCfgType = ConvertString("New Record Setting");
		break;
	case 124:
		strCfgType = ConvertString("Event Config");
		break;
	case 125:
		strCfgType = ConvertString("WorkSheet");
		break;
	case 126:
		strCfgType = ConvertString("color information");
	    break;
	case 127:
		strCfgType = ConvertString("Image Setting");
	    break;
	case 128:
		strCfgType = ConvertString("Image Setting");
	    break;
	case 131:
		strCfgType = ConvertString("Wifi config");
	    break;
	case 133:
		strCfgType = ConvertString("Transfer Policy config");
	    break;
	case 135:
		strCfgType = ConvertString("Wifi scanning");
		break;
	case 136:
		strCfgType = ConvertString("Backup config");
		break;
	case 137:
		strCfgType = ConvertString("RTSP config");
		break;
	case 140:
		strCfgType = ConvertString("DDNS config");
	    break;
	case 141:
		strCfgType = ConvertString("SNMP config");
	    break;
	case 142:
		strCfgType = ConvertString("ISCSI config");
	    break;
	case 154:
		strCfgType = ConvertString("AES encrypt info");
	    break;
	case 156:
		strCfgType = ConvertString("SNAP upload config");
	    break;
	case 190:
		strCfgType = ConvertString("Platform access configuration");
	    break;
	case 200:
		strCfgType = ConvertString("Camera IPC configuration");
	    break;
	case 201:
		strCfgType = ConvertString("Local configuration");
	    break;
	case 202:
		strCfgType = ConvertString("GUI configuration");
	    break;
	case 203:
		strCfgType = ConvertString("Record Worksheet configuration");
	    break;
	case 204:
		strCfgType = ConvertString("PTZ linkage alarm configuration");
	    break;
	case 205:
		strCfgType = ConvertString("Network Alarm configuration");
	    break;
	case 206:
		strCfgType = ConvertString("Alarm worksheet configuration");
	    break;
	case 207:
		strCfgType = ConvertString("Motion worksheet configuration");
	    break;
	case 208:
		strCfgType = ConvertString("PTZ Preset point");
	    break;
	case 209:
		strCfgType = ConvertString("PTZ tour");
	    break;
	case 210:
		strCfgType = ConvertString("Video Lost");
	    break;
	case 211:
		strCfgType = ConvertString("Video Blind");
	    break;
	case 212:
		strCfgType = ConvertString("Playback");
	    break;
	case 213:
		strCfgType = ConvertString("User configuration");
	    break;
	case 214:
		strCfgType = ConvertString("User Group configuration");
	    break;
	case 215:
		strCfgType = ConvertString("Monitor Tour");
	    break;
	case 216:
		strCfgType = ConvertString("TV Adjust");
	    break;
	case 217:
		strCfgType = ConvertString("ATM configuration");
	    break;
	case 218:
		strCfgType = ConvertString("No Hard Disk");
	    break;
	case 219:
		strCfgType = ConvertString("Hard Disk Error");
	    break;
	case 220:
		strCfgType = ConvertString("Hard Disk Nospace");
	    break;
	case 221:
		strCfgType = ConvertString("Broken network events");
	    break;
	case 222:
		strCfgType = ConvertString("Video Widget");
	    break;
	case 223:
		strCfgType = ConvertString("Video Matrix");
	    break;
	case 224:
		strCfgType = ConvertString("System Time");
	    break;
	case 225:
		strCfgType = ConvertString("Lost Focus configuration");
	    break;
	case 226:
		strCfgType = ConvertString("Lost Focus Worksheet configuration");
	    break;
	case 227:
		strCfgType = ConvertString("Scene change configuration");
	    break;
	case 228:
		strCfgType = ConvertString("Scene change worksheet configuration");
	    break;
	case 230:
		strCfgType = ConvertString("Network configuration");
	    break;
	case 231:
		strCfgType = ConvertString("FTP Server configuration");
	    break;
	case 232:
		strCfgType = ConvertString("FTP Application configuration");
	    break;
	case 233:
		strCfgType = ConvertString("IP Filter");
	    break;
	case 234:
		strCfgType = ConvertString("Multicast configuration");
	    break;
	case 235:
		strCfgType = ConvertString("PPPOE configuration");
	    break;
	case 236:
		strCfgType = ConvertString("DDNS configuration");
	    break;
	case 237:
		strCfgType = ConvertString("Alarm Server configuration");
	    break;
	case 238:
		strCfgType = ConvertString("NTP configuration");
	    break;
	case 239:
		strCfgType = ConvertString("Email configuration");
	    break;
	case 240:
		strCfgType = ConvertString("Sniffer configuration");
		break;
	case 243:
		strCfgType = ConvertString("Backup configuration");
		break;
	case 245:
		strCfgType = ConvertString("Motion Record State");
		break;
	case 246:
		strCfgType = ConvertString("Storage configuration");
		break;
	case 247:
		strCfgType = ConvertString("NVD TV Config");
		break;
	default:
		strCfgType = ConvertString("new type");
	    break;
	}

	return strCfgType;
}

void CClientDemo6Dlg::OnButtonPrePage() 
{
	UpdateData(TRUE);
	if (m_dataBegin > m_dataEnd || (m_dataBegin == m_dataEnd && m_timeBegin > m_timeEnd))
	{
		MessageBox(ConvertString("Bad time set!"), ConvertString("Prompt"));
		return;
	}
	
	QUERY_DEVICE_LOG_PARAM stuLogParam;
	memset(&stuLogParam, 0, sizeof(QUERY_DEVICE_LOG_PARAM));
	int nIndex = m_ctlQueryType.GetCurSel();
	stuLogParam.emLogType = (DH_LOG_QUERY_TYPE)m_ctlQueryType.GetItemData(nIndex);
	if (m_nPreStartNum - m_nPageLine > 0)
	{
		stuLogParam.nStartNum = m_nPreStartNum - m_nPageLine;
	}
	else
	{
		stuLogParam.nStartNum = 0;
	}
	stuLogParam.nEndNum = m_nPreEndNum - m_nPageLine - 1;	
	int nPreEndNum = stuLogParam.nEndNum + 1;
	int nPreStartNum = stuLogParam.nStartNum;
	stuLogParam.nLogStuType = 1;
	stuLogParam.stuStartTime.dwYear = m_dataBegin.GetYear();
	stuLogParam.stuStartTime.dwMonth = m_dataBegin.GetMonth();
	stuLogParam.stuStartTime.dwDay = m_dataBegin.GetDay();
	stuLogParam.stuStartTime.dwHour = m_timeBegin.GetHour();
	stuLogParam.stuStartTime.dwMinute = m_timeBegin.GetMinute();
	stuLogParam.stuStartTime.dwSecond = m_timeBegin.GetSecond();
	
	stuLogParam.stuEndTime.dwYear = m_dataEnd.GetYear();
	stuLogParam.stuEndTime.dwMonth = m_dataEnd.GetMonth();
	stuLogParam.stuEndTime.dwDay = m_dataEnd.GetDay();
	stuLogParam.stuEndTime.dwHour = m_timeEnd.GetHour();
	stuLogParam.stuEndTime.dwMinute = m_timeEnd.GetMinute();
	stuLogParam.stuEndTime.dwSecond = m_timeEnd.GetSecond();
	
	DH_DEVICE_LOG_ITEM_EX *szLogInfos = new DH_DEVICE_LOG_ITEM_EX[1024];
	memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
	int nRetLogNum = 0;
	BOOL bRet = CLIENT_QueryDeviceLog(m_LoginID, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum, DEMO_SDK_WAITTIME);
	if (bRet)
	{
		//display log info
		if (nRetLogNum <= 0)
		{
			MessageBox(ConvertString("No record!"), ConvertString("Prompt"));
			return;
		}
		// not enough, continue
		else if (nRetLogNum < m_nPageLine)
		{
			DisPlayNewLogInfo(szLogInfos, nRetLogNum);
			
			int nTotal = nRetLogNum;
			do 
			{
				memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
				stuLogParam.nStartNum = nPreStartNum + nTotal;
				stuLogParam.nEndNum = nPreEndNum - 1;
				bRet = CLIENT_QueryDeviceLog(m_LoginID, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum, DEMO_SDK_WAITTIME);
				if (bRet)
				{
					// no more
					if (nRetLogNum <= 0)
					{
						break;
					}
					DisPlayNewLogInfo(szLogInfos, nRetLogNum, TRUE);
					nTotal += nRetLogNum;
				}
				else
				{
					MessageBox(ConvertString("Query log failed!"), ConvertString("Prompt"));
					return;
				}
				
			} while (nTotal < m_nPageLine);
		}
		else
		{
			DisPlayNewLogInfo(szLogInfos, nRetLogNum);
		}

		m_nPreStartNum = nPreStartNum;
		m_nPreEndNum = nPreEndNum;
		
		//tell if there has more logs
		if (m_nPreStartNum == 0)
		{
			GetDlgItem(IDC_BUTTON_PREPAGE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_NEXTPAGE)->EnableWindow(TRUE);
			return;
		}

		memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
		stuLogParam.nStartNum = m_nPreEndNum - 2;
		stuLogParam.nEndNum = m_nPreEndNum;
		bRet = CLIENT_QueryDeviceLog(m_LoginID, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum, DEMO_SDK_WAITTIME);
		
		GetDlgItem(IDC_BUTTON_NEXTPAGE)->EnableWindow(TRUE);
		if (nRetLogNum > 0)
		{
			GetDlgItem(IDC_BUTTON_PREPAGE)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_PREPAGE)->EnableWindow(FALSE);
		}
	}
	else
	{
		m_ctlQueryResult.DeleteAllItems();
		MessageBox(ConvertString("Query log failed!"), ConvertString("Prompt"));
	}
	delete[] szLogInfos;
}

void CClientDemo6Dlg::OnButtonNextPage() 
{
	UpdateData(TRUE);
	if (m_dataBegin > m_dataEnd || (m_dataBegin == m_dataEnd && m_timeBegin > m_timeEnd))
	{
		MessageBox(ConvertString("Bad time set!"), ConvertString("Prompt"));
		return;
	}
	
	QUERY_DEVICE_LOG_PARAM stuLogParam;
	memset(&stuLogParam, 0, sizeof(QUERY_DEVICE_LOG_PARAM));
	int nIndex = m_ctlQueryType.GetCurSel();
	stuLogParam.emLogType = (DH_LOG_QUERY_TYPE)m_ctlQueryType.GetItemData(nIndex);
	stuLogParam.nStartNum = m_nPreEndNum ;
	stuLogParam.nEndNum = m_nPreEndNum + m_nPageLine - 1;
	m_nPreEndNum = stuLogParam.nEndNum + 1;
	m_nPreStartNum = stuLogParam.nStartNum;
	stuLogParam.nLogStuType = 1;
	stuLogParam.stuStartTime.dwYear = m_dataBegin.GetYear();
	stuLogParam.stuStartTime.dwMonth = m_dataBegin.GetMonth();
	stuLogParam.stuStartTime.dwDay = m_dataBegin.GetDay();
	stuLogParam.stuStartTime.dwHour = m_timeBegin.GetHour();
	stuLogParam.stuStartTime.dwMinute = m_timeBegin.GetMinute();
	stuLogParam.stuStartTime.dwSecond = m_timeBegin.GetSecond();
	
	stuLogParam.stuEndTime.dwYear = m_dataEnd.GetYear();
	stuLogParam.stuEndTime.dwMonth = m_dataEnd.GetMonth();
	stuLogParam.stuEndTime.dwDay = m_dataEnd.GetDay();
	stuLogParam.stuEndTime.dwHour = m_timeEnd.GetHour();
	stuLogParam.stuEndTime.dwMinute = m_timeEnd.GetMinute();
	stuLogParam.stuEndTime.dwSecond = m_timeEnd.GetSecond();
	
	DH_DEVICE_LOG_ITEM_EX *szLogInfos = new DH_DEVICE_LOG_ITEM_EX[1024];
	memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
	int nRetLogNum = 0;
	BOOL bRet = CLIENT_QueryDeviceLog(m_LoginID, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum, DEMO_SDK_WAITTIME);
	if (bRet)
	{
		//display log info
		if (nRetLogNum <= 0)
		{
			MessageBox(ConvertString("No record!"), ConvertString("Prompt"));
			return;
		}
		// not enough, continue
		else if (nRetLogNum < m_nPageLine)
		{
			DisPlayNewLogInfo(szLogInfos, nRetLogNum);
			
			int nTotal = nRetLogNum;
			do 
			{
				memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
				stuLogParam.nStartNum = m_nPreStartNum + nTotal;
				stuLogParam.nEndNum = m_nPreEndNum - 1;
				bRet = CLIENT_QueryDeviceLog(m_LoginID, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum, DEMO_SDK_WAITTIME);
				if (bRet)
				{
					// no more
					if (nRetLogNum <= 0)
					{
						break;
					}
					DisPlayNewLogInfo(szLogInfos, nRetLogNum, TRUE);
					nTotal += nRetLogNum;
				}
				else
				{
					MessageBox(ConvertString("Query log failed!"), ConvertString("Prompt"));
					return;
				}
				
			} while (nTotal < m_nPageLine);
		}
		else
		{
			DisPlayNewLogInfo(szLogInfos, nRetLogNum);
		}
		
		//tell if there has more logs
		memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
		stuLogParam.nStartNum = m_nPreEndNum;
		stuLogParam.nEndNum = m_nPreEndNum + 2;
		bRet = CLIENT_QueryDeviceLog(m_LoginID, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum, DEMO_SDK_WAITTIME);
		
		GetDlgItem(IDC_BUTTON_PREPAGE)->EnableWindow(TRUE);
		if (nRetLogNum > 0)
		{
			GetDlgItem(IDC_BUTTON_NEXTPAGE)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_NEXTPAGE)->EnableWindow(FALSE);
		}
	}
	else
	{
		m_ctlQueryResult.DeleteAllItems();
		MessageBox(ConvertString("Query log failed!"), ConvertString("Prompt"));
	}

	delete[] szLogInfos;
}

void CClientDemo6Dlg::DisPlayNewLogInfo(DH_DEVICE_LOG_ITEM_EX* pLogItem, int nCount, BOOL bAppend/* = FALSE*/)
{
	if(NULL == pLogItem || nCount <= 0)
	{
		return;
	}

	CString strLogType;
	CString strLogTime;
	CString strLogContext;

	if (!bAppend)
	{
		m_ctlQueryResult.DeleteAllItems();
	}

	if(pLogItem->bUnionType == 0)//新日志
	{
		for(int i=0; i< nCount; i++)
		{
			if (!TransLogInfo(&pLogItem[i], 0, strLogType, strLogTime, strLogContext))
			{
				continue;
			}
			
			
			int nIndex = m_ctlQueryType.GetCurSel();
			if(CB_ERR != nIndex)
			{
				DH_LOG_QUERY_TYPE eQueryType = (DH_LOG_QUERY_TYPE)m_ctlQueryType.GetItemData(nIndex);
				if(JudgeType(eQueryType,pLogItem[i].nLogType))
				{
					InsertListViewItem(strLogType,strLogTime,strLogContext);
				}
				else
				{
					CString strTemp;
					strTemp.Format("%s%d",ConvertString("the log information is not to the content of the query,please check-up device, the return log type is:"), pLogItem[i].nLogType);
					MessageBox(strTemp);
					break;
				}
			}// if
		}
	}
	else if(pLogItem->bUnionType == 1)//旧日志
	{
		for(int i=0; i < nCount; i++)
		{
			DH_LOG_ITEM *pOldLogItem = &(pLogItem[i].stuOldLog.stuLog);
		
			if (TransLogInfo(pOldLogItem, 1, strLogType, strLogTime, strLogContext))
			{
				continue;
			}
			
			int nIndex = m_ctlQueryType.GetCurSel();
			if(CB_ERR != nIndex)
			{
				DH_LOG_QUERY_TYPE eQueryType = (DH_LOG_QUERY_TYPE)m_ctlQueryType.GetItemData(nIndex);
				if(JudgeType(eQueryType,pOldLogItem->type))
				{
					InsertListViewItem(strLogType,strLogTime,strLogContext);
				}
				else
				{
					CString strTemp;
					strTemp.Format("%s%d",ConvertString("the log information is not to the content of the query,please check-up device, the return log type is:"), pOldLogItem->type);
					MessageBox(strTemp);
					break;
				}
			}// if
		}// for
	}
}






























































































































