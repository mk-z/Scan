#pragma once
#include "afxwin.h"


// CSystemMsgDlg 对话框

class CSystemMsgDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemMsgDlg)

public:
	CSystemMsgDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemMsgDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SYSTEMMSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit			m_eVender;
	CEdit			m_eOutTime;
	CEdit			m_eVersion;
	CEdit			m_eHardwareVersion;
	CEdit			m_eInNum;
	CEdit			m_eOutNum;
	CEdit			m_eChannelNum;
	CEdit			m_eRsNum485;
	CEdit			m_eRsNum232;
	CButton			m_bSave;
	CComboBox		m_cDeviceType;
	CComboBox		m_cMachineType;



	afx_msg void OnBnClickedButtonflash();
	afx_msg void OnClose();

	int					ReFreshWindow();
private:
	JDeviceInfo			m_Deviceinfo;
};
