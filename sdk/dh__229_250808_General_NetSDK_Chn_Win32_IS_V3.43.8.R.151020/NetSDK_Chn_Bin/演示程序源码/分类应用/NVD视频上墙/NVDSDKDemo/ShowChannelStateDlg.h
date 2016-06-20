#if !defined(AFX_SHOWCHANNELSTATEDLG_H__D270845E_A633_4C90_8056_3672A453FD82__INCLUDED_)
#define AFX_SHOWCHANNELSTATEDLG_H__D270845E_A633_4C90_8056_3672A453FD82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowChannelStateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowChannelStateDlg dialog

class CShowChannelStateDlg : public CDialog
{
// Construction
public:
	CShowChannelStateDlg(CWnd* pParent = NULL);   // standard constructor
	void OnRefreshInfo();
	void SetDlgParam(int nDecChannel);

// Dialog Data
	//{{AFX_DATA(CShowChannelStateDlg)
	enum { IDD = IDD_DLG_CHANNEL_STATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowChannelStateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowChannelStateDlg)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nDecChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWCHANNELSTATEDLG_H__D270845E_A633_4C90_8056_3672A453FD82__INCLUDED_)
