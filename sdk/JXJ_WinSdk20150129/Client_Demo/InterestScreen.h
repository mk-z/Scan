#pragma once
#include "BorderDlg.h"
// CInterestScreen 对话框

class CInterestScreen : public CDialog
{
	DECLARE_DYNAMIC(CInterestScreen)

public:
	CInterestScreen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInterestScreen();

// 对话框数据
	enum { IDD = IDD_DIALOG_INTERESTSCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	CPoint m_StartPoint[4];
	CPoint m_EndPoint[4];
	bool m_bStart[4];
	bool m_bStartPaint;
	void DrawHideAlarmBorder(int i, int iX, int iY, int iW, int iH);
	CBorderDlg m_cBorderDlg[4];

	static void CALLBACK DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser);
	void RegDrawCallBack();
	void ExitDrawCallBack();

};
