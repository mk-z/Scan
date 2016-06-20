#pragma once
#include "afxwin.h"


// CHxhtConfig 对话框

class CHxhtConfig : public CDialog
{
	DECLARE_DYNAMIC(CHxhtConfig)

public:
	CHxhtConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHxhtConfig();

// 对话框数据
	enum { IDD = IDD_DIALOG_HXHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	CEdit			m_eDevicePuid;
	CEdit			m_eServerAddr;
	CEdit			m_eServerPort;
	CEdit			m_eVideoPort;
	CEdit			m_eAudioPort;
	CEdit			m_eMessagePort;
	CEdit			m_ePlayBackPort;
	CEdit			m_eMaxVideoCount;
	CComboBox		m_bVideoStreamMode;
	CButton			m_bCheckEnablePicture;
	CButton			m_bCheckAudioSerPort;
	CComboBox		m_bNat;


	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();

	int ReFreshWindow();

private:
	JHxhtPfConfig		m_HxhtConfig;
};
