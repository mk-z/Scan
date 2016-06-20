#if !defined(AFX_PLAYBACKBYTIME_H__35EAB30F_C6FB_4466_84AC_BF1C76B9623E__INCLUDED_)
#define AFX_PLAYBACKBYTIME_H__35EAB30F_C6FB_4466_84AC_BF1C76B9623E__INCLUDED_

#include "dhnetsdk.h"
#include "PlaybackByFile.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlaybackByTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlaybackByTime dialog

class CPlaybackByTime : public CDialog
{
// Construction
public:
	//Set channel dropdown menu 
	void InitComboBox(int nChannel,long lLoginID);
	//Log out and then clear
	void Clean();

	long m_hLoginID;
	DWORD m_dwCurValue;
	DWORD m_dwTotalSize;
	CPlaybackByTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlaybackByTime)
	enum { IDD = IDD_PLAYBACK_BYTIME };
	CComboBox	m_ctlStreamType;
	CComboBox	m_ctlQueryType;
	CComboBox	m_ctlPlayMode;
	CComboBox	m_ctlLoadChannel;
	CProgressCtrl	m_ctlLoadPro;
	CComboBox	m_ctlChannel;
	CTime	m_timeLoadFrom;
	CTime	m_timeLoadTo;
	COleDateTime	m_dateLoadFrom;
	COleDateTime	m_dateLoadTo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaybackByTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlaybackByTime)
	afx_msg void OnButtonDownload();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelectMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonPlayReverse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void OnButtonPlay();
private:
	UINT m_nTimer;
	NET_RECORDFILE_INFO m_netFileInfo[2000];
	NET_TIME ConvertTime(CTime date,CTime time);
	NET_TIME ConvertToDateTime(const COleDateTime& date, const CTime& time);
	/// NET_TIME结构体之间的大小比较
	int Compare(const NET_TIME *pSrcTime, const NET_TIME *pDestTime);
    void SetControlButton(BOOL nFlag);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYBACKBYTIME_H__35EAB30F_C6FB_4466_84AC_BF1C76B9623E__INCLUDED_)
