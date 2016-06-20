#if !defined(AFX_DLGCFGACCESSCONTROL_H__E772DB79_8418_4423_B6FF_0FBC23F3D9EA__INCLUDED_)
#define AFX_DLGCFGACCESSCONTROL_H__E772DB79_8418_4423_B6FF_0FBC23F3D9EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgAccessControl.h : header file
//

// 最大支持时间段==>对应CFG_ACCESS_TIMESCHEDULE_INFO配置
#define MAX_TIME_SECTION	(128)

// typedef struct tagOpenMethod 
// {
// 	CFG_DOOR_OPEN_METHOD	emOpenMethod;
// 	const char*				szName;
// }OpenMethod;
// 
// const OpenMethod stuDemoOpenMethod[] = 
// {
// 	{CFG_DOOR_OPEN_METHOD_UNKNOWN, "Unknown"},
// 	{CFG_DOOR_OPEN_METHOD_PWD_ONLY, "PwdOnly"},
// 	{CFG_DOOR_OPEN_METHOD_CARD, "Card"},
// 	{CFG_DOOR_OPEN_METHOD_PWD_OR_CARD, "PwdOrCard"},
// 	{CFG_DOOR_OPEN_METHOD_CARD_FIRST, "CardFirst"},
// 	{CFG_DOOR_OPEN_METHOD_PWD_FIRST, "PwdFirst"},
// 	{CFG_DOOR_OPEN_METHOD_SECTION, "TimeSection"},
// };

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgAccessControl dialog

class CDlgCfgAccessControl : public CDialog
{
// Construction
public:
	CDlgCfgAccessControl(CWnd* pParent = NULL, LLONG lLoginID = 0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgAccessControl)
	enum { IDD = IDD_DLG_CFG_ACCESSCONTROL };
	CButton	m_chkRemoteCheck;
	CButton	m_chkFirstEnterEnable;
	CComboBox	m_cbFirstEnterStatus;
	CComboBox	m_cmbChannel;
	CComboBox	m_cmbOpenTimeIndex;
	CComboBox	m_cmbOpenMethod;
	CButton	m_chkSensor;
	CButton	m_chkRepeatEnterAlarm;
	CButton	m_chkDuressAlarm;
	CButton	m_chkDoorNotCloseAlarm;
	CButton	m_chkBreakAlarm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgAccessControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgAccessControl)
	virtual BOOL OnInitDialog();
	afx_msg void OnAccessControlBtnTimeSection();
	afx_msg void OnAccessControlBtnGet();
	afx_msg void OnAccessControlBtnSet();
	afx_msg void OnSelchangeAccesscontrolCmbChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	void InitDlg();
	BOOL SetConfigToDevice();
	BOOL GetConfigFromDevice();
	void DlgToStu();
	void StuToDlg();

private:
	LLONG					m_lLoginID;
	CFG_ACCESS_EVENT_INFO	m_stuInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGACCESSCONTROL_H__E772DB79_8418_4423_B6FF_0FBC23F3D9EA__INCLUDED_)
