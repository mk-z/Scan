#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CVideoTime 对话框

class CVideoTime : public CDialog
{
	DECLARE_DYNAMIC(CVideoTime)

public:
	CVideoTime(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVideoTime();

// 对话框数据
	enum { IDD = IDD_DIALOG_VIDEO_TIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comWeek;
	//CButton m_FullDay;
	CButton m_VideTime1;
	CButton m_VideoTime2;
	CButton m_VideoTime3;
	CButton m_VideoTime4;

	int m_iVideoTime1;
	int m_iVideoTime2;
	int m_iVideoTime3;
	int m_iVideoTime4;

	afx_msg void OnBnClickedCheckFullday();
	afx_msg void OnBnClickedCheckVideotime1();
	afx_msg void OnBnClickedCheckVideotime2();
	afx_msg void OnBnClickedCheckVideotime3();
	afx_msg void OnBnClickedCheckVideotime4();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboWeek();


	CDateTimeCtrl m_StartTime1;
	CDateTimeCtrl m_EndTime1;
	CDateTimeCtrl m_StartTime2;
	CDateTimeCtrl m_StartTime3;
	CDateTimeCtrl m_StartTime4;
	CDateTimeCtrl m_EndTime2;
	CDateTimeCtrl m_EndTime3;
	CDateTimeCtrl m_EndTime4;


	COleDateTime m_STime1;
	COleDateTime m_ETime1;

	COleDateTime m_STime2;
	COleDateTime m_ETime2;

	COleDateTime m_STime3;
	COleDateTime m_ETime3;

	COleDateTime m_STime4;
	COleDateTime m_ETime4;


	int m_iSelIndex;

	void EnableTimeCheck();
};
