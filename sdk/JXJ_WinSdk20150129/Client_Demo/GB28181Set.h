#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGB28181Set 对话框

class CGB28181Set : public CDialog
{
	DECLARE_DYNAMIC(CGB28181Set)

public:
	CGB28181Set(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGB28181Set();

// 对话框数据
	enum { IDD = IDD_DIALOG_GB28181_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit		m_DEVid;
	CEdit		m_DEVpass;
	CEdit		m_SERVERid;
	CEdit		m_SERVERip;
	CEdit		m_SERVERport;
	CEdit		m_SERVERmsg;
	CEdit		m_channelID;
	CComboBox	m_channelNo;
	CListCtrl	m_channelIDlist;
	CEdit		m_SubItemEdit;

	
	

	
	afx_msg void OnCbnSelchangeComboChannelno();
	afx_msg void OnNMDblclkListChannelid(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusListChannelid(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditEditchannel();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnClose();



	BOOL		PreTranslateMessage(MSG* pMsg);
	void		SetListItemText(void);
	int			ReFreshWindow();
	int			ReFreshChannelCfgWindow();

private:
	
	int								m_listSelFlag[3];
	int								m_iSelChannel;
	CString							m_cstrItemTextEdit;
	JGB28181Proto					m_gb28181;
	JGB28181Proto_nvr_chann_cfg		m_gb28181ChannelCfg;
};
