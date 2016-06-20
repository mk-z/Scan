// NVDSDKDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NVDSDKDemo.h"
#include "NVDSDKDemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_REBOOT_DEVICE       WM_USER+1001
//////////////////////////////////////////////////////////////////////////

void CALLBACK cbDisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser) 
{
	CNVDSDKDemoDlg *dlg = (CNVDSDKDemoDlg *)dwUser;
	if (dlg == NULL)
	{
		return;
	}

	dlg->DevDisConnect(lLoginID, pchDVRIP, nDVRPort);
}

void CALLBACK cbHaveReConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	CNVDSDKDemoDlg *dlg = (CNVDSDKDemoDlg *)dwUser;
	if (dlg == NULL)
	{
		return;
	}

	dlg->DevHaveReconnect(lLoginID, pchDVRIP, nDVRPort);
}

BOOL CALLBACK cbMessCallBack(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	CNVDSDKDemoDlg *dlg = (CNVDSDKDemoDlg *)dwUser;
	if (dlg == NULL)
	{
		return FALSE;
	}

	switch(lCommand)
	{
	case DH_DECODER_DECODE_ABILITY:
		{
			CString str;
			if (pBuf[0] == 1)
			{
				str.Format("Ip=%s, ", pchDVRIP);
				str += ConvertString("Have not enough decode ability");
				str + "!\n";
			}
			else
			{
				str.Format("Ip=%s, ", pchDVRIP);
				str += ConvertString("Decode ability has resumed");
				str += "!\n";
			}
			dlg->MessageBox(str, ConvertString("Prompt"));
		}
		break;
	case DH_REBOOT_EVENT_EX:
		{
			
			dlg->PostMessage(ID_REBOOT_DEVICE, 0, 0);

		}
	default:
	    break;
	}

	return TRUE;
}

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
// CNVDSDKDemoDlg dialog

CNVDSDKDemoDlg::CNVDSDKDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNVDSDKDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNVDSDKDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bUpdataTree1 = FALSE;
	m_bUpdataTree2 = FALSE;
	for (int i = 0; i < SPLIT16; i++)
	{
		for (int j = 0; j < SPLIT16; j++)
		{
			m_stuShowWindow[i][j].lDecLoginID = 0;
			m_stuShowWindow[i][j].nEncoderNum = -1;
			m_stuShowWindow[i][j].nPlayType = -1;
		}
	}
}

void CNVDSDKDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNVDSDKDemoDlg)
	DDX_Control(pDX, IDC_TREE_ENCODER, m_encoderTree);
	DDX_Control(pDX, IDC_TREE_DECODER, m_decoderTree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNVDSDKDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CNVDSDKDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_ENCODER, OnDblclkTreeEncoder)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_DECODER, OnDblclkTreeDecoder)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(ID_REBOOT_DEVICE, OnRebootDevice)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNVDSDKDemoDlg message handlers

void CALLBACK MessDataCallBackFunc(LLONG lCommand, LPNET_CALLBACK_DATA lpData, LDWORD dwUser)
{
	CNVDSDKDemoDlg *dlg = (CNVDSDKDemoDlg *)dwUser;
	if (dlg == NULL || lpData == NULL)
	{
		return;
	}

	dlg->MessDataCallBack(lCommand, lpData);
}

void CNVDSDKDemoDlg::MessDataCallBack(LONG lCommand, LPNET_CALLBACK_DATA lpData)
{
	// 先判断返回值
    if (lpData->nResultCode != 0)
	{
		switch(lCommand)
		{
			case RESPONSE_DECODER_CTRL_TV:
			{
				MessageBox(ConvertString("Control failed!"), ConvertString("Prompt"));
				break;
			}
			case RESPONSE_DECODER_SWITCH_TV:
			{
				MessageBox(ConvertString("Switch failed!"), ConvertString("Prompt"));
				break;
			}
			case RESPONSE_DECODER_PLAYBACK:
			{
				MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
				break;
			}
			default:
			{
				break;
			}
		}
	}

	if (lpData->userdata == NULL)
	{
		return;
	}

	switch(lCommand)
	{
		case RESPONSE_DECODER_CTRL_TV:
		{
			CTRL_TV_PARAM *pCtrlTvParam = (CTRL_TV_PARAM *)lpData->userdata;
			m_screenPannel.SetWndFlash(pCtrlTvParam->nMonitorID, pCtrlTvParam->nWndID, FALSE);

			m_screenPannel.SetMonitorMultiScreen(pCtrlTvParam->nMonitorID, pCtrlTvParam->nSplitType!=1?TRUE:FALSE);

			
			delete pCtrlTvParam;
		}
		break;
		case RESPONSE_DECODER_SWITCH_TV:
		{
			SWITCH_TV_PARAM *pSwitchTvParam = (SWITCH_TV_PARAM*)lpData->userdata;
			m_screenPannel.SetWndFlash(pSwitchTvParam->nMonitorID, pSwitchTvParam->nWndID, FALSE);

			m_stuShowWindow[pSwitchTvParam->nMonitorID][pSwitchTvParam->nWndID].lDecLoginID = pSwitchTvParam->lDecLoginID;
			m_stuShowWindow[pSwitchTvParam->nMonitorID][pSwitchTvParam->nWndID].nEncoderNum = pSwitchTvParam->nEncoderNum;
			m_stuShowWindow[pSwitchTvParam->nMonitorID][pSwitchTvParam->nWndID].nPlayType = pSwitchTvParam->nPlayType;

			
			delete pSwitchTvParam;
		}
	    break;
		case RESPONSE_DECODER_PLAYBACK:
		{
			SWITCH_TV_PARAM *pPlaybackTvParam = (SWITCH_TV_PARAM*)lpData->userdata;
			m_screenPannel.SetWndFlash(pPlaybackTvParam->nMonitorID, pPlaybackTvParam->nWndID, FALSE);

			m_stuShowWindow[pPlaybackTvParam->nMonitorID][pPlaybackTvParam->nWndID].lDecLoginID = pPlaybackTvParam->lDecLoginID;
			m_stuShowWindow[pPlaybackTvParam->nMonitorID][pPlaybackTvParam->nWndID].nEncoderNum = pPlaybackTvParam->nEncoderNum;
			m_stuShowWindow[pPlaybackTvParam->nMonitorID][pPlaybackTvParam->nWndID].nPlayType = pPlaybackTvParam->nPlayType;
			
			delete pPlaybackTvParam;
		}
		break;
		default:
	    break;
	}
}

void CALLBACK DecPlayBackPosFunc(LLONG lLoginID, int nEncoderID, DWORD dwTotalSize, DWORD dwPlaySize, LDWORD dwUser)
{
	CNVDSDKDemoDlg *dlg = (CNVDSDKDemoDlg *)dwUser;
	if (dlg == NULL)
	{
		return;
	}

	dlg->DecPlayBackPosCallback(lLoginID, nEncoderID, dwTotalSize, dwPlaySize, dwUser);
}

void CNVDSDKDemoDlg::DecPlayBackPosCallback(LLONG lLoginID, int nEncoderID, DWORD dwTotalSize, DWORD dwPlaySize, LDWORD dwUser)
{
	CReadWriteMutexLock lock(m_csDecoder);
	
	list<DECODER_INFO*>::iterator it = m_lstDecoders.begin();
	while (it != m_lstDecoders.end())
	{
		DECODER_INFO *pDecoderInfo = (DECODER_INFO *)(*it);
		if (pDecoderInfo != NULL)
		{
			if (pDecoderInfo->lLoginID == lLoginID)
			{
				if (nEncoderID < NVD_ENCODER_MAX)
				{
					pDecoderInfo->dwTotalSize[nEncoderID] = dwTotalSize;
					pDecoderInfo->dwCurSize[nEncoderID] = dwPlaySize;
				}
				break;
			}
		}
		
		++it;
	}
	lock.Unlock();
}


BOOL CNVDSDKDemoDlg::OnInitDialog()
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
	InitControl();
	InitSDK();
	m_nTimerID1 = SetTimer(1, 1000, NULL);
	m_nTimerID2 = SetTimer(2, 1000, NULL);

	m_dlgProcess.Create(IDD_DLG_PLAYBACK_PROCESS, this);
	m_dlgProcess.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNVDSDKDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNVDSDKDemoDlg::OnPaint() 
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
//		CDialog::OnPaint();

		CPaintDC dc(this);
		CBrush brush;
		CRect rect;

		GetClientRect(&rect);
		brush.CreateSolidBrush(RGB(204,206,213));
		dc.FillRect(&rect, &brush);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNVDSDKDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNVDSDKDemoDlg::UpdatePannelPosition()
{
	CRect screenRect;
	GetDlgItem(IDC_SCREEN_WINDOW)->GetWindowRect(&screenRect);
	ScreenToClient(&screenRect);
	m_screenPannel.MoveWindow(screenRect);
}

void CNVDSDKDemoDlg::InitControl()
{
	m_screenPannel.Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 1981);
	UpdatePannelPosition();
	m_screenPannel.ShowWindow(SW_SHOW);
	m_screenPannel.SetShowWindow(SPLIT4, SPLIT16);

	m_pannelDecoder.Create(IDD_PANNEL_DECODER, this);
	m_pannelDecoder.ShowWindow(SW_SHOW);

	m_pannelEncoder.Create(IDD_PANNEL_ENCODER, this);
	m_pannelEncoder.ShowWindow(SW_SHOW);
}

void CNVDSDKDemoDlg::InitSDK()
{
	CLIENT_Init(cbDisConnectFunc, (DWORD)this);
	CLIENT_SetAutoReconnect(cbHaveReConnectFunc, (DWORD)this);
	CLIENT_SetDVRMessCallBack(cbMessCallBack, (DWORD)this);
}

void CNVDSDKDemoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	{
		CReadWriteMutexLock lock(m_csDevice);
		list<DEVICE_INFO*>::iterator it = m_lstDevices.begin();
		while (it != m_lstDevices.end())
		{
			DEVICE_INFO *pDevInfo = (DEVICE_INFO*)(*it);
			if (pDevInfo != NULL)
			{
				delete pDevInfo;
			}
			it++;
		}
		m_lstDevices.clear();
	}

	{
		CReadWriteMutexLock lock(m_csDecoder);
		list<DECODER_INFO*>::iterator it = m_lstDecoders.begin();
		while (it != m_lstDecoders.end())
		{
			DECODER_INFO *pDecInfo = (DECODER_INFO*)(*it);
			if (pDecInfo != NULL)
			{
				delete pDecInfo;
			}
			it++;
		}
		m_lstDecoders.clear();
	}
	CLIENT_Cleanup();

	KillTimer(m_nTimerID1);
	KillTimer(m_nTimerID2);
	
	CDialog::OnClose();
}

void CNVDSDKDemoDlg::UpdateDeviceList()
{
	CReadWriteMutexLock lock(m_csDevice);

	m_encoderTree.DeleteAllItems();
	
	list<DEVICE_INFO*>::iterator it = m_lstDevices.begin();
	while (it != m_lstDevices.end())
	{
		DEVICE_INFO *pDeviceInfo = (DEVICE_INFO *)(*it);
		if (pDeviceInfo != NULL)
		{
			CString strItemName = pDeviceInfo->strDevName;
			strItemName += " (";
			strItemName += pDeviceInfo->strDevIp;
			strItemName += ")(";
			strItemName += pDeviceInfo->bIsOnline? ConvertString("online") : ConvertString("offline");
			strItemName += ")";

			HTREEITEM hRootItem = m_encoderTree.InsertItem(strItemName, TVI_ROOT, TVI_LAST);
			m_encoderTree.SetItemData(hRootItem, (DWORD)pDeviceInfo);

			for (int i = 0; i < pDeviceInfo->nDevChannel; i++)
			{
				strItemName.Format(" %d", i);
				strItemName = ConvertString("Channel") + strItemName;
				HTREEITEM hLeafItem = m_encoderTree.InsertItem(strItemName, hRootItem, TVI_LAST);
				m_encoderTree.SetItemData(hLeafItem, i);

				//码流类型
				for(int j = 0; j < 3; j++)
				{
					if (j == 0) 
					{
						strItemName = ConvertString("Main");
					}
					else if (j == 1)
					{
						strItemName = ConvertString("Sub");
					}
					else
					{
						strItemName = ConvertString("Snap");
					}

					HTREEITEM hLeafStreamItem = m_encoderTree.InsertItem(strItemName, hLeafItem, TVI_LAST);
					m_encoderTree.SetItemData(hLeafStreamItem, j);
				}
			}

			m_encoderTree.Expand(hRootItem, TVE_EXPAND);
		}

		++it;
	}

	if (m_encoderTree.GetCount() > 0)
	{
		m_encoderTree.SetFocus();
	}
}
				
void CNVDSDKDemoDlg::UpdateDecoderList()
{
	CReadWriteMutexLock lock(m_csDecoder);

	m_decoderTree.DeleteAllItems();
	
	list<DECODER_INFO*>::iterator it = m_lstDecoders.begin();
	while (it != m_lstDecoders.end())
	{
		DECODER_INFO *pDecoderInfo = (DECODER_INFO *)(*it);
		if (pDecoderInfo != NULL)
		{
			CString strItemName = pDecoderInfo->strDecName;
			strItemName += " (";
			strItemName += pDecoderInfo->strDecIp;
			strItemName += ")(";
			strItemName += pDecoderInfo->bIsOnline? ConvertString("online") : ConvertString("offline");
			strItemName += ")";

			HTREEITEM hRootItem = m_decoderTree.InsertItem(strItemName, TVI_ROOT, TVI_LAST);
			m_decoderTree.SetItemData(hRootItem, (DWORD)pDecoderInfo);

			for (int i = 0; i < pDecoderInfo->nDecChannel; i++)
			{
				strItemName.Format("TV %d", i);
				HTREEITEM hLeafItem = m_decoderTree.InsertItem(strItemName, hRootItem, TVI_LAST);
				m_decoderTree.SetItemData(hLeafItem, i);
			}

			m_decoderTree.Expand(hRootItem, TVE_EXPAND);
		}

		++it;
	}

	if (m_decoderTree.GetCount() > 0)
	{
		m_decoderTree.SetFocus();
	}
}

void CNVDSDKDemoDlg::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1 && m_bUpdataTree1)
	{
		m_bUpdataTree1 = FALSE;
		UpdateDeviceList();
		m_screenPannel.Invalidate();
	}
	else if (nIDEvent == 2 && m_bUpdataTree2)
	{
		m_bUpdataTree2 = FALSE;
		UpdateDecoderList();
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CNVDSDKDemoDlg::DevDisConnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort)
{
	{
		CReadWriteMutexLock lock(m_csDevice);
		
		list<DEVICE_INFO*>::iterator it = m_lstDevices.begin();
		while (it != m_lstDevices.end())
		{
			DEVICE_INFO *pDeviceInfo = (DEVICE_INFO *)(*it);
			if (pDeviceInfo != NULL)
			{
				if (pDeviceInfo->lLoginID == lLoginID)
				{
					pDeviceInfo->bIsOnline = FALSE;
					m_bUpdataTree1 = TRUE;
					break;
				}
			}
			
			++it;
		}
		lock.Unlock();
	}

	{
		CReadWriteMutexLock lock(m_csDecoder);
		
		list<DECODER_INFO*>::iterator it = m_lstDecoders.begin();
		while (it != m_lstDecoders.end())
		{
			DECODER_INFO *pDecoderInfo = (DECODER_INFO *)(*it);
			if (pDecoderInfo != NULL)
			{
				if (pDecoderInfo->lLoginID == lLoginID)
				{
					pDecoderInfo->bIsOnline = FALSE;
					m_bUpdataTree2 = TRUE;
					break;
				}
			}
			
			++it;
		}
		lock.Unlock();
	}
}

void CNVDSDKDemoDlg::DevHaveReconnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort)
{
	{
		CReadWriteMutexLock lock(m_csDevice);
		
		list<DEVICE_INFO*>::iterator it = m_lstDevices.begin();
		while (it != m_lstDevices.end())		 
		{
			DEVICE_INFO *pDeviceInfo = (DEVICE_INFO *)(*it);
			if (pDeviceInfo != NULL)
			{
				if (pDeviceInfo->lLoginID == lLoginID)
				{
					pDeviceInfo->bIsOnline = TRUE;
					m_bUpdataTree1 = TRUE;
					break;
				}
			}
			
			++it;
		}
		lock.Unlock();
	}

	{
		CReadWriteMutexLock lock(m_csDecoder);
		
		list<DECODER_INFO*>::iterator it = m_lstDecoders.begin();
		while (it != m_lstDecoders.end())
		{
			DECODER_INFO *pDecoderInfo = (DECODER_INFO *)(*it);
			if (pDecoderInfo != NULL)
			{
				if (pDecoderInfo->lLoginID == lLoginID)
				{
					pDecoderInfo->bIsOnline = TRUE;
					m_bUpdataTree2 = TRUE;
					break;
				}
			}
			
			++it;
		}
		lock.Unlock();
	}
}

void CNVDSDKDemoDlg::OnDblclkTreeEncoder(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nStreamType = 0;
	HTREEITEM enselectNode = m_encoderTree.GetSelectedItem();
	if (enselectNode != NULL)
	{
		HTREEITEM channelNode = NULL;
		HTREEITEM parentNode = m_encoderTree.GetParentItem(enselectNode);
		HTREEITEM childNode = m_encoderTree.GetChildItem(enselectNode);
		
		if (parentNode != NULL && childNode != NULL) 
		{
			channelNode = enselectNode;
		}
		else if (parentNode == NULL && childNode != NULL) 
		{
			channelNode = childNode;
		}
		else
		{
			channelNode = parentNode;	
		}
		
		if (channelNode != NULL) 
		{
			
			DWORD nData = m_encoderTree.GetItemData(channelNode);
			if ( nData <= 32 && nData >= 0)
			{
				HTREEITEM enparentNode = m_encoderTree.GetParentItem(channelNode);
				DEVICE_INFO *pDeviceInfo = (DEVICE_INFO *)m_encoderTree.GetItemData(enparentNode);
				
				if (pDeviceInfo != NULL)
				{
					LONG lLoginHandle = pDeviceInfo->lLoginID;
					int nChannel = nData;
					
					// Send command to nvd
					HTREEITEM selectNode = m_decoderTree.GetSelectedItem();
					if (selectNode != NULL)
					{
						HTREEITEM parentNode = selectNode;
						DWORD nData = m_decoderTree.GetItemData(selectNode);
						if (nData <= 32 && nData >= 0)
						{
							parentNode = m_encoderTree.GetParentItem(selectNode);
						}
						
						DECODER_INFO *pDecoderInfo = (DECODER_INFO *)m_decoderTree.GetItemData(parentNode);
						if (pDecoderInfo != NULL)
						{
							if (_stricmp(m_encoderTree.GetItemText(enselectNode), ConvertString("Sub")) == 0) 
							{
								nStreamType = 1;
							}
							else if(_stricmp(m_encoderTree.GetItemText(enselectNode), ConvertString("Main")) == 0)
							{
								nStreamType = 0;
							}
							else
							{
								nStreamType = 2;
							}
							
							DEV_ENCODER_INFO stuEncoderInfo = {0};
							strcpy(stuEncoderInfo.szDevIpEx, pDeviceInfo->strDevIp);
							strcpy(stuEncoderInfo.szDevUser, pDeviceInfo->strDevUser);
							strcpy(stuEncoderInfo.szDevPwd, pDeviceInfo->strDevPwd);
							stuEncoderInfo.wDevPort = pDeviceInfo->nDevPort;
							stuEncoderInfo.nDevChannel = nChannel;		
							stuEncoderInfo.nStreamType = nStreamType;
							stuEncoderInfo.bDevChnEnable = 1;
							stuEncoderInfo.byConnType = 0;
							stuEncoderInfo.byWorkMode = 0;
							SWITCH_TV_PARAM *pSwitchTvParam = new SWITCH_TV_PARAM;
							pSwitchTvParam->nMonitorID = m_screenPannel.m_nCurMonitorID;
							pSwitchTvParam->nWndID = m_screenPannel.m_nCurWndID;
							pSwitchTvParam->lDecLoginID = pDecoderInfo->lLoginID;
							pSwitchTvParam->nEncoderNum = m_screenPannel.m_nCurMonitorID*4+m_screenPannel.m_nCurWndID;
							pSwitchTvParam->nPlayType = 0;
							LLONG lOperateHandle = CLIENT_SwitchDecTVEncoder(pDecoderInfo->lLoginID, pSwitchTvParam->nEncoderNum, 
								&stuEncoderInfo, pSwitchTvParam);
							if (lOperateHandle == 0)
							{
								delete pSwitchTvParam;
								MessageBox(ConvertString("Switch failed!"), ConvertString("Prompt"));
							}
							else
							{
								m_screenPannel.SetWndFlash(pSwitchTvParam->nMonitorID, pSwitchTvParam->nWndID, TRUE);
							}
						}
					}
				}	
			}
			
		}
		
		*pResult = 0;
	}
}

void CNVDSDKDemoDlg::OnDblclkTreeDecoder(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM selectNode = m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = m_decoderTree.GetItemData(selectNode);
		if (nData <= 32 && nData >= 0)
		{
			parentNode = m_encoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pDecoderInfo = (DECODER_INFO *)m_decoderTree.GetItemData(parentNode);
		if (pDecoderInfo != NULL)
		{
			int nMonitorID = pDecoderInfo->nDecChannel;
			SPLIT_TYPE nMain = SPLIT4;
			if (nMonitorID <= 1)
			{
				nMain = SPLIT1;
			}
			else if (nMonitorID <= 4)
			{
				nMain = SPLIT4;
			}
			else if (nMonitorID <= 9)
			{
				nMain = SPLIT9;
			}
			else if (nMonitorID <= 16)
			{
				nMain = SPLIT16;
			}
			else
			{
				nMain = SPLIT16;
			}
			
			m_screenPannel.SetShowWindow(nMain, SPLIT16);

			for (int i = 0; i < pDecoderInfo->nDecChannel; i++)
			{
				DEV_DECODER_TV stuDevTvInfo = {0};
				stuDevTvInfo.nSplitType = 1;
				BOOL bRet = CLIENT_QueryDecoderTVInfo(pDecoderInfo->lLoginID, i, &stuDevTvInfo, 1000);
				if (bRet)
				{
					m_screenPannel.SetActiveWindow(i, 0);
					m_screenPannel.SetMonitorMultiScreen(i, stuDevTvInfo.nSplitType==1?FALSE:TRUE);
				}
			}
			m_screenPannel.SetActiveWindow(0, 0);
		}
	}
	
	*pResult = 0;
}

void CNVDSDKDemoDlg::OnVideoLButtonDblClk(int nMonitorID, int nWndID, BOOL bMultiScreen, int nSplitNum)
{
	HTREEITEM selectNode = m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = m_decoderTree.GetItemData(selectNode);
		if (nData <= 32 && nData >= 0)
		{
			parentNode = m_encoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pDecoderInfo = (DECODER_INFO *)m_decoderTree.GetItemData(parentNode);
		if (pDecoderInfo != NULL)
		{
			if (!bMultiScreen)
			{
				// from one screen to multi-screen
				BYTE* pbEncoderChannel = new BYTE[nSplitNum];
				for (int i = 0; i < nSplitNum; i++)
				{
					pbEncoderChannel[i] = nMonitorID*nSplitNum + i;
				}

				CTRL_TV_PARAM *pCtrlTVParam = new CTRL_TV_PARAM;
				pCtrlTVParam->nMonitorID = nMonitorID;
				pCtrlTVParam->nWndID = nWndID;
				pCtrlTVParam->nSplitType = nSplitNum;
				LLONG lOperateHandle = CLIENT_CtrlDecTVScreen(pDecoderInfo->lLoginID, nMonitorID, TRUE, nSplitNum, pbEncoderChannel, nSplitNum, pCtrlTVParam);
				delete[] pbEncoderChannel;
				if (lOperateHandle == 0)
				{
					delete pCtrlTVParam;
					MessageBox(ConvertString("Switch failed from one screen to multi-screen!"), ConvertString("Prompt"));
				}
				else
				{
					m_screenPannel.SetWndFlash(nMonitorID, nWndID, TRUE);
				}
			}
			else
			{
				// 多画面变单画面
				BYTE bEncoderChannel = nMonitorID*nSplitNum + nWndID;
				//bEncoderChannel = bEncoderChannel>0?1:bEncoderChannel;
				bEncoderChannel = bEncoderChannel<0?1:bEncoderChannel;

				CTRL_TV_PARAM *pCtrlTVParam = new CTRL_TV_PARAM;
				pCtrlTVParam->nMonitorID = nMonitorID;
				pCtrlTVParam->nWndID = nWndID;
				pCtrlTVParam->nSplitType = 1;
				LLONG lOperateHandle = CLIENT_CtrlDecTVScreen(pDecoderInfo->lLoginID, nMonitorID, TRUE, 1, &bEncoderChannel, 1, pCtrlTVParam);
				if (lOperateHandle == 0)
				{
					delete pCtrlTVParam;
					MessageBox(ConvertString("Switch failed from multi-screen to one screen!"), ConvertString("Prompt"));
				}
				else
				{
					m_screenPannel.SetWndFlash(nMonitorID, nWndID, TRUE);
				}
			}
		}
	}
}

void CNVDSDKDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if ((cx ==0 && cy == 0) || (cx == m_clientRect.Width() && cy == m_clientRect.Height())) 
	{
		return;
	}
	else
	{
		int nRectWidth = 0;
		GetClientRect(&m_clientRect);
		
		CRect decoderRect;
		GetDlgItem(IDC_TREE_DECODER)->GetWindowRect(&decoderRect);
		ScreenToClient(&decoderRect);
		nRectWidth = decoderRect.Width();
		decoderRect.left = m_clientRect.left;
		decoderRect.right = decoderRect.left + nRectWidth;
		decoderRect.top = m_clientRect.top;
		decoderRect.bottom = m_clientRect.bottom - 150;
		GetDlgItem(IDC_TREE_DECODER)->MoveWindow(decoderRect);

		CRect pannelDecoder;
		pannelDecoder.left = m_clientRect.left;
		pannelDecoder.right = pannelDecoder.left + nRectWidth;
		pannelDecoder.top = decoderRect.bottom;
		pannelDecoder.bottom = m_clientRect.bottom;
		m_pannelDecoder.MoveWindow(pannelDecoder);
		
		CRect encoderRect;
		GetDlgItem(IDC_TREE_ENCODER)->GetWindowRect(&encoderRect);
		ScreenToClient(&encoderRect);
		nRectWidth = encoderRect.Width();
		encoderRect.right = m_clientRect.right;
		encoderRect.left = encoderRect.right - nRectWidth;
		encoderRect.top = m_clientRect.top;
		encoderRect.bottom = m_clientRect.bottom - 150;
		GetDlgItem(IDC_TREE_ENCODER)->MoveWindow(encoderRect);

		CRect pannelEncoder;
		pannelEncoder.right = m_clientRect.right;
		pannelEncoder.left = pannelEncoder.right - nRectWidth;
		pannelEncoder.top = encoderRect.bottom;
		pannelEncoder.bottom = m_clientRect.bottom;
		m_pannelEncoder.MoveWindow(pannelEncoder);
		
		CRect videoRect;
		videoRect.left = decoderRect.right + 3;
		videoRect.right = encoderRect.left - 2;
		videoRect.top = m_clientRect.top;
		videoRect.bottom = m_clientRect.bottom;
		GetDlgItem(IDC_SCREEN_WINDOW)->MoveWindow(videoRect);
		UpdatePannelPosition();

		Invalidate();
	}
}


void CNVDSDKDemoDlg::PlaybackSeek(int nOffsetPos)
{
	LLONG lLoinHandle = m_stuShowWindow[m_screenPannel.m_nCurMonitorID][m_screenPannel.m_nCurWndID].lDecLoginID;
	int nEncoderNum = m_stuShowWindow[m_screenPannel.m_nCurMonitorID][m_screenPannel.m_nCurWndID].nEncoderNum;
	int nPlayType = m_stuShowWindow[m_screenPannel.m_nCurMonitorID][m_screenPannel.m_nCurWndID].nPlayType;
	if (lLoinHandle != 0 && nPlayType != 0)
	{
		DWORD dwTotalSize = 0;
		DWORD dwCurSize = 0;
		CReadWriteMutexLock lock(m_csDecoder);
		
		list<DECODER_INFO*>::iterator it = m_lstDecoders.begin();
		while (it != m_lstDecoders.end())
		{
			DECODER_INFO *pDecoderInfo = (DECODER_INFO *)(*it);
			if (pDecoderInfo != NULL)
			{
				if (pDecoderInfo->lLoginID == lLoinHandle)
				{
					if (nEncoderNum < NVD_ENCODER_MAX)
					{
						dwTotalSize = pDecoderInfo->dwTotalSize[nEncoderNum];
						dwCurSize = pDecoderInfo->dwCurSize[nEncoderNum];
					}
					break;
				}
			}
			
			++it;
		}
		lock.Unlock();

		CLIENT_CtrlDecPlayback(lLoinHandle, nEncoderNum, Dec_Playback_Seek, dwTotalSize*nOffsetPos/100);
	}
	else
	{
		MessageBox(ConvertString("Seek failed!"), ConvertString("Prompt"));
	}
}



int CNVDSDKDemoDlg::GetCurWndPlaybackPos()
{
	int nOffsetPos = 0;

	LONG lLoinHandle = m_stuShowWindow[m_screenPannel.m_nCurMonitorID][m_screenPannel.m_nCurWndID].lDecLoginID;
	int nEncoderNum = m_stuShowWindow[m_screenPannel.m_nCurMonitorID][m_screenPannel.m_nCurWndID].nEncoderNum;
	int nPlayType = m_stuShowWindow[m_screenPannel.m_nCurMonitorID][m_screenPannel.m_nCurWndID].nPlayType;
	if (lLoinHandle != 0 && nPlayType != 0)
	{
		CReadWriteMutexLock lock(m_csDecoder);
		
		list<DECODER_INFO*>::iterator it = m_lstDecoders.begin();
		while (it != m_lstDecoders.end())
		{
			DECODER_INFO *pDecoderInfo = (DECODER_INFO *)(*it);
			if (pDecoderInfo != NULL)
			{
				if (pDecoderInfo->lLoginID == lLoinHandle)
				{
					if (nEncoderNum < NVD_ENCODER_MAX)
					{
						DWORD dwTotalSize = pDecoderInfo->dwTotalSize[nEncoderNum];
						DWORD dwCurSize = pDecoderInfo->dwCurSize[nEncoderNum];
						if (dwCurSize == -1)
						{
							nOffsetPos = 100;
						}
						else if (dwTotalSize != 0)
						{
							nOffsetPos = dwCurSize*100/dwTotalSize;
						}
					}
					break;
				}
			}
			
			++it;
		}
		lock.Unlock();
	}

	return nOffsetPos;
}

int CNVDSDKDemoDlg::GetChannelState(int nEncoderID, DEV_DECCHANNEL_STATE *pChannelState)
{
	BOOL bRet = -1;
	if (pChannelState == NULL)
	{
		return bRet;
	}
	
	// 获取对应解码器
	HTREEITEM selectNode = m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = m_encoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pCurDecoderInfo = (DECODER_INFO *)m_decoderTree.GetItemData(parentNode);
		if (pCurDecoderInfo != NULL)
		{
			if (pCurDecoderInfo->lLoginID != 0)
			{
				memset(pChannelState, 0, sizeof(DEV_DECCHANNEL_STATE));
				
				CReadWriteMutexLock lock(m_csDecoder);
				
				list<DECODER_INFO*>::iterator it = m_lstDecoders.begin();
				while (it != m_lstDecoders.end())
				{
					DECODER_INFO *pDecoderInfo = (DECODER_INFO *)(*it);
					if (pDecoderInfo != NULL)
					{
						if (pDecoderInfo->lLoginID != 0 && pCurDecoderInfo->lLoginID == pDecoderInfo->lLoginID)
						{
							if (nEncoderID < NVD_ENCODER_MAX)
							{
								bRet = CLIENT_QueryDecChannelFlux(pDecoderInfo->lLoginID, nEncoderID, pChannelState, 500);
								if (bRet > 0)
								{
								}
							}
							break;
						}
					}
					
					++it;
				}
				lock.Unlock();	
			}
			else
			{
				//	MessageBox("刷新通道状态失败!", "提示");
			}
		}
	}

	return bRet;
}

LRESULT CNVDSDKDemoDlg::OnRebootDevice(WPARAM wParam, LPARAM lParam)
{
	if (IDYES ==MessageBox(ConvertString("IF effect the configuration, the device must be reboot! Do you really want to reboot?"), ConvertString("Reboot"), MB_ICONQUESTION | MB_YESNO)) 
	{
		// 获取对应解码器
		HTREEITEM selectNode = m_decoderTree.GetSelectedItem();
		if (selectNode != NULL)
		{
			HTREEITEM parentNode = selectNode;
			DWORD nData = m_decoderTree.GetItemData(selectNode);
			if (nData <= 16 && nData >= 0)
			{
				parentNode = m_encoderTree.GetParentItem(selectNode);
			}
			
			DECODER_INFO *pDecoderInfo = (DECODER_INFO *)m_decoderTree.GetItemData(parentNode);
			if (pDecoderInfo != NULL)
			{
				if (pDecoderInfo->lLoginID != 0)
				{
					
					BOOL bSuccess = CLIENT_ControlDevice(pDecoderInfo->lLoginID, DH_CTRL_REBOOT, NULL);
					if(bSuccess)
					{
						MessageBox(ConvertString("Succeed to reboot!"), ConvertString("Prompt"));
						m_pannelDecoder.OnBtnDelDecoder();
					}
					else
					{
						MessageBox(ConvertString("Failed to reboot!"), ConvertString("Prompt"));
					}
				}
			}
		}
		
	}	
	return 0;
}

DEVICE_INFO* CNVDSDKDemoDlg::GetSelectEncoderDeviceInfo()
{
    HTREEITEM hDeviceNode = NULL;
    HTREEITEM selectNode = m_encoderTree.GetSelectedItem();
    if (selectNode != NULL)
    {
        // 判断是否有子节点
        HTREEITEM hItem = m_encoderTree.GetChildItem(selectNode);
        if (hItem == NULL) // 没有子节点, 则当前为码流类型节点
        {
            hItem = m_encoderTree.GetParentItem(selectNode); // 通道节点
            if (hItem)
            {
                hDeviceNode = m_encoderTree.GetParentItem(hItem); // 设备节点
            }
        }
        // 子节点还有子节点, 则当前是设备节点
        else if (m_encoderTree.ItemHasChildren(hItem))
        {
            hDeviceNode = selectNode;
        }
        // 通道节点
        else
        {
            hDeviceNode = m_encoderTree.GetParentItem(selectNode);
        }
    }

    if (hDeviceNode)
    {
        return (DEVICE_INFO *)m_encoderTree.GetItemData(hDeviceNode);
    }
    return NULL;
}
