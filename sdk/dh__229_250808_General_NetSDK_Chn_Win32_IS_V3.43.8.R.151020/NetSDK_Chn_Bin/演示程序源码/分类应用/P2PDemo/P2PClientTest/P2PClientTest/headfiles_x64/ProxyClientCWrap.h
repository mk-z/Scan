/*************************************************************************
 ** 版权保留(C), 2001-2013, 浙江大华技术股份有限公司.
 ** 版权所有.
 **
 ** $Id$
 **
 ** 功能描述   : Proxy Client C适配层
 **
 ** 修改历史     : 2013年12月23日 zhu_long Modification
*************************************************************************/

#ifndef _DAHUA_P2P_PROXY_CLIENT_CWRAP_H_
#define _DAHUA_P2P_PROXY_CLIENT_CWRAP_H_

#include "Defs.h"

#ifdef WIN32
	typedef unsigned __int64 uint64_t;
#else
	typedef unsigned long long uint64_t;
#endif

#ifdef  __cplusplus
extern "C" {
#endif

///\brief 代理状态
typedef enum
{
    DHProxyStateUnauthorized,           ///< 服务认证失败（序列号非法、密钥错误）
    DHProxyStateForbidden,              ///< 服务禁止登陆（设备ID重复、服务器拒绝）
    DHProxyStateOffline,                ///< 服务离线
    DHProxyStateOnline,                 ///< 服务在线
} DHProxyClientProxyState;

///\brief P2P通道状态
typedef enum
{
    DHP2PChannelStateInit,              ///< P2P通道初始化中
    DHP2PChannelStateActive,            ///< P2P通道已连通
    DHP2PChannelStateNonExist,          ///< P2P通道不存在
} DHProxyClientP2PChannelState;

///\brief 映射端口速率统计
typedef struct
{
    uint64_t               recvBytes;     ///< 总接收字节KB
    uint64_t               sendBytes;     ///< 总发送字节KB

    double               curRecvRate;   ///< 当前接收速率Kb/s
    double               curSendRate;   ///< 当前发送速率Kb/s

    double               lostRate;      ///< 丢包率
    double               liveTime;      ///< 通道活动时间(秒S)
} DHProxyClientMapPortRate;

///\brief 远程代理信息
typedef struct
{
    char                remoteId[64];      ///< 服务器ID
    char                remoteIp[64];      ///< 远程代理IP
    int                 remotePort;        ///< 远程代理端口
} DHProxyClientRemotePortInfo;

///\brief 句柄
typedef void*	ProxyClientHandler;

///\breif 初始化
///\param[in]       svraddr  服务器IP(暂不支持域名)
///\param[in]       svrport  服务器端口
///\param[in]       passwd   密钥
///\return 0失败/其他，client句柄
TOU_API ProxyClientHandler DHProxyClientInit(const char* svrip, int svrport, const char* passwd);

///\breif 释放资源
///\param[in]       handler  实际client句柄
TOU_API void DHProxyClientRelease(ProxyClientHandler handler);

///\brief 通过远程代理打开映射
///\param[in]       handler  实际client句柄
///\param[in]       deviceId    远程代理ID
///\param[in]       targetPort  目标端口
///\param[in,out]   localPort   本地映射端口,为0由内部随机分配一个端口
///\return 0成功/-1失败
TOU_API int DHProxyClientAddPort(ProxyClientHandler handler,
		const char* deviceId, int targetPort, int *localPort);

///\brief 删除一个映射
///\param[in]   handler  实际client句柄
///\param[in]   port 本地映射端口
///\return 0成功/-1失败
TOU_API int DHProxyClientDelPort(ProxyClientHandler handler, int port);

///\brief 查询映射端口速率
///\param[in]   handler  实际client句柄
///\param[in]   port 本地映射端口
///\param[out]  rate 当前映射速率
///\return 0成功/-1失败
TOU_API int DHProxyClientQueryRate(ProxyClientHandler handler,
		int port, DHProxyClientMapPortRate *rate);

///\brief 查询映射端口的P2P通道状态
///\param[in]   handler  实际client句柄
///\param[in]   port 本地映射端口
///\param[out]  state 当前映射端口状态， @see DHProxyClientP2PChannelState
///\return 0成功/-1失败
TOU_API int DHProxyClientChannelstate(ProxyClientHandler handler, int port, int *state);

///\brief 获取当前代理客户端状态
///\param[in]   handler  实际client句柄
///\param[out] 	state  当前代理客户端状态, @see DHProxyClientProxyState
///\return 0成功/-1失败
TOU_API int DHProxyClientState(ProxyClientHandler handler, int *state);

///\brief 查询远程代理服务器的状态
///\param[in]   handler  实际client句柄
///\param[in]   deviceId 远程代理ID
///\param[out] 	state 当前代理服务器状态, @see DHProxyClientProxyState
///\return 0成功/-1失败
TOU_API int DHProxyClientServerState(ProxyClientHandler handler, const char* deviceId, int *state);

///\brief 查询远程代理服务器的信息
///\param[in]   handler  实际client句柄
///\param[in]   port  本地隐射端口
///\param[out]  info  远程代理服务器信息, @see DHProxyClientRemotePortInfo
///\return 0成功/-1失败
TOU_API int DHProxyClientQueryRemoetInfo(ProxyClientHandler handler, int port, DHProxyClientRemotePortInfo *info);

///\breif 初始化
///\param[in]       svraddr  服务器IP(暂不支持域名)
///\param[in]       svrport  服务器端口
///\param[in]       passwd   密钥
///\param[in]       username   用户名
///\return 0失败/其他，client句柄
TOU_API ProxyClientHandler DHProxyClientInitWtihName(const char* svrip, int svrport, const char* passwd, const char* username);

#ifdef  __cplusplus
}
#endif

#endif /* _DAHUA_P2P_PROXY_CLIENT_CWRAP_H_ */
