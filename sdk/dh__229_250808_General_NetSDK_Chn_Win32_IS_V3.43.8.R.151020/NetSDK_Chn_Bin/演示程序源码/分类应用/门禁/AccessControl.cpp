// AccessControl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AccessControl.h"
#include "AccessControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccessControlApp

BEGIN_MESSAGE_MAP(CAccessControlApp, CWinApp)
	//{{AFX_MSG_MAP(CAccessControlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccessControlApp construction

CAccessControlApp::CAccessControlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	theCrashDumper.Enable(_T("AccessControlDemo"), true, _T("C:\\"));
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAccessControlApp object

CAccessControlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAccessControlApp initialization

BOOL CAccessControlApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CAccessControlDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CString ConvertString(CString strText, const char* pszSeg /* = NULL */)
{
	CString strIniPath, strRet;
	char szVal[256] = {0};
	
	if (!pszSeg)
	{
		pszSeg = DLG_MAIN;
	}
	
	GetPrivateProfileString(pszSeg, strText, "", szVal, sizeof(szVal), "./langchn.ini");
	strRet = szVal;
	if(strRet.GetLength()==0)
	{
		//If there is no corresponding string in ini file then set it to be default value(English).
		strRet=strText;
	}
	
	return strRet;
}

//Set static text in the dialogue box(English->current language) 
void g_SetWndStaticText(CWnd * pWnd, const char* pszSeg /* = NULL */)
{
	CString strCaption,strText;
	
	//Set main window title 
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText=ConvertString(strCaption, pszSeg);
		pWnd->SetWindowText(strText);
		
	}
	
	//Set sub-window title 
	CWnd * pChild=pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit")
		{
			//The next sub-window 
			pChild=pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////	
		
		//Set current language text in the sub-window 
		pChild->GetWindowText(strCaption);
		strText=ConvertString(strCaption, pszSeg);
		pChild->SetWindowText(strText);
		
		//The next sub-window 
		pChild=pChild->GetWindow(GW_HWNDNEXT);
	}
}

void SenseTypeToStr(NET_SENSE_METHOD nSenseType, CString& szStr)
{
	if (NET_SENSE_DOOR == nSenseType)
	{
		szStr = "DoorMagnetism";
	}
	else if (NET_SENSE_PASSIVEINFRA == nSenseType)
	{
		szStr = "PassiveInfrared";
	}
	else if (NET_SENSE_GAS == nSenseType)
	{
		szStr = "GasSensor";
	}
	else if (NET_SENSE_SMOKING == nSenseType)
	{
		szStr = "SmokingSensor";
	}
	else if (NET_SENSE_WATER == nSenseType)
	{
		szStr = "WaterSensor";
	}
	else if (NET_SENSE_ACTIVEFRA == nSenseType)
	{
		szStr = "ActiveInfrared";
	}
	else if (NET_SENSE_GLASS == nSenseType)
	{
		szStr = "GlassSensor";
	}
	else if (NET_SENSE_EMERGENCYSWITCH == nSenseType)
	{
		szStr = "EmergencySwitch";
	}
	else if (NET_SENSE_SHOCK == nSenseType)
	{
		szStr = "ShockSensor";
	}
	else if (NET_SENSE_DOUBLEMETHOD == nSenseType)
	{
		szStr = "DoubleMethod";
	}
	else if (NET_SENSE_THREEMETHOD == nSenseType)
	{
		szStr = "ThreeMethod";
	}
	else if (NET_SENSE_TEMP == nSenseType)
	{
		szStr = "TempSensor";
	}
	else if (NET_SENSE_HUMIDITY == nSenseType)
	{
		szStr = "HumiditySensor";
	}
	else if (NET_SENSE_CALLBUTTON == nSenseType)
	{
		szStr = "CallButton";
	}
	else if (NET_SENSE_OTHER == nSenseType)
	{
		szStr = "OtherSensor";
	}
	else
	{
		szStr = "UnknownSensor";
	}
}