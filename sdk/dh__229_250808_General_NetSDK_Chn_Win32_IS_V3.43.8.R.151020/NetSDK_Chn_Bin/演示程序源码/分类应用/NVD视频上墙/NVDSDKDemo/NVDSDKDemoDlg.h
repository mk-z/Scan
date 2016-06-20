// NVDSDKDemoDlg.h : header file
//

#if !defined(AFX_NVDSDKDEMODLG_H__A3B225A4_4649_454A_9DD7_AFB62CC3A40B__INCLUDED_)
#define AFX_NVDSDKDEMODLG_H__A3B225A4_4649_454A_9DD7_AFB62CC3A40B__INCLUDED_

#include "./include/VideoWindow.h"	// Added by ClassView
#include <list>
#include "ReadWriteMutex.h"
using namespace Tools;
#include "dhnetsdk.h"
#include "PannelDecoder.h"	// Added by ClassView
#include "PannelEncoder.h"	// Added by ClassView
#include "PlayBackProcess.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

// device information
typedef struct __DEVICE_INFO
{
	CString		strDevName;
	CString		strDevUser;
	CString		strDevPwd;
	CString		strDevIp;
	LONG		nDevPort;
	LLONG		lLoginID;
	int			nDevChannel;
	BOOL		bIsOnline;
	int         nStreamType;
} DEVICE_INFO;

#define NVD_ENCODER_MAX	16

// nvd information
typedef struct __DECODER_INFO
{
	DEV_DECODER_INFO devDecInfo;
	CString		strDecName;
	CString		strDecUser;
	CString		strDecPwd;
	CString		strDecIp;
	LONG		nDecPort;
	LLONG		lLoginID;
	int			nDecChannel;
	BOOL		bIsOnline;
	DWORD		dwTotalSize[NVD_ENCODER_MAX];
	DWORD		dwCurSize[NVD_ENCODER_MAX];
} DECODER_INFO;

// screen information
typedef struct __SHOW_WINDOW_INFO 
{
	LLONG		lDecLoginID;
	int			nEncoderNum;
	int			nPlayType;	// 0£ºrealplay£»1£ºplayback by file£»2£ºplayback by time
} SHOW_WINDOW_INFO;

typedef struct __CTRL_TV_PARAM 
{
	int			nMonitorID;
	int			nWndID;
	int			nSplitType;
} CTRL_TV_PARAM;

typedef struct __SWITCH_TV_PARAM 
{
	int			nMonitorID;
	int			nWndID;
	LLONG		lDecLoginID;
	int			nEncoderNum;
	int			nPlayType;
} SWITCH_TV_PARAM;

typedef struct __COMBIN_TV_PARAM 
{
	int			nMonitorID;
	int			nSplitType;
	BYTE		*pEncoderChannel;
	int			nBufLen;
} COMBIN_TV_PARAM;


//////////////////////////////////////////////////////////////////////////
void CALLBACK MessDataCallBackFunc(LLONG lCommand, LPNET_CALLBACK_DATA lpData, LDWORD dwUser);
void CALLBACK DecPlayBackPosFunc(LLONG lLoginID, int nEncoderID, DWORD dwTotalSize, DWORD dwPlaySize, LDWORD dwUser);

class CNVDSDKDemoDlg : public CDialog
{
// Construction
public:
	CNVDSDKDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Operations
public:
	void OnVideoLButtonDblClk(int nMonitorID, int nWndID, BOOL bMultiScreen, int nSplitNum);
	void DevHaveReconnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort);
	void DevDisConnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort);
	void UpdateDeviceList();
	void UpdateDecoderList();
	void MessDataCallBack(LONG lCommand, LPNET_CALLBACK_DATA lpData);
	void DecPlayBackPosCallback(LLONG lLoginID, int nEncoderID, DWORD dwTotalSize, DWORD dwPlaySize, LDWORD dwUser);

    DEVICE_INFO* GetSelectEncoderDeviceInfo();

// Dialog Data
	//{{AFX_DATA(CNVDSDKDemoDlg)
	enum { IDD = IDD_NVDSDKDEMO_DIALOG };
	CTreeCtrl	m_encoderTree;
	CTreeCtrl	m_decoderTree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNVDSDKDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNVDSDKDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDblclkTreeEncoder(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkTreeDecoder(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
	LRESULT OnRebootDevice(WPARAM wParam, LPARAM lParam);

private:
	void InitSDK();
	void InitControl();
	void UpdatePannelPosition();
	
public:
	int GetChannelState(int nEncoderID, DEV_DECCHANNEL_STATE *pChannelState);
	int GetCurWndPlaybackPos();
	void PlaybackSeek(int nOffsetPos);
	CPlayBackProcess m_dlgProcess;
	std::list<DEVICE_INFO*> m_lstDevices;
	CReadWriteMutex m_csDevice;
	std::list<DECODER_INFO*> m_lstDecoders;
	CReadWriteMutex m_csDecoder;

	BOOL m_bUpdataTree1;
	BOOL m_bUpdataTree2;
	CVideoWindow m_screenPannel;
	SHOW_WINDOW_INFO m_stuShowWindow[SPLIT16][SPLIT16];

private:
	CPannelEncoder m_pannelEncoder;
	CPannelDecoder m_pannelDecoder;
	CRect m_clientRect;

	int m_nTimerID1;
	int m_nTimerID2;

	HICON m_hIcon;
	HTREEITEM m_hDecNode;
	HTREEITEM m_hDevNode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NVDSDKDEMODLG_H__A3B225A4_4649_454A_9DD7_AFB62CC3A40B__INCLUDED_)
