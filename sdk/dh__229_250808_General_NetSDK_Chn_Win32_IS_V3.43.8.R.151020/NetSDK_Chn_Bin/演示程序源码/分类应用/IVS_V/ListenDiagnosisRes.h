#if !defined(AFX_LISTENDIAGNOSISRES_H__167BC9FF_FF09_439F_8AC8_B31DEE3206C5__INCLUDED_)
#define AFX_LISTENDIAGNOSISRES_H__167BC9FF_FF09_439F_8AC8_B31DEE3206C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenDiagnosisRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListenDiagnosisRes dialog
class CProjectCfg;
class CListenDiagnosisRes : public CDialog
{
// Construction
public:
	CListenDiagnosisRes(CWnd* pParent = NULL);   // standard constructor
	CListenDiagnosisRes(CDialog* pProject, CWnd* pParent = NULL);
	~CListenDiagnosisRes();

// Dialog Data
	//{{AFX_DATA(CListenDiagnosisRes)
	enum { IDD = IDD_DLG_LISTEN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenDiagnosisRes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
public:
		CListCtrl           m_lstResult;
		LLONG               m_hDiagnosisHandle;
		CProjectCfg*        m_pProject;


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListenDiagnosisRes)
	afx_msg void OnBtnStopListen();
	afx_msg void OnBtnStartListen();
	afx_msg void OnListenBtnFirstPage();
	afx_msg void OnListenBtnPrePage();
	afx_msg void OnListenBtnNextPage();
	afx_msg void OnListenBtnEndPage();
	afx_msg void OnListenBtnGoPage();
	afx_msg void OnRadioListenAllDevices();
	afx_msg void OnRadioListenOneDevice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	//int CALLBACK RealVideoDiagnosis(LLONG lDiagnosisHandle, NET_REAL_DIAGNOSIS_RESULT* pDiagnosisInfo, void* pBuf, int nBufLen, LDWORD dwUser);
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENDIAGNOSISRES_H__167BC9FF_FF09_439F_8AC8_B31DEE3206C5__INCLUDED_)
