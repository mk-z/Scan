// TourCfg.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "TourCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTourCfg dialog


CTourCfg::CTourCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CTourCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTourCfg)
	m_nInterval = 0;
	m_strIP = _T("");
	m_nPort = 0;
	m_strPwd = _T("");
	m_strUserName = _T("");
	m_nCtrlType = 0;
	m_strDecoderChannel = _T("");
	//}}AFX_DATA_INIT

	m_hCurLoginID = 0;
	m_nTourNum = 0;
	m_nDecChannel = 0;
	memset(&m_stuTourCfgInfo, 0, sizeof(DHDEV_DECODER_TOUR_CFG));
}


void CTourCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTourCfg)
	DDX_Control(pDX, IDC_EDIT_RTSPPORT, m_editRtspport);
	DDX_Control(pDX, IDC_EDIT_HTTPPORT, m_editHttpport);
	DDX_Control(pDX, IDC_COMBO_MANUFACTORY, m_ctlManufactory);
	DDX_Control(pDX, IDC_LIST_TOUR_INFO, m_ctlTourCfgInfo);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ctlType);
	DDX_Control(pDX, IDC_COMBO_DECODERCHANNEL, m_ctlDecoderChannel);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctlChannelNo);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_nInterval);
	DDV_MinMaxUInt(pDX, m_nInterval, 0, 120);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDV_MaxChars(pDX, m_strIP, 128);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxUInt(pDX, m_nPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDV_MaxChars(pDX, m_strPwd, 32);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUserName);
	DDV_MaxChars(pDX, m_strUserName, 32);
	DDX_Radio(pDX, IDC_RADIO1, m_nCtrlType);
	DDX_Text(pDX, IDC_STATIC_DECODERCHANNEl, m_strDecoderChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTourCfg, CDialog)
	//{{AFX_MSG_MAP(CTourCfg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_SAVE, OnSave)
	ON_BN_CLICKED(ID_QUERY, OnQuery)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TOUR_INFO, OnClickListTourInfo)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_DELETE_ALL, OnDeleteAll)
	ON_BN_CLICKED(IDC_CONTROL, OnControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTourCfg message handlers

BOOL CTourCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	
	m_ctlTourCfgInfo.SetExtendedStyle(m_ctlTourCfgInfo.GetExtendedStyle() | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlTourCfgInfo.InsertColumn(0, ConvertString("Tour Num"), LVCFMT_LEFT, 80, -1);
	m_ctlTourCfgInfo.InsertColumn(1, ConvertString("IP"), LVCFMT_LEFT, 80, 0);
	m_ctlTourCfgInfo.InsertColumn(2, ConvertString("Port"), LVCFMT_LEFT, 60, 1);
	m_ctlTourCfgInfo.InsertColumn(3, ConvertString("Channel No."), LVCFMT_LEFT, 60, 2);
	m_ctlTourCfgInfo.InsertColumn(4, ConvertString("Type"), LVCFMT_LEFT, 80, 3);
	m_ctlTourCfgInfo.InsertColumn(5, ConvertString("User Name"), LVCFMT_LEFT, 80, 4);
	m_ctlTourCfgInfo.InsertColumn(6, ConvertString("Password"), LVCFMT_LEFT, 60, 5);
	m_ctlTourCfgInfo.InsertColumn(7, ConvertString("Interval"), LVCFMT_LEFT, 80, 6);
	m_ctlTourCfgInfo.InsertColumn(8, ConvertString("ManuFactory"), LVCFMT_LEFT, 80, 7);
	m_ctlTourCfgInfo.InsertColumn(9, ConvertString("Httpport"), LVCFMT_LEFT, 80, 8);
	m_ctlTourCfgInfo.InsertColumn(10, ConvertString("Rtspport"), LVCFMT_LEFT, 80, 9);

	m_ctlDecoderChannel.ResetContent();
	m_ctlType.ResetContent();
	m_ctlChannelNo.ResetContent();

	CString strText = "";
	int nIndex = 0;
	int i = 0;
	for (i = 0; i < m_nTourNum; i++)
	{
		strText.Format("%d", i+1);
		nIndex = m_ctlDecoderChannel.AddString(strText);
		m_ctlDecoderChannel.SetItemData(nIndex, i);
	}
	m_ctlDecoderChannel.SetCurSel(0);

	for (i = 0; i < 32; i++)
	{
		strText.Format("%d", i+1);
		nIndex = m_ctlChannelNo.AddString(strText);
		m_ctlChannelNo.SetItemData(nIndex, i+1);
	}
	m_ctlChannelNo.SetCurSel(0);

	nIndex = m_ctlType.AddString(ConvertString("main"));
	m_ctlType.SetItemData(nIndex, 0);
	nIndex = m_ctlType.AddString(ConvertString("sub"));
	m_ctlType.SetItemData(nIndex, 1);
	m_ctlType.SetCurSel(0);

	char szBuf[32] = {0};
	m_strDecoderChannel = ConvertString("current decoder channel number: ") + itoa(m_nDecChannel, szBuf, 10);

	InitComboManuFactory();

	UpdateData(FALSE);

	OnQuery(); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTourCfg::SetDlgParam(LLONG lLoginID, int nTourNum, int nDecChannel)
{
	m_hCurLoginID = lLoginID;
	m_nTourNum = nTourNum;
 	m_nDecChannel = nDecChannel;
}

void CTourCfg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CTourCfg::OnSave() 
{
    SaveChannelInfo();

	int nRet = CLIENT_SetDevConfig(m_hCurLoginID, DH_DEV_DECODER_TOUR_CFG, m_nDecChannel, &m_stuTourCfgInfo, sizeof(DHDEV_DECODER_TOUR_CFG), 2000);
	if (nRet) 
	{
		OnQuery();
	}
	else
	{
		MessageBox(ConvertString("Failed to set!"), ConvertString("Prompt"));		
	}	
}

void CTourCfg::OnQuery() 
{
	int nRet = 0;
	DWORD dwRetLen = 0;
	UpdateData(TRUE);
	
	nRet = CLIENT_GetDevConfig(m_hCurLoginID, DH_DEV_DECODER_TOUR_CFG, m_nDecChannel, &m_stuTourCfgInfo, sizeof(DHDEV_DECODER_TOUR_CFG), &dwRetLen, 2000);
	if (nRet && dwRetLen == sizeof(DHDEV_DECODER_TOUR_CFG))
	{
		ShowChannelInfo();	
	}
	else
	{
		MessageBox(ConvertString("Failed to query!"), ConvertString("Prompt"));
	}
}


void CTourCfg::SaveChannelInfo()
{
	UpdateData(TRUE);

	int nNum = m_ctlTourCfgInfo.GetItemCount();

	if (nNum > m_nTourNum || m_nTourNum > 64)
	{
		MessageBox(ConvertString("Beyond the tour support's numbers!"), ConvertString("Prompt"));
		return;
	}

	memset(&m_stuTourCfgInfo, 0, sizeof(DHDEV_DECODER_TOUR_CFG));
	m_stuTourCfgInfo.nCfgNum = nNum;
	
	for (int i = 0; i < nNum; i++)
	{
		DHDEV_DECODER_TOUR_SINGLE_CFG *pInfo = &m_stuTourCfgInfo.tourCfg[i];
		if(NULL != pInfo)
		{
			//ip
			CString strIp = m_ctlTourCfgInfo.GetItemText(i, 1);
			strcpy(pInfo->szIP, strIp.GetBuffer(0));
					
			//port
			pInfo->nPort = atoi(m_ctlTourCfgInfo.GetItemText(i, 2).GetBuffer(0));

			pInfo->nPlayChn = atoi(m_ctlTourCfgInfo.GetItemText(i, 3).GetBuffer(0));

			CString strType = m_ctlTourCfgInfo.GetItemText(i, 4);
			if (strType == ConvertString("sub"))
			{
				pInfo->nPlayType = 1;
			}
			else
			{
				pInfo->nPlayType = 0;
			}

			CString strUserName = m_ctlTourCfgInfo.GetItemText(i, 5);
			strcpy(pInfo->szUserName, strUserName.GetBuffer(0));

			CString strPwd = m_ctlTourCfgInfo.GetItemText(i, 6);
			strcpy(pInfo->szPassword, strPwd.GetBuffer(0));
			pInfo->nInterval = atoi(m_ctlTourCfgInfo.GetItemText(i, 7).GetBuffer(0));
			
			pInfo->nManuFactory = m_ctlTourCfgInfo.GetItemData(i);
			pInfo->nHttpPport = atoi(m_ctlTourCfgInfo.GetItemText(i, 9).GetBuffer(0));
			pInfo->nRtspPort = atoi(m_ctlTourCfgInfo.GetItemText(i,10).GetBuffer(0));

		}
	}
}

void CTourCfg::ShowChannelInfo()
{
	m_ctlTourCfgInfo.DeleteAllItems();
	for (int k = 0; k < m_stuTourCfgInfo.nCfgNum; k++)
	{
		DHDEV_DECODER_TOUR_SINGLE_CFG stuTourInfo = m_stuTourCfgInfo.tourCfg[k];
		CString strNum;
		strNum.Format("%d", k+1);
		CString strIP;
		CString strPort;
		CString strChannelNo;
		CString strType;
		CString strUserName;
		CString strInterval;
		CString strPassword;
		DWORD   dwManuFactory;
		CString strManuFactory;
		CString strHttpport;
		CString strRtspport;
		
		strIP = stuTourInfo.szIP;
		strPort.Format("%d", stuTourInfo.nPort);
		strChannelNo.Format("%d", stuTourInfo.nPlayChn);
		strType = stuTourInfo.nPlayType==0?ConvertString("main"):ConvertString("sub");
		strUserName = stuTourInfo.szUserName;
		strPassword = stuTourInfo.szPassword;
		strInterval.Format("%d", stuTourInfo.nInterval);
		dwManuFactory = stuTourInfo.nManuFactory;
		ChangeManuFactoryToStr(dwManuFactory, strManuFactory.GetBuffer(16), 16);
		strHttpport.Format("%d", stuTourInfo.nHttpPport);
		strRtspport.Format("%d", stuTourInfo.nRtspPort);
		
		
		int nIndex = m_ctlTourCfgInfo.GetItemCount();
		m_ctlTourCfgInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nIndex, strNum, 0, LVIS_SELECTED, 0, 0);
		
		m_ctlTourCfgInfo.SetItemText(nIndex, 1, strIP);
		m_ctlTourCfgInfo.SetItemText(nIndex, 2, strPort);
		m_ctlTourCfgInfo.SetItemText(nIndex, 3, strChannelNo);
		m_ctlTourCfgInfo.SetItemText(nIndex, 4, strType);
		m_ctlTourCfgInfo.SetItemText(nIndex, 5, strUserName);
		m_ctlTourCfgInfo.SetItemText(nIndex, 6, strPassword);
		m_ctlTourCfgInfo.SetItemText(nIndex, 7, strInterval);
		m_ctlTourCfgInfo.SetItemText(nIndex, 8, strManuFactory);
		m_ctlTourCfgInfo.SetItemText(nIndex, 9, strHttpport);
		m_ctlTourCfgInfo.SetItemText(nIndex, 10, strRtspport);

		m_ctlTourCfgInfo.SetItemData(nIndex, dwManuFactory);
	}
}

void CTourCfg::OnClickListTourInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CTourCfg::OnAdd() 
{
	UpdateData(TRUE);

	int nIndex = m_ctlTourCfgInfo.GetItemCount();
	if (nIndex >= m_nTourNum)
	{
		MessageBox(ConvertString("Beyond the tour support's numbers!"), ConvertString("Prompt"));
		return;
	}

	int nTypeIndex = m_ctlType.GetCurSel();
	int nChannelIndex = m_ctlChannelNo.GetCurSel();	
	CString strNum;
	strNum.Format("%d", nIndex + 1);
	CString strIP;
	CString strPort;
	CString strChannelNo;
	CString strType;
	CString strUserName;
	CString strInterval;
	CString strPassword;
	DWORD	dwManuFactory = 0;
	CString strManuFactory;
	CString strHttpport;
	CString strRtspport;
	int nChannelNo = m_ctlChannelNo.GetItemData(nChannelIndex);
	
	strIP = m_strIP;
	strPort.Format("%d", m_nPort);
	strChannelNo.Format("%d", nChannelNo);
	strType = m_ctlType.GetItemData(nTypeIndex)==0?ConvertString("main"):ConvertString("sub");
	strUserName = m_strUserName;
	strPassword = m_strPwd;
	strInterval.Format("%d", m_nInterval);

	if (strIP == "" || m_nInterval < 0 || m_nInterval > 120 || m_nPort < 0 || m_nPort > 65535)
	{
		MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
		return;
	}

	int nIndexManu = m_ctlManufactory.GetCurSel();
	if (nIndexManu!=CB_ERR)
	{
		dwManuFactory = (DWORD)m_ctlManufactory.GetItemData(nIndexManu);
	}

	m_ctlManufactory.GetWindowText(strManuFactory);
	m_editHttpport.GetWindowText(strHttpport);
	m_editRtspport.GetWindowText(strRtspport);

	m_ctlTourCfgInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nIndex, strNum, 0, LVIS_SELECTED, 0, 0);
	
	m_ctlTourCfgInfo.SetItemText(nIndex, 1, strIP);
	m_ctlTourCfgInfo.SetItemText(nIndex, 2, strPort);
	m_ctlTourCfgInfo.SetItemText(nIndex, 3, strChannelNo);
	m_ctlTourCfgInfo.SetItemText(nIndex, 4, strType);
	m_ctlTourCfgInfo.SetItemText(nIndex, 5, strUserName);
	m_ctlTourCfgInfo.SetItemText(nIndex, 6, strPassword);
	m_ctlTourCfgInfo.SetItemText(nIndex, 7, strInterval);
	m_ctlTourCfgInfo.SetItemText(nIndex, 8, strManuFactory);
	m_ctlTourCfgInfo.SetItemText(nIndex, 9, strHttpport);
	m_ctlTourCfgInfo.SetItemText(nIndex, 10, strRtspport);

	m_ctlTourCfgInfo.SetItemData(nIndex, dwManuFactory);

	m_nInterval = 0;
	m_strIP = _T("");
	m_nPort = 0;
	m_strPwd = _T("");
	m_strUserName = _T("");	

	UpdateData(FALSE);
}

void CTourCfg::OnDelete() 
{
	if ( m_ctlTourCfgInfo.GetItemCount() <= 0 )
	{
		MessageBox(ConvertString("No item in the list!"), ConvertString("ERROR"));
		return;
	}
	
	//得到当前list选项
	int nSelect = m_ctlTourCfgInfo.GetSelectionMark();
	if( nSelect < 0 )	
	{
		MessageBox(ConvertString("Please select a item!"), ConvertString("ERROR"));
		return;
	}

	if (MessageBox(ConvertString("Really to delete this item?"), ConvertString("WARING"), MB_YESNO|MB_ICONQUESTION)==IDNO) 
	{
		return;
	}
	
	m_ctlTourCfgInfo.DeleteItem(nSelect);

	UpdateData(FALSE);
}

void CTourCfg::OnDeleteAll() 
{
	if ( m_ctlTourCfgInfo.GetItemCount() <= 0 )
	{
		MessageBox(ConvertString("No item in the list!"), ConvertString("ERROR"));
		return;
	}

	if (MessageBox(ConvertString("Really to delete these items?"), ConvertString("WARING"), MB_YESNO|MB_ICONQUESTION)==IDNO) 
	{
		return;
	}
	
	m_ctlTourCfgInfo.DeleteAllItems();	
}

void CTourCfg::OnControl() 
{
	UpdateData(TRUE);

	DEC_CTRL_TOUR_TYPE emActionParam = (DEC_CTRL_TOUR_TYPE)m_nCtrlType;
	
	if (Dec_Tour_Start == emActionParam)
	{
		DEV_DECODER_TV stDecTVInfo;
		BOOL bRet = CLIENT_QueryDecoderTVInfo(m_hCurLoginID,m_nDecChannel/4,&stDecTVInfo,2000);
		if (bRet )
		{  
			if( stDecTVInfo.stuDevInfo[m_nDecChannel%4].bDevChnEnable)
			{
				DEV_ENCODER_INFO stEncodeInfo;
				stEncodeInfo = stDecTVInfo.stuDevInfo[m_nDecChannel%4];
				stEncodeInfo.bDevChnEnable = 0;
				LLONG lHandle = CLIENT_SwitchDecTVEncoder(m_hCurLoginID,stEncodeInfo.byEncoderID,&stEncodeInfo);
				if (0 == lHandle)
				{
					MessageBox(ConvertString("Switch failed!"), ConvertString("Prompt"));
				}	
			}
		
		}
		else
		{
			AfxMessageBox(ConvertString("Query decoder information failed!"));
		}
	
	}

	int nRet = CLIENT_CtrlDecoderTour(m_hCurLoginID, m_nDecChannel, emActionParam, 1500);
	if (nRet == FALSE)
	{
		MessageBox(ConvertString("Failed to control decoder tour."),  ConvertString("Prompt"));
	}
}


void CTourCfg::InitComboManuFactory()
{
	int ctlIndex = m_ctlManufactory.AddString("dahua");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_PRIVATE);
	ctlIndex = m_ctlManufactory.AddString("Aebell");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_AEBELL);
	ctlIndex = m_ctlManufactory.AddString("Panasonic");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_PANASONIC);
	ctlIndex = m_ctlManufactory.AddString("Sony");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_SONY);
	ctlIndex = m_ctlManufactory.AddString("Dynacolor");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_DYNACOLOR);
	ctlIndex = m_ctlManufactory.AddString("Tcws");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_TCWS);
	ctlIndex = m_ctlManufactory.AddString("Samsung");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_SAMSUNG);
	ctlIndex = m_ctlManufactory.AddString("YOKO");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_YOKO);
	ctlIndex = m_ctlManufactory.AddString("Axis");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_AXIS);
	ctlIndex = m_ctlManufactory.AddString("Sanyo");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_SANYO);
	ctlIndex = m_ctlManufactory.AddString("Bosch");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_BOSH);
	ctlIndex = m_ctlManufactory.AddString("Peclo");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_PECLO);
	ctlIndex = m_ctlManufactory.AddString("Provideo");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_PROVIDEO);
	ctlIndex = m_ctlManufactory.AddString("ACTi");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_ACTI);
	ctlIndex = m_ctlManufactory.AddString("Vivotek");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_VIVOTEK);
	ctlIndex = m_ctlManufactory.AddString("Arecont");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_ARECONT);
	ctlIndex = m_ctlManufactory.AddString("PrivateEH");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_PRIVATEEH);
	ctlIndex = m_ctlManufactory.AddString("IMatek");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_IMATEK);
	ctlIndex = m_ctlManufactory.AddString("Shany");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_SHANY);
	ctlIndex = m_ctlManufactory.AddString("videotrec");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_VIDEOTREC);
	ctlIndex = m_ctlManufactory.AddString("Ura");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_URA);
	ctlIndex = m_ctlManufactory.AddString("Bticino");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_BITICINO);
	ctlIndex = m_ctlManufactory.AddString("Onvif");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_ONVIF);
	ctlIndex = m_ctlManufactory.AddString("Shephero");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_SHEPHERD);
	ctlIndex = m_ctlManufactory.AddString("Yaan");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_YAAN);
	ctlIndex = m_ctlManufactory.AddString("Airpop");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_AIRPOINT);
	ctlIndex = m_ctlManufactory.AddString("TYCO");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_TYCO);
	ctlIndex = m_ctlManufactory.AddString("Xunmei");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_XUNMEI);
	ctlIndex = m_ctlManufactory.AddString("Hikvision");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_HIKVISION);
	ctlIndex = m_ctlManufactory.AddString("LG");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_LG);
	ctlIndex = m_ctlManufactory.AddString("Aoqiman");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_AOQIMAN);
	ctlIndex = m_ctlManufactory.AddString("Baokang");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_BAOKANG);
	ctlIndex = m_ctlManufactory.AddString("Watchnet");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_WATCHNET);
	ctlIndex = m_ctlManufactory.AddString("Xvision");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_XVISION);
	ctlIndex = m_ctlManufactory.AddString("fusitsu");
	m_ctlManufactory.SetItemData(ctlIndex,DH_IPC_FUSITSU);
	
	if (m_ctlManufactory.GetCount()>0)
	{
		m_ctlManufactory.SetCurSel(0);
	}
};



bool CTourCfg::ChangeManuFactoryToStr(UINT dwType, char *pOutBuf, UINT nOutBufLen)
{
	bool bState = true;
	if (pOutBuf == NULL || nOutBufLen!=16)//设备厂商16个字节
	{
		bState = false;
		return bState;
	}

	switch (dwType)
	{
	case DH_IPC_PRIVATE:
		memcpy(pOutBuf, "dahua", sizeof("dahua"));
		break;
	case DH_IPC_AEBELL:
		memcpy(pOutBuf, "Aebell", sizeof("Aebell"));
		break;
	case DH_IPC_PANASONIC:
		memcpy(pOutBuf, "Panasonic", sizeof("Panasonic"));
		break;
	case DH_IPC_SONY:
		memcpy(pOutBuf, "Sony", sizeof("Sony"));
		break;
	case DH_IPC_DYNACOLOR:
		memcpy(pOutBuf, "Dynacolor", sizeof("Dynacolor"));
		break;
	case DH_IPC_TCWS:
		memcpy(pOutBuf, "Tcws", sizeof("Tcws"));
		break;
	case DH_IPC_SAMSUNG:
		memcpy(pOutBuf, "Samsung", sizeof("Samsung"));
		break;
	case DH_IPC_YOKO:
		memcpy(pOutBuf, "YOKO", sizeof("YOKO"));
		break;
	case DH_IPC_AXIS:
		memcpy(pOutBuf, "Axis", sizeof("Axis"));
		break;
	case DH_IPC_SANYO:
		memcpy(pOutBuf, "Sanyo", sizeof("Sanyo"));
		break;
	case DH_IPC_BOSH:
		memcpy(pOutBuf, "Bosch", sizeof("Bosch"));
		break;
	case DH_IPC_PECLO:
		memcpy(pOutBuf, "Pelco", sizeof("Pelco"));
		break;
	case DH_IPC_PROVIDEO:
		memcpy(pOutBuf, "Provideo", sizeof("Provideo"));
		break;
	case DH_IPC_ACTI:
		memcpy(pOutBuf, "ACTi", sizeof("ACTi"));
		break;
	case DH_IPC_VIVOTEK:
		memcpy(pOutBuf, "Vivotek", sizeof("Vivotek"));
		break;
	case DH_IPC_ARECONT:
		memcpy(pOutBuf, "Arecont", sizeof("Arecont"));
		break;
	case DH_IPC_PRIVATEEH:
		memcpy(pOutBuf, "PrivateEH", sizeof("PrivateEH"));
		break;
	case DH_IPC_IMATEK:
		memcpy(pOutBuf, "IMatek", sizeof("IMatek"));
		break;
	case DH_IPC_SHANY:
		memcpy(pOutBuf, "Shany", sizeof("Shany"));
		break;
	case DH_IPC_VIDEOTREC:
		memcpy(pOutBuf, "videotrec", sizeof("videotrec"));
		break;
	case DH_IPC_URA:
		memcpy(pOutBuf, "Ura", sizeof("Ura"));
		break;
	case DH_IPC_BITICINO:
		memcpy(pOutBuf, "Bticino", sizeof("Bticino"));
		break;
	case DH_IPC_ONVIF:
		memcpy(pOutBuf, "Onvif", sizeof("Onvif"));
		break;
	case DH_IPC_SHEPHERD:
		memcpy(pOutBuf, "Shephero", sizeof("Shephero"));
		break;
	case DH_IPC_YAAN:
		memcpy(pOutBuf, "Yaan", sizeof("Yaan"));
		break;
	case DH_IPC_AIRPOINT:
		memcpy(pOutBuf, "Airpop", sizeof("Airpop"));
		break;
	case DH_IPC_TYCO:
		memcpy(pOutBuf, "TYCO", sizeof("TYCO"));
		break;
	case DH_IPC_XUNMEI:
		memcpy(pOutBuf, "Xunmei", sizeof("Xunmei"));
		break;
	case DH_IPC_HIKVISION:
		memcpy(pOutBuf, "Hikvision", sizeof("Hikvision"));
		break;
	case DH_IPC_LG:
		memcpy(pOutBuf, "LG", sizeof("LG"));
		break;
	case DH_IPC_AOQIMAN:
		memcpy(pOutBuf, "Aoqiman", sizeof("Aoqiman"));
		break;
	case DH_IPC_BAOKANG:
		memcpy(pOutBuf, "Baokang", sizeof("Baokang"));
		break;
	case DH_IPC_WATCHNET:
		memcpy(pOutBuf, "Watchnet", sizeof("Watchnet"));
		break;
	case DH_IPC_XVISION:
		memcpy(pOutBuf, "Xvision", sizeof("Xvision"));
		break;
	case DH_IPC_FUSITSU:
		memcpy(pOutBuf, "fusitsu", sizeof("fusitsu"));
		break;
	default:
		bState = false;
	}
	return bState;
};
