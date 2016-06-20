#if !defined(AFX_SEARCHTVDLG_H__1D2DCA6C_5B09_430F_BA75_0258B835B22A__INCLUDED_)
#define AFX_SEARCHTVDLG_H__1D2DCA6C_5B09_430F_BA75_0258B835B22A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchTVDlg.h : header file
//
#include "TypeDef.h"
#include "dhnetsdk.h"
/////////////////////////////////////////////////////////////////////////////
// CSearchTVDlg dialog

class CSearchTVDlg : public CDialog
{
// Construction
public:
	void SetDlgParam(LLONG lLoginID, int nDevChannel);
	int m_nDecChannel;
	LLONG m_hCurLoginID;
	int m_nCurTvID;
	DHDEV_DECODEPOLICY_CFG m_stuDecodePolicy;
	DEV_DECODER_TV m_stuDevTvInfo[MAX_DEC_TV_NUM];
	CSearchTVDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchTVDlg)
	enum { IDD = IDD_DLG_SEARCH_TV };
	CComboBox	m_ctlDecTV;
	CListCtrl	m_ctlSearchTVList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchTVDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchTVDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearchOk();
	afx_msg void OnButChangeenable();
	afx_msg void OnBtnWork();
	afx_msg void OnButtonSnap();
	afx_msg void OnButtonDecodepolicy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InsertListView(int nChannelId, int nWndId, CString strIp, int nPort,
		CString strUser, CString strPwd, CString strEnable, CString strWorkMode, 
		CString strConnType, int nListenPort, CString strStreamType,
		CString strSnapMode);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHTVDLG_H__1D2DCA6C_5B09_430F_BA75_0258B835B22A__INCLUDED_)
