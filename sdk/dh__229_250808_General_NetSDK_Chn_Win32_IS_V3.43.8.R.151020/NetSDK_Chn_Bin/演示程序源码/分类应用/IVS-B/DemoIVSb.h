// DemoIVSb.h : main header file for the DEMOIVSB application
//

#if !defined(AFX_DEMOIVSB_H__902FE451_4E3D_4E43_9666_B8FD7A29EF56__INCLUDED_)
#define AFX_DEMOIVSB_H__902FE451_4E3D_4E43_9666_B8FD7A29EF56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include <list>

#include "PlayApi.h"

#include "Include/IvsDrawer.h"
#pragma comment(lib, "Lib/IvsDrawer.lib")
//////////////////////////////////////////////////////////////////////////

#define WM_CLEARINFO		(WM_USER + 99)

#define WM_ZONEDONE			(WM_USER + 100)	//绘制全局标定区域/标尺完成后通知父窗口
#define WM_REGIONDONE		(WM_USER + 101)	//绘制模块检测区域/排除区域完成后通知给父窗口
#define WM_RULEDONE			(WM_USER + 102)	//规则绘图完成后通知给父窗口

#define WM_USER_ALAMR_COME	(WM_USER + 200)	//回调报警信息

//total channel count supported by device
const int g_MaxChannelCount = 64;


//decode port num
const int g_nPlayPort = 450;

//draw port num for preview
const int g_nPreviewDrawPort = 300;

//draw port num for RuleCfg
const int g_nRuleCfgDrawPort = 400;

// For Loading PlaySDK dynamically
extern CPlayAPI s_PlayAPI;

//////////////////////////////////////////////////////////////////////////
// Custom info for Global Config
//全局配置界面标定区域树控件上的节点绑定的信息定义
const int nNodeArea = 0;
const int nStaffHor = 1;
const int nStaffVer = 2;

//树节点类型
typedef struct tagGTNodeType
{
	int	nNodeType;		//节点类型：检测区域，标尺
	
	tagGTNodeType()
	{
		nNodeType = -1;
	}
	
	~tagGTNodeType()
	{
		nNodeType = -1;
	}
}GTNODETYPE;

//标定区域节点
typedef struct tagGTNodeArea
{
	int						nNodeType;
	CFG_CALIBRATEAREA_INFO	CfgCalibrateAreaInfo;
	
	tagGTNodeArea()
	{
		nNodeType = -1;
		ZeroMemory(&CfgCalibrateAreaInfo,
			sizeof(CfgCalibrateAreaInfo));
	}
}GTNODEAREA;

//标尺节点
typedef struct tagGTNodeStaff
{
	int			nNodeType;
	CFG_STAFF	CfgStaff;
	
	tagGTNodeStaff()
	{
		nNodeType = -1;
		ZeroMemory(&CfgStaff, sizeof(CfgStaff));
	}
}GTNODESTAFF;

//////////////////////////////////////////////////////////////////////////
// Custom info for Rule Config
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

//报警回调参数结构体
typedef struct tagEventPara
{
	LLONG	lAnalyzerHandle;
	DWORD	dwAlarmType;
	void*	pAlarmInfo;
	BYTE*	pBuffer;
	DWORD	dwBufSize;
	int		nSequence;
}EventPara;

//报警信息结构体
typedef struct tagAlarmInfoNode
{
	int nChnNum;
	char szAlarmName[128];
	DWORD dwRuleType;
	NET_TIME_EX Time;
	TCHAR szFile[MAX_PATH];

	tagAlarmInfoNode()
	{
		nChnNum = -1;
		ZeroMemory(szAlarmName, sizeof(szAlarmName));
		dwRuleType = -1;
		ZeroMemory(&Time, sizeof(Time));
		ZeroMemory(szFile, sizeof(szFile));
	}
}AlarmInfoNode;

//报警信息链表，按照客户接收到的先后顺序存入链表
typedef	std::list<AlarmInfoNode*> lsAlarmInfo;

//////////////////////////////////////////////////////////////////////////

template<class T> 
void setRuleEnableTime(T* pRule)
{
	if (!pRule)
	{
		return;
	}

	// 每周7天，每天6个时间段，只有在设置的时间范围内，并且使能，规则才生效。
	for (int i = 0; i < WEEK_DAY_NUM; i++)
	{
		pRule->stuTimeSection[i][0].dwRecordMask = 1;
		pRule->stuTimeSection[i][0].nBeginHour = 0;
		pRule->stuTimeSection[i][0].nBeginMin = 0;
		pRule->stuTimeSection[i][0].nBeginSec = 0;
		pRule->stuTimeSection[i][0].nEndHour = 23;
		pRule->stuTimeSection[i][0].nEndMin = 59;
		pRule->stuTimeSection[i][0].nEndSec = 59;
	}
}

//////////////////////////////////////////////////////////////////////////
//function: RealDataCallBackEx
//describe: callback to get buffer
//param: 
//return: 
//////////////////////////////////////////////////////////////////////////
void CALLBACK RealDataCallBackEx(LLONG lRealHandle,
								 DWORD dwDataType, 
								 BYTE *pBuffer,
								 DWORD dwBufSize, 
								 LONG lParam, 
								 LDWORD dwUser);

//////////////////////////////////////////////////////////////////////////
//function: ConvertString
//describe: convert GUI text
//param: 
//return: 
//////////////////////////////////////////////////////////////////////////
CString ConvertString(CString strText);

//////////////////////////////////////////////////////////////////////////
//function: g_SetWndStaticText
//describe: convert static wnd text
//param: 
//return: 
//////////////////////////////////////////////////////////////////////////
void  g_SetWndStaticText(CWnd * pWnd);

//////////////////////////////////////////////////////////////////////////
//function: g_getStructSize
//describe: get configuration struct size of ruletype
//param: 
//return: 
//////////////////////////////////////////////////////////////////////////
int g_getStructSize(int IN nRuleType);

//////////////////////////////////////////////////////////////////////////
//function: g_convertRuleTypeToString
//describe: convert ruletype to its name
//param: 
//return: 
//////////////////////////////////////////////////////////////////////////
CString g_convertRuleTypeToString(DWORD IN dwType);

//////////////////////////////////////////////////////////////////////////
//function: g_ConvertRuleTypeToStructSize
//describe: get struct size of ruletype, used for configuration struct
//param: 
//return: 
//////////////////////////////////////////////////////////////////////////
// int g_ConvertRuleTypeToStructSize(DWORD dwType);

//////////////////////////////////////////////////////////////////////////
//function: g_getStructInfo
//describe: get alarm struct size of ruletype
//param: 
//return: 
//////////////////////////////////////////////////////////////////////////
int g_getStructInfo(DWORD dwAlarmType);


//////////////////////////////////////////////////////////////////////////
// smart guard
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

/////////////////////////////////////////////////////////////////////////////
// CDemoIVSbApp:
// See DemoIVSb.cpp for the implementation of this class
//

class CDemoIVSbApp : public CWinApp
{
public:
	CDemoIVSbApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoIVSbApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemoIVSbApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOIVSB_H__902FE451_4E3D_4E43_9666_B8FD7A29EF56__INCLUDED_)
