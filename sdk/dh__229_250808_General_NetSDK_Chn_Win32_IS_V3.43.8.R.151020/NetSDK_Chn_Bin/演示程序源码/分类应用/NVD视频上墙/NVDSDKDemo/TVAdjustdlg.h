#if !defined(AFX_TVADJUSTDLG_H__958B696E_86CB_4B4A_96DA_9D3996E8F94B__INCLUDED_)
#define AFX_TVADJUSTDLG_H__958B696E_86CB_4B4A_96DA_9D3996E8F94B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TVAdjustdlg.h : header file
//
#include "dhnetsdk.h"
/////////////////////////////////////////////////////////////////////////////
// CTVAdjustdlg dialog

class CTVAdjustdlg : public CDialog
{
// Construction
public:
	CTVAdjustdlg(CWnd* pParent = NULL);   // standard constructor

	void SetDlgParam(LLONG lLoginID, int nDevChannel);


// Dialog Data
	//{{AFX_DATA(CTVAdjustdlg)
	enum { IDD = IDD_DIALOG_TV_ADJUST };
	CComboBox	m_ctlDecTV;
	CSliderCtrl	m_slider_botton;
	CSliderCtrl	m_slider_right;
	CSliderCtrl	m_slider_left;
	CSliderCtrl	m_slider_top;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTVAdjustdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTVAdjustdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcaptureSliderTop(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderLeft(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderRight(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderBotton(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCombo1();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nDecChannel;
	LLONG m_hCurLoginID;
	int m_nCurTvID;
	DHDEV_TVADJUST_CFG *m_stuTvAdjustInfo;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TVADJUSTDLG_H__958B696E_86CB_4B4A_96DA_9D3996E8F94B__INCLUDED_)
