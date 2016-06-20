#if !defined(AFX_ALARMMOTION_H__E5B73FCD_2BD1_4200_8090_053C3C1415DB__INCLUDED_)
#define AFX_ALARMMOTION_H__E5B73FCD_2BD1_4200_8090_053C3C1415DB__INCLUDED_

#include "dhnetsdk.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmMotion.h : header file
//
#include "DlgChn.h"
#include "ConfigAlarmMotionArea.h"

/////////////////////////////////////////////////////////////////////////////
// CAlarmMotion dialog

class CAlarmMotion : public CDialog
{
// Construction
public:
	//Save
	BOOL SaveAll();
	//Clear
	void CleanAll();
	//Display motion detection alarm information
//	void InitDlgInfo(DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo, BYTE nAlarmIn, BYTE nAlarmOut, BYTE nChannel, BOOL bNewProtocol, vector<string>& vecAlarmName);
	void InitDlgInfo(DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo, 
					 BYTE nAlarmIn, 
					 BYTE nAlarmOut, 
					 int nChannel, 
					 vector<string>& vecAlarmName);
	
	void RefreshAlarmName();

	vector<string> *m_vecAlarmName;

	int GetCurChannel(){return m_nCurAlarmChannel;}
	
	//Motion detection alarm information structure 
//	DH_MOTION_DETECT_CFG m_AlarmMotionInfo[DH_MAX_VIDEO_IN_NUM];
//	DH_MOTION_DETECT_CFG_EX m_AlarmMotionInfo[DH_MAX_VIDEO_IN_NUM_EX];
	
	CFG_MOTION_INFO* m_pstuMotionInfo;

	CAlarmMotion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmMotion)
	enum { IDD = IDD_CONFIG_ALARM_MOTION };
	CEdit	m_editAlarmName;
	CButton	m_ctlAlarmEn;
	CButton	m_ctlPRD6;
	CButton	m_ctlPRD5;
	CButton	m_ctlPRD4;
	CButton	m_ctlPRD3;
	CButton	m_ctlPRD2;
	CButton	m_ctlPRD1;
	CButton	m_chkRecord;
	CButton	m_chkSendMail;
	CButton	m_chkOutPut;
	CButton	m_chkLocalTour;
	CButton	m_chkLocalIP;
	CButton	m_chkUpload;
	CComboBox	m_ctlAlarmWeek;
	CComboBox	m_ctlChannel;
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
	UINT	m_dwAmount;
	UINT	m_dwMatrixMask;
	BOOL	m_bMatrixEn;
	BOOL	m_bLog;
	int     nwSenseLevel; 
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmMotion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmMotion)
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnSelchangeComboAlarmweek();
	afx_msg void OnBtnArea();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnChangeEditMotionAlarmName();
	afx_msg void OnBtnDriveRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool IsWeekDataValid();
	int m_nCurWeek;
	void ShowPeriodInfo(CFG_TIME_SECTION *pTSect, BYTE nNum);
	BOOL SaveWeekInfo(int nNum, int nWeek);
	int m_nCurAlarmChannel;
	BOOL SaveAlarmChannelInfo(int nNum);
	int m_nChannel;
	int m_nAlarmOut;
	BOOL m_bNewProtocol;
	CDlgChn m_chnAlarmOut;

    CConfigAlarmMotionArea m_areaDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMMOTION_H__E5B73FCD_2BD1_4200_8090_053C3C1415DB__INCLUDED_)
