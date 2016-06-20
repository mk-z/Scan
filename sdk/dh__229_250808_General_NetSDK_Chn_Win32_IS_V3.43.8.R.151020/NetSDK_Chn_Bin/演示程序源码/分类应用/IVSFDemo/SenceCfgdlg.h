#if !defined(AFX_SENCECFGDLG_H__84C8C9F9_2EA7_4B7E_BC87_8B056C48ECDE__INCLUDED_)
#define AFX_SENCECFGDLG_H__84C8C9F9_2EA7_4B7E_BC87_8B056C48ECDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SenceCfgdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSenceCfgdlg dialog
class CIvsSceneDraw;
class CSenceCfgdlg : public CDialog
{
// Construction
public:
	CSenceCfgdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSenceCfgdlg)
	enum { IDD = IDD_DIALOG_CFG_SCENCE };
	double	m_dbCameraHight;
	int	    m_nFaceAngleDown;
	int 	m_nFaceAngleLeft;
	int 	m_nFaceAngleRight;
	int 	m_nFaceAngleUp;
	CString	m_strMaindirection1;
	CString	m_strMaindirection2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSenceCfgdlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSenceCfgdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonDraw();
	afx_msg void OnButtonDelete();
	afx_msg LRESULT OnZoneDone(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void            ShowSceneInfo(CFG_ANALYSEGLOBAL_INFO* pSenceInfo);
	BOOL            SaveSceneInfo(CFG_ANALYSEGLOBAL_INFO* pSenceInfo);
	void            SetPlayParam(BOOL bStart);
	int             GetPlayPort(void){ return m_nPort; }

private:
	int             m_nPort;
	CIvsSceneDraw*  m_pIvsSceneDraw;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENCECFGDLG_H__84C8C9F9_2EA7_4B7E_BC87_8B056C48ECDE__INCLUDED_)
