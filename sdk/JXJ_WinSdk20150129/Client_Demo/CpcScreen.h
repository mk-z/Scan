#pragma once


// CCpcScreen 对话框

class CCpcScreen : public CDialog
{
	DECLARE_DYNAMIC(CCpcScreen)

public:
	CCpcScreen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCpcScreen();

// 对话框数据
	enum { IDD = IDD_DIALOG_CPC_SCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	int m_iCountPoint;

	void RegDrawCallBack();
	void ExitDrawCallBack();
	static void CALLBACK DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser);

	CPoint	m_cpcPoint[8/*J_SDK_MAX_CPC_RULE_POINT*/];
	bool	m_bDraw;
};
