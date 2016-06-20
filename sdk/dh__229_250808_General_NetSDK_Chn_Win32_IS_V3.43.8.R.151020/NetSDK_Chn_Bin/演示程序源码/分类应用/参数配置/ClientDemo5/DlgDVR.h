#if !defined(AFX_DLGDVR_H__0BE1B67A_144A_4D50_80BC_4A84BDFFF514__INCLUDED_)
#define AFX_DLGDVR_H__0BE1B67A_144A_4D50_80BC_4A84BDFFF514__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDVR.h : header file
//
#include "dhnetsdk.h"
#include "DlgMsgHandle.h"
#include "dhconfigsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDVR dialog

class CDlgDVR : public CDialog
{
// Construction
public:
	CDlgDVR(CWnd* pParent = NULL);   // standard constructor
	~CDlgDVR();
// Dialog Data
	//{{AFX_DATA(CDlgDVR)
	enum { IDD = IDD_DIALOG_DVR };
	BOOL	m_bIPColl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDVR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetLoginHandle(LONG lLogin, BOOL bNewProtocol){m_lLogin = lLogin; m_bNewProtocol = bNewProtocol;}
	void GetIPCollisionCfg();
	void SetIPCollisionCfg();
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDVR)
	afx_msg void OnButtonSave();
	afx_msg void OnButtonRead();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LLONG	m_lLogin;
	CDlgMsgHandle m_dlgMsgHandle;
	BOOL m_bNewProtocol;

	ALARM_IP_COLLISION_CFG m_stuIPCollCfg;//ip≥ÂÕª≈‰÷√
	CFG_IPCONFLICT_INFO *m_stuIPConflitInfo;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDVR_H__0BE1B67A_144A_4D50_80BC_4A84BDFFF514__INCLUDED_)
