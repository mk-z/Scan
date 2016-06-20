#if !defined(AFX_DLGCFGTIMESCHEDULE_H__C1541FB4_4DDD_48A9_8D6A_83F9E6ED9939__INCLUDED_)
#define AFX_DLGCFGTIMESCHEDULE_H__C1541FB4_4DDD_48A9_8D6A_83F9E6ED9939__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgTimeSchedule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgTimeSchedule dialog

class CDlgCfgTimeSchedule : public CDialog
{
// Construction
public:
	CDlgCfgTimeSchedule(CWnd* pParent = NULL, LLONG lLoginID = 0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgTimeSchedule)
	enum { IDD = IDD_DLG_CFG_TIMESECTION };
	CDateTimeCtrl	m_dtp4Start;
	CDateTimeCtrl	m_dtp3Start;
	CDateTimeCtrl	m_dtp2Start;
	CDateTimeCtrl	m_dtp1Start;
	CDateTimeCtrl	m_dtp4End;
	CDateTimeCtrl	m_dtp3End;
	CDateTimeCtrl	m_dtp2End;
	CDateTimeCtrl	m_dtp1End;
	CComboBox	m_cmbWeekDay;
	CComboBox	m_cmbIndex;
	CButton	m_chkSeg4;
	CButton	m_chkSeg3;
	CButton	m_chkSeg2;
	CButton	m_chkSeg1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgTimeSchedule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgTimeSchedule)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimescheduleBtnGet();
	afx_msg void OnTimescheduleBtnSet();
	afx_msg void OnSelchangeTimescheduleCmbIndex();
	afx_msg void OnSelchangeTimescheduleCmbWeekday();
	afx_msg void OnDatetimechangeTimescheduleDtp1Start(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeTimescheduleDtp1End(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeTimescheduleDtp2Start(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeTimescheduleDtp2End(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeTimescheduleDtp3Start(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeTimescheduleDtp3End(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeTimescheduleDtp4Start(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeTimescheduleDtp4End(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimescheduleChkSeg1Enable();
	afx_msg void OnTimescheduleChkSeg2Enable();
	afx_msg void OnTimescheduleChkSeg3Enable();
	afx_msg void OnTimescheduleChkSeg4Enable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitDlg();
	void StuToDlg();
	void DlgToStu();
	BOOL SetConfigToDevice();
	BOOL GetConfigFromDevice();	
	void ShowTimeSection(int nSeg, const CFG_TIME_SECTION& stuTimeSection);
	void GetTimeSectionFromDlg();	
	void CfgTimeSectionToDTP(const CFG_TIME_SECTION& stuTimeSection, SYSTEMTIME& stBegin, SYSTEMTIME& stEnd);
	void DTPToCfgTimeSection(const SYSTEMTIME& stBegin, const SYSTEMTIME& stEnd, CFG_TIME_SECTION& stuTimeSection);

private:
	LLONG							m_lLoginID;
	CFG_ACCESS_TIMESCHEDULE_INFO	m_stuInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGTIMESCHEDULE_H__C1541FB4_4DDD_48A9_8D6A_83F9E6ED9939__INCLUDED_)
