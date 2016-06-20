// DevMgr.h: interface for the CDevMgr class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _DEVMGR_H_
#define _DEVMGR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetSDKDemo.h"
#pragma warning(disable:4786)
#include <list>

using namespace std;

typedef struct 
{
	LONG alarmType;
	DEV_STATE state;
	CTime	timeStamp;
}AlarmNode;

class CDevMgr  
{
public:

	/*
	//设备信息列表结构
	typedef struct _DeviceNode {
		char UserNanme[20]; //登录用户名
		char Name[20];   //设备名称
		char IP[20];     //设备IP地址字符
		LONG LoginID;    //设备登录iD
		NET_DEVICEINFO Info;  //设备信息
		NET_CLIENT_STATE State; //设备状态
		DWORD TotalKbps;     //设备当前总码流
		DWORD Max_Kbps;     //设置最大网络流量
	}DeviceNode;
	*/

	class SearchDevByHandle;
	friend class SearchDevByHandle;

public:
	CDevMgr();
	~CDevMgr();

	static CDevMgr& GetDevMgr(void);

	//protected copy object
private:
	CDevMgr(const CDevMgr&);
	CDevMgr& operator=(const CDevMgr&);

public:

	//加入节点
	int  PushBack(DeviceNode* node);
	
	//删除节点
	int  DelNode(LONG lLoginID);

	//修改节点
	int	 ModifyNode(LONG lLoginID, BOOL bIsOnline);

	//回调函数返回值说明：1 结束枚举， 0 继续枚举
	void For_EachDev(int (* cbForEach)(const DeviceNode& node, DWORD dwUser), DWORD dwUser);

	//回调函数返回值说明：1 结束枚举， 0 继续枚举
	void For_EachAlmNode(int (* cbForEachAlm)(const AlarmNode& node, DWORD dwUser), DWORD dwUser);
	
	//返回的数据不能做长久保存，下次要重新获取
	int  GetDev(LONG lLoginID, DeviceNode& node);

	//写入回调出来的报警数据
	int SetAlarmInfo(LONG lLoginID, LONG lCommand, char *pchDVRIP, LONG nDVRPort, 
						  char *pBuf, DWORD dwBufLen);
	int CDevMgr::GetAlarmInfo(LONG lLoginID, DEV_STATE *des);

	BOOL IsOnline(LONG lLoginID);

	BOOL IsOnline(DeviceNode* node);

private:

	list<DeviceNode*> m_lstDevice;
	list<AlarmNode*> m_lstAlarm;
	CRITICAL_SECTION  m_csDev;
	CRITICAL_SECTION  m_csAlarm;
	CRITICAL_SECTION  m_csAlmList;
};

class CDevMgr::SearchDevByHandle
{
	LONG m_lLoginID;
public:
	SearchDevByHandle(const LONG& lLoginID):m_lLoginID(lLoginID){}

	bool operator()( DeviceNode* const node)
	{
		if (!node)
		{
			return false;
		}

		return (m_lLoginID==node->LoginID)?true:false;
	}
};

#endif // _DEVMGR_H_
