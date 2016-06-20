// IVSFDemoDlg.h : header file
//

#if !defined(AFX_IVSFDEMODLG_H__D4259FC3_D9BF_4D88_A74A_E5F11411AD47__INCLUDED_)
#define AFX_IVSFDEMODLG_H__D4259FC3_D9BF_4D88_A74A_E5F11411AD47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "PreviewDlg.h"
#include "ConfigDlg.h"
#include "EventDlg.h"

#define LOGOUT "LogOut"
#define LOGIN  "LogIn"
/////////////////////////////////////////////////////////////////////////////
// CIVSFDemoDlg dialog
#define WM_USER_ALAMR_COME (WM_USER + 1)

class CIVSFDemoDlg : public CDialog
{
// Construction
public:
	CIVSFDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIVSFDemoDlg)
	enum { IDD = IDD_IVSFDEMO_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIVSFDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIVSFDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonLog();
	afx_msg void OnButtonConfig();
	afx_msg void OnButtonPreviwe();
	afx_msg void OnButtonAlarmon();
	afx_msg LRESULT OnAlarmCome(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPreviewDlg*               m_pdlgPreview;
	CConfigDlg*                m_pdlgConfig;
	
	LLONG                       m_lDevLogHandle;
	int                        m_nChannelCount;

	LLONG                       m_lAlarmLoadHandle[128];

	static int  __stdcall RealLoadPicCallback (LLONG lAnalyzerHandle, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser, int nSequence, void *userdata);
	static void  __stdcall OnDisConnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

	void LogOutDev();
	BOOL LogInDev();
public:
	void AlarmLoad(int* pChannelSel, BOOL bStart);
	void OnReceiveEvent(LLONG lAnalyzerHandle, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, int nSequence);
};

struct EventPara
{
	LLONG lAnalyzerHandle;
	DWORD dwAlarmType;
	void* pAlarmInfo;
	BYTE *pBuffer;
	DWORD dwBufSize;
	int nSequence;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVSFDEMODLG_H__D4259FC3_D9BF_4D88_A74A_E5F11411AD47__INCLUDED_)
