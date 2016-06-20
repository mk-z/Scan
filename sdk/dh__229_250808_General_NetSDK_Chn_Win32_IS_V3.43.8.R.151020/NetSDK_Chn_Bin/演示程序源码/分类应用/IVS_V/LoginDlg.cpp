// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "LoginDlg.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CLoginDlg::CLoginDlg(std::vector<BYTE> *pvecDVRType, std::vector<BYTE> *pvecDVRTypeOut, CWnd* pParent /*=NULL*/)
: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//memcpy(m_szDvrType, szDVRType, sizeof(m_szDvrType));
	m_pvecDvrType = pvecDVRType;
	m_pvecDvrTypeOut = pvecDVRTypeOut;
} 

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_BTN_QUIT, OnBtnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	char    szIp[MAX_PATH] = {0};
	WORD    nPort = 0;
	char    szUsername[MAX_PATH] = {0};
	char    szPassword[MAX_PATH] = {0};

	//NET_DEVICEINFO stDevInfo = {0};
	int     nRet = 0;

	GetDlgItemText(IDC_EDIT_IP, szIp, MAX_PATH);
	GetDlgItemText(IDC_EDIT_USERNAME, szUsername, MAX_PATH);
	GetDlgItemText(IDC_EDIT_PASSWORD, szPassword, MAX_PATH);
	nPort = GetDlgItemInt(IDC_EDIT_PORT);

	char szErr[MAX_PATH] = {0};
	m_hLoginID = CLIENT_Login(szIp, nPort, szUsername, szPassword, &m_stDevInfo, &nRet);
	if (m_hLoginID > 0)
	{
		bool bErr = false;
		// 设备必须为智能服务器的情况
		if (NULL != m_pvecDvrType)
		{
			if (m_pvecDvrType->end() == std::find(m_pvecDvrType->begin(), m_pvecDvrType->end(), m_stDevInfo.byDVRType))
			{
				bErr = true;
			}
		}
		// 设备不能为智能服务器的情况
		if (NULL != m_pvecDvrTypeOut)
		{
			if (m_pvecDvrTypeOut->end() != std::find(m_pvecDvrTypeOut->begin(), m_pvecDvrTypeOut->end(), m_stDevInfo.byDVRType))
			{
				bErr = true;
			}
		}

		if (bErr)
		{
			sprintf(szErr, ConvertString("login %s:%d failure. device type error, type:%d !"), szIp, nPort, m_stDevInfo.byDVRType);
			OutputDebugString(szErr);
			AfxMessageBox(szErr);
		}
		else
		{
			memset(&m_stDevLoginInfo, 0x0, sizeof(CFG_TASK_REMOTEDEVICE));
			m_stDevLoginInfo.dwPort = nPort;
			memcpy(m_stDevLoginInfo.szAddress, szIp, sizeof(m_stDevLoginInfo.szAddress));
			memcpy(m_stDevLoginInfo.szUserName, szUsername, sizeof(m_stDevLoginInfo.szUserName));
			memcpy(m_stDevLoginInfo.szPassword, szPassword, sizeof(m_stDevLoginInfo.szPassword));
			memcpy(m_stDevLoginInfo.szProtocolType, "Main", sizeof(m_stDevLoginInfo.szPassword));
			CDialog::OnOK();
		}
	}
	else
	{
		sprintf(szErr, ConvertString("login %s:%d failure,error code:0x%x !"), szIp, nPort, nRet);
		OutputDebugString(szErr);
		AfxMessageBox(szErr);
	}
}

void CLoginDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	SetDlgItemText(IDC_EDIT_IP, "10.45.2.115");
	SetDlgItemText(IDC_EDIT_IP, "10.33.5.90");
	SetDlgItemText(IDC_EDIT_USERNAME, "admin");
	SetDlgItemText(IDC_EDIT_PASSWORD, "admin");
	SetDlgItemInt(IDC_EDIT_PORT,38888);

	g_SetWndStaticText(this);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CLoginDlg::Logout(DWORD hLoginID)
{
	return CLIENT_Logout(hLoginID);
}


void CLoginDlg::OnBtnQuit()
{
	EndDialog(-2);
}