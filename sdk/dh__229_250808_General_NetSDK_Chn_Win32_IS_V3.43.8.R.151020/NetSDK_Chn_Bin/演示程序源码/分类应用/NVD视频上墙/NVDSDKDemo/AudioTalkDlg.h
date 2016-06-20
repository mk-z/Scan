#if !defined(AFX_AUDIOTALKDLG_H__7BFB2BF2_EECA_4646_94E2_F2796D8E06C3__INCLUDED_)
#define AFX_AUDIOTALKDLG_H__7BFB2BF2_EECA_4646_94E2_F2796D8E06C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AudioTalkDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAudioTalkDlg dialog

class CAudioTalkDlg : public CDialog
{
// Construction
public:
	CAudioTalkDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAudioTalkDlg)
	enum { IDD = IDD_DLG_AUDIOTALK };
	CComboBox	m_ctlEncodeType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudioTalkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAudioTalkDlg)
	afx_msg void OnBtnStarttalk();
	afx_msg void OnBtnStoptalk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIOTALKDLG_H__7BFB2BF2_EECA_4646_94E2_F2796D8E06C3__INCLUDED_)
