#pragma once
#include "PerOscScreen.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CPeaOscCfg 对话框

class CPeaOscCfg : public CDialog
{
	DECLARE_DYNAMIC(CPeaOscCfg)

public:
	CPeaOscCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPeaOscCfg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PeaOsc };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	
	CButton			m_EnablePeaOsc;
	CComboBox		m_SceneType;
	CComboBox		m_TarGetLever;
	CButton			m_EnableTime1;
	CButton			m_EnableTime2;
	CButton			m_EnableTime3;
	CButton			m_EnableTime4;
	CDateTimeCtrl	m_StartTime1;
	CDateTimeCtrl	m_StartTime2;
	CDateTimeCtrl	m_StartTime3;
	CDateTimeCtrl	m_StartTime4;
	CDateTimeCtrl	m_EndTime1;
	CDateTimeCtrl	m_EndTime2;
	CDateTimeCtrl	m_EndTime3;
	CDateTimeCtrl	m_EndTime4;
	CComboBox		m_RuleId;
	CEdit			m_RuleName;
	CComboBox		m_RuleLever;
	CComboBox		m_RuleParam;
	CComboBox		m_cross;
	CButton			m_StartRule;
	CComboBox		m_ZjMode;
	CButton			m_UpLoadAlarm;


	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonjointaction();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedStarttime1();
	afx_msg void OnBnClickedStarttime2();
	afx_msg void OnBnClickedStarttime3();
	afx_msg void OnBnClickedStarttime4();
	afx_msg void OnCbnSelchangeComboRuleid();
	afx_msg void OnCbnSelchangeComboRuleid2();
	afx_msg void OnDestroy();

	void		SaveTime();
	int			ReFreshWindow();
	CPerOscScreen			m_peaoscScreen;

private:

	
	//JPeaOscCfg			m_PeaOscCfg;
	
	
};
