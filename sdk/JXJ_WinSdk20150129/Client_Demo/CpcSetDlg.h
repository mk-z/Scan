#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "CpcScreen.h"

// CCpcSetDlg 对话框

class CCpcSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CCpcSetDlg)

public:
	CCpcSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCpcSetDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CPC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedStarttime1();
	afx_msg void OnBnClickedStarttime2();
	afx_msg void OnBnClickedStarttime3();
	afx_msg void OnBnClickedStarttime4();


	CCpcScreen	m_cpcScreen;

	CButton m_EnableTime1;
	CButton m_EnableTime2;
	CButton m_EnableTime3;
	CButton m_EnableTime4;
	CDateTimeCtrl m_startTime1;
	CDateTimeCtrl m_startTime2;
	CDateTimeCtrl m_startTime3;
	CDateTimeCtrl m_startTime4;
	CDateTimeCtrl m_endTime1;
	CDateTimeCtrl m_endTime2;
	CDateTimeCtrl m_endTime3;
	CDateTimeCtrl m_endTime4;
	CComboBox m_sensitivity;
	CComboBox m_maxCount;
	CEdit m_minSize;
	CEdit m_maxSize;
	CButton m_enabelRule;
	afx_msg void OnBnClickedButtonClear();
	CComboBox m_ruleID;

	void SaveTime();
	CButton m_EnableCpc;
	afx_msg void OnCbnSelchangeCombo3();
	CComboBox m_combo_res;
};
