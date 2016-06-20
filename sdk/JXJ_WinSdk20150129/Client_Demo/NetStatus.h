#pragma once
#include "afxwin.h"


// CNetStatus 对话框

class CNetStatus : public CDialog
{
	DECLARE_DYNAMIC(CNetStatus)

public:
	CNetStatus(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNetStatus();

// 对话框数据
	enum { IDD = IDD_DIALOG_NET_CONNECT_STATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_LimitStatus;
	CComboBox m_WireLessStatus;
	CComboBox m_PppoeStatus;
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnClose();

	int		ReFreshWindow();


private:
	JNetworkStatus		m_netStatus;
};
