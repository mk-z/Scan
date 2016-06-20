#pragma once
#include "afxwin.h"


// CRtspServerDlg 对话框

class CRtspServerDlg : public CDialog
{
	DECLARE_DYNAMIC(CRtspServerDlg)

public:
	CRtspServerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRtspServerDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_RTSPSERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	CButton m_enable;
	CEdit m_rtspServerPort;


	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnEnChangeEdit1();


	
	int					ReFreshWindow();
private:
	JRtspSvrCfg			m_rtspParam;
};
