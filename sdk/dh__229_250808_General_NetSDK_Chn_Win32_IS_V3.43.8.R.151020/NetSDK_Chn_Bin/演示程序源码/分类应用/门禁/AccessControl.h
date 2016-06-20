// AccessControl.h : main header file for the ACCESSCONTROL application
//

#if !defined(AFX_ACCESSCONTROL_H__754E2D9E_DDC8_4B70_A7F2_DA23B66CF022__INCLUDED_)
#define AFX_ACCESSCONTROL_H__754E2D9E_DDC8_4B70_A7F2_DA23B66CF022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define SDK_API_WAIT			(5000)				// delay time of sdk api in msec

// after modification, demo need re-execute
#define SDK_PARAM				"SDKParam"			// for setting AVNetSDK basic params 
#define DEVICE_PARAM			"DeviceParam"		// for setting device basic params

// definition for dlg ui translation
#define DLG_MAIN				"MainDlg"			//
#define DLG_CAPABILITY			"CapabilityDlg"		//
#define DLG_SUBSCRIBE			"SubscribeDlg"		//
#define DLG_CFG_ALARM			"CfgAlarmDlg"		//
#define DLG_QUERYLOG			"QueryLog"
#define DLG_DEVICETIME			"DeviceTime"
#define DLG_UPGRADE				"UpgradeDlg"		//
#define DLG_DOOR_CONTROL		"DoorControl"		//
#define	DLG_USER				"UserPasswordDlg"	//=control
#define DLG_VERSION             "VersionDlg"
#define DLG_RECORDSET_CONTROL	"RecordSetControl"	//
#define DLG_RECORDSET_FINDER	"RecordSetFinder"
#define SUBDLG_INFO_CARD		"InfoCard"
#define SUBDLG_INFO_PWD			"InfoPwd"
#define SUBDLG_INFO_ACCESS		"InfoAccess"
#define SUBDLG_INFO_HOLIDAY		"InfoHoliday"

#define DLG_CFG_NETWORK			"CfgNetwork"		//=add to cfg
#define DLG_CFG_ACCESS_GENERAL	"CfgAccessControlGeneral"
#define DLG_CFG_ACCESS_CONTROL	"CfgAccessControl"
#define SUBDLG_CFG_DOOROPEN_TIMESECTION	"CfgDoorOpenTimeSection"
#define	DLG_CFG_TIME_SCHEDULE	"CfgAccessTimeSchedule"
#define DLG_CFG_NTP				"CfgNTP"			//=add to cfg


#define SDK_API_WAITTIME		5000                // 调用SDK接口超时时间

//////////////////////////////////////////////////////////////////////////

// TimeSection
typedef enum tagem_WeekDay
{
	em_WeekDay_Sunday = 0,			// 周日
	em_WeekDay_Monday,				// 周一
	em_WeekDay_Tuesday,				// 周二
	em_WeekDay_Wednesday,			// 周三
	em_WeekDay_Thursday,			// 周四
	em_WeekDay_Friday,				// 周五
	em_WeekDay_Saturday,			// 周六
}em_WeekDay;

typedef struct tagDemo_WeekDay
{
	em_WeekDay emWeekDay;
	char* pszName;
}Demo_WeekDay;

const Demo_WeekDay stuDemoWeekDay[] = 
{
	{em_WeekDay_Sunday, "Sunday"},
	{em_WeekDay_Monday, "Monday"},
	{em_WeekDay_Tuesday, "Tuesday"},
	{em_WeekDay_Wednesday, "Wednesday"},
	{em_WeekDay_Thursday, "Thursday"},
	{em_WeekDay_Friday, "Friday"},
	{em_WeekDay_Saturday, "Saturday"},
};

//////////////////////////////////////////////////////////////////////////
// open method of access
typedef struct tagOpenMethod 
{
	CFG_DOOR_OPEN_METHOD	emOpenMethod;
	const char*				szName;
}OpenMethod;

const OpenMethod stuDemoOpenMethod[] = 
{
	{CFG_DOOR_OPEN_METHOD_UNKNOWN, "Unknown"},
	{CFG_DOOR_OPEN_METHOD_PWD_ONLY, "PwdOnly"},
	{CFG_DOOR_OPEN_METHOD_CARD, "Card"},
	{CFG_DOOR_OPEN_METHOD_PWD_OR_CARD, "PwdOrCard"},
	{CFG_DOOR_OPEN_METHOD_CARD_FIRST, "CardFirst"},
	{CFG_DOOR_OPEN_METHOD_PWD_FIRST, "PwdFirst"},
    {CFG_DOOR_OPEN_METHOD_SECTION, "TimeSection"},
    {CFG_DOOR_OPEN_METHOD_FINGERPRINTONLY, "FingerPrintOnly"},
    {CFG_DOOR_OPEN_METHOD_PWD_OR_CARD_OR_FINGERPRINT, "PwdOrCardOrFingerPrint"},
    {CFG_DOOR_OPEN_METHOD_CARD_AND_FINGERPRINT, "CardAndFingerPrint"},
	{CFG_DOOR_OPEN_METHOD_MULTI_PERSON, "MultiPerson"},
};

//////////////////////////////////////////////////////////////////////////
// record set type
typedef enum tagEm_RecordSet_Type
{
	Em_RecordSet_Type_Card = 0,			// card
	Em_RecordSet_Type_Pwd,				// password of access
	Em_RecordSet_Type_Access,			// access record
	Em_RecordSet_Type_Holiday,			// holiday
}Em_RecordSet_Type;

//////////////////////////////////////////////////////////////////////////
// operate type of record set control
typedef enum tagEm_RecordSet_Operate_Type
{
	Em_Operate_Type_Show = 0,		// 所有字段只读
	Em_Operate_Type_Insert,			// 除了nRecNo字段，其他字段都可写
	Em_Operate_Type_Get,			// 只有nRecNo字段可写
	Em_Operate_Type_Update,			// 只有nRecNo字段只读，其他字段可写
	Em_Operate_Type_Remove,			// 只有nRecNo字段可写
	Em_Operate_Type_Clear,			// 无需参数
	Em_Operate_Type_InsertEX,		// 除了nRecNo字段，其他字段都可写
	Em_Operate_Type_UpdateEX,			// 只有nRecNo字段只读，其他字段可写
}Em_RecordSet_Operate_Type;

//////////////////////////////////////////////////////////////////////////
// 控制查询类型
typedef enum tagEM_CONTROL_QUERY_TYPE
{
	EM_CONTROL_QUERY_VERSION,//
	// recordset insert, update, delete, clear
// 	EM_CONTROL_QUERY_RECORDSET_INSERT,
// 	EM_CONTROL_QUERY_RECORDSET_UPDATE,
// 	EM_CONTROL_QUERY_RECORDSET_DELETE,
// 	EM_CONTROL_QUERY_RECORDSET_CLEAR,
	EM_CONTROL_QUERY_REBOOT,//
	EM_CONTROL_QUERY_RESTOREALL,//
	EM_CONTROL_QUERY_DOOR_CONTROL,	// open, close and query status
	EM_CONTROL_QUERY_LOG,
	EM_CONTROL_QUERY_MAC,
// 	EM_CONTROL_QUERY_RECORDFINEDER_CAP,
	// recordset count
	EM_CONTROL_QUERY_TIME,
// 	EM_CONTROL_QUERY_RECORDSET_FINDER,
	EM_CONTROL_QUERY_UPGRADE,
	EM_CONTROL_QUERY_MODIFY_PWD,
}EM_CONTROL_QUERY_TYPE;

typedef struct tagDemo_Em_Control_Query_Type 
{
	EM_CONTROL_QUERY_TYPE	emType;
	const char*				szName;
}Demo_Em_Control_Query_Type;

const Demo_Em_Control_Query_Type stuDemoEmControlQueryType[] = 
{
	{EM_CONTROL_QUERY_VERSION,		"Version"},//
	{EM_CONTROL_QUERY_REBOOT,		"Reboot"},// no dlg
	{EM_CONTROL_QUERY_RESTOREALL,	"RestoreAll"},//
	{EM_CONTROL_QUERY_DOOR_CONTROL,	"DoorControl"},
	{EM_CONTROL_QUERY_LOG,			"Log"},//
	{EM_CONTROL_QUERY_MAC,			"Mac"},// no dlg
	{EM_CONTROL_QUERY_TIME,			"Time"},//
	{EM_CONTROL_QUERY_UPGRADE,		"Upgrade"},
	{EM_CONTROL_QUERY_MODIFY_PWD,	"ModifyPwd"},
};

//////////////////////////////////////////////////////////////////////////
// 配置类型
typedef enum tagEM_CONFIG_TYPE
{
	EM_CONFIG_NETWORK,
	EM_CONFIG_ACCESSCONTROL_GENERAL,
	EM_CONFIG_ACCESSCONTROL,
	EM_CONFIG_ACCESS_TIMESECHDULE,
	EM_CONFIG_NTP,
}EM_CONFIG_TYPE;

typedef struct tagDemo_Em_Config_Type
{
	EM_CONFIG_TYPE	emType;
	const char*		szName;
}Demo_Em_Config_Type;

const Demo_Em_Config_Type stuDemoEmConfigType[] =
{
	{EM_CONFIG_NETWORK,					"CfgNetwork"},
	{EM_CONFIG_ACCESSCONTROL_GENERAL,	"CfgAccessControlGeneral"},
	{EM_CONFIG_ACCESSCONTROL,			"CfgAccessControl"},
	{EM_CONFIG_ACCESS_TIMESECHDULE,		"CfgAccessTimeSchedule"},
	{EM_CONFIG_NTP,						"CfgNTP"},
};

/////////////////////////////////////////////////////////////////////////////
// CAccessControlApp:
// See AccessControl.cpp for the implementation of this class
//

class CAccessControlApp : public CWinApp
{
public:
	CAccessControlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccessControlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAccessControlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

void g_SetWndStaticText(CWnd * pWnd, const char* pszSeg = NULL);
//--------------------------------------------------------------------------------
// convert GUI text
CString ConvertString(CString strText, const char* pszSeg = NULL);

// convert enum to str
void SenseTypeToStr(NET_SENSE_METHOD nSenseType, CString& szStr);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCESSCONTROL_H__754E2D9E_DDC8_4B70_A7F2_DA23B66CF022__INCLUDED_)
