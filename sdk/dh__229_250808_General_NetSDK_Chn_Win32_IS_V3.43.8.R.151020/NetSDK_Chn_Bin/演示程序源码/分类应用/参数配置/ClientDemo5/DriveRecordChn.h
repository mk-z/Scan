#if !defined(AFX_DRIVERECORDCHN_H__9DF1D93B_F51F_4C06_9809_7A041623DF83__INCLUDED_)
#define AFX_DRIVERECORDCHN_H__9DF1D93B_F51F_4C06_9809_7A041623DF83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DriveRecordChn.h : header file
//
#include "DlgChn.h"
/////////////////////////////////////////////////////////////////////////////
// DriveRecordChn dialog

class DriveRecordChn : public CDialog
{
// Construction
public:
	DriveRecordChn(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DriveRecordChn)
	enum { IDD = IDD_DIALOG_DRIVE_RECORD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DriveRecordChn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitDlgInfo();
	BOOL SetRecordMark(DWORD* pRecordMark, int nChannel);
	DWORD* GetRecordMark();

protected:

	// Generated message map functions
	//{{AFX_MSG(DriveRecordChn)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int         m_nChannel;         // total channel num
	CDlgChn     m_chnRecord[MAX_CHANNEL_COUNT];
	DWORD       m_RecordMark[MAX_CHANNEL_COUNT];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVERECORDCHN_H__9DF1D93B_F51F_4C06_9809_7A041623DF83__INCLUDED_)
