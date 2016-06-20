// NVDSDKDemo.h : main header file for the NVDSDKDEMO application
//

#if !defined(AFX_NVDSDKDEMO_H__4B80A605_FC02_46E3_939E_6F96F534795E__INCLUDED_)
#define AFX_NVDSDKDEMO_H__4B80A605_FC02_46E3_939E_6F96F534795E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNVDSDKDemoApp:
// See NVDSDKDemo.cpp for the implementation of this class
//

class CNVDSDKDemoApp : public CWinApp
{
public:
	CNVDSDKDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNVDSDKDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNVDSDKDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


void g_SetWndStaticText(CWnd * pWnd);
CString ConvertString(CString strText);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NVDSDKDEMO_H__4B80A605_FC02_46E3_939E_6F96F534795E__INCLUDED_)
