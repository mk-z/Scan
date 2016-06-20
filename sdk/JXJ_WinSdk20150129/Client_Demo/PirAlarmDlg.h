#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CPirAlarmDlg 对话框

class CPirAlarmDlg : public CDialog
{
	DECLARE_DYNAMIC(CPirAlarmDlg)

public:
	CPirAlarmDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPirAlarmDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PIR_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton				m_enableAlarm;
	CComboBox			m_detectInterval;
	CComboBox			m_chooseWeek;
	CButton				m_allDay;
	CDateTimeCtrl		m_startTime1;
	CDateTimeCtrl		m_startTime2;
	CDateTimeCtrl		m_startTime3;
	CDateTimeCtrl		m_startTime4;
	CDateTimeCtrl		m_endTime1;
	CDateTimeCtrl		m_endTime2;
	CDateTimeCtrl		m_endTime3;
	CDateTimeCtrl		m_endTime4;
	CButton				m_enableTime1;
	CButton				m_enableTime2;
	CButton				m_enableTime3;
	CButton				m_enableTime4;


	
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnCbnSelchangeComboWeek();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck2();


	void			SaveTime();
	int				ReFreshWindow();


private:
	JPirAlarm		m_pirAlarmParam;
};
