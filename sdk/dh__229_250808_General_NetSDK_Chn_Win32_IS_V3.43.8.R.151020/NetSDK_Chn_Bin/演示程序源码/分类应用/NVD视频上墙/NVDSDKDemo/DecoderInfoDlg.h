#if !defined(AFX_DECODERINFODLG_H__AEBD9493_B9C7_4CD9_A540_9B7DA3D4C083__INCLUDED_)
#define AFX_DECODERINFODLG_H__AEBD9493_B9C7_4CD9_A540_9B7DA3D4C083__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DecoderInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDecoderInfoDlg dialog
#include "dhnetsdk.h"
#include <map>

class CDecoderInfoDlg : public CDialog
{
// Construction
public:
	CDecoderInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDecoderInfoDlg)
	enum { IDD = IDD_DIALOG_ENCODER_INFO };
	CComboBox	m_ccbWorkMode;
	CComboBox	m_ccbSnapMode;
	CComboBox	m_ccbStreamType;
	CComboBox	m_ccbProtocolType;
	CComboBox	m_ccbFactory;
	CComboBox	m_ccbEncoderNum;
	CComboBox	m_ccbDeviceType;
	CComboBox	m_ccbConnectType;
	UINT	m_nChannel;
	CString	m_strDeviceName;
	CString	m_strIP;
	CString	m_strPassword;
	UINT	m_nListenPort;
	UINT	m_nPort;
	CString	m_strUserName;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecoderInfoDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetLoginHandle(LONG lLogin);
protected:

	// Generated message map functions
	//{{AFX_MSG(CDecoderInfoDlg)
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSet();
	afx_msg void OnSelchangeComboEncoderNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL InitCombox();
	BOOL UpdateInterface(int nEncoderNum);
	BOOL UpdateStruct(int nEncoderNum);
	BOOL GetEncoderInfo(int nEncoderNum);//获取
	BOOL SetEncoderInfo(int nEncoderNum);//设置
	void ChangeIPCtoString(int nType, CString &strType);
private:
	DEV_ENCODER_INFO	m_encoderInfo[48];//NULL表示没有获取过
	LONG				m_lLogin;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECODERINFODLG_H__AEBD9493_B9C7_4CD9_A540_9B7DA3D4C083__INCLUDED_)
