// DemoIVSPC.h : main header file for the DEMOIVSPC application
//

#if !defined(AFX_DEMOIVSPC_H__902FE451_4E3D_4E43_9666_B8FD7A29EF56__INCLUDED_)
#define AFX_DEMOIVSPC_H__902FE451_4E3D_4E43_9666_B8FD7A29EF56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "GlobalDef.h"

#include "../Include/IvsDrawer.h"
#pragma comment(lib, "../Lib/IvsDrawer.lib")


class CDemoIVSPCApp : public CWinApp
{
public:
	CDemoIVSPCApp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	DECLARE_MESSAGE_MAP()

};


#endif // !defined(AFX_DEMOIVSPC_H__902FE451_4E3D_4E43_9666_B8FD7A29EF56__INCLUDED_)
