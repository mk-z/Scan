#if !defined(AFX_ALARMSHOW_H__46D353D4_CA15_4647_9CB2_4C9AD42474B7__INCLUDED_)
#define AFX_ALARMSHOW_H__46D353D4_CA15_4647_9CB2_4C9AD42474B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmShow.h : header file
//
#include "ItemPanel.h"
/////////////////////////////////////////////////////////////////////////////
// CAlarmShow dialog
class CItemPanel;
class CAlarmShow : public CDialog
{
// Construction
public:
	CAlarmShow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmShow)
	enum { IDD = IDD_DIALOG_ALARMSHOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmShow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmShow)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CItemPanel	        m_Panel;

public:
	BOOL  ShowAlarmInfo(CString strFilePre, DEV_EVENT_FACERECOGNITION_INFO* pAlarmInfo);
	void  ClearShow();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMSHOW_H__46D353D4_CA15_4647_9CB2_4C9AD42474B7__INCLUDED_)
