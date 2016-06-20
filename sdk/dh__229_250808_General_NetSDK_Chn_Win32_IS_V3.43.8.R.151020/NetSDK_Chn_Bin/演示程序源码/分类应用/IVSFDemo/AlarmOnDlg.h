#if !defined(AFX_ALARMONDLG_H__28ED0453_9B53_4C00_88A9_B0D1294299EA__INCLUDED_)
#define AFX_ALARMONDLG_H__28ED0453_9B53_4C00_88A9_B0D1294299EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmOnDlg.h : header file
//
class CIVSFDemoDlg;
/////////////////////////////////////////////////////////////////////////////
// CAlarmOnDlg dialog

class CAlarmOnDlg : public CDialog
{
// Construction
public:
	CAlarmOnDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmOnDlg)
	enum { IDD = IDD_DIALOG_ALARMON };
	CListCtrl	m_lsChannels;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmOnDlg)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmOnDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonSelall();
	afx_msg void OnButtonAntisel();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CAlarmOnDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	CIVSFDemoDlg*    m_pIVSDemoDlg;
	int              m_nChannelCount;
	int              m_gChannelSel[128];

public:
	void Init(int nChannelCount, CIVSFDemoDlg* pIVSFDemoDlg, LLONG* pChannelHandle);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMONDLG_H__28ED0453_9B53_4C00_88A9_B0D1294299EA__INCLUDED_)
