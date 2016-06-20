#pragma once
#include "afxwin.h"
#include "MainStream.h"
#include "SecondStreamDlg.h"
#include "ThirdStreamDlg.h"
#include "Pub_Data.h"
#include "afxcmn.h"


// CEncodeDlg 对话框

class CEncodeDlg : public CDialog
{
	DECLARE_DYNAMIC(CEncodeDlg)

public:
	CEncodeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEncodeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ENCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox			m_comChooseChannel;
	CButton				m_bStartVoice;
	CComboBox			m_eInVoice;
	CMainStream			m_MainStream;
	CSecondStreamDlg	m_SecondStream;
	CThirdStreamDlg		m_ThirdStream;
	CTabCtrl			m_TabStream;
	
	
	afx_msg void OnClose();
	afx_msg void OnTcnSelchangingTabstream(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabstream(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();


	void		InitResalutionWnd();//初始化分辨率列表
	CString		GetComReasolution(int iText);  //得到iText的内容
	int			GetIndexOfString(CString strText);  //得到strText的值
	void		SaveMainStream();
	void		SaveSecondStream();
	void		SaveThirdStream();
	int			ReFreshMainStream();
	int			ReFreshSecondStream();
	int			ReFreshThirdStream();

private:
	JEncodeParameter	m_encodeParamer1;
	JEncodeParameter	m_encodeParamer2;
	JEncodeParameter	m_encodeParamer3;
	int					m_StreamId;
}; 
