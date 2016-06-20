// ClientDemo1Dlg.h : header file
//

#if !defined(AFX_CLIENTDEMO1DLG_H__7F279BB2_041F_4199_9E49_32FC11D6CD45__INCLUDED_)
#define AFX_CLIENTDEMO1DLG_H__7F279BB2_041F_4199_9E49_32FC11D6CD45__INCLUDED_

#include "dhnetsdk.h"
#include <math.h>
#include "TabAlarmDlg.h"	// Added by ClassView
#include "TabUserManageDlg.h"	// Added by ClassView
#include"NewAlarm.h"
#include "QueryAlarmState.h"
#include <afxtempl.h>
#include <afxmt.h>
#include "AlarmInfo.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDemo1Dlg dialog

class CClientDemo1Dlg : public CDialog
{
// Construction
public:
	//Callback interface 
	void DeviceDisConnect(LLONG lLoginID, char *sDVRIP,LONG nDVRPort);
	BOOL ReceiveMessageEx(LLONG lLoginID, LONG lCommand, char *pchDVRIP, LONG nDVRPort, char *pBuf, DWORD dwBufLen);
	BOOL ReceiveMessage(LLONG lLoginID, LONG lCommand, char *pchDVRIP, LONG nDVRPort, char *pBuf, DWORD dwBufLen);
	//callback function when device disconnected 
	friend void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
	//Message callback process function. It is a callback to the whole SDK implement to process the callbacked alarm message.
	friend BOOL CALLBACK MessCallBack(LONG lCommand, LLONG lLoginID, char *pBuf,
		DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
	bool NewVer(void){return m_bNewVer;}

	//Log in handle 
	LLONG m_LoginID;
	CCriticalSection m_cs;
	//Define list to storage alamr message 
	CList<CAlarmInfo,CAlarmInfo&> m_listAlarmInfo;
	CList<CAlarmInfoEx,CAlarmInfoEx&> m_ListAlarmInfoEx;

	CClientDemo1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDemo1Dlg)
	enum { IDD = IDD_CLIENTDEMO1_DIALOG };
	CIPAddressCtrl	m_dvrIP;
	CTabCtrl	m_Tab;
	int		m_dvrPort;
	CString	m_strDvrUserName;
	CString	m_strDvrPwd;
	SYSTEMTIME	stuTime;
	SYSTEMTIME	stuTimeLater;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo1Dlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLogout();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bIsListen;
	UINT m_nTimer;
	int m_nInAlarmCount;

	CAlarmInfo m_curAlarmInfo;
	//Device alarm page 
	CTabAlarmDlg *m_pTabAlarmDlg;
	//User management page 
	CTabUserManageDlg *m_pTabUsrManageDlg;
	CNewAlarm		* m_pTabNewAlarmDlg;
	CQueryAlarmState *m_pTabQueryAlarm;
	//Version is 2.6 or higher 
	bool	m_bNewVer;

	void SoundAlarm(char *pBuf, DWORD dwBufLen);
	void DiskError(char *pBuf, DWORD dwBufLen);
	void DiskFullAlarm(char *pBuf, DWORD dwBufLen);
	void ShelterAlarm(char *pBuf,DWORD dwBufLen);
	void CommAlarm(char *pBuf,DWORD dwBufLen);
	void ShowLoginErrorReason(int nError);
	CString GetDvrIP();
	void InitNetSDK();
	void InitTabControl();
	void DoTab(int nTab);
	void SetDlgState(CWnd *pWnd,BOOL bShow);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO1DLG_H__7F279BB2_041F_4199_9E49_32FC11D6CD45__INCLUDED_)





















