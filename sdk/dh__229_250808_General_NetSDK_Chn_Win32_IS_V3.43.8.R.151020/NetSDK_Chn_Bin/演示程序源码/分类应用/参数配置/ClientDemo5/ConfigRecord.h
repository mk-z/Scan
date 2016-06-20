#if !defined(AFX_CONFIGRECORD_H__7A66C7FE_C5F7_451E_B4BA_F4E23BDADF6D__INCLUDED_)
#define AFX_CONFIGRECORD_H__7A66C7FE_C5F7_451E_B4BA_F4E23BDADF6D__INCLUDED_

#include "dhnetsdk.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigRecord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigRecord dialog

class CConfigRecord : public CDialog
{
// Construction
public:
	void CleanAll(bool bCleanRecodinfo = true);
	void InitDlgInfo(DHDEV_RECORD_CFG *pRecordInfo,int nChannelCount, int nProtoVer, BOOL bNewProtocol);
	CConfigRecord(CWnd* pParent = NULL);   // standard constructor
	BOOL InitRecordInfo();

// Dialog Data
	//{{AFX_DATA(CConfigRecord)
	enum { IDD = IDD_CONFIG_RECORD };
	CComboBox	m_ctlRecordType;
	CButton	m_ctlALM1;
	CButton	m_ctlALM2;
	CButton	m_ctlALM3;
	CButton	m_ctlALM4;
	CButton	m_ctlALM5;
	CButton	m_ctlALM6;
	CButton	m_ctlDTT1;
	CButton	m_ctlDTT2;
	CButton	m_ctlDTT3;
	CButton	m_ctlDTT4;
	CButton	m_ctlDTT5;
	CButton	m_ctlDTT6;
	CButton	m_ctlPRD6;
	CButton	m_ctlPRD5;
	CButton	m_ctlPRD4;
	CButton	m_ctlPRD3;
	CButton	m_ctlPRD2;
	CButton	m_ctlPRD1;
	CButton	m_ctlMA6;
	CButton	m_ctlMA5;
	CButton	m_ctlMA4;
	CButton	m_ctlMA3;
	CButton	m_ctlMA2;
	CButton	m_ctlMA1;
	CComboBox	m_ctlRecordWeek;
	CButton	m_ctlRedundancy;
	CComboBox	m_ctlChannel;
	UINT	m_prd1EndHour;
	UINT	m_prd1StartHour;
	UINT	m_prd1EndMinute;
	UINT	m_prd1StartMinute;
	UINT	m_prd1EndSecond;
	UINT	m_prd1StartSecond;
	UINT	m_prd2EndHour;
	UINT	m_prd2StartHour;
	UINT	m_prd2StartMinute;
	UINT	m_prd2EndSecond;
	UINT	m_prd3EndHour;
	UINT	m_prd3EndMinute;
	UINT	m_prd3StartMinute;
	UINT	m_prd3EndSecond;
	UINT	m_prd3StartSecond;
	UINT	m_prd4EndHour;
	UINT	m_prd4StartHour;
	UINT	m_prd4EndMinute;
	UINT	m_prd4StartMinute;
	UINT	m_prd4EndSecond;
	UINT	m_prd4StartSecond;
	UINT	m_prd2EndMinute;
	UINT	m_prd5EndHour;
	UINT	m_prd5StartHour;
	UINT	m_prd5EndMinute;
	UINT	m_prd5StartMinute;
	UINT	m_prd5EndSecond;
	UINT	m_prd5StartSecond;
	UINT	m_prd6EndHour;
	UINT	m_prd6StartHour;
	UINT	m_prd6EndMinute;
	UINT	m_prd6StartMinute;
	UINT	m_prd6EndSecond;
	UINT	m_prd6StartSecond;
	UINT	m_prd2StartSecond;
	UINT	m_prd3StartHour;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigRecord)
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	afx_msg void OnSelchangeComboChanno();
	afx_msg void OnSelchangeComboRecordweek();
	afx_msg void OnClickMA1();
	afx_msg void OnClickMA2();
	afx_msg void OnClickMA3();
	afx_msg void OnClickMA4();
	afx_msg void OnClickMA5();
	afx_msg void OnClickMA6();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowPeriodInfo(DH_TSECT *pTSect,BYTE nNum);
	BOOL SaveWeekInfo(int nNum,int nWeek);
	int m_nCurWeek;
	int m_nCurChannel;
	BOOL SaveChannelInfo(int nNum);
	DHDEV_RECORD_CFG *m_pRecordInfo;
	int m_nChannelCount;
	int	m_nProtoVer;
	BOOL m_bNewProtocol;
	bool IsWeekDataValid();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGRECORD_H__7A66C7FE_C5F7_451E_B4BA_F4E23BDADF6D__INCLUDED_)
