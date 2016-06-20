// ConfigChannel.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigChannelEx.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigChannelEx dialog
CConfigChannelEx::CConfigChannelEx(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigChannelEx::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigChannelEx)
	//}}AFX_DATA_INIT
	m_nChannelCount = 0;
	m_nCurChannel = -1;
	m_nCurStream = -1;
	m_nVideoStandard = 0;
	m_bShowPix = FALSE;
	m_stEncodeInfo = NULL;
	m_pChannelInfo = NULL;
	m_iMinFps = 0;
	m_iMaxFps = 0;
	memset(&m_stEncodeCaps, 0, sizeof(m_stEncodeCaps));
	SET_SIZE(m_stEncodeCaps);
}

void CConfigChannelEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigChannelEx)
	DDX_Control(pDX, IDC_COMBO_IMGQUALITY, m_ctlImageQuality);
	DDX_Control(pDX, IDC_COMBO_FRAME, m_ctlFrame);
	DDX_Control(pDX, IDC_COMBO_BRCTRL, m_ctlBRCtl);
	DDX_Control(pDX, IDC_CHECK_AUDIO, m_ctlAudio);
	DDX_Control(pDX, IDC_CHECK_VIDEO, m_ctlVideo);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_ctlStream);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_ctlResolution);
	DDX_Control(pDX, IDC_COMBO_ENCODETYPE, m_ctlEncodeType);
	DDX_Control(pDX, IDC_COMBO_CHANNO, m_ctlChannel);
	DDX_Check(pDX, IDC_CHECK_AUDIO_OVERLAY, m_bAudioOverlay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConfigChannelEx, CDialog)
	//{{AFX_MSG_MAP(CConfigChannelEx)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNO, OnSelchangeComboChanno)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM, OnSelchangeComboStream)
	ON_WM_CANCELMODE()
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, OnSelchangeComboResolution)
	ON_CBN_SELCHANGE(IDC_COMBO_ENCODETYPE, OnSelchangeComboEncodetype)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAME, OnSelchangeComboFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigChannelEx message handlers
BOOL CConfigChannelEx::ParseVideoResolutionType(std::string resolutionType, int& nWidth, int& nHight)
{
    unsigned int unIndex;
    for (unIndex = 0; unIndex < resolutionNameCount; unIndex++)
    {
        if (_stricmp(szResolutionNames[unIndex], resolutionType.c_str()) == 0)
        {
            nWidth = stuResolutions[unIndex].snWidth;
            nHight = stuResolutions[unIndex].snHight;
            break;
        }
    }
    for (unIndex = 0; unIndex < stdRstNameCount; unIndex++)
    {
        if (_stricmp(szStantardResolutionNames[unIndex], resolutionType.c_str()) == 0)
        {
            nWidth = stuStantardResolutions[m_nVideoStandard][unIndex].snWidth;
            nHight = stuStantardResolutions[m_nVideoStandard][unIndex].snHight;
            break;
        }
    }
    // "123x456" format resolutions
    int nWidthTemp = 0;
    int nHightTemp = 0;
    // 1080p以上分辨率保存失败修复，其实是123x456格式分辨率处理问题
    if (sscanf(resolutionType.c_str(), "%dx%d", &nWidthTemp, &nHightTemp) == 2)
    {
        nWidth = nWidthTemp;
        nHight = nHightTemp;
    }
    return nWidth && nHight;
}

std::string  CConfigChannelEx::PacketVideoResolutionType(int nWidth, int nHight)
{
    unsigned int unIndex;
    std::string resolutionType = "";
    for (unIndex = 0; unIndex < resolutionNameCount; unIndex++)
    {
        if (stuResolutions[unIndex].snHight == nHight
            && stuResolutions[unIndex].snWidth == nWidth)
        {
            resolutionType = szResolutionNames[unIndex];
            break;
        }
    }
    for (unIndex = 0; unIndex < stdRstNameCount; unIndex++)
    {
        if (stuStantardResolutions[m_nVideoStandard][unIndex].snHight == nHight
            && stuStantardResolutions[m_nVideoStandard][unIndex].snWidth == nWidth)
        {
            resolutionType = szStantardResolutionNames[unIndex];
            break;
        }
    }
    // "123x456" format resolutions
    if (resolutionType.empty())
    {
        char szTemp[32] = {0};
        sprintf(szTemp, "%dx%d", nWidth, nHight);
        resolutionType = szTemp;
    }
    return resolutionType;
}

void CConfigChannelEx::RefreshCaps()
{
    // 根据配置获取能力集
    m_bShowPix = FALSE;
    ((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneChannelDspConfigF6(m_nCurChannel, m_stEncodeInfo[m_nCurChannel], 
            m_stEncodeCaps, m_bShowPix);

}
//Save
void CConfigChannelEx::OnButtonApply() 
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
	    ((CClientDemo5Dlg*)AfxGetMainWnd())->SetOneChannelConfigInfo(&m_stEncodeInfo[m_nCurChannel], m_nCurChannel);

	}
	else
	{
		MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
	}
}

//Read
void CConfigChannelEx::OnButtonReadall() 
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
void CConfigChannelEx::InitDlgInfo(int nChannelCount, int nVideoStandard)
{
//	m_stDspInfo = stDspInfo;
	m_nVideoStandard = nVideoStandard;
	m_stEncodeInfo = new CFG_ENCODE_INFO[CHANNEL_NUM_LIMIT];
	if(NULL != m_stEncodeInfo)
	{
		memset(m_stEncodeInfo, 0, CHANNEL_NUM_LIMIT*sizeof(CFG_ENCODE_INFO));
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

    //Set bit stream
    m_ctlStream.ResetContent();
    nIndex = m_ctlStream.AddString(ConvertString("Main Data stream"));
    m_ctlStream.SetItemData(nIndex,0);
    nIndex = m_ctlStream.AddString(ConvertString("Sub Data stream"));
	m_ctlStream.SetItemData(nIndex,3);

	//Select channel 0
	if(0 < m_ctlChannel.GetCount())
	{
		m_ctlChannel.SetCurSel(0);
		OnSelchangeComboChanno();
	}
}

void CConfigChannelEx::OnInitCtrl(int nIndex, BOOL bEncodeModeFlag)
{
    NET_STREAM_CFG_CAPS stuFormatCap = m_stEncodeCaps.stuMainFormatCaps[0];
    CFG_VIDEOENC_OPT stuVideoOpt = m_stEncodeInfo[m_nCurChannel].stuMainStream[0];
    if (nIndex)
    {
        stuFormatCap = m_stEncodeCaps.stuExtraFormatCaps[0];
        stuVideoOpt = m_stEncodeInfo[m_nCurChannel].stuExtraStream[0];
    }
    // 不同编码模式对应分辨率集合相同,不需要重填充
    if (TRUE == bEncodeModeFlag && FALSE == stuFormatCap.abIndivResolution)
    {
        return;
    }
    int nResolutionTypeNum = stuFormatCap.nResolutionTypeNum;
    DH_RESOLUTION_INFO* pResolution = stuFormatCap.stuResolutionTypes;
    // 不同编码模式对应不同的分辨率集合
    if (stuFormatCap.abIndivResolution)
    {
        nResolutionTypeNum = stuFormatCap.nIndivResolutionNums[stuVideoOpt.stuVideoFormat.emCompression];// Resolution Num
        pResolution = stuFormatCap.stuIndivResolutionTypes[stuVideoOpt.stuVideoFormat.emCompression];// Resolutions array
    }
    m_ctlResolution.ResetContent();
    int nIndexRsn = 0;
    std::string strTemp;
    for (int k=0; k<nResolutionTypeNum; ++k)
    {
        strTemp = PacketVideoResolutionType((pResolution+k)->snWidth, (pResolution+k)->snHight);
        nIndexRsn = m_ctlResolution.AddString(strTemp.c_str());
 		m_ctlResolution.SetItemData(nIndexRsn,k);
    }
    // 编码模式切换,只重填分辨率
    if (TRUE == bEncodeModeFlag)
    {
        return;
    }
    // Set dropdown menu in decode mode by encode subnet mask setup.
    m_ctlEncodeType.ResetContent();
    const int nH264ProfileRankNum = stuFormatCap.nH264ProfileRankNum;
    const BYTE* bH264ProfileRank = stuFormatCap.bH264ProfileRank;
    for (int j = 0; j < encodeCount; j++)
    {
        //dwEncodeModeMask is encode mode subnet mask. Each bit means the encode mode setup the device supported. 
        if (stuFormatCap.dwEncodeModeMask & (0x01<<j))
        {
            // DH_CAPTURE_COMP_H264
            if ((j == 7) && nH264ProfileRankNum)
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
}

void CConfigChannelEx::OnInitFpsRange()
{
    m_iMinFps = m_stEncodeCaps.stuMainFormatCaps[0].nMinBitRateOptions;
    m_iMaxFps = m_stEncodeCaps.stuMainFormatCaps[0].nMaxBitRateOptions;
    if (m_nCurStream)
    {
        m_iMinFps = m_stEncodeCaps.stuExtraFormatCaps[0].nMinBitRateOptions;
        m_iMaxFps = m_stEncodeCaps.stuExtraFormatCaps[0].nMaxBitRateOptions;
    }
    SetDlgItemInt(IDC_STATIC_MINFPS, m_iMinFps);
    SetDlgItemInt(IDC_STATIC_MAXFPS, m_iMaxFps);
}

//Channel switch 
void CConfigChannelEx::OnSelchangeComboChanno() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = (int)m_ctlChannel.GetItemData(nIndex);
		m_nCurChannel = nNum;
        // 获取配置
        ((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneChannelConfigInfo(&m_stEncodeInfo[m_nCurChannel], m_nCurChannel);
        // 更新能力集
        RefreshCaps();
        // 填充控件
		OnInitCtrl(0);// 0初始化为主码流
		
		//Display channel related information 
		m_ctlStream.SetCurSel(0);
        m_nCurStream = 0;
		ShowStreamInfo(nNum,0);
        RefreshFrame();
		UpdateData(FALSE);
	}
}

//Bit stream switch 
void CConfigChannelEx::OnSelchangeComboStream() 
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
            OnInitCtrl(nItem);
			ShowStreamInfo(nNum,nItem);
            RefreshFrame();
		}
	}
}

//Save bit stream information 
void CConfigChannelEx::SaveStreamInfo(int nNum, int nItem)
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
        if (CB_ERR != nIndex)
        {
            pStreamInfo->stuVideoFormat.nFrameRate = (BYTE)m_ctlFrame.GetItemData(nIndex);
        }
		
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
        CString strRsn;
		nIndex = m_ctlResolution.GetCurSel();
        if (CB_ERR != nIndex)
        {
            m_ctlResolution.GetLBText(nIndex, strRsn);
        }
		
        ParseVideoResolutionType(strRsn.GetBuffer(0),pStreamInfo->stuVideoFormat.nWidth, pStreamInfo->stuVideoFormat.nHeight);

		//Image quality 
		pStreamInfo->stuVideoFormat.emImageQuality = (CFG_IMAGE_QUALITY)(m_ctlImageQuality.GetCurSel() + 1);
		//Audio overlay
		pStreamInfo->bAudioAddEnable = m_bAudioOverlay;
	}
}

//Save channel information 
void CConfigChannelEx::SaveChannelInfo(int nNum)
{
	if(-1 < nNum && -1 < m_nCurStream)
	{
		CFG_ENCODE_INFO *pInfo = &(m_stEncodeInfo[nNum]);
		if(NULL != pInfo)
		{
			SaveStreamInfo(nNum,m_nCurStream);
		}
	}
}

//Display bit stream information 
void CConfigChannelEx::ShowStreamInfo(int nNum, int nItem)
{
 	if(NULL == m_stEncodeInfo)
 	{
		return;
	}
 
 	CFG_ENCODE_INFO Info = m_stEncodeInfo[nNum];
	CFG_VIDEOENC_OPT StreamInfo = {0};
 
	BYTE bImage = 0;
    std::string strRsnTemp;
 	if(0 <= nItem && 3 > nItem)
	{
		StreamInfo = Info.stuMainStream[nItem];
        m_iMinFps = m_stEncodeCaps.stuMainFormatCaps[nItem].nMinBitRateOptions;
        m_iMaxFps = m_stEncodeCaps.stuMainFormatCaps[nItem].nMaxBitRateOptions;
		strRsnTemp = PacketVideoResolutionType(Info.stuMainStream[nItem].stuVideoFormat.nWidth, Info.stuMainStream[nItem].stuVideoFormat.nHeight);
	}
 	else if(3 <= nItem && 6 >nItem)
	{
		StreamInfo = Info.stuExtraStream[nItem-3];
        m_iMinFps = m_stEncodeCaps.stuExtraFormatCaps[nItem-3].nMinBitRateOptions;
        m_iMaxFps = m_stEncodeCaps.stuExtraFormatCaps[nItem-3].nMaxBitRateOptions;
		strRsnTemp = PacketVideoResolutionType(Info.stuExtraStream[nItem-3].stuVideoFormat.nWidth, Info.stuExtraStream[nItem-3].stuVideoFormat.nHeight);
	}
	//Enable video 
 	m_ctlVideo.SetCheck(StreamInfo.bVideoEnable);
	
	//Enable audio 
	m_ctlAudio.SetCheck(StreamInfo.bAudioEnable);
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
    //m_ctlEncodeType.FindStringExact(-1, itemStr);

	//Resolution 
    m_ctlResolution.SelectString(-1, strRsnTemp.c_str());

    SetDlgItemInt(IDC_STATIC_MINFPS, m_iMinFps);
    SetDlgItemInt(IDC_STATIC_MAXFPS, m_iMaxFps);
    SetDlgItemInt(IDC_EDIT_LIMITSTREAM, StreamInfo.stuVideoFormat.nBitRate);
 	//Video quality 
 	m_ctlImageQuality.SetCurSel(StreamInfo.stuVideoFormat.emImageQuality - 1);
    //Audio encode 
	m_bAudioOverlay = StreamInfo.bAudioAddEnable;
}

//Clear 
void CConfigChannelEx::CleanAll()
{
	m_ctlChannel.SetCurSel(-1);
	m_ctlStream.SetCurSel(-1);
	m_ctlBRCtl.SetCurSel(-1);
	m_ctlFrame.SetCurSel(-1);
	m_ctlEncodeType.SetCurSel(-1);
	m_ctlResolution.SetCurSel(-1);
	m_ctlImageQuality.SetCurSel(-1);
    m_ctlChannel.ResetContent();
	m_ctlStream.ResetContent();

	SetDlgItemText(IDC_EDIT_TRACKNUM,"");
	SetDlgItemText(IDC_EDIT_BITPERSMPL,"");
	SetDlgItemText(IDC_EDIT_SMPLPERSEC,"");
	SetDlgItemText(IDC_STATIC_SHOW, "");
	SetDlgItemInt(IDC_STATIC_MINFPS,0);
	SetDlgItemInt(IDC_STATIC_MAXFPS,0);	
	SetDlgItemInt(IDC_EDIT_LIMITSTREAM, 0);
	GetDlgItem(IDC_EDIT_LIMITSTREAM)->ShowWindow(TRUE); // 复位ui的显示
	
	m_nChannelCount = 0;
	m_nCurChannel = -1;
	m_nCurStream = -1;
	if(m_stEncodeInfo)
	{
		delete[] m_stEncodeInfo;
		m_stEncodeInfo = NULL;
	}
	if(m_pChannelInfo)
	{
		delete[] m_pChannelInfo;
		m_pChannelInfo = NULL;
	}
}

BOOL CConfigChannelEx::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	ConvertComboBox(m_ctlImageQuality);
	ConvertComboBox(m_ctlBRCtl);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigChannelEx::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CConfigChannelEx::RefreshFrame() 
{
    NET_STREAM_CFG_CAPS stuFormatCap = m_stEncodeCaps.stuMainFormatCaps[0];
    CFG_VIDEOENC_OPT stuVideoOpt = m_stEncodeInfo[m_nCurChannel].stuMainStream[0];
    if (3 <= m_nCurStream && 6 >m_nCurStream)
    {
        stuFormatCap = m_stEncodeCaps.stuExtraFormatCaps[0];
        stuVideoOpt = m_stEncodeInfo[m_nCurChannel].stuExtraStream[0];
    }
    // 重填帧率下拉框
    unsigned int unIndex = 0;
    for (; unIndex < stuFormatCap.nResolutionTypeNum; unIndex++)
    {
        if (stuFormatCap.stuResolutionTypes[unIndex].snHight == stuVideoOpt.stuVideoFormat.nHeight
            && stuFormatCap.stuResolutionTypes[unIndex].snWidth == stuVideoOpt.stuVideoFormat.nWidth)
        {
            break;
        }
    }
    // 优先按分辨率取对应最大帧率
    int nMaxFrame = stuFormatCap.nResolutionFPSMax[unIndex];
    // 设备不同分辨率,nFPSMax可能变化,此处兼容处理
    if (0 >= nMaxFrame)
    {
        nMaxFrame = stuFormatCap.nFPSMax;
    }
    // 设备有返回,但最大帧率为0,按制式填默认值(PAL-25,NTSC-30)
    if (0 >= nMaxFrame)
    {
        nMaxFrame = m_nVideoStandard ? 30:25;
    }
    // Frame rate dropdown menu
    m_ctlFrame.ResetContent();
    int nIndex = 0;
    CString str;
    for (int i = 1; i <= nMaxFrame; i++)
    {
        str.Format("%d", i);
        nIndex = m_ctlFrame.AddString(str);
        m_ctlFrame.SetItemData(nIndex, i);
    }
    m_ctlFrame.SetCurSel(stuVideoOpt.stuVideoFormat.nFrameRate-1);
}

void CConfigChannelEx::OnSelchangeComboResolution() 
{
	// TODO: Add your control notification handler code here
    SaveStreamInfo(m_nCurChannel, m_nCurStream);
    RefreshCaps();
    RefreshFrame();
        
    OnInitFpsRange();
}

BOOL CConfigChannelEx::Attach(UINT uID, CDialog* pAttachDlg)
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
    
    //hide the attach window
    pAttachDlg->GetDlgItem(uID)->ShowWindow(SW_HIDE);
    
    this->MoveWindow(&rect, TRUE);
    this->ShowWindow(SW_SHOW);
    
    return TRUE;
}

void CConfigChannelEx::OnSelchangeComboEncodetype() 
{
	// TODO: Add your control notification handler code here
    SaveStreamInfo(m_nCurChannel, m_nCurStream);
    RefreshCaps();
	OnInitCtrl(m_nCurStream, TRUE);
    OnInitFpsRange();
}

void CConfigChannelEx::OnSelchangeComboFrame() 
{
	// TODO: Add your control notification handler code here
    SaveStreamInfo(m_nCurChannel, m_nCurStream);
	RefreshCaps();
    OnInitFpsRange();
}
