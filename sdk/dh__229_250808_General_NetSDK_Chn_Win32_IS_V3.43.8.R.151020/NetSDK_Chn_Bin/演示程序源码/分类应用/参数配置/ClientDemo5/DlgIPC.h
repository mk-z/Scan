#if !defined(AFX_DLGIPC_H__F722631E_FB1C_4E81_8F39_6D54840E92BB__INCLUDED_)
#define AFX_DLGIPC_H__F722631E_FB1C_4E81_8F39_6D54840E92BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPC.h : header file
//
#include "DlgMsgHandle.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgIPC dialog

//add by yu_peng
class CDlgIPC : public CDialog
{
// Construction
public:
	CDlgIPC(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIPC)
	enum { IDD = IDD_DIALOG_IPC };
	CComboBox	m_ccbMode;
	CComboBox	m_ccbEncode;
	CIPAddressCtrl	m_IPBlack;
	CComboBox	m_ccbType;
	CListBox	m_listWhite;
	CListBox	m_listSMS;
	CListBox	m_listEMS;
	CListBox	m_listDial;
	CListBox	m_listBlack;
	CIPAddressCtrl	m_IP;
	BOOL	m_bDial;
	BOOL	m_bEMS;
	BOOL	m_bList;
	BOOL	m_bSMS;
	CString	m_strRecv;
	CString	m_strCaller;
	CString	m_strSender;
	CString	m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetLoginHandle(LONG lLogin, BOOL bNewProtocol){m_lLogin = lLogin; m_bNewProtocol = bNewProtocol;}

	void GetTalkEncodeCfg();
	void SetTalkEncodeCfg();

	void GetMMSCfg();
	void SetMMSCfg();

	void GetSMSCfg();
	void SetSMSCfg();

	void GetDiaCfg();
	void SetDiaCfg();
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPC)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonRead();
	afx_msg void OnButtonEmsAdd();
	afx_msg void OnButtonEmsDelete();
	afx_msg void OnButtonSmsAdd();
	afx_msg void OnButtonSmsDelete();
	afx_msg void OnButtonDiaAdd();
	afx_msg void OnButtonDiaDelete();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnRadioWhite();
	afx_msg void OnRadioBlack();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnSelchangeComboMode();
	afx_msg void OnCloseupComboMode();
// 	afx_msg void OnEditchangeComboMode();
// 	afx_msg void OnEditupdateComboMode();
	afx_msg void OnButtonWhiteListBROW();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LLONG	m_lLogin;
	BOOL    m_bNewProtocol;

	DHDEV_IPIFILTER_CFG	m_stuIPFilterCfg;//ip过滤配置
	DHDEV_TALK_ENCODE_CFG m_stuTalkEncodeCfg;//语音对讲编码配置
	DHDEV_MMS_CFG	m_stuMMSCfg;//短信MMS配置
	DHDEV_SMSACTIVATION_CFG m_stuSMSCfg;//短信激活无线连接配置
	DHDEV_DIALINACTIVATION_CFG m_stuDiaCfg;//拨号激活无线连接配置

	BOOL	m_bWhite;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPC_H__F722631E_FB1C_4E81_8F39_6D54840E92BB__INCLUDED_)
