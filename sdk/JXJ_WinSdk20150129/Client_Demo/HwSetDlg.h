#pragma once
#include "afxwin.h"


// CHwSetDlg 对话框

class CHwSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CHwSetDlg)

public:
	CHwSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHwSetDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_HW_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	int			ReFreshWindow();

	CEdit		m_hwDeviceId;
	CEdit		m_hwDevicePwd;
	CEdit		m_localMsgPort;
	CEdit		m_hwServerIp;
	CEdit		m_hwServerAddr;
	CEdit		m_hwServerPort;
	CComboBox	m_ServerArea;

private:
	JHWPfCfg	m_hwcfg;
};
