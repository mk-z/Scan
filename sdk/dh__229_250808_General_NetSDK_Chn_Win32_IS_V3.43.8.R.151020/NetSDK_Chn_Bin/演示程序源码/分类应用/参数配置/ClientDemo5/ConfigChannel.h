#if !defined(AFX_CONFIGCHANNEL_H__C733B16C_7D41_4D06_9A93_5BE9F7970907__INCLUDED_)
#define AFX_CONFIGCHANNEL_H__C733B16C_7D41_4D06_9A93_5BE9F7970907__INCLUDED_

#include "dhnetsdk.h"
#include "Common.h"
#include "ComConstants.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigChannel.h : header file
//

// const char* const ecName[10] = {"MPEG4", "MS-MPEG4", "MPEG2", "MPEG1", "H.263", "MJPG", "FCC-MPEG4", "H.264", "H.265", "SVAC"};
const char* const ecName[9] = {"MPEG4", "MS-MPEG4", "MPEG2", "MPEG1", "H.263", "MJPG", "FCC-MPEG4", "H.264", "H.265"};

const size_t encodeCount = sizeof(ecName)/sizeof(ecName[0]);
const char* const profileName[] = {"H.264 B", "H.264  ", "H.264 E", "H.264 H"}; // TODO "H.264  " SelectString模糊搜索
const size_t profileCount = sizeof(profileName)/sizeof(profileName[0]);

/////////////////////////////////////////////////////////////////////////////
// CConfigChannel dialog

class CConfigChannel : public CDialog
{
// Construction
public:
	DWORD GetFramePerSec(WORD wFramePerSec);
	DWORD GetFenbianLv(WORD wImageSize);

	DWORD GetFenbianLvEx(CAPTURE_SIZE emType);
	int Round_x(int value, int divisor);

	BOOL IsValidForInput();
	void CleanAll();
	//Initialize dialogue box
	void InitDlgInfo(int nChannelCount, int nVideoStandard, int nProtoVer, BOOL bNewProtocol);
	void OnInitCtrl(int nProtoVer, int nVideoStandard, int nChannelCount);
	void InitListView();
	void InsertListView(CString strIndex,CString strBright,CString strContrast,CString strSaturation, CString strChroma, CString strPlus, 
		CString strStartHour, CString strStartMinute, CString strStartSecond,
		CString strEndHour,CString strEndMinute,CString strEndSecond, BOOL bMask);

	void ShowChannelVideoColor(AV_CFG_ChannelVideoColor *pstChannelVideoColor);
	BOOL GetVideoColorInfo(CString &strIndex,CString &strBrightness,CString &strContrast,CString &strSaturation, CString &strChroma, CString &strPlus, 
		CString &strStartHour, CString &strStartMinute, CString &strStartSecond,
		CString &strEndHour,CString &strEndMinute,CString &strEndSecond, BOOL &bMask);
    CFG_ENCODECAP* GetEncodeCap();
	CConfigChannel(CWnd* pParent = NULL);   // standard constructor
    BOOL m_bShowFpsRange; // 是否显示码流范围(兼容性)
// Dialog Data
	//{{AFX_DATA(CConfigChannel)
	enum { IDD = IDD_CONFIG_CHANNEL };
	CListCtrl	m_ctlVideoColorLst;
	CComboBox	m_ctlBlindType;
	CButton	m_ctlOSDShow;
	CComboBox	m_ctlOSD;
	CComboBox	m_ctlAudioFmt;
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
	CComboBox   m_ctlLimitStream;
	UINT	m_nBrightness;
	UINT	m_nContrast;
	UINT	m_nSaturation;
	UINT	m_nHue;
	UINT	m_nGain;
	BOOL	m_bAudioOverlay;
	int		m_nNoise;
	int		m_nVolume;
	BOOL	m_bVolumeEn;
	BOOL	m_bMask;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigChannel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigChannel)
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	afx_msg void OnSelchangeComboChanno();
	afx_msg void OnSelchangeComboStream();
	afx_msg void OnSelchangeComboOsd();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonModify();
	afx_msg void OnItemchangedListVideocolor(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboFrame();
	afx_msg void OnSelchangeComboResolution();
	afx_msg void OnSelchangeComboLimitstream();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SaveOSDInfo(int nNum,int nItem);
	int m_nCurOSD;
	int m_nCurStream;
	int m_nCurChannel;
	void SaveStreamInfo(int nNum,int nItem);
	BYTE m_nVideoStandard;
	DHDEV_DSP_ENCODECAP m_stDspInfo;
	void ShowStreamInfo(int nNum,int nItem);
	void SaveChannelInfo(int nNum);
	int m_nChannelCount;
	DHDEV_CHANNEL_CFG* m_pChannelInfo;
	CFG_ENCODE_INFO	*m_stEncodeInfo;
	AV_CFG_VideoWidget *m_pstVideoWidget;

	void SaveVideoColorInfo(int nNum);
	AV_CFG_ChannelVideoColor  *m_pstChannelVideoColor;
	AV_CFG_ChannelName *m_pstChannelName;
    
    CFG_ENCODECAP	m_EncodeCaps;  // 编码能力集
	RESOLUTION m_stPALSlu[CAPTURE_SIZE_NR];    // PAL制式分辨率信息
	RESOLUTION m_stNTSCSlu[CAPTURE_SIZE_NR];   // NTSC制式分配率信息
    VOID InitResolution();
	// 获取最大、最小限码流
    int GetImageBitRate(int imageSize, int frames, int &minBitRate, int&maxBitRate, int Iframes = 50);
	// 显示限码流范围，填充m_ctlLimitStream
    VOID ShowFpsRange();
	// 设置限码流值，包括m_ctlLimitStream的选项
	void SetFpsValue(int iFpsValue);
    int m_iMinFps;  // 最小限码流,根据GetImageBitRate计算获得
	int m_iMaxFps;  // 最大限码流,根据GetImageBitRate计算获得
    
	int m_nProtoVer;
	BOOL m_bNewProtocol;
	BOOL m_bShowPix;//  表示是否有扩展的分辨率
	CFG_DSPENCODECAP_INFO m_stDspInfoEx;// 用于表示新的分辨率
	NET_OUT_ENCODE_CFG_CAPS m_stEncodeCaps; // 最新的能力结构，目前只用到其中的h264 profile，如果有其他需要，可能需要扩展为通道个数的数组
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCHANNEL_H__C733B16C_7D41_4D06_9A93_5BE9F7970907__INCLUDED_)
