#pragma once


// CHerdAnalyseScreen 对话框

class CHerdAnalyseScreen : public CDialog
{
	DECLARE_DYNAMIC(CHerdAnalyseScreen)

public:
	CHerdAnalyseScreen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHerdAnalyseScreen();

// 对话框数据
	enum { IDD = IDD_DIALOG_HerdAnalyseScreen };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:

	void RegDrawCallBack();
	void ExitDrawCallBack();
	static void CALLBACK DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	

	CPoint m_innerPoint[4];
	CPoint m_outerPoint[4];

	int m_nInnerNum;
	int m_nOuterNum;
	bool m_bInner;
	bool m_bOuter;
	
};
