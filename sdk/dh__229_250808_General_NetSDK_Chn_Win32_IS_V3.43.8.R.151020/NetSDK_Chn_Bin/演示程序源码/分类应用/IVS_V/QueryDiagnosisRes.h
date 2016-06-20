#if !defined(AFX_QUERYDIAGNOSISRES_H__D6E7F312_C69B_4F2D_B6EC_B22F189278B4__INCLUDED_)
#define AFX_QUERYDIAGNOSISRES_H__D6E7F312_C69B_4F2D_B6EC_B22F189278B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryDiagnosisRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryDiagnosisRes dialog
class CProjectCfg;
class CQueryDiagnosisRes : public CDialog
{
// Construction
public:
	CQueryDiagnosisRes(CWnd* pParent = NULL);   // standard constructor
	CQueryDiagnosisRes(CDialog* pProject, CWnd* pParent = NULL);
	~CQueryDiagnosisRes();

// Dialog Data
	//{{AFX_DATA(CQueryDiagnosisRes)
	enum { IDD = IDD_DLG_QUERY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryDiagnosisRes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQueryDiagnosisRes)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnQuery();
	afx_msg void OnBtnStopQuery();
	afx_msg void OnBtnFirstPage();
	afx_msg void OnBtnPrePage();
	afx_msg void OnBtnNextPage();
	afx_msg void OnBtnEndPage();
	afx_msg void OnBtnGoPage();
	afx_msg void OnRadioAllDevices();
	afx_msg void OnRadioOneDevice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL UpDateDataToDlg(NET_OUT_DIAGNOSIS_INFO *pstDoOut);
	BOOL InitOutDiagnosisInfo(NET_OUT_DIAGNOSIS_INFO **pstDoOut);
	void DeleteOutDiagnosisInfo(NET_OUT_DIAGNOSIS_INFO *pstDoOut);
	BOOL QueryPage(LLONG lFindHandle, int nPage, NET_OUT_DIAGNOSIS_INFO * pstDoOut);
private:
	CDateTimeCtrl       m_startDate;
	CDateTimeCtrl       m_startTime;
	CDateTimeCtrl       m_endDate;
	CDateTimeCtrl       m_endTime;

	//CComboBox           m_comboType;

	CListCtrl           m_lstResult;
	LLONG               m_lFindHandle;

	CProjectCfg*        m_pProject;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYDIAGNOSISRES_H__D6E7F312_C69B_4F2D_B6EC_B22F189278B4__INCLUDED_)
