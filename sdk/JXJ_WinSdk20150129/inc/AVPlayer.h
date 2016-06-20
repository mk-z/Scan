
#ifndef	__AV_PLAYER_H__
#define	__AV_PLAYER_H__

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the AVPLAYER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// AVPLAYER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef AVPLAYER_EXPORTS
#define AVPLAYER_API extern "C" __declspec(dllexport)
#else
#define AVPLAYER_API extern "C" __declspec(dllimport)
#endif

#define	AVP_CODER_GEN			"GenCodec.dll"	// 通用解码器
#define	AVP_CODER_JXJ			"jxjcodec.dll"	// 佳信捷解码器
#define	AVP_CODER_HI			"HICoder.dll"	// 海思解码器
#define	AVPDisDevStrLen			124				// 显示设备名称长度

// 协议类型 begin
#define AVP_PROTOCOL_JXJ		0x204A584A
#define AVP_PROTOCOL_JPF		0x204A5046
#define AVP_PROTOCOL_LWZ		0x205a574c
// 协议类型 begin

// 定义错误码 begin
typedef enum
{
	AVPErrSuccess		= 0,			// 成功
	AVPErrUnInit		= -1,			// 未初始化
	AVPErrHandle		= -2,			// 句柄不存在
	AVPErrFile			= -3,			// 文件打开失败
	AVPErrParam			= -4,			// 参数错误
	AVPErrBuffSize		= -5,			// 缓存满
	AVPErrLoadCoder		= -6,			// 加载解码器失败
	AVPErrNoMem			= -7,			// 内存不足
	AVPErrNoFreePort	= -8,			// 没有空闲通道
	AVPErrReaderFormat	= -9,			// 数据格式不存在
	AVPErrRecMaxSize	= -10,			// 录像文件已经写满(指定预分配大小时)
	AVPErrRecMaxTime	= -11,			// 录像文件已经写满(指定文件时长时)
}AVPErr;
// 定义错误码 end

// 定义流类型 begin
typedef enum
{
	AVPStreamUndef		= 0,			// 未定义
	AVPStreamFile		= 1,			// 文件流
	AVPStreamReal		= 2,			// 实时流
	AVPStreamPlayback	= 3,			// 回放流
}AVPStreamType;
// 定义流类型 end

// 定义播放状态 begin
typedef enum
{
	AVPPlayStatusStop	= 0,			// 停止
	AVPPlayStatusRun	= 1,			// 运行
	AVPPlayStatusIdle	= 2,			// 闲置
}AVPPlayStatus;
// 定义播放状态 end

// 定义播放速度 begin
typedef enum
{
	AVPPlaySpeed_16X	= 0x01,			// 快16倍速
	AVPPlaySpeed_8X		= 0x02,			// 快8倍速
	AVPPlaySpeed_4X		= 0x03,			// 快4倍速
	AVPPlaySpeed_2X		= 0x04,			// 快2倍速

	AVPPlaySpeed_1X		= 0x5,			// 正常速度

	AVPPlaySpeed_1_2X	= 0x06,			// 慢2倍速
	AVPPlaySpeed_1_4X	= 0x07,			// 慢4倍速
	AVPPlaySpeed_1_8X	= 0x08,			// 慢8倍速
	AVPPlaySpeed_1_16X	= 0x09,			// 慢16倍速


	AVPPlaySpeed_0_1X	= 0x20,			// 快2倍速退
	AVPPlaySpeed_0_2X	= 0x21,			// 快2倍速退
	AVPPlaySpeed_0_4X	= 0x22,			// 快4倍速退
	AVPPlaySpeed_0_8X	= 0x23,			// 快8倍速退
	AVPPlaySpeed_0_16X	= 0x24,			// 快16倍速退
	AVPPlaySpeed_0_32X	= 0x25,			// 快32倍速退
}AVPPlaySpeed;
// 定义播放速度 end

// 定义放缩类型 begin
typedef enum
{
	AVPScaleNone		= 0x0,			// 不放缩
	AVPScaleFull		= 0x1,			// 全屏放缩
	AVPScaleKeep		= 0x2,			// 保持原比例
	AVPScale4_3			= 0x3,			// 4:3放缩
	AVPScale16_9		= 0x4,			// 16:9放缩
}AVPScaleType;
// 定义放缩类型 end

// 定义回调类型 begin
typedef enum
{
	AVPDecCBTypeNone	= 0,			// 无
	AVPDecCBTypeAudio16	= 1,			// 音频.采样率16khz,单声道,每个采样点16位表示
	AVPDecCBTypeRGB32	= 2,			// 视频.每像素4字节,排列方式与位图相似,"BGR0",第一个像素位于图像左下角 
	AVPDecCBTypeYV12	= 3,			// 视频,yv12格式.排列顺序"Y0Y1...","V0V1...","U0U1..."
	AVPDecCBTypeUYVY	= 4,			// 视频,uyvy格式.排列顺序"U0Y0V0Y1U2Y2V2Y3......",第一个像素位于图像左上角
	AVPDecCBTypeYUV420	= 5,			// 视频,YUV420格式.排列顺序"Y0Y1...","U0U1...","V0V1..."
	AVPDecCBTypeYUYV	= 6,			// 视频,yuy2或yuyv格式.排列顺序"Y0 U0 Y1 V0 Y2 U2 Y3 V2 ... ... ",第一个像素位于图像左上角.
}AVPDecCBType;
// 定义回调类型 end

// 定义端口回调消息 begin
typedef enum 
{
	AVPPlayCBUnknow		= 0,			// 未知消息
	AVPPlayCBError		= 1,			// 通知 错误 消息,返回值无具体意义
	AVPPlayCBStart		= 2,			// 通知 开始播放 消息,返回值无具体意义,lParam=文件的开始时间
	AVPPlayCBEnd		= 3,			// 已经弃用的消息
	AVPPlayCBFrame		= 4,			// 通知 帧时间发生变化(秒) 消息,返回值无具体意义,lParam=当前时间
	AVPPlayCBStop		= 5,			// 通知 结束播放 消息,返回值无具体意义,lParam=空
	AVPPlayCBPause		= 6,			// 通知 继续播放 消息,返回值无具体意义,lParam=文件已播放时间
	AVPPlayCBContinue	= 7,			// 通知 继续播放 消息,返回值无具体意义,lParam=文件已播放时间
	AVPPlayCBSpeed		= 8,			// 通知 播放速度 消息,返回值无具体意义,lParam=当前播放速度
}AVPPlayCBMsg;
// 定义端口回调消息 end

// 定义文件播放结束时的处理动作 begin
typedef enum
{
	AVPOnEndFileClose	= 0x0,			// 关闭
	AVPOnEndFileReopen	= 0x1,			// 重新打开
	AVPOnEndFileNext	= 0x2,			// 下一文件
}AVPOnEndFileAction;
// 定义文件播放结束时的处理动作 end

// 定义视频播放模式 begin
typedef enum
{
	AVPPlayRealTime		= 0x0,			// 实时优先
	AVPPlaySmooth		= 0x1,			// 流畅优先
}AVPPlayPriority;
// 定义视频播放模式 end

// 定义录像文件转换格式 begin
typedef enum
{
	AVPConverUnknown	= 0,			// 未定义
	AVPConverTrunk		= 1,			// 从预分配的录像中抽取
	AVPConverMKV		= 2,			// 转换为MKV格式
	AVPConverAVI		= 3,			// 转换为AVI格式(暂时不支持)
}AVPConverType;
// 定义录像文件转换格式 end

// 显示设备定义 begin
typedef struct stDisplayDev
{
	GUID			stGUID;								// 显示设备之GUID
	char			szDescription[AVPDisDevStrLen];		// 显示设备之描述
	char			szDriveName[AVPDisDevStrLen];		// 显示设备之驱动名称
	RECT			rcMonitor;							// 显示器的区域
	RECT			rcWork;								// 显示器的工作区域
	DWORD			dwFlags;							// 显示器的标志位,MONITORINFOF_PRIMARY 表示为主显示屏
	DWORD			dwData;								// 私有数据域
	stDisplayDev()
	{
		memset(&stGUID,0,sizeof(GUID));					// 显示设备之GUID
		memset(szDescription,0,AVPDisDevStrLen);		// 显示设备之描述
		memset(szDriveName,0,AVPDisDevStrLen);			// 显示设备之驱动名称
		memset(&rcMonitor,0,sizeof(RECT));				// 对应显示器信息
		memset(&rcWork,0,sizeof(RECT));					// 对应显示器信息
		dwFlags		= NULL;								// 对应显示器信息
		dwData		= NULL;								// 私有数据域
	}
}* PSTDisplayDev;
// 显示设备定义 end

// 解码回调函数所用参数 begin
typedef struct stDecFrameCB
{
	int			iPort;					// 解码通道号
	LPBYTE		lpBuf;					// 解码后的数据
	long		lSize;					// 解码后数据长
	long		lWidth;					// 宽
	long		lHeight;				// 高
	long		lStamp;					// 帧时间
	long		lType;					// AVPDecCBType
	long		lParam;					// 用户自定义参数
	DWORD		dwRes0;					// 保留数据0
	DWORD		dwRes1;					// 保留数据1
	DWORD		dwRes2;					// 保留数据2
	DWORD		dwRes3;					// 保留数据3
}* PSTDecFrameCB;
// 解码回调函数所用参数 end

// 显示回调函数所用参数 begin
typedef struct stDisplayCB
{
	long		lpWnd;					// CWnd*
	void*		hDC;					// HDC
	RECT		rtTag;					// 目标区域
	RECT		rtSrc;					// 源区域
	int			iScaleType;				// 放缩类型
	time_t		tDevTime;				// 设备时间
}* PSTDisplayCB;
// 显示回调函数所用参数 end

// 文件结束回调函数所用参数 begin
typedef struct stFileEndCB
{
	int			iPort;					// 解码通道号
	char		szNextPath[MAX_PATH];	// 下一文件路径
	long		lOffset;				// 偏移位置
	AVPOnEndFileAction	eAction;		// 下一操作动作
	DWORD		dwUserData;				// 用户参数
}* PSTFileEndCB;
// 文件结束回调函数所用参数 end

// 录像文件格式转换回调函数所用参数 begin
typedef struct stConverRecCB
{
	int			iPort;					// 解码通道号
	AVPConverType eType;				// 转换类型
	int			iStop;					// 是否结束
	int			iPercent;				// 百分比
	void*		pUserData;				// 用户参数
}* PSTConverRecCB;
// 录像文件格式转换回调函数所用参数 end

// 回调函数 begin
// 录音回调函数
typedef void (CALLBACK fcbPickAudio)(const BYTE* pBuffer, DWORD dwBufSize, void* pUserData);
// 解码回调函数,0表示继续处理,1表示不能继续处理
typedef int(CALLBACK fcbDecFrame)(PSTDecFrameCB pstDecFrameCB);
// 显示回调函数,0表示继续处理,1表示不能继续处理
typedef int(CALLBACK fcbDisplay)(PSTDisplayCB pstDisplayCB);
// 播放回调函数
typedef int(CALLBACK fcbPlay)(AVPPlayCBMsg eMsg,int iPlayerID,LPARAM lpUserParam,__int64 lParam);
// 文件播放结束时回调函数
typedef void(CALLBACK fcbOnEndFile)(int iPort,PSTFileEndCB pstFileEnd);
// 录像文件格式转换回调函数,返回0表示继续,返回1表示结束
typedef int(CALLBACK fcbOnConverFile)(int iPort,PSTConverRecCB pstConver);
// 额外OSD信息显示回调函数,返回0表示进行了设置,返回1表示没有进行设置
typedef int(CALLBACK fcbOnDrawExtOsd)(HDC hDC,long lWidth,long lHeight,LPCTSTR lpszOSD,DWORD dwTime,void* pUserData);
// 回调函数 end


// 系统操作 begin
// 初始化
AVPLAYER_API int AVP_Init();
// 初始化录像管理模块
AVPLAYER_API int AVP_InitRecMng(int iCount,int iBufMBs);
// 初始化抓拍管理模块
AVPLAYER_API int AVP_InitCaptureMng(int iCount,LPCTSTR lpszCoderPath);
// 注销操作
AVPLAYER_API int AVP_Cleanup();
// 获取所有的显示设备,返回设备列表的总大小
AVPLAYER_API int AVP_GetDisplayDevList(PSTDisplayDev pstDisDev,int iCount);
// 系统操作 end


// 便利函数 begin
// 获取文件信息
AVPLAYER_API int AVP_GetFileInfo(LPCTSTR lpszFilePath, time_t* plStart, time_t* plEnd, long* plSize, long* plProtocal, long* plEncoder);
// 获取文件头内容,仅用于创建录像文件
AVPLAYER_API int AVP_GetFileHeadContent(LPTSTR lpszFileHead);
// 便利函数 end


// 音频采集操作 begin
// 开始音频采集
AVPLAYER_API BOOL AVP_StartPickAudio(UINT nSamples,BOOL bAddHeader,fcbPickAudio* fcb,void* pUserData);
// 结束音频采集
AVPLAYER_API BOOL AVP_StopPickAudio();
// 音频采集操作 end


// 通道管理 begin
// 创建播放器
AVPLAYER_API int AVP_GetFreePort();
// 释放播放器
AVPLAYER_API int AVP_ReleasePort(int iPort);
// 设置解码器类型
AVPLAYER_API int AVP_SetCoder(int iPort, LPCTSTR lpszCoderName);
// 获取解码器类型
AVPLAYER_API int AVP_GetCoder(int iPort, LPTSTR lpszCoderName);
// 设置数据协议(格式头)
AVPLAYER_API int AVP_SetDataProtocol(int iPort, DWORD dwProtocol);
// 获取数据协议(格式头)
AVPLAYER_API DWORD AVP_GetDataProtocol(int iPort);
// 返回流类型
AVPLAYER_API int AVP_GetStreamType(int iPort);
// 返回播放状态
AVPLAYER_API int AVP_GetPlayStatus(int iPort);
// 通道管理 end


// 解码操作 begin
// 加入一帧
AVPLAYER_API int AVP_PutFrame(int iPort, void* pFrame);
AVPLAYER_API int AVP_SetDecCallBack(int iPort, fcbDecFrame* pFun, long lParam);
// 解码操作 end


// 媒体输出类 begin
// 添加一个显示窗口
AVPLAYER_API int AVP_AddPlayWnd(int iPort, PSTDisplayDev pstDispDev,HWND hWnd,LPRECT lpDrawOffset,LPRECT lpSrcOffset);
// 删除一个显示窗口
AVPLAYER_API int AVP_DelPlayWnd(int iPort, HWND hWnd);
// 设置播放器位置
AVPLAYER_API int AVP_SetWndPosOffset(int iPort, int iPlayWndID, RECT* lpRect);
// 设置源位置及拉伸倍数
AVPLAYER_API int AVP_SetSrcPosOffset(int iPort, int iPlayWndID, RECT* lpRect);
// 获取播放器位置
AVPLAYER_API int AVP_GetWndPosOffset(int iPort, int iPlayWndID, RECT* lpRect);
// 获取源位置及拉伸倍数
AVPLAYER_API int AVP_GetSrcPosOffset(int iPort, int iPlayWndID, RECT* lpRect);
// 启用视频
AVPLAYER_API int AVP_EnableVideo(int iPort, BOOL bEnable);
// 视频是否启用
AVPLAYER_API BOOL AVP_IsVideoEnable(int iPort);
// 启用音频
AVPLAYER_API int AVP_EnableAudio(int iPort, BOOL bEnable);
// 音频是否启用
AVPLAYER_API BOOL AVP_IsAudioEnable(int iPort);
// 获取音量
AVPLAYER_API int AVP_GetVolume(int iPort);
// 设置音量
AVPLAYER_API int AVP_SetVolume(int iPort, int iVolume);
// 启用视频显示
AVPLAYER_API int AVP_EnableDisplay(int iPort, BOOL bEnable);
// 刷新窗口
AVPLAYER_API int AVP_RefreshDisplay(int iPort);
// 设置拉伸方式
AVPLAYER_API int AVP_SetScaleType(int iPort, int iPlayWndID, int iScaleType);
// 获取拉伸方式
AVPLAYER_API int AVP_GetScaleType(int iPort, int iPlayWndID);
// 抗裂痕
AVPLAYER_API BOOL AVP_SetNoTearing(int iPort, int iPlayWndID, BOOL bEnable);
// 获取当前抗裂痕设置
AVPLAYER_API BOOL AVP_IsNoTearing(int iPort, int iPlayWndID);
// 设置显示的回调函数
AVPLAYER_API int AVP_SetDisplayCallBack(int iPort, int iPlayWndID, fcbDisplay* pFun, PSTDisplayCB pstDisplayCB);
// 设置视频播放模式
AVPLAYER_API int AVP_SetPlayPriority(int iPort, int iPriorityType);
// 获取视频播放模式
AVPLAYER_API int AVP_GetPlayPriority(int iPort);
// 获取缓冲区内的帧数
AVPLAYER_API int AVP_GetBuffSpan(int iPort, int* piMaxSpan);
// 设置是否使用YUV输出
AVPLAYER_API int AVP_EnableYUVDraw(int iPort,BOOL bEnable);
// 获取是否使用YUV输出
AVPLAYER_API BOOL AVP_IsYUVDrawEnable(int iPort);
// 设置额外OSD信息显示回调函数
AVPLAYER_API BOOL AVP_SetDrawExtOsd(fcbOnDrawExtOsd* pcbDrawExtOsd,void* pData);
// 清空缓存
AVPLAYER_API int AVP_ClearBuff(int iPort);
// 媒体输出类 end


// 录像文件操作 begin
// 写文件 begin
// 创建录像文件,指定文件大小,0 表示不预分配
AVPLAYER_API int AVP_CreateRecFileSize(LPCTSTR lpszPath,DWORD dwProtocol,DWORD dwEncoder,long lFileMaxSize);
// 创建录像文件
AVPLAYER_API int AVP_CreateRecFile(LPCTSTR lpszPath,DWORD dwProtocol,DWORD dwEncoder);
// 创建录像文件,指定文件时长(秒),0 表示不进行限制
AVPLAYER_API int AVP_CreateRecFileTime(LPCTSTR lpszPath,DWORD dwProtocol,DWORD dwEncoder,long lFileMaxTime);
// 写入录像
AVPLAYER_API int AVP_WriteRecFile(int iFile,void* lpFrame,int iFrameLen,void* lpBuf2,int iBufLen2);
// 关闭录像文件
AVPLAYER_API int AVP_CloseRecFile(int iFile);
// 文件格式转换
AVPLAYER_API int AVP_ConverJAV(LPCTSTR lpszSrc,LPCTSTR lpszTag,AVPConverType eType,DWORD dwRes,fcbOnConverFile* pFun,void* pUser);
// 停止文件格式转换
AVPLAYER_API int AVP_ConverStop(int iPort);
// 写文件 end
// 播放文件
AVPLAYER_API int AVP_PlayFileName(int iPort, LPCTSTR lpszPath,long lFileOffset);
// 获取总帧数
AVPLAYER_API DWORD AVP_GetTotalFrame(int iPort);
// 获取当前帧数
AVPLAYER_API DWORD AVP_GetCurFrame(int iPort);
// 获取帧率
AVPLAYER_API int AVP_GetFrameRate(int iPort);
// 获取文件总时长
AVPLAYER_API DWORD AVP_GetFileTotalTimeS(int iPort);
// 获取文件的开始播放时间
AVPLAYER_API time_t AVP_GetFileStartTimeS(int iPort);
// 获取当前播放时长
AVPLAYER_API DWORD AVP_GetCurPlayTimeS(int iPort);
// 获取当前OSD信息
AVPLAYER_API LPCTSTR AVP_GetCurOSD(int iPort);
// 获取当前写入时间
AVPLAYER_API DWORD AVP_GetCurFrameWriteTime(int iPort);
// 设置当播放文件结束时的回调函数
AVPLAYER_API int AVP_SetOnEndFileCallBack(int iPort, fcbOnEndFile* pFun,LPARAM lpParam);
// 录像文件操作 end


// 媒体播放控制操作 begin
// 播放
AVPLAYER_API int AVP_Play(int iPort);
// 暂停
AVPLAYER_API int AVP_Pause(int iPort);
// 停止
AVPLAYER_API int AVP_Stop(int iPort);
// 抓图
AVPLAYER_API int AVP_Capture(int iPort, LPCTSTR lpszPath);
// 下一帧
AVPLAYER_API int AVP_NextFrame(int iPort);
// 移动到指定位置
AVPLAYER_API int AVP_Seek(int iPort, DWORD dwTime);
// 设置播放速度
AVPLAYER_API int AVP_SetPlaySpeed(int iPort, int iSpeed);
// 获取当前播放速度
AVPLAYER_API int AVP_GetPlaySpeed(int iPort);
// 设置播放的回调函数
AVPLAYER_API int AVP_SetPlayCallBack(int iPort, fcbPlay* pFun,LPARAM lpParam);
// 媒体播放控制操作 end

// 抓拍通道操作 begin
// 创建抓拍通道
AVPLAYER_API int AVP_CreateCapture(DWORD dwProtocol,DWORD dwEncoder);
// 向抓拍通道传入视频帧
AVPLAYER_API int AVP_PutCaptureFrame(int iPort, void* pFrame,LPCTSTR lpszOSD,DWORD dwWriteTime);
// 开始抓拍
AVPLAYER_API int AVP_CapturePort(int iPort, LPCTSTR lpszPath,BOOL bSync);
// 关闭抓拍通道
AVPLAYER_API int AVP_CloseCapture(int iPort);
// 抓拍通道操作 end

#endif		// __AV_PLAYER_H__
