#pragma once
#include "resource.h"

// CMessageBoxDlg 对话框

class CMessageBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(CMessageBoxDlg)

public:
	CMessageBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMessageBoxDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();


	int m_iRet;
	CString m_strTitle;
	CString m_strMsg;

	void SetWndText(CString strTitle, CString strMsg);
};
