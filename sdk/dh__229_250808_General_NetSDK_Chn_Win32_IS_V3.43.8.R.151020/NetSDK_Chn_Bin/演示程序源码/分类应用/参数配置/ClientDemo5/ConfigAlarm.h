#if !defined(AFX_CONFIGALARM_H__F4DBE0FA_7EB3_49AC_BAD2_7980DE002A34__INCLUDED_)
#define AFX_CONFIGALARM_H__F4DBE0FA_7EB3_49AC_BAD2_7980DE002A34__INCLUDED_

#include "AlarmVLostDlg.h"	// Added by ClassView
#include "AlarmShelter.h"	// Added by ClassView
#include "AlarmInputDlg.h"	// Added by ClassView
#include "AlarmMotion.h"	// Added by ClassView
#include "dhnetsdk.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigAlarm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarm dialog

class CConfigAlarm : public CDialog
{
// Construction
public:
	//Clear information
	void CleanAll();
	//Display alarm information
//	void InitDlgInfo(DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo,BYTE nAlarmIn,BYTE nAlarmOut,BYTE nChannel,BOOL bNewProtocol = FALSE);
	void InitDlgInfo(DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo,
					 BYTE nAlarmIn,
					 BYTE nAlarmOut,
					 int nChannel);

	vector<string> m_vecAlarmName;

	CConfigAlarm(CWnd* pParent = NULL);   // standard constructor
	~CConfigAlarm();

// Dialog Data
	//{{AFX_DATA(CConfigAlarm)
	enum { IDD = IDD_CONFIG_ALARM };
	CTabCtrl	m_ctlAlarmTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigAlarm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigAlarm)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabAlarmboard(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	DHDEV_ALARM_SCHEDULE_EX * m_pAlarmInfo;	
	BOOL m_bNewProtocol;
	BOOL m_bNewMotionDetect;

	void SetDlgState(CWnd *pWnd, BOOL bShow);
	void DoTab(int nTab);
	CAlarmVLostDlg m_TabVideoLost;
	CAlarmShelter m_TabShelter;
	CAlarmMotion m_TabMotion;
	CAlarmInputDlg m_TabAlarmInput;
	void InitTabControl();

	void SaveAlarmName();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGALARM_H__F4DBE0FA_7EB3_49AC_BAD2_7980DE002A34__INCLUDED_)
