#if !defined(AFX_DEVBYFILEDLG_H__0A43A5B2_3A86_4CF2_91EB_101ACD082A3B__INCLUDED_)
#define AFX_DEVBYFILEDLG_H__0A43A5B2_3A86_4CF2_91EB_101ACD082A3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevByFileDlg.h : header file
//

#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CDevByFileDlg dialog

class CDevByFileDlg : public CDialog
{
// Construction
public:
	DEC_PLAYBACK_FILE_PARAM m_stuPlaybackParam;
	LONG m_lLoginHandle;
	int m_nChannelNum;
	CDevByFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDevByFileDlg)
	enum { IDD = IDD_DLG_DEV_FILE };
	CComboBox	m_ctlType;
	CComboBox	m_ctlChannel;
	CListCtrl	m_ctlRecordInfo;
	CTime	m_timeFrom;
	CTime	m_timeTo;
	COleDateTime	m_dateTo;
	COleDateTime	m_dateFrom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevByFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDevByFileDlg)
	afx_msg void OnButtonQuery();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListRecordInfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	NET_TIME ConvertToDateTime(const COleDateTime &date, const CTime &time);
	void AddRecordInfoToListView(LPNET_RECORDFILE_INFO pRecordFiles, int nFileCount);
	NET_TIME ConvertTime(CTime &date,CTime &time);
	NET_RECORDFILE_INFO m_netFileInfo[2000];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVBYFILEDLG_H__0A43A5B2_3A86_4CF2_91EB_101ACD082A3B__INCLUDED_)
