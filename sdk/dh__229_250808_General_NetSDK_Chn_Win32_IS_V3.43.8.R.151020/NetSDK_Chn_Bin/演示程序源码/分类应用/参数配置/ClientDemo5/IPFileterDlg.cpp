// IPFileterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "IPFileterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPFileterDlg dialog


CIPFileterDlg::CIPFileterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPFileterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPFileterDlg)
	m_bEnable = FALSE;
    m_pstuAccessFilter = NULL;
	//}}AFX_DATA_INIT
}


void CIPFileterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPFileterDlg)
	DDX_Control(pDX, IDC_IPADDRESS_BLACK_IP, m_ctlBlackIP);
	DDX_Control(pDX, IDC_IPADDRESS_WHITE_IP, m_ctlWhiteIP);
	DDX_Control(pDX, IDC_LIST_BLACK, m_lsBlack);
	DDX_Control(pDX, IDC_LIST_WHITE, m_lsWhite);
	DDX_Check(pDX, IDC_CHECK_LIST_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPFileterDlg, CDialog)
	//{{AFX_MSG_MAP(CIPFileterDlg)
	ON_BN_CLICKED(IDC_BUTTON_WL_BROW, OnButtonWlBrow)
	ON_BN_CLICKED(IDC_BUTTON_ADD_WHITE, OnButtonAddWhite)
	ON_BN_CLICKED(IDC_BUTTON_DEL_WHITE, OnButtonDelWhite)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BLACK, OnButtonAddBlack)
	ON_BN_CLICKED(IDC_BUTTON_DEL_BLACK, OnButtonDelBlack)
	ON_BN_CLICKED(IDC_RADIO_BLACK, OnRadioBlack)
	ON_BN_CLICKED(IDC_RADIO_WHITE, OnRadioWhite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL CIPFileterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	return TRUE;
}

// CIPFileterDlg message handlers
void CIPFileterDlg::GetIPFilterCfg()
{

    // 首次申请内存
    if (NULL == m_pstuAccessFilter)
    {
        m_pstuAccessFilter = new AV_CFG_AccessFilter;
    }
    if (NULL == m_pstuAccessFilter)
    {
        return;
    }
	int bufLen = 256 * 1024;
	char *buf = new char[bufLen];
    if (NULL == buf)
    {
        return;
    }
	memset(buf, 0, bufLen);
	int error = 0;
	int retLen = 0;
	BOOL bRet = CLIENT_GetNewDevConfig(m_lLogin, CFG_CMD_ACCESSFILTER, -1, buf, bufLen, &error, 5000);
	if (FALSE == bRet)
	{
        delete[] buf;
        buf = NULL;
        MessageBox(ConvertString("Get ip filter configure failed."));
		return;
	}

    memset(m_pstuAccessFilter, 0, sizeof(AV_CFG_AccessFilter));
	m_pstuAccessFilter->nStructSize = sizeof(AV_CFG_AccessFilter);
	bRet = CLIENT_ParseData(CFG_CMD_ACCESSFILTER, buf, m_pstuAccessFilter, sizeof(AV_CFG_AccessFilter), NULL);
	if (FALSE == bRet)
	{
        delete[] buf;
        buf = NULL;
        MessageBox(ConvertString("Parse ip filter configure failed."));
		return;
	}
    delete[] buf;
    buf = NULL;

    //TODO
    m_bEnable = m_pstuAccessFilter->bEnable;
    m_bWhite = m_pstuAccessFilter->nType == 0 ? FALSE : TRUE;
    ((CButton *)GetDlgItem(IDC_RADIO_WHITE))->SetCheck(m_bWhite);
    ((CButton *)GetDlgItem(IDC_RADIO_BLACK))->SetCheck(!m_bWhite);
    
    //add string
    m_lsWhite.ResetContent();
    int nMaxWhiteNum = __min(m_pstuAccessFilter->nWhiteListNum, AV_CFG_Max_White_List);
    for(unsigned int i = 0; i < nMaxWhiteNum; i++)
    {
        m_lsWhite.AddString(m_pstuAccessFilter->szWhiteList[i]);
    }

    m_lsBlack.ResetContent();
    int nMaxBlackNum = __min(m_pstuAccessFilter->nBlackListNum, AV_CFG_Max_Black_List);
    for(unsigned int j = 0; j < nMaxBlackNum; j++)
    {
        m_lsBlack.AddString(m_pstuAccessFilter->szBlackList[j]);
	}

	UpdateData(FALSE);
	return;
}

void CIPFileterDlg::SetIPFilterCfg()
{
	//TODO
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}
    if (NULL == m_pstuAccessFilter)
    {
        return;
    }
	m_pstuAccessFilter->bEnable = m_bEnable;
	m_pstuAccessFilter->nType = m_bWhite == TRUE ? 1 : 0;//0,黑名单，1白名单
	m_pstuAccessFilter->nWhiteListNum = m_lsWhite.GetCount();
	m_pstuAccessFilter->nBlackListNum = m_lsBlack.GetCount();
	//black and white list
	CString strWhite;
	CString strBlack;
    int nMaxWhiteNum = __min(m_pstuAccessFilter->nWhiteListNum, AV_CFG_Max_White_List);
	for(unsigned int i = 0; i < nMaxWhiteNum; i++)
	{
		m_lsWhite.GetText(i, strWhite);
		strcpy(m_pstuAccessFilter->szWhiteList[i], strWhite.GetBuffer(0));
	}
    int nMaxBlackNum = __min(m_pstuAccessFilter->nBlackListNum, AV_CFG_Max_Black_List);
	for(unsigned int j = 0; j < nMaxBlackNum; j++)
	{
		m_lsBlack.GetText(j, strBlack);
		strcpy(m_pstuAccessFilter->szBlackList[j], strBlack.GetBuffer(0));
	}
	//Set
    int bufLen = 256 * 1024;
    char *buf = new char[bufLen];
    if (NULL == buf)
    {
        return;
    }
    memset(buf, 0, bufLen);
    BOOL bRet = CLIENT_PacketData(CFG_CMD_ACCESSFILTER, m_pstuAccessFilter, sizeof(AV_CFG_AccessFilter), buf, bufLen);
    if (FALSE == bRet)
    {
        delete[] buf;
        MessageBox(ConvertString("Packet ip filter configure failed."));
        return;
	}
    int nErr = 0;
    int nRestart = 0;			
    bRet = CLIENT_SetNewDevConfig(m_lLogin, CFG_CMD_ACCESSFILTER, -1, buf, bufLen, &nErr, &nRestart, 5000);
	if (FALSE == bRet)
	{
        MessageBox(ConvertString("Set ip filter configure failed."));
	}
	delete []buf;	
	return;
}

void CIPFileterDlg::OnButtonWlBrow() 
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
	m_lsWhite.ResetContent();
	for(i = 0; i < nIPcount; i++)
	{
		sprintf(szIPName, "ip%d", i);
		GetPrivateProfileString("WihteIP", szIPName, "", szIPAddr, 32, strFilePathName);
		
		m_lsWhite.AddString(szIPAddr);
	}
	
	// 黑名单
	GetPrivateProfileString("BlackIP", "IPCount", "", szIPCount, 8, strFilePathName);
	nIPcount = atoi(szIPCount);
	m_lsBlack.ResetContent();
	for(i = 0; i < nIPcount; i++)
	{
		sprintf(szIPName, "ip%d", i);
		GetPrivateProfileString("BlackIP", szIPName, "", szIPAddr, 32, strFilePathName);
		
		m_lsBlack.AddString(szIPAddr);
	}
}

void CIPFileterDlg::OnButtonAddWhite() 
{
	if(m_lsWhite.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	CString strIP;
	m_ctlWhiteIP.GetWindowText(strIP);
	
	m_lsWhite.AddString(strIP);
	return;
}

void CIPFileterDlg::OnButtonDelWhite() 
{
	int nIndex = m_lsWhite.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a IP"));
		return;
	}
	
	m_lsWhite.DeleteString(nIndex);
}

void CIPFileterDlg::OnButtonAddBlack() 
{
	if(m_lsBlack.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	CString strIP;
	m_ctlBlackIP.GetWindowText(strIP);
	
	m_lsBlack.AddString(strIP);
	return;
}

void CIPFileterDlg::OnButtonDelBlack() 
{
	int nIndex = m_lsBlack.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a IP"));
		return;
	}
	
	m_lsBlack.DeleteString(nIndex);
}

void CIPFileterDlg::OnRadioBlack() 
{
	m_bWhite = FALSE;
}

void CIPFileterDlg::OnRadioWhite() 
{
	m_bWhite = TRUE;
}

void CIPFileterDlg::ClearAll()
{
	if (NULL == m_pstuAccessFilter)
	{
        return;
	}
    delete m_pstuAccessFilter;
    m_pstuAccessFilter = NULL;
}