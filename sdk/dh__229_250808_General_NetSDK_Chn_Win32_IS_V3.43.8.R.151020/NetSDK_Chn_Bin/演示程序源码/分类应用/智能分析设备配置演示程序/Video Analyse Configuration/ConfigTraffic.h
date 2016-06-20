#if !defined(AFX_CONFIGTRAFFIC_H__BF1A6B5C_FB1F_4B6F_8357_006C5701242C__INCLUDED_)
#define AFX_CONFIGTRAFFIC_H__BF1A6B5C_FB1F_4B6F_8357_006C5701242C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigTraffic.h : header file
//
#include "SceneShow.h"
#define MAX_CHANNEL_NUM 16

/////////////////////////////////////////////////////////////////////////////
// CConfigTraffic dialog

class CConfigTrafficScene : public CDialog
{
// Construction
public:
	CConfigTrafficScene(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CConfigTraffic)
	enum { IDD = IDD_CONFIG_TRAFFICSCENE };
	CListCtrl	m_clCarWayInfo;
	CComboBox	m_cbScene;
	CComboBox	m_cbChannel;
	double	m_dCameraDistance;
	double	m_dCameraHight;
	int		m_nFDPToCamDis;
	int		m_nFDPX;
	int		m_nFDPY;
	int		m_nNDPToCamsDis;
	int		m_nNDPX;
	int		m_nNDPY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigTraffic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConfigTraffic)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSaveT();
	afx_msg void OnButtonRefreshT();
	afx_msg void OnSelchangeComboChannelT();
	afx_msg void OnButtonAddroad();
	afx_msg void OnButtonChangeroad();
	afx_msg void OnButtonDeletroad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nChannelCount;
	int m_nCurrentChannel;
	int m_lLoginId;
	int m_nRePaintRoad;
	CString m_gDirection[8];

	void GetCannelObjTypes(void);
	void ShowTrafficSceneInfo(void);
	void ShowChannelScene(int nChannelId);
	void ShowCarWayInfo(CFG_ANALYSEGLOBAL_INFO &stuAnalysSceneInfo);
	void InsertRoadInfoToList(CFG_LANE* pLane, int nIndex);
	BOOL SaveChannelScene(int nChannelId);
	void SaveCarWayInfo(CFG_LANE* pLaneInfo, CSceneShow* pSceneShowDlg);
	int  GetSelectRoadItem();
	void SaveRoadInfoFromList(CFG_LANE &stuRoadInfo, int nIndex);
public:
	CFG_ANALYSEGLOBAL_INFO m_stuAnalysSceneInfo[MAX_CHANNEL_NUM];
	int  m_nSupportedSceneNum;
	char m_gSceneName[MAX_SCENE_LIST_SIZE][MAX_NAME_LEN];      // device supported scene types
	
	void Init(int nChannelCount);
	void Clear(void);
	void InPutExitLinesToPictur(CPictrueDialog* pPicShow, float fProportionX, float fProportionY);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGTRAFFIC_H__BF1A6B5C_FB1F_4B6F_8357_006C5701242C__INCLUDED_)
