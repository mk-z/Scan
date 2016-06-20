#if !defined(AFX_PANNELDECODER_H__1F8B9818_6DDA_4B18_B3D6_48881D76DE19__INCLUDED_)
#define AFX_PANNELDECODER_H__1F8B9818_6DDA_4B18_B3D6_48881D76DE19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PannelDecoder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPannelDecoder dialog

class CPannelDecoder : public CDialog
{
// Construction
public:
	CPannelDecoder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPannelDecoder)
	enum { IDD = IDD_PANNEL_DECODER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPannelDecoder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	afx_msg void OnBtnDelDecoder();
protected:

	// Generated message map functions
	//{{AFX_MSG(CPannelDecoder)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAddDecoder();
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnAudiotalk();
	afx_msg void OnBtnTour();
	afx_msg void OnBntVideoout();
	afx_msg void OnBntChannelState();
	afx_msg void OnBntTvAdjust();
	afx_msg void OnBntTourCfg();
	afx_msg void OnButtonEncoderInfo();
	afx_msg void OnButtonDecodepolicy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANNELDECODER_H__1F8B9818_6DDA_4B18_B3D6_48881D76DE19__INCLUDED_)
