// AddDeviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NVDSDKDemo.h"
#include "AddDeviceDlg.h"
#include "dhnetsdk.h"
#include <Winsock2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddDeviceDlg dialog


CAddDeviceDlg::CAddDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDeviceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddDeviceDlg)
	m_strDevIp = _T("10.6.10.16");
	m_strDevName = _T("test");
	m_nDevPort = 37777;
	m_strDevPwd = _T("");
	m_strDevUser = _T("1");
	//}}AFX_DATA_INIT
	m_lLoginHandle = 0;
	m_nMonitorNum = 0;
	m_dwStreamType = 0;
}


void CAddDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddDeviceDlg)
	DDX_Text(pDX, IDC_EDIT_DEV_IP, m_strDevIp);
	DDV_MaxChars(pDX, m_strDevIp, 63);
	DDX_Text(pDX, IDC_EDIT_DEV_NAME, m_strDevName);
	DDX_Text(pDX, IDC_EDIT_DEV_PORT, m_nDevPort);
	DDX_Text(pDX, IDC_EDIT_DEV_PWD, m_strDevPwd);
	DDX_Text(pDX, IDC_EDIT_DEV_USER, m_strDevUser);
	DDV_MaxChars(pDX, m_strDevUser, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddDeviceDlg, CDialog)
	//{{AFX_MSG_MAP(CAddDeviceDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddDeviceDlg message handlers

void CAddDeviceDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	int nErrorCode = 0;
	NET_DEVICEINFO stuDevInfo = {0};
	hostent* lpHosttent = gethostbyname(m_strDevIp.GetBuffer(0));	
	in_addr addr = {0};
	addr.s_addr = *(u_long *) lpHosttent->h_addr_list[0];
	CString strTmp = inet_ntoa(addr);
	m_lLoginHandle = CLIENT_Login(strTmp.GetBuffer(0), m_nDevPort, m_strDevUser.GetBuffer(0), m_strDevPwd.GetBuffer(0), &stuDevInfo, &nErrorCode);
	if (m_lLoginHandle == 0)
	{
		//Display login failed reason
		ShowLoginErrorReason(nErrorCode);
		return;
	}

	int nRetLen = 0;
	NET_DEV_CHN_COUNT_INFO stuChn = { sizeof(NET_DEV_CHN_COUNT_INFO) };
	stuChn.stuVideoIn.dwSize = sizeof(stuChn.stuVideoIn);
	stuChn.stuVideoOut.dwSize = sizeof(stuChn.stuVideoOut);
	CLIENT_QueryDevState(m_lLoginHandle, DH_DEVSTATE_DEV_CHN_COUNT, (char*)&stuChn, stuChn.dwSize, &nRetLen);
	m_nMonitorNum = __max(stuDevInfo.byChanNum,stuChn.stuVideoIn.nMaxTotal);

// 	DEV_DECODER_INFO devDecoderInfo = {0};
// 	if(!CLIENT_QueryDecoderInfo(m_lLoginHandle, &devDecoderInfo, 3000))
// 	{
// 		AfxMessageBox(ConvertString("Query decoder information failed!"));
// 		return;
// 	}
// 
// 	m_nMonitorNum = devDecoderInfo.nMonitorNum;

	//取前端设备是不是支持双码流
	DWORD retlen = 0;
	DHDEV_SYSTEM_ATTR_CFG stusysCFG = {0};
	BOOL bRet = CLIENT_GetDevConfig(m_lLoginHandle, DH_DEV_DEVICECFG, 0, &stusysCFG, sizeof(DHDEV_SYSTEM_ATTR_CFG), &retlen, 1000);
	if (!bRet || retlen != sizeof(DHDEV_SYSTEM_ATTR_CFG))
	{
		m_dwStreamType = 0;//主码流		
	}
	else
	{
		if (stusysCFG.stDspEncodeCap.dwStreamCap > 0x01)
		{
			m_dwStreamType = 1;
		}
		else 
		{
			m_dwStreamType = 0;
		}	 	
	}
	
	CDialog::OnOK();
}

void CAddDeviceDlg::ShowLoginErrorReason(int nError)
{
	if(1 == nError)		MessageBox(ConvertString("Invalid password!"), ConvertString("Prompt"));
	else if(2 == nError)	MessageBox(ConvertString("Invalid account!"), ConvertString("Prompt"));
	else if(3 == nError)	MessageBox(ConvertString("Timeout!"), ConvertString("Prompt"));
	else if(4 == nError)	MessageBox(ConvertString("The user has logged in!"), ConvertString("Prompt"));
	else if(5 == nError)	MessageBox(ConvertString("The user has been locked!"), ConvertString("Prompt"));
	else if(6 == nError)	MessageBox(ConvertString("The user has listed into illegal!"), ConvertString("Prompt"));
	else if(7 == nError)	MessageBox(ConvertString("The system is busy!"), ConvertString("Prompt"));
	else if(9 == nError)	MessageBox(ConvertString("You Can't find the network server!"), ConvertString("Prompt"));
	else	MessageBox(ConvertString("Login failed!"), ConvertString("Prompt"));
}
BOOL CAddDeviceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
