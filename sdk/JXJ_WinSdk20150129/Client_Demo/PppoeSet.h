#pragma once
#include "afxwin.h"


// CPppoeSet 对话框

class CPppoeSet : public CDialog
{
	DECLARE_DYNAMIC(CPppoeSet)

public:
	CPppoeSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPppoeSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_PPPOESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton			m_StartPPPOE;
	CComboBox		m_UseNetWork;
	CEdit			m_DeviceIp;
	CEdit			m_UserName;
	CEdit			m_Password;
	
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnClose();


	int					ReFreshWindow();

private:
	JPPPOEInfo			m_pppoeInfo;

};
