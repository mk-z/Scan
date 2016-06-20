// ClientDemo6.h : main header file for the CLIENTDEMO6 application
//

#if !defined(AFX_CLIENTDEMO6_H__5D353D36_7A2C_4383_9D2E_FC637BBE5E47__INCLUDED_)
#define AFX_CLIENTDEMO6_H__5D353D36_7A2C_4383_9D2E_FC637BBE5E47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientDemo6App:
// See ClientDemo6.cpp for the implementation of this class
//

class CClientDemo6App : public CWinApp
{
public:
	CClientDemo6App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo6App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientDemo6App)
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

#endif // !defined(AFX_CLIENTDEMO6_H__5D353D36_7A2C_4383_9D2E_FC637BBE5E47__INCLUDED_)
