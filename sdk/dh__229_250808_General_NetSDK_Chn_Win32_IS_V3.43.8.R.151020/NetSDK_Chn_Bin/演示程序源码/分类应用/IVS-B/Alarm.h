#if !defined(AFX_ALARM_H__A5B0E434_8039_41D6_86C1_E70762CBAD7C__INCLUDED_)
#define AFX_ALARM_H__A5B0E434_8039_41D6_86C1_E70762CBAD7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Alarm.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CAlarm dialog

class CAlarm : public CDialog
{
public:
	void initAlarmDlg(int nChnCount);
	void uninitAlarmDlg();

	//按照报警时间、报警事件类型、报警通道筛选
	lsAlarmInfo showAlarmByChannel(lsAlarmInfo* plsAlarmInfo);
	lsAlarmInfo showAlarmByTime(lsAlarmInfo* plsAlarmInfo);
	lsAlarmInfo showAlarmByRuleType(lsAlarmInfo* plsAlarmInfo);

	inline void insertAlarmInfo(AlarmInfoNode* pAlarmInfoNode);
	void clearAllAlarmInfo();
	void showAlarmInfo();

// Construction
public:
	CAlarm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarm)
	enum { IDD = IDD_ALARM };
	CDateTimeCtrl	m_dtpStartTime;
	CDateTimeCtrl	m_dtpStartDate;
	CDateTimeCtrl	m_dtpEndTime;
	CDateTimeCtrl	m_dtpEndDate;
	CTreeCtrl	m_treeRuleType;
	CListCtrl	m_lsAlarmInfo;
	CComboBox	m_cmbChannel;
	//}}AFX_DATA	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarm)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeAlarmCmbChannel();
	afx_msg void OnDatetimechangeAlarmDtpStartdate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeAlarmDtpStarttime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeAlarmDtpEnddate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeAlarmDtpEndtime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnDblclkAlarmListAlarminfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickAlarmTreeRulesel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnAlarmCome(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARM_H__A5B0E434_8039_41D6_86C1_E70762CBAD7C__INCLUDED_)
