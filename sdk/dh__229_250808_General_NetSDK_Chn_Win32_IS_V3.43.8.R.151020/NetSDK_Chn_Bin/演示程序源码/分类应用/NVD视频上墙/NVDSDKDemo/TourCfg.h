#if !defined(AFX_TOURCFG_H__086CCFC8_1FCD_43A5_B580_8A9416A41F47__INCLUDED_)
#define AFX_TOURCFG_H__086CCFC8_1FCD_43A5_B580_8A9416A41F47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TourCfg.h : header file
//
#include "dhnetsdk.h"
/////////////////////////////////////////////////////////////////////////////
// CTourCfg dialog

class CTourCfg : public CDialog
{
// Construction
public:
	CTourCfg(CWnd* pParent = NULL);   // standard constructor
	void SetDlgParam(LLONG lLoginID, int nTourNum, int nDecChannel);

// Dialog Data
	//{{AFX_DATA(CTourCfg)
	enum { IDD = IDD_DLA_TOUR_CFG };
	CEdit		m_editRtspport;
	CEdit		m_editHttpport;
	CComboBox	m_ctlManufactory;
	CListCtrl	m_ctlTourCfgInfo;
	CComboBox	m_ctlType;
	CComboBox	m_ctlDecoderChannel;
	CComboBox	m_ctlChannelNo;
	UINT	m_nInterval;
	CString	m_strIP;
	UINT	m_nPort;
	CString	m_strPwd;
	CString	m_strUserName;
	int		m_nCtrlType;
	CString	m_strDecoderChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTourCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTourCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSave();
	afx_msg void OnQuery();
	afx_msg void OnClickListTourInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnDeleteAll();
	afx_msg void OnControl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LLONG m_hCurLoginID;
	int m_nDecChannel;
	int m_nTourNum;
	void SaveChannelInfo();
	void ShowChannelInfo();
	DHDEV_DECODER_TOUR_CFG m_stuTourCfgInfo;
	void InitComboManuFactory();
	bool ChangeManuFactoryToStr(UINT dwType, char *pOutBuf, UINT nOutBufLen);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOURCFG_H__086CCFC8_1FCD_43A5_B580_8A9416A41F47__INCLUDED_)
