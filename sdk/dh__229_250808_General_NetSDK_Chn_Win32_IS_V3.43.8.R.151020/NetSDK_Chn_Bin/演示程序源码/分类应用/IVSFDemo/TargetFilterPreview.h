#pragma once


// CTargetFilterPreview

class CTargetFilterPreview : public CWnd
{
	DECLARE_DYNAMIC(CTargetFilterPreview)

public:
	CTargetFilterPreview();
	virtual ~CTargetFilterPreview();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	static void _stdcall DrawTargetFilterCfgProc(long nPort, HDC hDc, LONG dwUser);

	CRITICAL_SECTION	m_cs;
	inline CFG_ANALYSEMODULES_INFO* GetModuleInfo(){return m_pAnalyseModulesInfo;};
	void SetModuleInfo(CFG_ANALYSEMODULES_INFO* pAnalyseModulesInfo, int nChannel);

	CFG_ANALYSEMODULES_INFO* m_pAnalyseModulesInfo;
	int m_nChannel;
	
	bool m_bDrawboxBig;// 表示是否画，矩形的四个角的小框
	POINT m_pointDown;// 鼠标左击时坐标
	bool m_bClickBoxBig;// 表示鼠标左击，点击时是否在大的box中
	BYTE m_byPosBig;// 表示点击的box的那个角，1(左上),2(右上),3(左下),4(右下)
	bool m_bClickBoxSmall;// 表示鼠标左键，点击时是否在小的box中
	BYTE m_byPosSmall;// 表示点击的box的那个角，1(左上),2(右上),3(左下),4(右下)

	
	BOOL				m_bDrawDetectRegion;
	BOOL				m_bDrawFilter;
	BOOL				m_bDragging;
};


