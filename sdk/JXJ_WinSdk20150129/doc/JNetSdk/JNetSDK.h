#ifndef	__JNET_SDK_H__
#define	__JNET_SDK_H__

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the JNETSDK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// JNETSDK_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#if (defined _WIN32) || (defined _WIN64)
	//#ifdef JNETSDK_EXPORTS
	//#define JNETSDK_API __declspec(dllexport)
	//#else
	//#define JNETSDK_API __declspec(dllimport)

	//#endif
	#define JNETSDK_API
#elif (defined __APPLE_CPP__) || (defined __APPLE_CC__)
	#ifdef JNETSDK_EXPORTS
	#define JNETSDK_API extern "C"
	#else
	#define JNETSDK_API
	#endif
#else// __ANDROID__
	#define JNETSDK_API extern "C"
#endif	// __ANDROID__


// 定义协议类型 begin
#define JNET_PRO_T				0x20000000			// 协议类型
#define JNET_PRO_T_JXJ			0x20000002			// JXJ类型
#define JNET_PRO_T_JPF			0x20000004			// JPF类型
#define	JNET_PRO_T_FILE			0x22000000			// 录像类型(录像回放)
#define	JNET_PRO_T_FILE_JAV		0x22000001			// JAV录像类型
// 协议类型 begin
#define JNET_READ_PRO_JXJ		0x204A584A			// JXJ类型
#define JNET_READ_PRO_JPF		0x204A5046			// JPF类型
#define JNET_READ_PRO_LWZ		0x205a574c			// LWZ类型
// 协议类型 begin
// 定义协议类型 end

// 定义错误码 begin
typedef enum
{
	JNETErrSuccess				= 0,		// 成功
	JNETErrUnInit				= -1,		// 未初始化
	JNETErrHandle				= -2,		// 句柄不存在
	JNETErrParam				= -3,		// 参数错误
	JNETErrBuffSize				= -4,		// 缓存满
	JNETErrNoMem				= -5,		// 内存不足
	JNETErrRecv					= -6,		// 接收错误
	JNETErrSend					= -7,		// 发送错误
	JNETErrOperate				= -8,		// 操作错误
	JNETErrURL					= -9,		// URL有误
	JNETErrLogining				= -10,		// 用户正在登录
	JNETErrLogout				= -11,		// 已经登出
	JNETErrNoFreePort			= -100,		// 没有空闲通道
	JNETErrProtocol				= -101,		// 协议错误
	JNETErrXMLFormat			= -102,		// 错误的XML数据
	JNETErrNotSupport			= -103,		// 不支持的操作
	JNETErrGetParam				= -104,		// 获取参数错误
	JNETErrSetParam				= -105,		// 设置参数错误
	JNETErrOpenFile				= -106,		// 打开文件出错
	JNETErrUpgOpen				= -107,		// 升级出错
}JNETErr;
// 定义错误码 end

typedef enum
{
	JNET_EET_UNKNOWN			= -1,		// 未定义
											
	JNET_EET_LOGINING			= 0,		// 正在登录
	JNET_EET_LOGIN_OK			= 1,		// 登录成功
	JNET_EET_LOGIN_ERROR		= 2,		// 登录失败
	JNET_EET_LOGOUT				= 3,		// 登出
	JNET_EET_STREAM_OPENING		= 4,		// 流正在打开
	JNET_EET_STREAM_OK			= 5,		// 流打开成功
	JNET_EET_STREAM_ERROR		= 6,		// 流打开失败
	JNET_EET_STREAM_CLOSE		= 7,		// 流关闭
	JNET_EET_PB_OPENING			= 8,		// 回放流正在打开
	JNET_EET_PB_OK				= 9,		// 回放流打开成功
	JNET_EET_PB_ERROR			= 10,		// 回放流打开失败
	JNET_EET_PB_CLOSE			= 11,		// 回放流关闭
	JNET_EET_TALK_OPENING		= 12,		// 对讲正在打开
	JNET_EET_TALK_OK			= 13,		// 对讲打开成功
	JNET_EET_TALK_ERROR			= 14,		// 对讲打开失败
	JNET_EET_TALK_CLOSE			= 15,		// 对讲关闭
	JNET_EET_UPG_START			= 16,		// 升级开始
	JNET_EET_UPG_OK				= 17,		// 升级成功
	JNET_EET_UPG_ERR			= 18,		// 升级失败
	JNET_EET_CFG_SET			= 100,		// 获取配置
	JNET_EET_CFG_GET			= 101,		// 设置配置
	JNET_EET_PTZ_CTRL			= 102,		// 云台控制
	JNET_EET_DEV_CTRL			= 103,		// 设备控制
	JNET_EET_STREAM_LOST		= 104,		// 流丢失
	JNET_EET_EVENT_NOTIFY		= 201,		// 报警事件
	JNET_EET_EVENT_REC_DOWN     = 303,      // 下载
}eJNetEvent;

typedef enum
{
	JNET_STREAM_CTRL_UNKNOWN		= 0,
	JNET_STREAM_CTRL_I_FRAME_REQ	= 0x1,	// I帧请求
}eJNetStreamCtrl;

typedef enum
{
	JNET_PB_CTRL_UNKNOWN		= 0,
	JNET_PB_CTRL_START			= 0x1,		// 开始回放
	JNET_PB_CTRL_STOP			= 0x2,		// 停止回放
	JNET_PB_CTRL_PAUSE			= 0x3,		// 暂停回放
	JNET_PB_CTRL_RESUME			= 0x4,		// 恢复回放
	JNET_PB_CTRL_FAST			= 0x5,		// 快放
	JNET_PB_CTRL_SLOW			= 0x6,		// 慢放
	JNET_PB_CTRL_NORMAL			= 0x7,		// 正常播放
	JNET_PB_CTRL_SET_SPEED		= 0x8,		// 设置播放速度
	JNET_PB_CTRL_GET_SPEED		= 0x9,		// 获取播放速度
	JNET_PB_CTRL_FRAME			= 0xa,		// 单帧放
	JNET_PB_CTRL_SET_TIME		= 0xb,		// 设置回放时间
	JNET_PB_CTRL_GET_TIME		= 0xc,		// 获取回放时间
}eJNetPBCtrl;

typedef enum
{

	JNETPlaySpeed_16X		= 0x01,			// 快16倍速
	JNETPlaySpeed_8X		= 0x02,			// 快8倍速
	JNETPlaySpeed_4X		= 0x03,			// 快4倍速
	JNETPlaySpeed_2X		= 0x04,			// 快2倍速

	JNETPlaySpeed_1X		= 0x05,			// 正常速度

	JNETPlaySpeed_1_2X		= 0x06,			// 慢2倍速
	JNETPlaySpeed_1_4X		= 0x07,			// 慢4倍速
	JNETPlaySpeed_1_8X		= 0x08,			// 慢8倍速
	JNETPlaySpeed_1_16X		= 0x09,			// 慢16倍速

}eJNetPlaySpeed;

typedef enum
{
	JNET_PROXY_UNKNOWN			= 0,
	JNET_PROXY_JCMS				= 1,		// CMS代理服务器
	JNET_PROXY_JSW				= 2,		// SW代理服务器
	JNET_PROXY_JPB				= 3,		// PB代理服务器
	JNET_PROXY_JMDS				= 4,		// 转发代理服务器
}eJNetProxyType;

typedef enum
{
	eJNetFrame_I				= 0x1,		// I帧
	eJNetFrame_P				= 0x2,		// P帧
	eJNetFrame_B				= 0x3,		// B帧
	eJNetFrame_A				= 0x4,		// 音频帧
	eJNetFrame_Str				= 0x5,		// 字幕帧
	eJNetFrame_Shape			= 0x6,		// 形状帧
	eJNetFrame_User				= 0xF,		// 用户自定义帧
}eJNetFrameType;

#define MAX_BUFFER_LEN			8192		// 每包接收的缓存,其实2KB足够
#define MAX_POST_ACCEPT			10			// 最大接入数
#define	MAX_GET_PARAM_SIZE		96			// 最大同时获取参数的个数

#define RTP_PORT_START			80800		// 起始流端口
#define RTP_PORT_COUNT			1000		// 流端口个数
#define MAX_URL_LEN				256			// URL长
#define JNET_IP_LEN				64			// IP长
#define JNET_NAME_LEN			64			// 名称长
#define JNET_PWD_LEN			64			// 密码长
#define JNET_DATA_LEN			512			// 数据域长

typedef int (__stdcall fcbJStream)(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam);										// 接收到信息的回调函数
typedef int (__stdcall fcbJEvent)(long lHandle, eJNetEvent eType,int iDataType,void* pEventData,int iDataLen,void* pUserParam);		// 事件回调函数
typedef int (__stdcall fcbJMBNotify)(long lHandle,DWORD dwPortocol,int iErr,int iMsgID,LPCTSTR lpszDstID,void* pData,int iDataLen,void* pUserParam);	// 广播回调
typedef int (__stdcall fcbJGetParam)(long lHandle,int iChn,int iParamID,void* lpData,int iDataLen,void* pUserParam);				// 获取参数的回调

// 代理参数
typedef struct stJProxyParam
{
	char			m_szIP[JNET_IP_LEN];			// 代理服务器的IP
	int				m_iPort;						// 代理服务器的端口
	char			m_szUser[JNET_NAME_LEN];		// 代理服务器的用户名
	char			m_szPwd[JNET_PWD_LEN];			// 代理服务器的密码
	eJNetProxyType	m_eType;						// 代理服务器类型
	int				m_iDataLen;						// 扩展数据域长
	char			m_szData[JNET_DATA_LEN];		// 扩展数据域
}* PSTJProxyParam;

// VVP2P参数
typedef struct stJP2PParam
{
	long m_lStreamPort;								// 流端口
	long m_lTalkPort;								// 对讲端口
}* PSTJP2PParam;

// 系统操作 begin
// 获取网络库的版本号
JNETSDK_API DWORD JNetGetVersion();
// 获取可用的SOCKET端口
JNETSDK_API int JNetGetValidSocketPort(bool bUdp);
// 获取所有的IPv4,返回IPv4列表<IP;>
JNETSDK_API LPCTSTR JNetGetIPv4List(int& iCount);
// 初始化
JNETSDK_API int JNetInit(LPCTSTR lpszLogName);
// 注销操作
JNETSDK_API int JNetCleanup();
// 系统操作 end

// 广播操作 begin
// 初始化
JNETSDK_API long JNetMBOpen(LPCTSTR lpszMuIP, int iMuPort,fcbJMBNotify* pfcbMBNotify,void* pUserParam,DWORD dwProtocol,long& lMBHandle);
// 注销操作
JNETSDK_API long JNetMBClose(long lMBHandle);
// 搜索操作
JNETSDK_API long JNetMBSearch(long lMBHandle,int iTimeOut);
// 设置操作
JNETSDK_API long JNetMBSet(long lMBHandle,int iMsgID,LPCTSTR lpszDstID,
						   LPCTSTR lpszUser,LPCTSTR lpszPsw,void* pData,int iDataLen,int iTimeOut);
// 广播操作 end

// 登录相关 begin
JNETSDK_API long JNetLoginEx(LPCTSTR lpszConn,fcbJEvent* pfcbEvent,void* pUserEvent,long& lLogin);
JNETSDK_API long JNetLogin(LPCTSTR lpszIP,int iDevPort,LPCTSTR lpszUser,LPCTSTR lpszPassword,
						   int iTimeOut,fcbJEvent* pfcbEvent,void* pUserParam,DWORD dwProtocol,long& lLogin,PSTJProxyParam pstProxy);
JNETSDK_API long JNetLogout(long lLogin);
JNETSDK_API DWORD JNetGetProtocol(long lLogin);
// 登录相关 end

// 流操作 begin
// 打开流,返回句柄
JNETSDK_API long JNetStreamOpen(long lLogin,int iChn,int iStreamID,int iProtocol,fcbJStream* pfcbStream,void* pUserData,long& lStream);
// 打开流,返回句柄
// lpszConn:Protocol=0x20000002;DevIP=;DevChn=;StreamID=;DevPort=;UserName=;Password=;Breath=;
// lpszConn:Protocol=0x20000004;URL=;
JNETSDK_API long JNetStreamOpenEx(LPCTSTR lpszConn,fcbJStream* pfcbStream,void* pUserStream,fcbJEvent* pfcbEvent,void* pUserEvent,long& lStream);
// 控制流,传入需要控制的值
JNETSDK_API long JNetStreamCtrl(long lStream,eJNetStreamCtrl eCtrlType,void* pCtrlData,int iDataLen);
// 关闭流,传入需要关闭的句柄
JNETSDK_API long JNetStreamClose(long lStream);
// 流操作 end

// 对讲操作 begin
// 打开对讲,返回句柄
JNETSDK_API long JNetTalkOpen(long lLogin,int iSamples,int iEncodeType,int iChannels,int iBits,fcbJStream* pfcbStream,void* pUserData,long& lTalk);
// 打开对话，返回句柄
// lpszConn:Protocol=0x20000002;DevIP=;DevChn=;StreamID=;DevPort=;UserName=;Password=;Breath=;
// lpszConn:Protocol=0x20000002;DevIP=;DevChn=;StreamID=;DevPort=;UserName=;Password=;Breath=;
JNETSDK_API long JNetTalkOpenEx(LPCTSTR lpszConn,int iSamples,int iEncodeType,int iChannels,int iBits,fcbJStream* pfcbStream,void* pUserData,long& lTalk);
// 发送对讲数据
JNETSDK_API long JNetTalkSend(long lTalk,void* lpData,int iLen);
// 关闭对讲,传入需要关闭的句柄
JNETSDK_API long JNetTalkClose(long lTalk);
// 对讲操作 end

// 参数获取及设置 begin
JNETSDK_API long JNetGetParam(long lLogin,int iChn,int iParamID,void* lpData,int iDataLen,fcbJGetParam* pfcbGetParam,void* pUser);
JNETSDK_API long JNetSetParam(long lLogin,int iChn,int iParamID,void* lpData,int iDataLen,bool bSync);
// 参数获取及设置 end

// 设备控制 begin
JNETSDK_API long JNetDevCtrl(long lLogin,int iChn,int iCtrlCmd,int iCtrlValue);
JNETSDK_API long JNetUpgOpen(long lLogin,LPCTSTR lpszPath,long& lUpg);
JNETSDK_API long JNetUpgClose(long lUpg);
// 设备控制 end

// 录像控制 begin
// iStreamID:0~2,time:YYYYMMDDhhmmss
JNETSDK_API long JNetRecQuery(long lLogin,LPCTSTR lpszDevIP,int iChn,int iStreamID,LPCTSTR lpszBeginTime,LPCTSTR lpszEndTime,int iRecType);
JNETSDK_API long JNetRecOpen4Item(long lLogin,void* pItem,int iIsPlay,fcbJStream* pfcbStream,void* pUserData,long& lRec);
JNETSDK_API long JNetRecOpen4Time(long lLogin,
								  LPCTSTR lpszDevIP,int iChn,int iStreamID,LPCTSTR lpszBeginTime,LPCTSTR lpszEndTime,int iRecType,
								  int iIsPlay,fcbJStream* pfcbStream,void* pUserData,long& lRec);
JNETSDK_API long JNetRecOpen4TimeEx(LPCTSTR lpszConn,
								  LPCTSTR lpszDevIP,int iChn,int iStreamID,LPCTSTR lpszBeginTime,LPCTSTR lpszEndTime,int iRecType,
								  int iIsPlay,fcbJStream* pfcbStream,void* pUserData,fcbJEvent* pfcbEvent,void* pUserEvent,long& lRec);

JNETSDK_API long JNetRecCtrl(long lRec,eJNetPBCtrl eCtrlCmd,void* lpCtrlValue);
JNETSDK_API long JNetRecClose(long lRec);
// 录像控制 end

//设置WWP2P参数(zc20140228)
JNETSDK_API long JNetSetWWP2PParam(long lLogin, PSTJP2PParam pstP2PParam);

#endif	// __JNET_SDK_H__
