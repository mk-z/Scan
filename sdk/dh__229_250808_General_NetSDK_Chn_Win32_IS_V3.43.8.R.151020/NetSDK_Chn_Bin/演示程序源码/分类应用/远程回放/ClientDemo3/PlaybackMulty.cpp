// PlaybackMulty.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo3.h"
#include "PlaybackMulty.h"
#include "ClientDemo3Dlg.h"
#include "ChannelOneDialog.h"
#include "FourChannelsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlaybackMulty dialog


CPlaybackMulty::CPlaybackMulty(CWnd* pParent /*=NULL*/, const LLONG& lLoginID)
	: m_hLoginID(lLoginID), CDialog(CPlaybackMulty::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlaybackMulty)
	m_nBitRate = 1024;
	m_nFps = 25;
	m_DateFrom = COleDateTime::GetCurrentTime();
	m_DateTo = COleDateTime::GetCurrentTime();
	m_TimeFrom = 0;
	m_TimeTo = 0;
    m_pOneChannelDlg = NULL;
    m_pFourChannelsDlg = NULL;
    m_bEnableComboBoxFlag = false;
    m_nTotalChannel = 0;
	//}}AFX_DATA_INIT
}


void CPlaybackMulty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlaybackMulty)
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_cStreamType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cChannel);
	DDX_Control(pDX, IDC_COMBO_PLAYTYPE, m_cPlayType);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_cResolution);
	DDX_Control(pDX, IDC_COMBO_MULTYPLAYMODE, m_cMultyPlayMode);
	DDX_Text(pDX, IDC_EDIT_BITRATE, m_nBitRate);
	DDV_MinMaxInt(pDX, m_nBitRate, 192, 1024);
	DDX_Text(pDX, IDC_EDIT_FPS, m_nFps);
	DDV_MinMaxInt(pDX, m_nFps, 1, 25);
	DDX_DateTimeCtrl(pDX, IDC_DATE_FROM, m_DateFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATE_TO, m_DateTo);
	DDX_DateTimeCtrl(pDX, IDC_TIME_FROM, m_TimeFrom);
	DDX_DateTimeCtrl(pDX, IDC_TIME_TO, m_TimeTo);
	DDX_Text(pDX, IDC_EDIT_TOTALCHANNEL, m_nTotalChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlaybackMulty, CDialog)
	//{{AFX_MSG_MAP(CPlaybackMulty)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_CHANNELS_CHOOSE, OnButtonChannelsChoose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlaybackMulty message handlers

NET_TIME CPlaybackMulty::ConvertToDateTime(const COleDateTime &date, const CTime &time)
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

int CPlaybackMulty::Compare( const NET_TIME *pSrcTime, const NET_TIME *pDestTime)
{
    SYSTEMTIME srcTime={0}, destTime={0};
    srcTime.wYear   = (WORD)pSrcTime->dwYear;
    srcTime.wMonth  = (WORD)pSrcTime->dwMonth;
    srcTime.wDay    = (WORD)pSrcTime->dwDay;
    srcTime.wHour   = (WORD)pSrcTime->dwHour;
    srcTime.wMinute = (WORD)pSrcTime->dwMinute;
    srcTime.wSecond = (WORD)pSrcTime->dwSecond;
    /// dest
    destTime.wYear  = (WORD)pDestTime->dwYear;
    destTime.wMonth = (WORD)pDestTime->dwMonth;
    destTime.wDay   = (WORD)pDestTime->dwDay;
    destTime.wHour  = (WORD)pDestTime->dwHour;
    destTime.wMinute = (WORD)pDestTime->dwMinute;
    destTime.wSecond = (WORD)pDestTime->dwSecond;
    FILETIME   srcFileTime={0}, destFileTime={0};
    SystemTimeToFileTime(&srcTime, &srcFileTime);
    SystemTimeToFileTime(&destTime, &destFileTime);
    return CompareFileTime(&srcFileTime, &destFileTime);
}

void CPlaybackMulty::OnButtonPlay() 
{
	// TODO: Add your control notification handler code here
    //NET_RECORDFILE_INFO sFileInfo[2000];
    NET_TIME sEerlistStartTime;
    int nBaseChannel = 0;
    int nFileCount = 0;
    BOOL bValid = UpdateData(TRUE);

    // Set search type first
    int nStreamIndex = m_cStreamType.GetCurSel();
    DWORD dwStream = m_cStreamType.GetItemData(nStreamIndex);
    BOOL bRet = CLIENT_SetDeviceMode(m_hLoginID, DH_RECORD_STREAM_TYPE, &dwStream);
    if (TRUE != bRet)
    {
        MessageBox(ConvertString("Set stream type failed"), ConvertString("Prompt"));
    }

    if(bValid && (0 != m_hLoginID))
    {
        if (false == m_bEnableComboBoxFlag)
        {
            MessageBox(ConvertString("InitComboBox fail, can not play!"), ConvertString("Prompt"));
            return ;
        }
        //Channel number
        int nIndex = 0;
        int nChannelCount = 0;
        if (m_cChannel.GetCount() > 0)
        {
            nIndex = m_cChannel.GetCurSel();
            nChannelCount = m_cChannel.GetItemData(nIndex);
        }
        else
        {
            MessageBox(ConvertString("Channel mode error!"), ConvertString("Prompt"));
            return ;
        }

        //Time
        NET_TIME netTimeFrom = ConvertToDateTime(m_DateFrom, m_TimeFrom);
        NET_TIME netTimeTo = ConvertToDateTime(m_DateTo, m_TimeTo);

        if (Compare(&netTimeFrom, &netTimeTo) >= 0)
        {
            MessageBox(ConvertString("Invalid time!"), ConvertString("Prompt"));
            return ;
        }

        int nResolution = 0;
        if (m_cResolution.GetCount() > 0)
        {
            nResolution = m_cResolution.GetItemData(m_cResolution.GetCurSel());
        }
        else
        {
            MessageBox(ConvertString("Resolution error!"), ConvertString("Prompt"));
            return ;
        }

        int nPlayFileType = m_cPlayType.GetCurSel();

        //Playback
        //To get play mode
        nIndex = m_cMultyPlayMode.GetCurSel();
        memset(&((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam, 0, sizeof(NET_MULTI_PLAYBACK_PARAM));

        // 待转码的通道
        ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannelNum = nChannelCount;
        if (1 == nChannelCount && NULL != m_pOneChannelDlg)
        {
            m_pOneChannelDlg->GetOneChannelModeNumber(((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannels[0]);
        }
        else if (4 == nChannelCount && NULL != m_pFourChannelsDlg)
        {
            m_pFourChannelsDlg->GetFourChannelsNumber(
                ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannels[0],
                ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannels[1],
                ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannels[2],
                ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannels[3]);
        }
        else
        {
            for (int j = 0; j < (((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannelNum); ++j)
            {
                ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannels[j] = j;
            }
        }

        for (int i = 0; i < nChannelCount; ++i)
        {
            //Search
            DWORD dwFindHandle = CLIENT_FindFile(m_hLoginID, ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannels[i], nPlayFileType, NULL, &netTimeFrom, &netTimeTo, FALSE, 2000);
            if (dwFindHandle != 0)
            {
                int nRet = 1;

                nRet = CLIENT_FindNextFile(dwFindHandle, &m_netFileInfo[0]);
                if (nRet <= 0)
                {
                    MessageBox(ConvertString("No RecordFile!"), ConvertString("Prompt"));
                    return ;
                }

                CLIENT_FindClose(dwFindHandle);
            }
            
            if (0 == i)
            {
                sEerlistStartTime = m_netFileInfo[0].starttime;
                nBaseChannel = ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannels[i];
            }
            else
            {
                if (Compare(&sEerlistStartTime, &(m_netFileInfo[0].starttime)) > 0)
                {
                    sEerlistStartTime = m_netFileInfo[0].starttime;
                    nBaseChannel = ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nChannels[i];
                }
            }
        }

        DWORD dwFindHandle = CLIENT_FindFile(m_hLoginID, nBaseChannel, nPlayFileType, NULL, &netTimeFrom, &netTimeTo, FALSE, 2000);
        nFileCount = 0;
        if (dwFindHandle != 0)
        {
            int nRet = 1;
            while(nRet > 0)
            {
                nRet = CLIENT_FindNextFile(dwFindHandle, &m_netFileInfo[nFileCount]);
                if (nRet > 0)
                {
                    if (nFileCount >= 2000)
                    {
                        MessageBox(ConvertString("Too many recordfiles!"), ConvertString("Prompt"));
                        return;
                    }
                    nFileCount++;
                }
            }
            CLIENT_FindClose(dwFindHandle);
        }

        if (nFileCount > 0)
        {
            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeStart.dwYear = m_netFileInfo[0].starttime.dwYear;
            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeStart.dwMonth = m_netFileInfo[0].starttime.dwMonth;
            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeStart.dwDay = m_netFileInfo[0].starttime.dwDay;
            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeStart.dwHour = 0;
            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeStart.dwMinute = 0;
			((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeStart.dwSecond = 0;

            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeEnd.dwYear = m_netFileInfo[0].starttime.dwYear;
            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeEnd.dwMonth = m_netFileInfo[0].starttime.dwYear;
            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeEnd.dwDay = m_netFileInfo[0].starttime.dwYear;
            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeEnd.dwHour = 23;
            ((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeEnd.dwMinute = 59;
			((CClientDemo3Dlg *)AfxGetMainWnd())->m_PlayBackByTimeEnd.dwSecond = 59;

            ((CClientDemo3Dlg *)AfxGetMainWnd())->AddTimeToDateTimeCtl_Multy(m_netFileInfo, nFileCount);
        }

        
        ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.dwSize = sizeof(NET_MULTI_PLAYBACK_PARAM);
        
        // 二次压缩开始时间以及结束时间
        memcpy(&(((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.stStartTime), &netTimeFrom, sizeof(NET_TIME));
        memcpy(&(((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.stEndTime), &netTimeTo, sizeof(NET_TIME));
        // 分辨率，"D1"、"HD1"、"2CIF"、"CIF"、"QCIF" 
        char *rsName[33] = {"D1", "HD1", "BCIF", "CIF", "QCIF", "VGA", "QVGA", "SVCD", "QQVGA", 
            "SVGA", "XVGA", "WXGA", "SXGA", "WSXGA", "UXGA", "WUXGA", "LFT", "720", "1080", "1_3M", 
            "2M","5M","3M","5_0M","1_2M", "1408_1024", "8M", "2560_1920", "960H", "960_720"
            ,"NHD" , "QNHD", "QQNHD"};
        strcpy(((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.szResolution, rsName[nResolution]);
        // 回放文件类型，0：普通录象；1：报警录象；2：移动检测；3：卡号录象；4：图片
        ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nType = nPlayFileType;
        // 帧率,1~25
        ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nFPS = m_nFps;
        // 码流值，范围192~1024
        ((CClientDemo3Dlg *)AfxGetMainWnd())->m_MultyPlayBackParam.nBitRate = m_nBitRate;
        //UpdateData(TRUE);
        if(CB_ERR != nIndex)
        {
            PlayBackMode ePlayMode = (PlayBackMode)m_cMultyPlayMode.GetItemData(nIndex);
            if(ePlayMode == EM_SERVERMODE)
            {
                ((CClientDemo3Dlg *)AfxGetMainWnd())->PlayBackMultyServerMode();
            }
            else
            {
                ((CClientDemo3Dlg *)AfxGetMainWnd())->PlayBackMulty();
            }
        }
	}
}

void CPlaybackMulty::SetControlButton(BOOL bFlag)
{
    GetDlgItem(IDC_COMBO_CHANNEL)->EnableWindow(bFlag);
    GetDlgItem(IDC_EDIT_BITRATE)->EnableWindow(bFlag);
    GetDlgItem(IDC_EDIT_FPS)->EnableWindow(bFlag);
    GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(bFlag);
    GetDlgItem(IDC_COMBO_MULTYPLAYMODE)->EnableWindow(bFlag);
    GetDlgItem(IDC_COMBO_PLAYTYPE)->EnableWindow(bFlag);
    GetDlgItem(IDC_DATE_FROM)->EnableWindow(bFlag);
    GetDlgItem(IDC_TIME_FROM)->EnableWindow(bFlag);
    GetDlgItem(IDC_DATE_TO)->EnableWindow(bFlag);
    GetDlgItem(IDC_TIME_TO)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_CHANNELS_CHOOSE)->EnableWindow(bFlag);
    GetDlgItem(IDC_COMBO_STREAMTYPE)->EnableWindow(bFlag);
}

bool CPlaybackMulty::EnableComboBox(int nChannel)
{
    if (true == m_bEnableComboBoxFlag)
    {
        return true;
    }

    if (m_hLoginID <= 0)
    {
        return false;
    }
/*
    if (m_hLoginID <= 0)
    {
        MessageBox(ConvertString("please login first!"), ConvertString("Prompt"));
        return;
    }
*/
    if (nChannel < 0)
    {
        return false;
    }

    m_nTotalChannel = nChannel;
    int nIndex = 0;
    int i = 0;
    CString str;
    int nRet = 0;
    NET_MULTIPLAYBACK_SPLIT_CAP stuMultyParam = {sizeof(NET_MULTIPLAYBACK_SPLIT_CAP)};
    if (TRUE == CLIENT_QueryDevState(m_hLoginID, DH_DEVSTATE_MULTIPLAYBACK_SPLIT_CAP, (char *)&stuMultyParam, sizeof(stuMultyParam), &nRet))
    {
        m_cChannel.ResetContent();
        int nRealCount = __min(stuMultyParam.nModeNumber, DH_MAX_MULTIPLAYBACK_SPLIT_NUM);
        for(i=0; i<nRealCount; i++)
        {
            str.Format("%d", stuMultyParam.nSliptMode[i]);
            
            nIndex = m_cChannel.AddString(str);
            m_cChannel.SetItemData(nIndex,stuMultyParam.nSliptMode[i]);
        }

        if (m_cChannel.GetCount() > 0)
        {
            m_cChannel.SetCurSel(0);
        }
        else
        {
            MessageBox(ConvertString("Get zero multiplayback type!"), ConvertString("Prompt"));
            DisableComboBox();
            return false;
        }
    }
    else
    {
        if (0 != m_hLoginID)
        {
            MessageBox(ConvertString("Get multiplayback type fail!"), ConvertString("Prompt"));
            DisableComboBox();
            return false;
        }
    }

    DHDEV_DSP_ENCODECAP stuDSPParam = {0};
    if (TRUE == CLIENT_QueryDevState(m_hLoginID, DH_DEVSTATE_DSP, (char *)&stuDSPParam, sizeof(stuDSPParam), &nRet))
    {
        m_cResolution.ResetContent();
        char *rsName[33] = {"D1", "HD1", "BCIF", "CIF", "QCIF", "VGA", "QVGA", "SVCD", "QQVGA", 
            "SVGA", "XVGA", "WXGA", "SXGA", "WSXGA", "UXGA", "WUXGA", "LFT", "720", "1080", "1_3M", 
            "2M","5M","3M","5_0M","1_2M", "1408_1024", "8M", "2560_1920", "960H", "960_720"
            ,"NHD" , "QNHD", "QQNHD"};
        int i = 0;
        
        int test = m_cResolution.GetCurSel();

        for (i = 0; i < 32; i++)
        {
            if (stuDSPParam.dwImageSizeMask & (0x01<<i))
            {
                int nIndex = m_cResolution.AddString(rsName[i]);
                m_cResolution.SetItemData(nIndex,i);
            }
 	    }
        if (m_cResolution.GetCount() > 0)
        {
            m_cResolution.SetCurSel(0);
        }
        else
        {
            //在获取分辨率失败时，默认支持不大于D1的分辨率，针对NVR 5X系列修改
            int nIndex = m_cResolution.AddString(ConvertString("D1"));
            m_cResolution.SetItemData(nIndex,EM_D1);
            nIndex = m_cResolution.AddString(ConvertString("HD1"));
            m_cResolution.SetItemData(nIndex,EM_HD1);            
            nIndex = m_cResolution.AddString(ConvertString("2CIF"));
            m_cResolution.SetItemData(nIndex,EM_2CIF);            
            nIndex = m_cResolution.AddString(ConvertString("CIF"));
            m_cResolution.SetItemData(nIndex,EM_CIF);            
            nIndex = m_cResolution.AddString(ConvertString("QCIF"));
            m_cResolution.SetItemData(nIndex,EM_QCIF);

            m_cResolution.SetCurSel(0);
        }
    }
    else
    {
        if(0 != m_hLoginID)
        {
            MessageBox(ConvertString("Get Resolution type fail!"), ConvertString("Prompt"));
            DisableComboBox();
            return false;
        }
    }

    m_cPlayType.ResetContent();
    nIndex = m_cPlayType.AddString(ConvertString("All"));
    m_cPlayType.SetItemData(nIndex,EM_MULTY_LISTALL);
    nIndex = m_cPlayType.AddString(ConvertString("Alarm"));
    m_cPlayType.SetItemData(nIndex,EM_MULTY_ALARMALL);
    m_cPlayType.SetCurSel(EM_MULTY_LISTALL);

    m_cMultyPlayMode.ResetContent();
    nIndex = m_cMultyPlayMode.AddString( ConvertString("direct"));
    m_cMultyPlayMode.SetItemData(nIndex,EM_DIRECTMODE);
    nIndex = m_cMultyPlayMode.AddString(ConvertString("callback"));
    m_cMultyPlayMode.SetItemData(nIndex,EM_SERVERMODE);
    m_cMultyPlayMode.SetCurSel(EM_DIRECTMODE);

    m_cStreamType.ResetContent();
    nIndex = m_cStreamType.AddString(ConvertString("AllStream"));
    m_cStreamType.SetItemData(nIndex,EM_BOTH_STREAM);
    nIndex = m_cStreamType.AddString(ConvertString("MainStream"));
    m_cStreamType.SetItemData(nIndex,EM_MAIN_STREAM);
    nIndex = m_cStreamType.AddString(ConvertString("ExtraStrean"));
    m_cStreamType.SetItemData(nIndex,EM_EXTRA_STREAM);
	m_cStreamType.SetCurSel(EM_BOTH_STREAM);

    if (NULL == m_pOneChannelDlg)
    {
        m_pOneChannelDlg = new CChannelOneDialog(this, m_nTotalChannel);
        if (NULL == m_pOneChannelDlg)
        {
            MessageBox(ConvertString("System error!"), ConvertString("Prompt"));
            DisableComboBox();
            return false;
        }
    }

    if (NULL == m_pFourChannelsDlg)
    {
        m_pFourChannelsDlg = new CFourChannelsDialog(this, m_nTotalChannel);
        if (NULL == m_pFourChannelsDlg)
        {
            MessageBox(ConvertString("System error!"), ConvertString("Prompt"));
            DisableComboBox();
            return false;
        }
    }

    //Set current time
    CTimeSpan timeSpan(1,0,0,0);
    CTime curTime = CTime::GetCurrentTime();
    CTime dateFrom = curTime - timeSpan;
    CTime dateLoadFrom = curTime - timeSpan;
    m_DateFrom.SetDateTime(dateLoadFrom.GetYear(), dateLoadFrom.GetMonth(), dateLoadFrom.GetDay(), 
        dateLoadFrom.GetHour(), dateLoadFrom.GetMinute(), dateLoadFrom.GetSecond());
    m_TimeFrom = curTime;
    m_DateTo.SetDateTime(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), 
        curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
    m_TimeTo = curTime;

    UpdateData(FALSE);

    SetControlButton(TRUE);

    m_bEnableComboBoxFlag = true;
    return true;
}

bool CPlaybackMulty::DisableComboBox()
{
    SetControlButton(FALSE);
    m_nTotalChannel = 0;
    m_cChannel.ResetContent();
    m_cResolution.ResetContent();
    m_cPlayType.ResetContent();
    m_cMultyPlayMode.ResetContent();

    if (NULL != m_pOneChannelDlg)
    {
        delete m_pOneChannelDlg;
        m_pOneChannelDlg = NULL;
    }
    
    if (NULL != m_pFourChannelsDlg)
    {
        delete m_pFourChannelsDlg;
        m_pFourChannelsDlg = NULL;
    }

    UpdateData(FALSE);
    m_bEnableComboBoxFlag = false;
    return true;
}

BOOL CPlaybackMulty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    g_SetWndStaticText(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPlaybackMulty::OnButtonChannelsChoose() 
{
	// TODO: Add your control notification handler code here
	if (m_hLoginID > 0)
    {
        int nIndex = m_cChannel.GetCurSel();
        int nChannelCount = m_cChannel.GetItemData(nIndex);
        if (1 == nChannelCount)
        {
            if (NULL != m_pOneChannelDlg)
            {
                m_pOneChannelDlg->DoModal();
            }
        }
        else if (2 == nChannelCount)
        {
            
        }
        else if (4 == nChannelCount)
        {
            if (NULL != m_pFourChannelsDlg)
            {
                m_pFourChannelsDlg->DoModal();
            }
        }
    }
    else
    {
        return;
    }
}
