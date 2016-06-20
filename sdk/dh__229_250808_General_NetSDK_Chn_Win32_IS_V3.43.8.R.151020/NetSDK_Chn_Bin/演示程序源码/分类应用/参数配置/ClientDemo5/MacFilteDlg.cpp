// MacFilteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "MacFilteDlg.h"



#define MacLength	17

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMacFilteDlg dialog


CMacFilteDlg::CMacFilteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMacFilteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMacFilteDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CMacFilteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMacFilteDlg)
	DDX_Control(pDX, IDC_EDIT1_BLACK_MAC, m_editBlackMac);
	DDX_Control(pDX, IDC_EDIT_WHITE_MAC, m_editWhiteMac);
	DDX_Control(pDX, IDC_LIST_BLACK_MAC, m_blackList);
	DDX_Control(pDX, IDC_LIST_WHITE_MAC, m_whiteList);
	DDX_Check(pDX, IDC_CHECK_MACFILTER, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMacFilteDlg, CDialog)
	//{{AFX_MSG_MAP(CMacFilteDlg)
	ON_BN_CLICKED(IDC_BTN_MAC_INPUT, OnBtnMacInput)
	ON_BN_CLICKED(IDC_BTN_WHITE_ADD, OnBtnWhiteAdd)
	ON_BN_CLICKED(IDC_BTN_WHITE_DEL, OnBtnWhiteDel)
	ON_BN_CLICKED(IDC_BTN_BLACK_ADD, OnBtnBlackAdd)
	ON_BN_CLICKED(IDC_BTN_BLACK_DEL, OnBtnBlackDel)
	ON_BN_CLICKED(IDC_RADIO_WHITE_MAC, OnRadioWhiteMac)
	ON_BN_CLICKED(IDC_RADIO_BLACK_MAC, OnRadioBlackMac)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMacFilteDlg message handlers

BOOL CMacFilteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMacFilteDlg::OnBtnMacInput() 
{
	// TODO: Add your control notification handler code here
	CString strFilePathName;
	CFileDialog dlgFile(TRUE);
	if (IDOK == dlgFile.DoModal())
	{
		strFilePathName = dlgFile.GetPathName();
	}
	else
	{
		return;
	}
	
	int i = 0;
	int nMaccount = 0;
	char szMacName[16] = {0};
	char szMacAddr[32] = {0};
	char szMacCount[8] = {0};
	
	// 白名单
	GetPrivateProfileString("WihteMac", "MacCount", "", szMacCount, 8, strFilePathName);
	nMaccount = atoi(szMacCount);
	m_whiteList.ResetContent();
	for(i = 0; i < nMaccount; i++)
	{
		sprintf(szMacName, "mac%d", i);
		GetPrivateProfileString("WihteMac", szMacName, "", szMacAddr, 32, strFilePathName);
		if (IsVlidateMac(szMacAddr, m_whiteList))
		{
			m_whiteList.AddString(szMacAddr);
		}
		
	}
	
	// 黑名单
	GetPrivateProfileString("BlackMac", "MacCount", "", szMacCount, 8, strFilePathName);
	nMaccount = atoi(szMacCount);
	m_blackList.ResetContent();
	for(i = 0; i < nMaccount; i++)
	{
		sprintf(szMacName, "mac%d", i);
		GetPrivateProfileString("BlackMac", szMacName, "", szMacAddr, 32, strFilePathName);
		if (IsVlidateMac(szMacAddr, m_blackList))
		{
			m_blackList.AddString(szMacAddr);
		}
	}

	
}

void CMacFilteDlg::OnBtnWhiteAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_whiteList.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	CString strMac;
	m_editWhiteMac.GetWindowText(strMac);

	if (!IsVlidateMac(strMac.GetBuffer(0), m_whiteList))
	{
		return;
	}

	m_whiteList.AddString(strMac);
	m_editWhiteMac.SetWindowText("");
	return;
}

void CMacFilteDlg::OnBtnWhiteDel() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_whiteList.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a MAC"));
		return;
	}
	
	m_whiteList.DeleteString(nIndex);
}

void CMacFilteDlg::OnBtnBlackAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_blackList.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	CString strMac;
	m_editBlackMac.GetWindowText(strMac);

	if (!IsVlidateMac(strMac.GetBuffer(0), m_blackList))
	{
		return;
	}
	
	m_blackList.AddString(strMac);
	m_editBlackMac.SetWindowText("");
	return;
}

void CMacFilteDlg::OnBtnBlackDel() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_blackList.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a MAC"));
		return;
	}
	
	m_blackList.DeleteString(nIndex);
}


void CMacFilteDlg::GetMacFilterCfg()
{
	//DHDEV_MACFILTER_CFG* m_stuMacFilterCfg = new DHDEV_MACFILTER_CFG;
	/*memset(&m_stuMacFilterCfg, 0, sizeof(DHDEV_MACFILTER_CFG));
	m_stuMacFilterCfg.dwSize = sizeof(DHDEV_MACFILTER_CFG);
	m_stuMacFilterCfg.stuBannedMac.dwSize = sizeof(MACFILTER_INFO);
	m_stuMacFilterCfg.stuTrustMac.dwSize = sizeof(MACFILTER_INFO);
	
	DWORD dwRetLen = 0;
	BOOL bRet = CLIENT_GetDevConfig(m_lLogin
									, DH_DEV_MACFILTER_CFG
									, -1
									, &m_stuMacFilterCfg
									, sizeof(DHDEV_MACFILTER_CFG)
									, &dwRetLen);

	DWORD d = CLIENT_GetLastError();
	if(dwRetLen != sizeof(DHDEV_MACFILTER_CFG) || (bRet == FALSE))
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Get mac filter configure failed."));
		return;
	}
	//TODO
	m_bEnable = m_stuMacFilterCfg.dwEnable;
	m_bWhite = m_stuMacFilterCfg.dwType == 0 ? TRUE : FALSE;
	((CButton *)GetDlgItem(IDC_RADIO_WHITE_MAC))->SetCheck(m_bWhite);
	((CButton *)GetDlgItem(IDC_RADIO_BLACK_MAC))->SetCheck(!m_bWhite);
	
	//add string
	m_whiteList.ResetContent();
	m_blackList.ResetContent();
	for(unsigned int i = 0; i < m_stuMacFilterCfg.stuTrustMac.dwMacNum; i++)
	{
		if (IsVlidateMac(m_stuMacFilterCfg.stuTrustMac.szMac[i], m_whiteList))
			m_whiteList.AddString(m_stuMacFilterCfg.stuTrustMac.szMac[i]);
	}
	for(unsigned int j = 0; j < m_stuMacFilterCfg.stuBannedMac.dwMacNum; j++)
	{
		if (IsVlidateMac(m_stuMacFilterCfg.stuBannedMac.szMac[j], m_blackList))
			m_blackList.AddString(m_stuMacFilterCfg.stuBannedMac.szMac[j]);
	}
	
	UpdateData(FALSE);*/
	return;
}

void CMacFilteDlg::SetMacFilterCfg()
{
	//TODO
	/*if(UpdateData(TRUE) == FALSE)
	{
		return;
	}
	m_stuMacFilterCfg.dwEnable = m_bEnable;
	m_stuMacFilterCfg.dwType = m_bWhite == TRUE ? 0 : 1;//0,白名单，1黑名单
	m_stuMacFilterCfg.stuTrustMac.dwMacNum = m_whiteList.GetCount();
	m_stuMacFilterCfg.stuBannedMac.dwMacNum = m_blackList.GetCount();
	//black and white list
	CString strWhite;
	CString strBlack;
	for(unsigned int i = 0; i < m_stuMacFilterCfg.stuTrustMac.dwMacNum; i++)
	{
		m_whiteList.GetText(i, strWhite);
		strcpy(m_stuMacFilterCfg.stuTrustMac.szMac[i], strWhite.GetBuffer(0));
	}
	for(unsigned int j = 0; j < m_stuMacFilterCfg.stuBannedMac.dwMacNum; j++)
	{
		m_blackList.GetText(j, strBlack);
		strcpy(m_stuMacFilterCfg.stuBannedMac.szMac[j], strBlack.GetBuffer(0));
	}
	//Set
	BOOL bRet = CLIENT_SetDevConfig(m_lLogin,
									DH_DEV_MACFILTER_CFG,
									0,
									(LPVOID)&m_stuMacFilterCfg,
									sizeof(DHDEV_MACFILTER_CFG));
	if(bRet == FALSE)
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Set mac filter configure failed."));
		return;
	}

	MessageBox(ConvertString("Set mac filter configure succeed."));
*/
	return;
}


bool CMacFilteDlg::IsVlidateMac(char* strMac, CListBox& listbox)
{
	if (!IsValidityMacTolower(strMac))
	{
		MessageBox(ConvertString("mac is invalidity, validate mac like this(8C:89:A5:8E:E4:16)"));
		return false;
	}
	
	if (IsMacHas(strMac, listbox))
	{
		MessageBox(ConvertString("this mac is already exist!"));
		return false;
	}
	
	return true;
};

bool CMacFilteDlg::IsValidityMacTolower(char* mac)
{
	std::string tempMac = mac;
	if(tempMac.empty())
	{
		return false;
	}
	if(tempMac.size() != MacLength)
	{
		return false;
	}
	for(std::string::size_type index = 0; index != tempMac.size(); ++index)
	{
		if (((((index+1)%3) !=0) && isxdigit(tempMac[index])))
		{
			tempMac[index] = tolower(tempMac[index]);
		}
		else if ((((index+1)%3) ==0) && tempMac[index] == ':')
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	memcpy(mac,tempMac.c_str(), MacLength+1);
	return true;
}


bool CMacFilteDlg::IsMacHas(char* strMac, CListBox& listbox)
{
	int nIndex = listbox.FindString(0, strMac);
	if (nIndex == -1)
	{
		return false;
	}

	return true;
};

void CMacFilteDlg::OnRadioWhiteMac() 
{
	// TODO: Add your control notification handler code here
	m_bWhite = TRUE;
}

void CMacFilteDlg::OnRadioBlackMac() 
{
	// TODO: Add your control notification handler code here
	m_bWhite = FALSE;
}
