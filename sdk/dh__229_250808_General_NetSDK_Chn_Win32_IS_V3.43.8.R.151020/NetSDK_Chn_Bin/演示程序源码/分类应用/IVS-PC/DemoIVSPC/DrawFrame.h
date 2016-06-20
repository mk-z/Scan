#pragma once


#include "GlobalDef.h"

#define WM_MSG_SHOW WM_USER+1000

// CDrawFrame 对话框

class CDrawFrame : public CDialog
{
	DECLARE_DYNAMIC(CDrawFrame)

public:
	CDrawFrame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrawFrame();

	void DrawCoordinate();
	void SetRectClient(const CRect & rect);
	void InitData(NET_OUT_DOFINDNUMBERSTAT& dataShow, DWORD dwStartIndex, DWORD dwCount, int nType);
	void DrawFrame();
	void DrawLine(bool bEnter);//bEnter:1表示进入，0表示出去
	void DrawPointEnter(int nZoom, CString strShow);
	void DrawPointExit(int nZoom, CString strShow);
	int  GetZoom();
	bool CheckTimeLost(NET_TIME timeStart, NET_TIME timeEnd);
	void UninitData();
	inline void SetPaint(bool bPaint){m_bPaint = bPaint;};

// 对话框数据
	enum { IDD = IDD_DRAWFRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

private:
	// 画图的DC
	CDC*	m_pDC;

	// 表示此窗口的大小
	CRect	m_rectClient;

	// 表示此坐标的区域
	CRect	m_rectRange;

	// 数据
	NET_OUT_DOFINDNUMBERSTAT m_dataShow;

	// 表示从m_dataShow的第多少条开始取数据
	DWORD	 m_dwStartIndex;

	// 表示要从m_dataShow取出多少条数据
	DWORD	 m_dwCount;

	// 表示查询的类型，0分，1时，2天，3周，4月，5季度，6年
	int	 m_nType;

	// 数据同步锁
	CRITICAL_SECTION m_criticalSection;

	// 表示是否需要重画图表
	bool	 m_bPaint;
	// 表示画的线的最大的y轴坐标到，坐标轴最下端的，y轴距离
	DWORD m_nMaxY;
	
};
