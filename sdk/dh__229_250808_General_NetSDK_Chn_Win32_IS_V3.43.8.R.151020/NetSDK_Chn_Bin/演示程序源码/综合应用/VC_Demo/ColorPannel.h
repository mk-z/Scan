#if !defined(AFX_COLORPANNEL_H__6426C918_2630_42B4_8BC1_AB6E6C29309B__INCLUDED_)
#define AFX_COLORPANNEL_H__6426C918_2630_42B4_8BC1_AB6E6C29309B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorPannel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorPannel dialog

class CColorPannel : public CDialog
{
// Construction
public:
	CColorPannel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CColorPannel)
	enum { IDD = IDD_PANNEL_COLOR };
	CSliderCtrl	m_slider_saturation;
	CSliderCtrl	m_slider_hue;
	CSliderCtrl	m_slider_contrast;
	CSliderCtrl	m_slider_bright;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPannel)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColorPannel)
	afx_msg void OnReleasedcaptureSliderBright(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderContrast(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderSaturtion(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderHue(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void UpdateVideoDisplay(int nMode, BYTE byPos);
private:
	CBrush m_myBrush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPANNEL_H__6426C918_2630_42B4_8BC1_AB6E6C29309B__INCLUDED_)
