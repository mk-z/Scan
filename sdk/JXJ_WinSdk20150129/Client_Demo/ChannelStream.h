#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CChannelStream 对话框

class CChannelStream : public CDialog
{
	DECLARE_DYNAMIC(CChannelStream)

public:
	CChannelStream(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChannelStream();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHANNEL_STREAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CButton			m_StartAutoStream;
	CButton			m_StreamStart1;
	CButton			m_StreamStart2;
	CButton			m_StreamStart3;
	CButton			m_StreamStart4;
	CComboBox		m_ReplaceType;
	CComboBox		m_StreamType;
	CEdit			m_StreamHigh;
	CEdit			m_StreamLow;
	CEdit			m_SecondStreamHigh;
	CEdit			m_SecondStreamLow;
	CEdit			m_ThirdStreamHigh;
	CEdit			m_ThirdStreamLow;
	CDateTimeCtrl	m_StreamStartTime1;
	CDateTimeCtrl	m_StreamEndTime1;
	CDateTimeCtrl	m_StreamStartTime2;
	CDateTimeCtrl	m_StreamEndtime2;
	CDateTimeCtrl	m_StreamStartTime3;
	CDateTimeCtrl	m_StreamEndTime3;
	CDateTimeCtrl	m_StreamStartTime4;
	CDateTimeCtrl	m_StreamEndTime4;


	afx_msg void OnBnClickedCheckStart1();
	afx_msg void OnBnClickedCheckStart2();
	afx_msg void OnBnClickedCheckStart3();
	afx_msg void OnBnClickedCheckStart4();
	afx_msg void OnCbnSelchangeComboReplacetype();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();

	int ReFreshWindow();


private:
	JVencBitAutoSwitch	m_autoBit;
};
