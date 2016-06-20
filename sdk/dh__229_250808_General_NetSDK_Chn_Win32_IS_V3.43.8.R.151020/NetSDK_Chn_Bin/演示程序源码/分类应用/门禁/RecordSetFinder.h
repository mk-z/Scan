#if !defined(AFX_RECORDSETFINDER_H__10AFF1A7_C4AC_433F_A798_D5735112F8C5__INCLUDED_)
#define AFX_RECORDSETFINDER_H__10AFF1A7_C4AC_433F_A798_D5735112F8C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordSetFinder.h : header file
//

typedef enum tagDataType
{
	DataType_Card = 0,
	DataType_Password,
	DataType_Access,
// 	DataType_Holiday,
}DataType;

typedef struct tagDemoDataType 
{
	DataType	emType;
	const char*	szName;
}DemoDataType;

const DemoDataType stuDemoDataType[] = 
{
	{DataType_Card, "Card"},
	{DataType_Password, "Password"},
	{DataType_Access, "Access"},
// 	{DataType_Holiday, "Holiday"},  // do not support by BSC
};

/////////////////////////////////////////////////////////////////////////////
// CRecordSetFinder dialog

class CRecordSetFinder : public CDialog
{
// Construction
public:
	CRecordSetFinder(CWnd* pParent = NULL, LLONG lLoginID = 0, int nAccess = 1);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecordSetFinder)
	enum { IDD = IDD_DLG_RECORDSET_FINDER };
	CComboBox	m_cmbResult;
	CComboBox	m_cmbDataType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordSetFinder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRecordSetFinder)
	virtual BOOL OnInitDialog();
    afx_msg void OnRecordsetfinderBtnQueryStart();
    afx_msg void OnRecordsetfinderBtnQueryNext();
	afx_msg void OnRecordsetfinderBtnQueryStop();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeRecordsetfinderCmbResult();
	afx_msg void OnSelchangeRecordsetfinderCmbDatatype();
	afx_msg void OnRecordsetfinderBtnCount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitDlg();
	void ClearResult();

	// card ==>IDD_SUBDLG_INFO_CARD(CSubDlgInfoCard),22xx
	BOOL QueryCard();
	void RecordSetFind_Card(LLONG lLoginId, LLONG& lFinderId);
	int  RecordSetFindNext_Card(LLONG lFinderId);
	void ShowCard(NET_RECORDSET_ACCESS_CTL_CARD* pInfo);

	// pwd ==>IDD_SUBDLG_INFO_PASSWORD(?),23xx
	BOOL QueryPwd();
	void RecordSetFind_Pwd(LLONG lLoginId, LLONG& lFinderId);
	int  RecordSetFindNext_Pwd(LLONG lFinderId);
	void ShowPwd(NET_RECORDSET_ACCESS_CTL_PWD* pInfo);

	// cardrec ==>IDD_SUBDLG_INFO_ACCESS(?),24xx
	BOOL QueryCardRec();
	void RecordSetFind_CardRec(LLONG lLoginId, LLONG& lFinderId);
	int  RecordSetFindNext_CardRec(LLONG lFinderId);
	void ShowCardRec(NET_RECORDSET_ACCESS_CTL_CARDREC* pInfo);
	
	// holiday ==>IDD_SUBDLG_INFO_HOLIDAY(?),25xx
    /*
	BOOL QueryHoliday();
	void RecordSetFind_Holiday(LLONG lLoginId, LLONG& lFinderId);
	void RecordSetFindNext_Holiday(LLONG lFinderId);
	void ShowHoliday(NET_RECORDSET_HOLIDAY* pInfo);
    */


private:
	LLONG		m_lLoginID;
    LLONG       m_lFinder;
    int         m_nStartSeq;
    DataType	m_emDataType;
    int         m_nAccessGroup;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDSETFINDER_H__10AFF1A7_C4AC_433F_A798_D5735112F8C5__INCLUDED_)
