
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the IVSDRAWER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// IVSDRAWER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifdef IVSDRAWER_EXPORTS
#define IVSDRAWER_API __declspec(dllexport)
#else
#define IVSDRAWER_API __declspec(dllimport)
#endif
#ifndef IVS_DRAWER_H
#define IVS_DRAWER_H



#include <windows.h>
#include <time.h>
#include "dhnetsdk.h"
#include "dhconfigsdk.h"


/*画笔样式宏*/
#define DRAW_PEN_SOLID            PS_SOLID
#define DRAW_PEN_DASH             PS_DASH       /* -------  */
#define DRAW_PEN_DOT              PS_DOT       /* .......  */
#define DRAW_PEN_DASHDOT          PS_DASHDOT       /* _._._._  */
#define DRAW_PEN_DASHDOTDOT       PS_DASHDOTDOT      /* _.._.._  */
#define DRAW_PEN_NULL             PS_NULL
#define DRAW_PEN_INSIDEFRAME      PS_INSIDEFRAME
#define DRAW_PEN_USERSTYLE        PS_USERSTYLE
#define DRAW_PEN_ALTERNATE        PS_ALTERNATE
#define DRAW_PEN_DEFAULT		  0xffffffff


#define IVS_DATA_DEFAULT		0xffffffff
#define IVS_MAX_EVENT_NUM 32
#define IVS_MAX_TTL				0xff

enum{
	DRAW_JSON = 0,
		DRAW_TRACK,
		DRAW_ALARM,
		DRAW_RULE,
		DRAW_END = 20
};

enum
{
	IVS_LINGER = 0,				//int 
	IVS_TRACKTAIL,				//轨迹尾巴
	IVS_GET_OBJECT,
	IVS_DISABLE_VIDEO_TIME,		//禁止视频浓缩的时间 INT 默认开启
	IVS_DISABLE_VIDEO_OBJECT,
	IVS_MODIFY_OBJECT_RGB,		//Dword
	IVS_TRACK_OBJECT,
	IVS_SET_PEN_HEIGHT
};

#define MAX_OBJECT_NUM	16

typedef struct IVS_CONFIG_EVENT
{
	char szEventName[MAX_NAME_LEN];			// 事件名称,详见"事件类型列表"
	char szRuleName[MAX_NAME_LEN];			// 规则名称,不同规则不能重名
	DH_MSG_OBJECT		stuObject;
	char		Context[28];
	int		alarmAction;					//netsdk一致
	int		alarmType;
	
} IVS_CONFIG_EVENT_INFO;

typedef struct IVS_CONFIG_EVENTEX
{
	char szEventName[MAX_NAME_LEN];			// 事件名称,详见"事件类型列表"
	char szRuleName[MAX_NAME_LEN];			// 规则名称,不同规则不能重名
	char Context[28];					
	int		alarmAction;					//netsdk一致				
	int		alarmType;
	int					nObjectNum;
	DH_MSG_OBJECT		stuObject[MAX_OBJECT_NUM];						// 检测到的物体
	int					nContext;
	void*				pContext;
} IVS_CONFIG_EVENT_INFOEX;

typedef struct 
{
	int					nEventsNum;								// 视频分析规则数
	IVS_CONFIG_EVENT_INFO stuEventInfo[IVS_MAX_EVENT_NUM]; //事件信息
	
} IVS_CFG_ANALYSEVENTS_INFO;

typedef struct 
{
	int					nEventsNum;								// 视频分析规则数
	IVS_CONFIG_EVENT_INFOEX stuEventInfo[IVS_MAX_EVENT_NUM]; //事件信息
	
} IVS_CFG_ANALYSEVENTS_INFOEX;


typedef struct
{
	int objectid;
	struct tm startTime;
	struct tm endTime;
	char	cReverd[12];
}IVSOBJECT;

union ObjectContex
{
	IVSOBJECT object;
	POINT	  xPt;
};


#define CALLMETHOD __stdcall

#ifdef __cplusplus
extern "C" {
#endif

IVSDRAWER_API int CALLMETHOD DRAW_Startup();

IVSDRAWER_API void CALLMETHOD DRAW_Cleanup();

//------------------------------------------------------------------------
// 函数: DRAW_Open
// 描述: 打开作图
// 参数: nPort,作图端口.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
IVSDRAWER_API BOOL CALLMETHOD DRAW_Open(int nPort);

//------------------------------------------------------------------------
// 函数: DRAW_Close
// 描述: 关闭作图
// 参数: nPort,作图端口.
// 返回: void
//------------------------------------------------------------------------
IVSDRAWER_API void CALLMETHOD DRAW_Close(int nPort);

//------------------------------------------------------------------------
// 函数: DRAW_Reset
// 描述: 重置作图
// 参数: nPort,作图端口.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
IVSDRAWER_API BOOL CALLMETHOD DRAW_Reset(int nPort,int type);

//------------------------------------------------------------------------
// 函数: DRAW_InputJsonData
// 描述: 放入Json格式的智能帧数据.
// 参数: nPort,作图端口.
//		 pJsonData,json字符串
//		 nDataLen,json字符串的长度
// 返回: int,小于0失败,调用DRAW_GetLastError查询失败错误码;其它表示成功.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_InputJsonData(int nPort, unsigned char* pJsonData, int nDataLen,int nFrame);



//------------------------------------------------------------------------
// 函数: DRAW_InputRuleData
// 描述: 放入规则数据.
// 参数: nPort,作图端口.
//		 nType,类型:
//		 pRuleData,规则数据结构体
//		 nDataLen,数据长度
// 返回: int,小于0失败,调用DRAW_GetLastError查询失败错误码;其它表示成功.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_InputRuleData(int nPort, int nType, unsigned char* pRuleData, int nDataLen);

//------------------------------------------------------------------------
// 函数: DRAW_InputTrackData
// 描述: 放入轨迹数据.
// 参数: nPort,作图端口.
//		 nType,类型,轨迹信息有两种结构体类型.
//		 pTrackData,轨迹数据结构体
//		 nDataLen,数据长度
//       nFrameNum 视频帧号
// 返回: int,小于0失败,调用DRAW_GetLastError查询失败错误码;其它表示成功.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_InputTrackData(int nPort, int nType, unsigned char* pTrackData, int nDataLen,int nFrameNum);


//------------------------------------------------------------------------
// 函数: DRAW_InputAlarmData
// 描述: 放入报警数据.
// 参数: nPort,作图端口.
//		 nType,类型,轨迹信息有两种结构体类型.
//		 pAlarmData,报警数据结构体
//		 nDataLen,数据长度
// 返回: int,小于0失败,调用DRAW_GetLastError查询失败错误码;其它表示成功.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_InputAlarmData(int nPort, int nType, unsigned char* pAlarmData, int nDataLen);

//------------------------------------------------------------------------
// 函数: DRAW_InputAlarmData
// 描述: 放入报警数据.
// 参数: nPort,作图端口.
//		 nType,类型,轨迹信息有两种结构体类型.
//		 pAlarmData,报警数据结构体
//		 nDataLen,数据长度
// 返回: int,小于0失败,调用DRAW_GetLastError查询失败错误码;其它表示成功.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_InputAlarmDataEx(int nPort, int nType, unsigned char* pAlarmData, int nDataLen);

//------------------------------------------------------------------------
// 函数: DRAW_Draw
// 描述: 作图.
// 参数: nPort,作图端口.
//		 hDC,作图上下文句柄
// 返回: int,小于0失败,调用DRAW_GetLastError查询失败错误码;其它表示成功.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_Draw(int nPort, HDC hDC,HWND hwnd,int nFrameNum);

//------------------------------------------------------------------------
// 函数: DRAW_SetLifeCount
// 描述: 设置轨迹生命计数.
// 参数: nPort,作图端口.
//		 nLifeCount,生命计数
// 返回: int,小于0失败,调用DRAW_GetLastError查询失败错误码;其它表示成功.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_SetLifeCount(int nPort, int type,int nLifeCount);

//------------------------------------------------------------------------
// 函数: DRAW_SetEnable
// 描述: 设置使能.
// 参数: nPort,作图端口.
//		 nType,类型
//		 bEnable,使能
// 返回: int,小于0失败,调用DRAW_GetLastError查询失败错误码;其它表示成功.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_SetEnable(int nPort, int nType, BOOL bEnable);

//------------------------------------------------------------------------
// 函数: DRAW_SetPen
// 描述: 设置作图画笔.
// 参数: nPort,作图端口.
//		 nType,类型
//		 nPenStyle,画笔样式,见"画笔样式宏"
//		 nWidth,画笔宽度
//		 crColor,画笔颜色		 
// 返回: int,！=0失败,调用DRAW_SetPen查询失败错误码;其它表示成功.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_SetPen(int nPort, int nType, int nPenStyle, int nWidth, COLORREF crColor);

//------------------------------------------------------------------------
// 函数: DRAW_GetLastError(目前不支持)
// 描述: 获取最后的错误码
// 参数: nPort,作图端口.	 
// 返回: int,返回错误码.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_GetLastError(int nPort);

//------------------------------------------------------------------------
// 函数: DRAW_Ioctl
// 描述: 
// 参数: nPort,作图端口.	
//		cmdType 命令号
//		context 相对应结构体地址
//		len		结构体的长度
// 返回: int,返回错误码.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_Ioctl(int nPort,int cmdType,void* context,int len);


//------------------------------------------------------------------------
// 函数: DRAW_InputJpegData
// 描述: 获取最后的错误码
// 参数: nPort,作图端口.	
// 返回: int,返回错误码.
//------------------------------------------------------------------------
IVSDRAWER_API int  CALLMETHOD DRAW_InputJpegData(int nPort, int nType, unsigned char* pJpegData, int nDataLen,int nFrameNum);



//------------------------------------------------------------------------
// 函数: DRAW_Idle
// 描述: 
// 参数: nPort,作图端口.	
// 返回: void
IVSDRAWER_API void CALLMETHOD DRAW_Idle(int nPort);

#ifdef __cplusplus
}
#endif

#endif