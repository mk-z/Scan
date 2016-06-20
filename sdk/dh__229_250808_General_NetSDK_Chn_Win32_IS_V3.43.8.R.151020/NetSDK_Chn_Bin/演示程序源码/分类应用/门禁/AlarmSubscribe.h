#if !defined(AFX_ALARMSUBSCRIBE_H__C7BFC1C5_D321_4CEE_BE90_FB6A67BD954B__INCLUDED_)
#define AFX_ALARMSUBSCRIBE_H__C7BFC1C5_D321_4CEE_BE90_FB6A67BD954B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmSubscribe.h : header file
//
#include <afxmt.h>

typedef struct 
{
	NET_ALARM_TYPE	emAlarmType;
	char*			pszName;
}DemoConfirmEvent;

const DemoConfirmEvent stuDemoConfirmEvent[] = 
{
	{NET_ALARM_LOCAL, "AlarmLocal"},
	{NET_ALARM_ALARMEXTENDED, "AlarmExtended"},
	{NET_ALARM_TEMP, "Temperature"},
	{NET_ALARM_URGENCY, "Urgency"},
};

#define WM_ALARM_INFO	(WM_USER+199)

#define MAX_MSG_SHOW	(10000)

/////////////////////////////////////////////////////////////////////////////
// AlarmSubscribe dialog

class AlarmSubscribe : public CDialog
{
// Construction
public:
	AlarmSubscribe(CWnd* pParent = NULL, LLONG hLoginID = NULL, UINT32 uiAlarmIn = 0, UINT32 uiAccessGroup = 0);   // standard constructor
// Dialog Data
	//{{AFX_DATA(AlarmSubscribe)
	enum { IDD = IDD_DLG_SUBSCRIBE };
	CComboBox	m_cbChannel;
	CListCtrl m_ctrAlarmRptList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AlarmSubscribe)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AlarmSubscribe)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSub();
	afx_msg void OnButtonStop();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnAlarmInfo(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSubscribeBtnCapture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void	InitListControl();
	void	GetTimeStringByStruct(NET_TIME stuTime, char *pTime);

	void	UpdateEventList();

	void	InsertAccessCtlEvent(ALARM_ACCESS_CTL_EVENT_INFO* pInfo);
	void	InsertAccessCtlBreakIn(ALARM_ACCESS_CTL_BREAK_IN_INFO* pInfo);
	void	InsertAccessCtlDuress(ALARM_ACCESS_CTL_DURESS_INFO* pInfo);
	void	InsertAccessCtlNotClose(ALARM_ACCESS_CTL_NOT_CLOSE_INFO* pInfo);
	void	InsertAccessCtlRepeatEnter(ALARM_ACCESS_CTL_REPEAT_ENTER_INFO* pInfo);
	void	InsertAccessCtlStatus(ALARM_ACCESS_CTL_STATUS_INFO* pInfo);

    void    InsertChassisintruded(ALARM_CHASSISINTRUDED_INFO* pInfo);
    void    InsertOpenDoorGroup(ALARM_OPEN_DOOR_GROUP_INFO* pInfo);
    void    InsertFingerPrint(ALARM_CAPTURE_FINGER_PRINT_INFO* pInfo);
	
	void	InsertAlarmEx2Event(ALARM_ALARM_INFO_EX2* pInfo);

private:
	LLONG		m_hLogin;
	int			m_nAlarmIndex;
	UINT32		m_uiAlarmIn;
    UINT32      m_uiAccessGroup;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMSUBSCRIBE_H__C7BFC1C5_D321_4CEE_BE90_FB6A67BD954B__INCLUDED_)
