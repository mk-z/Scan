// ComConstants.h: interface for the CComConstants class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMCONSTANTS_H__CFA5806B_B91C_4665_89A2_AD397C38F75A__INCLUDED_)
#define AFX_COMCONSTANTS_H__CFA5806B_B91C_4665_89A2_AD397C38F75A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/************************************************************************
 ** 常量定义
 ***********************************************************************/
#define CHANNEL_NUM_LIMIT 256 // 最大视频通道数限制

#define MIN_CHANNEL_NUM_TAG 0	// 最大通道数选项
#define MAX_CHANNEL_NUM_TAG 256	// 最小通道数选项

#define MIN_CIF_PFRAME_SIZE     7       // CIF最小P帧大小，单位为Kbits
#define MAX_CIF_PFRAME_SIZE     40      // CIF最大P帧大小，单位为Kbits
#define IFRAME_PFRAME_QUOTIENT  3       // 剧烈运动情况下I帧大小与P帧大小之比 
#define MAXFPS_LIMIT            8192    // 限码流最大值
#define MAX_NAS_LIMIT           2       // 限制最大NAS服务器数
#define MAX_ETHERNET_LIMIT      9       // 限制最大网卡数,网卡信息最后一个为bond0,实际网卡数会少1
#define SDK_DEMO_WAITTIME       5000    // SDK接口等待时间，单位ms
/************************************************************************
 ** 枚举定义
 ***********************************************************************/
enum EnNetWorkMode
{
	En_Net_Bind,			///< 绑定
	En_Net_Balance,			///< 负载平衡
	En_Net_Multiple,		///< 多址
	En_Net_Tolerance,		///< 容错	
};


/************************************************************************
 ** 结构体定义
 ***********************************************************************/

#endif // !defined(AFX_COMCONSTANTS_H__CFA5806B_B91C_4665_89A2_AD397C38F75A__INCLUDED_)
