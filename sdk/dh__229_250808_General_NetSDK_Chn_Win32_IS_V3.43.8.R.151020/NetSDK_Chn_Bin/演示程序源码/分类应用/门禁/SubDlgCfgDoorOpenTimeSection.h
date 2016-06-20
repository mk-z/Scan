#if !defined(AFX_SUBDLGCFGDOOROPENTIMESECTION_H__7DFCB570_72B1_4ECE_AC08_329C195B165C__INCLUDED_)
#define AFX_SUBDLGCFGDOOROPENTIMESECTION_H__7DFCB570_72B1_4ECE_AC08_329C195B165C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgCfgDoorOpenTimeSection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubDlgCfgDoorOpenTimeSection dialog

class CSubDlgCfgDoorOpenTimeSection : public CDialog
{
// Construction
public:
	CSubDlgCfgDoorOpenTimeSection(CWnd* pParent = NULL);   // standard constructor
	
	void SetTimeSection(const CFG_DOOROPEN_TIMESECTION_INFO* pstuTimeSection)
	{
		memcpy(&m_stuDoorTimeSection[0][0], pstuTimeSection, sizeof(m_stuDoorTimeSection));
	}
	
	const CFG_DOOROPEN_TIMESECTION_INFO* GetTimeSection(int i, int j)
	{
		if ((i >=0 && i < WEEK_DAY_NUM) && (j >= 0 && j < MAX_DOOR_TIME_SECTION))
		{
			return &m_stuDoorTimeSection[i][j];
		} 
		else
		{
			return NULL;
		}
	}

// Dialog Data
	//{{AFX_DATA(CSubDlgCfgDoorOpenTimeSection)
	enum { IDD = IDD_SUBDLG_DOOR_OPEN_TIMESECTION };
	CDateTimeCtrl	m_dtp4End;
	CDateTimeCtrl	m_dtp3End;
	CDateTimeCtrl	m_dtp2End;
	CDateTimeCtrl	m_dtp1End;
	CDateTimeCtrl	m_dtp4Start;
	CDateTimeCtrl	m_dtp3Start;
	CDateTimeCtrl	m_dtp2Start;
	CDateTimeCtrl	m_dtp1Start;
	CComboBox	m_cmbWeekDay;
	CComboBox	m_cmbOpenMethod4;
	CComboBox	m_cmbOpenMethod3;
	CComboBox	m_cmbOpenMethod2;
	CComboBox	m_cmbOpenMethod1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgCfgDoorOpenTimeSection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgCfgDoorOpenTimeSection)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDooropentimesectionCmbWeekday();
	afx_msg void OnDatetimechangeDooropentimesectionDtpSt1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDooropentimesectionDtpEt1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDooropentimesectionDtpSt2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDooropentimesectionDtpEt2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDooropentimesectionDtpSt3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDooropentimesectionDtpEt3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDooropentimesectionDtpSt4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDooropentimesectionDtpEt4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeDooropentimesectionCmbOpenmethod1();
	afx_msg void OnSelchangeDooropentimesectionCmbOpenmethod2();
	afx_msg void OnSelchangeDooropentimesectionCmbOpenmethod3();
	afx_msg void OnSelchangeDooropentimesectionCmbOpenmethod4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitDlg();
	void StuToDlg();
	void DlgToStu();
	void ShowTimeSection(int nSeg, const CFG_DOOROPEN_TIMESECTION_INFO& stuTimeSection);
	void GetTimeSectionFromDlg();
	void CfgTimePeriodToDTP(const CFG_TIME_PERIOD& stuTimeSection, SYSTEMTIME& stBegin, SYSTEMTIME& stEnd);
	void DTPToCfgTimePeriod(const SYSTEMTIME& stuStart, const SYSTEMTIME& stuEnd, CFG_TIME_PERIOD& stuPeriod);

private:
	CFG_DOOROPEN_TIMESECTION_INFO	m_stuDoorTimeSection[WEEK_DAY_NUM][MAX_DOOR_TIME_SECTION];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGCFGDOOROPENTIMESECTION_H__7DFCB570_72B1_4ECE_AC08_329C195B165C__INCLUDED_)
