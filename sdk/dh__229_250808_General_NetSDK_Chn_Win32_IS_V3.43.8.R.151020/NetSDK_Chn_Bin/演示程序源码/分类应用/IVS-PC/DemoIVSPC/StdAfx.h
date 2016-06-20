// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D659FAE5_9200_4BF9_9CE2_BC4EC6BBB890__INCLUDED_)
#define AFX_STDAFX_H__D659FAE5_9200_4BF9_9CE2_BC4EC6BBB890__INCLUDED_

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

#include <AFXISAPI.H>
/************************************************************************/
/* NETSDK                                                            */
/************************************************************************/
#include "../Include/dhnetsdk.h"
#include "../Include/dhconfigsdk.h"
#pragma comment(lib, "../Lib/dhnetsdk.lib")
#pragma comment(lib, "../Lib/dhconfigsdk.lib")

#include "PlayApi.h"

extern CPlayAPI g_PlayAPI;
// #include <wingdi.h>
// #pragma comment(lib, "Gdi32.lib")
// #pragma comment(lib, "winmm.lib")

#pragma warning (disable:4786)


#endif // !defined(AFX_STDAFX_H__D659FAE5_9200_4BF9_9CE2_BC4EC6BBB890__INCLUDED_)
