#if !defined(AFX_CONFIGMODULE_H__E406E9A3_20E2_498F_8B4F_2A2D9DC1D04E__INCLUDED_)
#define AFX_CONFIGMODULE_H__E406E9A3_20E2_498F_8B4F_2A2D9DC1D04E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigModule.h : header file
//
#define  MAX_CHANNEL_NUM 16

/////////////////////////////////////////////////////////////////////////////
// CConfigModule dialog

class CConfigModule : public CDialog
{
// Construction
public:
	CConfigModule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigModule)
	enum { IDD = IDD_CONFIG_MODULE };
	CComboBox	m_cbObjTypes;
//	CListCtrl	m_lcTrackRegion;
//	CListCtrl	m_lcDetecRegion;
//	CComboBox	m_cbModules;
	CComboBox	m_cbFilterType;
	CComboBox	m_cbChannel;
	BOOL	m_bSnapEnable;
	int		m_nMaxSizeWidth;
	int		m_nMinSizeWidth;
	int		m_nMaxSizeHight;
	int 	m_nMinSizeHight;
	int		m_nMaxSizeArea;
	int		m_nMinSizeArea;
	int		m_nDRX;
	int		m_nDRY;
	int		m_nTRX;
	int		m_nTRY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigModule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigModule)
	virtual BOOL OnInitDialog();
// 	afx_msg void OnButtonAdddrM();
// 	afx_msg void OnButtonAddtrM();
// 	afx_msg void OnButtonDeletdrM();
// 	afx_msg void OnButtonDelettrM();
	afx_msg void OnButtonRefreshM();
	afx_msg void OnButtonSaveM();
	afx_msg void OnSelchangeComboChannelM();
	afx_msg void OnSelchangeComboFiltertypeM();
//	afx_msg void OnSelchangeComboModulesM();
	afx_msg void OnButtonAddmod();
	afx_msg void OnButtonDeletselmod();
//	afx_msg void OnClickListDetectregM(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnClickListTrackregM(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnButtonSavedrM();
//	afx_msg void OnButtonSavetrM();
	afx_msg void OnButtonSetDetectregion();
	afx_msg void OnButtonSetTrackregion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nChannelCount;
	int m_nCurrentChannel;
	int m_nCurrentModule;
	int m_nCurrentDRLine;
	int m_nCurrentTRLine;

	CFG_ANALYSEMODULES_INFO m_gModules[MAX_CHANNEL_NUM];
	int m_nMaxModeuleNum;
	int m_nMaxPointOfRegion;
	int m_nSupportedObjTypeNum;
	char m_gObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // device supported object types

	void GetDevCapInfo();
	void Refresh();
	void ClearModuleInfo();
	void ClearList(CListCtrl* lcList);
	void SaveChannelModule(int nChannelId);
	void SaveModule(int nModuleId, CFG_ANALYSEMODULES_INFO &stuModuleInfo);
	void ShowChannelModule(int nChannelId);
	void ShowModule(int nModuleId, CFG_ANALYSEMODULES_INFO stuModuleInfo);

public:
	void Init(int nChannelCount);
	void Clear();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGMODULE_H__E406E9A3_20E2_498F_8B4F_2A2D9DC1D04E__INCLUDED_)
