#if !defined(AFX_CONFIGCHANNELEX_H_INCLUDED_)
#define AFX_CONFIGCHANNELEX_H_INCLUDED_

#include "dhnetsdk.h"
#include "Common.h"
#include "ComConstants.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigChannel.h : header file
//

static const char* szResolutionNames[] = {
    "NHD",  "VGA",  "QVGA", "SVCD", "QQVGA",
    "SVGA", "SVGA1","WVGA", "FWVGA","DVGA",
    "XVGA","WXGA","WXGA2","WXGA3","WXGA4",
    "SXGA","SXGA+","WSXGA","UXGA","WUXGA",
    "ND1","720P","1080P","QFHD","1_3M",
    "1280x960","2_5M", "1872x1408","5M", "3744x1408",
    "3M", "2048x1536","5_0M", "2432x2048","1_2M",
    "1216x1024","1408x1024","3296x2472","5_1M", "2560x1920",
    "DV720P"
};
static const size_t resolutionNameCount = sizeof(szResolutionNames)/sizeof(szResolutionNames[0]);

static const char* szStantardResolutionNames[] = {
    "D1", "HD1", "BCIF", "CIF", "QCIF", "960H"
};
static const size_t stdRstNameCount = sizeof(szStantardResolutionNames)/sizeof(szStantardResolutionNames[0]);

static const DH_RESOLUTION_INFO stuResolutions[resolutionNameCount] = {
    {640, 360}, {640, 480}, {320, 240}, {480, 480},{160, 128},
    {800, 592}, {800, 600}, {800, 480}, {854, 480}, {960, 640},
    {1024, 768}, {1280, 800}, {1280, 768},{1280, 854}, {1366, 768},
    {1280, 1024}, {1400, 1050}, {1600, 1024}, {1600, 1200}, {1920, 1200}, 
    {240, 192}, {1280, 720}, {1920, 1080},{3840, 2160}, {1280, 960}, 
    {1280, 960}, {1872, 1408}, {1872, 1408}, {3744, 1408}, {3744, 1408}, 
    {2048, 1536}, {2048, 1536}, {2432, 2048}, {2432, 2048}, {1216, 1024}, 
    {1216, 1024}, {1408, 1024}, {3296, 2472}, {2560, 1920}, {2560, 1920}, 
    {960, 720}
};

static const DH_RESOLUTION_INFO stuStantardResolutions[2][stdRstNameCount] = {	
    {{704, 576}, {352, 576}, {704, 288}, {352, 288}, {176, 144}, {960, 576}},
    {{704, 480}, {352, 480}, {704, 240}, {352, 240}, {176, 120}, {960, 480}}
};


/////////////////////////////////////////////////////////////////////////////
// CConfigChannelEx dialog

class CConfigChannelEx : public CDialog
{
// Construction
public:

    BOOL Attach(UINT uID, CDialog* pAttachDlg);
	void CleanAll();
	//Initialize dialogue box
	void InitDlgInfo(int nChannelCount, int nVideoStandard);
	void OnInitCtrl(int nStreamIndex, BOOL bEncodeModeFlag = FALSE);
    void OnInitFpsRange();
	CConfigChannelEx(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CConfigChannelEx)
	enum { IDD = IDD_CONFIG_CHANNEL_EX };
	CComboBox	m_ctlImageQuality;
	CComboBox	m_ctlFrame;
	CComboBox	m_ctlBRCtl;
	CButton	m_ctlGain;
	CButton	m_ctlAudio;
	CButton	m_ctlVideo;
	CComboBox	m_ctlStream;
	CComboBox	m_ctlResolution;
	CComboBox	m_ctlEncodeType;
	CComboBox	m_ctlChannel;
	BOOL	m_bAudioOverlay;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigChannelEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigChannelEx)
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	afx_msg void OnSelchangeComboChanno();
	afx_msg void OnSelchangeComboStream();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnSelchangeComboResolution();
	afx_msg void OnSelchangeComboLimitstream();
	afx_msg void OnEditchangeComboEncodetype();
	afx_msg void OnSelchangeComboEncodetype();
	afx_msg void OnSelchangeComboFrame();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nCurStream;    // 记录下拉框当前码流类型
	int m_nCurChannel;
	void SaveStreamInfo(int nNum,int nItem);
    BOOL ParseVideoResolutionType(std::string resolutionType, int& nWidth, int& nHight);
    std::string PacketVideoResolutionType(int nWidth, int nHight);
    void RefreshCaps();
    void RefreshFrame();
	BYTE m_nVideoStandard;
	void ShowStreamInfo(int nNum,int nItem);
	void SaveChannelInfo(int nNum);
	int m_nChannelCount;
	DHDEV_CHANNEL_CFG* m_pChannelInfo;
	CFG_ENCODE_INFO	*m_stEncodeInfo;
    
    int m_iMinFps;  // 最小限码流
	int m_iMaxFps;  // 最大限码流
	BOOL m_bShowPix;//  表示是否有扩展的分辨率
	CFG_DSPENCODECAP_INFO m_stDspInfoEx;// 用于表示新的分辨率
	NET_OUT_ENCODE_CFG_CAPS m_stEncodeCaps; // 最新的能力结构，目前只用到其中的h264 profile，如果有其他需要，可能需要扩展为通道个数的数组
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCHANNELEX_H_INCLUDED_)
