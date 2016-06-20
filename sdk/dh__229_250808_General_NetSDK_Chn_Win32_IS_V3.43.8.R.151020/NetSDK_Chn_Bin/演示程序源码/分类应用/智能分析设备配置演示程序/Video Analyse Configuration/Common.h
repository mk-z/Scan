#if !defined _ITS_COMMON_H
#define  _ITS_COMMON_H


#define _CS 

#define WM_INSERTCOMBOX (WM_USER)
#define WM_UPDATESTATE	(WM_USER+1)

#define MAX_DETECT_LINE			8
#define MAX_ROAD_LINE			8
#define MAX_AREA				1
//**************************************
#define MAX_STOPLINE			8
#define MAX_PRELINE				8
#define MAX_POSTLINE			8
#define MAX_STOPLIGHTREGION		8
//***************************************

#define LIMIT_ANGLE  45	//离垂直线正负角度
#define CTRL_SPACING 30 //控件之间的间距

//绘制场景
enum SelectScene
{
	ssNone = -1,
	ssRoadLine ,     // 车道线
	ssDetectLine,       // 检测线
	ssDetectArea,       // 检测区域
// ***********************	
	ssStopLine,         // 停止线
	ssPreLine,          // 前置线
	ssPostLine,         // 后置线
	ssStopLightRegion,  // 红灯区
// *************************
};


#define 	eRoadLine   0       // 车道线
#define 	eDetectLine 1       // 检测线
#define 	eDetectArea 2       // 检测区域
// *****************	 
#define 	eStopLine   3       // 停止线
#define		ePreLine    4       // 前置线
#define  	ePostLine   5       // 后置线
#define 	eStopLightRegion 6  // 红灯区
// ******************
#define     eText        7      // 文字
#define     eTrackRegion 8      // 跟踪区域

struct   CVSPoint   
{   
	double   m_dX;   
	double   m_dY;   
};

typedef struct
{
	int		nDirect;	//方向
	char*	pName;		//名称
}MODIFY_DATA;

const double PI = 3.1415926;


#endif