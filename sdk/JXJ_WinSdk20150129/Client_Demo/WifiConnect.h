#pragma once
#include "afxwin.h"


// CWifiConnect 对话框

class CWifiConnect : public CDialog
{
	DECLARE_DYNAMIC(CWifiConnect)

public:
	CWifiConnect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWifiConnect();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONNECT_WIFI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_WifiPassword;
	int m_WifiState;
	CString m_StrPassword;
	afx_msg void OnBnClickedOk();
};
