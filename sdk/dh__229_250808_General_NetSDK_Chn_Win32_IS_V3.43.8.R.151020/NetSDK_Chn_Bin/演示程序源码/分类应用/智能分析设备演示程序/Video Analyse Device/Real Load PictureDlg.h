// Real Load PictureDlg.h : header file
//

#if !defined(AFX_REALLOADPICTUREDLG_H__CB9F65CD_15BE_4771_8D68_C69302319271__INCLUDED_)
#define AFX_REALLOADPICTUREDLG_H__CB9F65CD_15BE_4771_8D68_C69302319271__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DialogEventRule.h"
#include "DialogPCQuery.h"
/////////////////////////////////////////////////////////////////////////////
// CRealLoadPictureDlg dialog

class CRealLoadPictureDlg : public CDialog
{
// Construction
public:
	CRealLoadPictureDlg(CWnd* pParent = NULL);	// standard constructor

	void DeletAlarmInfo(char *pGUID);

// Dialog Data
	//{{AFX_DATA(CRealLoadPictureDlg)
	enum { IDD = IDD_REALLOADPICTURE_DIALOG };
	CIPAddressCtrl	m_ipcIP;
	CString	m_csUserName;
	int		m_nPort;
	CString	m_csPassword;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealLoadPictureDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRealLoadPictureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonEventRule();
	afx_msg void OnButtonLogin();
	afx_msg void OnButtonLogout();
	afx_msg void OnButtonDataQuery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	CDialogEventRule m_dlgEventRule;
	CDialogPCQuery	 m_dlgPCQuery;

	LONG			 m_lLoginID;


private:
	//¶ÏÏß»Øµ÷
	static void __stdcall OnDisConnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
	afx_msg void OnClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALLOADPICTUREDLG_H__CB9F65CD_15BE_4771_8D68_C69302319271__INCLUDED_)
