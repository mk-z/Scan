#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CSetTimeDlg 对话框

class CSetTimeDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetTimeDlg)

public:
	CSetTimeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetTimeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SETTIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit				m_eIp;
	CEdit				m_eTime;
	CButton				m_StartNtp;
	CButton				m_StartSummer;
	CEdit				m_eTimeArea;
	CEdit				m_DeviceTime;
	CComboBox			m_DeviceHour;
	CComboBox			m_DeviceMinute;
	CComboBox			m_DeviceSecond;
	CDateTimeCtrl		m_DeviceDate;

	afx_msg void OnBnClickedButtongettime();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCheckNtp();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();


	int					ReFreshNtp();
	int					ReFreshTime();
private:
	JDeviceTimeExt		m_deviceTime;
	JDeviceNTPInfo		m_ntpInfo;
	
};
