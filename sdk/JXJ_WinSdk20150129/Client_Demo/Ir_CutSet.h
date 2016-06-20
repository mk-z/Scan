#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CIr_CutSet 对话框

class CIr_CutSet : public CDialog
{
	DECLARE_DYNAMIC(CIr_CutSet)

public:
	CIr_CutSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIr_CutSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_IRCUT_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CButton				m_Radio1;
	CButton				m_Radio2;
	CButton				m_Radio3;
	CComboBox			m_Sensitive;
	CButton				m_Start1;
	CDateTimeCtrl		m_StartTime1;
	CDateTimeCtrl		m_EndTime1;
	CButton				m_Start2;
	CDateTimeCtrl		m_StartTime2;
	CDateTimeCtrl		m_EndTime2;
	CButton				m_Start3;
	CDateTimeCtrl		m_StartTime3;
	CDateTimeCtrl		m_EndTime3;
	CButton				m_Start4;
	CDateTimeCtrl		m_StartTime4;
	CDateTimeCtrl		m_EndTime4;
	CComboBox			m_SetColor;
	CComboBox			m_Model;


	afx_msg void OnBnClickedCheckStart1();
	afx_msg void OnBnClickedCheckStart2();
	afx_msg void OnBnClickedCheckStart3();
	afx_msg void OnBnClickedCheckStart4();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();

	int ReFreshWindow();

private:

	JIrcutCtrl			m_IrcutCtrl;
};
