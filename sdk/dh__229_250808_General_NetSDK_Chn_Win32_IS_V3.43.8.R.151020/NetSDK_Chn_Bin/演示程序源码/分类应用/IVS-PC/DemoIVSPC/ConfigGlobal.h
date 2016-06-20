#if !defined(AFX_CONFIGGLOBAL_H__B65DAC46_5353_45D7_9CC9_76046D91201C__INCLUDED_)
#define AFX_CONFIGGLOBAL_H__B65DAC46_5353_45D7_9CC9_76046D91201C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIvsGlobalPreview;

class CConfigGlobal : public CDialog
{
public:
	CConfigGlobal(CWnd* pParent = NULL);   // standard constructor

	//获取设备全局配置后初始化界面
	void InitGlobalDlg(int nChannel);
	//登出设备或退出窗口时清理界面
	void UninitGlobalDlg();
	void ShowPreview(LONG lLoginHanlde, int nChannel);
	void ClosePreview(LONG lRealPlayHandle);

	enum { IDD = IDD_CONFIG_GLOBAL };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//{{AFX_MSG(CConfigGlobal)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCfggloCmbScene();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnZoneDone(WPARAM, LPARAM);
	afx_msg void OnCfggloBtnGet();
	afx_msg void OnCfggloBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedCfggloBtnRedraw();
	afx_msg void OnBnClickedCfggloBtnReset();
	afx_msg void OnBnClickedBtnHorLine();

private:
	CEdit		m_edtChnName;
	CComboBox	m_cmbScene;
	COLORREF	m_colorPen;
	CIvsGlobalPreview* m_pIvsGlobalPreview;

};

#endif // !defined(AFX_CONFIGGLOBAL_H__B65DAC46_5353_45D7_9CC9_76046D91201C__INCLUDED_)
