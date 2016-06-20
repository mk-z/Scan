// Login.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSb.h"
#include "Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogin dialog


CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent),
	m_lLongHandle(0)
{
	//{{AFX_DATA_INIT(CLogin)
	ZeroMemory(&m_stuNetDevInfo, sizeof(m_stuNetDevInfo));
	//}}AFX_DATA_INIT
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

/////////////////////////////////////////////////////////////////////////////
// CLogin message handlers

BOOL CLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	m_ctrlIP.SetWindowText(_T("172.31.1.137"));
	SetDlgItemInt(IDC_LOGIN_EDT_PORTNUM, 37777, FALSE);
	SetDlgItemText(IDC_LOGIN_EDT_USERNAME, _T("admin"));
	SetDlgItemText(IDC_LOGIN_EDT_PSW, _T("admin"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogin::OnOK() 
{
	// TODO: Add extra validation here
	BYTE byIP[4] = {0};
	m_ctrlIP.GetAddress(byIP[0], byIP[1], byIP[2], byIP[3]);
	if (!byIP[0] && !byIP[1] && !byIP[1] && !byIP[1])
	{
		AfxMessageBox(ConvertString(_T("Error IP")));
		return;
	}

	int nPortNum = GetDlgItemInt(IDC_LOGIN_EDT_PORTNUM, &nPortNum, FALSE);
	if (!nPortNum)
	{
		AfxMessageBox(ConvertString(_T("Error PortNumber")));
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
	LLONG lLoginHandle	= ::CLIENT_Login(szIP, (WORD)nPortNum, szUserName, szPsw, &DevInfo, &nErr);

	if (!lLoginHandle)
	{
		TCHAR szErrMsg[64] = {0};
		_sntprintf(szErrMsg,
				   sizeof(szErrMsg), 
				   _T("%s: %08x"),
				   ConvertString(_T("Login Failed, Error Code")),
				   nErr);
		AfxMessageBox(szErrMsg);
		return;
	}

	if (DevInfo.byDVRType != NET_IVS_B)
	{
		//::CLIENT_Logout(lLoginHandle);
		AfxMessageBox(ConvertString(_T("This device may not support IVS-B")));
		//return;
	}

	m_lLongHandle = lLoginHandle;
	memcpy(&m_stuNetDevInfo, &DevInfo, sizeof(DevInfo));

	::OutputDebugString(_T("Login success.\n"));

	CDialog::OnOK();
}
