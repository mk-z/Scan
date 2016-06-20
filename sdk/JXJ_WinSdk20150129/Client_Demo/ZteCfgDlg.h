#pragma once
#include "afxwin.h"


// CZteCfgDlg 对话框

class CZteCfgDlg : public CDialog
{
	DECLARE_DYNAMIC(CZteCfgDlg)

public:
	CZteCfgDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CZteCfgDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ZTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CButton			m_enableZTE;
	CEdit			m_id;
	CEdit			m_userName;
	CEdit			m_password;
	CEdit			m_ip;
	CEdit			m_port;

	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonSave();

	int				ReFreshWindow();
private:
	JZtePfCfg		m_ztePfCfg;

};
