// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D659FAE5_9200_4BF9_9CE2_BC4EC6BBB890__INCLUDED_)
#define AFX_STDAFX_H__D659FAE5_9200_4BF9_9CE2_BC4EC6BBB890__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define  _WIN32_WINNT		0x500
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
#include "Include/dhnetsdk.h"

#include "Include/dhconfigsdk.h"
#pragma comment(lib, "Lib/dhnetsdk.lib")

#pragma comment(lib, "Lib/dhconfigsdk.lib")

#pragma warning (disable:4786)
#pragma warning (disable:4996)	// disable strncpy warning
#pragma warning (disable:4244)	// disable type convert warning
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D659FAE5_9200_4BF9_9CE2_BC4EC6BBB890__INCLUDED_)
