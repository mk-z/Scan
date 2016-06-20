#if !defined(AFX_CONFIGSERVER_H__26A6D1B1_1467_4D84_96FB_9DBD474A4A54__INCLUDED_)
#define AFX_CONFIGSERVER_H__26A6D1B1_1467_4D84_96FB_9DBD474A4A54__INCLUDED_

#include "dhnetsdk.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigServer dialog

class CConfigServer : public CDialog
{
// Construction
public:
	void CleanAll();
	//Initialize dialogue box
	void InitDlgInfo(DHDEV_SYSTEM_ATTR_CFG *pDevConfigInfo, int nChnCount);
	CConfigServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigServer)
	enum { IDD = IDD_CONFIG_SERVER };
	CComboBox	m_ctlTimeFormat;
	CComboBox	m_ctlDateSpr;
	CComboBox	m_ctlDateFormat;
	CComboBox	m_ctlVideoFormat;
	CComboBox	m_ctlDiskFull;
	UINT		m_nReclen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigServer)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsValid();
	void InitComboBox();
	CString GetDevType(NET_DEVICE_TYPE devType);
	BOOL CheckReclenValid();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGSERVER_H__26A6D1B1_1467_4D84_96FB_9DBD474A4A54__INCLUDED_)
