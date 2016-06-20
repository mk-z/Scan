#if !defined(AFX_LOGIN_H__FA603AD0_C268_4383_8AA5_B9B59FA350D9__INCLUDED_)
#define AFX_LOGIN_H__FA603AD0_C268_4383_8AA5_B9B59FA350D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Login.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogin dialog

class CLogin : public CDialog
{
public:
	LLONG getLoginHandle()
	{
		return m_lLongHandle;
	}

	NET_DEVICEINFO* getNetDeviceInfo()
	{
		return &m_stuNetDevInfo;
	}
	
private:
	LLONG m_lLongHandle;
	NET_DEVICEINFO m_stuNetDevInfo;

// Construction
public:
	CLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogin)
	enum { IDD = IDD_LOGIN };
	CIPAddressCtrl	m_ctrlIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogin)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__FA603AD0_C268_4383_8AA5_B9B59FA350D9__INCLUDED_)
