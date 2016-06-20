#if !defined(AFX_IVSMODULEPREVIEW_H__F4159618_F744_49CE_90FB_276A626E8C58__INCLUDED_)
#define AFX_IVSMODULEPREVIEW_H__F4159618_F744_49CE_90FB_276A626E8C58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IvsModulePreview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIvsModulePreview window

class CIvsModulePreview : public CWnd
{
// Construction
public:
	CIvsModulePreview();
	virtual ~CIvsModulePreview();

	//获取已经有的模块信息
	CFG_MODULE_INFO* GetModuleInfo();

	//设置/清空模块信息
	void SetModuleInfo(CFG_MODULE_INFO* pModuleInfo, BOOL bClear);

	//获取正在添加/已经添加完的区域
	CFG_POLYGON* GetPolygonCfg(int& nCnt);

	//设置添加的区域
	void SetPolygonCfg(CFG_POLYGON* pPolygonCfg, int nCnt);

	//开始绘图
	void BeginDraw(HTREEITEM hItem, BOOL bAddDectectZone);

	//是否正在画图
	BOOL IsDrawing();

	//绘图回调
	static void _stdcall DrawIvsModuleCfgProc(long nPort, HDC hDc, LONG dwUser);

	void Redraw(HTREEITEM hItem, BOOL bAddDectectZone);

	CRITICAL_SECTION	m_cs;

protected:
	//{{AFX_MSG(CIvsModulePreview)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	//将模块配置窗口的选中的模块信息传递到此
	CFG_MODULE_INFO	m_cfgModuleInfo;
	CFG_POLYGON*	m_pPolygonCfg;
	int				m_iPtCnt;
	float	m_fX;
	float	m_fY;

	BOOL			m_bAddDetecRegion;
	HTREEITEM		m_hItemToBeDraw;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVSMODULEPREVIEW_H__F4159618_F744_49CE_90FB_276A626E8C58__INCLUDED_)
