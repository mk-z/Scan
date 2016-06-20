#if !defined(AFX_CONFIG_H__671E9A78_9831_4C57_AE51_731CBCE26F45__INCLUDED_)
#define AFX_CONFIG_H__671E9A78_9831_4C57_AE51_731CBCE26F45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ConfigGlobal.h"
#include "ConfigModule.h"
#include "ConfigRules.h"

class CConfig : public CDialog
{
// Construction
public:
	CConfig(CWnd* pParent = NULL);   // standard constructor

	void InitConfigDlg(int nChannel);
	void UninitConfigDlg();
	void ShowPreview();

	enum { IDD = IDD_CONFIG };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//{{AFX_MSG(CConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeConfigTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	typedef enum DlgType
	{
		DlgNone = 0,
		DlgConfigGlobal,
		DlgConfigModule,
		DlgConfigRule,
	};

	DlgType			m_currentDlg;
	CConfigGlobal	m_dlgConfigGlobal;
	CConfigModule	m_dlgConfigModule;
	CConfigRules	m_dlgConfigRules;
	CTabCtrl		m_tabConfig;
};

#endif // !defined(AFX_CONFIG_H__671E9A78_9831_4C57_AE51_731CBCE26F45__INCLUDED_)
