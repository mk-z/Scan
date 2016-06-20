#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"


// COsdSet 对话框

class COsdSet : public CDialog
{
	DECLARE_DYNAMIC(COsdSet)

public:
	COsdSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COsdSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_OSDSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox			m_comChannel;
	CEdit				m_eText;
	CButton				m_bShowTime;
	CButton				m_bShowText;
	CButton				m_bShowStream;
	CEdit				m_eTimeX;
	CEdit				m_eTimeY;
	CEdit				m_eTextX;
	CEdit				m_eTextY;
	CButton				m_OSDOpposite;
	CMFCColorButton		m_TimeColor;
	CMFCColorButton		m_TextColor;
	COLORREF			m_colorTime;
	COLORREF			m_colorText;
	CButton				m_bShowText2;
	CButton				m_bShowText3;
	CEdit				m_eText2;
	CEdit				m_eText3;
	CEdit				m_eTextX2;
	CEdit				m_eTextX3;
	CEdit				m_eTextY2;
	CEdit				m_eTextY3;

	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeEditTextx();
	afx_msg void OnBnClickedButtontimecolor();
	afx_msg void OnBnClickedButtonTextcolor();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();

	void		UTF8toGB2312(const char *utf8);
	void		GB2312toUTF8(const char *gb2312);
	int			ReFreshWindow();

private:
	JOSDParameter		m_osdParameter;
	CRect				m_cRect;
	char				*m_strGB2312toUTF8;
	char				*m_strUTF8toGB2312;

};
