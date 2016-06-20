#if !defined(AFX_ALARMVLOSTDLG_H__B25B6583_1180_452C_8938_2AE7BD5B8B4F__INCLUDED_)
#define AFX_ALARMVLOSTDLG_H__B25B6583_1180_452C_8938_2AE7BD5B8B4F__INCLUDED_

#include "dhnetsdk.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmVLostDlg.h : header file
//
#include "DlgChn.h"
/////////////////////////////////////////////////////////////////////////////
// CAlarmVLostDlg dialog

class CAlarmVLostDlg : public CDialog
{
// Construction
public:
	//Save
	BOOL SaveAll();
	//Clear
	void CleanAll();
	//Display video loss alarm information
	void InitDlgInfo(DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo, BYTE nAlarmIn, BYTE nAlarmOut, int nChannel, vector<string>& vecAlarmName);

	void RefreshAlarmName();

	vector<string> *m_vecAlarmName;
	
	int GetCurChannel(){return m_nCurAlarmChannel;}
	
	void UpdateSchedule();
	//Video loss alarm information structure 
//	DH_VIDEO_LOST_CFG m_VideoLostInfo[DH_MAX_VIDEO_IN_NUM];
//	DH_VIDEO_LOST_CFG_EX m_VideoLostInfo[DH_MAX_VIDEO_IN_NUM_EX];

	CFG_VIDEOLOST_INFO   *m_pstVideoLostInfo;

	
	CAlarmVLostDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmVLostDlg)
	enum { IDD = IDD_CONFIG_ALARM_VIDEOLOST };
	CEdit	m_editAlarmName;
	CButton	m_ctlPRD6;
	CButton	m_ctlPRD5;
	CButton	m_ctlPRD4;
	CButton	m_ctlPRD3;
	CButton	m_ctlPRD2;
	CButton	m_ctlPRD1;
	CButton	m_chkLocalTour;
	CButton	m_chkLocalIP;
	CButton	m_chkUpload;
	CButton	m_chkSendMail;
	CButton	m_chkRecord;
	CButton	m_chkOutPut;
	CButton	m_chkAlarmEn;
	CComboBox	m_ctlChannel;
	CComboBox	m_ctlAlarmWeek;
	UINT	m_prd1EndHour;
	UINT	m_prd1StartHour;
	UINT	m_prd1EndMinute;
	UINT	m_prd1StartMinute;
	UINT	m_prd1EndSecond;
	UINT	m_prd1StartSecond;
	UINT	m_prd2EndHour;
	UINT	m_prd2StartHour;
	UINT	m_prd2StartMinute;
	UINT	m_prd2EndSecond;
	UINT	m_prd3EndHour;
	UINT	m_prd3EndMinute;
	UINT	m_prd3StartMinute;
	UINT	m_prd3EndSecond;
	UINT	m_prd3StartSecond;
	UINT	m_prd4EndHour;
	UINT	m_prd4StartHour;
	UINT	m_prd4EndMinute;
	UINT	m_prd4StartMinute;
	UINT	m_prd4EndSecond;
	UINT	m_prd4StartSecond;
	UINT	m_prd2EndMinute;
	UINT	m_prd5EndHour;
	UINT	m_prd5StartHour;
	UINT	m_prd5EndMinute;
	UINT	m_prd5StartMinute;
	UINT	m_prd5EndSecond;
	UINT	m_prd5StartSecond;
	UINT	m_prd6EndHour;
	UINT	m_prd6StartHour;
	UINT	m_prd6EndMinute;
	UINT	m_prd6StartMinute;
	UINT	m_prd6EndSecond;
	UINT	m_prd6StartSecond;
	UINT	m_prd2StartSecond;
	UINT	m_prd3StartHour;
	BOOL	m_bMatrixEn;
	BOOL	m_bLog;
	UINT	m_dwAmount;
	UINT	m_dwMatrixMask;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmVLostDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmVLostDlg)
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnSelchangeComboAlarmweek();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnChangeEditVideolostAlarmname();
	afx_msg void OnBtnDriveRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowPeriodInfo (CFG_TIME_SECTION *pTSect, BYTE nNum);
	int m_nCurWeek;
	BOOL SaveWeekInfo (int nNum, int nWeek);
	int m_nCurAlarmChannel;
	BOOL SaveAlarmChannelInfo (int nNum);
	int m_nChannel;
	int m_nAlarmOut;
	BOOL m_bNewProtocol;
	CDlgChn m_chnAlarmOut;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMVLOSTDLG_H__B25B6583_1180_452C_8938_2AE7BD5B8B4F__INCLUDED_)
