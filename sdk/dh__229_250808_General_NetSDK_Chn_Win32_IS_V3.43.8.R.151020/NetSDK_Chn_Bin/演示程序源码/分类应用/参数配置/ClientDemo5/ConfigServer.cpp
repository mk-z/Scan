// ConfigServer.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigServer.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigServer dialog


CConfigServer::CConfigServer(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigServer::IDD, pParent)
	,m_nReclen(1)
{
	//{{AFX_DATA_INIT(CConfigServer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigServer)
	DDX_Control(pDX, IDC_COMBO_TIMEFMT, m_ctlTimeFormat);
	DDX_Control(pDX, IDC_COMBO_DATESPR, m_ctlDateSpr);
	DDX_Control(pDX, IDC_COMBO_DATEFMT, m_ctlDateFormat);
	DDX_Control(pDX, IDC_COMBO_VIDEOFMT, m_ctlVideoFormat);
	DDX_Control(pDX, IDC_COMBO_OVERWRITE, m_ctlDiskFull);
	DDX_Text(pDX, IDC_EDIT_RECLEN, m_nReclen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigServer, CDialog)
	//{{AFX_MSG_MAP(CConfigServer)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigServer message handlers

BOOL CConfigServer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	InitComboBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//Save configuration information 
void CConfigServer::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	if (!CheckReclenValid())
	{
		return;
	}
	

	//Check input is valid or not 
	if(IsValid())
	{
		//Read input 
		DHDEV_SYSTEM_ATTR_CFG sysConfigInfo = {0};
		sysConfigInfo.wDevNo = GetDlgItemInt(IDC_EDIT_DEVNO);
		sysConfigInfo.byOverWrite = m_ctlDiskFull.GetCurSel();
		sysConfigInfo.byRecordLen = GetDlgItemInt(IDC_EDIT_RECLEN);
		sysConfigInfo.byVideoStandard = m_ctlVideoFormat.GetCurSel();
		sysConfigInfo.byDateFormat = m_ctlDateFormat.GetCurSel();
		sysConfigInfo.byDateSprtr = m_ctlDateSpr.GetCurSel();
		sysConfigInfo.byTimeFmt = m_ctlTimeFormat.GetCurSel();
		//Call father window to save data
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetDeviceConfigInfo(&sysConfigInfo);
	}
	else
	{
		MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
	}
}

//Read configuration information 
void CConfigServer::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	//First clear
	CleanAll();
	//Call father window to read data
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetDeviceConfigInfo();
}

//Initialize dialogue box 
void CConfigServer::InitDlgInfo(DHDEV_SYSTEM_ATTR_CFG *pDevConfigInfo, int nChnCount)
{
	if(pDevConfigInfo != NULL)
	{
		CString str;
		NET_DEVICE_TYPE devType = (NET_DEVICE_TYPE)pDevConfigInfo->byDevType;
		str = GetDevType(devType);
		SetDlgItemText(IDC_EDIT_DEVTYPE,str);

		//  副版本3位
		str.Format("Software Version: %d.%3d, Build:%d-%d-%d",
			pDevConfigInfo->stVersion.dwSoftwareVersion>>16, pDevConfigInfo->stVersion.dwSoftwareVersion & 0x0000FFFF,
			pDevConfigInfo->stVersion.dwSoftwareBuildDate>>16, (pDevConfigInfo->stVersion.dwSoftwareBuildDate>>8) & 0x000000FF,
			pDevConfigInfo->stVersion.dwSoftwareBuildDate & 0x000000FF);
		// 第一个.后的位如果为‘ ’占位符，则替换为0
		int iDot = str.Find('.');
		if (str[iDot+1] == ' ')
		{
			str.SetAt(iDot+1, '0');
		}

		SetDlgItemText(IDC_EDIT_VERSION,str);

		str = (LPCSTR)(LPSTR)(pDevConfigInfo->szDevType);
		SetDlgItemText(IDC_EDIT_DEVTYPE2,str);

		str = (LPCSTR)(LPSTR)(pDevConfigInfo->szDevSerialNo);
		SetDlgItemText(IDC_EDIT_SERIALNO,str);

		//SetDlgItemInt(IDC_EDIT_VIDEONUM, pDevConfigInfo->byVideoCaptureNum);
		SetDlgItemInt(IDC_EDIT_VIDEONUM, nChnCount);
		SetDlgItemInt(IDC_EDIT_AUDIONUM, pDevConfigInfo->byAudioCaptureNum);
		SetDlgItemInt(IDC_EDIT_ALARMIN, pDevConfigInfo->byAlarmInNum);
		SetDlgItemInt(IDC_EDIT_ALARMOUT, pDevConfigInfo->byAlarmOutNum);
		SetDlgItemInt(IDC_EDIT_NETPORT, pDevConfigInfo->byNetIONum);
		SetDlgItemInt(IDC_EDIT_USBNUM, pDevConfigInfo->byUsbIONum);
		SetDlgItemInt(IDC_EDIT_IDENUM, pDevConfigInfo->byIdeIONum);
		SetDlgItemInt(IDC_EDIT_LPORTNUM, pDevConfigInfo->byLPTIONum);
		SetDlgItemInt(IDC_EDIT_232NUM, pDevConfigInfo->byComIONum);
		SetDlgItemInt(IDC_EDIT_VGANUM, pDevConfigInfo->byVgaIONum);
		SetDlgItemInt(IDC_EDIT_TALKIN, pDevConfigInfo->byTalkInChanNum);
		SetDlgItemInt(IDC_EDIT_TALKOUT, pDevConfigInfo->byTalkOutChanNum);
		SetDlgItemInt(IDC_EDIT_DECCHAN, pDevConfigInfo->byDecodeChanNum);
		SetDlgItemInt(IDC_EDIT_IDECTRLNUM, pDevConfigInfo->byIdeControlNum);
		SetDlgItemInt(IDC_EDIT_IDECTRLTYPE, pDevConfigInfo->byIdeControlType);
		SetDlgItemInt(IDC_EDIT_DEVNO, pDevConfigInfo->wDevNo);

		m_ctlDiskFull.SetCurSel(pDevConfigInfo->byOverWrite);
		//SetDlgItemInt(IDC_EDIT_RECLEN, pDevConfigInfo->byRecordLen);
		m_nReclen = pDevConfigInfo->byRecordLen;
		m_ctlVideoFormat.SetCurSel(pDevConfigInfo->byVideoStandard);
		m_ctlDateFormat.SetCurSel(pDevConfigInfo->byDateFormat);
		m_ctlDateSpr.SetCurSel(pDevConfigInfo->byDateSprtr);
		m_ctlTimeFormat.SetCurSel(pDevConfigInfo->byTimeFmt);
//		SetDlgItemInt(IDC_EDIT_STARTCHAN, pDevConfigInfo->byStartChanNo);

		UpdateData(FALSE);
	}
}

//Get device type
CString CConfigServer::GetDevType(NET_DEVICE_TYPE devType)
{
	CString str;
	switch(devType) {
	case NET_PRODUCT_NONE:
		str = "";
		break;
	case NET_DVR_NONREALTIME_MACE:
		str = ConvertString("non-real time MACE");
		break;
	case NET_DVR_NONREALTIME:
		str = ConvertString("non-real time");
		break;
	case NET_NVS_MPEG1:
		str = ConvertString("NVS");
		break;
	case NET_DVR_MPEG1_2:
		str = ConvertString("MPEG1 2 Channel DVR");
		break;
	case NET_DVR_MPEG1_8:
		str = ConvertString("MPEG1 8 Channel DVR");
		break;
	case NET_DVR_MPEG4_8:
		str = ConvertString("MPEG4 8 Channel DVR");
		break;
	case NET_DVR_MPEG4_16:
		str = ConvertString("MPEG4 16 Channel DVR");
		break;
	case NET_DVR_MPEG4_SX2:
		str = ConvertString("MPEG4 LB0416");
		break;
	case NET_DVR_MEPG4_ST2:
		str = ConvertString("MPEG4 GB");
		break;
	case NET_DVR_MEPG4_SH2:
		str = ConvertString("MPEG4 HB");
		break;
	case NET_DVR_MPEG4_GBE:
		str = ConvertString("MPEG4 GBE II era");
		break;
	case NET_DVR_MPEG4_NVSII:
		str = ConvertString("MPEG4 NVS II era");
		break;
	case NET_DVR_STD_NEW:
		str = ConvertString("new standard config protocol");
		break;
	case NET_DVR_DDNS:
		str = ConvertString("DDNS Server");
		break;
	case NET_DVR_ATM:
		str = ConvertString("ATM");
		break;
	case NET_NB_SERIAL:
		str = ConvertString("NB");
		break;
	case NET_LN_SERIAL:
		str = ConvertString("LN");
		break;
	case NET_BAV_SERIAL:
		str = ConvertString("BAV SERIAL");
		break;
	case NET_SDIP_SERIAL:
		str = ConvertString("SDIP SERIAL");
		break;
	case NET_IPC_SERIAL:
		str = ConvertString("IPC SERIAL");
		break;
	case NET_NVS_B:
		str = ConvertString("NVS_B");
		break;
	case NET_NVS_C:
		str = ConvertString("NVS_C");
		break;
	case NET_NVS_S:
		str = ConvertString("NVS_S");
		break;
	case NET_NVS_E:
		str = ConvertString("NVS_E");
		break;
	case NET_DVR_NEW_PROTOCOL:
		str = ConvertString("NEW PROTOCOL");
		break;
	case NET_NVD_SERIAL:
		str = ConvertString("NVD SERIAL");
		break;
	case NET_DVR_N5:
		str = ConvertString("N5");
		break;
	case NET_DVR_MIX_DVR:
		str = ConvertString("MIX_DVR");
		break;
	case NET_DVR_N51:
		str = ConvertString("N51");
		break;
//	case NET_EVS:
//		str = ConvertString("EVS");
//		break;
//	case NET_EIVS:
//		str = ConvertString("EIVS");
//		break;
	default:
		break;
	}
	return str;
}

void CConfigServer::InitComboBox()
{
	m_ctlDiskFull.ResetContent();
	int nIndex = m_ctlDiskFull.AddString(ConvertString("Stop"));
	m_ctlDiskFull.SetItemData(nIndex,0);
	nIndex = m_ctlDiskFull.AddString(ConvertString("overlay"));
	m_ctlDiskFull.SetItemData(nIndex,1);
	
	m_ctlDateFormat.ResetContent();
	nIndex = m_ctlDateFormat.AddString("YYYY-MM-DD");
	m_ctlDateFormat.SetItemData(nIndex,0);
	nIndex = m_ctlDateFormat.AddString("MM-DD-YYYY");
	m_ctlDateFormat.SetItemData(nIndex,1);
	nIndex = m_ctlDateFormat.AddString("DD-MM-YYYY");
	m_ctlDateFormat.SetItemData(nIndex,2);
	
	m_ctlDateSpr.ResetContent();
	nIndex = m_ctlDateSpr.AddString("\" . \"");
	m_ctlDateSpr.SetItemData(nIndex,0);
	nIndex = m_ctlDateSpr.AddString("\" - \"");
	m_ctlDateSpr.SetItemData(nIndex,1);
	nIndex = m_ctlDateSpr.AddString("\" / \"");
	m_ctlDateSpr.SetItemData(nIndex,2);
	
	m_ctlTimeFormat.ResetContent();
	nIndex = m_ctlTimeFormat.AddString("24 Hour");
	m_ctlTimeFormat.SetItemData(nIndex,0);
	nIndex = m_ctlTimeFormat.AddString("12 Hour");
	m_ctlTimeFormat.SetItemData(nIndex,1);

	m_ctlVideoFormat.ResetContent();
	nIndex = m_ctlVideoFormat.AddString("PAL");
	m_ctlVideoFormat.SetItemData(nIndex,0);
	nIndex = m_ctlVideoFormat.AddString("NTSC");
	m_ctlVideoFormat.SetItemData(nIndex,1);
}

//Clear 
void CConfigServer::CleanAll()
{
	SetDlgItemText(IDC_EDIT_DEVTYPE,"");
	SetDlgItemText(IDC_EDIT_VERSION,"");
	SetDlgItemText(IDC_EDIT_DEVTYPE2,"");
	SetDlgItemText(IDC_EDIT_SERIALNO,"");
	SetDlgItemText(IDC_EDIT_VIDEONUM, "");
	SetDlgItemText(IDC_EDIT_AUDIONUM, "");
	SetDlgItemText(IDC_EDIT_ALARMIN, "");
	SetDlgItemText(IDC_EDIT_ALARMOUT, "");
	SetDlgItemText(IDC_EDIT_NETPORT, "");
	SetDlgItemText(IDC_EDIT_USBNUM, "");
	SetDlgItemText(IDC_EDIT_IDENUM, "");
	SetDlgItemText(IDC_EDIT_LPORTNUM, "");
	SetDlgItemText(IDC_EDIT_232NUM, "");
	SetDlgItemText(IDC_EDIT_VGANUM, "");
	SetDlgItemText(IDC_EDIT_TALKIN, "");
	SetDlgItemText(IDC_EDIT_TALKOUT, "");
	SetDlgItemText(IDC_EDIT_DECCHAN, "");
	SetDlgItemText(IDC_EDIT_IDECTRLNUM, "");
	SetDlgItemText(IDC_EDIT_IDECTRLTYPE, "");
	SetDlgItemText(IDC_EDIT_DEVNO, "");

	m_ctlDiskFull.SetCurSel(-1);
	SetDlgItemText(IDC_EDIT_RECLEN, "");
	m_ctlVideoFormat.SetCurSel(-1);
	m_ctlDateFormat.SetCurSel(-1);
	m_ctlDateSpr.SetCurSel(-1);
	m_ctlTimeFormat.SetCurSel(-1);
	SetDlgItemText(IDC_EDIT_STARTCHAN, "");
}

//Check input is valid or not 
BOOL CConfigServer::IsValid()
{
	if (CB_ERR == m_ctlDiskFull.GetCurSel() ||
		CB_ERR == m_ctlDateFormat.GetCurSel() ||
		CB_ERR == m_ctlDateSpr.GetCurSel() ||
		CB_ERR == m_ctlTimeFormat.GetCurSel())
	{
		return FALSE;
	}

	CString DevNo;
	GetDlgItemText(IDC_EDIT_DEVNO, DevNo);
	errno = 0;
	if (DevNo != "0" && atoi(DevNo) == 0 || errno == ERANGE || atoi(DevNo) > 998)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CConfigServer::CheckReclenValid()
{
	UpdateData();
	BOOL bValid = TRUE;
// 	if (1 <= m_nReclen  && m_nReclen <= 120)
// 	{
// 		bValid = TRUE;
// 	}
// 	else
// 	{
// 		MessageBox(ConvertString("Please input Record Length between 1 and 120!"), ConvertString("Prompt"));
// 		bValid = FALSE;
// 	}

	return bValid;
}

