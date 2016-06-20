// ClientDemo3Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "daytimepicksdk.h"
//}}AFX_INCLUDES

#if !defined(AFX_CLIENTDEMO3DLG_H__5F0C6987_3711_4A4D_8240_CEEC190FD725__INCLUDED_)
#define AFX_CLIENTDEMO3DLG_H__5F0C6987_3711_4A4D_8240_CEEC190FD725__INCLUDED_

#include "dhnetsdk.h"
#include "PlaybackByFile.h"	// Added by ClassView
#include "PlaybackByTime.h"	// Added by ClassView
#include "PlaybackMulty.h"  // Added by ClassView
#include "ExSliderCtrl.h"
#include <AFXMT.H>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDemo3Dlg dialog
//Playback mode 
enum PlayBackType{
	EM_FILEBACK,
	EM_TIMEBACK,
    EM_MULTYBACK,
};

// Playback Direction
typedef enum tagEM_PLAYBACK_DIRECTION
{
    EM_PLAYBACK_DIRECTION_FORWARD,
    EM_PLAYBACK_DIRECTION_REVERSE,
}EM_PLAYBACK_DIRECTION;

// 播放速度
enum PlaySpeed
{
    SPEED_MIN,					// 最小速度
    SPEED_DOWN_25 = SPEED_MIN,	// 减速到1/25
    SPEED_DOWN_16, 
    SPEED_DOWN_8, 
    SPEED_DOWN_4, 
    SPEED_DOWN_2, 
    SPEED_NORMAL,				// 正常速度
    SPEED_UP_2, 
    SPEED_UP_4, 
    SPEED_UP_8, 
    SPEED_UP_16, 
    SPEED_UP_25,				// 加速到25倍 
    SPEED_MAX = SPEED_UP_25,	// 最大速度
};

class CClientDemo3Dlg : public CDialog
{
// Construction
public:
	//Download by time
	BOOL DownLoadByTime(int nChannelId, LPNET_TIME tmStart, LPNET_TIME tmEnd, BOOL bLoad);
	//Playback by time
    //void PlayBackByTime(int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime);
	void PlayBackByTime(int nChannelID);
    //PlayBackMultyServerMode
    void PlayBackMultyServerMode();
    //Playback Multy
    void PlayBackMulty();
    //Download by file
	BOOL DownLoadByFile(NET_RECORDFILE_INFO fileInfo,BOOL bLoad);
	//Playback by file
	void PlayBackByFile(NET_RECORDFILE_INFO fileInfo, int nChannelId);
	//Interface to callback 
	void DeviceDisConnect(LONG lLoginID, char *sDVRIP,LONG nDVRPort);
	void ReceivePlayPos(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize);
	void TimeDownLoadCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo,DWORD dwUser);
	//Callback function when device disconnected.
	friend void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
	//Process status callback 
	friend void CALLBACK PlayCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);
	//Download callback in time mode
	friend void CALLBACK TimeDownLoadPos(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, DWORD dwUser);
	//Data callback
	friend int CALLBACK DataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);
	
	int ReceiveRealData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize);
    //void PlayBackByTimeServerMode(int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime);
	void PlayBackByTimeServerMode(int nChannelID);
	void PlayBackByFileServerMode(NET_RECORDFILE_INFO fileInfo, int nChannelID);
	void ExSliderButtonUp();
	void ExSliderButtonDown();

	void AddTimeToDateTimeCtl(NET_RECORDFILE_INFO fileInfo[2000], int nFileCount);
    void AddTimeToDateTimeCtl_Multy(NET_RECORDFILE_INFO fileInfo[2000], int nFileCount);

	void StopPlay();

	void InitTimeOcx(NET_RECORDFILE_INFO & fileInfo);
    LLONG PlayBackByTimeEx2(int nChannel, NET_IN_PLAY_BACK_BY_TIME_INFO *pstIn, NET_OUT_PLAY_BACK_BY_TIME_INFO*pstOut);

	long m_pDownLoadFile;
	long m_pDownLoadByTime;
	long m_pCurrentTime;
	NET_TIME m_PlayBackByTimeStart;
	NET_TIME m_PlayBackByTimeEnd;
    NET_MULTI_PLAYBACK_PARAM m_MultyPlayBackParam;
	BOOL m_bPlayBackByTimeMode;

	CClientDemo3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDemo3Dlg)
	enum { IDD = IDD_CLIENTDEMO3_DIALOG };
	CExSliderCtrl	m_ctlPlayBack;
	CTabCtrl	m_Tab;
	CIPAddressCtrl	m_ctlDvrIP;
	CString	m_strUserName;
	CString	m_strPwd;
	UINT	m_nPort;
//	CDayTimePick	m_DayTimePick;
	CDayTimePickSDK	m_DayTimePickSdk;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDemo3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLogout();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonStop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnReleasedcaptureSliderPlayposition(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonSlow();
	afx_msg void OnButtonFast();
	afx_msg void OnButtonFrameto();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonNormalspeed();
	afx_msg LRESULT OnSuccess(WPARAM w, LPARAM l);
	afx_msg void OnOnTimeClickDaytimepicksdkctrl1(long nHour, long nMinute, long nSecond);
	afx_msg void OnButtonCapturePicture();
	afx_msg void OnButtonPlayreverse();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	DWORD m_StartTime;
	//int		m_nPlayChannelNum;
private:
    void SetPlayControlButton(BOOL bFlag);
	void ClosePlayBack();
	PlayBackMode m_ePlayMode;
	CTime ConvertNetTimeToCTime(LPNET_TIME lpNetTime);
	PlayBackType m_PlayBackType;
    EM_PLAYBACK_DIRECTION m_PlayBackDirection;
	void LastError();
	UINT m_nTimer;
	DWORD m_dwCurValue;
	DWORD m_TotalTime;
	DWORD m_dwTotalSize;
	long m_hPlayBack;
	int m_nChannelCount;
	INT m_nChannelID;
	BOOL m_bSpeedCtrl;
	void SetDlgState(CWnd *pWnd, BOOL bShow);
	void DoTab(int nTab);
	CPlaybackByTime *m_pTabTimeDlg;
	CPlaybackByFile *m_pTabFileDlg;
    CPlaybackMulty *m_pTabMultyDlg;
	void InitTabControl();
	void ShowLoginErrorReason(int nError);
	CString GetDvrIP();
	long m_LoginID;
	void InitNetSDK();
    void ChangeSpeedStatus( int nMode );
    long GetUTCTimebyNetTime(const NET_TIME& stTime);
    BOOL PlayBackByDirection(EM_PLAYBACK_DIRECTION emDirection);
    PlaySpeed	m_eSpeed;
    int m_nReverseMode;
//	CCriticalSection m_cs;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO3DLG_H__5F0C6987_3711_4A4D_8240_CEEC190FD725__INCLUDED_)
