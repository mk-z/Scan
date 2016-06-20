#if !defined(AFX_PLAYBACKBYFILE_H__9F2433DE_CF15_42D1_AB9E_AF306B0471EB__INCLUDED_)
#define AFX_PLAYBACKBYFILE_H__9F2433DE_CF15_42D1_AB9E_AF306B0471EB__INCLUDED_

#include "dhnetsdk.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlaybackByFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlaybackByFile dialog
//Search type
enum QueryType{
	EM_LISTALL,
	EM_ALARMALL,
	EM_PICTURE,
	EM_CARD,
};

//Play mode 
enum PlayBackMode{
	EM_DIRECTMODE,
	EM_SERVERMODE,
};

//Stream type 
enum PlayBackStream{
    EM_BOTH_STREAM,
        EM_MAIN_STREAM,
        EM_EXTRA_STREAM
};



class CPlaybackByFile : public CDialog
{
// Construction
public:
	//Set channel 
	void InitComboBox(int nChannel,long lLoginID);
	//Log off and then clear
	void Clean();
	
	DWORD m_dwTotalSize;
	DWORD m_dwCurValue;
	long m_hLoginID;

	CPlaybackByFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlaybackByFile)
	enum { IDD = IDD_PLAYBACK_RECORDFILE };
	CComboBox	m_ctlPlayMode;
	CProgressCtrl	m_ctlLoadPro;
	CListCtrl	m_ctlListInfo;
	CComboBox	m_ctlQueryType;
	CComboBox	m_ctlChannel;
	CTime	m_timeFrom;
	CTime	m_timeTo;
	COleDateTime	m_dateFrom;
	COleDateTime	m_dateTo;
    CComboBox	m_ctlStreamType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaybackByFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlaybackByFile)
	afx_msg void OnButtonQuery();
	afx_msg void OnButtonPlaybyfile();
	afx_msg void OnButtonCleanlist();
	afx_msg void OnButtonDownloadbyfile();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListQueryinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonFarthestrecord();
	afx_msg void OnButtonLock();
	afx_msg void OnButtonUnlock();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nTimer;
	NET_RECORDFILE_INFO m_netFileInfo[2000];
	void AddRecordInfoToListView(LPNET_RECORDFILE_INFO pRecordFiles,int nFileCount);
	NET_TIME ConvertTime(CTime date,CTime time);
	NET_TIME ConvertToDateTime(const COleDateTime &date, const CTime &time);
	void InitListView();
    void SetControlButton(BOOL bFlag);
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYBACKBYFILE_H__9F2433DE_CF15_42D1_AB9E_AF306B0471EB__INCLUDED_)
