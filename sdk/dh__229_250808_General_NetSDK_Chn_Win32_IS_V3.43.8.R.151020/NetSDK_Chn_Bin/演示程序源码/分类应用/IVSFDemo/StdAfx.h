// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__7F7BF0BF_628B_4198_8DE4_12E0187C8459__INCLUDED_)
#define AFX_STDAFX_H__7F7BF0BF_628B_4198_8DE4_12E0187C8459__INCLUDED_

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

#pragma warning(disable : 4786)
#include "include/dhnetsdk.h"
#include "include/dhconfigsdk.h"
//#include "include/dhplay.h"
#include "Utility.h"
#pragma comment(lib, "lib/dhnetsdk.lib")
#pragma comment(lib, "lib/dhconfigsdk.lib")

#include "PlayApi.h"

extern CPlayAPI g_PlayAPI;
//#pragma comment(lib, "lib/dhplay.lib")



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7F7BF0BF_628B_4198_8DE4_12E0187C8459__INCLUDED_)
