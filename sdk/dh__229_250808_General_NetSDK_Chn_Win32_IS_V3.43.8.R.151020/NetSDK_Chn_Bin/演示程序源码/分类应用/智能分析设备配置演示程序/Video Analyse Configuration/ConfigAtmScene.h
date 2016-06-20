#if !defined(AFX_CONFIGATMSCENE_H__FA9B0EA3_1A25_415F_8570_67AD65B26F0B__INCLUDED_)
#define AFX_CONFIGATMSCENE_H__FA9B0EA3_1A25_415F_8570_67AD65B26F0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigAtmScene.h : header file
//
#include "SceneShow.h"
#define MAX_CHANNEL_NUM 16

/////////////////////////////////////////////////////////////////////////////
// CConfigAtmScene dialog

class CConfigAtmScene : public CDialog
{
// Construction
public:
	CConfigAtmScene(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigAtmScene)
	enum { IDD = IDD_CONFIG_ATM_SCENE };
	CComboBox	m_cbChannel;
	CComboBox	m_cbScene;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigAtmScene)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigAtmScene)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonSaveT();
	afx_msg void OnButtonRefreshT();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboChannelT();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CFG_ANALYSEGLOBAL_INFO* m_stuAnalysSceneInfo[MAX_CHANNEL_NUM];
	int m_nChannelCount;
	int m_nCurrentChannel;
	int m_lLoginId;
	int  m_nSupportedSceneNum;
	char m_gSceneName[MAX_SCENE_LIST_SIZE][MAX_NAME_LEN];      // device supported scene types

public:
	void Clear(void);

	void Init(int nChannelCount);

	void GetCannelObjTypes();

	void ShowChannelScene(int nChannelId);
	void ShowTrafficSceneInfo();

	BOOL SaveChannelScene(int nChannelId);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGATMSCENE_H__FA9B0EA3_1A25_415F_8570_67AD65B26F0B__INCLUDED_)
