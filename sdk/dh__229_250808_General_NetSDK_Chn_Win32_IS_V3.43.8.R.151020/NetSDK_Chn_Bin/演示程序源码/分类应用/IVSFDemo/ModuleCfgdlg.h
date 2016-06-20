#if !defined(AFX_MODULECFGDLG_H__F8446B1D_C547_458C_A56C_106522152BF3__INCLUDED_)
#define AFX_MODULECFGDLG_H__F8446B1D_C547_458C_A56C_106522152BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModuleCfgdlg.h : header file
//

class CTargetFilterPreview;
/////////////////////////////////////////////////////////////////////////////
// CModuleCfgdlg dialog

class CModuleCfgdlg : public CDialog
{
// Construction
public:
	CModuleCfgdlg(CWnd* pParent = NULL);   // standard constructor

public:
	void	ShowModuleInfo(CFG_ANALYSEMODULES_INFO* pModule, DWORD dwChannel);
	void	SaveModuleInfo(CFG_ANALYSEMODULES_INFO* pModule, DWORD dwChannel);

	void	ShowPreview(LLONG llLoginHandle, DWORD dwChannel);
	void	ClosePreview(LLONG llLoginHandle, DWORD dwChannel);

	void	SetNewPosition(CFG_ANALYSEMODULES_INFO* pModule);

	int    GetPlayPort(){ return m_nPort; }

public:
	int                  m_nPort;
	CTargetFilterPreview* m_pPreview;
	DWORD				m_dwChannel;
	CRITICAL_SECTION	m_csModule;
	CFG_ANALYSEMODULES_INFO* m_pModuleCfgInfo;
	LLONG				m_llRealPlayHandle;

// Dialog Data
	//{{AFX_DATA(CModuleCfgdlg)
	enum { IDD = IDD_DIALOG_CFG_MODULE };
	CSliderCtrl	m_ctrlSliderAccuracy;
	CSliderCtrl	m_ctrlSliderSensitivity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModuleCfgdlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModuleCfgdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnZoneDraw();
	afx_msg void OnBtnZoneClear();
	afx_msg void OnBtnWidthDraw();
	afx_msg void OnBtnWidthClear();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODULECFGDLG_H__F8446B1D_C547_458C_A56C_106522152BF3__INCLUDED_)
