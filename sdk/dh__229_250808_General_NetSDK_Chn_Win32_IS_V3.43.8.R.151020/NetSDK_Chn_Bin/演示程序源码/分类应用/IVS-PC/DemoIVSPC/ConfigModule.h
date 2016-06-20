#if !defined(AFX_CONFIGMODULE_H__48401F85_A8CF_4435_BE09_66A1B86B2678__INCLUDED_)
#define AFX_CONFIGMODULE_H__48401F85_A8CF_4435_BE09_66A1B86B2678__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CIvsModulePreview;

class CConfigModule : public CDialog
{
public:
	CConfigModule(CWnd* pParent = NULL);   

	void InitConfigModuleDlg(int nChannel);
	void UninitConfigModuleDlg();
	void ShowPreview(LONG lLoginHanlde, int nChannel);
	void ClosePreview(LONG lRealPlayHandle);
	static void _stdcall DrawIvsInfoModuleProc(long nPort,HDC hdc,LONG nUser);
	CFG_MODULE_INFO* GetSelectModule();

	enum { IDD = IDD_CONFIG_MODULE };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//{{AFX_MSG(CConfigModule)
	virtual BOOL OnInitDialog();
	afx_msg void OnCfgmodBtnAdddetec();
	afx_msg void OnCfgmodBtnAddmod();
	afx_msg void OnCfgmodBtnDelmod();
	afx_msg void OnCfgmodBtnDelregion();
	afx_msg void OnDestroy();
	afx_msg void OnCfgmodBtnGet();
	afx_msg void OnCfgmodBtnSet();
	afx_msg LRESULT OnRegionDone(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClickCfgmodTreeModlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCfgmodBtnFilter();
	afx_msg void OnBnClickedCfgmodBtnRedraw();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void	clearTreeModuleList();
	void	clearTreeTrackRegion();
	void	EnableAddModuleOrDetect();

	CComboBox	m_cmbObjType;
	CButton		m_chkEnCapture;
	CSliderCtrl	m_ctrlSlidSensi;
	CTreeCtrl	m_treeTrackRegion;
	CTreeCtrl	m_treeModuleList;
	BOOL		m_bAddDetectRegion;
	CIvsModulePreview* m_pIvsModulePreview;
	// 是否允许增加模块
	bool		m_bAddModule;
	// 是否允许增加检测区
	bool		m_bAddDetect;
};

#endif // !defined(AFX_CONFIGMODULE_H__48401F85_A8CF_4435_BE09_66A1B86B2678__INCLUDED_)
