#pragma once
#include "afxwin.h"


// CWarningUpload 对话框

class CWarningUpload : public CDialog
{
	DECLARE_DYNAMIC(CWarningUpload)

public:
	CWarningUpload(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWarningUpload();

// 对话框数据
	enum { IDD = IDD_DIALOG_WARNING_UPLOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton			m_StartWarningUpLoad;
	CEdit			m_WarningDeviceIp;
	CEdit			m_WarningDevicePort;
	CComboBox		m_WarningProtocolType;



	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnClose();

	
	int						ReFreshWindow();
private:
	JAlarmUploadCfg			m_AlarmUploadCfg;
};
