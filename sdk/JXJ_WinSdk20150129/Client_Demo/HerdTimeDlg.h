#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CHerdTimeDlg 对话框

class CHerdTimeDlg : public CDialog
{
	DECLARE_DYNAMIC(CHerdTimeDlg)

public:
	CHerdTimeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHerdTimeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_HERDTIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_week;
	CButton m_fullDayEnable;
	CButton m_enable1;
	CButton m_enable2;
	CButton m_enable3;
	CButton m_enable4;
	CDateTimeCtrl m_startTime1;
	CDateTimeCtrl m_startTime2;
	CDateTimeCtrl m_startTime3;
	CDateTimeCtrl m_startTime4;
	CDateTimeCtrl m_endTime1;
	CDateTimeCtrl m_endTime2;
	CDateTimeCtrl m_endTime3;
	CDateTimeCtrl m_endTime4;
	afx_msg void OnBnClickedOk();
};
