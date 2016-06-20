#pragma once
#include "afxcmn.h"


// CRecodeScreenDlg 对话框

class CRecodeScreenDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecodeScreenDlg)

public:
	CRecodeScreenDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecodeScreenDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_RECODESCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_PlayProgress;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	bool m_bDbclk;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL PreTranslateMessage(MSG* pMsg); //按钮按下和松开
	bool m_bPlayFileProgress;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
