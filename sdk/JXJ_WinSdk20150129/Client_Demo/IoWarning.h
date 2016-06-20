#pragma once
#include "afxwin.h"
#include "VideoTime.h"

// CIoWarning 对话框

class CIoWarning : public CDialog
{
	DECLARE_DYNAMIC(CIoWarning)

public:
	CIoWarning(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIoWarning();

// 对话框数据
	enum { IDD = IDD_DIALOG_IOWARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox		m_channel;
	CButton			m_StartIo;
	int				m_iSelChannel;
	CComboBox		m_IoType;
	CComboBox		m_Seconds;
	CVideoTime		m_cVideoTime;

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnCbnSelchangeComboChannel();
	afx_msg void OnBnClickedButtonSettime();

	void ShowVideoTime(int iIndex);
	int	 ReFreshWindow();


private:
	JIoAlarm	m_ioAlarm[10];
};
