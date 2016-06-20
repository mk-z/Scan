// Real Load Picture.h : main header file for the REAL LOAD PICTURE application
//

#if !defined(AFX_REALLOADPICTURE_H__D79C176B_B614_478F_A246_6DACDBE3869F__INCLUDED_)
#define AFX_REALLOADPICTURE_H__D79C176B_B614_478F_A246_6DACDBE3869F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


#include <vector>
#include <string>

#include "Utility.h"
/************************************************************************/
/* 全局常量和宏定义                                                             */
/************************************************************************/
//const int MAX_REAL_EVENT_DISPLAY_COUNT = 200;		//显示的事件的最多条数，超过这个条数后，最开始的时间会被覆盖
const int MAX_REAL_EVENT_STORE_COUNT   = 2000;		//临时保存在内存中的所有事件的总和，超过这个值后，前面的将被覆盖
#define CFG_SECTION_NAME				"INFO"		//配置文件的section的名字
#define	CFG_KEY_NAME_ALARM_TYPE		"alarm_type"	//配置文件的键名，alarm_type
#define	CFG_KEY_NAME_ALARM_INFO		"alarm_info"	//配置文件的键名，alarm_info
#define	PC_DATA_STORE_FOLDER		"PCStore\\"		//数据保存文件夹名字
#define PC_DATA_STORE_FILE			"cfg.ini"

#define CFG_CFG_FILE_NAME			"Config.ini"
#define CFG_SECTION_CFG				"CFG"
#define CFG_KEY_DATA_PATH			"DATA_PATH"

#define MAX_GUID_LEN 55

#define GET_SI_SIZE 0x01
#define GET_SI_TITLE 0x02
#define GET_SI_CONTENT 0x04
#define GET_SI_FILEINFO 0x08

const int SINGLE_PAGE_SIZE = 200; //分页大小

//#define	
typedef struct __ALARM_ITEM
{
	std::string strGUID;
	int		nAlarmType;
	int		nLen;
	void*	pAlarmInfo;
	int		nCheckFlag;
	GUID     nPictureGroupId;
	GUID     nEventGroupId;
}ALARM_ITEM, *LPALARM_ITEM;

//列的描述
typedef struct __COL_DES
{
	std::string strColTitle; //列的标题
	int			nColWidth;   //列的宽度
}ColDes;
/************************************************************************/
/* 全局函数                                                             */
/************************************************************************/

HBITMAP ExtractBitmap(IPicture *pPicture, int &nWidth, int &nHeight);
HBITMAP LoadImageFile(LPCSTR szImagePath, int &nWidth, int &nHeight);
void  g_SetWndStaticText(CWnd * pWnd);
CString ConvertString(CString strText);
BOOL TryDisplayLP(const DWORD dwAlarmType, const void* pAlarmInfo, CWnd* window);
//BOOL TryDisplayLPPic(const char* szImage, const ALARM_ITEM* item, CWnd* window);
BOOL IsTypeHasLP(DWORD dwAlarmType);
std::string GetDataFolder();
int RenderJPG(const char* szImagePath, HWND hwnd);

BOOL IsPicOfRecordExist(char* szGUID);


BOOL TryDisplayImageAndLPPart(const char* szJPGPath, const ALARM_ITEM* item, CWnd* fullImageWindow, CWnd* lpImageWindow);
/////////////////////////////////////////////////////////////////////////////
// CRealLoadPictureApp:
// See Real Load Picture.cpp for the implementation of this class
//



class CRealLoadPictureApp : public CWinApp
{
public:
	CRealLoadPictureApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealLoadPictureApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRealLoadPictureApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////







inline ColDes ColDesObj(char* szColTitle, const int nColWidth)
{
	ColDes colDes;
	colDes.strColTitle = ConvertStr(szColTitle);
	colDes.nColWidth = nColWidth;
	return colDes;
}

void GettrafficCarInfo(int  nGetWhat, DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO *pTrafficCar, std::vector<ColDes>* vTitles, std::vector<std::string>* vContent);
BOOL GetStructInfo(int nAlarmType,
				   void* pAlarmInfo,
				   int  nGetWhat,
				   int* nStructSize,
				   DH_EVENT_FILE_INFO* pFileInfo,
				   std::vector<ColDes>* vTitles, 
				   std::vector<std::string>* vContent);


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_REALLOADPICTURE_H__D79C176B_B614_478F_A246_6DACDBE3869F__INCLUDED_)
