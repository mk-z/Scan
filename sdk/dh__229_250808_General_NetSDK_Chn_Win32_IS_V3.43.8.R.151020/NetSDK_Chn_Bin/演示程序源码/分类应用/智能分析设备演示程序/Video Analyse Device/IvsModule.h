#pragma once

#include <vector>
#include <list>
#include <map>

#define M_PI 3.1415926
#define LOCUS_WIDTH				1024
#define LOCUS_HEIGHT			1024
#define IVS_VIDEO_WIDTH			8192
#define IVS_VIDEO_HEIGHT		8192

#define Min_Distance			512		//画警戒区方向箭头的最小2点间距离（8192坐标系下）
#define  MAX_TRACKPOINT_NUM 10
#define IVS_INFO_SHOW_FRAMES	100		// 在多少帧内显示智能分析信息(运动轨迹,报警信息)
#define MAX_IVS_LOCUS_SEG_CNT	50		// 运动目标最大运动轨迹段数目
#define MAX_IVS_OBJECT_CNT		50		// 运动目标最大数目
#define CHANNEL_MAX_COUNT		32

enum
{
	Color_ObjectNormal = RGB(0,255,0),	// 正常目标框颜色
		Color_ObjectAlarm  = RGB(255,0,0),	// 报警时目标框颜色
		Color_LocusNormal  = RGB(0,255,0),	// 正常轨迹颜色
		Color_LocusAlarm   = RGB(255,0,0),	// 报警时轨迹颜色
		Color_RuleNormal   = RGB(0,0,255),	// 正常规则颜色
		Color_RuleAlarm    = RGB(255,0,0)	// 报警时规则颜色
};

enum IvsOjbOpt
{
	IvsOjbOpt_AddOjb = 1,
		IvsOjbOpt_AddLocus,
		IvsOjbOpt_DelOjb,
		IvsOjbOpt_HideLocus
};

typedef struct _tagCHANNEL_INFO
{
	bool			m_bAtmIvs;
	bool			m_bSupportIvs;
	bool			m_bEnableIvs;
	int				m_nMaxRuleStructSize;
	int				m_nMaxRuleNum;
}CHANNEL_INFO;

typedef struct _deviceinfo_tag
{
public:	
	LONG			m_ID;									//设备ID
	LONG			m_LoginHandle;							//登陆句柄
	int				m_ChannelCount;							//通道数
	CHANNEL_INFO	m_Channel[CHANNEL_MAX_COUNT];			//通道信息
}DEV_INFO;

//RECT=(X-XSize, Y-YSize, X+XSize, Y+YSize)
typedef struct _PRIVATE_IVS_POINT
{
	short			x;
	short			y;
	short			xSize;
	short			ySize;
}PRIVATE_IVS_POINT;

//运动目标轨迹
typedef struct _PRIVATE_IVS_OBJ
{
	int				decode_id;
	int				obj_id;
	int				enable;
	PRIVATE_IVS_POINT	track_point[MAX_TRACKPOINT_NUM];
	int				trackpt_num;
	int				operator_type; //操作分为三类：新增物体(1), 增加物体轨迹点(2)，删除物体(3)，隐藏物体轨迹(4),其它值无效
	int				frame_part_id; //0表示一帧的开始，依次递增
	char			reserved[128]; //保留
	
}PRIVATE_IVS_OBJ;

struct IvsRuleInfo
{
	char szRuleName[MAX_NAME_LEN];				// 规则名称,不同规则不能重名
	bool bRuleEnable;							// 规则使能
	
	CFG_RULE_INFO stuRuleInfo;
	
	union RuleEvent
	{
		CFG_CROSSLINE_INFO			stuCrossLineCfg;		// 警戒线规则配置,规则类型为"CrossLineDetection"时有效
		CFG_CROSSREGION_INFO		stuCrossRegionCfg;		// 警戒区规则配置,规则类型为"CrossRegionDetection"时有效
		CFG_PASTE_INFO				stuPasteCfg;			// ATM贴条规则配置,规则类型为"PasteDetection"时有效
		CFG_LEFT_INFO				stuLetfCfg;				// 物品遗留规则配置,规则类型为"LeftDetection"时有效
		CFG_PRESERVATION_INFO		stuPreseRvationCfg;		// 物品保全规则配置,规则类型为"Preservation"时有效
		CFG_STAY_INFO				stuStayCfg;				// 停留规则配置,规则类型为"StayDetection"时有效
		CFG_WANDER_INFO				stuWanderCfg;			// 徘徊规则配置,规则类型为"WanderDetection"时有效
		CFG_MOVE_INFO				stuMoveCfg;				// 运动规则配置,规则类型为"MoveDetection"时有效
		CFG_TAIL_INFO				stuTailCfg;				// 尾随规则配置,规则类型为"TailDetection"时有效
		CFG_RIOTER_INFO				stuRioterCfg;			// 聚集规则配置,规则类型为"RioterDetection"时有效
		CFG_FIGHT_INFO				stuFightCfg;			// 打架规则配置,规则类型为"FightDetection"时有效
		CFG_FIRE_INFO				stuFireCfg;				// 火焰规则配置,规则类型为"FireDetection"时有效
		CFG_SMOKE_INFO				stuSmokeCfg;			// 烟雾规则配置,规则类型为"SmokeDetection"时有效
		CFG_FLOWSTAT_INFO			stuFlowStatCfg;			// 流量统计规则配置, 规则类型为"FlowStat"时有效
		CFG_NUMBERSTAT_INFO			stuNumberStatCfg;		// 数量统计规则配置,规则类型为"NumberStat"时有效
		CFG_TRAFFICCONTROL_INFO		stuTraControlCfg;		// 交通管制规则配置,规则类型为"TrafficControl"时有效
		CFG_TRAACCIDENT_INFO		stuAccidentCfg;			// 交通事故规则配置,规则类型为"TrafficAccident"时有效
		CFG_TRAJUNCTION_INFO		stuJunctionCfg;			// 路口规则配置,规则类型为"TrafficJunction"时有效
		CFG_TRAFFICGATE_INFO		stuTrafficGateCfg;		// 卡口规则配置,规则类型为"TrafficGate"时有效
		CFG_FACEDETECT_INFO			stuFaceDetectCfg;		// 人脸检测规则配置,规则类型为"FaceDetect"时有效
	} ruleEvent;
};

// 解码信息
struct IvsDecodeInfo
{
	LONG				dev_id;			// 设备ID
	int					chnl_idx;		// 通道序号
	int					decoder_id;		// 解码端口
	HWND				hwnd;			// 视频显示窗口

	bool				bShowRule;		// 是否显示智能分析规则
	bool				bShowObj;		// 是否显示运动目标外框
	bool				bShowLocus;		// 是否显示运动轨迹
};

// 智能分析规则信息
struct IvsRule
{
	int					rule_id;				// 规则序号
	int					trigger_cnt;			// 被触发次数
 	IvsRuleInfo			ruleInfo;				//规则信息
	IvsRule()
	{
		memset(&ruleInfo, 0 , sizeof(ruleInfo));
		rule_id = 0;
		trigger_cnt = 0;
	}
};

typedef std::map<int,IvsRule*>		IvsRuleMap;		// 规则ID ==> 规则
typedef DH_RECT				IvsRect;
typedef std::list<CFG_POLYLINE>		IvsLocusSeg;	// 一段运动轨迹
typedef std::list<IvsLocusSeg>		IvsLocus;		// 目标运动轨迹

struct IvsObject
{
	int					object_id;			// 运动目标ID
	int					opt_type;			// 操作分为三类：新增物体(1), 增加物体轨迹点(2)，删除物体(3)，隐藏物体轨迹(4),其它值无效
	int					alarm_cnt;			// 运动目标报警计数
	int					display_cnt;		// 运动目标显示计数
	IvsRect				obj_rect;			// 运动目标外框
 	IvsLocus			obj_locus;			// 运动轨迹
};

typedef std::map<int,IvsObject>		IvsObjectMap;	// 运动目标ID ==> 运动目标

// 智能通道信息
struct IvsChnlInfo
{
	LONG				dev_id;				// 设备ID
	int					chnl_idx;			// 通道序号
	BOOL				bEnableIvs;			// 通道是否启用智能分析功能
	BOOL				bAtm;				// 是ATM设备吗?
	BYTE				bPreset;			// 场景号

	/*
		使用哪个解码端口的轨迹信息:
		一个设备通道可能被多次打开,有多个实时监视在进行,其中的轨迹信息应该都是一样的,
		所以只使用其中一个实时监视中的轨迹信息就可以了.本字段指示使用哪个解码端口上报的轨迹信息.
	*/
	int					live_dec_id;
	IvsRuleMap			rule_map;			// 规则表
	IvsObjectMap		mapId2Obj;			// 运动目标列表
};

struct ReloadIvsRuleReq
{
	LONG				devHandle;
	int					nChnlIdx;
	bool				bReloadCfg;
	bool				bAddNew;
	int					nDecPort;
	HWND				hVideoWnd;
	int					nChnlCnt;
};

class CIvsModule : public CWnd
{
public:
	// 打开设备通道时获取其智能分析规则
	static int OnOpenDeviceRealplay(LONG lDevHandle,int nChnlIdx,int nDecoderPort,HWND hwnd,int nChnlCnt);
	static void ReloadIvsRuleProc(ReloadIvsRuleReq* pReq);
	static int GetDeviceIvsConfig(DEV_INFO& devInfo);
	static int GetRulesMaxStructSize(DWORD *pRulesTypes, int nRuleNum);

	// 重新读取智能分析通道规则
	static int ReloadChannelIvsRule(LONG lDevHandle,DEV_INFO &devInfo,int nChnlIdx,
		bool bAddNew = true,int  nDecPort = -1);

	// 绘制规则和运动目标(轨迹和外框)
	static int DrawIvsRuleProc(IvsChnlInfo* pChnlInfo,HDC hdc);
	static void DrawIvsRule(IvsRule* pIvsRule,HDC hdc);
	static int DrawIvsObjectProc(IvsChnlInfo* pChnlInfo,IvsDecodeInfo* pDecInfo,HDC hdc);
	
	// 绘制箭头
	static void DrawDirectionArrow(HDC hdc,POINT ptStart,POINT ptEnd,int nDirection,HRGN hrgn = NULL);

	static void DrawIvsObjectLocus(IvsObject* pIvsObj, HDC hdc);
	static void DrawIvsObjectBoundBox(IvsObject* pIvsObj, HDC hdc);


	static void __stdcall GetIvsInfoProc(char* buf, long type, long len, long reallen, void* reserved, void* nUser);
	static void __stdcall DrawIvsInfoProc(long nPort,HDC hdc,LONG nUser);

	static BOOL Init();
	static BOOL UnInit();

	static void ClearData();
protected:
private:
	CIvsModule(){}
	virtual ~CIvsModule();
	static void* AllocateMemory(UINT nSize);
	static void FreeMemory(void* pMem);

private:
	static HANDLE								m_hIvsHeap;
	static std::map<int,IvsDecodeInfo>			m_decode_info_map;		// 解码端口号 ==> 解码信息
	static std::list<IvsChnlInfo>				m_chnl_info_list;		// 通道信息表
	static CRITICAL_SECTION						m_cs;
};