// ClientDemo5.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5App

BEGIN_MESSAGE_MAP(CClientDemo5App, CWinApp)
	//{{AFX_MSG_MAP(CClientDemo5App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5App construction

bool GetModulePath(const char* szDllName, char* szModuleDir)
{
	HMODULE hModule = NULL;
//	if (szDllName != NULL)
//	{
		hModule = ::GetModuleHandle(szDllName);
		if (hModule == NULL)
		{
			return false;
		}
//	}
	char szFullDllPath[_MAX_PATH] = {0};
	::GetModuleFileName(hModule, szFullDllPath, _MAX_PATH);
	char* lastBackslash = strrchr(szFullDllPath, '\\');
	int lastBackslashPos = lastBackslash - szFullDllPath + 1;
	strncpy(szModuleDir, szFullDllPath, lastBackslashPos);
	return true;
}

CString ConvertString(CString strText)
{
	char *val = new char[200];
	CString strIniPath,strRet;

	char buf[MAX_PATH] = {0};
	bool bRet = GetModulePath(NULL, buf);
	if (bRet)
	{
		strIniPath = buf;
	    strIniPath +="//langchn.ini";
	}
	
	memset(val,0,200);
	GetPrivateProfileString("String",strText,"",
		val,200, strIniPath);//"./langchn.ini"
	strRet = val;
	if(strRet.GetLength()==0)
	{
		//If there is no corresponding string in ini file. Set it to default value(English)
		strRet=strText;
	}
	delete val;
	return strRet;
}

void ConvertComboBox(CComboBox &stuComboBox)
{
	int nCount = stuComboBox.GetCount();
	if(nCount <= 0)
	{
		return;
	}
	CString* strText = new CString[nCount];
	DWORD* dwData = new DWORD[nCount];
	int i = 0;
	for(i = 0; i < nCount;i++)
	{
		stuComboBox.GetLBText(i, strText[i]);
		strText[i] = ConvertString(strText[i]);
		dwData[i] = stuComboBox.GetItemData(i);
	}
	stuComboBox.ResetContent();
	for(i = 0; i< nCount; i++)
	{
		stuComboBox.SetItemData(stuComboBox.AddString(strText[i]), dwData[i]);
	}
	delete []strText;
	delete []dwData;
}

//Set current dialogue box static text(English -->Current language)
void g_SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;
	
	//Set main window title 
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText=ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}
	
	//Set sub-window title 
	CWnd * pChild=pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit")
		{
			//Nex sub-window 
			pChild=pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////	
		
		//Set sub-window current language text
		pChild->GetWindowText(strCaption);
		strText=ConvertString(strCaption);
		pChild->SetWindowText(strText);
		
		//Next sub-window 
		pChild=pChild->GetWindow(GW_HWNDNEXT);
	}
}

void Translate(string strData, vector<string>& vecOut)
{
	if (strData.empty())
	{
		return;
	}
	
	int nIndex = strData.find_first_of('&');
	if (nIndex == -1)//找不到&字符，返回
	{
		return;
	}
	
	if (strData.size()<=nIndex+1 || strData[nIndex+1]!='&')//找的&，但是&后面没有&，即不是&&格式
	{
		return;
	}
	vecOut.push_back(strData.substr(0,nIndex));
	Translate(strData.substr(strData.find_first_of('&')+2),vecOut);
};

void g_RefreshAlarmName(vector<string> *vecAlarmName, int nIndex, CEdit& editAlarmName)
{
	if (vecAlarmName == NULL)
	{
		return;
	}

	if (vecAlarmName->size() > nIndex)
	{
		editAlarmName.EnableWindow(TRUE);
		editAlarmName.SetWindowText((*vecAlarmName)[nIndex].c_str());
	}
	else
	{
		editAlarmName.EnableWindow(FALSE);
		editAlarmName.SetWindowText("");
	}
}

void g_OnChangeEditAlarmname(vector<string>* vecAlarmName, int nIndex, CEdit& editAlarmName) 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (vecAlarmName == NULL)
	{
		return;
	}

	if (vecAlarmName->size() > nIndex)
	{
		CString str;
		editAlarmName.GetWindowText(str);
		TRACE("\r\n");
		TRACE(str.Left(32));
		(*vecAlarmName)[nIndex] = str.GetLength() > 32 ? str.Left(32) : str.GetBuffer(0);
	}
	
}



CClientDemo5App::CClientDemo5App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClientDemo5App object

CClientDemo5App theApp;

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5App initialization

BOOL CClientDemo5App::InitInstance()
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

	CClientDemo5Dlg dlg;
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








































































































































































































































































































































































































































































































































