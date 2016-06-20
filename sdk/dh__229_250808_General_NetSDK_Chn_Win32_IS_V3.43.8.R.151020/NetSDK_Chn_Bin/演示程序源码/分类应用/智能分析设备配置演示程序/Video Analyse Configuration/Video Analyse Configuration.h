// Video Analyse Configuration.h : main header file for the VIDEO ANALYSE CONFIGURATION application
//

#if !defined(AFX_VIDEOANALYSECONFIGURATION_H__59BF66CA_A106_4581_B8FB_34C2B7C08587__INCLUDED_)
#define AFX_VIDEOANALYSECONFIGURATION_H__59BF66CA_A106_4581_B8FB_34C2B7C08587__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVideoAnalyseConfigurationApp:
// See Video Analyse Configuration.cpp for the implementation of this class
//

class CVideoAnalyseConfigurationApp : public CWinApp
{
public:
	CVideoAnalyseConfigurationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoAnalyseConfigurationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVideoAnalyseConfigurationApp)
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

#endif // !defined(AFX_VIDEOANALYSECONFIGURATION_H__59BF66CA_A106_4581_B8FB_34C2B7C08587__INCLUDED_)
