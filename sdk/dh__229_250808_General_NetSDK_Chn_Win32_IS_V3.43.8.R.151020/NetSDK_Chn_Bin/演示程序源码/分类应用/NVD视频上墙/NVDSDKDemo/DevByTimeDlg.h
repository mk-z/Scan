#if !defined(AFX_DEVBYTIMEDLG_H__27627758_479F_40D5_B20D_44E246DEA9A9__INCLUDED_)
#define AFX_DEVBYTIMEDLG_H__27627758_479F_40D5_B20D_44E246DEA9A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevByTimeDlg.h : header file
//

#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CDevByTimeDlg dialog

class CDevByTimeDlg : public CDialog
{
// Construction
public:
	DEC_PLAYBACK_TIME_PARAM m_stuPlaybackParam;
	LONG m_lLoginHandle;
	int m_nChannelNum;
	CDevByTimeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDevByTimeDlg)
	enum { IDD = IDD_DLG_DEV_TIME };
	CComboBox	m_ctlChannel;
	CTime	m_timeTo;
	CTime	m_timeFrom;
	COleDateTime	m_dateTo;
	COleDateTime	m_dateFrom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevByTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDevByTimeDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	NET_TIME ConvertTime(CTime &date, CTime &time);
	NET_TIME ConvertToDateTime(const COleDateTime &date, const CTime &time);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVBYTIMEDLG_H__27627758_479F_40D5_B20D_44E246DEA9A9__INCLUDED_)
