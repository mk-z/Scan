#pragma once


// CTargetFilterPreview

class CTargetFilterPreview : public CWnd
{
	DECLARE_DYNAMIC(CTargetFilterPreview)

public:
	CTargetFilterPreview();
	virtual ~CTargetFilterPreview();

	static void _stdcall DrawTargetFilterCfgProc(long nPort, HDC hDc, LONG dwUser);

	void SetModuleInfo(CFG_OBJECT_SIZEFILTER_INFO* pObjectFilter, int nChannel);

	CRITICAL_SECTION	m_cs;
	// 表示是否画，矩形的四个角的小框
	bool m_bDrawboxBig;
	// 表示鼠标左击，点击时是否在大的box中
	bool m_bClickBoxBig;
	// 表示鼠标左键，点击时是否在小的box中
	bool m_bClickBoxSmall;
	// 表示点击的box的那个角，1(左上),2(右上),3(左下),4(右下)
	BYTE m_byPosBig;

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

private:
	
	CFG_OBJECT_SIZEFILTER_INFO* m_pObjectFilter;
	int m_nChannel;
	int m_nCenterPointIndex;
	// 鼠标左击时坐标
	POINT m_pointDown;
	// 表示点击的box的那个角，1(左上),2(右上),3(左下),4(右下)
	BYTE m_byPosSmall;
};


