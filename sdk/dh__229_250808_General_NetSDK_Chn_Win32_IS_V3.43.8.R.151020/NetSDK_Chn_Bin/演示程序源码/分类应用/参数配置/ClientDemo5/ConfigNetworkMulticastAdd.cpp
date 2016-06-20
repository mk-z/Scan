// ConfigNetworkMulticastAdd.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigNetworkMulticastAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigNetworkMulticastAdd dialog


CConfigNetworkMulticastAdd::CConfigNetworkMulticastAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigNetworkMulticastAdd::IDD, pParent),
	m_pInfo(NULL),
	m_nCastType(0),
	m_dwChannel(0)
{
	//{{AFX_DATA_INIT(CConfigNetworkMulticastAdd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigNetworkMulticastAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigNetworkMulticastAdd)
	DDX_Control(pDX, IDC_IPADDRESS_LOCALIP, m_ctrlLocalIP);
	DDX_Control(pDX, IDC_IPADDRESS_HOSTIP, m_ctrlHostIP);
	DDX_Control(pDX, IDC_CHECK_REMOTEHOST, m_chkEnable);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_cmbStreamType);
	DDX_Control(pDX, IDC_COMBO_CASTTYPE, m_cmbCastType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigNetworkMulticastAdd, CDialog)
	//{{AFX_MSG_MAP(CConfigNetworkMulticastAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigNetworkMulticastAdd message handlers

BOOL CConfigNetworkMulticastAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	m_pInfo = new CFG_MULTICAST_INFO;
	if (m_pInfo)
	{
		memset(m_pInfo, 0, sizeof(*m_pInfo));
		m_pInfo->nStructSize = sizeof(*m_pInfo);
	}
	
	m_cmbCastType.InsertString(-1, ConvertString(_T("TS")));
	m_cmbCastType.InsertString(-1, ConvertString(_T("RTP")));
	m_cmbCastType.InsertString(-1, ConvertString(_T("DHII")));
	m_cmbCastType.SetCurSel(0);
	
	m_cmbStreamType.InsertString(-1, ConvertString("MainStream"));
	m_cmbStreamType.InsertString(-1, ConvertString("SubStream1"));
	m_cmbStreamType.InsertString(-1, ConvertString("SubStream2"));
	m_cmbStreamType.InsertString(-1, ConvertString("SubStream3"));
	m_cmbStreamType.SetCurSel(0);
	
	char szChn[16] = {0};
	m_cmbChannel.ResetContent();
	for (int i = 0; i < m_dwChannel; i++)
	{
		_sntprintf(szChn, 16, _T("%s%02d"), ConvertString("Channel:"), i + 1);
		m_cmbChannel.InsertString(-1, szChn);
		memset(szChn, 0, 16);
	}
	m_cmbChannel.SetCurSel(0);

	m_ctrlHostIP.SetAddress(0, 0, 0, 0);
	m_ctrlLocalIP.SetAddress(0, 0, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigNetworkMulticastAdd::OnOK() 
{
	// TODO: Add extra validation here
	m_nCastType = m_cmbCastType.GetCurSel();
	if (m_nCastType == -1)
	{
		return;
	}
	
	m_pInfo->bEnable = m_chkEnable.GetCheck();

	if (m_cmbChannel.GetCurSel() == -1)
	{
		return;
	}
	m_pInfo->nChannelID = m_cmbChannel.GetCurSel();

	if (m_cmbStreamType.GetCurSel() == -1)
	{
		return;
	}
	m_pInfo->nStreamType = m_cmbStreamType.GetCurSel();

	GetDlgItemText(IDC_IPADDRESS_HOSTIP, m_pInfo->szMulticastAddr, MAX_ADDRESS_LEN);
	m_pInfo->nPort = GetDlgItemInt(IDC_EDIT_HOSTPORT, &m_pInfo->nPort, FALSE);
	if (m_pInfo->nPort <= 0 || m_pInfo->nPort > 65536)
	{
		return;
	}

	GetDlgItemText(IDC_IPADDRESS_LOCALIP, m_pInfo->szLocalAddr, MAX_ADDRESS_LEN);

	CDialog::OnOK();
}

void CConfigNetworkMulticastAdd::InitDlg(DWORD dwChnCount)
{
	m_dwChannel = dwChnCount;
}

void CConfigNetworkMulticastAdd::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (m_pInfo)
	{
		delete m_pInfo;
		m_pInfo = NULL;
	}

	CDialog::OnCancel();
}
