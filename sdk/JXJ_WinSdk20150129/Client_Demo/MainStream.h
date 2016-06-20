#pragma once
#include "afxwin.h"


// CMainStream 对话框

class CMainStream : public CDialog
{
	DECLARE_DYNAMIC(CMainStream)

public:
	CMainStream(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainStream();

// 对话框数据
	enum { IDD = IDD_DIALOG_MAIN_STREAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_eZl;
	CEdit m_eSpaceZ;
	CComboBox m_comResolution;
	CComboBox m_comQuality;
	CComboBox m_eZs;
	CEdit m_eMlv;
	CComboBox m_comWlv;
	CComboBox m_comEncodeOrder;
	CComboBox m_comEncodeModel;
	CButton m_IfFirst;
	CStringArray m_strArray;
	afx_msg void OnClose();
};
