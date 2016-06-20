#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDeviceState 对话框

class CDeviceState : public CDialog
{
	DECLARE_DYNAMIC(CDeviceState)

public:
	CDeviceState(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeviceState();

// 对话框数据
	enum { IDD = IDD_DIALOG_DEVICE_STATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox m_DeviceState;
	CComboBox m_LocalShow;
	CListCtrl m_ListDiskState;
	CListCtrl m_ListChannelState;
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();



	void ShowWndData();
	void ShowWndDataEnglish();

private:
	JDevWorkState m_DevWorkState;
};
