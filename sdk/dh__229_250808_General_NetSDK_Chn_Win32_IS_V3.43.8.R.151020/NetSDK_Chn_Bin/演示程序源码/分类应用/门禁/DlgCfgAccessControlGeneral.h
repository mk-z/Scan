#if !defined(AFX_DLGCFGACCESSCONTROLGENERAL_H__ABE7F24E_EA3D_41A0_901C_816858095443__INCLUDED_)
#define AFX_DLGCFGACCESSCONTROLGENERAL_H__ABE7F24E_EA3D_41A0_901C_816858095443__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgAccessControlGeneral.h : header file
//

typedef struct tagAccessPropertyType
{
    CFG_ACCESS_PROPERTY_TYPE    emType;
    const char*                 szInfo;
}AccessPropertyType;

const AccessPropertyType stuDemoAccessProperty[] = {
    {CFG_ACCESS_PROPERTY_UNKNOWN, "Unknown"},
    {CFG_ACCESS_PROPERTY_BIDIRECT, "BiDirect"},
    {CFG_ACCESS_PROPERTY_UNIDIRECT, "UniDirect"},
};

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgAccessControlGeneral dialog

class CDlgCfgAccessControlGeneral : public CDialog
{
// Construction
public:
	CDlgCfgAccessControlGeneral(CWnd* pParent = NULL, LLONG lLoginID = 0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgAccessControlGeneral)
	enum { IDD = IDD_DLG_CFG_ACCESS_CONTROL_GENERAL };
	CComboBox	m_cmbAccessProperty;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgAccessControlGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgAccessControlGeneral)
	afx_msg void OnAccesscontrolGeneralBtnGet();
	afx_msg void OnAccesscontrolGeneralBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
    void InitDlg();
	BOOL SetConfigToDevice();
	BOOL GetConfigFromDevice();
	void DlgToStu();
	void StuToDlg();

private:
	LLONG					m_lLoginID;
	CFG_ACCESS_GENERAL_INFO	m_stuInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGACCESSCONTROLGENERAL_H__ABE7F24E_EA3D_41A0_901C_816858095443__INCLUDED_)
