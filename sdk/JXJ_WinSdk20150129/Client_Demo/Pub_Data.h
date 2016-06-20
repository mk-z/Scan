#pragma once

#include "IniFile.h"

//全局
class CPub_Data
{
public:
	CPub_Data(void);
	virtual ~CPub_Data(void);

public:
	CStringArray g_strArrayLoginIp;
	CStringArray g_strArraySavedIp;//已经添加的设备IP
	CStringArray g_strArrayPlaySuccessIp;  //播放成功的IP

	int g_iWarnIpIndex;
	int g_iCountDevice;            //添加的设备数量
	HTREEITEM     g_hAddItem[GET_MAX_DEV_NUM];   //正在添加的节点

	CString g_strUser;             //设备登陆用户名
	CString g_strPassword;       // 设备登陆密码
	int g_iDevicePort;          //设备端口号

	int g_iChancel[GET_MAX_DEV_NUM];   //视频播放通道号
	int g_iIsPlayNum;              //正在播放的窗口数

	bool g_bOpenStreamInAttribute;
	
	CString g_strLoginIp;       //登陆的IP

	int g_iStaticScreenWidth;       //静态窗口的宽
	int g_iStaticScreenHeight;		//静态窗口的高
	int g_iCutScreenNum;          //分割的窗口数
	int g_iCutScreenWidth;         //分割的窗口的宽
	int g_iCutScreenHeight;		//分割的窗口的高

	CRect g_RectDlg ;           //主窗体位置
	int g_iMainWindowX;         //主窗体基于屏幕的坐标X
	int g_iMainWindowY;			//主窗体基于屏幕的坐标Y
	int g_iMainWindowW;         //主窗体基于屏幕的坐标width
	int g_iMainWindowH;			//主窗体基于屏幕的坐标height

	int g_iMoveX;        //静态框基于对话框 x 位置
	int g_iMoveY;       //静态框基于对话框 y 位置
	int g_iStaticToScreenX; //静态框基于屏幕 x 位置
	int g_iStaticToScreenY;//静态框基于屏幕 y 位置
	
	int g_iAttributeIng;    //正在进行属性设置的窗口

	int g_iCountPerson[GET_MAX_DEV_NUM]; //绊线统计人数

	int g_iStreamType[GET_MAX_DEV_NUM];
	long g_vLoginHandle[GET_MAX_DEV_NUM];
	long g_vStreamHandle[GET_MAX_DEV_NUM];
	long g_vTalkHandle[GET_MAX_DEV_NUM];

	int g_iCountHide[GET_MAX_DEV_NUM];    //遮挡区域数量
	int g_iCountInterset[GET_MAX_DEV_NUM]; //感兴趣区域数量
	int g_iCountHideAlarm[GET_MAX_DEV_NUM];  //遮挡报警区域数量
	int g_iCountMoveSense[GET_MAX_DEV_NUM];    //移动侦测区域数量
	HTREEITEM g_hTreeItem[GET_MAX_DEV_NUM];  //数的节点
	int g_iRecFileID[GET_MAX_DEV_NUM];    //录像ID
	int g_iPlayBack;                 //视频回放的窗口
	int g_iWarningCount;

	int g_iReplace;     //删除后替换下标
	int g_iDeleteDevice;  // 删除的设备下标
	int g_iFullScreenId;   //全屏的窗口
//////////////////////////////
	int g_iVideoTime1;      //保存时间
	int g_iVideoTime2;
	int g_iVideoTime3;
	int g_iVideoTime4;

	int g_iLanguageFlag;


	COleDateTime g_STime1;
	COleDateTime g_STime2;
	COleDateTime g_STime3;
	COleDateTime g_STime4;

	COleDateTime g_ETime1;
	COleDateTime g_ETime2;
	COleDateTime g_ETime3;
	COleDateTime g_ETime4;
/////////////////////////////////////
	int g_iShowTimeDlgFlag;    //调用设置时间对话框标记
	int m_iVideoIndex;
	CString g_StrPath;
	long g_setPos;
	BOOL g_bTalk[GET_MAX_DEV_NUM];
	BOOL g_DeviceClose[GET_MAX_DEV_NUM];  //设备是否断开

	int g_iDownIndex; //按下时的窗口
	bool g_bDragDown; //按下标志
	bool g_bAllFullScreen;
	int g_bUpgDeviceClose;  //是否升级中掉过线
	int g_iIoWarningChannelNul;
	int g_iChannelNo;
	JDevCap g_jDevCap[GET_MAX_DEV_NUM];//设备能力集



	int g_iDownLoadPos;

	/////////////////////////////////
	//0.代表osd 1.视频遮挡 2.图像参数 3.感兴趣区域 4.遮挡报警 5.移动侦测 6.丢失报警
	int g_iPlayWndFlag;			//	属性配置中打开带有视频的窗口标志 
	/////////////////////////////////

	long g_lRecodeStartTime[GET_MAX_DEV_NUM];  //录像开始时间
	long g_lRecodeEndTime[GET_MAX_DEV_NUM]; 
	long g_lFrameCount[GET_MAX_DEV_NUM];   //帧数

	BOOL FreeObj(void*  pObj);

	HDC g_drawHdc;
	int g_iServerFlag[GET_MAX_DEV_NUM];  //是否反向登陆标志
	int m_nDrawCount[GET_MAX_DEV_NUM];

	int  m_iJointActionChannel;
	int  m_iJointRecTime;
	int  m_iJointOut;
	int  m_iJointOutTime;
	int  m_iJointTakePicChannel;
	int  m_iJoinTakePicLever;
	int  m_iTakePicFtpUp;
	int  m_iTakePicCount;
	int  m_iJointVoice;
	int  m_iJointVoiceTime;
	int  m_iJointEmail;

	int g_iFormatProgress;
	int g_iControlDevRet;

	CString g_strSetMessage;
	CString g_strGetMessage;

	CIniFile g_iniFile;




	CString g_strTalkS;
	CString g_strTalkE;

	CString g_strRecordS;
	CString g_strRecordE;

	CString g_strListenS;
	CString g_strListemE;


	bool g_bHideAlarmDrawBorder;  //是否画框
	bool g_bMoveAlarmDrawBorder;
	bool g_bHideDrawBorder;
	bool g_bInterestDrawBorder;



	
};

extern CPub_Data g_PubData;