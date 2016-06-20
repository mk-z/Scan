// ClientDemoDlg.h : header file
//

#if !defined(AFX_CLIENTDEMODLG_H__475AE43D_B618_4F15_9DE9_2628AA826F52__INCLUDED_)
#define AFX_CLIENTDEMODLG_H__475AE43D_B618_4F15_9DE9_2628AA826F52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dhnetsdk.h"
#include "VideoNodeInfo.h"
#include "ExButton.h"
#include "ptzScreen.h"
#include <afxmt.h>
/////////////////////////////////////////////////////////////////////////////
// CClientDemoDlg dialog

class CClientDemoDlg : public CDialog
{
// Construction
public:
	
	//PTZ extensive control function 
	void PtzExtControl(DWORD dwCommand, DWORD dwParam = 0);
	//PTZ control function 
	void PtzControl(int type, BOOL stop);
	//Log in handle 
	long m_LoginID;
	//Display function execution error reason.
	void LastError();
	//The callback interface
	void DeviceDisConnect(LONG lLoginID, char *sDVRIP,LONG nDVRPort);
	//To get real-time data
	void ReceiveRealData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize);
	//Callback function when device disconnected
	friend void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
	//Callback monitor data and then save
	friend void CALLBACK RealDataCallBackEx(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, 
		DWORD dwBufSize, LONG lParam, DWORD dwUser);
	
	friend void CALLBACK  MessageProcFunc(int nWndID, UINT message, DWORD dwUser);
	friend BOOL CALLBACK  GetParamsFunc(int nWndID, int type, DWORD dwUser);
	friend void CALLBACK SetParamsFunc(int nWndID, int type, DWORD dwUser);
	friend void CALLBACK RectEventFunc(RECT WinRect,CPoint &pointStart,CPoint &pointEnd,DWORD dwUser);
	CClientDemoDlg(CWnd* pParent = NULL);	// standard constructor

	
// Dialog Data
	//{{AFX_DATA(CClientDemoDlg)
	enum { IDD = IDD_CLIENTDEMO_DIALOG };
	CComboBox	m_comboPlayMode;
	CComboBox	m_auxNosel;
	CComboBox	m_comboPTZData;
	CExButton	m_iris_open;
	CExButton	m_iris_close;
	CExButton	m_focus_far;
	CExButton	m_focus_near;
	CExButton	m_zoom_tele;
	CExButton	m_zoom_wide;
	CExButton	m_ptz_rightdown;
	CExButton	m_ptz_rightup;
	CExButton	m_ptz_leftdown;
	CExButton	m_ptz_leftup;
	CExButton	m_ptz_right;
	CExButton	m_ptz_left;
	CExButton	m_ptz_down;
	CExButton	m_ptz_up;
	CComboBox	m_comboChannel;
	CComboBox	m_comboDispNum;
	CIPAddressCtrl	m_DvrIPAddr;
	CString	m_DvrUserName;
	CString	m_DvrPassword;
	DWORD	m_DvrPort;
	int		m_presetData;
	int		m_crviseGroup;
	int		m_moveNo;
	int		m_posX;
	int		m_posY;
	int		m_posZoom;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBTLogin();
	afx_msg void OnBUTTONPlay();
	afx_msg void OnBTLeave();
	afx_msg void OnDestroy();
	afx_msg void OnButtonStop();
	afx_msg void OnBtnPtzexctrl();
	afx_msg void OnPresetSet();
	afx_msg void OnPresetAdd();
	afx_msg void OnPresetDele();
	afx_msg void OnStartCruise();
	afx_msg void OnCruiseAddPoint();
	afx_msg void OnCruiseDelPoint();
	afx_msg void OnCruiseDelGroup();
	afx_msg void OnModeSetBegin();
	afx_msg void OnModeStart();
	afx_msg void OnModeSetDelete();
	afx_msg void OnLineSetLeft();
	afx_msg void OnLineSetRight();
	afx_msg void OnLineStart();
	afx_msg void OnFastGo();
	afx_msg void OnExactGo();
	afx_msg void OnResetZero();
	afx_msg void OnRotateStart();
	afx_msg void OnRotateStop();
	afx_msg void OnAuxOpen();
	afx_msg void OnAuxClose();
	afx_msg void OnBtnPtzmenu();
	afx_msg void OnSelchangeCOMBODispNum();
	afx_msg void OnCloseupCOMBODispNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void MultiPlayServerMode(int iDispNum, HWND hWnd);
	void ShowLoginErrorReason(int nError);
	void ServerPlayMode(int iDispNum,int iChannel,HWND hWnd);
	void DirectPlayMode(int iDispNum,int iChannel,HWND hWnd);
	void MultiPlayMode(int iDispNum,HWND hWnd);
	void StopPlayForMultiMode(int iDispNum);
	void StopPlayForServerMode(int iDispNum);
	void StopPlayForDirectMode(int iDispNum);
	void StopPlayForMultiServer(int iDispNum);
	
	void InitNetSDK();
	void InitPTZControl();
	void InitComboBox();
	HWND GetDispHandle(int nNum);
	CString GetDvrIP();
	void IsValid();
	long GetStreamPort(long lRealHandle);
	void SetPlayVideoInfo(int iDispNum,int iChannel,enum RealPlayMode ePlayMode);
	void CloseDispVideo(int iDispNum);

	void UpdataScreenPos(void);
	void MessageProc(int nWndID, UINT message);
	BOOL GetParams(int nWndID, int type);
	void SetParams(int nWndID, int type);
	BOOL GetExitDecode(int nCurWndID);
	BOOL GetExitCycle(int nCurWndID);
	void SetExitDecode(int nCurWndID);
	void SetExitCycle(int nCurWndID);
	
	//Device channel amount 
	int m_nChannelCount;
	CRect m_rectSmall;
	CRect m_rectLarge;
	//9-window control information 
	CVideoNodeInfo m_videoNodeInfo[9];
	long m_DispHanle[9];

	CPtzScreen m_ptzScreen;
	CRect			m_screenRect;
	CRect			m_clientRect;
	int				m_CurScreen;
	BOOL			m_bWndExitDecode[16];
	BOOL			m_bWndExitCycle[16];
	CCriticalSection m_cs;
	CCriticalSection m_csPos;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMODLG_H__475AE43D_B618_4F15_9DE9_2628AA826F52__INCLUDED_)
