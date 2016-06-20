#if !defined(AFX_DLGSUBDLGINFOACCESSRECORD_H__A8F05AE6_EFD7_4F76_852F_105E3A09FFE8__INCLUDED_)
#define AFX_DLGSUBDLGINFOACCESSRECORD_H__A8F05AE6_EFD7_4F76_852F_105E3A09FFE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSubDlgInfoAccessRecord.h : header file
//
typedef struct
{
	NET_ACCESS_DOOROPEN_METHOD		emMethod;
	char*							pszName;
}Demo_Method;
const Demo_Method stuDemoMethod[] = 
{
	{NET_ACCESS_DOOROPEN_METHOD_UNKNOWN, "UnKnown"},
	{NET_ACCESS_DOOROPEN_METHOD_PWD_ONLY, "Pwd_Only"},
	{NET_ACCESS_DOOROPEN_METHOD_CARD, "Card"},
	{NET_ACCESS_DOOROPEN_METHOD_CARD_FIRST, "CardFirst"},
	{NET_ACCESS_DOOROPEN_METHOD_PWD_FIRST, "PwdFirst"},
	{NET_ACCESS_DOOROPEN_METHOD_REMOTE, "Remote"},
    {NET_ACCESS_DOOROPEN_METHOD_BUTTON, "Button"},
    {NET_ACCESS_DOOROPEN_METHOD_FINGERPRINT, "FingerPrint"},
    {NET_ACCESS_DOOROPEN_METHOD_PWD_CARD_FINGERPRINT, "Pwd+Card+FingerPrint"},
    {NET_ACCESS_DOOROPEN_METHOD_PWD_FINGERPRINT, "Pwd+FingerPrint"},
    {NET_ACCESS_DOOROPEN_METHOD_CARD_FINGERPRINT, "Card+FingerPrint"},
	{NET_ACCESS_DOOROPEN_METHOD_PERSONS, "Persons"},
};

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoAccessRecord dialog

class CDlgSubDlgInfoAccessRecord : public CDialog
{
// Construction
public:
	CDlgSubDlgInfoAccessRecord(CWnd* pParent = NULL, NET_RECORDSET_ACCESS_CTL_CARDREC* p = NULL);   // standard constructor
	
	void		SetOperateType(Em_RecordSet_Operate_Type emType) {m_emOperateType = emType;}
	
	void		SetInfo(const NET_RECORDSET_ACCESS_CTL_CARDREC* p) {	
		memcpy(&m_stuInfo, p, sizeof(NET_RECORDSET_ACCESS_CTL_CARDREC));}
	
	const NET_RECORDSET_ACCESS_CTL_CARDREC& GetInfo() const { return m_stuInfo;}

// Dialog Data
	//{{AFX_DATA(CDlgSubDlgInfoAccessRecord)
	enum { IDD = IDD_SUBDLG_INFO_ACCESS };
	CDateTimeCtrl	m_Time;
	CDateTimeCtrl	m_Date;
	CComboBox	m_cmbMethod;
	CButton	m_ckStatus;
	CString	m_csCardNo;
	int		m_nDoorNo;
	CString	m_csPwd;
	int		m_nRecNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSubDlgInfoAccessRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSubDlgInfoAccessRecord)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitDlg();
	void StuToDlg();
	void DlgToStu();

private:
	NET_RECORDSET_ACCESS_CTL_CARDREC	m_stuInfo;
	Em_RecordSet_Operate_Type			m_emOperateType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSUBDLGINFOACCESSRECORD_H__A8F05AE6_EFD7_4F76_852F_105E3A09FFE8__INCLUDED_)
