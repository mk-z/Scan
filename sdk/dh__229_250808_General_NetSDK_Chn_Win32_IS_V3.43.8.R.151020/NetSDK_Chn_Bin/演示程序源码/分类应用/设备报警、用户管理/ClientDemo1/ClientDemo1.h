// ClientDemo1.h : main header file for the CLIENTDEMO1 application
//

#if !defined(AFX_CLIENTDEMO1_H__1EBA1713_8D02_439C_820A_8FB592364BA0__INCLUDED_)
#define AFX_CLIENTDEMO1_H__1EBA1713_8D02_439C_820A_8FB592364BA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientDemo1App:
// See ClientDemo1.cpp for the implementation of this class
//

class CClientDemo1App : public CWinApp
{
public:
	CClientDemo1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientDemo1App)
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

#endif // !defined(AFX_CLIENTDEMO1_H__1EBA1713_8D02_439C_820A_8FB592364BA0__INCLUDED_)
