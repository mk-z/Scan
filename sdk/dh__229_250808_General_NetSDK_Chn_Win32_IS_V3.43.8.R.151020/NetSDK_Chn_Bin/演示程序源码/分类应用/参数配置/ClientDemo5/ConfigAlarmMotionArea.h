#if !defined(AFX_CONFIGALARMMOTIONAREA_H__3DA25876_BE0B_4847_9843_4F9E62F60406__INCLUDED_)
#define AFX_CONFIGALARMMOTIONAREA_H__3DA25876_BE0B_4847_9843_4F9E62F60406__INCLUDED_

#include "dhnetsdk.h"
#include "ConfigAlarmMotionAreaBlock.h"
#include "AreaDraw.h"
#include <list>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigAlarmMotionArea.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarmMotionArea dialog

class CConfigAlarmMotionArea : public CDialog
{
// Construction
public:
	CConfigAlarmMotionArea(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigAlarmMotionArea)
	enum { IDD = IDD_CONFIG_ALARM_MOTION_AREA };
	CComboBox	m_DetectId;
	int		m_nAreaThreshold;
	int		m_nSensitivity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigAlarmMotionArea)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigAlarmMotionArea)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonAddrect();
	afx_msg void OnButtonDelrect();
	afx_msg void OnSelchangeComboDetectId();
	afx_msg void OnDropdownComboDetectId();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    void SetMaxMotionWindow(int nMaxWindow);
 
	//void SetArea(BYTE *area, WORD wRows, WORD wCols);
	void SetArea(CFG_MOTION_INFO* pMotionInfo);
	//BYTE *GetArea(){return (BYTE*)m_myArea;}
	void RecordPoint(BYTE x, BYTE y);
	void ReleasePoint();
	void MovePoint(DWORD dwParm, BYTE x, BYTE y);

	void ShowParam(const CFG_MOTION_WINDOW& stuMotionWnd);

    void InitComboDetectId();

    void ShowRegionInfo();
    void RetrieveRegionInfo();
private:
	CConfigAlarmMotionAreaBlock m_block[DH_MOTION_ROW][DH_MOTION_COL];
    WORD			m_wRows;
	WORD			m_wCols;
	int				m_blckWid;
	int				m_blckHght;
	
	BOOL			m_bDrawing;
	POINT			m_stpoint;
	POINT			m_lastpoint;

	CFG_MOTION_INFO*	m_pMotionInfo;
    int     m_nMaxMotionWindow;
	//CAreaDraw		m_dlgAreaDraw;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGALARMMOTIONAREA_H__3DA25876_BE0B_4847_9843_4F9E62F60406__INCLUDED_)
