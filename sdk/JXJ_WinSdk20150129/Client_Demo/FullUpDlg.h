#pragma once


// CFullUpDlg 对话框

class CFullUpDlg : public CDialog
{
	DECLARE_DYNAMIC(CFullUpDlg)

public:
	CFullUpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFullUpDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_FULLUP_SCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	bool m_bMaxofScreen;
	bool m_bIfFullup;
	int m_iWndX;
	int m_iWndY;
	int m_iWndWidth;
	int m_iWndHeight;
	CMenu m_pMenu;
	CRect m_Rect;
	int m_iHideIndex;  
	int m_iPlayWndIndex;  //  该窗口播放的 视频索引
	int m_iPlayWndNum;		//该窗口在主窗体的排序
	int m_iPlayFlag;			//该窗口是否已经播放视频了
	int m_iFlag;
	HCURSOR m_hcursor;
	CImageList m_imageList;


	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuFullscreen();
	afx_msg void OnMenuMainstream();
	afx_msg void OnMenuSecondstream();
	afx_msg void OnMenuThirdstream();
	afx_msg void OnMenuClose();
	afx_msg void OnBnClickedButtonTalk();
	afx_msg void OnBnClickedButtonAttribute();
	void DrewWinBorder();   
	void ResetBorder();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	bool m_bTalk;   //是否启用对讲
	bool m_bListen; //是否启用监听
	bool m_bRecode; //是否录像
	CBitmapButton m_TalkButton;
	afx_msg void OnBnClickedButtonTakeapicture();
	afx_msg void OnBnClickedButtonListen();
	afx_msg void OnBnClickedButtonRecode();
	BOOL PreTranslateMessage(MSG* pMsg); //按钮按下和松开

	void DeviceClose();   //关闭视频
	void ShowMenuState();   //显示右键菜单的状态
	void EscEvent();
	void ButtonCloseAll();
};

extern CFullUpDlg g_cFullUpDlg[GET_MAX_DEV_NUM];