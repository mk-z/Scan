// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A42990E7_D06C_4F9F_BA2E_5A2CEFE35AB1__INCLUDED_)
#define AFX_STDAFX_H__A42990E7_D06C_4F9F_BA2E_5A2CEFE35AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "include/dhnetsdk.h"
#include "include/dhconfigsdk.h"
#pragma comment(lib, "include/dhnetsdk.lib")
#pragma comment(lib, "include/dhconfigsdk.lib")

///////////////////////////////////////////////////////
// 宏定义
#define SAFE_DELETE(p) if(0!=p) {delete p;p=0;}
#define SAFE_DELETE_A(p) if(0!=p) {delete[] p;p=0;}

///////////////////////////////////////////////////////
// 去除STL警告
#pragma warning(disable:4786)// 标识符长度超过256个字符

///////////////////////////////////////////////////////
// 全局函数
void ClearComboBox(CComboBox &stComboBox);

CString ConvertString(CString strText);

void g_SetWndStaticText(CWnd * pWnd);

#define AfxMessageBox(S) ::MessageBox(NULL, S,ConvertString("Prompt"), 0);

#include "vld/vld.h"

// 此枚举如果变动，则dhnetsdk.h中也应做相应变动 linjy-2006-12-16
enum DhServerType
{
	VIDEO_PRODUCT_NONE = 0,
	VIDEO_DVR_NONREALTIME_MACE,	// 非实时MACE
	VIDEO_DVR_NONREALTIME,			// 非实时
	VIDEO_NVS_MPEG1,				// 网络视频服务器
	VIDEO_DVR_MPEG1_2,				// MPEG1二路录像机
	VIDEO_DVR_MPEG1_8,				// MPEG1八路录像机
	VIDEO_DVR_MPEG4_8,				// MPEG4八路录像机
	VIDEO_DVR_MPEG4_16,			// MPEG4十六路录像机
	VIDEO_DVR_MPEG4_SX2,			// MPEG4视新十六路录像机
	VIDEO_DVR_MEPG4_ST2,			// MPEG4视通录像机
	VIDEO_DVR_MEPG4_SH2,			// MPEG4视豪录像机
	VIDEO_DVR_MPEG4_GBE,			// MPEG4视通二代增强型录像机
	VIDEO_DVR_MPEG4_NVSII,			// MPEG4网络视频服务器II代
	VIDEO_DVR_STD_NEW,				// 新标准配置协议
	VIDEO_DVR_DDNS,				// DDNS服务器
	VIDEO_DVR_ATM,					// ATM机
	VIDEO_NB_SERIAL,				// 二代非实时NB系列机器
	VIDEO_LN_SERIAL,				// LN系列产品
	VIDEO_BAV_SERIAL,				// BAV系列产品
	VIDEO_SDIP_SERIAL,				// SDIP系列产品
	VIDEO_IPC_SERIAL,				// IPC系列产品
	VIDEO_NVS_B,					// NVS B系列
	VIDEO_NVS_C,					// NVS H系列
	VIDEO_NVS_S,					// NVS S系列
	VIDEO_NVS_E,					// NVS E系列
	VIDEO_DVR_NEW_PROTOCOL,		// 新协议
	VIDEO_NVD_SERIAL,				// 解码器
	VIDEO_DVR_N5,					// N5
	VIDEO_DVR_MIX_DVR,				// 混合DVR
	VIDEO_SVR_SERIAL,				// SVR
	VIDEO_SVR_BS,					// SVR-BS
	VIDEO_NVR_SERIAL,				// NVR
	VIDEO_DVR_N51,                 // N51
	VIDEO_ITSE_SERIAL,				// ITSE 智能分析盒
	VIDEO_ITC_SERIAL,              // 智能交通像机设备
	VIDEO_ITC_HWS,                 // 雷达测速仪HWS
	VIDEO_PVR_SERIAL,              // 便携式音视频录像机
	VIDEO_IVS_SERIAL,              // IVS（智能视频服务器系列）
	VIDEO_IVS_B,                   // 通用智能视频侦测服务器
	VIDEO_IVS_F,                   // 人脸识别服务器
	VIDEO_IVS_V,                   // 视频质量诊断服务器	
	VIDEO_MATRIX_SERIAL,			// 矩阵
	VIDEO_DVR_N52,					// N52
	VIDEO_DVR_N56,                 // n56
	VIDEO_ESS_SERIAL,              // ESS
	VIDEO_IVS_PC,                  // 智能交通人数统计服务器
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A42990E7_D06C_4F9F_BA2E_5A2CEFE35AB1__INCLUDED_)
