#if !defined(AFX_PLAYBACKMULTY_H__B8F066CA_0472_4A6C_AC7D_B6BF778CCD8A__INCLUDED_)
#define AFX_PLAYBACKMULTY_H__B8F066CA_0472_4A6C_AC7D_B6BF778CCD8A__INCLUDED_
#include "dhnetsdk.h"
#include "PlaybackByFile.h"
#include "ChannelOneDialog.h"
#include "FourChannelsDialog.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlaybackMulty.h : header file
//
//Play mode 
enum MultyMode{
    EM_CHANNLE_1,
    EM_CHANNLE_1_to_4,
};

enum MultyPlayBackType{
        EM_MULTY_LISTALL,
        EM_MULTY_ALARMALL,
        EM_MULTY_MOVING,
        EM_MULTY_CARD,
        EM_MULTY_PICTURE,
};

//Resolution type
enum ResolutionType{
    EM_D1,
    EM_HD1,
    EM_2CIF,
    EM_CIF,
    EM_QCIF,
};

/////////////////////////////////////////////////////////////////////////////
// CPlaybackMulty dialog

class CPlaybackMulty : public CDialog
{
// Construction
public:
	CPlaybackMulty(CWnd* pParent = NULL, const LLONG& lLoginID = 0);   // standard constructor
	bool EnableComboBox(int nChannel);
    bool DisableComboBox();
// Dialog Data
	//{{AFX_DATA(CPlaybackMulty)
	enum { IDD = IDD_PLAYBACK_MULTY };
	CComboBox	m_cStreamType;
	CComboBox	m_cChannel;
	CComboBox	m_cPlayType;
	CComboBox	m_cResolution;
	CComboBox	m_cMultyPlayMode;
	int		m_nBitRate;
	int		m_nFps;
	COleDateTime	m_DateFrom;
	COleDateTime	m_DateTo;
	CTime	m_TimeFrom;
	CTime	m_TimeTo;
	int		m_nTotalChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaybackMulty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    int Compare( const NET_TIME *pSrcTime, const NET_TIME *pDestTime);
    NET_TIME ConvertToDateTime(const COleDateTime &date, const CTime &time);
	// Generated message map functions
	//{{AFX_MSG(CPlaybackMulty)
	afx_msg void OnButtonPlay();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonChannelsChoose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    const LLONG& m_hLoginID;
    NET_RECORDFILE_INFO m_netFileInfo[2000];
    CChannelOneDialog* m_pOneChannelDlg;
    CFourChannelsDialog* m_pFourChannelsDlg;
    bool m_bEnableComboBoxFlag;
    void SetControlButton(BOOL bFlag);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYBACKMULTY_H__B8F066CA_0472_4A6C_AC7D_B6BF778CCD8A__INCLUDED_)
