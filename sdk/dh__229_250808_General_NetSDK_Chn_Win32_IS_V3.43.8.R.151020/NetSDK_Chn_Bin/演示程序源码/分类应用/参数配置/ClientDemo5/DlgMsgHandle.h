#if !defined(AFX_DLGMSGHANDLE_H__A6F06F77_7434_4C72_AF6A_EAFFE2BEA1CE__INCLUDED_)
#define AFX_DLGMSGHANDLE_H__A6F06F77_7434_4C72_AF6A_EAFFE2BEA1CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMsgHandle.h : header file
#include "DlgChn.h"
#include "dhnetsdk.h"
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgHandle dialog

//add by yu_peng
class CDlgMsgHandle : public CDialog
{
// Construction
public:
	CDlgMsgHandle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMsgHandle)
	enum { IDD = IDD_DIALOG_MSGHANDLE };
	BOOL	m_bLog;
	BOOL	m_bLocalPrompt;
	BOOL	m_bMatrix;
	BOOL	m_bMMS;
	BOOL	m_bAlarmOut;
	BOOL	m_bRecord;
	BOOL	m_bMail;
	BOOL	m_bSnap;
	BOOL	m_bTour;
	BOOL	m_bUpload;
	UINT	m_uMount;
	UINT	m_uEventLatch;
	UINT	m_uMatrixMask;
	UINT	m_uAlarmLatch;
	UINT	m_uRecLatch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMsgHandle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL InitChn();
	BOOL SetMsgHandle(const DH_MSG_HANDLE& stuMsgHandle, int nAlarmInCount, int nAlarmOutCount, int nChannelCount);
	BOOL GetMsgHandle(DH_MSG_HANDLE& stuMsgHandle);
	BOOL SetMsgHandleEx(const DH_MSG_HANDLE_EX& stuMsgHandle, int nAlarmInCount, int nAlarmOutCount, int nChannelCount);
	BOOL GetMsgHandleEx(DH_MSG_HANDLE_EX& stuMsgHandle);
	BOOL Attach(UINT uID, CDialog* pAttachDlg);
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMsgHandle)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDlgChn		m_chnAlarmOut;
	CDlgChn		m_chnRecord;
	CDlgChn		m_chnSnap;
	CDlgChn		m_chnTour;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMSGHANDLE_H__A6F06F77_7434_4C72_AF6A_EAFFE2BEA1CE__INCLUDED_)
