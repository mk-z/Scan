#if !defined(AFX_ALARMINPUTDLG_H__5FBC643A_F376_45EC_947B_F31CE8C6B38C__INCLUDED_)
#define AFX_ALARMINPUTDLG_H__5FBC643A_F376_45EC_947B_F31CE8C6B38C__INCLUDED_

#include "dhnetsdk.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmInputDlg.h : header file
//
#include "DlgChn.h"
/////////////////////////////////////////////////////////////////////////////
// CAlarmInputDlg dialog

class CAlarmInputDlg : public CDialog
{
// Construction
public:
	//Save
	BOOL SaveAll();
	//Clear
	void CleanAll();
	//Display input alarm information
	void InitDlgInfo(DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo, BYTE nAlarmIn, BYTE nAlarmOut, int nChannel, vector<string>& vecAlarmName);
	vector<string> *m_vecAlarmName;
	void RefreshAlarmName();

	int GetCurChannel(){return m_nCurAlarmChannel;}
	//Input alarm information structure
//	DH_ALARMIN_CFG m_AlarmInInfo[DH_MAX_ALARM_IN_NUM];
//	DH_ALARMIN_CFG_EX m_AlarmInInfo[DH_MAX_ALARM_IN_NUM_EX];
	CFG_ALARMIN_INFO *m_pstAlarminInfo;
	
	CAlarmInputDlg(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CAlarmInputDlg)
	enum { IDD = IDD_CONFIG_ALARM_INPUT };
	CEdit	m_editAlarmName;
	CButton	m_ctlPRD6;
	CButton	m_ctlPRD5;
	CButton	m_ctlPRD4;
	CButton	m_ctlPRD3;
	CButton	m_ctlPRD2;
	CButton	m_ctlPRD1;
	CButton	m_ctlAlarmEn;
	CButton	m_chkUpload;
	CButton	m_chkSendMail;
	CButton	m_chkRecord;
	CButton	m_chkOutPut;
	CButton	m_chkLocalTour;
	CButton	m_chkLocalIP;
	CComboBox	m_ctlAlarmWeek;
	CComboBox	m_ctlAlarmType;
	CComboBox	m_ctlAlarmIn;
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
	UINT	m_dwMatrixMask;
	UINT	m_dwAmount;
	BOOL	m_bMatrixEn;
	BOOL	m_bLog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmInputDlg)
	afx_msg void OnSelchangeComboAlarmin();
	afx_msg void OnSelchangeComboAlarmweek();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnChangeEditAlarmname();
	afx_msg void OnBtnDriveRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nChannel;
	int m_nAlarmOut;
	void ShowPeriodInfo(CFG_TIME_SECTION *pTSect, BYTE nNum);
	int m_nCurWeek;
	BOOL SaveWeekInfo(int nNum, int nWeek);
	BOOL SaveAlarmChannelInfo(int nNum);
	int m_nCurAlarmChannel;
	BOOL m_bNewProtocol;
	bool IsWeekDataValid();
	CDlgChn m_chnAlarmOut;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMINPUTDLG_H__5FBC643A_F376_45EC_947B_F31CE8C6B38C__INCLUDED_)
