#if !defined(AFX_DLGRECORDSETCONTROL_H__E89F5591_8E9A_487B_9751_B7A3772E6C1D__INCLUDED_)
#define AFX_DLGRECORDSETCONTROL_H__E89F5591_8E9A_487B_9751_B7A3772E6C1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordSetControl.h : header file
//

// set type
typedef struct tagDemoRecordSetType
{
	Em_RecordSet_Type	emType;
	const char*			szName;
}DemoRecordSetType;

const DemoRecordSetType stuDemoRecordSetType[] = 
{
	{Em_RecordSet_Type_Card,	"Card"},
	{Em_RecordSet_Type_Pwd,		"Password"},
	{Em_RecordSet_Type_Access,	"Access"},
	{Em_RecordSet_Type_Holiday, "Holiday"},
};

// control type
typedef struct tagDemoRecordSetCtlType
{
	Em_RecordSet_Operate_Type	emType;
	const char*					szName;
}DemoRecordSetCtlType;

const DemoRecordSetCtlType stuDemoRecordSetCtlType[] = 
{
	{Em_Operate_Type_Insert,	"Insert"},
	{Em_Operate_Type_Get,		"Get"},
	{Em_Operate_Type_Update,	"Update"},
	{Em_Operate_Type_Remove,	"Remove"},
	{Em_Operate_Type_Clear,		"Clear"},
	{Em_Operate_Type_InsertEX,	"InsertEX"},
	{Em_Operate_Type_UpdateEX,	"UpdateEX"},
};

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordSetControl dialog

class CDlgRecordSetControl : public CDialog
{
// Construction
public:
	CDlgRecordSetControl(CWnd* pParent = NULL, LLONG lLoginID = 0, int nAccess = 1);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordSetControl)
	enum { IDD = IDD_DLG_RECORDSET_CONTROL };
	CComboBox	m_cmbSetType;
	CComboBox	m_cmbCtlType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordSetControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordSetControl)
	virtual BOOL OnInitDialog();
	afx_msg void OnRecordsetCtlBtnExecute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void		InitDlg();
	
	//////////////////////////////////////////////////////////////////////////
	// Card
	//////////////////////////////////////////////////////////////////////////
	void		CardInsert();
	void		CardGet();
	void		CardUpdate();
	void		CardRemove();
	void		CardClear();
	
	//////////////////////////////////////////////////////////////////////////
	// Password
	//////////////////////////////////////////////////////////////////////////
	void		PwdInsert();
	void		PwdGet();
	void		PwdUpdate();
	void		PwdRemove();
	void		PwdClear();
	
	//////////////////////////////////////////////////////////////////////////
	// Access
	//////////////////////////////////////////////////////////////////////////
	void		AccessInsert();
	void		AccessGet();
	void		AccessUpdate();
	void		AccessRemove();
	void		AccessClear();
	
	//////////////////////////////////////////////////////////////////////////
	// Holiday
	//////////////////////////////////////////////////////////////////////////
	void		HolidayInsert();
	void		HolidayGet();
	void		HolidayUpdate();
	void		HolidayRemove();
	void		HolidayClear();

private:
    LLONG		m_lLoginID;
    int         m_nAccessGroup;
	Em_RecordSet_Operate_Type m_emOpType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDSETCONTROL_H__E89F5591_8E9A_487B_9751_B7A3772E6C1D__INCLUDED_)
