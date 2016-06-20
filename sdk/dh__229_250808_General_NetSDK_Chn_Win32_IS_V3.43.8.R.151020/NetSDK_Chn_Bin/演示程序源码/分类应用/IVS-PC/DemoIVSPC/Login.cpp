// Login.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSPC.h"
#include "Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent),
	m_lLongHandle(0)
{
	ZeroMemory(&m_stuNetDevInfo, sizeof(m_stuNetDevInfo));
}


void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogin)
	DDX_Control(pDX, IDC_LOGIN_IPADDR_IP, m_ctrlIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	//{{AFX_MSG_MAP(CLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	m_ctrlIP.SetWindowText(_T("10.36.45.93"));
	SetDlgItemInt(IDC_LOGIN_EDT_PORTNUM, 37777, FALSE);
	SetDlgItemText(IDC_LOGIN_EDT_USERNAME, _T("admin"));
	SetDlgItemText(IDC_LOGIN_EDT_PSW, _T("admin"));
	
	return TRUE;
}

void CLogin::OnOK() 
{
	// TODO: Add extra validation here
	BYTE byIP[4] = {0};
	m_ctrlIP.GetAddress(byIP[0], byIP[1], byIP[2], byIP[3]);
	if (!byIP[0] && !byIP[1] && !byIP[1] && !byIP[1])
	{
		MessageBox(ConvertString("Error IP!"),ConvertString("Prompt"));
		return;
	}

	int nPortNum = GetDlgItemInt(IDC_LOGIN_EDT_PORTNUM, &nPortNum, FALSE);
	if (!nPortNum)
	{
		MessageBox(ConvertString("Error PortNumber!"),ConvertString("Prompt"));
		return;
	}

	char szIP[16] = {0};
	m_ctrlIP.GetWindowText(szIP, 16);

	char szUserName[64] = {0};
	GetDlgItemText(IDC_LOGIN_EDT_USERNAME, szUserName, 64);

	char szPsw[64] = {0};
	GetDlgItemText(IDC_LOGIN_EDT_PSW, szPsw, 64);

	NET_DEVICEINFO DevInfo = {0};
	int nErr = 0;
	LLONG lLoginHandle
		= ::CLIENT_Login(szIP, (WORD)nPortNum, szUserName, szPsw, &DevInfo, &nErr);

	if (!lLoginHandle)
	{
		CString strError(ConvertString("Login Failed, Error Code:"));
		CString strErrorCode;
		strErrorCode.Format("%08x", nErr);
		strError += strErrorCode;
		MessageBox(strError,ConvertString("Prompt"));
		return;
	}
	if ( DevInfo.byDVRType != NET_IVS_PC)
	{
		MessageBox(ConvertString("This device isn't type of IVS-PC!"),ConvertString("Prompt"));
	}

	m_lLongHandle = lLoginHandle;
	memcpy(&m_stuNetDevInfo, &DevInfo, sizeof(DevInfo));

	::OutputDebugString(_T("Login success!"));

	CDialog::OnOK();
}
