// ClientDemo4.h : main header file for the CLIENTDEMO4 application
//

#if !defined(AFX_CLIENTDEMO4_H__4A9C93F8_AE11_4E01_980E_38D5B7FA4C55__INCLUDED_)
#define AFX_CLIENTDEMO4_H__4A9C93F8_AE11_4E01_980E_38D5B7FA4C55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "dhnetsdk.h"
#include <IOSTREAM>

#define DEMO_SDK_WAITTIME 3000
/////////////////////////////////////////////////////////////////////////////
// CClientDemo4App:
// See ClientDemo4.cpp for the implementation of this class
//

class CClientDemo4App : public CWinApp
{
public:
	CClientDemo4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo4App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientDemo4App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void g_SetWndStaticText(CWnd * pWnd);
CString ConvertString(CString strText);
std::string I2Str(const int v);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO4_H__4A9C93F8_AE11_4E01_980E_38D5B7FA4C55__INCLUDED_)
