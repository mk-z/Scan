#pragma once
#include "afxwin.h"

#include "GlobalDef.h"

//struct CFG_NUMBERSTAT_INFO;

/////////////////////////////////////////////////////////////////////////////////
/// \class CIvsRulePreview IvsRulePreview.h ".\SDKInvoker.h"
/// \brief 绘制规则配置类
/////////////////////////////////////////////////////////////////////////////////
class CIvsRulePreview :public CWnd
{
public:
	CIvsRulePreview(void);
	~CIvsRulePreview(void);
	int InitRuleData();
	/// 绘图规则配置回调
	static void _stdcall DrawIvsRuleCfgProc(long nPort, HDC hDc, LONG dwUser);
	/// 更新绘制信息
	void InitState(eRuleState ruleState) {m_curState = ruleState;}
	/// 初始化绘制数据
	BOOL InitDarwData(int nPort, CFG_ANALYSERULES_INFO *pRuleInfo);
	/// 获取当前人数统计结构体指针
	inline CFG_NUMBERSTAT_INFO *GetNumberStatInfo() {return m_pNumberStatInfo;}
	inline CFG_ANALYSERULES_INFO *GetAnalysRuleInfo() { return m_pANARuleInfo; }
protected:
	/// 更新状态
	eRuleState UpdataState(CPoint &point);
	/// 增加点信息
	void AddPoint(int nTYpe, CPoint &point);
	/// 更新数据
	void UpdataRuleData(int nType);
	
	//{{AFX_MSG(CIvsModulePreview)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	/// \var static float s_fFactorX
	/// X轴缩放比例
	static float s_fFactorX;
	/// \var static float s_fFactorY
	/// Y轴缩放比例
	static float s_fFactorY;

	/// \var static float s_fFactorX
	/// X轴缩放比例
	static int s_nWidth;
	/// \var static float s_fFactorY
	/// Y轴缩放比例
	static int s_nHeight;

	/// \var eRuleState m_curState
	/// 当前规则状态
	eRuleState m_curState;
	
	///\var int m_nPort
	/// 要绘制的当前视频源端口
	int       m_nPort;
    
	/// \var CFG_NUMBERSTAT_INFO *m_pNumberStatInfo
	/// 人数统计规则结构体指针
	CFG_NUMBERSTAT_INFO *m_pNumberStatInfo;

	/// \var int m_nRegionIndex
	/// 区域数组索引
	int m_nRegionIndex;

	/// \var int m_nDirectIndex
	///  方向数组索引
	int m_nDirectIndex;

	/// \var CFG_ANALYSERULES_INFO *m_pANARuleInfo
	/// 实时更新的规则信息
	CFG_ANALYSERULES_INFO *m_pANARuleInfo;

	/// \var CFG_ANALYSERULES_INFO *m_pOrgANARuleInfo
	/// 保存没有更新前的规则信息
	CFG_ANALYSERULES_INFO *m_pOrgANARuleInfo;



};
