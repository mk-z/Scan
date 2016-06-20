#pragma once
#include "afxwin.h"


// CNetParam 对话框

class CNetParam : public CDialog
{
	DECLARE_DYNAMIC(CNetParam)

public:
	CNetParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNetParam();

// 对话框数据
	enum { IDD = IDD_DIALOG_NET_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox		m_NetWorkCarding;
	CEdit			m_SignPort;
	CEdit			m_DataPort;
	CEdit			m_WebPort;
	CComboBox		m_NetWorkType;
	CEdit			m_MacAddress;
	CButton			m_StartDhcp;
	CEdit			m_IpAddr;
	CEdit			m_ChildNet;
	CEdit			m_NetAddr;
	CButton			m_StartAtupDns;
	CEdit			m_MainDns;
	CEdit			m_BackUpDns;
	CButton			m_StartTerrace;
	CEdit			m_CmsAddr;
	CEdit			m_CmsPort;
	CEdit			m_MdsAddr;
	CEdit			m_MdsPort;
	CEdit			m_Puid;
	CEdit			m_TalkPort;
	CComboBox		m_TransProtocol;


	
	
	
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	int		     ReFreshWindow1();
	int		     ReFreshWindow2();


private:
	JPlatformInfo		m_platform;
	JNetworkInfo		m_networkinfo;
};
