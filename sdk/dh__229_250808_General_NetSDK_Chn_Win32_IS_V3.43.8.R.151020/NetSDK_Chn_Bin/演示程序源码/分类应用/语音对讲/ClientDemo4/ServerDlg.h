#if !defined(AFX_SERVERDLG_H__9128FE31_E178_4DD5_A86D_A9DF899EECDC__INCLUDED_)
#define AFX_SERVERDLG_H__9128FE31_E178_4DD5_A86D_A9DF899EECDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

class CServerDlg : public CDialog
{
// Construction
public:
	void AudioData(LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag);
	void AudioRecord(LPBYTE pDataBuffer, DWORD DataLength);
	void ShowTalkErrorReason(int nError);
	CServerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_DIALOG_SERVER };
	CComboBox	m_ctlTransmitType;
	CComboBox	m_ctlSpeakerChl;
	CComboBox	m_ctlEncodeType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLogout();
	afx_msg void OnBtnStarttalk();
	afx_msg void OnBtnStoptalk();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboTransmitType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void * m_hisEncodeHandle;
	void * m_AACEncodeHandle;
	LONG m_hTalkHandle;
	BOOL m_bOpenAudioRecord;
	LONG m_lLoginHandle;
	DHDEV_TALKDECODE_INFO m_curTalkMode;
	DHDEV_TALKFORMAT_LIST m_lstTalkEncode;
	void ShowLoginErrorReason(int nError);
	BOOL StartAudioRecord();
    LONG m_lTalkChnNum;
    LONG m_lDevChnNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__9128FE31_E178_4DD5_A86D_A9DF899EECDC__INCLUDED_)
