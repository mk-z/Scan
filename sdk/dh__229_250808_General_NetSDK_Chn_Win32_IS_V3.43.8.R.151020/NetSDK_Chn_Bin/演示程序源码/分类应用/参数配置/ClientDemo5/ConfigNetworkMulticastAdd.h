#if !defined(AFX_CONFIGNETWORKMULTICASTADD_H__7836D3CD_B41E_4443_A8F5_11ECF789DFDA__INCLUDED_)
#define AFX_CONFIGNETWORKMULTICASTADD_H__7836D3CD_B41E_4443_A8F5_11ECF789DFDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigNetworkMulticastAdd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigNetworkMulticastAdd dialog

class CConfigNetworkMulticastAdd : public CDialog
{
// Construction
public:
	CConfigNetworkMulticastAdd(CWnd* pParent = NULL);   // standard constructor

	void InitDlg(DWORD dwChnCount);

public:
	CFG_MULTICAST_INFO* m_pInfo;
	int					m_nCastType;

// Dialog Data
	//{{AFX_DATA(CConfigNetworkMulticastAdd)
	enum { IDD = IDD_CONFIG_NETWORK_MULTICAST_ADD };
	CIPAddressCtrl	m_ctrlLocalIP;
	CIPAddressCtrl	m_ctrlHostIP;
	CButton	m_chkEnable;
	CComboBox	m_cmbChannel;
	CComboBox	m_cmbStreamType;
	CComboBox	m_cmbCastType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigNetworkMulticastAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigNetworkMulticastAdd)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DWORD	m_dwChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGNETWORKMULTICASTADD_H__7836D3CD_B41E_4443_A8F5_11ECF789DFDA__INCLUDED_)
