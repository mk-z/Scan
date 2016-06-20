#pragma once
#include "afxwin.h"


// CUPNPSet 对话框

class CUPNPSet : public CDialog
{
	DECLARE_DYNAMIC(CUPNPSet)

public:
	CUPNPSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUPNPSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_UPNP_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CButton				m_StartUpnp;
	CComboBox			m_ShineType;
	CEdit				m_SerVerIp;
	CComboBox			m_NetCardShine;
	CEdit				m_DataPORT;
	CEdit				m_WebPort;
	CComboBox			m_UPNPUpdateTime;
	CEdit				m_UPNPCmdPort;
	CEdit				m_UPNPTalkPort;
	CEdit				m_DataStatus;
	CEdit				m_WebStatus;
	CEdit				m_CmdStatus;
	CEdit				m_TalkStatus;


	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();

	int						ReFreshWindow();
private:
	JUPNPParameter			m_upnpParam;
};
