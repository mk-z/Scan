// ConfigNetwork.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigNetwork.h"
#include "ClientDemo5Dlg.h"
#include "MessageText.h"
#include "ConfigNetworkMulticastAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigNetwork dialog


CConfigNetwork::CConfigNetwork(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigNetwork::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigNetwork)
	m_bTransmit = FALSE;
	m_bValid = FALSE;
	m_bVideoCP = FALSE;
	m_bDefault = FALSE;
	m_bMailEn = FALSE;
	m_bMailSSLEn = FALSE;
	m_nMaxTcp = 0;
	//}}AFX_DATA_INIT
	m_nCurEthernet = -1;
	m_nCurRemoteHost = -1;

	m_b3Dev = FALSE;
	m_dwChannel = 0;
	m_pstuMulticastInfo = NULL;
	m_pstuMIn = NULL;
	m_bDBEthernet = FALSE;
	m_nEthernetNum = -1;
// 	m_pstuMulticastInfo = new CFG_MULTICASTS_INFO_OUT;
// 	if (m_pstuMulticastInfo)
// 	{
// 		memset(m_pstuMulticastInfo, 0, sizeof(*m_pstuMulticastInfo));
// 	}
}


void CConfigNetwork::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigNetwork)
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_cmbStreamType);
	DDX_Control(pDX, IDC_COMBO_COUNT, m_cmbCount);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMBO_CASTTYPE, m_cmbCastType);
	DDX_Control(pDX, IDC_IPADDRESS_LOCALIP, m_ctrlLocalIP);
	DDX_Control(pDX, IDC_IPADDRESS_MAILIP, m_ctlMailIP);
	DDX_Control(pDX, IDC_IPADDRESS_NETIPMASK, m_ctlNetIPMask);
	DDX_Control(pDX, IDC_IPADDRESS_NETIP, m_ctlNetIP);
	DDX_Control(pDX, IDC_IPADDRESS_NETGATEWAY, m_ctlNetGateWay);
	DDX_Control(pDX, IDC_IPADDRESS_HOSTIP, m_ctlHostIP);
	DDX_Control(pDX, IDC_CHECK_REMOTEHOST, m_ctlChkRemote);
	DDX_Control(pDX, IDC_COMBO_REMOTEHOST, m_ctlRemoteHost);
	DDX_Control(pDX, IDC_COMBO_ETHERNET, m_ctlEthernet);
	DDX_Control(pDX, IDC_COMBO_NETINTERFACE, m_ctlNetInterface);
    DDX_Control(pDX, IDC_COMBO_NETMODE, m_ctlNetMode);
	DDX_Control(pDX, IDC_COMBO_DEFAULTCARD, m_ctlDefaultCard);
	DDX_Check(pDX, IDC_CHECK_TRANS, m_bTransmit);
	DDX_Check(pDX, IDC_CHECK_VALID, m_bValid);
	DDX_Check(pDX, IDC_CHECK_DHCP, m_bVideoCP);
	DDX_Check(pDX, IDC_CHECK_DEFAULT, m_bDefault);
	DDX_Check(pDX, IDC_CHECK_MAILEN, m_bMailEn);
	DDX_Check(pDX, IDC_CHECK_MAILSSLEN, m_bMailSSLEn);
	DDX_Check(pDX, IDC_CHECK_ANONYMITY, m_bAnoymity);
	DDX_Text(pDX, IDC_EDIT_MAXTCP, m_nMaxTcp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConfigNetwork, CDialog)
	//{{AFX_MSG_MAP(CConfigNetwork)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_CBN_SELCHANGE(IDC_COMBO_ETHERNET, OnSelchangeComboEthernet)
	ON_CBN_SELCHANGE(IDC_COMBO_REMOTEHOST, OnSelchangeComboRemotehost)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_CHECK_ANONYMITY, OnBnClickedCheckAnonymity)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_REMOTEHOST, OnCheckRemotehost)
	ON_CBN_SELCHANGE(IDC_COMBO_CASTTYPE, OnSelchangeComboCasttype)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_CBN_SELCHANGE(IDC_COMBO_COUNT, OnSelchangeComboCount)
	ON_BN_CLICKED(IDC_BUTTON_INC, OnButtonInc)
	ON_BN_CLICKED(IDC_BUTTON_DEC, OnButtonDec)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_HOSTIP, OnFieldchangedIpaddressHostip)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_LOCALIP, OnFieldchangedIpaddressLocalip)
	ON_EN_CHANGE(IDC_EDIT_HOSTPORT, OnChangeEditHostport)
	ON_CBN_SELCHANGE(IDC_COMBO_NETMODE, OnSelchangeComboNetmode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigNetwork message handlers

//Save
void CConfigNetwork::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	if(-1 != m_ctlEthernet.GetCurSel() && -1 != m_ctlRemoteHost.GetCurSel())
	{
        UpdateData(TRUE);
		SaveNetWork(m_nCurEthernet);
		SaveRemoteHost(m_nCurRemoteHost);
		
		GetDlgItemText(IDC_EDIT_DEVNAME, m_NetIOInfo.sDevName,DH_MAX_NAME_LEN);
        if( m_nMaxTcp <=0 || m_nMaxTcp > 65535)
        {
            MessageBox(ConvertString("Connect Count between:") + " [1 , 65535]" , ConvertString("Prompt")  );
            return;
        }
        m_NetIOInfo.wTcpMaxConnectNum = m_nMaxTcp;
		
		m_NetIOInfo.wTcpPort = GetDlgItemInt(IDC_EDIT_TCPPORT);
		m_NetIOInfo.wUdpPort = GetDlgItemInt(IDC_EDIT_UDPPORT);
		m_NetIOInfo.wHttpPort = GetDlgItemInt(IDC_EDIT_HTTPPORT);
		m_NetIOInfo.wHttpsPort = GetDlgItemInt(IDC_EDIT_HTTPSPORT);
		m_NetIOInfo.wSslPort = GetDlgItemInt(IDC_EDIT_SSLPORT);
		
		m_MailInfo.bAnonymous = m_bAnoymity;
		GetDlgItemText(IDC_EDIT_MAILUSERNAME, m_MailInfo.szUserName, MAX_USERNAME_LEN);
		GetDlgItemText(IDC_EDIT_MAILUSERPSW, m_MailInfo.szPassword, MAX_PASSWORD_LEN);
		GetDlgItemText(IDC_IPADDRESS_MAILIP, m_MailInfo.szAddress, MAX_ADDRESS_LEN);
		int nPortTmp = GetDlgItemInt(IDC_EDIT_MAILPORT);
		if (nPortTmp <= 0 || nPortTmp > 65535)
		{
            MessageBox(ConvertString("Port between:") + " [1 , 65535]" , ConvertString("Prompt")  );
			return;
		}
		m_MailInfo.nPort = nPortTmp;
		GetDlgItemText(IDC_EDIT_MAILSEDADDR, m_MailInfo.szSendAddress, MAX_ADDRESS_LEN);
	
		GetDlgItemText(IDC_EDIT_MAILDESADDR, m_MailInfo.szReceivers[0], MAX_ADDRESS_LEN);
		if (0 != strlen(m_MailInfo.szReceivers[0]))
		{
            m_MailInfo.nRetReciversNum = 1;
		}
		GetDlgItemText(IDC_EDIT_MAILCCADDR, m_MailInfo.szReceivers[1], MAX_ADDRESS_LEN);
        if (0 != strlen(m_MailInfo.szReceivers[1]))
        {
            m_MailInfo.nRetReciversNum = 2;
		}
		GetDlgItemText(IDC_EDIT_MAILBCCADDR, m_MailInfo.szReceivers[2], MAX_ADDRESS_LEN);
        if (0 != strlen(m_MailInfo.szReceivers[2]))
        {
            m_MailInfo.nRetReciversNum = 3;
		}
		GetDlgItemText(IDC_EDIT_MAILSUBJECT, m_MailInfo.szTitle, MAX_MAILTITLE_LEN);
		m_MailInfo.nSendInterv = GetDlgItemInt(IDC_EDIT_SENDINTERVAL);
		if (m_MailInfo.nSendInterv > 3600)
		{
			m_MailInfo.nSendInterv = 3600;
		}
		m_MailInfo.bEnable = m_bMailEn;
		m_MailInfo.bSslEnable = m_bMailSSLEn;

		//
		if (m_pstuMulticastInfo)
		{
			m_pstuMIn = new CFG_MULTICASTS_INFO_IN;
			if (!m_pstuMIn)
			{
				return;
			}
			memset(m_pstuMIn, 0, sizeof(*m_pstuMIn));
			m_pstuMIn->nStructSize = sizeof(*m_pstuMIn);

			//TS
			m_pstuMIn->nTSCount = m_lsTS.size();
			if (m_pstuMIn->nTSCount)
			{
				m_pstuMIn->pTSMulticast = new CFG_MULTICAST_INFO[m_pstuMIn->nTSCount];
				if (!m_pstuMIn->pTSMulticast)
				{
				}

				int i = 0;
				std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsTS.begin();
				char* pTmp = (char*)m_pstuMIn->pTSMulticast;
				while(it != m_lsTS.end())
				{
					CFG_MULTICAST_INFO* p = *it;
					memcpy(pTmp + i * sizeof(CFG_MULTICAST_INFO), p, sizeof(CFG_MULTICAST_INFO));
					it++;
					i++;
				}
			}
			
			//RTP
			m_pstuMIn->nRTPCount = m_lsRTP.size();
			if (m_pstuMIn->nRTPCount)
			{
				m_pstuMIn->pRTPMulticast = new CFG_MULTICAST_INFO[m_pstuMIn->nRTPCount];
				if (!m_pstuMIn->pRTPMulticast)
				{
				}
				
				int i = 0;
				std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsRTP.begin();
				char* pTmp = (char*)m_pstuMIn->pRTPMulticast;
				while(it != m_lsRTP.end())
				{
					CFG_MULTICAST_INFO* p = *it;
					memcpy(pTmp + i * sizeof(CFG_MULTICAST_INFO), *it, sizeof(CFG_MULTICAST_INFO));
					it++;
					i++;
				}
			}
			
			//DHII
			m_pstuMIn->nDHIICount = m_lsVideoII.size();
			if (m_pstuMIn->nDHIICount)
			{
				m_pstuMIn->pDHIIMulticast = new CFG_MULTICAST_INFO[m_pstuMIn->nDHIICount];
				if (!m_pstuMIn->pDHIIMulticast)
				{
				}
				
				int i = 0;
				std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsVideoII.begin();
				char* pTmp = (char*)m_pstuMIn->pDHIIMulticast;
				while(it != m_lsVideoII.end())
				{
					CFG_MULTICAST_INFO* p = *it;
					memcpy(pTmp + i * sizeof(CFG_MULTICAST_INFO), *it, sizeof(CFG_MULTICAST_INFO));
					it++;
					i++;
				}
			}
		}
		//Call father window  to save data
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetNetWorkConfigInfo(&m_NetIOInfo, m_MailInfo, m_pstuMIn);
		if (m_pstuMIn)
		{
			if (m_pstuMIn->pDHIIMulticast)
			{
				delete []m_pstuMIn->pDHIIMulticast;
				m_pstuMIn->pDHIIMulticast = NULL;
			}

			if (m_pstuMIn->pRTPMulticast)
			{
				delete []m_pstuMIn->pRTPMulticast;
				m_pstuMIn->pRTPMulticast = NULL;
			}

			if (m_pstuMIn->pTSMulticast)
			{
				delete []m_pstuMIn->pTSMulticast;
				m_pstuMIn->pTSMulticast = NULL;
			}

			delete m_pstuMIn;
			m_pstuMIn = NULL;
		}
	}
	else
	{
		MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
	}
}

//Read and get 
void CConfigNetwork::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	//First clear 
	CleanAll();
	//Call father widnow to get data 
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetNetWorkConfigInfo();
}

BOOL CConfigNetwork::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//Interface type
	m_ctlNetInterface.InsertString(0, ConvertString(NAME_NETCFG_NET1));
	m_ctlNetInterface.InsertString(1, ConvertString(NAME_NETCFG_NET2));
	m_ctlNetInterface.InsertString(2, ConvertString(NAME_NETCFG_NET3));
	m_ctlNetInterface.InsertString(3, ConvertString(NAME_NETCFG_NET4));
	m_ctlNetInterface.InsertString(4, ConvertString(NAME_NETCFG_NET5));
    m_ctlNetInterface.InsertString(5, ConvertString(NAME_NETCFG_NET6));
    m_ctlNetInterface.InsertString(6, ConvertString(NAME_NETCFG_NET7));
	
    //Net Mode
	int nIndex = 0;
	nIndex = m_ctlNetMode.AddString(ConvertString(NAME_NETMODE_BALANCE));
	m_ctlNetMode.SetItemData(nIndex,1);
	nIndex = m_ctlNetMode.AddString(ConvertString(NAME_NETMODE_MULTI));
	m_ctlNetMode.SetItemData(nIndex,2);
	nIndex = m_ctlNetMode.AddString(ConvertString(NAME_NETMODE_FAULT_TOERANT));
	m_ctlNetMode.SetItemData(nIndex,3);

	// 设备返回的数据格式为eth0 eth1...bond0,实际网卡数量为DH_MAX_ETHERNET_NUM_EX - 1
	CString strNet;
	for (int i = 0; i < DH_MAX_ETHERNET_NUM_EX - 1; i++)
	{
		strNet.Format(ConvertString("Ethernet network%d"), i+1);
		m_ctlDefaultCard.InsertString(i, strNet);
		
	}

	//Remote host 
	m_ctlRemoteHost.InsertString(0, ConvertString(NAME_NETCFG_REMOTE_ALARM));
	m_ctlRemoteHost.InsertString(1, ConvertString(NAME_NETCFG_REMOTE_LOG));
	m_ctlRemoteHost.InsertString(2, ConvertString(NAME_NETCFG_REMOTE_SMTP));
	m_ctlRemoteHost.InsertString(3, ConvertString(NAME_NETCFG_REMOTE_MULTICAST));
	m_ctlRemoteHost.InsertString(4, ConvertString(NAME_NETCFG_REMOTE_NFS));
	m_ctlRemoteHost.InsertString(5, ConvertString(NAME_NETCFG_REMOTE_PPPOE));
	m_ctlRemoteHost.InsertString(6, ConvertString(NAME_NETCFG_REMOTE_DDNS));
	m_ctlRemoteHost.InsertString(7, ConvertString(NAME_NETCFG_REMOTE_DNS));

	g_SetWndStaticText(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
 *	Function：Display network configuration information
 *	Input parameter：
 *	pNetIOInfo：Network configuration structure 
 *	nNetIOCount：Network port amount
 */
void CConfigNetwork::InitDlgInfo(DHDEV_NET_CFG_EX *pNetIOInfo, BYTE nNetIOCount, CFG_EMAIL_INFO *pMailInfo)
{
	if(pNetIOInfo != NULL)
	{
		m_NetIOInfo = *pNetIOInfo;
		m_MailInfo = *pMailInfo;
		//Set Ethernet network port dropdown menu 
		m_ctlEthernet.ResetContent();
		CString strNet;
		int i =0;
		int nIndex = 0;
		for (i = 0; i < nNetIOCount; i++)
		{
			strNet.Format(ConvertString("Ethernet network%d"), i+1);
			nIndex = m_ctlEthernet.AddString(strNet);
			m_ctlEthernet.SetItemData(nIndex,i);
		}
		
        m_nMaxTcp =  m_NetIOInfo.wTcpMaxConnectNum;
        UpdateData(FALSE);
		SetDlgItemText(IDC_EDIT_DEVNAME, m_NetIOInfo.sDevName);
		SetDlgItemInt(IDC_EDIT_TCPPORT, m_NetIOInfo.wTcpPort);
		SetDlgItemInt(IDC_EDIT_UDPPORT, m_NetIOInfo.wUdpPort);
		SetDlgItemInt(IDC_EDIT_HTTPPORT, m_NetIOInfo.wHttpPort);
		SetDlgItemInt(IDC_EDIT_HTTPSPORT, m_NetIOInfo.wHttpsPort);
		SetDlgItemInt(IDC_EDIT_SSLPORT, m_NetIOInfo.wSslPort);

		m_bAnoymity = m_MailInfo.bAnonymous;
		if (!m_bAnoymity)
		{
			SetDlgItemText(IDC_EDIT_MAILUSERNAME, m_MailInfo.szUserName);
			SetDlgItemText(IDC_EDIT_MAILUSERPSW, m_MailInfo.szPassword);
		}
		EnableAnonymityWin(!m_bAnoymity);

		SetDlgItemText(IDC_IPADDRESS_MAILIP, m_MailInfo.szAddress);
		SetDlgItemInt(IDC_EDIT_MAILPORT, m_MailInfo.nPort);
		SetDlgItemText(IDC_EDIT_MAILSEDADDR, m_MailInfo.szSendAddress);
        if (1 <= m_MailInfo.nRetReciversNum)
        {
            SetDlgItemText(IDC_EDIT_MAILDESADDR, m_MailInfo.szReceivers[0]);
        }
        if (2 <= m_MailInfo.nRetReciversNum)
        {
            SetDlgItemText(IDC_EDIT_MAILCCADDR, m_MailInfo.szReceivers[1]);
        }
        if (3 <= m_MailInfo.nRetReciversNum)
        {
            SetDlgItemText(IDC_EDIT_MAILBCCADDR, m_MailInfo.szReceivers[2]);
        }
		SetDlgItemText(IDC_EDIT_MAILSUBJECT, m_MailInfo.szTitle);
		SetDlgItemInt(IDC_EDIT_SENDINTERVAL, m_MailInfo.nSendInterv);
		m_bMailEn = m_MailInfo.bEnable;
		m_bMailSSLEn = m_MailInfo.bSslEnable;
		m_nEthernetNum = nNetIOCount;
		SetFrameEthernetInfo();
		if (m_bDBEthernet && m_NetIOInfo.stEtherNet[0].bMode)
		{
			m_ctlNetMode.SetCurSel(m_NetIOInfo.stEtherNet[0].bMode - 1);
			OnSelchangeComboNetmode();
		}
		else
		{
			if (m_ctlEthernet.GetCount() > 0)
			{
				m_ctlEthernet.SetCurSel(0);
				OnSelchangeComboEthernet();
			}
		}
		
		if (m_ctlRemoteHost.GetCount() > 0)
		{
			m_ctlRemoteHost.SetCurSel(0);
			OnSelchangeComboRemotehost();
		}
	}
}

// special initialization, get info first
void CConfigNetwork::InitDlgInfo(CFG_MULTICASTS_INFO_OUT* pInfo, DWORD dwChnCount)
{
	if (!pInfo || !dwChnCount)
	{
		return;
	}

// 	if (!m_pstuMulticastInfo)
// 	{
// 		return;
// 	}
	m_dwChannel = dwChnCount;
	m_pstuMulticastInfo = new CFG_MULTICASTS_INFO_OUT;
	if (!m_pstuMulticastInfo)
	{
		return;
	}

	m_b3Dev = TRUE;
	m_cmbStreamType.InsertString(-1, ConvertString("MainStream"));
	m_cmbStreamType.InsertString(-1, ConvertString("SubStream1"));
	m_cmbStreamType.InsertString(-1, ConvertString("SubStream2"));
	m_cmbStreamType.InsertString(-1, ConvertString("SubStream3"));
	m_cmbStreamType.EnableWindow(FALSE);

	memcpy(m_pstuMulticastInfo, pInfo, sizeof(*pInfo));

	m_lsTS.clear();
	m_lsRTP.clear();
	m_lsVideoII.clear();

	int i = 0;
	int nCount = m_pstuMulticastInfo->stuTSMulticast.nCount;
	for (i = 0; i < nCount; i++)
	{
		m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[i].nStructSize = sizeof(CFG_MULTICAST_INFO);
		m_lsTS.push_back(&m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[i]);
	}
	
	nCount = m_pstuMulticastInfo->stuRTPMulticast.nCount;
	for (i = 0; i < nCount; i++)
	{
		m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[i].nStructSize = sizeof(CFG_MULTICAST_INFO);
		m_lsRTP.push_back(&m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[i]);
	}

	nCount = m_pstuMulticastInfo->stuDHIIMulticast.nCount;
	for (i = 0; i < nCount; i++)
	{
		m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[i].nStructSize = sizeof(CFG_MULTICAST_INFO);
		m_lsVideoII.push_back(&m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[i]);
	}

	m_cmbCastType.ResetContent();
	m_cmbCastType.InsertString(-1, ConvertString(_T("TS")));
	m_cmbCastType.InsertString(-1, ConvertString(_T("RTP")));
	m_cmbCastType.InsertString(-1, ConvertString(_T("DHII")));
	m_cmbCastType.SetCurSel(-1);
	m_cmbCastType.EnableWindow(FALSE);

	char szChn[16] = {0};
	m_cmbChannel.ResetContent();
	for (i = 0; i < dwChnCount; i++)
	{
		_sntprintf(szChn, 16, _T("%s%d"), ConvertString("Channel:"), i + 1);
		m_cmbChannel.InsertString(-1, szChn);
		memset(szChn, 0, 16);
	}
	m_cmbChannel.SetCurSel(-1);
	m_cmbChannel.EnableWindow(FALSE);

	m_cmbCount.ResetContent();
	m_cmbCount.EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_INC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DEC)->EnableWindow(FALSE);
	m_ctrlLocalIP.EnableWindow(FALSE);
}

//Ethernet port switch 
void CConfigNetwork::OnSelchangeComboEthernet() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlEthernet.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = m_ctlEthernet.GetItemData(nIndex);
		
		//First save Ethernet port information 
		SaveNetWork(m_nCurEthernet);
		
		//Display Ethernet port corresponding information 
		SetDlgItemText(IDC_IPADDRESS_NETIP, m_NetIOInfo.stEtherNet[nNum].sDevIPAddr);
		SetDlgItemText(IDC_IPADDRESS_NETIPMASK, m_NetIOInfo.stEtherNet[nNum].sDevIPMask);
		SetDlgItemText(IDC_IPADDRESS_NETGATEWAY, m_NetIOInfo.stEtherNet[nNum].sGatewayIP);
		m_ctlNetInterface.SetCurSel(m_NetIOInfo.stEtherNet[nNum].dwNetInterface-1);
		SetDlgItemText(IDC_EDIT_NETMAC, m_NetIOInfo.stEtherNet[nNum].byMACAddr);
		m_bVideoCP = (m_NetIOInfo.stEtherNet[nNum].bValid & 0x2) != 0 ? TRUE : FALSE;
		m_bValid = (m_NetIOInfo.stEtherNet[nNum].bValid & 0x1) != 0 ? TRUE : FALSE;
		m_bTransmit = m_NetIOInfo.stEtherNet[nNum].bTranMedia == 0 ? TRUE : FALSE;
		m_bDefault = m_NetIOInfo.stEtherNet[nNum].bDefaultEth == 0 ? FALSE : TRUE;
		UpdateData(FALSE);
		
		m_nCurEthernet = nNum;
	}
}

//Remote host switch 
void CConfigNetwork::OnSelchangeComboRemotehost() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlRemoteHost.GetCurSel();
	if(CB_ERR != nIndex && CB_ERR != m_ctlEthernet.GetCurSel())
	{
		//First save remote host information 
		SaveRemoteHost(m_nCurRemoteHost);
		CleanRemoteDeviceInfo();

		if (m_b3Dev && nIndex == 3)
		{
			// show special multicast
			m_cmbCastType.EnableWindow(TRUE);
			m_cmbCastType.SetCurSel(0);
			OnSelchangeComboCasttype();

			// count and channel
			
			m_nCurRemoteHost = nIndex;
		} 
		else
		{
			m_ctlChkRemote.EnableWindow(FALSE);
			m_cmbCastType.EnableWindow(FALSE);
			m_cmbCount.EnableWindow(FALSE);
			m_cmbChannel.EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_INC)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_DEC)->EnableWindow(FALSE);
			m_ctrlLocalIP.EnableWindow(FALSE);
			
			//Display remote host corresponding information 
			DH_REMOTE_HOST remoteHostInfo = GetRemoteHostType(nIndex);
			m_ctlChkRemote.SetCheck(remoteHostInfo.byEnable?1:0);
			SetDlgItemText(IDC_IPADDRESS_HOSTIP, remoteHostInfo.sHostIPAddr);
			SetDlgItemInt(IDC_EDIT_HOSTPORT, remoteHostInfo.wHostPort);
			SetDlgItemText(IDC_EDIT_HOSTUSERNAME, remoteHostInfo.sHostUser);
			SetDlgItemText(IDC_EDIT_HOSTUSERPSW, remoteHostInfo.sHostPassword);
			UpdateData(FALSE);
			
			m_nCurRemoteHost = nIndex;
		}
	}
}

//Save Ethernet port information 
void CConfigNetwork::SaveNetWork(int nNum)
{
	if(-1 < nNum && DH_MAX_ETHERNET_NUM_EX > nNum)
	{
		GetDlgItemText(IDC_IPADDRESS_NETIP,m_NetIOInfo.stEtherNet[nNum].sDevIPAddr,DH_MAX_IPADDR_LEN);
		GetDlgItemText(IDC_IPADDRESS_NETIPMASK,m_NetIOInfo.stEtherNet[nNum].sDevIPMask,DH_MAX_IPADDR_LEN);
		GetDlgItemText(IDC_IPADDRESS_NETGATEWAY,m_NetIOInfo.stEtherNet[nNum].sGatewayIP,DH_MAX_IPADDR_LEN);
		m_NetIOInfo.stEtherNet[nNum].dwNetInterface = m_ctlNetInterface.GetCurSel() + 1;
		GetDlgItemText(IDC_EDIT_NETMAC,m_NetIOInfo.stEtherNet[nNum].byMACAddr,DH_MACADDR_LEN);
		UpdateData(TRUE);
		if (m_bVideoCP)
		{
			m_NetIOInfo.stEtherNet[nNum].bValid |= 0x02;
		}
		else
		{
			m_NetIOInfo.stEtherNet[nNum].bValid &= 0xFD;
		}
		if (m_bValid)
		{
			m_NetIOInfo.stEtherNet[nNum].bValid |= 0x01;
		}
		else
		{
			m_NetIOInfo.stEtherNet[nNum].bValid &= 0xFE;
		}
		m_NetIOInfo.stEtherNet[nNum].bTranMedia = m_bTransmit ? 0 : 1;
		m_NetIOInfo.stEtherNet[nNum].bDefaultEth = m_bDefault ? 1 : 0; 
		if (m_bDBEthernet)
		{
			if (DH_MAX_ETHERNET_NUM_EX <= m_nEthernetNum || 0 == m_NetIOInfo.stEtherNet[0].bMode)
			{
				return;
			}
			// 多网卡最后一个网卡信息bond0也需要修改，保证eth0，eth1...bond0网络模式一致
			int i = 0;
			for (i = 0; i <= m_nEthernetNum; i++)
			{
                m_NetIOInfo.stEtherNet[i].bMode = m_ctlNetMode.GetCurSel() + 1;
			}
			// 设置默认网卡
			int nCurIndex = m_ctlDefaultCard.GetCurSel();
			if (m_nEthernetNum>= nCurIndex && 0 <= nCurIndex)
			{
				// 多网卡最后一个网卡bond0信息是否默认字段也要修改
				for (i = 0; i <= m_nEthernetNum; i++)
				{
					if (i == nCurIndex)
					{
						m_NetIOInfo.stEtherNet[i].bDefaultEth = 1;
					}
					else
					{
						m_NetIOInfo.stEtherNet[i].bDefaultEth = 0;
					}
				}
			}
		}
	}
}

//Save remote host information 
void CConfigNetwork::SaveRemoteHost(int nNum)
{
	if(-1 < nNum)
	{
		switch(nNum)
		{
		case 0:	/* Alarm server */
			GetDlgItemText(IDC_IPADDRESS_HOSTIP,m_NetIOInfo.struAlarmHost.sHostIPAddr,DH_MAX_IPADDR_LEN);
			m_NetIOInfo.struAlarmHost.wHostPort = GetDlgItemInt(IDC_EDIT_HOSTPORT);
			break;
		case 1:/* Log server */
			GetDlgItemText(IDC_IPADDRESS_HOSTIP,m_NetIOInfo.struLogHost.sHostIPAddr,DH_MAX_IPADDR_LEN);
			m_NetIOInfo.struLogHost.wHostPort = GetDlgItemInt(IDC_EDIT_HOSTPORT);
			break;
		case 2:/* SMTP server */
			GetDlgItemText(IDC_IPADDRESS_HOSTIP,m_NetIOInfo.struSmtpHost.sHostIPAddr,DH_MAX_IPADDR_LEN);
			m_NetIOInfo.struSmtpHost.wHostPort = GetDlgItemInt(IDC_EDIT_HOSTPORT);
			break;
		case 3:/* Multiplecast group */
			GetDlgItemText(IDC_IPADDRESS_HOSTIP,m_NetIOInfo.struMultiCast.sHostIPAddr,DH_MAX_IPADDR_LEN);
			m_NetIOInfo.struMultiCast.wHostPort = GetDlgItemInt(IDC_EDIT_HOSTPORT);
			m_NetIOInfo.struMultiCast.byEnable = m_ctlChkRemote.GetCheck();
			break;
		case 4:/* NFS server */
			GetDlgItemText(IDC_IPADDRESS_HOSTIP,m_NetIOInfo.struNfs.sHostIPAddr,DH_MAX_IPADDR_LEN);
			m_NetIOInfo.struNfs.wHostPort = GetDlgItemInt(IDC_EDIT_HOSTPORT);
			m_NetIOInfo.struNfs.byEnable = m_ctlChkRemote.GetCheck();
			break;
		case 5:/* PPPoE server*/
			GetDlgItemText(IDC_EDIT_HOSTUSERNAME, m_NetIOInfo.struPppoe.sHostUser,DH_MAX_HOST_NAMELEN);
			GetDlgItemText(IDC_EDIT_HOSTUSERPSW, m_NetIOInfo.struPppoe.sHostPassword,DH_MAX_HOST_PSWLEN);
			m_NetIOInfo.struPppoe.byEnable = m_ctlChkRemote.GetCheck();
			GetDlgItemText(IDC_EDIT_HOSTRESERVED, m_NetIOInfo.sPppoeIP,DH_MAX_IPADDR_LEN);
			break;
		case 6:/* DDNS server */
			GetDlgItemText(IDC_IPADDRESS_HOSTIP,m_NetIOInfo.struDdns.sHostIPAddr,DH_MAX_IPADDR_LEN);
			m_NetIOInfo.struDdns.wHostPort = GetDlgItemInt(IDC_EDIT_HOSTPORT);
			m_NetIOInfo.struDdns.byEnable = m_ctlChkRemote.GetCheck();
			GetDlgItemText(IDC_EDIT_HOSTRESERVED, m_NetIOInfo.sDdnsHostName,DH_MAX_HOST_NAMELEN);
			break;
		case 7:/* DNS server*/
			GetDlgItemText(IDC_IPADDRESS_HOSTIP,m_NetIOInfo.struDns.sHostIPAddr,DH_MAX_IPADDR_LEN);
			break;
		default:
			break;
		}
	}
}

//Get current selected remote host type
DH_REMOTE_HOST CConfigNetwork::GetRemoteHostType(int nType)
{
	DH_REMOTE_HOST remoteHostInfo = {0};
	CString str;
	switch(nType)
	{
	case 0:	/* Alarm server */
		remoteHostInfo = m_NetIOInfo.struAlarmHost;
		break;
	case 1:/* Log server*/
		remoteHostInfo = m_NetIOInfo.struLogHost;
		break;
	case 2:/* SMTP server*/
		remoteHostInfo = m_NetIOInfo.struSmtpHost;
		break;
	case 3:/* Multiplecast group */
		remoteHostInfo = m_NetIOInfo.struMultiCast;
		break;
	case 4:/* NFS server */
		remoteHostInfo = m_NetIOInfo.struNfs;
		break;
	case 5:/* PPPoE server */
		remoteHostInfo = m_NetIOInfo.struPppoe;
		str = NAME_NETCFG_PPPOE_IP;
		str = str + ":";
		SetDlgItemText(IDC_HOSTRESERVED, str);
		SetDlgItemText(IDC_EDIT_HOSTRESERVED, m_NetIOInfo.sPppoeIP);
		break;
	case 6:/* DDNS server*/
		remoteHostInfo = m_NetIOInfo.struDdns;
		str = NAME_NETCFG_DDNS_HOSTNAME;
		str = str + ":";
		SetDlgItemText(IDC_HOSTRESERVED, str);
		SetDlgItemText(IDC_EDIT_HOSTRESERVED, m_NetIOInfo.sDdnsHostName);
		break;
	case 7:/* DNS server*/
		remoteHostInfo = m_NetIOInfo.struDns;
		break;
	default:
		break;
	}
	m_ctlChkRemote.EnableWindow(4 == nType || 5 == nType);// || 6 == nType
	GetDlgItem(IDC_IPADDRESS_HOSTIP)->EnableWindow(5 != nType && 6 != nType);
	GetDlgItem(IDC_EDIT_HOSTPORT)->EnableWindow(5 != nType && 7 != nType && 6!= nType);
	GetDlgItem(IDC_EDIT_HOSTUSERNAME)->EnableWindow(4 == nType || 5 == nType);
	GetDlgItem(IDC_EDIT_HOSTUSERPSW)->EnableWindow(4 == nType || 5 == nType);
	GetDlgItem(IDC_HOSTRESERVED)->ShowWindow((5 == nType )?SW_SHOW:SW_HIDE);//|| 6 == nType
	GetDlgItem(IDC_EDIT_HOSTRESERVED)->ShowWindow((5 == nType)?SW_SHOW:SW_HIDE);// || 6 == nType
	return remoteHostInfo;
}

//Clear
void CConfigNetwork::CleanAll()
{
	m_ctlNetInterface.SetCurSel(-1);
	m_ctlRemoteHost.SetCurSel(-1);
	m_ctlEthernet.ResetContent();

    m_nMaxTcp = 0;
	
	SetDlgItemText(IDC_EDIT_DEVNAME, "");
	SetDlgItemText(IDC_EDIT_TCPPORT, "");
	SetDlgItemText(IDC_EDIT_UDPPORT, "");
	SetDlgItemText(IDC_EDIT_HTTPPORT, "");
	SetDlgItemText(IDC_EDIT_HTTPSPORT, "");
	SetDlgItemText(IDC_EDIT_SSLPORT, "");
	
	SetDlgItemText(IDC_EDIT_MAILUSERNAME, "");
	SetDlgItemText(IDC_EDIT_MAILUSERPSW, "");
	SetDlgItemText(IDC_IPADDRESS_MAILIP,"");
	SetDlgItemText(IDC_EDIT_MAILPORT, "");
	SetDlgItemText(IDC_EDIT_MAILSEDADDR, "");
	SetDlgItemText(IDC_EDIT_MAILDESADDR, "");
	SetDlgItemText(IDC_EDIT_MAILCCADDR, "");
	SetDlgItemText(IDC_EDIT_MAILBCCADDR, "");
	SetDlgItemText(IDC_EDIT_MAILSUBJECT, "");
	SetDlgItemInt(IDC_EDIT_SENDINTERVAL, 0);
	m_bMailEn = FALSE;
	m_bMailSSLEn = FALSE;

	SetDlgItemText(IDC_IPADDRESS_NETIP, "");
	SetDlgItemText(IDC_IPADDRESS_NETIPMASK, "");
	SetDlgItemText(IDC_IPADDRESS_NETGATEWAY, "");
	SetDlgItemText(IDC_EDIT_NETMAC, "");

	m_ctlChkRemote.SetCheck(0);
	SetDlgItemText(IDC_IPADDRESS_HOSTIP, "");
	SetDlgItemText(IDC_EDIT_HOSTPORT, "");
	SetDlgItemText(IDC_EDIT_HOSTUSERNAME, "");
	SetDlgItemText(IDC_EDIT_HOSTUSERPSW, "");
	GetDlgItem(IDC_HOSTRESERVED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_HOSTRESERVED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK_DEFAULT)->ShowWindow(SW_SHOW);
	m_nCurEthernet = -1;
	m_nCurRemoteHost = -1;

	
	m_cmbCastType.SetCurSel(-1);
	m_cmbCount.SetCurSel(-1);
	m_cmbChannel.SetCurSel(-1);
	m_ctrlLocalIP.ClearAddress();
	
	m_ctlChkRemote.EnableWindow(FALSE);
	m_cmbCastType.EnableWindow(FALSE);
	m_cmbCount.EnableWindow(FALSE);
	m_cmbChannel.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_INC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DEC)->EnableWindow(FALSE);
	m_ctrlLocalIP.EnableWindow(FALSE);
    
	m_bDBEthernet = FALSE;
	m_nEthernetNum = -1;
	m_b3Dev = FALSE;
	if (m_pstuMulticastInfo)
	{
		delete m_pstuMulticastInfo;
		m_pstuMulticastInfo = NULL;
	}
	
	while (m_lsTS.size())
	{
		m_lsTS.pop_front();
	}
	
	while (m_lsRTP.size())
	{		
		m_lsRTP.pop_front();
	}
	
	while (m_lsVideoII.size())
	{		
		m_lsVideoII.pop_front();
	}

	UpdateData(FALSE);
}

void CConfigNetwork::CleanRemoteDeviceInfo()
{
	m_ctlChkRemote.SetCheck(0);
	SetDlgItemText(IDC_IPADDRESS_HOSTIP, "");
	SetDlgItemText(IDC_EDIT_HOSTPORT, "");
	SetDlgItemText(IDC_EDIT_HOSTUSERNAME, "");
	SetDlgItemText(IDC_EDIT_HOSTUSERPSW, "");
	GetDlgItem(IDC_HOSTRESERVED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_HOSTRESERVED)->ShowWindow(SW_HIDE);

	m_cmbCastType.SetCurSel(-1);
	m_cmbCount.SetCurSel(-1);
	m_cmbChannel.SetCurSel(-1);
	m_ctrlLocalIP.ClearAddress();
	
	m_ctlChkRemote.EnableWindow(FALSE);
	m_cmbCastType.EnableWindow(FALSE);
	m_cmbCount.EnableWindow(FALSE);
	m_cmbChannel.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_INC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DEC)->EnableWindow(FALSE);
	m_ctrlLocalIP.EnableWindow(FALSE);

	UpdateData(FALSE);
}

void CConfigNetwork::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CConfigNetwork::OnBnClickedCheckAnonymity()
{
	if(((CButton*)GetDlgItem(IDC_CHECK_ANONYMITY))->GetCheck())
	{
		EnableAnonymityWin(false);
	}
	else
	{
		EnableAnonymityWin(true);
	}
};


void CConfigNetwork::EnableAnonymityWin(bool bCheck)
{
    return; //鱼眼设备匿名也需要填写用户名密码
	GetDlgItem(IDC_EDIT_MAILUSERNAME)->EnableWindow(bCheck);
	GetDlgItem(IDC_EDIT_MAILUSERPSW)->EnableWindow(bCheck);
	GetDlgItem(IDC_EDIT_MAILSEDADDR)->EnableWindow(bCheck);
	
	if (!bCheck)// 匿名
	{
		SetDlgItemText(IDC_EDIT_MAILUSERNAME, "anonymity");
		SetDlgItemText(IDC_EDIT_MAILUSERPSW, "none");
		SetDlgItemText(IDC_EDIT_MAILSEDADDR, "");
	}
}

void CConfigNetwork::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pstuMulticastInfo)
	{
		delete m_pstuMulticastInfo;
		m_pstuMulticastInfo = NULL;
	}

	while (m_lsTS.size())
	{
		m_lsTS.pop_front();
	}

	while (m_lsRTP.size())
	{		
		m_lsRTP.pop_front();
	}

	while (m_lsVideoII.size())
	{		
		m_lsVideoII.pop_front();
	}
}

void CConfigNetwork::OnCheckRemotehost() 
{
	// TODO: Add your control notification handler code here
	if (m_ctlRemoteHost.GetCurSel() == 3)
	{
		if (m_cmbCount.GetCurSel() == -1)
		{
			return;
		}

		int nSeq = 0;
		CFG_MULTICAST_INFO* p = NULL;
		
		nSeq = m_cmbCount.GetCurSel();
		p = (CFG_MULTICAST_INFO*)m_cmbCount.GetItemData(nSeq);
		if (p)
		{
			p->bEnable = m_ctlChkRemote.GetCheck();
		}

// 		switch(m_cmbCastType.GetCurSel())
// 		{
// 			//TS
// 		case 0:
// 			m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[m_cmbCount.GetCurSel()].bEnable = m_ctlChkRemote.GetCheck();
// 			break;
// 			//RTP
// 		case 1:
// 			m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[m_cmbCount.GetCurSel()].bEnable = m_ctlChkRemote.GetCheck();
// 			break;
// 			//DHII
// 		case 2:
// 			m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[m_cmbCount.GetCurSel()].bEnable = m_ctlChkRemote.GetCheck();
// 			break;
// 		default:
// 			break;
// 		}
	}
}

void CConfigNetwork::OnSelchangeComboCasttype() 
{
	// TODO: Add your control notification handler code here
	
	m_ctlChkRemote.EnableWindow(TRUE);
	m_ctlChkRemote.SetCheck(FALSE);
	m_cmbStreamType.EnableWindow(TRUE);
	m_cmbCount.EnableWindow(TRUE);
	m_cmbChannel.EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_INC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DEC)->EnableWindow(TRUE);
	m_ctlHostIP.EnableWindow(TRUE);
	m_ctrlLocalIP.EnableWindow(FALSE);
	SetDlgItemText(IDC_IPADDRESS_HOSTIP, "");
	SetDlgItemText(IDC_EDIT_HOSTPORT, "");
	
	// show first one
	m_cmbCount.ResetContent();

	std::list<CFG_MULTICAST_INFO*>::iterator it;
	CFG_MULTICAST_INFO* p = NULL;

	int nCastType = m_cmbCastType.GetCurSel();
	if (nCastType == 0)
	{
		//TS
		char szChn[16] = {0};

		it = m_lsTS.begin();
		for (int i = 0; i < m_lsTS.size(); i++)
		{
			p = *it;
			memset(szChn, 0, 16);
			_sntprintf(szChn, 16, _T("%d"), i + 1);
			int nSeq = m_cmbCount.InsertString(-1, szChn);
			m_cmbCount.SetItemData(nSeq, (DWORD)p);
			
			it++;
		}
		
		if (m_lsTS.size())
		{
			m_cmbCount.SetCurSel(0);
			
			ShowMulticastInfo();
		} 
		else
		{
			m_cmbCount.ResetContent();
			m_cmbCount.SetCurSel(-1);
		}
	} 
	else if (nCastType == 1)
	{
		//RTP
		char szChn[16] = {0};
		
		it = m_lsRTP.begin();
		for (int i = 0; i < m_lsRTP.size(); i++)
		{
			p = *it;
			memset(szChn, 0, 16);
			_sntprintf(szChn, 16, _T("%d"), i + 1);
			int nSeq = m_cmbCount.InsertString(-1, szChn);
			m_cmbCount.SetItemData(nSeq, (DWORD)p);
			
			it++;
		}

		if (m_lsRTP.size())
		{
			m_cmbCount.SetCurSel(0);
			
			ShowMulticastInfo();
		} 
		else
		{
			m_cmbCount.ResetContent();
			m_cmbCount.SetCurSel(-1);
		}
	}
	else if (nCastType == 2)
	{
		//DHII
		char szChn[16] = {0};
		
		it = m_lsVideoII.begin();
		for (int i = 0; i < m_lsVideoII.size(); i++)
		{
			p = *it;
			memset(szChn, 0, 16);
			_sntprintf(szChn, 16, _T("%d"), i + 1);
			int nSeq = m_cmbCount.InsertString(-1, szChn);
			m_cmbCount.SetItemData(nSeq, (DWORD)p);
			
			it++;
		}
		
		if (m_lsVideoII.size())
		{
			m_cmbCount.SetCurSel(0);
			
			ShowMulticastInfo();
		} 
		else
		{
			m_cmbCount.ResetContent();
			m_cmbCount.SetCurSel(-1);
		}
	}
}

void CConfigNetwork::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	if (m_ctlRemoteHost.GetCurSel() == 3)
	{
		if (m_cmbCount.GetCurSel() == -1)
		{
			return;
		}
		
		int nSeq = 0;
		CFG_MULTICAST_INFO* p = NULL;
		
		nSeq = m_cmbCount.GetCurSel();
		p = (CFG_MULTICAST_INFO*)m_cmbCount.GetItemData(nSeq);
		if (p)
		{
			p->bEnable = m_ctlChkRemote.GetCheck();
		}
	}
	
}

void CConfigNetwork::OnSelchangeComboCount() 
{
	// TODO: Add your control notification handler code here
	int nSeq = m_cmbCount.GetCurSel();
	if (nSeq == -1 && nSeq >= MAX_CHAN_NUM)
	{
		return;
	}

	ShowMulticastInfo();
}

void CConfigNetwork::OnButtonInc() 
{
	// TODO: Add your control notification handler code here
	CConfigNetworkMulticastAdd dlgAdd;
	dlgAdd.InitDlg(m_dwChannel);

	if (dlgAdd.DoModal() == IDOK)
	{
		if (dlgAdd.m_pInfo)
		{
			if (dlgAdd.m_nCastType == 0)
			{
				if (m_lsTS.size() >= MAX_CHAN_NUM)
				{
					return;
				}
// 				memcpy(&m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[m_lsTS.size()],
// 					   dlgAdd.m_pInfo,
// 					   sizeof(CFG_MULTICAST_INFO));
// 				m_lsTS.push_back(&m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[m_lsTS.size()]);

				CString str;
				str.Format(_T("%d"), m_cmbCount.GetCount() + 1);
				int nSeq = m_cmbCount.InsertString(-1, str);
				m_cmbCount.SetItemData(nSeq, (DWORD)dlgAdd.m_pInfo);
 				m_lsTS.push_back(dlgAdd.m_pInfo);
			}
			else if (dlgAdd.m_nCastType == 1)
			{
				if (m_lsRTP.size() >= MAX_CHAN_NUM)
				{
					return;
				}
// 				memcpy(&m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[m_lsRTP.size()],
// 						dlgAdd.m_pInfo,
// 						sizeof(CFG_MULTICAST_INFO));
// 				m_lsRTP.push_back(&m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[m_lsRTP.size()]);
				
				CString str;
				str.Format(_T("%d"), m_cmbCount.GetCount() + 1);
				int nSeq = m_cmbCount.InsertString(-1, str);
				m_cmbCount.SetItemData(nSeq, (DWORD)dlgAdd.m_pInfo);
 				m_lsRTP.push_back(dlgAdd.m_pInfo);
			}
			else if (dlgAdd.m_nCastType == 2)
			{
				if (m_lsVideoII.size() >= MAX_CHAN_NUM)
				{
					return;
				}
// 				memcpy(&m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[m_lsVideoII.size()],
// 						dlgAdd.m_pInfo,
// 					   sizeof(CFG_MULTICAST_INFO));
// 				m_lsVideoII.push_back(&m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[m_lsVideoII.size()]);
				
				CString str;
				str.Format(_T("%d"), m_cmbCount.GetCount() + 1);
				int nSeq = m_cmbCount.InsertString(-1, str);
				m_cmbCount.SetItemData(nSeq, (DWORD)dlgAdd.m_pInfo);
 				m_lsVideoII.push_back(dlgAdd.m_pInfo);
			}
			OnSelchangeComboCasttype();
		}
	}
}

void CConfigNetwork::OnButtonDec() 
{
	// TODO: Add your control notification handler code here
	int nCastType = m_cmbCastType.GetCurSel();
	int nSeq = m_cmbCount.GetCurSel();
	
	if (nCastType == 0)
	{
		//TS
		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsTS.begin();
		for (int i = 0; i < m_lsTS.size(); i++)
		{
			if (*it == (CFG_MULTICAST_INFO*)m_cmbCount.GetItemData(nSeq))//&m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[nSeq])
			{
				break;
			}
			else
			{
				it++;
			}
		}
		
		if (it == m_lsTS.end())
		{
			return;
		}

		m_lsTS.remove(*it);
		OnSelchangeComboCasttype();
	}
	else if (nCastType == 1)
	{
		//RTP
		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsRTP.begin();
		for (int i = 0; i < m_lsRTP.size(); i++)
		{
			if (*it == &m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[nSeq])
			{
				break;
			}
			else
			{
				it++;
			}
		}
		
		if (it == m_lsRTP.end())
		{
			return;
		}

		m_lsRTP.remove(*it);
		OnSelchangeComboCasttype();
	}
	else if (nCastType == 2)
	{
		//DHII
		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsVideoII.begin();
		for (int i = 0; i < m_lsVideoII.size(); i++)
		{
			if (*it == &m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[nSeq])
			{
				break;
			}
			else
			{
				it++;
			}
		}
		
		if (it == m_lsVideoII.end())
		{
			return;
		}

		m_lsVideoII.remove(*it);
		OnSelchangeComboCasttype();
	}
	
}

void CConfigNetwork::ShowMulticastInfo()
{
	int nCastType = m_cmbCastType.GetCurSel();
	int nSeq = m_cmbCount.GetCurSel();

	if (nCastType == 0)
	{
		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsTS.begin();
		for (int i = 0; i < m_lsTS.size(); i++)
		{
			if (*it == (CFG_MULTICAST_INFO*)m_cmbCount.GetItemData(nSeq))//&m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[nSeq])
			{
				break;
			}
			else
			{
				it++;
			}
		}

		if (it == m_lsTS.end())
		{
			return;
		}

		CFG_MULTICAST_INFO& stuInfo = **it;

		m_ctlChkRemote.SetCheck(stuInfo.bEnable);
		SetDlgItemText(IDC_IPADDRESS_HOSTIP, stuInfo.szMulticastAddr);
		SetDlgItemText(IDC_IPADDRESS_LOCALIP, stuInfo.szLocalAddr);

		int nPortNum = stuInfo.nPort;
		SetDlgItemInt(IDC_EDIT_HOSTPORT, nPortNum, FALSE);
		stuInfo.nPort = nPortNum;

		m_cmbChannel.SetCurSel(stuInfo.nChannelID);
		m_cmbStreamType.SetCurSel(stuInfo.nStreamType);
		if (stuInfo.abStreamType)
		{
			m_cmbStreamType.EnableWindow(TRUE);
		}
		else
		{
			m_cmbStreamType.EnableWindow(FALSE);
		}
	} 
	else if (nCastType == 1)
	{
		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsRTP.begin();
		for (int i = 0; i < m_lsRTP.size(); i++)
		{
			if (*it == (CFG_MULTICAST_INFO*)m_cmbCount.GetItemData(nSeq))//&m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[nSeq])
			{
				break;
			}
			else
			{
				it++;
			}
		}
		if (it == m_lsRTP.end())
		{
			return;
		}

		CFG_MULTICAST_INFO& stuInfo = **it;

		m_ctlChkRemote.SetCheck(m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[nSeq].bEnable);
		SetDlgItemText(IDC_IPADDRESS_HOSTIP, stuInfo.szMulticastAddr);
		SetDlgItemText(IDC_IPADDRESS_LOCALIP, stuInfo.szLocalAddr);

		int nPortNum = stuInfo.nPort;
		SetDlgItemInt(IDC_EDIT_HOSTPORT, nPortNum, FALSE);
		stuInfo.nPort = nPortNum;

		m_cmbChannel.SetCurSel(stuInfo.nChannelID);
		m_cmbStreamType.SetCurSel(stuInfo.nStreamType);
		if (stuInfo.abStreamType)
		{
			m_cmbStreamType.EnableWindow(TRUE);
		}
		else
		{
			m_cmbStreamType.EnableWindow(FALSE);
		}
	}
	else if (nCastType == 2)
	{
		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsVideoII.begin();
		for (int i = 0; i < m_lsVideoII.size(); i++)
		{
			if (*it == (CFG_MULTICAST_INFO*)m_cmbCount.GetItemData(nSeq))//&m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[nSeq])
			{
				break;
			}
			else
			{
				it++;
			}
		}
		if (it == m_lsVideoII.end())
		{
			return;
		}

		CFG_MULTICAST_INFO& stuInfo = **it;

		m_ctlChkRemote.SetCheck(m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[nSeq].bEnable);
		SetDlgItemText(IDC_IPADDRESS_HOSTIP, stuInfo.szMulticastAddr);
		SetDlgItemText(IDC_IPADDRESS_LOCALIP, stuInfo.szLocalAddr);
		
		int nPortNum = stuInfo.nPort;
		SetDlgItemInt(IDC_EDIT_HOSTPORT, nPortNum, FALSE);
		stuInfo.nPort = nPortNum;

		m_cmbChannel.SetCurSel(stuInfo.nChannelID);
		m_cmbStreamType.SetCurSel(stuInfo.nStreamType);
		if (stuInfo.abStreamType)
		{
			m_cmbStreamType.EnableWindow(TRUE);
		}
		else
		{
			m_cmbStreamType.EnableWindow(FALSE);
		}
	}
}

void CConfigNetwork::OnFieldchangedIpaddressHostip(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	if (m_ctlRemoteHost.GetCurSel() == 3)
	{
		if (m_cmbCount.GetCurSel() == -1)
		{
			return;
		}
		
		int nSeq = 0;
		CFG_MULTICAST_INFO* p = NULL;
		
		nSeq = m_cmbCount.GetCurSel();
		p = (CFG_MULTICAST_INFO*)m_cmbCount.GetItemData(nSeq);
		if (p)
		{
			CString str;
			m_ctlHostIP.GetWindowText(str);

			memset(p->szMulticastAddr, 0, MAX_ADDRESS_LEN);
			strncpy(p->szMulticastAddr, str.GetBuffer(0), str.GetLength());
		}
	}
// 	int nCastType = m_cmbCastType.GetCurSel();
// 	int nSeq = m_cmbCount.GetCurSel();
// 
// 	if (nCastType == 0)
// 	{
// 		//TS
// 		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsTS.begin();
// 		for (int i = 0; i < m_lsTS.size(); i++)
// 		{
// 			if (*it == &m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[nSeq])
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				it++;
// 			}
// 		}
// 
// 		if (it == m_lsTS.end())
// 		{
// 			return;
// 		}
// 
// 		CFG_MULTICAST_INFO* pInfo = *it;
// 		
// 		GetDlgItemText(IDC_IPADDRESS_HOSTIP, pInfo->szMulticastAddr, MAX_ADDRESS_LEN);
// 	}
// 	else if (nCastType == 1)
// 	{
// 		//RTP
// 		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsRTP.begin();
// 		for (int i = 0; i < m_lsRTP.size(); i++)
// 		{
// 			if (*it == &m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[nSeq])
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				it++;
// 			}
// 		}
// 		
// 		if (it == m_lsRTP.end())
// 		{
// 			return;
// 		}
// 		
// 		CFG_MULTICAST_INFO* pInfo = *it;
// 		
// 		GetDlgItemText(IDC_IPADDRESS_HOSTIP, pInfo->szMulticastAddr, MAX_ADDRESS_LEN);
// 	}
// 	else if (nCastType == 2)
// 	{
// 		//DHII
// 		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsVideoII.begin();
// 		for (int i = 0; i < m_lsVideoII.size(); i++)
// 		{
// 			if (*it == &m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[nSeq])
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				it++;
// 			}
// 		}
// 		
// 		if (it == m_lsVideoII.end())
// 		{
// 			return;
// 		}
// 		
// 		CFG_MULTICAST_INFO* pInfo = *it;
// 		
// 		GetDlgItemText(IDC_IPADDRESS_HOSTIP, pInfo->szMulticastAddr, MAX_ADDRESS_LEN);
// 	}

	*pResult = 0;
}

void CConfigNetwork::OnFieldchangedIpaddressLocalip(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	if (m_ctlRemoteHost.GetCurSel() == 3)
	{
		if (m_cmbCount.GetCurSel() == -1)
		{
			return;
		}
		
		int nSeq = 0;
		CFG_MULTICAST_INFO* p = NULL;
		
		nSeq = m_cmbCount.GetCurSel();
		p = (CFG_MULTICAST_INFO*)m_cmbCount.GetItemData(nSeq);
		if (p)
		{
			CString str;
			m_ctrlLocalIP.GetWindowText(str);
			
			memset(p->szMulticastAddr, 0, MAX_ADDRESS_LEN);
			strncpy(p->szMulticastAddr, str.GetBuffer(0), str.GetLength());
		}
	}
// 	int nCastType = m_cmbCastType.GetCurSel();
// 	int nSeq = m_cmbCount.GetCurSel();
// 	
// 	if (nCastType == 0)
// 	{
// 		//TS
// 		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsTS.begin();
// 		for (int i = 0; i < m_lsTS.size(); i++)
// 		{
// 			if (*it == &m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[nSeq])
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				it++;
// 			}
// 		}
// 		
// 		if (it == m_lsTS.end())
// 		{
// 			return;
// 		}
// 		
// 		CFG_MULTICAST_INFO* pInfo = *it;
// 		
// 		GetDlgItemText(IDC_IPADDRESS_LOCALIP, pInfo->szLocalAddr, MAX_ADDRESS_LEN);
// 	}
// 	else if (nCastType == 1)
// 	{
// 		//RTP
// 		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsRTP.begin();
// 		for (int i = 0; i < m_lsRTP.size(); i++)
// 		{
// 			if (*it == &m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[nSeq])
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				it++;
// 			}
// 		}
// 		
// 		if (it == m_lsRTP.end())
// 		{
// 			return;
// 		}
// 		
// 		CFG_MULTICAST_INFO* pInfo = *it;
// 		
// 		GetDlgItemText(IDC_IPADDRESS_LOCALIP, pInfo->szLocalAddr, MAX_ADDRESS_LEN);
// 	}
// 	else if (nCastType == 2)
// 	{
// 		//DHII
// 		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsVideoII.begin();
// 		for (int i = 0; i < m_lsVideoII.size(); i++)
// 		{
// 			if (*it == &m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[nSeq])
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				it++;
// 			}
// 		}
// 		
// 		if (it == m_lsVideoII.end())
// 		{
// 			return;
// 		}
// 		
// 		CFG_MULTICAST_INFO* pInfo = *it;
// 		
// 		GetDlgItemText(IDC_IPADDRESS_LOCALIP, pInfo->szLocalAddr, MAX_ADDRESS_LEN);
// 	}

	*pResult = 0;
}

void CConfigNetwork::OnChangeEditHostport() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	if (m_ctlRemoteHost.GetCurSel() == 3)
	{
		if (m_cmbCount.GetCurSel() == -1)
		{
			return;
		}
		
		int nSeq = 0;
		CFG_MULTICAST_INFO* p = NULL;
		
		nSeq = m_cmbCount.GetCurSel();
		p = (CFG_MULTICAST_INFO*)m_cmbCount.GetItemData(nSeq);
		if (p)
		{
			int nPort = GetDlgItemInt(IDC_EDIT_HOSTPORT, &nPort, FALSE);
            if (1025 <= nPort && nPort <= 65534)
            {
			    p->nPort = nPort;
            }
            else
            {
                MessageBox(ConvertString("Port range (1025-65534)!"), ConvertString("Prompt"));

                GetDlgItem(IDC_EDIT_HOSTPORT)->SetWindowText("65534");
            }
//			p->nPort = GetDlgItemInt(IDC_EDIT_PORT, NULL, FALSE);
		}
	}
// 	int nCastType = m_cmbCastType.GetCurSel();
// 	int nSeq = m_cmbCount.GetCurSel();
// 	
// 	if (nCastType == 0)
// 	{
// 		//TS
// 		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsTS.begin();
// 		for (int i = 0; i < m_lsTS.size(); i++)
// 		{
// 			if (*it == &m_pstuMulticastInfo->stuTSMulticast.stuMultiInfo[nSeq])
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				it++;
// 			}
// 		}
// 		
// 		if (it == m_lsTS.end())
// 		{
// 			return;
// 		}
// 		
// 		CFG_MULTICAST_INFO* pInfo = *it;
// 		
// 		pInfo->nPort = GetDlgItemInt(IDC_EDIT_HOSTPORT, &pInfo->nPort, FALSE);
// 	}
// 	else if (nCastType == 1)
// 	{
// 		//RTP
// 		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsRTP.begin();
// 		for (int i = 0; i < m_lsRTP.size(); i++)
// 		{
// 			if (*it == &m_pstuMulticastInfo->stuRTPMulticast.stuMultiInfo[nSeq])
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				it++;
// 			}
// 		}
// 		
// 		if (it == m_lsRTP.end())
// 		{
// 			return;
// 		}
// 		
// 		CFG_MULTICAST_INFO* pInfo = *it;
// 		
// 		pInfo->nPort = GetDlgItemInt(IDC_EDIT_HOSTPORT, &pInfo->nPort, FALSE);
// 	}
// 	else if (nCastType == 2)
// 	{
// 		//DHII
// 		std::list<CFG_MULTICAST_INFO*>::iterator it = m_lsVideoII.begin();
// 		for (int i = 0; i < m_lsVideoII.size(); i++)
// 		{
// 			if (*it == &m_pstuMulticastInfo->stuDHIIMulticast.stuMultiInfo[nSeq])
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				it++;
// 			}
// 		}
// 		
// 		if (it == m_lsVideoII.end())
// 		{
// 			return;
// 		}
// 		
// 		CFG_MULTICAST_INFO* pInfo = *it;
// 		
// 		pInfo->nPort = GetDlgItemInt(IDC_EDIT_HOSTPORT, &pInfo->nPort, FALSE);
// 	}

}

void CConfigNetwork::SetFrameEthernetInfo()
{
	int nShowFlag = (m_bDBEthernet && m_NetIOInfo.stEtherNet[0].bMode) ? SW_SHOW:SW_HIDE;
	GetDlgItem(IDC_STATIC_NETMODE)->ShowWindow(nShowFlag);
    m_ctlNetMode.ShowWindow(nShowFlag);

	GetDlgItem(IDC_STATIC_DEFAULTCARD)->ShowWindow(nShowFlag);
	m_ctlDefaultCard.ShowWindow(nShowFlag);

	// 多网卡使用m_ctlDefaultCard选择默认网卡,隐藏checkBox
	if (m_bDBEthernet)
	{
		// 设备返回的数据格式为eth0 eth1...bond0,实际网卡数量为DH_MAX_ETHERNET_NUM_EX - 1
		if (0 >= m_nEthernetNum 
			|| DH_MAX_ETHERNET_NUM_EX - 1 < m_nEthernetNum
			|| 0 == m_NetIOInfo.stEtherNet[0].bMode)
		{
            return;
		}
        m_ctlEthernet.ResetContent();
		CString strNet;
		int nIndex = 0;
		int i = 0;
		for (i = 0; i < m_nEthernetNum; i++)
		{
			strNet.Format(ConvertString("Ethernet network%d"), i+1);
			nIndex = m_ctlEthernet.AddString(strNet);
			m_ctlEthernet.SetItemData(nIndex,i);
		}
		m_ctlDefaultCard.ResetContent();
		nIndex = 0;
		for (i = 0; i < m_nEthernetNum; i++)
		{
			strNet.Format(ConvertString("Ethernet network%d"), i+1);
			nIndex = m_ctlDefaultCard.AddString(strNet);
			m_ctlDefaultCard.SetItemData(nIndex,i);
		}
        
		GetDlgItem(IDC_CHECK_DEFAULT)->ShowWindow(SW_HIDE);
	}
}

void CConfigNetwork::OnSelchangeComboNetmode() 
{
	// TODO: Add your control notification handler code here
	// 网络模式切换只针对双网卡设备
	if (!m_bDBEthernet)
	{
		return;
	}
    int nCurrentMode = m_ctlNetMode.GetCurSel() + 1;
	if (0 > nCurrentMode)
	{
		return;
	}
	m_ctlEthernet.ResetContent();
	int nShowFlag = SW_SHOW;
	CString strNet;
	int i = 0;
	int nIndex = 0;
	switch(nCurrentMode)
	{
	case En_Net_Balance:        // 负载均衡，隐藏默认网卡设置
		nShowFlag = SW_HIDE;
		strNet.Format(ConvertString("bond card"));
		nIndex = m_ctlEthernet.AddString(strNet);
		// 负载均衡模式，网卡选项只显示bond0(网卡信息数组最后元素)
		// 便于保存数据时根据m_ctlEthernet当前选中index作为数组下标
		m_ctlEthernet.SetItemData(nIndex,m_nEthernetNum); 
		break;
	case En_Net_Multiple:
		for (i = 0; i < m_nEthernetNum; i++)
		{
			strNet.Format(ConvertString("Ethernet network%d"), i+1);
			nIndex = m_ctlEthernet.AddString(strNet);
			m_ctlEthernet.SetItemData(nIndex,i);
		}
		break;
	case En_Net_Tolerance:
		strNet.Format(ConvertString("bond card"));
		nIndex = m_ctlEthernet.AddString(strNet);
		// 容错模式，网卡选项只显示bond0(网卡信息数组最后元素)
		// 便于保存数据时根据m_ctlEthernet当前选中index作为数组下标
		m_ctlEthernet.SetItemData(nIndex,m_nEthernetNum);
	default:
		break;
	}

	GetDlgItem(IDC_STATIC_DEFAULTCARD)->ShowWindow(nShowFlag);
	m_ctlDefaultCard.ShowWindow(nShowFlag);
	m_ctlDefaultCard.SetCurSel(0);
	if (DH_MAX_ETHERNET_NUM_EX <= m_nEthernetNum)
	{
		return;
	}
	for (i = 0; i< m_nEthernetNum; i++)
	{
		if (1 == m_NetIOInfo.stEtherNet[i].bDefaultEth)
		{
			m_ctlDefaultCard.SetCurSel(i);
			break;
		}
	}
    m_ctlEthernet.SetCurSel(0);
	OnSelchangeComboEthernet();
}
