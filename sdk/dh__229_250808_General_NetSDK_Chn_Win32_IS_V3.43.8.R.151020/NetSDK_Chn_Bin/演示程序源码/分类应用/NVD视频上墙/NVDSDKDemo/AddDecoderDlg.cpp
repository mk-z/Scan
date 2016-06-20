// AddDecoderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NVDSDKDemo.h"
#include "AddDecoderDlg.h"
#include "dhnetsdk.h"
#include <Winsock2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddDecoderDlg dialog


CAddDecoderDlg::CAddDecoderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDecoderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddDecoderDlg)
	m_strDecIp = _T("10.43.3.56");
	m_strDecName = _T("Decoder");
	m_nDecPort = 37777;
	m_strDecPwd = _T("admin");
	m_strDecUser = _T("admin");
	//}}AFX_DATA_INIT
	m_nMonitorNum = 0;
}


void CAddDecoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddDecoderDlg)
	DDX_Text(pDX, IDC_EDIT_DEC_IP, m_strDecIp);
	DDV_MaxChars(pDX, m_strDecIp, 63);
	DDX_Text(pDX, IDC_EDIT_DEC_NAME, m_strDecName);
	DDX_Text(pDX, IDC_EDIT_DEC_PORT, m_nDecPort);
	DDX_Text(pDX, IDC_EDIT_DEC_PWD, m_strDecPwd);
	DDX_Text(pDX, IDC_EDIT_DEC_USER, m_strDecUser);
	DDV_MaxChars(pDX, m_strDecUser, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddDecoderDlg, CDialog)
	//{{AFX_MSG_MAP(CAddDecoderDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddDecoderDlg message handlers

void CAddDecoderDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	int nErrorCode = 0;
	NET_DEVICEINFO stuDevInfo = {0};
	hostent* lpHosttent = gethostbyname(m_strDecIp.GetBuffer(0));
	if (lpHosttent == NULL)
	{
		nErrorCode = 10;
		ShowLoginErrorReason(nErrorCode);
		return;
	}
	in_addr addr = {0};
	addr.s_addr = *(u_long *) lpHosttent->h_addr_list[0];
	CString strTmp = inet_ntoa(addr);

	m_lLoginHandle = CLIENT_Login(strTmp.GetBuffer(0), m_nDecPort, m_strDecUser.GetBuffer(0), m_strDecPwd.GetBuffer(0), &stuDevInfo, &nErrorCode);
	if (m_lLoginHandle == 0)
	{
		//Display login failed reason
		ShowLoginErrorReason(nErrorCode);
		return;
	}

	DEV_DECODER_INFO devDecoderInfo = {0};
	BOOL bRet = CLIENT_QueryDecoderInfo(m_lLoginHandle, &devDecoderInfo, 3000);
	if(bRet == FALSE)
	{
		AfxMessageBox(ConvertString("Query decoder information failed!"));
		return;
	}
	
	m_nMonitorNum = devDecoderInfo.nMonitorNum;
	
	CDialog::OnOK();
}

void CAddDecoderDlg::ShowLoginErrorReason(int nError)
{
	if(1 == nError)		MessageBox(ConvertString("Invalid password!"), ConvertString("Prompt"));
	else if(2 == nError)	MessageBox(ConvertString("Invalid account!"), ConvertString("Prompt"));
	else if(3 == nError)	MessageBox(ConvertString("Timeout!"), ConvertString("Prompt"));
	else if(4 == nError)	MessageBox(ConvertString("The user has logged in!"), ConvertString("Prompt"));
	else if(5 == nError)	MessageBox(ConvertString("The user has been locked!"), ConvertString("Prompt"));
	else if(6 == nError)	MessageBox(ConvertString("The user has listed into illegal!"), ConvertString("Prompt"));
	else if(7 == nError)	MessageBox(ConvertString("The system is busy!"), ConvertString("Prompt"));
	else if(9 == nError)	MessageBox(ConvertString("You Can't find the network server!"), ConvertString("Prompt"));
	else if(10 == nError)  MessageBox(ConvertString("Wrong IP address!"));
	else	MessageBox(ConvertString("Login failed!"), ConvertString("Prompt"));
}

BOOL CAddDecoderDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
