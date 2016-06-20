// DlgIPC.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "DlgIPC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WAITTIME 2000

/////////////////////////////////////////////////////////////////////////////
// CDlgIPC dialog

BOOL SetCurSelByData(CComboBox& comboBox, DWORD dwData)
{
	int nCount = comboBox.GetCount();
	for(int i = 0; i < nCount; i++)
	{
		if(comboBox.GetItemData(i) == dwData)
		{
			comboBox.SetCurSel(i);
			return TRUE;
		}
	}

	return FALSE;
}

CDlgIPC::CDlgIPC(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIPC)
	m_bDial = FALSE;
	m_bEMS = FALSE;
	m_bList = FALSE;
	m_bSMS = FALSE;
	m_strRecv = _T("");
	m_strCaller = _T("");
	m_strSender = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
}


void CDlgIPC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPC)
	DDX_Control(pDX, IDC_COMBO_MODE, m_ccbMode);
	DDX_Control(pDX, IDC_COMBO_COMPRESSION, m_ccbEncode);
	DDX_Control(pDX, IDC_IPADDRESS_IP2, m_IPBlack);
	DDX_Control(pDX, IDC_COMBO_MOBILE_TYPE, m_ccbType);
	DDX_Control(pDX, IDC_LIST_WHITE, m_listWhite);
	DDX_Control(pDX, IDC_LIST_SMS, m_listSMS);
	DDX_Control(pDX, IDC_LIST_EMS, m_listEMS);
	DDX_Control(pDX, IDC_LIST_DIA, m_listDial);
	DDX_Control(pDX, IDC_LIST_BLACK, m_listBlack);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_IP);
	DDX_Check(pDX, IDC_CHECK_DIAL, m_bDial);
	DDX_Check(pDX, IDC_CHECK_EVENT_SEND, m_bEMS);
	DDX_Check(pDX, IDC_CHECK_LIST_ENABLE, m_bList);
	DDX_Check(pDX, IDC_CHECK_SMS, m_bSMS);
	DDX_Text(pDX, IDC_EDIT_RECEIVER, m_strRecv);
	DDV_MaxChars(pDX, m_strRecv, 31);
	DDX_Text(pDX, IDC_EDIT1_CALLER, m_strCaller);
	DDV_MaxChars(pDX, m_strCaller, 31);
	DDX_Text(pDX, IDC_EDIT1_SENDER, m_strSender);
	DDV_MaxChars(pDX, m_strSender, 31);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDV_MaxChars(pDX, m_strTitle, 31);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPC, CDialog)
	//{{AFX_MSG_MAP(CDlgIPC)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_EMS_ADD, OnButtonEmsAdd)
	ON_BN_CLICKED(IDC_BUTTON_EMS_DELETE, OnButtonEmsDelete)
	ON_BN_CLICKED(IDC_BUTTON_SMS_ADD, OnButtonSmsAdd)
	ON_BN_CLICKED(IDC_BUTTON_SMS_DELETE, OnButtonSmsDelete)
	ON_BN_CLICKED(IDC_BUTTON_DIA_ADD, OnButtonDiaAdd)
	ON_BN_CLICKED(IDC_BUTTON_DIA_DELETE, OnButtonDiaDelete)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_RADIO_WHITE, OnRadioWhite)
	ON_BN_CLICKED(IDC_RADIO_BLACK, OnRadioBlack)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, OnSelchangeComboMode)
	ON_CBN_CLOSEUP(IDC_COMBO_MODE, OnCloseupComboMode)
// 	ON_CBN_EDITCHANGE(IDC_COMBO_MODE, OnEditchangeComboMode)
// 	ON_CBN_EDITUPDATE(IDC_COMBO_MODE, OnEditupdateComboMode)//
	ON_BN_CLICKED(IDC_BUTTON_WL_BROW, OnButtonWhiteListBROW)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIPC message handlers

BOOL CDlgIPC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//CListBox
	m_listEMS.SetHorizontalExtent(190);
	m_listSMS.SetHorizontalExtent(190);
	m_listDial.SetHorizontalExtent(190);
	//CComboBox
	m_ccbType.SetItemData(m_ccbType.AddString("MMS"), 0);
	m_ccbType.SetItemData(m_ccbType.AddString("SMS"), 1);
	
	m_ccbEncode.SetItemData(m_ccbEncode.AddString("AMR475"), DH_TALK_AMR_AMR475);
	m_ccbEncode.SetItemData(m_ccbEncode.AddString("AMR515"), DH_TALK_AMR_AMR515);
	m_ccbEncode.SetItemData(m_ccbEncode.AddString("AMR59"), DH_TALK_AMR_AMR59);
	m_ccbEncode.SetItemData(m_ccbEncode.AddString("AMR67"), DH_TALK_AMR_AMR67);
	m_ccbEncode.SetItemData(m_ccbEncode.AddString("AMR74"), DH_TALK_AMR_AMR74);
	m_ccbEncode.SetItemData(m_ccbEncode.AddString("AMR795"), DH_TALK_AMR_AMR795);
	m_ccbEncode.SetItemData(m_ccbEncode.AddString("AMR102"), DH_TALK_AMR_AMR102);
	m_ccbEncode.SetItemData(m_ccbEncode.AddString("AMR122"), DH_TALK_AMR_AMR122);


	g_SetWndStaticText(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIPC::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CDlgIPC::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	//SetIPFilterCfg();
	SetTalkEncodeCfg();
	SetMMSCfg();
	SetSMSCfg();
	SetDiaCfg();
}

void CDlgIPC::OnButtonRead() 
{
	// TODO: Add your control notification handler code here
	//GetIPFilterCfg();
	GetTalkEncodeCfg();
	GetMMSCfg();
	GetSMSCfg();
	GetDiaCfg();
}

void CDlgIPC::GetTalkEncodeCfg()
{
	m_ccbMode.ResetContent();

	int nRetLen = 0;
	DHDEV_TALKFORMAT_LIST talkFormat = {0};
	BOOL bRet = CLIENT_QueryDevState(m_lLogin, 
									 DH_DEVSTATE_TALK_ECTYPE,	
									 (char*)&talkFormat,
									 sizeof(talkFormat),
									 &nRetLen,
									 WAITTIME);
	if(bRet == FALSE || nRetLen != sizeof(talkFormat))
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Get talk encode type failed."));
		return;
	}
	//TODO
	int nType = 0;
	int nAddFlag = 0;	
	char* szTalk[] = {"Default", "PCM", "G711a", "AMR", "G711u", "G726", "G723_53", "G723_63", "AAC", "OGG"};
	for(int i = 0; i < talkFormat.nSupportNum; i++)
	{
		nType = talkFormat.type[i].encodeType;
		if (!(nAddFlag & 0x01 << nType))
		{
			nAddFlag |= 0x01 << nType; // 防止重复AddString
			m_ccbMode.SetItemData(m_ccbMode.AddString(szTalk[nType]), nType);
		}
	}

	DWORD dwRetLen = 0;
	bRet = CLIENT_GetDevConfig(m_lLogin, 
							   DH_DEV_TALK_ENCODE_CFG,
							   0,
							   (LPVOID)&m_stuTalkEncodeCfg,
							   sizeof(m_stuTalkEncodeCfg),
							   &dwRetLen,
							   WAITTIME);
	if(bRet == FALSE || dwRetLen != sizeof(m_stuTalkEncodeCfg))
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Get talk encode configure falied."));
	}

	SetCurSelByData(m_ccbMode, m_stuTalkEncodeCfg.nCompression);
	SetCurSelByData(m_ccbEncode, m_stuTalkEncodeCfg.nMode);

	OnSelchangeComboMode();
	UpdateData(FALSE);
}

void CDlgIPC::SetTalkEncodeCfg()
{
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}

	m_stuTalkEncodeCfg.nMode = m_ccbEncode.GetItemData(m_ccbEncode.GetCurSel());
	m_stuTalkEncodeCfg.nCompression = m_ccbMode.GetItemData(m_ccbMode.GetCurSel());

	BOOL bRet = CLIENT_SetDevConfig(m_lLogin,
									DH_DEV_TALK_ENCODE_CFG,
									0,
									(LPVOID)&m_stuTalkEncodeCfg,
									sizeof(m_stuTalkEncodeCfg),
									WAITTIME);
	if(bRet == FALSE)
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Set talk encode configure failed."));
		return;
	}
}

void CDlgIPC::SetMMSCfg()
{
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}

	m_stuMMSCfg.dwEnable = m_bEMS;
	m_stuMMSCfg.dwReceiverNum = m_listSMS.GetCount();
	m_stuMMSCfg.byType = m_ccbType.GetItemData(m_ccbType.GetCurSel());
	strcpy(m_stuMMSCfg.SZTitle, m_strTitle.GetBuffer(0));
	//receiver
	CString strRecv;
	for(int i = 0; i < m_stuMMSCfg.dwReceiverNum; i++)
	{
		m_listEMS.GetText(i, strRecv);
		strcpy(m_stuMMSCfg.SZReceiver[i], strRecv.GetBuffer(0));
	}

	BOOL bRet = CLIENT_SetDevConfig(m_lLogin,
									DH_DEV_MMS_CFG,
									0,
									(LPVOID)&m_stuMMSCfg,
									sizeof(m_stuMMSCfg),
									WAITTIME);
	if(bRet == FALSE)
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Set MMS configure failed."));
		return;
	}

	return;
}

void CDlgIPC::GetMMSCfg()
{
	DWORD dwRetLen = 0;
	BOOL bRet = CLIENT_GetDevConfig(m_lLogin,
									DH_DEV_MMS_CFG,
									0,
									(LPVOID)&m_stuMMSCfg,
									sizeof(m_stuMMSCfg),
									&dwRetLen,
									WAITTIME);
	if(dwRetLen != sizeof(m_stuMMSCfg) || (bRet == FALSE))
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Get MMS configure failed."));
		return;
	}

	m_bEMS = m_stuMMSCfg.dwEnable;
	m_ccbType.SetCurSel(m_stuMMSCfg.byType);
	m_strTitle = m_stuMMSCfg.SZTitle;
	
	m_listEMS.ResetContent();
	for(int i = 0; i < m_stuMMSCfg.dwReceiverNum; i++)
	{
		m_listEMS.AddString(m_stuMMSCfg.SZReceiver[i]);
	}

	UpdateData(FALSE);
}

void CDlgIPC::SetSMSCfg()
{
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}

	m_stuSMSCfg.dwEnable = m_bSMS;
	m_stuSMSCfg.dwSenderNum = m_listSMS.GetCount();
	//sender
	CString strSender;
	for(int i = 0; i < m_stuSMSCfg.dwSenderNum; i++)
	{
		m_listSMS.GetText(i, strSender);
		strcpy(m_stuSMSCfg.SZSender[i], strSender.GetBuffer(0));
	}

	BOOL bRet = CLIENT_SetDevConfig(m_lLogin, 
									DH_DEV_SMSACTIVATION_CFG,
									0,
									(LPVOID)&m_stuSMSCfg,
									sizeof(m_stuSMSCfg),
									WAITTIME);
	if(bRet == FALSE)
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Set SMS configure failed."));
		return;
	}
	
	return;
}

void CDlgIPC::GetSMSCfg()
{
	DWORD dwRetLen = 0;
	BOOL bRet = CLIENT_GetDevConfig(m_lLogin,
									DH_DEV_SMSACTIVATION_CFG,
									0,
									(LPVOID)&m_stuSMSCfg,
									sizeof(m_stuSMSCfg),
									&dwRetLen,
									WAITTIME);
	if(dwRetLen != sizeof(m_stuSMSCfg) || (bRet == FALSE))
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Get SMS configure failed."));
		return;
	}

	m_bSMS = m_stuSMSCfg.dwEnable;
	
	m_listSMS.ResetContent();
	for(int i = 0; i < m_stuSMSCfg.dwSenderNum; i++)
	{
		m_listSMS.AddString(m_stuSMSCfg.SZSender[i]);
	}

	UpdateData(FALSE);
}

void CDlgIPC::SetDiaCfg()
{
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}

	m_stuDiaCfg.dwEnable = m_bDial;
	m_stuDiaCfg.dwCallerNum = m_listDial.GetCount();
	//caller
	CString strCaller;
	for(int i = 0; i < m_stuDiaCfg.dwCallerNum; i++)
	{
		m_listDial.GetText(i, strCaller);
		strcpy(m_stuDiaCfg.SZCaller[i], strCaller.GetBuffer(0));
	}

	BOOL bRet = CLIENT_SetDevConfig(m_lLogin, 
									DH_DEV_DIALINACTIVATION_CFG,
									0,
									(LPVOID)&m_stuDiaCfg,
									sizeof(m_stuDiaCfg),
									WAITTIME);
	if(bRet == FALSE)
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Set Dial configure failed."));
		return;
	}
	
	return;
}
void CDlgIPC::GetDiaCfg()
{
	DWORD dwRetLen = 0;
	BOOL bRet = CLIENT_GetDevConfig(m_lLogin,
									DH_DEV_DIALINACTIVATION_CFG,
									0,
									(LPVOID)&m_stuDiaCfg,
									sizeof(m_stuDiaCfg),
									&dwRetLen,
									WAITTIME);
	if(dwRetLen != sizeof(m_stuDiaCfg) || (bRet == FALSE))
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Get Dial configure failed."));
		return;
	}

	m_bDial = m_stuDiaCfg.dwEnable;

	m_listDial.ResetContent();
	for(int i = 0; i < m_stuDiaCfg.dwCallerNum; i++)
	{
		m_listDial.AddString(m_stuDiaCfg.SZCaller[i]);
	}

	UpdateData(FALSE);
}

void CDlgIPC::OnButtonEmsAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_listEMS.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}

	if(m_strRecv != "")
	{
		m_listEMS.AddString(m_strRecv);
	}

	return;
}

void CDlgIPC::OnButtonEmsDelete() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listEMS.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a string"));
		return;
	}
	
	m_listEMS.DeleteString(nIndex);
}

void CDlgIPC::OnButtonSmsAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_listSMS.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}
	
	if(m_strSender != "")
	{
		m_listSMS.AddString(m_strSender);
	}
	
	return;
}

void CDlgIPC::OnButtonSmsDelete() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listSMS.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a string"));
		return;
	}
	
 	m_listSMS.DeleteString(nIndex);
}

void CDlgIPC::OnButtonDiaAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_listDial.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}
	
	if(m_strCaller != "")
	{
		m_listDial.AddString(m_strCaller);
	}
	
	return;
}

void CDlgIPC::OnButtonDiaDelete() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listDial.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a string"));
		return;
	}
	
	m_listDial.DeleteString(nIndex);
}

void CDlgIPC::OnButton7() //add
{
	// TODO: Add your control notification handler code here
	if(m_listWhite.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}

	CString m_strIP;
	m_IP.GetWindowText(m_strIP);

	m_listWhite.AddString(m_strIP);
	return;
}

void CDlgIPC::OnButton8() //delete
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listWhite.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a IP"));
		return;
	}

	m_listWhite.DeleteString(nIndex);
}

void CDlgIPC::OnRadioWhite() 
{
	// TODO: Add your control notification handler code here
	m_bWhite = TRUE;
}

void CDlgIPC::OnRadioBlack() 
{
	// TODO: Add your control notification handler code here
	m_bWhite = FALSE;
}

void CDlgIPC::OnButton9() //add
{
	// TODO: Add your control notification handler code here
	if(m_listBlack.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	CString m_strIP;
	m_IPBlack.GetWindowText(m_strIP);
	
	m_listBlack.AddString(m_strIP);
	return;	
}

void CDlgIPC::OnButton10() //delete
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listBlack.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a IP"));
		return;
	}
	
	m_listBlack.DeleteString(nIndex);
}

void CDlgIPC::OnSelchangeComboMode() 
{
	// TODO: Add your control notification handler code here
	//char* szTalk[] = {"Default", "PCM", "G711a", "AMR", "G711u", "G726"};
	BOOL bShow = (m_ccbMode.GetItemData(m_ccbMode.GetCurSel()) == 3);
	m_ccbEncode.ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_BITRATE)->ShowWindow(bShow);
}

void CDlgIPC::OnCloseupComboMode() 
{
	// TODO: Add your control notification handler code here
	
}

// void CDlgIPC::OnEditchangeComboMode() 
// {
// 	// TODO: Add your control notification handler code here
// 
// 
// }
// 
// void CDlgIPC::OnEditupdateComboMode() 
// {
// 	// TODO: Add your control notification handler code here
// }

void CDlgIPC::OnButtonWhiteListBROW()
{
	CString strFilePathName;
	CFileDialog *dlgFile = new CFileDialog(TRUE);
	if (IDOK == dlgFile->DoModal())
	{
		strFilePathName = dlgFile->GetPathName();
	}
	else
	{
		return;
	}

	int i = 0;
	int nIPcount = 0;
	char szIPName[16] = {0};
	char szIPAddr[32] = {0};
	char szIPCount[8] = {0};

	// 白名单
	GetPrivateProfileString("WihteIP", "IPCount", "", szIPCount, 8, strFilePathName);
	nIPcount = atoi(szIPCount);
	m_listWhite.ResetContent();
	for(i = 0; i < nIPcount; i++)
	{
		sprintf(szIPName, "ip%d", i);
		GetPrivateProfileString("WihteIP", szIPName, "", szIPAddr, 32, strFilePathName);

		m_listWhite.AddString(szIPAddr);
	}

	// 黑名单
	GetPrivateProfileString("BlackIP", "IPCount", "", szIPCount, 8, strFilePathName);
	nIPcount = atoi(szIPCount);
	m_listBlack.ResetContent();
	for(i = 0; i < nIPcount; i++)
	{
		sprintf(szIPName, "ip%d", i);
		GetPrivateProfileString("BlackIP", szIPName, "", szIPAddr, 32, strFilePathName);
		
		m_listBlack.AddString(szIPAddr);
	}
}
