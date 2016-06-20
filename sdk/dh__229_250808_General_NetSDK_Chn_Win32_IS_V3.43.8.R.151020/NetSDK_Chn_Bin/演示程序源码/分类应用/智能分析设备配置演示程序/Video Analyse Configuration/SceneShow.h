#if !defined(AFX_SCENESHOW_H__B2B30BD8_3F20_48AF_B6B8_C1E1F907DABC__INCLUDED_)
#define AFX_SCENESHOW_H__B2B30BD8_3F20_48AF_B6B8_C1E1F907DABC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SceneShow.h : header file
//
#include "PictrueDialog.h"
#include "Common.h"
#include "DrawObject.h"
#include "dhnetsdk.h"

#define     PICTRUE_REAL_SIZE   8192
#define ROADLINE         "RoadLine"
#define PRELINE          "PreLine"
#define DETECTLINE       "DetectLine"
#define POSTLINE         "PostLine"
#define DETECTREGION     "DetectRegion"
#define TRACKREGION      "TrackRegion"
#define REDLIGHTREGION    "RedLightRegion"
#define STOPLINE         "StopLine"

#define isDrawSceneRoads   1
#define isDrawRules        2
#define isDrawModuleInfo   3


/////////////////////////////////////////////////////////////////////////////
// CSceneShow dialog

class CSceneShow : public CDialog
{
// Construction
public:
	CSceneShow(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CSceneShow)
	enum { IDD = IDD_SCENESHOW_DIALOG };
	CComboBox	m_cbDirection;
	int		m_nRoadId;
	int		m_nRadioId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSceneShow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSceneShow)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonRepaint();
	afx_msg void OnRadio1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LLONG m_lLoginId;
	LLONG m_lPlayHandle;
	int  m_nChannelId;
	int  m_nDrawType;
	int	 m_nSubDrawType;
	CString m_gPaintType[5];
	int m_nPaintTypeCount;
	int m_nSelectPaintType;
	int m_nDirection;
	CWnd* m_dlgSourceWindow;

	void GetProportion(CRect stuWindowSize);
	void GetSelectPaintType(int nIndex);
	void ClearRadioState();
public:
	CPictrueDialog m_stuPicShow;
	float m_fProportionX;      
	float m_fProportionY;

	void Init(int nDrawType,int nSubDrawType, long lLoginId, int nChannelId, CWnd* pWnd);
	void SetPaintType(int nTypeCount, CString* pTypeName);
	int GetRoadID() {return m_nRoadId;};
	int GetRoadDirection(){return m_nDirection;};
	
	friend void CALLBACK ChannelAutoDraw(LLONG lLoginID, LLONG lPlayHandle, HDC hDC, LDWORD dwUser);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCENESHOW_H__B2B30BD8_3F20_48AF_B6B8_C1E1F907DABC__INCLUDED_)
