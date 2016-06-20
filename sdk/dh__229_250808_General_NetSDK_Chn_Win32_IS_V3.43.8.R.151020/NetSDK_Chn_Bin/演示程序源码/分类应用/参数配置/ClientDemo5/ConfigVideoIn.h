#if !defined(AFX_CONFIGVIDEOIN_H__6FA3A58D_0244_4737_8D94_BD2C782AB87A__INCLUDED_)
#define AFX_CONFIGVIDEOIN_H__6FA3A58D_0244_4737_8D94_BD2C782AB87A__INCLUDED_
#include "dhnetsdk.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigVideoIn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigVideoIn dialog

class CConfigVideoIn : public CDialog
{
// Construction
public:
	CConfigVideoIn(CWnd* pParent = NULL);   // standard constructor
	void CleanAll();
	CFG_VIDEO_IN_OPTIONS *m_pstVideoInOption;
	CFG_CAP_VIDEOINPUT_INFO *m_pstCapVideoInput;
	void InitDlgInfo(int nChannelCount);
	void SaveChannelInfo(int nNum);
	BOOL SaveOptionInfo(int nNum,int nItem);
	void ShowOptionInfo(int nNum,int nItem);
// Dialog Data
	//{{AFX_DATA(CConfigVideoIn)
	enum { IDD = IDD_CONFIG_VIDEOIN };
	CComboBox	m_ctlBlackLightMode;
	CComboBox	m_ctlOptionSwitch;
	CButton	m_ctlIrisAuto;
	CButton	m_ctlMirror;
	CButton	m_ctlFlip;
	CComboBox	m_ctlRotate;
	CComboBox	m_ctlDayNightColor;
	CComboBox	m_ctlWhiteBalance;
	CComboBox	m_ctlExpMode;
	CComboBox	m_ctlAntiFliker;
	CComboBox	m_ctlOptionType;
	CComboBox	m_ctlChannel;
	int		m_GainMin;
	int		m_GainMax;
	float	m_ExpMax;
	float	m_ExpMin;
	int		m_ExpSpeed;
	int		m_GainBule;
	int		m_GainRed;
	int		m_StartHour;
	int		m_StartMinute;
	int		m_StartSecond;
	int		m_EndHour;
	int		m_EndMinute;
	int		m_EndSecond;
	int		m_Left;
	int		m_Right;
	int		m_Bottom;
	int		m_Top;
	int		m_WideDynamicRange;
	int		m_GlareInhiBition;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigVideoIn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigVideoIn)
	afx_msg void OnButtonSave();
	afx_msg void OnButtonReadall();
	afx_msg void OnSelchangeComboChanno();
	afx_msg void OnSelchangeComboOptiontype();
	afx_msg void OnSelchangeComboAntifliker();
	afx_msg void OnSelchangeComboExpmode();
	afx_msg void OnSelchangeComboOptionswitch();
	afx_msg void OnSelchangeComboBacklightmode();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nChannelCount;
	int m_nCurChannel;
	int m_nCurExpmode;
	int m_nCurTypeOption;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGVIDEOIN_H__6FA3A58D_0244_4737_8D94_BD2C782AB87A__INCLUDED_)
