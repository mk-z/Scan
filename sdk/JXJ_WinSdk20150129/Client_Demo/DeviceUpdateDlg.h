#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDeviceUpdateDlg 对话框

class CDeviceUpdateDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceUpdateDlg)

public:
	CDeviceUpdateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeviceUpdateDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DEVICE_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	static  DWORD ThreadFun(LPVOID lpThreadParameter);
	static  DWORD ControlThreadFun(LPVOID lpThreadParameter);
	afx_msg void OnBnClickedButtonOpenfile();
	afx_msg void OnBnClickedButtonUpdate();

	CString m_strPath;
	CEdit m_eShowFilePath;
	CProgressCtrl m_UpdateProgress;
	afx_msg void OnBnClickedButtonDeviceClose();
	afx_msg void OnBnClickedButtonOutAgain();
	afx_msg void OnBnClickedButtonMoren();
	afx_msg void OnBnClickedButtonDestroycheck();
	afx_msg void OnBnClickedButtonLightCheck();
	afx_msg void OnClose();

	//static int SetDeviceCallBack(struct _jcu_notify_cb_s *handle, jcu_cb_parm_t *parm);
	void UpdateEnable(bool bFlag);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	long	m_lUpgHandle;
};
