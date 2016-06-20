// IVSFDemo.h : main header file for the IVSFDEMO application
//

#if !defined(AFX_IVSFDEMO_H__906B69AB_3ACF_4515_8F72_D559E50DBC56__INCLUDED_)
#define AFX_IVSFDEMO_H__906B69AB_3ACF_4515_8F72_D559E50DBC56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIVSFDemoApp:
// See IVSFDemo.cpp for the implementation of this class
//

class CIVSFDemoApp : public CWinApp
{
public:
	CIVSFDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIVSFDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIVSFDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CString ConvertString(CString strText);

void g_SetWndStaticText(CWnd * pWnd);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVSFDEMO_H__906B69AB_3ACF_4515_8F72_D559E50DBC56__INCLUDED_)
