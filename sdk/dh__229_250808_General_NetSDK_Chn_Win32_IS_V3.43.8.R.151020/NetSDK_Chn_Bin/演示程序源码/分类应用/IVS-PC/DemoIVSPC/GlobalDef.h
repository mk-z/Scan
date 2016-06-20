#ifndef __IVS_GLOBAL_DEF_H__
#define __IVS_GLOBAL_DEF_H__

#include <list>
using namespace std;



/// 绘制规则状态
/// \enum  __eRULESTATE
typedef enum __eRULESTATE
{
	eStateNull = 0,    ///<无状态
	eRegionStart,      ///<开始划区域
	eRegionNext,       ///<划区域的下一个点
	eRegionEnd,        ///<划区域结束
	eDirctionStart,    ///<开始划方向
	eDirctionEnd,      ///<划方向结束
	eStateNum
}eRuleState;

#define  WM_RULE_DRAW            (WM_USER+300)   /// 划规则消息
#define  WM_UPDATE_NOTIFY        (WM_USER+400)   /// 数据更新通知

typedef enum _ARROW_DIRECTION_TYPE
{
	ARROW_UP = 0,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT
}ARROW_DIRECTION_TYPE, *PARROW_DIRECTION_TYPE;

typedef enum __ModuleDrawState
{
	DetectZone = 1, // 检测区域
	ExcludeZone		// 排除区域

}ModuleDrawState;



typedef enum __LoginState
{
	LoginSucc = 1,	// 登陆成功
	LoginFailed ,	// 登陆失败
	LogOut,			// 登出
	LoginOpenView,	// 打开监视通道	

}LoginState;




//////////////////////////////////////////////////////////////////////////

#define WM_ZONEDONE			(WM_USER + 100)	//绘制全局标定区域/标尺完成后通知父窗口
#define WM_REGIONDONE		(WM_USER + 101)	//绘制模块检测区域/排除区域完成后通知给父窗口
#define WM_USER_ALAMR_COME	(WM_USER + 200)	//回调报警信息


#define PEN_WIDTH 1 // 画笔的宽度

/////////////////////////////////////////////////////////////////////////////





//一台设备的最大总通道数
const int g_MaxChannelCount = 32;

//decode port num
const int g_nPlayPort = 450;

//draw port num for preview
const int g_nPreviewDrawPort = 300;

//draw port num for RuleCfg
const int g_nRuleCfgDrawPort = 400;

//////////////////////////////////////////////////////////////////////////

//全局配置界面标定区域树控件上的节点绑定的信息定义



const int nNodeArea = 0;
const int nStaffHor = 1;
const int nStaffVer = 2;

//树节点类型
typedef struct tagGTNodeType
{
	int	nNodeType;		//节点类型：检测区域，标尺
}GTNODETYPE;

//标定区域节点
typedef struct tagGTNodeArea
{
	int						nNodeType;
	CFG_CALIBRATEAREA_INFO	CfgCalibrateAreaInfo;
}GTNODEAREA;

//标尺节点
typedef struct tagGTNodeStaff
{
	int			nNodeType;
	CFG_STAFF	CfgStaff;
}GTNODESTAFF;

//////////////////////////////////////////////////////////////////////////

//每个规则的存储结构体
typedef struct tagRuleStruct
{
	CFG_RULE_INFO RuleInfo;
	char* pRuleBuf;

	tagRuleStruct()
	{
		ZeroMemory(&RuleInfo, sizeof(RuleInfo));
		pRuleBuf = NULL;
	}

	~tagRuleStruct()
	{
		ZeroMemory(&RuleInfo, sizeof(RuleInfo));
		if (pRuleBuf)
		{
			delete pRuleBuf;
			pRuleBuf = NULL;
		}
	}
}RuleStruct;

//一个通道的规则列表
typedef std::list<RuleStruct*> lsRuleList;

//规则事件树控件CRuleTreeCtrl上节点绑定的信息
typedef struct tagRuleNodeInfo
{
	int nChnNum;		//通道号
	BOOL bEnPic;		//是否订阅图片	
	DWORD sRuleType;	//报警类型

	tagRuleNodeInfo()
	{
		nChnNum = -1;
		bEnPic = FALSE;
		sRuleType = 0;
	}
}RuleNodeInfo;
//要/在检测的规则类型列表
typedef std::list<RuleNodeInfo*> vecRULE;


//报警回调参数结构体
typedef struct tagEventPara
{
	LONG lAnalyzerHandle;
	DWORD dwAlarmType;
	void* pAlarmInfo;
	BYTE *pBuffer;
	DWORD dwBufSize;
	int nSequence;
}EventPara;

//报警信息结构体
typedef struct tagAlarmInfoNode
{
	int nChnNum;
	DWORD dwRuleType;
	NET_TIME_EX Time;
	TCHAR szFile[MAX_PATH];

	tagAlarmInfoNode()
	{
		nChnNum = -1;
		dwRuleType = -1;
		ZeroMemory(&Time, sizeof(Time));
		ZeroMemory(szFile, _countof(szFile));
	}
}AlarmInfoNode;
//报警信息链表，按照客户接收到的先后顺序存入链表
typedef	std::list<AlarmInfoNode*> lsAlarmInfo;




typedef struct tagMTNode
{
	int			nNodeType;
	int			nPointCount;
	CFG_POLYGON	CfgPolygon[MAX_POLYGON_NUM];

	tagMTNode()
	{
		nNodeType = 0;
		nPointCount = 0;
		for (int i = 0; i < MAX_POLYGON_NUM; i++)
		{
			CfgPolygon[i].nX = 0;
			CfgPolygon[i].nY = 0;
		}
	}
}MTNODE;

typedef struct
{
	int ivsType;
	TCHAR szType[32];
}IVSType;

const IVSType TypeTable[] = 
{
	{EVENT_IVS_CROSSFENCEDETECTION, _T("CrossFence")},
	{EVENT_IVS_CROSSLINEDETECTION, _T("CrossLine")},
	{EVENT_IVS_CROSSREGIONDETECTION, _T("CrossRegion")},
	{EVENT_IVS_MOVEDETECTION, _T("MoveDetection")},
	{EVENT_IVS_LEFTDETECTION, _T("LeftDetection")},
	{EVENT_IVS_PARKINGDETECTION, _T("Parking")},
	{EVENT_IVS_PRESERVATION, _T("Preservation")},
	{EVENT_IVS_RETROGRADEDETECTION, _T("Retrogradation")},
	{EVENT_IVS_STAYDETECTION, _T("Stay")},
	{EVENT_IVS_TAKENAWAYDETECTION, _T("TakenAway")},
	{EVENT_IVS_VIDEOABNORMALDETECTION, _T("VideoAbnormal")},
	{EVENT_IVS_WANDERDETECTION, _T("Wander")},
	{0, _T("\0")}
};


//////////////////////////////////////////////////////////////////////////

void CALLBACK RealDataCallBackEx(LLONG lRealHandle,
								 DWORD dwDataType, 
								 BYTE *pBuffer,
								 DWORD dwBufSize, 
								 LONG lParam, 
								 LDWORD dwUser);
//
void  g_SetWndStaticText(CWnd * pWnd);

//
CString ConvertString(CString strText);

//
int g_getStructSize(int nRuleType);

//
CString g_ConvertRuleTypeToString(DWORD dwType);

//
int g_ConvertRuleTypeToStructSize(DWORD dwType);

//
int g_GetStructInfo(DWORD dwAlarmType);

//
void g_DrawArrow(CDC *pDC, POINT pointStart, ARROW_DIRECTION_TYPE eArrowDirection);

//////////////////////////////////////////////////////////////////////////
//

class CGuard
{
public:
	CGuard(CRITICAL_SECTION* pCS)
		:m_lock(pCS)
	{
		EnterCriticalSection(m_lock);
	}
	virtual ~CGuard()
	{
		LeaveCriticalSection(m_lock);
	}

private:
	CRITICAL_SECTION* m_lock;
};







#endif