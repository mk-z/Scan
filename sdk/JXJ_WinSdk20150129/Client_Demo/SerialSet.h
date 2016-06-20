#pragma once
#include "afxwin.h"


// CSerialSet 对话框

class CSerialSet : public CDialog
{
	DECLARE_DYNAMIC(CSerialSet)

public:
	CSerialSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSerialSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_SERIAL_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit				m_DataBit;
	CEdit				m_StopBit;
	CEdit				m_BaudRate;
	CComboBox			m_SerialType;
	CComboBox			m_CheckBit;
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();



	int					ReFreshWindow();
private:

	JSerialParameter			m_serialParam;
};
