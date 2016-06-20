// DemoIVSb.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DemoIVSb.h"
#include "DemoIVSbDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoIVSbApp

BEGIN_MESSAGE_MAP(CDemoIVSbApp, CWinApp)
	//{{AFX_MSG_MAP(CDemoIVSbApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoIVSbApp construction

CDemoIVSbApp::CDemoIVSbApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDemoIVSbApp object

CDemoIVSbApp theApp;

CPlayAPI s_PlayAPI;

/////////////////////////////////////////////////////////////////////////////
// CDemoIVSbApp initialization

BOOL CDemoIVSbApp::InitInstance()
{
	AfxEnableControlContainer();

	// Initializationi of SDK
	if (!::CLIENT_Init(NULL, 0))
	{
		::MessageBox(NULL, 
					 ConvertString(_T("Initialization of SDK Error")),
					 ConvertString(_T("Error")), 
					 MB_OK);
	}
	
	// Initialization of draw tool for drawing rules, tracks, etc
	::DRAW_Startup();
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	CDemoIVSbDlg dlg;
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

int CDemoIVSbApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	// Uninitialization of SDK
	::DRAW_Cleanup();

	// Uninitialization of draw tool
	::CLIENT_Cleanup();
	
	return CWinApp::ExitInstance();
}
/*
 *	callback funtion for receive&process stream data
 */
void CALLBACK RealDataCallBackEx(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize, LONG lParam, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	
	//Stream port number according to the real-time handle.
	long lRealPort = 450;
	//Input the stream data getting from the card
	BOOL bInput = FALSE;
	if(0 != lRealPort)
	{
		switch(dwDataType) {
		case 0:
			//Original data 

			// Actually, in this Demo, PLAY_InputData() is used only when lRealPort == g_nPlayPort
			bInput = s_PlayAPI.PLAY_InputData(lRealPort, pBuffer, dwBufSize);
			break;
		case 1:
			//Standard video data 
			
			break;
		case 2:
			//yuv data 
			
			break;
		case 3:
			//pcm audio data 
			
			break;
		case 4:
			//Original audio data 
			
			break;
		default:
			break;
		}	
	}
}
/*
 *	
 */
CString ConvertString(CString strText)
{
	CString strIniPath, strRet;
	char *val = new char[200];
	if (!val)
	{
		return strRet;
	}
	
	memset(val,0,200);
	GetPrivateProfileString("String", strText, "", val, 200, "./langchn.ini");
	strRet = val;
	if(strRet.GetLength()==0)
	{
		//If there is no corresponding string in ini file then set it to be deafault value(English).
		strRet=strText;
	}
	delete[] val;
	return strRet;
}
/*
 *	
 */
//Set static text for dialogue box(English->current language)
void g_SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;
	
	//Set main window title 
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText = ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}
	
	//Set small window title
	CWnd * pChild = pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit")
		{
			//The next small window 
			pChild = pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////	
		
		//Set current language text for small window. 
		pChild->GetWindowText(strCaption);
		strText = ConvertString(strCaption);
		pChild->SetWindowText(strText);
		
		//Next small window 
		pChild = pChild->GetWindow(GW_HWNDNEXT);
	}
}
/*
 *	
 */
int g_getStructSize(int nRuleType)
{
	int nSize = 0;

	switch(nRuleType)
	{
		//1CrossFence
	case EVENT_IVS_CROSSFENCEDETECTION:
		nSize = sizeof(CFG_CROSSFENCEDETECTION_INFO);
		break;
		//2CrossLine
	case EVENT_IVS_CROSSLINEDETECTION:
		nSize = sizeof(CFG_CROSSLINE_INFO);
		break;
		//3CrossRegion
	case EVENT_IVS_CROSSREGIONDETECTION:
		nSize = sizeof(CFG_CROSSREGION_INFO);
		break;
		//4Move
	case EVENT_IVS_MOVEDETECTION:
		nSize = sizeof(CFG_MOVE_INFO);
		break;
		//5Left
	case EVENT_IVS_LEFTDETECTION:
		nSize = sizeof(CFG_LEFT_INFO);
		break;
		//6Parking
	case EVENT_IVS_PARKINGDETECTION:
		nSize = sizeof(CFG_PARKINGDETECTION_INFO);
		break;
		//7Preservation
	case EVENT_IVS_PRESERVATION:
		nSize = sizeof(CFG_PRESERVATION_INFO);
		break;
		//8Retro
	case EVENT_IVS_RETROGRADEDETECTION:
		nSize = sizeof(CFG_RETROGRADEDETECTION_INFO);
		break;
		//9Stay
	case EVENT_IVS_STAYDETECTION:
		nSize = sizeof(CFG_STAY_INFO);
		break;
		//10TakenAway
	case EVENT_IVS_TAKENAWAYDETECTION:
		nSize = sizeof(CFG_TAKENAWAYDETECTION_INFO);
		break;
		//11VideoAbnormal
	case EVENT_IVS_VIDEOABNORMALDETECTION:
		nSize = sizeof(CFG_VIDEOABNORMALDETECTION_INFO);
		break;
		//12Wander
	case EVENT_IVS_WANDERDETECTION:
		nSize = sizeof(CFG_WANDER_INFO);
		 break;
	default:
		break;
	}
	return nSize;
}
/*
 *	
 */
CString g_convertRuleTypeToString(DWORD dwType)
{
	CString strName;

	switch(dwType)
	{
		//0Paste
	 case EVENT_IVS_PASTEDETECTION:	
		 strName = ConvertString(_T("Paste"));
		 break;
		 //1
	 case EVENT_IVS_CROSSFENCEDETECTION:
		 strName = ConvertString(_T("CrossFence"));
		 break;
		 //2
	 case EVENT_IVS_CROSSLINEDETECTION:
		 strName = ConvertString(_T("CrossLine"));
		 break;
		 //3CrossRegion
	 case EVENT_IVS_CROSSREGIONDETECTION:
		 strName = ConvertString(_T("CrossRegion"));
		 break;
		 //4Move
	 case EVENT_IVS_MOVEDETECTION:
		 strName = ConvertString(_T("Move"));
		 break;
		 //5Left
	 case EVENT_IVS_LEFTDETECTION:
		 strName = ConvertString(_T("Left"));
		 break;
		 //6Parking
	 case EVENT_IVS_PARKINGDETECTION:
		 strName = ConvertString(_T("Parking"));
		 break;
		 //7Preservation
	 case EVENT_IVS_PRESERVATION:
		 strName = ConvertString(_T("Preservation"));
		 break;
		 //8Retro
	 case EVENT_IVS_RETROGRADEDETECTION:
		 strName = ConvertString(_T("Retrograde"));
		 break;
		 //9Stay
	 case EVENT_IVS_STAYDETECTION:
		 strName = ConvertString(_T("Stay"));
		 break;
		 //10TakenAway
	 case EVENT_IVS_TAKENAWAYDETECTION:
		 strName = ConvertString(_T("TakenAway"));
		 break;
		 //11VideoAbnormal
	 case EVENT_IVS_VIDEOABNORMALDETECTION:
		 strName = ConvertString(_T("VideoAbnormal"));
		 break;
		 //12Wander
	 case EVENT_IVS_WANDERDETECTION:
		 strName = ConvertString(_T("Wander"));
		 break;
	}

	return strName;
}
/*
 *	
 */
int g_getStructInfo(DWORD dwAlarmType)
{
	int nLen = 0;
	
	switch(dwAlarmType)
	{
		//0Paste
	case EVENT_IVS_PASTEDETECTION:
		nLen = sizeof(DEV_EVENT_PASTE_INFO);
		break;
		//1
	case EVENT_IVS_CROSSFENCEDETECTION:
		nLen = sizeof(DEV_EVENT_CROSSFENCEDETECTION_INFO);
		break;
		//2
	case EVENT_IVS_CROSSLINEDETECTION:
		nLen = sizeof(DEV_EVENT_CROSSLINE_INFO);
		break;
		//3CrossRegion
	case EVENT_IVS_CROSSREGIONDETECTION:
		nLen = sizeof(DEV_EVENT_CROSSREGION_INFO);
		break;
		//4Move
	case EVENT_IVS_MOVEDETECTION:
		nLen = sizeof(DEV_EVENT_MOVE_INFO);
		break;
		//5Left
	case EVENT_IVS_LEFTDETECTION:
		nLen = sizeof(DEV_EVENT_LEFT_INFO);
		break;
		//6Parking
	case EVENT_IVS_PARKINGDETECTION:
		nLen = sizeof(DEV_EVENT_PARKINGDETECTION_INFO);
		break;
		//7Preservation
	case EVENT_IVS_PRESERVATION:
		nLen = sizeof(DEV_EVENT_PRESERVATION_INFO);
		break;
		//8Retro
	case EVENT_IVS_RETROGRADEDETECTION:
		nLen = sizeof(DEV_EVENT_RETROGRADEDETECTION_INFO);
		break;
		//9Stay
	case EVENT_IVS_STAYDETECTION:
		nLen = sizeof(DEV_EVENT_STAY_INFO);
		break;
		//10TakenAway
	case EVENT_IVS_TAKENAWAYDETECTION:
		nLen = sizeof(DEV_EVENT_TAKENAWAYDETECTION_INFO);
		break;
		//11VideoAbnormal
	case EVENT_IVS_VIDEOABNORMALDETECTION:
		nLen = sizeof(DEV_EVENT_VIDEOABNORMALDETECTION_INFO);
		break;
		//12Wander
	case EVENT_IVS_WANDERDETECTION:
		nLen = sizeof(DEV_EVENT_WANDER_INFO);
		break;
	}

	return nLen;
}