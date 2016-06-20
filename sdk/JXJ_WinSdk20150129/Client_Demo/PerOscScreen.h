#pragma once


// CPerOscScreen 对话框

class CPerOscScreen : public CDialog
{
	DECLARE_DYNAMIC(CPerOscScreen)

public:
	CPerOscScreen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPerOscScreen();

// 对话框数据
	enum { IDD = IDD_DIALOG_PeaOscScreen };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	static void CALLBACK DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser);
	void RegDrawCallBack();
	void ExitDrawCallBack();

	int m_ruleID;
	int m_ruleParam;
	bool m_bStartLine;
	bool m_bKeepWatch;
	bool m_bLeft;
	bool m_bTake;
	CPoint m_lineStartPoint;
	CPoint m_lineEndPoint;
	int m_iCountKeepWatchPoints;
	int m_iCountLeftPoints;
	int m_iCountTakePoints;
	bool m_bLbuttonUp;
	bool m_bDBlbuttonDown;
	CPoint m_KeepWatchPoints[8/*J_SDK_MAX_POLYGON_POINT*/];
	CPoint m_LeftPoints[8/*J_SDK_MAX_POLYGON_POINT*/];
	CPoint m_TakePoints[8/*J_SDK_MAX_POLYGON_POINT*/];
};
