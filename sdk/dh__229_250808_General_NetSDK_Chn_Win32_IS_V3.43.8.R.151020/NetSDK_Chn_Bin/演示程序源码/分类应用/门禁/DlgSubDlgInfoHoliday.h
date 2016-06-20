#if !defined(AFX_DLGSUBDLGINFOHOLIDAY_H__427BF0EF_A4A3_484B_9AA2_DE5EA2F9F8E4__INCLUDED_)
#define AFX_DLGSUBDLGINFOHOLIDAY_H__427BF0EF_A4A3_484B_9AA2_DE5EA2F9F8E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSubDlgInfoHoliday.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoHoliday dialog

class CDlgSubDlgInfoHoliday : public CDialog
{
// Construction
public:
	CDlgSubDlgInfoHoliday(CWnd* pParent = NULL, NET_RECORDSET_HOLIDAY* p = NULL, int nAccess = 1);   // standard constructor
	
	void		SetOperateType(Em_RecordSet_Operate_Type emType) {m_emOperateType = emType;}
	
	void		SetInfo(const NET_RECORDSET_HOLIDAY* p) {	
		memcpy(&m_stuInfo, p, sizeof(NET_RECORDSET_HOLIDAY));}
	
	const NET_RECORDSET_HOLIDAY& GetInfo() const { return m_stuInfo;}

// Dialog Data
	//{{AFX_DATA(CDlgSubDlgInfoHoliday)
	enum { IDD = IDD_SUBDLG_INFO_HOLIDAY };
	CDateTimeCtrl	m_StartDate;
	CDateTimeCtrl	m_EndDate;
	CButton	m_ckEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSubDlgInfoHoliday)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSubDlgInfoHoliday)
	virtual BOOL OnInitDialog();
	afx_msg void OnSubdlgInfoHolidayButtonDoors();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitDlg();
	void StuToDlg();
	void DlgToStu();
	
private:
	NET_RECORDSET_HOLIDAY	        m_stuInfo;
    Em_RecordSet_Operate_Type		m_emOperateType;
    int                             m_nAccessGroup;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSUBDLGINFOHOLIDAY_H__427BF0EF_A4A3_484B_9AA2_DE5EA2F9F8E4__INCLUDED_)
