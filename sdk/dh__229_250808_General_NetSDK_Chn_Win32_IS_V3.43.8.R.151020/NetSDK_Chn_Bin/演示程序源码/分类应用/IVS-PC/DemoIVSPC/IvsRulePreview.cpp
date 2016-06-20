#include "stdafx.h"
#include "IvsRulePreview.h"
#include "ConfigRules.h"

float CIvsRulePreview::s_fFactorX = 1.0;
float CIvsRulePreview::s_fFactorY = 1.0;

int CIvsRulePreview::s_nWidth = 400	;
int CIvsRulePreview::s_nHeight = 400;
CIvsRulePreview::CIvsRulePreview(void)
:m_pNumberStatInfo(NULL),
 m_pANARuleInfo(NULL),
 m_pOrgANARuleInfo(NULL),
 m_nDirectIndex(0),
 m_nRegionIndex(0)
{
	InitRuleData();
}

CIvsRulePreview::~CIvsRulePreview(void)
{
	if (m_pANARuleInfo)
	{
		if (m_pANARuleInfo->pRuleBuf)
		{
			delete []m_pANARuleInfo->pRuleBuf;
		}
		delete m_pANARuleInfo;
		m_pANARuleInfo = NULL;
	}
}

int CIvsRulePreview::InitRuleData()
{
	if (NULL == m_pANARuleInfo)
	{
		m_pANARuleInfo = new CFG_ANALYSERULES_INFO;
		if (m_pANARuleInfo)
		{
			m_pANARuleInfo->nRuleCount = 1;
			m_pANARuleInfo->nRuleLen = sizeof(CFG_RULE_INFO) + sizeof(CFG_NUMBERSTAT_INFO);
			m_pANARuleInfo->pRuleBuf = new char[m_pANARuleInfo->nRuleLen];
			if (m_pANARuleInfo->pRuleBuf)
			{
				memset(m_pANARuleInfo->pRuleBuf, 0, m_pANARuleInfo->nRuleLen);
                CFG_RULE_INFO *pRule = (CFG_RULE_INFO *)m_pANARuleInfo->pRuleBuf;
				pRule->dwRuleType = EVENT_IVS_NUMBERSTAT;
				pRule->nRuleSize = sizeof(CFG_NUMBERSTAT_INFO);
				m_pNumberStatInfo = (CFG_NUMBERSTAT_INFO *)(m_pANARuleInfo->pRuleBuf+sizeof(CFG_RULE_INFO));
			}
		}
	}
	return 1;
}
BEGIN_MESSAGE_MAP(CIvsRulePreview, CWnd)
	//{{AFX_MSG_MAP(CIvsModulePreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////////
/// \fn  static void _stdcall CIvsRulePreview::drawIvsRuleCfgProc(long nPort, HDC hDc, LONG dwUser)
/// \brief  绘制规则配置回调函数
/// \param[in] nPort 视频绘制端口
/// \param[in] hDc   视频绘制dc
/// \param[in] dwUser 用户自定义数据
/// \exception 暂无异常发生
/// \return TURE解析成功，FALSE解析失败
/////////////////////////////////////////////////////////////////////////////////
void _stdcall CIvsRulePreview::DrawIvsRuleCfgProc(long nPort, HDC hDc, LONG dwUser)
{
	CConfigRules* pRulesInfo = (CConfigRules*)dwUser;
	if (NULL == pRulesInfo || !IsWindow(pRulesInfo->GetSafeHwnd()))
	{
		return ;
	}
	int nErr = 0;

	HWND hWnd = pRulesInfo->GetDrawRuleHandle()->GetSafeHwnd();
	RECT rect = {0};
	::GetClientRect(hWnd,&rect);

	nErr = DRAW_Draw(pRulesInfo->GetDrawPortNum(), hDc, hWnd, 0);
	if(nErr < 0)
	{
		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////
/// \fn  eRuleState CIvsRulePreview::UpdataState(CPoint &point)
/// \brief  初始化划绘制数据
/// \param[in] nPort 视频端口
/// \param[in] pRuleInfo 规划数据
/// \exception 暂无异常发生
/// \return 返回规则状态
/////////////////////////////////////////////////////////////////////////////////
BOOL CIvsRulePreview::InitDarwData(int nPort, CFG_ANALYSERULES_INFO *pRuleInfo)
{
	m_nPort = nPort;
	if (NULL == pRuleInfo)
	{
		return FALSE;
	}
	int nReadBufLen = 0;
	for (int nIndexRule = 0; nIndexRule <pRuleInfo->nRuleCount; nIndexRule++)
	{
		if (nReadBufLen > pRuleInfo->nRuleLen)
		{
			break;
		}
		CFG_RULE_INFO *pRuleHeaderInfo = (CFG_RULE_INFO *)(pRuleInfo->pRuleBuf + nReadBufLen);
		nReadBufLen += sizeof(CFG_RULE_INFO);
		if (NULL == pRuleInfo)
		{
			break;
		}
		if (pRuleHeaderInfo->dwRuleType == EVENT_IVS_NUMBERSTAT &&
			pRuleHeaderInfo->nRuleSize  == sizeof(CFG_NUMBERSTAT_INFO))
		{
			memcpy(m_pNumberStatInfo, pRuleInfo->pRuleBuf + nReadBufLen, sizeof(CFG_NUMBERSTAT_INFO));
			if (m_curState == eRegionStart)
			{
				m_pNumberStatInfo->nDetectRegionPoint = 0;
				memset(&m_pNumberStatInfo->stuDetectRegion, 0, MAX_POLYGON_NUM*sizeof(CFG_POLYGON));
				m_nRegionIndex = 0;
				UpdataRuleData(0);
			}
			else if ( m_curState == eDirctionStart)
			{
				memset(&m_pNumberStatInfo->stDirection, 0, 2*sizeof(CFG_POLYGON));
				m_nDirectIndex = 0;
				UpdataRuleData(1);
			}
			break;
		}
		nReadBufLen += pRuleHeaderInfo->nRuleSize;
	}

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////
/// \fn  eRuleState CIvsRulePreview::UpdataState(CPoint &point)
/// \brief  更新绘制的状态
/// \param[in] point 绘制的点
/// \exception 暂无异常发生
/// \return 返回规则状态
/////////////////////////////////////////////////////////////////////////////////
eRuleState CIvsRulePreview::UpdataState(CPoint &point)
{
	switch ( m_curState )
	{
	case eRegionStart:
		m_curState = eRegionNext;
		AddPoint(0, point);
		break;
	case eRegionNext:
		m_curState = eRegionNext;
		AddPoint(0, point);
		break;
	case eRegionEnd:
		m_curState = eStateNull;
		AddPoint(0, point);
		m_nRegionIndex = 0;
		break;
	case eDirctionStart:
		m_curState = eDirctionEnd;
		AddPoint(1, point);
		break;
	case eDirctionEnd:
		m_curState = eStateNull;
		AddPoint(1, point);
		m_nDirectIndex = 0;
		break;
	default:
		m_curState = eStateNull;
		m_nRegionIndex = 0;
		m_nDirectIndex = 0;
		break;
	}
	return m_curState;
}

/////////////////////////////////////////////////////////////////////////////////
/// \fn void CIvsRulePreview::AddPoint(int nTYpe)
/// \brief  增加点函数
/// \param[in] nType 点类型，0表示区域， 1表示方向
/// \param[in] point 绘制的点信息
/// \exception 暂无异常发生
/// \return 返回规则状态
/////////////////////////////////////////////////////////////////////////////////
void CIvsRulePreview::AddPoint(int nType, CPoint &point)
{
	CRect rt;
	GetClientRect( &rt);
	if(nType == 0)
	{
		if (m_nRegionIndex<MAX_POLYGON_NUM)
		{
			m_pNumberStatInfo->stuDetectRegion[m_nRegionIndex].nX = (int)(point.x*8196.0f/rt.Width());
			m_pNumberStatInfo->stuDetectRegion[m_nRegionIndex].nY = (int)(point.y*8196.0f/rt.Height());
			m_pNumberStatInfo->nDetectRegionPoint = ++m_nRegionIndex;
			UpdataRuleData(0);
		}
	}
	else
	{
		if ( m_nDirectIndex < 2)
		{
			m_pNumberStatInfo->stDirection[m_nDirectIndex].nX =  int(point.x*8196.0f/rt.Width());
			m_pNumberStatInfo->stDirection[m_nDirectIndex].nY =  int(point.y*8196.0f/rt.Height());
			++m_nDirectIndex;
			m_pNumberStatInfo->emType = NET_EM_NUMSTAT_TYPE_ENTRANCE;
			if (m_nDirectIndex == 2)
			{
				UpdataRuleData(1);
				::SendMessage(GetParent()->GetSafeHwnd(), WM_RULE_DRAW, 0, (LPARAM)eDirctionEnd);
			}
			
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
/// \fn void CIvsRulePreview::UpdataRuleData()
/// \brief  实时更新规则
/// \param[in] nType 点类型，0表示区域， 1表示方向
/// \exception 暂无异常发生
/// \return 返回规则状态
/////////////////////////////////////////////////////////////////////////////////
void CIvsRulePreview::UpdataRuleData(int nType)
{

	if(m_pNumberStatInfo && m_pANARuleInfo)
	{
		DRAW_Reset(m_nPort, DRAW_RULE);
		/// 更新数据
		DRAW_InputRuleData(m_nPort, 0, (unsigned char *)m_pANARuleInfo, 0);
	}
}

void CIvsRulePreview::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	UpdataState(point);
	//	CWnd::OnLButtonDown(nFlags, point);
}

void CIvsRulePreview::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int nPoint = 0;
	nPoint = 1;
}

void CIvsRulePreview::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (eRegionNext == m_curState)
	{
		m_curState = eRegionEnd; 
	}
	UpdataState(point);
	if (m_pNumberStatInfo->nDetectRegionPoint >= 3)
	{
		::SendMessage(GetParent()->GetSafeHwnd(), WM_RULE_DRAW, 0, (LPARAM)eRegionEnd);
	}
	//	CWnd::OnRButtonUp(nFlags, point);
}

int CIvsRulePreview::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	

	return 0;
}

void CIvsRulePreview::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rt;
	GetClientRect(&rt);
	dc.FillSolidRect(&rt, RGB(100, 100, 100));
	// TODO: Add your message handler code here

	// Do not call CWnd::OnPaint() for painting messages
}

void CIvsRulePreview::OnDestroy() 
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}

