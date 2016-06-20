#if !defined(AFX_DLGSUBDLGINFOPASSWORD_H__402A6816_6AA3_4460_B324_44D46ED7CA02__INCLUDED_)
#define AFX_DLGSUBDLGINFOPASSWORD_H__402A6816_6AA3_4460_B324_44D46ED7CA02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSubDlgInfoPassword.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSubDlgInfoPassword dialog

class CDlgSubDlgInfoPassword : public CDialog
{
// Construction
public:
	CDlgSubDlgInfoPassword(CWnd* pParent = NULL, NET_RECORDSET_ACCESS_CTL_PWD* p = NULL, int nAccess = 1);   // standard constructor
	
	void		SetOperateType(Em_RecordSet_Operate_Type emType) {m_emOperateType = emType;}
	
	void		SetInfo(const NET_RECORDSET_ACCESS_CTL_PWD* p) {	
		memcpy(&m_stuInfo, p, sizeof(NET_RECORDSET_ACCESS_CTL_PWD));}
	
	const NET_RECORDSET_ACCESS_CTL_PWD& GetInfo() const { return m_stuInfo;}

// Dialog Data
	//{{AFX_DATA(CDlgSubDlgInfoPassword)
	enum { IDD = IDD_SUBDLG_INFO_PASSWORD };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSubDlgInfoPassword)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSubDlgInfoPassword)
	afx_msg void OnSubdlgInfoPasswordBtnDoors();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitDlg();
	void StuToDlg();
	void DlgToStu();
	
	BOOL Get();
	BOOL Update();
	BOOL Remove();
	void Clear();
	
private:
	NET_RECORDSET_ACCESS_CTL_PWD	m_stuInfo;
    Em_RecordSet_Operate_Type		m_emOperateType;
    int                             m_nAccessGroup;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSUBDLGINFOPASSWORD_H__402A6816_6AA3_4460_B324_44D46ED7CA02__INCLUDED_)
