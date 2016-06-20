#if !defined(AFX_DECTOURDLG_H__C6750A03_8C95_4FB9_832F_F023AEC2821B__INCLUDED_)
#define AFX_DECTOURDLG_H__C6750A03_8C95_4FB9_832F_F023AEC2821B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DecTourDlg.h : header file
//

#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CDecTourDlg dialog
class CDecTourDlg : public CDialog
{
// Construction
public:
	void SetDlgParam(LLONG lLoginID, int nDevChannel);
	CDecTourDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDecTourDlg)
	enum { IDD = IDD_DLG_TOUR };
	CEdit	m_editTourTime;
	CTreeCtrl	m_treeCombins;
	CComboBox	m_TVID;
	CComboBox	m_disMode;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecTourDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDecTourDlg)
	afx_msg BOOL OnInitDialog();
	afx_msg void OnBtnAddCombin();
	afx_msg void OnBtnDelCombin();
	afx_msg void OnBtnTourOk();
	afx_msg void OnBtnQueryCombin();
	afx_msg void OnSelendokComboTvid();
	afx_msg void OnSelchangeComboDismode();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnCheck1(UINT uID);
	afx_msg void OnBtnDelAllcombin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nDecChannel;
	LLONG m_hCurLoginID;
	UINT m_tourTime;
	BOOL UpdateTourTime(BOOL b = TRUE);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECTOURDLG_H__C6750A03_8C95_4FB9_832F_F023AEC2821B__INCLUDED_)
