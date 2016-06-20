// ConfigChannel.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigChannel.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigChannel dialog


CConfigChannel::CConfigChannel(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigChannel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigChannel)
	m_nBrightness = 0;
	m_nContrast = 0;
	m_nSaturation = 0;
	m_nHue = 0;
	m_nGain = 0;
	m_bAudioOverlay = FALSE;
	m_nNoise = 0;
	m_nVolume = 0;
	m_bVolumeEn = FALSE;
	m_bMask = FALSE;
	//}}AFX_DATA_INIT
	m_nChannelCount = 0;
	m_nCurChannel = -1;
	m_nCurStream = -1;
	m_nCurOSD = -1;
	m_nProtoVer = 4;
	m_nVideoStandard = 0;
	m_bNewProtocol = FALSE;
	m_bShowPix = FALSE;
	m_stEncodeInfo = NULL;
	m_pstChannelVideoColor = NULL;
	m_pstChannelName = NULL;
	m_pChannelInfo = NULL;
	m_iMinFps = 0;
	m_iMaxFps = 0;
	m_bShowFpsRange = FALSE;
	InitResolution();
	memset(&m_EncodeCaps, 0, sizeof(CFG_ENCODECAP));
	memset(&m_stEncodeCaps, 0, sizeof(m_stEncodeCaps));
	SET_SIZE(m_stEncodeCaps);
}


void CConfigChannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigChannel)
	DDX_Control(pDX, IDC_LIST_VIDEOCOLOR, m_ctlVideoColorLst);
	DDX_Control(pDX, IDC_COMBO_AUDIOFMT, m_ctlAudioFmt);
	DDX_Control(pDX, IDC_COMBO_IMGQUALITY, m_ctlImageQuality);
	DDX_Control(pDX, IDC_COMBO_FRAME, m_ctlFrame);
	DDX_Control(pDX, IDC_COMBO_BRCTRL, m_ctlBRCtl);
	DDX_Control(pDX, IDC_CHECK_AUDIO, m_ctlAudio);
	DDX_Control(pDX, IDC_CHECK_VIDEO, m_ctlVideo);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_ctlStream);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_ctlResolution);
	DDX_Control(pDX, IDC_COMBO_ENCODETYPE, m_ctlEncodeType);
	DDX_Control(pDX, IDC_COMBO_CHANNO, m_ctlChannel);
    DDX_Control(pDX, IDC_COMBO_LIMITSTREAM, m_ctlLimitStream);
	DDX_Check(pDX, IDC_CHECK_AUDIO_OVERLAY, m_bAudioOverlay);
	DDX_Check(pDX, IDC_CHECK_MASK, m_bMask);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigChannel, CDialog)
	//{{AFX_MSG_MAP(CConfigChannel)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNO, OnSelchangeComboChanno)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM, OnSelchangeComboStream)
	ON_CBN_SELCHANGE(IDC_COMBO_OSD, OnSelchangeComboOsd)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_VIDEOCOLOR, OnItemchangedListVideocolor)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAME, OnSelchangeComboFrame)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, OnSelchangeComboResolution)
	ON_CBN_SELCHANGE(IDC_COMBO_LIMITSTREAM, OnSelchangeComboLimitstream)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigChannel message handlers

//Save
void CConfigChannel::OnButtonApply() 
{
	BOOL bSuccess = UpdateData(TRUE);
	if (!bSuccess)
	{
		return;
	}

	// TODO: Add your control notification handler code here
	if(-1 != m_ctlChannel.GetCurSel())
	{
		SaveChannelInfo(m_nCurChannel);
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetOneChannelName(&m_pstChannelName[m_nCurChannel], m_nCurChannel);
	    ((CClientDemo5Dlg*)AfxGetMainWnd())->SetOneChannelConfigInfo(&m_stEncodeInfo[m_nCurChannel], m_nCurChannel);
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetOneChannelVideoColor(&m_pstChannelVideoColor[m_nCurChannel], m_nCurChannel);

	}
	else
	{
		MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
	}
}

//Read
void CConfigChannel::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	OnSelchangeComboChanno();
}

/*
 *	Function:display channel video information.
 *	Please pay attention to the resolution position and frame rate position
 *	Note：DHDEV_DSP_ENCODECAP is DSP capacity information. dwMaxEncodePower means the highest encode capacity DSP supported. wMaxSupportChannel means the max video channel each DSP supported.
 *	wChannelMaxSetSync measn synchronization or not. 0-not synchronized (DSP each channel resolution may not be the same.), 1-synchronized. (The modification may fail if DSP each channel resolution is not the same. )
 *	Resolution*Frame rate(channel 0) + Resolution*frame rate(channel 1) + Resolution*frame rate(channel 2) + Resolution*Frame rate(channel 3) <= dwMaxEncodePower
 */
void CConfigChannel::InitDlgInfo(int nChannelCount, int nVideoStandard, int nProtoVer, BOOL bNewProtocol)
{
//	m_stDspInfo = stDspInfo;
	m_nProtoVer = nProtoVer;
	m_nVideoStandard = nVideoStandard;
	m_bNewProtocol = bNewProtocol;


	m_stEncodeInfo = new CFG_ENCODE_INFO[CHANNEL_NUM_LIMIT];
	if(NULL != m_stEncodeInfo)
	{
		memset(m_stEncodeInfo, 0, CHANNEL_NUM_LIMIT*sizeof(CFG_ENCODE_INFO));
	}
	else
	{
		return;
	}
	m_pstChannelVideoColor = new AV_CFG_ChannelVideoColor[CHANNEL_NUM_LIMIT];
	if(NULL != m_pstChannelVideoColor)
	{
		memset(m_pstChannelVideoColor, 0, CHANNEL_NUM_LIMIT*sizeof(AV_CFG_ChannelVideoColor));
	}
	else
	{
		return;
	}
	m_pstChannelName = new AV_CFG_ChannelName[CHANNEL_NUM_LIMIT];
	if(NULL != m_pstChannelName)
	{
		memset(m_pstChannelName, 0, CHANNEL_NUM_LIMIT*sizeof(AV_CFG_ChannelName));
	}
	else
	{
		return;
	}
    if (NULL == m_pChannelInfo)
    {
        m_pChannelInfo = new DHDEV_CHANNEL_CFG[CHANNEL_NUM_LIMIT];
		if (NULL != m_pChannelInfo)
		{
            memset(m_pChannelInfo, 0, CHANNEL_NUM_LIMIT*sizeof(DHDEV_CHANNEL_CFG));
		}
    }
	int nIndex = 0;
	CString str;
	
	// Channel name dropdown menu 
	m_ctlChannel.ResetContent();
	m_nChannelCount = nChannelCount>CHANNEL_NUM_LIMIT?CHANNEL_NUM_LIMIT:nChannelCount;
	for(int i = 0; i < m_nChannelCount; i++)
	{
		str.Format("%d",i+1);
		nIndex = m_ctlChannel.AddString(str);
		m_ctlChannel.SetItemData(nIndex,i);
	}

	memset(&m_stEncodeCaps, 0, sizeof(m_stEncodeCaps));
	SET_SIZE(m_stEncodeCaps);
	//if (m_bNewProtocol == TRUE)//32路配置取单个通道
	{
		((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneChannelDspConfig(nIndex, m_stDspInfo, m_stDspInfoEx, m_stEncodeCaps, m_bShowPix);
	}
	OnInitCtrl(m_nProtoVer, m_nVideoStandard, m_nChannelCount);

	//Select channel 0
	if(0 < m_ctlChannel.GetCount())
	{
		m_ctlChannel.SetCurSel(0);
		OnSelchangeComboChanno();
	}
}
void CConfigChannel::OnInitCtrl(int nProtoVer, int nVideoStandard, int nChannelCount)
{
	int nIndex = 0;
	CString str;

	// Frame rate dropdown menu(Depends on video format and protocol version)
	m_ctlFrame.ResetContent();
	if (nProtoVer >= 5)
	{
		if (0 == nVideoStandard)		//PAL
		{
			for (int i = 1; i <= 25; i++)
			{
				str.Format("%d", i);
				nIndex = m_ctlFrame.AddString(str);
				m_ctlFrame.SetItemData(nIndex, i);
			}
		}
		else if (1 == nVideoStandard)	//NTSC
		{
			for (int i = 1; i <= 30; i++)
			{
				str.Format("%d", i);
				nIndex = m_ctlFrame.AddString(str);
				m_ctlFrame.SetItemData(nIndex, i);
			}
		}
	}
	else
	{
		if (0 == nVideoStandard)		//PAL
		{
			nIndex = m_ctlFrame.AddString("1");
			m_ctlFrame.SetItemData(nIndex, 0);
			nIndex = m_ctlFrame.AddString("2");
			m_ctlFrame.SetItemData(nIndex, 1);
			nIndex = m_ctlFrame.AddString("3");
			m_ctlFrame.SetItemData(nIndex, 2);
			nIndex = m_ctlFrame.AddString("6");
			m_ctlFrame.SetItemData(nIndex, 3);
			nIndex = m_ctlFrame.AddString("12");
			m_ctlFrame.SetItemData(nIndex, 4);
			nIndex = m_ctlFrame.AddString("25");
			m_ctlFrame.SetItemData(nIndex, 5);
		}
		else if (1 == nVideoStandard)	//NTSC
		{
			nIndex = m_ctlFrame.AddString("1");
			m_ctlFrame.SetItemData(nIndex, 0);
			nIndex = m_ctlFrame.AddString("2");
			m_ctlFrame.SetItemData(nIndex, 1);
			nIndex = m_ctlFrame.AddString("4");
			m_ctlFrame.SetItemData(nIndex, 2);
			nIndex = m_ctlFrame.AddString("7");
			m_ctlFrame.SetItemData(nIndex, 3);
			nIndex = m_ctlFrame.AddString("15");
			m_ctlFrame.SetItemData(nIndex, 4);
			nIndex = m_ctlFrame.AddString("20");
			m_ctlFrame.SetItemData(nIndex, 5);
			nIndex = m_ctlFrame.AddString("30");
			m_ctlFrame.SetItemData(nIndex, 6);
		}
	}
	
	//m_ctlOSD
// 	m_ctlOSD.ResetContent();
// 	if (nChannelCount > 16)
// 	{
// 		char *OSDName[8] = {"Channel OSD", "Time OSD"};
// 		for (int k = 0; k < 2; k++)
// 		{
// 			int nIndex = m_ctlOSD.AddString(ConvertString(OSDName[k]));
// 			m_ctlOSD.SetItemData(nIndex,k);
// 		}
// 	}
// 	else
// 	{
// 		char *OSDName[8] = {"Channel OSD", "Time OSD", "Area Shelter"};
// 		for (int k = 0; k < 3; k++)
// 		{
// 			int nIndex = m_ctlOSD.AddString(ConvertString(OSDName[k]));
// 			m_ctlOSD.SetItemData(nIndex,k);
// 		}
// 	}
// 	m_ctlOSD.SetCurSel(0);
	
	// Set dropdown menu in decode mode by encode subnet mask setup.
	// 此处假设主辅码流的编码方式能力相同，如果日后设备有变化，则需要在ShowStreamInfo中处理辅码流
	// 当然其实更好的做法是把与能力有关的操作集中在一个或几个函数中，但是原来的代码太乱，实在改不动了……
	// 勇敢的少年，你愿意接下这个光荣的使命吗？ :) -- 2014.09.05 wu_pengzhou
	m_ctlEncodeType.ResetContent();
	const int nH264ProfileRankNum = m_stEncodeCaps.stuMainFormatCaps[0].nH264ProfileRankNum;
	const BYTE* bH264ProfileRank = m_stEncodeCaps.stuMainFormatCaps[0].bH264ProfileRank;
	for (int j = 0; j < encodeCount; j++)
	{
		//dwEncodeModeMask is encode mode subnet mask. Each bit means the encode mode setup the device supported. 
		if (m_stDspInfo.dwEncodeModeMask & (0x01<<j))
		{
			
			if (j == VIDEO_FORMAT_H264 && nH264ProfileRankNum)
			{
				for (int i = 0; i < nH264ProfileRankNum; ++i)
				{
					int nIndex = m_ctlEncodeType.AddString(profileName[bH264ProfileRank[i]-1]);
					m_ctlEncodeType.SetItemData(nIndex,bH264ProfileRank[i] - 1 - profileCount);
				}
			}
			else
			{
				int nIndex = m_ctlEncodeType.AddString(ecName[j]);
				m_ctlEncodeType.SetItemData(nIndex,j);
			}
		}
	}

	// If synchronized, the channel resolution in each DSP shall be the same.
	if (1 == m_stDspInfo.wChannelMaxSetSync)
	{
		CString strText = ConvertString("(notice:");
		for (int i = 0; i < m_nChannelCount/m_stDspInfo.wMaxSupportChannel; i++)
		{
			CString str;
			str.Format(ConvertString(" %d~%dchannel"), i*m_stDspInfo.wMaxSupportChannel, i*m_stDspInfo.wMaxSupportChannel+m_stDspInfo.wMaxSupportChannel-1);
			strText = strText + str;
		}
		strText += ConvertString(" demand the same sampling rate!");
		SetDlgItemText(IDC_STATIC_SHOW, strText);
	}

}
void CConfigChannel::InitListView()
{
	
	
	m_ctlVideoColorLst.SetExtendedStyle(m_ctlVideoColorLst.GetExtendedStyle() | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlVideoColorLst.InsertColumn(0, ConvertString("nIndex"),LVCFMT_LEFT,60,-1);
	m_ctlVideoColorLst.InsertColumn(1, ConvertString("Brightness"),LVCFMT_LEFT,80,-1);
	m_ctlVideoColorLst.InsertColumn(2, ConvertString("Contrast"),LVCFMT_LEFT,80,-1);
	m_ctlVideoColorLst.InsertColumn(3, ConvertString("Saturation"),LVCFMT_LEFT,100,-1);
	m_ctlVideoColorLst.InsertColumn(4, ConvertString("Chroma"),LVCFMT_LEFT,60,-1);
//	m_ctlVideoColorLst.InsertColumn(5, ConvertString("Plus"),LVCFMT_LEFT,60,-1);
	m_ctlVideoColorLst.InsertColumn(5, ConvertString("StartHour"),LVCFMT_LEFT,80,-1);
	m_ctlVideoColorLst.InsertColumn(6, ConvertString("StartMinute"),LVCFMT_LEFT,80,-1);
	m_ctlVideoColorLst.InsertColumn(7, ConvertString("StartSecond"),LVCFMT_LEFT,80,-1);
	m_ctlVideoColorLst.InsertColumn(8, ConvertString("EndHour"),LVCFMT_LEFT,80,-1);
	m_ctlVideoColorLst.InsertColumn(9, ConvertString("EndMinute"),LVCFMT_LEFT,80,-1);
	m_ctlVideoColorLst.InsertColumn(10, ConvertString("EndSecond"),LVCFMT_LEFT,80,-1);
	m_ctlVideoColorLst.InsertColumn(11, ConvertString("Enable"), LVCFMT_LEFT,80,-1);
}
void CConfigChannel::InsertListView(CString strIndex,CString strBright,CString strContrast,CString strSaturation, CString strChroma, CString strPlus, 
									CString strStartHour, CString strStartMinute, CString strStartSecond,
									CString strEndHour,CString strEndMinute,CString strEndSecond, BOOL bEnable)
{

	int nIndex = m_ctlVideoColorLst.GetItemCount();
	m_ctlVideoColorLst.InsertItem(LVIF_TEXT|LVIF_STATE,nIndex,strIndex,0,LVIS_SELECTED,0,0);
	m_ctlVideoColorLst.SetItemText(nIndex,1,strBright);
	m_ctlVideoColorLst.SetItemText(nIndex,2,strContrast);
	m_ctlVideoColorLst.SetItemText(nIndex,3,strSaturation);
	m_ctlVideoColorLst.SetItemText(nIndex,4,strChroma);
//	m_ctlVideoColorLst.SetItemText(nIndex,5,strPlus);
	m_ctlVideoColorLst.SetItemText(nIndex,5,strStartHour);
	m_ctlVideoColorLst.SetItemText(nIndex,6,strStartMinute);
	m_ctlVideoColorLst.SetItemText(nIndex,7,strStartSecond);
	m_ctlVideoColorLst.SetItemText(nIndex,8,strEndHour);
	m_ctlVideoColorLst.SetItemText(nIndex,9,strEndMinute);
	m_ctlVideoColorLst.SetItemText(nIndex,10,strEndSecond);
	if (bEnable)
	{
		m_ctlVideoColorLst.SetItemText(nIndex, 11, "true");
	}
	else
	{
		m_ctlVideoColorLst.SetItemText(nIndex, 11, "false");
	}
}
void CConfigChannel::ShowChannelVideoColor(AV_CFG_ChannelVideoColor *pstChannelVideoColor)
{
	if(NULL == pstChannelVideoColor)
	{
		return;
	}
	m_ctlVideoColorLst.DeleteAllItems();
	int i = 0;
	for(i = 0 ; i < pstChannelVideoColor->nColorNum; i ++)
	{
		CString strIndex;
		strIndex.Format("%d",i+1);
		
		CString strBrightness;
		strBrightness.Format("%d", pstChannelVideoColor->stuColor[i].nBrightness);

		CString strContrast;
		strContrast.Format("%d", pstChannelVideoColor->stuColor[i].nContrast);

		CString strSaturation;
		strSaturation.Format("%d", pstChannelVideoColor->stuColor[i].nSaturation);

		CString strChroma;
		strChroma.Format("%d", pstChannelVideoColor->stuColor[i].nHue);
		
		CString strPlus;
		strPlus.Format("%d", 0);
		
		CString strStartHour;
		strStartHour.Format("%d", pstChannelVideoColor->stuColor[i].stuTimeSection.nBeginHour);

		CString strStartMinute;
		strStartMinute.Format("%d", pstChannelVideoColor->stuColor[i].stuTimeSection.nBeginMinute);

		CString strStartSecond;
		strStartSecond.Format("%d", pstChannelVideoColor->stuColor[i].stuTimeSection.nBeginSecond);
			
		CString strEndHour;
		strEndHour.Format("%d", pstChannelVideoColor->stuColor[i].stuTimeSection.nEndHour);

		CString strEndMinute;
		strEndMinute.Format("%d", pstChannelVideoColor->stuColor[i].stuTimeSection.nEndMinute);

		CString strEndSecond;
		strEndSecond.Format("%d", pstChannelVideoColor->stuColor[i].stuTimeSection.nEndSecond);
		
		InsertListView(strIndex, strBrightness, strContrast, strSaturation, strChroma, strPlus, 
			strStartHour, strStartMinute, strStartSecond,
			strEndHour, strEndMinute, strEndSecond, pstChannelVideoColor->stuColor[i].stuTimeSection.nMask);
	}
}





//Channel switch 
void CConfigChannel::OnSelchangeComboChanno() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = (int)m_ctlChannel.GetItemData(nIndex);
		m_nCurChannel = nNum;

		// 每次切换通道都会重新获取DSP能力，没有必要，可以优化为只获取一次
		((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneChannelDspConfig(m_nCurChannel, m_stDspInfo, m_stDspInfoEx, m_stEncodeCaps, m_bShowPix);
		OnInitCtrl(m_nProtoVer, m_nVideoStandard, m_nChannelCount);
		
		((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneChannelName(&m_pstChannelName[nNum],nIndex);
		((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneChannelConfigInfo(&m_stEncodeInfo[nNum], nIndex);
		((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneChannelVideoColor(&m_pstChannelVideoColor[nNum],nIndex);

		//Display channel related information 
		
		//Set channel name
		char szBuf[AV_CFG_Channel_Name_Len + 1] = {0};
		memcpy(szBuf, m_pstChannelName[nNum].szName, AV_CFG_Channel_Name_Len);
		SetDlgItemText(IDC_EDIT_CHANNAME, szBuf);
		
		
		//Set bit stream
		m_ctlStream.ResetContent();
		int nIndex = m_ctlStream.AddString(ConvertString("Main Data stream"));
		m_ctlStream.SetItemData(nIndex,0);
		
		
		//Check there is extra stream in accordance with capacity. 
		if (m_stDspInfo.dwStreamCap & (0x01<<1))
		{
			nIndex = m_ctlStream.AddString(ConvertString("Sub Data stream"));
			m_ctlStream.SetItemData(nIndex,3);
		}
		
		m_ctlStream.SetCurSel(0);
		OnSelchangeComboStream();

		ShowChannelVideoColor(&m_pstChannelVideoColor[nNum]);

		SaveChannelInfo(nIndex);
		
		UpdateData(FALSE);
	}
}

//Bit stream switch 
void CConfigChannel::OnSelchangeComboStream() 
{
	// TODO: Add your control notification handler code here
	int nStreamIndex = m_ctlStream.GetCurSel();
	if(CB_ERR != nStreamIndex)
	{
		int nItem = m_ctlStream.GetItemData(nStreamIndex);
		int nChn = m_ctlChannel.GetCurSel();
		if(CB_ERR != nChn)
		{
			int nNum = m_ctlChannel.GetItemData(nChn);
			//First save current bit stream information 
			//SaveStreamInfo(m_nCurChannel,m_nCurStream);
			m_nCurStream = nItem;
			//Display bit stream information 
			ShowStreamInfo(nNum,nItem);
		}
	}
}

//Save bit stream information 
void CConfigChannel::SaveStreamInfo(int nNum, int nItem)
{

//P3 ---------------------------------------------------
	CFG_VIDEOENC_OPT *pStreamInfo = NULL;

	if(0 <= nItem && 3 >nItem)
	{
		pStreamInfo = &(m_stEncodeInfo[nNum].stuMainStream[nItem]);
		
	}
	else if(3 <= nItem && 6 >nItem)
	{
		pStreamInfo = &(m_stEncodeInfo[nNum].stuExtraStream[nItem-3]);
	}
	if(NULL != pStreamInfo)
	{
		pStreamInfo->bVideoEnable = m_ctlVideo.GetCheck();
		pStreamInfo->bAudioEnable = m_ctlAudio.GetCheck();
		pStreamInfo->stuVideoFormat.emBitRateControl = (CFG_BITRATE_CONTROL)m_ctlBRCtl.GetCurSel();
		int nIndex = m_ctlFrame.GetCurSel();
		pStreamInfo->stuVideoFormat.nFrameRate = (BYTE)m_ctlFrame.GetItemData(nIndex);
		
		//CBR. It begins with 0. the value ranges from 50~4*1024 (K)
		pStreamInfo->stuVideoFormat.nBitRate = GetDlgItemInt(IDC_EDIT_LIMITSTREAM);
		
		//I frame interval value 
		pStreamInfo->stuVideoFormat.nIFrameInterval = GetDlgItemInt(IDC_EDIT_IFRAME);
		
		//Decode mode 
		DWORD compression = m_ctlEncodeType.GetItemData(m_ctlEncodeType.GetCurSel());
		if (compression > encodeCount) // H264 with profile
		{
			pStreamInfo->stuVideoFormat.emCompression = VIDEO_FORMAT_H264;
			pStreamInfo->stuVideoFormat.emProfile = (CFG_H264_PROFILE_RANK)(compression + profileCount + 1);
		}
		else
		{
			pStreamInfo->stuVideoFormat.emCompression = (CFG_VIDEO_COMPRESSION)compression;
		}
		
		
		//Resolution 
		nIndex = m_ctlResolution.GetCurSel();


		int nTemp = m_ctlResolution.GetItemData(nIndex);
		
		if(nTemp >= 0)
		{
			BYTE byImageSize = (BYTE)nTemp;
			((CClientDemo5Dlg*)AfxGetMainWnd())->ResolutionSizetoInt(byImageSize,&pStreamInfo->stuVideoFormat.nWidth, &pStreamInfo->stuVideoFormat.nHeight);
		
		}
		//Image quality 
		pStreamInfo->stuVideoFormat.emImageQuality = (CFG_IMAGE_QUALITY)(m_ctlImageQuality.GetCurSel() + 1);
		//Audio overlay
		pStreamInfo->bAudioAddEnable = m_bAudioOverlay;
	
	}
}

//Save channel information 
void CConfigChannel::SaveChannelInfo(int nNum)
{
	if(-1 < nNum && -1 < m_nCurStream)
	{
		SaveVideoColorInfo(nNum);

		CFG_ENCODE_INFO *pInfo = &(m_stEncodeInfo[nNum]);
		if(NULL != pInfo)
		{
			SaveStreamInfo(nNum,m_nCurStream);
			CString str = "";
			GetDlgItemText(IDC_EDIT_CHANNAME,str);
			strncpy(m_pstChannelName[nNum].szName, str.GetBuffer(0), AV_CFG_Channel_Name_Len);
		}
	}
}

//Save OSD type information
void CConfigChannel::SaveOSDInfo(int nNum, int nItem)
{

}

//Display bit stream information 
void CConfigChannel::ShowStreamInfo(int nNum, int nItem)
{

 	if(NULL == m_stEncodeInfo)
 	{
		return;
	}
 
 	CFG_ENCODE_INFO Info = m_stEncodeInfo[nNum];
	CFG_VIDEOENC_OPT StreamInfo = {0};
 
 	DWORD dwImageSizeMask = 0;
	BYTE bImage = 0;
 	if(0 <= nItem && 3 > nItem)
	{
		StreamInfo = Info.stuMainStream[nItem];
		dwImageSizeMask = m_stDspInfo.dwImageSizeMask;
		bImage = (BYTE)(((CClientDemo5Dlg*)AfxGetMainWnd())->ResolutionInttoSize(Info.stuMainStream[nItem].stuVideoFormat.nWidth, Info.stuMainStream[nItem].stuVideoFormat.nHeight));

	}	
 	else if(3 <= nItem && 6 >nItem)
	{	
		StreamInfo = Info.stuExtraStream[nItem-3];
		BYTE bImageSize = (BYTE)(((CClientDemo5Dlg*)AfxGetMainWnd())->ResolutionInttoSize(Info.stuMainStream[0].stuVideoFormat.nWidth, Info.stuMainStream[0].stuVideoFormat.nHeight));
 		dwImageSizeMask = m_stDspInfo.dwImageSizeMask_Assi[bImageSize];
		bImage = (BYTE)(((CClientDemo5Dlg*)AfxGetMainWnd())->ResolutionInttoSize(Info.stuExtraStream[nItem-3].stuVideoFormat.nWidth, Info.stuExtraStream[nItem-3].stuVideoFormat.nHeight));
	}


	m_ctlResolution.ResetContent();
 	char *rsName[33] = {"D1", "HD1", "BCIF", "CIF", "QCIF", "VGA", "QVGA", "SVCD", "QQVGA", 
 		"SVGA", "XVGA", "WXGA", "SXGA", "WSXGA", "UXGA", "WUXGA", "LFT", "720", "1080", "1_3M", 
 		"2M","5M","3M","5_0M","1_2M", "1408_1024", "8M", "2560_1920", "960H", "960_720"
 		,"NHD" , "QNHD", "QQNHD"};
 	int i = 0;
 	for (i = 0; i < 32; i++)
 	{
 		if (dwImageSizeMask & (0x01<<i))
 		{
 			int nIndex = m_ctlResolution.AddString(rsName[i]);
 			m_ctlResolution.SetItemData(nIndex,i);
 		}
 	}
 
 	if (m_bShowPix)
 	{
 		for (i = 0; i < 256; ++i)
 		{
 			if (0 < m_stDspInfoEx.byImageSize[i] && m_stDspInfoEx.byImageSize[i] != 255)
			{
 				if (m_stDspInfoEx.byImageSize[i] == 32)
 				{
 					int nIndex = m_ctlResolution.AddString(rsName[32]);
 					m_ctlResolution.SetItemData(nIndex,32);
 				}
 			}
 		}	
 	}
 
	//Enable video 
 	m_ctlVideo.SetCheck(StreamInfo.bVideoEnable);
	
	//Enable audio 
	m_ctlAudio.SetCheck(StreamInfo.bAudioEnable);
 	//SetDlgItemInt(IDC_EDIT_LIMITSTREAM, StreamInfo.stuVideoFormat.nBitRate);
 	SetDlgItemInt(IDC_EDIT_IFRAME, StreamInfo.stuVideoFormat.nIFrameInterval);
		
  	m_ctlBRCtl.SetCurSel(StreamInfo.stuVideoFormat.emBitRateControl);

 	
	m_ctlFrame.SetCurSel(StreamInfo.stuVideoFormat.nFrameRate-1);


 	//Decode mode 
  	int nItemCount = m_ctlEncodeType.GetCount();

	const char* itemStr = NULL;
	if (StreamInfo.stuVideoFormat.emCompression == VIDEO_FORMAT_H264 && 
		StreamInfo.stuVideoFormat.abProfile)  // H264 with profile
	{
		itemStr = profileName[StreamInfo.stuVideoFormat.emProfile - 1];
	}
	else
	{
		itemStr = ecName[StreamInfo.stuVideoFormat.emCompression];
	}
	m_ctlEncodeType.SelectString(-1, itemStr); // TODO SelectString模糊搜索,不建议使用

	//Resolution 
	nItemCount = m_ctlResolution.GetCount();
	for(i = 0; i < nItemCount; i++)
	{
		BYTE nTagData = (BYTE)(m_ctlResolution.GetItemData(i));
	 	if(nTagData == bImage)
	 	{
	 		m_ctlResolution.SetCurSel(i);
			break;
		}
 	}
	ShowFpsRange();
	SetFpsValue(StreamInfo.stuVideoFormat.nBitRate);
 	//Video quality 
 	m_ctlImageQuality.SetCurSel(StreamInfo.stuVideoFormat.emImageQuality - 1);
 	 
    //Audio encode 
	m_bAudioOverlay = StreamInfo.bAudioAddEnable;

}

//OSD type switch 
void CConfigChannel::OnSelchangeComboOsd() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = (int)m_ctlChannel.GetItemData(nIndex);
	}
	
}

//Clear 
void CConfigChannel::CleanAll()
{
	m_ctlChannel.SetCurSel(-1);
	m_ctlStream.SetCurSel(-1);
	m_ctlBRCtl.SetCurSel(-1);
	m_ctlFrame.SetCurSel(-1);
	m_ctlEncodeType.SetCurSel(-1);
	m_ctlResolution.SetCurSel(-1);
	m_ctlImageQuality.SetCurSel(-1);
	m_ctlAudioFmt.SetCurSel(-1);
//	m_ctlOSD.SetCurSel(-1);
    m_ctlChannel.ResetContent();
	m_ctlStream.ResetContent();

	SetDlgItemText(IDC_EDIT_CHANNAME,"");
	SetDlgItemText(IDC_EDIT_TRACKNUM,"");
	SetDlgItemText(IDC_EDIT_BITPERSMPL,"");
	SetDlgItemText(IDC_EDIT_SMPLPERSEC,"");
//	SetDlgItemText(IDC_EDIT_BRIGHTNESS,"");
//	SetDlgItemText(IDC_EDIT_CONTRAST,"");
//	SetDlgItemText(IDC_EDIT_SATURATION,"");
//	SetDlgItemText(IDC_EDIT_HUE,"");
//	SetDlgItemText(IDC_EDIT_GAIN,"");
//	SetDlgItemText(IDC_EDIT_FORE_RED, "");
// 	SetDlgItemText(IDC_EDIT_FORE_GREEN, "");
// 	SetDlgItemText(IDC_EDIT_FORE_BLUE, "");
// 	SetDlgItemText(IDC_EDIT_FORE_TRANS, "");
// 	SetDlgItemText(IDC_EDIT_BACK_RED, "");
// 	SetDlgItemText(IDC_EDIT_BACK_GREEN, "");
// 	SetDlgItemText(IDC_EDIT_BACK_BLUE, "");
// 	SetDlgItemText(IDC_EDIT_BACK_TRANS, "");
// 	SetDlgItemText(IDC_EDIT_RECT_LFET, "");
// 	SetDlgItemText(IDC_EDIT_RECT_TOP, "");
// 	SetDlgItemText(IDC_EDIT_RECT_RIGHT, "");
// 	SetDlgItemText(IDC_EDIT_RECT_BOTTOM, "");
	SetDlgItemText(IDC_STATIC_SHOW, "");
	SetDlgItemInt(IDC_STATIC_MINFPS,0);
	SetDlgItemInt(IDC_STATIC_MAXFPS,0);	
	SetDlgItemInt(IDC_EDIT_LIMITSTREAM, 0);
	GetDlgItem(IDC_EDIT_LIMITSTREAM)->ShowWindow(TRUE); // 复位ui的显示
	
// 	m_ctlVideo.SetCheck(0);
// 	m_ctlAudio.SetCheck(0);
// 	m_ctlGain.SetCheck(0);
// 	m_ctlOSDShow.SetCheck(0);

// 	GetDlgItem(IDC_STATIC_BLINDTYPE)->ShowWindow(SW_HIDE);
// 	GetDlgItem(IDC_COMBO_BLINDTYPE)->ShowWindow(SW_HIDE);

	m_nChannelCount = 0;
	m_nCurChannel = -1;
	m_nCurStream = -1;
	m_nCurOSD = -1;
	m_bShowFpsRange = FALSE;
	if(m_stEncodeInfo)
	{
		delete[] m_stEncodeInfo;
		m_stEncodeInfo = NULL;
	}
	

	if(m_pstChannelVideoColor)
	{
		delete[] m_pstChannelVideoColor;
		m_pstChannelVideoColor = NULL;
	}

	if(m_pstChannelName)
	{
		delete[] m_pstChannelName;
		m_pstChannelName = NULL;
	}
	if(m_pChannelInfo)
	{
		delete[] m_pChannelInfo;
		m_pChannelInfo = NULL;
	}
}

/*
 *	Summary：Verify resolution and frame rate
 */
BOOL CConfigChannel::IsValidForInput()
{
	DWORD dwMaxEncodePower = m_stDspInfo.dwMaxEncodePower;
	WORD wMaxSupportChannel = m_stDspInfo.wMaxSupportChannel;
	WORD wChannelMaxSetSync = m_stDspInfo.wChannelMaxSetSync;
	BOOL bDoubleFrame = (m_stDspInfo.dwStreamCap & (0x01<<1)) ? TRUE:FALSE;

	if (NULL == m_pChannelInfo)
	{
		return FALSE;
	}
	// Check it is synchronized or not. The resolution shall be the same if you want to be synchronized. 
	if (wChannelMaxSetSync == 1)
	{
		for (int i = 0; i < m_nChannelCount/wMaxSupportChannel; i++)
		{
			int j = 0;
			BYTE byMainImageSize = m_pChannelInfo[i*wMaxSupportChannel].stMainVideoEncOpt[0].byImageSize;
			for (j = 1; j < wMaxSupportChannel; j++)
			{
				if (byMainImageSize != m_pChannelInfo[i*wMaxSupportChannel+j].stMainVideoEncOpt[0].byImageSize)
				{
					MessageBox(ConvertString(" DSP is synchronization, demand channel of DSP have the same sampling rate!"), ConvertString("Prompt"));
					return FALSE;
				}
				
			}

			if (bDoubleFrame)
			{
				BYTE byAssiImageSize = m_pChannelInfo[i*wMaxSupportChannel].stAssiVideoEncOpt[0].byImageSize;
				for (j = 1; j < wMaxSupportChannel; j++)
				{
					if (byAssiImageSize != m_pChannelInfo[i*wMaxSupportChannel+j].stAssiVideoEncOpt[0].byImageSize)
					{
						MessageBox(ConvertString(" DSP is synchronization, demand channel of DSP have the same sampling rate!"), ConvertString("Prompt"));
						return FALSE;
					}
					
				}
			}
			
		}
	}
	
	// Check it exceeds the highest encode capacity 
	for (int i = 0; i < m_nChannelCount/wMaxSupportChannel; i++)
	{
		DWORD dwCurEncodePower = 0;
		for (int j = 0; j < wMaxSupportChannel; j++)
		{
			//	When there is only main stream, system adds up encode capacity without chekcing video has been enabled or not. When there is extra stream, system needs to check video has benn enabled or not when adding up the encode capacity.
			if (bDoubleFrame)
			{
				BYTE byImageSize = m_pChannelInfo[i*wMaxSupportChannel+j].stMainVideoEncOpt[0].byImageSize;
				BYTE byFramesPerSec = m_pChannelInfo[i*wMaxSupportChannel+j].stMainVideoEncOpt[0].byFramesPerSec;
				
				if (m_pChannelInfo[i*wMaxSupportChannel+j].stMainVideoEncOpt[0].byVideoEnable)
				{
					dwCurEncodePower += GetFramePerSec(byFramesPerSec) * GetFenbianLv(byImageSize);
				}

				byImageSize = m_pChannelInfo[i*wMaxSupportChannel+j].stAssiVideoEncOpt[0].byImageSize;
				byFramesPerSec = m_pChannelInfo[i*wMaxSupportChannel+j].stAssiVideoEncOpt[0].byFramesPerSec;
				
				if (m_pChannelInfo[i*wMaxSupportChannel+j].stAssiVideoEncOpt[0].byVideoEnable)
				{
					dwCurEncodePower += GetFramePerSec(byFramesPerSec) * GetFenbianLv(byImageSize);
				}
			}
			else
			{
				BYTE byImageSize = m_pChannelInfo[i*wMaxSupportChannel+j].stMainVideoEncOpt[0].byImageSize;
				BYTE byFramesPerSec = m_pChannelInfo[i*wMaxSupportChannel+j].stMainVideoEncOpt[0].byFramesPerSec;
				dwCurEncodePower += GetFramePerSec(byFramesPerSec) * GetFenbianLv(byImageSize);
			}
		}

		if (dwCurEncodePower > dwMaxEncodePower)
		{
			MessageBox(ConvertString("Sampling rate and frame rate too high to out of the bigest code ability of DSP!"), ConvertString("Prompt"));
			return FALSE;
		}
	}

	return TRUE;
}

DWORD CConfigChannel::GetFenbianLv(WORD wImageSize)
{
	int width = 1;
	int height = 1;
	if(m_nVideoStandard == 0)  //PAL
	{
		switch (wImageSize)
		{
			case 0: 			width = 704;	height = 576;		break;//D1
			case 1:				width = 352;	height = 576;		break;//HD1
			case 2:				width = 704;	height = 288;		break;//BCIF
			case 3:				width = 352;	height = 288;		break;//CIF
			case 4:				width = 176;	height = 144;		break;//QCIF
			case 5:				width = 640;	height = 480;		break;//VGA
			case 6:				width = 320;	height = 240;		break;//QVGA
			case 7:				width = 480;	height = 480;		break;//SVCD
			case 8:				width = 160;	height = 128;		break;//QQVGA
			case 9:				width = 800;	height = 592;		break;//SVGA
			case 10:			width = 1024;	height = 768;		break;//XVGA
			case 11:			width = 1280;	height = 800;		break;//WXGA
			case 12:			width = 1280;	height = 1024;		break;//SXGA
			case 13:			width = 1600;	height = 1024;		break;//WSXGA
			case 14:			width = 1600;	height = 1200;		break;//UXGA
			case 15:			width = 1920;	height = 1200;		break;//WUXGA
			case 16:			width = 240;	height = 192;		break;//LTF
			case 17:			width = 1280;	height = 720;		break;//720
			case 18:			width = 1920;	height = 1080;		break;//1080
			case 19:			width = 1280;	height = 960;		break;//1_3M
			case 20:			width = 1872;	height = 1408;		break;//2M
			case 21:			width = 3744;	height = 1408;		break;//5M
			case 22:			width = 2048;	height = 1536;		break;//3M
			case 23:			width = 2432;	height = 2050;		break;//5_0M
			case 24:			width = 1216;	height = 1024;		break;//1_2M
			case 25:			width = 1408;	height = 1024;		break;//1408_1024
			case 26:			width = 3296;   height = 2472;		break;//8M
			case 27:			width = 2560;	height = 1920;		break;//2560_1920
			case 28:			width = 960;    height = 576;		break;//960H
			case 29:			width = 960;	height = 720;		break;//960_720
			default:	ASSERT(FALSE);				break;
		}
	}	
	else
	{
		switch (wImageSize)
		{
			case 0:				width = 704;	height = 480;		break;//D1
			case 1:				width = 352;	height = 480;		break;//HD1
			case 2:				width = 704;	height = 240;		break;//BCIF
			case 3:				width = 352;	height = 240;		break;//CIF
			case 4:				width = 176;	height = 120;		break;//QCIF
			case 5:				width = 640;	height = 480;		break;//VGA
			case 6:				width = 320;	height = 240;		break;//QVGA
			case 7:				width = 480;	height = 480;		break;//SVCD
			case 8:				width = 160;	height = 128;		break;//QQVGA
			case 9:				width = 800;	height = 592;		break;//SVGA
			case 10:			width = 1024;	height = 768;		break;//XVGA
			case 11:			width = 1280;	height = 800;		break;//WXGA
			case 12:			width = 1280;	height = 1024;		break;//SXGA
			case 13:			width = 1600;	height = 1024;		break;//WSXGA
			case 14:			width = 1600;	height = 1200;		break;//UXGA
			case 15:			width = 1920;	height = 1200;		break;//WUXGA
			case 16:			width = 240;	height = 192;		break;//LTF
			case 17:			width = 1280;	height = 720;		break;//720
			case 18:			width = 1920;	height = 1080;		break;//1080
			case 19:			width = 1280;	height = 960;		break;//1_3M
			case 20:			width = 1872;	height = 1408;		break;//2M
			case 21:			width = 3744;	height = 1408;		break;//5M
			case 22:			width = 2048;	height = 1536;		break;//3M
			case 23:			width = 2432;	height = 2050;		break;//5_0M
			case 24:			width = 1216;	height = 1024;		break;//1_2M
			case 25:			width = 1408;	height = 1024;		break;//1408_1024
			case 26:			width = 3296;   height = 2472;		break;//8M
			case 27:			width = 2560;	height = 1920;		break;//2560_1920
			case 28:			width = 960;    height = 480;		break;//960H
			case 29:			width = 960;	height = 720;		break;//960_720
			default:	ASSERT(FALSE);				break;
		}
	}

	return width*height;
}

DWORD CConfigChannel::GetFramePerSec(WORD wFramePerSec)
{
	DWORD dwRet = 1;

	if (m_nProtoVer >= 5)
	{
		dwRet = wFramePerSec;
	}
	else
	{
		if (0 == m_nVideoStandard)		//PAL
		{
			switch(wFramePerSec)
			{
				case 0:
				case 1:
				case 2:			dwRet = wFramePerSec + 1;			break;
				case 3:			dwRet = 6;							break;
				case 4:			dwRet = 12;							break;
				case 5:			dwRet = 25;							break;
				default:							break;
			}
		}
		else if (1 == m_nVideoStandard)	//NTSC
		{
			switch(wFramePerSec)
			{
				case 0:
				case 1:			dwRet = wFramePerSec + 1;			break;
				case 2:			dwRet = 4;							break;
				case 3:			dwRet = 7;							break;
				case 4:			dwRet = 15;							break;
				case 5:			dwRet = 20;							break;
				case 6:			dwRet = 30;							break;
				default:							break;
			}
		}
	}

	return dwRet;
}

DWORD CConfigChannel::GetFenbianLvEx(CAPTURE_SIZE emType)
{
	if(emType >= CAPTURE_SIZE_NR)
		return 1;
	
	DWORD dwRet = 0;
	PRESOLUTION pSlu = NULL;
	//用于保存pSlu初始指向
	PRESOLUTION pBase = NULL;
	
	
	
	if(PAL == m_nVideoStandard)  //PAL
	{
		pSlu = &m_stPALSlu[0];
		pBase = &m_stPALSlu[0];
	}
	else
	{
		pSlu = &m_stNTSCSlu[0];
		pBase = &m_stNTSCSlu[0];
	}
	
	for (int i = 0; i < CAPTURE_SIZE_NR; i++)
	{
		if(pSlu->emType == emType)
			break;
		pSlu++;
	}
	
	if ((pSlu - pBase) / sizeof(RESOLUTION) >= CAPTURE_SIZE_NR)
	{
		return 0;
	}
	if(NULL != pSlu)
		dwRet = pSlu->nWidth * pSlu->nHeight;
	
	return dwRet;
}

int CConfigChannel::Round_x(int value, int divisor)
{
	int modulus = value % divisor;
	if(modulus < divisor / 2)
	{
		return value - modulus;
	}
	else
	{
		return value + divisor - modulus;
	}
}

BOOL CConfigChannel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	ConvertComboBox(m_ctlImageQuality);
	ConvertComboBox(m_ctlBRCtl);
//	ConvertComboBox(m_ctlOSD);
//	ConvertComboBox(m_ctlBlindType);
	InitListView();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigChannel::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CConfigChannel::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_ctlVideoColorLst.GetItemCount())
	{
		if(0 < m_ctlVideoColorLst.GetSelectedCount())
		{
			int nIndex = m_ctlVideoColorLst.GetSelectionMark();
			if(-1 != nIndex)
			{
				m_ctlVideoColorLst.DeleteItem(nIndex);
			}
		}
	}
}




void CConfigChannel::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_nCurChannel >-1 && m_nCurChannel < 32)
	{
		CString strIndex; 
		CString strBrightness;
		CString strContrast;
		CString strSaturation;
		CString strChroma;
		CString strPlus;		
		CString strStartHour;
		CString strStartMinute;
		CString strStartSecond;
		CString strEndHour;	
		CString strEndMinute;	
		CString strEndSecond;
		BOOL bMask;
		
		BOOL bRet = GetVideoColorInfo(strIndex, strBrightness, strContrast, strSaturation, strChroma, strPlus,
			strStartHour, strStartMinute, strStartSecond,
			strEndHour, strEndMinute, strEndSecond, bMask);

		if(!bRet)
		{
			return;
		}

	
		InsertListView(strIndex, strBrightness, strContrast, strSaturation, strChroma, strPlus, 
			strStartHour, strStartMinute, strStartSecond,
			strEndHour, strEndMinute, strEndSecond, bMask);
	}
}

void CConfigChannel::OnButtonModify() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_ctlVideoColorLst.GetItemCount())
	{
		if(0 < m_ctlVideoColorLst.GetSelectedCount())
		{
			int nIndex = m_ctlVideoColorLst.GetSelectionMark();
			if(-1 != nIndex)
			{
				CString strIndex;
				CString strBrightness;
				CString strContrast;
				CString strSaturation;
				CString strChroma;
				CString strPlus;		
				CString strStartHour;
				CString strStartMinute;
				CString strStartSecond;
				CString strEndHour;
				CString strEndMinute;			
				CString strEndSecond;
				BOOL bMask;

				BOOL bRet = GetVideoColorInfo(strIndex, strBrightness, strContrast, strSaturation, strChroma, strPlus,
					strStartHour, strStartMinute, strStartSecond,
					strEndHour, strEndMinute, strEndSecond, bMask);			
				if(!bRet)
				{
					return;
				}

				m_ctlVideoColorLst.SetItemText(nIndex,1, strBrightness);
				m_ctlVideoColorLst.SetItemText(nIndex,2, strContrast);
				m_ctlVideoColorLst.SetItemText(nIndex,3, strSaturation);
				m_ctlVideoColorLst.SetItemText(nIndex,4, strChroma);
//				m_ctlVideoColorLst.SetItemText(nIndex,5, strPlus);
				m_ctlVideoColorLst.SetItemText(nIndex,5, strStartHour);
				m_ctlVideoColorLst.SetItemText(nIndex,6, strStartMinute);
				m_ctlVideoColorLst.SetItemText(nIndex,7, strStartSecond);
				m_ctlVideoColorLst.SetItemText(nIndex,8, strEndHour);
				m_ctlVideoColorLst.SetItemText(nIndex,9, strEndMinute);
				m_ctlVideoColorLst.SetItemText(nIndex,10, strEndSecond);
				if (bMask)
				{
					m_ctlVideoColorLst.SetItemText(nIndex, 11, "true");
				}
				else
				{
					m_ctlVideoColorLst.SetItemText(nIndex, 11, "false");
				}
			}
		}
	}
}


void CConfigChannel::OnItemchangedListVideocolor(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pNMListView ==NULL)
	{
		return;
	}
	if(pNMListView->uNewState == 3)
	{
		int nIndex = pNMListView->iItem;
		if(-1 != nIndex)
		{
			CString strTmp;

			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 1);
			SetDlgItemText(IDC_EDIT_BRIGHTNESS2, strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 2);
			SetDlgItemText(IDC_EDIT_CONTRAST2, strTmp);
			
			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 3);
			SetDlgItemText(IDC_EDIT_SATURATION2, strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 4);
			SetDlgItemText(IDC_EDIT_HUE2, strTmp);
			
//			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 5);
//			SetDlgItemText(IDC_EDIT_GAIN2, strTmp);
			
			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 5);
			SetDlgItemText(IDC_EDIT_STARTHOUR, strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 6);
			SetDlgItemText(IDC_EDIT_STARTMINUTE, strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 7);
			SetDlgItemText(IDC_EDIT_STARTSECOND, strTmp);


			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 8);
			SetDlgItemText(IDC_EDIT_ENDHOUR, strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 9);
			SetDlgItemText(IDC_EDIT_ENDMINUTE, strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 10);
			SetDlgItemText(IDC_EDIT_ENDSECOND, strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(nIndex, 11);
			if (0 == strcmp(strTmp.GetBuffer(0), "true"))
			{
				CButton *p = (CButton *)GetDlgItem(IDC_CHECK_MASK);
				p->SetCheck(1);
			}
			else if (0 == strcmp(strTmp.GetBuffer(0), "false"))
			{
				CButton *p = (CButton *)GetDlgItem(IDC_CHECK_MASK);
				p->SetCheck(0);
			}
		}
	}
	

	*pResult = 0;
}
BOOL CConfigChannel::GetVideoColorInfo(CString &strIndex,CString &strBrightness,CString &strContrast,CString &strSaturation, CString &strChroma, CString &strPlus, 
					   CString &strStartHour, CString &strStartMinute, CString &strStartSecond,
		CString &strEndHour,CString &strEndMinute,CString &strEndSecond, BOOL &bMask)
{

		int nCount = m_ctlVideoColorLst.GetItemCount();
			
		strIndex.Format("%d", nCount+1);

		
		int nTmp = GetDlgItemInt(IDC_EDIT_BRIGHTNESS2);
		if(nTmp < 0 || nTmp > 100 ) 
		{
			MessageBox(ConvertString("Brightness 0~100"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strBrightness.Format("%d", nTmp);
		}


		
		nTmp = GetDlgItemInt(IDC_EDIT_CONTRAST2);
		if(nTmp < 0 || nTmp > 100)
		{
			MessageBox(ConvertString("Contrast 0~100"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strContrast.Format("%d", nTmp);
		}

		
		nTmp = GetDlgItemInt(IDC_EDIT_SATURATION2);
		if(nTmp < 0 || nTmp > 100)
		{
			MessageBox(ConvertString("Saturation 0~100"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strSaturation.Format("%d", nTmp);
		}

	
		nTmp = GetDlgItemInt(IDC_EDIT_HUE2);
		if(nTmp < 0 || nTmp > 100)
		{
			MessageBox(ConvertString("Chroma 0~100"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strChroma.Format("%d", nTmp);
		}

	
		nTmp = GetDlgItemInt(IDC_EDIT_GAIN2);
		if(nTmp < 0 || nTmp > 100)
		{
			MessageBox(ConvertString("Plus 0~100"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strPlus.Format("%d", nTmp);
		}
		
		
		nTmp = GetDlgItemInt(IDC_EDIT_STARTHOUR);
		if(nTmp < 0 || nTmp >24)
		{
			MessageBox(ConvertString("StartHour 0~24"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strStartHour.Format("%d", nTmp);
		}

		
		nTmp = GetDlgItemInt(IDC_EDIT_STARTMINUTE);
		if(nTmp < 0 || nTmp > 60)
		{
			MessageBox(ConvertString("StartMinute 0~60"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strStartMinute.Format("%d", nTmp);
		}

	
		nTmp = GetDlgItemInt(IDC_EDIT_STARTSECOND);
		if(nTmp < 0 || nTmp > 60)
		{
			MessageBox(ConvertString("StartSecond 0~60"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strStartSecond.Format("%d",nTmp);
		}

		
		nTmp = GetDlgItemInt(IDC_EDIT_ENDHOUR);
		if(nTmp < 0 || nTmp >24)
		{
			MessageBox(ConvertString("EndHour 0~24"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strEndHour.Format("%d", nTmp);
		}
		
		
		nTmp = GetDlgItemInt(IDC_EDIT_ENDMINUTE);
		if(nTmp < 0 || nTmp > 60)
		{
			MessageBox(ConvertString("EndMinute 0~60"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strEndMinute.Format("%d", nTmp);
		}
		
	
		nTmp = GetDlgItemInt(IDC_EDIT_ENDSECOND);
		if(nTmp < 0 || nTmp > 60)
		{
			MessageBox(ConvertString("StartSecond 0~60"),ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			strEndSecond.Format("%d",nTmp);
		}

		CButton *p = (CButton *)GetDlgItem(IDC_CHECK_MASK);
		bMask = p->GetCheck();
		
		return TRUE;
}
void CConfigChannel::SaveVideoColorInfo(int nNum)
{
	if(nNum  > -1 || nNum < 32)
	{
		AV_CFG_ChannelVideoColor *pstVideoColor = &m_pstChannelVideoColor[nNum];
		
		int nCount = m_ctlVideoColorLst.GetItemCount();
		nCount = nCount > AV_CFG_Max_VideoColor ? AV_CFG_Max_VideoColor:nCount;
		int i = 0;
		CString strTmp;
		for(i = 0; i < nCount; i ++)
		{	
			strTmp = m_ctlVideoColorLst.GetItemText(i, 1);
			pstVideoColor->stuColor[i].nBrightness = atol(strTmp);
	
	
			strTmp = m_ctlVideoColorLst.GetItemText(i, 2);
			pstVideoColor->stuColor[i].nContrast = atol(strTmp);

	
			strTmp = m_ctlVideoColorLst.GetItemText(i, 3);
			pstVideoColor->stuColor[i].nSaturation = atol(strTmp);

	
			strTmp = m_ctlVideoColorLst.GetItemText(i,4);
			pstVideoColor->stuColor[i].nHue = atol(strTmp);

//			strTmp = m_ctlVideoColorLst.GetItemText(i,5);
//			pstVideoColor->stuColor[i].nGamma = atol(strTmp);
			

			strTmp = m_ctlVideoColorLst.GetItemText(i, 5);
			pstVideoColor->stuColor[i].stuTimeSection.nBeginHour = atol(strTmp);


			strTmp = m_ctlVideoColorLst.GetItemText(i, 6);
			pstVideoColor->stuColor[i].stuTimeSection.nBeginMinute = atol(strTmp);

	
			strTmp = m_ctlVideoColorLst.GetItemText(i, 7);
			pstVideoColor->stuColor[i].stuTimeSection.nBeginSecond = atol(strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(i, 8);
			pstVideoColor->stuColor[i].stuTimeSection.nEndHour = atol(strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(i, 9);
			pstVideoColor->stuColor[i].stuTimeSection.nEndMinute = atol(strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(i ,10);
			pstVideoColor->stuColor[i].stuTimeSection.nEndSecond = atol(strTmp);

			strTmp = m_ctlVideoColorLst.GetItemText(i, 11);
			if (0 == strcmp(strTmp.GetBuffer(0), "true"))
			{
				pstVideoColor->stuColor[i].stuTimeSection.nMask = 1;
			}
			else if (0 == strcmp(strTmp.GetBuffer(0), "false"))
			{
				pstVideoColor->stuColor[i].stuTimeSection.nMask = 0;
			}
		}
        pstVideoColor->nColorNum = nCount;
	}
}

VOID CConfigChannel::InitResolution()
{
	memset(&m_stNTSCSlu, 0, sizeof(m_stNTSCSlu));
	memset(&m_stPALSlu, 0, sizeof(m_stNTSCSlu));
	
	CCommon cc;
	cc.ReadResolution(m_stPALSlu, sizeof(m_stPALSlu), PAL, TRUE);
	cc.ReadResolution(m_stNTSCSlu, sizeof(m_stNTSCSlu), NTSC, TRUE);
}

int CConfigChannel::GetImageBitRate(int imageSize, int frames, int &minBitRate, int&maxBitRate, int Iframes /* = 50 */)
{
	CCommon cc;
	int nIndexChannel = m_ctlChannel.GetCurSel();
	if (CB_ERR == nIndexChannel)
	{
        return 1;
	}
	int nChannel = m_ctlChannel.GetItemData(nIndexChannel);
	if (Iframes < 1)
	{
		Iframes = 1;
	}
	
	int nMin_CIF_pFrame_Size = MIN_CIF_PFRAME_SIZE;
	int nMax_CIF_pFrame_Size = MAX_CIF_PFRAME_SIZE;
	if (m_EncodeCaps.stuVideoEncodeCap[nChannel].nMinCIFFrame > 0)
	{
		nMin_CIF_pFrame_Size = m_EncodeCaps.stuVideoEncodeCap[nChannel].nMinCIFFrame;
	}
	if (m_EncodeCaps.stuVideoEncodeCap[nChannel].nMaxCIFFrame > 0)
	{
		nMax_CIF_pFrame_Size = m_EncodeCaps.stuVideoEncodeCap[nChannel].nMaxCIFFrame;
	}
	LONGLONG GOP = (Iframes > 149)?50:Iframes;
	LONGLONG FPS = frames;
	
	LONGLONG llUP ,llDown;
	llUP = (GOP+IFRAME_PFRAME_QUOTIENT-1)*FPS*nMin_CIF_pFrame_Size;
	llDown = GOP ;
	
	LONGLONG llMin = GetFenbianLvEx((CAPTURE_SIZE)imageSize) * llUP / llDown /(352 * 288);
	minBitRate = llMin;
	
	if (minBitRate >= 4)
	{
		minBitRate = Round_x(minBitRate, (1 << cc.log2i(minBitRate)) / 4);  // 按16K，32K，64K等等对齐
	}	
	
	llUP = (GOP+IFRAME_PFRAME_QUOTIENT-1)*FPS*nMax_CIF_pFrame_Size ;
	llDown = GOP ;
	
	LONGLONG llMax = GetFenbianLvEx((CAPTURE_SIZE)imageSize) * llUP / llDown /(352 * 288);
	
	maxBitRate = llMax;
	
	if (maxBitRate >= 4)
	{
		maxBitRate = Round_x(maxBitRate , (1 << cc.log2i(maxBitRate )) / 4);  // 按16K，32K，64K等等对齐
	}
	
	return 0;
}

CFG_ENCODECAP* CConfigChannel::GetEncodeCap()
{
	return &m_EncodeCaps;
}

void CConfigChannel::ShowFpsRange()
{
	int nShowFlag = m_bShowFpsRange ? SW_SHOW:SW_HIDE;
	m_ctlLimitStream.ShowWindow(nShowFlag);
	GetDlgItem(IDC_STATIC_RANGEUNIT)->ShowWindow(nShowFlag);
	GetDlgItem(IDC_STATIC_MAXFPS)->ShowWindow(nShowFlag);
	GetDlgItem(IDC_STATIC_RANGECHAR)->ShowWindow(nShowFlag);
	GetDlgItem(IDC_STATIC_MINFPS)->ShowWindow(nShowFlag);
	GetDlgItem(IDC_STATIC_REFBIT)->ShowWindow(nShowFlag);
	if (!m_bShowFpsRange)
	{
        return;
	}
	int iFrameIndex = m_ctlFrame.GetCurSel();
	if (CB_ERR == iFrameIndex)
	{
        return;
	}
    int iCurFrame = m_ctlFrame.GetItemData(iFrameIndex);
	
	int iResolutionIndex = m_ctlResolution.GetCurSel();
	if (CB_ERR == iResolutionIndex)
	{
        return;
	}
	//int iIframes = GetDlgItemInt(IDC_EDIT_IFRAME);
    int iCurResolution = m_ctlResolution.GetItemData(iResolutionIndex);
	// 获取最大、最小限码流并显示
	GetImageBitRate(iCurResolution,iCurFrame,m_iMinFps,m_iMaxFps,2*iCurFrame);
	m_iMaxFps = m_iMaxFps > MAXFPS_LIMIT? MAXFPS_LIMIT : m_iMaxFps;
    SetDlgItemInt(IDC_STATIC_MINFPS, m_iMinFps);
	SetDlgItemInt(IDC_STATIC_MAXFPS, m_iMaxFps);
	// 填充限码流combox
	m_ctlLimitStream.ResetContent();
    int ni = 0;
	int nFpsOptions[25] = {32,48,64,80,96,128,160,192,224,256,320,384,448,512,640,
		768,896,1024,1280,1536,1792,2048,4096,6144,8192};
	char szTemp[20] = {0};
	for (int j = 0; j < 25; ++j)
	{
		memset(szTemp,0,20);
        if (m_iMinFps <= nFpsOptions[j] && m_iMaxFps >= nFpsOptions[j])
        {
			CCommon::InitComboBox(&m_ctlLimitStream, ni++, itoa(nFpsOptions[j],szTemp,10), nFpsOptions[j]);
        }
	}
    CCommon::InitComboBox(&m_ctlLimitStream, ni++, ConvertString("Custom"), 0);
	
}

void CConfigChannel::SetFpsValue(int iBitRate)
{
	SetDlgItemInt(IDC_EDIT_LIMITSTREAM, iBitRate);
	if (!m_bShowFpsRange)
	{
        return;
	}
	int iCount = m_ctlLimitStream.GetCount();
	// 自定义选项，显示可编辑的限码流
	int iRetIndex = CCommon::SetCurSelByData(&m_ctlLimitStream, iBitRate);

	if ((iCount -1) == iRetIndex)
	{
		GetDlgItem(IDC_EDIT_LIMITSTREAM)->ShowWindow(SW_SHOW);
	}
	else
	{
        GetDlgItem(IDC_EDIT_LIMITSTREAM)->ShowWindow(SW_HIDE);
	}
}

void CConfigChannel::OnSelchangeComboFrame() 
{
	// TODO: Add your control notification handler code here
	if (!m_bShowFpsRange)
	{
        return;
	}
	ShowFpsRange();
	int iBitRate = GetDlgItemInt(IDC_EDIT_LIMITSTREAM);
    if (m_iMaxFps < iBitRate)
    {
		iBitRate = m_iMaxFps;
    }
	else if (m_iMinFps > iBitRate)
	{
		iBitRate = m_iMinFps;
	}
    CCommon::SetCurSelByData(&m_ctlLimitStream, iBitRate);
    SetDlgItemInt(IDC_EDIT_LIMITSTREAM, iBitRate);
}

void CConfigChannel::OnSelchangeComboResolution() 
{
	// TODO: Add your control notification handler code here
	OnSelchangeComboFrame();
}

void CConfigChannel::OnSelchangeComboLimitstream() 
{
	// TODO: Add your control notification handler code here
	int iCurIndex = m_ctlLimitStream.GetCurSel();
	if (CB_ERR == iCurIndex)
	{
	    return;
	}
	if (iCurIndex == m_ctlLimitStream.GetCount() - 1)
	{
        GetDlgItem(IDC_EDIT_LIMITSTREAM)->ShowWindow(SW_SHOW);
	}
	else
	{
        GetDlgItem(IDC_EDIT_LIMITSTREAM)->ShowWindow(SW_HIDE);
        SetDlgItemInt(IDC_EDIT_LIMITSTREAM, m_ctlLimitStream.GetItemData(iCurIndex));
	}
}
