#if !defined(AFX_CHANNELONEDIALOG_H__F9E96260_CB87_4D96_9B82_15B52C957B5A__INCLUDED_)
#define AFX_CHANNELONEDIALOG_H__F9E96260_CB87_4D96_9B82_15B52C957B5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelOneDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChannelOneDialog dialog

class CChannelOneDialog : public CDialog
{
// Construction
public:
	CChannelOneDialog(CWnd* pParent = NULL, int nChannelNum = 0);   // standard constructor
    void GetOneChannelModeNumber(int &nChannelOne);
// Dialog Data
	//{{AFX_DATA(CChannelOneDialog)
	enum { IDD = IDD_ONE_CHANNEL_DIALOG };
	int		m_nChannelOne;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelOneDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChannelOneDialog)
	afx_msg void OnButtonOk();
	afx_msg void OnButtonCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    int m_nChannelNum;
    int m_nChannelOneValible;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELONEDIALOG_H__F9E96260_CB87_4D96_9B82_15B52C957B5A__INCLUDED_)
