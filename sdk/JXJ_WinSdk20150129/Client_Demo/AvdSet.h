#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CAvdSet 对话框

class CAvdSet : public CDialog
{
	DECLARE_DYNAMIC(CAvdSet)

public:
	CAvdSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAvdSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_AVD_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	JAvdConfig		m_AvdConfig;
	int				m_iSaveIndex;
	int				m_iSaveIndexAll[MAX_IVS_AVD_RULES];
	int				m_iIfCheck[MAX_IVS_AVD_RULES];
	int				m_iLever[MAX_IVS_AVD_RULES];
	int				m_iWarnTime[MAX_IVS_AVD_RULES];



	


public:
	CButton			m_StartAvd;
	CComboBox		m_DiagnRule;
	CButton			m_IfCheck;
	CComboBox		m_Sensivity;
	CComboBox		m_WarningTime;
	CButton			m_Start1;
	CButton			m_Start2;
	CButton			m_start3;
	CButton			m_Start4;
	CDateTimeCtrl	m_StartData1;
	CDateTimeCtrl	m_SatrtData2;
	CDateTimeCtrl	m_SatrtData3;
	CDateTimeCtrl	m_SatrtData4;
	CDateTimeCtrl	m_EndData1;
	CDateTimeCtrl	m_EndData2;
	CDateTimeCtrl	m_EndData3;
	CDateTimeCtrl	m_EndData4;


	
	afx_msg void OnBnClickedCheckStart1();
	afx_msg void OnBnClickedCheckStart2();
	afx_msg void OnBnClickedCheckStart3();
	afx_msg void OnBnClickedCheckStart4();
	afx_msg void OnCbnSelchangeComboDiagnoserule();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();

	void		SetAvdRule();
	int			RefreshWindow();

};
