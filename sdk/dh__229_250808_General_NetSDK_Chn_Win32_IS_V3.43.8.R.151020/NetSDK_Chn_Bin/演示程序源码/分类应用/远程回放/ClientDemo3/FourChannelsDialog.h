#if !defined(AFX_FOURCHANNELSDIALOG_H__4780E05D_E01D_4BDE_989C_CFA5830E7B57__INCLUDED_)
#define AFX_FOURCHANNELSDIALOG_H__4780E05D_E01D_4BDE_989C_CFA5830E7B57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FourChannelsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFourChannelsDialog dialog

class CFourChannelsDialog : public CDialog
{
// Construction
public:
	CFourChannelsDialog(CWnd* pParent = NULL, int nChannelNum = 0);   // standard constructor
    void GetFourChannelsNumber(int &nChannelOne, int &nChannelTwo, int &nChannelThree, int &nChannelFour);
// Dialog Data
	//{{AFX_DATA(CFourChannelsDialog)
	enum { IDD = IDD_FOUR_CHANNELS_DIALOG };
	int		m_nChannelFour;
	int		m_nChannelOne;
	int		m_nChannelThree;
	int		m_nChannelTwo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFourChannelsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFourChannelsDialog)
	afx_msg void OnButtonOk();
	afx_msg void OnButtonCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    int m_nChannelNum;
    int m_nChannelOneValible;
    int m_nChannelTwoValible;
    int m_nChannelThreeValible;
    int m_nChannelFourValible;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOURCHANNELSDIALOG_H__4780E05D_E01D_4BDE_989C_CFA5830E7B57__INCLUDED_)
