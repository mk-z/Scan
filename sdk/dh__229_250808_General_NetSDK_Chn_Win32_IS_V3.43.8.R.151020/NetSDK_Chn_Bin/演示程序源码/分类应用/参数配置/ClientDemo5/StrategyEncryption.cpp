// StrategyEncryption.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "StrategyEncryption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrategyEncryption dialog


CStrategyEncryption::CStrategyEncryption(CWnd* pParent /*=NULL*/)
	: CDialog(CStrategyEncryption::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStrategyEncryption)
	//}}AFX_DATA_INIT
	m_nChannel = 0;
	m_nChannelPreIndex  = 0;
	m_lLogin = 0;
	m_stuEncryption.byEncrptAlgoType = 0;
	m_stuEncryption.stuEncrptAlgoparam.byAlgoWorkMode = 0;
	m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 0;
	ZeroMemory(m_stuEncryption.stuEncrptAlgoparam.reserved,sizeof(m_stuEncryption.stuEncrptAlgoparam.reserved));
	ZeroMemory(m_stuEncryption.byReserved1,sizeof(m_stuEncryption.byReserved1));
	ZeroMemory(m_stuEncryption.reserved2,sizeof(m_stuEncryption.reserved2));
	ZeroMemory(m_byKey, sizeof(m_byKey));
	for(int i = 0; i < 32; i ++)
	{
		m_stuEncryption.stuEncryptKeys[i].byEncryptEnable = 0;
		ZeroMemory(m_stuEncryption.stuEncryptKeys[i].byAesKey,sizeof(m_stuEncryption.stuEncryptKeys[i].byAesKey));
		ZeroMemory(m_stuEncryption.stuEncryptKeys[i].byReserved,sizeof(m_stuEncryption.stuEncryptKeys[i].byReserved));
	}
}


void CStrategyEncryption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStrategyEncryption)
	DDX_Control(pDX, IDC_CHECK_ENCRYPT, m_ctlEncrypt);
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_ccbWorkmode);
	DDX_Control(pDX, IDC_COMBO_KEYLENGTH, m_ccbKeylength);
	DDX_Control(pDX, IDC_COMBO_ENCRYPTION, m_ccbEncryption);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ccbChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStrategyEncryption, CDialog)
	//{{AFX_MSG_MAP(CStrategyEncryption)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_CBN_SELENDCANCEL(IDC_COMBO_CHANNEL, OnSelendcancelComboChannel)
	ON_CBN_SELCHANGE(IDC_COMBO_ENCRYPTION, OnSelchangeComboEncryption)
	ON_CBN_SELCHANGE(IDC_COMBO_WORKMODE, OnSelchangeComboWorkmode)
	ON_CBN_SELCHANGE(IDC_COMBO_KEYLENGTH, OnSelchangeComboKeylength)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStrategyEncryption message handlers

BOOL CStrategyEncryption::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	m_nChannelPreIndex = -1;

	int nIndex;

	nIndex = m_ccbWorkmode.AddString(ConvertString("ECB"));
	m_ccbWorkmode.SetItemData(nIndex,0);
	nIndex = m_ccbWorkmode.AddString(ConvertString("CBC"));
	m_ccbWorkmode.SetItemData(nIndex,1);
	nIndex = m_ccbWorkmode.AddString(ConvertString("CFB"));
	m_ccbWorkmode.SetItemData(nIndex,2);
	nIndex = m_ccbWorkmode.AddString(ConvertString("OFB"));
	m_ccbWorkmode.SetItemData(nIndex,3);

    nIndex = m_ccbEncryption.AddString(ConvertString("AES"));
	m_ccbEncryption.SetItemData(nIndex,0);
	nIndex = m_ccbEncryption.AddString(ConvertString("DES"));
	m_ccbEncryption.SetItemData(nIndex,1);
	nIndex = m_ccbEncryption.AddString(ConvertString("3DES"));
	m_ccbEncryption.SetItemData(nIndex,2);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStrategyEncryption::GetEncryptionCfg()
{
    char buf[200];
	int  nIndex = 0, i = 0;
	DWORD dwRetLen = 0;
	BOOL bRet	 = CLIENT_GetDevConfig(m_lLogin,DH_DEV_STREAM_ENCRYPT_CFG,0,(LPVOID)&m_stuEncryption,sizeof(DHEDV_STREAM_ENCRYPT),&dwRetLen);
	if(bRet == FALSE || dwRetLen != sizeof(m_stuEncryption))
	{
	#ifdef _DEBUG
			DWORD dwError = CLIENT_GetLastError();
	#endif
		MessageBox(ConvertString("get Encryption configure failed!"), ConvertString("Prompt"));
	}
	CleanAll();
	m_nChannelPreIndex = 0;
	for(i = 0; i < m_nChannel; i ++)
	{ 
		itoa(i+1,buf,10);
		nIndex = m_ccbChannel.AddString(ConvertString(buf));
		m_ccbChannel.SetItemData(nIndex,i);
	}
	m_ccbChannel.SetCurSel(0);
	if(m_stuEncryption.stuEncryptKeys[0].byEncryptEnable)
	{
		m_ctlEncrypt.SetCheck(1);
	}
	else
	{
		m_ctlEncrypt.SetCheck(0);
	}
	ShowChannelKey(0);

//Init
	if(m_stuEncryption.byEncrptAlgoType == 0)
	{
		m_ccbEncryption.SetCurSel(0);
		
		nIndex = m_ccbKeylength.AddString(ConvertString("128bits"));
		m_ccbKeylength.SetItemData(nIndex,0);
		
		nIndex = m_ccbKeylength.AddString(ConvertString("192bits"));
		m_ccbKeylength.SetItemData(nIndex,1);
		
		nIndex = m_ccbKeylength.AddString(ConvertString("256bits"));
		m_ccbKeylength.SetItemData(nIndex,2);

		if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 128)
		{
			m_ccbKeylength.SetCurSel(0);
		}
		else if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 192)
		{
			m_ccbKeylength.SetCurSel(1);
		}
		else if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 256)
		{
			m_ccbKeylength.SetCurSel(2);
		}

	}
	else if(m_stuEncryption.byEncrptAlgoType == 1)
	{
		m_ccbEncryption.SetCurSel(1);
		nIndex = m_ccbKeylength.AddString(ConvertString("64bits"));
		m_ccbKeylength.SetItemData(nIndex,0);
		m_ccbKeylength.SetCurSel(0);
	}
	else if(m_stuEncryption.byEncrptAlgoType == 2)
	{
		m_ccbEncryption.SetCurSel(2);

		nIndex = m_ccbKeylength.AddString(ConvertString("2 64bits"));
		m_ccbKeylength.SetItemData(nIndex,0);
		
		nIndex = m_ccbKeylength.AddString(ConvertString("3 64bits"));
		m_ccbKeylength.SetItemData(nIndex,1);
		if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 2)
		{
			m_ccbKeylength.SetCurSel(0);
		}else
		{
			m_ccbKeylength.SetCurSel(1);
		}
	}

	if(m_stuEncryption.stuEncrptAlgoparam.byAlgoWorkMode == ENCRYPT_ALOG_WORKMODE_ECB)
	{
		m_ccbWorkmode.SetCurSel(0);	
	}
	else if(m_stuEncryption.stuEncrptAlgoparam.byAlgoWorkMode == ENCRYPT_ALOG_WORKMODE_CBC)
	{
		m_ccbWorkmode.SetCurSel(1);
	}
	else if(m_stuEncryption.stuEncrptAlgoparam.byAlgoWorkMode == ENCRYPT_ALOG_WORKMODE_CFB)
	{
		m_ccbWorkmode.SetCurSel(2);
	}
	else if(m_stuEncryption.stuEncrptAlgoparam.byAlgoWorkMode == ENCRYPT_ALOG_WORKMODE_OFB)
	{
		m_ccbWorkmode.SetCurSel(3);
	}		
}
void CStrategyEncryption::SetEncryptionCfg()
{
	BOOL bSaveSuccess = SaveChannelKey(m_nChannelPreIndex);
	if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 0 || bSaveSuccess == FALSE)
	{
		MessageBox(ConvertString("Set Encryption configure failed!"), ConvertString("Prompt"));
		return;
	}
	DWORD dwRetLen = 0;
	int i = 0;
	char buf[200];

	BOOL bRet	 = CLIENT_SetDevConfig(m_lLogin,DH_DEV_STREAM_ENCRYPT_CFG,0,(LPVOID)&m_stuEncryption,sizeof(DHEDV_STREAM_ENCRYPT));
	if(bRet == FALSE)
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Set Encryption configure failed!"), ConvertString("Prompt"));
		return; 
	}
	std::string swrite = "Encryption Algorithm:";
	if(m_stuEncryption.byEncrptAlgoType == 0)
	{
		swrite += "AES KeyLength:";
		itoa(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth,buf,10);
		swrite += buf;
		swrite += "bits";
	}
	else if(m_stuEncryption.byEncrptAlgoType == 1)
	{
		swrite += "DES KeyLength:64bits";
	}
	else
	{
		swrite += "3DES Keylength:";
		itoa(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth,buf,10);
		swrite += buf;
		swrite += " 64bits";
	}
	memset(buf,0,sizeof(buf));
	for(i = 0; i < swrite.length();i++)
	{
		buf[i]=swrite[i];
	}
	MessageBox(ConvertString(buf));
}
void CStrategyEncryption::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	BOOL bSaveSuccess = SaveChannelKey(m_nChannelPreIndex);
	if(!bSaveSuccess)
	{
		m_ccbChannel.SetCurSel(m_nChannelPreIndex);
		return;
	}
	int nIndex = m_ccbChannel.GetCurSel();
	if(nIndex != -1)
	{
		if(m_stuEncryption.stuEncryptKeys[nIndex].byEncryptEnable)
		{
			m_ctlEncrypt.SetCheck(1);
		}
		else
		{
			m_ctlEncrypt.SetCheck(0);
		}
		ShowChannelKey(nIndex);
		m_nChannelPreIndex = nIndex;
	}
}

void CStrategyEncryption::OnSelendcancelComboChannel() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ccbChannel.GetCurSel();
}

void CStrategyEncryption::OnSelchangeComboEncryption() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ccbEncryption.GetCurSel(); // 0 AES, 1 DES, 2 3DES
	int nChannelIndex = 0;
	int EncrptType = m_stuEncryption.byEncrptAlgoType;

	if(nIndex == -1)
		return;

	if(EncrptType != nIndex)
	{
		while(m_ccbKeylength.GetCount())
		{
			m_ccbKeylength.DeleteString(0);
		}
		if(nIndex == 0)
		{
			nChannelIndex = m_ccbKeylength.AddString(ConvertString("128bits"));
			m_ccbKeylength.SetItemData(nChannelIndex,0);
			
			nChannelIndex = m_ccbKeylength.AddString(ConvertString("192bits"));
			m_ccbKeylength.SetItemData(nChannelIndex,1);
			
			nChannelIndex = m_ccbKeylength.AddString(ConvertString("256bits"));
			m_ccbKeylength.SetItemData(nChannelIndex,2);
			
			m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 128;
		}
		else if(nIndex == 1)
		{
			nChannelIndex = m_ccbKeylength.AddString(ConvertString("64bits"));
			m_ccbKeylength.SetItemData(nChannelIndex,0);

			m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 64;
		}
		else if(nIndex ==2)
		{
			nChannelIndex = m_ccbKeylength.AddString(ConvertString("2 64bits"));
			m_ccbKeylength.SetItemData(nChannelIndex,0);
			
			nChannelIndex = m_ccbKeylength.AddString(ConvertString("3 64bits"));
			m_ccbKeylength.SetItemData(nChannelIndex,1);

			m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 2;
		}
		m_ccbKeylength.SetCurSel(0);
		m_stuEncryption.byEncrptAlgoType = nIndex;

	}
}

void CStrategyEncryption::OnSelchangeComboWorkmode() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ccbWorkmode.GetCurSel();
	if(nIndex == -1)
		return;
	if(nIndex == 0)
	{
		m_stuEncryption.stuEncrptAlgoparam.byAlgoWorkMode = ENCRYPT_ALOG_WORKMODE_ECB;
	}
	else if(nIndex == 1)
	{
		m_stuEncryption.stuEncrptAlgoparam.byAlgoWorkMode = ENCRYPT_ALOG_WORKMODE_CBC;
	}
	else if(nIndex == 2)
	{
		m_stuEncryption.stuEncrptAlgoparam.byAlgoWorkMode = ENCRYPT_ALOG_WORKMODE_CFB;
	}
	else if(nIndex == 3)
	{
		m_stuEncryption.stuEncrptAlgoparam.byAlgoWorkMode = ENCRYPT_ALOG_WORKMODE_OFB;
	}
}

void CStrategyEncryption::OnSelchangeComboKeylength() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ccbKeylength.GetCurSel();
	int nEncryptionIndex = m_ccbEncryption.GetCurSel();
	if(nEncryptionIndex == -1)
	{
		MessageBox(ConvertString("Please choose the Encryption Algorithm first"));
		return;
	}
	if(nIndex == -1)
		return;
	if(nEncryptionIndex == 0)
	{
		if(nIndex == 0)
		{
			m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 128;
		}
		else if(nIndex == 1)
		{
			m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 192;
		}
		else if(nIndex == 2)
		{
			m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 256;
		}
	}
	else if(nEncryptionIndex == 1)
	{
		m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 64;
	}
	else if(nEncryptionIndex == 2)
	{
		if(nIndex == 0)
		{
			m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 2;
		}
		else
		{
			m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth = 3;
		}
	}

}
BOOL CStrategyEncryption::SaveChannelKey(int nChannelID)
{
//	UpdateData(); //default TRUE;
	int i,j,nKey;
	int nEditItemID = 1047;
	char buf[21];
	for(i = 0; i < 32; i ++)
	{
	    GetDlgItem(nEditItemID+i)->GetWindowText(buf,20);
		for(j = 0; buf[j] != '\0'; j ++)
		{
			if(buf[j] < '0' || buf[j] > '9')
			{
				MessageBox(ConvertString("Please input an interger 0-255"));
				return FALSE;
			}
		}
		nKey = atoi(buf);
	    if(nKey > 255 || nKey < 0)
		{
			MessageBox(ConvertString("Please input an interger 0-255"));
			return FALSE;
		}
	}
	for(i = 0 ; i < 32; i ++)
	{
		GetDlgItem(nEditItemID+i)->GetWindowText(buf,10);
		nKey = atoi(buf);
		m_byKey[i] = nKey;
	}

	int nEncryptIndex = m_ccbEncryption.GetCurSel();
	if(nEncryptIndex == -1)
	{
		MessageBox(ConvertString("Please choose the Encryption Algorithm first"));
		return FALSE;
	}

	int nKeylengthIndex = m_ccbKeylength.GetCurSel();
	if(nKeylengthIndex == -1)
	{
		MessageBox(ConvertString("Please choose the KeyLength first"));
		return FALSE;
	}
	int nWorkModeIndex = m_ccbWorkmode.GetCurSel();
	if(nWorkModeIndex == -1)
	{
		MessageBox(ConvertString("Please choose the WorkMode first"));
		return FALSE;
	}

	if(nChannelID == -1)
	{
		return TRUE;
	}
	int nEncrypt = m_ctlEncrypt.GetCheck();
	if(nEncrypt)
	{
		m_stuEncryption.stuEncryptKeys[nChannelID].byEncryptEnable = 1;
		ZeroMemory(m_stuEncryption.stuEncryptKeys[nChannelID].byAesKey, sizeof(m_stuEncryption.stuEncryptKeys[nChannelID].byAesKey));
		if(m_stuEncryption.byEncrptAlgoType == 0) //AES 128,192,256 bits
		{
			if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 128)
			{
				for(i = 0; i < 16; i++)
				{
					m_stuEncryption.stuEncryptKeys[nChannelID].byAesKey[i] = (BYTE)m_byKey[i];
				}
			}
			else if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 192)
			{	
				for(i = 0; i < 24; i++)
				{
					m_stuEncryption.stuEncryptKeys[nChannelID].byAesKey[i] = (BYTE)m_byKey[i];
				}
			
			}
			else if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 256)
			{
				for(i = 0; i < 32; i++)
				{
					m_stuEncryption.stuEncryptKeys[nChannelID].byAesKey[i] =(BYTE)m_byKey[i];
				}
			}
		}
		else if(m_stuEncryption.byEncrptAlgoType == 1)  //DES  64bits
		{
			for(i = 0; i < 8; i++)
			{
				m_stuEncryption.stuEncryptKeys[nChannelID].byDesKey[i] = (BYTE)m_byKey[i];
			}			
		}
		else if(m_stuEncryption.byEncrptAlgoType == 2)  //3DES  2,3
		{										
			if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 2)
			{
				for(i  =0 ; i < 2; i ++)
				{
					for( j = 0; j < 8;  j++)
					{
						m_stuEncryption.stuEncryptKeys[nChannelID].by3DesKey[i][j] = (BYTE)m_byKey[i*8+j];
					}
				}
			}
			else
			{
				for(i  =0 ; i < 3; i ++)
				{
					for( j = 0; j < 8;  j++)
					{
						m_stuEncryption.stuEncryptKeys[nChannelID].by3DesKey[i][j] = (BYTE)m_byKey[i*8+j];
					}
				}
				
			}
		}
	}
	else
	{
		m_stuEncryption.stuEncryptKeys[nChannelID].byEncryptEnable = 0;
		ZeroMemory(m_stuEncryption.stuEncryptKeys[nChannelID].byAesKey, sizeof(m_stuEncryption.stuEncryptKeys[nChannelID].byAesKey));
	}
	return TRUE;
}
void CStrategyEncryption::ShowChannelKey(int nChennelID)
{
	int i;
	int nEditItemID = 1047; // IDC_EDIT_KEY0  1047
	if(m_stuEncryption.byEncrptAlgoType == 0)
	{
		if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 128)
		{
			for(i = 0 ; i < 32; i ++)
			{
				if(i < 16)
				{
					SetDlgItemInt(nEditItemID+i,m_stuEncryption.stuEncryptKeys[nChennelID].byAesKey[i]);
				}
				else
				{
					SetDlgItemInt(nEditItemID+i,0);
				}

			}
		}
		else if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 192)
		{
			for(i = 0 ; i < 32; i ++)
			{
				if(i < 24)
				{
					SetDlgItemInt(nEditItemID+i,m_stuEncryption.stuEncryptKeys[nChennelID].byAesKey[i]);
				}
				else
				{
					SetDlgItemInt(nEditItemID+i,0);
				}
			}

		}
		else if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 256)
		{
			for(i = 0 ; i < 32; i++)
			{
				SetDlgItemInt(nEditItemID+i,m_stuEncryption.stuEncryptKeys[nChennelID].byAesKey[i]);
			}

		}
	}
	else if(m_stuEncryption.byEncrptAlgoType == 1)
	{
		for(i = 0 ; i < 32; i ++)
		{
			if(i < 8)
			SetDlgItemInt(nEditItemID+i,m_stuEncryption.stuEncryptKeys[nChennelID].byDesKey[i]);
			else
			SetDlgItemInt(nEditItemID+i,0);
		}

	}
	else if(m_stuEncryption.byEncrptAlgoType == 2) //3DES 2,3
	{
		if(m_stuEncryption.stuEncrptAlgoparam.wEncryptLenth == 2)
		{
			for(i = 0 ; i < 32; i ++)
			{
				if(i < 16)
					SetDlgItemInt(nEditItemID+i,m_stuEncryption.stuEncryptKeys[nChennelID].by3DesKey[i/8][i%8]);
				else
					SetDlgItemInt(nEditItemID+i,0);
			}
		}
		else
		{
			for(i = 0 ; i < 32; i ++)
			{
				if(i < 24)
					SetDlgItemInt(nEditItemID+i,m_stuEncryption.stuEncryptKeys[nChennelID].by3DesKey[i/8][i%8]);
				else
					SetDlgItemInt(nEditItemID+i,0);
			}

		}
	}	
}
void CStrategyEncryption::CleanAll()
{
	m_nChannelPreIndex = -1;
	m_ccbKeylength.SetCurSel(-1);
	m_ccbWorkmode.SetCurSel(-1);
	m_ccbChannel.SetCurSel(-1);	
	m_ccbEncryption.SetCurSel(-1);
	m_ctlEncrypt.SetCheck(0);
	int i;
	int nEditItemID = 1047;
	for(i = 0; i < 32; i ++)
	{
		SetDlgItemInt(i+nEditItemID,0);
	}
	while(m_ccbKeylength.GetCount())
	{
		m_ccbKeylength.DeleteString(0);
	}
	while(m_ccbChannel.GetCount())
	{
		m_ccbChannel.DeleteString(0);
	}
}
