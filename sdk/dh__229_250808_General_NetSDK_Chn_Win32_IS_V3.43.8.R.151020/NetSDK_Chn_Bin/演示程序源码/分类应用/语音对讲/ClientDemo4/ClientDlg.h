#if !defined(AFX_CLIENTDLG_H__C192EAB6_1DE7_4095_B1DF_8106869D0F65__INCLUDED_)
#define AFX_CLIENTDLG_H__C192EAB6_1DE7_4095_B1DF_8106869D0F65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	void AudioData(LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag);
	void ShowTalkErrorReason(int nError);
	CClientDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_DIALOG_CLIENT };
	CComboBox	m_ctlTransmitType;
	CComboBox	m_ctlSpeakerChl;
	CComboBox	m_ctlEncodeType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
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
	BOOL m_bRecordStatus;
	LONG m_hTalkHandle;
	DHDEV_TALKDECODE_INFO m_curTalkMode;
	void ShowLoginErrorReason(int nError);
	
	DHDEV_TALKFORMAT_LIST m_lstTalkEncode;
	LONG m_lLoginHandle;
    LONG m_lTalkChnNum;
    LONG m_lDevChnNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__C192EAB6_1DE7_4095_B1DF_8106869D0F65__INCLUDED_)
