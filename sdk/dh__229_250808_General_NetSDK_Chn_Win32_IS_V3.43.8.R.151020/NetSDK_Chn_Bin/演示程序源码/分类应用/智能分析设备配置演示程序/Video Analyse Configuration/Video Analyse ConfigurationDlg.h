// Video Analyse ConfigurationDlg.h : header file
//

#if !defined(AFX_VIDEOANALYSECONFIGURATIONDLG_H__36D81FB2_06BD_4E16_BABD_99A6DDFC2099__INCLUDED_)
#define AFX_VIDEOANALYSECONFIGURATIONDLG_H__36D81FB2_06BD_4E16_BABD_99A6DDFC2099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  MAX_CHANNEL_NUM 16

#include "ConfigModule.h"
#include "ConfigRules.h"
#include "ConfigTraffic.h"
#include "ConfigTrafficGateRule.h"
#include "ConfigAtmScene.h"

/////////////////////////////////////////////////////////////////////////////
// CVideoAnalyseConfigurationDlg dialog

class CVideoAnalyseConfigurationDlg : public CDialog
{
// Construction
public:
	CVideoAnalyseConfigurationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoAnalyseConfigurationDlg)
	enum { IDD = IDD_VIDEOANALYSECONFIGURATION_DIALOG };
	CTabCtrl	m_ctlMainTab;
	CString	m_strIP;
	CString	m_strPassWord;
	DWORD	m_dwPort;
	CString	m_strUserName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoAnalyseConfigurationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CVideoAnalyseConfigurationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonLogin();
	afx_msg void OnButtonLogout();
	afx_msg void OnSelchangeTabAttribute(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void DeviceDisConnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HICON                     m_hIcon;
	LLONG                      m_lLoginID;
	int                       m_nChannelCount;
	CFG_CAP_ANALYSE_INFO *    m_pDeviceCap[MAX_CHANNEL_NUM];
	
	CConfigModule             m_cModuleConfigDlg;
	CConfigRules              m_cRulesConfigDlg;
	CConfigTrafficScene*      m_pTrafficSceneDlg;
	CConfigAtmScene*		  m_pAtmSceneDlg;
	//CConfigTrafficGateRule    m_cTrafficGateRuleDlg;
	
	void InitNetSDK(void);
	BOOL AddPage(DWORD dwDevType, CString strTitle, CDialog* dlgPage, UINT uID);
	BOOL DeletePage();
	void DeviceDisConnect(LLONG lLoginID, char *sDVRIP, LONG nDVRPort);
	friend void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
	friend BOOL CALLBACK MessCallBackFunc(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
	
	void GetCap(int nChannel, CFG_CAP_ANALYSE_INFO *pstuChannelCap);
	void InitTabControl();
	void DoTab(int nTab);
	void SetDlgState(CWnd *pWnd, BOOL bShow);
	void ClearSource();

public:
	CFG_CAP_ANALYSE_INFO* GetChannelCapInfo(int nChannel);
	long GetLoginID();

	BOOL GetTrafficScene(int nChannel, CFG_ANALYSEGLOBAL_INFO &stuAnalysGlobalInfo);
	void SetTrafficScene(int nChannel, CFG_ANALYSEGLOBAL_INFO &stuAnalysGlobalInfo);
	BOOL GetModule(int nChannel, CFG_ANALYSEMODULES_INFO &stuAnalysModuleInfo);
	void SetModule(int nChannelId, CFG_ANALYSEMODULES_INFO &stuAnalysModuleInfo);
	BOOL GetRule(int nChannel, CFG_ANALYSERULES_INFO &stuAnalysModuleInfo);
	void SetRule(int nChannelId, CFG_ANALYSERULES_INFO stuAnalysModuleInfo);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOANALYSECONFIGURATIONDLG_H__36D81FB2_06BD_4E16_BABD_99A6DDFC2099__INCLUDED_)
