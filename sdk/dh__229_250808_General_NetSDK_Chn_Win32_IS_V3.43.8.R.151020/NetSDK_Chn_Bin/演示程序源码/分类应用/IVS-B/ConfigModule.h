#if !defined(AFX_CONFIGMODULE_H__48401F85_A8CF_4435_BE09_66A1B86B2678__INCLUDED_)
#define AFX_CONFIGMODULE_H__48401F85_A8CF_4435_BE09_66A1B86B2678__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigModule.h : header file
//


const int nDetectZone = 1;
const int nExcludeZone = 2;

//模块检测区域列表
typedef struct tagMDTNodeType
{
	int	nNodeType;		//节点类型：检测区域，排除区域
}MDTNODETYPE;

typedef struct tagMTNode
{
	int			nNodeType;
	int			nPointCount;
	CFG_POLYGON	CfgPolygon[MAX_POLYGON_NUM];

	tagMTNode()
	{
		nNodeType = 0;
		nPointCount = 0;
		for (int i = 0; i < MAX_POLYGON_NUM; i++)
		{
			CfgPolygon[i].nX = 0;
			CfgPolygon[i].nY = 0;
		}
	}
}MTNODE;

class CIvsModulePreview;
/////////////////////////////////////////////////////////////////////////////
// CConfigModule dialog

class CConfigModule : public CDialog
{
private:
	BOOL	m_bAddDetectRegion;
	BOOL	m_bAddExcludeRegion;
	CIvsModulePreview* m_pIvsModulePreview;

private:
	void	clearTreeModuleList();
	void	clearTreeTrackRegion();

public:
	void initConfigModuleDlg(int nChannel);

	void uninitConfigModuleDlg();
	
	void showPreview(LONG lLoginHanlde, int nChannel);
	
	void closePreview(LONG lRealPlayHandle);
	
	static void _stdcall DrawIvsInfoModuleProc(long nPort,HDC hdc,LONG nUser);
	
	CFG_MODULE_INFO* getSelectModule();

public:
	friend class CDemoIVSbDlg;
	friend class CConfig;

// Construction
public:
	CConfigModule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigModule)
	enum { IDD = IDD_CONFIG_MODULE };
	CComboBox	m_cmbObjType;
	CButton	m_chkEnCapture;
	CComboBox	m_cmbBalance;
	CSliderCtrl	m_ctrlSlidSensi;
	CTreeCtrl	m_treeTrackRegion;
	CTreeCtrl	m_treeModuleList;
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
	afx_msg void OnCfgmodBtnAdddetec();
	afx_msg void OnCfgmodBtnAddexclud();
	afx_msg void OnCfgmodBtnAddmod();
	afx_msg void OnCfgmodBtnDelmod();
	afx_msg void OnCfgmodBtnDelregion();
	afx_msg void OnDestroy();
	afx_msg void OnCfgmodBtnGet();
	afx_msg void OnCfgmodBtnSet();
	afx_msg LRESULT OnRegionDone(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClickCfgmodTreeModlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickCfgmodTreeTrackregion(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCfgmodBtnRedraw();
	afx_msg void OnCfgmodBtnFilter();
	afx_msg void OnSelchangeCfgmodCmbBanlance();
	afx_msg void OnSelchangeCfgmodCmbObjtype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGMODULE_H__48401F85_A8CF_4435_BE09_66A1B86B2678__INCLUDED_)
