// ClientDemo5.h : main header file for the CLIENTDEMO5 application
//

#if !defined(AFX_CLIENTDEMO5_H__2BCE6C28_87FD_400A_BF6D_95C784696FC9__INCLUDED_)
#define AFX_CLIENTDEMO5_H__2BCE6C28_87FD_400A_BF6D_95C784696FC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "ComConstants.h"
#pragma warning(disable:4786)
#include <string>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5App:
// See ClientDemo5.cpp for the implementation of this class
//

class CClientDemo5App : public CWinApp
{
public:
	CClientDemo5App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo5App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientDemo5App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void g_SetWndStaticText(CWnd * pWnd);
void ConvertComboBox(CComboBox &stuComboBox);
CString ConvertString(CString strText);
void Translate(string strData, vector<string>& vecOut);
void g_RefreshAlarmName(vector<string> *vecAlarmName, int nIndex, CEdit& editAlarmName);
void g_OnChangeEditAlarmname(vector<string>* vecAlarmName, int nIndex, CEdit& editAlarmName);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO5_H__2BCE6C28_87FD_400A_BF6D_95C784696FC9__INCLUDED_)
